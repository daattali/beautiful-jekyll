// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2008 Benoit Jacob <jacob.benoit.1@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "main.h"

struct TestNew1
{
  MatrixXd m; // good: m will allocate its own array, taking care of alignment.
  TestNew1() : m(20,20) {}
};

struct TestNew2
{
  Matrix3d m; // good: m's size isn't a multiple of 16 bytes, so m doesn't have to be 16-byte aligned,
              // 8-byte alignment is good enough here, which we'll get automatically
};

struct TestNew3
{
  Vector2f m; // good: m's size isn't a multiple of 16 bytes, so m doesn't have to be 16-byte aligned
};

struct TestNew4
{
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  Vector2d m;
  float f; // make the struct have sizeof%16!=0 to make it a little more tricky when we allow an array of 2 such objects
};

struct TestNew5
{
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  float f; // try the f at first -- the EIGEN_ALIGN16 attribute of m should make that still work
  Matrix4f m;
};

struct TestNew6
{
  Matrix<float,2,2,DontAlign> m; // good: no alignment requested
  float f;
};

template<bool Align> struct Depends
{
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW_IF(Align)
  Vector2d m;
  float f;
};

template<typename T>
void check_unalignedassert_good()
{
  T *x, *y;
  x = new T;
  delete x;
  y = new T[2];
  delete[] y;
}

#if EIGEN_ALIGN_STATICALLY
template<typename T>
void construct_at_boundary(int boundary)
{
  char buf[sizeof(T)+256];
  size_t _buf = reinterpret_cast<size_t>(buf);
  _buf += (16 - (_buf % 16)); // make 16-byte aligned
  _buf += boundary; // make exact boundary-aligned
  T *x = ::new(reinterpret_cast<void*>(_buf)) T;
  x[0].setZero(); // just in order to silence warnings
  x->~T();
}
#endif

void unalignedassert()
{
  #if EIGEN_ALIGN_STATICALLY
  construct_at_boundary<Vector2f>(4);
  construct_at_boundary<Vector3f>(4);
  construct_at_boundary<Vector4f>(16);
  construct_at_boundary<Matrix2f>(16);
  construct_at_boundary<Matrix3f>(4);
  construct_at_boundary<Matrix4f>(16);

  construct_at_boundary<Vector2d>(16);
  construct_at_boundary<Vector3d>(4);
  construct_at_boundary<Vector4d>(16);
  construct_at_boundary<Matrix2d>(16);
  construct_at_boundary<Matrix3d>(4);
  construct_at_boundary<Matrix4d>(16);

  construct_at_boundary<Vector2cf>(16);
  construct_at_boundary<Vector3cf>(4);
  construct_at_boundary<Vector2cd>(16);
  construct_at_boundary<Vector3cd>(16);
  #endif

  check_unalignedassert_good<TestNew1>();
  check_unalignedassert_good<TestNew2>();
  check_unalignedassert_good<TestNew3>();

  check_unalignedassert_good<TestNew4>();
  check_unalignedassert_good<TestNew5>();
  check_unalignedassert_good<TestNew6>();
  check_unalignedassert_good<Depends<true> >();

#if EIGEN_ALIGN_STATICALLY
  VERIFY_RAISES_ASSERT(construct_at_boundary<Vector4f>(8));
  VERIFY_RAISES_ASSERT(construct_at_boundary<Matrix4f>(8));
  VERIFY_RAISES_ASSERT(construct_at_boundary<Vector2d>(8));
  VERIFY_RAISES_ASSERT(construct_at_boundary<Vector4d>(8));
  VERIFY_RAISES_ASSERT(construct_at_boundary<Matrix2d>(8));
  VERIFY_RAISES_ASSERT(construct_at_boundary<Matrix4d>(8));
  VERIFY_RAISES_ASSERT(construct_at_boundary<Vector2cf>(8));
  VERIFY_RAISES_ASSERT(construct_at_boundary<Vector2cd>(8));
#endif
}

void test_unalignedassert()
{
  CALL_SUBTEST(unalignedassert());
}
