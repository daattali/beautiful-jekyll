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
#include <Eigen/Geometry>
#include <Eigen/LU>
#include <Eigen/QR>

template<typename LineType> void parametrizedline(const LineType& _line)
{
  /* this test covers the following files:
     ParametrizedLine.h
  */

  const int dim = _line.dim();
  typedef typename LineType::Scalar Scalar;
  typedef typename NumTraits<Scalar>::Real RealScalar;
  typedef Matrix<Scalar, LineType::AmbientDimAtCompileTime, 1> VectorType;
  typedef Matrix<Scalar, LineType::AmbientDimAtCompileTime,
                         LineType::AmbientDimAtCompileTime> MatrixType;

  VectorType p0 = VectorType::Random(dim);
  VectorType p1 = VectorType::Random(dim);

  VectorType d0 = VectorType::Random(dim).normalized();

  LineType l0(p0, d0);

  Scalar s0 = ei_random<Scalar>();
  Scalar s1 = ei_abs(ei_random<Scalar>());

  VERIFY_IS_MUCH_SMALLER_THAN( l0.distance(p0), RealScalar(1) );
  VERIFY_IS_MUCH_SMALLER_THAN( l0.distance(p0+s0*d0), RealScalar(1) );
  VERIFY_IS_APPROX( (l0.projection(p1)-p1).norm(), l0.distance(p1) );
  VERIFY_IS_MUCH_SMALLER_THAN( l0.distance(l0.projection(p1)), RealScalar(1) );
  VERIFY_IS_APPROX( Scalar(l0.distance((p0+s0*d0) + d0.unitOrthogonal() * s1)), s1 );

  // casting
  const int Dim = LineType::AmbientDimAtCompileTime;
  typedef typename GetDifferentType<Scalar>::type OtherScalar;
  ParametrizedLine<OtherScalar,Dim> hp1f = l0.template cast<OtherScalar>();
  VERIFY_IS_APPROX(hp1f.template cast<Scalar>(),l0);
  ParametrizedLine<Scalar,Dim> hp1d = l0.template cast<Scalar>();
  VERIFY_IS_APPROX(hp1d.template cast<Scalar>(),l0);
}

void test_eigen2_parametrizedline()
{
  for(int i = 0; i < g_repeat; i++) {
    CALL_SUBTEST_1( parametrizedline(ParametrizedLine<float,2>()) );
    CALL_SUBTEST_2( parametrizedline(ParametrizedLine<float,3>()) );
    CALL_SUBTEST_3( parametrizedline(ParametrizedLine<double,4>()) );
    CALL_SUBTEST_4( parametrizedline(ParametrizedLine<std::complex<double>,5>()) );
  }
}
