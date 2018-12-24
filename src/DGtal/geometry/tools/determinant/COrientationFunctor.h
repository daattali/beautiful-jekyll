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
 * @file COrientationFunctor.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/12/12
 *
 * Header file for concept COrientationFunctor.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(COrientationFunctor_RECURSES)
#error Recursive header files inclusion detected in COrientationFunctor.h
#else // defined(COrientationFunctor_RECURSES)
/** Prevents recursive inclusion of headers. */
#define COrientationFunctor_RECURSES

#if !defined COrientationFunctor_h
/** Prevents repeated inclusion of headers. */
#define COrientationFunctor_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/kernel/CPointFunctor.h"
#include "DGtal/kernel/CSignedNumber.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
 namespace concepts
 {
  /////////////////////////////////////////////////////////////////////////////
  // class COrientationFunctor
  /**
     Description of \b concept '\b COrientationFunctor' <p>
     @ingroup Concepts
     @brief Aim: This concept gathers models implementing an 
     orientation test of \f$ k+1 \f$ points in a space of dimension \f$ n \f$. 

     The orientation of \f$ k+1 \f$ points \f$ (p_1, \ldots, p_{k+1}) \f$
     is given by the sign of the algebraic distance between \f$ p_{k+1} \f$ 
     and an algebraic variety, chosen such that it is uniquely defined 
     by the first \f$ k \f$ points \f$ (p_1, \ldots, p_{k}) \f$. 

     These \f$ k+1 \f$ points are provided in two steps so that this concept 
     is a refinement of CPointFunctor: 
     - First, we set the first \f$ k \f$ points by a method 'init'. 
     - Then, we look at the position of the \f$ k+1 \f$ -th point with respect
     to the first \f$ k \f$ ones: the parenthesis operator takes an input point and 
     returns a signed value.  

     The returned value, which is a model of CSignedNumber, is guaranteed to be: 
     - zero if the \f$ k+1 \f$ points belong to the same algebraic variety.
     - strictly negative if  \f$ k+1 \f$ -th point belongs to the interior of 
     the algebraic variety defined by the first \f$ k \f$ points.  
     - strictly positive if  \f$ k+1 \f$ -th point belongs to the exterior of 
     the algebraic variety defined by the first \f$ k \f$ points.  
     
     ### Refinement of CPointFunctor

     ### Associated types
     As a refinement of CPointFunctor, it has the following nested types: 
     - Point type of input points
     - Value type of the result, at least a model of CSignedNumbe
     
     In addition it has the following inner types: 
     - PointArray a model of static array of k points
     - Size type used for representing the size of the array 

     ### Notation
     - \e X : A type that is a model of COrientationFunctor
     - \e x : object of type X
     - \e a : object of type PointArray

     ### Definitions

     ### Valid expressions and semantics

     | Name            | Expression | Type requirements       | Return type | Precondition | Semantics                           | Post condition | Complexity      |
     |-----------------|------------|-------------------------|-------------|--------------|-------------------------------------|----------------|-----------------|
     | array dimension | X::size    |                         | SizeArray   |              | size of the array, equal to k       |                |                 |
     | initialization  | x.init(a)  | a is of type PointArray | void        |              | implicitely set the algebraic curve |                | model-dependent |


     ### Models
     InHalfPlaneBy2x2DetComputer InHalfPlaneBySimpleMatrix InGeneralizedDiskOfGivenRadius

     @tparam T the type that should be a model of COrientationFunctor.
  */
  template <typename T>
  struct COrientationFunctor : concepts::CPointFunctor<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:

    BOOST_CONCEPT_ASSERT(( concepts::CSignedNumber< typename T::Value > ));
    
    typedef typename T::PointArray PointArray; 
    typedef typename T::SizeArray SizeArray; 

    BOOST_CONCEPT_USAGE( COrientationFunctor )
    {
      concepts::ConceptUtils::sameType( myS, T::size ); 
      myX.init( myA );
    }
    // ------------------------- Private Datas --------------------------------
  private:
    T myX; 
    PointArray myA; 
    SizeArray myS;

  }; // end of concept COrientationFunctor
 }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined COrientationFunctor_h

#undef COrientationFunctor_RECURSES
#endif // else defined(COrientationFunctor_RECURSES)
