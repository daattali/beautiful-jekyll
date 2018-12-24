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
 * @file CPowerSeparableMetric.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/11/01
 *
 * Header file for concept CPowerSeparableMetric.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CPowerSeparableMetric_RECURSES)
#error Recursive header files inclusion detected in CPowerSeparableMetric.h
#else // defined(CPowerSeparableMetric_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CPowerSeparableMetric_RECURSES

#if !defined CPowerSeparableMetric_h
/** Prevents repeated inclusion of headers. */
#define CPowerSeparableMetric_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/volumes/distance/CPowerMetric.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {

  /////////////////////////////////////////////////////////////////////////////
  // class CPowerSeparableMetric
  /**
 Description of \b concept '\b CPowerSeparableMetric' <p>
 @ingroup Concepts
 @brief Aim: defines the concept of separable metrics. 

 Separable metrics are metrics satsifying the monotonicity property. 

 ### Refinement of CPowerMetric

 ### Associated types :

 ### Notation
 - \e X : A type that is a model of CPowerSeparableMetric
 - \e x, \e y : object of type X

 ### Definitions

 ### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| hiddenBy predicate |  hiddenByPower(u,Wu,v,Wv,w,Wv,startingPoint,endPoint,dim)    | u,v,w,startingPoint,endPoint of type @a Point, Wu,Wv,Ww of type @a Weight, dim of type DGtal::Dimension |   @a startingPoint and @a endPoint only differ by their @a dim-th coordinate   | returns true if the intersection between the segment [@a startingPoint,@a endPoint] and the Voronoi cell associated with @a v is empty (hidden on the segment by @a u and @a w Voronoi cells).   |           |                |   -         |

 ### Invariants

 ### Models

ExactPredicateLpPowerSeparableMetric, 

 ### Notes

 @tparam T the type that should be a model of CPowerSeparableMetric.
  */
  template <typename T>
  struct CPowerSeparableMetric: CPowerMetric<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    typedef typename T::Point Point;
    typedef typename T::Weight Weight;

    BOOST_CONCEPT_USAGE( CPowerSeparableMetric )
    {
      checkConstConstraints();
    }
    void checkConstConstraints() const
    {
      // const method dummyConst should take parameter myA of type A and return
      // something of type B
      ConceptUtils::sameType( myBool, myX.hiddenByPower(u,wu,v,wv,w,ww,start,end,dim) );
    }
    // ------------------------- Private Datas --------------------------------
  private:
    T myX; // do not require T to be default constructible.
    Point u,v,w,start,end;
    Weight ww,wu,wv;
    bool myBool;
    DGtal::Dimension dim;
  
    // ------------------------- Internals ------------------------------------
  private:

  }; // end of concept CPowerSeparableMetric
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CPowerSeparableMetric_h

#undef CPowerSeparableMetric_RECURSES
#endif // else defined(CPowerSeparableMetric_RECURSES)
