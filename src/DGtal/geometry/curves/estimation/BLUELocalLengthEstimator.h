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
 * @file BLUELocalLengthEstimator.h
 * @brief Implementation of Best Linear Unbiased Two (BLUE) step length estimator.
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/06/27
 *
 * Header file for module BLUELocalLengthEstimator.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testLengthEstimators.cpp
 */

#if defined(BLUELocalLengthEstimator_RECURSES)
#error Recursive header files inclusion detected in BLUELocalLengthEstimator.h
#else // defined(BLUELocalLengthEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define BLUELocalLengthEstimator_RECURSES

#if !defined BLUELocalLengthEstimator_h
/** Prevents repeated inclusion of headers. */
#define BLUELocalLengthEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/curves/estimation/TwoStepLocalLengthEstimator.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class BLUELocalLengthEstimator
  /**
   * Description of template class 'BLUELocalLengthEstimator' <p>
   * \brief Aim: Best Linear Unbiased Two step length estimator.
   *
   * @note L. Dorst & A.W.M. Smeulders "Length Estimators for
   * Digitized Contours", Computer Vision, Graphics, and Image
   * Processing, vol 40, pp.311-333, 1987
   *
   * Model of  CGlobalCurveGeometricEstimator
   *
   * @tparam TConstIterator a model of CConstIteratorOnArrows.
   */
  template <typename TConstIterator>
  class BLUELocalLengthEstimator: public DGtal::TwoStepLocalLengthEstimator<TConstIterator>
  {
    // ----------------------- Standard services ------------------------------
  public:


    ///@todo CONCEPT CHECK sur ConstIterator
    typedef TConstIterator ConstIterator;
    typedef double Quantity;


    /**
     * Default Constructor.
     */
    BLUELocalLengthEstimator():
      TwoStepLocalLengthEstimator<TConstIterator>(0.948,1.343)
    {}



    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const
    {
      out << "[BLUELocalLengthEstimator]";
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
    BLUELocalLengthEstimator ( const BLUELocalLengthEstimator & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    BLUELocalLengthEstimator & operator= ( const BLUELocalLengthEstimator & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class BLUELocalLengthEstimator


  /**
   * Overloads 'operator<<' for displaying objects of class 'BLUELocalLengthEstimator'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'BLUELocalLengthEstimator' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const BLUELocalLengthEstimator<T> & object );

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined BLUELocalLengthEstimator_h

#undef BLUELocalLengthEstimator_RECURSES
#endif // else defined(BLUELocalLengthEstimator_RECURSES)
