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
 * @file Point2ScalarFunctors.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2014/09/01
 *
 * Header file for module Point2ScalarFunctors.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Point2ScalarFunctors_RECURSES)
#error Recursive header files inclusion detected in Point2ScalarFunctors.h
#else // defined(Point2ScalarFunctors_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Point2ScalarFunctors_RECURSES

#if !defined Point2ScalarFunctors_h
/** Prevents repeated inclusion of headers. */
#define Point2ScalarFunctors_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal {
  namespace functors {

    /**
    The hat function of value v0 at point 0 with a linear decrease to 0 at distance r.
    A function Point -> Scalar.
    */
    template <typename TPoint, typename TScalar>
    struct HatPointFunction {
      typedef TPoint Point;
      typedef TScalar Scalar;
      typedef Point argument_type;
      typedef Scalar value_type;

      Scalar myV0;
      Scalar myV0OverR;
      Scalar myR;
      Scalar myR2;

    public:
      HatPointFunction( Scalar v0, Scalar r ) 
        : myV0( v0 ), myV0OverR( v0 / r ), myR( r ), myR2( r*r ) {}
      Scalar operator()( const Point& p ) const
      {
        Scalar d = 0;
        for ( typename Point::ConstIterator it = p.begin(), itE = p.end(); it != itE; ++it )
          d += functions::square( (Scalar) *it );
        if ( d >= myR2 ) return 0.0;
        d = sqrt( d );
        return myV0 - myV0OverR * d;
      }
    };

    /**
    The ball constant function of value v0 between norm 0 and r, 0 elsewhere.
    A function Point -> Scalar.
    */
    template <typename TPoint, typename TScalar>
    struct BallConstantPointFunction {
      typedef TPoint Point;
      typedef TScalar Scalar;
      typedef Point argument_type;
      typedef Scalar value_type;

      Scalar myV0;
      Scalar myR2;

    public:
      BallConstantPointFunction( Scalar v0, Scalar r ) 
        : myV0( v0 ), myR2( r*r ) {}
      Scalar operator()( const Point& p ) const
      {
        Scalar d = 0;
        for ( typename Point::ConstIterator it = p.begin(), itE = p.end(); it != itE; ++it )
          d += functions::square( (Scalar) *it );
        return ( d > myR2 ) ? 0.0 : myV0;
      }
    };

  } // namespace functors
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/Point2ScalarFunctors.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Point2ScalarFunctors_h

#undef Point2ScalarFunctors_RECURSES
#endif // else defined(Point2ScalarFunctors_RECURSES)
