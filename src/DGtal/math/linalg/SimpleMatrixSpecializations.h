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
 * @file SimpleMatrixSpecializations.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/07/19
 *
 * Header file for module SimpleMatrixSpecializations.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SimpleMatrixSpecializations_RECURSES)
#error Recursive header files inclusion detected in SimpleMatrixSpecializations.h
#else // defined(SimpleMatrixSpecializations_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SimpleMatrixSpecializations_RECURSES

#if !defined SimpleMatrixSpecializations_h
/** Prevents repeated inclusion of headers. */
#define SimpleMatrixSpecializations_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/math/linalg/SimpleMatrix.h"
#include "DGtal/kernel/NumberTraits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{


  /////////////////////////////////////////////////////////////////////////////
  // template class SimpleMatrixSpecializations
  /**
   * Description of template class 'SimpleMatrixSpecializations' <p>
   * \brief Aim: Implement internal matrix services for specialized
   * matrix size.
   *
   * Determiant of a matrix and determinant of a minor of the
   * matrix are specialized for 2x2 and 3x3 matrices.
   *
   * @tparam TMatrix a type of matrix
   * @tparam TM number of rows
   * @tparam TN number of columns
   */
  template <typename TMatrix, DGtal::Dimension TM, DGtal::Dimension TN>
  struct SimpleMatrixSpecializations
  {
    // ----------------------- Standard services ------------------------------

    ///Matrix componenets type
    typedef typename TMatrix::Component Component;
    ///Matrix type
    typedef TMatrix Matrix;

    BOOST_STATIC_ASSERT( TM == TMatrix::M );
    BOOST_STATIC_ASSERT( TN == TMatrix::N );

    /**
     * Return the minor determinant (i,j) of the current matrix
     *
     * @param M the matrix
     * @param i row index
     * @param j column index
     *
     * @return the minor (i,j)
     */
    static Component minorDeterminant(const Matrix &M,
                                      const DGtal::Dimension i,
                                      const DGtal::Dimension j);

    /**
     * Returns the determinant of square matrix.
     * Slow method for large matrices.
     * @pre this must be NxN
     *
     * @return the determinant.
     */
    static Component determinant(const Matrix &M);


  }; // end of class SimpleMatrixSpecializations

  /////////////////////////////////////////////////////////////////////////////
  // template class SimpleMatrixSpecializations
  /**
   * Description of template class 'SimpleMatrixSpecializations' <p>
   * \brief Aim:
   */
  template <typename TMatrix>
  struct SimpleMatrixSpecializations<TMatrix,2,2>
  {
    // ----------------------- Standard services ------------------------------
  public:

    typedef typename TMatrix::Component Component;
    typedef TMatrix Matrix;

    BOOST_STATIC_ASSERT( 2 == TMatrix::M );
    BOOST_STATIC_ASSERT( 2 == TMatrix::N );

    /**
     * Return the minor determinant (i,j) of the current matrix
     *
     * @param aM  the matrix
     * @param i row index
     * @param j column index
     *
     * @return the minor (i,j)
     */
    static Component minorDeterminant(const Matrix &aM,
                                      const DGtal::Dimension i,
                                      const DGtal::Dimension j);

    /**
     * Returns the determinant of square matrix.
     * Slow method for large matrices.
     * @pre this must be NxN
     *
     * @return the determinant.
     */
    static Component determinant(const Matrix &aM);


  }; // end of class SimpleMatrixSpecializations
  /////////////////////////////////////////////////////////////////////////////
  // template class SimpleMatrixSpecializations
  /**
   * Description of template class 'SimpleMatrixSpecializations' <p>
   * \brief Aim:
   */
  template <typename TMatrix>
  struct SimpleMatrixSpecializations<TMatrix,1,1>
  {
    // ----------------------- Standard services ------------------------------
  public:

    typedef typename TMatrix::Component Component;
    typedef TMatrix Matrix;

    BOOST_STATIC_ASSERT( 1 == TMatrix::M );
    BOOST_STATIC_ASSERT( 1 == TMatrix::N );

    /**
     * Return the minor determinant (i,j) of the current matrix
     *
     * @param aM  the matrix.
     * @param i row index
     * @param j column index
     *
     * @return the minor (i,j)
     */
    static Component minorDeterminant(const Matrix &aM,
                                      const DGtal::Dimension i,
                                      const DGtal::Dimension j);

    /**
     * Returns the determinant of square matrix.
     * Slow method for large matrices.
     * @pre this must be NxN
     *
     * @return the determinant.
     */
    static Component determinant(const Matrix &aM);


  }; // end of class SimpleMatrixSpecializations

  /////////////////////////////////////////////////////////////////////////////
  // template class SimpleMatrixSpecializations
  /**
   * Description of template class 'SimpleMatrixSpecializations' <p>
   * \brief Aim:
   */
  template <typename TMatrix>
  struct SimpleMatrixSpecializations<TMatrix,3,3>
  {
    // ----------------------- Standard services ------------------------------
  public:

    typedef typename TMatrix::Component Component;
    typedef TMatrix Matrix;

    BOOST_STATIC_ASSERT( 3 == TMatrix::M );
    BOOST_STATIC_ASSERT( 3 == TMatrix::N );

    /**
     * Return the minor determinant (i,j) of the current matrix
     *
     * @param M the matrix
     * @param i row index
     * @param j column index
     *
     * @return the minor (i,j)
     */
    static Component minorDeterminant(const Matrix &M,
                                      const DGtal::Dimension i,
                                      const DGtal::Dimension j);

    /**
     * Returns the determinant of square matrix.
     * Slow method for large matrices.
     * @pre this must be NxN
     *
     * @return the determinant.
     */
    static Component determinant(const Matrix &M);


  }; // end of class SimpleMatrixSpecializations

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/math/linalg/SimpleMatrixSpecializations.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SimpleMatrixSpecializations_h

#undef SimpleMatrixSpecializations_RECURSES
#endif // else defined(SimpleMatrixSpecializations_RECURSES)
