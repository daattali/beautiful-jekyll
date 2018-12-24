// This file is part of Eigen, a lightweight C++ template library
// for linear algebra. Eigen itself is part of the KDE project.
//
// Copyright (C) 2006-2008 Benoit Jacob <jacob.benoit.1@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#define EIGEN_NO_STATIC_ASSERT
#include "product.h"

void test_eigen2_product_small()
{
  for(int i = 0; i < g_repeat; i++) {
    CALL_SUBTEST_1( product(Matrix<float, 3, 2>()) );
    CALL_SUBTEST_2( product(Matrix<int, 3, 5>()) );
    CALL_SUBTEST_3( product(Matrix3d()) );
    CALL_SUBTEST_4( product(Matrix4d()) );
    CALL_SUBTEST_5( product(Matrix4f()) );
  }
}
