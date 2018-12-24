// This file is part of Eigen, a lightweight C++ template library
// for linear algebra. Eigen itself is part of the KDE project.
//
// Copyright (C) 2008 Gael Guennebaud <g.gael@free.fr>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "main.h"

template<typename MatrixType> void verifySizeOf(const MatrixType&)
{
  typedef typename MatrixType::Scalar Scalar;
  if (MatrixType::RowsAtCompileTime!=Dynamic && MatrixType::ColsAtCompileTime!=Dynamic)
    VERIFY(sizeof(MatrixType)==sizeof(Scalar)*MatrixType::SizeAtCompileTime);
  else
    VERIFY(sizeof(MatrixType)==sizeof(Scalar*) + 2 * sizeof(typename MatrixType::Index));
}

void test_eigen2_sizeof()
{
  CALL_SUBTEST( verifySizeOf(Matrix<float, 1, 1>()) );
  CALL_SUBTEST( verifySizeOf(Matrix4d()) );
  CALL_SUBTEST( verifySizeOf(Matrix<double, 4, 2>()) );
  CALL_SUBTEST( verifySizeOf(Matrix<bool, 7, 5>()) );
  CALL_SUBTEST( verifySizeOf(MatrixXcf(3, 3)) );
  CALL_SUBTEST( verifySizeOf(MatrixXi(8, 12)) );
  CALL_SUBTEST( verifySizeOf(MatrixXcd(20, 20)) );
  CALL_SUBTEST( verifySizeOf(Matrix<float, 100, 100>()) );
}
