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
 * @file RosenProffittLocalLengthEstimator.h
 * @brief Computes length using Rosen-Proffitt Length Estimator.
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/06/27
 *
 * Header file for module RosenProffittLocalLengthEstimator.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testLengthEstimators.cpp
 */

#if defined(RosenProffittLocalLengthEstimator_RECURSES)
#error Recursive header files inclusion detected in RosenProffittLocalLengthEstimator.h
#else // defined(RosenProffittLocalLengthEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define RosenProffittLocalLengthEstimator_RECURSES

#if !defined RosenProffittLocalLengthEstimator_h
/** Prevents repeated inclusion of headers. */
#define RosenProffittLocalLengthEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/curves/estimation/TwoStepLocalLengthEstimator.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class RosenProffittLocalLengthEstimator
  /**
   * Description of template class 'RosenProffittLocalLengthEstimator' <p>
   * \brief Aim: Rosen-Proffitt Length Estimator.
   *
   * @note   T. J. Ellis and D. Proffitt and D. Rosen and W. Rutkowski
   * Measurement of the lengths of digitized curved lines
   * Computer Graphics and Image Processing, Vol. 10, pp. 333-347, August 1979
   *
   * Model of  CGlobalCurveGeometricEstimator
   *
   * @tparam TConstIterator a model of CConstIteratorOnArrows.
   */
  template <typename TConstIterator>
  class RosenProffittLocalLengthEstimator: public DGtal::TwoStepLocalLengthEstimator<TConstIterator>
  {
    // ----------------------- Standard services ------------------------------
  public:


    ///@todo CONCEPT CHECK sur ConstIterator
    typedef TConstIterator ConstIterator;
    typedef double Quantity;


    /**
     * Default Constructor.
     */
    RosenProffittLocalLengthEstimator():
      TwoStepLocalLengthEstimator<TConstIterator>(M_PI*(sqrt(2.0f)+1.0)/8.0,
              M_PI*(sqrt(2.0f)+2.0)/16.0)
    {}



    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const
    {
      out << "[RosenProffittLocalLengthEstimator]";
      if (this->myIsInitBefore)
  out <<" myH="<< this->myH;
      else
  out<< " not initialized";
  }


  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    RosenProffittLocalLengthEstimator ( const RosenProffittLocalLengthEstimator & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    RosenProffittLocalLengthEstimator & operator= ( const RosenProffittLocalLengthEstimator & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class RosenProffittLocalLengthEstimator


  /**
   * Overloads 'operator<<' for displaying objects of class 'RosenProffittLocalLengthEstimator'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'RosenProffittLocalLengthEstimator' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const RosenProffittLocalLengthEstimator<T> & object );

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined RosenProffittLocalLengthEstimator_h

#undef RosenProffittLocalLengthEstimator_RECURSES
#endif // else defined(RosenProffittLocalLengthEstimator_RECURSES)
