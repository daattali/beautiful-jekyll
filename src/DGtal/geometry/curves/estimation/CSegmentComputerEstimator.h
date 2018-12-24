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
 * @file CSegmentComputerEstimator.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/06/21
 *
 * Header file for concept CSegmentComputerEstimator.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CSegmentComputerEstimator_RECURSES)
#error Recursive header files inclusion detected in CSegmentComputerEstimator.h
#else // defined(CSegmentComputerEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CSegmentComputerEstimator_RECURSES

#if !defined CSegmentComputerEstimator_h
/** Prevents repeated inclusion of headers. */
#define CSegmentComputerEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/curves/estimation/CCurveLocalGeometricEstimator.h"
#include "DGtal/geometry/curves/CSegment.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  
    /////////////////////////////////////////////////////////////////////////////
    // class CSegmentComputerEstimator
    /**
       Description of \b concept '\b CSegmentComputerEstimator' <p>
       @ingroup Concepts
       @brief Aim: This concept is a refinement of CCurveLocalGeometricEstimator
       devoted to the estimation of a geometric quantiy along a segment 
       detected by a segment computer. 

       ### Refinement of 
       - CCurveLocalGeometricEstimator
       - boost::CopyConstructible
       - boost::Assignable

       ### Associated types :
       - SegmentComputer

       ### Notation
       - \e X : A type that is a model of CSegmentComputerEstimator
       - \e x : object of type X
       - \e x : object of type SegmentComputer
  
       ### Definitions

       ### Valid expressions and semantics

       | Name     | Expression          | Type requirements | Return type | Precondition | Semantics                       | Post condition | Complexity      |
       |----------|---------------------|-------------------|-------------|--------------|---------------------------------|----------------|-----------------|
       | Attach   | x.attach(s)         |                   | void        |              | Attach the segment computer     |                | constant        |                              

       ### Invariants

       ### Models

       TangentFromDSSEstimator, TangentAngleFromDSSEstimator, CurvatureFromDSSEstimator, TangentFromDCAEstimator, CurvatureFromDCAEstimator

       @see SegmentComputerEstimators

       ### Notes

       @tparam T the type that should be a model of CSegmentComputerEstimator.
    */
    template <typename T>
    struct CSegmentComputerEstimator: 
      concepts::CCurveLocalGeometricEstimator<T>, boost::CopyConstructible<T>, boost::Assignable<T>
    {
      // ----------------------- Concept checks ------------------------------
    public:

      typedef typename T::SegmentComputer SegmentComputer;
      BOOST_CONCEPT_ASSERT(( CSegment< SegmentComputer > ));

      BOOST_CONCEPT_USAGE( CSegmentComputerEstimator )
      {

        myX.attach(mySC); 

      }

      // ------------------------- Private Datas --------------------------------
    private:
      T myX;
      SegmentComputer mySC;

      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CSegmentComputerEstimator
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CSegmentComputerEstimator_h

#undef CSegmentComputerEstimator_RECURSES
#endif // else defined(CSegmentComputerEstimator_RECURSES)
