// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2009 Benoit Jacob <jacob.benoit.1@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "main.h"

template<typename Scalar>
void test_eigen2_first_aligned_helper(Scalar *array, int size)
{
  const int packet_size = sizeof(Scalar) * ei_packet_traits<Scalar>::size;
  VERIFY(((std::size_t(array) + sizeof(Scalar) * ei_alignmentOffset(array, size)) % packet_size) == 0);
}

template<typename Scalar>
void test_eigen2_none_aligned_helper(Scalar *array, int size)
{
  VERIFY(ei_packet_traits<Scalar>::size == 1 || ei_alignmentOffset(array, size) == size);
}

struct some_non_vectorizable_type { float x; };

void test_eigen2_first_aligned()
{
  EIGEN_ALIGN_128 float array_float[100];
  test_first_aligned_helper(array_float, 50);
  test_first_aligned_helper(array_float+1, 50);
  test_first_aligned_helper(array_float+2, 50);
  test_first_aligned_helper(array_float+3, 50);
  test_first_aligned_helper(array_float+4, 50);
  test_first_aligned_helper(array_float+5, 50);
  
  EIGEN_ALIGN_128 double array_double[100];
  test_first_aligned_helper(array_double, 50);
  test_first_aligned_helper(array_double+1, 50);
  test_first_aligned_helper(array_double+2, 50);
  
  double *array_double_plus_4_bytes = (double*)(std::size_t(array_double)+4);
  test_none_aligned_helper(array_double_plus_4_bytes, 50);
  test_none_aligned_helper(array_double_plus_4_bytes+1, 50);
  
  some_non_vectorizable_type array_nonvec[100];
  test_first_aligned_helper(array_nonvec, 100);
  test_none_aligned_helper(array_nonvec, 100);
}
