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
 * @file EigenSupport.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/27
 *
 * Header file for module EigenSupport.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(EigenSupport_RECURSES)
#error Recursive header files inclusion detected in EigenSupport.h
#else // defined(EigenSupport_RECURSES)
/** Prevents recursive inclusion of headers. */
#define EigenSupport_RECURSES

#if !defined EigenSupport_h
/** Prevents repeated inclusion of headers. */
#define EigenSupport_h

/** Prevents inclusion if Eigen support hasn't been enabled **/
#if defined(WITH_EIGEN)

//////////////////////////////////////////////////////////////////////////////
// Eigen API extensions
#define EIGEN_DENSEBASE_PLUGIN "DGtal/math/linalg/EigenDenseBaseAddons.h"
#define EIGEN_SPARSEMATRIX_PLUGIN "DGtal/math/linalg/EigenSparseMatrixAddons.h"
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#if defined(__GNUG__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wignored-attributes"
#pragma GCC diagnostic ignored "-Wshadow"
#endif
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wignored-attributes"
#endif
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>
#include <Eigen/IterativeLinearSolvers>
#include <Eigen/SparseLU>
#include <Eigen/SparseQR>
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#if defined(__GNUG__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// struct EigenLinearAlgebraBackend
/**
 * Description of struct 'EigenLinearAlgebraBackend' <p>
 * \brief Aim:
 * Provide linear algebra backend using Eigen dense and sparse matrix as well as dense vector.
 * 6 linear solvers available:
 *  - EigenLinearAlgebraBackend::SolverSimplicialLLT
 *  - EigenLinearAlgebraBackend::SolverSimplicialLDLT
 *  - EigenLinearAlgebraBackend::SolverConjugateGradient
 *  - EigenLinearAlgebraBackend::SolverBiCGSTAB
 *  - EigenLinearAlgebraBackend::SolverSparseLU
 *  - EigenLinearAlgebraBackend::SolverSparseQR
 * Eigen solvers documentation <a href="http://eigen.tuxfamily.org/dox/group__TopicSparseSystems.html">here</a>
 */
struct EigenLinearAlgebraBackend
{
    typedef Eigen::VectorXd DenseVector;
    typedef Eigen::MatrixXd DenseMatrix;
    typedef Eigen::VectorXi IntegerVector;

    typedef Eigen::Triplet<double> Triplet;
    typedef Eigen::SparseMatrix<DenseVector::Scalar, Eigen::ColMajor, DenseVector::Index> SparseMatrix;

    typedef Eigen::SimplicialLLT<SparseMatrix> SolverSimplicialLLT;
    typedef Eigen::SimplicialLDLT<SparseMatrix> SolverSimplicialLDLT;
    typedef Eigen::ConjugateGradient<SparseMatrix> SolverConjugateGradient;
    typedef Eigen::BiCGSTAB<SparseMatrix> SolverBiCGSTAB;
    typedef Eigen::SparseLU<SparseMatrix> SolverSparseLU;
    typedef Eigen::SparseQR<SparseMatrix, Eigen::COLAMDOrdering<SparseMatrix::Index> > SolverSparseQR;
};
///////////////////////////////////////////////////////////////////////////////


/**
 * Overloads 'operator<<' for displaying objects of class 'Eigen::ComputationInfo'.
 * @param os the output stream where the object is written.
 * @param info the object of class 'EigenSupport' to write.
 * @return the output stream after the writing.
 */
inline
std::ostream&
operator<<(std::ostream & os, const Eigen::ComputationInfo& info)
{
    switch (info)
    {
        case Eigen::Success:
            os << "success";
            break;
        case Eigen::NumericalIssue:
            os << "numerical_issue";
            break;
        case Eigen::NoConvergence:
            os << "no_convergence";
            break;
        case Eigen::InvalidInput:
            os << "invalid_input";
            break;
    }

    return os;
}

} // namespace DGtal

#else // defined WITH_EIGEN
#error "DGtal Eigen support hasn't been enabled"
#endif // defined WITH_EIGEN
#endif // !defined EigenSupport_h

#undef EigenSupport_RECURSES
#endif // else defined(EigenSupport_RECURSES)
