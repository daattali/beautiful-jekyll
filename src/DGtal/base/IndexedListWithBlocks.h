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
 * @file IndexedListWithBlocks.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/07/05
 *
 * Header file for module IndexedListWithBlocks.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(IndexedListWithBlocks_RECURSES)
#error Recursive header files inclusion detected in IndexedListWithBlocks.h
#else // defined(IndexedListWithBlocks_RECURSES)
/** Prevents recursive inclusion of headers. */
#define IndexedListWithBlocks_RECURSES

#if !defined IndexedListWithBlocks_h
/** Prevents repeated inclusion of headers. */
#define IndexedListWithBlocks_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <cstring>
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class IndexedListWithBlocks
  /**
     Description of template class 'IndexedListWithBlocks' <p> \brief
     Aim: Represents a mixed list/array structure which is useful in
     some context. It is essentially a list of blocks.

     @verbatim
     if less than 3 values and N = 2
     +------+------+------+------+------+
     | size | V[0] | V[1] | ...  |  0   |
     +------+------+------+------+------+

     if only 3 values and N = 2
     +------+------+------+------+------+
     | size | V[0] | V[1] | V[2] | V[3] |
     +------+------+------+------+------+

     if more than 3 values and N = 2, M = 4
     +------+------+------+------+------+        +------+------+------+------+------+
     | size | V[0] | V[1] | V[2] | ptr --------> | V[3] | V[4] | V[5] | V[6] | ptr --------> ...
     +------+------+------+------+------+        +------+------+------+------+------+

     @endverbatim

     Such a structure is useful when:
     - the user knows at which position/index lies its value.
     - the expected size of this container is small, but may sometimes increase.
     - the user wishes sometimes to insert a new value or erase another value. Note that in this case the user knows that further indices have changed.
     - the user wishes to have a random access to the values that is as fast as possible.
     - one wishes to limit as possible the memory usage.
     - generally this structure is embedded as the value of a big array.

     @tparam TValue the type for the values stored in the list.
     @tparam N the number of value stored in the first block.
     @tparam M the number of value stored in the further blocks.

     NB: In the following, we use the notations
     - n is the size of the container
     - b is the number of blocks ( b = 1 + (size()-N) / M ).
   */
  template <typename TValue, unsigned int N, unsigned int M>
  class IndexedListWithBlocks
  {
    BOOST_STATIC_ASSERT( N >= 1 );
    BOOST_STATIC_ASSERT( M >= 2 );
  public:
    // ----------------------- Public types ------------------------------
    typedef TValue Value;
    typedef std::ptrdiff_t DifferenceType;
    typedef std::size_t SizeType;
    typedef Value& Reference;
    typedef Value* Pointer;
    typedef const Value& ConstReference;
    typedef const Value* ConstPointer;

    class Iterator;
    class ConstIterator;

    // ----------------------- Standard types ------------------------------
    typedef Value value_type;
    typedef DifferenceType difference_type;
    typedef Reference reference;
    typedef Pointer pointer;
    typedef ConstReference const_reference;
    typedef ConstPointer const_pointer;
    typedef SizeType size_type;
    typedef Iterator iterator;
    typedef ConstIterator const_iterator;
    
    struct FirstBlock; ///< Forward declaration
    struct AnyBlock; ///< Forward declaration

    union BlockPointer {
      FirstBlock* first;
      AnyBlock* any;
    };

    /// Used in blocks to finish it or to point to the next block.
    union ValueOrBlockPointer {
      Value lastValue; // used when at the end of the list
      AnyBlock* nextBlock;  // used otherwise
    };

    /// Represents the first block in the container.
    /// Internal structure.
    struct FirstBlock {
      inline
      FirstBlock() : size( 0 )
      { data.nextBlock = 0; }

      inline
      void insert( unsigned int idx, const Value & v )
      {
	if ( size <= N )
	  {
	    ASSERT( idx <= size );
	    // works also in the case we use 'data' to store a N+1-th value.
	    std::copy_backward( values + idx, values + size, values + size + 1 );
	    values[ idx ] = v;
	  }
	else if ( size == (N+1) )
	  {
	    ASSERT( idx <= size );
	    // This cannot be tested.
	    // ASSERT( data.nextBlock == 0 );
	    AnyBlock* next = new AnyBlock;
	    if ( idx < N )
	      {
		next->values[ 0 ] = values[ N - 1 ];
		next->values[ 1 ] = data.lastValue;
		std::copy_backward( values + idx, values + N - 1, values + N );
		values[ idx ] = v;
	      }
	    else if ( idx == N )
	      {
		next->values[ 0 ] = v;
		next->values[ 1 ] = data.lastValue;
	      }
	    else if ( idx > N )
	      {
		next->values[ 0 ] = data.lastValue;
		next->values[ 1 ] = v;
	      }
	    data.nextBlock = next;
	  }
	else // size > N + 1
	  {
	    if ( idx < N )
	      {
		Value v1 = values[ N - 1 ];
		std::copy_backward( values + idx, values + N - 1, values + N );
		data.nextBlock->insert( 0, size - N, v1 );
		values[ idx ] = v;
	      }
	    else
	      data.nextBlock->insert( idx - N, size - N, v );
	  }
	++size;
      }

      inline 
      void erase( unsigned int idx )
      {
	// std::cerr << "FirstBlock::erase(" << idx << ")"
	// 	  << " this=" << this
	// 	  << " next=" << data.nextBlock
	// 	  << std::endl;
	ASSERT( idx < size );
	if ( size <= ( N + 1 ) )
	  {
	    // works also in the case we use 'data' to store a N+1-th value.
	    std::copy( values + idx + 1, values + size, values + idx );
            data.nextBlock = 0;
	  }
	else if ( size == N + 2 )
	  { 
	    if ( idx < N )
	      {
		std::copy( values + idx + 1, values + N, values + idx );
		values[ N - 1 ] = data.nextBlock->values[ 0 ];
                Value tmp = data.nextBlock->values[ 1 ];
		delete data.nextBlock;
                data.lastValue = tmp;
	      }
	    else if ( idx == N )
              {
                Value tmp = data.nextBlock->values[ 1 ];
		delete data.nextBlock;
                data.lastValue = tmp;
              }
            else // idx == N + 1
              {
                Value tmp = data.nextBlock->values[ 0 ];
		delete data.nextBlock;
                data.lastValue = tmp;
              }
	  }
	else // size > N + 2
	  {
	    if ( idx < N )
	      {
		std::copy( values + idx + 1, values + N, values + idx );
		values[ N - 1 ] = data.nextBlock->values[ 0 ];
		data.nextBlock = data.nextBlock->erase( 0, size - N );
	      }
	    else
	      data.nextBlock = data.nextBlock->erase( idx - N, size - N );
	  }
	--size;
      }

      unsigned int size;
      Value values[ N ];
      ValueOrBlockPointer data;
    };

    /// Represents a block (except the first) in the container.
    /// Internal structure.
    struct AnyBlock {
      inline AnyBlock() : next( 0 ) {}

      inline
      void insert( unsigned int idx, unsigned int size, const Value & v )
      {
        ASSERT( idx <= size );
	if ( idx >= M ) 
	  {
	    if ( next == 0 )
	      {
		ASSERT( idx == M );
		next = new AnyBlock;
                next->values[ 0 ] = v;
	      }
            else
              next->insert( idx - M, size - M, v );
	  }
	else 
	  { // idx < M
            if ( size < ( M - 1) )
              {
                std::copy_backward( values + idx, values + size, 
                                    values + size + 1 );
                values[ idx ] = v;
              }
            else
              {
                Value v1 = values[ M - 1 ];
                std::copy_backward( values + idx, values + M - 1, values + M );
                values[ idx ] = v;
                if ( size >= M )
                  {
                    if ( next == 0 )
                      {
                        ASSERT( size == M );
                        next = new AnyBlock;
                        next->values[ 0 ] = v1;
                      }
                    else
                      next->insert( 0, size - M, v1 );
                  }
              }
	  }
      }

      inline 
      AnyBlock* erase( unsigned int idx, unsigned int size )
      {
	// std::cerr << "AnyBlock::erase(" << idx << "," << size << ")" 
	// 	  << " this=" << this
	// 	  << " next=" << next
	// 	  << std::endl;
        if ( size == 1 )
          {
            ASSERT( idx == 0 );
            delete this;
            return 0;
          }
	if ( idx < M )
	  {
	    std::copy( values + idx + 1, values + M, values + idx );
	    if ( next != 0 )
	      {
		ASSERT( size > M );
		values[ M - 1 ] = next->values[ 0 ];
                next = next->erase( 0, size - M );
	      }
	  }
	else
	  next = next->erase( idx - M, size - M );
	return this;
      }


      Value values[ M ];
      AnyBlock* next;
    };

    /**
       Pseudo-random iterator to visit IndexedListWithBlocks (it is
       only a random forward iterator).  Model of
       boost::ForwardIterator. Provides also + and += arithmetic.
    */
    class Iterator {
    public:
      typedef Iterator Self;
      typedef TValue Value;
      typedef Value* Pointer;
      typedef Value& Reference;
      typedef std::ptrdiff_t DifferenceType; ///< only positive offsets allowed.

      // ----------------------- std types ----------------------------------
      typedef Value value_type;
      typedef std::size_t size_type;
      typedef DifferenceType difference_type;
      typedef Pointer pointer;
      typedef Reference reference;
      //typedef const Reference const_reference;
      typedef std::forward_iterator_tag iterator_category;


    protected:
      unsigned int myIdx;      ///< current index in \a myValues of the iterator
      unsigned int myNbValues; ///< number of valid values in array \a myValues
      Value* myValues;         ///< array of \a myNbValues values.
      AnyBlock* myNext;        ///< pointer to next block or 0 if last block.

      friend class IndexedListWithBlocks;

    protected:
      /**
	 Constructor from first block and index. Used by class IndexedListWithBlocks.
      */
      Iterator( FirstBlock & block, unsigned int idx );
      
    public:
      /**
	 Default destructor.
      */
      ~Iterator();

      /**
	 Default constructor.
      */
      Iterator();

      /**
	 Copy constructor.
	 @param other the object to clone.
      */
      Iterator( const Iterator & other );

      /**
       * Assignment.
       * @param other the object to copy.
       * @return a reference on 'this'.
       */
      Self & operator= ( const Self & other );
      
      /**
	 Dereference operator.
	 @return the current value of the iterator, if valid.
      */
      Reference operator*() const;
     
      /**
	 Pointer dereference operator.
	 @return a non-mutable pointer on the current value.
      */  
      Pointer operator->() const;
      
      /** 
	  Pre-increment operator.
	  @return a reference to itself.
      */
      Self& operator++();
      
      /** 
	  Post-increment operator.
	  @return a reference to itself.
      */
      Self operator++( int );

      /** 
	  Addition operator. Moves the iterator at position + \a n.
	  @param n any positive integer
	  @return a reference to itself.
      */
      Self& operator+=( DifferenceType n );

      /** 
	  Positive offset dereference operator. Moves the iterator at position + \a n.
	  @param n any positive integer
	  @return a reference to itself.
      */
      Reference operator[]( DifferenceType n ) const;
    
      /**
	 Equality operator.
	 @param other any other iterator.
	 @return 'true' iff the iterators points on the same element.
      */
      bool operator==( const Self & other ) const;
      
      /**
	 Inequality operator.
	 @param other any other iterator.
	 @return 'true' iff the iterators points on different elements.
      */
      bool operator!=( const Self & other ) const;
      
      
    };


    /**
       Pseudo-random iterator to visit IndexedListWithBlocks (it is
       only a random forward iterator).  Model of
       boost::ForwardIterator. Provides also + and += arithmetic.
    */
    class ConstIterator {
    public:
      typedef ConstIterator Self;
      typedef TValue Value;
      typedef const Value* Pointer;
      typedef const Value& Reference;
      typedef std::ptrdiff_t DifferenceType; ///< only positive offsets allowed.

      // ----------------------- std types ----------------------------------
      typedef Value value_type;
      typedef std::size_t size_type;
      typedef DifferenceType difference_type;
      typedef Pointer pointer;
      typedef Reference reference;
      // typedef Reference const_reference;
      typedef std::forward_iterator_tag iterator_category;


    protected:
      unsigned int myIdx;      ///< current index in \a myValues of the iterator
      unsigned int myNbValues; ///< number of valid values in array \a myValues
      const Value* myValues;   ///< array of \a myNbValues values.
      const AnyBlock* myNext;  ///< pointer to next block or 0 if last block.

      friend class IndexedListWithBlocks;

    protected:
      /**
	 Constructor from first block and index.
         Used by class IndexedListWithBlocks.
      */
      ConstIterator( const FirstBlock & block, unsigned int idx );
      
    public:
      /**
	 Default destructor.
      */
      ~ConstIterator();

      /**
	 Default constructor.
      */
      ConstIterator();

      /**
	 Copy constructor.
	 @param other the object to clone.
      */
      ConstIterator( const ConstIterator & other );

      /**
       * Assignment.
       * @param other the object to copy.
       * @return a reference on 'this'.
       */
      Self & operator= ( const Self & other );
      
      /**
	 Dereference operator.
	 @return the current value of the iterator, if valid.
      */
      Reference operator*() const;
     
      /**
	 Pointer dereference operator.
	 @return a non-mutable pointer on the current value.
      */  
      Pointer operator->() const;
      
      /** 
	  Pre-increment operator.
	  @return a reference to itself.
      */
      Self& operator++();
      
      /** 
	  Post-increment operator.
	  @return a reference to itself.
      */
      Self operator++( int );

      /** 
	  Addition operator. Moves the iterator at position + \a n.
	  @param n any positive integer
	  @return a reference to itself.
      */
      Self& operator+=( DifferenceType n );

      /** 
	  Positive offset dereference operator. Moves the iterator at position + \a n.
	  @param n any positive integer
	  @return a reference to itself.
      */
      Reference operator[]( DifferenceType n ) const;
    
      /**
	 Equality operator.
	 @param other any other iterator.
	 @return 'true' iff the iterators points on the same element.
      */
      bool operator==( const Self & other ) const;
      
      /**
	 Inequality operator.
	 @param other any other iterator.
	 @return 'true' iff the iterators points on different elements.
      */
      bool operator!=( const Self & other ) const;
      
      
    };


    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor.
     */
    IndexedListWithBlocks();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    IndexedListWithBlocks ( const IndexedListWithBlocks & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    IndexedListWithBlocks & operator= ( const IndexedListWithBlocks & other );

    /**
     * Destructor.
     */
    ~IndexedListWithBlocks();

    // ----------------------- Container services -----------------------------
  public:
    
    /**
       The number of values stored in the structure. O(1) complexity.
     */
    SizeType size() const;

    /**
       @return 'true' if and only if the container is empty. O(1)
     */
    bool empty() const;

    /**
       The maximum number of values storable in the structure.
     */
    SizeType max_size() const;

    /**
       The number of values currently allocated in the structure.
     */
    SizeType capacity() const;

    /**
       Removes all the values stored in the structure. O(b)
       complexity.
     */
    void clear();

    /**
       Random unprotected read-write access to value at position \a idx
       @param idx the index of the value in the container.
       @return a reference on the value.
       @pre idx < size()
       NB: O( b ), E = O( 1 + ceil( ( idx - N ) / M ) )
    */
    Value & operator[]( unsigned int idx );

    /**
       Random unprotected read access to value at position \a idx
       @param idx the index of the value in the container.
       @return a const reference on the value.
       @pre idx < size()
       NB: O( b ), E = O( 1 + ceil( ( idx - N ) / M ) )
    */
    const Value & operator[]( unsigned int idx ) const;

    /**
       Insertion of a new value at given position. The former value at
       this position and the next ones are shifted.

       @param idx the index of the value in the container.
       @pre idx <= size() (if size(), inserts at the end.
       @param value the value to insert.
       NB: O( n ), E = O( n - idx )
    */
    void insert( unsigned int idx, const Value & value );

    /**
       Removal of a value at a given position. Following values are shifted.

       @param idx the index of the value in the container.
       @pre idx < size()
       NB: O( n ), E = O( n - idx )
    */
    void erase( unsigned int idx );

    /**
       @return an iterator pointing on the first element in the container.
    */
    Iterator begin();

    /**
       @return an iterator pointing after the last element in the container.
    */
    Iterator end();

    /**
       @return an iterator pointing on the first element in the container.
    */
    ConstIterator begin() const;

    /**
       @return an iterator pointing after the last element in the container.
    */
    ConstIterator end() const;

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:

    /**
       Stores the first block of values.
    */
    FirstBlock myFirstBlock;

    // ------------------------- Hidden services ------------------------------
  protected:

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class IndexedListWithBlocks


  /**
   * Overloads 'operator<<' for displaying objects of class 'IndexedListWithBlocks'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'IndexedListWithBlocks' to write.
   * @return the output stream after the writing.

   @tparam TValue the type for the values stored in the list.
   @tparam N the number of value stored in the first block.
   @tparam M the number of value stored in the further blocks.

   */
  template  <typename TValue, unsigned int N, unsigned int M>
  std::ostream&
  operator<< ( std::ostream & out, 
               const IndexedListWithBlocks<TValue, N, M> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/base/IndexedListWithBlocks.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined IndexedListWithBlocks_h

#undef IndexedListWithBlocks_RECURSES
#endif // else defined(IndexedListWithBlocks_RECURSES)
