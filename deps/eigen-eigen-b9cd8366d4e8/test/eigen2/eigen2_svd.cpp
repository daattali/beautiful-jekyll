// This file is part of Eigen, a lightweight C++ template library
// for linear algebra. Eigen itself is part of the KDE project.
//
// Copyright (C) 2008 Gael Guennebaud <g.gael@free.fr>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "main.h"
#include <Eigen/SVD>

template<typename MatrixType> void svd(const MatrixType& m)
{
  /* this test covers the following files:
     SVD.h
  */
  int rows = m.rows();
  int cols = m.cols();

  typedef typename MatrixType::Scalar Scalar;
  typedef typename NumTraits<Scalar>::Real RealScalar;
  MatrixType a = MatrixType::Random(rows,cols);
  Matrix<Scalar, MatrixType::RowsAtCompileTime, 1> b =
    Matrix<Scalar, MatrixType::RowsAtCompileTime, 1>::Random(rows,1);
  Matrix<Scalar, MatrixType::ColsAtCompileTime, 1> x(cols,1), x2(cols,1);

  RealScalar largerEps = test_precision<RealScalar>();
  if (ei_is_same_type<RealScalar,float>::ret)
    largerEps = 1e-3f;

  {
    SVD<MatrixType> svd(a);
    MatrixType sigma = MatrixType::Zero(rows,cols);
    MatrixType matU  = MatrixType::Zero(rows,rows);
    sigma.block(0,0,cols,cols) = svd.singularValues().asDiagonal();
    matU.block(0,0,rows,cols) = svd.matrixU();
    VERIFY_IS_APPROX(a, matU * sigma * svd.matrixV().transpose());
  }


  if (rows==cols)
  {
    if (ei_is_same_type<RealScalar,float>::ret)
    {
      MatrixType a1 = MatrixType::Random(rows,cols);
      a += a * a.adjoint() + a1 * a1.adjoint();
    }
    SVD<MatrixType> svd(a);
    svd.solve(b, &x);
    VERIFY_IS_APPROX(a * x,b);
  }


  if(rows==cols)
  {
    SVD<MatrixType> svd(a);
    MatrixType unitary, positive;
    svd.computeUnitaryPositive(&unitary, &positive);
    VERIFY_IS_APPROX(unitary * unitary.adjoint(), MatrixType::Identity(unitary.rows(),unitary.rows()));
    VERIFY_IS_APPROX(positive, positive.adjoint());
    for(int i = 0; i < rows; i++) VERIFY(positive.diagonal()[i] >= 0); // cheap necessary (not sufficient) condition for positivity
    VERIFY_IS_APPROX(unitary*positive, a);

    svd.computePositiveUnitary(&positive, &unitary);
    VERIFY_IS_APPROX(unitary * unitary.adjoint(), MatrixType::Identity(unitary.rows(),unitary.rows()));
    VERIFY_IS_APPROX(positive, positive.adjoint());
    for(int i = 0; i < rows; i++) VERIFY(positive.diagonal()[i] >= 0); // cheap necessary (not sufficient) condition for positivity
    VERIFY_IS_APPROX(positive*unitary, a);
  }
}

void test_eigen2_svd()
{
  for(int i = 0; i < g_repeat; i++) {
    CALL_SUBTEST_1( svd(Matrix3f()) );
    CALL_SUBTEST_2( svd(Matrix4d()) );
    CALL_SUBTEST_3( svd(MatrixXf(7,7)) );
    CALL_SUBTEST_4( svd(MatrixXd(14,7)) );
    // complex are not implemented yet
//     CALL_SUBTEST( svd(MatrixXcd(6,6)) );
//     CALL_SUBTEST( svd(MatrixXcf(3,3)) );
    SVD<MatrixXf> s;
    MatrixXf m = MatrixXf::Random(10,1);
    s.compute(m);
  }
}
