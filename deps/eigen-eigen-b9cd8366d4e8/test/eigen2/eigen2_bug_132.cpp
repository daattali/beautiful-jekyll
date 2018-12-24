// This file is part of Eigen, a lightweight C++ template library
// for linear algebra. Eigen itself is part of the KDE project.
//
// Copyright (C) 2010 Benoit Jacob <jacob.benoit.1@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "main.h"

void test_eigen2_bug_132() {
  int size = 100;
  MatrixXd A(size, size);
  VectorXd b(size), c(size);
  {
    VectorXd y = A.transpose() * (b-c);  // bug 132: infinite recursion in coeffRef
    VectorXd z = (b-c).transpose() * A;  // bug 132: infinite recursion in coeffRef
  }

  // the following ones weren't failing, but let's include them for completeness:
  {
    VectorXd y = A * (b-c);
    VectorXd z = (b-c).transpose() * A.transpose();
  }
}
