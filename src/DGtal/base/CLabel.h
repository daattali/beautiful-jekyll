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
 * @file CLabel.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/07
 *
 * Header file for concept CLabel.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CLabel_RECURSES)
#error Recursive header files inclusion detected in CLabel.h
#else // defined(CLabel_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CLabel_RECURSES

#if !defined CLabel_h
/** Prevents repeated inclusion of headers. */
#define CLabel_h

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
    // class CLabel
    /**
       Description of \b concept '\b CLabel' <p>
       @ingroup Concepts
       @brief Aim: Define the concept of DGtal labels.
       Models of CLabel can be default-constructible, assignable and equality comparable.

       ### Refinement of 
       - boost::DefaultConstructible
       - boost::Assignable 
       - boost::EqualityComparable

       ### Associated types :

       ### Notation
       - \a X : A type that is a model of CLabel
       - \a x, \a y : object of type X

       ### Definitions

       ### Valid expressions and semantics


       | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
       |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
       |               |            |                     |             |                  |           |                |            |     
       ### Invariants###

       ### Models###

       ### Notes###

       @tparam T the type that should be a model of CLabel.
    */
    template <typename T>
    struct CLabel  : boost::DefaultConstructible<T>, boost::Assignable<T>,
      boost::EqualityComparable<T>
    {

    }; // end of concept CLabel

  } // namespace concepts

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CLabel_h

#undef CLabel_RECURSES
#endif // else defined(CLabel_RECURSES)
