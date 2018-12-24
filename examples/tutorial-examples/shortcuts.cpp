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
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/helpers/Shortcuts.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int /* argc */, char** /* argv */ )
{
  unsigned int nb = 0, nbok = 0;
  // Using standard 3D digital space.
  typedef Shortcuts<Z3i::KSpace> SH3;

  // 3d tests
  trace.beginBlock ( "Load vol file -> noisify -> save as vol file." );
  {
    auto params    = SH3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_1_1s]
    // load and noisify image directly.
    auto al_capone = SH3::makeBinaryImage( examplesPath + "samples/Al.100.vol",
					   params( "noise", 0.3 ) );
    auto ok        = SH3::saveBinaryImage( al_capone, "noisy-Al.vol" );
    //! [dgtal_shortcuts_ssec2_1_1s]
    ++nb, nbok += ok ? 1 : 0; 
  }
  trace.endBlock();
  trace.beginBlock ( "Load vol file -> build main connected digital surface." );
  {
    auto params    = SH3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_1_2s]
    auto al_capone = SH3::makeBinaryImage( examplesPath + "samples/Al.100.vol", params );
    auto K         = SH3::getKSpace( al_capone );
    auto surface   = SH3::makeLightDigitalSurface( al_capone, K, params );
    trace.info() << "#surfels=" << surface->size() << std::endl;
    //! [dgtal_shortcuts_ssec2_1_2s]
    ++nb, nbok += surface->size() == 21239 ? 1 : 0; 
  }
  trace.endBlock();

  trace.beginBlock ( "Load vol file -> extract 2 isosurfaces -> build mesh" );
  {
    auto params    = SH3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_1_3s]
    params( "faceSubdivision", "Centroid" )( "surfelAdjacency", 1);
    auto gimage    = SH3::makeGrayScaleImage( examplesPath + "samples/lobster.vol" );
    auto trisurf150= SH3::makeTriangulatedSurface( gimage, params( "thresholdMin", 150 ) );
    auto trisurf40 = SH3::makeTriangulatedSurface( gimage, params( "thresholdMin", 40 ) );
    auto mesh150   = SH3::makeMesh( trisurf150 );
    auto mesh40    = SH3::makeMesh( trisurf40 );
    trace.info() << "#mesh150=" << mesh150->nbVertex()
		 << " #mesh40=" << mesh40->nbVertex() << std::endl;
    //! [dgtal_shortcuts_ssec2_1_3s]
    ++nb, nbok += ( mesh150->nbVertex() < mesh40->nbVertex() )
      && ( mesh40->nbVertex() == 273182 ) ? 1 : 0;
  }
  trace.endBlock();

  trace.beginBlock ( "Load vol file -> extract 2 triangulated isosurfaces -> save as OBJ." );
  {
    auto params    = SH3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_1_4s]
    params( "faceSubdivision", "Centroid" )( "surfelAdjacency", 1);
    auto gimage    = SH3::makeGrayScaleImage( examplesPath + "samples/lobster.vol" );
    auto trisurf150= SH3::makeTriangulatedSurface( gimage, params( "thresholdMin", 150 ) );
    auto trisurf40 = SH3::makeTriangulatedSurface( gimage, params( "thresholdMin", 40 ) );
    auto ok40      = SH3::saveOBJ( trisurf40, SH3::RealVectors(), SH3::Colors(),
				   "lobster-40.obj", // semi-transparent red diffuse color
				   SH3::Color( 30,30,30 ), SH3::Color( 255,0,0,100 ) );
    auto ok150     = SH3::saveOBJ( trisurf150, SH3::RealVectors(), SH3::Colors(),
				   "lobster-150.obj", // opaque blue diffuse color
				   SH3::Color( 30,30,30 ), SH3::Color( 0,0,255,255 ) );
    //! [dgtal_shortcuts_ssec2_1_4s]
    ++nb, nbok += ok40  ? 1 : 0;
    ++nb, nbok += ok150 ? 1 : 0;
  }
  trace.endBlock();

  trace.beginBlock ( "Load vol file -> build main digital surface -> breadth first traversal -> save OBJ with colored distance." );
  {
    auto params    = SH3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_1_5s]
    params( "surfaceTraversal", "BreadthFirst" ) // specifies breadth-first traversal
      ( "colormap", "Jet" ); // specifies the colormap
    auto al_capone = SH3::makeBinaryImage( examplesPath + "samples/Al.100.vol", params );
    auto K         = SH3::getKSpace( al_capone );
    auto surface   = SH3::makeLightDigitalSurface( al_capone, K, params );
    auto surfels   = SH3::getSurfelRange( surface, params );
    auto cmap      = SH3::getColorMap( 0, surfels.size(), params );
    SH3::Colors colors( surfels.size() );
    for ( unsigned int i = 0; i < surfels.size(); ++i ) colors[ i ] = cmap( i );
    bool ok        = SH3::saveOBJ( surface, SH3::RealVectors(), colors, "al-primal-bft.obj" );
    //! [dgtal_shortcuts_ssec2_1_5s]
    ++nb, nbok += ok ? 1 : 0; 
  }
  trace.endBlock();

  trace.beginBlock ( "Build polynomial shape -> digitize -> noisify -> save as vol file." );
  {
    auto params          = SH3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_2_1s]
    params( "polynomial", "3*x^2+2*y^2+z^2-90" )( "gridstep", 0.25 ) 
      ( "noise", 0.3 );
    auto implicit_shape  = SH3::makeImplicitShape3D( params );
    auto digitized_shape = SH3::makeDigitizedImplicitShape3D( implicit_shape, params );
    auto noisy_shape     = SH3::makeBinaryImage    ( digitized_shape, params );
    auto ok              = SH3::saveBinaryImage    ( noisy_shape, "noisy-ellipsoid.vol" );
    //! [dgtal_shortcuts_ssec2_2_1s]
    ++nb, nbok += ok ? 1 : 0;
  }
  trace.endBlock();

  trace.beginBlock ( "Build polynomial shape -> digitize -> build digital surface -> save primal surface as obj." );
  {
    auto params          = SH3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_2_2s]
    params( "polynomial", "goursat" )( "gridstep", 0.25 );
    auto implicit_shape  = SH3::makeImplicitShape3D  ( params );
    auto digitized_shape = SH3::makeDigitizedImplicitShape3D( implicit_shape, params );
    auto K               = SH3::getKSpace( params );
    auto binary_image    = SH3::makeBinaryImage( digitized_shape, params );
    auto surface         = SH3::makeDigitalSurface( binary_image, K, params );
    bool ok              = SH3::saveOBJ( surface, "goursat-primal.obj" );
    //! [dgtal_shortcuts_ssec2_2_2s]
    ++nb, nbok += ok ? 1 : 0;
  }
  trace.endBlock();

  trace.beginBlock ( "Build polynomial shape -> digitize -> build indexed surface on a subpart." );
  {
    auto params          = SH3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_2_3s]
    params( "polynomial", "leopold" )( "gridstep", 0.25 )
      ( "minAABB", -12.0 )( "maxAABB", 12.0 )
      ( "surfaceComponents", "All" );
    auto implicit_shape  = SH3::makeImplicitShape3D  ( params );
    auto digitized_shape = SH3::makeDigitizedImplicitShape3D( implicit_shape, params );
    auto Kwhole          = SH3::getKSpace( params );
    auto K               = SH3::getKSpace( SH3::Point::zero, Kwhole.upperBound(), params );
    auto binary_image    = SH3::makeBinaryImage( digitized_shape, 
						 SH3::Domain(K.lowerBound(),K.upperBound()),
						 params );
    auto surface         = SH3::makeIdxDigitalSurface( binary_image, K, params );
    trace.info() << "#surfels=" << surface->size() << std::endl;
    //! [dgtal_shortcuts_ssec2_2_3s]
    ++nb, nbok += surface->size() > 1000 ? 1 : 0;
  }
  trace.endBlock();

  trace.beginBlock ( "Build polynomial shape -> digitize -> noisify -> count components -> save OBJ with different colors." );
  {
    auto params          = SH3::defaultParameters();
    //! [dgtal_shortcuts_ssec2_2_4s]
    params( "polynomial", "leopold" )( "gridstep", 0.25 )
      ( "minAABB", -12.0 )( "maxAABB", 12.0 )
      ( "surfaceComponents", "All" )( "noise", 0.5 );
    auto implicit_shape  = SH3::makeImplicitShape3D  ( params );
    auto digitized_shape = SH3::makeDigitizedImplicitShape3D( implicit_shape, params );
    auto K               = SH3::getKSpace( params );
    auto binary_image    = SH3::makeBinaryImage(digitized_shape,
						SH3::Domain(K.lowerBound(),K.upperBound()),
						params );
    // Extracts the whole surface (with all components)
    auto surface         = SH3::makeDigitalSurface( binary_image, K, params );
    // Extracts a vector of connected surfaces.
    auto vec_surfs       = SH3::makeLightDigitalSurfaces( binary_image, K, params );
    trace.info() << "#connected components = " << vec_surfs.size() << std::endl;
    std::map< SH3::Surfel, unsigned int> label;
    unsigned int n = 0;
    for ( auto&& surf : vec_surfs ) {
      auto surfels = SH3::getSurfelRange( surf, params );
      for ( auto&& s : surfels ) label[ s ] = n;
      n += 1;
    }
    auto cmap        = SH3::getColorMap( 0, vec_surfs.size(), params );
    auto all_surfels = SH3::getSurfelRange( surface, params );
    SH3::Colors colors( all_surfels.size() );
    for ( unsigned int i = 0; i < all_surfels.size(); ++i )
      colors[ i ] = cmap( label[ all_surfels[ i ] ] );
    bool ok = SH3::saveOBJ( surface, SH3::RealVectors(), colors, "leopold-primal-cc.obj" );
    //! [dgtal_shortcuts_ssec2_2_4s]
    ++nb, nbok += ok ? 1 : 0;
  }
  trace.endBlock();
  
  trace.info() << nbok << "/" << nb << " passed tests." << std::endl;
  
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
