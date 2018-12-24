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
 * @file LabelledMap.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/07/05
 *
 * Header file for module LabelledMap.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(LabelledMap_RECURSES)
#error Recursive header files inclusion detected in LabelledMap.h
#else // defined(LabelledMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define LabelledMap_RECURSES

#if !defined LabelledMap_h
/** Prevents repeated inclusion of headers. */
#define LabelledMap_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <cstring>
#include <cmath>
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/Labels.h"
//#include "DGtal/base/FakeKeyValuePair.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class LabelledMap
  /**
     Description of template class 'LabelledMap' <p> \brief Aim:
     Represents a map label -> data, where the label is an integer
     between 0 and a constant L-1. It is based on a binary coding of
     labels and a mixed list/array structure. The assumption is that
     the number of used labels is much less than L. The objective is
     to minimize the memory usage.

     Model of boost::AssociativeContainer,
     boost::PairAssociativeContainer,
     boost::UniqueAssociativeContainer. As such, it is refinement of
     boost::ForwardContainer and boost::Container.  It is also a model
     of boost::Assignable, boost::CopyConstructible.

     @verbatim
     V[ 0 ] is the data of the first set label.
     V[ 1 ] is the data of the second set label.
     ...

     if less than 4 datas and N = 3
     +------+------+------+------+------+
     |labels| V[0] | V[1] | ...  |  0   |
     +------+------+------+------+------+

     if only 4 datas and N = 3
     +------+------+------+------+------+
     |labels| V[0] | V[1] | V[2] | V[3] |
     +------+------+------+------+------+

     if more than 4 datas and N = 3, M = 4
     +------+------+------+------+------+        +------+------+------+------+------+
     |labels| V[0] | V[1] | V[2] | ptr --------> | V[3] | V[4] | V[5] | V[6] | ptr --------> ...
     +------+------+------+------+------+        +------+------+------+------+------+

     @endverbatim

     This structure is related to the IndexedListWithBlocks, except
     that it stores the mapping label -> index. The (maximum) number
     of possible labels is fixed at instantiation for optimisation
     purposes.

     Such a structure is useful when:
     - the expected size of this container is small, but may sometimes increase.
     - the user wishes sometimes to insert a new data or erase another data.
     - the user wishes to have an access to the datas that is as fast as possible given a valid label.
     - one wishes to limit as possible the memory usage.
     - generally this structure is embedded as the data of a big array.

     Model of boost::PairAssociativeContainer and
     boost::SimpleAssociativeContainer.

     @tparam TData the type for the datas stored in the list.
     @tparam L the maximum number of labels.
     @tparam TWord the integer used to store the labels (if L >= log_2( digits( TWord ) ) then several consecutive words are stored.), e.g. DGtal::uint8_t.
     @tparam N the number of data stored in the first block.
     @tparam M the number of data stored in the further blocks.

     NB: In the following, we use the notations
     - n is the size of the container
     - b is the number of blocks ( b = 1 + (size()-N) / M ).
  */
  template <typename TData, unsigned int L, typename TWord,
            unsigned int N, unsigned int M>
  class LabelledMap
  {
    BOOST_STATIC_ASSERT( L >= 1 );
    BOOST_STATIC_ASSERT( N >= 0 );
    BOOST_STATIC_ASSERT( M >= 2 );
  public:
    // ----------------------- Public types ------------------------------
    typedef LabelledMap<TData, L, TWord, N, M> Self;
    typedef TData Data;
    typedef TWord Word;
    typedef Labels<L, Word> LabelsType;
    typedef typename LabelsType::Label Label;
    typedef Label Key;
    typedef std::pair<const Key, Data> Value;
    //typedef FakeKeyValuePair<Key, Data> Value;

    typedef typename LabelsType::ConstIterator LabelsConstIterator;
    typedef std::ptrdiff_t DifferenceType;
    typedef std::size_t SizeType;
    typedef Value& Reference;
    typedef Value* Pointer;
    typedef const Value& ConstReference;
    typedef const Value* ConstPointer;

    //class Iterator;      ///< Forward declaration
    class ConstIterator; ///< Forward declaration
    class KeyCompare;    ///< Forward declaration
    class ValueCompare;  ///< Forward declaration
    // ----------------------- Standard types ------------------------------
    typedef Key key_type;
    typedef Value value_type;
    typedef Data data_type;
    typedef Data mapped_type;
    typedef DifferenceType difference_type;
    typedef Reference reference;
    typedef Pointer pointer;
    typedef ConstReference const_reference;
    typedef ConstPointer const_pointer;
    typedef SizeType size_type;
    typedef ConstIterator iterator;
    typedef ConstIterator const_iterator;
    typedef KeyCompare key_compare;
    typedef ValueCompare value_compare;

    struct __FirstBlock; ///< Forward declaration
    struct __AnyBlock; ///< Forward declaration

    union BlockPointer {
      __FirstBlock* first;
      __AnyBlock* any;
    };

    /// Used in first block to finish it or to point to the next block.
    union DataOrBlockPointer {
      Data lastData; // used when at the end of the list
      __AnyBlock* nextBlock;  // used otherwise
    };

    /// Represents the first block in the container.
    /// Internal structure.
    struct __FirstBlock {
      inline
      __FirstBlock() 
      { data.nextBlock = 0; }

      inline
      Data & insert( unsigned int idx, unsigned int size, const Data & v )
      {
        ASSERT( idx <= size );
	if ( size < N )
	  {
	    std::copy_backward( datas + idx, datas + size, datas + size + 1 );
	    return ( datas[ idx ] = v );
	  }
	else if ( size == N )
	  {
            if ( idx < N )
              {
                data.lastData = datas[ N - 1 ];
                std::copy_backward( datas + idx, datas + N - 1, datas + N );
                return ( datas[ idx ] = v );
              }
            else // idx == N
              {
                return ( data.lastData = v );
              }
	  }
	else if ( size == (N+1) )
	  {
	    // This cannot be tested.
	    // ASSERT( data.nextBlock == 0 );
	    __AnyBlock* next = new __AnyBlock;
	    if ( idx < N )
	      {
		next->datas[ 0 ] = datas[ N - 1 ];
		next->datas[ 1 ] = data.lastData;
		std::copy_backward( datas + idx, datas + N - 1, datas + N );
                data.nextBlock = next;
		return ( datas[ idx ] = v );
	      }
	    else if ( idx == N )
	      {
		next->datas[ 1 ] = data.lastData;
                data.nextBlock = next;
		return ( next->datas[ 0 ] = v );
	      }
	    else //if ( idx > N )
	      {
		next->datas[ 0 ] = data.lastData;
                data.nextBlock = next;
                return ( next->datas[ 1 ] = v );
	      }
	  }
	else // size > N + 1
	  {
	    if ( idx < N )
	      {
		Data v1 = datas[ N - 1 ];
		std::copy_backward( datas + idx, datas + N - 1, datas + N );
		data.nextBlock->insert( 0, size - N, v1 );
		return ( datas[ idx ] = v );
	      }
	    else
	      return data.nextBlock->insert( idx - N, size - N, v );
	  }
      }

      inline 
      void erase( unsigned int idx, unsigned int size )
      {
	// std::cerr << "__FirstBlock::erase(" << idx << ")"
	// 	  << " this=" << this
	// 	  << " next=" << data.nextBlock
	// 	  << std::endl;
	ASSERT( idx < size );
	if ( size <= ( N + 1 ) )
	  {
	    // works also in the case we use 'data' to store a N+1-th data.
	    std::copy( datas + idx + 1, datas + size, datas + idx );
            data.nextBlock = 0;
	  }
	else if ( size == N + 2 )
	  { 
	    if ( idx < N )
	      {
		std::copy( datas + idx + 1, datas + N, datas + idx );
		datas[ N - 1 ] = data.nextBlock->datas[ 0 ];
                Data tmp = data.nextBlock->datas[ 1 ];
		delete data.nextBlock;
                data.lastData = tmp;
	      }
	    else if ( idx == N )
              {
                Data tmp = data.nextBlock->datas[ 1 ];
		delete data.nextBlock;
                data.lastData = tmp;
              }
            else // idx == N + 1
              {
                Data tmp = data.nextBlock->datas[ 0 ];
		delete data.nextBlock;
                data.lastData = tmp;
              }
	  }
	else // size > N + 2
	  {
	    if ( idx < N )
	      {
		std::copy( datas + idx + 1, datas + N, datas + idx );
		datas[ N - 1 ] = data.nextBlock->datas[ 0 ];
		data.nextBlock = data.nextBlock->erase( 0, size - N );
	      }
	    else
	      data.nextBlock = data.nextBlock->erase( idx - N, size - N );
	  }
      }

      Data datas[ N ];
      DataOrBlockPointer data;
    };

    /// Represents a block (except the first) in the container.
    /// Internal structure.
    struct __AnyBlock {
      inline __AnyBlock() : next( 0 ) {}

      inline
      Data & insert( unsigned int idx, unsigned int size, const Data & v )
      {
        ASSERT( idx <= size );
	if ( idx >= M ) 
	  {
	    if ( next == 0 )
	      {
		ASSERT( size == M );
		ASSERT( idx == M );
		next = new __AnyBlock;
                return ( next->datas[ 0 ] = v );
	      }
            else
              {
		ASSERT( size > M );
                return next->insert( idx - M, size - M, v );
              }
	  }
	else 
	  { // idx < M
            if ( size <= ( M - 1) ) // ( size < ( M - 1) )
              {
                ASSERT( next == 0 );
                std::copy_backward( datas + idx, datas + size, 
                                    datas + size + 1 );
                return ( datas[ idx ] = v );
              }
            else
              {
                Data v1 = datas[ M - 1 ];
                std::copy_backward( datas + idx, datas + M - 1, datas + M );
                // if ( size >= M )
                //   {
                if ( next == 0 )
                  {
                    ASSERT( size == M );
                    next = new __AnyBlock;
                    next->datas[ 0 ] = v1;
                  }
                else
                  {
                    ASSERT( size > M );
                    next->insert( 0, size - M, v1 );
                  }
                // }
                return ( datas[ idx ] = v );
              }
	  }
      }

      inline 
      __AnyBlock* erase( unsigned int idx, unsigned int size )
      {
	// std::cerr << "__AnyBlock::erase(" << idx << "," << size << ")" 
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
	    std::copy( datas + idx + 1, datas + M, datas + idx );
	    if ( next != 0 )
	      {
		ASSERT( size > M );
		datas[ M - 1 ] = next->datas[ 0 ];
                next = next->erase( 0, size - M );
	      }
	  }
	else
	  next = next->erase( idx - M, size - M );
	return this;
      }


      Data datas[ M ];
      __AnyBlock* next;
    };

    /**
       Pseudo-random iterator to visit LabelledMap (it is
       only a random forward iterator).  Model of
       boost::ForwardIterator. Provides also + and += arithmetic.
    */
    class BlockIterator {
    public:
      typedef BlockIterator Self;
      typedef TData Value;
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
      unsigned int myIdx;      ///< current index in \a myDatas of the iterator
      unsigned int myNbDatas; ///< number of valid datas in array \a myDatas
      Data* myDatas;         ///< array of \a myNbDatas datas.
      __AnyBlock* myNext;        ///< pointer to next block or 0 if last block.

      friend class LabelledMap;

    protected:
      /**
	 Constructor from first block and index. Used by class LabelledMap.
      */
      BlockIterator( __FirstBlock & block, unsigned int idx, unsigned int size );
      
    public:
      /**
	 Default destructor.
      */
      ~BlockIterator();

      /**
	 Default constructor.
      */
      BlockIterator();

      /**
	 Copy constructor.
	 @param other the object to clone.
      */
      BlockIterator( const BlockIterator & other );

      /**
       * Assignment.
       * @param other the object to copy.
       * @return a reference on 'this'.
       */
      Self & operator= ( const Self & other );
      
      /**
	 Dereference operator.
	 @return the current data of the iterator, if valid.
      */
      Reference operator*() const;
     
      /**
	 Pointer dereference operator.
	 @return a non-mutable pointer on the current data.
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
       Pseudo-random iterator to visit LabelledMap (it is
       only a random forward iterator).  Model of
       boost::ForwardIterator. Provides also + and += arithmetic.
    */
    class BlockConstIterator {
    public:
      typedef BlockConstIterator Self;
      typedef TData Value;
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
      unsigned int myIdx;      ///< current index in \a myDatas of the iterator
      unsigned int myNbDatas; ///< number of valid datas in array \a myDatas
      const Data* myDatas;   ///< array of \a myNbDatas datas.
      const __AnyBlock* myNext;  ///< pointer to next block or 0 if last block.

      friend class LabelledMap;

    protected:
      /**
	 Constructor from first block and index.
         Used by class LabelledMap.
      */
      BlockConstIterator( const __FirstBlock & block, unsigned int idx, unsigned int size );
      
    public:
      /**
	 Default destructor.
      */
      ~BlockConstIterator();

      /**
	 Default constructor.
      */
      BlockConstIterator();

      /**
	 Copy constructor.
	 @param other the object to clone.
      */
      BlockConstIterator( const BlockConstIterator & other );

      /**
       * Assignment.
       * @param other the object to copy.
       * @return a reference on 'this'.
       */
      Self & operator= ( const Self & other );
      
      /**
	 Dereference operator.
	 @return the current data of the iterator, if valid.
      */
      Reference operator*() const;
     
      /**
	 Pointer dereference operator.
	 @return a non-mutable pointer on the current data.
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

    // ----------------------- Iterator services ------------------------------
  public:

    /**
       This class allows to visit all stored pairs (key,value).
    */
    class ConstIterator {
    public:
      friend class LabelledMap;
      typedef ConstIterator Self;
      // The following line is removed so that gcc-4.2 and gcc-4.6 compiles. 
      //typedef typename LabelledMap<TData, L, TWord, N, M>::Value Value;
      typedef const Value* Pointer;
      /// Note the trick here. The reference is a rvalue. Works only for const iterator.
      typedef Value Reference;
      typedef std::ptrdiff_t DifferenceType;

      // ----------------------- std types ----------------------------------
      typedef Value value_type;
      typedef std::size_t size_type;
      typedef DifferenceType difference_type;
      typedef Pointer pointer;
      typedef Reference reference;
      // typedef Reference const_reference;
      typedef std::forward_iterator_tag iterator_category;

    private:
      /// ConstIterator to visit keys.
      LabelsConstIterator myLabelsIt; 
      /// ConstIterator to visit datas.
      BlockConstIterator myBlockIt;

    protected:
      /**
	 Constructor. Internal. Used by LabelledMap.
      */
      ConstIterator( LabelsConstIterator lIt, BlockConstIterator bIt );

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
	 @return the current data of the iterator, if valid.
      */
      Reference operator*() const;
     
      /**
	 Pointer dereference operator.
         \b Warning: Not thread-safe !! Use operator* instead.
	 @return a non-mutable pointer on the current data.
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


      Data & _data() const;
      const Data & _const_data() const;
    };
    
    /// non-mutable class via iterators.
    typedef ConstIterator Iterator;
    /// Key comparator class. Always natural ordering.
    class KeyCompare {
    public:
      inline KeyCompare() {}
      inline bool operator()( Key k1, Key k2 ) const
      {
        return k1 < k2;
      }
    };
    /// Value comparator class. Always natural ordering between keys.
    class ValueCompare {
    public:
      inline ValueCompare() {}
      inline bool operator()( const Value & v1, const Value & v2 ) const
      {
        return v1.first < v2.first;
      }
    };

    
    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor.
     */
    LabelledMap();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    LabelledMap ( const LabelledMap & other );

    /**
       Constructor from range.
       
       @tparam InputIterator model of boost::InputIterator whose
       value type is convertible to Value.
       
       @param first an iterator on the first value of the range.
       @param last an iterator after the last value of the range.
    */
    template <typename InputIterator>
    LabelledMap( InputIterator first, InputIterator last );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    LabelledMap & operator= ( const LabelledMap & other );

    /**
     * Destructor.
     */
    ~LabelledMap();

    // ----------------------- Container services -----------------------------
  public:

    /**
       @return a reference to the labels.
    */
    const LabelsType & labels() const;

    /**
       The number of datas stored in the structure. O(1) complexity.
     */
    SizeType size() const;

    /**
       @return 'true' if and only if the container is empty. O(1)
     */
    bool empty() const;

    /**
       The maximum number of datas storable in the structure.
     */
    SizeType max_size() const;

    /**
       The number of datas currently allocated in the structure.
     */
    SizeType capacity() const;

    /**
       @return a comparator object for two keys. Corresponds to k1 < k2.
    */
    KeyCompare key_comp() const;

    /**
       @return a comparator object for two values. Corresponds to v1.first < v2.first.
    */
    ValueCompare value_comp() const;

    /**
       Swap content. Exchanges the content of the container with the
       content of mp, which is another map object containing elements
       of the same type. Sizes may differ.

       After the call to this member function, the elements in this
       container are those which were in mp before the call, and the
       elements of mp are those which were in this. 

       NB: not exactly standard ! The iterators pointing on the first
       block change roles ! The other references and pointers remain
       valid for the swapped objects.
    */
    void swap( Self & other );

    /**
       Removes all the datas stored in the structure. 
     */
    void clear();

    /**
       Follows std::count. 

       @param key any label
       @return 0 if the key is not present in container, 1 otherwise.
    */
    SizeType count( const Key & key ) const;

    /**
       Follows std::operator[]. Given a key \a key, returns a
       reference to the associated data.

       @param key any label
       @return a reference to the associated data.
    */
    Data & operator[]( const Key & key );

    /**
       Read-only version. Follows std::operator[]. Given a key \a key,
       returns a reference to the associated data.

       @param key any label
       @return a const reference to the associated data.
    */
    const Data & operator[]( const Key & key ) const;

    /**
       A read-write accessor to the data associated to an \b existing key.

       @param key any label (such that count(key)==1)
       @return a reference to the associated data.
    */
    Data & fastAt( const Key & key );

    /**
       A read-only accessor to the data associated to an \b existing key.

       @param key any label (such that count(key)==1)
       @return a const reference to the associated data.
    */
    const Data & fastAt( const Key & key ) const;

    /**
       Insertion of a new data at given label. Follows std::insert
       return a pair<iterator,bool>).  Note that the data is
       associated to key only if key was not present in the container.

       @param val a pair<key,data>. 

       @return a pair <iterator,bool> where iterator points on the
       pair (key,data) while the boolean is true if a new element was
       indeed created. 

       NB: This method is provided to follow the
       std::AssociativeContainer concept. You are discourage to use
       this functions since the correct iterator must be recomputed at
       each insert. Prefer operator[] or fastAt.
    */
    std::pair<Iterator, bool> insert( const Value & val );

    /**
       Inserts the pair \a val (key,data) in the container, where position is a hint

       @param position an iterator used as a hint to find the good
       place. Unused here.
       @param val a pair (key,data)
       @return an iterator on the inserted element.

       NB: This method is provided to follow the
       std::AssociativeContainer concept. You are discourage to use
       this functions since the correct iterator must be recomputed at
       each insert. Prefer operator[] or fastAt.
    */
    Iterator insert( Iterator position, const Value & val );

    /**
       Insertion from range. Insert all values in the range. Be
       careful that if a value in the container has the same key as a
       value in the range, then the mapped data is not changed.
       
       @tparam InputIterator model of boost::InputIterator whose
       value type is convertible to Value.
       
       @param first an iterator on the first value of the range.
       @param last an iterator after the last value of the range.
    */
    template <typename InputIterator>
    void insert( InputIterator first, InputIterator last );

    /**
       Erases the pair (key,data) pointed by \a iterator.

       @param position any valid iterator in the container.
    */
    void erase( Iterator position );

    /**
       Erases the element of key \a key.
       
       @param key any key (in 0..L-1)
       @return the number of elements deleted (0 or 1).
    */
    SizeType erase( Key key );

    /**
       Erases the elements in the range [first,last).

       @param first a valid iterator.
       @param last a valid iterator.

       NB: to clear the container, prefer clear() instead of erase( begin(), end() ).
       @see clear
    */
    void erase( Iterator first, Iterator last );

    /// @return an iterator pointing on the first element in the container.
    ConstIterator begin() const;

    /// @return an iterator pointing after the last element in the container.
    ConstIterator end() const;

    /// @return an iterator pointing on the first element in the container.
    Iterator begin();

    /// @return an iterator pointing after the last element in the container.
    Iterator end();

    /**
       Get range of equal elements.

       Returns the bounds of a range that includes all the elements in
       the container with a key that compares equal to x. Here, the range will
       include one element at most.

       If x does not match any key in the container, the range
       returned has a length of zero, with both iterators pointing to
       the element with nearest key greater than x, if any, or to
       map::end if x is greater than all the elements in the
       container.

       @param x any key in 0..L-1

       @return a pair, where its member pair::first is an iterator to
       the lower bound of the range with the same value as the one
       that would be returned by lower_bound(x), and pair::second is
       an iterator to the upper bound of the range with the same value
       as the one that would be returned by upper_bound(x).
     */
    std::pair<Iterator, Iterator> equal_range( const Key & x );

    /**
       Get range of equal elements.
       
       Returns the bounds of a range that includes all the elements in
       the container with a key that compares equal to x. Here, the range will
       include one element at most.

       If x does not match any key in the container, the range
       returned has a length of zero, with both iterators pointing to
       the element with nearest key greater than x, if any, or to
       map::end if x is greater than all the elements in the
       container.

       @param x any key in 0..L-1

       @return a pair, where its member pair::first is an iterator to
       the lower bound of the range with the same value as the one
       that would be returned by lower_bound(x), and pair::second is
       an iterator to the upper bound of the range with the same value
       as the one that would be returned by upper_bound(x).
     */
    std::pair<ConstIterator, ConstIterator> equal_range( const Key & x ) const;

    /**
       Get iterator to element.

       Searches the container for an element with \a x as key and
       returns an iterator to it if found, otherwise it returns an
       iterator to end() (the element past the end of the container).

       NB: Another member function, count(), can be used to just check
       whether a particular key exists. 'count( x ) == 1' is faster
       than 'find( x ) != end()'.

       @param x Key to be searched for (in 0..L-1)

       @return An iterator to the element, if the specified key value
       is found, end() if the specified key is not found in the
       container.
    */
    Iterator find ( const Key & x );

    /**
       Get iterator to element.

       Searches the container for an element with \a x as key and
       returns an iterator to it if found, otherwise it returns an
       iterator to end() (the element past the end of the container).

       NB: Another member function, count(), can be used to just check
       whether a particular key exists. 'count( x ) == 1' is faster
       than 'find( x ) != end()'.

       @param x Key to be searched for (in 0..L-1)

       @return An iterator to the element, if the specified key value
       is found, end() if the specified key is not found in the
       container.
    */
    ConstIterator find ( const Key & x ) const;

    /**
       Return iterator to lower bound.

       Returns an iterator pointing to the first element in the
       container whose key does not compare less than \a x (using the
       container's comparison object), i.e. it is either equal or
       greater.

       Unlike upper_bound(), this member function returns an iterator
       to the element also if it compares equal to \a x and not only
       if it compares greater.

       Notice that, internally, all the elements in this container are
       always ordered by their keys, therefore all the elements that
       follow the one returned by this function will have a key that
       compares greater than x.

       @param x Key to be searched for (in 0..L-1)

       @return an iterator to the the first element in the container
       whose key does not compare less than \a x.
    */
    Iterator lower_bound( const Key & x );

    /**
       Return iterator to lower bound.

       Returns an iterator pointing to the first element in the
       container whose key does not compare less than \a x, i.e. it is
       either equal or greater.

       Unlike upper_bound(), this member function returns an iterator
       to the element also if it compares equal to \a x and not only
       if it compares greater.

       Notice that, internally, all the elements in this container are
       always ordered by their keys, therefore all the elements that
       follow the one returned by this function will have a key that
       compares greater than x.

       @param x Key to be searched for (in 0..L-1)

       @return an iterator to the the first element in the container
       whose key does not compare less than \a x.
    */
    ConstIterator lower_bound ( const Key & x ) const;

    /**
       Return iterator to upper bound.

       Returns an iterator pointing to the first element in the
       container whose key compares greater than \a x. (>x)

       Unlike lower_bound(), this member function does not return an
       iterator to the element if its key compares equal to \a x, but
       only if it compares strictly greater.

       Notice that, internally, all the elements in this container are
       always ordered by their keys, therefore all the elements that
       follow the one returned by this function will have a key that
       compares greater than x.

       @param x Key to be searched for (in 0..L-1)

       @return an iterator to the the first element in the container
       whose key compares greater than \a x.
    */
    Iterator upper_bound ( const Key & x );

    /**
       Return iterator to upper bound.

       Returns an iterator pointing to the first element in the
       container whose key compares greater than \a x. (>x)

       Unlike lower_bound(), this member function does not return an
       iterator to the element if its key compares equal to \a x, but
       only if it compares strictly greater.

       Notice that, internally, all the elements in this container are
       always ordered by their keys, therefore all the elements that
       follow the one returned by this function will have a key that
       compares greater than x.

       @param x Key to be searched for (in 0..L-1)

       @return an iterator to the the first element in the container
       whose key compares greater than \a x.
    */
    ConstIterator upper_bound ( const Key & x ) const;


    /**
       Removes all the datas stored in the block structure. 
       @param size must be the current size of the block structure.
     */
    void blockClear( unsigned int size );

    /**
       Random unprotected read-write access to data at position \a idx
       @param idx the index of the data in the container.
       @return a reference on the data.
       @pre idx < size()
       NB: O( b ), E = O( 1 + ceil( ( idx - N ) / M ) )
    */
    Data & blockAt( unsigned int idx );

    /**
       Random unprotected read access to data at position \a idx
       @param idx the index of the data in the container.
       @return a const reference on the data.
       @pre idx < size()
       NB: O( b ), E = O( 1 + ceil( ( idx - N ) / M ) )
    */
    const Data & blockAt( unsigned int idx ) const;

    /**
       Insertion of a new data at given position. The former data at
       this position and the next ones are shifted.

       @param idx the index of the data in the container.
       @pre idx <= size() (if size(), inserts at the end.
       @param block_size the block size.
       @param data the data to insert.
       NB: O( n ), E = O( n - idx )
    */
    Data & blockInsert( unsigned int idx, unsigned int block_size, const Data & data );

    /**
       Removal of a data at a given position. Following datas are shifted.

       @param idx the index of the data in the container.
       @pre idx < size()
       NB: O( n ), E = O( n - idx )
    */
    void blockErase( unsigned int idx );


    /// @return an iterator pointing on the first element in the container.
    BlockIterator blockBegin();

    /// @return an iterator pointing after the last element in the container.
    BlockIterator blockEnd();

    /// @return an iterator pointing on the first element in the container.
    BlockConstIterator blockBegin() const;

    /// @return an iterator pointing after the last element in the container.
    BlockConstIterator blockEnd() const;

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

    /// Stores the labels for this sequence of datas.
    LabelsType myLabels;

    /**
       Stores the first block of datas.
    */
    __FirstBlock myFirstBlock;

    // ------------------------- Hidden services ------------------------------
  protected:

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class LabelledMap


  /**
   * Overloads 'operator<<' for displaying objects of class 'LabelledMap'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'LabelledMap' to write.
   * @return the output stream after the writing.

   @tparam TData the type for the datas stored in the list.
   @tparam N the number of data stored in the first block.
   @tparam M the number of data stored in the further blocks.

   */
  template  <typename TData, unsigned int L, typename TWord,
             unsigned int N, unsigned int M>
  std::ostream&
  operator<< ( std::ostream & out, 
               const LabelledMap<TData, L, TWord, N, M> & object );

  namespace detail {

    /**
       Functor used to compute the best parameters for minimizing the
       memory usage of a LabelledMap structure.
    */
    struct LabelledMapMemFunctor 
    { 
      double _p; double _q;
      unsigned int _sL;
      unsigned int _sV;      
      unsigned int _sP;
      unsigned int _sA;
      LabelledMapMemFunctor( double p, double q,
                             unsigned int sL, unsigned int sV,
                             unsigned int sP, unsigned int sA )
        : _p( p ), _q( q ), _sL( sL ), _sV( sV ), _sP( sP ), _sA( sA )
      {}
      
      inline
      double fctNM( unsigned int N, unsigned int M ) const
      {
        double alpha0 = _sL + _sV * ( N+1 );
        double beta0 = _sV * M + _sA + _sP;
        return alpha0 
          + beta0 * _q * pow(1.0 - _p, (double)N+1) 
          * ( 1.0 + pow(1.0 - _p, (double)M-1 ) 
              / ( 1.0 - pow(1.0 - _p, (double)M ) ) );
      }
      inline
      double fctNMpq( unsigned int N, unsigned int M, double p, double q ) const
      {
        double alpha0 = _sL + _sV * ( N+1 );
        double beta0 = _sV * M + _sA + _sP;
        return alpha0 
          + beta0 * q * pow(1.0 - p, (double)N+1) 
          * ( 1.0 + pow(1.0 - p, (double)M-1 ) 
              / ( 1.0 - pow(1.0 - p, (double)M ) ) );
      }

    };

    /**
       Tries to find the best values N and M which will minimized the
       memory usage of a LabelledMap, for the distribution specified by
       the parameters.
     
       @tparam TData the type of data that will be stored.

       @param L the total number of labels.

       @param prob_no_data Probability that there is no data at this location.
     
       @param prob_one_data If there is a possibility to have a data,
       this probability is used to define a geometric distribution that
       defines the number of data (ie valid labels) at this place. The
       smaller, the higher is the expectation. 0.5 means E(X) = 1.
     
       @return the pair (N,M) that minimizes the memory usage of a
       LabelledMap for the given distribution.
    */
    template <typename TData>
    std::pair< unsigned int, unsigned int >
    argminLabelledMapMemoryUsageForGeometricDistribution
    ( unsigned int L, double prob_no_data, double prob_one_data );
  }

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/base/LabelledMap.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined LabelledMap_h

#undef LabelledMap_RECURSES
#endif // else defined(LabelledMap_RECURSES)
