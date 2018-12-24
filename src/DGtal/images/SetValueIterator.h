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
 * @file SetValueIterator.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/10
 *
 * Header file for module SetValueIterator.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SetValueIterator_RECURSES)
#error Recursive header files inclusion detected in SetValueIterator.h
#else // defined(SetValueIterator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SetValueIterator_RECURSES

#if !defined SetValueIterator_h
/** Prevents repeated inclusion of headers. */
#define SetValueIterator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/base/Common.h"
#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/images/CTrivialImage.h"

#include <iostream>

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class SetValueIterator
  /**
   * Description of template class 'SetValueIterator' <p>
   * \brief Aim: implements an output iterator,
   * which is able to write values in an underlying image,
   * by calling its setValue method.
   *
   * @tparam TImage a model of CSetValueImage
   *
   */
  template <typename TImage, typename TIteratorOnPts
	    = typename TImage::Domain::ConstIterator>
  class SetValueIterator:
    public std::iterator<std::output_iterator_tag,void,void,void,void>
  {
    // ----------------------- Types definitions ------------------------------
  public:

    typedef TImage Image;
    BOOST_CONCEPT_ASSERT(( concepts::CTrivialImage<Image> ));


    // ----------------------- Standard services ------------------------------
  public:
    /**
     * Constructor.
     * @param aItOnPts an iterator on points
     * @param aImg any image passed by reference
     */
    SetValueIterator(const TIteratorOnPts& aItOnPts, Image &aImg)
: myImg(&aImg), myItOnPts(aItOnPts) {}

    /**
     * Overloaded constructor, which can be used
     * with the default template argument.
     * @param aImg any image passed by reference
     */
    SetValueIterator(Image &aImg)
: myImg(&aImg), myItOnPts(myImg->domain().begin()) {}

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    SetValueIterator ( const SetValueIterator & other )
: myImg(other.myImg), myItOnPts(other.myItOnPts) {}

    /**
     * Destructor.
     */
    ~SetValueIterator() {}

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Assignment
     * @param aValue any value
     * @return a reference to *this
     */
    SetValueIterator& operator=(const typename Image::Value& aValue)
      {
        myImg->setValue( *myItOnPts, aValue );
        return *this;
      }

    /**
     * Dereference operator
     * @return a reference to *this
     */
    SetValueIterator& operator*() { return *this; }

    /**
     * Pre-increment operator
     * @return a reference to *this
     */
    SetValueIterator& operator++() { ++myItOnPts; return *this; }

    /**
     * Post-increment operator
     * @return *this
     */
    SetValueIterator operator++(int)
    {
      SetValueIterator tmp = *this;
      ++myItOnPts;
      return tmp;
    }


    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:


  private:


    // ------------------------- Internals ------------------------------------
  private:

    /**
     * Aliasing pointer on the underlying image
     */
    Image* myImg;

    /**
     * Iterator on points that scan the domain of the underlying image
     */
    TIteratorOnPts myItOnPts;

  }; // end of class SetValueIterator

}
///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
//#include "DGtal/images/SetValueIterator.ih"

//
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SetValueIterator_h

#undef SetValueIterator_RECURSES
#endif // else defined(SetValueIterator_RECURSES)
