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
 * @file CUnaryFunctor.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/02/07
 *
 * Header file for concept CUnaryFunctor.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CUnaryFunctor_RECURSES)
#error Recursive header files inclusion detected in CUnaryFunctor.h
#else // defined(CUnaryFunctor_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CUnaryFunctor_RECURSES

#if !defined CUnaryFunctor_h
/** Prevents repeated inclusion of headers. */
#define CUnaryFunctor_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConceptUtils.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // class CUnaryFunctor
  /**
Description of \b concept '\b CUnaryFunctor' <p>
     @ingroup Concepts
     \brief Aim: Defines a unary functor, which
     associates arguments to results

### Refinement of 

 - boost::Assignable

### Associated types :

### Notation
     - \a X : a type that is a model of CUnaryFunctor
     - \a x : Object of type \a X
     - \a A : argument type
     - \a a : Object of type \a A
     - \a R : result type
     - \a r : Object of type \a R

### Definitions

### Valid expressions and semantics

| Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
|---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
| Apply function | r = x(\a a) |                   | \c R        |                  | returns the value of the function \a x on argument \a a | | |         


### Invariants

### Models

### Notes
  */
  template <typename X, typename A, typename R>
  struct CUnaryFunctor : boost::Assignable<X>
  {

    // ----------------------- Concept checks ------------------------------
  public:

    BOOST_CONCEPT_USAGE( CUnaryFunctor )
    {
      // x( a ) returns r.
      ConceptUtils::sameType( r, x.operator() ( a ) );
    }
    // ------------------------- Private Datas --------------------------------
  private:
    X x;
    A a;
    R r;
    // ------------------------- Internals ------------------------------------
  private:

  }; // end of concept CUnaryFunctor

  //specialization for references
  template <typename X, typename A, typename R>
  struct CUnaryFunctor<X, A&, R&> : boost::Assignable<X>
  {

    // ----------------------- Concept checks ------------------------------
  public:

    BOOST_CONCEPT_USAGE( CUnaryFunctor )
    {
      ConceptUtils::sameType( getRef(r), x.operator() ( getRef(a) ) );
    }
    // ------------------------- Private Datas --------------------------------
  private:
    X x;
    A a;
    R r;
    // ------------------------- Internals ------------------------------------
  private:
    template<typename T>
    T& getRef(T& t) 
    {
      return t; 
    }

  }; // end of concept CUnaryFunctor
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CUnaryFunctor_h

#undef CUnaryFunctor_RECURSES
#endif // else defined(CUnaryFunctor_RECURSES)
