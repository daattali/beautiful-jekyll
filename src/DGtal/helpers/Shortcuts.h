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

#pragma once

/**
 * @file Shortcuts.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2018/06/25
 *
 * Header file for module Shortcuts.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Shortcuts_RECURSES)
#error Recursive header files inclusion detected in Shortcuts.h
#else // defined(Shortcuts_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Shortcuts_RECURSES

#if !defined Shortcuts_h
/** Prevents repeated inclusion of headers. */
#define Shortcuts_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/kernel/RegularPointEmbedder.h"
#include "DGtal/math/MPolynomial.h"
#include "DGtal/math/Statistic.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/IntervalForegroundPredicate.h"
#include <DGtal/images/ImageLinearCellEmbedder.h>
#include "DGtal/shapes/implicit/ImplicitPolynomial3Shape.h"
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/shapes/ShapeGeometricFunctors.h"
#include "DGtal/shapes/MeshHelpers.h"
#include "DGtal/topology/CCellularGridSpaceND.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/topology/SetOfSurfels.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/IndexedDigitalSurface.h"
#include "DGtal/topology/SurfelAdjacency.h"
#include "DGtal/topology/CCellEmbedder.h"
#include "DGtal/topology/CanonicCellEmbedder.h"
#include "DGtal/topology/CanonicSCellEmbedder.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/geometry/volumes/KanungoNoise.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/io/colormaps/TickedColorMap.h"
#include "DGtal/io/readers/MPolynomialReader.h"
#include "DGtal/io/readers/GenericReader.h"
#include "DGtal/io/writers/GenericWriter.h"
#include "DGtal/graph/BreadthFirstVisitor.h"
#include "DGtal/graph/DepthFirstVisitor.h"
#include "DGtal/graph/GraphVisitorRange.h"
#include "DGtal/helpers/Parameters.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class Shortcuts
  /**
   * Description of template class 'Shortcuts' <p> \brief Aim: This
   * class is used to simplify shape and surface creation. With it,
   * you can create new shapes and surface with few lines of code. The
   * drawback is that you use specific types or objects, which could
   * lead to faster code or more compact data structures.
   *
   * @tparam TKSpace any cellular grid space, a model of
   * concepts::CCellularGridSpaceND like KhalimskySpaceND.
   */
  template  < typename TKSpace >
    class Shortcuts
    {
      BOOST_CONCEPT_ASSERT(( concepts::CCellularGridSpaceND< TKSpace > ));

      // ----------------------- Usual space types --------------------------------------
    public:
      /// Digital cellular space
      typedef TKSpace                                  KSpace;
      /// Digital space
      typedef typename KSpace::Space                   Space;
      /// Integer numbers
      typedef typename Space::Integer                  Integer;
      /// Point with integer coordinates.
      typedef typename Space::Point                    Point;
      /// Vector with integer coordinates.
      typedef typename Space::Vector                   Vector;
      /// Vector with floating-point coordinates.
      typedef typename Space::RealVector               RealVector;
      /// Point with floating-point coordinates.
      typedef typename Space::RealPoint                RealPoint;
      /// Floating-point numbers.
      typedef typename RealVector::Component           Scalar;
      /// An (hyper-)rectangular domain.
      typedef HyperRectDomain<Space>                   Domain;
      /// The type for 8-bits gray-scale elements.
      typedef unsigned char                            GrayScale;

      // ----------------------- Shortcut types --------------------------------------
    public:
      /// defines a multi-variate polynomial : RealPoint -> Scalar
      typedef MPolynomial< Space::dimension, Scalar >      ScalarPolynomial;
      /// defines an implicit shape of the space, which is the
      /// zero-level set of a ScalarPolynomial.
      typedef ImplicitPolynomial3Shape<Space>              ImplicitShape3D;
      /// defines the digitization of an implicit shape.
      typedef GaussDigitizer< Space, ImplicitShape3D >     DigitizedImplicitShape3D;
      /// defines a black and white image with (hyper-)rectangular domain.
      typedef ImageContainerBySTLVector<Domain, bool>      BinaryImage;
      /// defines a grey-level image with (hyper-)rectangular domain.
      typedef ImageContainerBySTLVector<Domain, GrayScale> GrayScaleImage;
      /// defines a float image with (hyper-)rectangular domain.
      typedef ImageContainerBySTLVector<Domain, float>     FloatImage;
      /// defines a double image with (hyper-)rectangular domain.
      typedef ImageContainerBySTLVector<Domain, double>    DoubleImage;
      /// defines a set of surfels
      typedef typename KSpace::SurfelSet                   SurfelSet;
      /// defines a light container that represents a connected digital
      /// surface over a binary image.
      typedef LightImplicitDigitalSurface< KSpace, BinaryImage >  LightSurfaceContainer;
      /// defines a connected digital surface over a binary image.
      typedef ::DGtal::DigitalSurface< LightSurfaceContainer >    LightDigitalSurface;
      /// defines a heavy container that represents any digital surface.
      typedef SetOfSurfels< KSpace, SurfelSet >                   ExplicitSurfaceContainer;
      /// defines an arbitrary digital surface over a binary image.
      typedef ::DGtal::DigitalSurface< ExplicitSurfaceContainer > DigitalSurface;
      /// defines a connected or not indexed digital surface.
      typedef IndexedDigitalSurface< ExplicitSurfaceContainer >   IdxDigitalSurface;
      typedef typename LightDigitalSurface::Surfel                Surfel;
      typedef typename LightDigitalSurface::Cell                  Cell;
      typedef typename LightDigitalSurface::SCell                 SCell;
      typedef typename LightDigitalSurface::Vertex                Vertex;
      typedef typename LightDigitalSurface::Arc                   Arc;
      typedef typename LightDigitalSurface::Face                  Face;
      typedef typename LightDigitalSurface::ArcRange              ArcRange;
      typedef typename IdxDigitalSurface::Vertex                  IdxSurfel;
      typedef typename IdxDigitalSurface::Vertex                  IdxVertex;
      typedef typename IdxDigitalSurface::Arc                     IdxArc;
      typedef typename IdxDigitalSurface::ArcRange                IdxArcRange;
      typedef std::set< IdxSurfel >                               IdxSurfelSet;
      typedef std::vector< SCell >                                SCellRange;
      typedef std::vector< Cell >                                 CellRange;
      typedef CellRange                                           PointelRange;
      typedef SCellRange                                          SurfelRange;
      typedef std::vector< IdxSurfel >                            IdxSurfelRange;
      typedef std::vector< Scalar >                               Scalars;
      typedef std::vector< RealVector >                           RealVectors;
      typedef std::vector< RealPoint >                            RealPoints;
      typedef IdxVertex                                           Idx;
      typedef std::vector< IdxVertex >                            IdxRange;

      typedef ::DGtal::Mesh<RealPoint>                            Mesh;
      typedef ::DGtal::TriangulatedSurface<RealPoint>             TriangulatedSurface;
      typedef ::DGtal::PolygonalSurface<RealPoint>                PolygonalSurface;
      typedef std::map<Surfel, IdxSurfel>                         Surfel2Index;
      typedef std::map<Cell,   IdxVertex>                         Cell2Index;

      typedef ::DGtal::Color                                      Color;
      typedef std::vector< Color >                                Colors;
      typedef GradientColorMap<Scalar>                            ColorMap;
      typedef TickedColorMap<Scalar,ColorMap>                     ZeroTickedColorMap;
    
      // ----------------------- Static services --------------------------------------
    public:

      // ----------------------- General static services ------------------------------
    public:
    
      /// @return the parameters and their default values used in shortcuts.
      static Parameters defaultParameters()
      {
        return parametersImplicitShape3D()
          | parametersKSpace()
          | parametersDigitizedImplicitShape3D()
          | parametersBinaryImage()
          | parametersGrayScaleImage()
          | parametersDigitalSurface()
          | parametersMesh()
          | parametersUtilities();
      }

      // ----------------------- ImplicitShape3D static services ------------------------
    public:

      /// Returns a map associating a name and a polynomial,
      /// e.g. "sphere1", "x^2+y^2+z^2-1".
      ///
      /// { "sphere1", "x^2+y^2+z^2-1" },
      /// { "sphere9", "x^2+y^2+z^2-81" },
      /// { "ellipsoid", "3*x^2+2*y^2+z^2-90" },
      /// { "cylinder", "x^2+2*z^2-90" },
      ///	{ "torus",   "(x^2+y^2+z^2+6*6-2*2)^2-4*6*6*(x^2+y^2)" },
      /// { "rcube",   "x^4+y^4+z^4-6561" },
      /// { "goursat", "-1*(8-0.03*x^4-0.03*y^4-0.03*z^4+2*x^2+2*y^2+2*z^2)" },
      /// { "distel",  "10000-(x^2+y^2+z^2+1000*(x^2+y^2)*(x^2+z^2)*(y^2+z^2))"},
      /// { "leopold", "(x^2*y^2*z^2+4*x^2+4*y^2+3*z^2)-100" },
      /// { "diabolo", "x^2-(y^2+z^2)^2" },
      /// { "heart",   "-1*(x^2+2.25*y^2+z^2-1)^3+x^2*z^3+0.1125*y^2*z^3" },
      /// { "crixxi",  "-0.9*(y^2+z^2-1)^2-(x^2+y^2-1)^3" }
      ///
      /// @return the map associating a polynomial to a name.
      static std::map< std::string, std::string >
        getPolynomialList()
        {
          std::vector< std::pair< std::string, std::string > >
            Ps = { { "sphere1", "x^2+y^2+z^2-1" },
                   { "sphere9", "x^2+y^2+z^2-81" },
                   { "ellipsoid", "3*x^2+2*y^2+z^2-90" },
                   { "cylinder", "x^2+2*z^2-90" },
                   { "torus",   "(x^2+y^2+z^2+6*6-2*2)^2-4*6*6*(x^2+y^2)" },
                   { "rcube",   "x^4+y^4+z^4-6561" },
                   { "goursat", "-1*(8-0.03*x^4-0.03*y^4-0.03*z^4+2*x^2+2*y^2+2*z^2)" },
                   { "distel",  "10000-(x^2+y^2+z^2+1000*(x^2+y^2)*(x^2+z^2)*(y^2+z^2))"},
                   { "leopold", "(x^2*y^2*z^2+4*x^2+4*y^2+3*z^2)-100" },
                   { "diabolo", "x^2-(y^2+z^2)^2" },
                   { "heart",   "-1*(x^2+2.25*y^2+z^2-1)^3+x^2*z^3+0.1125*y^2*z^3" },
                   { "crixxi",  "-0.9*(y^2+z^2-1)^2-(x^2+y^2-1)^3" } };
          std::map< std::string, std::string > L;
          for ( auto p : Ps )
            L[ p.first ] = p.second;
          return L;
        }

      /// @return the parameters and their default values which are used
      /// to define an implicit shape.
      ///   - polynomial     ["sphere1"]: the implicit polynomial whose zero-level set
      ///                                 defines the shape of interest.
      ///   - projectionMaxIter [    20]: the maximum number of iteration for the projection.
      ///   - projectionAccuracy[0.0001]: the zero-proximity stop criterion during projection.
      ///   - projectionGamma   [   0.5]: the damping coefficient of the projection.
      static Parameters parametersImplicitShape3D()
      {
        return Parameters
          ( "polynomial", "sphere1" )
          ( "projectionMaxIter", 20 )
          ( "projectionAccuracy", 0.0001 )
          ( "projectionGamma",    0.5 );
      }
    
      /// Builds a 3D implicit shape from parameters
      ///
      /// @param[in] params the parameters:
      ///   - polynomial["sphere1"]: the implicit polynomial whose zero-level set
      ///                            defines the shape of interest.
      ///
      /// @return a smart pointer on the created implicit shape.
      static CountedPtr<ImplicitShape3D>
        makeImplicitShape3D( const Parameters& params = parametersImplicitShape3D() )
      {
        typedef MPolynomialReader< Space::dimension, Scalar> Polynomial3Reader;
        std::string poly_str = params[ "polynomial" ].as<std::string>();
        // Recognizes specific strings as polynomials.
        auto PL = getPolynomialList();
        if ( PL[ poly_str ] != "" ) poly_str = PL[ poly_str ];
        ScalarPolynomial poly;
        Polynomial3Reader reader;
        std::string::const_iterator iter
          = reader.read( poly, poly_str.begin(), poly_str.end() );
        if ( iter != poly_str.end() )
          {
            trace.error() << "[Shortcuts::makeImplicitShape3D]"
                          << " ERROR reading polynomial: I read only <"
                          << poly_str.substr( 0, iter - poly_str.begin() )
                          << ">, and I built P=" << poly << std::endl;
          }
        return CountedPtr<ImplicitShape3D>( new ImplicitShape3D( poly ) );
      }

      // ----------------------- KSpace static services ------------------------------
    public:
    
      /// @return the parameters and their default values which are used for digitization.
      ///   - closed   [1  ]: specifies if the Khalimsky space is closed (!=0) or not (==0).
      ///   - gridsizex[1.0]: specifies the space between points along x.
      ///   - gridsizey[1.0]: specifies the space between points along y.
      ///   - gridsizez[1.0]: specifies the space between points along z.
      static Parameters parametersKSpace()
      {
        return Parameters
          ( "closed",    1   )
          ( "gridsizex", 1.0 )
          ( "gridsizey", 1.0 )
          ( "gridsizez", 1.0 );
      }

      /// Builds a Khalimsky space that encompasses the lower and upper
      /// digital points.  Note that digital points are cells of the
      /// Khalimsky space with maximal dimensions.  A closed Khalimsky
      /// space adds lower dimensional cells all around its boundary to
      /// define a closed complex.
      ///
      /// @param[in] low the lowest point in the space
      /// @param[in] up the highest point in the space
      /// @param[in] params the parameters:
      ///   - closed   [1]: specifies if the Khalimsky space is closed (!=0) or not (==0).
      ///
      /// @return the Khalimsky space.
      static KSpace getKSpace( const Point& low, const Point& up,
                               Parameters params = parametersKSpace() )
      {
        int closed  = params[ "closed"  ].as<int>();
        KSpace K;
        if ( ! K.init( low, up, closed ) )
          trace.error() << "[Shortcuts::getKSpace]"
                        << " Error building Khalimsky space K=" << K << std::endl;
        return K;
      }

      /// Builds a Khalimsky space that encompasses the domain of the given image.
      /// Note that digital points are cells of the Khalimsky space with
      /// maximal dimensions.  A closed Khalimsky space adds lower
      /// dimensional cells all around its boundary to define a closed
      /// complex.
      ///
      /// @param[in] bimage any binary image
      /// @param[in] params the parameters:
      ///   - closed   [1]: specifies if the Khalimsky space is closed (!=0) or not (==0).
      ///
      /// @return the Khalimsky space.
      static KSpace getKSpace( CountedPtr<BinaryImage> bimage,
                               Parameters params = parametersKSpace() )
      {
        int closed  = params[ "closed"  ].as<int>();
        KSpace K;
        if ( ! K.init( bimage->domain().lowerBound(),
                       bimage->domain().upperBound(),
                       closed ) )
          trace.error() << "[Shortcuts::getKSpace]"
                        << " Error building Khalimsky space K=" << K << std::endl;
        return K;
      }

      /// Builds a Khalimsky space that encompasses the domain of the given image.
      /// Note that digital points are cells of the Khalimsky space with
      /// maximal dimensions.  A closed Khalimsky space adds lower
      /// dimensional cells all around its boundary to define a closed
      /// complex.
      ///
      /// @param[in] gimage any gray-scale image
      /// @param[in] params the parameters:
      ///   - closed   [1]: specifies if the Khalimsky space is closed (!=0) or not (==0).
      ///
      /// @return the Khalimsky space.
      static KSpace getKSpace( CountedPtr<GrayScaleImage> gimage,
                               Parameters params = parametersKSpace() )
      {
        int closed  = params[ "closed"  ].as<int>();
        KSpace K;
        if ( ! K.init( gimage->domain().lowerBound(),
                       gimage->domain().upperBound(),
                       closed ) )
          trace.error() << "[Shortcuts::getKSpace]"
                        << " Error building Khalimsky space K=" << K << std::endl;
        return K;
      }

      /// @tparam TDigitalSurfaceContainer either kind of DigitalSurfaceContainer
      /// @param[in] surface a smart pointer on a (light or not) digital surface (e.g. DigitalSurface or LightDigitalSurface).
      /// @return the Khalimsky space associated to the given surface.
      template <typename TDigitalSurfaceContainer>
        static KSpace
        getKSpace
        ( CountedPtr< ::DGtal::DigitalSurface< TDigitalSurfaceContainer> > surface )
        {
          return surface->container().space();
        }

      /// @tparam TDigitalSurfaceContainer either kind of DigitalSurfaceContainer
      /// @param[in] surface a smart pointer on any indexed digital surface.
      /// @return the Khalimsky space associated to the given surface.
      template <typename TDigitalSurfaceContainer>
        static KSpace
        getKSpace
        ( CountedPtr< ::DGtal::IndexedDigitalSurface< TDigitalSurfaceContainer> > surface )
        {
          return surface->container().space();
        }

      /// @tparam TDigitalSurfaceContainer either kind of DigitalSurfaceContainer
      /// @param[in] surface a smart pointer on a (light or not) digital surface (e.g. DigitalSurface or LightDigitalSurface).
      /// @return a const reference to the Khalimsky space associated to the given surface.
      template <typename TDigitalSurfaceContainer>
        static const KSpace&
        refKSpace
        ( CountedPtr< ::DGtal::DigitalSurface< TDigitalSurfaceContainer> > surface )
        {
          return surface->container().space();
        }

      /// @tparam TDigitalSurfaceContainer either kind of DigitalSurfaceContainer
      /// @param[in] surface a smart pointer on any indexed digital surface.
      /// @return a const reference to the Khalimsky space associated to the given surface.
      template <typename TDigitalSurfaceContainer>
        static const KSpace&
        refKSpace
        ( CountedPtr< ::DGtal::IndexedDigitalSurface< TDigitalSurfaceContainer> > surface )
        {
          return surface->container().space();
        }

      /// @param[in] K any Khalimsky space.
      /// @return the canonic cell embedder associated to the given Khalimsky space.
      static CanonicCellEmbedder<KSpace>
        getCellEmbedder( const KSpace& K )
      {
        return CanonicCellEmbedder<KSpace>( K );
      }

      /// @param[in] K any Khalimsky space.
      /// @return the canonic signed cell embedder associated to the given Khalimsky space.
      static CanonicSCellEmbedder<KSpace>
        getSCellEmbedder( const KSpace& K )
      {
        return CanonicSCellEmbedder<KSpace>( K );
      }
      
    
      // ----------------------- DigitizedImplicitShape3D static services --------------
    public:
    
      /// @return the parameters and their default values which are used for digitization.
      ///   - minAABB  [-10.0]: the min value of the AABB bounding box (domain)
      ///   - maxAABB  [ 10.0]: the max value of the AABB bounding box (domain)
      ///   - gridstep [  1.0]: the gridstep that defines the digitization (often called h).
      ///   - offset   [  5.0]: the digital dilation of the digital space,
      ///                       useful when you process shapes and that you add noise.
      static Parameters parametersDigitizedImplicitShape3D()
      {
        return Parameters
          ( "minAABB",  -10.0 )
          ( "maxAABB",   10.0 )
          ( "gridstep",   1.0 )
          ( "offset",     5.0 );
      }

    
      /// Builds a Khalimsky space that encompasses the bounding box
      /// specified by a digitization in \a params. It is useful when
      /// digitizing an implicit shape.
      ///
      /// @param[in] params the parameters:
      ///   - minAABB  [-10.0]: the min value of the AABB bounding box (domain)
      ///   - maxAABB  [ 10.0]: the max value of the AABB bounding box (domain)
      ///   - gridstep [  1.0]: the gridstep that defines the digitization (often called h).
      ///   - offset   [  5.0]: the digital dilation of the digital space,
      ///                       useful when you process shapes and that you add noise.
      ///   - closed   [1]    : specifies if the Khalimsky space is closed (!=0) or not (==0).
      ///
      /// @return the Khalimsky space.
      /// @see makeDigitizedImplicitShape3D
      static KSpace
        getKSpace( Parameters params =
                   parametersKSpace() | parametersDigitizedImplicitShape3D() )
      {
        Scalar min_x  = params[ "minAABB"  ].as<Scalar>();
        Scalar max_x  = params[ "maxAABB"  ].as<Scalar>();
        Scalar h      = params[ "gridstep" ].as<Scalar>();
        Scalar offset = params[ "offset"   ].as<Scalar>();
        bool   closed = params[ "closed"   ].as<int>();
        RealPoint p1( min_x - offset * h, min_x - offset * h, min_x - offset * h );
        RealPoint p2( max_x + offset * h, max_x + offset * h, max_x + offset * h );
        CountedPtr<DigitizedImplicitShape3D> dshape( new DigitizedImplicitShape3D() );
        dshape->init( p1, p2, h );
        Domain domain = dshape->getDomain();
        KSpace K;
        if ( ! K.init( domain.lowerBound(), domain.upperBound(), closed ) )
          trace.error() << "[Shortcuts::getKSpace]"
                        << " Error building Khalimsky space K=" << K << std::endl;
        return K;
      }

      /// Makes the Gauss digitization of the given implicit shape
      /// according to parameters. Use getKSpace to build the associated digital space.
      ///
      /// @param[in] shape a smart pointer on the implicit shape.
      /// @param[in] params the parameters:
      ///   - minAABB  [-10.0]: the min value of the AABB bounding box (domain)
      ///   - maxAABB  [ 10.0]: the max value of the AABB bounding box (domain)
      ///   - gridstep [  1.0]: the gridstep that defines the digitization (often called h).
      ///   - offset   [  5.0]: the digital dilation of the digital space,
      ///                       useful when you process shapes and that you add noise.
      ///
      /// @return a smart pointer on the created implicit digital shape.
      /// @see getKSpaceDigitizedImplicitShape3D 
      static CountedPtr<DigitizedImplicitShape3D>
        makeDigitizedImplicitShape3D
        ( CountedPtr<ImplicitShape3D> shape,
          Parameters params = parametersDigitizedImplicitShape3D() )
      {
        Scalar min_x  = params[ "minAABB"  ].as<Scalar>();
        Scalar max_x  = params[ "maxAABB"  ].as<Scalar>();
        Scalar h      = params[ "gridstep" ].as<Scalar>();
        Scalar offset = params[ "offset"   ].as<Scalar>();
        RealPoint p1( min_x - offset * h, min_x - offset * h, min_x - offset * h );
        RealPoint p2( max_x + offset * h, max_x + offset * h, max_x + offset * h );
        CountedPtr<DigitizedImplicitShape3D> dshape( new DigitizedImplicitShape3D() );
        dshape->attach( shape );
        dshape->init( p1, p2, h );
        return dshape;
      }


      // ----------------------- BinaryImage static services --------------------------
    public:
    
      /// @return the parameters and their default values which are
      /// related to binary images and synthetic noise.
      ///   - noise        [0.0]: specifies the Kanungo noise level for binary pictures.
      ///   - thresholdMin [  0]: specifies the threshold min (excluded) to define binary shape
      ///   - thresholdMax [255]: specifies the threshold max (included) to define binary shape
      static Parameters parametersBinaryImage()
      {
        return Parameters
          ( "noise", 0.0 )
          ( "thresholdMin", 0 )
          ( "thresholdMax", 255 );
      }
    
      /// Makes an empty binary image within a given domain.
      ///
      /// @param[in] shapeDomain any domain.
      ///
      /// @return a smart pointer on a binary image that fits the given domain.
      static CountedPtr<BinaryImage>
        makeBinaryImage( Domain shapeDomain )
      {
        return CountedPtr<BinaryImage>( new BinaryImage( shapeDomain ) );
      }
    
      /// Vectorizes an implicitly defined digital shape into a binary
      /// image, and possibly add Kanungo noise to the result depending
      /// on parameters given in \a params.
      ///
      /// @param[in] shape_digitization a smart pointer on an implicit digital shape.
      /// @param[in] params the parameters:
      ///   - noise   [0.0]: specifies the Kanungo noise level for binary pictures.
      ///
      /// @return a smart pointer on a binary image that samples the digital shape.
      static CountedPtr<BinaryImage>
        makeBinaryImage( CountedPtr<DigitizedImplicitShape3D> shape_digitization,
                         Parameters params = parametersBinaryImage() )
      {
        return makeBinaryImage( shape_digitization,
                                shape_digitization->getDomain(),
                                params );
      }
    
      /// Vectorizes an implicitly defined digital shape into a binary
      /// image, in the specified (hyper-)rectangular domain, and
      /// possibly add Kanungo noise to the result depending on
      /// parameters given in \a params.
      ///
      /// @param[in] shape_digitization a smart pointer on an implicit digital shape.
      /// @param[in] shapeDomain any domain.
      /// @param[in] params the parameters:
      ///   - noise   [0.0]: specifies the Kanungo noise level for binary pictures.
      ///
      /// @return a smart pointer on a binary image that samples the digital shape.
      static CountedPtr<BinaryImage>
        makeBinaryImage( CountedPtr<DigitizedImplicitShape3D> shape_digitization,
                         Domain shapeDomain,
                         Parameters params = parametersBinaryImage() )
      {
        const Scalar noise        = params[ "noise"  ].as<Scalar>();
        CountedPtr<BinaryImage> img ( new BinaryImage( shapeDomain ) );
        if ( noise <= 0.0 )
          {
            std::transform( shapeDomain.begin(), shapeDomain.end(),
                            img->begin(),
                            [&shape_digitization]
                            ( const Point& p ) { return (*shape_digitization)(p); } );
          }
        else
          {
            typedef KanungoNoise< DigitizedImplicitShape3D, Domain > KanungoPredicate;
            KanungoPredicate noisy_dshape( *shape_digitization, shapeDomain, noise );
            std::transform( shapeDomain.begin(), shapeDomain.end(),
                            img->begin(),
                            [&noisy_dshape] ( const Point& p ) { return noisy_dshape(p); } );
          }
        return img;
      }

      /// Adds Kanungo noise to a binary image and returns the resulting new image. 
      ///
      /// @param[in] bimage a smart pointer on a binary image.
      /// @param[in] params the parameters:
      ///   - noise   [0.0]: specifies the Kanungo noise level for binary pictures.
      ///
      /// @return a smart pointer on the noisified binary image.
      static CountedPtr<BinaryImage>
        makeBinaryImage( CountedPtr<BinaryImage> bimage,
                         Parameters params = parametersBinaryImage() )
      {
        const Scalar noise = params[ "noise"  ].as<Scalar>();
        if ( noise <= 0.0 ) return bimage;
        typedef KanungoNoise< BinaryImage, Domain > KanungoPredicate;
        const Domain shapeDomain    = bimage->domain();
        CountedPtr<BinaryImage> img ( new BinaryImage( shapeDomain ) );
        KanungoPredicate noisy_dshape( *bimage, shapeDomain, noise );
        std::transform( shapeDomain.begin(), shapeDomain.end(),
                        img->begin(),
                        [&noisy_dshape] ( const Point& p ) { return noisy_dshape(p); } );
        return img;
      }

      /// Loads an arbitrary image file (e.g. vol file in 3D) and returns
      /// the binary image corresponding to the threshold/noise parameters.
      ///
      /// @param[in] input the input filename.
      /// @param[in] params the parameters:
      ///   - noise        [0.0]: specifies the Kanungo noise level for binary pictures.
      ///   - thresholdMin [  0]: specifies the threshold min (excluded) to define binary shape
      ///   - thresholdMax [255]: specifies the threshold max (included) to define binary shape
      ///
      /// @return a smart pointer on a binary image that represents the
      /// (thresholded/noisified) image file.
      static CountedPtr<BinaryImage>
        makeBinaryImage
        ( std::string input,
          Parameters params = parametersBinaryImage() )
      {
        int     thresholdMin = params["thresholdMin"].as<int>();
        int     thresholdMax = params["thresholdMax"].as<int>();
        GrayScaleImage image = GenericReader<GrayScaleImage>::import( input );
        Domain        domain = image.domain();
        typedef functors::IntervalForegroundPredicate<GrayScaleImage> ThresholdedImage;
        ThresholdedImage tImage( image, thresholdMin, thresholdMax );
        CountedPtr<BinaryImage> img ( new BinaryImage( domain ) );
        std::transform( domain.begin(), domain.end(),
                        img->begin(),
                        [tImage] ( const Point& p ) { return tImage(p); } );
        return makeBinaryImage( img, params );
      }

      /// Binarizes an arbitrary gray scale image file and returns
      /// the binary image corresponding to the threshold/noise parameters.
      ///
      /// @param[in] gray_scale_image the input gray scale image.
      /// @param[in] params the parameters:
      ///   - noise        [0.0]: specifies the Kanungo noise level for binary pictures.
      ///   - thresholdMin [  0]: specifies the threshold min (excluded) to define binary shape
      ///   - thresholdMax [255]: specifies the threshold max (included) to define binary shape
      ///
      /// @return a smart pointer on a binary image that represents the
      /// (thresholded/noisified) gray scale image.
      static CountedPtr<BinaryImage>
        makeBinaryImage
        ( CountedPtr<GrayScaleImage> gray_scale_image,
          Parameters params = parametersBinaryImage() )
      {
        int     thresholdMin = params["thresholdMin"].as<int>();
        int     thresholdMax = params["thresholdMax"].as<int>();
        Domain        domain = gray_scale_image->domain();
        typedef functors::IntervalForegroundPredicate<GrayScaleImage> ThresholdedImage;
        ThresholdedImage tImage( *gray_scale_image, thresholdMin, thresholdMax );
        CountedPtr<BinaryImage> img ( new BinaryImage( domain ) );
        std::transform( domain.begin(), domain.end(),
                        img->begin(),
                        [tImage] ( const Point& p ) { return tImage(p); } );
        return makeBinaryImage( img, params );
      }

    
      /// Saves an arbitrary binary image file (e.g. vol file in 3D).
      ///
      /// @param[in] bimage the input binary image.
      /// @param[in] output the output filename .
      /// @return 'true' if everything went well, 'false' if there was an error during save.
      static bool
        saveBinaryImage
        ( CountedPtr<BinaryImage> bimage, std::string output )
      {
        auto gray_scale_image = makeGrayScaleImage( bimage );
        return saveGrayScaleImage( gray_scale_image, output );
      }


      // ----------------------- GrayScaleImage static services -------------------------
    public:

      /// @return the parameters and their default values which are used for quantification.
      ///   - qShift   [128.0]: the shift used when quantifying the implicit shape
      ///                       (q(x)=qSlope*x+qShift, e.g. to build a grayscale image).
      ///   - qSlope   [  1.0]: the slope used when quantifying the implicit shape
      ///                       (q(x)=qSlope*x+qShift, e.g. to build a grayscale image).
      static Parameters parametersGrayScaleImage()
      {
        return Parameters
          ( "qShift",   128.0 )
          ( "qSlope",     1.0 );
      }
    
      /// Makes an empty gray scale image within a given domain (values are unsigned char).
      ///
      /// @param[in] aDomain any domain.
      ///
      /// @return a smart pointer on a gray scale image that fits the given domain.
      static CountedPtr<GrayScaleImage>
        makeGrayScaleImage( Domain aDomain )
      {
        return CountedPtr<GrayScaleImage>( new GrayScaleImage( aDomain ) );
      }

      /// Loads an arbitrary binary image file (e.g. vol file in 3D) and returns
      /// the corresponding gray-scale image.
      ///
      /// @param[in] input the input filename.
      ///
      /// @return a smart pointer on the loaded gray-scale image.
      static CountedPtr<GrayScaleImage>
        makeGrayScaleImage
        ( std::string input )
      {
        GrayScaleImage image = GenericReader<GrayScaleImage>::import( input );
        return CountedPtr<GrayScaleImage>( new GrayScaleImage( image ) );
      }

      /// Makes a gray-scale image from a binary image using the given transformation
      ///
      /// @param[in] binary_image the input binary image.
      /// @param[in] bool2grayscale the binarizing function.
      ///
      /// @return a smart pointer on the resulting gray-scale image.
      static CountedPtr<GrayScaleImage>
        makeGrayScaleImage
        ( CountedPtr<BinaryImage> binary_image,
          std::function< GrayScale( bool ) > const & bool2grayscale
          = [] ( bool v ) { return v ? (unsigned char) 255 : (unsigned char) 0; }
          // JOL: (GrayScale) was not working with visual C++: error C2065
          )
      {
        const Domain domain = binary_image->domain(); 
        CountedPtr<GrayScaleImage> gray_scale_image( new GrayScaleImage( domain ) );
        std::transform( binary_image->begin(), binary_image->end(),
                        gray_scale_image->begin(),
                        bool2grayscale );
        return gray_scale_image;
      }

      /// Saves an arbitrary gray-scale image file (e.g. vol file in 3D).
      ///
      /// @param[in] gray_scale_image the input gray-scale image.
      /// @param[in] output the output filename .
      /// @return 'true' if everything went well, 'false' if there was an error during save.
      static bool
        saveGrayScaleImage
        ( CountedPtr<GrayScaleImage> gray_scale_image, std::string output )
      {
        return GenericWriter< GrayScaleImage > 
          ::exportFile( output, *gray_scale_image );
      }


      /// Makes a gray-scale image from the given float image
      /// (i.e. quantify the given image)..
      ///
      /// @param[in] fimage a smart pointer on the float image.
      /// @param[in] params the parameters:
      ///   - qShift   [128.0]: the shift used when quantifying the implicit shape
      ///                       (q(x)=qSlope*x+qShift, e.g. to build a grayscale image).
      ///   - qSlope   [  1.0]: the slope used when quantifying the implicit shape
      ///                       (q(x)=qSlope*x+qShift, e.g. to build a grayscale image).
      ///
      /// @return a smart pointer on the created image
      static CountedPtr<GrayScaleImage>
        makeGrayScaleImage
        ( CountedPtr<FloatImage> fimage,
          Parameters params = parametersGrayScaleImage() )
      {
        float qShift = params[ "qShift"   ].as<float>();
        float qSlope = params[ "qSlope"   ].as<float>();
        std::function< unsigned char( float ) > f
          = [qShift,qSlope] (float v)
          { return (unsigned char) std::min( 255.0f, std::max( 0.0f, qSlope * v + qShift ) ); };
        Domain domain = fimage->domain();
        auto   gimage = makeGrayScaleImage( domain );
        auto       it = gimage->begin();
        for ( auto p : domain )
          {
            float val = (*fimage)( p );
            *it++      = f( val );
          }
        return gimage;
      }

      /// Makes a gray-scale image from the given double image.
      /// (i.e. quantify the given image)..
      ///
      /// @param[in] fimage a smart pointer on the double image.
      /// @param[in] params the parameters:
      ///   - qShift   [128.0]: the shift used when quantifying the implicit shape
      ///                       (q(x)=qSlope*x+qShift, e.g. to build a grayscale image).
      ///   - qSlope   [  1.0]: the slope used when quantifying the implicit shape
      ///                       (q(x)=qSlope*x+qShift, e.g. to build a grayscale image).
      ///
      /// @return a smart pointer on the created image
      static CountedPtr<GrayScaleImage>
        makeGrayScaleImage
        ( CountedPtr<DoubleImage> fimage,
          Parameters params = parametersGrayScaleImage() )
      {
        double qShift = params[ "qShift"   ].as<double>();
        double qSlope = params[ "qSlope"   ].as<double>();
        std::function< unsigned char( double ) > f
          = [qShift,qSlope] (double v)
          { return (unsigned char) std::min( 255.0, std::max( 0.0, qSlope * v + qShift ) ); };
        Domain domain = fimage->domain();
        auto   gimage = makeGrayScaleImage( domain );
        auto       it = gimage->begin();
        for ( auto p : domain )
          {
            double val = (*fimage)( p );
            *it++      = f( val );
          }
        return gimage;
      }

      // ----------------------- FloatImage static services -------------------------
    public:

      /// Makes an empty float image within a given domain (values are unsigned char).
      ///
      /// @param[in] aDomain any domain.
      ///
      /// @return a smart pointer on a float image that fits the given domain.
      static CountedPtr<FloatImage>
        makeFloatImage( Domain aDomain )
      {
        return CountedPtr<FloatImage>( new FloatImage( aDomain ) );
      }

      /// Loads an arbitrary image file (e.g. vol file in 3D) and returns
      /// the corresponding float image.
      ///
      /// @param[in] input the input filename.
      ///
      /// @return a smart pointer on the loaded float image.
      static CountedPtr<FloatImage>
        makeFloatImage
        ( std::string input )
      {
        FloatImage image = GenericReader<FloatImage>::import( input );
        return CountedPtr<FloatImage>( new FloatImage( image ) );
      }

      /// Makes a float image from the given implicit shape
      /// according to parameters. Use getKSpace to build the associated
      /// digital space.
      ///
      /// @param[in] shape a smart pointer on the implicit shape.
      /// @param[in] params the parameters:
      ///   - minAABB  [-10.0]: the min value of the AABB bounding box (domain)
      ///   - maxAABB  [ 10.0]: the max value of the AABB bounding box (domain)
      ///   - gridstep [  1.0]: the gridstep that defines the digitization (often called h).
      ///   - offset   [  5.0]: the digital dilation of the digital space,
      ///                       useful when you process shapes and that you add noise.
      ///
      /// @return a smart pointer on the created image.
      static CountedPtr<FloatImage>
        makeFloatImage
        ( CountedPtr<ImplicitShape3D> shape,
          Parameters params = parametersDigitizedImplicitShape3D() )
      {
        Scalar min_x  = params[ "minAABB"  ].as<Scalar>();
        Scalar max_x  = params[ "maxAABB"  ].as<Scalar>();
        Scalar h      = params[ "gridstep" ].as<Scalar>();
        Scalar offset = params[ "offset"   ].as<Scalar>();
        RealPoint p1( min_x - offset * h, min_x - offset * h, min_x - offset * h );
        RealPoint p2( max_x + offset * h, max_x + offset * h, max_x + offset * h );
        CountedPtr<DigitizedImplicitShape3D> dshape( new DigitizedImplicitShape3D() );
        dshape->attach( shape );
        dshape->init( p1, p2, h );
        Domain domain = dshape->getDomain();
        auto   fimage = makeFloatImage( domain );
        auto       it = fimage->begin();
        for ( auto p : domain )
          {
            float val = (float) (*shape)( p );
            *it++      = val;
          }
        return fimage;
      }

      // ----------------------- DoubleImage static services -------------------------
    public:

      /// Makes an empty double image within a given domain (values are unsigned char).
      ///
      /// @param[in] aDomain any domain.
      ///
      /// @return a smart pointer on a double image that fits the given domain.
      static CountedPtr<DoubleImage>
        makeDoubleImage( Domain aDomain )
      {
        return CountedPtr<DoubleImage>( new DoubleImage( aDomain ) );
      }

      /// Loads an arbitrary image file (e.g. vol file in 3D) and returns
      /// the corresponding double image.
      ///
      /// @param[in] input the input filename.
      ///
      /// @return a smart pointer on the loaded double image.
      static CountedPtr<DoubleImage>
        makeDoubleImage
        ( std::string input )
      {
        DoubleImage image = GenericReader<DoubleImage>::import( input );
        return CountedPtr<DoubleImage>( new DoubleImage( image ) );
      }

      /// Makes a double image from the given implicit shape
      /// according to parameters. Use getKSpace to build the associated
      /// digital space.
      ///
      /// @param[in] shape a smart pointer on the implicit shape.
      /// @param[in] params the parameters:
      ///   - minAABB  [-10.0]: the min value of the AABB bounding box (domain)
      ///   - maxAABB  [ 10.0]: the max value of the AABB bounding box (domain)
      ///   - gridstep [  1.0]: the gridstep that defines the digitization (often called h).
      ///   - offset   [  5.0]: the digital dilation of the digital space,
      ///                       useful when you process shapes and that you add noise.
      ///
      /// @return a smart pointer on the created image.
      static CountedPtr<DoubleImage>
        makeDoubleImage
        ( CountedPtr<ImplicitShape3D> shape,
          Parameters params = parametersDigitizedImplicitShape3D() )
      {
        Scalar min_x  = params[ "minAABB"  ].as<Scalar>();
        Scalar max_x  = params[ "maxAABB"  ].as<Scalar>();
        Scalar h      = params[ "gridstep" ].as<Scalar>();
        Scalar offset = params[ "offset"   ].as<Scalar>();
        RealPoint p1( min_x - offset * h, min_x - offset * h, min_x - offset * h );
        RealPoint p2( max_x + offset * h, max_x + offset * h, max_x + offset * h );
        CountedPtr<DigitizedImplicitShape3D> dshape( new DigitizedImplicitShape3D() );
        dshape->attach( shape );
        dshape->init( p1, p2, h );
        Domain domain = dshape->getDomain();
        auto   fimage = makeDoubleImage( domain );
        auto       it = fimage->begin();
        for ( auto p : domain )
          {
            double val = (double) (*shape)( p );
            *it++      = val;
          }
        return fimage;
      }
    
      // ----------------------- DigitalSurface static services ------------------------
    public:
        
      /// @return the parameters and their default values which are
      /// related to digital surfaces.
      ///   - surfelAdjacency     [        0]: specifies the surfel adjacency (1:ext, 0:int)
      ///   - nbTriesToFindABel   [   100000]: number of tries in method Surfaces::findABel
      ///   - surfaceComponents   [ "AnyBig"]: "AnyBig"|"All", "AnyBig": any big-enough componen
      ///   - surfaceTraversal    ["Default"]: "Default"|"DepthFirst"|"BreadthFirst": "Default" default surface traversal, "DepthFirst": depth-first surface traversal, "BreadthFirst": breadth-first surface traversal.
      static Parameters parametersDigitalSurface()
      {
        return Parameters
          ( "surfelAdjacency",   0 )
          ( "nbTriesToFindABel", 100000 )
          ( "surfaceComponents", "AnyBig" )
          ( "surfaceTraversal",  "Default" );
      }

      /// @tparam TDigitalSurfaceContainer either kind of DigitalSurfaceContainer
      /// @param[in] surface a smart pointer on a (light or not) digital surface (e.g. DigitalSurface or LightDigitalSurface).
      /// @return the canonic cell embedder associated to the given digital surface.
      template <typename TDigitalSurfaceContainer>
        static CanonicCellEmbedder<KSpace>
        getCellEmbedder
        ( CountedPtr< ::DGtal::DigitalSurface< TDigitalSurfaceContainer> > surface )
        {
          return getCellEmbedder( refKSpace( surface ) );
        }

      /// @tparam TDigitalSurfaceContainer either kind of DigitalSurfaceContainer
      /// @param[in] surface a smart pointer on a (light or not) digital surface (e.g. DigitalSurface or LightDigitalSurface).
      /// @return the canonic signed cell embedder associated to the given digital surface.
      template <typename TDigitalSurfaceContainer>
        static CanonicSCellEmbedder<KSpace>
        getSCellEmbedder
        ( CountedPtr< ::DGtal::DigitalSurface< TDigitalSurfaceContainer> > surface )
        {
          return getSCellEmbedder( refKSpace( surface ) );
        }

      /// @tparam TDigitalSurfaceContainer either kind of DigitalSurfaceContainer
      /// @param[in] surface a smart pointer on any indexed digital surface.
      /// @return the canonic cell embedder associated to the given indexed digital surface.
      template <typename TDigitalSurfaceContainer>
        static CanonicCellEmbedder<KSpace>
        getCellEmbedder
        ( CountedPtr< ::DGtal::IndexedDigitalSurface< TDigitalSurfaceContainer> > surface )
        {
          return getCellEmbedder( refKSpace( surface ) );
        }

      /// @tparam TDigitalSurfaceContainer either kind of DigitalSurfaceContainer
      /// @param[in] surface a smart pointer on any indexed digital surface.
      /// @return the canonic signed cell embedder associated to the given indexed digital surface.
      template <typename TDigitalSurfaceContainer>
        static CanonicSCellEmbedder<KSpace>
        getSCellEmbedder
        ( CountedPtr< ::DGtal::IndexedDigitalSurface< TDigitalSurfaceContainer> > surface )
        {
          return getSCellEmbedder( refKSpace( surface ) );
        }
    
      /// Builds a light digital surface from a space \a K and a binary image \a bimage.
      ///
      /// @param[in] bimage a binary image representing the characteristic function of a digital shape.
      /// @param[in] K the Khalimsky space whose domain encompasses the digital shape.
      ///
      /// @param[in] params the parameters:
      ///   - surfelAdjacency   [     0]: specifies the surfel adjacency (1:ext, 0:int)
      ///   - nbTriesToFindABel [100000]: number of tries in method Surfaces::findABel
      ///
      /// @return a smart pointer on a (light) digital surface that
      /// represents the boundary of any big component of the digital shape.
      static CountedPtr<LightDigitalSurface>
        makeLightDigitalSurface
        ( CountedPtr<BinaryImage> bimage,
          const KSpace&           K,
          const Parameters&       params = parametersDigitalSurface() )
      {
        bool surfel_adjacency      = params[ "surfelAdjacency" ].as<int>();
        int nb_tries_to_find_a_bel = params[ "nbTriesToFindABel" ].as<int>();
        SurfelAdjacency< KSpace::dimension > surfAdj( surfel_adjacency );

        // We have to search for a surfel that belongs to a big connected component.
        CountedPtr<LightDigitalSurface> ptrSurface;
        Surfel       bel;
        Scalar       minsize    = bimage->extent().norm();
        unsigned int nb_surfels = 0;
        unsigned int tries      = 0;
        do
          {
            try { // Search initial bel
              bel = Surfaces<KSpace>::findABel( K, *bimage, nb_tries_to_find_a_bel );
            } catch (DGtal::InputException e) {
              trace.error() << "[Shortcuts::makeLightDigitalSurface]"
                            << " ERROR Unable to find bel." << std::endl;
              return ptrSurface;
            }
            // this pointer will be acquired by the surface.
            LightSurfaceContainer* surfContainer
              = new LightSurfaceContainer( K, *bimage, surfAdj, bel );
            ptrSurface = CountedPtr<LightDigitalSurface>
              ( new LightDigitalSurface( surfContainer ) ); // acquired
            nb_surfels = ptrSurface->size();
          }
        while ( ( nb_surfels < 2 * minsize ) && ( tries++ < 150 ) );
        if( tries >= 150 )
          trace.warning() << "[Shortcuts::makeLightDigitalSurface]"
                          << "ERROR cannot find a proper bel in a big enough component."
                          << std::endl;
        return ptrSurface;
      }

      /// Returns a vector containing either all the light digital
      /// surfaces in the binary image \a bimage, or any one of its big
      /// components according to parameters.
      ///
      /// @param[in] bimage a binary image representing the
      /// characteristic function of a digital shape.
      ///
      /// @param[in] K the Khalimsky space whose domain encompasses the
      /// digital shape.
      ///
      /// @param[in] params the parameters:
      ///   - surfelAdjacency   [       0]: specifies the surfel adjacency (1:ext, 0:int)
      ///   - nbTriesToFindABel [  100000]: number of tries in method Surfaces::findABel
      ///   - surfaceComponents ["AnyBig"]: "AnyBig"|"All", "AnyBig": any big-enough component (> twice space width), "All": all components
      ///
      /// @return a vector of smart pointers to the connected (light)
      /// digital surfaces present in the binary image.
      static std::vector< CountedPtr<LightDigitalSurface> >
        makeLightDigitalSurfaces
        ( CountedPtr<BinaryImage> bimage,
          const KSpace&           K,
          const Parameters&       params = parametersDigitalSurface() )
      {
        SurfelRange surfel_reps;
        return makeLightDigitalSurfaces( surfel_reps, bimage, K, params );
      }

      /// Returns a vector containing either all the light digital
      /// surfaces in the binary image \a bimage, or any one of its big
      /// components according to parameters.
      ///
      /// @param[out] surfel_reps a vector of surfels, one surfel per
      /// digital surface component.
      ///
      /// @param[in] bimage a binary image representing the
      /// characteristic function of a digital shape.
      ///
      /// @param[in] K the Khalimsky space whose domain encompasses the
      /// digital shape.
      ///
      /// @param[in] params the parameters:
      ///   - surfelAdjacency   [       0]: specifies the surfel adjacency (1:ext, 0:int)
      ///   - nbTriesToFindABel [  100000]: number of tries in method Surfaces::findABel
      ///   - surfaceComponents ["AnyBig"]: "AnyBig"|"All", "AnyBig": any big-enough component (> twice space width), "All": all components
      ///
      /// @return a vector of smart pointers to the connected (light)
      /// digital surfaces present in the binary image.
      static std::vector< CountedPtr<LightDigitalSurface> >
        makeLightDigitalSurfaces
        ( SurfelRange&            surfel_reps,
          CountedPtr<BinaryImage> bimage,
          const KSpace&           K,
          const Parameters&       params = parametersDigitalSurface() )
      {
        std::vector< CountedPtr<LightDigitalSurface> > result;
        std::string component      = params[ "surfaceComponents" ].as<std::string>();
        if ( component == "AnyBig" )
          {
            result.push_back( makeLightDigitalSurface( bimage, K, params ) );
            surfel_reps.push_back( *( result[ 0 ]->begin() ) );
            return result;
          }	
        bool surfel_adjacency      = params[ "surfelAdjacency" ].as<int>();
        SurfelAdjacency< KSpace::dimension > surfAdj( surfel_adjacency );
        // Extracts all boundary surfels
        SurfelSet all_surfels;
        Surfaces<KSpace>::sMakeBoundary( all_surfels, K, *bimage,
                                         K.lowerBound(), K.upperBound() );
        // Builds all connected components of surfels.
        SurfelSet marked_surfels;
        CountedPtr<LightDigitalSurface> ptrSurface;
        for ( auto bel : all_surfels )
          {
            if ( marked_surfels.count( bel ) != 0 ) continue;
            surfel_reps.push_back( bel );
            LightSurfaceContainer* surfContainer
              = new LightSurfaceContainer( K, *bimage, surfAdj, bel );
            ptrSurface = CountedPtr<LightDigitalSurface>
              ( new LightDigitalSurface( surfContainer ) ); // acquired
            // mark all surfels of the surface component.
            marked_surfels.insert( ptrSurface->begin(), ptrSurface->end() );
            // add surface component to result.
            result.push_back( ptrSurface );
          }
        return result;
      }

    
      /// Creates a explicit digital surface representing the boundaries in
      /// the binary image \a bimage, or any one of its big components
      /// according to parameters.
      ///
      /// @tparam TPointPredicate any type representing a point
      /// predicate (e.g. a BinaryImage or a DigitizedImplicitShape3D).
      ///
      /// @param[in] bimage any point predicate: Point -> boolean that
      /// represents the characteristic function of a digital shape
      ///
      /// @param[in] K the Khalimsky space whose domain encompasses the
      /// digital shape.
      ///
      /// @param[in] params the parameters:
      ///   - surfelAdjacency   [       0]: specifies the surfel adjacency (1:ext, 0:int)
      ///
      /// @return a smart pointer on the explicit digital surface
      /// representing the boundaries in the binary image.
      template <typename TPointPredicate>
        static CountedPtr< DigitalSurface >
        makeDigitalSurface
        ( CountedPtr< TPointPredicate > bimage,
          const KSpace&           K,
          const Parameters&       params = parametersDigitalSurface() )
        {
          SurfelSet all_surfels;
          bool      surfel_adjacency = params[ "surfelAdjacency" ].as<int>();
          SurfelAdjacency< KSpace::dimension > surfAdj( surfel_adjacency );
          // Extracts all boundary surfels
          Surfaces<KSpace>::sMakeBoundary( all_surfels, K, *bimage,
                                           K.lowerBound(), K.upperBound() );
          ExplicitSurfaceContainer* surfContainer
            = new ExplicitSurfaceContainer( K, surfAdj, all_surfels );
          return CountedPtr< DigitalSurface >
	    ( new DigitalSurface( surfContainer ) ); // acquired
        }


      /// Builds a explicit digital surface from an indexed digital surface.
      ///
      /// @note if the given surfel adjacency is not the same as the one
      /// chosen for the input indexed digital surface, the number of
      /// connected components may change in the process.
      ///
      /// @param[in] idx_surface any indexed digital surface.
      ///
      /// @param[in] params the parameters:
      ///   - surfelAdjacency   [       0]: specifies the surfel adjacency (1:ext, 0:int)
      ///
      /// @return a smart pointer on a explicit digital surface.
      static CountedPtr< DigitalSurface >
        makeDigitalSurface
        ( CountedPtr<IdxDigitalSurface> idx_surface,
          const Parameters&             params = parametersDigitalSurface() )
      {
        bool surfel_adjacency      = params[ "surfelAdjacency" ].as<int>();
        const KSpace& K = refKSpace( idx_surface );
        SurfelAdjacency< KSpace::dimension > surfAdj( surfel_adjacency );
        auto all_idx_surfels
          = getIdxSurfelRange( idx_surface, Parameters( "surfaceTraversal", "Default" ) );
        auto idx2surfel = idx_surface->surfels();
        SurfelSet all_surfels;
        for ( auto idx : all_idx_surfels ) all_surfels.insert( idx2surfel[ idx ] );
        ExplicitSurfaceContainer* surfContainer
          = new ExplicitSurfaceContainer( K, surfAdj, all_surfels );
        return CountedPtr<DigitalSurface>
          ( new DigitalSurface( surfContainer ) ); // acquired
      }
    
      /// Builds an indexed digital surface from a space \a K and a
      /// binary image \a bimage. Note that it may connected or not
      /// depending on parameters.
      ///
      /// @param[in] bimage a binary image representing the
      /// characteristic function of a digital shape.
      ///
      /// @param[in] K the Khalimsky space whose domain encompasses the
      /// digital shape.
      ///
      /// @param[in] params the parameters:
      ///   - surfelAdjacency   [     0]: specifies the surfel adjacency (1:ext, 0:int)
      ///   - nbTriesToFindABel [100000]: number of tries in method Surfaces::findABel
      ///   - surfaceComponents ["AnyBig"]: "AnyBig"|"All", "AnyBig": any big-enough component (> twice space width), "All": all components
      ///
      /// @return a smart pointer on the required indexed digital surface.
      static CountedPtr<IdxDigitalSurface>
        makeIdxDigitalSurface
        ( CountedPtr<BinaryImage> bimage,
          const KSpace&           K,
          const Parameters&       params = parametersDigitalSurface() )
      {
        std::string component      = params[ "surfaceComponents" ].as<std::string>();
        SurfelSet surfels;
        if ( component == "AnyBig" )
          {
            auto light_surface = makeLightDigitalSurface( bimage, K, params );
            surfels.insert( light_surface->begin(), light_surface->end() );
          }
        else if ( component == "All" )
          {
            Surfaces<KSpace>::sMakeBoundary( surfels, K, *bimage,
                                             K.lowerBound(), K.upperBound() );
          }
        return makeIdxDigitalSurface( surfels, K, params );
      }    

      /// Builds an indexed digital surface from a space \a K and an
      /// arbitrary range of surfels.
      ///
      /// @param[in] surfels an arbitrary range of surfels.
      ///
      /// @param[in] K the Khalimsky space whose domain encompasses the given surfels.
      ///
      /// @param[in] params the parameters:
      ///   - surfelAdjacency   [     0]: specifies the surfel adjacency (1:ext, 0:int)
      ///
      /// @return a smart pointer on the indexed digital surface built over the surfels.
      template <typename TSurfelRange>
        static CountedPtr<IdxDigitalSurface>
        makeIdxDigitalSurface
        ( const TSurfelRange&  surfels,
          ConstAlias< KSpace > K,
          const Parameters&    params = parametersDigitalSurface() )
        {
          bool surfel_adjacency      = params[ "surfelAdjacency" ].as<int>();
          SurfelAdjacency< KSpace::dimension > surfAdj( surfel_adjacency );
          // Build indexed digital surface.
          CountedPtr<ExplicitSurfaceContainer> ptrSurfContainer
            ( new ExplicitSurfaceContainer( K, surfAdj, surfels ) );
          CountedPtr<IdxDigitalSurface> ptrSurface
            ( new IdxDigitalSurface() );
          bool ok = ptrSurface->build( ptrSurfContainer );
          if ( !ok )
            trace.warning() << "[Shortcuts::makeIdxDigitalSurface]"
                            << " Error building indexed digital surface." << std::endl;
          return ptrSurface;
        }

      /// Builds an indexed digital surface from a light digital
      /// surface. Note that the surfel adjacency may be changed and a
      /// connected light digital surface could be disconnected in the process.
      ///
      /// @tparam TDigitalSurfaceContainer either kind of DigitalSurfaceContainer
      ///
      /// @param[in] surface a smart pointer on a (light or not) digital surface (e.g. DigitalSurface or LightDigitalSurface).
      ///
      /// @param[in] params the parameters:
      ///   - surfelAdjacency   [     0]: specifies the surfel adjacency (1:ext, 0:int)
      ///
      /// @return a smart pointer on the required indexed digital surface.
      template <typename TDigitalSurfaceContainer>
        static CountedPtr<IdxDigitalSurface>
        makeIdxDigitalSurface
        ( CountedPtr< ::DGtal::DigitalSurface< TDigitalSurfaceContainer> > surface,
          const Parameters&               params = parametersDigitalSurface() )
        {
          const KSpace& K = refKSpace( surface );
          SurfelSet     surfels;
          surfels.insert( surface->begin(), surface->end() );
          return makeIdxDigitalSurface( surfels, K, params );
        }    

      /// Builds an indexed digital surface from a vector of light digital
      /// surfaces. Note that the surfel adjacency may be changed and a
      /// connected light digital surface could be disconnected in the process.
      ///
      /// @note the surfaces must live in the same digital spaces. 
      ///
      /// @param[in] surfaces a vector of smart pointers on light digital surfaces.
      ///
      /// @param[in] params the parameters:
      ///   - surfelAdjacency   [     0]: specifies the surfel adjacency (1:ext, 0:int)
      ///
      /// @return a smart pointer on the required indexed digital surface.
      static CountedPtr<IdxDigitalSurface>
        makeIdxDigitalSurface
        ( const std::vector< CountedPtr<LightDigitalSurface> >& surfaces,
          const Parameters&       params = parametersDigitalSurface()  )
      {
        if ( surfaces.empty() ) return CountedPtr<IdxDigitalSurface>( 0 );
        const KSpace& K = surfaces[ 0 ]->container().space();
        SurfelSet     surfels;
        for ( std::size_t i = 0; i < surfaces.size(); ++i )
          {
            const KSpace& Ki = surfaces[ i ]->container().space();
            if ( ( Ki.lowerBound() != K.lowerBound() )
                 || ( Ki.upperBound() != K.upperBound() ) )
              trace.warning() << "[Shortcuts::makeIdxDigitalSurface]"
                              << " Incompatible digital spaces for surface " << i << std::endl;
            surfels.insert( surfaces[ i ]->begin(), surfaces[ i ]->end() );
          }
        return makeIdxDigitalSurface( surfels, K, params );
      }    

    
      /// Given any digital surface, returns the vector of its pointels.
      ///
      /// @note The order of pointels is given by the default traversal
      /// of the surfels of the surface, where the 4 pointels of each
      /// surfel are visited in order.
      ///
      /// @note If you wish to consider the primal digital surface, and
      /// visits pointels as vertices of this graph in
      /// breadth-first/depth-first order, the best is to build first a
      /// PolygonalSurface and then use specialized visitors.
      ///
      /// @tparam TDigitalSurfaceContainer either kind of DigitalSurfaceContainer
      ///
      /// @param[out] c2i the map Cell -> Vertex index in the pointel range.
      /// @param[in] surface a smart pointer on a (light or not) digital surface (e.g. DigitalSurface or LightDigitalSurface).
      ///
      /// @return a range of pointels as a vector.
      template <typename TDigitalSurfaceContainer>
        static PointelRange
        getPointelRange
        ( Cell2Index& c2i,
          CountedPtr< ::DGtal::DigitalSurface<TDigitalSurfaceContainer> > surface )
        {
          PointelRange result;
          result.reserve( surface->size() );
          const KSpace& K = refKSpace( surface );
          Idx n = 0;
          for ( auto&& surfel : *surface )
            {
              CellRange primal_vtcs = getPointelRange( K, surfel );
              for ( auto&& primal_vtx : primal_vtcs )
                {
                  if ( ! c2i.count( primal_vtx ) )
                    {
                      result.push_back( primal_vtx );
                      c2i[ primal_vtx ] = n++;
                    }
                }
            }
          return result;
        }

      /// Given any digital surface, returns the vector of its pointels.
      ///
      /// @note The order of pointels is given by the default traversal
      /// of the surfels of the surface, where the 4 pointels of each
      /// surfel are visited in order.
      ///
      /// @note If you wish to consider the primal digital surface, and
      /// visits pointels as vertices of this graph in
      /// breadth-first/depth-first order, the best is to build first a
      /// PolygonalSurface and then use specialized visitors.
      ///
      /// @tparam TDigitalSurfaceContainer either kind of DigitalSurfaceContainer
      ///
      /// @param[in] surface a smart pointer on a (light or not) digital surface (e.g. DigitalSurface or LightDigitalSurface).
      ///
      /// @return a range of pointels as a vector.
      template <typename TDigitalSurfaceContainer>
        static PointelRange
        getPointelRange
        ( CountedPtr< ::DGtal::DigitalSurface<TDigitalSurfaceContainer> > surface )
        {
          Cell2Index c2i;
          return getPointelRange( c2i, surface );
        }

      /// Given any surfel, returns its 4 pointels in ccw order.
      ///
      /// @see getPrimalVertices
      ///
      /// @param[in] K the Khalimsky space
      /// @param[in] surfel any surfel that lives in the Khalimsky space
      ///
      /// @return a range of pointels as a vector.
      static PointelRange
        getPointelRange
        ( const KSpace& K, const SCell& surfel )
      {
        return getPrimalVertices( K, surfel, true );
      }
    
      /// Given any digital surface, returns a vector of surfels in
      /// some specified order.
      ///
      /// @tparam TDigitalSurfaceContainer either kind of DigitalSurfaceContainer
      ///
      /// @param[in] surface a smart pointer on a (light or not) digital surface (e.g. DigitalSurface or LightDigitalSurface).
      ///
      /// @param[in] params the parameters:
      ///   - surfaceTraversal  ["Default"]: "Default"|"DepthFirst"|"BreadthFirst": "Default" default surface traversal, "DepthFirst": depth-first surface traversal, "BreadthFirst": breadth-first surface traversal.
      ///
      /// @return a range of surfels as a vector.
      template <typename TDigitalSurfaceContainer>
        static SurfelRange
        getSurfelRange
        ( CountedPtr< ::DGtal::DigitalSurface<TDigitalSurfaceContainer> > surface,
          const Parameters&   params = parametersDigitalSurface() )
        {
          return getSurfelRange( surface, *( surface->begin() ), params );
        }

      /// Given a light digital surface, returns a vector of surfels in
      /// some specified order.
      ///
      /// @tparam TDigitalSurfaceContainer either kind of DigitalSurfaceContainer
      ///
      /// @param[in] surface a smart pointer on a (light or not) digital surface (e.g. DigitalSurface or LightDigitalSurface).
      ///
      /// @param[in] start_surfel the surfel where the traversal starts
      /// in case of depth-first/breadth-first traversal.
      ///
      /// @param[in] params the parameters:
      ///   - surfaceTraversal  ["Default"]: "Default"|"DepthFirst"|"BreadthFirst": "Default" default surface traversal, "DepthFirst": depth-first surface traversal, "BreadthFirst": breadth-first surface traversal.
      ///
      /// @return a range of surfels as a vector.
      template <typename TDigitalSurfaceContainer>
        static SurfelRange
        getSurfelRange
        ( CountedPtr< ::DGtal::DigitalSurface<TDigitalSurfaceContainer> > surface,
          const Surfel&       start_surfel,
          const Parameters&   params = parametersDigitalSurface() )
        {
          typedef ::DGtal::DigitalSurface<TDigitalSurfaceContainer> AnyDigitalSurface;
          SurfelRange result;
          std::string traversal = params[ "surfaceTraversal" ].as<std::string>();
          if ( traversal == "DepthFirst" )
            {
              typedef DepthFirstVisitor< AnyDigitalSurface > Visitor;
              typedef GraphVisitorRange< Visitor > VisitorRange;
              VisitorRange range( new Visitor( *surface, start_surfel ) );
              std::for_each( range.begin(), range.end(),
                             [&result] ( Surfel s ) { result.push_back( s ); } );
            }
          else if ( traversal == "BreadthFirst" )
            {
              typedef BreadthFirstVisitor< AnyDigitalSurface > Visitor;
              typedef GraphVisitorRange< Visitor > VisitorRange;
              VisitorRange range( new Visitor( *surface, start_surfel ) );
              std::for_each( range.begin(), range.end(),
                             [&result] ( Surfel s ) { result.push_back( s ); } );
            }
          else
            {
              std::for_each( surface->begin(), surface->end(),
                             [&result] ( Surfel s ) { result.push_back( s ); } );
            }
          return result;
        }

      /// Given an indexed digital surface, returns a vector of surfels in
      /// some specified order.
      ///
      /// @param[in] surface a smart pointer on a digital surface.
      ///
      /// @param[in] params the parameters:
      ///   - surfaceTraversal  ["Default"]: "Default"|"DepthFirst"|"BreadthFirst": "Default" default surface traversal, "DepthFirst": depth-first surface traversal, "BreadthFirst": breadth-first surface traversal.
      ///
      /// @return a range of indexed surfels as a vector.
      static IdxSurfelRange
        getIdxSurfelRange
        ( CountedPtr<IdxDigitalSurface> surface,
          const Parameters&   params = parametersDigitalSurface() )
      {
        return getIdxSurfelRange( surface, (IdxSurfel) 0, params );
      }
    
      /// Given an indexed digital surface, returns a vector of surfels in
      /// some specified order.
      ///
      /// @param[in] surface a smart pointer on a digital surface.
      ///
      /// @param[in] start_surfel the surfel where the traversal starts
      /// in case of depth-first/breadth-first traversal.
      ///
      /// @param[in] params the parameters:
      ///   - surfaceTraversal  ["Default"]: "Default"|"DepthFirst"|"BreadthFirst": "Default" default surface traversal, "DepthFirst": depth-first surface traversal, "BreadthFirst": breadth-first surface traversal.
      ///
      /// @return a range of indexed surfels as a vector.
      static IdxSurfelRange
        getIdxSurfelRange
        ( CountedPtr<IdxDigitalSurface> surface,
          const IdxSurfel&    start_surfel,
          const Parameters&   params = parametersDigitalSurface() )
      {
        IdxSurfelRange result;
        std::string traversal = params[ "surfaceTraversal" ].as<std::string>();
        if ( traversal == "DepthFirst" )
          {
            typedef DepthFirstVisitor< IdxDigitalSurface > Visitor;
            typedef GraphVisitorRange< Visitor > VisitorRange;
            VisitorRange range( new Visitor( *surface, start_surfel ) );
            std::for_each( range.begin(), range.end(),
                           [&result] ( IdxSurfel s ) { result.push_back( s ); } );
          }
        else if ( traversal == "BreadthFirst" )
          {
            typedef BreadthFirstVisitor< IdxDigitalSurface > Visitor;
            typedef GraphVisitorRange< Visitor > VisitorRange;
            VisitorRange range( new Visitor( *surface, start_surfel ) );
            std::for_each( range.begin(), range.end(),
                           [&result] ( IdxSurfel s ) { result.push_back( s ); } );
          }
        else return surface->allVertices();
        return result;
      }

      /// Outputs a digital surface as an OBJ file (with its topology)
      /// and a material MTL file. Optionnaly you can specify the
      /// surfels normals and diffuse colors, and even specify how
      /// 0-cells are embedded into the space.
      ///
      /// @tparam TDigitalSurfaceContainer any model of concepts::CDigitalSurfaceContainer
      /// @tparam TCellEmbedder any type for maping Cell -> RealPoint.
      ///
      /// @param[in] digsurf the digital surface to output as an OBJ file
      /// @param[in] embedder any map Cell->RealPoint
      /// @param[in] normals the normal vector per face.
      /// @param[in] diffuse_colors either empty or a vector of size `trisurf.nbFaces` specifying the diffuse color for each face.
      /// @param[in] objfile the output filename.
      /// @param[in] ambient_color the ambient color of all faces.
      /// @param[in] diffuse_color the diffuse color of all faces (if diffuse_colors is empty).
      /// @param[in] specular_color the specular color of all faces.
      /// @return 'true' if the output stream is good.
      template <typename TDigitalSurfaceContainer,
        typename TCellEmbedder>
        static bool
        saveOBJ
        ( CountedPtr< ::DGtal::DigitalSurface<TDigitalSurfaceContainer> > digsurf,
          const TCellEmbedder&           embedder,
          const RealVectors&             normals,
          const Colors&                  diffuse_colors,
          std::string                    objfile,
          const Color&                   ambient_color  = Color( 32, 32, 32 ),
          const Color&                   diffuse_color  = Color( 200, 200, 255 ),
          const Color&                   specular_color = Color::White )
        {
          BOOST_STATIC_ASSERT (( KSpace::dimension == 3 ));
          std::string mtlfile;
          auto lastindex = objfile.find_last_of(".");
          if ( lastindex == std::string::npos )
            {
              mtlfile  = objfile + ".mtl";
              objfile  = objfile + ".obj";
            }
          else
            {
              mtlfile  = objfile.substr(0, lastindex) + ".mtl"; 
            }
          std::ofstream output_obj( objfile.c_str() );
          output_obj << "#  OBJ format" << std::endl;
          output_obj << "# DGtal::MeshHelpers::exportOBJwithFaceNormalAndColor" << std::endl;
          output_obj << "o anObject" << std::endl;
          output_obj << "mtllib " << mtlfile << std::endl;
          std::ofstream output_mtl( mtlfile.c_str() );
          output_mtl << "#  MTL format"<< std::endl;
          output_mtl << "# generated from MeshWriter from the DGTal library"<< std::endl;
          // Number and output vertices.
          const KSpace&     K = refKSpace( digsurf );
          Cell2Index      c2i;
          auto       pointels = getPointelRange( c2i, digsurf );
          for ( auto&& pointel : pointels )
            {
              RealPoint p = embedder( pointel );
              output_obj << "v " << p[ 0 ] << " " << p[ 1 ] << " " << p[ 2 ] << std::endl;
            }	
          // Taking care of normals
          Idx nbfaces = digsurf->size();
          bool has_normals = ( nbfaces == normals.size() );
          if ( has_normals )
            {
              for ( Idx f = 0; f < nbfaces; ++f )
                {
                  const auto& p = normals[ f ];
                  output_obj << "vn " << p[ 0 ] << " " << p[ 1 ] << " " << p[ 2 ] << std::endl;
                }
            }
          // Taking care of materials
          bool has_material = ( nbfaces == diffuse_colors.size() );
          Idx   idxMaterial = 0;
          std::map<Color, unsigned int > mapMaterial;
          // MeshHelpers::exportMTLNewMaterial
          // 	( output_mtl, idxMaterial, ambient_color, Color::Black, specular_color );
          // mapMaterial[ Color::Black ] = idxMaterial++;
          if ( has_material )
            {
              for ( Idx f = 0; f < nbfaces; ++f )
                {
                  Color c = diffuse_colors[ f ];
                  if ( mapMaterial.count( c ) == 0 )
                    {
                      MeshHelpers::exportMTLNewMaterial
                        ( output_mtl, idxMaterial, ambient_color, c, specular_color );
                      mapMaterial[ c ] = idxMaterial++;
                    }
                }
            }
          else
            {
              MeshHelpers::exportMTLNewMaterial
                ( output_mtl, idxMaterial, ambient_color, diffuse_color, specular_color );
            }
      
          // Taking care of faces
          Idx f = 0;
          for ( auto&& surfel : *digsurf )
            {
              output_obj << "usemtl material_"
                         << ( has_material ? mapMaterial[ diffuse_colors[ f ] ] : idxMaterial )
                         << std::endl; 
              output_obj << "f";
              auto primal_vtcs = getPointelRange( K, surfel );
              // The +1 in lines below is because indexing starts at 1 in OBJ file format.
              if ( has_normals )
                {
                  for ( auto&& primal_vtx : primal_vtcs )
                    output_obj << " " << (c2i[ primal_vtx ]+1) << "//" << (f+1);
                }
              else
                {
                  for ( auto&& primal_vtx : primal_vtcs )
                    output_obj << " " << (c2i[ primal_vtx ]+1);
                }
              output_obj << std::endl;
              f += 1;
            }
          output_mtl.close();
          return output_obj.good();
        }
    
      /// Outputs a digital surface as an OBJ file (with its topology)
      /// and a material MTL file. Optionnaly you can specify the
      /// surfels normals and diffuse colors. Here surfels are
      /// canonically embedded into the space.
      ///
      /// @tparam TDigitalSurfaceContainer any model of concepts::CDigitalSurfaceContainer
      ///
      /// @param[in] digsurf the digital surface to output as an OBJ file
      /// @param[in] normals the normal vector per face.
      /// @param[in] diffuse_colors either empty or a vector of size `trisurf.nbFaces` specifying the diffuse color for each face.
      /// @param[in] objfile the output filename.
      /// @param[in] ambient_color the ambient color of all faces.
      /// @param[in] diffuse_color the diffuse color of all faces (if diffuse_colors is empty).
      /// @param[in] specular_color the specular color of all faces.
      /// @return 'true' if the output stream is good.
      template <typename TDigitalSurfaceContainer>
        static bool
        saveOBJ
        ( CountedPtr< ::DGtal::DigitalSurface<TDigitalSurfaceContainer> > digsurf,
          const RealVectors&                            normals,
          const Colors&                                 diffuse_colors,
          std::string                                   objfile,
          const Color&                   ambient_color  = Color( 32, 32, 32 ),
          const Color&                   diffuse_color  = Color( 200, 200, 255 ),
          const Color&                   specular_color = Color::White )
        {
          auto embedder = getCellEmbedder( digsurf );
          return saveOBJ( digsurf, embedder, normals, diffuse_colors, objfile,
                          ambient_color, diffuse_color, specular_color );
        }

      /// Outputs a digital surface as an OBJ file (with its topology)
      /// and a simple MTL file. Here surfels are canonically embedded
      /// into the space.
      ///
      /// @tparam TDigitalSurfaceContainer any model of concepts::CDigitalSurfaceContainer
      ///
      /// @param[in] digsurf the digital surface to output as an OBJ file
      /// @param[in] objfile the output filename.
      /// @param[in] ambient_color the ambient color of all faces.
      /// @param[in] diffuse_color the diffuse color of all faces (if diffuse_colors is empty).
      /// @param[in] specular_color the specular color of all faces.
      /// @return 'true' if the output stream is good.
      template <typename TDigitalSurfaceContainer>
        static bool
        saveOBJ
        ( CountedPtr< ::DGtal::DigitalSurface<TDigitalSurfaceContainer> > digsurf,
          std::string                                   objfile,
          const Color&                   ambient_color  = Color( 32, 32, 32 ),
          const Color&                   diffuse_color  = Color( 200, 200, 255 ),
          const Color&                   specular_color = Color::White )
        {
          auto embedder = getCellEmbedder( digsurf );
          return saveOBJ( digsurf, embedder, RealVectors(), Colors(), objfile,
                          ambient_color, diffuse_color, specular_color );
        }


      // ----------------------- Mesh services ------------------------------
    public:

      /// @return the parameters and their default values which are
      /// related to meshes.
      ///   - faceSubdivision ["Centroid"]: "No"|"Naive"|"Centroid" specifies how polygonal faces should be subdivided when triangulated or when exported.
      static Parameters parametersMesh()
      {
        return Parameters
          ( "faceSubdivision", "Centroid" ); 
      }
      
      /// Builds a triangulated surface (class TriangulatedSurface) from
      /// a mesh (class Mesh). Note that a triangulated surface contains
      /// only triangles, so polygonal faces (0,1,2,3,4,...) of the
      /// input mesh are (naively) triangulated (triangles (0,1,2),
      /// (0,2,3), (0,3,4), etc). Furthermore, the output triangulated
      /// surface rebuilds a topology between faces.
      ///
      /// @param[in] aMesh any mesh (which should be a valid combinatorial surface).
      ///
      /// @return a smart pointer on the built triangulated surface or 0 if
      /// the mesh was invalid.
      static CountedPtr< TriangulatedSurface >
        makeTriangulatedSurface( CountedPtr< Mesh > aMesh )
      {
        auto pTriSurf = CountedPtr<TriangulatedSurface>
          ( new TriangulatedSurface ); // acquired
        bool ok = MeshHelpers::mesh2TriangulatedSurface( *aMesh, *pTriSurf );
        return ok ? pTriSurf : CountedPtr< TriangulatedSurface >( nullptr );
      }

      /// Builds a mesh (class Mesh) from a triangulated surface (class
      /// TriangulatedSurface). Note that the mesh looses the topology
      /// of the triangulated surface, since it is essentially a soup of
      /// triangles.
      ///
      /// @param[in]  triSurf the input triangulated surface mesh.
      /// @param[in]  aColor the default color of the mesh.
      /// @return a smart pointer on the output mesh.
      static CountedPtr< Mesh >
        makeMesh( CountedPtr< TriangulatedSurface > triSurf,
                  const Color& aColor = Color::White )
      {
        auto pMesh = CountedPtr<Mesh>( new Mesh( aColor ) ); // acquired
        MeshHelpers::triangulatedSurface2Mesh( *triSurf, *pMesh );
        return pMesh;
      }

      /// Builds a mesh (class Mesh) from a polygonal surface (class
      /// PolygonalSurface). Note that the mesh looses the topology
      /// of the polygonal surface, since it is essentially a soup of
      /// triangles.
      ///
      /// @param[in]  polySurf the input polygonal surface mesh.
      /// @param[in]  aColor the default color of the mesh.
      /// @return a smart pointer on the output mesh.
      static CountedPtr< Mesh >
        makeMesh( CountedPtr< PolygonalSurface > polySurf,
                  const Color& aColor = Color::White )
      {
        auto pMesh = CountedPtr<Mesh>( new Mesh( aColor ) ); // acquired
        MeshHelpers::polygonalSurface2Mesh( *polySurf, *pMesh );
        return pMesh;
      }

      /// Builds the dual triangulated surface associated to the given digital surface.
      ///
      /// @tparam TContainer the digital surface container
      /// @param[out] s2i the map Surfel -> Vertex index in the triangulated surface.
      /// @param[in] aSurface any digital surface (e.g. LightDigitalSurface or DigitalSurface)
      /// @return a smart pointer on the built triangulated surface.
      template < typename TContainer >
        static CountedPtr< TriangulatedSurface >
        makeTriangulatedSurface( Surfel2Index& s2i,
                                 CountedPtr< ::DGtal::DigitalSurface< TContainer > > aSurface )
        {
          auto embedder = getCellEmbedder( aSurface );
          auto pTriSurf = CountedPtr<TriangulatedSurface>
	    ( new TriangulatedSurface ); // acquired
          MeshHelpers::digitalSurface2DualTriangulatedSurface
            ( *aSurface, embedder, *pTriSurf, s2i );
          return pTriSurf;
        }

      /// Builds the dual triangulated surface associated to the given digital surface.
      ///
      /// @tparam TContainer the digital surface container
      /// @param[in] aSurface any digital surface (e.g. LightDigitalSurface or DigitalSurface)
      /// @return a smart pointer on the built triangulated surface.
      template < typename TContainer >
        static CountedPtr< TriangulatedSurface >
        makeTriangulatedSurface( CountedPtr< ::DGtal::DigitalSurface< TContainer > > aSurface )
        {
          Surfel2Index s2i;
          return makeTriangulatedSurface( s2i, aSurface );
        }

      /// Builds a triangulated surface from a polygonal surface.
      ///
      /// @note Be \b very \b careful \b with \b "Naive" \b subdivision,
      /// since it may create non-manifold edges on general polygonal
      /// surfaces. Indeed, take the closed surface made of faces (0, 1,
      /// 2, 3) and (3, 2, 1, 0). Depending on how faces are
      /// triangulated, it is still a valid combinatorial triangulated
      /// 2-manifold (e.g. (0,1,2,3) gives (0,1,2) and (2,0,3) and
      /// (3,2,1,0) gives (3,2,1) and (1,3,0)) or a non-valid one
      /// (e.g. (0,1,2,3) gives (0,1,2) and (2,0,3) and (3,2,1,0) gives
      /// (3,2,0) and (0,2,1): then edge {2,0} is shared by four faces).
      ///
      /// @param[in] polySurf any polygonal surface.
      /// @param[in] params the parameters:
      ///   - faceSubdivision ["Centroid"]: "No"|"Naive"|"Centroid" specifies how faces are subdivided, "No" is considered as "Naive" since faces must be triangulated.
      ///
      /// @return a smart pointer on the built triangulated surface.
      static CountedPtr< TriangulatedSurface >
        makeTriangulatedSurface( CountedPtr< PolygonalSurface > polySurf,
                                 const Parameters&   params = parametersMesh() )
      {
        std::string faceSubdivision = params[ "faceSubdivision" ].as<std::string>();
        bool centroid = ( faceSubdivision == "Centroid" );
        auto pTriSurf = CountedPtr<TriangulatedSurface>
          ( new TriangulatedSurface ); // acquired
        MeshHelpers::polygonalSurface2TriangulatedSurface( *polySurf, *pTriSurf, centroid );
        return pTriSurf;
      }
    
      /// Builds a polygon mesh (class PolygonalSurface) from
      /// a mesh (class Mesh). The output polygonal
      /// surface rebuilds a topology between faces.
      ///
      /// @param[in] aMesh any mesh (which should be a valid combinatorial surface).
      ///
      /// @return a smart pointer on the built polygonal surface or 0 if
      /// the mesh was invalid.
      static CountedPtr< PolygonalSurface >
        makePolygonalSurface( CountedPtr< Mesh > aMesh )
      {
        auto pPolySurf = CountedPtr<PolygonalSurface>
          ( new PolygonalSurface ); // acquired
        bool ok = MeshHelpers::mesh2PolygonalSurface( *aMesh, *pPolySurf );
        return ok ? pPolySurf : CountedPtr< PolygonalSurface >( nullptr );
      }

      /// Builds the polygonal marching-cubes surface that approximate an
      /// iso-surface of value "thresholdMin+0.5" in the given 3D
      /// gray-scale image.
      ///
      /// @param[in] gray_scale_image any gray-scale image.
      /// @param[in] params the parameters: 
      ///   - surfelAdjacency[0]: specifies the surfel adjacency (1:ext, 0:int)
      ///   - thresholdMin   [0]: specifies the threshold min (excluded) to define binary shape
      ///   - gridsizex    [1.0]: specifies the space between points along x.
      ///   - gridsizey    [1.0]: specifies the space between points along y.
      ///   - gridsizez    [1.0]: specifies the space between points along z.
      /// @return a smart pointer on the built polygonal surface or 0 if
      /// the mesh was invalid.
      static CountedPtr< PolygonalSurface >
        makePolygonalSurface( CountedPtr<GrayScaleImage> gray_scale_image,
                              const Parameters&          params =
                              parametersKSpace()
                              | parametersBinaryImage()
                              | parametersDigitalSurface() )
      {
        auto K       = getKSpace( gray_scale_image );
        auto bimage  = makeBinaryImage( gray_scale_image, params );
        auto digSurf = makeDigitalSurface( bimage, K, params );
        RealVector gh = { params[ "gridsizex" ].as<double>(),
                          params[ "gridsizey" ].as<double>(),
                          params[ "gridsizez" ].as<double>() };
        double threshold = params[ "thresholdMin" ].as<double>() + 0.5;
        typedef RegularPointEmbedder<Space>         PointEmbedder;
        typedef ImageLinearCellEmbedder
          < KSpace, GrayScaleImage, PointEmbedder > ImageCellEmbedder;
        PointEmbedder pembedder;
        pembedder.init( gh );
        ImageCellEmbedder cembedder;
        cembedder.init( K, *gray_scale_image, pembedder, threshold );
        auto pPolySurf = CountedPtr<PolygonalSurface>
          ( new PolygonalSurface ); // acquired
        Surfel2Index s2i;
        MeshHelpers::digitalSurface2DualPolygonalSurface
          ( *digSurf, cembedder, *pPolySurf, s2i );
        return pPolySurf;
      }

      /// Builds the marching-cubes surface that approximate an
      /// iso-surface of value "thresholdMin+0.5" in the given 3D
      /// gray-scale image. Non triangular faces are triangulated by
      /// putting a centroid vertex.
      ///
      /// @param[in] gray_scale_image any gray-scale image.
      /// @param[in] params the parameters:
      ///   - surfelAdjacency[0]: specifies the surfel adjacency (1:ext, 0:int)
      ///   - thresholdMin   [0]: specifies the threshold min (excluded) to define binary shape
      ///   - gridsizex    [1.0]: specifies the space between points along x.
      ///   - gridsizey    [1.0]: specifies the space between points along y.
      ///   - gridsizez    [1.0]: specifies the space between points along z.
      /// @return a smart pointer on the built triangulated surface or 0 if
      /// the mesh was invalid.
      static CountedPtr< TriangulatedSurface >
        makeTriangulatedSurface( CountedPtr<GrayScaleImage> gray_scale_image,
                                 const Parameters&          params =
                                 parametersKSpace()
                                 | parametersBinaryImage()
                                 | parametersDigitalSurface() )
      {
        auto K       = getKSpace( gray_scale_image );
        auto bimage  = makeBinaryImage( gray_scale_image, params );
        auto digSurf = makeDigitalSurface( bimage, K, params );
        RealVector gh = { params[ "gridsizex" ].as<double>(),
                          params[ "gridsizey" ].as<double>(),
                          params[ "gridsizez" ].as<double>() };
        double threshold = params[ "thresholdMin" ].as<double>() + 0.5;
        typedef RegularPointEmbedder<Space>         PointEmbedder;
        typedef ImageLinearCellEmbedder
          < KSpace, GrayScaleImage, PointEmbedder > ImageCellEmbedder;
        PointEmbedder pembedder;
        pembedder.init( gh );
        ImageCellEmbedder cembedder;
        cembedder.init( K, *gray_scale_image, pembedder, threshold );
        auto pPolySurf = CountedPtr<TriangulatedSurface>
          ( new TriangulatedSurface ); // acquired
        Surfel2Index s2i;
        MeshHelpers::digitalSurface2DualTriangulatedSurface
          ( *digSurf, cembedder, *pPolySurf, s2i );
        return pPolySurf;
      }

      /// Builds the dual polygonal surface associated to the given
      /// digital surface.
      ///
      /// @tparam TContainer the digital surface container
      /// @param[out] s2i the map Surfel -> Vertex index in the polygonal surface.
      /// @param[in] aSurface any digital surface (e.g. DigitalSurface or LightDigitalSurface)
      /// @return a smart pointer on the built polygonal surface.
      template < typename TContainer >
        static CountedPtr< PolygonalSurface >
        makeDualPolygonalSurface( Surfel2Index& s2i,
                                  CountedPtr< ::DGtal::DigitalSurface< TContainer > > aSurface )
        {
          BOOST_STATIC_ASSERT (( KSpace::dimension == 3 ));
          auto embedder = getCellEmbedder( aSurface );
          auto pPolySurf = CountedPtr<PolygonalSurface>
	    ( new PolygonalSurface ); // acquired
          MeshHelpers::digitalSurface2DualPolygonalSurface
            ( *aSurface, embedder, *pPolySurf, s2i );
          return pPolySurf;
        }

      /// Builds the dual polygonal surface associated to the given
      /// digital surface.
      ///
      /// @tparam TContainer the digital surface container
      /// @param[in] aSurface any digital surface (e.g. DigitalSurface or LightDigitalSurface)
      /// @return a smart pointer on the built polygonal surface.
      template < typename TContainer >
        static CountedPtr< PolygonalSurface >
        makeDualPolygonalSurface( CountedPtr< ::DGtal::DigitalSurface< TContainer > > aSurface )
        {
          Surfel2Index s2i;
          return makeDualPolygonalSurface( s2i, aSurface );
        }

      /// Builds the dual polygonal surface associated to the given
      /// indexed digital surface.
      ///
      /// @tparam TContainer the digital surface container
      /// @param[in] aSurface any indexed digital surface (e.g. IdxDigitalSurface)
      /// @return a smart pointer on the built polygonal surface.
      template < typename TContainer >
        static CountedPtr< PolygonalSurface >
        makeDualPolygonalSurface
        ( CountedPtr< ::DGtal::IndexedDigitalSurface< TContainer > > aSurface )
        {
          BOOST_STATIC_ASSERT (( KSpace::dimension == 3 ));
          auto pPolySurf = CountedPtr<PolygonalSurface>
            ( new PolygonalSurface( aSurface->heds(),
                                    aSurface->positions().storage() ) );
          return pPolySurf;
        }

      /// Builds the primal polygonal surface associated to the given
      /// digital surface.
      ///
      /// @tparam TContainer the digital surface container
      /// @param[out] c2i the map Cell -> Vertex index in the polygonal surface.
      /// @param[in] aSurface any digital surface (e.g. DigitalSurface or LightDigitalSurface)
      /// @return a smart pointer on the built polygonal surface or 0 if it fails because aSurface is not a combinatorial 2-manifold.
      template < typename TContainer >
        static CountedPtr< PolygonalSurface >
        makePrimalPolygonalSurface( Cell2Index& c2i,
                                    CountedPtr< ::DGtal::DigitalSurface<TContainer> > aSurface )
        {
          BOOST_STATIC_ASSERT (( KSpace::dimension == 3 ));
          auto embedder = getCellEmbedder( aSurface );
          auto pPolySurf = CountedPtr<PolygonalSurface>
            ( new PolygonalSurface ); // acquired
          bool ok = MeshHelpers::digitalSurface2PrimalPolygonalSurface
            ( *aSurface, embedder, *pPolySurf, c2i );
          return ok ? pPolySurf : CountedPtr< PolygonalSurface >( nullptr );
        }

      /// Builds the primal polygonal surface associated to the given
      /// digital surface.
      ///
      /// @tparam TContainer the digital surface container
      /// @param[in] aSurface any digital surface (e.g. DigitalSurface or LightDigitalSurface)
      /// @return a smart pointer on the built polygonal surface or 0 if it fails because aSurface is not a combinatorial 2-manifold.
      template < typename TContainer >
        static CountedPtr< PolygonalSurface >
        makePrimalPolygonalSurface( CountedPtr< ::DGtal::DigitalSurface<TContainer> > aSurface )
        {
          Cell2Index c2i;
          return makePrimalPolygonalSurface( c2i, aSurface );
        }

      /// Builds the primal polygonal surface associated to the given
      /// indexed digital surface.
      ///
      /// @tparam TContainer the digital surface container
      /// @param[in] aSurface any indexed digital surface (e.g. IdxDigitalSurface)
      /// @return a smart pointer on the built polygonal surface or 0 if it fails because aSurface is not a combinatorial 2-manifold.
      template < typename TContainer >
        static CountedPtr< PolygonalSurface >
        makePrimalPolygonalSurface
        ( CountedPtr< ::DGtal::IndexedDigitalSurface<TContainer> > aSurface )
        {
          auto dsurf = makeDigitalSurface( aSurface );
          Cell2Index c2i;
          return makePrimalPolygonalSurface( c2i, dsurf );
        }

      /// Outputs a polygonal surface as an OBJ file (with its topology).
      ///
      /// @tparam TPoint any model of point
      /// @param[in] polysurf the polygonal surface to output as an OBJ file
      /// @param[in] objfile the output filename.
      /// @return 'true' if the output stream is good.
      template <typename TPoint>
        static bool
        saveOBJ
        ( CountedPtr< ::DGtal::PolygonalSurface<TPoint> > polysurf,
          const std::string&                            objfile )
        {
          std::ofstream output( objfile.c_str() );
          bool ok = MeshHelpers::exportOBJ( output, *polysurf );
          output.close();
          return ok;
        }

      /// Outputs a triangulated surface as an OBJ file (with its topology).
      ///
      /// @tparam TPoint any model of point
      /// @param[in] trisurf the triangulated surface to output as an OBJ file
      /// @param[in] objfile the output filename.
      /// @return 'true' if the output stream is good.
      template <typename TPoint>
        static bool
        saveOBJ
        ( CountedPtr< ::DGtal::TriangulatedSurface<TPoint> > trisurf,
          const std::string&                               objfile )
        {
          std::ofstream output( objfile.c_str() );
          bool ok = MeshHelpers::exportOBJ( output, *trisurf );
          output.close();
          return ok;
        }

      /// Outputs a polygonal surface as an OBJ file (with its topology)
      /// (and a material MTL file).
      ///
      /// @tparam TPoint any model of point
      /// @param[in] polysurf the polygonal surface to output as an OBJ file
      /// @param[in] normals the normal vector per face.
      /// @param[in] diffuse_colors either empty or a vector of size `polysurf.nbFaces` specifying the diffuse color for each face.
      /// @param[in] objfile the output filename.
      /// @param[in] ambient_color the ambient color of all faces.
      /// @param[in] diffuse_color the diffuse color of all faces (if diffuse_colors is empty).
      /// @param[in] specular_color the specular color of all faces.
      /// @return 'true' if the output stream is good.
      template <typename TPoint>
        static bool
        saveOBJ
        ( CountedPtr< ::DGtal::PolygonalSurface<TPoint> > polysurf,
          const RealVectors&                            normals,
          const Colors&                                 diffuse_colors,
          std::string                                   objfile,
          const Color&                   ambient_color  = Color( 32, 32, 32 ),
          const Color&                   diffuse_color  = Color( 200, 200, 255 ),
          const Color&                   specular_color = Color::White )
        {
          std::string mtlfile;
          auto lastindex = objfile.find_last_of(".");
          if ( lastindex == std::string::npos )
            {
              mtlfile  = objfile + ".mtl";
              objfile  = objfile + ".obj";
            }
          else
            {
              mtlfile  = objfile.substr(0, lastindex) + ".mtl"; 
            }
          std::ofstream output( objfile.c_str() );
          bool ok = MeshHelpers::exportOBJwithFaceNormalAndColor
            ( output, mtlfile, *polysurf, normals, diffuse_colors,
              ambient_color, diffuse_color, specular_color );
          output.close();
          return ok;
        }

      /// Outputs a triangulated surface as an OBJ file (with its topology)
      /// (and a material MTL file).
      ///
      /// @tparam TPoint any model of point
      /// @param[in] trisurf the triangulated surface to output as an OBJ file
      /// @param[in] normals the normal vector per face.
      /// @param[in] diffuse_colors either empty or a vector of size `trisurf.nbFaces` specifying the diffuse color for each face.
      /// @param[in] objfile the output filename.
      /// @param[in] ambient_color the ambient color of all faces.
      /// @param[in] diffuse_color the diffuse color of all faces (if diffuse_colors is empty).
      /// @param[in] specular_color the specular color of all faces.
      /// @return 'true' if the output stream is good.
      template <typename TPoint>
        static bool
        saveOBJ
        ( CountedPtr< ::DGtal::TriangulatedSurface<TPoint> > trisurf,
          const RealVectors&                            normals,
          const Colors&                                 diffuse_colors,
          std::string                                   objfile,
          const Color&                   ambient_color  = Color( 32, 32, 32 ),
          const Color&                   diffuse_color  = Color( 200, 200, 255 ),
          const Color&                   specular_color = Color::White )
        {
          std::string mtlfile;
          auto lastindex = objfile.find_last_of(".");
          if ( lastindex == std::string::npos )
            {
              mtlfile  = objfile + ".mtl";
              objfile  = objfile + ".obj";
            }
          else
            {
              mtlfile  = objfile.substr(0, lastindex) + ".mtl"; 
            }
          std::ofstream output( objfile.c_str() );
          bool ok = MeshHelpers::exportOBJwithFaceNormalAndColor
            ( output, mtlfile, *trisurf, normals, diffuse_colors,
              ambient_color, diffuse_color, specular_color );
          output.close();
          return ok;
        }


    
      // ------------------------------ utilities ------------------------------
    public:

      /// @return the parameters and their default values which are
      /// related to utilities
      ///   - colormap   [ "Custom" ]: "Cool"|"Copper"|"Hot"|"Jet"|"Spring"|"Summer"|"Autumn"|"Winter"|"Error"|"Custom" specifies standard colormaps (if invalid, falls back to "Custom").
      ///   - zero-tic   [      0.0 ]: if positive defines a black zone ]-zt,zt[ in the colormap.
      static Parameters parametersUtilities()
      {
        return Parameters
          ( "colormap", "Custom" )
          ( "zero-tic", 0.0 ); 
      }

      /// Given two ranges with same elements but not necessarily in the
      /// same order, returns a vector V: index -> index such that `s1[
      /// i ] == s2[ V[ i ] ]`.
      ///
      /// @tparam TValue a model of boost::Assignable,
      /// boost::CopyConstructible, boost::LessThanComparable
      ///
      /// @param[in] s1 a range of values
      /// @param[in] s2 another range of values which contains the same values as \a s1 but in any order.
      /// @param[in] perfect if 'true' ask for a perfect match, otherwise extracts correspondences.
      ///
      /// @return the vector V: index -> index such that `s1[ i ] == s2[
      /// V[ i ] ]`. If \a perfect is true, then an empty range is
      /// returned in case of mismatch.
      ///
      /// @note if `perfect==false` and `s1[ i ]` is not in `s2`, then `V[ i ] = s2.size()`.
      template <typename TValue>
        static IdxRange
        getRangeMatch( const std::vector< TValue >& s1, const std::vector< TValue >& s2,
                       bool perfect = false )
        {
          if ( perfect && ( s1.size() != s2.size() ) ) return IdxRange();
          std::map<TValue, Idx> M;
          Idx idx = 0;
          for ( auto val : s2 ) M[ val ] = idx++;
          IdxRange V( s1.size() );
          idx = 0;
          for ( auto val : s1 )
            {
              auto it = M.find( val );
              if ( it != M.end() ) V[ idx++ ] = it->second;
              else
                {
                  if ( perfect ) return IdxRange();
                  V[ idx++ ] = s2.size();
                }
            }
          return V;
        }

      /// Given a perfect or approximate \a match, returns the
      /// corresponding reordered/rematched \a range.
      ///
      /// @param[in] range any range.
      ///
      /// @param[in] match a function V: Idx -> Idx such that `result[ i
      /// ] = range[ match[ i ] ]`.
      ///
      /// @return the the corresponding reordered/rematched \a range.
      ///
      /// @see getRangeMatch
      template <typename TValue>
        static std::vector< TValue >
        getMatchedRange( const std::vector< TValue >& range, const IdxRange& match )
        {
          std::vector< TValue > result( match.size() );
          for ( Idx i = 0; i < result.size(); i++ )
            result[ i ] = range[ match[ i ] ]; 
          return result;
        }
    
    
      /// @param[in] min the minimum considered value for the colormap.
      /// @param[in] max the maximum considered value for the colormap.
      /// @param[in] params the parameters:
      ///   - colormap   [ "Custom" ]: "Cool"|"Copper"|"Hot"|"Jet"|"Spring"|"Summer"|"Autumn"|"Winter"|"Error"|"Custom" specifies standard colormaps (if invalid, falls back to "Custom").
      /// @return a colormap according to the specified parameters
      static ColorMap
        getColorMap( Scalar            min,
                     Scalar            max,
                     const Parameters& params = parametersUtilities() )
      {
        std::string cmap = params[ "colormap" ].as<std::string>();
        if      ( cmap == "Cool" )   return ColorMap( min, max, CMAP_COOL );
        else if ( cmap == "Copper" ) return ColorMap( min, max, CMAP_COPPER );
        else if ( cmap == "Hot" )    return ColorMap( min, max, CMAP_HOT );
        else if ( cmap == "Jet" )    return ColorMap( min, max, CMAP_JET );
        else if ( cmap == "Spring" ) return ColorMap( min, max, CMAP_SPRING );
        else if ( cmap == "Summer" ) return ColorMap( min, max, CMAP_SUMMER );
        else if ( cmap == "Autumn" ) return ColorMap( min, max, CMAP_AUTUMN );
        else if ( cmap == "Winter" ) return ColorMap( min, max, CMAP_WINTER );
        else if ( cmap == "Error" )
          {
            ColorMap gradcmap( min, max );
            gradcmap.addColor( Color( 255, 255, 255 ) );
            gradcmap.addColor( Color( 255,   0,   0 ) );
            gradcmap.addColor( Color( 0,   0,   0 ) );
            return gradcmap;
          }
        // Custom colormap 
        ColorMap gradcmap( min, max );
        gradcmap.addColor( Color( 0, 0, 255 ) );
        gradcmap.addColor( Color( 0, 255, 255 ) );
        gradcmap.addColor( Color( 255, 255, 255 ) );
        gradcmap.addColor( Color( 255, 255, 0 ) );
        gradcmap.addColor( Color( 255, 0, 0 ) );
        return gradcmap;
      }

      /// @param[in] min the minimum considered value for the colormap.
      /// @param[in] max the maximum considered value for the colormap.
      /// @param[in] params the parameters:
      ///   - colormap   [ "Custom" ]: "Cool"|"Copper"|"Hot"|"Jet"|"Spring"|"Summer"|"Autumn"|"Winter"|"Error"|"Custom" specifies standard colormaps (if invalid, falls back to "Custom").
      ///   - zero-tic   [      0.0 ]: if positive defines a black zone ]-zt,zt[ in the colormap.
      /// @return a colormap according to the specified parameters adapted to make darker tics for a background "Tics" colormap.
      static ZeroTickedColorMap
        getZeroTickedColorMap( Scalar           min,
                               Scalar           max,
                               const Parameters& params = parametersUtilities() )
      {
        auto cmap = getColorMap( min, max, params );
        auto ztic = params[ "zero-tic" ].as<double>();
        ZeroTickedColorMap ztic_cmap( cmap, Color::Black );
        if ( ztic <= 0.0 ) return ztic_cmap;
        if ( min <= 0.0 && 0.0 <= max )
          ztic_cmap.addTick( 0.0, ztic );
        ztic_cmap.finalize();
        return ztic_cmap;
      }

    
      /// Outputs a range of surfels as an OBJ file, embedding each
      /// vertex using the given cell embedder (3D only).
      ///
      /// @tparam TCellEmbedder any model of CCellEmbedder
      /// @param[out] output the output stream.
      /// @param[in] surfels the range of surfels (oriented cells of dimension 2).
      /// @param[in] embedder the embedder for mapping surfel vertices (cells of dimension 0) to points in space.
      /// @return 'true' if the output stream is good.
      template <typename TCellEmbedder = CanonicCellEmbedder< KSpace > >
        static bool
        outputSurfelsAsObj
        ( std::ostream&              output,
          const SurfelRange&         surfels,
          const TCellEmbedder&       embedder )
        {
          typedef unsigned long Size;
          BOOST_STATIC_ASSERT (( KSpace::dimension == 3 ));
          BOOST_CONCEPT_ASSERT(( concepts::CCellEmbedder< TCellEmbedder > ));
          const KSpace& K = embedder.space();
          // Number and output vertices.
          std::map< Cell, Size > vtx_numbering;
          Size n = 1;  // OBJ vertex numbering start at 1 
          for ( auto&& s : surfels )
            {
              auto primal_vtcs = getPointelRange( K, s );
              for ( auto&& primal_vtx : primal_vtcs )
                {
                  if ( ! vtx_numbering.count( primal_vtx ) )
                    {
                      vtx_numbering[ primal_vtx ] = n++;
                      // Output vertex positions
                      RealPoint p = embedder( primal_vtx );
                      output << "v " << p[ 0 ] << " " << p[ 1 ] << " " << p[ 2 ] << std::endl;
                    }
                }
            }
          // Outputs all faces
          for ( auto&& s : surfels )
            {
              output << "f";
              auto primal_vtcs = getPointelRange( K, s, true );
              for ( auto&& primal_vtx : primal_vtcs )
                output << " " << vtx_numbering[ primal_vtx ];
              output << std::endl;
            }      
          return output.good();
        }
    
      /// Outputs a digital surface, seen from the primal point of view
      /// (surfels=face), as an OBJ file (3D only). Note that faces are
      /// oriented consistently (normals toward outside).
      ///
      /// @tparam TAnyDigitalSurface either kind of DigitalSurface, like
      /// Shortcuts::LightDigitalSurface or Shortcuts::DigitalSurface.
      ///
      /// @param[out] output the output stream.
      /// @param[in] surface a smart pointer on a digital surface.
      ///
      /// @return 'true' if the output stream is good.
      template <typename TAnyDigitalSurface>
        static bool
        outputPrimalDigitalSurfaceAsObj
        ( std::ostream&              output,
          CountedPtr<TAnyDigitalSurface> surface )
        {
          auto embedder = getCellEmbedder( surface );
          return outputPrimalDigitalSurfaceAsObj( output, surface, embedder );
        }
    
      /// Outputs a digital surface, seen from the primal point of view
      /// (surfels=face), as an OBJ file (3D only). Note that faces are
      /// oriented consistently (normals toward outside). Each vertex is
      /// mapped to a 3D point using the given cell embedder.
      ///
      /// @tparam TAnyDigitalSurface either kind of DigitalSurface, like
      /// Shortcuts::LightDigitalSurface or Shortcuts::DigitalSurface.
      ///
      /// @tparam TCellEmbedder any model of CCellEmbedder
      ///
      /// @param[out] output the output stream.
      /// @param[in] surface a smart pointer on a digital surface.
      ///
      /// @param[in] embedder the embedder for mapping surfel vertices
      /// (cells of dimension 0) to points in space.
      ///
      /// @return 'true' if the output stream is good.
      template < typename TAnyDigitalSurface,
        typename TCellEmbedder = CanonicCellEmbedder< KSpace > >
        static bool
        outputPrimalDigitalSurfaceAsObj
        ( std::ostream&              output,
          CountedPtr<TAnyDigitalSurface> surface,
          const TCellEmbedder&       embedder )
        {
          auto surfels = getSurfelRange( surface, Parameters( "Traversal", "Default" ) );
          return outputSurfelsAsObj( output, surfels, embedder );
        }

      /// Outputs an indexed digital surface, seen from the primal point
      /// of view (surfels=face), as an OBJ file (3D only). Note that
      /// faces are oriented consistently (normals toward outside).
      ///
      /// @param[out] output the output stream.
      /// @param[in] surface a smart pointer on an indexed digital surface.
      ///
      /// @return 'true' if the output stream is good.
      static bool
        outputPrimalIdxDigitalSurfaceAsObj
        ( std::ostream&              output,
          CountedPtr<IdxDigitalSurface> surface )
      {
        auto embedder = getCellEmbedder( surface );
        return outputPrimalIdxDigitalSurfaceAsObj( output, surface, embedder );
      }
    
      /// Outputs an indexed digital surface, seen from the primal point of view
      /// (surfels=face), as an OBJ file (3D only). Note that faces are
      /// oriented consistently (normals toward outside). Each vertex is
      /// mapped to a 3D point using the given cell embedder.
      ///
      /// @tparam TCellEmbedder any model of CCellEmbedder
      /// @param[out] output the output stream.
      /// @param[in] surface a smart pointer on an indexed digital surface.
      ///
      /// @param[in] embedder the embedder for mapping surfel vertices
      /// (cells of dimension 0) to points in space.
      ///
      /// @return 'true' if the output stream is good.
      template <typename TCellEmbedder = CanonicCellEmbedder< KSpace > >
        static bool
        outputPrimalIdxDigitalSurfaceAsObj
        ( std::ostream&                 output,
          CountedPtr<IdxDigitalSurface> surface,
          const TCellEmbedder&          embedder )
        {
          auto idxsurfels = getIdxSurfelRange( surface, Parameters( "Traversal", "Default" ) );
          auto  surfelmap = surface->surfels();
          SurfelRange surfels;
          for ( auto&& idx : idxsurfels )
            surfels.push_back( surfelmap[ idx ] );
          return outputSurfelsAsObj( output, surfels, embedder );
        }

      /// Outputs a digital surface, seen from the dual point of view
      /// (surfels=vertices), as an OBJ file (3D only). Note that faces are
      /// oriented consistently (normals toward outside).
      ///
      /// @tparam TDigitalSurfaceContainer either model of
      /// concepts::CDigitalSurfaceContainer.
      ///
      /// @param[out] output the output stream.
      ///
      /// @param[in] surface a smart pointer on a digital surface (a
      /// DigitalSurface or a LightDigitalSurface).
      ///
      /// @param[in] params the parameters:
      ///   - faceSubdivision ["Centroid"]: "No"|"Naive"|"Centroid" specifies how dual faces are subdivided when exported.
      ///
      /// @return 'true' if the output stream is good.
      template <typename TDigitalSurfaceContainer>
        static bool
        outputDualDigitalSurfaceAsObj
        ( std::ostream&              output,
          CountedPtr< ::DGtal::DigitalSurface< TDigitalSurfaceContainer> > surface,
          const Parameters&   params = parametersMesh() )
        {
          auto embedder = getCellEmbedder( surface );
          return outputDualDigitalSurfaceAsObj( output, surface, embedder, params );
        }
    
      /// Outputs a digital surface, seen from the dual point of view
      /// (surfels=vertices), as an OBJ file (3D only). Note that faces are
      /// oriented consistently (normals toward outside). Each vertex is
      /// mapped to a 3D point using the given cell embedder.
      ///
      /// @tparam TDigitalSurfaceContainer either model of
      /// concepts::CDigitalSurfaceContainer.
      ///
      /// @tparam TCellEmbedder any model of CCellEmbedder
      ///
      /// @param[out] output the output stream.
      ///
      /// @param[in] surface a smart pointer on a digital surface
      /// (either DigitalSurface or LightDigitalSurface).
      ///
      /// @param[in] embedder the embedder for mapping (unsigned)
      /// surfels (cells of dimension 2) to points in space.
      ///
      /// @param[in] params the parameters:
      ///   - faceSubdivision ["Centroid"]: "No"|"Naive"|"Centroid" specifies how dual faces are subdivided when exported.
      ///
      /// @return 'true' if the output stream is good.
      template < typename TDigitalSurfaceContainer,
        typename TCellEmbedder = CanonicCellEmbedder< KSpace > >
        static bool
        outputDualDigitalSurfaceAsObj
        ( std::ostream&              output,
          CountedPtr< ::DGtal::DigitalSurface< TDigitalSurfaceContainer > > surface,
          const TCellEmbedder&       embedder,
          const Parameters&   params = parametersMesh() )
        {
          typedef unsigned long Size;
          BOOST_STATIC_ASSERT (( KSpace::dimension == 3 ));
          BOOST_CONCEPT_ASSERT(( concepts::CCellEmbedder< TCellEmbedder > ));
          std::string dualFaceSubdivision = params[ "faceSubdivision" ].as<std::string>();
          const int   subdivide
          = dualFaceSubdivision == "Naive"    ? 1
          : dualFaceSubdivision == "Centroid" ? 2
          : 0;
          const KSpace& K = embedder.space();
          // Number and ouput vertices.
          std::map< Vertex, Size > vtx_numbering;
          std::map< Face,   Size > sub_numbering;
          Size n = 1;  // OBJ vertex numbering start at 1 
          for ( auto && s : *surface )
            {
              if ( ! vtx_numbering.count( s ) )
                {
                  vtx_numbering[ s ] = n++;
                  // Output vertex positions
                  RealPoint p = embedder( K.unsigns( s ) );
                  output << "v " << p[ 0 ] << " " << p[ 1 ] << " " << p[ 2 ] << std::endl;
                }
            }
          auto faces = surface->allClosedFaces();
          // Prepare centroids if necessary
          if ( subdivide == 2 )
            {
              for ( auto&& f : faces )
                {
                  auto vtcs = surface->verticesAroundFace( f );
                  Size   nv = vtcs.size();
                  if ( nv > 3 )
                    {
                      sub_numbering[ f ] = n++;
                      RealPoint p = RealPoint::zero;
                      for ( auto&& s : vtcs ) p += embedder( K.unsigns( s ) );
                      p /= nv;
                      output << "v " << p[ 0 ] << " " << p[ 1 ] << " " << p[ 2 ] << std::endl;
                    }
                }
            }
          // Outputs closed faces.
          if ( subdivide == 0 )
            { // No subdivision
              for ( auto&& f : faces )
                {
                  output << "f";
                  auto vtcs = surface->verticesAroundFace( f );
                  std::reverse( vtcs.begin(), vtcs.end() );
                  for ( auto&& s : vtcs )
                    output << " " << vtx_numbering[ s ];
                  output << std::endl;
                }
            }
          else if ( subdivide == 1 )
            { // naive subdivision
              for ( auto&& f : faces )
                {
                  auto vtcs = surface->verticesAroundFace( f );
                  Size   nv = vtcs.size();
                  for ( Size i = 1; i < nv - 1; ++i )
                    output << "f " << vtx_numbering[ vtcs[ 0 ] ]
                           << " "  << vtx_numbering[ vtcs[ i+1 ] ]
                           << " "  << vtx_numbering[ vtcs[ i ] ] << std::endl;
                }
            }
          else if ( subdivide == 2 )
            { // centroid subdivision
              for ( auto&& f : faces )
                {
                  auto vtcs = surface->verticesAroundFace( f );
                  Size   nv = vtcs.size();
                  if ( nv == 3 )
                    output << "f " << vtx_numbering[ vtcs[ 0 ] ]
                           << " "  << vtx_numbering[ vtcs[ 2 ] ]
                           << " "  << vtx_numbering[ vtcs[ 1 ] ] << std::endl;
                  else {
                    Size c = sub_numbering[ f ];
                    for ( Size i = 0; i < nv; ++i )
                      {
                        output << "f " << c
                               << " "  << vtx_numbering[ vtcs[ (i+1)%nv ] ]
                               << " "  << vtx_numbering[ vtcs[ i ] ] << std::endl;
                      }
                  }
                }
            }
          return output.good();
        }
    

      // -------------------- map I/O services ------------------------------------------
    public:
      struct CellWriter {
        void operator()( std::ostream& output, const KSpace& K, const Cell & cell )
        {
          for ( Dimension d = 0; d < KSpace::dimension; ++d )
            output << " " << K.sKCoord( cell, d );
        }
      };
      struct CellReader {
        Cell operator()( std::istream& input, const KSpace& K )
        {
          Point kp;
          for ( Dimension d = 0; d < KSpace::dimension; ++d )
            input >> kp[ d ];
          return K.uCell( kp );
        }
      };
      struct SCellWriter {
        void operator()( std::ostream& output, const KSpace& K, const SCell & scell )
        {
          CellWriter::operator()( output, K, K.unsigns( scell ) );
          output << " " << K.sSign( scell );
        }
      };
      struct SCellReader {
        SCell operator()( std::istream& input, const KSpace& K )
        {
          Point                 kp;
          typename KSpace::Sign s;
          for ( Dimension d = 0; d < KSpace::dimension; ++d )
            input >> kp[ d ];
          input >> s;
          return K.sCell( kp, s );
        }
      };

      template <typename Value>
        struct ValueWriter {
          void operator()( std::ostream& output, const Value& v )
          {
            output << " " << v;
          }
          void operator()( std::ostream& output, const std::vector<Value>& vv )
          {
            for ( auto&& v : vv ) output << " " << v;
          }
        };

      template <typename Value>
        struct ValueReader {
          bool operator()( std::istream& input, Value& value )
          {
            std::string str;
            std::getline( input, str );
            // construct a stream from the string
            std::stringstream strstr(str);
            // use stream iterators to copy the stream to the vector as whitespace separated strings
            std::istream_iterator<std::string> it(strstr);
            std::istream_iterator<std::string> end;
            std::vector<std::string> results(it, end);
            std::stringstream sstr( results[ 0 ] );
            sstr >> value;
            return ( results.size() == 1 ) && input.good();
          }
      
          bool operator()( std::istream& input, std::vector<Value>& values )
          {
            std::string str;
            std::getline( input, str );
            // construct a stream from the string
            std::stringstream strstr(str);
            // use stream iterators to copy the stream to the vector as whitespace separated strings
            std::istream_iterator<std::string> it(strstr);
            std::istream_iterator<std::string> end;
            std::vector<std::string> results(it, end);
            values.resize( results.size() );
            for ( unsigned int i = 0; i < results.size(); ++i ) {
              std::stringstream sstr( results[ i ] );
              sstr >> values[ i ];
            }
            return input.good();
          }
        };

      // Outputs in \a output a map \a anyMap: SCell -> Value given the
      // appropriate value \a writer.
      //
      // @tparam TSCellMap any model of map SCell -> Value., e.g. std::map<SCell,double>
      // @tparam TValueWriter any model of value writer, e.g. ValueWriter<double>
      //
      // @param[out] output the output stream
      // @param[in]  K the Khalimsky space where cells are defined.
      // @param[in]  anyMap the map associated a value to signed cells.
      // @param[in]  writer the writer that can write values on the ouput
      // stream, e.g. ValueWriter<double> to write double value or
      // vector<double> values.
      template <typename TSCellMap, typename TValueWriter>
        static
        bool outputSCellMapAsCSV
        ( std::ostream&       output,
          const KSpace&       K,
          const TSCellMap&     anyMap,
          const TValueWriter& writer )
      {
        SCellWriter w;
        for ( auto&& v : anyMap )
          {
            w( output, K, v.first );
            writer( output, v.second );
            output << std::endl;
          }
        return output.good();
      }
    
      // Outputs in \a output a map \a anyMap: SCell -> value given the
      // appropriate value \a writer.
      //
      // @tparam TCellMap any model of map Cell -> Value., e.g. std::map<Cell,double>
      // @tparam TValueWriter any model of value writer, e.g. ValueWriter<double>
      //
      // @param[out] output the output stream
      // @param[in]  K the Khalimsky space where cells are defined.
      // @param[in]  anyMap the map associated a value to signed cells.
      // @param[in]  writer the writer that can write values on the ouput
      // stream, e.g. ValueWriter<double> to write double value or
      // vector<double> values.
      template <typename TCellMap, typename TValueWriter>
        static
        bool outputCellMapAsCSV
        ( std::ostream&       output,
          const KSpace&       K,
          const TCellMap&      anyMap,
          const TValueWriter& writer )
      {
        CellWriter w;
        for ( auto&& v : anyMap )
          {
            w( output, K, v.first );
            writer( output, v.second );
            output << std::endl;
          }
        return output.good();
      }
    
      /// Given a space \a K and an oriented cell \a s, returns its vertices.
      /// @param K any cellular grid space.
      /// @param s any signed cell.
      /// @return the vector of the vertices of s, as unsigned cells of dimension 0.
      static
        CellRange getPrimalVertices( const KSpace& K, const SCell& s )
      {
        auto faces = K.uFaces( K.unsigns( s ) );
        CellRange primal_vtcs;
        for ( auto&& f : faces )
          {
            if ( K.uDim( f ) == 0 ) primal_vtcs.push_back( f );
          }
        return primal_vtcs;
      }
    
      /// Given a space \a K and a surfel \a s, returns its vertices in ccw or cw order.
      /// @param K any cellular grid space of dimension 3.
      /// @param s any surfel, a signed cell of dimension 2.
      /// @param ccw when 'true', the order corresponds to a ccw orientation seen from the exterior normal to the surfel, otherwise it is a cw order.
      /// @return the vector of the vertices of s, as unsigned cells of dimension 0.
      /// @note useful when exporting faces to OBJ format. 
      static
        CellRange getPrimalVertices( const KSpace& K, const Surfel& s, bool ccw )
      {
        BOOST_STATIC_ASSERT(( KSpace::dimension == 3 ));
        CellRange vtcs = getPrimalVertices( K, s );
        std::swap( vtcs[ 2 ], vtcs[ 3 ] );
        auto  orth_dir = K.sOrthDir( s );
        auto    direct = K.sDirect( s, orth_dir ) ? ccw : ! ccw;
        Vector    s0s1 = K.uCoords( vtcs[ 1 ] ) - K.uCoords( vtcs[ 0 ] );
        Vector    s0s2 = K.uCoords( vtcs[ 2 ] ) - K.uCoords( vtcs[ 0 ] );
        Vector       t = s0s1.crossProduct( s0s2 );
        if ( ( ( t[ orth_dir ] > 0.0 ) && direct )
             || ( ( t[ orth_dir ] < 0.0 ) && ! direct ) )
          std::reverse( vtcs.begin(), vtcs.end() );
        return vtcs;
      }

    
      // ----------------------- Standard services ------------------------------
    public:

      /**
       * Default constructor.
       */
      Shortcuts() = delete;

      /**
       * Destructor.
       */
      ~Shortcuts() = delete;

      /**
       * Copy constructor.
       * @param other the object to clone.
       */
      Shortcuts ( const Shortcuts & other ) = delete;

      /**
       * Move constructor.
       * @param other the object to move.
       */
      Shortcuts ( Shortcuts && other ) = delete;

      /**
       * Copy assignment operator.
       * @param other the object to copy.
       * @return a reference on 'this'.
       */
      Shortcuts & operator= ( const Shortcuts & other ) = delete;

      /**
       * Move assignment operator.
       * @param other the object to move.
       * @return a reference on 'this'.
       */
      Shortcuts & operator= ( Shortcuts && other ) = delete;

      // ----------------------- Interface --------------------------------------
    public:

      /**
       * Writes/Displays the object on an output stream.
       * @param out the output stream where the object is written.
       */
      void selfDisplay ( std::ostream & out ) const
      {
        out << "[Shortcuts]";
      }

      /**
       * Checks the validity/consistency of the object.
       * @return 'true' if the object is valid, 'false' otherwise.
       */
      bool isValid() const
      {
        return true;
      }

      // ------------------------- Protected Datas ------------------------------
    protected:

      // ------------------------- Private Datas --------------------------------
    private:

      // ------------------------- Hidden services ------------------------------
    protected:

      // ------------------------- Internals ------------------------------------
    private:

    }; // end of class Shortcuts


  /**
   * Overloads 'operator<<' for displaying objects of class 'Shortcuts'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Shortcuts' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
    std::ostream&
    operator<< ( std::ostream & out, const Shortcuts<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Shortcuts_h

#undef Shortcuts_RECURSES
#endif // else defined(Shortcuts_RECURSES)
