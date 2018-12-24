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
 * @file TwoStepLocalLengthEstimator.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/06/27
 *
 * Header file for module TwoStepLocalLengthEstimator.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testL1LengthEstimator.cpp, testLengthEstimators.cpp
 */

#if defined(TwoStepLocalLengthEstimator_RECURSES)
#error Recursive header files inclusion detected in TwoStepLocalLengthEstimator.h
#else // defined(TwoStepLocalLengthEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define TwoStepLocalLengthEstimator_RECURSES

#if !defined TwoStepLocalLengthEstimator_h
/** Prevents repeated inclusion of headers. */
#define TwoStepLocalLengthEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class TwoStepLocalLengthEstimator
  /**
   * Description of template class 'TwoStepLocalLengthEstimator' <p>
   * \brief Aim: a simple model of CGlobalCurveEstimator that compute
   * the length of a curve using the l_1 metric (just add 1/h for
   * every step).
   *
   * Model of CGlobalCurveGeometricEstimator
   *
   * @tparam TConstIterator a model of CConstIteratorOnArrows.
   */
  template <typename TConstIterator>
  class TwoStepLocalLengthEstimator
  {
    // ----------------------- Standard services ------------------------------
  public:


    ///@todo CONCEPT CHECK sur ConstIterator
    typedef TConstIterator ConstIterator;

    typedef double Quantity;


    /**
     * Default Constructor.
     */
    TwoStepLocalLengthEstimator(const double wdirect, const double wdiag):
      myWeightDirect(wdirect), myWeightDiagonal(wdiag)
    {}


    /**
     * Destructor.
     */
    ~TwoStepLocalLengthEstimator();


    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Initialize the measure computation.
     *
     * @param h grid size (must be >0).
     * @param itb begin iterator
     * @param ite end iterator
     * @param isClosed true if the input range is closed.
     */
    void init( const double h, const ConstIterator& itb,
	       const ConstIterator& ite,
	       const bool& isClosed);


    /**
     * Computation of the l1 length of the curve.
     * Complexity: O(|Range|)
     * @pre init() method must be called before.
     *
     * @return the curve length.
     */
    Quantity eval( ) const;


    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------------- Private Datas --------------------------------
  private:

    ///Grid size.
    double myH;

    ///Copy of the range.
    ConstIterator myBeginIt;
    ConstIterator myEndIt;

    ///Boolean to make sure that init() has been called before eval().
    bool myIsInitBefore;

    ///Weights
    double myWeightDirect;
    double myWeightDiagonal;


  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    TwoStepLocalLengthEstimator ( const TwoStepLocalLengthEstimator & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    TwoStepLocalLengthEstimator & operator= ( const TwoStepLocalLengthEstimator & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class TwoStepLocalLengthEstimator


  /**
   * Overloads 'operator<<' for displaying objects of class 'TwoStepLocalLengthEstimator'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'TwoStepLocalLengthEstimator' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const TwoStepLocalLengthEstimator<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/estimation/TwoStepLocalLengthEstimator.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined TwoStepLocalLengthEstimator_h

#undef TwoStepLocalLengthEstimator_RECURSES
#endif // else defined(TwoStepLocalLengthEstimator_RECURSES)
