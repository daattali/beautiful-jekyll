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
 * @file GraphVisitorRange.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2013/01/31
 *
 * Header file for module GraphVisitorRange.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(GraphVisitorRange_RECURSES)
#error Recursive header files inclusion detected in GraphVisitorRange.h
#else // defined(GraphVisitorRange_RECURSES)
/** Prevents recursive inclusion of headers. */
#define GraphVisitorRange_RECURSES

#if !defined GraphVisitorRange_h
/** Prevents repeated inclusion of headers. */
#define GraphVisitorRange_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class GraphVisitorRange
  /**
     Description of template class 'GraphVisitorRange' <p>
     \brief Aim: Transforms a graph visitor into a single pass input range.
   
     @code
  typedef DepthFirstVisitor<Graph, std::set<Vertex> > DFSVisitor;
  typedef GraphVisitorRange<DFSVisitor> VisitorRange;
  VisitorRange range( new DFSVisitor( g, Point( -2, -1 ) ) );
  for ( VisitorRange::ConstIterator it = range.begin(), itEnd = range.end();
        it != itEnd; ++it )
    { // Vertex is *it
    ...
    }
     @endcode

     @todo Complete boost::range_iterator<> accordingly.
   */
  template < typename TGraphVisitor >
  class GraphVisitorRange
  {
  public:
    typedef TGraphVisitor GraphVisitor;
    typedef typename GraphVisitor::Graph Graph;
    typedef typename GraphVisitor::Vertex Vertex;
    typedef typename GraphVisitor::Node Node;
    typedef typename GraphVisitor::Size Size;
    typedef typename GraphVisitor::Data Data;

    /**
       Allows to access the node as the pair (Vertex,distance) when
       iterating over the graph.
    */
    struct NodeAccessor {
      typedef const Node value;
      typedef const Node value_type;
      typedef const Node* pointer;
      typedef const Node& reference;
      inline
      static reference get( const Node & node )
      { return node; }
    };

    /**
       Allows to access the node as only the Vertex when iterating
       over the graph.
    */
    struct VertexAccessor {
      typedef const Vertex value;
      typedef const Vertex value_type;
      typedef const Vertex* pointer;
      typedef const Vertex& reference;
      inline
      static reference get( const Node & node )
      { return node.first; }
    };

    /**
       A single-pass input iterator that adapts a visitor to explore vertices. The default iterator is equivalent to an end().

       @tparam TAccessor  type of accessor for the iterator, either NodeAccessor or VertexAccessor.

       @todo Complete boost::iterator_traversal<> accordingly.
     */
    template <typename TAccessor>
    struct GenericConstIterator 
    {
      typedef GenericConstIterator<TAccessor> Self;
      typedef TAccessor Accessor;

      // stl iterator types.
      typedef std::input_iterator_tag iterator_category;
      typedef typename Accessor::value value_type;
      typedef std::ptrdiff_t difference_type; 
      typedef typename Accessor::pointer pointer;
      typedef typename Accessor::reference reference;

      /// Smart pointer to a Visitor.
      CountedPtr< GraphVisitor > myVisitor;

      inline
      GenericConstIterator() 
        : myVisitor( 0 ) {}
      inline
      GenericConstIterator( CountedPtr<GraphVisitor> ptrV ) 
        : myVisitor( ptrV ) {}
      inline
      GenericConstIterator( const Self & other ) 
        : myVisitor( other.myVisitor ) {}

      inline
      Self & operator=( const Self & other )
      {
        if ( this != &other )
          myVisitor = other.myVisitor;
        return *this;
      }

      inline
      reference
      operator*() const
      {
        ASSERT( ( myVisitor.get() != 0 )
                && "DGtal::GraphVisitorRange<>::GenericConstIterator<>::operator*(): you cannot dereferenced a null visitor (i.e. end()).");
        return Accessor::get( myVisitor->current() );
      }

      inline
      pointer
      operator->() const
      { 
        ASSERT( ( myVisitor.get() != 0 )
                && "DGtal::GraphVisitorRange<>::GenericConstIterator<>::operator->(): you cannot dereferenced a null visitor (i.e. end()).");
        return & Accessor::get( operator*() );
      }

      inline
      Self&
      operator++()
      {
        myVisitor->expand();
	return *this;
      }

      inline
      Self
      operator++(int)
      {
	Self __tmp = *this;
        myVisitor->expand();
	return __tmp;
      }
      
      inline
      bool operator==( const Self & other ) const
      {
        if ( ( myVisitor.get() == 0 ) || myVisitor->finished() )
          return ( other.myVisitor.get() == 0 ) || other.myVisitor->finished();
        else if ( other.myVisitor.get() == 0 )
          return false;
        else
          return &(myVisitor->current()) == &(other.myVisitor->current());
      }

      inline
      bool operator!=( const Self & other ) const
      {
        return ! ( this->operator==( other ) );
      }
    };

    /// const iterator on Vertex for visiting a graph by following a
    /// breadth first traversal.
    typedef GenericConstIterator<VertexAccessor> VertexConstIterator;
    /// const iterator on pair (Vertex,distance) for visiting a graph by
    /// following a breadth first traversal.
    typedef GenericConstIterator<NodeAccessor> NodeConstIterator;

    typedef VertexConstIterator ConstIterator;
    typedef ConstIterator const_iterator;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~GraphVisitorRange();

    /**
       Constructor from dynamically allocated visitor. The visitor is
       acquired by this object.

       @param visitorPtr a pointer to a dynamically allocated visitor,
       which is acquired by this object. This visitor defines the
       starting point for the traversal. It must be valid (!= 0).
     */
    GraphVisitorRange( GraphVisitor* visitorPtr );

    /**
       The value of the iterator has type Vertex. 
       @return a single pass input iterator pointing on the first element of the graph traversal induced by the given visitor.

       NB: if you have already called begin() or beginNode(), it will raise an assertion.
    */
    ConstIterator begin() const;

    /**
       The value of the iterator has type Vertex. 
       @return a single pass input iterator pointing after the last element of the graph traversal induced by the given visitor.
    */
    ConstIterator end() const;

    /**
       The value of the iterator has type Node, i.e. std::pair<Vertex,Data>.
       @return a single pass input iterator pointing on the first element of the graph traversal induced by the given visitor.

       NB: if you have already called begin() or beginNode(), it will raise an assertion.
    */
    NodeConstIterator beginNode() const;

    /**
       The value of the iterator has type Node, i.e. std::pair<Vertex,Data>.
       @return a single pass input iterator pointing after the last element of the graph traversal induced by the given visitor.
    */
    NodeConstIterator endNode() const;

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

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:

    /// A smart pointer on a graph visitor.
    CountedPtr<GraphVisitor> myVisitor;

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    GraphVisitorRange();

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    GraphVisitorRange ( const GraphVisitorRange & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    GraphVisitorRange & operator= ( const GraphVisitorRange & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class GraphVisitorRange


  /**
   * Overloads 'operator<<' for displaying objects of class 'GraphVisitorRange'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'GraphVisitorRange' to write.
   * @return the output stream after the writing.
   */
  template <typename TGraphVisitor>
  std::ostream&
  operator<< ( std::ostream & out, const GraphVisitorRange<TGraphVisitor> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/graph/GraphVisitorRange.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined GraphVisitorRange_h

#undef GraphVisitorRange_RECURSES
#endif // else defined(GraphVisitorRange_RECURSES)
