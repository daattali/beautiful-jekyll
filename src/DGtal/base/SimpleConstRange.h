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
 * @file SimpleConstRange.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/02/06
 *
 *
 * Header file for module SimpleConstRange.h
 *
 * This file contains the definition of basic functors.
 *
 * This file is part of the DGtal library.
 */

#if defined(SimpleConstRange_RECURSES)
#error Recursive header files inclusion detected in SimpleConstRange.h
#else // defined(SimpleConstRange_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SimpleConstRange_RECURSES

#if !defined SimpleConstRange_h
/** Prevents repeated inclusion of headers. */
#define SimpleConstRange_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iterator>
#include <iostream>
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/base/Circulator.h"
#include "DGtal/base/ConstIteratorAdapter.h"
#include "boost/concept_check.hpp"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{


  ///////////////////////////////////////////////////////////////////////////////
  // class SimpleConstRange
  ///////////////////////////////////////////////////////////////////////////////

  /**
   * @brief Aim: model of CConstRange that adapts any range of elements
   * bounded by two iterators [itb, ite) and provides services to
   * (circularly)iterate over it (in a read-only manner).
   *
   * @tparam TConstIterator the type of the iterator to adapt
   * (at least bidirectional)
   *
   * @see ConstRangeAdapter
   */
  template <typename TConstIterator>
  class SimpleConstRange
  {

    BOOST_CONCEPT_ASSERT(( boost::BidirectionalIterator<TConstIterator> ));

    // ------------------------- inner types --------------------------------
  public:

    typedef TConstIterator ConstIterator;
    typedef std::reverse_iterator<ConstIterator> ConstReverseIterator;

    typedef Circulator<ConstIterator> ConstCirculator;
    typedef std::reverse_iterator<ConstCirculator> ConstReverseCirculator;

    // ------------------------- standard services --------------------------------

    /**
     * Standard constructor from two iterators
     * and one functor.
     * @param itb begin iterator.
     * @param ite end iterator.
     *
     */
    SimpleConstRange(const TConstIterator& itb, const TConstIterator& ite)
      : myBegin(itb), myEnd(ite) {}

    /**
     * Copy constructor.
     * @param other the iterator to clone.
     */
    SimpleConstRange( const SimpleConstRange & other )
      : myBegin(other.myBegin), myEnd(other.myEnd) {}

    /**
     * Assignment.
     * @param other the iterator to copy.
     * @return a reference on 'this'.
     */
    SimpleConstRange& operator= ( const SimpleConstRange & other )
    {
      if ( this != &other )
	{
	  myBegin = other.myBegin;
	  myEnd = other.myEnd;
	}
      return *this;
    }

    /**
     * Destructor. Does nothing.
     */
    ~SimpleConstRange() {}

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const { return true; }

    // ------------------------- display --------------------------------
    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const
    {
      typedef typename IteratorCirculatorTraits<ConstIterator>::Value Value;
      out << "[SimpleConstRange]" << std::endl;
      out << "\t";
      std::copy( myBegin, myEnd, std::ostream_iterator<Value>(out, ", ") );
      out << std::endl;
    }

    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const
    {
      return "SimpleConstRange";
    }


    // ------------------------- private data --------------------------------
  private:
    /**
     * Begin underlying iterator
     */
    TConstIterator myBegin;
    /**
     * End underlying iterator
     */
    TConstIterator myEnd;

    // ------------------------- iterator services --------------------------------
  public:

    /**
     * Iterator service.
     * @return begin iterator
     */
    ConstIterator begin() const {
      return ConstIterator( myBegin );
    }

    /**
     * Iterator service.
     * @return end iterator
     */
    ConstIterator end() const {
      return ConstIterator( myEnd );
    }

    /**
     * Iterator service.
     * @return rbegin iterator
     */
    ConstReverseIterator rbegin() const {
      return ConstReverseIterator(this->end());
    }

    /**
     * Iterator service.
     * @return rend iterator
     */
    ConstReverseIterator rend() const {
      return ConstReverseIterator(this->begin());
    }

    /**
     * Circulator service.
     * @return a circulator
     */
    ConstCirculator c() const {
      return ConstCirculator( this->begin(), this->begin(), this->end() );
    }

    /**
     * Circulator service.
     * @return a reverse circulator
     */
    ConstReverseCirculator rc() const {
      return ConstReverseCirculator( this->c() );
    }

  }; //end class SimpleConstRange

} // namespace DGtal

  ///////////////////////////////////////////////////////////////////////////////


#endif // !defined SimpleConstRange_h

#undef SimpleConstRange_RECURSES
#endif // else defined(SimpleConstRange_RECURSES)
