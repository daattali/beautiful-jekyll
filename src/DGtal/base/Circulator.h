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
 * @file Circulator.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/07/05
 *
 * Header file for module Circulator.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Circulator_RECURSES)
#error Recursive header files inclusion detected in Circulator.h
#else // defined(Circulator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Circulator_RECURSES

#if !defined Circulator_h
/** Prevents repeated inclusion of headers. */
#define Circulator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include<iterator>
#include "DGtal/base/IteratorCirculatorTraits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{


  /////////////////////////////////////////////////////////////////////////////
  // template class Circulator
  /**
   * Description of template class 'Circulator' <p>
   * \brief Aim: 
   *  Provides an adapter for classical iterators that can 
   *  iterate through the underlying data structure as in a loop. 
   *  The increment (resp. decrement) 
   *  operator encapsulates the validity test and the assignement
   *  to the begin (resp. end) iterator of a given range, 
   *  when the end (resp. beginning) has been reached. 
   *  For instance, the pre-increment operator does:  
   *  @code
        ++myCurrentIt;
        if (myCurrentIt == myEndIt) myCurrentIt = myBeginIt;
        return *this;
   *  @endcode
   * whereas the pre-decrement operator does (if at least bidirectional): 
   *  @code
        if (myCurrentIt == myBeginIt) myCurrentIt = myEndIt;
        --myCurrentIt;
   *  @endcode
   *
   * Be aware that random access operators are quite different for
   * circular iterators and classical iterators. Firstly, the difference between 
   * two circular iterators c and d is always positive and such that
   * (c-d) + (d-c) is equal to the size of the underlying range. Secondly, 
   * comparison operators 'less than' and 'less than or equal to' always return 'true', 
   * whereas 'greater than' and 'greater than or equal to' always return 'false'. 
   *
   * @tparam TIterator any forward, bidirectional or random access iterator 
  */

  template <typename TIterator>
  class Circulator
  {

    BOOST_STATIC_ASSERT(( boost::is_same< 
			    typename IteratorCirculatorTraits<TIterator>::Type, 
			    IteratorType >::value ));
 
    // ----------------------- Types ------------------------------
  public:

      typedef TIterator                                           Iterator;
      typedef Circulator<TIterator>                               Self;

      typedef CirculatorType                                      Type; 

      typedef typename boost::iterator_category<TIterator>::type
                                                                     iterator_category;

    typedef typename std::iterator_traits<TIterator>::value_type        value_type;
    typedef typename std::iterator_traits<TIterator>::difference_type   difference_type;
    typedef typename std::iterator_traits<TIterator>::pointer           pointer;
    typedef typename std::iterator_traits<TIterator>::reference         reference;



    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Default constructor.
     * Default-initializes iterator members
     * NB: not valid
     */
    Circulator() : myCurrentIt(), myBeginIt(), myEndIt(), myFlagIsValid(false) {}


    /**
     * Constructor.
     * This object can iterate through the underlying data structure 
     * as in a loop, because it knows the begin and end iterator of the range. 
     * @param i any iterator
     * @param itb begin iterator
     * @param ite end iterator
     */
    Circulator(const Iterator& i,
               const Iterator& itb, 
               const Iterator& ite) 
     : myCurrentIt(i), myBeginIt(itb), myEndIt(ite), myFlagIsValid(true) 
    { if (myBeginIt == myEndIt) myFlagIsValid = false; }

    /**
     * Destructor.
     */
    ~Circulator() {}

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    Circulator ( const Circulator & other )
    : myCurrentIt(other.myCurrentIt), 
      myBeginIt(other.myBeginIt), myEndIt(other.myEndIt), 
      myFlagIsValid(other.myFlagIsValid)  
    {}

    /**
     *  Copy of circulators that adapts other iterator types (not const / const).
     * @param other the object to clone.
    */
    template<typename other_Iterator>
    Circulator ( const Circulator<other_Iterator>& other )
    : myCurrentIt(other.base()), 
      myBeginIt(other.begin()), myEndIt(other.end()), 
      myFlagIsValid(other.isValid())  
    {}

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    Circulator & operator= ( const Circulator & other ) 
    {
      if ( this != &other )
        {
          myCurrentIt = other.myCurrentIt;
          myBeginIt = other.myBeginIt;
          myEndIt = other.myEndIt;
	  if (myBeginIt != myEndIt) 
	    myFlagIsValid = true; 
	  else 
	    myFlagIsValid = false;
        }
      return *this;
    }

    /**
     * Assignment that adapts other iterator types (not const / const).
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    template<typename other_Iterator>
    Circulator & operator= ( const Circulator<other_Iterator>& other )
    {
      if ( this != &other )
        {
          myCurrentIt = other.base();
          myBeginIt = other.begin();
          myEndIt = other.end();
	  if (myBeginIt != myEndIt) 
	    myFlagIsValid = true; 
	  else 
	    myFlagIsValid = false;
        }
      return *this;
    }

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const 
    { return myFlagIsValid; }


    // ----------------------- Interface --------------------------------------
  public:

    /**
     *  @return  member [myCurrentIt], the underlying iterator.
    */
    Iterator base() const
    { return myCurrentIt; }

    /**
     *  @return  member [myBeginIt], begin iterator of the underlying range.
    */
    Iterator begin() const
    { return myBeginIt; }

    /**
     *  @return  member [myEndIt], end iterator of the underlying range.
    */
    Iterator end() const
    { return myEndIt; }

    /**
     *  @return  *myCurrentIt.
    */
    reference operator*() const 
    { 
     //ASSERT( myCurrentIt != myEndIt ); //myCurrentIt == myEndIt when using reverse iterators on circulators
     ASSERT( isValid() ); 
     return *myCurrentIt; 
    }

    /**
     *  @return  pointer to myCurrentIt
    */
    pointer operator->() const 
    { 
     //ASSERT( myCurrentIt != myEndIt ); //myCurrentIt == myEndIt when using reverse iterators on circulators
     ASSERT( isValid() ); 
     return myCurrentIt.operator->(); 
    }


    // ----------------------- Incrementation/Decrementation --------------------------------------
  public:

     /**
      *  Pre-increment
      */
      Self& operator++()
      {
        ASSERT( isValid() ); 
        ++myCurrentIt;
        if (myCurrentIt == myEndIt) myCurrentIt = myBeginIt;
        return *this;
      }

      /**
      * Post-increment
      */
      Self operator++(int)
      {
        Self tmp = *this;
        operator++(); 
        return tmp;
      }


     /**
      *  Pre-decrement
      */
      Self& operator--()
      {
        ASSERT( isValid() ); 
        if (myCurrentIt == myBeginIt) myCurrentIt = myEndIt;
        --myCurrentIt;
        return *this;
      }

      /**
      * Post-decrement
      */
      Self operator--(int)
      {
        Self tmp = *this;
        operator--(); 
        return tmp;
      }

    // ----------------------- Equality operators --------------------------------------
  public:

    //'true' if their three underlying iterators are equal
    //or if their underlying ranges are both empty,
    //'false' otherwise
    bool operator==( const Self& other) const 
    { 
      return ( ( (!isValid())&&(!other.isValid()) )
               || 
               ( ( isValid() && other.isValid())
                 &&
                 ( (myBeginIt == other.begin())
                   &&(myEndIt == other.end())
                   &&(myCurrentIt == other.base())
                   )
                 )
               ); 
    }
    bool operator!=( const Self& other) const { return !(*this == other); }

    template<typename OtherIterator>
    bool operator==( const OtherIterator& other) const 
    { 
      return ( ( (!isValid())&&(!other.isValid()) )
               || 
               ( ( isValid() && other.isValid())
                 &&
                 ( (myBeginIt == other.begin())
                   &&(myEndIt == other.end())
                   &&(myCurrentIt == other.base())
                   )
                 )
               ); 
    }
    template<typename OtherIterator>
    bool operator!=( const OtherIterator& other) const { return !(*this == other); }


    // ----------------------- Random access operators --------------------------------------
  public:

    Self& operator+=( difference_type d ) 
    {
      if ( isValid() )
	{
	  //size range
	  typename Iterator::difference_type n = myEndIt - myBeginIt;
	  ASSERT( n > 0 );
	  //difference modulo n
	  if ( (d >= n)||(-d >= n) )
	    d = d%n; 
	  ASSERT( (d < n)&&(-d < n) );
	  //position of the current iterator
	  typename Iterator::difference_type j = myCurrentIt - myBeginIt;
	  ASSERT( (j >= 0) && (j < n) );
	  //deviation between the position of the past-the-end value 
	  //and the current iterator
	  typename Iterator::difference_type e = n - j;
	  if (d >= 0)
	    { //in case of positive distance
	      if (d < e) j += d;
	      else j = d - e; 
	    }
	  else 
	    { //in case of negative distance
	      if (-d <= j) j += d; 
	      else j = j + d + n; 
	    }
	  ASSERT( (j >= 0) && (j < n) );
	  myCurrentIt = myBeginIt + j;
	  return *this;
	}
      else
	return *this; 
    }

    Self& operator-=( difference_type d) { return operator+=( -d); }

    Self operator+( difference_type d) const 
    {
        Self tmp = *this;
        return tmp += d;
    }

    Self operator-( difference_type d) const 
    {
        Self tmp = *this;
        return tmp += -d;
    }

    difference_type operator-( const Self& c) const 
    {
	typename Iterator::difference_type d = (myCurrentIt - c.myCurrentIt);
	if (d >= 0)
	  return d; 
	else 
	  {
	    typename Iterator::difference_type n = myEndIt - myBeginIt;
	    ASSERT( n > 0 );
	    return (n + d); 
	  }
    }
    reference operator[]( difference_type d) const 
    {
        Self tmp = *this;
        tmp += d;
        return *tmp;
    }

    // ----------------------- Comparisons operators --------------------------------------
    bool operator<( const Self& /*c*/) const 
    {
      return true; 
    }
    bool operator<=( const Self& /*c*/) const 
    {
      return true; 
    }
    bool operator>( const Self& c) const 
    {
      return !operator<=(c); 
    }
    bool operator>=( const Self& c) const 
    {
      return !operator>(c); 
    }


    // ------------------------- Protected Datas --------------------------------
  protected:

    Iterator myCurrentIt; 
    Iterator myBeginIt; 
    Iterator myEndIt; 
    bool myFlagIsValid; 

    // ------------------------- Private Datas --------------------------------
  private:



    // ------------------------- Hidden services ------------------------------
  protected:



  private:


  }; // end of class Circulator


  template <typename TIterator>
  Circulator<TIterator> 
  operator+(typename IteratorCirculatorTraits<TIterator>::Difference d, 
	    Circulator<TIterator> & object )
  {
    Circulator<TIterator> tmp = object;
    return tmp += d;
  }


} // namespace DGtal

#include "DGtal/base/IteratorFunctions.h"

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
//#include "DGtal/base/Circulator.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Circulator_h

#undef Circulator_RECURSES
#endif // else defined(Circulator_RECURSES)
