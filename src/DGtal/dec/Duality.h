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
 * @file Duality.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/26
 *
 * Header file for module Duality.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Duality_RECURSES)
#error Recursive header files inclusion detected in Duality.h
#else // defined(Duality_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Duality_RECURSES

#if !defined Duality_h
/** Prevents repeated inclusion of headers. */
#define Duality_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>

#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// Duality
/**
 * Description of 'Duality' <p>
 * \brief Aim:
 * Duality enumerator tells if templated object lives in primal or dual space.
 * Used as template parameter for DEC classes.
 */
enum Duality
{
    PRIMAL = 0,
    DUAL = 1
};

template <Duality duality_orig>
struct OppositeDuality
{
};

template <>
struct OppositeDuality<PRIMAL>
{
    BOOST_STATIC_CONSTANT( Duality, duality = DUAL );
};

template <>
struct OppositeDuality<DUAL>
{
    BOOST_STATIC_CONSTANT( Duality, duality = PRIMAL );
};

/////////////////////////////////////////////////////////////////////////////
// Order
/**
 * Description of 'Order' <p>
 * \brief Aim:
 * Order is used as template parameter for DEC classes.
 */
typedef unsigned int Order;

/**
 * Overloads 'operator<<' for displaying objects of class 'Duality'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'Duality' to write.
 * @return the output stream after the writing.
 */
std::ostream&
operator<< ( std::ostream & out, const Duality& object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#if !defined(BUILD_INLINE)
#include "DGtal/dec/Duality.ih"
#endif


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Duality_h

#undef Duality_RECURSES
#endif // else defined(Duality_RECURSES)
