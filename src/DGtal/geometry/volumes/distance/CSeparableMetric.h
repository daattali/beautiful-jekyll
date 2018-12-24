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
 * @file CSeparableMetric.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/11/01
 *
 * Header file for concept CSeparableMetric.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CSeparableMetric_RECURSES)
#error Recursive header files inclusion detected in CSeparableMetric.h
#else // defined(CSeparableMetric_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CSeparableMetric_RECURSES

#if !defined CSeparableMetric_h
/** Prevents repeated inclusion of headers. */
#define CSeparableMetric_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/volumes/distance/CMetricSpace.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
namespace concepts
{
/////////////////////////////////////////////////////////////////////////////
// class CSeparableMetric
/**
Description of \b concept '\b CSeparableMetric' <p>
@ingroup Concepts
@brief Aim: defines the concept of separable metrics. 

Separable metrics are metrics satsifying the monotonicity
property. More formally, in dimension 2, consider two points @f$
p(x,y)@f$, @f$q(x',y')@f$ with @f$x<x@f$. Let @f$r( x'',0)@f$ be a
point on the x-axis such that @f$d(p,r) = d(q,r)@f$ and @f$ s(u,0)@f$
be another point on the x-axis. A metric @f$ d@f$ is @e monotonic if 
    
@f[     u < x'' \implies d(p,s) \leq d(q,s) @f]
and
@f[    u > x'' \implies d(p,s) \geq d(q,s) @f]

 

### Refinement of 
  - concepts::CMetricSpace.

### Associated types :

### Notation
 - \e X : A type that is a model of CSeparableMetric
 - \e x, \e y : object of type X

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| hiddenBy predicate |  hiddenBy(u,v,w,startingPoint,endPoint,dim)    | u,v,w,startingPoint,endPoint of type @a Point, dim of type DGtal::Dimension |   @a startingPoint and @a endPoint only differ by their @a dim-th coordinate   | returns true if the intersection between the segment [@a startingPoint,@a endPoint] and the Voronoi cell associated with @a v is empty (hidden on the segment by @a u and @a w Voronoi cells).   |           |                |   -         |

### Invariants

### Models


ExactPredicateLpSeparableMetric, InexactPredicateLpSeparableMetric


### Notes

@tparam T the type that should be a model of concepts::CSeparableMetric.
 */
template <typename T>
struct CSeparableMetric: CMetricSpace<T>
{
    // ----------------------- Concept checks ------------------------------
public:
    typedef typename T::Point Point;
    BOOST_CONCEPT_USAGE( CSeparableMetric )
    {
      checkConstConstraints();
    }
    void checkConstConstraints() const
    {
        // const method dummyConst should take parameter myA of type A and return
        // something of type B
      ConceptUtils::sameType( myBool, myX.hiddenBy(u,v,w,start,end,dim) );
    }
    // ------------------------- Private Datas --------------------------------
private:
  T myX; // do not require T to be default constructible.
  Point u,v,w,start,end;
  bool myBool;
  DGtal::Dimension dim;
  
    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CSeparableMetric
}
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CSeparableMetric_h

#undef CSeparableMetric_RECURSES
#endif // else defined(CSeparableMetric_RECURSES)
