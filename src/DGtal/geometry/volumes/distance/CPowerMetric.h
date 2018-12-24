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
 * @file CPowerMetric.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/11/01
 *
 * Header file for concept CPowerMetric.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CPowerMetric_RECURSES)
#error Recursive header files inclusion detected in CPowerMetric.h
#else // defined(CPowerMetric_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CPowerMetric_RECURSES

#if !defined CPowerMetric_h
/** Prevents repeated inclusion of headers. */
#define CPowerMetric_h

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
// class CPowerMetric
/**
Description of \b concept '\b CPowerMetric' <p>
@ingroup Concepts
@brief Aim: defines the concept of special weighted metrics, so called
power metrics. 


### Refinement of 

  boost::CopyConstructible<T>, boost::Assignable<T>

### Associated types :
 - @e Space: type of space on which the premetric is defined (model of CSpace)
 - @e Weight: type for weights associated to the power metric (model
 of CQuantity)
 - @e Value: type for power distance value (model of CQuantity)

### Notation
 - \e X : A type that is a model of CPowerMetric
 - \e x, \e y : object of type X

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| power distance computation | x.powerDistance(aPoint, anotherPoint, anotherWeight) | @a aPoint and @a anotherPoint of type @a Point, @a aWeight  of type Weight |  a value of type @a Weight   |              |  compute the power distance between a point and a weighted point  |                |    -        |
| closest point test | closestPower(aOrigin, aP, aWp, aQ, aWq) | @a aOrigin, @a aP,@a aQ of type @a aPoint, @a aWp,@a aWq of type @a Weight |   a value of type Closest | | decide between weighted points  @a aP and @a aQ which one is closer to the origin. This functions returns either DGtal::ClosestFIRST if @a aP is closer, DGtal::ClosestSECOND if @a aQ is closer  and DGtal::ClosestBOTH if both are equidistant.| | - |
  

### Invariants

### Models

 ExactPredicateLpPowerSeparableMetric

### Notes

@tparam T the type that should be a model of CPowerMetric.
 */
template <typename T>
struct CPowerMetric: boost::CopyConstructible<T>, boost::Assignable<T>
{
    // ----------------------- Concept checks ------------------------------
public:
  typedef typename T::Space Space;
  typedef typename T::Weight Weight;
  typedef typename T::Value Value;
  typedef typename T::Point Point;
  
  BOOST_CONCEPT_ASSERT(( CSpace< Space > ));
  BOOST_CONCEPT_ASSERT(( CQuantity< Value > ));
  BOOST_CONCEPT_ASSERT(( CQuantity< Weight > ));


  BOOST_CONCEPT_USAGE( CPowerMetric )
  {
    checkConstConstraints();
  }
  
  void checkConstConstraints() const
  {
    ConceptUtils::sameType( myW3, myX.powerDistance( myPoint,  myPoint2, myW1 ) );
    ConceptUtils::sameType( aclosest, myX.closestPower( myPoint , myPoint2, myW2,myPoint3, myW3 ) );
  }
  // ------------------------- Private Datas --------------------------------
private:
  T myX; // do not require T to be default constructible.
  Point myPoint, myPoint2, myPoint3;
  Value myValue;
  Weight myW1,myW2, myW3;
  DGtal::Closest aclosest;
  // ------------------------- Internals ------------------------------------
private:

}; // end of concept CPowerMetric
}
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CPowerMetric_h

#undef CPowerMetric_RECURSES
#endif // else defined(CPowerMetric_RECURSES)
