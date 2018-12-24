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
 * @file CImage.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/08
 *
 * This file is part of the DGtal library.
 */

#if defined(CImageRECURSES)
#error Recursive header files inclusion detected in CImage.h
#else // defined(CImageRECURSES)
/** Prevents recursive inclusion of headers. */
#define CImageRECURSES

#if !defined CImage_h
/** Prevents repeated inclusion of headers. */
#define CImage_h

#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#include <boost/concept/requires.hpp>

#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/images/CConstImage.h"
#include "DGtal/base/CConstBidirectionalRangeFromPoint.h"
#include "DGtal/base/CBidirectionalRangeWithWritableIteratorFromPoint.h"
#include "DGtal/images/CTrivialImage.h"

namespace DGtal
{
namespace concepts
{
/////////////////////////////////////////////////////////////////////////////
// struct CImage
/**
   Description of \b concept '\b CImage' <p>
   @ingroup Concepts
   @brief Aim: Defines the concept describing a read/write image,
   having an output iterator.
   
### Refinement of

  CTrivialImage and CConstImage

### Associated types:
- the same as CTrivialImage
- the same as CConstImage
- \a Range : type of the Range
 
 
 ### Notation
  - \a X : A type that is a model of CImage
  - \a x : Object of type X
  - \a aPoint : Object of type Point
  - \a aValue : Object of type Value
 
 
 ### Definitions
 
 ### Valid expressions and semantics


| Name                                | Expression                         | Type requirements    | Return type           | Precondition                       | Semantics                                             | Post condition | Complexity |
|-------------------------------------|------------------------------------|----------------------|-----------------------|------------------------------------|-------------------------------------------------------|----------------|------------|
| get range                           | x.range()                          |                      | Range                 |                                    | Returns a range on the image values                   |                |            |


 
### Invariants

### Models
  ImageContainerBySTLVector, ImageContainerBySTLMap, ImageContainerByITKImage, ImageContainerByHashTree
 

### Notes
 
 */

template <typename I>
struct CImage: CConstImage<I>, CTrivialImage<I>
{

public:

    typedef typename I::Range Range;
    BOOST_CONCEPT_ASSERT((CConstBidirectionalRangeFromPoint<Range>));
    BOOST_CONCEPT_ASSERT((CBidirectionalRangeWithWritableIteratorFromPoint<Range, typename
    I::Value>));

public:

    BOOST_CONCEPT_USAGE(CImage)
    {
        ConceptUtils::sameType( myI.range(), myR);
    }

private:

    I myI;
    Range myR;

};
}
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CImage_h

#undef CImageRECURSES
#endif // else defined(CImageRECURSES)
