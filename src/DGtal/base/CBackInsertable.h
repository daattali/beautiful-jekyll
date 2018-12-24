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
 * @file CBackInsertable.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/04/02
 *
 * Header file for concept CBackInsertable.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CBackInsertable_RECURSES)
#error Recursive header files inclusion detected in CBackInsertable.h
#else // defined(CBackInsertable_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CBackInsertable_RECURSES

#if !defined CBackInsertable_h
/** Prevents repeated inclusion of headers. */
#define CBackInsertable_h

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
    // class CBackInsertable
    /**
       Description of \b concept '\b CBackInsertable' <p>
       @ingroup Concepts

       @brief Aim: Represents types for which a std::back_insert_iterator can
       be constructed with std::back_inserter. Back Insertion Sequence are
       refinements of CBackInsertable. They require more services than
       CBackInsertable, for instance read services or erase services.

       ### Refinement of

       ### Associated types :
       - \e value_type: the type of object that can be inserted at the back.

       ### Notation
       - \e X : A type that is a model of CBackInsertable
       - \e x : object of type X
       - \e e : object of type value_type

       ### Definitions

       ### Valid expressions and semantics

       | Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
       |-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
       | Add to back | \e x.push_back( \e e )|  |               |              | adds the element \e e at the end of object \e x | | |

       ### Invariants

       ### Models

       - Most standard linear containers: std::vector, std::list, std::deque
       - CPositiveIrreducibleFraction is a refinement of CBackInsertable
       - hence fractions: SternBrocot::Fraction, LighterSternBrocot::Fraction, LightSternBrocot::Fraction

       ### Notes

       @tparam T the type that should be a model of CBackInsertable.
    */
    template <typename T>
    struct CBackInsertable
    {
      // ----------------------- Concept checks ------------------------------
    public:
      typedef typename T::value_type value_type;
      BOOST_CONCEPT_USAGE( CBackInsertable )
      {
        myX.push_back( myV );
        checkConstConstraints();
      }
      void checkConstConstraints() const
      {
      }
      // ------------------------- Private Datas --------------------------------
    private:
      T myX; // do not require T to be default constructible.
      value_type myV;

      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CBackInsertable

  } // namespace concepts

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CBackInsertable_h

#undef CBackInsertable_RECURSES
#endif // else defined(CBackInsertable_RECURSES)
