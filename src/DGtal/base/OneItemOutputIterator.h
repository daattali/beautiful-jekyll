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
 * @file OneItemOutputIterator.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/04/24
 *
 * Header file for module OneItemOutputIterator.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(OneItemOutputIterator_RECURSES)
#error Recursive header files inclusion detected in OneItemOutputIterator.h
#else // defined(OneItemOutputIterator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define OneItemOutputIterator_RECURSES

#if !defined OneItemOutputIterator_h
/** Prevents repeated inclusion of headers. */
#define OneItemOutputIterator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class OneItemOutputIterator
  /**
   * Description of template class 'OneItemOutputIterator' <p>
   * \brief Aim: model of output iterator, ie incrementable and writable iterator, 
   * which only stores in a variable the last assigned item.
   * @tparam T at least a default constructible, copy constuctible and assignable type. 
   */
  template <typename T>
  class OneItemOutputIterator :
    public std::iterator<std::output_iterator_tag,void,void,void,void>  
  {

    BOOST_CONCEPT_ASSERT(( boost::DefaultConstructible<T> )); 
    BOOST_CONCEPT_ASSERT(( boost::CopyConstructible<T> )); 
    BOOST_CONCEPT_ASSERT(( boost::Assignable<T> ));
 
    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Default constructor.
     */
    OneItemOutputIterator(): myItemPtr(NULL)
    {
      myItemPtr = new T(); 
    }
    /**
     * Copy constructor.
     */
    OneItemOutputIterator(const OneItemOutputIterator& other): myItemPtr(other.myItemPtr) {}

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Assignment
     * @param aItem any item
     * @return a reference to *this
     */
    inline OneItemOutputIterator& operator=(const T& aItem) 
    { 
      ASSERT( isValid() ); 
      *myItemPtr = aItem;
      return *this; 
    }

    /**
     * Dereference operator
     * @return a reference to *this
     */
    inline OneItemOutputIterator& operator*() { return *this; }

    /**
     * Pre-increment operator
     * @return a reference to *this
     */
    inline OneItemOutputIterator& operator++() { return *this; }

    /**
     * Post-increment operator
     * @return *this
     */
    inline OneItemOutputIterator operator++(int) { return *this; } 

    /**
     * Accessor to the last assigned item.
     * @return the content of @a myItem.
     */
    inline T get() const 
    {
      ASSERT( isValid() ); 
      return *myItemPtr; 
    }

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    inline bool isValid() const { return (myItemPtr != NULL); }

    // ------------------------- Private Datas --------------------------------
  private:
    ///pointer that stores the last assigned item
    T* myItemPtr; 

  }; // end of class OneItemOutputIterator


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
//#include "DGtal/base/OneItemOutputIterator.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined OneItemOutputIterator_h

#undef OneItemOutputIterator_RECURSES
#endif // else defined(OneItemOutputIterator_RECURSES)
