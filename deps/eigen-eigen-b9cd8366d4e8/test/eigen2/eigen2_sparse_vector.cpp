// This file is part of Eigen, a lightweight C++ template library
// for linear algebra. Eigen itself is part of the KDE project.
//
// Copyright (C) 2008 Daniel Gomez Ferro <dgomezferro@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "sparse.h"

template<typename Scalar> void sparse_vector(int rows, int cols)
{
  double densityMat = std::max(8./(rows*cols), 0.01);
  double densityVec = std::max(8./float(rows), 0.1);
  typedef Matrix<Scalar,Dynamic,Dynamic> DenseMatrix;
  typedef Matrix<Scalar,Dynamic,1> DenseVector;
  typedef SparseVector<Scalar> SparseVectorType;
  typedef SparseMatrix<Scalar> SparseMatrixType;
  Scalar eps = 1e-6;

  SparseMatrixType m1(rows,cols);
  SparseVectorType v1(rows), v2(rows), v3(rows);
  DenseMatrix refM1 = DenseMatrix::Zero(rows, cols);
  DenseVector refV1 = DenseVector::Random(rows),
    refV2 = DenseVector::Random(rows),
    refV3 = DenseVector::Random(rows);

  std::vector<int> zerocoords, nonzerocoords;
  initSparse<Scalar>(densityVec, refV1, v1, &zerocoords, &nonzerocoords);
  initSparse<Scalar>(densityMat, refM1, m1);

  initSparse<Scalar>(densityVec, refV2, v2);
  initSparse<Scalar>(densityVec, refV3, v3);

  Scalar s1 = ei_random<Scalar>();

  // test coeff and coeffRef
  for (unsigned int i=0; i<zerocoords.size(); ++i)
  {
    VERIFY_IS_MUCH_SMALLER_THAN( v1.coeff(zerocoords[i]), eps );
    //VERIFY_RAISES_ASSERT( v1.coeffRef(zerocoords[i]) = 5 );
  }
  {
    VERIFY(int(nonzerocoords.size()) == v1.nonZeros());
    int j=0;
    for (typename SparseVectorType::InnerIterator it(v1); it; ++it,++j)
    {
      VERIFY(nonzerocoords[j]==it.index());
      VERIFY(it.value()==v1.coeff(it.index()));
      VERIFY(it.value()==refV1.coeff(it.index()));
    }
  }
  VERIFY_IS_APPROX(v1, refV1);

  v1.coeffRef(nonzerocoords[0]) = Scalar(5);
  refV1.coeffRef(nonzerocoords[0]) = Scalar(5);
  VERIFY_IS_APPROX(v1, refV1);

  VERIFY_IS_APPROX(v1+v2, refV1+refV2);
  VERIFY_IS_APPROX(v1+v2+v3, refV1+refV2+refV3);

  VERIFY_IS_APPROX(v1*s1-v2, refV1*s1-refV2);

  VERIFY_IS_APPROX(v1*=s1, refV1*=s1);
  VERIFY_IS_APPROX(v1/=s1, refV1/=s1);
  
  VERIFY_IS_APPROX(v1+=v2, refV1+=refV2);
  VERIFY_IS_APPROX(v1-=v2, refV1-=refV2);

  VERIFY_IS_APPROX(v1.eigen2_dot(v2), refV1.eigen2_dot(refV2));
  VERIFY_IS_APPROX(v1.eigen2_dot(refV2), refV1.eigen2_dot(refV2));

}

void test_eigen2_sparse_vector()
{
  for(int i = 0; i < g_repeat; i++) {
    CALL_SUBTEST_1( sparse_vector<double>(8, 8) );
    CALL_SUBTEST_2( sparse_vector<std::complex<double> >(16, 16) );
    CALL_SUBTEST_1( sparse_vector<double>(299, 535) );
  }
}

