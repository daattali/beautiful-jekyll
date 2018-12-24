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
 * @file geometry/surfaces/dvcm-2d-curvature.cpp
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
This example shows the computation of the VCM of a sequence of 2D
digital points forming a 4-connected curve. The absolute curvature is estimated from the diagonalization of
the VCM tensor. A red color indicates a strong curvature, flat zones are blue, in-between is yellow.

@see \ref moduleVCM_sec3_2

@verbatim
$ ./examples/geometry/surfaces/dvcm-2d-curvature
@endverbatim

@image html dvcm-curvature.png "Absolute curvature estimation with Voronoi Covariance Measure."
@image latex dvcm-curvature.png "Absolute curvature estimation with Voronoi Covariance Measure." width=8cm

\example geometry/surfaces/dvcm-2d-curvature.cpp
*/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/SetOfSurfels.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/geometry/curves/GridCurve.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/estimation/VoronoiCovarianceMeasure.h"
#include "DGtal/geometry/surfaces/estimation/VoronoiCovarianceMeasureOnDigitalSurface.h"
#include "DGtal/geometry/surfaces/estimation/VCMDigitalSurfaceLocalEstimator.h"
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
  typedef Z2i::KSpace KSpace;
  typedef Z2i::Curve Curve;
  typedef Z2i::Point Point;
  typedef ExactPredicateLpSeparableMetric<Space, 2> Metric; // L2-metric

  typedef Curve::SCellsRange LinelRange;
  typedef SetOfSurfels<KSpace> DigitalSurfaceContainer;
  typedef DigitalSurface<DigitalSurfaceContainer> Surface;
  typedef functors::BallConstantPointFunction<Point,double> KernelFunction;
  typedef VoronoiCovarianceMeasureOnDigitalSurface<DigitalSurfaceContainer,Metric,KernelFunction> VCMOnSurface;
  typedef functors::VCMAbsoluteCurvatureFunctor<VCMOnSurface> CurvatureFunctor;
  typedef VCMDigitalSurfaceLocalEstimator<DigitalSurfaceContainer,Metric,
                                          KernelFunction, CurvatureFunctor> VCMCurvatureEstimator;

  // Transform a 4-connected sequence of discrete points into a digital surface.
  //string inputSDP = examplesPath + "samples/flower-30-8-3.sdp";
  //string inputSDP = examplesPath + "samples/ellipse-20-7-0.4.sdp";
  //string inputSDP = examplesPath + "samples/accflower-20-5-5-0.1.sdp";
  string inputSDP = examplesPath + "samples/circle-43.sdp";
  trace.info() << "Reading input 2d discrete points file: " << inputSDP; 
  KSpace ks; ks.init( Point( -1000, -1000 ), Point( 1000, 1000 ), true );
  Curve curve( ks ); 
  fstream inputStream( inputSDP.c_str(), ios::in);
  curve.initFromVectorStream(inputStream);
  inputStream.close();
  DigitalSurfaceContainer* container 
    = new DigitalSurfaceContainer( ks,  SurfelAdjacency<KSpace::dimension>( true ) );
  LinelRange range = curve.getSCellsRange();
  for ( LinelRange::ConstIterator it = range.begin(), itE = range.end(); it != itE; ++it )
    container->surfelSet().insert( *it );
  CountedConstPtrOrConstPtr<Surface> ptrSurface( new Surface( container ) ); // acquired
  trace.info() << " [done] " << std::endl ; 
  const double R = 40;
  trace.info() << "Big radius   R = " << R << std::endl;
  const double r = 20;
  trace.info() << "Small radius r = " << r << std::endl;
  const double T = 0.2;
  trace.info() << "Curvature thres. T = " << T << std::endl; // threshold for displaying features as red.

  Metric l2;
  KernelFunction chi( 1.0, r );
  VCMCurvatureEstimator estimator( ptrSurface );
  estimator.setParams( Pointels, R, r, chi, 3.0, l2, true );
  estimator.init( 1.0, ptrSurface->begin(), ptrSurface->end() );

  // Flat zones are blue, more curved zones are yellow till red.
  GradientColorMap<double> colormap( 0, T );
  colormap.addColor( Color::Blue );
  colormap.addColor( Color::Yellow );
  colormap.addColor( Color::Red );
  Board2D board;
  for ( Surface::ConstIterator it = ptrSurface->begin(), itE = ptrSurface->end();
        it != itE; ++it )
    {
      double curv = estimator.eval( it );
      curv = std::min( T, curv );
      board << CustomStyle( it->className(), 
                            new CustomColors( colormap( curv ),  colormap( curv ) ) )
            << *it;
      std::cout << curv << std::endl;
    }      
  board.saveSVG("dvcm-curvature.svg");

  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
