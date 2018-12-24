// This file is part of Eigen, a lightweight C++ template library
// for linear algebra. Eigen itself is part of the KDE project.
//
// Copyright (C) 2008 Gael Guennebaud <g.gael@free.fr>
// Copyright (C) 2006-2008 Benoit Jacob <jacob.benoit.1@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "main.h"
#include <functional>
#include <Eigen/Array>

using namespace std;

template<typename Scalar> struct AddIfNull {
    const Scalar operator() (const Scalar a, const Scalar b) const {return a<=1e-3 ? b : a;}
    enum { Cost = NumTraits<Scalar>::AddCost };
};

template<typename MatrixType> void cwiseops(const MatrixType& m)
{
  typedef typename MatrixType::Scalar Scalar;
  typedef typename NumTraits<Scalar>::Real RealScalar;
  typedef Matrix<Scalar, MatrixType::RowsAtCompileTime, 1> VectorType;

  int rows = m.rows();
  int cols = m.cols();

  MatrixType m1 = MatrixType::Random(rows, cols),
             m2 = MatrixType::Random(rows, cols),
             m3(rows, cols),
             m4(rows, cols),
             mzero = MatrixType::Zero(rows, cols),
             mones = MatrixType::Ones(rows, cols),
             identity = Matrix<Scalar, MatrixType::RowsAtCompileTime, MatrixType::RowsAtCompileTime>
                              ::Identity(rows, rows);
  VectorType vzero = VectorType::Zero(rows),
             vones = VectorType::Ones(rows),
             v3(rows);

  int r = ei_random<int>(0, rows-1),
      c = ei_random<int>(0, cols-1);
  
  Scalar s1 = ei_random<Scalar>();
  
  // test Zero, Ones, Constant, and the set* variants
  m3 = MatrixType::Constant(rows, cols, s1);
  for (int j=0; j<cols; ++j)
    for (int i=0; i<rows; ++i)
    {
      VERIFY_IS_APPROX(mzero(i,j), Scalar(0));
      VERIFY_IS_APPROX(mones(i,j), Scalar(1));
      VERIFY_IS_APPROX(m3(i,j), s1);
    }
  VERIFY(mzero.isZero());
  VERIFY(mones.isOnes());
  VERIFY(m3.isConstant(s1));
  VERIFY(identity.isIdentity());
  VERIFY_IS_APPROX(m4.setConstant(s1), m3);
  VERIFY_IS_APPROX(m4.setConstant(rows,cols,s1), m3);
  VERIFY_IS_APPROX(m4.setZero(), mzero);
  VERIFY_IS_APPROX(m4.setZero(rows,cols), mzero);
  VERIFY_IS_APPROX(m4.setOnes(), mones);
  VERIFY_IS_APPROX(m4.setOnes(rows,cols), mones);
  m4.fill(s1);
  VERIFY_IS_APPROX(m4, m3);
  
  VERIFY_IS_APPROX(v3.setConstant(rows, s1), VectorType::Constant(rows,s1));
  VERIFY_IS_APPROX(v3.setZero(rows), vzero);
  VERIFY_IS_APPROX(v3.setOnes(rows), vones);

  m2 = m2.template binaryExpr<AddIfNull<Scalar> >(mones);

  VERIFY_IS_APPROX(m1.cwise().pow(2), m1.cwise().abs2());
  VERIFY_IS_APPROX(m1.cwise().pow(2), m1.cwise().square());
  VERIFY_IS_APPROX(m1.cwise().pow(3), m1.cwise().cube());

  VERIFY_IS_APPROX(m1 + mones, m1.cwise()+Scalar(1));
  VERIFY_IS_APPROX(m1 - mones, m1.cwise()-Scalar(1));
  m3 = m1; m3.cwise() += 1;
  VERIFY_IS_APPROX(m1 + mones, m3);
  m3 = m1; m3.cwise() -= 1;
  VERIFY_IS_APPROX(m1 - mones, m3);

  VERIFY_IS_APPROX(m2, m2.cwise() * mones);
  VERIFY_IS_APPROX(m1.cwise() * m2,  m2.cwise() * m1);
  m3 = m1;
  m3.cwise() *= m2;
  VERIFY_IS_APPROX(m3, m1.cwise() * m2);
  
  VERIFY_IS_APPROX(mones,    m2.cwise()/m2);
  if(NumTraits<Scalar>::HasFloatingPoint)
  {
    VERIFY_IS_APPROX(m1.cwise() / m2,    m1.cwise() * (m2.cwise().inverse()));
    m3 = m1.cwise().abs().cwise().sqrt();
    VERIFY_IS_APPROX(m3.cwise().square(), m1.cwise().abs());
    VERIFY_IS_APPROX(m1.cwise().square().cwise().sqrt(), m1.cwise().abs());
    VERIFY_IS_APPROX(m1.cwise().abs().cwise().log().cwise().exp() , m1.cwise().abs());

    VERIFY_IS_APPROX(m1.cwise().pow(2), m1.cwise().square());
    m3 = (m1.cwise().abs().cwise()<=RealScalar(0.01)).select(mones,m1);
    VERIFY_IS_APPROX(m3.cwise().pow(-1), m3.cwise().inverse());
    m3 = m1.cwise().abs();
    VERIFY_IS_APPROX(m3.cwise().pow(RealScalar(0.5)), m3.cwise().sqrt());
    
//     VERIFY_IS_APPROX(m1.cwise().tan(), m1.cwise().sin().cwise() / m1.cwise().cos());
    VERIFY_IS_APPROX(mones, m1.cwise().sin().cwise().square() + m1.cwise().cos().cwise().square());
    m3 = m1;
    m3.cwise() /= m2;
    VERIFY_IS_APPROX(m3, m1.cwise() / m2);
  }

  // check min
  VERIFY_IS_APPROX( m1.cwise().min(m2), m2.cwise().min(m1) );
  VERIFY_IS_APPROX( m1.cwise().min(m1+mones), m1 );
  VERIFY_IS_APPROX( m1.cwise().min(m1-mones), m1-mones );

  // check max
  VERIFY_IS_APPROX( m1.cwise().max(m2), m2.cwise().max(m1) );
  VERIFY_IS_APPROX( m1.cwise().max(m1-mones), m1 );
  VERIFY_IS_APPROX( m1.cwise().max(m1+mones), m1+mones );
  
  VERIFY( (m1.cwise() == m1).all() );
  VERIFY( (m1.cwise() != m2).any() );
  VERIFY(!(m1.cwise() == (m1+mones)).any() );
  if (rows*cols>1)
  {
    m3 = m1;
    m3(r,c) += 1;
    VERIFY( (m1.cwise() == m3).any() );
    VERIFY( !(m1.cwise() == m3).all() );
  }
  VERIFY( (m1.cwise().min(m2).cwise() <= m2).all() );
  VERIFY( (m1.cwise().max(m2).cwise() >= m2).all() );
  VERIFY( (m1.cwise().min(m2).cwise() < (m1+mones)).all() );
  VERIFY( (m1.cwise().max(m2).cwise() > (m1-mones)).all() );

#if(__cplusplus < 201103L)
// std::binder* are deprecated since c++11 and will be removed in c++17
  VERIFY( (m1.cwise()<m1.unaryExpr(bind2nd(plus<Scalar>(), Scalar(1)))).all() );
  VERIFY( !(m1.cwise()<m1.unaryExpr(bind2nd(minus<Scalar>(), Scalar(1)))).all() );
  VERIFY( !(m1.cwise()>m1.unaryExpr(bind2nd(plus<Scalar>(), Scalar(1)))).any() );
#endif
}

void test_eigen2_cwiseop()
{
  for(int i = 0; i < g_repeat ; i++) {
    CALL_SUBTEST_1( cwiseops(Matrix<float, 1, 1>()) );
    CALL_SUBTEST_2( cwiseops(Matrix4d()) );
    CALL_SUBTEST_3( cwiseops(MatrixXf(3, 3)) );
    CALL_SUBTEST_3( cwiseops(MatrixXf(22, 22)) );
    CALL_SUBTEST_4( cwiseops(MatrixXi(8, 12)) );
    CALL_SUBTEST_5( cwiseops(MatrixXd(20, 20)) );
  }
}
