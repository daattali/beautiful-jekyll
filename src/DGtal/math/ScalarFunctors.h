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
 * @file ScalarFunctors.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2014/09/01
 *
 * Gathers functors on scalar values (ie function objects from R to R).
 *
 * This file is part of the DGtal library.
 */

#if defined(ScalarFunctors_RECURSES)
#error Recursive header files inclusion detected in ScalarFunctors.h
#else // defined(ScalarFunctors_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ScalarFunctors_RECURSES

#if !defined ScalarFunctors_h
/** Prevents repeated inclusion of headers. */
#define ScalarFunctors_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal {
  namespace functors {

    /**
    The hat function of value v0 at 0 with a linear decrease to 0 at value r.
    A function Scalar -> Scalar.
    */
    template <typename TScalar>
    struct HatFunction {
      typedef TScalar Scalar;
      typedef Scalar argument_type;
      typedef Scalar value_type;

      Scalar myV0;
      Scalar myV0OverR;
      Scalar myR;

    public:
      HatFunction( Scalar v0, Scalar r ) 
        : myV0( v0 ), myV0OverR( v0 / r ), myR( r ) {}
      Scalar operator()( Scalar d ) const
      { // d >= 0
        ASSERT( d >= 0.0 );
        if ( d >= myR ) return 0.0;
        return myV0 - myV0OverR * d;
      }
    };

    /**
    The ball constant function of value v0 between 0 and r, 0 elsewhere.
    A function Scalar -> Scalar.
    */
    template <typename TScalar>
    struct BallConstantFunction {
      typedef TScalar Scalar;
      typedef Scalar argument_type;
      typedef Scalar value_type;

      Scalar myV0;
      Scalar myR;

    public:
      BallConstantFunction( Scalar v0, Scalar r ) 
        : myV0( v0 ), myR( r ) {}
      Scalar operator()( Scalar d ) const
      {// d >= 0
        ASSERT( d >= 0.0 );
        return ( d > myR ) ? 0.0 : myV0;
      }
    };


  } // namespace functors
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/math/ScalarFunctors.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ScalarFunctors_h

#undef ScalarFunctors_RECURSES
#endif // else defined(ScalarFunctors_RECURSES)
