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
 * @file Viewer3DFactory.h
 * @author Aline Martin <aline.martin@insa-lyon.fr>
 * @date mardi 2 juillet 2013
 *
 * @brief
 *
 * Header file for module Viewer3DFactory
 *
 * This file is part of the DGtal library.
 */

#if defined(Viewer3DFactory_RECURSES)
#error Recursive header files inclusion detected in Viewer3DFactory.h
#else // defined(Viewer3DFactory_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Viewer3DFactory_RECURSES

#if !defined Viewer3DFactory_h
/** Prevents repeated inclusion of headers. */
#define Viewer3DFactory_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions

#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"

#include "DGtal/io/Display3DFactory.h"
#include "DGtal/io/viewers/DrawWithViewer3DModifier.h"
#include "DGtal/geometry/curves/StandardDSS6Computer.h"
#include "DGtal/geometry/curves/Naive3DDSSComputer.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"
#include "DGtal/kernel/sets/DigitalSetBySTLVector.h"
#include "DGtal/kernel/sets/DigitalSetByAssociativeContainer.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/Object.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/geometry/curves/GridCurve.h"
#include "DGtal/shapes/Mesh.h"
#include "DGtal/geometry/tools/SphericalAccumulator.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/colormaps/CColorMap.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ImageContainerBySTLMap.h"
#include "DGtal/images/ConstImageAdapter.h"
#include "DGtal/images/ImageAdapter.h"
#include "DGtal/helpers/StdDefs.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // struct Viewer3DFactory
  /**
   * Description of struct 'Viewer3DFactory' <p>
   * \brief Factory for GPL Viewer3D:
   */
  template <typename TSpace = Z3i::Space, typename TKSpace = Z3i::KSpace>
  struct Viewer3DFactory : public Display3DFactory<TSpace,TKSpace>
  {
    ///Space type
    typedef TSpace Space;

    ///KSpace type
    typedef TKSpace KSpace;

    /**
     * Set the camera position on the board.
     * @param board the board where to draw
     * @param aThing the camera position to set
     */
    static void
    draw( Viewer3D<Space,KSpace> & board, const DGtal::CameraPosition & aThing );

    /**
     * Set the camera direction on the board.
     * @param board the board where to draw
     * @param aThing the camera direction to set
     */
    static void
    draw( Viewer3D<Space,KSpace> & board, const DGtal::CameraDirection & aThing );

    /**
     * Set the camera up vector on the board.
     * @param board the board where to draw
     * @param aThing the camera up vector to set
     */
    static void
    draw( Viewer3D<Space,KSpace> & board, const DGtal::CameraUpVector & aThing );

    /**
     * Set the near and far distance on the board.
     * @param board the board where to draw
     * @param aThing the near and far distance
     */
    static void
    draw( Viewer3D<Space,KSpace> & board, const DGtal::CameraZNearFar & aThing );

    //---------------------------------------------------
    // heritage
    // SphericalAccumulator
    /**
     * Display an spherical accumulator in 3D. Bin values are mapped
     * using a default HueShadeColorMap.
     *
     * @param viewer the viewer where to draw current viewer
     * @param accumulator the accumulator to viewer
     * @param shift translate vector for viewer purposes (default:
     * zero vector)
     * @param radius scale factor for the unit sphere radius (default:1)
     * @tparam TVector a vector model
     */
    template <typename TVector>
    static void draw( Viewer3D<Space,KSpace> & viewer, const DGtal::SphericalAccumulator<TVector> & accumulator,
                      const DGtal::Z3i::RealVector & shift = Z3i::RealVector(0,0,0),
                      const double radius=1.0);
    // SphericalAccumulator

    // Mesh
    /**
     * Method to draw Mesh as faces.
     * @param viewer the viewer where to draw
     * @param aMesh the mesh to draw
     */
    template <typename TPoint>
    static void drawAsFaces( Viewer3D<Space,KSpace> & viewer, const DGtal::Mesh<TPoint> & aMesh );

    /**
     * Method to draw Mesh.
     * @param viewer the viewer where to draw
     * @param aMesh the mesh to draw
     */
    template <typename TPoint>
    static void draw( Viewer3D<Space,KSpace> & viewer, const DGtal::Mesh<TPoint> & aMesh );
    // Mesh



    // StandardDSS6Computer
    /**
     * Default drawing style object.
     * @param str the name of the class
     * @param arithm the arithm to draw
     * @return the dyn. alloc. default style for this object.
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static DGtal::DrawableWithViewer3D * defaultStyle( std::string str, const DGtal::StandardDSS6Computer<TIterator,TInteger,connectivity> & arithm );

    /**
     * Method to draw StandardDSS6Computer as Balls.
     * @param viewer the viewer where to draw
     * @param arithm the arithm to draw
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static void drawAsBalls( Viewer3D<Space,KSpace> & viewer, const DGtal::StandardDSS6Computer<TIterator,TInteger,connectivity> & arithm );

    /**
     * Method to draw StandardDSS6Computer as BoundingBox.
     * @param viewer the viewer where to draw
     * @param arithm the arithm to draw
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static void drawAsBoundingBox( Viewer3D<Space,KSpace> & viewer, const DGtal::StandardDSS6Computer<TIterator,TInteger,connectivity> & arithm );

    /**
     * Method to draw StandardDSS6Computer.
     * @param viewer the viewer where to draw
     * @param arithm the arithm to draw
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static void draw( Viewer3D<Space,KSpace> & viewer, const DGtal::StandardDSS6Computer<TIterator,TInteger,connectivity> & arithm );
    // StandardDSS6Computer


    // naive3DDSSComputer
    /**
     * Default drawing style object.
     * @param str the name of the class
     * @param arithm the arithm to draw
     * @return the dyn. alloc. default style for this object.
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static DGtal::DrawableWithViewer3D * defaultStyle( std::string str, const DGtal::Naive3DDSSComputer<TIterator,TInteger,connectivity> & arithm );

    /**
     * Method to draw Naive3DDSSComputer as Balls.
     * @param viewer the viewer where to draw
     * @param arithm the arithm to draw
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static void drawAsBalls( Viewer3D<Space,KSpace> & viewer, const DGtal::Naive3DDSSComputer<TIterator,TInteger,connectivity> & arithm );

    /**
     * Method to draw Naive3DDSSComputer as BoundingBox.
     * @param viewer the viewer where to draw
     * @param arithm the arithm to draw
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static void drawAsBoundingBox( Viewer3D<Space,KSpace> & viewer, const DGtal::Naive3DDSSComputer<TIterator,TInteger,connectivity> & arithm );

    /**
     * Method to draw Naive3DDSSComputer.
     * @param viewer the viewer where to draw
     * @param arithm the arithm to draw
     */
    template <typename TIterator, typename TInteger, int connectivity>
    static void draw( Viewer3D<Space,KSpace> & viewer, const DGtal::Naive3DDSSComputer<TIterator,TInteger,connectivity> & arithm );
    // Naive3DDSSComputer


    // DigitalSetBySTLSet
    /**
     * Return the default drawing style object.
     * @param str the name of the class
     * @param aSet the set to draw
     * @return the dyn. alloc. default style for this object.
     */
    template<typename Domain, typename Compare>
    static DGtal::DrawableWithViewer3D * defaultStyle( std::string str, const DGtal::DigitalSetBySTLSet<Domain, Compare> & aSet );

    /**
     * Method to draw DigitalSetBySTLSet as Paving Transparent.
     * @param viewer the viewer where to draw
     * @param aSet the set to draw
     */
    template<typename Domain, typename Compare>
    static void drawAsPavingTransparent( Viewer3D<Space,KSpace> & viewer, const DGtal::DigitalSetBySTLSet<Domain, Compare> & aSet );

    /**
     * Method to draw DigitalSetBySTLSet as Paving.
     * @param viewer the viewer where to draw
     * @param aSet the set to draw
     */
    template<typename Domain, typename Compare>
    static void drawAsPaving( Viewer3D<Space,KSpace> & viewer, const DGtal::DigitalSetBySTLSet<Domain, Compare> & aSet );

    /**
     * Method to draw DigitalSetBySTLSet as Grid.
     * @param viewer the viewer where to draw
     * @param aSet the set to draw
     */
    template<typename Domain, typename Compare>
    static void drawAsGrid( Viewer3D<Space,KSpace> & viewer, const DGtal::DigitalSetBySTLSet<Domain, Compare> & aSet );

    /**
     * Method to draw DigitalSetBySTLSet.
     * @param viewer the viewer where to draw
     * @param aSet the set to draw
     */
    template<typename Domain, typename Compare>
    static void draw( Viewer3D<Space,KSpace> & viewer, const DGtal::DigitalSetBySTLSet<Domain, Compare> & aSet );
    // DigitalSetBySTLSet

    // DigitalSetByAssociativeContainer
    /**
     * Return the default drawing style object.
     * @param str the name of the class
     * @param aSet the set to draw
     * @return the dyn. alloc. default style for this object.
     */
    template<typename Domain, typename Container>
    static DGtal::DrawableWithViewer3D * defaultStyle( std::string str, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & aSet );

    /**
     * Method to draw DigitalSetByAssociativeContainer as Paving Transparent.
     * @param viewer the viewer where to draw
     * @param aSet the set to draw
     */
    template<typename Domain, typename Container>
    static void drawAsPavingTransparent( Viewer3D<Space,KSpace> & viewer, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & aSet );

    /**
     * Method to draw DigitalSetByAssociativeContainer as Paving.
     * @param viewer the viewer where to draw
     * @param aSet the set to draw
     */
    template<typename Domain, typename Container>
    static void drawAsPaving( Viewer3D<Space,KSpace> & viewer, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & aSet );

    /**
     * Method to draw DigitalSetByAssociativeContainer as Grid.
     * @param viewer the viewer where to draw
     * @param aSet the set to draw
     */
    template<typename Domain, typename Container>
    static void drawAsGrid( Viewer3D<Space,KSpace> & viewer, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & aSet );

    /**
     * Method to draw DigitalSetByAssociativeContainer.
     * @param viewer the viewer where to draw
     * @param aSet the set to draw
     */
    template<typename Domain, typename Container>
    static void draw( Viewer3D<Space,KSpace> & viewer, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & aSet );
    // DigitalSetByAssociativeContainer


    // DigitalSetBySTLVector
    /**
     * Default drawing style object.
     * @param str the name of the class
     * @param aSet the set to draw
     * @return the dyn. alloc. default style for this object.
     */
    template<typename Domain>
    static DGtal::DrawableWithViewer3D * defaultStyle( std::string str, const DGtal::DigitalSetBySTLVector<Domain> & aSet );

    /**
     * Method to draw DigitalSetBySTLVector as Paving Transparent.
     * @param viewer the viewer where to draw
     * @param aSet the set to draw
     */
    template<typename Domain>
    static void drawAsPavingTransparent( Viewer3D<Space,KSpace> & viewer, const DGtal::DigitalSetBySTLVector<Domain> & aSet );

    /**
     * Method to draw DigitalSetBySTLVector as Paving.
     * @param viewer the viewer where to draw
     * @param aSet the set to draw
     */
    template<typename Domain>
    static void drawAsPaving( Viewer3D<Space,KSpace> & viewer, const DGtal::DigitalSetBySTLVector<Domain> & aSet );

    /**
     * Method to draw DigitalSetBySTLVector as Grid.
     * @param viewer the viewer where to draw
     * @param aSet the set to draw
     */
    template<typename Domain>
    static void drawAsGrid( Viewer3D<Space,KSpace> & viewer, const DGtal::DigitalSetBySTLVector<Domain> & aSet );

    /**
     * Method to draw DigitalSetBySTLVector.
     * @param viewer the viewer where to draw
     * @param aSet the set to draw
     */
    template<typename Domain>
    static void draw( Viewer3D<Space,KSpace> & viewer, const DGtal::DigitalSetBySTLVector<Domain> & aSet );
    // DigitalSetBySTLVector


    // HyperRectDomain
    /**
     * Default drawing style object.
     * @param str the name of the class
     * @param aDomain the domain to draw
     * @return the dyn. alloc. default style for this object.
     */
    template <typename SpaceDom>
    static DGtal::DrawableWithViewer3D * defaultStyle( std::string str, const DGtal::HyperRectDomain<SpaceDom> & aDomain );

    /**
     * Method to draw HyperRectDomain as BoundingBox.
     * @param viewer the viewer where to draw
     * @param aDomain the domain to draw
     */
    template <typename SpaceDom>
    static void drawAsBoundingBox( Viewer3D<Space,KSpace> & viewer, const DGtal::HyperRectDomain<SpaceDom> & aDomain );

    /**
     * Method to draw HyperRectDomain as grid.
     * @param viewer the viewer where to draw
     * @param aDomain the domain to draw
     */
    template <typename SpaceDom>
    static void drawAsGrid( Viewer3D<Space,KSpace> & viewer, const DGtal::HyperRectDomain<SpaceDom> & aDomain );

    /**
     * Method to draw HyperRectDomain with Paving Balls.
     * @param viewer the viewer where to draw
     * @param aDomain the domain to draw
     */
    template <typename SpaceDom>
    static void drawAsPavingBalls( Viewer3D<Space,KSpace> & viewer, const DGtal::HyperRectDomain<SpaceDom> & aDomain );

    /**
     * Method to draw HyperRectDomain with Paving mode.
     * @param viewer the viewer where to draw
     * @param aDomain the domain to draw
     */
    template <typename SpaceDom>
    static void drawAsPaving( Viewer3D<Space,KSpace> & viewer, const DGtal::HyperRectDomain<SpaceDom> & aDomain );

    /**
     * Method to draw HyperRectDomain.
     * @param viewer the viewer where to draw
     * @param aDomain the domain to draw
     */
    template <typename SpaceDom>
    static void draw( Viewer3D<Space,KSpace> & viewer, const DGtal::HyperRectDomain<SpaceDom> & aDomain );
    // HyperRectDomain


    // KhalimskyCell
    /**
     * Default drawing style object.
     * @param str the name of the class
     * @param aCell the cell to draw
     * @return the dyn. alloc. default style for this object.
     */
    static DGtal::DrawableWithViewer3D * defaultStyle( std::string str, const typename KSpace::Cell & aCell );

    /**
     * Method to draw KhalimskyCell.
     * @param viewer the viewer where to draw
     * @param aCell the cell to draw
     */
    static void draw( Viewer3D<Space,KSpace> & viewer, const typename KSpace::Cell & aCell );
    // KhalimskyCell


    // Object
    /**
     * Method to return the defaultStyle of an object.    
     * @param str the name of the class
     * @param anObject the object to draw
     * @return a pointer to the default object style
     */
    template <typename TDigitalTopology, typename TDigitalSet>
    static DGtal::DrawableWithViewer3D * defaultStyle( std::string str, const DGtal::Object<TDigitalTopology, TDigitalSet> & anObject );

    /**
     * Method to draw Object with adjacency mode.
     * @param viewer the viewer where to draw
     * @param anObject the object to draw
     */
    template <typename TDigitalTopology, typename TDigitalSet>
    static void drawWithAdjacencies( Viewer3D<Space,KSpace> & viewer, const DGtal::Object<TDigitalTopology, TDigitalSet> & anObject );

    /**
     * Method to draw Object.
     * @param viewer the viewer where to draw
     * @param anObject the object to draw
     */
    template <typename TDigitalTopology, typename TDigitalSet>
    static void draw( Viewer3D<Space,KSpace> & viewer, const DGtal::Object<TDigitalTopology, TDigitalSet> & anObject );
    // Object


    // PointVector
    /**
     * Default drawing style object.
     * @param str the name of the class
     * @param aPoint the point to draw
     * @return the dyn. alloc. default style for this object.
     */
    template<Dimension dim, typename TComponent, typename TContainer>
    static DGtal::DrawableWithViewer3D * defaultStyle( std::string str, const DGtal::PointVector<dim, TComponent, TContainer> & aPoint );

    /**
     * Method to draw PointVector as Grid.
     * @param viewer the viewer where to draw
     * @param aPoint the point to draw
     */
    template<Dimension dim, typename TComponent, typename TContainer>
    static void drawAsGrid( Viewer3D<Space,KSpace> & viewer, const DGtal::PointVector<dim, TComponent, TContainer> & aPoint );

    /**
     * Method to draw PointVector as Paving.
     * @param viewer the viewer where to draw
     * @param aPoint the point to draw
     */
    template<Dimension dim, typename TComponent, typename TContainer>
    static void drawAsPaving( Viewer3D<Space,KSpace> & viewer, const DGtal::PointVector<dim, TComponent, TContainer> & aPoint );

    /**
     * Method to draw PointVector as Paving Wired.
     * @param viewer the viewer where to draw
     * @param aPoint the point to draw
     */
    template<Dimension dim, typename TComponent, typename TContainer>
    static void drawAsPavingWired( Viewer3D<Space,KSpace> & viewer, const DGtal::PointVector<dim, TComponent, TContainer> & aPoint );

    /**
     * Method to draw PointVector.
     * @param viewer the viewer where to draw
     * @param aPoint the point to draw
     */
    template<Dimension dim, typename TComponent, typename TContainer>
    static void draw( Viewer3D<Space,KSpace> & viewer, const DGtal::PointVector<dim, TComponent, TContainer> & aPoint );

    /**
     * Method to draw PointVector.
     * @param viewer the viewer where to draw
     * @param aPoint the point to draw
     * @param aPoint2 the point to draw
     */
    template<Dimension dim, typename TComponent1, typename TComponent2, typename TContainer1, typename TContainer2>
    static void draw( Viewer3D<Space,KSpace> & viewer, const DGtal::PointVector<dim, TComponent1, TContainer1> & aPoint, const DGtal::PointVector<dim, TComponent2, TContainer2> & aPoint2 );
    // PointVector


    // SignedKhalimskyCell
    /**
     * Default drawing style object.
     * @param str the name of the class
     * @param aSCell the signed cell to draw
     * @return the dyn. alloc. default style for this object.
     */
    static DGtal::DrawableWithViewer3D * defaultStyle( std::string str, const typename KSpace::SCell & aSCell );

    /**
     * Method to draw SignedKhalimskyCell.
     * @param viewer the viewer where to draw
     * @param aSCell the signed cell to draw
     */
    static void draw( Viewer3D<Space,KSpace> & viewer, const typename KSpace::SCell & aSCell );
    // SignedKhalimskyCell

    // GridCurve
    /**
     * Method to draw GridCurve.
     * @param viewer the viewer where to draw
     * @param aGrid the grid to draw
     */
    static void draw( Viewer3D<Space,KSpace> & viewer, const DGtal::GridCurve<KSpace> & aGrid );
    // GridCurve

    // SCellsRange
    /**
     * Method to draw SCellsRange.
     * @param viewer the viewer where to draw
     * @param aRangeAdapter the range adapter to draw
     */
    template < typename TIterator, typename TSCell>
    static void draw( DGtal::Viewer3D<Space, KSpace> & viewer,
                      const DGtal::ConstRangeAdapter<TIterator, DGtal::functors::Identity, TSCell> & aRangeAdapter );
    // SCellsRange

    // PointsRange
    /**
     * Method to draw PointsRange.
     * @param viewer the viewer where to draw
     * @param aRangeAdapter the range adapter to draw
     */
    template <typename TIterator>
    static void draw( Viewer3D<Space,KSpace> & viewer,
                      const DGtal::ConstRangeAdapter<TIterator, functors::SCellToPoint<TKSpace>, typename TKSpace::Point> & aRangeAdapter );
    // PointsRange

    // MidPointsRange
    /**
     * Method to draw MidPointsRange.
     * @param viewer the viewer where to draw
     * @param aRangeAdapter the range adapter to draw
     */
    template <typename TIterator>
    static void draw( Viewer3D<Space,KSpace> & viewer,
                      const DGtal::ConstRangeAdapter<TIterator, CanonicSCellEmbedder<TKSpace>, typename TKSpace::Space::RealPoint> & aRangeAdapter );
    // MidPointsRange

    // ArrowsRange
    /**
     * Method to draw ArrowsRange.
     * @param viewer the viewer where to draw
     * @param aRangeAdapter the range adapter to draw
     */
    template <typename TIterator>
    static void draw( Viewer3D<Space, KSpace> & viewer,
                      const DGtal::ConstRangeAdapter<TIterator, functors::SCellToArrow<TKSpace>, std::pair<typename TKSpace::Point, typename TKSpace::Vector > > & aRangeAdapter );
    // ArrowsRange

    // InnerPointsRange
    /**
     * Method to draw InnerPointsRange.
     * @param viewer the viewer where to draw
     * @param aRangeAdapter the range adapter to draw
     */
    template <typename TIterator>
    static void draw( Viewer3D<Space,KSpace> & viewer,
                      const DGtal::ConstRangeAdapter<TIterator, functors::SCellToInnerPoint<TKSpace>, typename TKSpace::Point> & aRangeAdapter );
    // InnerPointsRange

    // OuterPointsRange
    /**
     * Method to draw OuterPointsRange.
     * @param viewer the viewer where to draw
     * @param aRangeAdapter the range adapter to draw
     */
    template <typename TIterator>
    static void draw( Viewer3D<Space,KSpace> & viewer,
                      const DGtal::ConstRangeAdapter<TIterator, functors::SCellToOuterPoint<TKSpace>, typename TKSpace::Point> & aRangeAdapter );
    // OuterPointsRange

    // IncidentPointsRange
    /**
     * Method to draw IncidentPointsRange.
     * @param viewer the viewer where to draw
     * @param aRangeAdapter the range adapter to draw
     */
    template <typename TIterator>
    static void draw( Viewer3D<Space,KSpace> & viewer,
                      const DGtal::ConstRangeAdapter<TIterator, functors::SCellToIncidentPoints<TKSpace>,std::pair<typename TKSpace::Point, typename TKSpace::Point > > & aRangeAdapter );
    // IncidentPointsRange


    // ImageContainerBySTLVector (2D)
    /**
     * Method to draw an 2D Image (ImageContainerBySTLVector).
     * @param viewer the viewer where to draw
     * @param anImage the image to draw
     */
    template <typename TValue>
    static void draw( Viewer3D<Space,KSpace> & viewer, const ImageContainerBySTLVector<DGtal::Z2i::Domain, TValue> & anImage );
    // ImageContainerBySTLVector (2D)

    // ImageContainerBySTLMap (2D)
    /**
     * Method to draw an 2D Image (ImageContainerBySTLMap).
     * @param viewer the viewer where to draw
     * @param anImage the image to draw
     */
    template <typename TValue>
    static void draw( Viewer3D<Space, KSpace> & viewer, const ImageContainerBySTLMap<DGtal::Z2i::Domain, TValue> & anImage );
    // ImageContainerBySTLMap (2D)

    // ConstImageAdapter (2D)
    /**
     * Method to draw an 2D Image (ConstImageAdapter).
     * @param viewer the viewer where to draw
     * @param anImage the image to draw
     */
    template <typename TImageContainer, typename TFunctorD, typename TNewValue, typename TFunctorValue>
    static void draw( Viewer3D<Space,KSpace> & viewer, const ConstImageAdapter<TImageContainer, DGtal::Z2i::Domain, TFunctorD, TNewValue, TFunctorValue> & anImage );
    // ConstImageAdapter (2D)

    // ImageAdapter (2D)
    /**
     * Method to draw an 2D Image (ImageAdapter).
     * @param viewer the viewer where to draw
     * @param anImage the image to draw
     */
    template <typename TImageContainer, typename TFunctorD, typename TNewValue, typename TFunctorValue, typename TFunctorValueVm1>
    static void draw( Viewer3D<Space,KSpace> & viewer, const ImageAdapter<TImageContainer, DGtal::Z2i::Domain, TFunctorD,
                      TNewValue, TFunctorValue, TFunctorValueVm1> & anImage );
    // ImageAdapter (2D)


    // ImageContainerBySTLVector (3D)
    /**
     * Method to draw an 3D Image (ImageContainerBySTLVector).
     * @param viewer the viewer where to draw
     * @param anImage the image to draw
     */
    template <typename TValue>
    static void draw( Viewer3D<Space,KSpace> & viewer, const ImageContainerBySTLVector<DGtal::Z3i::Domain, TValue> & anImage );
    // ImageContainerBySTLVector (3D)


    // ImageContainerBySTLMap (3D)
    /**
     * Method to draw an 3D Image (ImageContainerBySTLMap).
     * @param viewer the viewer where to draw
     * @param anImage the image to draw
     */
    template <typename TValue>
    static void draw( Viewer3D<Space,KSpace> & viewer, const ImageContainerBySTLMap<DGtal::Z3i::Domain, TValue> & anImage );
    // ImageContainerBySTLMap (3D)

    // ConstImageAdapter (3D)
    /**
     * Method to draw an 3D Image (ConstImageAdapter).
     * @param viewer the viewer where to draw
     * @param anImage the image to draw
     */
    template <typename TImageContainer, typename TFunctorD, typename TNewValue, typename TFunctorValue>
    static void draw( Viewer3D<Space,KSpace> & viewer, const ConstImageAdapter<TImageContainer, DGtal::Z3i::Domain, TFunctorD,
                      TNewValue, TFunctorValue> & anImage );
    // ConstImageAdapter (3D)

    // ImageAdapter (3D)
    /**
     * Method to draw an 3D Image (ImageAdapter).
     * @param viewer the viewer where to draw
     * @param anImage the image to draw
     */
    template <typename TImageContainer, typename TFunctorD, typename TNewValue, typename TFunctorValue, typename TFunctorValueVm1>
    static void draw( Viewer3D<Space,KSpace> & viewer, const ImageAdapter<TImageContainer, DGtal::Z3i::Domain, TFunctorD,
                      TNewValue, TFunctorValue, TFunctorValueVm1> & anImage );
    // ImageAdapter (3D)


    /**
     * Method to draw an 3D Image.
     * @param viewer the viewer where to draw
     * @param anImage the image to draw
     * @param aFunctor the functor to draw
     * @param aTextureMode the mode of the texture to set
     */
    template < typename TImageType2D, typename TFunctor>
    static void
    drawImage2D( Viewer3D<Space,KSpace> & viewer, const TImageType2D & anImage, const TFunctor & aFunctor,
                 typename Viewer3D<Space,KSpace>::TextureMode aTextureMode );

    /**
     * Method to draw an 2D Image.
     * @param viewer the viewer where to draw
     * @param anImage3D the image to draw
     * @param aFunctor the functor to draw
     * @param aTextureMode the mode of the texture to set
     */
    template < typename TImageType3D, typename TFunctor>
    static void
    drawImage3D( Viewer3D<Space,KSpace> & viewer, const TImageType3D & anImage3D, const TFunctor & aFunctor,
                 typename Viewer3D<Space,KSpace>::TextureMode aTextureMode );

    /**
     * Method to set a custom mode for 3d object
     * @param viewer the viewer where to draw
     * @param aMode the mode to set
     */
    static void
    draw( Viewer3D<Space,KSpace> & viewer, const DGtal::SetMode3D & aMode);

    /**
     * Method to set a custom style for 3d object
     * @param viewer the viewer where to draw
     * @param aStyle the style to set
     */
    static void
    draw( Viewer3D<Space,KSpace> & viewer, const DGtal::CustomStyle3D & aStyle);

    /**
     * Method to set a custom color for 3d object
     * @param viewer the viewer where to draw
     * @param aColor the color to set
     */
    static void
    draw( Viewer3D<Space,KSpace> & viewer, const DGtal::CustomColors3D & aColor);

    /**
     * Method to add an clipping plane
     * @param viewer the viewer where to draw
     * @param aClipping the clipping plane to draw
     */
    static void
    draw( Viewer3D<Space,KSpace> & viewer, const DGtal::ClippingPlane & aClipping);


    // AddTextureImage3DWithFunctor
    /**
     * Method to draw an TextureImage3D.
     * @param viewer the viewer where to draw
     * @param aFunctor the functor to draw
     */
    template<typename TImageType, typename TFunctor>
    static void
    draw( Viewer3D<Space,KSpace> & viewer, const DGtal::AddTextureImage3DWithFunctor<TImageType, TFunctor, Space, KSpace> & aFunctor );
    // AddTextureImage3DWithFunctor

    // AddTextureImage2DWithFunctor
    /**
     * Method to draw an TextureImage2D.
     * @param viewer the viewer where to draw
     * @param aFunctor the functor to draw
     */
    template<typename TImageType, typename TFunctor>
    static void
    draw( Viewer3D<Space,KSpace> & viewer, const DGtal::AddTextureImage2DWithFunctor<TImageType, TFunctor, Space, KSpace> & aFunctor );
    // AddTextureImage2DWithFunctor

    /**
     * Method to update the position of an image.
     * @param viewer the viewer where to draw
     * @param anUpdate the update to set
     */
    static void
    draw( Viewer3D<Space,KSpace> & viewer, const DGtal::UpdateImagePosition<Space, KSpace> & anUpdate);

    /**
     * Method to update the position of the last added image.
     * @param viewer the viewer where to draw
     * @param anUpdate the update to set
     */
    static void
    draw( Viewer3D<Space,KSpace> & viewer, const DGtal::UpdateLastImagePosition<Space, KSpace> & anUpdate );


    /**
     * Method to modify 3D Image embedding.
     * @param viewer the viewer where to draw
     * @param anUpdate the update to set
     */
    static void
    draw( Viewer3D<Space,KSpace> & viewer, const DGtal::UpdateImage3DEmbedding<Space, KSpace> & anUpdate);

    /**
     * Method to apply domain position change
     * @param viewer the viewer where to draw
     * @param anUpdate the update to set
     */
    static void
    draw( Viewer3D<Space,KSpace> &viewer, const DGtal::Update2DDomainPosition<Space, KSpace> & anUpdate);

    /**
     * Method to apply image translate.
     * @param viewer the viewer where to draw
     * @param anTranslation the translation to apply
     */
    static void
    draw( Viewer3D<Space,KSpace> &viewer, const DGtal::Translate2DDomain & anTranslation);

    /**
     * Method to apply image data change.
     * @param viewer the viewer where to draw
     * @param anUpdate the update to set
     */
    template<typename TImageType, typename TFunctor>
    static void
    draw( Viewer3D<Space,KSpace> & viewer, const DGtal::UpdateImageData<TImageType, TFunctor> & anUpdate);

    /**
     * Method to draw TransformedPrism
     * @param viewer the viewer where to draw
     * @param aTransformedPrism the transformed surfelprism to draw
     */
    static void
    draw( Viewer3D<Space,KSpace> & viewer, const DGtal::TransformedPrism & aTransformedPrism);

    /**
     * Set the "OpenGL name" of future graphical commands.
     * @param viewer the viewer where to draw
     * @param aName3d an object storing the "OpenGL" name.
     */
    static void 
    draw( Viewer3D<Space,KSpace> & viewer, const DGtal::SetName3D& aName3d );

    /**
     * Set the callback function when selecting an object (e.g. shift
     * + left click in QGLViewer).
     *
     * @param viewer the viewer where to draw
     * @param aFct an object storing the callback function.
     */
    static void 
    draw( Viewer3D<Space,KSpace> & viewer, const DGtal::SetSelectCallback3D& aFct );

    // end heritage
    //----------------------------------------------------------------------------------------------

  }; // end of struct Viewer3DFactory

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods
#include "DGtal/io/viewers/Viewer3DFactory.ih"


// //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Viewer3DFactory_h

#undef Viewer3DFactory_RECURSES
#endif // else defined(Viewer3DFactory_RECURSES)
