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
 * @file CMetricSpace.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/06/29
 *
 * Header file for concept CMetricSpace.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CMetricSpace_RECURSES)
#error Recursive header files inclusion detected in CMetricSpace.h
#else // defined(CMetricSpace_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CMetricSpace_RECURSES

#if !defined CMetricSpace_h
/** Prevents repeated inclusion of headers. */
#define CMetricSpace_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CSpace.h"
#include "DGtal/base/CQuantity.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {

/////////////////////////////////////////////////////////////////////////////
// class CMetricSpace
/**
Description of \b concept '\b CMetricSpace' <p>
@ingroup Concepts
@brief Aim: defines the concept of metric spaces.

Models of metric spaces must satsify metric space conditions as
described in @ref moduleMetrics. For short, models must have a 
@e Point inner type and a distance @a Value type.
 
In addition, CMetricSpace models should implement a distance function
(operator ()) on points satisfying the metric conditions:
 - d(x,y) >= 0
 - d(x,y) == 0 <=> x==y
 - d(x,y) == d(y,x) (symmetry)
 - d(x,y) <= d(x,z) + d(z,y) (triangle inequality)

Two additional methods must be implemented: 
- @e rawDistance(x,y) method provides internal distance representation
between two points. For example, a convenient way to have an exact
representation of hte Euclidean metric is to consider its square which
can be represented error free on a CInteger type for example. In this
case, the rawDistance method returns the square of the Euclidean
distance between the two points in an exact way as soon as the
internal @a RawValue type is error free and can represents sum of
squares of Point::Coordiante values.
- @e closest(a,x,y) decides which point between x and y is closest to
   a. This method is required for performance purposes.


### Refinement of
  - boost::CopyConstructible
  - boost::Assignable



### Associated types :

 - @e Space: type of space on which the metric is defined (model of CSpace).
 - @e Point: type of points associated with the underlying metric space.
 - @e Value: the value type of the metric (model of CQuantity).
 - @e RawValue: the value type for the rawDistance method  (model of CQuantity).

### Notation
 - \e X : A type that is a model of CMetricSpace
 - \e x, \e y : object of type X

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| distance computation | x(aPoint,anotherPoint) | @a aPoint and @a anotherPoint of type @a Point  |  a value of type @a Value   |              |  compute the distance between two points  |                |    -        |
| raw distance computation | x.rawDistance(aPoint,anotherPoint) | @a aPoint and @a anotherPoint of type @a Point  |  a value of type @a RawValue   |              |  compute the raw representation of the distance between two points  |                |    -        |
| closest point test | closest(aOrigin, aP, aQ) | @a aOrigin, @a aP,@a aQ of type @a aPoint |   a value of type Closest | | decide between @a aP and @a aQ which one is closer to the origin. This functions returns either DGtal::ClosestFIRST if @a aP is closer, DGtal::ClosestSECOND if @a aQ is closer  and DGtal::ClosestBOTH if both are equidistant.| | - |


### Invariants

### Models

ExactPredicateLpSeparableMetric, InexactPredicateLpSeparableMetric.

### Notes

@tparam T the type that should be a model of CMetricSpace.
 */
template <typename T>
struct CMetricSpace:  boost::CopyConstructible<T>, boost::Assignable<T>
{
    // ----------------------- Concept checks ------------------------------
public:
  typedef typename T::Point Point;
  typedef typename T::Space Space;
  typedef typename T::Value Value;
  typedef typename T::RawValue RawValue;

  BOOST_CONCEPT_ASSERT(( CSpace< Space > ));
  BOOST_CONCEPT_ASSERT(( CQuantity< Value > ));
  BOOST_CONCEPT_ASSERT(( CQuantity< RawValue > ));

  BOOST_CONCEPT_USAGE( CMetricSpace )
  {
    checkConstConstraints();
  }

  void checkConstConstraints() const
  {
    // const method dummyConst should take parameter myA of type A and return
    // something of type B
    ConceptUtils::sameType( myValue, myX.operator()( myPoint , myPoint2 ) );
    ConceptUtils::sameType( myRawValue, myX.rawDistance( myPoint , myPoint2 ) );
    ConceptUtils::sameType( myClosest, myX.closest( myPoint , myPoint2,myPoint3 ) );
 }
  // ------------------------- Private Datas --------------------------------
private:
  T myX; // do not require T to be default constructible.
  Point myPoint, myPoint2, myPoint3;
  Value myValue;
  RawValue myRawValue;
  DGtal::Closest myClosest;
    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CMetricSpace
  } //namespace concept
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CMetricSpace_h

#undef CMetricSpace_RECURSES
#endif // else defined(CMetricSpace_RECURSES)
