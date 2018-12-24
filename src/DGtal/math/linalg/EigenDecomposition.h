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
 * @file EigenDecomposition.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 * @author Jérémy Levallois (\c jeremy.levallois@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), INSA-Lyon, France
 * LAboratoire de MAthématiques - LAMA (CNRS, UMR 5127), Université de Savoie, France
 *
 * @date 2014/02/27
 *
 * This file provides methods to compute the eigen decomposition of a
 * matrix. Its objective is to replace a specialized matrix library
 * when none are available.
 *
 * This is derived from the Algol procedures tred2 and tql2 by Bowdler, Martin, Reinsch
 * and Wilkinson, Handbook for Auto. Comp., Vol.ii-Linear Algebra, and the corresponding
 * Fortran subroutine in EISPACK.
 *
 * This file is part of the DGtal library.
 */

#if defined(EigenDecomposition_RECURSES)
#error Recursive header files inclusion detected in EigenDecomposition.h
#else // defined(EigenDecomposition_RECURSES)
/** Prevents recursive inclusion of headers. */
#define EigenDecomposition_RECURSES

#if !defined EigenDecomposition_h
/** Prevents repeated inclusion of headers. */
#define EigenDecomposition_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/math/linalg/SimpleMatrix.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // template class EigenDecomposition
  /**
   * Description of template class 'EigenDecomposition' <p> \brief
   * Aim: This class provides methods to compute the eigen
   * decomposition of a matrix. Its objective is to replace a
   * specialized matrix library when none are available.
   *
   * This class provides static services and is not really supposed to
   * be instantiated.
   *
   * @note This is derived from the Algol procedures tred2 and tql2 by
   * Bowdler, Martin, Reinsch and Wilkinson, Handbook for Auto. Comp.,
   * Vol.ii-Linear Algebra, and the corresponding Fortran subroutine
   * in EISPACK.
   *
   *
   * @tparam TN the size TN of the matrix TN x TN.
   *
   * @tparam TComponent the type of each component of the matrix. For
   * now, should be some double or float type.
   * 
   * @tparam TMatrix a model of CMatrix, for instance SimpleMatrix.
   */
   
  template  <DGtal::Dimension TN, typename TComponent, typename TMatrix=SimpleMatrix<TComponent, TN, TN> >
  class EigenDecomposition
  {
    // BOOST_CONCEPT_ASSERT(( CMatrix<TMatrix> ));
    BOOST_CONCEPT_ASSERT(( concepts::CEuclideanRing<TComponent> ));
    BOOST_STATIC_ASSERT(TN > 0 );

    // ----------------------- Public types -----------------------------------
  public:
    typedef TComponent Component;                    ///< the type of each coefficient, i.e. scalar
    static const DGtal::Dimension M = TN;
    static const DGtal::Dimension N = TN;
    typedef Component                   Quantity;    ///< the type of scalar (i.e. Component)
    typedef PointVector<N,Component>    RowVector;   ///< the type for row vectors (1xN)
    typedef PointVector<M,Component>    ColumnVector;///< the type for column vectors (Nx1)
    typedef ColumnVector                Vector;      ///< an alias for column vectors (Nx1)
    typedef TMatrix Matrix;      ///< the type for matrices (NxN)

 
    // ----------------------- Static constants ------------------------------
  public:
    /// Usual static constant for dimension.
    static const DGtal::Dimension dimension = TN;
    /// Static constant for dimension - 1.
    static const DGtal::Dimension dimensionMinusOne = TN - 1;

    // ----------------------- Static services ------------------------------
  public:

    /**
     * \brief Reduces a real symmetric matrix to a symmetric
     * tridiagonal matrix using and accumulating orthogonal similarity
     * transformations
     *
     * This is derived from the Algol procedures tred2 and tql2 by Bowdler, Martin, Reinsch
     * and Wilkinson, Handbook for Auto. Comp., Vol.ii-Linear Algebra, and the corresponding
     * Fortran subroutine in EISPACK.
     *
     * @param[in,out] V \b input: symmetric matrix / \b output: the orthogonal transformation matrix produced in the reduction.
     * @param[out] d contains the diagonal elements of the tridiagonal matrix.
     * @param[out] e contains the subdiagonal elements of the tridiagonal matrix in its last n-1 positions. e[0] is set to 0.
     */
    static void tridiagonalize( Matrix& V, Vector& d, Vector& e );
    
    /**
     * \brief finds the eigenvalues and eigenvectors of a symmetric
     * tridiagonal matrix by the QL method.  The eigenvectors of a
     * full symmetric matric can also be found if tridiagonalize() has
     * been used to reduce this full matrix to tridiagonal form.
     *
     * This is derived from the Algol procedures tred2 and tql2 by Bowdler, Martin, Reinsch
     * and Wilkinson, Handbook for Auto. Comp., Vol.ii-Linear Algebra, and the corresponding
     * Fortran subroutine in EISPACK.
     *
     * @param[in] e contains the subdiagonal elements of the input matrix in its last n-1 positions. e(0) is arbitrary.
     * @param[in,out] d \b input: the diagonal elements of the input matrix / \b output: orthonormal eigenvalues in ascending order.

     * @param[in,out] V \b input: transformation matrix produced in the
     * reduction by tridiagonalize(), if performed. If the
     * eigenvectors of the tridiagonal matrix are desired, V must
     * contain the identity matrix / \b output: orthonormal eigenvectors
     * of the symmetric tridiagonal (or full) transformation matrix.
     *
     * @todo Sorting the eigenvalues is done by selection sort. This
     * could be improved for big values of TN.
     */
    static void decomposeQL( Matrix& V, Vector& d, Vector e );

    /**
     * \brief Compute both eigen vectors and eigen values from an
     * input matrix.
     *
     * This is derived from the Algol procedures tred2 and tql2 by Bowdler, Martin, Reinsch
     * and Wilkinson, Handbook for Auto. Comp., Vol.ii-Linear Algebra, and the corresponding
     * Fortran subroutine in EISPACK.
     *
     * @param[in]  matrix        3D matrix whose eigen values/vectors are computed (size = dimension * dimension).
     * @param[out] eigenVectors  matrix of eigenvectors (size = dimension * dimension). Eigenvectors are put in column.
     * @param[out] eigenValues   vector of eigenvalues (size = dimension), sorted in ascending order (smallest to highest).
     */
    static void getEigenDecomposition( const Matrix& matrix, Matrix& eigenVectors, Vector& eigenValues );
    
    
    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:


    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class EigenDecomposition

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/math/linalg/EigenDecomposition.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined EigenDecomposition_h

#undef EigenDecomposition_RECURSES
#endif // else defined(EigenDecomposition_RECURSES)
