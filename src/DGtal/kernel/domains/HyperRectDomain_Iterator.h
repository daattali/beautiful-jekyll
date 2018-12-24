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
 * @file HyperRectDomain_Iterator.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * @author Guillaume Damiand
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/05/31
 *
 * Header file for module HyperRectDomain_Iterator.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(HyperRectDomain_Iterator_RECURSES)
#error Recursive header files inclusion detected in HyperRectDomain_Iterator.h
#else // defined(HyperRectDomain_Iterator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define HyperRectDomain_Iterator_RECURSES

#if !defined HyperRectDomain_Iterator_h
/** Prevents repeated inclusion of headers. */
#define HyperRectDomain_Iterator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//#include <iterator> // Bug for operator * => dangling reference !!!
// Class allowing to build a reverse iterator of a given iterator.
template<typename _Iterator>
class myreverse_iterator
  : public std::iterator<typename std::iterator_traits<_Iterator>::iterator_category,
                         typename std::iterator_traits<_Iterator>::value_type,
                         typename std::iterator_traits<_Iterator>::difference_type,
                         typename std::iterator_traits<_Iterator>::pointer,
                         typename std::iterator_traits<_Iterator>::reference>
{
protected:
  _Iterator current;
  _Iterator prev;

public:
  typedef _Iterator                 iterator_type;
  typedef typename std::iterator_traits<_Iterator>::difference_type
      difference_type;
  typedef typename std::iterator_traits<_Iterator>::reference   reference;
  typedef typename std::iterator_traits<_Iterator>::pointer     pointer;

public:
  explicit
      myreverse_iterator(iterator_type __x) : current(__x),
      prev(current)
  { --prev; }

  myreverse_iterator(const myreverse_iterator& __x)
    : current(__x.current), prev(__x.prev) { }

  iterator_type base() const
  { return current; }

  /*const*/ reference operator*() const
  { return *prev; }

  reference operator*()
  { return *prev; }

  pointer operator->() const
  { return &(operator*()); }

  myreverse_iterator& operator++()
  { --current; --prev;
    return *this;
  }

  myreverse_iterator operator++(int)
  {
    myreverse_iterator __tmp = *this;
    operator++();
    return __tmp;
  }

  myreverse_iterator& operator--()
  {
    ++current; ++prev;
    return *this;
  }

  myreverse_iterator operator--(int)
  {
    myreverse_iterator __tmp = *this;
    operator--();
    return __tmp;
  }

  myreverse_iterator operator+(difference_type __n) const
  { return myreverse_iterator(current - __n); }

  myreverse_iterator& operator+=(difference_type __n)
                                {
    current -= __n; prev = current; --prev;
    return *this;
  }

  myreverse_iterator operator-(difference_type __n) const
  { return myreverse_iterator(current + __n); }

  myreverse_iterator& operator-=(difference_type __n)
                                {
    current += __n; prev = current; --prev;
    return *this;
  }

  reference operator[](difference_type __n) const
  { return *(*this + __n); }
};
template<typename _Iterator>
inline bool
    operator==(const myreverse_iterator<_Iterator>& __x,
               const myreverse_iterator<_Iterator>& __y)
{ return __x.base() == __y.base(); }
template<typename _Iterator>
inline bool
    operator!=(const myreverse_iterator<_Iterator>& __x,
               const myreverse_iterator<_Iterator>& __y)
{ return !(__x == __y); }

//******************************************************************************
namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // class HyperRectDomain_Iterator
  /**
   * Description of class 'HyperRectDomain_Iterator' <p>
   * Aim:
   */
  template<typename TPoint>
  class HyperRectDomain_Iterator
  {
  public:
    typedef std::bidirectional_iterator_tag iterator_category; ///\todo construct a RANDOM-ACCESS iterator
    typedef TPoint value_type;
    typedef ptrdiff_t difference_type;
    typedef TPoint* pointer;
    typedef TPoint& reference;
    typedef typename TPoint::Dimension Dimension;


    HyperRectDomain_Iterator( const TPoint & p, const TPoint& lower, const TPoint &upper )
      : myPoint( p ), mylower( lower ), myupper( upper )
      {
        ASSERT_MSG( // For an empty domain, lower = upper + diag(1) so that begin() == end().
            lower.isLower(upper) || lower == upper + TPoint::diagonal(1),
            "The lower bound must be lower than the upper bound or, for an empty domain, be equal to the upper bound + diagonal(1)."
        );

        ASSERT_MSG( 
            ( lower.isLower(p) && p.isLower(upper) ) || p == lower || p == upper,
            "The point must be inside the domain or be equal to one of his bound."
        );
      }

    const TPoint & operator*() const
      {
        ASSERT_MSG( // we must be between [begin,end]
            mylower.isLower(myPoint) && myPoint.isLower(myupper),
            "The iterator points outside the domain." 
        );

        return myPoint;
      }

    TPoint & operator*()
      {
        ASSERT_MSG( // we must be between [begin,end]
            mylower.isLower(myPoint) && myPoint.isLower(myupper), 
            "The iterator points outside the domain."
        );
        
        return myPoint;
      }

    /**
     * Operator ==
     *
     */
    bool operator== ( const HyperRectDomain_Iterator<TPoint> &it ) const
      {
        return ( myPoint==it.myPoint );
      }

    /**
     * Operator !=
     *
     */
    bool operator!= ( const HyperRectDomain_Iterator<TPoint> &aIt ) const
      {
        return ( myPoint!=aIt.myPoint );
      }

    /**
     * Implements the next() method to scan the domain points dimension by dimension
     * (lexicographic order).
     **/
    void nextLexicographicOrder()
      {
        ++myPoint[0];
        if (( TPoint::dimension > 1 ) &&
            ( myPoint[0] > myupper[0] ) )
          {
            Dimension current_pos = 0;
            do
              {
                myPoint[current_pos] = mylower[current_pos];
                current_pos++;
                if ( current_pos < TPoint::dimension )
                  ++myPoint[current_pos];
              }
            while (( current_pos + 1 < TPoint::dimension ) &&
                ( myPoint[ current_pos ]  >  myupper[ current_pos ] ) );
          }
      }

    /**
     * Operator ++ (++it)
     */
    HyperRectDomain_Iterator<TPoint> &operator++()
      {
        nextLexicographicOrder();
        return *this;
      }

    /**
     * Operator ++ (it++)
     *
     */
    HyperRectDomain_Iterator<TPoint> operator++ ( int )
      {
        HyperRectDomain_Iterator<TPoint> tmp = *this;
        nextLexicographicOrder();
        return tmp;
      }

    /**
     * Implements the prev() method to scan the domain points dimension by dimension
     * (lexicographic order).
     **/
    void prevLexicographicOrder()
      {
        --myPoint[0];
        if (( TPoint::dimension > 1 ) &&
            ( myPoint[0]  <  mylower[0] ) )
          {
            Dimension current_pos = 0;
            do
              {
                myPoint[ current_pos ] = myupper[ current_pos ];
                ++current_pos;
                if ( current_pos < TPoint::dimension )
                  --myPoint[ current_pos ];
              }
            while (( current_pos + 1 < TPoint::dimension ) &&
                ( myPoint[ current_pos ]  <  mylower[ current_pos ] ) );
          }
      }

    /**
     * Operator -- (--it)
     *
     */
    HyperRectDomain_Iterator<TPoint> &operator--()
      {
        prevLexicographicOrder();
        return *this;
      }

    /**
     * Operator -- (it--)
     */
    HyperRectDomain_Iterator<TPoint> operator-- ( int )
      {
        HyperRectDomain_Iterator<TPoint> tmp = *this;
        prevLexicographicOrder();
        return tmp;
      }

  private:
    ///Current Point in the domain
    TPoint myPoint;
    ///Copies of the Domain limits
    TPoint mylower, myupper;
  }; // End of class HyperRectDomain_Iterator

  /////////////////////////////////////////////////////////////////////////////
  // class HyperRectDomain_Iterator
  /**
   * Description of class 'HyperRectDomain_subIterator' <p>
   * Aim:
   */
  template<typename TPoint>
  class HyperRectDomain_subIterator
  {
  public:
    typedef std::bidirectional_iterator_tag iterator_category; ///\todo construct a RANDOM-ACCESS iterator
    typedef TPoint value_type;
    typedef ptrdiff_t difference_type;
    typedef TPoint* pointer;
    typedef TPoint& reference;
    typedef typename TPoint::Dimension Dimension;

    HyperRectDomain_subIterator(const TPoint & p, const TPoint& lower,
        const TPoint &upper,
        std::initializer_list<Dimension> subDomain)
      : myPoint( p ), mylower( lower ), myupper( upper )
      {
        ASSERT_MSG( // For an empty domain, lower = upper + diag(1) so that begin() == end().
            lower.isLower(upper) || lower == upper + TPoint::diagonal(0).partialCopy( TPoint::diagonal(1), subDomain),
            "The lower bound must be lower than the upper bound or, for an empty domain, be equal to the upper bound + diagonal(1)."
            );

        ASSERT_MSG( 
            ( lower.isLower(p) && p.isLower(upper) ) || p == lower || p == upper, 
            "The point must be inside the domain or be equal to one of his bound."
        );

        ASSERT_MSG( 
            subDomain.size() <= TPoint::dimension,
            "The sub-range cannot have more dimensions than the ambiant space."
        );

        mySubDomain.reserve( subDomain.size() );
        for ( const unsigned int *c = subDomain.begin();
            c != subDomain.end(); ++c )
          {
            ASSERT_MSG( 
                *c <= TPoint::dimension,
                "Invalid dimension in the sub-range."
            );
            
            mySubDomain.push_back( *c );
          }

        // TODO: check the validity of the subDomain ?
      }

    HyperRectDomain_subIterator(const TPoint & p, const TPoint& lower,
        const TPoint &upper,
        const std::vector<Dimension> &subDomain)
      : myPoint( p ), mylower( lower ), myupper( upper )
      {
        ASSERT_MSG( // For an empty domain, lower = upper + diag(1) so that begin() == end().
            lower.isLower(upper) || lower == upper + TPoint::diagonal(0).partialCopy( TPoint::diagonal(1), subDomain ),
            "The lower bound must be lower than the upper bound or, for an empty domain, be equal to the upper bound + diagonal(1)."
        );

        ASSERT_MSG(
            ( lower.isLower(p) && p.isLower(upper) ) || p == lower || p == upper,
            "The point must be inside the domain or be equal to one of his bound."
        );

        ASSERT_MSG( 
            subDomain.size() <= TPoint::dimension,
            "The sub-range cannot have more dimensions than the ambiant space."
        );

        mySubDomain.reserve( subDomain.size() );
        for ( typename std::vector<Dimension>::const_iterator it = subDomain.begin();
            it != subDomain.end(); ++it )
          {
            ASSERT_MSG( 
                *it <= TPoint::dimension,
                "Invalid dimension in the sub-range."
            );
            mySubDomain.push_back( *it );
          }

        // TODO: check the validity of the subDomain ?
      }


    const TPoint & operator*() const
      {
        ASSERT_MSG( // we must be between [begin,end]
            mylower.isLower(myPoint) && myPoint.isLower(myupper),
            "The iterator points outside the domain."
        ); 

        return myPoint;
      }

    TPoint & operator*()
      {
        ASSERT_MSG( // we must be between [begin,end]
            mylower.isLower(myPoint) && myPoint.isLower(myupper),
            "The iterator points outside the domain."
        );

        return myPoint;
      }

    /**
     * Operator ==
     *
     */
    bool operator== ( const HyperRectDomain_subIterator<TPoint> &it ) const
      {
        for (unsigned int i=0; i<mySubDomain.size(); ++i)
          if ( myPoint[mySubDomain[i]]!=it.myPoint[mySubDomain[i]])
            return false;
        
        return true;
      }

    /**
     * Operator !=
     *
     */
    bool operator!= ( const HyperRectDomain_subIterator<TPoint> &aIt ) const
      {
        return !operator==(aIt);
      }

    /**
     * Implements the next() method to scan the domain points dimension by dimension
     * (by using the subDomain order given by the user).
     **/
    void nextSubDomainOrder()
      {
        ASSERT( mySubDomain.size() > 0 );
        ++myPoint[ mySubDomain[0] ];

        if ( mySubDomain.size() > 1 &&
            myPoint[ mySubDomain[0] ] >
            myupper[ mySubDomain[0] ] )
          {
            Dimension current_pos = 0;
            do
              {
                myPoint[ mySubDomain[current_pos] ] =
                  mylower[ mySubDomain[current_pos] ];
                ++current_pos;
                if ( current_pos < mySubDomain.size() )
                  ++myPoint[ mySubDomain[current_pos] ];
              }
            while (( current_pos + 1 < mySubDomain.size() ) &&
                ( myPoint[ mySubDomain[current_pos] ]  >
                  myupper[ mySubDomain[current_pos] ] ) );
          }
      }

    /**
     * Operator ++ (++it)
     */
    HyperRectDomain_subIterator<TPoint> &operator++()
      {
        nextSubDomainOrder();
        return *this;
      }

    /**
     * Operator ++ (it++)
     *
     */
    HyperRectDomain_subIterator<TPoint> operator++ ( int )
      {
        HyperRectDomain_subIterator<TPoint> tmp = *this;
        nextSubDomainOrder();
        return tmp;
      }

    /**
     * Implements the prev() method to scan the domain points dimension by dimension
     * (subDomain order).
     **/
    void prevSubDomainOrder()
      {
        ASSERT( mySubDomain.size() > 0 );
        --myPoint[ mySubDomain[0] ];

        if (  mySubDomain.size() > 1 &&
            myPoint[ mySubDomain[0] ]  <
            mylower[ mySubDomain[0] ] )
          {
            Dimension current_pos = 0;
            do
              {
                myPoint[ mySubDomain[current_pos] ] =
                  myupper[ mySubDomain[current_pos] ];
                ++current_pos;
                if ( current_pos < mySubDomain.size() )
                  --myPoint[ mySubDomain[current_pos] ];
              }
            while (( current_pos + 1 < mySubDomain.size() ) &&
                ( myPoint[ mySubDomain[current_pos] ]  <
                  mylower[ mySubDomain[current_pos] ] ) );
          }
      }

    /**
     * Operator -- (--it)
     *
     */
    HyperRectDomain_subIterator<TPoint> &operator--()
      {
        prevSubDomainOrder();
        return *this;
      }

    /**
     * Operator -- (it--)
     */
    HyperRectDomain_subIterator<TPoint> operator-- ( int )
      {
        HyperRectDomain_subIterator<TPoint> tmp = *this;
        prevSubDomainOrder();
        return tmp;
      }

  private:
    ///Current Point in the domain
    TPoint myPoint;
    ///Copies of the Domain limits
    TPoint mylower, myupper;
    ///Vector of subDomain on dimension, to fix the order in which dimensions
    /// are considered.
    std::vector<Dimension> mySubDomain;
  }; // End of class HyperRectDomain_subIterator

} //namespace
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined HyperRectDomain_Iterator_h

#undef HyperRectDomain_Iterator_RECURSES
#endif // else defined(HyperRectDomain_Iterator_RECURSES)
