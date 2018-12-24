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
 * @file BasicEstimatorFromSurfelsFunctors.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/05/30
 *
 * Header file for module BasicEstimatorFromSurfelsFunctors.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(BasicEstimatorFromSurfelsFunctors_RECURSES)
#error Recursive header files inclusion detected in BasicEstimatorFromSurfelsFunctors.h
#else // defined(BasicEstimatorFromSurfelsFunctors_RECURSES)
/** Prevents recursive inclusion of headers. */
#define BasicEstimatorFromSurfelsFunctors_RECURSES

#if !defined BasicEstimatorFromSurfelsFunctors_h
/** Prevents repeated inclusion of headers. */
#define BasicEstimatorFromSurfelsFunctors_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/topology/CSCellEmbedder.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace functors
  {
  template<typename TSurfel, typename TSCellEmbedder>
  struct DummyEstimatorFromSurfels
  {
  public:

    ///Surfel type
    typedef TSurfel Surfel;

    ///Embedder type
    typedef TSCellEmbedder SCellEmbedder;

    BOOST_CONCEPT_ASSERT(( concepts::CSCellEmbedder<SCellEmbedder> ));

    ///Type of output values
    typedef int Quantity;

    /**
     * Constructor.
     *
     * @param [in] anEmbedder any model of CSCellEmbedder.
     * @param [in] h a grid step
     */
    DummyEstimatorFromSurfels(ConstAlias<SCellEmbedder> anEmbedder ,
                              const double h):
      myEmbedder(&anEmbedder), myH(h)
    {
      myCpt=0;
    }

    /**
     * Destructor
     */
    ~DummyEstimatorFromSurfels() {}

    /**
     * Push a surfel to the estimator. For this dummy estimator,
     * we just count the number of surfels.
     */
    void pushSurfel(const Surfel &aSurfel,
                    const double aDistance)
    {
      BOOST_VERIFY(aDistance == aDistance);
      BOOST_VERIFY(aSurfel == aSurfel);

      myCpt++;
    }

    /**
     * @return the estimated quantity.
     */
    Quantity eval( ) const {return myCpt; }

    /**
     * Reset the estimator.
     */
    void reset()
    {
      myCpt = NumberTraits<Quantity>::ZERO;
    }

  private:

    /**
     * Private default constructor.
     */
    DummyEstimatorFromSurfels();

    ///ConstAlias of the Embedder
    const SCellEmbedder * myEmbedder;

    ///Surfel counter.
    Quantity myCpt;

    ///Grid step
    double myH;
  };
  }

} // namespace DGtal



#endif // !defined BasicEstimatorFromSurfelsFunctors_h

#undef BasicEstimatorFromSurfelsFunctors_RECURSES
#endif // else defined(BasicEstimatorFromSurfelsFunctors_RECURSES)
