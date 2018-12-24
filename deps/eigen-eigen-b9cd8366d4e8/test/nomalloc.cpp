// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2008 Gael Guennebaud <gael.guennebaud@inria.fr>
// Copyright (C) 2006-2008 Benoit Jacob <jacob.benoit.1@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

// this hack is needed to make this file compiles with -pedantic (gcc)
#ifdef __GNUC__
#define throw(X)
#endif

#ifdef __INTEL_COMPILER
  // disable "warning #76: argument to macro is empty" produced by the above hack
  #pragma warning disable 76
#endif

// discard stack allocation as that too bypasses malloc
#define EIGEN_STACK_ALLOCATION_LIMIT 0
// any heap allocation will raise an assert
#define EIGEN_NO_MALLOC

#include "main.h"
#include <Eigen/Cholesky>
#include <Eigen/Eigenvalues>
#include <Eigen/LU>
#include <Eigen/QR>
#include <Eigen/SVD>

template<typename MatrixType> void nomalloc(const MatrixType& m)
{
  /* this test check no dynamic memory allocation are issued with fixed-size matrices
  */
  typedef typename MatrixType::Index Index;
  typedef typename MatrixType::Scalar Scalar;

  Index rows = m.rows();
  Index cols = m.cols();

  MatrixType m1 = MatrixType::Random(rows, cols),
             m2 = MatrixType::Random(rows, cols),
             m3(rows, cols);

  Scalar s1 = internal::random<Scalar>();

  Index r = internal::random<Index>(0, rows-1),
        c = internal::random<Index>(0, cols-1);

  VERIFY_IS_APPROX((m1+m2)*s1,              s1*m1+s1*m2);
  VERIFY_IS_APPROX((m1+m2)(r,c), (m1(r,c))+(m2(r,c)));
  VERIFY_IS_APPROX(m1.cwiseProduct(m1.block(0,0,rows,cols)), (m1.array()*m1.array()).matrix());
  VERIFY_IS_APPROX((m1*m1.transpose())*m2,  m1*(m1.transpose()*m2));
  
  m2.col(0).noalias() = m1 * m1.col(0);
  m2.col(0).noalias() -= m1.adjoint() * m1.col(0);
  m2.col(0).noalias() -= m1 * m1.row(0).adjoint();
  m2.col(0).noalias() -= m1.adjoint() * m1.row(0).adjoint();

  m2.row(0).noalias() = m1.row(0) * m1;
  m2.row(0).noalias() -= m1.row(0) * m1.adjoint();
  m2.row(0).noalias() -= m1.col(0).adjoint() * m1;
  m2.row(0).noalias() -= m1.col(0).adjoint() * m1.adjoint();
  VERIFY_IS_APPROX(m2,m2);
  
  m2.col(0).noalias() = m1.template triangularView<Upper>() * m1.col(0);
  m2.col(0).noalias() -= m1.adjoint().template triangularView<Upper>() * m1.col(0);
  m2.col(0).noalias() -= m1.template triangularView<Upper>() * m1.row(0).adjoint();
  m2.col(0).noalias() -= m1.adjoint().template triangularView<Upper>() * m1.row(0).adjoint();

  m2.row(0).noalias() = m1.row(0) * m1.template triangularView<Upper>();
  m2.row(0).noalias() -= m1.row(0) * m1.adjoint().template triangularView<Upper>();
  m2.row(0).noalias() -= m1.col(0).adjoint() * m1.template triangularView<Upper>();
  m2.row(0).noalias() -= m1.col(0).adjoint() * m1.adjoint().template triangularView<Upper>();
  VERIFY_IS_APPROX(m2,m2);
  
  m2.col(0).noalias() = m1.template selfadjointView<Upper>() * m1.col(0);
  m2.col(0).noalias() -= m1.adjoint().template selfadjointView<Upper>() * m1.col(0);
  m2.col(0).noalias() -= m1.template selfadjointView<Upper>() * m1.row(0).adjoint();
  m2.col(0).noalias() -= m1.adjoint().template selfadjointView<Upper>() * m1.row(0).adjoint();

  m2.row(0).noalias() = m1.row(0) * m1.template selfadjointView<Upper>();
  m2.row(0).noalias() -= m1.row(0) * m1.adjoint().template selfadjointView<Upper>();
  m2.row(0).noalias() -= m1.col(0).adjoint() * m1.template selfadjointView<Upper>();
  m2.row(0).noalias() -= m1.col(0).adjoint() * m1.adjoint().template selfadjointView<Upper>();
  VERIFY_IS_APPROX(m2,m2);
  
  m2.template selfadjointView<Lower>().rankUpdate(m1.col(0),-1);
  m2.template selfadjointView<Lower>().rankUpdate(m1.row(0),-1);

  // The following fancy matrix-matrix products are not safe yet regarding static allocation
//   m1 += m1.template triangularView<Upper>() * m2.col(;
//   m1.template selfadjointView<Lower>().rankUpdate(m2);
//   m1 += m1.template triangularView<Upper>() * m2;
//   m1 += m1.template selfadjointView<Lower>() * m2;
//   VERIFY_IS_APPROX(m1,m1);
}

template<typename Scalar>
void ctms_decompositions()
{
  const int maxSize = 16;
  const int size    = 12;

  typedef Eigen::Matrix<Scalar,
                        Eigen::Dynamic, Eigen::Dynamic,
                        0,
                        maxSize, maxSize> Matrix;

  typedef Eigen::Matrix<Scalar,
                        Eigen::Dynamic, 1,
                        0,
                        maxSize, 1> Vector;

  typedef Eigen::Matrix<std::complex<Scalar>,
                        Eigen::Dynamic, Eigen::Dynamic,
                        0,
                        maxSize, maxSize> ComplexMatrix;

  const Matrix A(Matrix::Random(size, size)), B(Matrix::Random(size, size));
  Matrix X(size,size);
  const ComplexMatrix complexA(ComplexMatrix::Random(size, size));
  const Matrix saA = A.adjoint() * A;
  const Vector b(Vector::Random(size));
  Vector x(size);

  // Cholesky module
  Eigen::LLT<Matrix>  LLT;  LLT.compute(A);
  X = LLT.solve(B);
  x = LLT.solve(b);
  Eigen::LDLT<Matrix> LDLT; LDLT.compute(A);
  X = LDLT.solve(B);
  x = LDLT.solve(b);

  // Eigenvalues module
  Eigen::HessenbergDecomposition<ComplexMatrix> hessDecomp;        hessDecomp.compute(complexA);
  Eigen::ComplexSchur<ComplexMatrix>            cSchur(size);      cSchur.compute(complexA);
  Eigen::ComplexEigenSolver<ComplexMatrix>      cEigSolver;        cEigSolver.compute(complexA);
  Eigen::EigenSolver<Matrix>                    eigSolver;         eigSolver.compute(A);
  Eigen::SelfAdjointEigenSolver<Matrix>         saEigSolver(size); saEigSolver.compute(saA);
  Eigen::Tridiagonalization<Matrix>             tridiag;           tridiag.compute(saA);

  // LU module
  Eigen::PartialPivLU<Matrix> ppLU; ppLU.compute(A);
  X = ppLU.solve(B);
  x = ppLU.solve(b);
  Eigen::FullPivLU<Matrix>    fpLU; fpLU.compute(A);
  X = fpLU.solve(B);
  x = fpLU.solve(b);

  // QR module
  Eigen::HouseholderQR<Matrix>        hQR;  hQR.compute(A);
  X = hQR.solve(B);
  x = hQR.solve(b);
  Eigen::ColPivHouseholderQR<Matrix>  cpQR; cpQR.compute(A);
  X = cpQR.solve(B);
  x = cpQR.solve(b);
  Eigen::FullPivHouseholderQR<Matrix> fpQR; fpQR.compute(A);
  // FIXME X = fpQR.solve(B);
  x = fpQR.solve(b);

  // SVD module
  Eigen::JacobiSVD<Matrix> jSVD; jSVD.compute(A, ComputeFullU | ComputeFullV);
}

void test_zerosized() {
  // default constructors:
  Eigen::MatrixXd A;
  Eigen::VectorXd v;
  // explicit zero-sized:
  Eigen::ArrayXXd A0(0,0);
  Eigen::ArrayXd v0(std::ptrdiff_t(0)); // FIXME ArrayXd(0) is ambiguous

  // assigning empty objects to each other:
  A=A0;
  v=v0;
}

template<typename MatrixType> void test_reference(const MatrixType& m) {
  typedef typename MatrixType::Scalar Scalar;
  enum { Flag          =  MatrixType::IsRowMajor ? Eigen::RowMajor : Eigen::ColMajor};
  enum { TransposeFlag = !MatrixType::IsRowMajor ? Eigen::RowMajor : Eigen::ColMajor};
  typename MatrixType::Index rows = m.rows(), cols=m.cols();
  // Dynamic reference:
  typedef Eigen::Ref<const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Flag         > > Ref;
  typedef Eigen::Ref<const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, TransposeFlag> > RefT;

  Ref r1(m);
  Ref r2(m.block(rows/3, cols/4, rows/2, cols/2));
  RefT r3(m.transpose());
  RefT r4(m.topLeftCorner(rows/2, cols/2).transpose());

  VERIFY_RAISES_ASSERT(RefT r5(m));
  VERIFY_RAISES_ASSERT(Ref r6(m.transpose()));
  VERIFY_RAISES_ASSERT(Ref r7(Scalar(2) * m));
}

void test_nomalloc()
{
  // check that our operator new is indeed called:
  VERIFY_RAISES_ASSERT(MatrixXd dummy(MatrixXd::Random(3,3)));
  CALL_SUBTEST_1(nomalloc(Matrix<float, 1, 1>()) );
  CALL_SUBTEST_2(nomalloc(Matrix4d()) );
  CALL_SUBTEST_3(nomalloc(Matrix<float,32,32>()) );
  
  // Check decomposition modules with dynamic matrices that have a known compile-time max size (ctms)
  CALL_SUBTEST_4(ctms_decompositions<float>());
  CALL_SUBTEST_5(test_zerosized());
  CALL_SUBTEST_6(test_reference(Matrix<float,32,32>()));
}
