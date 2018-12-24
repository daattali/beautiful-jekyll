// This file is part of Eigen, a lightweight C++ template library
// for linear algebra. Eigen itself is part of the KDE project.
//
// Copyright (C) 2008 Gael Guennebaud <g.gael@free.fr>
// Copyright (C) 2006-2008 Benoit Jacob <jacob.benoit.1@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

// this hack is needed to make this file compiles with -pedantic (gcc)
#ifdef __GNUC__
#define throw(X)
#endif
// discard stack allocation as that too bypasses malloc
#define EIGEN_STACK_ALLOCATION_LIMIT 0
// any heap allocation will raise an assert
#define EIGEN_NO_MALLOC

#include "main.h"

template<typename MatrixType> void nomalloc(const MatrixType& m)
{
  /* this test check no dynamic memory allocation are issued with fixed-size matrices
  */

  typedef typename MatrixType::Scalar Scalar;

  int rows = m.rows();
  int cols = m.cols();

  MatrixType m1 = MatrixType::Random(rows, cols),
             m2 = MatrixType::Random(rows, cols);

  Scalar s1 = ei_random<Scalar>();

  int r = ei_random<int>(0, rows-1),
      c = ei_random<int>(0, cols-1);

  VERIFY_IS_APPROX((m1+m2)*s1,              s1*m1+s1*m2);
  VERIFY_IS_APPROX((m1+m2)(r,c), (m1(r,c))+(m2(r,c)));
  VERIFY_IS_APPROX(m1.cwise() * m1.block(0,0,rows,cols), m1.cwise() * m1);
  VERIFY_IS_APPROX((m1*m1.transpose())*m2,  m1*(m1.transpose()*m2));
}

void test_eigen2_nomalloc()
{
  // check that our operator new is indeed called:
  VERIFY_RAISES_ASSERT(MatrixXd dummy = MatrixXd::Random(3,3));
  CALL_SUBTEST_1( nomalloc(Matrix<float, 1, 1>()) );
  CALL_SUBTEST_2( nomalloc(Matrix4d()) );
  CALL_SUBTEST_3( nomalloc(Matrix<float,32,32>()) );
}
