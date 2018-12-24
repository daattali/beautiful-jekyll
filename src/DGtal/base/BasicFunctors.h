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
 * @file BasicFunctors.h
 * @author Guillaume Damiand (\c guillaume.damiand@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2010/07/02
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/01/27
 *
 *
 * Header file for module BasicFunctors.h
 *
 * This file contains the definition of basic functors.
 *
 * This file is part of the DGtal library.
 */

#if defined(BasicFunctors_RECURSES)
#error Recursive header files inclusion detected in BasicFunctors.h
#else // defined(BasicFunctors_RECURSES)
/** Prevents recursive inclusion of headers. */
#define BasicFunctors_RECURSES

#if !defined BasicFunctors_h
/** Prevents repeated inclusion of headers. */
#define BasicFunctors_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <algorithm>
#include <functional>
#include <cmath>
#include "DGtal/io/Color.h"
#include "DGtal/base/Common.h"
#include "DGtal/base/BasicBoolFunctors.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace functors
{
/////////////////////////////////////////////////////////////////////////////
/// Duplicated STL functors
/////////////////////////////////////////////////////////////////////////////
  template<typename T>
  struct Min
  {
    inline
    T operator() (const T&a, const T&b) const
    { return std::min(a,b); }
  };

  template<typename T>
  struct Max
  {
    inline
    T operator() (const T&a, const T&b) const
    { return std::max(a,b); }
  };

 /**
   * Copy of the std::minus binary operator (not implemented on MS-VS)
   */
  template <class T>
  struct Minus
  {
    T operator() (const T& x, const T& y) const
    {return x-y;}
  };

  /**
   * Abs functor.
   */
  template <class T>
  struct Abs
  {
    inline
    T operator() (const T &x) const
    {
      if (x < 0)
	return -x;
      else
	return x;
    }
  };

  /**
   * Unary minus functor.
   */
  template <class T>
  struct UnaryMinus
  {
    /**
       @param x any value.
       @return the opposite of \a x, i.e. -x.
    */
    inline
    T operator() (const T &x) const
    {
      return -x;
    }
  };

  /**
   * Unary minus functor.
   */
  template <class T>
  struct MultiplicationByScalar
  {
    inline
    MultiplicationByScalar( const T & aValue )
      : myValue( aValue )
    {}

    /**
       @param x any value.
       @return the value myValue * \a x.
    */
    inline
    T operator() (const T &x) const
    {
      return myValue * x;
    }

    T myValue;
  };

///////////////////////////////////////////////////////////////////////////////
// Some basic unary functors that may be useful
//////////////////////////////////////////////////////////////////////////////
  /**
   * Description of template class 'functors::Identity' <p>
   * \brief Aim: Define a simple default functor that
   * just returns its argument
   *
   */
  struct Identity
  {
    /**
     * Operator
     * @return @a aT.
     * @tparam T any type
     */
    template <typename T >
    inline
    T operator()(const T& aT) const
    {
      return aT;
    }
  };

  /**
   * Description of template class 'ConstValue' <p>
   * \brief Aim: Define a simple functor that returns
   * a constant value (0 by default).
   *
   * @tparam TValue type of the value
   */
  template <typename TValue>
  class ConstValue
  {
  public:
    typedef TValue Value;

    /**
     * Constructor.
     * @param aValue  the constant value.
     */
    ConstValue(const Value& aValue = 0)
      :myValue(aValue) {};

    /**
     * Operator
     *
     * @tparam TInput type of the input object
     *
     * @return the constant value.
     */
    template <typename TInput>
    inline
    Value operator()(const TInput& /*aInput*/) const
    {
      return myValue;
    }

  private:
    /**
     * value
     */
    Value myValue;
    
  };

  /**
   * Description of template class 'ConstValueCell' <p>
   * \brief Aim: Define a simple functor that returns
   * a constant quantity (0 by default).
   *
   * @tparam TQuantity type of the quantity
   * @tparam TCell type of the cell
   */
  template <typename TQuantity, typename TCell>
  class ConstValueCell
  {
  public:
    typedef TCell Cell;
    typedef TQuantity Quantity;

    /**
     * Constructor.
     * @param aQuantity  the constant quantity.
     */
    ConstValueCell(const Quantity& aQuantity = 0)
      :myQuantity(aQuantity) {}

    /**
     * Operator
     *
     * @return the constant value.
     */
    inline
    Quantity operator()(const Cell& /*aInput*/) const
    {
      return myQuantity;
    }

  private:
    /**
     * value
     */
    Quantity myQuantity;

  };


  /**
   * Description of template class 'Cast' <p>
   * \brief Aim: Define a simple functor using the static cast operator.
   *
   * @tparam TOutput type of the return value
   */
  template <typename TOutput >
  struct Cast
  {
    /**
     * Operator
     * @return the conversion of @a aInput into an object of type TOutput.
     * @tparam TInput type of the input value
     */
    template<typename TInput>
    inline
    TOutput operator()(const TInput& aInput) const
    {
      return static_cast<TOutput>(aInput);
    }
  };

  /**
   * Description of template class 'Composer' <p>
   * \brief Aim: Define a new Functor from the composition of two other functors
   *
   * @tparam TFunctor1 first functor
   * @tparam TFunctor2 second functor
   * @tparam ReturnType return type
   */
  template <typename TFunctor1, typename TFunctor2, typename ReturnType >
  class Composer
  {
  public:
    /// Necessary for DistanceVisitor.
    typedef ReturnType Value;

    /**
     * Default constructor
     */
    Composer(): myF1(NULL), myF2(NULL) {}
    /**
     * Constructor
     * @param aF1 any Functor
     * @param aF2 any Functor
     */
    Composer(const TFunctor1& aF1, const TFunctor2& aF2): myF1(&aF1), myF2(&aF2) {}
    /**
     * Copy Operator
     * @param other object to copy
     */
    Composer(const Composer& other): myF1(other.myF1), myF2(other.myF2) {}

    /**
     * Assignement Operator
     * @param other object to copy
     */
    Composer& operator=(const Composer& other)
    {
      if (this != &other)
	{
	  myF1 = other.myF1;
	  myF2 = other.myF2;
	}
    return *this;
    }


    /**
     * Operator ()
     *
     * NB: @a myF2 return type should be equal to
     * (or implicitly castable into) ReturnType
     *
     * @return object of type ReturnType coming from
     * the composition @a myF1 o @a myF2 on @a aInput,
     * ie. myF2 ( myF1 ( aInput ) )
     *
     * @tparam TInput type of the input value
     */
    template<typename TInput>
    inline
    ReturnType operator()(const TInput& aInput) const
    {
      ASSERT( myF1 );
      ASSERT( myF2 );
      return myF2->operator()( myF1->operator()( aInput ) );
    }

  private:
    /**
     * Aliasing pointer to the first functor.
     */
    const TFunctor1* myF1;
    /**
     * Aliasing pointer to the second functor.
     */
    const TFunctor2* myF2;
  };

/**
 * // template class Thresholder
 * \brief Aim: A small functor with an operator ()
 * that compares one value to a threshold value
 * according to two bool template parameters.
 *
 * @tparam T  type for a value that must be equally and less-than comparable
 * @tparam isLower  a bool for the comparison sign :
 * 'true' for < (default), 'false' for <
 * @tparam isEqual  a bool for the equality :
 * 'true' for a large inequality (default), 'false' for a strict one
 *
 */
template <typename T, bool isLower = true, bool isEqual = true >
class Thresholder
 {
  public:
    BOOST_CONCEPT_ASSERT(( boost::EqualityComparable<T> ));
    BOOST_CONCEPT_ASSERT(( boost::LessThanComparable<T> ));

    typedef T Input;

    /**
     * Constructor.
     * @param aT  the threshold value (default 0).
     */
    Thresholder(const Input& aT = 0):myT(aT) {}
    /**
    * Compares  @a aI to @ myT.
    * @param aI  any input value
    * @return 'true' or 'false' according to isLower and isEqual
    */
    bool operator()(const Input& aI) const {
      std::less_equal<Input> c;
      return c(aI,myT);
    }
  private:
    /**
     * Threshold value
     */
   Input myT;
};

//specializations
template <typename T>
struct Thresholder<T,false,false>
{

  public:
    BOOST_CONCEPT_ASSERT(( boost::EqualityComparable<T> ));
    BOOST_CONCEPT_ASSERT(( boost::LessThanComparable<T> ));

    typedef T Input;

    Thresholder(const Input& aT = 0):myT(aT) {}

    bool operator()(const Input& aI) const {
    std::greater<Input> c;
    return c(aI,myT);
    }

  private:
    Input myT;
};
template <typename T>
struct Thresholder<T,false,true>
 {
  public:
    BOOST_CONCEPT_ASSERT(( boost::EqualityComparable<T> ));
    BOOST_CONCEPT_ASSERT(( boost::LessThanComparable<T> ));

    typedef T Input;

    Thresholder(const Input& aT = 0):myT(aT) {}
    bool operator()(const Input& aI) const {
    std::greater_equal<Input> c;
    return c(aI,myT);
    }

  private:
    Input myT;
};

template <typename T>
struct Thresholder<T,true,false>
  {
  public:
    BOOST_CONCEPT_ASSERT(( boost::EqualityComparable<T> ));
    BOOST_CONCEPT_ASSERT(( boost::LessThanComparable<T> ));

    typedef T Input;

    Thresholder(const Input& aT = 0):myT(aT) {}

    bool operator()(const Input& aI) const {
    std::less<Input> c;
    return c(aI,myT);
    }

  private:
    Input myT;
};

template <typename T>
struct Thresholder<T,true,true>
 {
  public:
    BOOST_CONCEPT_ASSERT(( boost::EqualityComparable<T> ));
    BOOST_CONCEPT_ASSERT(( boost::LessThanComparable<T> ));

    typedef T Input;

    Thresholder(const Input& aT = 0):myT(aT) {}

    bool operator()(const Input& aI) const {
    std::less_equal<Input> c;
    return c(aI,myT);
    }

  private:
    Input myT;
};

  /////////////////////////////////////////////////////////////////////////////
  // template class PredicateCombiner
  /**
   * Description of template class 'PredicateCombiner' <p> \brief
   * Aim: The predicate returns true when the given binary functor
   * returns true for the two Predicates given at construction.
   *
   * @tparam TPredicate1 the left predicate type.
   * @tparam TPredicate2 the right predicate type.
   * @tparam TBinaryFunctor binary functor used for comparison
   */
  template <typename TPredicate1, typename TPredicate2,
	    typename TBinaryFunctor = BoolFunctor2 >
  struct PredicateCombiner
  {
    typedef TPredicate1 Predicate1;
    typedef TPredicate2 Predicate2;

    /**
       Constructor from predicates and bool Functor.
       @param pred1 the left predicate.
       @param pred2 the right predicate.
       @param boolFunctor the binary function used to combine pred1
       and pred2.
     */
    PredicateCombiner( const Predicate1 & pred1,
        const Predicate2 & pred2,
        const TBinaryFunctor & boolFunctor )
      : myPred1( &pred1 ), myPred2( &pred2 ), myBoolFunctor( &boolFunctor )
    {
    }

    /**
       Copy constructor.
       @param other the object to copy
      */
    PredicateCombiner(  const PredicateCombiner& other )
      : myPred1( other.myPred1 ), myPred2( other.myPred2 ), myBoolFunctor( other.myBoolFunctor )
    {
    }

    /**
       Assignement
       @param other the object to copy
       @return reference to the current object
     */
    PredicateCombiner& operator=( const PredicateCombiner& other )
    {
      if (this != &other)
	{
	  myPred1 = other.myPred1;
	  myPred2 = other.myPred2;
	  myBoolFunctor = other.myBoolFunctor;
	}
    return *this;
    }

    /**
       Destructor
     */
    ~PredicateCombiner() {}

    /**
     * @param t any object of type T.
     * @tparam T any input type supported
     * by the two predicates to combine
     * @return the value of the predicate.
     */
    template<typename T>
    bool operator()( const T & t ) const
    {
      return myBoolFunctor->operator()( myPred1->operator()( t ),
					myPred2->operator()( t ) );
    }

    /// aliasing pointer to the left predicate.
    const Predicate1* myPred1;
    /// aliasing pointer to the right predicate.
    const Predicate2* myPred2;
    /// aliasing pointer to the binary functor.
    const TBinaryFunctor* myBoolFunctor;
  };

/**
 * template class IntervalThresholder
 * \brief Aim: A small functor with an operator ()
 * that compares one value to an interval.
 *
 * @tparam T  type for a value that must be equality and less-than comparable
 */
template <typename T>
class IntervalThresholder
{
public:
  BOOST_CONCEPT_ASSERT(( boost::EqualityComparable<T> ));
  BOOST_CONCEPT_ASSERT(( boost::LessThanComparable<T> ));

  /// input type
  typedef T Input;

  /// predicates type
  typedef Thresholder<T,false,true> Tlow;
  typedef Thresholder<T,true,true> Tup;
  typedef PredicateCombiner<Tlow,Tup,AndBoolFct2 > CombinedPredicate;

  /**
   * Constructor.
   * @param low lower threshold.
   * @param up upper threshold.
   */
  IntervalThresholder(const Input& low, const Input& up)
    : myTlow( low), myTup ( up ),
      myPred( myTlow, myTup, AndBoolFct2() ) {}

  /**
   * Compares  @a aI to @ myT.
   * @param aI  any input value
   * @return 'true' or 'false' according to @a myPred
   */
  bool operator()(const Input& aI) const
  {
    return myPred(aI);
  }
private:
  /**
   * First thresholder
   */
  Tlow myTlow;
  /**
   * Second thresholder
   */
  Tup myTup;
  /**
   * Combined predicate
   */
  CombinedPredicate myPred;
};


  /**
   * Description of template class 'Pair1st' <p>
   * \brief Aim: Define a simple functor that returns
   * the first member of a pair.
   *
   * @tparam ReturnType  type of the first member of the pair
   */
  template <typename ReturnType>
  class Pair1st
  {
  public:

    /**
     * Operator
     *
     * @tparam TPair model of CPair
     * @param aPair input pair
     *
     * @return first member of @a aPair.
     */
    template <typename TPair>
    inline
    ReturnType operator()(const TPair& aPair) const
    {
      return aPair.first;
    }

  };

  /**
   * Description of template class 'Pair2nd' <p>
   * \brief Aim: Define a simple functor that returns
   * the second member of a pair.
   *
   * @tparam ReturnType  type of the second member of the pair
   */
  template <typename ReturnType>
  class Pair2nd
  {
  public:

    /**
     * Operator
     *
     * @tparam TPair model of CPair
     * @param aPair input pair
     *
     * @return second member of @a aPair.
     */
    template <typename TPair>
    inline
    ReturnType operator()(const TPair& aPair) const
    {
      return aPair.second;
    }

  };

  /**
   * Description of template class 'Pair1stMutator' <p>
   * \brief Aim: Define a simple unary functor that returns
   * a reference on the first member of a pair in order
   * to update it.
   *
   * @tparam ReturnType  type of the first member of the pair
   */
  template <typename ReturnType>
  class Pair1stMutator
  {
  public:

    /**
     * Operator
     *
     * @tparam TPair model of CPair
     * @param aPair input pair
     *
     * @return reference on the first member of @a aPair.
     */
    template <typename TPair>
    inline
    ReturnType& operator()(TPair& aPair) const
    {
      return aPair.first;
    }

    /**
     * Operator
     *
     * @tparam TPair model of CPair
     * @param aPair input pair
     *
     * @return constant reference on the first member of @a aPair.
     */
    template <typename TPair>
    inline
    const ReturnType& operator()(const TPair& aPair) const
    {
      return aPair.first;
    }

  };

  /**
   * Description of template class 'Pair2ndMutator' <p>
   * \brief Aim: Define a simple unary functor that returns
   * a reference on the first member of a pair in order
   * to update it.
   *
   * @tparam ReturnType  type of the first member of the pair
   */
  template <typename ReturnType>
  class Pair2ndMutator
  {
  public:

    /**
     * Operator
     *
     * @tparam TPair model of CPair
     * @param aPair input pair
     *
     * @return reference on the second member of @a aPair.
     */
    template <typename TPair>
    inline
    ReturnType& operator()(TPair& aPair) const
    {
      return aPair.second;
    }

    /**
     * Operator
     *
     * @tparam TPair model of CPair
     * @param aPair input pair
     *
     * @return constant reference on the second member of @a aPair.
     */
    template <typename TPair>
    inline
    const ReturnType& operator()(const TPair& aPair) const
    {
      return aPair.second;
    }

  };

  /**
   * Description of template class 'Rescaling' <p>
   * \brief Aim: Functor allowing to rescale a value.
   * Values of the initial scale [initMin,initMax] are rescaled to the new scale [newMin,newMax].
   *
   * @tparam TInputType the type of values on the inital scale.
   * @tparam TOutputType the type of values on the new scale.
   */
  template<typename TInputType, typename TOutputType>
  struct Rescaling
  {
      TInputType myInitMin;
      TInputType myInitMax;
      TInputType myInitRange;

      TOutputType myNewMin;
      TOutputType myNewMax;
      TOutputType myNewRange;

      /**
       * Constructor.
       *
       * @param initMin the minimum value of the initial scale. Lower values are set to this value.
       * @param initMax the maximum value of the initial scale. Greater values are set to this value.
       * @param newMin the minimum value of the new scale.
       * @param newMax the maximum value of the new scale.
       */
      Rescaling( const TInputType &initMin, const TInputType &initMax, const TOutputType &newMin, const TOutputType &newMax ) :
                          myInitMin(initMin), myInitMax(initMax), myInitRange(initMax-initMin), myNewMin(newMin), myNewMax(newMax), myNewRange(newMax-newMin) {}
      /**
       * Operator.
       *
       *
       * @param anInitVal value of the initial scale.
       *
       * @return value of anInitVal, considered on the initial scale, on the new scale.
       */
      inline
      TOutputType operator() (const TInputType& anInitVal) const
      { return anInitVal<myInitMin ? myNewMin : anInitVal > myInitMax ? myNewMax : (anInitVal-myInitMin)*myNewRange/myInitRange + myNewMin; }
  };


  /**
   * Description of class 'GaussianKernel' <p>
   * \brief Aim: defines a
   * functor on double numbers which corresponds to a Gaussian
   * convolution kernel.  This functor acts from [0,1] to [0,1]
   *
   */
  struct GaussianKernel
  {
    /**
     * Constructor
     *
     * @param [in] aSigma the sigma parameter of the Gaussian function.
     */
    GaussianKernel(const double aSigma) :mySigma(aSigma)
    {
      myCoef = 1.0/(mySigma * sqrt(2.0*M_PI));
      myCoef2 = 1.0/(2.0*M_PI);
   }

    /**
     * @return the Gaussian value at point @a aVal
     * @param  [in] aVal a value between 0 and 1.
     */
    inline
    double operator()(const double aVal) const
    {
      ASSERT((aVal <= 1) && (aVal>=0));
      return myCoef*exp(-aVal*aVal*myCoef2);
    }

    ///Sigma parameter
    double mySigma;

    ///Temporary variable
    double myCoef;
  private: 
    ///Temporary variable
    double myCoef2;
  };
}
}
///////////////////////////////////////////////////////////////////////////////


#endif // !defined BasicFunctors_h

#undef BasicFunctors_RECURSES
#endif // else defined(BasicFunctors_RECURSES)
