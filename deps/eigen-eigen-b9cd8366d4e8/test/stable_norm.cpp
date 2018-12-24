// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2009 Gael Guennebaud <gael.guennebaud@inria.fr>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "main.h"

// workaround aggressive optimization in ICC
template<typename T> EIGEN_DONT_INLINE  T sub(T a, T b) { return a - b; }

template<typename T> bool isFinite(const T& x)
{
  return isNotNaN(sub(x,x));
}

template<typename T> EIGEN_DONT_INLINE T copy(const T& x)
{
  return x;
}

template<typename MatrixType> void stable_norm(const MatrixType& m)
{
  /* this test covers the following files:
     StableNorm.h
  */
  using std::sqrt;
  using std::abs;
  typedef typename MatrixType::Index Index;
  typedef typename MatrixType::Scalar Scalar;
  typedef typename NumTraits<Scalar>::Real RealScalar;

  // Check the basic machine-dependent constants.
  {
    int ibeta, it, iemin, iemax;

    ibeta = std::numeric_limits<RealScalar>::radix;         // base for floating-point numbers
    it    = std::numeric_limits<RealScalar>::digits;        // number of base-beta digits in mantissa
    iemin = std::numeric_limits<RealScalar>::min_exponent;  // minimum exponent
    iemax = std::numeric_limits<RealScalar>::max_exponent;  // maximum exponent

    VERIFY( (!(iemin > 1 - 2*it || 1+it>iemax || (it==2 && ibeta<5) || (it<=4 && ibeta <= 3 ) || it<2))
           && "the stable norm algorithm cannot be guaranteed on this computer");
  }


  Index rows = m.rows();
  Index cols = m.cols();

  // get a non-zero random factor
  Scalar factor = internal::random<Scalar>();
  while(numext::abs2(factor)<RealScalar(1e-4))
    factor = internal::random<Scalar>();
  Scalar big = factor * ((std::numeric_limits<RealScalar>::max)() * RealScalar(1e-4));
  
  factor = internal::random<Scalar>();
  while(numext::abs2(factor)<RealScalar(1e-4))
    factor = internal::random<Scalar>();
  Scalar small = factor * ((std::numeric_limits<RealScalar>::min)() * RealScalar(1e4));

  MatrixType  vzero = MatrixType::Zero(rows, cols),
              vrand = MatrixType::Random(rows, cols),
              vbig(rows, cols),
              vsmall(rows,cols);

  vbig.fill(big);
  vsmall.fill(small);

  VERIFY_IS_MUCH_SMALLER_THAN(vzero.norm(), static_cast<RealScalar>(1));
  VERIFY_IS_APPROX(vrand.stableNorm(),      vrand.norm());
  VERIFY_IS_APPROX(vrand.blueNorm(),        vrand.norm());
  VERIFY_IS_APPROX(vrand.hypotNorm(),       vrand.norm());

  RealScalar size = static_cast<RealScalar>(m.size());

  // test isFinite
  VERIFY(!isFinite( std::numeric_limits<RealScalar>::infinity()));
  VERIFY(!isFinite(sqrt(-abs(big))));

  // test overflow
  VERIFY(isFinite(sqrt(size)*abs(big)));
  VERIFY_IS_NOT_APPROX(sqrt(copy(vbig.squaredNorm())), abs(sqrt(size)*big)); // here the default norm must fail
  VERIFY_IS_APPROX(vbig.stableNorm(), sqrt(size)*abs(big));
  VERIFY_IS_APPROX(vbig.blueNorm(),   sqrt(size)*abs(big));
  VERIFY_IS_APPROX(vbig.hypotNorm(),  sqrt(size)*abs(big));

  // test underflow
  VERIFY(isFinite(sqrt(size)*abs(small)));
  VERIFY_IS_NOT_APPROX(sqrt(copy(vsmall.squaredNorm())),   abs(sqrt(size)*small)); // here the default norm must fail
  VERIFY_IS_APPROX(vsmall.stableNorm(), sqrt(size)*abs(small));
  VERIFY_IS_APPROX(vsmall.blueNorm(),   sqrt(size)*abs(small));
  VERIFY_IS_APPROX(vsmall.hypotNorm(),  sqrt(size)*abs(small));

  // Test compilation of cwise() version
  VERIFY_IS_APPROX(vrand.colwise().stableNorm(),      vrand.colwise().norm());
  VERIFY_IS_APPROX(vrand.colwise().blueNorm(),        vrand.colwise().norm());
  VERIFY_IS_APPROX(vrand.colwise().hypotNorm(),       vrand.colwise().norm());
  VERIFY_IS_APPROX(vrand.rowwise().stableNorm(),      vrand.rowwise().norm());
  VERIFY_IS_APPROX(vrand.rowwise().blueNorm(),        vrand.rowwise().norm());
  VERIFY_IS_APPROX(vrand.rowwise().hypotNorm(),       vrand.rowwise().norm());
}

void test_stable_norm()
{
  for(int i = 0; i < g_repeat; i++) {
    CALL_SUBTEST_1( stable_norm(Matrix<float, 1, 1>()) );
    CALL_SUBTEST_2( stable_norm(Vector4d()) );
    CALL_SUBTEST_3( stable_norm(VectorXd(internal::random<int>(10,2000))) );
    CALL_SUBTEST_4( stable_norm(VectorXf(internal::random<int>(10,2000))) );
    CALL_SUBTEST_5( stable_norm(VectorXcd(internal::random<int>(10,2000))) );
  }
}
