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
 * @file CLMSTTangentFromDSS.h
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, France
 *
 * @date 2015/09/12
 *
 * This file is part of the DGtal library.
 */

#if defined(CLMSTTangentFromDSS_RECURSES)
#error Recursive header files inclusion detected in CLMSTTangentFromDSS.h
#else // defined(CLMSTTangentFromDSS_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CLMSTTangentFromDSS_RECURSES

#if !defined CLMSTTangentFromDSS_h
/** Prevents repeated inclusion of headers. */
#define CLMSTTangentFromDSS_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "boost/concept_check.hpp"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/base/CBidirectionalRange.h"
#include "DGtal/geometry/curves/CForwardSegmentComputer.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
    
    /////////////////////////////////////////////////////////////////////////////
    // class CLMSTTangentFromDSS
    /**
     * Description of \b concept '\b CLMSTTangentFromDSS' <p>
     * @ingroup Concepts
     * @brief Aim: Defines the concept describing a functor which calculates a direction
     *        of the 2D DSS and an eccentricity \cite LachaudIVC2007 of a given point in this DSS.
     * 
     * ### Refinement of boost::DefaultConstructible<T>, boost::CopyConstructible<T>, boost::Assignable<T>
     * 
     * ### Associated types :
     *    - TDSS a 3d digital straight segment recognition algorithm
     *    - LambdaFunction @see FunctorsLambdaMST.h
     *    - Value
     *    struct Value { RealVector first; double second; Value & operator += ( const Value &); }
     * 
     * ### Notation
     * - \e T : A type that is a model of CLMSTTangentFromDSS
     * - \e x object of type X
     * 
     * ### Definitions
     * 
     * ### Valid expressions and semantics
     * 
     * | Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
     * |-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
     * | operator()|x()     |(const TDSS &, const int &, const int &)|T::Value|              | Calculates DSS direction and eccentricity of given points  in the DSS. | |model dependant|
     * 
     * ### Invariants
     * 
     * ### Models
     * 
     * - TangentFromDSS2DFunctor, TangentFromDSS3DFunctor
     * 
     * ### Notes
     * 
     * @tparam T the type that should be a model of CLMSTTangentFromDSS.
     */
    template <typename T>
    struct CLMSTTangentFromDSS : boost::DefaultConstructible<T>, boost::CopyConstructible<T>, boost::Assignable<T>
    {
      // ----------------------- Types ------------------------------
      typedef typename T::Value Value;
      typedef typename T::RealVector RealVector;
      typedef typename T::TDSS TDSS;
      // ----------------------- Concept checks ------------------------------
      BOOST_CONCEPT_ASSERT(( CForwardSegmentComputer < TDSS > ));
      BOOST_CONCEPT_ASSERT(( CBidirectionalRange < RealVector > ));
    public:
      BOOST_CONCEPT_USAGE(CLMSTTangentFromDSS)
      {
	concepts::ConceptUtils::sameType( vec, v1.first );
	concepts::ConceptUtils::sameType( d, v1.second );
	concepts::ConceptUtils::sameType( v1, x.operator()( dss, 0, 10 ) );
	concepts::ConceptUtils::sameType( v1, v1 += v2 );
      }
      void checkConstConstraints() const
      {
	ConceptUtils::sameType( v1, x.operator()( dss, 0, 10 ) );
      }
      // ------------------------- Private Datas --------------------------------
    private:
      RealVector vec;
      Value v1, v2;
      T x;
      double d;
      TDSS dss;
    }; // end of concept CLMSTTangentFromDSS
    
  } // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CLMSTTangentFromDSS_h

#undef CLMSTTangentFromDSS_RECURSES
#endif // else defined(CLMSTTangentFromDSS_RECURSES)
