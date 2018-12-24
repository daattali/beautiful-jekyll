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
 * @file CDigitalMetricSpace.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/06/29
 *
 * Header file for concept CDigitalMetricSpace.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDigitalMetricSpace_RECURSES)
#error Recursive header files inclusion detected in CDigitalMetricSpace.h
#else // defined(CDigitalMetricSpace_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDigitalMetricSpace_RECURSES

#if !defined CDigitalMetricSpace_h
/** Prevents repeated inclusion of headers. */
#define CDigitalMetricSpace_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/geometry/volumes/distance/CMetricSpace.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
 namespace concepts
  {
 
/////////////////////////////////////////////////////////////////////////////
// class CDigitalMetricSpace
/**
Description of \b concept '\b CDigitalMetricSpace' <p>
@ingroup Concepts
@brief Aim: defines the concept of digital metric spaces.

CDigitalMetricSpace is a refinement of CMetricSpace such that the
value type of the distance function is an Integer type (model of
CInteger).


### Refinement of
  - CMetricSpace


### Associated types :

 - @e Space: type of space on which the metric is defined (model of CSpace)
 - @e Point: type of points associated with the underlying metric space.
 - @e Value: the value type of the metric (model of CInteger)
 - @e RawValue: the value type for the rawDistance method (model of CInteger)

### Notation
 - \e X : A type that is a model of CDigitalMetricSpace
 - \e x, \e y : object of type X

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
|       |            |                   |               |              |           |                |            | 

### Invariants

### Models

### Notes

@tparam T the type that should be a model of CDigitalMetricSpace.
 */
    template <typename T>
    struct CDigitalMetricSpace: concepts::CMetricSpace<T>
    {
      // ----------------------- Concept checks ------------------------------
    public:
      typedef typename T::Point Point;
      typedef typename T::Space Space;
      typedef typename T::Value Value;
      typedef typename T::RawValue RawValue;

      BOOST_CONCEPT_ASSERT(( CInteger< Value > ));
      BOOST_CONCEPT_ASSERT(( CInteger< RawValue > ));


      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CDigitalMetricSpace

} // namespace concepts

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDigitalMetricSpace_h

#undef CDigitalMetricSpace_RECURSES
#endif // else defined(CDigitalMetricSpace_RECURSES)
