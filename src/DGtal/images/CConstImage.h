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
 * @file CConstImage.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/02/08
 *
 * This file is part of the DGtal library.
 */

#if defined(CConstImageRECURSES)
#error Recursive header files inclusion detected in CConstImage.h
#else // defined(CConstImageRECURSES)
/** Prevents recursive inclusion of headers. */
#define CConstImageRECURSES

#if !defined CConstImage_h
/** Prevents repeated inclusion of headers. */
#define CConstImage_h

#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#include <boost/concept/requires.hpp>

#include "DGtal/kernel/CPointFunctor.h"
#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/base/CConstBidirectionalRangeFromPoint.h"
#include "DGtal/base/CLabel.h"
#include "DGtal/images/CTrivialConstImage.h"

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // struct CConstImage
  /**
 * Description of \b concept '\b CConstImage' <p>
 *
 * @ingroup Concepts
 * @brief Aim: Defines the concept describing a read-only image,
 * which is a refinement of CPointFunctor.
 *
### Refinement of CTrivialConstImage
   
###  Associated types :
    - \e Domain: type of the image domain, model of concept CDomain
    - \e ConstRange: type of range of image values,
    model of concept CConstBidirectionalRangeFromPoint
    
###  Notation
- \e X : A type that is a model of CConstImage
- \e x, \e y  : Object of type X

###  Definitions

###  Valid expressions and semantics


| Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
|---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
|Accessor to the domain |x.domain() | |const Domain & | | returns a const reference to the image domain | | O(1) | 
|Accessor to the range of the image values | x.constRange() | | ConstRange | | returns a constant range | | O(1) |



###  Invariants

###  Model
   ImageContainerBySTLVector, ImageContainerBySTLMap, ImageContainerByITKImage, ImageContainerByHashTree
  
###  Notes

   */

  template <typename I>
  struct CConstImage: CTrivialConstImage<I>
  {

  public:

    //Inner types
    typedef typename I::Domain Domain;
    BOOST_CONCEPT_ASSERT((concepts::CDomain<Domain>));

    typedef typename I::ConstRange ConstRange;
    BOOST_CONCEPT_ASSERT((CConstBidirectionalRangeFromPoint<ConstRange>));

    BOOST_CONCEPT_USAGE(CConstImage)
    {
      ConceptUtils::sameType(i.domain(), d);
      ConceptUtils::sameType(i.constRange(), r);
    }

  private:
    I i;
    Domain d;
    ConstRange r;

  };
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CConstImage_h

#undef CConstImageRECURSES
#endif // else defined(CConstImageRECURSES)
