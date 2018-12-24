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

/**
 * @file testDigitalSurfaceBoostGraphInterface.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2013/01/20
 *
 * Functions for testing class DigitalSurfaceBoostGraphInterface.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <boost/property_map/property_map.hpp>
#include <boost/pending/queue.hpp>
#include "DGtal/base/Common.h"
#include "DGtal/math/MPolynomial.h"
#include "DGtal/graph/DigitalSurfaceBoostGraphInterface.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/SetOfSurfels.h"
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/shapes/implicit/ImplicitPolynomial3Shape.h"
#include "DGtal/io/readers/MPolynomialReader.h"
/// JOL: Since using boost::vertices is enforced before we define it,
/// the compiler is unable to find our function boost::vertices. We
/// *must* include graph_concepts.hpp after defining our graph wrapper.
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/copy.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/stoer_wagner_min_cut.hpp>
#include <boost/graph/boykov_kolmogorov_max_flow.hpp>
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class DigitalSurfaceBoostGraphInterface.
///////////////////////////////////////////////////////////////////////////////


struct surfel_position_t {
    typedef boost::vertex_property_tag kind;
};

struct surfel_position {
  Z3i::Point myP;
  surfel_position() : myP()
  {
  }
};

typedef boost::property< boost::vertex_index_t, std::size_t, 
                         boost::property<surfel_position_t, surfel_position> > VertexProperties;


template <typename Graph1, typename Graph2, typename VertexIndexMap>
struct my_vertex_copier {
  typedef typename boost::property_map< Graph2, boost::vertex_index_t>::type graph_vertex_index_map;
  typedef typename boost::property_map< Graph2, surfel_position_t>::type graph_vertex_position_map;
  typedef typename boost::graph_traits< Graph1 >::vertex_descriptor Vertex1;
  typedef typename boost::graph_traits< Graph2 >::vertex_descriptor Vertex2;

  const Graph1 & myG1;
  graph_vertex_index_map graph_vertex_index;
  graph_vertex_position_map graph_vertex_position;
  VertexIndexMap & myIndexMap;

  my_vertex_copier(const Graph1& g1, Graph2& g2, VertexIndexMap & indexMap )
    : myG1( g1 ), 
      graph_vertex_index( boost::get( boost::vertex_index_t(), g2 ) ),
      graph_vertex_position( boost::get( surfel_position_t(), g2) ),
      myIndexMap( indexMap )
  {}

  void operator()( const Vertex1& v1, const Vertex2& v2 ) const {
    //  std::size_t idx = myIndexMap[ v1 ];
    // Does not work !
    // put( graph_vertex_index, v2, idx);
    surfel_position pos;
    pos.myP = v1.myCoordinates;
    //std::cout << "surfel " << idx << " at " << pos.myP << std::endl;
    put( graph_vertex_position, v2, pos);
  }
};
template <typename Graph1, typename Graph2>
struct my_edge_copier {
  my_edge_copier(const Graph1& UNUSED(g1), Graph2& UNUSED(g2))
  {}
  template <typename Edge1, typename Edge2>
  void operator()(const Edge1& /*v1*/, Edge2& /*v2*/) const {
    // does nothing
  }
};

/**
 * Example of a test. To be completed.
 *
 */
bool testDigitalSurfaceBoostGraphInterface()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;


  using namespace Z3i;

  // Construct the implicit shape
  typedef Space::RealPoint RealPoint;
  typedef RealPoint::Coordinate Ring;
  typedef MPolynomial<3, Ring> Polynomial3;
  typedef MPolynomialReader<3, Ring> Polynomial3Reader;
  typedef ImplicitPolynomial3Shape<Space> ImplicitShape;
  typedef GaussDigitizer<Space,ImplicitShape> DigitalShape; 

  // Implicit shape is an ellipse
  trace.beginBlock( "Constructing implicit shape." );
  double p1[] = {-2,-2,-2};
  double p2[] = { 2, 2, 2};
  std::string poly_str = "x*x+y*y+z*z-1";
  double step = 0.4;
  Polynomial3 P;
  Polynomial3Reader reader;
  std::string::const_iterator iter 
    = reader.read( P, poly_str.begin(), poly_str.end() );
  if ( iter != poly_str.end() )
    {
      std::cerr << "ERROR: I read only <" 
                << poly_str.substr( 0, iter - poly_str.begin() )
                << ">, and I built P=" << P << std::endl;
      return 1;
    }
  trace.info() << "- P = " << P << std::endl;
  ImplicitShape ishape( P );
  DigitalShape dshape;
  dshape.attach( ishape );
  dshape.init( RealPoint( p1 ), RealPoint( p2 ), step );
  Domain domain = dshape.getDomain();
  trace.endBlock();

  // Construct the Khalimsky space from the image domain
  trace.beginBlock ( "Construct the Khalimsky space from the image domain ..." );
  KSpace K;
  bool space_ok = K.init( domain.lowerBound(), 
                          domain.upperBound(), true // necessary
                          );
  if (!space_ok)
    {
      trace.error() << "Error in the Khamisky space construction."<<std::endl;
      return false;
    }
  trace.endBlock();

  //! [trackImplicitPolynomialSurfaceToOFF-SurfelAdjacency]
  typedef SurfelAdjacency<KSpace::dimension> MySurfelAdjacency;
  typedef KSpace::Surfel Surfel;
  typedef KSpace::SurfelSet SurfelSet;
  typedef SetOfSurfels< KSpace, SurfelSet > MySetOfSurfels;
  typedef DigitalSurface< MySetOfSurfels > MyDigitalSurface;
  trace.beginBlock ( "Extract surface ..." );

  MySurfelAdjacency surfAdj( true ); // interior in all directions.
  MySetOfSurfels theSetOfSurfels( K, surfAdj );
  Surfel bel = Surfaces<KSpace>::findABel( K, dshape, 100000 );
  Surfaces<KSpace>::trackBoundary( theSetOfSurfels.surfelSet(),
                                   K, surfAdj, 
                                   dshape, bel );
  MyDigitalSurface digSurf( theSetOfSurfels );
  trace.info() << "Digital surface has " << digSurf.size() << " surfels."
               << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing Graph concepts for DigitalSurface ..." );
  typedef MyDigitalSurface Graph;
  typedef boost::graph_traits<Graph>::vertex_descriptor vertex_descriptor; // ie DigitalSurface::Vertex
  typedef boost::graph_traits<Graph>::edge_descriptor edge_descriptor; // ie DigitalSurface::Arc
  typedef boost::graph_traits<Graph>::vertices_size_type vertices_size_type; // ie DigitalSurface::Size
  typedef boost::graph_traits<Graph>::vertex_iterator vertex_iterator;
  typedef boost::graph_traits<Graph>::out_edge_iterator out_edge_iterator;
  typedef boost::graph_traits<Graph>::edge_iterator edge_iterator;

  BOOST_CONCEPT_ASSERT(( boost::VertexListGraphConcept<Graph> ));
  BOOST_CONCEPT_ASSERT(( boost::AdjacencyGraphConcept<Graph> ));
  BOOST_CONCEPT_ASSERT(( boost::IncidenceGraphConcept<Graph> ));
  BOOST_CONCEPT_ASSERT(( boost::EdgeListGraphConcept<Graph> ));
  // BOOST_CONCEPT_ASSERT(( BidirectionalGraphConcept<Graph> ));
  trace.endBlock();

  trace.beginBlock ( "Testing IncidenceGraph interface with breadth_first_visit ..." );
  // get the property map for coloring vertices.
  typedef std::map< vertex_descriptor, boost::default_color_type > StdColorMap;
  StdColorMap colorMap;
  boost::associative_property_map< StdColorMap > propColorMap( colorMap );
  // get the property map for storing distances
  typedef std::map< vertex_descriptor, uint64_t > StdDistanceMap;
  StdDistanceMap distanceMap;
  boost::associative_property_map< StdDistanceMap > propDistanceMap( distanceMap );
  boost::queue< vertex_descriptor > Q; // std::queue does not have top().
  vertex_descriptor start = *( digSurf.begin() );
  boost::breadth_first_visit // boost graph breadth first visiting algorithm.
    ( digSurf, // the graph
      start, // the starting vertex
      Q, // the buffer for breadth first queueing
      boost::make_bfs_visitor( boost::record_distances( propDistanceMap, boost::on_tree_edge() ) ), // only record distances
      propColorMap  // necessary for the visiting vertices
      );
  trace.endBlock();

  // Display results
  trace.beginBlock ( "Display breadth_first_visit result ..." );
  uint64_t maxD = 0;
  vertex_descriptor furthest = start;
  uint64_t nbV = 0;
  for ( std::pair<vertex_iterator, vertex_iterator>
          vp = boost::vertices( digSurf ); vp.first != vp.second; ++vp.first, ++nbV )
    {
      uint64_t d = boost::get( propDistanceMap, *vp.first );
      if ( d > maxD ) 
        {
          maxD = d;
          furthest = *vp.first;
        }
    }
  trace.info() << "- d[ " << start << " ] = " << boost::get( propDistanceMap, start ) << std::endl;
  trace.info() << "- d[ " << furthest << " ] = " << maxD << std::endl;
  ++nb, nbok += ( nbV == digSurf.size() ) ? 1 : 0; 
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "nb vertices is ok" << std::endl;
  ++nb, nbok += ( maxD == 12 ) ? 1 : 0; 
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "maxD == 12" << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing VertexListGraph interface with connected_components ..." );
  // get the property map for labelling vertices.
  typedef std::map< vertex_descriptor, vertices_size_type > StdComponentMap;
  StdComponentMap componentMap;
  boost::associative_property_map< StdComponentMap > propComponentMap( componentMap );
  vertices_size_type nbComp =
    boost::connected_components // boost graph connected components algorithm.
    ( digSurf, // the graph
      propComponentMap, // the mapping vertex -> label
      boost::color_map( propColorMap ) // this map is used internally when computing connected components.
      );
  trace.info() << "- nbComponents = " << nbComp << std::endl;
  ++nb, nbok += ( nbComp == 1 ) ? 1 : 0; 
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "nbComp == 1" << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing UndirectedGraph interface with Wagner-Stoer min cut ..." );
  // get the property map for weighting edges.
  typedef double weight_type;
  typedef std::map< edge_descriptor, weight_type > StdWeightMap;
  StdWeightMap weightMap;
  boost::associative_property_map< StdWeightMap > propWeightMap( weightMap );
  typedef std::map< vertex_descriptor, vertices_size_type > StdVertexIndexMap;
  StdVertexIndexMap vertexIndexMap;
  boost::associative_property_map< StdVertexIndexMap > propVertexIndexMap( vertexIndexMap );
  vertices_size_type idxV = 0;
  // The weight is smaller for edges traversing plane z=0 than anywhere else.
  // The min cut thus cuts the sphere in two approximate halves.
  for ( std::pair<vertex_iterator, vertex_iterator> 
          vp = boost::vertices( digSurf ); vp.first != vp.second; ++vp.first, ++idxV )
    {
      vertex_descriptor v1 = *vp.first;
      vertexIndexMap[ v1 ] = idxV; 
      for ( std::pair<out_edge_iterator, out_edge_iterator>
              ve = boost::out_edges( v1, digSurf ); ve.first != ve.second; ++ve.first )
        {
          vertex_descriptor v2 = boost::target( *ve.first, digSurf );
          if ( v1 < v2 )
            {
              KSpace::SCell sep = digSurf.separator( *ve.first );
              weight_type weight = ( K.sKCoord( sep, 2 ) == 0 ) ? 0.01 : 1.0;
              weightMap[ *ve.first ] = weight;
              weightMap[ digSurf.opposite( *ve.first ) ] = weight;
            }
        }
    }  
  // get the parity map for assigning a set to each vertex.
  typedef std::map< vertex_descriptor, bool > StdParityMap;
  StdParityMap parityMap;
  boost::associative_property_map< StdParityMap > propParityMap( parityMap );

  weight_type total_weight =
    boost::stoer_wagner_min_cut // boost wagner stoer min cut algorithm.
    ( digSurf, // the graph
      propWeightMap, // the mapping edge -> weight
      boost::parity_map( propParityMap ) // this map stores the vertex assignation
      .vertex_index_map( propVertexIndexMap )
      );
  trace.info() << "- total weight = " << total_weight << std::endl;
  uint64_t nb0 = 0;
  uint64_t nb1 = 0;
  for ( std::pair<vertex_iterator, vertex_iterator> 
           vp = boost::vertices( digSurf ); vp.first != vp.second; ++vp.first, ++idxV )
     {
       vertex_descriptor v1 = *vp.first;
       //trace.info() << "- " << v1 << " in " << parityMap[ v1 ] << std::endl;
       if ( parityMap[ v1 ] ) ++nb1;
       else ++nb0;
     }
  ++nb, nbok += ( total_weight < 1.0 ) ? 1 : 0; 
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "total_weight < 1.0" 
               << ", nb0=" << nb0 << " nb1=" << nb1 << std::endl;
  trace.info() << "- parity[ " << start << " ] = " << parityMap[ start ] << std::endl;
  trace.info() << "- parity[ " << furthest << " ] = " << parityMap[ furthest ] << std::endl;
  ++nb, nbok += ( parityMap[ start ] != parityMap[ furthest ] ) ? 1 : 0; 
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "parityMap[ start ] != parityMap[ furthest ]" << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing EdgeListGraph and IncidenceGraph interfaces with Boykov-Kolmogorov max flow ..." );
  typedef double capacity_type;
  // get the property map for edge capacity.
  typedef std::map< edge_descriptor, weight_type > StdEdgeCapacityMap;
  StdEdgeCapacityMap edgeCapacityMap;
  boost::associative_property_map< StdEdgeCapacityMap > propEdgeCapacityMap( edgeCapacityMap );
  // get the property map for edge residual capacity.
  typedef std::map< edge_descriptor, weight_type > StdEdgeResidualCapacityMap;
  StdEdgeResidualCapacityMap edgeResidualCapacityMap;
  boost::associative_property_map< StdEdgeResidualCapacityMap > propEdgeResidualCapacityMap( edgeResidualCapacityMap );
  // get the property map for reverse edge.
  typedef std::map< edge_descriptor, edge_descriptor > StdReversedEdgeMap;
  StdReversedEdgeMap reversedEdgeMap;
  boost::associative_property_map< StdReversedEdgeMap > propReversedEdgeMap( reversedEdgeMap );
  // get the property map for vertex predecessor.
  typedef std::map< vertex_descriptor, edge_descriptor > StdPredecessorMap;
  StdPredecessorMap predecessorMap;
  boost::associative_property_map< StdPredecessorMap > propPredecessorMap( predecessorMap );
  // We already have vertex color map, vertex distance map and vertex index map.
  uint64_t nbEdges = 0;
  // The weight is smaller for edges traversing plane z=0 than anywhere else.
  // The min cut thus cuts the sphere in two approximate halves.
  for ( std::pair<edge_iterator, edge_iterator>
          ve = boost::edges( digSurf ); ve.first != ve.second; ++ve.first, ++nbEdges )
    {
      edge_descriptor e = *ve.first;
      edge_descriptor rev_e = digSurf.opposite( e );
      vertex_descriptor v1 = boost::source( e, digSurf );
      vertex_descriptor v2 = boost::target( e, digSurf );
      ASSERT( boost::source( rev_e, digSurf ) == v2 ); 
      ASSERT( boost::target( rev_e, digSurf ) == v1 ); 
      if ( v1 < v2 )
        {
          KSpace::SCell sep = digSurf.separator( *ve.first );
          capacity_type capacity = ( K.sKCoord( sep, 2 ) == 0 ) ? 0.01 : 1.0;
          edgeCapacityMap[ e ] = capacity;
          edgeCapacityMap[ digSurf.opposite( e ) ] = capacity;
          reversedEdgeMap[ e ] = digSurf.opposite( e );
          reversedEdgeMap[ digSurf.opposite( e ) ] = e;
        }
    }  
  trace.info() << "- nb edges = " << nbEdges << std::endl;
  distanceMap.clear();
  colorMap.clear();
  capacity_type max_flow =
    boost::boykov_kolmogorov_max_flow // boykov kolmogorov max flow algorithm.
    ( digSurf, // the graph
      propEdgeCapacityMap, propEdgeResidualCapacityMap,
      propReversedEdgeMap, propPredecessorMap, propColorMap, propDistanceMap, propVertexIndexMap, 
      start, furthest );
  trace.info() << "- max flow = " << max_flow << std::endl;
  ++nb, nbok += ( abs( max_flow - total_weight ) < 0.0000001 ) ? 1 : 0; 
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "max_flow == min_cut, Duality max-flow/min-cut." << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing AdjacencyListGraph with copy_graph ..." );
  typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::undirectedS, VertexProperties > BGraph;
  BGraph bG;
  boost::copy_graph( digSurf, bG,
                     boost::vertex_copy( my_vertex_copier<Graph,BGraph,StdVertexIndexMap>( digSurf, bG, vertexIndexMap ) )
                     .edge_copy( my_edge_copier<Graph,BGraph>( digSurf, bG ) )
                     .vertex_index_map( propVertexIndexMap )
                     );
  typedef boost::graph_traits< BGraph >::vertex_descriptor vertex_descriptor_2;
  typedef boost::graph_traits< BGraph >::vertex_iterator vertex_iterator_2;
  typedef boost::property_map< BGraph, surfel_position_t>::type GraphSurfelPositionMap;
  GraphSurfelPositionMap surfelPos( boost::get( surfel_position_t(), bG) );
  for ( std::pair<vertex_iterator_2, vertex_iterator_2> 
           vp = boost::vertices( bG ); vp.first != vp.second; ++vp.first )
     {
       vertex_descriptor_2 v1 = *vp.first;
       surfel_position pos = boost::get( surfelPos, v1 );
       trace.info() << "- " << v1 << " was at " << pos.myP << std::endl;
     }
  ++nb, nbok += boost::num_vertices( bG ) == boost::num_vertices( digSurf ) ? 1 : 0; 
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "after copy: Boost graph has " << num_vertices( bG ) 
               << " vertices." << std::endl;
  trace.endBlock();

  return nbok == nb;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int /* argc */, char** /* argv */ )
{
  trace.beginBlock ( "Testing class DigitalSurfaceBoostGraphInterface" );

  bool res = testDigitalSurfaceBoostGraphInterface(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
