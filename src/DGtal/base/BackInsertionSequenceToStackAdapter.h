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
 * @file BackInsertionSequenceToStackAdapter.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/12/07
 *
 * Header file for module BackInsertionSequenceToStackAdapter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(BackInsertionSequenceToStackAdapter_RECURSES)
#error Recursive header files inclusion detected in BackInsertionSequenceToStackAdapter.h
#else // defined(BackInsertionSequenceToStackAdapter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define BackInsertionSequenceToStackAdapter_RECURSES

#if !defined BackInsertionSequenceToStackAdapter_h
/** Prevents repeated inclusion of headers. */
#define BackInsertionSequenceToStackAdapter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/Alias.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class BackInsertionSequenceToStackAdapter
  /**
   * \brief Aim:
   * This class implements a dynamic adapter to an instance
   * of a model of back insertion sequence in order to get 
   * a stack interface. 
   * This class is a model of CStack. 
   * @tparam TSequence a model of boost::BackInsertionSequence
   */
  template <typename TSequence>
  class BackInsertionSequenceToStackAdapter
  {

    // ----------------------- Inner types ------------------------------------
  public: 

    /**
     * Type of the underlying container
     */
    typedef TSequence Container; 
    BOOST_CONCEPT_ASSERT(( boost::BackInsertionSequence<Container> ));

    /**
     * STL-like type of elements
     */
    typedef typename Container::value_type value_type; 
    /**
     * Type of elements
     */
    typedef typename Container::value_type Value; 

    /**
     * STL-like type used to represent the size of the container
     */
    typedef typename Container::size_type size_type; 
    /**
     * Type used to represent the size of the container
     */
    typedef typename Container::size_type Size; 


    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor.
     * @param aContainer a container to adapt
     */
    BackInsertionSequenceToStackAdapter(Alias<Container> aContainer);

    /**
     * Returns the size of the container.
     * @return the size, ie. the number of elements.
     */
    Size size() const;

    /**
     * Tests whether the container is empty or not. 
     * @return 'true' if empty, 'false' otherwise
     */
    bool empty() const;

    /**
     * Access to the top element, ie. the element 
     * available at the back of the underlying container. 
     * This method indeed calls method @a back of the 
     * underlying container. 
     * @return reference to the top element of the stack
     */
    Value& top();
    /**
     * Access to the top element, ie. the element 
     * available at the back of the underlying container. 
     * This method indeed calls method @a back of the 
     * underlying container. 
     * @return reference to the top element of the stack
     */
    const Value& top() const; 

    /**
     * Inserts an element above the current top element.
     * This method calls method @a push_back of the 
     * underlying container. 
     * @param aValue any value
     */
    void push(const Value& aValue);

    /**
     * Removes the element on top of the stack.
     * This method calls method @a pop_back of the 
     * underlying container. 
     */
    void pop();

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

    // ------------------------- Private Datas --------------------------------
  private:
    /**
     * Pointer to the underlying container
     */
    Container* myContainerPtr; 



  }; // end of class BackInsertionSequenceToStackAdapter


  /**
   * Overloads 'operator<<' for displaying objects of class 'BackInsertionSequenceToStackAdapter'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'BackInsertionSequenceToStackAdapter' to write.
   * @return the output stream after the writing.
   */
  template <typename TSequence>
  std::ostream&
  operator<< ( std::ostream & out, const BackInsertionSequenceToStackAdapter<TSequence> & object );

  /**
   * Function returning an object of class 'BackInsertionSequenceToStackAdapter' 
   * @param aSequence container to adapt. 
   * @tparam TSequence a model of back insertion sequence
   * @return the adapter.
   */
  template <typename TSequence>
  BackInsertionSequenceToStackAdapter<TSequence> 
  backStack ( TSequence& aSequence );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/base/BackInsertionSequenceToStackAdapter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined BackInsertionSequenceToStackAdapter_h

#undef BackInsertionSequenceToStackAdapter_RECURSES
#endif // else defined(BackInsertionSequenceToStackAdapter_RECURSES)
