/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file MPolynomial.h
 *
 * @author Felix Fontein (\c felix@fontein.de), University of Zurich,
 * Switzerland
 *
 * Adapted by Jacques-Olivier Lachaud (\c
 * jacques-olivier.lachaud@univ-savoie.fr ) Laboratory of Mathematics
 * (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2012/02/12
 *
 * Afil containing the class that implements multivariate polynomials.
 *
 * This file is part of the DGtal library.
 */

#if defined(MPolynomial_RECURSES)
#error Recursive header files inclusion detected in MPolynomial.h
#else // defined(MPolynomial_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MPolynomial_RECURSES

#if !defined MPolynomial_h
/** Prevents repeated inclusion of headers. */
#define MPolynomial_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  template < int n, typename TRing, 
             typename TAlloc = std::allocator<TRing> >
  class MPolynomial;
  template < int N, int n, typename TRing, 
             typename TAlloc = std::allocator<TRing> >
  class MPolynomialDerivativeComputer;
  template < int n, typename TRing, 
             typename TAlloc = std::allocator<TRing>, 
             typename TX = TRing >
  class MPolynomialEvaluator;

  template < int n,  typename TRing, typename TOwner, 
             typename TAlloc, typename TX >
  class MPolynomialEvaluatorImpl;

  /**
     Forward declaration, to be able to declare this as a friend.
  */
  template < typename TRing, typename TAlloc >
  void euclidDiv( const MPolynomial<1, TRing, TAlloc> & f, 
                  const MPolynomial<1, TRing, TAlloc> & g, 
                  MPolynomial<1, TRing, TAlloc> & q, 
                  MPolynomial<1, TRing, TAlloc> & r );

  /**
     Description of template class 'MPolynomialEvaluatorImpl' <p> 
     
     Specialization of MPolynomialEvaluatorImpl for 1 variable.

     This class is a backport from <a
     href="http://spielwiese.fontein.de/">Spielwiese</a>.
  */
  template < typename TRing, typename TOwner, 
             typename TAlloc, typename TX >
  class MPolynomialEvaluatorImpl< 1, TRing, TOwner, TAlloc, TX >
  {
  public:
    typedef TRing Ring;
    typedef TOwner Owner;
    typedef TAlloc Alloc;
    typedef TX X;

    template <int nn, class TT, class AA, class SS>
    friend class MPolynomialEvaluator;
    
    template <int nn, class TT, class HLHL, class AA, class SS>
    friend class MPolynomialEvaluatorImpl;

private:
    const Owner & myOwner; ///< The "owner"
    const X & myEvalPoint; ///< The evaluation point on this level
    
    inline MPolynomialEvaluatorImpl( const Owner & owner, const X & evalpoint)
        : myOwner(owner), myEvalPoint(evalpoint)
    {}
    
    /**
       Evaluates a polynomial of type MPolynomial<1, T> in myEvalPoint.
    */
    class EvalFun
    {
      const MPolynomialEvaluatorImpl<1, Ring, Owner, Alloc, X> & myOwner;
        
    public:
      inline 
      EvalFun( const MPolynomialEvaluatorImpl<1, Ring, Owner, Alloc, X> & 
               owner )
        : myOwner(owner)
      {}
      
      /**
         Evalutate polynomial \a p at the point stored in myOwner.
         @param p a monovariate polynomial.
         @return the value of p at the point.
      */
      inline
      X operator() ( const MPolynomial<1, Ring, Alloc> & p ) const
      {
        X res = (X) 0;
        X xx = (X) 1;
        for ( int i = 0; i < (int) p.myValue.size(); ++i )
          {
            res += (X)(Ring) p.myValue[i] * xx;
            xx = xx * myOwner.myEvalPoint;
          }
        return res;
      }
    };
    
public:
    /** 
        Cast operator to type X (the explicit type of the variable).
    */
    inline operator X() const
    {
        X res = (X) 0;
        myOwner.evaluate( res, EvalFun( *this ) );
        return res;
    }

    /**
       Explicit evaluate. Essentially calls operator S().
    */
    inline X operator() () const
    {
      return (X)(*this);
    }
    
  };

  /**
     Description of template class 'MPolynomialEvaluatorImpl' <p> 

     Another helper for polynomial evaluation. This template is
     returned from MPolynomialEvaluator<n, TRing, TAlloc>::operator().
 
     The template parameter TOwner is the type of the "owner" of this
     template, i.e. either MPolynomialEvaluator<n+1, TRing, TAlloc> or
     MPolynomialEvaluatorImpl<n+1, TRing, ..., TAlloc>.

     This class is a backport from <a
     href="http://spielwiese.fontein.de/">Spielwiese</a>.

  */
  template < int n, typename TRing, typename TOwner, 
             typename TAlloc, typename TX >
  class MPolynomialEvaluatorImpl
  {
  public:
    typedef TRing Ring;
    typedef TOwner Owner;
    typedef TAlloc Alloc;
    typedef TX X;
    /// Type for the multivariate polynomial
    typedef MPolynomial< n, Ring, Alloc> MPolyN;
    
    /** 
        Type for the "child" multivariate polynomial, where the first
        variable X has been substituted by its value. Note that the
        ring type has been substituted by the type of the variable
        (i.e. X).
    */
    typedef MPolynomial< n - 1, X, 
                         typename Alloc::template rebind<X>::other > MPolyNM1;

    template<int nn, class TT, class AA, class SS>
    friend class MPolynomialEvaluator;
    
    template<int nn, class TT, class HLHL, class AA, class SS>
    friend class MPolynomialEvaluatorImpl;
    
  private:
    const Owner & myOwner; // The "owner"
    const X & myEvalPoint; // The evaluation point on this level
    
    inline 
    MPolynomialEvaluatorImpl(const Owner & owner, const X & evalpoint)
        : myOwner(owner), myEvalPoint(evalpoint)
    {}
    
    /**
       Evaluates a polynomial of type MPolynomial<n, TRing> in myEvalPoint; the
       coefficients of the first indeterminate are evaluated using the
       given functor of type Fun.
    */
    template < typename XX, typename Fun >
    class EvalFun
    {
      const MPolynomialEvaluatorImpl<n, Ring, Owner, Alloc, X> & myOwner;
      const Fun & myEvalFun;
      
    public:
      inline 
      EvalFun( const MPolynomialEvaluatorImpl<n, Ring, Owner, Alloc, X> & owner, 
               const Fun & evalfun)
        : myOwner(owner), myEvalFun(evalfun)
      {}
        
      /**
         Evaluate: the first indeterminate is replaced by myEvalPoint,
         and the coefficients of the first indeterminate (which are
         polynomials of type poly<n-1, T>) are evaluated using
         myEvalFun.
      */
      inline XX operator() ( const MPolynomial<n, Ring, Alloc> & p ) const
      {
        XX res = (XX) 0;
        X xx = (X) 1;
        for ( int i = 0; i < (int) p.myValue.size(); ++i )
          {
            res += myEvalFun(p.myValue[i]) * (XX) xx;
            xx = xx * myOwner.myEvalPoint;
          }
        return res;
      }
    };

    /**
       This will be called from a child (i.e. a class of type
       MPolynomialEvaluatorImpl<n-1, Ring,
       MPolynomialEvaluator<n,Ring,Owner,Alloc,X>, Alloc, X>) to
       trigger evaluation.
    */
    template < typename XX, typename Fun >
    inline 
    void evaluate( XX & res, const Fun & evalfun ) const
    {
        // We have to pass evaluation on to our owner, but give a new
        // functor which now evaluates polynomials of type poly<n, T>.
      myOwner.evaluate( res, EvalFun< XX, Fun >( *this, evalfun ) );
    }
    
    /**
      Evaluates a polynomial of type poly<n, T> in myEvalPoint; the
      coefficients of the first indeterminate (which are polynomials
      of type poly<n-1, Ring>) are casted to poly<n-1, X>, and the result
      is of type poly<n-1, X> as well.
    */
    class EvalFun2
    {
      const MPolynomialEvaluatorImpl<n, Ring, Owner, Alloc, X> & myOwner;
      
    public:
      inline 
      EvalFun2( const MPolynomialEvaluatorImpl<n, Ring, Owner, Alloc, X> & owner)
        : myOwner(owner)
      {
      }
      
      /**
         Evaluate: the first indeterminate is replaced by myEvalPoint,
         and the coefficients of the first indeterminate (which are
         polynomials of type poly<n-1, Ring>) are casted to the type
         poly<n-1, X>.
      */
      inline MPolyNM1 operator() (const MPolyN & p) const
        {
          MPolyNM1 res;
          X xx = (X) 1;
          for ( int i = 0; i < (int) p.myValue.size(); ++i )
            {
              res += ( (MPolyNM1) p.myValue[i] ) * xx;
              xx = xx * myOwner.myEvalPoint;
            }
          return res;
        }
    };
    
  public:
    /**
       Allows casting to poly<n-1, S>.
    */
    inline
    operator MPolyNM1() const
    // operator poly<n - 1, S, typename Alloc::template rebind<S>::other>() const
    {
      MPolyNM1 res; // missing: determine allocator object
      // We need to pass evaluation on to our owner
      myOwner.evaluate( res, EvalFun2( *this ) );
      return res;
    }
    
    /**
      Continues evaluation with the next indeterminant.  Functor
      returining a "child" evaluator implementation.
      @param x the next indeterminant.
    */
    template < typename XX >
    inline 
    MPolynomialEvaluatorImpl
    < n - 1, Ring, 
      MPolynomialEvaluatorImpl< n, Ring, Owner, Alloc, X >,
      Alloc, XX > operator() ( const XX & x ) const
      {
        return MPolynomialEvaluatorImpl
          < n - 1, Ring, MPolynomialEvaluatorImpl< n, Ring, Owner, Alloc, X>, 
            Alloc, XX >( *this, x );
      }
  };

  /**
     The top level polynomial evaluation class, in case n = 1,
     i.e. does direct evaluation.

     This class is a backport from <a
     href="http://spielwiese.fontein.de/">Spielwiese</a>.

  */
  template < typename TRing, typename TAlloc, typename TX >
  class MPolynomialEvaluator< 1, TRing, TAlloc, TX>
  {
    friend class MPolynomial< 1, TRing, TAlloc >;
  public:
    typedef TRing Ring;
    typedef TAlloc Alloc;
    typedef TX X;
    typedef MPolynomial< 1, Ring, Alloc > MPoly1;

  private:
    const MPoly1 & myPoly; ///< The polynomial in question
    const X & myEvalPoint; ///< The evaluation point
    
    inline 
    MPolynomialEvaluator( const MPoly1 & poly, const X & evalpoint)
      : myPoly( poly ), myEvalPoint( evalpoint )
    {}
    
  public:
    /**
       Casting to X is done by evaluation in myEvalPoint.
    */
    inline 
    operator X() const
    {
      X res = (X) 0;
      X xx = (X) 1;
      for ( int i = 0; i < (int) myPoly.myValue.size(); ++i )
        {
          res += ( (X) (Ring) myPoly.myValue[i] ) * xx;
          xx = xx * myEvalPoint;
        }
      return res;
    }
    
    /**
       Evaluates and returns value in X.
    */
    inline
    X operator() () const
    {
      return (X) (*this);
    }
  };


  /**
     The top level polynomial evaluation class, in case n > 1, i.e. in
     case the coefficients are polynomials by themselves.

     This class is a backport from <a
     href="http://spielwiese.fontein.de/">Spielwiese</a>.

  */
  template < int n, typename TRing, typename TAlloc, typename TX >
  class MPolynomialEvaluator
  {
    friend class MPolynomial< n, TRing, TAlloc>;

    template<int nn, class TT, class HLHL, class AA, class SS>
    friend class MPolynomialEvaluatorImpl;

  public:
    typedef TRing Ring;
    typedef TAlloc Alloc;
    typedef TX X;
    typedef MPolynomial< n, Ring, Alloc > MPolyN;
    typedef MPolynomial< n - 1, X, 
                         typename Alloc::template rebind<X>::other > MPolyNM1;
  private:
    const MPolyN & myPoly; ///< The polynomial in question
    const X & myEvalPoint; ///< the evaluation point
    
    inline 
    MPolynomialEvaluator( const MPolyN & poly, const X & evalpoint)
        : myPoly( poly ), myEvalPoint( evalpoint )
    {}
    
    /**
       Will be called by "child". Evaluates the polynomial into an
       element of XX (which must not necessarily be X, it can also be
       MPolynomial<k, X> for some k < n - 1) using the given functor to
       evaluate the coefficients, which are of type MPolynomial<n-1, Ring>.
    */
    template < typename XX, typename Fun >
    inline 
    void evaluate( XX & res, const Fun & evalfun ) const
    {
      X xx = (X) 1;
      for ( int i = 0; i < (int) myPoly.myValue.size(); ++i )
        {
          res += evalfun( myPoly.myValue[i] ) * xx;
          xx = xx * myEvalPoint;
        }
    }
    
public:
    /**
       Evaluate to polynomial of type MPolynomial< n-1, X>.
    */
    inline 
    operator MPolyNM1() const
    {
      MPolyNM1 res( myPoly.getAllocator() );
      X xx = (X) 1;
      for ( int i = 0; i < (int) myPoly.myValue.size(); ++i )
        {
          res += MPolyNM1( myPoly.myValue[i] ) * xx;
          xx = xx * myEvalPoint;
        }
      return res;
    }
    
    /**
       Continue evaluation to lower level.
    */
    template <typename XX>
    inline 
    MPolynomialEvaluatorImpl
    < n - 1, Ring, MPolynomialEvaluator< n, Ring, Alloc, X >, Alloc, XX > 
    operator() (const XX & x) const
    {
      return MPolynomialEvaluatorImpl
        < n - 1, Ring, MPolynomialEvaluator< n, Ring, Alloc, X >, Alloc, XX > 
        ( *this, x );
    }
  };

  /**
     Description of template class 'MPolynomial' <p> 

     \brief Aim: Specialization of MPolynomial for degree 0.

     Stores a polynomial of degree 0, i.e. a scalar of type T. We
     assume that the type T is not "too" complex, otherwise this class
     will be partially not very effective.

     @tparam TRing the type chosen for the polynomial, defines also
     the type of the coefficents (generally int, float or double).
     
     @tparam TAlloc is an allocator for TRing, for example
     std::allocator<TRing>; this is also the default
     parameter. Usually this parameter does not needs to be changed.

     This class is a backport from <a
     href="http://spielwiese.fontein.de/">Spielwiese</a>.
     @author Felix Fontein (\c felix@fontein.de), University of Zurich,
     Switzerland
  */
  template < typename TRing, typename TAlloc >
  class MPolynomial< 0, TRing, TAlloc >
  {
  public:
    typedef TRing Ring;
    typedef TAlloc Alloc;

  private:
    Alloc myAllocator;
    Ring myValue;

  public:
    /**
       Constructor (default, or from ring value). Creates the constant
       polynomial \a v.
       
       @param v any value in the ring.
       @param allocator an allocator for the polynomial.
    */
    inline 
    MPolynomial( const Ring & v = 0, const Alloc & allocator = Alloc() )
      : myAllocator(allocator), myValue(v)
    {}
    
    /**
       Allocator constructor. Creates the constant polynomial \a 0,
       where 0 is the default value of the ring.
       
       @param allocator an allocator for the polynomial.
    */
    inline 
    MPolynomial( const Alloc & allocator )
      : myAllocator(allocator), myValue( Ring() )
    {}
    
    /**
       @return true if the polynomial is 0.
    */
    inline bool isZero() const
    {
      return myValue == 0;
    }
    
    /**
       Const cast operator to Ring value. Returns the coefficient
       value of this constant polynomial.
    */
    inline operator const Ring & () const
    {
        return myValue;
    }
    
    /**
       Assigment from coefficient in the ring.
       @param v any value in the ring.
       @return itself
    */
    inline MPolynomial & operator = (const Ring & v)
    {
      myValue = v;
      return *this;
    }

    /**
       Evaluation operator for the polynomial.
       @return the value of its coefficient.
    */
    inline Ring operator() () const
    {
      return myValue;
    }
    
    /**
       Multiplication by value \a v.
       @param v any value in the ring.
       @return a constant polynomial of coefficient myValue*v.
    */
    inline MPolynomial operator * (const Ring & v) const
    {
        return MPolynomial(myValue * v);
    }
    
    /**
       Division by value \a v.
       @param v any value in the ring.
       @return a constant polynomial of coefficient myValue/v.
    */
    inline MPolynomial operator / (const Ring & v) const
    {
        return MPolynomial(myValue / v);
    }
    
    /**
       Addition by value \a v.
       @param v any value in the ring.
       @return a constant polynomial of coefficient myValue+v.
    */
    inline MPolynomial operator + (const Ring & v) const
    {
        return MPolynomial(myValue + v);
    }
    
    /**
       Subtraction by value \a v.
       @param v any value in the ring.
       @return a constant polynomial of coefficient myValue-v.
    */
    inline MPolynomial operator - (const Ring & v) const
    {
        return MPolynomial(myValue - v);
    }
    
    /**
       Unary minus operator.
       @return a constant polynomial of coefficient -myValue.
    */
    inline MPolynomial operator - () const
    {
      return MPolynomial(-myValue);
    }
    
    /**
       Self-multiplication by value \a v.
       @param v any value in the ring.
       @return itself
    */
    inline MPolynomial & operator *= (const Ring & v)
    {
      myValue *= v;
      return *this;
    }
    
    /**
       Self-division by value \a v.
       @param v any value in the ring.
       @return itself
    */
    inline MPolynomial & operator /= (const Ring & v)
    {
      myValue /= v;
      return *this;
    }
    
    /**
       Self-addition by value \a v.
       @param v any value in the ring.
       @return itself
    */
    inline MPolynomial & operator += (const Ring & v)
    {
      myValue += v;
      return *this;
    }
    
    /**
       Self-subtraction by value \a v.
       @param v any value in the ring.
       @return itself
    */
    inline MPolynomial & operator -= (const Ring & v)
    {
      myValue -= v;
      return *this;
    }
    
    /**
       Equality operator.
       @param v any value in the ring.
       @return true iff myValue is equal to \a v.
    */
    inline bool operator == (const Ring & v) const
    {
        return myValue == v;
    }
    
    /**
       Difference operator.
       @param v any value in the ring.
       @return true iff myValue is different from \a v.
    */
    inline bool operator != (const Ring & v) const
    {
        return myValue != v;
    }
    
    /**
       Outputs itself in the stream \a s.
       @param s any stream
    */
    void selfDisplay( std::ostream & s, int /*N = 0*/ ) const
    {
      s << myValue;
    }
    
    /**
       Swaps two polynomials.
       @param p any zero-degree polynomial.
    */
    inline void swap( MPolynomial & p )
    {
      std::swap(myValue, p.myValue);
    }
    
    /**
       @return the allocator for this object.
    */
    Alloc getAllocator() const
    {
      return myAllocator;
    }
  };


  /**
     Next, we want to define the storage class IVector<T, Alloc,
     usePointers>. It behaves like a subset of std::vector<T>'s
     capabilities (i.e. access elements, get size, set size, get last
     element, swap with other storage of same type), but uses
     std::vector<T*> in case usePointers is true.
 
     The advantage of this approach is that if T is a more complex
     object, reallocation done with resize() can be very costly.

     This generic version is just using std::vector<T>.
  */
  template < typename T, typename TAlloc = std::allocator<T>, 
             bool usePointers = false>
  class IVector
  {
  public:
    typedef TAlloc Alloc;
    typedef typename std::vector<T, Alloc>::size_type Size;
  private:
    std::vector<T, Alloc> myVec;
    
  public:
    IVector( const Alloc & allocator = Alloc() )
      : myVec(allocator)
    {}
    
    IVector( Size aSize, const Alloc & allocator = Alloc() )
      : myVec( aSize, T(), allocator )
    {}
    
    IVector( Size aSize, const T & entry, const Alloc & allocator = Alloc() )
      : myVec(aSize, entry, allocator)
    {}
    
    Size size() const
    {
      return myVec.size();
    }
    
    void resize( Size aSize, const T & entry = T() )
    {
      myVec.resize(aSize, entry);
    }
    
    const T & operator[] ( Size i ) const
    {
      return myVec[i];
    }
    
    T & operator[] ( Size i )
    {
      return myVec[i];
    }
    
    const T & back() const
    {
      return myVec.back();
    }
    
    T & back()
    {
      return myVec.back();
    }
    
    void swap(IVector & v)
    {
      myVec.swap( v.myVec );
    }
    
    Alloc get_allocator() const
    {
        return myVec.get_allocator();
    }
    
    Alloc getAllocator() const
    {
        return myVec.get_allocator();
    }
  };

  /**
     Specialization that is using std::vector<T*>, but behaving like
     std::vector<T>.
  */
  template < typename T, typename TAlloc>
  class IVector< T, TAlloc, true >
  {
  public:
    typedef TAlloc Alloc;
    typedef typename std::vector<typename Alloc::pointer, typename Alloc::template rebind<typename Alloc::pointer>::other>::size_type Size;
   
  private:
    Alloc myAllocator;
    std::vector<typename Alloc::pointer, typename Alloc::template rebind<typename Alloc::pointer>::other> myVec;
    
    void create( Size begin, Size end, typename Alloc::const_reference entry)
    {
      for (Size i = begin; i < end; ++i)
        {
          myVec[i] = myAllocator.allocate(sizeof(T));
          myAllocator.construct(myVec[i], entry);
        }
    }
    
    void free(Size begin, Size end)
    {
      for (Size i = begin; i < end; ++i)
        {
          myAllocator.destroy(myVec[i]);
          myAllocator.deallocate(myVec[i], sizeof(T));
        }
    }
    
    template<class A>
    void copy_from(const std::vector<typename Alloc::pointer, A> & source)
    {
      for (Size i = 0; i < myVec.size(); ++i)
        {
          myVec[i] = myAllocator.allocate(sizeof(T));
          myAllocator.construct(myVec[i], *source[i]);
        }
    }
    
  public:
    IVector(const Alloc & allocator = Alloc())
      : myAllocator(allocator), myVec(allocator)
    {}
    
    IVector(Size aSize, const Alloc & allocator = Alloc())
      : myAllocator(allocator), myVec(aSize, 0, allocator)
    {
      create(0, aSize, T());
    }
    
    IVector(Size aSize, const T & entry, const Alloc & allocator = Alloc())
      : myAllocator(allocator), myVec(aSize, 0, allocator)
    {
      create(0, aSize, entry);
    }
    
    IVector(const IVector & v)
      : myVec(v.size())
    {
      copy_from(v.myVec);
    }
    
    ~IVector()
    {
      free(0, (Size)myVec.size());
    }
    
    IVector & operator = (const IVector & v)
    {
      if (&v != this)
        {
          free(0, (Size)myVec.size());
          myVec.resize(v.size());
          copy_from(v.myVec);
        }
      return *this;
    }
    
    Size size() const
    {
      return (Size)myVec.size();
    }
    
    void resize(Size aSize, const T & entry = T())
    {
      Size oldsize = (Size)myVec.size();
      if (oldsize > aSize)
        free(aSize, oldsize);
      myVec.resize(aSize);
      if (oldsize < aSize)
        create(oldsize, aSize, entry);
    }
    
    const T & operator[] (Size i) const
    {
      return *myVec[i];
    }
    
    T & operator[] (Size i)
    {
      return *myVec[i];
    }
    
    const T & back() const
    {
      return *myVec.back();
    }
    
    T & back()
    {
      return *myVec.back();
    }
    
    void swap(IVector & v)
    {
      myVec.swap(v.myVec);
    }
    
    Alloc get_allocator() const
    {
      return myVec.get_allocator();
    }

    Alloc getAllocator() const
    {
      return myVec.get_allocator();
    }
  };
  

  /////////////////////////////////////////////////////////////////////////////
  // template class MPolynomial
  /**
     Description of template class 'MPolynomial' <p> 

     \brief Aim: Represents a multivariate polynomial, i.e. an element
     of \f$ K[X_0, ..., X_{n-1}] \f$, where \e K is some ring or field.

     Monomials are products of power of variables, like
     xy^2z^3. Polynomials in \e n variables are constructed
     recursively with polynomials in \e n - 1 variables.

     There is a specialization for polynomials with no indeterminates,
     i.e. constants.

     @see dgtal_multivariate_polynomial

     @tparam n the number of variables or indeterminates.

     @tparam TRing the type chosen for the polynomial, defines also
     the type of the coefficents (generally int, float or double).
     
     @tparam TAlloc is an allocator for TRing, for example
     std::allocator<TRing>; this is also the default
     parameter. Usually this parameter does not needs to be changed.

     This class is a backport from <a
     href="http://spielwiese.fontein.de/">Spielwiese</a>.
     @author Felix Fontein (\c felix@fontein.de), University of Zurich,
     Switzerland
  */
  template < int n, typename TRing, class TAlloc >
  class MPolynomial
  {
    // ----------------------- friends ---------------------------------------
    
    template<int NN, int nn, typename TT, typename AA>
    friend class MPolynomialDerivativeComputer;
    
    friend void euclidDiv<TRing, TAlloc>
    ( const MPolynomial<1, TRing, TAlloc> &, 
      const MPolynomial<1, TRing, TAlloc> &, 
      MPolynomial<1, TRing, TAlloc> &, 
      MPolynomial<1, TRing, TAlloc> & );
    
    template<int nn, typename TT, typename AA, typename SS>
    friend class MPolynomialEvaluator;
    
    template<int nn, typename TT, typename HLHL, typename AA, typename SS>
    friend class MPolynomialEvaluatorImpl;

  public:
    typedef TRing Ring;
    typedef TAlloc Alloc;
    typedef MPolynomial< n - 1, Ring, Alloc > MPolyNM1; 
    /**
       The type for the vector storing polynomials coefficients. For 0
       or 1 variables, uses a standard vector, for more variables,
       uses a specific vector of pointers to polynomials, with
       adequate allocators. This is for efficiency purposes.
    */
    typedef IVector< MPolyNM1, 
                     typename Alloc::template rebind<MPolyNM1 >::other, (n>1) >
    Storage;
    typedef typename Storage::Size Size;

    // ----------------------- Datas  ----------------------------
private:
    /// The zero polynomial of n-1 variables for a n-multivariate polynomial.
    static MPolyNM1 myZeroPolynomial;
    /**
       The vector storing polynomials coefficients. For 0 or 1
       variables, uses a standard vector, for more variables, uses a
       specific vector of pointers to polynomials, with adequate
       allocators. This is for efficiency purposes.
    */
    Storage myValue;

    /**
       Private constructor for initializing an array of size \a s.
    */
    inline 
      MPolynomial( bool, Size s, const Alloc & /*allocator*/)
      : myValue(s) 
    {}
    
public:
    /**
       Adjusts the size of myValue that the leading term and degree
       can be computed trivially. This must be called only after calls
       to the non-const operator[], in which the degree of the
       polynomial has potentially been changed.
    */
    inline void normalize()
    {
      Size dp1 = myValue.size();
      while ( dp1 )
        {
          if (myValue[dp1 - 1].isZero())
            --dp1;
          else
            break;
        }
      if (dp1 < myValue.size())
        myValue.resize(dp1);
    }

    // ----------------------- Standard services ----------------------------
  public:
      
    /**
       Constructs a zero polynomial
    */
    inline MPolynomial( const Alloc & allocator = Alloc() )
      : myValue( allocator )
    {}
    
    /**
       Constructs a constant polynomial with constant term v.
    */
    inline MPolynomial( const Ring & v, const Alloc & allocator = Alloc() )
      : myValue( 1, MPolyNM1( v ), allocator )
    {}
    
    /**
       Constructs a polynomial of type MPolynomial<n, Ring> which is
       initialized with a polynomial of type MPolynomial<n-1, Ring>.
    */
    inline MPolynomial( const MPolyNM1 & pdm1, 
                        const Alloc & /*allocator = Alloc()*/ )
      : myValue( 1, pdm1 )
    {}

    /**
       Casts a polynomial of type MPolynomial<n, Ring2, Alloc2> to a
       polynomial of type MPolynomial<n, Ring, Alloc>.
    */
    template < typename Ring2, typename Alloc2 >
    inline MPolynomial( const MPolynomial<n, Ring2, Alloc2> & p, 
                        const Alloc & allocator = Alloc() )
      : myValue( p.degree() + 1, MPolyNM1(), allocator )
    {
      for ( Size i = 0; i < myValue.size(); ++i )
        myValue[i] = p[i];
      normalize();
    }
    
    /**
       Copies a polynomial of type MPolynomial<n, Ring2, Alloc2> to
       this polynomial (of type MPolynomial<n, Ring, Alloc>).
    */
    template < typename Ring2, typename Alloc2 >
    inline 
    MPolynomial & operator= 
    (const MPolynomial< n, Ring2, Alloc2> & p )
    {
      myValue.resize(p.degree() + 1);
      for ( Size i = 0; i < myValue.size(); ++i )
        myValue[i] = p[i];
      normalize();
      return *this;
    }

    /**
       Swaps two polynomials.
       @param p the polynomial to exchange with.
    */
    inline void swap( MPolynomial & p )
    {
        myValue.swap(p.myValue);
    }
    
    /**
       @return the allocator for this object.
    */
    Alloc getAllocator() const
    {
        return myValue.getAllocator();
    }

    // ----------------------- MPolynomial services ----------------------------
  public:

    /**
       @return the degree of this polynomial. If this is the zero
       polynomial, the degree is -1.
    */
    inline int degree() const
    {
      return (int)(myValue.size() - 1);
    }
    
    /**
       @return the leading term (of type MPolynomial<n-1, Ring>) of the first
       indeterminate. Returns 0 (of type MPolynomial<n-1, Ring>) in case of the
       zero polynomial.
    */
    inline const MPolyNM1 & leading() const
    {
      return myValue.size() ? myValue.back() : myZeroPolynomial;
    }
    
    /**
       Tests whether this polynomial is the zero polynomial.
    */
    inline bool isZero() const
    {
      return myValue.size() == 0;
    }
    
    /**
       @return a reference to the i-th coefficient. If i > degree(),
       the array myValue is enlarged. Afterwards, one should better
       call normalize() to make sure future operations are correct.
    */
    inline MPolyNM1 & operator[] ( Size i )
    {
      if (i >= myValue.size())
        myValue.resize(i + 1);
      return myValue[i];
    }
    
    /**
       @return a reference to the i-th coefficient, or zero if i > degree().
    */
    inline const MPolyNM1 & operator[] (Size i) const
    {
      return i < myValue.size() ? myValue[i] : myZeroPolynomial;
    }

    /**
       Evaluation in \a x.

       @param x a value in the ring.
       @return a functor for performing this evaluation
    */
    inline 
    MPolynomialEvaluator<n, Ring, Alloc, Ring> operator() (const Ring & x) const
    {
      return MPolynomialEvaluator<n, Ring, Alloc, Ring>( *this, x );
    }

    /**
       Evaluation in \a x of type Ring2.

       @tparam Ring2 another ring (like a polynomial with less variables).
       @param x a value in this ring.
       @return a functor for performing this evaluation
    */
    template <typename Ring2>
    inline 
    MPolynomialEvaluator<n, Ring, Alloc, Ring2> operator() (const Ring2 & x) const
    {
      return MPolynomialEvaluator<n, Ring, Alloc, Ring2>( *this, x );
    }
    
    // ----------------------- Operators --------------------------------------
  public:

    /**
       Multiply by constant.
       @param v any value in the ring.
       @return the corresponding polynomial.
    */
    inline MPolynomial operator * (const Ring & v) const
    {
      MPolynomial r(*this);
      for ( Size i = 0; i < myValue.size(); ++i )
        r[i] *= v;
      return r;
    }
    
    /**
       Divide by constant.
       @param v any value in the ring.
       @return the corresponding polynomial.
    */
    inline MPolynomial operator / (const Ring & v) const
    {
      MPolynomial r(*this);
      for ( Size i = 0; i < myValue.size(); ++i )
        r[i] /= v;
      return r;
    }

    /**
       Self-multiplication by other polynomial.
       @param p any polynomial of the same type.
       @return a reference to this.
    */
    inline MPolynomial & operator *= (const MPolynomial & p)
    {
      return *this = *this * p;
    }
    
    /**
       Self-multiplication by a constant.
       @param v any value in the ring.
       @return a reference to this.
    */
    inline MPolynomial & operator *= (const Ring & v)
    {
      MPolynomial r( *this );
      for ( Size i = 0; i < myValue.size(); ++i )
        myValue[i] *= v;
      return *this;
    }
    
    /**
       Self-division by a constant.
       @param v any value in the ring.
       @return a reference to this.
    */
    inline MPolynomial & operator /= (const Ring & v)
    {
      for ( Size i = 0; i < myValue.size(); ++i )
        myValue[i] /= v;
      return *this;
    }
    
    /**
       Multiplication by a constant from the left.
       @param v any value in the ring.
       @param p any polynomial of this type.
       @return the corresponding polynomial.
    */
    friend 
    inline MPolynomial operator * (const Ring & v, const MPolynomial & p)
    {
      MPolynomial r(p);
      for ( Size i = 0; i < p.myValue.size(); ++i )
        r[i] *= v;
      return r;
    }
    
    /**
      @return the additive inverse of the polynomial.
    */
    inline MPolynomial operator - () const
    {
      MPolynomial r( true, myValue.size(), getAllocator() );
      for ( Size i = 0; i < myValue.size(); ++i )
        r[i] = -myValue[i];
      return r;
    }
    
    /**
       Computes the sum of two polynomials.
       @param q any polynomial of this type.
       @return the corresponding polynomial.
    */
    inline MPolynomial operator + (const MPolynomial & q) const
    {
      MPolynomial r(*this);
      if (r.myValue.size() < q.myValue.size())
        r.myValue.resize(q.myValue.size());
      for ( Size i = 0; i < q.myValue.size(); ++i )
        r[i] += q[i];
      r.normalize();
      return r;
    }
    
    /**
       Computes the difference of two polynomials.
       @param q any polynomial of this type.
       @return the corresponding polynomial.
    */
    inline MPolynomial operator - (const MPolynomial & q) const
    {
      MPolynomial r(*this);
      if (r.myValue.size() < q.myValue.size())
        r.myValue.resize(q.myValue.size());
      for ( Size i = 0; i < q.myValue.size(); ++i )
        r[i] -= q[i];
      r.normalize();
      return r;
    }
    
    /**
       Adds \a q to this polynomial.
       @param q any polynomial of this type.
       @return a reference to this.
    */
    inline MPolynomial & operator += (const MPolynomial & q)
    {
      if (myValue.size() < q.myValue.size())
        myValue.resize(q.myValue.size());
      for ( Size i = 0; i < q.myValue.size(); ++i )
        myValue[i] += q[i];
      normalize();
      return *this;
    }
    
    /**
       Subtracts \a q from this polynomial.
       @param q any polynomial of this type.
       @return a reference to this.
    */
    inline MPolynomial & operator -= (const MPolynomial & q)
    {
      if (myValue.size() < q.myValue.size())
        myValue.resize(q.myValue.size());
      for ( Size i = 0; i < q.myValue.size(); ++i )
        myValue[i] -= q[i];
      normalize();
      return *this;
    }
    
    /**
       Computes the sum of this polynomial with a polynomial with
       one less variable.
       @param q any polynomial with n-1 indeterminates in the same ring.
       @return the corresponding polynomial.
    */
    inline MPolynomial operator + (const MPolyNM1 & q) const
    {
      MPolynomial r(*this);
      if (r.myValue.size() < 1)
        r.myValue.resize(1);
      r[0] += q;
      r.normalize();
      return r;
    }
    
    /**
       Computes the difference of this polynomial with a polynomial with
       one less variable.
       @param q any polynomial with n-1 indeterminates in the same ring.
       @return the corresponding polynomial.
    */
    inline MPolynomial operator - (const MPolyNM1 & q) const
    {
      MPolynomial r(*this);
      if (r.myValue.size() < 1)
        r.myValue.resize(1);
      r[0] -= q;
      r.normalize();
      return r;
    }
    
    /**
       Addition with a constant.
       @param v any value in the ring.
       @return the corresponding polynomial.
    */
    inline MPolynomial operator + (const Ring & v) const
    {
      MPolynomial r(*this);
      if (r.myValue.size() < 1)
        r.myValue.resize(1);
      r[0] += v;
      r.normalize();
      return r;
    }

    /**
       Difference to a constant.
       @param v any value in the ring.
       @return the corresponding polynomial.
    */
    inline MPolynomial operator - (const Ring & v) const
    {
      MPolynomial r(*this);
      if (r.myValue.size() < 1)
        r.myValue.resize(1);
      r[0] -= v;
      r.normalize();
      return r;
    }

    /**
       Self-addition of this polynomial with a polynomial with
       one less variable.
       @param q any polynomial with n-1 indeterminates in the same ring.
       @return a reference to this.
    */
    inline MPolynomial & operator += (const MPolyNM1 & q)
    {
      if (myValue.size() < 1)
        myValue.resize(1);
      myValue[0] += q;
      normalize();
      return *this;
    }
    
    /**
       Self-subtraction of this polynomial with a polynomial with
       one less variable.
       @param q any polynomial with n-1 indeterminates in the same ring.
       @return a reference to this.
    */
    inline MPolynomial & operator -= (const MPolyNM1 & q)
    {
      if (myValue.size() < 1)
        myValue.resize(1);
      myValue[0] -= q;
      normalize();
      return *this;
    }
    
    /**
       Self-addition of a constant.
       @param v any value in the ring.
       @return a reference to this.
    */
    inline MPolynomial & operator += (const Ring & v)
    {
      if (myValue.size() < 1)
        myValue.resize(1);
      myValue[0] += v;
      normalize();
      return *this;
    }
    
    /**
       Self-subtraction of a constant.
       @param v any value in the ring.
       @return a reference to this.
    */
    inline MPolynomial & operator -= (const Ring & v)
    {
      if (myValue.size() < 1)
        myValue.resize(1);
      myValue[0] -= v;
      normalize();
      return *this;
    }

    /**
       Multiplies the polynomial with another polynomial.
       @param p any polynomial of the same type.
       @return the corresponding polynomial.

       @todo Multiplication could be optimized for monovariate polynomials.
    */
    inline MPolynomial operator * (const MPolynomial & p) const
    {
      int d = p.degree() + degree();
      if (d < -1)
        d = -1;
      MPolynomial r( true, d + 1, getAllocator() );
      if (!isZero() && !p.isZero())
        for ( Size i = 0; i < r.myValue.size(); ++i )
          for ( Size j = 0; j < myValue.size(); ++j )
            if (i < j + p.myValue.size())
              r[i] += myValue[j] * p[i - j];
      r.normalize();
      return r;
    }

    // ----------------------- Comparison operators ---------------------------
  public:

    /**
       Equality operator.
       @param q any polynomial of the same type as this.
       @return 'true' iff this polynomial is equal to \a q.
    */
    inline bool operator == (const MPolynomial & q) const
    {
      if (myValue.size() != q.myValue.size())
        return false;
      for (Size i = 0; i < myValue.size(); ++i)
        if (myValue[i] != q[i])
          return false;
      return true;
    }
    
    /**
       Inequality operator.
       @param q any polynomial of the same type as this.
       @return 'true' iff this polynomial is different from \a q.
    */
    inline bool operator != (const MPolynomial & q) const
    {
      return !(*this == q);
    }
    
    /**
       Equality operator with a constant.
       @param v any value in the ring.
       @return 'true' iff this polynomial is equal to \a v.
    */
    inline bool operator == (const Ring & v) const
    {
      if ((v == 0) && (myValue.size() == 0))
        return true;
      if (myValue.size() != 1)
        return false;
      return myValue[0] == v;
    }

    /**
       Inequality operator with a constant.
       @param v any value in the ring.
       @return 'true' iff this polynomial is different from \a v.
    */
    inline bool operator != (const Ring & v) const
    {
      return !(*this == v);
    }
    

      
    // ----------------------- Interface --------------------------------------
  public:

    /**
       Prints this polynomial to the stream s. N gives the number of
       variables; this is needed for recursive printing.

       @param s the output stream where the object is written.
       @param N the number of variables.
    */
    void selfDisplay ( std::ostream & s, int N = n ) const
    {
      if (isZero())
        s << (Ring) 0;
      else
        {
          Size nonzero = 0;
          for (Size i = 0; i < myValue.size(); ++i)
            if (!myValue[i].isZero())
              ++nonzero;
          if (nonzero > 1) s << "(";
          bool first = true;
          for (Size i = 0; i < myValue.size(); ++i)
            if (!myValue[i].isZero())
              {
                if (first) first = false;
                else       s << " + ";
                myValue[i].selfDisplay(s, N);
                if (i > 0)
                  {
                    s << " ";
                    s << "X_" << N - n;
                    if (i > 1) s << "^" << i;
                  }
              }
          if (nonzero > 1)
            s << ")";
        }
    }
    
    /**
       Checks the validity/consistency of the object.
       @return 'true' if the object is valid, 'false' otherwise.
    */
    bool isValid() const;

     
    // ------------------------- Datas --------------------------------------
  private:
    // ------------------------- Hidden services ----------------------------
  protected:
    

  }; // end of class MPolynomial


  /**
   * Overloads 'operator<<' for displaying objects of class 'MPolynomial'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'MPolynomial' to write.
   * @return the output stream after the writing.
   */
  template <int N, typename TRing, class TAlloc>
  std::ostream&
  operator<< ( std::ostream & out, 
               const MPolynomial<N, TRing, TAlloc> & object );


  // ------------------------- monomial services ----------------------------

  /**
     Creates a monomial X_k^e
     @tparam n the number of indetermionates.
     @tparam Ring the type for the coefficent ring of the polynomial.
     @tparam Alloc the type of allocator.
  */
  template <int n, typename Ring, typename Alloc>
  class Xe_kComputer
  {
  public:
    Xe_kComputer() {}

   /** 
   *  @param k the index of the variable (X_k)
    * @param e the exponent for X_k
    *  @return the 1-variable polynomial X_0^e
        */
    MPolynomial<n, Ring, Alloc> 
    get( unsigned int k, unsigned int e )
    {
      MPolynomial<n, Ring, Alloc> p;
      if ( k == 0 )
        p[e] = Xe_kComputer<n-1,Ring,Alloc>().get( k-1, e ); 
      else
        p[0] = Xe_kComputer<n-1,Ring,Alloc>().get( k-1, e );
      p.normalize();
      //std::cerr << "Xe_k(" << k << "," << e << ")=" << p << std::endl;
      return p;
    }

  };

  template <typename Ring, typename Alloc>
  class Xe_kComputer<0,Ring,Alloc>
  {
  public:
    Xe_kComputer() {}

    MPolynomial<0, Ring, Alloc> 
      get( unsigned int /*k*/, unsigned int /*e*/ )
    {
      MPolynomial<0, Ring, Alloc> p = 1;
      return p;
    }
  };

  /**
     Creates a monomial X_k^e 
     @param k the index of the variable (X_k)
     @param e the exponent for X_k
     @return the 1-variable polynomial X_0^e
     @tparam n the number of indetermionates.
     @tparam Ring the type for the coefficent ring of the polynomial.
     @tparam Alloc the type of allocator.
  */
  template <int n, typename Ring, typename Alloc>
  inline 
  MPolynomial<n, Ring, Alloc> 
  Xe_k( unsigned int k, unsigned int e )
  {
    return Xe_kComputer<n, Ring, Alloc>().get( k, e );
  }

  /**
     Creates a monomial X_k^e 
     @param k the index of the variable (X_k)
     @param e the exponent for X_k
     @return the 1-variable polynomial X_0^e
     @tparam n the number of indetermionates.
     @tparam Ring the type for the coefficent ring of the polynomial.
  */
  template <int n, typename Ring>
  inline 
  MPolynomial<n, Ring, std::allocator<Ring> >
  Xe_k( unsigned int k, unsigned int e )
  {
    return Xe_kComputer<n, Ring, std::allocator<Ring> >().get( k, e );
  }


  /**
     Creates a monomial in one indeterminate.
     @param e the exponent for X_0
     @return the 1-variable polynomial X_0^e
     @tparam Ring the type for the coefficent ring of the polynomial.
     @tparam Alloc the type of allocator.
  */
  template <typename Ring, typename Alloc>
  inline 
  MPolynomial<1, Ring, Alloc> 
  mmonomial(unsigned int e)
  {
    MPolynomial<1, Ring, Alloc> p;
    p[e] = 1;
    return p;
  }

  /**
     Creates a monomial in two indeterminates.
     @param e the exponent for X_0
     @param f the exponent for X_1
     @return the 2-variables polynomial X_0^e X_1^f
     @tparam Ring the type for the coefficent ring of the polynomial.
     @tparam Alloc the type of allocator.
  */
  template <typename Ring, typename Alloc>
  inline 
  MPolynomial<2, Ring, Alloc> 
  mmonomial(unsigned int e, unsigned int f)
  {
    MPolynomial<2, Ring, Alloc> p;
    p[e][f] = 1;
    return p;
  }

  /**
     Creates a monomial in three indeterminates.
     @param e the exponent for X_0
     @param f the exponent for X_1
     @param g the exponent for X_2
     @return the 3-variables polynomial X_0^e X_1^f X_2^g
     @tparam Ring the type for the coefficent ring of the polynomial.
     @tparam Alloc the type of allocator.
  */
  template <typename Ring, typename Alloc>
  inline MPolynomial<3, Ring, Alloc> 
  mmonomial(unsigned int e, unsigned int f, unsigned int g)
  {
    MPolynomial<3, Ring, Alloc> p;
    p[e][f][g] = 1;
    return p;
  }

  /**
     Creates a monomial in four indeterminates.
     @param e the exponent for X_0
     @param f the exponent for X_1
     @param g the exponent for X_2
     @param h the exponent for X_3
     @return the 3-variables polynomial X_0^e X_1^f X_2^g X_3^h
     @tparam Ring the type for the coefficent ring of the polynomial.
     @tparam Alloc the type of allocator.
  */
  template <typename Ring, typename Alloc>
  inline 
  MPolynomial<4, Ring, Alloc> 
  mmonomial(unsigned int e, unsigned int f, unsigned int g, unsigned int h)
  {
    MPolynomial<4, Ring, Alloc> p;
    p[e][f][g][h] = 1;
    return p;
  }

  /**
     Creates a monomial in one indeterminate.
     @param e the exponent for X_0
     @return the 1-variable polynomial X_0^e
     @tparam Ring the type for the coefficent ring of the polynomial.
  */
  template <typename Ring>
  inline 
  MPolynomial<1, Ring, std::allocator<Ring> > 
  mmonomial(unsigned int e)
  {
    MPolynomial<1, Ring, std::allocator<Ring> > p;
    p[e] = 1;
    return p;
  }

  /**
     Creates a monomial in two indeterminates.
     @param e the exponent for X_0
     @param f the exponent for X_1
     @return the 2-variables polynomial X_0^e X_1^f
     @tparam Ring the type for the coefficent ring of the polynomial.
  */
  template <typename Ring>
  inline
  MPolynomial<2, Ring, std::allocator<Ring> > 
  mmonomial(unsigned int e, unsigned int f)
  {
    MPolynomial<2, Ring, std::allocator<Ring> > p;
    p[e][f] = 1;
    return p;
  }

    /**
     Creates a monomial in three indeterminates.
     @param e the exponent for X_0
     @param f the exponent for X_1
     @param g the exponent for X_2
     @return the 3-variables polynomial X_0^e X_1^f X_2^g
     @tparam Ring the type for the coefficent ring of the polynomial.
  */
  template <typename Ring>
  inline
  MPolynomial<3, Ring, std::allocator<Ring> > 
  mmonomial(unsigned int e, unsigned int f, unsigned int g)
  {
    MPolynomial<3, Ring, std::allocator<Ring> > p;
    p[e][f][g] = 1;
    return p;
  }

  /**
     Creates a monomial in four indeterminates.
     @param e the exponent for X_0
     @param f the exponent for X_1
     @param g the exponent for X_2
     @param h the exponent for X_3
     @return the 3-variables polynomial X_0^e X_1^f X_2^g X_3^h
     @tparam Ring the type for the coefficent ring of the polynomial.
  */
  template <typename Ring>
  inline
  MPolynomial<4, Ring, std::allocator<Ring> >
  mmonomial
  (unsigned int e, unsigned int f, unsigned int g, unsigned int h)
  {
    MPolynomial<4, Ring, std::allocator<Ring> > p;
    p[e][f][g][h] = 1;
    return p;
  }
  

  /**
     Utility class for computing the derivative of a given polynomial
     with respect to the first indeterminate. The coefficients of the
     first indeterminate are left untouched.

     Specialization of MPolynomialDerivativeComputer to the first
     indeterminate.

     @tparam n the number of variables or indeterminates.
     
     @tparam Ring the type chosen for the polynomial, defines also
     the type of the coefficents (generally int, float or double).
     
     @tparam Alloc is an allocator for TRing, for example
     std::allocator<TRing>; this is also the default
     parameter. Usually this parameter does not needs to be changed.

     This class is a backport from <a
     href="http://spielwiese.fontein.de/">Spielwiese</a>.
  */
  template <int n, typename Ring, class Alloc>
  class MPolynomialDerivativeComputer<0, n, Ring, Alloc>
  {
  public:
    /// Type for polynomial with \a n variable in the ring \a Ring.
    typedef MPolynomial<n, Ring, Alloc> MPolyN;

    /**
       Computes the derivative of \a src with respect to X_0 and puts
       it in \a dest.

       @param src any polynomial
       @param dest (returns) the polynomial d/dX_0(src).
    */
    static inline 
    void computeDerivative( const MPolyN & src, MPolyN & dest)
    {
      dest.myValue.resize(src.degree() >= 0 ? src.degree() : 0);
      for ( int i = 1; i <= src.degree(); ++i )
        dest[i - 1] = src[i] * (Ring)i;
      dest.normalize();
    }
  };

  /**
     Utility class for computing the derivative of a given polynomial
     with respect to the N-th indeterminate, N > 0. Uses
     MPolynomialDerivativeComputer<N-1, n-1, T, Alloc> to partially
     derive the coefficients of the first indeterminate.

     @tparam N the variable used for derivation.

     @tparam n the number of variables or indeterminates.
     
     @tparam Ring the type chosen for the polynomial, defines also
     the type of the coefficents (generally int, float or double).
     
     @tparam Alloc is an allocator for Ring, for example
     std::allocator<Ring>; this is also the default
     parameter. Usually this parameter does not needs to be changed.

     This class is a backport from <a
     href="http://spielwiese.fontein.de/">Spielwiese</a>.

  */
  template <int N, int n, typename Ring, typename Alloc>
  class MPolynomialDerivativeComputer
  {
  public:
    /// Type for polynomial with \a n variable in the ring \a Ring.
    typedef MPolynomial<n, Ring, Alloc> MPolyN;

    /**
       Computes the derivative of \a src with respect to X_N and puts
       it in \a dest.

       @param src any polynomial
       @param dest (returns) the polynomial d/dX_N(src).
    */
    static inline
    void computeDerivative(const MPolyN & src, MPolyN & dest)
    {
      dest.myValue.resize(src.degree() + 1);
      for ( int i = 0; i <= src.degree(); ++i )
        MPolynomialDerivativeComputer<N - 1, n - 1, Ring, Alloc>
          ::computeDerivative( src[i], dest[i] );
      dest.normalize();
    }
  };

  /**
     Provides an error message in case N = n.
  */
  template<typename Ring, class Alloc>
  class MPolynomialDerivativeComputer<0, 0, Ring, Alloc>
  {
  public:
    class ERROR_N_must_be_strictly_less_than_n_in_derivative_template;
    typedef MPolynomial<0, Ring, Alloc> MPoly0;

    static inline 
    void computeDerivative(const MPoly0 &, MPoly0 &)
    {
      ERROR_N_must_be_strictly_less_than_n_in_derivative_template();
    }
  };
  
  /**
     Provides an error message in case N > n.
  */
  template<int N, typename Ring, class Alloc>
  class MPolynomialDerivativeComputer<N, 0, Ring, Alloc>
  {
  public:
    class ERROR_N_must_be_strictly_less_than_n_in_derivative_template;
    typedef MPolynomial<0, Ring, Alloc> MPoly0;

    static inline
    void computeDerivative(const MPoly0 &, MPoly0 &)
    {
      ERROR_N_must_be_strictly_less_than_n_in_derivative_template();
    }
  };

  /**
     Computes the partial derivative of \a p with respect to the N-th
     indeterminate. We assume that 0 <= N < n.

     @param p an arbitrary polynomial.

     @tparam N the variable used for derivation.

     @tparam n the number of variables or indeterminates.
     
     @tparam Ring the type chosen for the polynomial, defines also
     the type of the coefficents (generally int, float or double).
     
     @tparam Alloc is an allocator for Ring, for example
     std::allocator<Ring>; this is also the default
     parameter. Usually this parameter does not needs to be changed.

  */
  template <int N, int n, typename Ring, typename Alloc>
  inline 
  MPolynomial<n, Ring, Alloc> 
  derivative( const MPolynomial<n, Ring, Alloc> & p )
  {
    MPolynomial<n, Ring, Alloc> res( p.getAllocator() );
    MPolynomialDerivativeComputer<N, n, Ring, Alloc>::computeDerivative(p, res);
    return res;
  }

  /**
     Computes the partial derivative of \a p with respect to the N-th
     indeterminate. We assume that 0 <= N < n.
     
     @param p an arbitrary polynomial.
     
     @tparam N the variable used for derivation.
     
     @tparam n the number of variables or indeterminates.
     
     @tparam Ring the type chosen for the polynomial, defines also
     the type of the coefficents (generally int, float or double).
  */
  template<int N, int n, typename Ring>
  inline
  MPolynomial<n, Ring, std::allocator<Ring> > 
  derivative
  (const MPolynomial<n,Ring,std::allocator<Ring> > & p)
   {
     MPolynomial<n, Ring, std::allocator<Ring> > res( p.getAllocator() );
     MPolynomialDerivativeComputer<N, n, Ring, std::allocator<Ring> >
       ::computeDerivative( p, res );
     return res;
   }
   
   /**
      Computes q and r such that f = q g + r and degree(r) < degree(g).
   */
   template<typename Ring, typename Alloc>
   void 
   euclidDiv( const MPolynomial<1, Ring, Alloc> & f, 
              const MPolynomial<1, Ring, Alloc> & g,
              MPolynomial<1, Ring, Alloc> & q, 
              MPolynomial<1, Ring, Alloc> & r )
   {
     if (f.degree() < g.degree())
       {
         // Ignore the trivial case
         q = MPolynomial<1, Ring, Alloc>(f.getAllocator());
         r = f;
         return;
       }
    q = MPolynomial<1, Ring, Alloc>( true, f.degree() - g.degree() + 1, 
                                     f.getAllocator() );
    r = f;
    for (int i = q.degree(); i >= 0; --i)
      {
        q[i] = r[i + g.degree()] / g.leading();
        for (int j = g.degree(); j >= 0; --j)
          r[i + j] -= q[i] * g[j];
      }
    r.normalize();
    // Note that the degree of q is already correct.
   }

   /**
      Computes q and r such that f = q g + r and degree(r) < degree(g).
   */
   template <typename Ring>
   void 
   euclidDiv( const MPolynomial<1, Ring, std::allocator<Ring> > & f,
              const MPolynomial<1, Ring, std::allocator<Ring> > & g, 
              MPolynomial<1, Ring, std::allocator<Ring> > & q, 
              MPolynomial<1, Ring, std::allocator<Ring> > & r )
   {
     euclidDiv<Ring, std::allocator<Ring> >(f, g, q, r);
   }

   /**
      Compute the monic greatest common divisor of f and g using the
      Euclidean Algorithm.
   */
   template<typename Ring, typename Alloc>
   MPolynomial<1, Ring, Alloc> 
   gcd( const MPolynomial<1, Ring, Alloc> & f, 
        const MPolynomial<1, Ring, Alloc> & g )
   {
     if (f.isZero())
       {
         if (g.isZero()) return f; // both are zero
         else            return g / g.leading(); // make g monic
       }
     MPolynomial<1, Ring, Alloc> 
       d1(f / f.leading()), 
       d2(g / g.leading()), 
       q(f.getAllocator()), 
       r(f.getAllocator());
     while (!d2.isZero())
       {
         euclidDiv(d1, d2, q, r);
         d1.swap(d2);
         d2 = r;
         d2 /= r.leading(); // make r monic
       }
     return d1;
   }
  
  /**
     Compute the monic greatest common divisor of f and g using the
     Euclidean Algorithm.
  */
  template<typename Ring>
  MPolynomial<1, Ring, std::allocator<Ring> > 
  gcd( const MPolynomial<1, Ring, std::allocator<Ring> > & f, 
       const MPolynomial<1, Ring, std::allocator<Ring> > & g )
  {
    return gcd<Ring, std::allocator<Ring> >(f, g);
  }

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/math/MPolynomial.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined MPolynomial_h

#undef MPolynomial_RECURSES
#endif // else defined(MPolynomial_RECURSES)
