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
 * @file CQuantity.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/07
 *
 * Header file for concept CQuantity.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CQuantity_RECURSES)
#error Recursive header files inclusion detected in CQuantity.h
#else // defined(CQuantity_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CQuantity_RECURSES

#if !defined CQuantity_h
/** Prevents repeated inclusion of headers. */
#define CQuantity_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CLabel.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace concepts
  {

    /////////////////////////////////////////////////////////////////////////////
    // class CQuantity
    /**
       Description of \b concept '\b CQuantity' <p>
       @ingroup Concepts
       @brief Aim: defines the concept of quantity in DGtal.

       ###  Refinement of
       -  CLabel 
       -  boost::LessThanComparable

       ###  Associated types :

       ###  Notation
       - \a X : A type that is a model of CQuantity
       - \a x, \a y : object of type X

       ###  Definitions

       ###  Valid expressions and semantics

       | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
       |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
       |               |            | | | | | | | 


       ###  Invariants

       ###  Models


       ###  Notes

       @tparam T the type that should be a model of CQuantity.
    */
    template <typename T>
    struct CQuantity : CLabel<T>, boost::LessThanComparable<T>
    {


    }; // end of concept CQuantity

  } // namespace concepts

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CQuantity_h

#undef CQuantity_RECURSES
#endif // else defined(CQuantity_RECURSES)
