// This file is part of Eigen, a lightweight C++ template library
// for linear algebra. Eigen itself is part of the KDE project.
//
// Copyright (C) 2008 Gael Guennebaud <g.gael@free.fr>
// Copyright (C) 2008 Benoit Jacob <jacob.benoit.1@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "main.h"
#include <Eigen/LU>

template<typename MatrixType> void inverse(const MatrixType& m)
{
  /* this test covers the following files:
     Inverse.h
  */
  int rows = m.rows();
  int cols = m.cols();

  typedef typename MatrixType::Scalar Scalar;
  typedef typename NumTraits<Scalar>::Real RealScalar;
  typedef Matrix<Scalar, MatrixType::ColsAtCompileTime, 1> VectorType;

  MatrixType m1 = MatrixType::Random(rows, cols),
             m2(rows, cols),
             identity = MatrixType::Identity(rows, rows);

  while(ei_abs(m1.determinant()) < RealScalar(0.1) && rows <= 8)
  {
    m1 = MatrixType::Random(rows, cols);
  }

  m2 = m1.inverse();
  VERIFY_IS_APPROX(m1, m2.inverse() );

  m1.computeInverse(&m2);
  VERIFY_IS_APPROX(m1, m2.inverse() );

  VERIFY_IS_APPROX((Scalar(2)*m2).inverse(), m2.inverse()*Scalar(0.5));

  VERIFY_IS_APPROX(identity, m1.inverse() * m1 );
  VERIFY_IS_APPROX(identity, m1 * m1.inverse() );

  VERIFY_IS_APPROX(m1, m1.inverse().inverse() );

  // since for the general case we implement separately row-major and col-major, test that
  VERIFY_IS_APPROX(m1.transpose().inverse(), m1.inverse().transpose());
}

void test_eigen2_inverse()
{
  for(int i = 0; i < g_repeat; i++) {
    CALL_SUBTEST_1( inverse(Matrix<double,1,1>()) );
    CALL_SUBTEST_2( inverse(Matrix2d()) );
    CALL_SUBTEST_3( inverse(Matrix3f()) );
    CALL_SUBTEST_4( inverse(Matrix4f()) );
    CALL_SUBTEST_5( inverse(MatrixXf(8,8)) );
    CALL_SUBTEST_6( inverse(MatrixXcd(7,7)) );
  }
}
