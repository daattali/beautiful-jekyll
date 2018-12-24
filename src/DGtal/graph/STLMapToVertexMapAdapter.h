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
 * @file STLMapToVertexMapAdapter.h
 * @author Jérémy Gaillard (\c jeremy.gaillard@insa-lyon.fr )
 * Institut National des Sciences Appliquées - INSA, France
 *
 * @date 2012/07/11
 *
 * Header file for template class STLMapToVertexMapAdapter
 *
 * This file is part of the DGtal library.
 */

#if defined(STLMapToVertexMapAdapter_RECURSES)
#error Recursive header files inclusion detected in STLMapToVertexMapAdapter.h
#else // defined(STLMapToVertexMapAdapter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define STLMapToVertexMapAdapter_RECURSES

#if !defined STLMapToVertexMapAdapter_h
/** Prevents repeated inclusion of headers. */
#define STLMapToVertexMapAdapter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class STLMapToVertexMapAdapter
  /**
  Description of template class 'STLMapToVertexMapAdapter' <p> \brief
  Aim: This class adapts any map of the STL to match with the CVertexMap concept
  
 
  @tparam TMap the type of the associative container.
 

   */
  template < typename TMap >
  class STLMapToVertexMapAdapter :
    public TMap
  {
    // ----------------------- Associated types ------------------------------
  public:
    typedef STLMapToVertexMapAdapter<TMap> Self;
    typedef TMap Container;
    typedef typename Container::value_compare Compare;
    typedef typename Container::allocator_type Allocator;
    typedef typename Container::key_type Vertex;
    typedef typename Container::mapped_type Value;
    

    // Cannot check this since some types using it are incomplete.
    // BOOST_CONCEPT_ASSERT(( CUndirectedSimpleLocalGraph< Graph > ));
    // BOOST_CONCEPT_ASSERT(( CSet< MarkSet, Vertex > ));


    // ----------------------- Standard services ------------------------------
  public:

    STLMapToVertexMapAdapter() : Container() {}
    
    template <class InputIterator> STLMapToVertexMapAdapter( InputIterator first,
	InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
	: Container( first, last, comp, alloc ) {}
    
    STLMapToVertexMapAdapter( STLMapToVertexMapAdapter & other ) 
	: Container( other ) {}

    void setValue(Vertex v, Value val)
    {
      (*this)[v] = val;
    }
    
    Value operator()(Vertex v)
    {
      typename Container::const_iterator it = Container::find(v);
      ASSERT( it != this->end() );
      return it->second;
    }

  }; // end of class STLMapToVertexMapAdapter


 

} // namespace DGtal



#endif // !defined STLMapToVertexMapAdapter_h

#undef STLMapToVertexMapAdapter_RECURSES
#endif // else defined(STLMapToVertexMapAdapter_RECURSES)
