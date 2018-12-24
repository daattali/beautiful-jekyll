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
 * @file ConstIteratorAdapter.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/09/01
 *
 * Header file for module ConstIteratorAdapter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ConstIteratorAdapter_RECURSES)
#error Recursive header files inclusion detected in ConstIteratorAdapter.h
#else // defined(ConstIteratorAdapter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ConstIteratorAdapter_RECURSES

#if !defined ConstIteratorAdapter_h
/** Prevents repeated inclusion of headers. */
#define ConstIteratorAdapter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/IteratorCirculatorTraits.h"
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/utility.hpp>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class ConstIteratorAdapter
  /**
   * Description of template class 'ConstIteratorAdapter'
   * \brief This class adapts any iterator
   * so that operator* returns another element 
   * than the one pointed to by the iterator.
   *
   * @tparam TIterator the type of the iterator to adapt.
   * 
   * To achieve this goal, the adapter is based on a functor f
   * given at construction so that operator* calls f(\*it), 
   * instead of calling directly operator* of the underlying 
   * iterator it.
   *
   * @tparam TLightFunctor the type of functor that transforms
   * the pointed element into another one (required to be light
   * because the functor is passed by value)
   *
   * @tparam TReturnType the type of the element returned by the underlying functor
   * (if TLightFunctor has a nested type called 'Value', 
   * TReturnType is set to TLightFunctor::Value by default)
   *
   * NB: from boost/iterator/transform_iterator.hpp
   */
  template <typename TIterator, typename TLightFunctor, typename TReturnType = typename TLightFunctor::Value >
  class ConstIteratorAdapter
    : public boost::iterator_adaptor< ConstIteratorAdapter<TIterator,TLightFunctor,TReturnType>, 
				      TIterator, TReturnType, boost::use_default, TReturnType >
  {
    typedef typename
    boost::iterator_adaptor< ConstIteratorAdapter<TIterator,TLightFunctor,TReturnType>, 
			     TIterator, TReturnType, boost::use_default, TReturnType >
    Super;

    friend class boost::iterator_core_access;

  public:

    typedef typename IteratorCirculatorTraits<TIterator>::Type Type; 


    /** 
     * Default constructor
     */
    ConstIteratorAdapter() { }

    /** 
     * Constructor
     *
     * @param i any iterator
     * @param f any functor
     */
    ConstIteratorAdapter(TIterator const& i, TLightFunctor f)
      : Super(i), myF(f) { }

    /** 
     * Copy constructor
     *
     * @param other the object to copy
     */
    template <
        class OtherFunctor
      , class OtherIterator
      , class OtherReturnType>
    ConstIteratorAdapter(
         ConstIteratorAdapter<OtherFunctor, OtherIterator, OtherReturnType> const& other
    )
      : Super(other.base()), myF(other.functor())
   {}

    /** 
     * Accessor on the functor
     *
     * @return a copy of @a myF
     */
    TLightFunctor functor() const
      { return myF; }

  private:

    /** 
     * Dereference function
     *
     * @return the object returned by the functor
     * from the element pointed by the underlying iterator 
     */
    typename Super::reference dereference() const
    { return myF(*this->base()); }

    /** functor */
    TLightFunctor myF;
  };


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
//#include "DGtal/base/ConstIteratorAdapter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ConstIteratorAdapter_h

#undef ConstIteratorAdapter_RECURSES
#endif // else defined(ConstIteratorAdapter_RECURSES)
