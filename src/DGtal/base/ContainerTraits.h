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
 * @file ContainerTraits.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2015/09/22
 *
 * Header file for module ContainerTraits.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ContainerTraits_RECURSES)
#error Recursive header files inclusion detected in ContainerTraits.h
#else // defined(ContainerTraits_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ContainerTraits_RECURSES

#if !defined ContainerTraits_h
/** Prevents repeated inclusion of headers. */
#define ContainerTraits_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <boost/type_traits.hpp>
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <unordered_set>
#include <unordered_map>
#include <forward_list>
#include <array>

#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  // Tag classes for containers
  struct NotContainerCategory {};
  struct ContainerCategory {};
  struct SequenceCategory :  ContainerCategory {};
  struct AssociativeCategory :  ContainerCategory {};
  struct SimpleAssociativeCategory :  AssociativeCategory {};
  struct PairAssociativeCategory :  AssociativeCategory {};
  struct UniqueAssociativeCategory :  AssociativeCategory {};
  struct MultipleAssociativeCategory :  AssociativeCategory {};
  struct OrderedAssociativeCategory :  AssociativeCategory {};
  struct UnorderedAssociativeCategory :  AssociativeCategory {};
  struct SetAssociativeCategory :  OrderedAssociativeCategory, SimpleAssociativeCategory, UniqueAssociativeCategory {};
  struct MultisetAssociativeCategory :  OrderedAssociativeCategory, SimpleAssociativeCategory, MultipleAssociativeCategory {};
  struct MapAssociativeCategory :  OrderedAssociativeCategory, PairAssociativeCategory, UniqueAssociativeCategory {};
  struct MultimapAssociativeCategory :  OrderedAssociativeCategory, PairAssociativeCategory, MultipleAssociativeCategory {};
  struct UnorderedSetAssociativeCategory :  UnorderedAssociativeCategory, SimpleAssociativeCategory, UniqueAssociativeCategory {};
  struct UnorderedMultisetAssociativeCategory :  UnorderedAssociativeCategory, SimpleAssociativeCategory, MultipleAssociativeCategory {};
  struct UnorderedMapAssociativeCategory :  UnorderedAssociativeCategory, PairAssociativeCategory, UniqueAssociativeCategory {};
  struct UnorderedMultimapAssociativeCategory :  UnorderedAssociativeCategory, PairAssociativeCategory, MultipleAssociativeCategory {};
  
  /// Defines default container traits for arbitrary types.
  template <typename TContainer>
  struct ContainerTraits 
  {
    typedef NotContainerCategory Category;
  };

  /// Defines container traits for std::vector<>.
  template < class T, class Alloc >
  struct ContainerTraits< std::vector<T, Alloc> >
  {
    typedef SequenceCategory Category;
  };

  /// Defines container traits for std::list<>.
  template < class T, class Alloc >
  struct ContainerTraits< std::list<T, Alloc> >
  {
    typedef SequenceCategory Category;
  };

  /// Defines container traits for std::deque<>.
  template < class T, class Alloc >
  struct ContainerTraits< std::deque<T, Alloc> >
  {
    typedef SequenceCategory Category;
  };
  
  /// Defines container traits for std::forward_list<>.
  template < class T, class Alloc >
  struct ContainerTraits< std::forward_list<T, Alloc> >
  {
    typedef SequenceCategory Category;
  };

  /// Defines container traits for std::array<>.
  template < class T, size_t N >
  struct ContainerTraits< std::array<T, N> >
  {
    typedef SequenceCategory Category;
  };

  /// Defines container traits for std::set<>.
  template < class T, class Compare, class Alloc >
  struct ContainerTraits< std::set<T, Compare, Alloc> >
  {
    typedef SetAssociativeCategory Category;
  };
  
  /// Defines container traits for std::map<>.
  template < class Key, class T, class Compare, class Alloc >
  struct ContainerTraits< std::map<Key, T, Compare, Alloc> >
  {
    typedef MapAssociativeCategory Category;
  };

  /// Defines container traits for std::multiset<>.
  template < class T, class Compare, class Alloc >
  struct ContainerTraits< std::multiset<T, Compare, Alloc> >
  {
    typedef MultisetAssociativeCategory Category;
  };
  
  /// Defines container traits for std::multimap<>.
  template < class Key, class T, class Compare, class Alloc >
  struct ContainerTraits< std::multimap<Key, T, Compare, Alloc> >
  {
    typedef MultimapAssociativeCategory Category;
  };

  /// Defines container traits for boost::unordered_set<>.
  template < typename Value, typename Hash, typename Pred, typename Alloc >
  struct ContainerTraits< boost::unordered_set<Value, Hash, Pred, Alloc> >
  {
    typedef UnorderedSetAssociativeCategory Category;
  };

  /// Defines container traits for boost::unordered_multiset<>.
  template < typename Value, typename Hash, typename Pred, typename Alloc >
  struct ContainerTraits< boost::unordered_multiset<Value, Hash, Pred, Alloc> >
  {
    typedef UnorderedMultisetAssociativeCategory Category;
  };

  /// Defines container traits for boost::unordered_map<>.
  template < typename Value, typename T, typename Hash, typename Pred, typename Alloc >
  struct ContainerTraits< boost::unordered_map<Value, T, Hash, Pred, Alloc> >
  {
    typedef UnorderedMapAssociativeCategory Category;
  };

  /// Defines container traits for boost::unordered_multimap<>.
  template < typename Value, typename T, typename Hash, typename Pred, typename Alloc >
  struct ContainerTraits< boost::unordered_multimap<Value, T, Hash, Pred, Alloc> >
  {
    typedef UnorderedMultimapAssociativeCategory Category;
  };

  /// Defines container traits for std::unordered_set<>.
  template < class Key, class Hash, class Pred, class Alloc >
  struct ContainerTraits< std::unordered_set<Key, Hash, Pred, Alloc> >
  {
    typedef UnorderedSetAssociativeCategory Category;
  };

  /// Defines container traits for std::unordered_multiset<>.
  template < class Key, class Hash, class Pred, class Alloc >
  struct ContainerTraits< std::unordered_multiset<Key, Hash, Pred, Alloc> >
  {
    typedef UnorderedMultisetAssociativeCategory Category;
  };

  /// Defines container traits for std::unordered_map<>.
  template < class Key, class T, class Hash, class Pred, class Alloc >
  struct ContainerTraits< std::unordered_map<Key, T, Hash, Pred, Alloc> >
  {
    typedef UnorderedMapAssociativeCategory Category;
  };

  /// Defines container traits for std::unordered_multimap<>.
  template < class Key, class T, class Hash, class Pred, class Alloc >
  struct ContainerTraits< std::unordered_multimap<Key, T, Hash, Pred, Alloc> >
  {
    typedef UnorderedMultimapAssociativeCategory Category;
  };

  namespace detail
  {

    /////////////////////////////////////////////////////////////////////////////
    /**
     * Description of template class 'HasNestedTypeCategory' <p>
     * \brief Aim: 
     *  Checks whether type @a T has a nested type called 'Category' or not.
     *  NB: from en.wikipedia.org/wiki/Substitution_failure_is_not_an_error
     *  NB: to avoid various compiler issues, we use BOOST_STATIC_CONSTANT according to 
     *  http://www.boost.org/development/int_const_guidelines.html
     *  @tparam T any type.
     */
    template <typename T> 
    struct HasNestedTypeCategory 
    {
      typedef char yes[1]; 
      typedef char no[2]; 
      
      template <typename C>
      static yes& test(typename C::Category*);
      
      template <typename C>
      static no& test(...);
      
      BOOST_STATIC_CONSTANT(bool, value = sizeof(test<T>(0)) == sizeof(yes));  
    };

    /**
     * This class is used by IsContainer to determine if the container
     * category corresponds indeed to a container.
     */
    template <typename TCategory>
    struct IsContainerFromCategory {
      BOOST_STATIC_CONSTANT(bool, value = ( boost::is_base_of<ContainerCategory,TCategory>::value ) );
    };

    /**
     * This class is used by IsSequenceContainer to determine if the container category is a sequence.
     */
    template <typename TCategory>
    struct IsSequenceContainerFromCategory {
      BOOST_STATIC_CONSTANT(bool, value = ( boost::is_base_of<SequenceCategory,TCategory>::value ) );
    };

    /**
     * This class is used by IsAssociativeContainer to determine if the container category is  associative.
     */
    template <typename TCategory>
    struct IsAssociativeContainerFromCategory {
      BOOST_STATIC_CONSTANT(bool, value = ( boost::is_base_of<AssociativeCategory,TCategory>::value ) );
    };

    /**
     * This class is used by IsOrderedAssociativeContainer to determine if the container category is ordered associative.
     */
    template <typename TCategory>
    struct IsOrderedAssociativeContainerFromCategory {
      BOOST_STATIC_CONSTANT(bool, value = ( boost::is_base_of<OrderedAssociativeCategory,TCategory>::value ) );
    };

    /**
     * This class is used by IsUnorderedAssociativeContainer to determine if the container category is ordered associative.
     */
    template <typename TCategory>
    struct IsUnorderedAssociativeContainerFromCategory {
      BOOST_STATIC_CONSTANT(bool, value = ( boost::is_base_of<UnorderedAssociativeCategory,TCategory>::value ) );
    };

    /**
     * This class is used by IsSimpleAssociativeContainer to determine if the container category is simple associative.
     */
    template <typename TCategory>
    struct IsSimpleAssociativeContainerFromCategory {
      BOOST_STATIC_CONSTANT(bool, value = ( boost::is_base_of<SimpleAssociativeCategory,TCategory>::value ) );
    };
    
    /**
     * This class is used by IsPairAssociativeContainer to determine if the container category is pair associative.
     */
    template <typename TCategory>
    struct IsPairAssociativeContainerFromCategory {
      BOOST_STATIC_CONSTANT(bool, value = ( boost::is_base_of<PairAssociativeCategory,TCategory>::value ) );
    };
    
    /**
     * This class is used by IsUniqueAssociativeContainer to determine if the container category is unique associative.
     */
    template <typename TCategory>
    struct IsUniqueAssociativeContainerFromCategory {
      BOOST_STATIC_CONSTANT(bool, value = ( boost::is_base_of<UniqueAssociativeCategory,TCategory>::value ) );
    };
    
    /**
     * This class is used by IsMultipleAssociativeContainer to determine if the container category is multiple associative.
     */
    template <typename TCategory>
    struct IsMultipleAssociativeContainerFromCategory {
      BOOST_STATIC_CONSTANT(bool, value = ( boost::is_base_of<MultipleAssociativeCategory,TCategory>::value ) );
    };
    
  }

  /**
   * Determines at compile time if the given type \a T corresponds to a
   * (defined) container.
   */
  template <typename T>
  struct IsContainer {
    BOOST_STATIC_CONSTANT( bool, 
                           value = ( detail::HasNestedTypeCategory< ContainerTraits<T> >::value
                                     && detail::IsContainerFromCategory<typename ContainerTraits<T>::Category>::value ) );
  };

  /**
   * Determines at compile time if the given type \a T corresponds to an associative container.
   */
  template <typename T>
  struct IsSequenceContainer {
    BOOST_STATIC_CONSTANT( bool, 
                           value = ( detail::HasNestedTypeCategory< ContainerTraits<T> >::value
                                     && detail::IsSequenceContainerFromCategory<typename ContainerTraits<T>::Category>::value ) );
  };

  /**
   * Determines at compile time if the given type \a T corresponds to an associative container.
   */
  template <typename T>
  struct IsAssociativeContainer {
    BOOST_STATIC_CONSTANT( bool, 
                           value = ( detail::HasNestedTypeCategory< ContainerTraits<T> >::value
                                     && detail::IsAssociativeContainerFromCategory<typename ContainerTraits<T>::Category>::value ) );
  };

  /**
   * Determines at compile time if the given type \a T corresponds to an ordered associative container.
   */
  template <typename T>
  struct IsOrderedAssociativeContainer {
    BOOST_STATIC_CONSTANT( bool, 
                           value = ( detail::HasNestedTypeCategory< ContainerTraits<T> >::value
                                     && detail::IsOrderedAssociativeContainerFromCategory<typename ContainerTraits<T>::Category>::value ) );
  };

  /**
   * Determines at compile time if the given type \a T corresponds to an unordered associative container.
   */
  template <typename T>
  struct IsUnorderedAssociativeContainer {
    BOOST_STATIC_CONSTANT( bool, 
                           value = ( detail::HasNestedTypeCategory< ContainerTraits<T> >::value
                                     && detail::IsUnorderedAssociativeContainerFromCategory<typename ContainerTraits<T>::Category>::value ) );
  };

  /**
   * Determines at compile time if the given type \a T corresponds to a simple associative container.
   */
  template <typename T>
  struct IsSimpleAssociativeContainer {
    BOOST_STATIC_CONSTANT( bool, 
                           value = ( detail::HasNestedTypeCategory< ContainerTraits<T> >::value
                                     && detail::IsSimpleAssociativeContainerFromCategory<typename ContainerTraits<T>::Category>::value ) );
  };

  /**
   * Determines at compile time if the given type \a T corresponds to a pair associative container.
   */
  template <typename T>
  struct IsPairAssociativeContainer {
    BOOST_STATIC_CONSTANT( bool, 
                           value = ( detail::HasNestedTypeCategory< ContainerTraits<T> >::value
                                     && detail::IsPairAssociativeContainerFromCategory<typename ContainerTraits<T>::Category>::value ) );
  };

  /**
  * Determines at compile time if the given type \a T corresponds to a unique associative container.
  */
  template <typename T>
  struct IsUniqueAssociativeContainer {
    BOOST_STATIC_CONSTANT( bool, 
                           value = ( detail::HasNestedTypeCategory< ContainerTraits<T> >::value
                                     && detail::IsUniqueAssociativeContainerFromCategory<typename ContainerTraits<T>::Category>::value ) );
  };

  /**
   * Determines at compile time if the given type \a T corresponds to a multiple associative container.
   */
  template <typename T>
  struct IsMultipleAssociativeContainer {
    BOOST_STATIC_CONSTANT( bool, 
                           value = ( detail::HasNestedTypeCategory< ContainerTraits<T> >::value
                                     && detail::IsMultipleAssociativeContainerFromCategory<typename ContainerTraits<T>::Category>::value ) );
  };


} // namespace DGtal



//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ContainerTraits_h

#undef ContainerTraits_RECURSES
#endif // else defined(ContainerTraits_RECURSES)
