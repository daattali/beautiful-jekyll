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
 * @file
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/06/21
 *
 * Header file for concept CGlobalGeometricEstimator.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CGlobalGeometricEstimator_RECURSES)
#error Recursive header files inclusion detected in CGlobalGeometricEstimator.h
#else // defined(CGlobalGeometricEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CGlobalGeometricEstimator_RECURSES

#if !defined CGlobalGeometricEstimator_h
/** Prevents repeated inclusion of headers. */
#define CGlobalGeometricEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CQuantity.h"
#include <boost/iterator/iterator_archetypes.hpp>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
    /////////////////////////////////////////////////////////////////////////////
    // class CGlobalGeometricEstimator
    /**
       Description of \b concept '\b CGlobalGeometricEstimator' <p>
       @ingroup Concepts
       @brief Aim: This concept describes an object that can process 
       a range so as to return one estimated quantity for the whole range. 

       ### Refinement of 
       - boost::DefaultConstructible

       ### Associated types :
       - ConstIterator 
       - Quantity

       ### Notation
       - \e X : A type that is a model of CGlobalGeometricEstimator
       - \e x : object of type X
       - \e h : double
       - \e itb, ite, it : objects of type ConstIterator
       - \e ito : an instance of a model of output iterator having Quantity as value type
 
       ### Definitions

       ### Valid expressions and semantics

       | Name           | Expression            |   | Return type | Precondition | Semantics                          |   | Complexity      |
       |----------------|-----------------------|---|-------------|--------------|------------------------------------|---|-----------------|
       | Initialization | x.init( h, itb, ite ) |   | void        | h > 0        | Grid step and range initialization |   | constant        |
       | Evaluation     | x.eval( )             |   | Quantity    |              | Estimation of the quantity         |   | model dependant |

       ### Invariants

       ### Models

       TrueGlobalEstimatorOnPoints L1LengthEstimator TwoStepLocalLengthEstimator
       DSSLengthEstimator FPLengthEstimator MLPLengthEstimator 

       ### Notes

       @tparam T the type that should be a model of CGlobalGeometricEstimator.
    */
    template <typename T>
    struct CGlobalGeometricEstimator: 
      boost::DefaultConstructible<T>
    {

      // ----------------------- Concept checks ------------------------------
    public:

      typedef typename T::Quantity Quantity;
      BOOST_CONCEPT_ASSERT(( concepts::CQuantity< Quantity > ));

      typedef typename T::ConstIterator ConstIterator;
      BOOST_CONCEPT_ASSERT(( boost_concepts::ReadableIteratorConcept< ConstIterator > ));
      BOOST_CONCEPT_ASSERT(( boost_concepts::ForwardTraversalConcept< ConstIterator > ));


      BOOST_CONCEPT_USAGE( CGlobalGeometricEstimator )
      {
        //init method
        myX.init( myH, myItb, myIte ); 

        ConceptUtils::sameType( myQ, myX.eval( ) );
      }

      // ------------------------- Private Datas --------------------------------
    private:
      T myX;
    
      double myH; 
      ConstIterator myItb, myIte; 
      Quantity myQ;

      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CGlobalGeometricEstimator
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CGlobalGeometricEstimator_h

#undef CGlobalGeometricEstimator_RECURSES
#endif // else defined(CGlobalGeometricEstimator_RECURSES)
