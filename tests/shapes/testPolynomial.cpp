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
 * @file testPolynomial.cpp
 * @ingroup tests
 * @author Anis Benyoub (anis.benyoub@insa-lyon.fr)
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/06/21
 *
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/SetOfSurfels.h"
#include "DGtal/math/MPolynomial.h"
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/shapes/implicit/ImplicitPolynomial3Shape.h"
#include "DGtal/shapes/implicit/ImplicitFunctionDiff1LinearCellEmbedder.h"
#include "DGtal/io/readers/MPolynomialReader.h"
#include "DGtal/topology/SCellsFunctors.h"
#include "DGtal/topology/helpers/BoundaryPredicate.h"
#include "DGtal/topology/SetOfSurfels.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include <boost/math/special_functions/fpclassify.hpp>

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////


void usage( int /*argc*/, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <Polynomial> <Px> <Py> <Pz> <Qx> <Qy> <Qz> <step>" << std::endl;
  std::cerr << "\t - displays the boundary of a shape defined implicitly by a 3-polynomial <Polynomial>." << std::endl;
  std::cerr << "\t - P and Q defines the bounding box." << std::endl;
  std::cerr << "\t - step is the grid step." << std::endl;
  std::cerr << "\t - You may try x^3y+xz^3+y^3z+z^3+5z or (y^2+z^2-1)^2 +(x^2+y^2-1)^3 " << std::endl;
  std::cerr << "\t - See http://www.freigeist.cc/gallery.html" << std::endl;
}
  
  typedef Space::RealPoint RealPointT;
  typedef RealPointT::Coordinate Ring;
  typedef MPolynomial<3, Ring> Polynomial3;
  typedef MPolynomialReader<3, Ring> Polynomial3Reader;
  typedef ImplicitPolynomial3Shape<Space> ImplicitShape;
  typedef GaussDigitizer<Space,ImplicitShape> DigitalShape;
  typedef DigitalShape::PointEmbedder DigitalEmbedder;



int main( int argc, char** argv )
{
  if ( argc < 9 )
  {
    usage( argc, argv );
    return 1;
  }
  double p1[ 3 ];
  double p2[ 3 ];
  for ( unsigned int i = 0; i < 3; ++i )
  {
    p1[ i ] = atof( argv[ 2 + i ] );
    p2[ i ] = atof( argv[ 5 + i ] );
  }
  double step = atof( argv[ 8 ] );


  Polynomial3 P;
  Polynomial3Reader reader;
  std::string poly_str = argv[ 1 ];
  std::string::const_iterator iter
      = reader.read( P, poly_str.begin(), poly_str.end() );
  if ( iter != poly_str.end() )
  {
    std::cerr << "ERROR: I read only <"
              << poly_str.substr( 0, iter - poly_str.begin() )
              << ">, and I built P=" << P << std::endl;
    return 1;
  }


  ImplicitShape ishape( P );
  DigitalShape dshape;
  dshape.attach( ishape );
  dshape.init( RealPointT( p1 ), RealPointT( p2 ), step );
  Domain domain = dshape.getDomain();


  KSpace K;

  bool space_ok = K.init( domain.lowerBound(),
                          domain.upperBound(), true
                          );
  if ( !space_ok )
  {
    trace.error() << "Error in the Khamisky space construction." << std::endl;
    return 2;
  }

  typedef SurfelAdjacency< KSpace::dimension > MySurfelAdjacency;
  MySurfelAdjacency surfAdj( true ); // interior in all directions.


  typedef KSpace::Surfel Surfel;
  typedef KSpace::SurfelSet SurfelSet;
  typedef SetOfSurfels< KSpace, SurfelSet > MySetOfSurfels;

  MySetOfSurfels theSetOfSurfels( K, surfAdj );
  Surfel bel = Surfaces< KSpace >::findABel( K, dshape, 100000 );
  Surfaces< KSpace >::trackBoundary( theSetOfSurfels.surfelSet(),
                                   K, surfAdj,
                                   dshape, bel );




  QApplication application( argc, argv );
  Viewer3D<> viewer;
  viewer.show();
  viewer << SetMode3D( domain.className(), "BoundingBox" ) << domain;




  //-----------------------------------------------------------------------
  // Looking for the min and max values

  double minCurv = 1;
  double maxCurv = 0;
  CanonicSCellEmbedder< KSpace > midpoint( K );
  for ( std::set< SCell >::iterator it = theSetOfSurfels.begin(), it_end = theSetOfSurfels.end();
        it != it_end; ++it)
  {

    RealPointT A = midpoint( *it ) * step;
    A = ishape.nearestPoint (A,0.01,200,0.1*step);
    double a = ishape.meanCurvature( A );
//    double a=ishape.gaussianCurvature(A);
    if ( !boost::math::isnan( a ))
    {

     if ( a > maxCurv )
      {
        maxCurv = a;
      }
      else
        if ( a < minCurv )
        {
          minCurv = a;
        }
    }
  }
  trace.info() << " Min = " << minCurv << std::endl;
  trace.info() << " Max = " << maxCurv << std::endl;


  //-----------------------------------------------------------------------
  //Specifing a color map

  GradientColorMap< double > cmap_grad( minCurv, maxCurv );
  cmap_grad.addColor( Color( 50, 50, 255 ) );
  cmap_grad.addColor( Color( 255, 0, 0 ) );
  cmap_grad.addColor( Color( 255, 255, 10 ) );

  //------------------------------------------------------------------------------------
  //drawing
  unsigned int nbSurfels = 0;

  for ( std::set<SCell>::iterator it = theSetOfSurfels.begin(),
        it_end = theSetOfSurfels.end();
        it != it_end; ++it, ++nbSurfels )
  {


    RealPointT A = midpoint( *it ) * step;
    A = ishape.nearestPoint (A,0.01,200,0.1*step);
//    double a=ishape.gaussianCurvature(A);
    double a = ishape.meanCurvature( A );
    if ( boost::math::isnan( a ))
    {
      a = 0;
    }

    viewer << CustomColors3D( Color::Black, cmap_grad( a ));
    viewer << *it;
  }

  viewer << Viewer3D<>::updateDisplay;

  return application.exec();
}
