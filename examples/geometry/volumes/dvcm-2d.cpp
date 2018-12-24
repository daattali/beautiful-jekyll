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
 * @file geometry/volumes/dvcm-2d.cpp
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2014/04/15
 *
 * Computes the Voronoi Covariance Measure of a list of 2D digital
 * points. Displays the resulting normal vector and feature detection.
 *
 * This file is part of the DGtal library.
 */

/**
This example shows the computation of the VCM of a set of 2D
digital points. The normal is estimated from the diagonalization of
the VCM tensor. Feature detection is achieved with the eigenvalues
of the VCM. A red color indicates a feature. Normals are displayed
as arrows.

@see \ref moduleVCM_sec2

@verbatim
$ ./examples/geometry/volumes/dvcm-2d
@endverbatim

@image html dvcm-hat-r.png "Normal vector and feature detection with Voronoi Covariance Measure."
@image latex dvcm-hat-r.png "Normal vector and feature detection with Voronoi Covariance Measure." width=8cm

\example geometry/volumes/dvcm-2d.cpp
*/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/BasicPointPredicates.h"
#include "DGtal/math/linalg/EigenDecomposition.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/estimation/VoronoiCovarianceMeasure.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/io/boards/Board2D.h"
#include "ConfigExamples.h"


///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
int main( int /* argc */, char** /* argv */ )
{
  typedef Z2i::Space Space;
  typedef Z2i::Point Point;
  typedef Z2i::RealPoint RealPoint;
  typedef Z2i::RealVector RealVector;
  typedef HyperRectDomain<Space> Domain;
  typedef ExactPredicateLpSeparableMetric<Space, 2> Metric; // L2-metric
  typedef EigenDecomposition<2,double> LinearAlgebraTool;
  typedef LinearAlgebraTool::Matrix Matrix;

  typedef VoronoiCovarianceMeasure<Space,Metric> VCM;
  typedef functors::HatPointFunction<Point,double> KernelFunction;

  // Gets the points
  vector<unsigned int> vPos;
  vPos.push_back(0);
  vPos.push_back(1);
  string inputSDP = examplesPath + "samples/flower-30-8-3.sdp";
  // string inputSDP = examplesPath + "samples/ellipse-20-7-0.4.sdp";
  // string inputSDP = examplesPath + "samples/accflower-20-5-5-0.1.sdp";
  trace.info() << "Reading input 2d discrete points file: " << inputSDP; 
  std::vector<Point> pts = PointListReader<Point>::getPointsFromFile(inputSDP, vPos); 
  trace.info() << " [done] " << std::endl ; 
  const double R = 20;
  trace.info() << "Big radius   R = " << R << std::endl;
  const double r = 5;
  trace.info() << "Small radius r = " << r << std::endl;
  const double T = 0.1;
  trace.info() << "Feature thres. T = " << T << std::endl; // threshold for displaying features as red.
  const double size = 3.0; // size of displayed normals

  Metric l2;
  VCM vcm( R, ceil( r ), l2, true );
  vcm.init( pts.begin(), pts.end() );
  Domain domain = vcm.domain();
  KernelFunction chi( 1.0, r );

  // Flat zones are metallic blue, slightly curved zones are white,
  // more curved zones are yellow till red.
  GradientColorMap<double> colormap( 0.0, T );
  colormap.addColor( Color( 128, 128, 255 ) );
  colormap.addColor( Color( 255, 255, 255 ) );
  colormap.addColor( Color( 255, 255, 0 ) );
  colormap.addColor( Color( 255, 0, 0 ) );
  Board2D board;
  Matrix vcm_r, evec;
  RealVector eval;
  for ( std::vector<Point>::const_iterator it = pts.begin(), itE = pts.end();
        it != itE; ++it )
    {
      // Compute VCM and diagonalize it.
      vcm_r = vcm.measure( chi, *it );
      LinearAlgebraTool::getEigenDecomposition( vcm_r, evec, eval );
      double feature = eval[ 0 ] / ( eval[ 0 ] +  eval[ 1 ] );
      board << CustomStyle( it->className(), 
                            new CustomColors( Color::Black,  colormap( feature > T ? T : feature ) ) )
            << *it;
      // Display normal
      RealVector normal = evec.column( 1 );
      RealPoint p( (*it)[ 0 ], (*it)[ 1 ] ); 
      Display2DFactory::draw( board, size*normal, p );
      Display2DFactory::draw( board, -size*normal, p );
    }      
  board.saveSVG("dvcm-hat-r.svg");

  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
