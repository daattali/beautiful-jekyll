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
 * @file IteratorAdapter.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/09/01
 *
 * Header file for module IteratorAdapter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(IteratorAdapter_RECURSES)
#error Recursive header files inclusion detected in IteratorAdapter.h
#else // defined(IteratorAdapter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define IteratorAdapter_RECURSES

#if !defined IteratorAdapter_h
/** Prevents repeated inclusion of headers. */
#define IteratorAdapter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include <boost/iterator/transform_iterator.hpp>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class IteratorAdapter
  /**
   * Description of template class 'IteratorAdapter' <p>
   * \brief This class adapts any lvalue iterator
   * so that operator* returns a member on the element pointed 
   * to by the iterator, instead the element itself.
   *
   * @tparam TIterator the type of the iterator to adapt
   *
   * To achieve this goal, the adapter is based on a functor f
   * given at construction so that operator* calls f(\*it), 
   * instead of calling directly operator* of the underlying 
   * iterator it. This operation returns a reference (or constant
   * reference) on a member of the element pointed to by the 
   * iterator, which can be read as well as assigned (if the 
   * member is not constant).  
   *
   * @tparam TFunctor the type of functor that transforms
   * the pointed element into another one
   *
   * @tparam TReturnType the type of the element returned by the underlying functor
   *
   */
  template <typename TIterator, typename TFunctor, typename TReturnType = typename TFunctor::Value>
  class IteratorAdapter:
    public boost::transform_iterator< TFunctor, TIterator, TReturnType&, TReturnType  > 
  {

  BOOST_CONCEPT_ASSERT(( boost_concepts::LvalueIteratorConcept<TIterator> ));

  public: 

    /** this class **/
    typedef IteratorAdapter< TIterator, TFunctor, TReturnType > Self; 
    /** parent class **/
    typedef boost::transform_iterator< TFunctor, TIterator, TReturnType&, TReturnType > Parent; 

    /** 
     * Default constructor
     */
    IteratorAdapter(): Parent() {}
    /** 
     * Constructor from an iterator and a functor
     * 
     * @param iter any iterator
     * @param func any functor 
     */
    IteratorAdapter( const TIterator& iter, TFunctor func ): Parent(iter,func) {}
    /** 
     * Copy operator
     * 
     * @param other the object of type Self to copy.
     */
    IteratorAdapter( const Self& other ): Parent( static_cast<const Parent&>(other) ) {}
    /** 
     * Copy operator
     * 
     * @param other the object of type Parent to copy.
     */
    IteratorAdapter( const Parent& other ): Parent(other) {}
    /** 
     * Assignement operator
     * 
     * @param other the object of type Self to copy.
     * @return this
     */
    Self& operator=( const Self& other )
    {
      if (this != &other)
	Parent::operator=( static_cast<const Parent&>(other) ); 
      return *this; 
    } 
    /** 
     * Assignement operator
     * 
     * @param other the object of type Parent to copy.
     * @return this
     */
    Self& operator=( const Parent& other )
    {
      if (this != &other)
	  Parent::operator=(other); 
      return *this; 
    }
    /** 
     * Destructor.
     *
     */
    ~IteratorAdapter() {}
  };

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
//#include "DGtal/base/IteratorAdapter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined IteratorAdapter_h

#undef IteratorAdapter_RECURSES
#endif // else defined(IteratorAdapter_RECURSES)
