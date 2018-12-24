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
 * @file ITKIOTrait.h
 * @author Pierre Gueth (\c pierre.gueth@gmail.com )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/10/28
 *
 * Header file for module ITKIOTrait.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ITKIOTrait_RECURSES)
#error Recursive header files inclusion detected in ITKIOTrait.h
#else // defined(ITKIOTrait_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ITKIOTrait_RECURSES

#if !defined ITKIOTrait_h
/** Prevents repeated inclusion of headers. */
#define ITKIOTrait_h

#include "DGtal/base/BasicFunctors.h"

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class ITKIOTrait
/**
 * Description of class 'ITKIOTrait' <p>
 * \brief Aim: Provide type trait for ITK reader and ITK writer
 * @tparam Value is the value type of the DGtal image one wants to save or read using ITKWriter or ITKReader
 */
template <typename Value>
struct ITKIOTrait
{
		typedef Value ValueOut; // Associated ITK image value type
		typedef functors::Cast<ValueOut> DefaultWriteFunctor; // Default functor used by ITKWriter
		typedef functors::Cast<Value> DefaultReadFunctor; // Default functor used by ITKReader

private:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    ITKIOTrait();
    ITKIOTrait(const ITKIOTrait & other);
    ITKIOTrait& operator=(const ITKIOTrait& other);


}; // end of struct ITKIOTrait

// specialization
template <>
struct ITKIOTrait<bool>
{
		typedef unsigned char ValueOut;
		typedef functors::Cast<unsigned char> DefaultWriteFunctor;
		typedef functors::Cast<bool> DefaultReadFunctor;
};

} // namespace DGtal


#endif // !defined ITKIOTrait_h

#undef ITKIOTrait_RECURSES
#endif // else defined(ITKIOTrait_RECURSES)
