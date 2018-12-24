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
 * @file ExpressionTemplates.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/11/18
 *
 * Header file for module ExpressionTemplates.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ExpressionTemplates_RECURSES)
#error Recursive header files inclusion detected in ExpressionTemplates.h
#else // defined(ExpressionTemplates_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ExpressionTemplates_RECURSES

#if !defined ExpressionTemplates_h
/** Prevents repeated inclusion of headers. */
#define ExpressionTemplates_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

   /**
   * Template metaprogramming to compute at compilation time a power.
   */
  template <int X, unsigned exponent> class POW
  {
  public:  enum{ VALUE = X* POW<X, exponent-1>::VALUE};
  };
  template <int X > class POW<X, 1>
  {
  public:  enum{ VALUE = X };
  };
  template <int X > class POW<X, 0>
  {
  public:  enum { VALUE = 1 };
  };

  /**
   * Template metaprogramming to compute at compilation time a log2.
   */
  template <int X>
  class LOG2
  {
  public:  enum{ VALUE = 1 +  LOG2<X / 2>::VALUE};
  };
  template <> class LOG2<2>
  {
  public:  enum{ VALUE = 1 };
  };
  template <> class LOG2<1>
  {
  public:  enum{ VALUE = 0 };
  };} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ExpressionTemplates_h

#undef ExpressionTemplates_RECURSES
#endif // else defined(ExpressionTemplates_RECURSES)
