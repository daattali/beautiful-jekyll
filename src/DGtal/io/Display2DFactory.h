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
 * @file   Display2DFactory.h
 * @author Martial Tola <http://liris.cnrs.fr/martial.tola/>
 * @date   mercredi 28 septembre 2011
 * 
 * @brief
 *
 * Header file for module Display2DFactory
 *
 * This file is part of the DGtal library.
 */

#if defined(Display2DFactory_RECURSES)
#error Recursive header files inclusion detected in Display2DFactory.h
#else // defined(Display2DFactory_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Display2DFactory_RECURSES

#if !defined Display2DFactory_h
/** Prevents repeated inclusion of headers. */
#define Display2DFactory_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions

#include "DGtal/base/Common.h"

#include "DGtal/kernel/sets/DigitalSetByAssociativeContainer.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"
#include "DGtal/kernel/sets/DigitalSetBySTLVector.h"

#include "DGtal/math/AngleLinearMinimizer.h"
#include "DGtal/geometry/curves/ArithmeticalDSS.h"
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
#include "DGtal/geometry/curves/AlphaThickSegmentComputer.h"
#include "DGtal/shapes/fromPoints/CircleFrom2Points.h"
#include "DGtal/shapes/fromPoints/CircleFrom3Points.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"
#include "DGtal/kernel/sets/DigitalSetBySTLVector.h"
#include "DGtal/geometry/curves/GridCurve.h"
#include "DGtal/geometry/curves/FP.h"
#include "DGtal/geometry/curves/FreemanChain.h"
#include "DGtal/geometry/curves/StabbingLineComputer.h"
#include "DGtal/geometry/curves/StabbingCircleComputer.h"
#include "DGtal/geometry/curves/FrechetShortcut.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/ImageContainerByHashTree.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ImageAdapter.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/KhalimskyPreSpaceND.h"
#include "DGtal/topology/Object.h"
#include "DGtal/topology/CubicalComplex.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/geometry/tools/Preimage2D.h"
#include "DGtal/shapes/fromPoints/StraightLineFrom2Points.h"
#include "DGtal/arithmetic/LatticePolytope2D.h"
#include "DGtal/topology/CanonicSCellEmbedder.h"
#include "DGtal/dec/VectorField.h"
#include "DGtal/dec/KForm.h"
#include "DGtal/dec/DiscreteExteriorCalculus.h"

#include "DGtal/helpers/StdDefs.h"

//////////////////////////////////////////////////////////////////////////////


namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// struct Display2DFactory
/**
 * Description of struct 'Display2DFactory' <p>
 * \brief Factory for Display2D:
 */
  struct Display2DFactory
 {
		public:

template <Dimension dim, typename TInteger>
static
void
drawDECSignedKhalimskyCell(DGtal::Board2D& board, const DGtal::SignedKhalimskyCell<dim, TInteger>& cell);

template <Dimension dim, typename TInteger>
static
void
drawDECSignedKhalimskyCell(DGtal::Board2D& board, const DGtal::SignedKhalimskyPreCell<dim, TInteger>& cell);

// DiscreteExteriorCalculus
template <Dimension dimEmbedded, Dimension dimAmbient, typename TLinearAlgebraBackend, typename TInteger>
static
void
draw(DGtal::Board2D& board, const DGtal::DiscreteExteriorCalculus<dimEmbedded, dimAmbient, TLinearAlgebraBackend, TInteger>& calculus);
// DiscreteExteriorCalculus

// KForm
template <typename TCalculus, DGtal::Order order, DGtal::Duality duality>
static
void
draw(DGtal::Board2D& board, const DGtal::KForm<TCalculus, order, duality>& kform);

template <typename TCalculus, DGtal::Order order, DGtal::Duality duality, typename TColorMap>
static
void
drawWithColorMap(DGtal::Board2D& board, const DGtal::KForm<TCalculus, order, duality>& kform, const TColorMap& colormap);
// KForm
    
// VectorField
template <typename TCalculus, DGtal::Duality duality>
static
void
draw(DGtal::Board2D& board, const DGtal::VectorField<TCalculus, duality>& vector_field);
// VectorField

// AngleLinearMinimizer
static void draw( DGtal::Board2D & board, const DGtal::AngleLinearMinimizer & );
// AngleLinearMinimizer
    
// ArithmeticalDSS
template <typename TCoordinate, typename TInteger, unsigned short adjacency>
  static void drawAsBoundingBox( DGtal::Board2D & aBoard, 
			  const DGtal::ArithmeticalDSS<TCoordinate,TInteger,adjacency> & );

template <typename TCoordinate, typename TInteger, unsigned short adjacency>
  static void drawAsDigitalPoints( DGtal::Board2D & aBoard, 
			    const DGtal::ArithmeticalDSS<TCoordinate,TInteger,adjacency> & );

template <typename TCoordinate, typename TInteger, unsigned short adjacency>
  static void draw( DGtal::Board2D & board, const DGtal::ArithmeticalDSS<TCoordinate,TInteger,adjacency> & );
// ArithmeticalDSS

    
// ArithmeticalDSSComputer
template <typename TIterator, typename TInteger, int connectivity>
  static void drawAsBoundingBox( DGtal::Board2D & aBoard, 
			  const DGtal::ArithmeticalDSSComputer<TIterator,TInteger,connectivity> & );

template <typename TIterator, typename TInteger, int connectivity>
  static void drawAsDigitalPoints( DGtal::Board2D & aBoard, 
			    const DGtal::ArithmeticalDSSComputer<TIterator,TInteger,connectivity> & );

template <typename TIterator, typename TInteger, int connectivity>
static void draw( DGtal::Board2D & board, const DGtal::ArithmeticalDSSComputer<TIterator,TInteger,connectivity> & );
// ArithmeticalDSSComputer


// AlphaThickSegmentComputer
template < typename TInputPoint,  typename TConstIterator>
static void drawAsBoundingBox( DGtal::Board2D & aBoard, 
                               const DGtal::AlphaThickSegmentComputer< TInputPoint, TConstIterator> & );

template < typename TInputPoint, typename TConstIterator>
static void drawAsDigitalPoints( DGtal::Board2D & aBoard, 
                                 const DGtal::AlphaThickSegmentComputer<TInputPoint, TConstIterator> & );

template < typename TInputPoint,  typename TConstIterator>
  static void draw( DGtal::Board2D & aBoard, 
                    const DGtal::AlphaThickSegmentComputer< TInputPoint, TConstIterator> & );
// AlphaThickSegmentComputer
    
    
// CircleFrom2Points
template <typename TPoint>
static void draw(Board2D & aBoard, const DGtal::CircleFrom2Points<TPoint> & );
// CircleFrom2Points


// CircleFrom3Points
template <typename Point>
static void drawArc(Board2D & aBoard, const DGtal::CircleFrom3Points<Point> &, const Point &, const Point &, bool anOrientation = true);
    
template <typename Point>
static void drawSector(Board2D & aBoard, const DGtal::CircleFrom3Points<Point> &, const Point &, const Point &, bool anOrientation = true);
    
template <typename Point>
static void drawAnnulus(Board2D & aBoard, const DGtal::CircleFrom3Points<Point> &, const Point &, const Point &, bool anOrientation = true, const double& w = 1.0);
    
template <typename Point>
static void draw(Board2D & aBoard, const DGtal::CircleFrom3Points<Point> &, const Point &, const Point &, bool anOrientation = true);
    
template <typename TPoint>
static void draw(Board2D & aBoard, const DGtal::CircleFrom3Points<TPoint> & );
// CircleFrom3Points
    
    
// DigitalSetBySTLSet
template<typename Domain, typename Compare>
static void draw( DGtal::Board2D & board, const DGtal::DigitalSetBySTLSet<Domain, Compare> & );
// DigitalSetBySTLSet

   
// DigitalSetByAssociativeContainer
template<typename Domain, typename Container>
static void draw( DGtal::Board2D & board, const DGtal::DigitalSetByAssociativeContainer<Domain,Container> & );
// DigitalSetByAssociativeContainer
   
    
// DigitalSetBySTLVector
template<typename Domain>
static void draw( DGtal::Board2D & board, const DGtal::DigitalSetBySTLVector<Domain> & );
// DigitalSetBySTLVector
    
    
// FP
template <typename TIterator, typename TInteger, int connectivity>
  static void drawAsPolygon( DGtal::Board2D & aBoard, const DGtal::FP<TIterator,TInteger,connectivity> & );

template <typename TIterator, typename TInteger, int connectivity>
  static void draw( DGtal::Board2D & board, const DGtal::FP<TIterator,TInteger,connectivity> & );
// FP
    
    
// FreemanChain
template <typename TInteger>
static void drawAsGrid( DGtal::Board2D & aBoard, const DGtal::FreemanChain<TInteger> & );
    
template <typename TInteger>
static void drawAsInterGrid( DGtal::Board2D & aBoard, const DGtal::FreemanChain<TInteger> & );
    
template <typename TInteger>
static void draw( DGtal::Board2D & aBoard, const DGtal::FreemanChain<TInteger> & );
// FreemanChain
    
    
// StabbingLineComputer
template <typename TConstIterator>
static void draw(DGtal::Board2D & aBoard, const DGtal::StabbingLineComputer<TConstIterator> & );
// StabbingLineComputer

// StabbingCircleComputer
template <typename TConstIterator>
static void draw(DGtal::Board2D & aBoard, const DGtal::StabbingCircleComputer<TConstIterator> & );
// StabbingCircleComputer


//FrechetShortcut
template <typename TIterator, typename TInteger>
static  void draw(DGtal::Board2D & aBoard, const DGtal::FrechetShortcut<TIterator,TInteger> & );
//FrechetShortcut

    
// GridCurve
template <typename TKSpace>
static void draw( DGtal::Board2D & aBoard, 
           const GridCurve<TKSpace> & object );
template <typename TKSpace>
static void drawFill( DGtal::Board2D & aBoard, const GridCurve<TKSpace> & object );
// GridCurve
    
// SCellsRange
template <typename TIterator, typename TSCell>
static void draw( DGtal::Board2D & aBoard,
                  const ConstRangeAdapter<TIterator, functors::Identity, TSCell> & object );
// SCellsRange
    
// PointsRange
template <typename TIterator, typename TKSpace>
static void draw( DGtal::Board2D & aBoard, 
           const ConstRangeAdapter<TIterator, functors::SCellToPoint<TKSpace>, typename TKSpace::Point> & object );
// PointsRange

// MidPointsRange
template <typename TIterator, typename TKSpace>
static void draw( DGtal::Board2D & aBoard, 
           const ConstRangeAdapter<TIterator, CanonicSCellEmbedder<TKSpace>,
           typename TKSpace::Space::RealPoint> & object );
// MidPointsRange

// ArrowsRange
template <typename TIterator, typename TKSpace>
static void draw( DGtal::Board2D & aBoard, 
           const ConstRangeAdapter<TIterator, functors::SCellToArrow<TKSpace>, 
           std::pair<typename TKSpace::Point, typename TKSpace::Vector > > & object );
// ArrowsRange

// InnerPointsRange
template <typename TIterator, typename TKSpace>
static void draw( DGtal::Board2D & aBoard, 
           const ConstRangeAdapter<TIterator, functors::SCellToInnerPoint<TKSpace>, 
           typename TKSpace::Point > & object );
// InnerPointsRange

// OuterPointsRange
template <typename TIterator, typename TKSpace>
static void draw( DGtal::Board2D & aBoard, 
           const ConstRangeAdapter<TIterator, functors::SCellToOuterPoint<TKSpace>, 
           typename TKSpace::Point > & object );
// OuterPointsRange

// IncidentPointsRange
template <typename TIterator, typename TKSpace>
static void draw( DGtal::Board2D & aBoard, 
           const ConstRangeAdapter<TIterator, functors::SCellToIncidentPoints<TKSpace>, 
           std::pair<typename TKSpace::Point, typename TKSpace::Point> > & object );
// IncidentPointsRange

// HyperRectDomain
template<typename TSpace>
static void drawAsGrid( DGtal::Board2D & aboard, const DGtal::HyperRectDomain<TSpace> & );

template<typename TSpace>
static void drawAsPaving( DGtal::Board2D & aboard, const DGtal::HyperRectDomain<TSpace> & );

template<typename TSpace>
static void draw( DGtal::Board2D & board, const DGtal::HyperRectDomain<TSpace> & );
// HyperRectDomain
    
    
// ImageContainerByHashTree
template <typename C, typename Domain, typename Value, typename HashKey>
static void drawImageRecursive( DGtal::Board2D & aBoard, 
                         const DGtal::experimental::ImageContainerByHashTree<Domain, Value, HashKey> & i,
                         HashKey key,
                         const double p[2],
                         const double len,
                         LibBoard::Board & board,
                         const C& cmap );

template <typename C, typename Domain, typename Value, typename HashKey>
static void drawImageHashTree( Board2D & board,
                const DGtal::experimental::ImageContainerByHashTree<Domain, Value, HashKey> &,
                const Value &, const Value & );
// ImageContainerByHashTree


// ImageContainerBySTLVector, ImageContainerByHashTree, Image and ImageAdapter...
// minV and maxV are bounds values of colormap
template <typename Colormap, typename Image>
  static void drawImage( DGtal::Board2D & board,
                          const Image & i,
                          const typename Image::Value & minV,
                          const typename Image::Value & maxV );
// ImageContainerBySTLVector, ImageContainerByHashTree, Image and ImageAdapter...
    
    
// KhalimskyCell
template < Dimension dim, typename TInteger >
  static void draw( DGtal::Board2D & board, const DGtal::KhalimskyCell<dim, TInteger> & );
// KhalimskyCell
    
// KhalimskyPreCell
template < Dimension dim, typename TInteger >
  static void draw( DGtal::Board2D & board, const DGtal::KhalimskyPreCell<dim, TInteger> & );
// KhalimskyPreCell
    
// Object
template <typename TDigitalTopology, typename TDigitalSet>
  static void drawWithAdjacencies( DGtal::Board2D & aBoard, const DGtal::Object<TDigitalTopology, TDigitalSet> & );

template <typename TDigitalTopology, typename TDigitalSet>
  static void draw( DGtal::Board2D & board, const DGtal::Object<TDigitalTopology, TDigitalSet> & );
// Object


// CubicalComplex
template < typename TKSpace, typename TCellContainer >
  static void draw( DGtal::Board2D & board, const DGtal::CubicalComplex<TKSpace, TCellContainer> & );
// CubicalComplex

    
    
// PointVector
template<Dimension dim, typename TComponent, typename TContainer>
  static void drawAsPaving( DGtal::Board2D & board, const DGtal::PointVector<dim, TComponent, TContainer> & );

template<Dimension dim, typename TComponent, typename TContainer>
  static void drawAsGrid( DGtal::Board2D & board, const DGtal::PointVector<dim, TComponent, TContainer> & );

template<Dimension dim, typename TComponent, typename TContainer>
  static void draw( DGtal::Board2D & board, const DGtal::PointVector<dim, TComponent, TContainer> & );

//arrow drawing
template<Dimension dim, typename TComponent1, typename TComponent2, typename TContainer1, typename TContainer2>
  static void draw( DGtal::Board2D & board, 
	     const DGtal::PointVector<dim, TComponent1, TContainer1> & shift,
	     const DGtal::PointVector<dim, TComponent2, TContainer2> & basepoint);
// PointVector
    
    
// Preimage2D
template <typename Shape>
static void draw( DGtal::Board2D & aBoard, const DGtal::Preimage2D<Shape> & );
// Preimage2D
    
    
// SignedKhalimskyCell
template < Dimension dim, typename TInteger >
  static void draw( DGtal::Board2D & board, const DGtal::SignedKhalimskyCell<dim, TInteger> & );
// SignedKhalimskyCell
    
// SignedKhalimskyPreCell
template < Dimension dim, typename TInteger >
  static void draw( DGtal::Board2D & board, const DGtal::SignedKhalimskyPreCell<dim, TInteger> & );
// SignedKhalimskyPreCell
    
// StraightLineFrom2Points
template <typename TPoint>
static void draw(Board2D & aBoard, const DGtal::StraightLineFrom2Points<TPoint> & );
// StraightLineFrom2Points
  
    
//
    
    
static void draw( DGtal::Board2D & board, const DGtal::CustomStyle & );
static void draw( DGtal::Board2D & board, const DGtal::SetMode & );


   /**
      Draw method on Board for LatticePolytope2D.
      
      @param aBoard an instance of Board2D.
      @param cip an instance of convex integer polygon.
   */
   template <typename TSpace, typename TSequence>
   static
   void draw( DGtal::Board2D & aBoard, 
              const DGtal::LatticePolytope2D<TSpace, TSequence> & cip );

    
  }; // end of struct Display2DFactory

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods 
#include "DGtal/io/Display2DFactory.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Display2DFactory_h

#undef Display2DFactory_RECURSES
#endif // else defined(Display2DFactory_RECURSES)
