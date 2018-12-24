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
 * @file ImageHelper.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/15
 *
 * Header file for module ImageHelper.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImageHelper_RECURSES)
#error Recursive header files inclusion detected in ImageHelper.h
#else // defined(ImageHelper_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImageHelper_RECURSES

#if !defined ImageHelper_h
/** Prevents repeated inclusion of headers. */
#define ImageHelper_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <algorithm>
#include <functional>

#include "DGtal/base/Common.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/base/CConstSinglePassRange.h"
#include "DGtal/kernel/BasicPointPredicates.h"
#include "DGtal/kernel/CPointFunctor.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/images/CConstImage.h"
#include "DGtal/images/ConstImageAdapter.h"
#include "DGtal/images/CImage.h"
#include "DGtal/base/CQuantity.h"
#include "DGtal/images/ImageContainerBySTLMap.h"
#include "DGtal/images/SetValueIterator.h"
#include "DGtal/kernel/sets/DigitalSetFromMap.h"
#include "DGtal/kernel/sets/CDigitalSet.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/base/ConstAlias.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /// useful functions
  /**
   * Fill a set through the inserter @a ito
   * with the points of the range [@a itb , @a ite )
   * such that @a aPred is true
   *
   * @param itb begin iterator on points
   * @param ite end iterator on points
   * @param ito output iterator on points
   * @param aPred any predicate
   *
   * @tparam I any model of input iterator
   * @tparam O any model of output iterator
   * @tparam P any model of concepts::CPointPredicate
   */
  template<typename I, typename O, typename P>
  void setFromPointsRangeAndPredicate(const I& itb, const I& ite, const O& ito, const P& aPred); 

  /**
   * Fill a set through the inserter @a ito
   * with the points of the range [@a itb , @a ite )
   * such that their associated value 
   * (returned by @a aFunctor ) is less than or
   * equal to @a aThreshold
   *
   * @param itb begin iterator on points
   * @param ite end iterator on points
   * @param ito output iterator on points
   * @param aFunctor any functor on points
   * @param aThreshold any value (default: 0)
   *
   * @tparam I any model of input iterator
   * @tparam O any model of output iterator
   * @tparam F any model of CPointFunctor
   */
  template<typename I, typename O, typename F>
  void setFromPointsRangeAndFunctor(const I& itb, const I& ite, 
				    const O& ito, const F& aFunctor, 
				    const typename F::Value& aThreshold = 0); 

  /**
   * Fill a set through the inserter @a ito
   * with the points lying within the domain 
   * of the image @a aImg whose value 
   * (in the image) is less than or equal to 
   * @a aThreshold
   *
   * @param aImg any image
   * @param ito set inserter
   * @param aThreshold any value (default: 0)
   *
   * @tparam I any model of CConstImage
   * @tparam O any model of output iterator
   */
  template<typename I, typename O>
  void setFromImage(const I& aImg, 
		    const O& ito, 
		    const typename I::Value& aThreshold = 0); 

  /**
   * Fill a set through the inserter @a ito
   * with the points lying within the domain 
   * of the image @a aImg whose value 
   * (in the image) lies between @a low and @a up
   * (both included) 
   *
   * @param aImg any image
   * @param ito set inserter
   * @param low lower value
   * @param up upper value
   *
   * @tparam I any model of CConstImage
   * @tparam O any model of output iterator
   */
  template<typename I, typename O>
  void setFromImage(const I& aImg, 
		    const O& ito, 
		    const typename I::Value& low,
		    const typename I::Value& up); 


  /**
   * Set the values of @a aImg at @a aValue
   * for each points of the range [ @a itb , @a ite )
   *
   * @param itb begin iterator on points
   * @param ite end iterator on points
   * @param aImg (returned) image
   * @param aValue any value (default: 0)
   *
   * @tparam It any model of forward iterator
   * @tparam Im any model of CImage
   */
  template<typename It, typename Im>
  void imageFromRangeAndValue(const It& itb, const It& ite, Im& aImg, 
			      const typename Im::Value& aValue = 0); 

  /**
   * Set the values of @a aImg at @a aValue
   * for each points of the range @a aRange
   *
   * @param aRange any range
   * @param aImg (returned) image
   * @param aValue any value (default: 0)
   *
   * @tparam R any model of CConstSinglePassRange
   * @tparam I any model of CImage
   */
  template<typename R, typename I>
  void imageFromRangeAndValue(const R& aRange, I& aImg, 
			      const typename I::Value& aValue = 0); 

  /**
   * In a window corresponding to the domain of @a aImg, 
   * copy the values of @a aFun into @a aImg
   *
   * @param aImg (returned) image
   * @param aFun a unary functor
   *
   * @tparam I any model of CImage
   * @tparam F any model of CPointFunctor
   */
  template<typename I, typename F>
  void imageFromFunctor(I& aImg, const F& aFun); 

  /**
   * Copy the values of @a aImg2 into @a aImg1 .
   *
   * @param aImg1 the image to fill
   * @param aImg2 the image to copy
   *
   * @tparam I1 any model of CImage
   * @tparam I2 any model of CConstImage
   */
  template<typename I1, typename I2>
  void imageFromImage(I1& aImg1, const I2& aImg2); 

  /**
   * Insert @a aPoint in @a aSet and if (and only if)
   * @a aPoint is a newly inserted point. 
   * Then set @a aValue at @a aPoint in @a aImg.
   *
   * @param aImg an image
   * @param aSet a digital set
   * @param aPoint a point
   * @param aValue a value
   *
   * @return 'true' if a new point was inserted in @a aSet 
   * but 'false' if the same point already exist in @a aSet
   *
   * @tparam I any model of CImage
   * @tparam S any model of CDigitalSet
   *
   * The general behavior is like: 
   * @code
    bool found = true; 
    if ( aSet.find( aPoint ) == aSet.end() )
      { //if not found
	found = false; 
	aSet.insert( aPoint );
	aImg.setValue( aPoint, aValue ); 
      }      
    return !found; 
   * @endcode
   * 
   * However, this code is specialized if 
   * I is an ImageContainerBySTLMap and 
   * S is a @link DigitalSetFromMap DigitalSetFromMap\<I\>@endlink as follows: 
   * @code
   std::pair<P, V> 
   pair( aPoint, aValue );  
   std::pair<Iterator, bool> res 
   = aImg.insert( pair ); 
   return res.second;  
   * @endcode
   *
   * @see ImageContainerBySTLMap DigitalSetFromMap 
   * @see insertAndAlwaysSetValue
   */
  template<typename I, typename S>
  bool insertAndSetValue(I& aImg, S& aSet, 
			 const typename I::Point& aPoint, 
			 const typename I::Value& aValue ); 

  /**
   * Insert @a aPoint in @a aSet and 
   * set @a aValue at @a aPoint in @a aImg.
   *
   * @param aImg an image
   * @param aSet a digital set
   * @param aPoint a point
   * @param aValue a value
   *
   * @return 'true' if a new point was inserted in @a aSet 
   * but 'false' if the same point already exist in @a aSet
   *
   * @tparam I any model of CImage
   * @tparam S any model of CDigitalSet
   *
   * The general behavior is like: 
   * @code
    bool found = false; 
    if ( aSet.find( aPoint ) != aSet.end() )
      found = true;       
    //always set value
    aSet.insert( aPoint );
    aImg.setValue( aPoint, aValue ); 
    return !found; 
   * @endcode
   * 
   * However, this code is specialized if 
   * I is an ImageContainerBySTLMap and 
   * S is a @link DigitalSetFromMap DigitalSetFromMap\<I\>@endlink as follows: 
   * @code
   std::pair<P, V> 
   pair( aPoint, aValue );  
   std::pair<Iterator, bool> res 
   = aImg.insert( pair );
   bool flag = res.second; 
   if (flag == false) //set value even in this case
   res.first->second = aValue;
   return flag; 
   * @endcode
   *
   * @see ImageContainerBySTLMap DigitalSetFromMap 
   * @see insertAndSetValue
   */
  template<typename I, typename S>
  bool insertAndAlwaysSetValue(I& aImg, S& aSet, 
			       const typename I::Point& aPoint, 
			       const typename I::Value& aValue ); 

  /**
   * Read the value contained in @a aImg at @a aPoint
   * if @a aPoint belongs to @a aSet.
   *
   * @param aImg an image
   * @param aSet a digital set
   * @param aPoint a point
   * @param aValue (returned) value
   *
   * @return 'true' if a new point is found and the value read 
   * but 'false' otherwise
   *
   * @tparam I any model of CConstImage
   * @tparam S any model of CDigitalSet
   *
   * The general behavior is like: 
   * @code
   * @endcode
   * 
   * However, this code is specialized if 
   * I is an ImageContainerBySTLMap and 
   * S is a @link DigitalSetFromMap DigitalSetFromMap\<I\>@endlink as follows: 
   * @code
   * @endcode
   *
   * @see ImageContainerBySTLMap DigitalSetFromMap 
   * @see insertAndSetValue
   */
  template<typename I, typename S>
  bool findAndGetValue(const I& aImg, const S& aSet, 
		       const typename I::Point& aPoint, 
		       typename I::Value& aValue ); 




  /**
   * Create a Point Functor from a Point Predicate and an Image.
   *
   * @tparam Image a model of CImage.
   * @tparam PointPredicate a model of concepts::CPointPredicate.
   * @tparam TValue a model of CQuantity. Type return by the functor.
   *
   */
  template<typename Image, typename PointPredicate, typename TValue=DGtal::int32_t>
  class ImageToConstantFunctor
  {
  public:

    typedef typename Image::Point Point;
    typedef TValue Value;
    
    BOOST_CONCEPT_ASSERT(( concepts::CConstImage<Image> ));
    BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate<PointPredicate> ));
    BOOST_CONCEPT_ASSERT(( concepts::CQuantity<Value> ));
    
    /*BOOST_CONCEPT_USAGE(ImageToConstantFunctor)
    {
        Point p1;
        typename PointPredicate::Point p2;
        ConceptUtils::sameType( p1, p2 );
    }*/
    
    /** 
     * 
     * 
     * @param[in] anImage image
     * @param[in] aPointPred predicate on points
     * @param[in] aVal const value when functor answer true.
     * @param[in] reverseValues used to reverse values returned by the predicate. (Some shapes consider inner as > 0, others as < 0)
     */
    ImageToConstantFunctor( ConstAlias< Image > anImage,
                            ConstAlias< PointPredicate > aPointPred,
                            Value aVal = NumberTraits< Value >::ONE,
                            bool reverseValues = false )
      : myImage(&anImage),
        myPointPred(&aPointPred),
        myVal(aVal),
        reverse(reverseValues)
    {}
    
    /** 
     * 
     * @param[in] aPoint point to evaluate.
     * 
     * @return val between _ZERO_ or aVal
     */
    Value operator()( const Point &aPoint ) const
    {
      if ((myImage->domain().isInside(aPoint)))
      {
          if( reverse )
          {
              if( !myPointPred->operator()(aPoint) )
              {
                  return myVal;
              }
              else
              {
                  return NumberTraits<Value>::ZERO;
              }
          }
          else
          {
              if( myPointPred->operator()(aPoint) )
              {
                  return myVal;
              }
              else
              {
                  return NumberTraits<Value>::ZERO;
              }
          }
      }
      else
      {
        return NumberTraits<Value>::ZERO;
      }
    }

    private:
    
    /// const pointor to an image
    const Image *myImage;
    
    /// const pointor to a predicate on points
    const PointPredicate *myPointPred;

    /// constant value when functor answer true.
    Value myVal;

    /// reverse values returned by the predicate. (Some shapes consider inner as > 0, others as < 0)
    bool reverse;
  };




 
} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions
#include "DGtal/images/ImageHelper.ih"
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImageHelper_h

#undef ImageHelper_RECURSES
#endif // else defined(ImageHelper_RECURSES)
