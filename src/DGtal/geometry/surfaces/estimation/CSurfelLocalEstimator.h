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
 * @file CSurfelLocalEstimator.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2014/04/01
 *
 * Header file for concept CSurfelLocalEstimator.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CSurfelLocalEstimator_RECURSES)
#error Recursive header files inclusion detected in CSurfelLocalEstimator.h
#else // defined(CSurfelLocalEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CSurfelLocalEstimator_RECURSES

#if !defined CSurfelLocalEstimator_h
/** Prevents repeated inclusion of headers. */
#define CSurfelLocalEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <boost/iterator/iterator_archetypes.hpp>
#include "DGtal/base/Common.h"
#include "DGtal/base/CQuantity.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal {
  namespace concepts {

  /////////////////////////////////////////////////////////////////////////////
  // class CSurfelLocalEstimator
  /**
  *  Description of \b concept '\b CSurfelLocalEstimator' <p>
  *  @ingroup Concepts
  *
  *  @brief Aim: This concept describes an object that can process a
  *  range of surfels (that are supposed to belong to some (abstract)
  *  surface) so as to return one estimated quantity for each element
  *  of the range (or a given subrange).
  *
  * It is rather general in the sense that it does not impose a type
  * for the shape under study. It may be a digital surface, a point
  * predicate that defines implicitly a digital shape, an implicit
  * function, etc. This concept has refinements specifying some
  * cases.
  *
  *  ### Refinement of 
  *  - boost::DefaultConstructible,  boost::CopyConstructible, boost::Assignable
  *
  *  ### Associated types :
  *  - Surfel : the type of elements of the surface
  *  - Quantity : the type of the (geometric) quantity that is estimated, must be a model of CQuantity.
  *
  *  ### Notation
  *  - \e X : A type that is a model of CSurfelLocalEstimator
  *  - \e x : object of type \e X
  *  - \e h : double
  *  - \e itb, \e ite, \e it,\e itb2, \e ite2 : instances of a model of forward iterators having Surfel as value type.
  *  - \e ito : an instance of a model of output iterator having Quantity as value type
  *
  *  ### Definitions
  *
  *  ### Valid expressions and semantics
  *
  *  | Name           | Expression                    |   | Return type                  | Precondition | Semantics                                 |   | Complexity      |
  *  |----------------|-------------------------------|---|------------------------------|--------------|-------------------------------------------|---|-----------------|
  *  | Initialization | x.init( \e h, \e itb, \e ite )|   | void                         | \e h > 0     | Grid step and range initialization in [\e itb,\e ite) |   | model dependent |
  *  | Evaluation     | x.eval( \e it )               |   | Quantity                     |              | Estimation of the quantity at \e \e it, which must belong to [\e itb,\e ite) |   | model dependent |
  *  | Evaluation     | \e ito = x.eval( \e itb2, \e ite2, \e ito ) |   | a model of output iterator |  | Estimation for each element of [\e itb2, \e ite2), which must be a subrange of or the whole range [\e itb,\e ite) |   | model dependent |
  *  | gridstep  accessor | x.h()                     |   | double                       |              | Accessor to the gridstep  value           |   | O(1)            |
  *
  *  ### Invariants
  *
  *  ### Models
  *
  *  - TrueDigitalSurfaceLocalEstimator, VCMDigitalSurfaceLocalEstimator, IntegralInvariantCovarianceEstimator, IntegralInvariantVolumeEstimator
  *
  *  ### Notes
  *
  *  @tparam T the type that should be a model of CSurfelLocalEstimator.
  */
  template <typename T>
  struct CSurfelLocalEstimator
    : boost::DefaultConstructible<T>,  boost::CopyConstructible<T>, boost::Assignable<T>
  {

    // ----------------------- Concept checks ------------------------------
  public:

    typedef typename T::Quantity Quantity;
    BOOST_CONCEPT_ASSERT(( CQuantity< Quantity > ));
    typedef typename T::Surfel Surfel;

    BOOST_CONCEPT_USAGE( CSurfelLocalEstimator )
    {
      //init method
      myX.init( myH, myItb, myIte ); 

      ConceptUtils::sameType( myQ, myX.eval( myItb ) );
      ConceptUtils::sameType( myIto, myX.eval( myItb, myIte, myIto ) );
      check_const_constraints();
    }
    void check_const_constraints() const
    {
      ConceptUtils::sameType( myH, myX.h() );
    }

    // ------------------------- Private Datas --------------------------------
  private:
    T myX;
    
    double myH; 
    Quantity myQ;
    boost::iterator_archetype<Surfel,
			      boost::iterator_archetypes::readable_iterator_t,
			      boost::forward_traversal_tag > myItb, myIte; 
    boost::iterator_archetype<Quantity,
			      boost::iterator_archetypes::writable_iterator_t,
			      boost::incrementable_traversal_tag > myIto; 

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of concept CSurfelLocalEstimator

} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CSurfelLocalEstimator_h

#undef CSurfelLocalEstimator_RECURSES
#endif // else defined(CSurfelLocalEstimator_RECURSES)
