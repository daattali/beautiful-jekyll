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
 * @file
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2017/05/28
 *
 * Header file for module IntegerSequenceIterator.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(IntegerSequenceIterator_RECURSES)
#error Recursive header files inclusion detected in IntegerSequenceIterator.h
#else // defined(IntegerSequenceIterator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define IntegerSequenceIterator_RECURSES

#if !defined IntegerSequenceIterator_h
/** Prevents repeated inclusion of headers. */
#define IntegerSequenceIterator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <boost/iterator/iterator_facade.hpp>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class IntegerSequenceIterator
  /**
   * Description of template class 'IntegerSequenceIterator' <p>
   * \brief Aim: It is a simple class that mimics a (non mutable)
   * iterator over integers. You can increment it, decrement it,
   * displace it, compare it, etc. It is useful if you have a
   * collection of consecutive integers, and you wish to create an
   * iterator over it. It is used in the class TriangulatedSurface for
   * example, since vertices are numbers from 0 to nbVertices - 1.
   *
   * It is model of boost::RandomAccessIterator.
   */
  template <typename TInteger>
  class IntegerSequenceIterator
    : public boost::iterator_facade< IntegerSequenceIterator< TInteger >,
				     TInteger const,
				     boost::random_access_traversal_tag >
  {
  public:
    typedef IntegerSequenceIterator<TInteger> Self;
    typedef TInteger                          Integer;
    
    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor from Integer;
     * @param n any integer (default to zero).
     */
    IntegerSequenceIterator( Integer n = Integer( 0 ) ) : myNumber( n ) {}

    /**
     * Destructor.
     */
    ~IntegerSequenceIterator() = default;

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    IntegerSequenceIterator ( const IntegerSequenceIterator & other ) = default;

    /**
     * Move constructor.
     * @param other the object to move.
     */
    IntegerSequenceIterator ( IntegerSequenceIterator && other ) = default;

    /**
     * Copy assignment operator.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    IntegerSequenceIterator & operator= ( const IntegerSequenceIterator & other ) = default;

    /**
     * Move assignment operator.
     * @param other the object to move.
     * @return a reference on 'this'.
     */
    IntegerSequenceIterator & operator= ( IntegerSequenceIterator && other ) = default;

    // ----------------------- Boost facade services --------------------------------------
  private:
    friend class boost::iterator_core_access;

    /// Increments the iterator. Required by boost::iterator_facade.
    void increment() { myNumber++; }
    /// Decrements the iterator. Required by boost::iterator_facade.
    void decrement() { myNumber--; }
    /// Advances the iterator. Required by boost::iterator_facade.
    /// @param n the number of forward steps performed by the iterator.
    void advance( std::ptrdiff_t n ) { myNumber += n; }
    /// Distance to given iterator. Required by boost::iterator_facade.
    /// @param other any iterator on the same sequence.
    std::ptrdiff_t distance_to( IntegerSequenceIterator const& other )
    { return other.myNumber - myNumber; }
    /// Equality comparison with another iterator. Required by boost::iterator_facade.
    /// @param other any iterator on the same sequence.
    bool equal( IntegerSequenceIterator const& other) const
    { return this->myNumber == other.myNumber; }
    /// @return the integer value corresponding to the position of
    /// this iterator. Required by boost::iterator_facade.
    Integer const& dereference() const { return myNumber; }
    
    // ----------------------- Interface --------------------------------------
  public:

    // ------------------------- Protected Datas ------------------------------
  protected:
    /// The current value of the interator.
    Integer myNumber;
    
    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class IntegerSequenceIterator

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined IntegerSequenceIterator_h

#undef IntegerSequenceIterator_RECURSES
#endif // else defined(IntegerSequenceIterator_RECURSES)
