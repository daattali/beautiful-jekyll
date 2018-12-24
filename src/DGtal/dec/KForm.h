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
 * @file KForm.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/26
 *
 * Header file for module KForm.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(KForm_RECURSES)
#error Recursive header files inclusion detected in KForm.h
#else // defined(KForm_RECURSES)
/** Prevents recursive inclusion of headers. */
#define KForm_RECURSES

#if !defined KForm_h
/** Prevents repeated inclusion of headers. */
#define KForm_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/base/Clone.h"
#include "DGtal/dec/Duality.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class KForm
  /**
   * Description of template class 'KForm' <p>
   * \brief Aim:
   * KForm represents discrete kforms in the dec package.
   *
   * @tparam TCalculus should be DiscreteExteriorCalculus.
   * @tparam order is the order of the kform.
   * @tparam duality is the duality of the kform.
   */
  template <typename TCalculus, Order order, Duality duality>
  class KForm
  {
    // ----------------------- Standard services ------------------------------
  public:
    typedef TCalculus Calculus;

    BOOST_STATIC_ASSERT(( order >= 0 ));
    BOOST_STATIC_ASSERT(( order <= Calculus::dimensionEmbedded ));

    typedef typename Calculus::DenseVector Container;
    typedef typename Calculus::Scalar Scalar;
    typedef typename Calculus::SCell SCell;
    typedef typename Calculus::Index Index;

    /**
     * Create a kform with all values initialized to 1.
     * @param calculus the discrete exterior calculus to use.
     */
    static
    KForm<TCalculus, order, duality>
    ones(ConstAlias<Calculus> calculus);

    /**
     * Create a kform with all values initialized to 0.
     * Convenience wrapper for default constructor.
     * @param calculus the discrete exterior calculus to use.
     */
    static
    KForm<TCalculus, order, duality>
    zeros(ConstAlias<Calculus> calculus);

    /**
     * Create a kform with all values initialized to 0, except value associated with cell initialized to 1.
     * @param calculus the discrete exterior calculus to use.
     * @param cell Dirac position.
     */
    static
    KForm<TCalculus, order, duality>
    dirac(ConstAlias<Calculus> calculus, const typename Calculus::Cell& cell);

    /**
     * Constructor.
     * @param calculus the discrete exterior calculus to use.
     */
    KForm(ConstAlias<Calculus> calculus);

    /**
     * Constructor.
     * @param calculus the discrete exterior calculus to use.
     * @param container the container to copy.
     */
    KForm(ConstAlias<Calculus> calculus, const Container& container);

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    KForm& operator=(const KForm& other);

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Container used to actually hold the kform data.
     */
    Container myContainer;

    /**
     * Pointer to const calculus.
     */
    const Calculus* myCalculus;

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay(std::ostream& out) const;

    /**
     * Get class name string "KForm".
     */
    std::string className() const;

    /**
     * Clear current k-form.
     */
    void clear();

    /**
     * Get signed k-cell from index.
     * @param index the index.
     * @return associated Khalimsky cell.
     */
    SCell getSCell(const Index& index) const;

    /**
     * Get k-form length.
     * @return k-form length.
     */
    Index length() const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    KForm();

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class KForm

  /**
   * Overloads 'operator<<' for displaying objects of class 'KForm'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'KForm' to write.
   * @return the output stream after the writing.
   */
  template <typename Calculus, Order order, Duality duality>
  std::ostream&
  operator<<(std::ostream& out, const KForm<Calculus, order, duality>& object);

  /**
   * Overloads 'operator+' for adding objects of class 'KForm'.
   * @param form_a left operant
   * @param form_b right operant
   * @return form_a + form_b.
   */
  template <typename Calculus, Order order, Duality duality>
  KForm<Calculus, order, duality>
  operator+(const KForm<Calculus, order, duality>& form_a, const KForm<Calculus, order, duality>& form_b);

  /**
   * Overloads 'operator-' for substracting objects of class 'KForm'.
   * @param form_a left operant
   * @param form_b right operant
   * @return form_a - form_b.
   */
  template <typename Calculus, Order order, Duality duality>
  KForm<Calculus, order, duality>
  operator-(const KForm<Calculus, order, duality>& form_a, const KForm<Calculus, order, duality>& form_b);

  /**
   * Overloads 'operator*' for scalar multiplication of objects of class 'KForm'.
   * @param scalar left operant
   * @param form right operant
   * @return scalar * form.
   */
  template <typename Calculus, Order order, Duality duality>
  KForm<Calculus, order, duality>
  operator*(const typename Calculus::Scalar& scalar, const KForm<Calculus, order, duality>& form);

  /**
   * Overloads 'operator-' for unary additive inverse of objects of class 'KForm'.
   * @param form operant
   * @return -form.
   */
  template <typename Calculus, Order order, Duality duality>
  KForm<Calculus, order, duality>
  operator-(const KForm<Calculus, order, duality>& form);

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/dec/KForm.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined KForm_h

#undef KForm_RECURSES
#endif // else defined(KForm_RECURSES)
