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
 * @file OutputIteratorAdapter.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/10
 *
 * Header file for module OutputIteratorAdapter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(OutputIteratorAdapter_RECURSES)
#error Recursive header files inclusion detected in OutputIteratorAdapter.h
#else // defined(OutputIteratorAdapter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define OutputIteratorAdapter_RECURSES

#if !defined OutputIteratorAdapter_h
/** Prevents repeated inclusion of headers. */
#define OutputIteratorAdapter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/base/CUnaryFunctor.h"
#include "DGtal/base/Circulator.h"

#include <iostream>

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class OutputIteratorAdapter
  /**
   * Description of template class 'OutputIteratorAdapter' <p>
   * \brief Aim: Adapts an output iterator i 
   * with a unary functor f, both given at construction,
   * so that the element pointed to by i is updated with 
   * a given value through f. 
   *
   * @tparam TIterator an output iterator
   *
   * @tparam TInputValue any input value
   *
   * @tparam TFunctor a unary functor
   * with reference on the element type as argument type
   * and reference on the the input value type as return type 
   *
   */
  template <typename TIterator, typename TFunctor, typename TInputValue>
  class OutputIteratorAdapter:
    public std::iterator<std::output_iterator_tag,void,void,void,void>
  {
    // ----------------------- Types definitions ------------------------------

  public:

    typedef TIterator Iterator; 
    BOOST_CONCEPT_ASSERT(( boost::ForwardIterator<Iterator> )); 
    BOOST_CONCEPT_ASSERT(( concepts::CUnaryFunctor<TFunctor, 
                           typename std::iterator_traits<Iterator>::value_type&, TInputValue& > )); 

    // ----------------------- Standard services ------------------------------
  public:
    /**
     * Constructor.
     * @param it any iterator 
     * @param f any functor
     */
    OutputIteratorAdapter(const Iterator &it, ConstAlias<TFunctor> f)
    : myIt(it), myF(&f) {}

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    OutputIteratorAdapter ( const OutputIteratorAdapter & other )
    : myIt(other.myIt), myF(other.myF) {}

    /**
     * Destructor.
     */
    ~OutputIteratorAdapter() {}

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Assignment
     * @param aValue any value
     * @return a reference to *this
     */
    OutputIteratorAdapter& operator=(const TInputValue& aValue) 
      { 
        myF->operator()( *myIt ) = aValue; 
        return *this; 
      }

    /**
     * Dereference operator
     * @return a reference to *this
     */
    OutputIteratorAdapter& operator*() { return *this; }

    /**
     * Pre-increment operator
     * @return a reference to *this
     */
    OutputIteratorAdapter& operator++() { ++myIt; return *this; }

    /**
     * Post-increment operator
     * @return *this
     */
    OutputIteratorAdapter operator++(int) 
    { 
      OutputIteratorAdapter tmp = *this; 
      ++myIt; 
      return tmp; 
    }


    // ------------------------- Hidden services ------------------------------
  protected:


  private:

    // ------------------------- Private Datas --------------------------------
  private:
    /**
     * Underlying iterator
     */
    Iterator myIt; 

    /**
     * Aliasing pointer on the underlying functor
     */
    const TFunctor* myF; 

  }; // end of class OutputIteratorAdapter

}
///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
//#include "DGtal/images/OutputIteratorAdapter.ih"

//
///////////////////////////////////////////////////////////////////////////////

#endif // !defined OutputIteratorAdapter_h

#undef OutputIteratorAdapter_RECURSES
#endif // else defined(OutputIteratorAdapter_RECURSES)
