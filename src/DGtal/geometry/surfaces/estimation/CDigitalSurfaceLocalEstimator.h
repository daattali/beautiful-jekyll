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
 * @file CDigitalSurfaceLocalEstimator.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2014/04/01
 *
 * Header file for concept CDigitalSurfaceLocalEstimator.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDigitalSurfaceLocalEstimator_RECURSES)
#error Recursive header files inclusion detected in CDigitalSurfaceLocalEstimator.h
#else // defined(CDigitalSurfaceLocalEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDigitalSurfaceLocalEstimator_RECURSES

#if !defined CDigitalSurfaceLocalEstimator_h
/** Prevents repeated inclusion of headers. */
#define CDigitalSurfaceLocalEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/topology/CDigitalSurfaceContainer.h"
#include "DGtal/geometry/surfaces/estimation/CSurfelLocalEstimator.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal {
  namespace concepts {

  /////////////////////////////////////////////////////////////////////////////
  // class CDigitalSurfaceLocalEstimator
  /**
  *  Description of \b concept '\b CDigitalSurfaceLocalEstimator' <p>
  *  @ingroup Concepts
  *
  *  @brief Aim: This concept describes an object that can process a
  *  range over some generic digital surface so as to return one
  *  estimated quantity for each element of the range (or a given
  *  subrange). 
  *
  *  It refines the concept CSurfelLocalEstimator by forcing the
  *  abstract surface to be some digital surface.
  *
  *  ### Refinement of 
  *  - CSurfelLocalEstimator
  *
  *  ### Associated types :
  *  - Surface : the type of digital surface, some DigitalSurface<T> where T is a model of CDigitalSurfaceContainer.
  *  - Surfel (from CSurfelLocalEstimator) and type Surface::Surfel must be the same
  *
  *  ### Notation
  *  - \e X : A type that is a model of CDigitalSurfaceLocalEstimator
  *  - \e x : object of type \e X
  *  - \e s : an instance of Surface
  *
  *  ### Definitions
  *
  *  ### Valid expressions and semantics
  *
  *  | Name           | Expression                    |   | Return type                  | Precondition | Semantics                                 |   | Complexity      |
  *  |----------------|-------------------------------|---|------------------------------|--------------|-------------------------------------------|---|-----------------|
  *  | Attach surface | \e x.attach( \e s )           |   | \c void                      |              | Indicates to the estimator the surface on which estimations are done. | | Model dependent |
  *
  *  ### Invariants
  *
  *  ### Models
  *
  *  - VCMDigitalSurfaceLocalEstimator.
  *  - LocalEstimatorFromSurfelFunctorAdapter.
  *  - IntegralInvariantVolumeEstimator.
  *  - IntegralInvariantCovarianceEstimator.
  *
  *  ### Notes
  *  - A surface must be attached to \e x before the call to \c init and \c eval.
  *
  *  @tparam T the type that should be a model of CDigitalSurfaceLocalEstimator.
  */
  template <typename T>
  struct CDigitalSurfaceLocalEstimator
    : CSurfelLocalEstimator<T>
  {

    // ----------------------- Concept checks ------------------------------
  public:

    typedef typename T::Surface Surface;
    typedef typename Surface::DigitalSurfaceContainer DigitalSurfaceContainer;
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSurfaceContainer< DigitalSurfaceContainer > ));
    typedef typename T::Surfel Surfel;
    BOOST_STATIC_ASSERT(( ConceptUtils::SameType< Surfel, typename Surface::Surfel >::value ));
    BOOST_CONCEPT_USAGE( CDigitalSurfaceLocalEstimator )
    {
      myX.attach( myS );
    }

    // ------------------------- Private Datas --------------------------------
  private:
    T myX;
    Surface myS;

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of concept CDigitalSurfaceLocalEstimator

} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDigitalSurfaceLocalEstimator_h

#undef CDigitalSurfaceLocalEstimator_RECURSES
#endif // else defined(CDigitalSurfaceLocalEstimator_RECURSES)
