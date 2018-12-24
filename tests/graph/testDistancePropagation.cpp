/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

/**
 * @file testDistancePropagation.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2012/06/18
 *
 * Functions for testing objects as graph.
 *
 * This file is part of the DGtal library.
 */
 
 ///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <set>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CanonicEmbedder.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/graph/CUndirectedSimpleGraph.h"
#include "DGtal/graph/CGraphVisitor.h"
#include "DGtal/graph/GraphVisitorRange.h"
#include "DGtal/graph/DistanceBreadthFirstVisitor.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/shapes/Shapes.h"
///////////////////////////////////////////////////////////////////////////////


using namespace std;
using namespace DGtal;
using namespace DGtal::concepts;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing objects as graph.
///////////////////////////////////////////////////////////////////////////////

typedef ImageSelector < Z2i::Domain, int>::Type Image;
bool testDistancePropagation()
{
  typedef Z2i::Space Space;
  typedef Z2i::Point Point;
  typedef Z2i::Domain Domain;
  typedef Z2i::DigitalSet DigitalSet;
  typedef Z2i::Object4_8 Object;
  
  BOOST_CONCEPT_ASSERT(( CUndirectedSimpleGraph<Z2i::Object4_8> ));

  trace.beginBlock( "Distance propagation in 2D object" );
  Point p1( -41, -36 );
  Point p2( 18, 18 );
  Domain domain( p1, p2 );
  Point c1( -2, -1 );
  Point c2( -14, 5 );
  Point c3( -30, -15 );
  Point c4( -10, -20 );
  Point c5( 12, -1 );
  DigitalSet shape_set( domain );
  
  Shapes<Domain>::addNorm2Ball( shape_set, c1, 9 );
  Shapes<Domain>::addNorm1Ball( shape_set, c2, 9 );
  Shapes<Domain>::addNorm1Ball( shape_set, c3, 10 );
  Shapes<Domain>::addNorm2Ball( shape_set, c4, 12 );
  Shapes<Domain>::addNorm1Ball( shape_set, c5, 4 );

  Object obj(Z2i::dt4_8, shape_set);
  
  
  GradientColorMap<int> cmap_grad( 0, 25);
  cmap_grad.addColor( Color( 0, 0, 255 ) );
  cmap_grad.addColor( Color( 0, 255, 0 ) );
  cmap_grad.addColor( Color( 255, 0, 0 ) );
  
  Board2D board;
  board << SetMode( domain.className(), "Paving" )
        << domain
        << SetMode( p1.className(), "Paving" );
  
  Image image = ImageFromSet<Image>::create(shape_set, 1);
  
  // Type definitions
  typedef CanonicEmbedder<Space> VertexEmbedder;
  typedef VertexEmbedder::Value RealPoint;
  typedef RealPoint::Coordinate Scalar;
  typedef ExactPredicateLpSeparableMetric<Space,2> Distance;
  using DistanceToPoint = std::function<double(const Space::Point &)>;
  typedef DGtal::functors::Composer<VertexEmbedder, DistanceToPoint, Scalar> VertexFunctor;
  typedef DistanceBreadthFirstVisitor< Object, VertexFunctor, std::set<Point> > Visitor;

  BOOST_CONCEPT_ASSERT(( CGraphVisitor<Visitor> ));


  VertexEmbedder embedder;
  Distance distance;
  DistanceToPoint distanceToPoint = std::bind(distance, embedder(c1), std::placeholders::_1);

  VertexFunctor vfunctor( embedder, distanceToPoint );
  Visitor visitor( obj, vfunctor, c1 );
  
  while( ! visitor.finished() )
    {
      Scalar v = visitor.current().second;
      image.setValue( visitor.current().first, v ); 
      visitor.expand();
    }
  
  string specificStyle = p1.className() + "/Paving";
  
  for ( DigitalSet::ConstIterator it = shape_set.begin();
        it != shape_set.end();
        ++it )
    {
      if( image(*it) == 0)
        board << CustomStyle( specificStyle,
                              new CustomColors( Color::Black,
                                                Color::Red ) );
      else if( image(*it) > 0 )
        board << CustomStyle( specificStyle,
                              new CustomColors( Color::Black,
                                                cmap_grad( image(*it) ) ) );
      else
        board << CustomStyle( specificStyle,
                              new CustomColors( Color::Black,
                                                cmap_grad( 0 ) ) );
      board << *it;
    }

  trace.info() << "- Output file testDistancePropagation.eps" << std::endl;
  board.saveEPS("testDistancePropagation.eps");
  trace.endBlock();

  trace.beginBlock( "Distance visitor as a range." );
  typedef GraphVisitorRange<Visitor> VisitorRange;
  VisitorRange range( new Visitor( obj, vfunctor, c1 ) );
  Scalar d = -1.0;
  unsigned int nb = 0;
  unsigned int nbok = 0;
  unsigned int nbperfect = 0;
  for ( VisitorRange::NodeConstIterator it = range.beginNode(), itEnd = range.endNode();
        it != itEnd; ++it )
    { // Vertex is *it.first
      Scalar next_d = (*it).second;
      ++nb; nbok += (next_d >= d-0.75 ) ? 1 : 0;
      nbperfect += (next_d >= d ) ? 1 : 0;
      d = next_d;
    }
  trace.info() << "(" << nbok << "/" << nb 
               << ") number of vertices in approximate Euclidean distance ordering."<< std::endl;
  trace.info() << "(" << nbperfect << "/" << nb 
               << ") number of vertices in perfect Euclidean distance ordering."<< std::endl;
  trace.endBlock();
  return nb == nbok;
}

int main( int /*argc*/, char** /*argv*/ )
{
  bool res = testDistancePropagation();
  return res ? 0 : 1;
}




