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
 * @file CTrivialConstImage.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/02/08
 *
 * This file is part of the DGtal library.
 */

#if defined(CTrivialConstImageRECURSES)
#error Recursive header files inclusion detected in CTrivialConstImage.h
#else // defined(CTrivialConstImageRECURSES)
/** Prevents recursive inclusion of headers. */
#define CTrivialConstImageRECURSES

#if !defined CTrivialConstImage_h
/** Prevents repeated inclusion of headers. */
#define CTrivialConstImage_h

#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#include <boost/concept/requires.hpp>

#include "DGtal/kernel/CPointFunctor.h"
#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/base/CLabel.h"

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // struct CTrivialConstImage
  /**
Description of \b concept '\b CTrivialConstImage' <p>
@ingroup Concepts
     
@brief Aim: Defines the concept describing a read-only image,
which is a refinement of CPointFunctor.
     
###  Refinement of 
     CPointFunctor
     
###  Associated types :
     - \a Domain: type of the image domain, model of concept CDomain
     
###  Notation
    - \a X : A type that is a model of CTrivialConstImage
    - \a x, \a y  : Object of type X
    
###  Definitions
   
###  Valid expressions and semantics

   
| Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
|---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
|Accessor to the domain | x.domain() | | const Domain & | | returns a const reference to the image domain | | O(1) |



###  Invariants

###  Models
ImageContainerBySTLVector, ImageContainerBySTLMap, ImageContainerByITKImage, ImageContainerByHashTree

   */

  template <typename I>
  struct CTrivialConstImage: concepts::CPointFunctor<I>
  {

  public:

    BOOST_CONCEPT_ASSERT((CLabel<typename I::Value>));
    //Inner types
    typedef typename I::Domain Domain;
    BOOST_CONCEPT_ASSERT((concepts::CDomain<Domain>));


    BOOST_CONCEPT_USAGE(CTrivialConstImage)
    {
      ConceptUtils::sameType(i.domain(), d);
    }

  private:
    I i;
    Domain d;

  };
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CTrivialConstImage_h

#undef CTrivialConstImageRECURSES
#endif // else defined(CTrivialConstImageRECURSES)
