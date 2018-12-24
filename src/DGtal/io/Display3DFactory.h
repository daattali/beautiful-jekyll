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

#pragma once

/**
 * @file Display3DFactory.h
 * @author Martial Tola <http://liris.cnrs.fr/martial.tola/>
 * @date mercredi 21 septembre 2011
 *
 * @brief
 *
 * Header file for module Display3DFactory
 *
 * This file is part of the DGtal library.
 */

#if defined(Display3DFactory_RECURSES)
#error Recursive header files inclusion detected in Display3DFactory.h
#else // defined(Display3DFactory_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Display3DFactory_RECURSES

#if !defined Display3DFactory_h
/** Prevents repeated inclusion of headers. */
#define Display3DFactory_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions

#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"

#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/geometry/curves/StandardDSS6Computer.h"
#include "DGtal/geometry/curves/Naive3DDSSComputer.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"
#include "DGtal/kernel/sets/DigitalSetBySTLVector.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/Object.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/geometry/curves/GridCurve.h"
#include "DGtal/shapes/Mesh.h"
#include "DGtal/geometry/tools/SphericalAccumulator.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/colormaps/CColorMap.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ImageContainerBySTLMap.h"
#include "DGtal/images/ConstImageAdapter.h"
#include "DGtal/images/ImageAdapter.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/CanonicSCellEmbedder.h"
#include "DGtal/dec/VectorField.h"
#include "DGtal/dec/KForm.h"
#include "DGtal/dec/DiscreteExteriorCalculus.h"

#include "DGtal/kernel/sets/DigitalSetByAssociativeContainer.h"

//
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // struct Display3DFactory
  /**
   * Description of struct 'Display3DFactory' <p>
   * \brief Factory for GPL Display3D:
   */
  template <typename TSpace=Z3i::Space, typename TKSpace=Z3i::KSpace>
  struct Display3DFactory
  {

    ///The ball radius (the actual radius being 1/POINT_AS_BALL_RADIUS )when used to display a 3D point.
    BOOST_STATIC_CONSTANT(unsigned int, POINT_AS_BALL_RADIUS = 5);
    ///The ball resolution when used to display a point
    BOOST_STATIC_CONSTANT(unsigned int, POINT_AS_BALL_RES = 5);
    
    typedef TSpace Space;
    typedef TKSpace KSpace;
    typedef Display3DFactory<Space, KSpace> Self;
    typedef Display3D<Space, KSpace> Display;
    typedef typename Display::RealPoint RealPoint;
    typedef typename Display::RealVector RealVector;

    // DiscreteExteriorCalculus
    template <Dimension dimEmbedded, Dimension dimAmbient, typename TLinearAlgebraBackend, typename TInteger>
    static
    void
    draw(Display3D<Space, KSpace>& display, const DGtal::DiscreteExteriorCalculus<dimEmbedded, dimAmbient, TLinearAlgebraBackend, TInteger>& calculus);
    // DiscreteExteriorCalculus

    // KForm
    template <typename Calculus, DGtal::Order order, DGtal::Duality duality>
    static
    void
    draw(Display3D<Space, KSpace>& display, const DGtal::KForm<Calculus, order, duality>& kform, double cmap_min = 0, double cmap_max = 0);

    template <typename Calculus, DGtal::Order order, DGtal::Duality duality, typename ColorMap>
    static
    void
    drawWithColorMap(Display3D<Space, KSpace>& display, const DGtal::KForm<Calculus, order, duality>& kform, const ColorMap& colormap);
    // KForm

    // VectorField
    template <typename Calculus, DGtal::Duality duality>
    static
    void
    draw(Display3D<Space, KSpace>& display, const DGtal::VectorField<Calculus, duality>& vector_field, const double& scale = 0.5, const double& epsilon = 1e-5, const DGtal::Color color = DGtal::Color::Black);
    // VectorField

    // SphericalAccumulator
    /**
     * Display an spherical accumulator in 3D. Bin values are mapped
     * using a default HueShadeColorMap.
     *
     * @param display the display where to draw current display
     * @param accumulator the accumulator to display
     * @param shift translate vector for display purposes (default:
     * zero vector)
     * @param radius scale factor for the unit sphere radius (default:1)
     * @tparam TVector a vector model
     */
    template <typename TVector>
    static void draw( Display & display, const DGtal::SphericalAccumulator<TVector> & accumulator,
                      const DGtal::Z3i::RealVector &shift = DGtal::Z3i::RealVector(0,0,0),
                      const double radius=1.0);
    // SphericalAccumulator

    // Mesh
    /**
     * @brief drawAsFaces
     * @param display the display where to draw
     * @param aMesh the mesh to draw
     */
    template <typename TPoint>
    static void drawAsFaces( Display & display, const DGtal::Mesh<TPoint> & aMesh);

    /**
     * @brief draw
     * @param display the display where to draw
     * @param aMesh the mesh to draw
     */
    template <typename TPoint>
    static void draw( Display & display, const DGtal::Mesh<TPoint> & aMesh);
    // Mesh


    // StandardDSS6Computer
    /**
     * Default drawing style object.
     * @param str the name of the class
     * @param anObject the object to draw
     * @return the dyn. alloc. default style for this object.
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static DGtal::DrawableWithDisplay3D * defaultStyle( std::string str, const DGtal::StandardDSS6Computer<TIterator,TInteger,connectivity> & anObject );

    /**
     * @brief drawAsBalls
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static void drawAsBalls( Display & display, const DGtal::StandardDSS6Computer<TIterator,TInteger,connectivity> & anObject );

    /**
     * @brief drawAsBoundingBox
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static void drawAsBoundingBox( Display & display, const DGtal::StandardDSS6Computer<TIterator,TInteger,connectivity> & anObject );

    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static void draw( Display & display, const DGtal::StandardDSS6Computer<TIterator,TInteger,connectivity> & anObject );
    // StandardDSS6Computer

    // Naive3DDSSComputer
    /**
     * @brief defaultStyle
     * Default drawing style object.
     * @param str the name of the class
     * @param anObject the object to draw
     * @return the dyn. alloc. default style for this object.
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static DGtal::DrawableWithDisplay3D * defaultStyle( std::string str, const DGtal::Naive3DDSSComputer<TIterator,TInteger,connectivity> & anObject );

    /**
     * @brief drawAsBalls
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static void drawAsBalls( Display & display, const DGtal::Naive3DDSSComputer<TIterator,TInteger,connectivity> & anObject );

    /**
     * @brief drawAsBoundingBox
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static void drawAsBoundingBox( Display & display, const DGtal::Naive3DDSSComputer<TIterator,TInteger,connectivity> & anObject );
    
    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static void draw( Display & display, const DGtal::Naive3DDSSComputer<TIterator,TInteger,connectivity> & anObject );
    // Naive3DDSSComputer 
   
    
    // DigitalSetByAssociativeContainer
    /**
     * @brief defaultStyle
     * @param str the name of the class
     * @param anObject the object to draw
     * @return the dyn. alloc. default style for this object.
     */
    template<typename Domain, typename Container>
    static DGtal::DrawableWithDisplay3D * defaultStyle( std::string str, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & anObject );

    /**
     * @brief drawAsPavingTransparent
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<typename Domain, typename Container>
    static void drawAsPavingTransparent( Display & display, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & anObject );

    /**
     * @brief drawAsPaving
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<typename Domain, typename Container>
    static void drawAsPaving( Display & display, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & anObject );

    /**
     * @brief drawAsGrid
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<typename Domain, typename Container>
    static void drawAsGrid( Display & display, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & anObject );

    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<typename Domain, typename Container>
    static void draw( Display & display, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & anObject );
    // DigitalSetByAssociativeContainer

    
    // DigitalSetBySTLSet
    /**
     * @brief defaultStyle
     * @param str the name of the class
     * @param anObject the object to draw
     * @return the dyn. alloc. default style for this object.
     */
    template<typename Domain, typename Compare>
    static DGtal::DrawableWithDisplay3D * defaultStyle( std::string str, const DGtal::DigitalSetBySTLSet<Domain, Compare> & anObject );

    /**
     * @brief drawAsPavingTransparent
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<typename Domain, typename Compare>
    static void drawAsPavingTransparent( Display & display, const DGtal::DigitalSetBySTLSet<Domain, Compare> & anObject );

    /**
     * @brief drawAsPaving
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<typename Domain, typename Compare>
    static void drawAsPaving( Display & display, const DGtal::DigitalSetBySTLSet<Domain, Compare> & anObject );

    /**
     * @brief drawAsGrid
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<typename Domain, typename Compare>
    static void drawAsGrid( Display & display, const DGtal::DigitalSetBySTLSet<Domain, Compare> & anObject );

    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<typename Domain, typename Compare>
    static void draw( Display & display, const DGtal::DigitalSetBySTLSet<Domain, Compare> & anObject );
    // DigitalSetBySTLSet


    // DigitalSetBySTLVector
    /**
     * @brief Default drawing style object.
     * @param str the name of the class
     * @param anObject the object to draw
     * @return the dyn. alloc. default style for this object.
     */
    template<typename Domain>
    static DGtal::DrawableWithDisplay3D * defaultStyle( std::string str, const DGtal::DigitalSetBySTLVector<Domain> & anObject );

    /**
     * @brief drawAsPavingTransparent
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<typename Domain>
    static void drawAsPavingTransparent( Display & display, const DGtal::DigitalSetBySTLVector<Domain> & anObject );

    /**
     * @brief drawAsPaving
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<typename Domain>
    static void drawAsPaving( Display & display, const DGtal::DigitalSetBySTLVector<Domain> & anObject );

    /**
     * @brief drawAsGrid
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<typename Domain>
    static void drawAsGrid( Display & display, const DGtal::DigitalSetBySTLVector<Domain> & anObject );

    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<typename Domain>
    static void draw( Display & display, const DGtal::DigitalSetBySTLVector<Domain> & anObject );
    // DigitalSetBySTLVector


    // HyperRectDomain
    /**
     * Default drawing style object.
     * @param str the name of the class
     * @param anObject the object to draw
     * @return the dyn. alloc. default style for this object.
     */
    template <typename SpaceDom>
    static DGtal::DrawableWithDisplay3D * defaultStyle( std::string str, const DGtal::HyperRectDomain<SpaceDom> & anObject );

    /**
     * @brief drawAsBoundingBox
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename SpaceDom>
    static void drawAsBoundingBox( Display & display, const DGtal::HyperRectDomain<SpaceDom> & anObject );

    /**
     * @brief drawAsGrid
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename SpaceDom>
    static void drawAsGrid( Display & display, const DGtal::HyperRectDomain<SpaceDom> & anObject );

    /**
     * @brief drawAsPavingBalls
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename SpaceDom>
    static void drawAsPavingBalls( Display & display, const DGtal::HyperRectDomain<SpaceDom> & anObject );

    /**
     * @brief drawAsPaving
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename SpaceDom>
    static void drawAsPaving( Display & display, const DGtal::HyperRectDomain<SpaceDom> & anObject );


    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename SpaceDom>
    static void draw( Display & display, const DGtal::HyperRectDomain<SpaceDom> & anObject );


    // HyperRectDomain


    // KhalimskyCell
    /**
     * Default drawing style object.
     * @param str the name of the class
     * @param anObject the object to draw
     * @return the dyn. alloc. default style for this object.
     */
    static DGtal::DrawableWithDisplay3D * defaultStyle( std::string str, const typename KSpace::Cell & anObject );

    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    static void draw( Display & display, const typename KSpace::Cell & anObject );

    /**
     * Draw K-cell with normal vector
     * 
     * We use the normal vector to orient the quad properly.  As a
     * consequence, the angle between the normal vector and the
     * canonical normal vector attached to the oriented quad is less
     * than pi/2.
     *
     * @param display the display where to draw
     * @param anObject the object to draw
     * @param aNormal a unitary normal vector
     * @param enableDoubleFace if true, two quad (with opposite normal
     * vector) will be drawn.
     */
    static void drawUnorientedSurfelWithNormal( Display & display, const typename KSpace::Cell & anObject,
                                                const RealVector & aNormal,
                                                const bool enableDoubleFace = false);
    // KhalimskyCell

    // SignedKhalimskyCell
    /**
     * Default drawing style object.
     * @param str the name of the class
     * @param anObject the object to draw
     * @return the dyn. alloc. default style for this object.
     */
    static DGtal::DrawableWithDisplay3D * defaultStyle( std::string str, const typename KSpace::SCell & anObject );

    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    static void draw( Display & display, const typename KSpace::SCell & anObject );

    /**
     * Draw K-signed cell with normal vector
     * We use the surfel orientation to create the properly oriented
     * Quad.
     *  
     * @param display the display where to draw
     * @param aSignedCell the signed cell to draw
     * @param aNormal a unitary normal vector
     * @param enableDoubleFace if true, two quad (with opposite normal
     * vector) will be drawn.
     */
    static void drawOrientedSurfelWithNormal( Display & display, 
                                              const typename KSpace::SCell & aSignedCell,
                                              const RealVector & aNormal,
                                              const bool enableDoubleFace = false);
    // SignedKhalimskyCell

    // Object
    /**
     * Default drawing style object.
     * @param str the name of the class
     * @param anObject the object to draw
     * @return the dyn. alloc. default style for this object.
     */
    template <typename TDigitalTopology, typename TDigitalSet>
    static DGtal::DrawableWithDisplay3D * defaultStyle( std::string str, const DGtal::Object<TDigitalTopology, TDigitalSet> & anObject );

    /**
     * @brief drawWithAdjacencies
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename TDigitalTopology, typename TDigitalSet>
    static void drawWithAdjacencies( Display & display, const DGtal::Object<TDigitalTopology, TDigitalSet> & anObject );

    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename TDigitalTopology, typename TDigitalSet>
    static void draw( Display & display, const DGtal::Object<TDigitalTopology, TDigitalSet> & anObject );
    // Object


    // PointVector
    /**
     * Default drawing style object.
     * @param str the name of the class
     * @param anObject the object to draw
     * @return the dyn. alloc. default style for this object.
     */
    template<Dimension dim, typename TComponent, typename TContainer>
    static DGtal::DrawableWithDisplay3D * defaultStyle( std::string str, const DGtal::PointVector<dim, TComponent, TContainer> & anObject );

    /**
     * @brief drawAsGrid
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<Dimension dim, typename TComponent, typename TContainer>
    static void drawAsGrid( Display & display, const DGtal::PointVector<dim, TComponent, TContainer> & anObject );

    /**
     * @brief drawAsPaving
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<Dimension dim, typename TComponent, typename TContainer>
    static void drawAsPaving( Display & display, const DGtal::PointVector<dim, TComponent, TContainer> & anObject );

    /**
     * @brief drawAsPavingWired
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<Dimension dim, typename TComponent, typename TContainer>
    static void drawAsPavingWired( Display & display, const DGtal::PointVector<dim, TComponent, TContainer> & anObject );

    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<Dimension dim, typename TComponent, typename TContainer>
    static void draw( Display & display, const DGtal::PointVector<dim, TComponent, TContainer> & anObject );

    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template<Dimension dim, typename TComponent1, typename TComponent2, typename TContainer1, typename TContainer2>
    static void draw( Display & display, const DGtal::PointVector<dim, TComponent1, TContainer1> & , const DGtal::PointVector<dim, TComponent2, TContainer2> & anObject );
    // PointVector

    // GridCurve
    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    static void draw( Display & display, const DGtal::GridCurve<KSpace> & anObject );
    // GridCurve

    // SCellsRange
    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template < typename TIterator, typename TSCell>
    static void draw( Display & display,
                      const DGtal::ConstRangeAdapter<TIterator, DGtal::functors::Identity, TSCell> & anObject );
    // SCellsRange

    // PointsRange
    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename TIterator>
    static void draw( Display & display,
                      const DGtal::ConstRangeAdapter<TIterator, DGtal::functors::SCellToPoint<KSpace>, typename TKSpace::Point> & anObject );
    // PointsRange

    // MidPointsRange
    template <typename TIterator>
    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    static void draw( Display & display,
                      const DGtal::ConstRangeAdapter<TIterator, CanonicSCellEmbedder<KSpace>,
                      typename TKSpace::Space::RealPoint> & anObject );
    // MidPointsRange

    // ArrowsRange
    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename TIterator>
    static void draw( Display & display,
                      const DGtal::ConstRangeAdapter<TIterator, DGtal::functors::SCellToArrow<KSpace>,
                      std::pair<typename TKSpace::Point, typename TKSpace::Vector > > & anObject );
    // ArrowsRange

    // InnerPointsRange
    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename TIterator>
    static void draw( Display & display,
                      const DGtal::ConstRangeAdapter<TIterator, DGtal::functors::SCellToInnerPoint<KSpace>, typename TKSpace::Point> & anObject );
    // InnerPointsRange

    // OuterPointsRange
    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename TIterator>
    static void draw( Display & display,
                      const DGtal::ConstRangeAdapter<TIterator, DGtal::functors::SCellToOuterPoint<KSpace>, typename TKSpace::Point> & anObject );
    // OuterPointsRange

    // IncidentPointsRange
    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    template <typename TIterator>
    static void draw( Display & display,
                      const DGtal::ConstRangeAdapter<TIterator, DGtal::functors::SCellToIncidentPoints<KSpace>,
                      std::pair<typename KSpace::Point, typename KSpace::Point > > & anObject );
    // IncidentPointsRange

    /**
     *  draw.This function will create new
     * sublists for Display3D models.
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    static void
    draw( Display & display, const DGtal::SetMode3D & anObject );

    /**
     * Draw for CustomStyle class. This function will create new
     * sublists for Display3D models.
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    static void
    draw( Display & display, const DGtal::CustomStyle3D & anObject );

    /**
     * brief draw.This function will create new
     * sublists for Display3D models.
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    static void
    draw( Display & display, const DGtal::CustomColors3D & anObject );

    /**
     * @brief draw
     * @param display the display where to draw
     * @param anObject the object to draw
     */
    static void
    draw( Display & display, const DGtal::ClippingPlane & anObject );


    /**
     * Draw a surfel
     * @param display the display where to draw
     * @param aTransformedPrism a transformed surfel prism
     */
    static void
    draw( Display & display, const DGtal::TransformedPrism & aTransformedPrism);

    /**
     * Set the "OpenGL name" of future graphical commands.
     * @param display the display where to draw
     * @param aName3d an object storing the "OpenGL" name.
     */
    static void 
    draw( Display & display, const DGtal::SetName3D& aName3d );

    /**
     * Set the callback function when selecting an object (e.g. shift
     * + left click in QGLViewer).
     *
     * @param display the display where to draw
     * @param aFct an object storing the callback function.
     */
    static void 
    draw( Display & display, const DGtal::SetSelectCallback3D& aFct );
    
  }; // end of struct Display3DFactory

} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods

#include "DGtal/io/Display3DFactory.ih"

// //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Display3DFactory_h

#undef Display3DFactory_RECURSES
#endif // else defined(Display3DFactory_RECURSES)
