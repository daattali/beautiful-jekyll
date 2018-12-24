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
 * @file DSSLengthEstimator.h
 * @brief Segments the digital curve into DSS and computes the length of the
 * resulting polygon.
 *
 * @author Tristan Roussillon (\c
 * tristan.roussillon@liris.cnrs.fr ) Laboratoire d'InfoRmatique en
 * Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS,
 * France
 *
 *
 * @date 2011/07/07
 *
 * Header file for module DSSLengthEstimator.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testLengthEstimator.cpp, testL1LengthEstimator.cpp
 */

#if defined(DSSLengthEstimator_RECURSES)
#error Recursive header files inclusion detected in DSSLengthEstimator.h
#else // defined(DSSLengthEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DSSLengthEstimator_RECURSES

#if !defined DSSLengthEstimator_h
/** Prevents repeated inclusion of headers. */
#define DSSLengthEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//#include "DGtal/base/IteratorTraits.h"
#include "DGtal/geometry/curves/GreedySegmentation.h"
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class DSSLengthEstimator
  /**
   * Description of template class 'DSSLengthEstimator' <p>
   * \brief Aim: a model of CGlobalCurveEstimator that
   * segments the digital curve into DSS and computes
   * the length of the resulting (not uniquely defined)
   * polygon.
   *
   * Model of CGlobalCurveGeometricEstimator
   *
   * @tparam TConstIterator a model of CConstIteratorOnPoints.
   */
  template <typename TConstIterator>
  class DSSLengthEstimator
  {
    // ----------------------- Standard services ------------------------------
  public:


    ///@todo CONCEPT CHECK sur ConstIterator
    typedef TConstIterator ConstIterator;

    typedef double Quantity;

    typedef ArithmeticalDSSComputer<ConstIterator,int,4> DSSComputer;
    typedef typename DSSComputer::Point Point;
    typedef typename DSSComputer::Vector Vector;

    /**
     * Default Constructor.
     */
    DSSLengthEstimator();


    /**
     * Destructor.
     */
    ~DSSLengthEstimator();


    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Initialize the measure computation.
     *
     * @param h grid size (must be >0).
     * @param itb begin iterator
     * @param ite end iterator
     */
    void init( const double h, const ConstIterator& itb, const ConstIterator& ite);


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
    DSSLengthEstimator ( const DSSLengthEstimator & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    DSSLengthEstimator & operator= ( const DSSLengthEstimator & other );

    // ------------------------- Internals ------------------------------------
  private:

    Point lastPoint (const ConstIterator& ite);
    Point lastPoint (const ConstIterator& c, CirculatorType);
    Point lastPoint (const ConstIterator& ite, IteratorType);

  }; // end of class DSSLengthEstimator


  /**
   * Overloads 'operator<<' for displaying objects of class 'DSSLengthEstimator'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'DSSLengthEstimator' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const DSSLengthEstimator<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/estimation/DSSLengthEstimator.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DSSLengthEstimator_h

#undef DSSLengthEstimator_RECURSES
#endif // else defined(DSSLengthEstimator_RECURSES)
