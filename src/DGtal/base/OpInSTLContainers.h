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
 * @file OpInSTLContainers.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/10/29
 *
 * \brief Implementation of an adapter for erase and insert 
 * methods of STL containers so that they not only 
 * work for iterator type, but also for reverse_iterator type.  
 *
 * Header file for module OpInSTLContainers.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(OpInSTLContainers_RECURSES)
#error Recursive header files inclusion detected in OpInSTLContainers.h
#else // defined(OpInSTLContainers_RECURSES)
/** Prevents recursive inclusion of headers. */
#define OpInSTLContainers_RECURSES

#if !defined OpInSTLContainers_h
/** Prevents repeated inclusion of headers. */
#define OpInSTLContainers_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <list>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

//////////////////////////////////////////////////////////////////////////////
// generic classes for operations in STL containers
// that cannot be performed with a reverse_iterator type

  /////////////////////////////////////////////////////////////////////////////
  /** 
   * Description of struct 'OpInSTLContainers' <p>
   * \brief Aim: Implementation of an adapter for erase and insert 
   * methods of STL containers so that they not only 
   * work for the iterator type, but also for the reverse_iterator type.  
   * @code
//      anIterator = aContainer.erase(anIterator);
//does not compile if anIterator has type 'std::reverse_iterator'
//erase only takes parameter of type 'std::iterator'
        anIterator = 
        DGtal::OpInSTLContainers<Container,Iterator>
             ::erase(aContainer, anIterator);
   * @endcode
   * @see Preimage2D.ih
   */

    //default (iterator type)
    template <typename Container, typename Iterator>
    struct OpInSTLContainers 
    {
      static Iterator erase(Container& aContainer,Iterator& anIterator) 
      {
        return aContainer.erase(anIterator);
      }

      static Iterator insert(Container& aContainer,Iterator& anIterator) 
      {
        return aContainer.insert(anIterator);
      }

    };

    //specialisation for reverse_iterator type
    template <typename Container>
    struct OpInSTLContainers<
      Container, 
      std::reverse_iterator<typename Container::iterator> > 
    {
      typedef typename Container::iterator Iterator;
      typedef std::reverse_iterator<typename Container::iterator> ReverseIterator;

      static ReverseIterator erase(
                  Container& aContainer,
                  ReverseIterator& anIterator) 
      {
        //base iterator pointing to the same element 
        Iterator base = (++anIterator).base();
        //base iterator pointing to the element that
        //followed the erased element 
	base = aContainer.erase(base);
        //reverse iterator pointing to the element that
        //preceded the erased element  
        return ReverseIterator(base);
      }

      static ReverseIterator insert(
                  Container& aContainer,
                  ReverseIterator& anIterator, 
                  const typename Container::value_type& aValue) 
      {
        Iterator base = aContainer.insert(anIterator.base(), aValue);
        return ReverseIterator(base);
      }
    };

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined OpInSTLContainers_h

#undef OpInSTLContainers_RECURSES
#endif // else defined(OpInSTLContainers_RECURSES)
