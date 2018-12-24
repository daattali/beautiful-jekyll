// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2009 Benoit Jacob <jacob.benoit.1@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "main.h"

using namespace std;
template<typename MatrixType> void permutationmatrices(const MatrixType& m)
{
  typedef typename MatrixType::Index Index;
  typedef typename MatrixType::Scalar Scalar;
  enum { Rows = MatrixType::RowsAtCompileTime, Cols = MatrixType::ColsAtCompileTime,
         Options = MatrixType::Options };
  typedef PermutationMatrix<Rows> LeftPermutationType;
  typedef Matrix<int, Rows, 1> LeftPermutationVectorType;
  typedef Map<LeftPermutationType> MapLeftPerm;
  typedef PermutationMatrix<Cols> RightPermutationType;
  typedef Matrix<int, Cols, 1> RightPermutationVectorType;
  typedef Map<RightPermutationType> MapRightPerm;

  Index rows = m.rows();
  Index cols = m.cols();

  MatrixType m_original = MatrixType::Random(rows,cols);
  LeftPermutationVectorType lv;
  randomPermutationVector(lv, rows);
  LeftPermutationType lp(lv);
  RightPermutationVectorType rv;
  randomPermutationVector(rv, cols);
  RightPermutationType rp(rv);
  MatrixType m_permuted = lp * m_original * rp;

  for (int i=0; i<rows; i++)
    for (int j=0; j<cols; j++)
        VERIFY_IS_APPROX(m_permuted(lv(i),j), m_original(i,rv(j)));

  Matrix<Scalar,Rows,Rows> lm(lp);
  Matrix<Scalar,Cols,Cols> rm(rp);

  VERIFY_IS_APPROX(m_permuted, lm*m_original*rm);

  VERIFY_IS_APPROX(lp.inverse()*m_permuted*rp.inverse(), m_original);
  VERIFY_IS_APPROX(lv.asPermutation().inverse()*m_permuted*rv.asPermutation().inverse(), m_original);
  VERIFY_IS_APPROX(MapLeftPerm(lv.data(),lv.size()).inverse()*m_permuted*MapRightPerm(rv.data(),rv.size()).inverse(), m_original);
  
  VERIFY((lp*lp.inverse()).toDenseMatrix().isIdentity());
  VERIFY((lv.asPermutation()*lv.asPermutation().inverse()).toDenseMatrix().isIdentity());
  VERIFY((MapLeftPerm(lv.data(),lv.size())*MapLeftPerm(lv.data(),lv.size()).inverse()).toDenseMatrix().isIdentity());

  LeftPermutationVectorType lv2;
  randomPermutationVector(lv2, rows);
  LeftPermutationType lp2(lv2);
  Matrix<Scalar,Rows,Rows> lm2(lp2);
  VERIFY_IS_APPROX((lp*lp2).toDenseMatrix().template cast<Scalar>(), lm*lm2);
  VERIFY_IS_APPROX((lv.asPermutation()*lv2.asPermutation()).toDenseMatrix().template cast<Scalar>(), lm*lm2);
  VERIFY_IS_APPROX((MapLeftPerm(lv.data(),lv.size())*MapLeftPerm(lv2.data(),lv2.size())).toDenseMatrix().template cast<Scalar>(), lm*lm2);

  LeftPermutationType identityp;
  identityp.setIdentity(rows);
  VERIFY_IS_APPROX(m_original, identityp*m_original);

  // check inplace permutations
  m_permuted = m_original;
  m_permuted = lp.inverse() * m_permuted;
  VERIFY_IS_APPROX(m_permuted, lp.inverse()*m_original);

  m_permuted = m_original;
  m_permuted = m_permuted * rp.inverse();
  VERIFY_IS_APPROX(m_permuted, m_original*rp.inverse());

  m_permuted = m_original;
  m_permuted = lp * m_permuted;
  VERIFY_IS_APPROX(m_permuted, lp*m_original);

  m_permuted = m_original;
  m_permuted = m_permuted * rp;
  VERIFY_IS_APPROX(m_permuted, m_original*rp);

  if(rows>1 && cols>1)
  {
    lp2 = lp;
    Index i = internal::random<Index>(0, rows-1);
    Index j;
    do j = internal::random<Index>(0, rows-1); while(j==i);
    lp2.applyTranspositionOnTheLeft(i, j);
    lm = lp;
    lm.row(i).swap(lm.row(j));
    VERIFY_IS_APPROX(lm, lp2.toDenseMatrix().template cast<Scalar>());

    RightPermutationType rp2 = rp;
    i = internal::random<Index>(0, cols-1);
    do j = internal::random<Index>(0, cols-1); while(j==i);
    rp2.applyTranspositionOnTheRight(i, j);
    rm = rp;
    rm.col(i).swap(rm.col(j));
    VERIFY_IS_APPROX(rm, rp2.toDenseMatrix().template cast<Scalar>());
  }  
}

void test_permutationmatrices()
{
  for(int i = 0; i < g_repeat; i++) {
    CALL_SUBTEST_1( permutationmatrices(Matrix<float, 1, 1>()) );
    CALL_SUBTEST_2( permutationmatrices(Matrix3f()) );
    CALL_SUBTEST_3( permutationmatrices(Matrix<double,3,3,RowMajor>()) );
    CALL_SUBTEST_4( permutationmatrices(Matrix4d()) );
    CALL_SUBTEST_5( permutationmatrices(Matrix<double,40,60>()) );
    CALL_SUBTEST_6( permutationmatrices(Matrix<double,Dynamic,Dynamic,RowMajor>(20, 30)) );
    CALL_SUBTEST_7( permutationmatrices(MatrixXcf(15, 10)) );
  }
}
