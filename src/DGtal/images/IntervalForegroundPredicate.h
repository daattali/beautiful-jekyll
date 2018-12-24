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
 * @file IntervalForegroundPredicate.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/03/26
 *
 * Header file for module IntervalForegroundPredicate.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(IntervalForegroundPredicate_RECURSES)
#error Recursive header files inclusion detected in IntervalForegroundPredicate.h
#else // defined(IntervalForegroundPredicate_RECURSES)
/** Prevents recursive inclusion of headers. */
#define IntervalForegroundPredicate_RECURSES

#if !defined IntervalForegroundPredicate_h
/** Prevents repeated inclusion of headers. */
#define IntervalForegroundPredicate_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/images/CConstImage.h"
#include "DGtal/base/ConstAlias.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::functors
namespace DGtal {
  namespace functors {

  /**
   * Description of template class 'IntervalForegroundPredicate' <p>
   * \brief Aim: Define a simple Foreground predicate thresholding
   * image values  between two constant values (the first one being
   * excluded).
   *
   * This class is a model of concepts::CPointPredicate.
   *
   * @tparam Image an model of CImageContainer concept. 
   */
  template <typename Image>
  class IntervalForegroundPredicate
  {
  public:
    BOOST_CONCEPT_ASSERT(( concepts::CConstImage<Image> ));
    
    typedef typename Image::Value Value;
    typedef typename Image::Point Point; 

    /** 
     * Constructor. This functor can be used to threshold image values
     * in the interval ]minVal,maxVal].
     *
     * @param aImage the image.
     * @param minVal the minimum value (first value excluded).
     * @param maxVal the maximum value (last value considered).
     */
    IntervalForegroundPredicate(ConstAlias<Image> aImage,
                                const Value minVal, 
                                const Value maxVal): 
      myImage(&aImage), myMaxVal(maxVal), myMinVal(minVal) {};
    
    /** 
     * @return True if the point belongs to the value interval.
     */
    bool operator()(const typename Image::Point &aPoint) const
    {
      return ((*myImage)(aPoint) > myMinVal) && ((*myImage)(aPoint) <= myMaxVal);
    }
    
    /** 
     * @return True if the point belongs to the value interval.
     */
    bool operator()(const typename Image::ConstRange::ConstIterator &it) const
    {
      return ((*it) > myMinVal) && ((*it) <= myMaxVal);
    }

  
  private:
    const Image* myImage;
    Value myMaxVal;
    Value myMinVal;
    
  protected:
    IntervalForegroundPredicate();
    
  };

} // namespace functors
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined IntervalForegroundPredicate_h

#undef IntervalForegroundPredicate_RECURSES
#endif // else defined(IntervalForegroundPredicate_RECURSES)
