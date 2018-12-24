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
 * @file   Board3DTo2DFactory.h
 * @author Aline Martin <aline.martin@insa-lyon.fr>
 * @date   mardi 2 juillet 2013
 *
 * @brief
 *
 * Header file for module Board3DTo2DFactory
 *
 * This file is part of the DGtal library.
 */

#if defined(Board3DTo2DFactory_RECURSES)
#error Recursive header files inclusion detected in Board3DTo2DFactory.h
#else // defined(Board3DTo2DFactory_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Board3DTo2DFactory_RECURSES

#if !defined Board3DTo2DFactory_h
/** Prevents repeated inclusion of headers. */
#define Board3DTo2DFactory_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions

#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"

#include "DGtal/io/Display3DFactory.h"
#include "DGtal/io/boards/DrawWithBoard3DTo2DModifier.h"
#include "DGtal/geometry/curves/StandardDSS6Computer.h"
#include "DGtal/geometry/curves/Naive3DDSSComputer.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"
#include "DGtal/kernel/sets/DigitalSetByAssociativeContainer.h"
#include "DGtal/kernel/sets/DigitalSetBySTLVector.h"
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

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
/////////////////////////////////////////////////////////////////////////////
// struct Board3DTo2DFactory
/**
   * Description of struct 'Board3DTo2DFactory' <p>
   * \brief Factory for GPL Display3D:
   */
  template <typename TSpace, typename TKSpace>
  struct Board3DTo2DFactory : public Display3DFactory<TSpace,TKSpace>
  {
    typedef TSpace Space;
    typedef TKSpace KSpace;

  /**
   * set the camera position on the board
   * @param board the board where to draw
   * @param aThing the camera position to set
   */
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::CameraPosition & aThing );

  /**
   * set the camera direction on the board
   * @param board the board where to draw
   * @param aThing the camera direction to set
   */
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::CameraDirection & aThing );

  /**
   * set the camera up vector on the board
   * @param board the board where to draw
   * @param aThing the camera up vector to set
   */
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::CameraUpVector & aThing );

  /**
   * set the near and far distance on the board
   * @param board the board where to draw
   * @param aThing the near and far distance
   */
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::CameraZNearFar & aThing );


  //----------------------------------------------------------------------------------------------
  // heritage
  // SphericalAccumulator
  /**
       * Display an spherical accumulator in 3D. Bin values are mapped
       * using a default HueShadeColorMap.
       *
       * @param board the board where to draw current board
       * @param accumulator the accumulator to board
       * @param shift translate vector for board purposes (default:
       * zero vector)
       * @param radius scale factor for the unit sphere radius (default:1)
       * @tparam TVector a vector model
       */
  template <typename TVector>
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const  DGtal::SphericalAccumulator<TVector> & accumulator,
                    const typename DGtal::SphericalAccumulator<TVector>::RealVector & shift =
      typename DGtal::SphericalAccumulator<TVector>::RealVector(0,0,0),
                    const double radius=1.0);
  // SphericalAccumulator

  // Mesh
  /**
   * @brief drawAsFaces
   * @param board the board where to draw
   * @param aMesh the mesh to draw
   */
    template <typename TPoint>
  static void
  drawAsFaces( Board3DTo2D<Space, KSpace> & board, const DGtal::Mesh<TPoint> & aMesh );

  /**
   * @brief draw
   * @param board the board where to draw
   * @param aMesh the mesh to draw
   */
  template <typename TPoint>
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const  DGtal::Mesh<TPoint> & aMesh );
  // Mesh



  // StandardDSS6Computer
  /**
   * Default drawing style object.
   * @param str the name of the class
   * @param arithm the arithm to draw
   *  @return the dyn. alloc. default style for this object.
   */
  template <typename TIterator, typename TInteger, int connectivity>
  static DGtal::DrawableWithBoard3DTo2D *
  defaultStyle( std::string str, const DGtal::StandardDSS6Computer<TIterator,TInteger,connectivity> & arithm );

  template <typename TIterator, typename TInteger, int connectivity>
  /**
   * @brief drawAsBalls
   * @param board the board where to draw
   * @param arithm the arithm to draw
   */
  static void
  drawAsBalls( Board3DTo2D<Space, KSpace> & board, const DGtal::StandardDSS6Computer<TIterator,TInteger,connectivity> & arithm );

  /**
   * @brief drawAsBoundingBox
   * @param board the board where to draw
   * @param arithm the arithm to draw
   */
  template <typename TIterator, typename TInteger, int connectivity>
  static void
  drawAsBoundingBox( Board3DTo2D<Space, KSpace> & board, const DGtal::StandardDSS6Computer<TIterator,TInteger,connectivity> & arithm );

  template <typename TIterator, typename TInteger, int connectivity>
  /**
   * @brief draw
   * @param board the board where to draw
   * @param arithm the arithm to draw
   */
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::StandardDSS6Computer<TIterator,TInteger,connectivity> & arithm );
  // StandardDSS6Computer
  
  
    // Naive3DDSSComputer
  /**
   * Default drawing style object.
   * @param str the name of the class
   * @param arithm the arithm to draw
   *  @return the dyn. alloc. default style for this object.
   */
  template <typename TIterator, typename TInteger, int connectivity>
  static DGtal::DrawableWithBoard3DTo2D *
  defaultStyle( std::string str, const DGtal::Naive3DDSSComputer<TIterator,TInteger,connectivity> & arithm );

  template <typename TIterator, typename TInteger, int connectivity>
  /**
   * @brief drawAsBalls
   * @param board the board where to draw
   * @param arithm the arithm to draw
   */
  static void
  drawAsBalls( Board3DTo2D<Space, KSpace> & board, const DGtal::Naive3DDSSComputer<TIterator,TInteger,connectivity> & arithm );

  /**
   * @brief drawAsBoundingBox
   * @param board the board where to draw
   * @param arithm the arithm to draw
   */
  template <typename TIterator, typename TInteger, int connectivity>
  static void
  drawAsBoundingBox( Board3DTo2D<Space, KSpace> & board, const DGtal::Naive3DDSSComputer<TIterator,TInteger,connectivity> & arithm );

  template <typename TIterator, typename TInteger, int connectivity>
  /**
   * @brief draw
   * @param board the board where to draw
   * @param arithm the arithm to draw
   */
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::Naive3DDSSComputer<TIterator,TInteger,connectivity> & arithm );
  // Naive3DDSSComputer


    // DigitalSetBySTLSet
    /**
     * Default drawing style object.
     * @param str the name of the class
     * @param aSet the set to draw
     * @return the dyn. alloc. default style for this object.
     */
    template<typename Domain, typename Compare>
    static DGtal::DrawableWithBoard3DTo2D *
    defaultStyle( std::string str, const DGtal::DigitalSetBySTLSet<Domain, Compare> & aSet );
    
    /**
     * @brief drawAsPavingTransparent
     * @param board the board where to draw
     * @param aSet the set to draw
     */
    template<typename Domain, typename Compare>
    static void
    drawAsPavingTransparent( Board3DTo2D<Space, KSpace> & board, const DGtal::DigitalSetBySTLSet<Domain, Compare> & aSet );
    
    /**
     * @brief drawAsPaving
     * @param board the board where to draw
     * @param aSet the set to draw
     */
    template<typename Domain, typename Compare>
    static void
    drawAsPaving( Board3DTo2D<Space, KSpace> & board, const DGtal::DigitalSetBySTLSet<Domain, Compare> & aSet );
    
    /**
     * @brief drawAsGrid
     * @param board the board where to draw
     * @param aSet the set to draw
     */
    template<typename Domain, typename Compare>
    static void
    drawAsGrid( Board3DTo2D<Space, KSpace> & board, const DGtal::DigitalSetBySTLSet<Domain, Compare> & aSet );
    
    /**
     * @brief draw
     * @param board the board where to draw
     * @param aSet the set to draw
     */
    template<typename Domain, typename Compare>
    static void
    draw( Board3DTo2D<Space, KSpace> & board, const DGtal::DigitalSetBySTLSet<Domain, Compare> & aSet );
    // DigitalSetBySTLSet

    // DigitalSetByAssociativeContainer
  /**
   * Default drawing style object.
   * @param str the name of the class
   * @param aSet the set to draw
   * @return the dyn. alloc. default style for this object.
   */
  template<typename Domain, typename Container>
  static DGtal::DrawableWithBoard3DTo2D *
  defaultStyle( std::string str, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & aSet );

  /**
   * @brief drawAsPavingTransparent
   * @param board the board where to draw
   * @param aSet the set to draw
   */
  template<typename Domain, typename Container>
  static void
  drawAsPavingTransparent( Board3DTo2D<Space, KSpace> & board, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & aSet );

  /**
   * @brief drawAsPaving
   * @param board the board where to draw
   * @param aSet the set to draw
   */
  template<typename Domain, typename Container>
  static void
  drawAsPaving( Board3DTo2D<Space, KSpace> & board, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & aSet );

  /**
   * @brief drawAsGrid
   * @param board the board where to draw
   * @param aSet the set to draw
   */
  template<typename Domain, typename Container>
  static void
  drawAsGrid( Board3DTo2D<Space, KSpace> & board, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & aSet );

  /**
   * @brief draw
   * @param board the board where to draw
   * @param aSet the set to draw
   */
  template<typename Domain, typename Container>
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::DigitalSetByAssociativeContainer<Domain, Container> & aSet );
  // DigitalSetByAssociativeContainer


  // DigitalSetBySTLVector
  /**
   * Default drawing style object.
   * @param str the name of the class
   * @param aSet the set to draw
   * @return the dyn. alloc. default style for this object.
   */
  template<typename Domain>
  static DGtal::DrawableWithBoard3DTo2D *
  defaultStyle( std::string str, const DGtal::DigitalSetBySTLVector<Domain> & aSet );

  /**
   * @brief drawAsPavingTransparent
   * @param board the board where to draw
   * @param aSet the set to draw
   */
  template<typename Domain>
  static void
  drawAsPavingTransparent( Board3DTo2D<Space, KSpace> & board, const DGtal::DigitalSetBySTLVector<Domain> & aSet );

  /**
   * @brief drawAsPaving
   * @param board the board where to draw
   * @param aSet the set to draw
   */
  template<typename Domain>
  static void
  drawAsPaving( Board3DTo2D<Space, KSpace> & board, const DGtal::DigitalSetBySTLVector<Domain> & aSet );

  /**
   * @brief drawAsGrid
   * @param board the board where to draw
   * @param aSet the set to draw
   */
  template<typename Domain>
  static void
  drawAsGrid( Board3DTo2D<Space, KSpace> & board, const DGtal::DigitalSetBySTLVector<Domain> & aSet );

  /**
   * @brief draw
   * @param board the board where to draw
   * @param aSet the set to draw
   */
  template<typename Domain>
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::DigitalSetBySTLVector<Domain> & aSet );
  // DigitalSetBySTLVector


  // HyperRectDomain
  /**
   * Default drawing style object.
   * @param str the name of the class
   * @param aDomain the domain to draw
   * @return the dyn. alloc. default style for this object.
   */
  template<typename SpaceDom>
  static DGtal::DrawableWithBoard3DTo2D *
  defaultStyle( std::string str, const DGtal::HyperRectDomain<SpaceDom> & aDomain );

  /**
   * @brief drawAsBoundingBox
   * @param board the board where to draw
   * @param aDomain the domain to draw
   */
  template<typename SpaceDom>
  static void
  drawAsBoundingBox( Board3DTo2D<Space, KSpace> & board, const DGtal::HyperRectDomain<SpaceDom> & aDomain );

  /**
   * @brief drawAsGrid
   * @param board the board where to draw
   * @param aDomain the domain to draw
   */
  template<typename SpaceDom>
  static void
  drawAsGrid( Board3DTo2D<Space, KSpace> & board, const DGtal::HyperRectDomain<SpaceDom> & aDomain );

  /**
   * @brief drawAsPavingBalls
   * @param board the board where to draw
   * @param aDomain the domain to draw
   */
  template<typename SpaceDom>
  static void
  drawAsPavingBalls( Board3DTo2D<Space, KSpace> & board, const DGtal::HyperRectDomain<SpaceDom> & aDomain );

  /**
   * @brief drawAsPaving
   * @param board the board where to draw
   * @param aDomain the domain to draw
   */
  template<typename SpaceDom>
  static void
  drawAsPaving( Board3DTo2D<Space, KSpace> & board, const DGtal::HyperRectDomain<SpaceDom> & aDomain );

  /**
   * @brief draw
   * @param board the board where to draw
   * @param aDomain the domain to draw
   */
  template<typename SpaceDom>
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::HyperRectDomain<SpaceDom> & aDomain );
  // HyperRectDomain


  // KhalimskyCell
  /**
   * Default drawing style object.
   * @param str the name of the class
   * @param aCell the cell to draw
   * @return the dyn. alloc. default style for this object.
   */
  static DGtal::DrawableWithBoard3DTo2D *
  defaultStyle( std::string str, const typename KSpace::Cell & aCell );

  /**
   * @brief draw
   * @param board the board where to draw
   * @param aCell the cell to draw
   */
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const typename KSpace::Cell & aCell );
  // KhalimskyCell


  // Object
  /**
   * @brief defaultStyle
   * @param str the name of the class
   * @param anObject the object to draw
   * @return the dyn. alloc. default style for this object.
   */
  template <typename TDigitalTopology, typename TDigitalSet>
  static DGtal::DrawableWithBoard3DTo2D *
  defaultStyle( std::string str, const DGtal::Object<TDigitalTopology, TDigitalSet> & anObject );

  /**
   * @brief drawWithAdjacencies
   * @param board the board where to draw
   * @param anObject the object to draw
   */
  template <typename TDigitalTopology, typename TDigitalSet>
  static void
  drawWithAdjacencies( Board3DTo2D<Space, KSpace> & board, const DGtal::Object<TDigitalTopology, TDigitalSet> & anObject );

  /**
   * @brief draw
   * @param board the board where to draw
   * @param anObject the object to draw
   */
  template <typename TDigitalTopology, typename TDigitalSet>
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::Object<TDigitalTopology, TDigitalSet> & anObject );
  // Object


  // PointVector
  /**
   * Default drawing style object.
   * @param str the name of the class
   * @param aPoint the point to draw
   * @return the dyn. alloc. default style for this object.
   */
  template<Dimension dim, typename TComponent, typename TContainer>
  static DGtal::DrawableWithBoard3DTo2D *
  defaultStyle( std::string str, const DGtal::PointVector<dim, TComponent, TContainer> & aPoint );

  /**
   * @brief drawAsGrid
   * @param board the board where to draw
   * @param aPoint the point to draw
   */
  template<Dimension dim, typename TComponent, typename TContainer>
  static void
  drawAsGrid( Board3DTo2D<Space, KSpace> & board, const DGtal::PointVector<dim, TComponent, TContainer> & aPoint );

  /**
   * @brief drawAsPaving
   * @param board the board where to draw
   * @param aPoint the point to draw
   */
  template<Dimension dim, typename TComponent, typename TContainer>
  static void
  drawAsPaving( Board3DTo2D<Space, KSpace> & board, const DGtal::PointVector<dim, TComponent, TContainer> & aPoint );

  /**
   * @brief drawAsPavingWired
   * @param board the board where to draw
   * @param aPoint the point to draw
   */
  template<Dimension dim, typename TComponent, typename TContainer>
  static void
  drawAsPavingWired( Board3DTo2D<Space, KSpace> & board, const DGtal::PointVector<dim, TComponent, TContainer> & aPoint );

  /**
   * @brief draw
   * @param board the board where to draw
   * @param aPoint the point to draw
   */
  template<Dimension dim, typename TComponent, typename TContainer>
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::PointVector<dim, TComponent, TContainer> & aPoint );

  /**
   * @brief draw
   * @param board the board where to draw
   * @param aPoint the point to draw
   * @param aPoint2 the point to draw
   */
  template<Dimension dim, typename TComponent1, typename TComponent2, typename TContainer1, typename TContainer2>
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::PointVector<dim, TComponent1, TContainer1> & aPoint, const DGtal::PointVector<dim, TComponent2, TContainer2> & aPoint2 );
  // PointVector


  // SignedKhalimskyCell
  /**
   * Default drawing style object.
   * @param str the name of the class
   * @param aSCell the signed cell to draw
   * @return the dyn. alloc. default style for this object.
   */
  static DGtal::DrawableWithBoard3DTo2D *
  defaultStyle( std::string str, const typename KSpace::SCell & aSCell );

  /**
   * @brief draw
   * @param board the board where to draw
   * @param aSCell the signed cell to draw
   */
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const typename KSpace::SCell & aSCell );
  // SignedKhalimskyCell

  // GridCurve
  /**
   * @brief draw
   * @param board the board where to draw
   * @param aGrid the grid to draw
   */
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::GridCurve<KSpace> & aGrid );
  // GridCurve

  // SCellsRange
  /**
   * @brief draw
   * @param board the board where to draw
   * @param aRangeAdapter the range adapter to draw
   */
  template < typename TIterator, typename TSCell>
  static void
  draw( Board3DTo2D<Space, KSpace> & board,
        const ConstRangeAdapter<TIterator, DGtal::functors::Identity, TSCell> & aRangeAdapter );
  // SCellsRange

  // PointsRange
  /**
   * @brief draw
   * @param board the board where to draw
   * @param aRangeAdapter the range adapter to draw
   */
  template <typename TIterator>
  static void
  draw( Board3DTo2D<Space, KSpace> & board,
                    const DGtal::ConstRangeAdapter<TIterator, functors::SCellToPoint<KSpace>, typename KSpace::Point> & aRangeAdapter );
  // PointsRange

  // MidPointsRange
  /**
   * @brief draw
   * @param board the board where to draw
   * @param aRangeAdapter the range adapter to draw
   */
  template <typename TIterator>
  static void
  draw( Board3DTo2D<Space, KSpace> & board,
                    const DGtal::ConstRangeAdapter<TIterator, CanonicSCellEmbedder<KSpace>, typename KSpace::Space::RealPoint> & aRangeAdapter );
  // MidPointsRange

  // ArrowsRange
  /**
   * @brief draw
   * @param board the board where to draw
   * @param aRangeAdapter the range adapter to draw
   */
    template <typename TIterator>
  static void
  draw( Board3DTo2D<Space, KSpace> & board,
                    const DGtal::ConstRangeAdapter<TIterator, functors::SCellToArrow<KSpace>, std::pair<typename KSpace::Point, typename KSpace::Vector > > & aRangeAdapter );
  // ArrowsRange

  // InnerPointsRange
  /**
   * @brief draw
   * @param board the board where to draw
   * @param aRangeAdapter the range adapter to draw
   */
  template <typename TIterator>
  static void
  draw( Board3DTo2D<Space, KSpace> & board,
                    const DGtal::ConstRangeAdapter<TIterator, functors::SCellToInnerPoint<KSpace>, typename KSpace::Point> & aRangeAdapter );
  // InnerPointsRange

  // OuterPointsRange
  /**
   * @brief draw
   * @param board the board where to draw
   * @param aRangeAdapter the range adapter to draw
   */
  template <typename TIterator>
  static void
  draw( Board3DTo2D<Space, KSpace> & board,
                    const DGtal::ConstRangeAdapter<TIterator, functors::SCellToOuterPoint<KSpace>, typename KSpace::Point> & aRangeAdapter );
  // OuterPointsRange

  // IncidentPointsRange
  /**
   * @brief draw
   * @param board the board where to draw
   * @param aRangeAdapter the range adapter to draw
   */
  template <typename TIterator>
  static void
  draw( Board3DTo2D<Space, KSpace> & board,
                    const DGtal::ConstRangeAdapter<TIterator, functors::SCellToIncidentPoints<KSpace>,std::pair<typename KSpace::Point, typename KSpace::Point > > & aRangeAdapter );
  // IncidentPointsRange


  /**
   * @brief draw
   * @param board the board where to draw
   * @param aMode the mode to set
   */
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::SetMode3D & aMode);

  /**
   * @brief draw
   * @param board the board where to draw
   * @param aStyle the style to set
   */
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::CustomStyle3D & aStyle);

  /**
   * @brief draw
   * @param board the board where to draw
   * @param aColor the color to set
   */
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::CustomColors3D & aColor);

  /**
   * @brief draw
   * @param board the board where to draw
   * @param aClipping the clipping plane to draw
   */
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::ClippingPlane & aClipping);

  /**
   * @brief draw
   * @param board the board where to draw
   * @param aTransformedPrism the transformed surfelprism to draw
   */
  static void
  draw( Board3DTo2D<Space, KSpace> & board, const DGtal::TransformedPrism & aTransformedPrism);

  // end heritage
  //----------------------------------------------------------------------------------------------

}; // end of struct Board3DTo2DFactory

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods
#include "DGtal/io/boards/Board3DTo2DFactory.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Board3DTo2DFactory_h

#undef Board3DTo2DFactory_RECURSES
#endif // else defined(Board3DTo2DFactory_RECURSES)
