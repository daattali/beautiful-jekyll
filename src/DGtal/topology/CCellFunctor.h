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
 * @file CCellFunctor.h
 *
 * @author Jeremy Levallois (\c jeremy.levallois@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), INSA-Lyon, France
 * LAboratoire de MAthématiques - LAMA (CNRS, UMR 5127), Université de Savoie, France
 *
 * @date 2013/02/21
 *
 * Header file for concept CCellFunctor.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CCellFunctor_RECURSES)
#error Recursive header files inclusion detected in CCellFunctor.h
#else // defined(CCellFunctor_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CCellFunctor_RECURSES

#if !defined CCellFunctor_h
/** Prevents repeated inclusion of headers. */
#define CCellFunctor_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CUnaryFunctor.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts (and in DGtal/topology)
namespace DGtal {
  namespace concepts {

  /////////////////////////////////////////////////////////////////////////////
  // class CCellFunctor
  /**
  Description of \b concept '\b CCellFunctor' <p>
  @ingroup Concepts

  @brief Aim: Defines a functor on cells.
  
  Associates values to cells.
  
  ### Refinement of CUnaryFunctor
  
  ### Associated types
  - Cell : specifies the type for a cells (inner type).
  - Quantity : specifies the type for a quantity (inner type).
  
  ### Notation
  - \a X : A type that is a model of CCellFunctor
  - \a x : Object of type \a X
  - \a c : Object of type Cell
  - \a q : Object of type Quantity
    
  ### Definitions
  
  ### Valid expressions and semantics
  
  | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
  |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|     
  |Apply function | \a x( \a c)|                     | \c q        |                  |the quantity of the function \a x at cell \a c | | |
  
  ### Invariants
  
  ### Notes###
  */
  template <typename T>
  struct CCellFunctor
  {
    // ----------------------- Concept checks ------------------------------
  public:
    typedef typename T::Cell Cell;
    typedef typename T::Quantity Quantity;
    
    BOOST_CONCEPT_ASSERT(( CUnaryFunctor<T,Cell,Quantity> ));
    
    BOOST_CONCEPT_USAGE( CCellFunctor )
    {
      check_const_constraints();
    }
    void check_const_constraints() const
    {
    }
      
    // ------------------------- Private Datas --------------------------------
  private:
    // ------------------------- Internals ------------------------------------
  private:
    T myT;
  }; // end of concept CCellFunctor
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CCellFunctor_h

#undef CCellFunctor_RECURSES
#endif // else defined(CCellFunctor_RECURSES)
