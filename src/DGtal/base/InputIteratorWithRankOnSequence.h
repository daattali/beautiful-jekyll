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
 * @file InputIteratorWithRankOnSequence.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/04/02
 *
 * Header file for module InputIteratorWithRankOnSequence.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(InputIteratorWithRankOnSequence_RECURSES)
#error Recursive header files inclusion detected in InputIteratorWithRankOnSequence.h
#else // defined(InputIteratorWithRankOnSequence_RECURSES)
/** Prevents recursive inclusion of headers. */
#define InputIteratorWithRankOnSequence_RECURSES

#if !defined InputIteratorWithRankOnSequence_h
/** Prevents repeated inclusion of headers. */
#define InputIteratorWithRankOnSequence_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <iterator>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/kernel/CInteger.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class InputIteratorWithRankOnSequence
  /**
     Description of template class 'InputIteratorWithRankOnSequence' <p>
     
     \brief Aim: Useful to create an iterator that returns a pair
     (value,rank) when visiting a sequence. The sequence is smartly
     copied within the iterator. Hence, the given sequence need not to
     persist during the visit. Since it is only an input sequence, it
     is not necessary to give a valid sequence when creating the end()
     iterator. 

     It is used by SternBrocot::Fraction, LightSternBrocot::Fraction,
     LighterSternBrocot::Fraction to visit the quotients of the
     continued fraction.

     It is a model of boost::InputIterator.

     @note It is not exactly an adapter since it requires the sequence
     itself. In fact, it could be decomposed into an adapter (which
     creates a pair) and a proxy on sequence.

     @tparam TSequence the type of sequence (a model of Sequence).
     @tparam TRank the type of the rank (a model of CInteger).
   */
  template <typename TSequence, typename TRank = typename TSequence::difference_type>
  class InputIteratorWithRankOnSequence
  {
    // ----------------------- public types ------------------------------
  public:
    BOOST_CONCEPT_ASSERT(( boost::Sequence<TSequence> ));
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<TRank> ));

    typedef TSequence Sequence;
    typedef TRank Rank;
    typedef InputIteratorWithRankOnSequence<Sequence,Rank> Self;
    typedef typename Sequence::value_type SequenceValue;
    typedef std::pair<SequenceValue,Rank> Value;
    typedef typename Sequence::const_iterator ConstIterator;
    typedef Value* Pointer;

    // ----------------------- std types ----------------------------------
    typedef Value value_type;
    typedef typename Sequence::size_type size_type;
    typedef typename Sequence::difference_type difference_type;
    typedef Pointer pointer;
    typedef value_type& reference;
    typedef reference const_reference;
    typedef std::input_iterator_tag iterator_category;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~InputIteratorWithRankOnSequence();

    /**
       Constructor.
       @param seq any sequence.
       @param it any iterator in the sequence \e seq.
     */
    InputIteratorWithRankOnSequence( const Sequence & seq, ConstIterator it );

    /**
       Constructor.
       @param ptrSeq any dynamically allocated pointer on a sequence (acquired).
       @param it any iterator in the sequence \e ptrSeq.
     */
    InputIteratorWithRankOnSequence( Sequence* ptrSeq, ConstIterator it );

    /**
       Constructor.
       @param ptrSeq any smart pointer on a sequence (CountedPtr or CowPtr).
       @param it any iterator in the sequence \e ptrSeq.
     */
    InputIteratorWithRankOnSequence( const CountedPtr<Sequence> & ptrSeq, ConstIterator it );

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    InputIteratorWithRankOnSequence ( const Self & other );

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
    Value operator*() const;

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

    /// A smart pointer to the visited sequence.
    CountedPtr<Sequence> mySequence;
    /// The current iterator position on the sequence.
    ConstIterator myIterator;
    /// Hack to store a value when using operator->. This value is not copied
    /// nor initialized.
    Value myTmpValue;

    // ------------------------- Hidden services ------------------------------
  protected:
    /**
     * Constructor.
     */
    InputIteratorWithRankOnSequence();

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class InputIteratorWithRankOnSequence


  /**
   * Overloads 'operator<<' for displaying objects of class 'InputIteratorWithRankOnSequence'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'InputIteratorWithRankOnSequence' to write.
   * @return the output stream after the writing.
   */
  template <typename TSequence, typename TRank>
  std::ostream&
  operator<< ( std::ostream & out, const InputIteratorWithRankOnSequence<TSequence, TRank> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/base/InputIteratorWithRankOnSequence.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined InputIteratorWithRankOnSequence_h

#undef InputIteratorWithRankOnSequence_RECURSES
#endif // else defined(InputIteratorWithRankOnSequence_RECURSES)
