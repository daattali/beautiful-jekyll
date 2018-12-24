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
 * @file CImageCacheWritePolicy.h
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/02/22
 *
 * Header file for concept CImageCacheWritePolicy.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CImageCacheWritePolicy_RECURSES)
#error Recursive header files inclusion detected in CImageCacheWritePolicy.h
#else // defined(CImageCacheWritePolicy_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CImageCacheWritePolicy_RECURSES

#if !defined CImageCacheWritePolicy_h
/** Prevents repeated inclusion of headers. */
#define CImageCacheWritePolicy_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
/////////////////////////////////////////////////////////////////////////////
// class CImageCacheWritePolicy
/**
Description of \b concept '\b CImageCacheWritePolicy' <p>
@ingroup Concepts
@brief Aim: Defines the concept describing a cache write policy

### Refinement of

### Associated types :
 - \e ImageContainer : type of the image in the cache, model of concept CImage
 - \e Point : type of the image point
 - \e Value : type of the image value

### Notation
 - \e X : A type that is a model of CImageCacheWritePolicy
 - \e x : object of type X
 - \e i : object of type ImageContainer
 - \e p : object of type Point
 - \e v : object of type Value

### Definitions

### Valid expressions and semantics

| Name                | Expression              | Type requirements                                          | Return type       | Precondition | Semantics                                                   | Post condition | Complexity |
|---------------------|-------------------------|------------------------------------------------------------|-------------------|--------------|-------------------------------------------------------------|----------------|------------|
| Write in page       | x.writeInPage(i,p,v)    | i of type ImageContainer, p of type Point, v of type Value |                   |              | set a value v on an image i at a given position p           |                |            |
| Flush page          | x.flushPage(i)          | i of type ImageContainer                                   |                   |              | flush the image i on disk according to the cache policy     |                |            |

### Invariants

### Models
ImageCacheWritePolicyWT, ImageCacheWritePolicyWB

### Notes

@tparam T the type that should be a model of CImageCacheWritePolicy.
 */
template <typename T>
struct CImageCacheWritePolicy
{
    // ----------------------- Concept checks ------------------------------
public:

    typedef typename T::ImageContainer ImageContainer;

    BOOST_CONCEPT_USAGE( CImageCacheWritePolicy )
    {
        myT.writeInPage(myIC, myPoint, myValue);
        myT.flushPage(myIC);

        // check const methods.
        checkConstConstraints();
    }
    
    void checkConstConstraints() const
    {
    }
    
    // ------------------------- Private Datas --------------------------------
private:
    T myT; // do not require T to be default constructible.
    ImageContainer * myIC;
    typename T::Point myPoint;
    typename T::Value myValue;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CImageCacheWritePolicy
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CImageCacheWritePolicy_h

#undef CImageCacheWritePolicy_RECURSES
#endif // else defined(CImageCacheWritePolicy_RECURSES)
