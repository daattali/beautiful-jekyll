// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2008-2009 Gael Guennebaud <gael.guennebaud@inria.fr>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "main.h"

template<typename ArrayType> void array(const ArrayType& m)
{
  typedef typename ArrayType::Index Index;
  typedef typename ArrayType::Scalar Scalar;
  typedef Array<Scalar, ArrayType::RowsAtCompileTime, 1> ColVectorType;
  typedef Array<Scalar, 1, ArrayType::ColsAtCompileTime> RowVectorType;

  Index rows = m.rows();
  Index cols = m.cols(); 

  ArrayType m1 = ArrayType::Random(rows, cols),
             m2 = ArrayType::Random(rows, cols),
             m3(rows, cols);

  ColVectorType cv1 = ColVectorType::Random(rows);
  RowVectorType rv1 = RowVectorType::Random(cols);

  Scalar  s1 = internal::random<Scalar>(),
          s2 = internal::random<Scalar>();

  // scalar addition
  VERIFY_IS_APPROX(m1 + s1, s1 + m1);
  VERIFY_IS_APPROX(m1 + s1, ArrayType::Constant(rows,cols,s1) + m1);
  VERIFY_IS_APPROX(s1 - m1, (-m1)+s1 );
  VERIFY_IS_APPROX(m1 - s1, m1 - ArrayType::Constant(rows,cols,s1));
  VERIFY_IS_APPROX(s1 - m1, ArrayType::Constant(rows,cols,s1) - m1);
  VERIFY_IS_APPROX((m1*Scalar(2)) - s2, (m1+m1) - ArrayType::Constant(rows,cols,s2) );
  m3 = m1;
  m3 += s2;
  VERIFY_IS_APPROX(m3, m1 + s2);
  m3 = m1;
  m3 -= s1;
  VERIFY_IS_APPROX(m3, m1 - s1);  
  
  // scalar operators via Maps
  m3 = m1;
  ArrayType::Map(m1.data(), m1.rows(), m1.cols()) -= ArrayType::Map(m2.data(), m2.rows(), m2.cols());
  VERIFY_IS_APPROX(m1, m3 - m2);
  
  m3 = m1;
  ArrayType::Map(m1.data(), m1.rows(), m1.cols()) += ArrayType::Map(m2.data(), m2.rows(), m2.cols());
  VERIFY_IS_APPROX(m1, m3 + m2);
  
  m3 = m1;
  ArrayType::Map(m1.data(), m1.rows(), m1.cols()) *= ArrayType::Map(m2.data(), m2.rows(), m2.cols());
  VERIFY_IS_APPROX(m1, m3 * m2);
  
  m3 = m1;
  m2 = ArrayType::Random(rows,cols);
  m2 = (m2==0).select(1,m2);
  ArrayType::Map(m1.data(), m1.rows(), m1.cols()) /= ArrayType::Map(m2.data(), m2.rows(), m2.cols());  
  VERIFY_IS_APPROX(m1, m3 / m2);

  // reductions
  VERIFY_IS_APPROX(m1.abs().colwise().sum().sum(), m1.abs().sum());
  VERIFY_IS_APPROX(m1.abs().rowwise().sum().sum(), m1.abs().sum());
  using std::abs;
  VERIFY_IS_MUCH_SMALLER_THAN(abs(m1.colwise().sum().sum() - m1.sum()), m1.abs().sum());
  VERIFY_IS_MUCH_SMALLER_THAN(abs(m1.rowwise().sum().sum() - m1.sum()), m1.abs().sum());
  if (!internal::isMuchSmallerThan(abs(m1.sum() - (m1+m2).sum()), m1.abs().sum(), test_precision<Scalar>()))
      VERIFY_IS_NOT_APPROX(((m1+m2).rowwise().sum()).sum(), m1.sum());
  VERIFY_IS_APPROX(m1.colwise().sum(), m1.colwise().redux(internal::scalar_sum_op<Scalar>()));

  // vector-wise ops
  m3 = m1;
  VERIFY_IS_APPROX(m3.colwise() += cv1, m1.colwise() + cv1);
  m3 = m1;
  VERIFY_IS_APPROX(m3.colwise() -= cv1, m1.colwise() - cv1);
  m3 = m1;
  VERIFY_IS_APPROX(m3.rowwise() += rv1, m1.rowwise() + rv1);
  m3 = m1;
  VERIFY_IS_APPROX(m3.rowwise() -= rv1, m1.rowwise() - rv1);
}

template<typename ArrayType> void comparisons(const ArrayType& m)
{
  using std::abs;
  typedef typename ArrayType::Index Index;
  typedef typename ArrayType::Scalar Scalar;
  typedef typename NumTraits<Scalar>::Real RealScalar;

  Index rows = m.rows();
  Index cols = m.cols();

  Index r = internal::random<Index>(0, rows-1),
        c = internal::random<Index>(0, cols-1);

  ArrayType m1 = ArrayType::Random(rows, cols),
             m2 = ArrayType::Random(rows, cols),
             m3(rows, cols);            

  VERIFY(((m1 + Scalar(1)) > m1).all());
  VERIFY(((m1 - Scalar(1)) < m1).all());
  if (rows*cols>1)
  {
    m3 = m1;
    m3(r,c) += 1;
    VERIFY(! (m1 < m3).all() );
    VERIFY(! (m1 > m3).all() );
  }
  VERIFY(!(m1 > m2 && m1 < m2).any());
  VERIFY((m1 <= m2 || m1 >= m2).all());

  // comparisons to scalar
  VERIFY( (m1 != (m1(r,c)+1) ).any() );
  VERIFY( (m1 > (m1(r,c)-1) ).any() );
  VERIFY( (m1 < (m1(r,c)+1) ).any() );
  VERIFY( (m1 == m1(r,c) ).any() );

  // test Select
  VERIFY_IS_APPROX( (m1<m2).select(m1,m2), m1.cwiseMin(m2) );
  VERIFY_IS_APPROX( (m1>m2).select(m1,m2), m1.cwiseMax(m2) );
  Scalar mid = (m1.cwiseAbs().minCoeff() + m1.cwiseAbs().maxCoeff())/Scalar(2);
  for (int j=0; j<cols; ++j)
  for (int i=0; i<rows; ++i)
    m3(i,j) = abs(m1(i,j))<mid ? 0 : m1(i,j);
  VERIFY_IS_APPROX( (m1.abs()<ArrayType::Constant(rows,cols,mid))
                        .select(ArrayType::Zero(rows,cols),m1), m3);
  // shorter versions:
  VERIFY_IS_APPROX( (m1.abs()<ArrayType::Constant(rows,cols,mid))
                        .select(0,m1), m3);
  VERIFY_IS_APPROX( (m1.abs()>=ArrayType::Constant(rows,cols,mid))
                        .select(m1,0), m3);
  // even shorter version:
  VERIFY_IS_APPROX( (m1.abs()<mid).select(0,m1), m3);

  // count
  VERIFY(((m1.abs()+1)>RealScalar(0.1)).count() == rows*cols);

  // and/or
  VERIFY( (m1<RealScalar(0) && m1>RealScalar(0)).count() == 0);
  VERIFY( (m1<RealScalar(0) || m1>=RealScalar(0)).count() == rows*cols);
  RealScalar a = m1.abs().mean();
  VERIFY( (m1<-a || m1>a).count() == (m1.abs()>a).count());

  typedef Array<typename ArrayType::Index, Dynamic, 1> ArrayOfIndices;

  // TODO allows colwise/rowwise for array
  VERIFY_IS_APPROX(((m1.abs()+1)>RealScalar(0.1)).colwise().count(), ArrayOfIndices::Constant(cols,rows).transpose());
  VERIFY_IS_APPROX(((m1.abs()+1)>RealScalar(0.1)).rowwise().count(), ArrayOfIndices::Constant(rows, cols));
}

template<typename ArrayType> void array_real(const ArrayType& m)
{
  using std::abs;
  using std::sqrt;
  typedef typename ArrayType::Index Index;
  typedef typename ArrayType::Scalar Scalar;
  typedef typename NumTraits<Scalar>::Real RealScalar;

  Index rows = m.rows();
  Index cols = m.cols();

  ArrayType m1 = ArrayType::Random(rows, cols),
            m2 = ArrayType::Random(rows, cols),
            m3(rows, cols);

  Scalar  s1 = internal::random<Scalar>();

  // these tests are mostly to check possible compilation issues.
  VERIFY_IS_APPROX(m1.sin(), sin(m1));
  VERIFY_IS_APPROX(m1.cos(), cos(m1));
  VERIFY_IS_APPROX(m1.asin(), asin(m1));
  VERIFY_IS_APPROX(m1.acos(), acos(m1));
  VERIFY_IS_APPROX(m1.tan(), tan(m1));
  
  VERIFY_IS_APPROX(cos(m1+RealScalar(3)*m2), cos((m1+RealScalar(3)*m2).eval()));

  VERIFY_IS_APPROX(m1.abs().sqrt(), sqrt(abs(m1)));
  VERIFY_IS_APPROX(m1.abs(), sqrt(numext::abs2(m1)));

  VERIFY_IS_APPROX(numext::abs2(numext::real(m1)) + numext::abs2(numext::imag(m1)), numext::abs2(m1));
  VERIFY_IS_APPROX(numext::abs2(real(m1)) + numext::abs2(imag(m1)), numext::abs2(m1));
  if(!NumTraits<Scalar>::IsComplex)
    VERIFY_IS_APPROX(numext::real(m1), m1);

  // shift argument of logarithm so that it is not zero
  Scalar smallNumber = NumTraits<Scalar>::dummy_precision();
  VERIFY_IS_APPROX((m1.abs() + smallNumber).log() , log(abs(m1) + smallNumber));

  VERIFY_IS_APPROX(m1.exp() * m2.exp(), exp(m1+m2));
  VERIFY_IS_APPROX(m1.exp(), exp(m1));
  VERIFY_IS_APPROX(m1.exp() / m2.exp(),(m1-m2).exp());

  VERIFY_IS_APPROX(m1.pow(2), m1.square());
  VERIFY_IS_APPROX(pow(m1,2), m1.square());

  ArrayType exponents = ArrayType::Constant(rows, cols, RealScalar(2));
  VERIFY_IS_APPROX(Eigen::pow(m1,exponents), m1.square());

  m3 = m1.abs();
  VERIFY_IS_APPROX(m3.pow(RealScalar(0.5)), m3.sqrt());
  VERIFY_IS_APPROX(pow(m3,RealScalar(0.5)), m3.sqrt());

  // scalar by array division
  const RealScalar tiny = sqrt(std::numeric_limits<RealScalar>::epsilon());
  s1 += Scalar(tiny);
  m1 += ArrayType::Constant(rows,cols,Scalar(tiny));
  VERIFY_IS_APPROX(s1/m1, s1 * m1.inverse());
  
  // check inplace transpose
  m3 = m1;
  m3.transposeInPlace();
  VERIFY_IS_APPROX(m3,m1.transpose());
  m3.transposeInPlace();
  VERIFY_IS_APPROX(m3,m1);
}

template<typename ArrayType> void array_complex(const ArrayType& m)
{
  typedef typename ArrayType::Index Index;

  Index rows = m.rows();
  Index cols = m.cols();

  ArrayType m1 = ArrayType::Random(rows, cols),
            m2(rows, cols);

  for (Index i = 0; i < m.rows(); ++i)
    for (Index j = 0; j < m.cols(); ++j)
      m2(i,j) = sqrt(m1(i,j));

  VERIFY_IS_APPROX(m1.sqrt(), m2);
  VERIFY_IS_APPROX(m1.sqrt(), Eigen::sqrt(m1));
}

template<typename ArrayType> void min_max(const ArrayType& m)
{
  typedef typename ArrayType::Index Index;
  typedef typename ArrayType::Scalar Scalar;

  Index rows = m.rows();
  Index cols = m.cols();

  ArrayType m1 = ArrayType::Random(rows, cols);

  // min/max with array
  Scalar maxM1 = m1.maxCoeff();
  Scalar minM1 = m1.minCoeff();

  VERIFY_IS_APPROX(ArrayType::Constant(rows,cols, minM1), (m1.min)(ArrayType::Constant(rows,cols, minM1)));
  VERIFY_IS_APPROX(m1, (m1.min)(ArrayType::Constant(rows,cols, maxM1)));

  VERIFY_IS_APPROX(ArrayType::Constant(rows,cols, maxM1), (m1.max)(ArrayType::Constant(rows,cols, maxM1)));
  VERIFY_IS_APPROX(m1, (m1.max)(ArrayType::Constant(rows,cols, minM1)));

  // min/max with scalar input
  VERIFY_IS_APPROX(ArrayType::Constant(rows,cols, minM1), (m1.min)( minM1));
  VERIFY_IS_APPROX(m1, (m1.min)( maxM1));

  VERIFY_IS_APPROX(ArrayType::Constant(rows,cols, maxM1), (m1.max)( maxM1));
  VERIFY_IS_APPROX(m1, (m1.max)( minM1));

}

void test_array()
{
  for(int i = 0; i < g_repeat; i++) {
    CALL_SUBTEST_1( array(Array<float, 1, 1>()) );
    CALL_SUBTEST_2( array(Array22f()) );
    CALL_SUBTEST_3( array(Array44d()) );
    CALL_SUBTEST_4( array(ArrayXXcf(internal::random<int>(1,EIGEN_TEST_MAX_SIZE), internal::random<int>(1,EIGEN_TEST_MAX_SIZE))) );
    CALL_SUBTEST_5( array(ArrayXXf(internal::random<int>(1,EIGEN_TEST_MAX_SIZE), internal::random<int>(1,EIGEN_TEST_MAX_SIZE))) );
    CALL_SUBTEST_6( array(ArrayXXi(internal::random<int>(1,EIGEN_TEST_MAX_SIZE), internal::random<int>(1,EIGEN_TEST_MAX_SIZE))) );
  }
  for(int i = 0; i < g_repeat; i++) {
    CALL_SUBTEST_1( comparisons(Array<float, 1, 1>()) );
    CALL_SUBTEST_2( comparisons(Array22f()) );
    CALL_SUBTEST_3( comparisons(Array44d()) );
    CALL_SUBTEST_5( comparisons(ArrayXXf(internal::random<int>(1,EIGEN_TEST_MAX_SIZE), internal::random<int>(1,EIGEN_TEST_MAX_SIZE))) );
    CALL_SUBTEST_6( comparisons(ArrayXXi(internal::random<int>(1,EIGEN_TEST_MAX_SIZE), internal::random<int>(1,EIGEN_TEST_MAX_SIZE))) );
  }
  for(int i = 0; i < g_repeat; i++) {
    CALL_SUBTEST_1( min_max(Array<float, 1, 1>()) );
    CALL_SUBTEST_2( min_max(Array22f()) );
    CALL_SUBTEST_3( min_max(Array44d()) );
    CALL_SUBTEST_5( min_max(ArrayXXf(internal::random<int>(1,EIGEN_TEST_MAX_SIZE), internal::random<int>(1,EIGEN_TEST_MAX_SIZE))) );
    CALL_SUBTEST_6( min_max(ArrayXXi(internal::random<int>(1,EIGEN_TEST_MAX_SIZE), internal::random<int>(1,EIGEN_TEST_MAX_SIZE))) );
  }
  for(int i = 0; i < g_repeat; i++) {
    CALL_SUBTEST_1( array_real(Array<float, 1, 1>()) );
    CALL_SUBTEST_2( array_real(Array22f()) );
    CALL_SUBTEST_3( array_real(Array44d()) );
    CALL_SUBTEST_5( array_real(ArrayXXf(internal::random<int>(1,EIGEN_TEST_MAX_SIZE), internal::random<int>(1,EIGEN_TEST_MAX_SIZE))) );
  }
  for(int i = 0; i < g_repeat; i++) {
    CALL_SUBTEST_4( array_complex(ArrayXXcf(internal::random<int>(1,EIGEN_TEST_MAX_SIZE), internal::random<int>(1,EIGEN_TEST_MAX_SIZE))) );
  }

  VERIFY((internal::is_same< internal::global_math_functions_filtering_base<int>::type, int >::value));
  VERIFY((internal::is_same< internal::global_math_functions_filtering_base<float>::type, float >::value));
  VERIFY((internal::is_same< internal::global_math_functions_filtering_base<Array2i>::type, ArrayBase<Array2i> >::value));
  typedef CwiseUnaryOp<internal::scalar_sum_op<double>, ArrayXd > Xpr;
  VERIFY((internal::is_same< internal::global_math_functions_filtering_base<Xpr>::type,
                           ArrayBase<Xpr>
                         >::value));
}
