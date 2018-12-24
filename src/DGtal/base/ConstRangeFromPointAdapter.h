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
 * @file ConstRangeFromPointAdapter.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/02/06
 *
 *
 * @brief Header file for module ConstRangeFromPointAdapter.h
 *
 * This file contains an adapter for 
 * bidirectional ranges, which can be defined from points.
 *
 * This file is part of the DGtal library.
 */

#if defined(ConstRangeFromPointAdapter_RECURSES)
#error Recursive header files inclusion detected in ConstRangeFromPointAdapter.h
#else // defined(ConstRangeFromPointAdapter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ConstRangeFromPointAdapter_RECURSES

#if !defined ConstRangeFromPointAdapter_h
/** Prevents repeated inclusion of headers. */
#define ConstRangeFromPointAdapter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/base/ConstAlias.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/base/Circulator.h"
#include "DGtal/base/CConstBidirectionalRangeFromPoint.h"
#include "DGtal/base/ConstIteratorAdapter.h"
#include "boost/concept_check.hpp"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal 
{


  ///////////////////////////////////////////////////////////////////////////////
  // class ConstRangeFromPointAdapter
  ///////////////////////////////////////////////////////////////////////////////

  /**
   * @brief Aim: model of CConstBidirectionalRangeFromPoint 
   * that adapts any bidirectional range and provides services to 
   * iterate over it (in a read-only manner). 
   *
   * @tparam TRange a model of CConstBidirectionalRangeFromPoint
   *
   * Moreover, the provided iterators are adapted 
   * with a functor f given at construction so that 
   * operator* calls f(\*it), instead of calling directly 
   * operator* of the iterator it.
   *
   * @tparam TFunctor the type of functor that transforms
   * the pointed element into another one
   *
   * @tparam TReturnType the type of the element returned by the underlying functor. 
   *
   * NB: the underlying range and functor are stored as aliasing pointers
   * in order to avoid copies. As a consequence the pointed object must exist 
   * and must not be deleted during the use of any instance of this class.
   *
   * @see ConstIteratorAdapter BasicFunctors.h
   */
  template <typename TRange, typename TFunctor, typename TReturnType>
  class ConstRangeFromPointAdapter
  {

    BOOST_CONCEPT_ASSERT(( CConstBidirectionalRangeFromPoint<TRange> )); 

    // ------------------------- inner types --------------------------------
  public: 

    typedef typename TRange::Point Point;   
    typedef ConstIteratorAdapter<typename TRange::ConstIterator,TFunctor,TReturnType> ConstIterator; 
    typedef std::reverse_iterator<ConstIterator> ConstReverseIterator;

    // ------------------------- standard services --------------------------------

    /**
     * Standard constructor from one range and one functor.
     * @param aRange the range to adapt.
     * @param aFunctor functor used to adapt on-the-fly the elements of the range
     *
     */
    ConstRangeFromPointAdapter( ConstAlias<TRange> aRange, 
		      ConstAlias<TFunctor> aFunctor )
      : myRangePtr(&aRange), myFunctorPtr(&aFunctor) {}

    /**
     * Copy constructor.
     * @param other the iterator to clone.
     */
    ConstRangeFromPointAdapter( const ConstRangeFromPointAdapter & other )
      : myRangePtr(other.myRangePtr), myFunctorPtr(other.myFunctorPtr) {}
  
    /**
     * Assignment.
     * @param other the iterator to copy.
     * @return a reference on 'this'.
     */
    ConstRangeFromPointAdapter& operator= ( const ConstRangeFromPointAdapter & other )
    {  
      if ( this != &other )
	{
	  myRangePtr = other.myRangePtr;
	  myFunctorPtr = other.myFunctorPtr;
	}
      return *this;
    }

    /**
     * Destructor. Does nothing.
     */
    ~ConstRangeFromPointAdapter() {}

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const { return true; }
  

    // ------------------------- private data --------------------------------
  private: 
    /**
     * Aliasing pointer on the range
     */
    const TRange* myRangePtr; 
    /**
     * Aliasing pointer on the underlying functor
     */
    const TFunctor* myFunctorPtr; 

    // ------------------------- iterator services --------------------------------
  public:

    /**
     * Iterator service.
     * @return begin iterator
     */
    ConstIterator begin() const {
      return ConstIterator( myRangePtr->begin(), *myFunctorPtr );
    }

    /**
     * Iterator service.
     * @return begin iterator from a point
     */
    ConstIterator begin(const Point& aPoint) const {
      return ConstIterator( myRangePtr->begin(aPoint), *myFunctorPtr );
    }

    /**
     * Iterator service.
     * @return end iterator
     */
    ConstIterator end() const {
      return ConstIterator( myRangePtr->end(), *myFunctorPtr );
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
     * @return rbegin iterator from a point
     */
    ConstReverseIterator rbegin(const Point& aPoint) const {
      ConstIterator it( myRangePtr->begin(aPoint), *myFunctorPtr ); 
      if ( it != this->end() ) ++it; 
      return ConstReverseIterator( it );
    }

    /**
     * Iterator service.
     * @return rend iterator
     */
    ConstReverseIterator rend() const {
      return ConstReverseIterator(this->begin());
    }


  }; //end class ConstRangeFromPointAdapter

} // namespace DGtal

  ///////////////////////////////////////////////////////////////////////////////


#endif // !defined ConstRangeFromPointAdapter_h

#undef ConstRangeFromPointAdapter_RECURSES
#endif // else defined(ConstRangeFromPointAdapter_RECURSES)
