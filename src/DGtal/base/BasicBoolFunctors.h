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
 * @file BasicBoolFunctors.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/10
 *
 * Defines several boolean function object wrapper types.
 *
 * This file is part of the DGtal library.
 */

#if defined(BasicBoolFunctors_RECURSES)
#error Recursive header files inclusion detected in BasicBoolFunctors.h
#else // defined(BasicBoolFunctors_RECURSES)
/** Prevents recursive inclusion of headers. */
#define BasicBoolFunctors_RECURSES

#if !defined BasicBoolFunctors_h
/** Prevents repeated inclusion of headers. */
#define BasicBoolFunctors_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <boost/function.hpp>
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::functors
namespace DGtal {
  namespace functors {

  /**
   * May hold bool functors taking no arguments.
   */
  typedef boost::function0< bool > BoolFunctor0;

  /**
   * May hold bool functors taking one bool argument.
   */
  typedef boost::function1< bool, bool > BoolFunctor1;

  /**
   * May hold bool functors taking two bool arguments.
   */
  typedef boost::function2< bool, bool, bool > BoolFunctor2;

  /**
   * May hold bool functors taking three bool arguments (Useful ?).
   */
  typedef boost::function3< bool, bool, bool, bool > BoolFunctor3;

  /**
   * Functor with no argument returning true.
   */
  struct TrueBoolFct0 {
    bool operator()() const;
  };

  /**
   * Functor with no argument returning false.
   */
  struct FalseBoolFct0 {
    bool operator()() const;
  };

  /**
   * The object function (0 bool args) returning true.
   */
  static const BoolFunctor0 trueBF0 = TrueBoolFct0();

  /**
   * The object function (0 bool args) returning false.
   */
  static const BoolFunctor0 falseBF0 = FalseBoolFct0();

  /**
   * Functor boolean identity.
   */
  struct IdentityBoolFct1 {
    bool operator()( bool b ) const;
  };

  /**
   * Functor boolean NOT.
   */
  struct NotBoolFct1 {
    bool operator()( bool b ) const;
  };

  /**
   * The object function identity (1 bool args).
   */
  static const BoolFunctor1 identityBF1 = IdentityBoolFct1();

  /**
   * The object function NOT (1 bool args).
   */
  static const BoolFunctor1 notBF1 = NotBoolFct1();

  /**
   * Functor boolean and.
   */
  struct AndBoolFct2 {
    bool operator()( bool b1, bool b2 ) const;
  };

  /**
   * Functor boolean or.
   */
  struct OrBoolFct2 {
    bool operator()( bool b1, bool b2 ) const;
  };

  /**
   * Functor boolean xor.
   */
  struct XorBoolFct2 {
    bool operator()( bool b1, bool b2 ) const;
  };

  /**
   * Functor boolean implies.
   */
  struct ImpliesBoolFct2 {
    bool operator()( bool b1, bool b2 ) const;
  };

  /**
   * The object function and (2 bool args).
   */
  static const BoolFunctor2 andBF2 = AndBoolFct2();

  /**
   * The object function or (2 bool args).
   */
  static const BoolFunctor2 orBF2 = OrBoolFct2();

  /**
   * The object function xor (2 bool args).
   */
  static const BoolFunctor2 xorBF2 = XorBoolFct2();

  /**
   * The object function implies (2 bool args).
   */
  static const BoolFunctor2 impliesBF2 = ImpliesBoolFct2();

} // namespace functors
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functors.
#include "DGtal/base/BasicBoolFunctors.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined BasicBoolFunctors_h

#undef BasicBoolFunctors_RECURSES
#endif // else defined(BasicBoolFunctors_RECURSES)
