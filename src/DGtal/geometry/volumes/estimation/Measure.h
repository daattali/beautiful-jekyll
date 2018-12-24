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
 * @file Measure.h
 * @brief Computes simple measure (in the Lesbegue sens) of a set.
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/06/25
 *
 * Header file for module Measure.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testMeasureSet.cpp
 */

#if defined(Measure_RECURSES)
#error Recursive header files inclusion detected in Measure.h
#else // defined(Measure_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Measure_RECURSES

#if !defined Measure_h
/** Prevents repeated inclusion of headers. */
#define Measure_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/sets/CDigitalSet.h"
#include "DGtal/base/CowPtr.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class Measure
  /**
   * Description of template class 'Measure' <p>
   * \brief Aim: Implements a simple measure computation (in the
   * Lesbegue sens) of a set.
   * In dimension 2, it corresponds to the area of the set, to the
   * volume in dimension 3,...
   *
   * Model of CGlobalGeometricEstimator
   *
   * @tparam TSet type of set on which the geometrical moments is
   * computed.
   */
  template< typename TSet >
  class Measure
  {
    // ----------------------- Standard services ------------------------------
  public:

    typedef TSet Set;
    typedef typename TSet::Domain Domain;

    // Does not work
    //BOOST_CONCEPT_ASSERT(( CDigitalSet<TSet> ));

    typedef double Quantity;

    /**
     * Constructor.
     */
    Measure();

    /**
     * Destructor.
     */
    ~Measure();

    /**
     * Initialize the measure computation.
     *
     * @param h grid size (must be >0).
     * @param aSetPointer a pointer to an input set.
     */
    void init(const double h, const Set &aSetPointer);


    /**
     * Compute the measure (area, volume) of the set. Since we rely on
     * the Set::size() method which is O(1). The current method is
     * O(1) too.
     *
     * @pre init method must have been called before.
     *
     * @return the measure of the set.
     */
    Quantity eval() const;


    // ----------------------- Interface --------------------------------------
  public:

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



    // ------------------------- Hidden services ------------------------------
  protected:

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    Measure ( const Measure & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    Measure & operator= ( const Measure & other );

    // ------------------------- Internals ------------------------------------
  private:

    ///grid resolution parameter.
    double myH;

    ///Copy of the set size.
    typename Set::Size mySetSize;

    ///Boolean to assert that the init() was called before the eval().
    double myIsInitBefore;


  }; // end of class Measure


  /**
   * Overloads 'operator<<' for displaying objects of class 'Measure'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Measure' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const Measure<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/volumes/estimation/Measure.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Measure_h

#undef Measure_RECURSES
#endif // else defined(Measure_RECURSES)
