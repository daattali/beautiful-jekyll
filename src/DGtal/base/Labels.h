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
 * @file Labels.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/07/07
 *
 * Header file for module Labels.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Labels_RECURSES)
#error Recursive header files inclusion detected in Labels.h
#else // defined(Labels_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Labels_RECURSES

#if !defined Labels_h
/** Prevents repeated inclusion of headers. */
#define Labels_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CUnsignedNumber.h"
#include "DGtal/kernel/CIntegralNumber.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class Labels
  /**
     Description of template class 'Labels' <p>
     \brief Aim: Stores a set of labels in {O..L-1} as a sequence of bits. 

     This class is useful to stores a set of numbers as a
     characteristic set. It is very similar to a bitset, except it
     provides more functions, like giving the index of a label (i.e.,
     if (1, 5, 6, 13, 20) are the labels, then 1 has index 0, 5 has
     index 1, 6 has index 2, 13 has index 3, 20 has index 4.)

     @tparam L is the maximum number of labels.
     @tparam TWord the integer used to store the labels (if L >= log_2( digits( TWord ) ) then several consecutive words are stored.)

     @see bitset
   */
  template <unsigned int L, typename TWord = DGtal::uint8_t>
  class Labels
  {
    BOOST_STATIC_ASSERT(( L >= 1 ));
    BOOST_CONCEPT_ASSERT(( concepts::CUnsignedNumber<TWord> ));
    BOOST_CONCEPT_ASSERT(( concepts::CIntegralNumber<TWord> ));

  public:
    typedef TWord Word;
    typedef Labels<L, Word> Self;
    typedef unsigned int Label;
    typedef Label SizeType;

#define __DGTAL_WORD_NBDIGITS ( sizeof( Word ) * 8 )
#define __DGTAL_LABELS_NBWORDS ( (L-1) / __DGTAL_WORD_NBDIGITS + 1 )
#define __DGTAL_LABEL_WORD_INDEX( label ) ( label / __DGTAL_WORD_NBDIGITS )
#define __DGTAL_LABEL_DIGIT_INDEX( label ) ( label % __DGTAL_WORD_NBDIGITS )

  protected:

    /// Stores the labels as bits. The bit of index l is set if l is in the set.
    Word myLabels[ __DGTAL_LABELS_NBWORDS ];

    /// Returns the word in which is the label l.
    static SizeType _word( Label l );
    /// Returns the bit at which is the label l.
    static SizeType _digit( Label l );
    /// Returns the mask for the label l (1 << _digit( l )).
    static Word _mask( Label l );

  public:
    /**
       This class is used to enumerate the set values in the Labels container.
       A model of boost::ForwardIterator.
    */
    class ConstEnumerator {
    public:
      typedef ConstEnumerator Self;
      typedef Label Value;
      typedef const Value* Pointer;
      typedef const Value& Reference;
      typedef std::ptrdiff_t DifferenceType; ///< only positive offsets allowed.

      // ----------------------- std types ----------------------------------
      typedef Value value_type;
      typedef std::size_t size_type;
      typedef DifferenceType difference_type;
      typedef Pointer pointer;
      typedef Reference reference;
      typedef std::forward_iterator_tag iterator_category;

    private:
      const Word* myWordAddress;  ///< current address of word
      Label myWordLabel;///< index of first label of the current word.
      Label myLabel;    ///< current label
      Word myWord;      ///< current word (modified until 0).
      
    public:
      /**
	 Default destructor.
      */
      ~ConstEnumerator();

      /**
	 Default constructor (Invalid).
      */
      ConstEnumerator();

      /**
	 Constructor from word address. 
         @param address is some Labels.myLabels
         @param firstWord is 0 (begin) or __DGTAL_LABELS_NBWORDS (end)
      */
      ConstEnumerator( const Word* address, SizeType firstWord );

      /**
	 Copy constructor.
	 @param other the object to clone.
      */
      ConstEnumerator( const ConstEnumerator & other );

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

    typedef ConstEnumerator ConstIterator;
    typedef ConstIterator const_iterator;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~Labels();

    /**
     * Constructor.
     */
    Labels();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    Labels ( const Self & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    Self & operator= ( const Self & other );

    /**
       @param l any label in 0..L-1
       @return 'true' iff this label is set.
    */
    bool test( Label l ) const;

    // bitset<N>& set ( );
    // bitset<N>& reset ( );

    /**
       If val is true, inserts l in the set, otherwise removes it.
       @param l any label in 0..L-1
       @param val either true or false. 
       @return a reference on this.
    */
    Self& set ( Label l, bool val = true );

    /**
       Removes l from the set.
       @param l any label in 0..L-1
       @return a reference on this.
    */
    Self& reset( Label l );

    /**
       Flips l in or out of the set.
       @param l any label in 0..L-1
       @return a reference on this.
    */
    Self& flip( Label l );

    /**
       Clears the set.
       @return a reference on this.
    */
    Self& reset();

    /**
       @return the number of labels sets.
    */
    SizeType count() const;

    /**
       @return the total maximum possible number of labels sets,
       i.e. template parameter L.
    */
    static SizeType size();

    /**
       As output, labels[0] contains the label of index 0, labels[1]
       the label of index 1, and so on.

       @param labels (modified) the (ordered) labels set. 
    */
    void getLabels( std::vector<Label> & labels ) const;

    /**
       @param l any label in 0..L-1
       @return the index of the label l in this set, starting from 0. If the label is not set, returns L (ie. size()).
    */
    SizeType index( Label l ) const;

    /**
       @return an iterator pointing on the first valid label.
    */
    ConstIterator begin() const;

    /**
       @return an iterator pointing after the last valid label.
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

    // ------------------------- Hidden services ------------------------------
  protected:


    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Labels


  /**
   * Overloads 'operator<<' for displaying objects of class 'Labels'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Labels' to write.
   * @return the output stream after the writing.
   */
  template <unsigned int L, typename TWord>
  std::ostream&
  operator<< ( std::ostream & out, const Labels<L, TWord> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/base/Labels.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Labels_h

#undef Labels_RECURSES
#endif // else defined(Labels_RECURSES)
