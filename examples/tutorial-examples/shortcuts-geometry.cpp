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
 * @file
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2018/06/26
 *
 * An example file named shortcuts.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ConfigExamples.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/helpers/Shortcuts.h"
#include "DGtal/helpers/ShortcutsGeometry.h"
#include "DGtal/base/Common.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int /* argc */, char** /* argv */ )
{
  unsigned int nb = 0, nbok = 0;
  // 3d tests
  typedef Shortcuts< Z3i::KSpace >         SH3;
  typedef ShortcutsGeometry< Z3i::KSpace > SHG3;

  trace.beginBlock ( "Load vol file -> build digital surface -> estimate mean curvature -> save OBJ." );
  {
    //! [dgtal_shortcuts_ssec2_1_6s]
    auto params    = SH3::defaultParameters() | SHG3::defaultParameters();
    params( "colormap", "Tics" );
    auto bimage    = SH3::makeBinaryImage( examplesPath + "samples/Al.100.vol", params );
    auto K         = SH3::getKSpace( bimage, params );
    auto surface   = SH3::makeDigitalSurface( bimage, K, params );
    auto surfels   = SH3::getSurfelRange( surface, params );
    auto curv      = SHG3::getIIMeanCurvatures( bimage, surfels, params );
    // To get Gauss curvatures, write instead:
    // auto curv = SHG3::getIIGaussianCurvatures( bimage, surfels, params );
    auto cmap      = SH3::getColorMap( -0.5, 0.5, params );
    auto colors    = SH3::Colors( surfels.size() );
    std::transform( curv.cbegin(), curv.cend(), colors.begin(), cmap );
    bool ok        = SH3::saveOBJ( surface, SH3::RealVectors(), colors,
				   "al-H-II.obj" );
    //! [dgtal_shortcuts_ssec2_1_6s]
    ++nb, nbok += ok ? 1 : 0;
  }
  trace.endBlock();

  trace.beginBlock ( "Load vol file -> build digital surface -> estimate Gauss curvature -> save OBJ." );
  {
    auto params    = SH3::defaultParameters() | SHG3::defaultParameters();
    params( "colormap", "Tics" );
    auto bimage    = SH3::makeBinaryImage( examplesPath + "samples/Al.100.vol", params );
    auto K         = SH3::getKSpace( bimage, params );
    auto surface   = SH3::makeDigitalSurface( bimage, K, params );
    auto surfels   = SH3::getSurfelRange( surface, params );
    auto curv      = SHG3::getIIGaussianCurvatures( bimage, surfels, params );
    auto cmap      = SH3::getColorMap( -0.25, 0.25, params );
    auto colors    = SH3::Colors( surfels.size() );
    std::transform( curv.cbegin(), curv.cend(), colors.begin(), cmap );
    bool ok        = SH3::saveOBJ( surface, SH3::RealVectors(), colors,
				   "al-G-II.obj" );
    ++nb, nbok += ok ? 1 : 0;
  }
  trace.endBlock();
  
  trace.beginBlock ( "Build polynomial shape -> digitize -> extract ground-truth geometry." );
  {
    auto params          = SH3::defaultParameters() | SHG3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_2_5s]
    params( "polynomial", "3*x^2+2*y^2+z^2-90" )( "gridstep", 0.25 );
    auto implicit_shape  = SH3::makeImplicitShape3D  ( params );
    auto digitized_shape = SH3::makeDigitizedImplicitShape3D( implicit_shape, params );
    auto binary_image    = SH3::makeBinaryImage      ( digitized_shape, params );
    auto K               = SH3::getKSpace( params );
    auto surface         = SH3::makeLightDigitalSurface( binary_image, K, params );
    auto surfels         = SH3::getSurfelRange( surface, params );
    auto positions       = SHG3::getPositions( implicit_shape, K, surfels, params );
    auto normals         = SHG3::getNormalVectors( implicit_shape, K, surfels, params );
    auto mean_curvs      = SHG3::getMeanCurvatures( implicit_shape, K, surfels, params );
    auto gauss_curvs     = SHG3::getGaussianCurvatures( implicit_shape, K, surfels, params );
    //! [dgtal_shortcuts_ssec2_2_5s]
    auto stat_mean       = SHG3::getStatistic( mean_curvs );
    auto stat_gauss      = SHG3::getStatistic( gauss_curvs );
    trace.info() << " min(H)=" << stat_mean.min()
		 << " avg(H)=" << stat_mean.mean()
		 << " max(H)=" << stat_mean.max() << std::endl;
    trace.info() << " min(G)=" << stat_gauss.min()
		 << " avg(G)=" << stat_gauss.mean()
		 << " max(G)=" << stat_gauss.max() << std::endl;
    ++nb, nbok += positions.size() == surfels.size() ? 1 : 0;
    ++nb, nbok += normals.size() == surfels.size() ? 1 : 0;
    ++nb, nbok += mean_curvs.size() == surfels.size() ? 1 : 0;
    ++nb, nbok += gauss_curvs.size() == surfels.size() ? 1 : 0;
    ++nb, nbok += stat_mean.min() > 0.08 ? 1 : 0;
    ++nb, nbok += stat_gauss.min() > 0.0064 ? 1 : 0;
  }
  trace.endBlock();

  trace.beginBlock ( "Build polynomial shape -> digitize -> get pointels -> save projected quadrangulated surface." );
  {
    auto params          = SH3::defaultParameters() | SHG3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_2_6s]
    const double h       = 0.25;
    params( "polynomial", "goursat" )( "gridstep", h );
    auto implicit_shape  = SH3::makeImplicitShape3D  ( params );
    auto digitized_shape = SH3::makeDigitizedImplicitShape3D( implicit_shape, params );
    auto binary_image    = SH3::makeBinaryImage      ( digitized_shape, params );
    auto K               = SH3::getKSpace( params );
    auto embedder        = SH3::getCellEmbedder( K );
    auto surface         = SH3::makeLightDigitalSurface( binary_image, K, params );
    SH3::Cell2Index c2i;
    auto pointels        = SH3::getPointelRange( c2i, surface );
    SH3::RealPoints pos( pointels.size() );
    std::transform( pointels.cbegin(), pointels.cend(), pos.begin(),
		    [&] (const SH3::Cell& c) { return h * embedder( c ); } ); 
    auto ppos     = SHG3::getPositions( implicit_shape, pos, params );
    bool ok       = SH3::saveOBJ( surface,
				  [&] (const SH3::Cell& c){ return ppos[ c2i[ c ] ];},
				  SH3::RealVectors(), SH3::Colors(),
				  "goursat-quad-proj.obj" );
    //! [dgtal_shortcuts_ssec2_2_6s]
    ++nb, nbok += ok ? 1 : 0;
  }
  trace.endBlock();

  trace.beginBlock ( "Build polynomial shape -> digitize -> extract mean curvature -> save as OBJ with colors." );
  {
    auto params          = SH3::defaultParameters() | SHG3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_2_7s]
    params( "polynomial", "goursat" )( "gridstep", 0.25 )( "colormap", "Tics" );
    auto implicit_shape  = SH3::makeImplicitShape3D  ( params );
    auto digitized_shape = SH3::makeDigitizedImplicitShape3D( implicit_shape, params );
    auto binary_image    = SH3::makeBinaryImage      ( digitized_shape, params );
    auto K               = SH3::getKSpace( params );
    auto surface         = SH3::makeLightDigitalSurface( binary_image, K, params );
    auto surfels         = SH3::getSurfelRange( surface, params );
    auto mean_curv       = SHG3::getMeanCurvatures( implicit_shape, K, surfels, params );
    auto cmap            = SH3::getColorMap( -0.3, 0.3, params );
    auto colors          = SH3::Colors( surfels.size() );
    std::transform( mean_curv.cbegin(), mean_curv.cend(), colors.begin(), cmap );
    bool ok              = SH3::saveOBJ( surface, SH3::RealVectors(), colors,
					 "goursat-H.obj" );
    //! [dgtal_shortcuts_ssec2_2_7s]
    ++nb, nbok += ok ? 1 : 0;
  }
  trace.endBlock();

  trace.beginBlock ( "Build polynomial shape -> digitize -> extract ground-truth and estimated mean curvature -> display errors in OBJ with colors." );
  {
    auto params          = SH3::defaultParameters() | SHG3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_2_8s]
    params( "polynomial", "goursat" )( "gridstep", 0.25 )( "colormap", "Tics" )
      ( "R-radius", 5.0 );
    auto implicit_shape  = SH3::makeImplicitShape3D  ( params );
    auto digitized_shape = SH3::makeDigitizedImplicitShape3D( implicit_shape, params );
    auto bimage          = SH3::makeBinaryImage      ( digitized_shape, params );
    auto K               = SH3::getKSpace( params );
    auto surface         = SH3::makeLightDigitalSurface( bimage, K, params );
    auto surfels         = SH3::getSurfelRange( surface, params );
    auto t_curv          = SHG3::getMeanCurvatures( implicit_shape, K, surfels, params );
    auto ii_curv         = SHG3::getIIMeanCurvatures( bimage, surfels, params );
    auto cmap            = SH3::getColorMap( -0.5, 0.5, params );
    auto colors          = SH3::Colors( surfels.size() );
    std::transform( t_curv.cbegin(),  t_curv.cend(),  colors.begin(), cmap );
    bool ok_t  = SH3::saveOBJ( surface, SH3::RealVectors(), colors, "goursat-H.obj" );
    std::transform( ii_curv.cbegin(), ii_curv.cend(), colors.begin(), cmap );
    bool ok_ii = SH3::saveOBJ( surface, SH3::RealVectors(), colors, "goursat-H-ii.obj" );
    auto errors          = SHG3::getScalarsAbsoluteDifference( t_curv, ii_curv );
    auto stat_errors     = SHG3::getStatistic( errors );
    auto cmap_errors     = SH3::getColorMap( 0.0, stat_errors.max(), params );
    std::transform( errors.cbegin(), errors.cend(), colors.begin(), cmap_errors );
    bool ok_err = SH3::saveOBJ( surface, SH3::RealVectors(), colors, "goursat-H-ii-err.obj" );
    trace.info() << "Error Loo=" << SHG3::getScalarsNormLoo( t_curv, ii_curv )
		 << " L1="       << SHG3::getScalarsNormL1 ( t_curv, ii_curv )
		 << " L2="       << SHG3::getScalarsNormL2 ( t_curv, ii_curv )
		 << std::endl;
    //! [dgtal_shortcuts_ssec2_2_8s]
    ++nb, nbok += ( ok_t && ok_ii && ok_err ) ? 1 : 0;
  }
  trace.endBlock();
    
  trace.beginBlock ( "Build polynomial shape -> digitize -> build digital surface -> save primal surface with VCM normals as obj." );
  {
    auto params          = SH3::defaultParameters() | SHG3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_2_9s]
    params( "polynomial", "goursat" )( "gridstep", 0.25 )
      ( "Traversal", "Default" );
    auto implicit_shape  = SH3::makeImplicitShape3D  ( params );
    auto digitized_shape = SH3::makeDigitizedImplicitShape3D( implicit_shape, params );
    auto K               = SH3::getKSpace( params );
    auto binary_image    = SH3::makeBinaryImage( digitized_shape, params );
    auto surface         = SH3::makeDigitalSurface( binary_image, K, params );
    auto surfels         = SH3::getSurfelRange( surface, params );
    auto vcm_normals     = SHG3::getVCMNormalVectors( surface, surfels, params );
    bool ok              = SH3::saveOBJ( surface, vcm_normals, SH3::Colors(),
					 "goursat-primal-vcm.obj" );
    //! [dgtal_shortcuts_ssec2_2_9s]
    ++nb, nbok += ok ? 1 : 0;
  }
  trace.endBlock();

  trace.beginBlock ( "Build polynomial shape -> digitize implicitly -> estimate II normals and curvature." );
  {
    auto params          = SH3::defaultParameters() | SHG3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_2_10s]
    params( "polynomial", "goursat" )( "gridstep", .25 );
    auto implicit_shape  = SH3::makeImplicitShape3D     ( params );
    auto dig_shape       = SH3::makeDigitizedImplicitShape3D( implicit_shape, params );
    auto K               = SH3::getKSpace               ( params );
    auto surface         = SH3::makeDigitalSurface      ( dig_shape, K, params );
    auto surfels         = SH3::getSurfelRange          ( surface, params( "surfaceTraversal", "DepthFirst" ) );
    auto def_surfels     = SH3::getSurfelRange          ( surface, params( "surfaceTraversal", "Default" ) );
    auto ii_normals      = SHG3::getIINormalVectors     ( dig_shape, surfels, params );
    trace.beginBlock( "II with default traversal (slower)" );
    auto ii_mean_curv    = SHG3::getIIMeanCurvatures    ( dig_shape, def_surfels, params );
    trace.endBlock();
    trace.beginBlock( "II with depth-first traversal (faster)" );
    auto ii_mean_curv2   = SHG3::getIIMeanCurvatures    ( dig_shape, surfels, params );
    trace.endBlock();
    auto cmap            = SH3::getColorMap             ( -0.5, 0.5, params );
    auto colors          = SH3::Colors                  ( def_surfels.size() );
    auto match           = SH3::getRangeMatch           ( def_surfels, surfels );
    auto normals         = SH3::getMatchedRange         ( ii_normals, match );
    for ( SH3::Idx i = 0; i < colors.size(); i++ )
      colors[ i ] = cmap( ii_mean_curv[ match[ i ] ] ); 
    bool ok_H  = SH3::saveOBJ( surface, SH3::RealVectors(), colors, "goursat-imp-H-ii.obj" );
    //! [dgtal_shortcuts_ssec2_2_10s]
    ++nb, nbok += ( ok_H && ii_mean_curv.size() == ii_mean_curv2.size() ) ? 1 : 0;
  }
  trace.endBlock();

  trace.beginBlock ( "Build polynomial shape -> save several projected quadrangulated surface and digitized boundaries." );
  {
    auto params          = SH3::defaultParameters() | SHG3::defaultParameters();
    std::vector<double> gridsteps {0.5, 0.25, 0.125};
    for ( auto h : gridsteps ) {
      params( "polynomial", "goursat" )( "gridstep", h );
      auto implicit_shape  = SH3::makeImplicitShape3D  ( params );
      auto digitized_shape = SH3::makeDigitizedImplicitShape3D( implicit_shape, params );
      auto binary_image    = SH3::makeBinaryImage      ( digitized_shape, params );
      auto K               = SH3::getKSpace( params );
      auto embedder        = SH3::getCellEmbedder( K );
      auto surface         = SH3::makeLightDigitalSurface( binary_image, K, params );
      SH3::Cell2Index c2i;
      auto pointels        = SH3::getPointelRange( c2i, surface );
      SH3::RealPoints pos( pointels.size() );
      std::transform( pointels.cbegin(), pointels.cend(), pos.begin(),
		      [&] (const SH3::Cell& c) { return h * embedder( c ); } ); 
      auto ppos       = SHG3::getPositions( implicit_shape, pos, params );
      auto fname      = std::string( "goursat-quad-" ) + std::to_string( h ) + std::string( ".obj" );
      bool ok         = SH3::saveOBJ( surface,
				      [&] (const SH3::Cell& c){ return pos[ c2i[ c ] ];},
				      SH3::RealVectors(), SH3::Colors(),
				      fname );
      auto proj_fname = std::string( "goursat-quad-proj-" ) + std::to_string( h ) + std::string( ".obj" );
      bool proj_ok    = SH3::saveOBJ( surface,
				      [&] (const SH3::Cell& c){ return ppos[ c2i[ c ] ];},
				      SH3::RealVectors(), SH3::Colors(),
				      proj_fname );
      ++nb, nbok += ok      ? 1 : 0;
      ++nb, nbok += proj_ok ? 1 : 0;
    }
  }
  trace.endBlock();

  
  trace.info() << nbok << "/" << nb << " passed tests." << std::endl;
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
