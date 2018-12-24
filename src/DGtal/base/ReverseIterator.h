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
 * @file ReverseIterator.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/06/20
 *
 * Header file for module ReverseIterator.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ReverseIterator_RECURSES)
#error Recursive header files inclusion detected in ReverseIterator.h
#else // defined(ReverseIterator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ReverseIterator_RECURSES

#if !defined ReverseIterator_h
/** Prevents repeated inclusion of headers. */
#define ReverseIterator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/IteratorCirculatorTraits.h"
#include <boost/iterator.hpp>
#include <boost/utility.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class ReverseIterator
  /**
   * Description of template class 'ReverseIterator' <p>
   * \brief This class adapts any bidirectional iterator
   * so that operator++ calls operator-- and vice versa
   *
   * @tparam Iterator the type of the iterator to adapt,
   * a model of bidirectional iterator
   *
   * NB: adapted from boost/iterator/ReverseIterator.hpp
   */

  template <class Iterator>
  class ReverseIterator
      : public boost::iterator_adaptor< ReverseIterator<Iterator>, Iterator >
  {

      typedef boost::iterator_adaptor< ReverseIterator<Iterator>, Iterator > super_t;

      friend class boost::iterator_core_access;

   public:

      typedef typename IteratorCirculatorTraits<Iterator>::Type Type; 

      ReverseIterator() {}

      explicit ReverseIterator(Iterator x) 
          : super_t(x) {}

      template<class OtherIterator>
      ReverseIterator(
          ReverseIterator<OtherIterator> const& r
          , typename boost::enable_if_convertible<OtherIterator, Iterator>::type* = 0
          )
          : super_t(r.base())
      {}

   private:
      typename super_t::reference dereference() const { return *boost::prior(this->base()); }
    
      void increment() { --this->base_reference(); }
      void decrement() { ++this->base_reference(); }

      void advance(typename super_t::difference_type n)
      {
          this->base_reference() += -n;
      }

      template <class OtherIterator>
      typename super_t::difference_type
      distance_to(ReverseIterator<OtherIterator> const& y) const
      {
          return this->base_reference() - y.base();
      }
  };

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
//#include "DGtal/base/ReverseIterator.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ReverseIterator_h

#undef ReverseIterator_RECURSES
#endif // else defined(ReverseIterator_RECURSES)
