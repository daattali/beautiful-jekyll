// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2008-2009 Gael Guennebaud <gael.guennebaud@inria.fr>
// Copyright (C) 2006-2008 Benoit Jacob <jacob.benoit.1@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "main.h"

// using namespace Eigen;

namespace Eigen {
namespace internal {
template<typename T> T negate(const T& x) { return -x; }
}
}

template<typename Scalar> bool isApproxAbs(const Scalar& a, const Scalar& b, const typename NumTraits<Scalar>::Real& refvalue)
{
  return internal::isMuchSmallerThan(a-b, refvalue);
}

template<typename Scalar> bool areApproxAbs(const Scalar* a, const Scalar* b, int size, const typename NumTraits<Scalar>::Real& refvalue)
{
  for (int i=0; i<size; ++i)
  {
    if (!isApproxAbs(a[i],b[i],refvalue))
    {
      std::cout << "[" << Map<const Matrix<Scalar,1,Dynamic> >(a,size) << "]" << " != " << Map<const Matrix<Scalar,1,Dynamic> >(b,size) << "\n";
      return false;
    }
  }
  return true;
}

template<typename Scalar> bool areApprox(const Scalar* a, const Scalar* b, int size)
{
  for (int i=0; i<size; ++i)
  {
    if (a[i]!=b[i] && !internal::isApprox(a[i],b[i]))
    {
      std::cout << "[" << Map<const Matrix<Scalar,1,Dynamic> >(a,size) << "]" << " != " << Map<const Matrix<Scalar,1,Dynamic> >(b,size) << "\n";
      return false;
    }
  }
  return true;
}


#define CHECK_CWISE2(REFOP, POP) { \
  for (int i=0; i<PacketSize; ++i) \
    ref[i] = REFOP(data1[i], data1[i+PacketSize]); \
  internal::pstore(data2, POP(internal::pload<Packet>(data1), internal::pload<Packet>(data1+PacketSize))); \
  VERIFY(areApprox(ref, data2, PacketSize) && #POP); \
}

#define CHECK_CWISE1(REFOP, POP) { \
  for (int i=0; i<PacketSize; ++i) \
    ref[i] = REFOP(data1[i]); \
  internal::pstore(data2, POP(internal::pload<Packet>(data1))); \
  VERIFY(areApprox(ref, data2, PacketSize) && #POP); \
}

template<bool Cond,typename Packet>
struct packet_helper
{
  template<typename T>
  inline Packet load(const T* from) const { return internal::pload<Packet>(from); }

  template<typename T>
  inline void store(T* to, const Packet& x) const { internal::pstore(to,x); }
};

template<typename Packet>
struct packet_helper<false,Packet>
{
  template<typename T>
  inline T load(const T* from) const { return *from; }

  template<typename T>
  inline void store(T* to, const T& x) const { *to = x; }
};

#define CHECK_CWISE1_IF(COND, REFOP, POP) if(COND) { \
  packet_helper<COND,Packet> h; \
  for (int i=0; i<PacketSize; ++i) \
    ref[i] = REFOP(data1[i]); \
  h.store(data2, POP(h.load(data1))); \
  VERIFY(areApprox(ref, data2, PacketSize) && #POP); \
}

#define REF_ADD(a,b) ((a)+(b))
#define REF_SUB(a,b) ((a)-(b))
#define REF_MUL(a,b) ((a)*(b))
#define REF_DIV(a,b) ((a)/(b))

template<typename Scalar> void packetmath()
{
  using std::abs;
  typedef typename internal::packet_traits<Scalar>::type Packet;
  const int PacketSize = internal::packet_traits<Scalar>::size;
  typedef typename NumTraits<Scalar>::Real RealScalar;

  const int size = PacketSize*4;
  EIGEN_ALIGN16 Scalar data1[internal::packet_traits<Scalar>::size*4];
  EIGEN_ALIGN16 Scalar data2[internal::packet_traits<Scalar>::size*4];
  EIGEN_ALIGN16 Packet packets[PacketSize*2];
  EIGEN_ALIGN16 Scalar ref[internal::packet_traits<Scalar>::size*4];
  RealScalar refvalue = 0;
  for (int i=0; i<size; ++i)
  {
    data1[i] = internal::random<Scalar>()/RealScalar(PacketSize);
    data2[i] = internal::random<Scalar>()/RealScalar(PacketSize);
    refvalue = (std::max)(refvalue,abs(data1[i]));
  }

  internal::pstore(data2, internal::pload<Packet>(data1));
  VERIFY(areApprox(data1, data2, PacketSize) && "aligned load/store");

  for (int offset=0; offset<PacketSize; ++offset)
  {
    internal::pstore(data2, internal::ploadu<Packet>(data1+offset));
    VERIFY(areApprox(data1+offset, data2, PacketSize) && "internal::ploadu");
  }

  for (int offset=0; offset<PacketSize; ++offset)
  {
    internal::pstoreu(data2+offset, internal::pload<Packet>(data1));
    VERIFY(areApprox(data1, data2+offset, PacketSize) && "internal::pstoreu");
  }

  for (int offset=0; offset<PacketSize; ++offset)
  {
    packets[0] = internal::pload<Packet>(data1);
    packets[1] = internal::pload<Packet>(data1+PacketSize);
         if (offset==0) internal::palign<0>(packets[0], packets[1]);
    else if (offset==1) internal::palign<1>(packets[0], packets[1]);
    else if (offset==2) internal::palign<2>(packets[0], packets[1]);
    else if (offset==3) internal::palign<3>(packets[0], packets[1]);
    internal::pstore(data2, packets[0]);

    for (int i=0; i<PacketSize; ++i)
      ref[i] = data1[i+offset];

    VERIFY(areApprox(ref, data2, PacketSize) && "internal::palign");
  }

  CHECK_CWISE2(REF_ADD,  internal::padd);
  CHECK_CWISE2(REF_SUB,  internal::psub);
  CHECK_CWISE2(REF_MUL,  internal::pmul);
  #ifndef EIGEN_VECTORIZE_ALTIVEC
  if (!internal::is_same<Scalar,int>::value)
    CHECK_CWISE2(REF_DIV,  internal::pdiv);
  #endif
  CHECK_CWISE1(internal::negate, internal::pnegate);
  CHECK_CWISE1(numext::conj, internal::pconj);

  for(int offset=0;offset<3;++offset)
  {
    for (int i=0; i<PacketSize; ++i)
      ref[i] = data1[offset];
    internal::pstore(data2, internal::pset1<Packet>(data1[offset]));
    VERIFY(areApprox(ref, data2, PacketSize) && "internal::pset1");
  }
  
  VERIFY(internal::isApprox(data1[0], internal::pfirst(internal::pload<Packet>(data1))) && "internal::pfirst");
  
  if(PacketSize>1)
  {
    for(int offset=0;offset<4;++offset)
    {
      for(int i=0;i<PacketSize/2;++i)
        ref[2*i+0] = ref[2*i+1] = data1[offset+i];
      internal::pstore(data2,internal::ploaddup<Packet>(data1+offset));
      VERIFY(areApprox(ref, data2, PacketSize) && "ploaddup");
    }
  }

  ref[0] = 0;
  for (int i=0; i<PacketSize; ++i)
    ref[0] += data1[i];
  VERIFY(isApproxAbs(ref[0], internal::predux(internal::pload<Packet>(data1)), refvalue) && "internal::predux");

  ref[0] = 1;
  for (int i=0; i<PacketSize; ++i)
    ref[0] *= data1[i];
  VERIFY(internal::isApprox(ref[0], internal::predux_mul(internal::pload<Packet>(data1))) && "internal::predux_mul");

  for (int j=0; j<PacketSize; ++j)
  {
    ref[j] = 0;
    for (int i=0; i<PacketSize; ++i)
      ref[j] += data1[i+j*PacketSize];
    packets[j] = internal::pload<Packet>(data1+j*PacketSize);
  }
  internal::pstore(data2, internal::preduxp(packets));
  VERIFY(areApproxAbs(ref, data2, PacketSize, refvalue) && "internal::preduxp");

  for (int i=0; i<PacketSize; ++i)
    ref[i] = data1[PacketSize-i-1];
  internal::pstore(data2, internal::preverse(internal::pload<Packet>(data1)));
  VERIFY(areApprox(ref, data2, PacketSize) && "internal::preverse");
}

template<typename Scalar> void packetmath_real()
{
  using std::abs;
  typedef typename internal::packet_traits<Scalar>::type Packet;
  const int PacketSize = internal::packet_traits<Scalar>::size;

  const int size = PacketSize*4;
  EIGEN_ALIGN16 Scalar data1[internal::packet_traits<Scalar>::size*4];
  EIGEN_ALIGN16 Scalar data2[internal::packet_traits<Scalar>::size*4];
  EIGEN_ALIGN16 Scalar ref[internal::packet_traits<Scalar>::size*4];

  for (int i=0; i<size; ++i)
  {
    data1[i] = internal::random<Scalar>(-1,1) * std::pow(Scalar(10), internal::random<Scalar>(-3,3));
    data2[i] = internal::random<Scalar>(-1,1) * std::pow(Scalar(10), internal::random<Scalar>(-3,3));
  }
  CHECK_CWISE1_IF(internal::packet_traits<Scalar>::HasSin, std::sin, internal::psin);
  CHECK_CWISE1_IF(internal::packet_traits<Scalar>::HasCos, std::cos, internal::pcos);
  CHECK_CWISE1_IF(internal::packet_traits<Scalar>::HasTan, std::tan, internal::ptan);
  
  for (int i=0; i<size; ++i)
  {
    data1[i] = internal::random<Scalar>(-1,1);
    data2[i] = internal::random<Scalar>(-1,1);
  }
  CHECK_CWISE1_IF(internal::packet_traits<Scalar>::HasASin, std::asin, internal::pasin);
  CHECK_CWISE1_IF(internal::packet_traits<Scalar>::HasACos, std::acos, internal::pacos);

  for (int i=0; i<size; ++i)
  {
    data1[i] = internal::random<Scalar>(-87,88);
    data2[i] = internal::random<Scalar>(-87,88);
  }
  CHECK_CWISE1_IF(internal::packet_traits<Scalar>::HasExp, std::exp, internal::pexp);
  {
    data1[0] = std::numeric_limits<Scalar>::quiet_NaN();
    packet_helper<internal::packet_traits<Scalar>::HasExp,Packet> h;
    h.store(data2, internal::pexp(h.load(data1))); 
    VERIFY(isNaN(data2[0]));
  }

  for (int i=0; i<size; ++i)
  {
    data1[i] = internal::random<Scalar>(0,1) * std::pow(Scalar(10), internal::random<Scalar>(-6,6));
    data2[i] = internal::random<Scalar>(0,1) * std::pow(Scalar(10), internal::random<Scalar>(-6,6));
  }
  if(internal::random<float>(0,1)<0.1)
    data1[internal::random<int>(0, PacketSize)] = 0;
  CHECK_CWISE1_IF(internal::packet_traits<Scalar>::HasSqrt, std::sqrt, internal::psqrt);
  CHECK_CWISE1_IF(internal::packet_traits<Scalar>::HasLog, std::log, internal::plog);
  {
    data1[0] = std::numeric_limits<Scalar>::quiet_NaN();
    packet_helper<internal::packet_traits<Scalar>::HasLog,Packet> h;
    h.store(data2, internal::plog(h.load(data1)));
    VERIFY(isNaN(data2[0]));
    data1[0] = -1.0f;
    h.store(data2, internal::plog(h.load(data1)));
    VERIFY(isNaN(data2[0]));
#if !EIGEN_FAST_MATH
    h.store(data2, internal::psqrt(h.load(data1)));
    VERIFY(isNaN(data2[0]));
    VERIFY(isNaN(data2[1]));
#endif
  }
}

template<typename Scalar> void packetmath_notcomplex()
{
  using std::abs;
  typedef typename internal::packet_traits<Scalar>::type Packet;
  const int PacketSize = internal::packet_traits<Scalar>::size;

  EIGEN_ALIGN16 Scalar data1[internal::packet_traits<Scalar>::size*4];
  EIGEN_ALIGN16 Scalar data2[internal::packet_traits<Scalar>::size*4];
  EIGEN_ALIGN16 Scalar ref[internal::packet_traits<Scalar>::size*4];
  
  Array<Scalar,Dynamic,1>::Map(data1, internal::packet_traits<Scalar>::size*4).setRandom();

  ref[0] = data1[0];
  for (int i=0; i<PacketSize; ++i)
    ref[0] = (std::min)(ref[0],data1[i]);
  VERIFY(internal::isApprox(ref[0], internal::predux_min(internal::pload<Packet>(data1))) && "internal::predux_min");

  CHECK_CWISE2((std::min), internal::pmin);
  CHECK_CWISE2((std::max), internal::pmax);
  CHECK_CWISE1(abs, internal::pabs);

  ref[0] = data1[0];
  for (int i=0; i<PacketSize; ++i)
    ref[0] = (std::max)(ref[0],data1[i]);
  VERIFY(internal::isApprox(ref[0], internal::predux_max(internal::pload<Packet>(data1))) && "internal::predux_max");
  
  for (int i=0; i<PacketSize; ++i)
    ref[i] = data1[0]+Scalar(i);
  internal::pstore(data2, internal::plset(data1[0]));
  VERIFY(areApprox(ref, data2, PacketSize) && "internal::plset");
}

template<typename Scalar,bool ConjLhs,bool ConjRhs> void test_conj_helper(Scalar* data1, Scalar* data2, Scalar* ref, Scalar* pval)
{
  typedef typename internal::packet_traits<Scalar>::type Packet;
  const int PacketSize = internal::packet_traits<Scalar>::size;
  
  internal::conj_if<ConjLhs> cj0;
  internal::conj_if<ConjRhs> cj1;
  internal::conj_helper<Scalar,Scalar,ConjLhs,ConjRhs> cj;
  internal::conj_helper<Packet,Packet,ConjLhs,ConjRhs> pcj;
  
  for(int i=0;i<PacketSize;++i)
  {
    ref[i] = cj0(data1[i]) * cj1(data2[i]);
    VERIFY(internal::isApprox(ref[i], cj.pmul(data1[i],data2[i])) && "conj_helper pmul");
  }
  internal::pstore(pval,pcj.pmul(internal::pload<Packet>(data1),internal::pload<Packet>(data2)));
  VERIFY(areApprox(ref, pval, PacketSize) && "conj_helper pmul");
  
  for(int i=0;i<PacketSize;++i)
  {
    Scalar tmp = ref[i];
    ref[i] += cj0(data1[i]) * cj1(data2[i]);
    VERIFY(internal::isApprox(ref[i], cj.pmadd(data1[i],data2[i],tmp)) && "conj_helper pmadd");
  }
  *pval += 0; // Workaround msvc 2013 issue (bad code generation)
  internal::pstore(pval,pcj.pmadd(internal::pload<Packet>(data1),internal::pload<Packet>(data2),internal::pload<Packet>(pval)));
  VERIFY(areApprox(ref, pval, PacketSize) && "conj_helper pmadd");
}

template<typename Scalar> void packetmath_complex()
{
  typedef typename internal::packet_traits<Scalar>::type Packet;
  const int PacketSize = internal::packet_traits<Scalar>::size;

  const int size = PacketSize*4;
  EIGEN_ALIGN16 Scalar data1[PacketSize*4];
  EIGEN_ALIGN16 Scalar data2[PacketSize*4];
  EIGEN_ALIGN16 Scalar ref[PacketSize*4];
  EIGEN_ALIGN16 Scalar pval[PacketSize*4];

  for (int i=0; i<size; ++i)
  {
    data1[i] = internal::random<Scalar>() * Scalar(1e2);
    data2[i] = internal::random<Scalar>() * Scalar(1e2);
  }
  
  test_conj_helper<Scalar,false,false> (data1,data2,ref,pval);
  test_conj_helper<Scalar,false,true>  (data1,data2,ref,pval);
  test_conj_helper<Scalar,true,false>  (data1,data2,ref,pval);
  test_conj_helper<Scalar,true,true>   (data1,data2,ref,pval);
  
  {
    for(int i=0;i<PacketSize;++i)
      ref[i] = Scalar(std::imag(data1[i]),std::real(data1[i]));
    internal::pstore(pval,internal::pcplxflip(internal::pload<Packet>(data1)));
    VERIFY(areApprox(ref, pval, PacketSize) && "pcplxflip");
  }
  
  
}

void test_packetmath()
{
  for(int i = 0; i < g_repeat; i++) {
    CALL_SUBTEST_1( packetmath<float>() );
    CALL_SUBTEST_2( packetmath<double>() );
    CALL_SUBTEST_3( packetmath<int>() );
    CALL_SUBTEST_1( packetmath<std::complex<float> >() );
    CALL_SUBTEST_2( packetmath<std::complex<double> >() );

    CALL_SUBTEST_1( packetmath_notcomplex<float>() );
    CALL_SUBTEST_2( packetmath_notcomplex<double>() );
    CALL_SUBTEST_3( packetmath_notcomplex<int>() );
    
    CALL_SUBTEST_1( packetmath_real<float>() );
    CALL_SUBTEST_2( packetmath_real<double>() );

    CALL_SUBTEST_1( packetmath_complex<std::complex<float> >() );
    CALL_SUBTEST_2( packetmath_complex<std::complex<double> >() );
  }
}
