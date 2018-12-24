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
 * @file MLPLengthEstimator.h
 * @brief Computes the length of a digital curve using its MLP.
 * @author Tristan Roussillon (\c
 * tristan.roussillon@liris.cnrs.fr ) Laboratoire d'InfoRmatique en
 * Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS,
 * France
 *
 *
 * @date 2011/07/07
 *
 * Header file for module MLPLengthEstimator.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testLengthEstimators.cpp, testL1LengthEstimator.cpp
 */

#if defined(MLPLengthEstimator_RECURSES)
#error Recursive header files inclusion detected in MLPLengthEstimator.h
#else // defined(MLPLengthEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MLPLengthEstimator_RECURSES

#if !defined MLPLengthEstimator_h
/** Prevents repeated inclusion of headers. */
#define MLPLengthEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/curves/FP.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class MLPLengthEstimator
  /**
   * Description of template class 'MLPLengthEstimator' <p>
   * \brief Aim: a model of CGlobalCurveEstimator that computes
   * the length of a digital curve using its MLP (given by the FP)
   *
   * Model of CGlobalCurveGeometricEstimator
   *
   * @tparam TConstIterator a model of CConstIteratorOnPoints.
   */
  template <typename TConstIterator>
  class MLPLengthEstimator
  {
    // ----------------------- Standard services ------------------------------
  public:


    ///@todo CONCEPT CHECK sur ConstIterator
    typedef TConstIterator ConstIterator;

    typedef double Quantity;

    typedef FP<ConstIterator,int,4> FaithfulPolygon;
    typedef typename FaithfulPolygon::RealPoint Point;
    typedef typename FaithfulPolygon::RealVector Vector;

    /**
     * Default Constructor.
     */
    MLPLengthEstimator();


    /**
     * Destructor.
     */
    ~MLPLengthEstimator();


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
    void init( const double h, const ConstIterator& itb, const ConstIterator& ite, const bool& isClosed);


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

    ///polygonal representation of the input
    std::vector<Point> myRep;

    ///Boolean to make sure that init() has been called before eval().
    bool myIsInitBefore;

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    MLPLengthEstimator ( const MLPLengthEstimator & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    MLPLengthEstimator & operator= ( const MLPLengthEstimator & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class MLPLengthEstimator


  /**
   * Overloads 'operator<<' for displaying objects of class 'MLPLengthEstimator'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'MLPLengthEstimator' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const MLPLengthEstimator<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/estimation/MLPLengthEstimator.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined MLPLengthEstimator_h

#undef MLPLengthEstimator_RECURSES
#endif // else defined(MLPLengthEstimator_RECURSES)
