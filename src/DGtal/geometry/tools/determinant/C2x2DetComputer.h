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
 * @file C2x2DetComputer.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/11/22
 *
 * Header file for concept C2x2DetComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(C2x2DetComputer_RECURSES)
#error Recursive header files inclusion detected in C2x2DetComputer.h
#else // defined(C2x2DetComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define C2x2DetComputer_RECURSES

#if !defined C2x2DetComputer_h
/** Prevents repeated inclusion of headers. */
#define C2x2DetComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/kernel/CEuclideanRing.h"
#include "DGtal/kernel/CSignedNumber.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class C2x2DetComputer
  /**
     Description of \b concept '\b C2x2DetComputer' <p>
     @ingroup Concepts
     @brief Aim: This concept gathers all models that are
     able to compute the (sign of the) determinant of a 2x2
     matrix with integral entries. 

     ### Invariant

     The returned value, which is a model of CSignedNumber, is guaranteed to be: 
     - strictly positive if the determinant is strictly positive
     - striclty negative if the determinant is strictly negative
     - zero if the determinant is null

     ### Refinement of 
     boost::DefaultConstructible<T>, boost::CopyConstructible<T>, boost::Assignable<T>

     ### Associated types :
     - ArgumentInteger : integral type of the four entries, at least a model of CEuclideanRing
     - ResultInteger : integral type of the result, at least a model of CSignedNumber

     ### Notation
     - \e X : A type that is a model of C2x2DetComputer
     - \e x : object of type X
     - \e a, b, c, d : integral entries of type ArgumentInteger
     - \e r : result to type ResultInteger

     ### Valid expressions and semantics

     | Name               | Expression        | Type requirements | Return type   | Precondition | Semantics         | Post condition | Complexity      |
     |--------------------|-------------------|-------------------|---------------|--------------|-------------------|----------------|-----------------|
     | full operator()    | r = x(a, b, c, d) |                   | ResultInteger |              | (sign of) ad - bc |                | model dependent |
     | initialization     | x.init(a,b)       |                   | void          |              | memorizes a and b |                | constant        |
     | partial operator() | r = x(c, d)       |                   | ResultInteger |              | (sign of) ad - bc |                | model dependent |

     ### Notes

     In addition to the full operator(), this concept allows another way to compute the quantity ad - bc in two steps: 
     - first, we set the first column vector, ie a and b. 
     - then, we compute the quantity ad - bc from a given column vector, ie c and d with the memorized values of a and b.   
     This feature is a way of accepting models that incrementally computes many determinants of matrices 
     whose first column vector, ie a and b, is constant and whose second column vector, ie c and d, 
     slightly varies from one computation to the next one. See for instance, SimpleIncremental2x2DetComputer. 

     ### Models

     Simple2x2DetComputer, SimpleIncremental2x2DetComputer, AvnaimEtAl2x2DetSignComputer, Filtered2x2DetComputer


     @tparam T the type that should be a model of C2x2DetComputer.
  */
  template <typename T>
  struct C2x2DetComputer : boost::DefaultConstructible<T>, boost::CopyConstructible<T>, boost::Assignable<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    typedef typename T::ArgumentInteger ArgumentType;
    BOOST_CONCEPT_ASSERT(( concepts::CEuclideanRing< ArgumentType > ));

    typedef typename T::ResultInteger ResultType;
    BOOST_CONCEPT_ASSERT(( concepts::CSignedNumber< ResultType > ));

    BOOST_CONCEPT_USAGE( C2x2DetComputer )
    {
      concepts::ConceptUtils::sameType( myR, myX( myA, myB, myC, myD ) );
      myX.init(myA, myB); 
      concepts::ConceptUtils::sameType( myR, myX( myA, myB ) );
    }
    // ------------------------- Private Datas --------------------------------
  private:
    T myX; 
    ArgumentType myA, myB, myC, myD;
    ResultType myR; 
    // ------------------------- Internals ------------------------------------
  private:

  }; // end of concept C2x2DetComputer

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined C2x2DetComputer_h

#undef C2x2DetComputer_RECURSES
#endif // else defined(C2x2DetComputer_RECURSES)
