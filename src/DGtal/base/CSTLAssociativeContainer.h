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
 * @file CSTLAssociativeContainer.h
 * @author David Coeurjolly
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2015/07/06
 *
 * Header file for concept CSTLAssociativeContainer
 *
 * This file is part of the DGtal library.
 */

#if defined(CSTLAssociativeContainer_RECURSES)
#error Recursive header files inclusion detected in CSTLAssociativeContainer.h
#else // defined(CSTLAssociativeContainer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CSTLAssociativeContainer_RECURSES

#if !defined CSTLAssociativeContainer_h
/** Prevents repeated inclusion of headers. */
#define CSTLAssociativeContainer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
    /////////////////////////////////////////////////////////////////////////////
    // class CSTLAssociativeContainer
    /**
       DescriptionDescription of \b concept '\b CSTLAssociativeContainer' 
       @ingroup Concepts

       \brief Aim: Defines the concept describing an Associative
       Container of the STL
       (https://www.sgi.com/tech/stl/AssociativeContainer.html).

       @note This concept can also be found in the boost library under
       the name  boost::AssociativeContainer. However, there is a
       issue in this concept (problem in boost 1.58 but present in
       several releases) which requires the container to be "sorted". As
       a consequence, boost::unordered_set does not satisfy the concept.


       ### Refinement of 
       - boost::ForwardContainer
       - boost::DefaultConstructible

       ### Provided types:

       - value_type: the value type
       - key_type: the key type
       - iterator: the iterator type
       - const_iterator: a const iterator type
       - size_type: a size type
 

       ### Notation:

       - x an object of a model of CSTLAssociativeContainer.
       - val an object of type value_type
       - key and object of type key_type
       - p, q two instances of type iterator
 
       For a complete desccription of this concept, please check https://www.sgi.com/tech/stl/AssociativeContainer.html.

       ### Invariants

       ### Models
      
       std::set, std::unordered_set (c++11), boost::unordered_set.


       ### Notes

       @tparam T the type that is checked. T should be a model of CSTLAssociativeContainer.

    */
    template <typename T>
      struct CSTLAssociativeContainer : boost::ForwardContainer<T>, boost::DefaultConstructible<T>
    {
      // ----------------------- Concept checks ------------------------------
    public:
      typedef typename T::iterator iterator;
      typedef typename T::value_type value_type;
      typedef typename T::key_type key_type;
      typedef typename T::size_type size_type;
      typedef typename T::const_iterator const_iterator;

      BOOST_CONCEPT_USAGE(CSTLAssociativeContainer)
      {
        x.erase(key);
        x.erase(p);
        x.erase(p, q);
        x.clear();
        p = x.find(key);
        r = x.equal_range(key);
        n = x.count(key);
      };

    private:
      void const_constraints(const T& cc)
      {
        ci = cc.find(key);
        n = cc.count(key);
        cr = cc.equal_range(key);
      }
    

    private:
      T x;
      iterator p,q;
      const_iterator ci;
      value_type val;
      key_type key;
      size_type n;
      std::pair<iterator,iterator> r;
      std::pair<const_iterator,const_iterator> cr;
    
    }; // end of concept CSTLAssociativeContainer
  } // namespace concept
} // namespace DGtal



//                                        //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CSTLAssociativeContainer_h

#undef CSTLAssociativeContainer_RECURSES
#endif // else defined(CSTLAssociativeContainer_RECURSES)
