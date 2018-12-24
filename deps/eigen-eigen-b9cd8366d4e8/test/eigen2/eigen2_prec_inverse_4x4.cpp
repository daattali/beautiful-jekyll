// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2009 Benoit Jacob <jacob.benoit.1@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "main.h"
#include <Eigen/LU>
#include <algorithm>

template<typename T> std::string type_name() { return "other"; }
template<> std::string type_name<float>() { return "float"; }
template<> std::string type_name<double>() { return "double"; }
template<> std::string type_name<int>() { return "int"; }
template<> std::string type_name<std::complex<float> >() { return "complex<float>"; }
template<> std::string type_name<std::complex<double> >() { return "complex<double>"; }
template<> std::string type_name<std::complex<int> >() { return "complex<int>"; }

#define EIGEN_DEBUG_VAR(x) std::cerr << #x << " = " << x << std::endl;

template<typename T> inline typename NumTraits<T>::Real epsilon()
{
 return std::numeric_limits<typename NumTraits<T>::Real>::epsilon();
}

template<typename MatrixType> void inverse_permutation_4x4()
{
  typedef typename MatrixType::Scalar Scalar;
  typedef typename MatrixType::RealScalar RealScalar;
  Vector4i indices(0,1,2,3);
  for(int i = 0; i < 24; ++i)
  {
    MatrixType m = MatrixType::Zero();
    m(indices(0),0) = 1;
    m(indices(1),1) = 1;
    m(indices(2),2) = 1;
    m(indices(3),3) = 1;
    MatrixType inv = m.inverse();
    double error = double( (m*inv-MatrixType::Identity()).norm() / epsilon<Scalar>() );
    VERIFY(error == 0.0);
    std::next_permutation(indices.data(),indices.data()+4);
  }
}

template<typename MatrixType> void inverse_general_4x4(int repeat)
{
  typedef typename MatrixType::Scalar Scalar;
  typedef typename MatrixType::RealScalar RealScalar;
  double error_sum = 0., error_max = 0.;
  for(int i = 0; i < repeat; ++i)
  {
    MatrixType m;
    RealScalar absdet;
    do {
      m = MatrixType::Random();
      absdet = ei_abs(m.determinant());
    } while(absdet < 10 * epsilon<Scalar>());
    MatrixType inv = m.inverse();
    double error = double( (m*inv-MatrixType::Identity()).norm() * absdet / epsilon<Scalar>() );
    error_sum += error;
    error_max = std::max(error_max, error);
  }
  std::cerr << "inverse_general_4x4, Scalar = " << type_name<Scalar>() << std::endl;
  double error_avg = error_sum / repeat;
  EIGEN_DEBUG_VAR(error_avg);
  EIGEN_DEBUG_VAR(error_max);
  VERIFY(error_avg < (NumTraits<Scalar>::IsComplex ? 8.0 : 1.25));
  VERIFY(error_max < (NumTraits<Scalar>::IsComplex ? 64.0 : 20.0));
}

void test_eigen2_prec_inverse_4x4()
{
  CALL_SUBTEST_1((inverse_permutation_4x4<Matrix4f>()));
  CALL_SUBTEST_1(( inverse_general_4x4<Matrix4f>(200000 * g_repeat) ));

  CALL_SUBTEST_2((inverse_permutation_4x4<Matrix<double,4,4,RowMajor> >()));
  CALL_SUBTEST_2(( inverse_general_4x4<Matrix<double,4,4,RowMajor> >(200000 * g_repeat) ));

  CALL_SUBTEST_3((inverse_permutation_4x4<Matrix4cf>()));
  CALL_SUBTEST_3((inverse_general_4x4<Matrix4cf>(50000 * g_repeat)));
}
