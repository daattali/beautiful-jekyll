/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/

/**
* @file testProjection.cpp
* @ingroup Tests
* @author Thomas Caissard (\c thomas.caissard@liris.cnrs.fr )
*
* @date 2016/05/05
*
* Tests of projections functions in starshape.
*
* This file is part of the DGtal library.
*/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/helpers/StdDefs.h"

#include "DGtal/topology/SurfelAdjacency.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/helpers/BoundaryPredicate.h"
#include "DGtal/topology/SetOfSurfels.h"
#include "DGtal/topology/SCellsFunctors.h"

#include "DGtal/shapes/Shapes.h"
#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/GaussDigitizer.h"

#include "DGtal/io/boards/Board2D.h"

#include "DGtalCatch.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :/

double angle(const DGtal::Z2i::RealPoint& point)
{
  double angle = atan2(point[1], point[0]);
  if(angle < 0.) angle += 2. * M_PI;
  return angle;
}

double angle(const DGtal::Z2i::KSpace& kspace, const DGtal::Z2i::SCell& cell, const double h)
{
  DGtal::CanonicSCellEmbedder<DGtal::Z2i::KSpace> emb(kspace);
  return angle(h * emb(cell));
}

struct AngleLessCell
{
  typedef DGtal::Z2i::KSpace KSpace;
  typedef KSpace::SCell SCell;
  typedef KSpace::Point Point;

  AngleLessCell(const KSpace& kspace, const double h) : _kspace(kspace), _h(h)
  {
  }

  inline bool operator()(const SCell& a, const SCell& b) const
  {
      return angle(_kspace, a, _h) < angle(_kspace, b, _h);
  }

  const KSpace& _kspace;
  const double _h;
};

Domain domain;

template <typename Shape>
void digitize(Shape& shape, std::vector<SCell>& sCells0, std::vector<SCell>& sCells1, KSpace& kspace, const double h)
{
  // -------------------------------------------------------------------------- Type declaring
  typedef typename DGtal::GaussDigitizer<Space, Shape> Digitizer;
  typedef SurfelAdjacency<2> SurfelAdj;
  typedef Surfaces<KSpace> Surf;

  sCells0.clear();
  sCells1.clear();

  // -------------------------------------------------------------------------- Creating the shape
  Digitizer digitizer;
  digitizer.attach(shape);
  digitizer.init(shape.getLowerBound() + Vector(-1,-1), shape.getUpperBound() + Vector(1,1), h);
  domain = digitizer.getDomain();

  kspace.init(digitizer.getLowerBound(), digitizer.getUpperBound(), true);

  const SurfelAdj surfel_adjacency(true);
  const KSpace::SCell cell_bel = Surf::findABel(kspace, digitizer);
  Surf::track2DBoundary(sCells1, kspace, surfel_adjacency, digitizer, cell_bel);
  {
    typedef std::vector<Point> Points;
    Points points;
    Surf::track2DBoundaryPoints(points, kspace, surfel_adjacency, digitizer, cell_bel);
    const KSpace::SCell point_ref = kspace.sCell(Point(0,0));
    for(Points::const_iterator pi = points.begin(), pe = points.end(); pi != pe; ++pi) sCells0.push_back(kspace.sCell(*pi, point_ref));
  }

  std::sort(sCells0.begin(), sCells0.end(), AngleLessCell(kspace, h));
  std::sort(sCells1.begin(), sCells1.end(), AngleLessCell(kspace, h));

  ASSERT(sCells0.size() == sCells1.size());
}

template <typename Shape>
bool test_shape(Shape& shape, const double h, const double epsilon)
{
  std::vector<SCell> sCells0, sCells1;

  KSpace kspace;

  digitize(shape, sCells0, sCells1, kspace, h);

  CanonicSCellEmbedder<KSpace> canonicSCellEmbedder(kspace);

  for(unsigned int i = 0; i < sCells0.size(); i++)
  {
  	functors::SCellToInnerPoint<KSpace> sCellToInnerPoint(kspace);
    functors::SCellToOuterPoint<KSpace> sCellToOuterPoint(kspace);

    const int prev = ( i + sCells0.size() - 3 ) % sCells0.size(), next = (i + 3) % sCells0.size();

    RealPoint inner_prev = sCellToInnerPoint( sCells0[prev] );
    RealPoint outer_prev = sCellToOuterPoint( sCells0[prev] );

    RealPoint inner_next = sCellToInnerPoint( sCells0[next] );
    RealPoint outer_next = sCellToOuterPoint( sCells0[next] );

    inner_prev *= h;
    inner_next *= h;

    outer_prev *= h;
    outer_next *= h;

    RealPoint q_prev = shape.findIntersection(inner_prev, outer_prev, epsilon);
    RealPoint q_next = shape.findIntersection(inner_next, outer_next, epsilon);
    RealPoint p = shape.closestPointWithWitnesses(h * canonicSCellEmbedder( sCells0[i] ), q_prev, q_next, 300);

    const double norm2 = (p - h * canonicSCellEmbedder( sCells0[i]) ).norm();

    if ( norm2 > sqrt(2.) * h)
        return false;
  }

  return true;
}

TEST_CASE( "Projection test on various shapes" )
{
  typedef Ball2D<Space> Ball;
  const Ball ball(Point(0,0), 1.0);

  typedef Flower2D<Space> Flower2D;
  const Flower2D flower2D(Point(0,0), 1., 0.3, 5, 0.);

  typedef AccFlower2D<Space> AccFlower2D;
  const AccFlower2D accFlower2D(Point(0,0), 1., 0.3, 5, 0.);

  typedef Ellipse2D<Space> Ellipse2D;
  const Ellipse2D ellipse2D(Point(0,0), 1., 0.4, 0.2);

  double h = 0.1;

  SECTION( "Actual test" )
  {
      while(h > 0.01)
      {
        REQUIRE( test_shape( ball, h, h * 0.01 ) );
        REQUIRE( test_shape( flower2D, h, h * 0.01 ) );
        REQUIRE( test_shape( ellipse2D, h, h * 0.01 ) );
        h /= 1.3;
      }
  }
}
