// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2006-2010 Benoit Jacob <jacob.benoit.1@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_NO_STATIC_ASSERT
#define EIGEN_NO_STATIC_ASSERT // turn static asserts into runtime asserts in order to check them
#endif

#include "main.h"

template<typename VectorType> void map_class_vector(const VectorType& m)
{
  typedef typename VectorType::Index Index;
  typedef typename VectorType::Scalar Scalar;

  Index size = m.size();

  // test Map.h
  Scalar* array1 = internal::aligned_new<Scalar>(size);
  Scalar* array2 = internal::aligned_new<Scalar>(size);
  Scalar* array3 = new Scalar[size+1];
  Scalar* array3unaligned = size_t(array3)%16 == 0 ? array3+1 : array3;

  Map<VectorType, Aligned>(array1, size) = VectorType::Random(size);
  Map<VectorType, Aligned>(array2, size) = Map<VectorType,Aligned>(array1, size);
  Map<VectorType>(array3unaligned, size) = Map<VectorType>(array1, size);
  VectorType ma1 = Map<VectorType, Aligned>(array1, size);
  VectorType ma2 = Map<VectorType, Aligned>(array2, size);
  VectorType ma3 = Map<VectorType>(array3unaligned, size);
  VERIFY_IS_EQUAL(ma1, ma2);
  VERIFY_IS_EQUAL(ma1, ma3);
  #ifdef EIGEN_VECTORIZE
  if(internal::packet_traits<Scalar>::Vectorizable)
    VERIFY_RAISES_ASSERT((Map<VectorType,Aligned>(array3unaligned, size)))
  #endif

  internal::aligned_delete(array1, size);
  internal::aligned_delete(array2, size);
  delete[] array3;
}

template<typename MatrixType> void map_class_matrix(const MatrixType& m)
{
  typedef typename MatrixType::Index Index;
  typedef typename MatrixType::Scalar Scalar;

  Index rows = m.rows(), cols = m.cols(), size = rows*cols;

  // test Map.h
  Scalar* array1 = internal::aligned_new<Scalar>(size);
  for(int i = 0; i < size; i++) array1[i] = Scalar(1);
  Scalar* array2 = internal::aligned_new<Scalar>(size);
  for(int i = 0; i < size; i++) array2[i] = Scalar(1);
  Scalar* array3 = new Scalar[size+1];
  for(int i = 0; i < size+1; i++) array3[i] = Scalar(1);
  Scalar* array3unaligned = size_t(array3)%16 == 0 ? array3+1 : array3;
  Map<MatrixType, Aligned>(array1, rows, cols) = MatrixType::Ones(rows,cols);
  Map<MatrixType>(array2, rows, cols) = Map<MatrixType>(array1, rows, cols);
  Map<MatrixType>(array3unaligned, rows, cols) = Map<MatrixType>(array1, rows, cols);
  MatrixType ma1 = Map<MatrixType>(array1, rows, cols);
  MatrixType ma2 = Map<MatrixType, Aligned>(array2, rows, cols);
  VERIFY_IS_EQUAL(ma1, ma2);
  MatrixType ma3 = Map<MatrixType>(array3unaligned, rows, cols);
  VERIFY_IS_EQUAL(ma1, ma3);

  internal::aligned_delete(array1, size);
  internal::aligned_delete(array2, size);
  delete[] array3;
}

template<typename VectorType> void map_static_methods(const VectorType& m)
{
  typedef typename VectorType::Index Index;
  typedef typename VectorType::Scalar Scalar;

  Index size = m.size();

  // test Map.h
  Scalar* array1 = internal::aligned_new<Scalar>(size);
  Scalar* array2 = internal::aligned_new<Scalar>(size);
  Scalar* array3 = new Scalar[size+1];
  Scalar* array3unaligned = size_t(array3)%16 == 0 ? array3+1 : array3;

  VectorType::MapAligned(array1, size) = VectorType::Random(size);
  VectorType::Map(array2, size) = VectorType::Map(array1, size);
  VectorType::Map(array3unaligned, size) = VectorType::Map(array1, size);
  VectorType ma1 = VectorType::Map(array1, size);
  VectorType ma2 = VectorType::MapAligned(array2, size);
  VectorType ma3 = VectorType::Map(array3unaligned, size);
  VERIFY_IS_EQUAL(ma1, ma2);
  VERIFY_IS_EQUAL(ma1, ma3);

  internal::aligned_delete(array1, size);
  internal::aligned_delete(array2, size);
  delete[] array3;
}

template<typename PlainObjectType> void check_const_correctness(const PlainObjectType&)
{
  // there's a lot that we can't test here while still having this test compile!
  // the only possible approach would be to run a script trying to compile stuff and checking that it fails.
  // CMake can help with that.

  // verify that map-to-const don't have LvalueBit
  typedef typename internal::add_const<PlainObjectType>::type ConstPlainObjectType;
  VERIFY( !(internal::traits<Map<ConstPlainObjectType> >::Flags & LvalueBit) );
  VERIFY( !(internal::traits<Map<ConstPlainObjectType, Aligned> >::Flags & LvalueBit) );
  VERIFY( !(Map<ConstPlainObjectType>::Flags & LvalueBit) );
  VERIFY( !(Map<ConstPlainObjectType, Aligned>::Flags & LvalueBit) );
}

template<typename Scalar>
void map_not_aligned_on_scalar()
{
  typedef Matrix<Scalar,Dynamic,Dynamic> MatrixType;
  typedef typename MatrixType::Index Index;
  Index size = 11;
  Scalar* array1 = internal::aligned_new<Scalar>((size+1)*(size+1)+1);
  Scalar* array2 = reinterpret_cast<Scalar*>(sizeof(Scalar)/2+std::size_t(array1));
  Map<MatrixType,0,OuterStride<> > map2(array2, size, size, OuterStride<>(size+1));
  MatrixType m2 = MatrixType::Random(size,size);
  map2 = m2;
  VERIFY_IS_EQUAL(m2, map2);
  
  typedef Matrix<Scalar,Dynamic,1> VectorType;
  Map<VectorType> map3(array2, size);
  MatrixType v3 = VectorType::Random(size);
  map3 = v3;
  VERIFY_IS_EQUAL(v3, map3);
  
  internal::aligned_delete(array1, (size+1)*(size+1)+1);
}

void test_mapped_matrix()
{
  for(int i = 0; i < g_repeat; i++) {
    CALL_SUBTEST_1( map_class_vector(Matrix<float, 1, 1>()) );
    CALL_SUBTEST_1( check_const_correctness(Matrix<float, 1, 1>()) );
    CALL_SUBTEST_2( map_class_vector(Vector4d()) );
    CALL_SUBTEST_2( check_const_correctness(Matrix4d()) );
    CALL_SUBTEST_3( map_class_vector(RowVector4f()) );
    CALL_SUBTEST_4( map_class_vector(VectorXcf(8)) );
    CALL_SUBTEST_5( map_class_vector(VectorXi(12)) );
    CALL_SUBTEST_5( check_const_correctness(VectorXi(12)) );

    CALL_SUBTEST_1( map_class_matrix(Matrix<float, 1, 1>()) );
    CALL_SUBTEST_2( map_class_matrix(Matrix4d()) );
    CALL_SUBTEST_11( map_class_matrix(Matrix<float,3,5>()) );
    CALL_SUBTEST_4( map_class_matrix(MatrixXcf(internal::random<int>(1,10),internal::random<int>(1,10))) );
    CALL_SUBTEST_5( map_class_matrix(MatrixXi(internal::random<int>(1,10),internal::random<int>(1,10))) );

    CALL_SUBTEST_6( map_static_methods(Matrix<double, 1, 1>()) );
    CALL_SUBTEST_7( map_static_methods(Vector3f()) );
    CALL_SUBTEST_8( map_static_methods(RowVector3d()) );
    CALL_SUBTEST_9( map_static_methods(VectorXcd(8)) );
    CALL_SUBTEST_10( map_static_methods(VectorXf(12)) );
    
    CALL_SUBTEST_11( map_not_aligned_on_scalar<double>() );
  }
}
