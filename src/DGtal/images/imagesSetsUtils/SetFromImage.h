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
 * @file SetFromImage.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/03/26
 *
 * Header file for module SetFromImage.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SetFromImage_RECURSES)
#error Recursive header files inclusion detected in SetFromImage.h
#else // defined(SetFromImage_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SetFromImage_RECURSES

#if !defined SetFromImage_h
/** Prevents repeated inclusion of headers. */
#define SetFromImage_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/images/CImage.h"
#include "DGtal/kernel/sets/CDigitalSet.h"
#include "DGtal/images/IntervalForegroundPredicate.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class SetFromImage
  /**
   * Description of template class 'SetFromImage' <p>
    * \brief Aim: Define utilities to convert a digital set into an
   * image.
   *
   * @tparam TSet an model of CImageContainer concept.
   */
  template <typename TSet>
  struct SetFromImage
  {
    typedef TSet Set;
   
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet<Set> ));
         
    /** 
     * Append an Image value set  to an existing Set (maybe empty).
     * @pre the ForegroundPredicate instance must have been created on the image aImage.
     *
     * @param aSet the set (maybe empty) to which points are added.
     * @param isForeground instance of ForegroundPredicate to decide
     * @param itBegin starting point in the input image Domain.
     * @param itEnd ending point in the input image domain.
     * which points to copy.
     */
    template<typename Image, typename ForegroundPredicate>
    static
    void append(Set &aSet, 
		const ForegroundPredicate &isForeground,
		typename Image::Domain::ConstIterator itBegin, 
		typename Image::Domain::ConstIterator itEnd);
  
    /** 
     * Append an Image value set  to an existing Set (maybe empty).
     * This method will construct a default ForegroundPredicate
     * instance as a simple thresholding (SimpleForegroundPredicate)
     * of values in ]minVal,maxVal].
     *
     * @param aSet the set (maybe empty) to which points are added.
     * @param aImage  the image.
     * @param minVal minimum value of the thresholding
     * @param maxVal maximum value of the thresholding
     * @param itBegin starting point in the input image Domain.
     * @param itEnd ending point in the input image domain.
     * 
     */
    template<typename Image>
    static
    void append(Set &aSet, const Image &aImage,
		const typename Image::Value minVal,
		const typename Image::Value maxVal,
		typename Image::Domain::ConstIterator itBegin, 
		typename Image::Domain::ConstIterator itEnd)
    {
      functors::IntervalForegroundPredicate<Image> isForeground(aImage,minVal,maxVal);
      
      append(aSet, isForeground,itBegin,itEnd);
    }

    /** 
     * Append an Image value set  to an existing Set (maybe empty).
     * @pre the ForegroundPredicate instance must have been created on
     * the image @a aImage.
     *
     * @param aSet the set (maybe empty) to which points are added.
     * @param aImage image to convert to a Set.
     * @param isForeground instance of ForegroundPredicate to decide
     * which points to copy.
     */
    template<typename Image,typename ForegroundPredicate>
    static
    void append(Set &aSet, const Image &aImage, const ForegroundPredicate &isForeground)
    {
      typename Image::Domain domain=aImage.domain();

      append<Image,ForegroundPredicate>(aSet,isForeground,domain.begin(),domain.end());
    }

    /** 
     * Append an Image value set  to an existing Set (maybe empty).
     * This method will construct a default ForegroundPredicate
     * instance as a simple thresholding (SimpleForegroundPredicate)
     * of values in ]minVal,maxVal].
     *
     * @param aSet the set (maybe empty) to which points are added.
     * @param aImage image to convert to a Set.
     * @param minVal minimum value of the thresholding
     * @param maxVal maximum value of the thresholding
     *
     */
    template<typename Image>
    static
    void append(Set &aSet, const Image &aImage, 
		const typename Image::Value minVal,
		const typename Image::Value maxVal)
    {
      functors::IntervalForegroundPredicate<Image> isForeground(aImage,minVal,maxVal);
      append(aSet,aImage,isForeground);
    }

  };
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/images/imagesSetsUtils/SetFromImage.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SetFromImage_h

#undef SetFromImage_RECURSES
#endif // else defined(SetFromImage_RECURSES)
