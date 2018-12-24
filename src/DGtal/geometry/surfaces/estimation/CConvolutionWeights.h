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
 * @file CConvolutionWeights.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/03/06
 *
 * Header file for concept CConvolutionWeights.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CConvolutionWeights_RECURSES)
#error Recursive header files inclusion detected in CConvolutionWeights.h
#else // defined(CConvolutionWeights_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CConvolutionWeights_RECURSES

#if !defined CConvolutionWeights_h
/** Prevents repeated inclusion of headers. */
#define CConvolutionWeights_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace deprecated
  {
    namespace concepts
    {
      /////////////////////////////////////////////////////////////////////////////
      // class CConvolutionWeights
      /**
         Description of \b concept '\b CConvolutionWeights' <p>
         @ingroup Concepts
         @brief Aim: defines models of centered convolution kernel used for normal vector integration for instance.

         CConvolutionWeights models are functor mappings displacement vectors to real values.

         @warning deprecated since 0.7

         ### Refinement of CopyConstructible, Assignable

         ### Associated types :

         - Distance: type to represent topological distances.

         ### Notation
         - \a X : A type that is a model of CConvolutionWeights
         - \a x, \a y : object of type X

         ### Definitions

         ### Valid expressions and


         | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
         |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
         | Apply function|x(v)        |v of type const Vector&| double    |                  |the value of the kernel at @e v | | O(1) |

         ### Invariants###

         ### Models###

         ConstantConvolutionWeights, GaussianConvolutionWeights

         ### Notes###

         @tparam T the type that should be a model of CConvolutionWeights.
      */
      template <typename T>
      struct CConvolutionWeights:  boost::CopyConstructible<T>, boost::Assignable<T>
        // Use derivation for coarser concepts, like
        // : CoarserConcept<T>
        // Think to boost::CopyConstructible<T>, boost::DefaultConstructible<T>, ...
        // http://www.boost.org/doc/libs/1_49_0/libs/concept_check/reference.htm
      {
        // ----------------------- Concept checks ------------------------------
      public:

        //inner type
        typedef typename T::Distance Distance;

        // 2. then check the presence of data members, operators and methods with
        BOOST_CONCEPT_USAGE( CConvolutionWeights )
        {

          DGtal::concepts::ConceptUtils::sameType( myB, myX( myA ) );
        }

        // ------------------------- Private Datas --------------------------------
      private:
        T myX; // do not require T to be default constructible.
        Distance myA;
        double myB;

        // ------------------------- Internals ------------------------------------
      private:

      }; // end of concept CConvolutionWeights
    }
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CConvolutionWeights_h

#undef CConvolutionWeights_RECURSES
#endif // else defined(CConvolutionWeights_RECURSES)
