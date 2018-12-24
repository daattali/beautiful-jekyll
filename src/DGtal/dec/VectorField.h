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
 * @file VectorField.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/26
 *
 * Header file for module VectorField.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(VectorField_RECURSES)
#error Recursive header files inclusion detected in VectorField.h
#else // defined(VectorField_RECURSES)
/** Prevents recursive inclusion of headers. */
#define VectorField_RECURSES

#if !defined VectorField_h
/** Prevents repeated inclusion of headers. */
#define VectorField_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/dec/Duality.h"
#include "DGtal/dec/KForm.h"
#include "DGtal/kernel/PointVector.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class VectorField
  /**
   * Description of template class 'VectorField' <p>
   * \brief Aim:
   * VectorField represents a discrete vector field in the dec package.
   * Vector field values are attached to 0-cells with the same duality as the vector field.
   *
   * @tparam TCalculus should be DiscreteExteriorCalculus.
   * @tparam duality is the duality of the vector field.
   */
template <typename TCalculus, Duality duality>
  class VectorField
  {
    // ----------------------- Standard services ------------------------------
  public:
    typedef TCalculus Calculus;

    typedef typename Calculus::Scalar Scalar;
    typedef typename Calculus::SCell SCell;
    typedef typename Calculus::Index Index;
    typedef typename DGtal::PointVector<Calculus::dimensionAmbient, Scalar> Vector;

    typedef typename Calculus::DenseMatrix Coordinates;
    typedef Coordinates Container;

    /**
     * Constructor.
     * @param calculus the discrete exterior calculus to use.
     */
    VectorField(ConstAlias<Calculus> calculus);

    /**
     * Constructor.
     * @param calculus the discrete exterior calculus to use.
     * @param container the container to copy.
     */
    VectorField(ConstAlias<Calculus> calculus, const Container& container);

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    VectorField& operator=(const VectorField& other);

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
     * Get vector from index.
     * @param index of the corresponding 0-cell.
     */
    Vector getVector(const Index& index) const;

    /**
     * Set vector at index.
     * @param index of the corresponding 0-cell.
     * @param vector value of the vector field to set at this index.
     */
    void setVector(const Index& index, const Vector& vector);

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Container used to actually hold the kform data.
     */
    Coordinates myCoordinates;

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
     * Get class name string "VectorField".
     */
    std::string className() const;

    /**
     * Create zero form by projecting the vector field along basis vector.
     * @param dir direction along wich the vector field is projected.
     */
    KForm<Calculus, 0, duality> coordAlongDirection(const Dimension& dir) const;

    /**
     * Create zero from with field intensity.
     * @param norm_type norm type.
     */
    KForm<Calculus, 0, duality> intensity(const typename Vector::NormType norm_type = Vector::L_2) const;

    /**
     * Clear current vector field.
     */
    void clear();

    /**
     * Return the normalized vector field.
     * Scale vector field to norm 1 at each point.
     * @param epsilon vectors with norm lower than epsilon are set to zero.
     */
    VectorField<TCalculus, duality> normalized(const Scalar& epsilon = 0) const;

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
    VectorField();

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class VectorField


  /**
   * Overloads 'operator<<' for displaying objects of class 'VectorField'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'VectorField' to write.
   * @return the output stream after the writing.
   */
  template <typename Calculus, Duality duality>
  std::ostream&
  operator<<(std::ostream& out, const VectorField<Calculus, duality>& object);

  /**
   * Overloads 'operator+' for adding objects of class 'VectorField'.
   * @param vector_field_a left operant
   * @param vector_field_b right operant
   * @return vector_field_a + vector_field_b.
   */
  template <typename Calculus, Duality duality>
  VectorField<Calculus, duality>
  operator+(const VectorField<Calculus, duality>& vector_field_a, const VectorField<Calculus, duality>& vector_field_b);

  /**
   * Overloads 'operator-' for substracting objects of class 'VectorField'.
   * @param vector_field_a left operant
   * @param vector_field_b right operant
   * @return vector_field_a - vector_field_b.
   */
  template <typename Calculus, Duality duality>
  VectorField<Calculus, duality>
  operator-(const VectorField<Calculus, duality>& vector_field_a, const VectorField<Calculus, duality>& vector_field_b);

  /**
   * Overloads 'operator*' for scalar multiplication of objects of class 'VectorField'.
   * @param scalar left operant
   * @param vector_field right operant
   * @return scalar * vector_field.
   */
  template <typename Calculus, Duality duality>
  VectorField<Calculus, duality>
  operator*(const typename Calculus::Scalar& scalar, const VectorField<Calculus, duality>& vector_field);

  /**
   * Overloads 'operator-' for unary additive inverse of objects of class 'VectorField'.
   * @param vector_field operant
   * @return -vector_field
   */
  template <typename Calculus, Duality duality>
  VectorField<Calculus, duality>
  operator-(const VectorField<Calculus, duality>& vector_field);

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/dec/VectorField.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined VectorField_h

#undef VectorField_RECURSES
#endif // else defined(VectorField_RECURSES)
