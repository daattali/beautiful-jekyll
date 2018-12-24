/**
 * @file graph/graphTraversal.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 * @author Jérémy Gaillard (\c jeremy.gaillard@insa-lyon.fr )
 *
 * @date 2013/01/31
 *
 * An example file named graphTraversal.
 *
 * This file is part of the DGtal library.
 */

/**
Traverses a 2D graph in different ways (enumeration, breadth-first traversal, depth-first traversal).

@see \ref dgtal_graph_def_2

@verbatim
# Commands
$ ./examples/graph/graphTraversal
# see files graphTraversal-enum.eps, graphTraversal-bfs.eps, graphTraversal-dfs-range.eps.
@endverbatim

@image html graphTraversal-enum.png "Coloring vertices of an object graph according to the enumeration order."
@image html graphTraversal-bfs.png "Coloring vertices of an object graph according to the topological distance to a seed (breadth-first traversal)."
@image html graphTraversal-dfs-range.png "Coloring vertices of an object graph according to their order given by a depth-first traversal."

\example graph/graphTraversal.cpp
*/

///////////////////////////////////////////////////////////////////////////////
//! [graphTraversal-basicIncludes]
#include <iostream>
#include <vector>
#include <iterator>
#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/topology/Object.h"
#include "DGtal/graph/BreadthFirstVisitor.h"
#include "DGtal/graph/DepthFirstVisitor.h"
#include "DGtal/graph/GraphVisitorRange.h"
#include "DGtal/graph/CUndirectedSimpleGraph.h"
//! [graphTraversal-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int /* argc */, char** /* argv */ )
{
  //! [graphTraversal-graph-instanciation]
  using namespace Z2i;
  Point p1( -41, -36 ), p2( 18, 18 );
  Domain domain( p1, p2 );
  DigitalSet shape_set( domain );
  Shapes<Domain>::addNorm2Ball( shape_set, Point( -2, -1 ), 9 );
  Shapes<Domain>::addNorm1Ball( shape_set, Point( -14, 5 ), 9 );
  Shapes<Domain>::addNorm1Ball( shape_set, Point( -30, -15 ), 10 );
  Shapes<Domain>::addNorm2Ball( shape_set, Point( -10, -20 ), 12 );
  Shapes<Domain>::addNorm1Ball( shape_set, Point( 12, -1 ), 4 );
  Object4_8 g( dt4_8, shape_set ); // 4-adjacency graph.
  typedef Object4_8 Graph;
  typedef Point Vertex;
  BOOST_CONCEPT_ASSERT(( concepts::CUndirectedSimpleGraph< Graph > ));
  //! [graphTraversal-graph-instanciation]

  HueShadeColorMap<int> cmap_hue( 0, 400, 10 );
  GradientColorMap<int> cmap_grad( 0, 52);
  cmap_grad.addColor( Color( 0, 0, 255 ) );
  cmap_grad.addColor( Color( 0, 255, 255 ) );
  cmap_grad.addColor( Color( 0, 255, 0 ) );
  cmap_grad.addColor( Color( 255, 255, 0 ) );
  cmap_grad.addColor( Color( 255, 0, 0 ) );
  cmap_grad.addColor( Color( 255, 0, 255 ) );

  Board2D board;
  board << SetMode( domain.className(), "Paving" )
        << domain << SetMode( p1.className(), "Paving" );
  string specificStyle = p1.className() + "/Paving";

  //! [graphTraversal-graph-enumeration]
  int n = 0;
  for ( Graph::ConstIterator it = g.begin(), itEnd = g.end();
        it != itEnd; ++it, ++n )
    { // Vertex are colored in order.
      Vertex vtx = *it;
      board << CustomStyle( specificStyle,
                            new CustomColors( Color::Black,
                                              cmap_hue( n ) ) )
            << vtx;
    }
  board.saveEPS("graphTraversal-enum.eps");
  //! [graphTraversal-graph-enumeration]

  {
    //! [graphTraversal-vertex-edge-enumeration]
    int nn = 0;
    int mm = 0;
    std::vector<Vertex> neighbors;
    for ( Graph::ConstIterator it = g.begin(), itEnd = g.end();
          it != itEnd; ++it, ++nn )
      {
        Vertex vtx = *it;
        std::back_insert_iterator< std::vector<Vertex> > neighIt
          = std::back_inserter( neighbors );
        g.writeNeighbors( neighIt, vtx );
        mm += neighbors.size();
        neighbors.clear();
      }
    trace.info() << "Graph has " << nn << " vertices and "
                 << (mm/2) << " edges." << std::endl;
    //! [graphTraversal-vertex-edge-enumeration]
  }

  board.clear();
  board << SetMode( domain.className(), "Paving" )
        << domain << SetMode( p1.className(), "Paving" );
  //! [graphTraversal-graph-bfs]
  typedef BreadthFirstVisitor<Graph, std::set<Vertex> > BFSVisitor;
  typedef BFSVisitor::Node Node;
  BFSVisitor bfv( g, Point( -2, -1 ) );
  while( ! bfv.finished() )
  { // Vertex are colored according to the distance to initial seed.
    Node node = bfv.current();
    board << CustomStyle( specificStyle,
                          new CustomColors( Color::Black,
                                            cmap_grad( node.second ) ) )
          << node.first; // the vertex
    bfv.expand();
  }
  board.saveEPS("graphTraversal-bfs.eps");
  //! [graphTraversal-graph-bfs]

  board.clear();
  board << SetMode( domain.className(), "Paving" )
        << domain << SetMode( p1.className(), "Paving" );
  //! [graphTraversal-graph-dfs-range]
  typedef DepthFirstVisitor<Graph, std::set<Vertex> > DFSVisitor;
  typedef GraphVisitorRange<DFSVisitor> VisitorRange;
  VisitorRange range( new DFSVisitor( g, Point( -2, -1 ) ) );
  n = 0;
  for ( VisitorRange::ConstIterator it = range.begin(), itEnd = range.end();
        it != itEnd; ++it, ++n )
    { // Vertex are colored according to their order (depth first order here).
      Vertex vtx = *it;
      board << CustomStyle( specificStyle,
                            new CustomColors( Color::Black,
                                              cmap_hue( n ) ) )
            << vtx;
    }
  board.saveEPS("graphTraversal-dfs-range.eps");
  //! [graphTraversal-graph-dfs-range]

  return 0;
}
