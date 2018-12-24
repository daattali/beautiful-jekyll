// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2008 Gael Guennebaud <gael.guennebaud@inria.fr>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "main.h"

void test_meta()
{
  VERIFY((internal::conditional<(3<4),internal::true_type, internal::false_type>::type::value));
  VERIFY(( internal::is_same<float,float>::value));
  VERIFY((!internal::is_same<float,double>::value));
  VERIFY((!internal::is_same<float,float&>::value));
  VERIFY((!internal::is_same<float,const float&>::value));
  
  VERIFY(( internal::is_same<float,internal::remove_all<const float&>::type >::value));
  VERIFY(( internal::is_same<float,internal::remove_all<const float*>::type >::value));
  VERIFY(( internal::is_same<float,internal::remove_all<const float*&>::type >::value));
  VERIFY(( internal::is_same<float,internal::remove_all<float**>::type >::value));
  VERIFY(( internal::is_same<float,internal::remove_all<float**&>::type >::value));
  VERIFY(( internal::is_same<float,internal::remove_all<float* const *&>::type >::value));
  VERIFY(( internal::is_same<float,internal::remove_all<float* const>::type >::value));

  // test add_const
  VERIFY(( internal::is_same< internal::add_const<float>::type, const float >::value));
  VERIFY(( internal::is_same< internal::add_const<float*>::type, float* const>::value));
  VERIFY(( internal::is_same< internal::add_const<float const*>::type, float const* const>::value));
  VERIFY(( internal::is_same< internal::add_const<float&>::type, float& >::value));

  // test remove_const
  VERIFY(( internal::is_same< internal::remove_const<float const* const>::type, float const* >::value));
  VERIFY(( internal::is_same< internal::remove_const<float const*>::type, float const* >::value));
  VERIFY(( internal::is_same< internal::remove_const<float* const>::type, float* >::value));

  // test add_const_on_value_type
  VERIFY(( internal::is_same< internal::add_const_on_value_type<float&>::type, float const& >::value));
  VERIFY(( internal::is_same< internal::add_const_on_value_type<float*>::type, float const* >::value));

  VERIFY(( internal::is_same< internal::add_const_on_value_type<float>::type, const float >::value));
  VERIFY(( internal::is_same< internal::add_const_on_value_type<const float>::type, const float >::value));

  VERIFY(( internal::is_same< internal::add_const_on_value_type<const float* const>::type, const float* const>::value));
  VERIFY(( internal::is_same< internal::add_const_on_value_type<float* const>::type, const float* const>::value));
  
  VERIFY(( internal::is_same<float,internal::remove_reference<float&>::type >::value));
  VERIFY(( internal::is_same<const float,internal::remove_reference<const float&>::type >::value));
  VERIFY(( internal::is_same<float,internal::remove_pointer<float*>::type >::value));
  VERIFY(( internal::is_same<const float,internal::remove_pointer<const float*>::type >::value));
  VERIFY(( internal::is_same<float,internal::remove_pointer<float* const >::type >::value));
  
  VERIFY(internal::meta_sqrt<1>::ret == 1);
  #define VERIFY_META_SQRT(X) VERIFY(internal::meta_sqrt<X>::ret == int(std::sqrt(double(X))))
  VERIFY_META_SQRT(2);
  VERIFY_META_SQRT(3);
  VERIFY_META_SQRT(4);
  VERIFY_META_SQRT(5);
  VERIFY_META_SQRT(6);
  VERIFY_META_SQRT(8);
  VERIFY_META_SQRT(9);
  VERIFY_META_SQRT(15);
  VERIFY_META_SQRT(16);
  VERIFY_META_SQRT(17);
  VERIFY_META_SQRT(255);
  VERIFY_META_SQRT(256);
  VERIFY_META_SQRT(257);
  VERIFY_META_SQRT(1023);
  VERIFY_META_SQRT(1024);
  VERIFY_META_SQRT(1025);
}
