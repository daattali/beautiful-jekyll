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
 * @file testObjectBoostGraphInterface.cpp
 * @ingroup Tests
 * @author Pablo Hernandez-Cerdan. Institute of Fundamental Sciences. Massey University. Palmerston North, New Zealand
 *
 * @date 2016/02/01
 *
 * Functions for testing class ObjectBoostGraphInterface.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include "DGtalCatch.h"
#include <iostream>
#include <queue>
#include <boost/property_map/property_map.hpp>
#include <boost/pending/queue.hpp>
#include "DGtal/base/Common.h"
#include "DGtal/graph/ObjectBoostGraphInterface.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/Object.h"
#include "DGtal/topology/DigitalTopology.h"
#include "DGtal/topology/SurfelAdjacency.h"
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
#include <boost/graph/filtered_graph.hpp>
///////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////
// Fixture for object from a diamond set and DT26_6 topology.
///////////////////////////////////////////////////////////////////////////
struct Fixture_object_diamond_with_hole {
  ///////////////////////////////////////////////////////////
  // type aliases
  ///////////////////////////////////////////////////////////
  using Point  = DGtal::Z3i::Point;
  using Domain = DGtal::Z3i::Domain;

  using FixtureDigitalTopology =
    DGtal::Z3i::DT26_6;
  using FixtureDigitalSet =
    DGtal::DigitalSetByAssociativeContainer<Domain , std::unordered_set<Point> >;
  using FixtureObject =
    DGtal::Object<FixtureDigitalTopology, FixtureDigitalSet>;

  ///////////////////////////////////////////////////////////
  // fixture data
  FixtureObject obj_fixture;
  ///////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////
  // Constructor
  ///////////////////////////////////////////////////////////
  Fixture_object_diamond_with_hole() {
    using namespace DGtal;

    // trace.beginBlock ( "Create Fixture_object_diamond" );
    Point p1( -10, -10, -10 );
    Point p2( 10, 10, 10 );
    Domain domain( p1, p2 );
    Point c( 0, 0, 0 );

    // diamond of radius 4
    FixtureDigitalSet diamond_set( domain );
    for ( auto it = domain.begin(); it != domain.end(); ++it )
    {
      if ( (*it - c ).norm1() <= 3 ) diamond_set.insertNew( *it );
    }
    diamond_set.erase( c );

    FixtureDigitalTopology::ForegroundAdjacency adjF;
    FixtureDigitalTopology::BackgroundAdjacency adjB;
    FixtureDigitalTopology topo(adjF, adjB, DGtal::DigitalTopologyProperties::JORDAN_DT);
    obj_fixture = FixtureObject(topo,diamond_set);

    // trace.endBlock();
  }
 };

////////////////////////////////////////////////////////
// copiers between Object and boost::adjacency_list
////////////////////////////////////////////////////////
struct vertex_position_t {
  using kind = boost::vertex_property_tag ;
};

struct vertex_position {
  Z3i::Point myP;
  vertex_position() : myP()
  {
  }
};

using VertexProperties = boost::property< boost::vertex_index_t, std::size_t,
            boost::property<vertex_position_t, vertex_position> > ;

template <typename Graph1, typename Graph2, typename VertexIndexMap>
struct my_vertex_copier {
  using graph_vertex_index_map = typename boost::property_map< Graph2, boost::vertex_index_t>::type ;
  using graph_vertex_position_map = typename boost::property_map< Graph2, vertex_position_t>::type ;
  using Vertex1 = typename boost::graph_traits< Graph1 >::vertex_descriptor ;
  using Vertex2 = typename boost::graph_traits< Graph2 >::vertex_descriptor ;

  const Graph1 & myG1;
  graph_vertex_index_map graph_vertex_index;
  graph_vertex_position_map graph_vertex_position;
  VertexIndexMap & myIndexMap;

  my_vertex_copier(const Graph1& g1, Graph2& g2, VertexIndexMap & indexMap )
    : myG1( g1 ),
    graph_vertex_index( boost::get( boost::vertex_index_t(), g2 ) ),
    graph_vertex_position( boost::get( vertex_position_t(), g2) ),
    myIndexMap( indexMap )
  {}

  void operator()( const Vertex1& v1, const Vertex2& v2 ) const {
    vertex_position pos;
    pos.myP = v1;
    put( graph_vertex_position, v2, pos);
  }
};
template <typename Graph1, typename Graph2>
struct my_edge_copier {
  my_edge_copier(const Graph1& , Graph2& )
  {}
  template <typename Edge1, typename Edge2>
    void operator()(const Edge1& /*v1*/, Edge2& /*v2*/) const {
      // does nothing
    }
};


TEST_CASE_METHOD(Fixture_object_diamond_with_hole, "Basic Graph functions", "[interface]" ){
  GIVEN( "A diamond object with graph properties" ){
    THEN( "Vertices, Num Vertices" ){
      auto num_verts = boost::num_vertices(obj_fixture);
      auto verts = boost::vertices(obj_fixture);
      size_t count_verts{0};
      for(auto v = verts.first; v != verts.second; ++v, ++count_verts){};
      REQUIRE(count_verts == num_verts);
    }
    THEN( "Edges, Num Edges" ){
      auto num_edges = boost::num_edges(obj_fixture);
      auto edges = boost::edges(obj_fixture);
      size_t count_edges{0};
      for(auto v = edges.first; v != edges.second; ++v, ++count_edges){};
      REQUIRE(count_edges == num_edges);
    }
    THEN( "Out Edges, Out Degree, Degree, and Adjacencies of a vertex" ){
      // Map relating point and known degree in the diamond.
      std::map<Point, size_t> point_numedges;
      Point north{ 0 , 0 , 3 };
      point_numedges[north] = 5;

      Point x3{ 3 , 0 , 0 };
      point_numedges[x3] = 5;

      Point x1y1z1{ 1 , 1 , 1 };
      point_numedges[x1y1z1] = 15;

      Point cz2{ 0 , 0 , 2 };
      point_numedges[cz2] = 14;

      Point cz1{ 0 , 0 , 1 };
      point_numedges[cz1] = 21;

      for(auto && pm : point_numedges){
        auto out_edges = boost::out_edges(pm.first, obj_fixture);
        size_t count_edges{0};
        for(auto v = out_edges.first; v != out_edges.second; ++v, ++count_edges){};
        REQUIRE(count_edges == pm.second);
        auto out_degree = boost::out_degree(pm.first, obj_fixture);
        REQUIRE(out_degree == count_edges);
        auto degree = obj_fixture.degree(pm.first);
        REQUIRE(degree == out_degree);
        auto adj_vp = boost::adjacent_vertices(pm.first, obj_fixture);
        size_t count_verts{0};
        for(auto v = adj_vp.first; v != adj_vp.second; ++v, ++count_verts){};
        REQUIRE(count_verts == degree);
      }
    }
  }
}

TEST_CASE_METHOD(Fixture_object_diamond_with_hole, "Boost Graph Concepts", "[concepts]" ){
  GIVEN( "A diamond object with graph properties" ){
    using Graph = FixtureObject ;

    THEN( "Check Graph Concepts" ){

      BOOST_CONCEPT_ASSERT(( boost::VertexListGraphConcept<Graph> ));
      BOOST_CONCEPT_ASSERT(( boost::AdjacencyGraphConcept<Graph> ));
      BOOST_CONCEPT_ASSERT(( boost::IncidenceGraphConcept<Graph> ));
      BOOST_CONCEPT_ASSERT(( boost::EdgeListGraphConcept<Graph> ));
      // BOOST_CONCEPT_ASSERT(( boost::BidirectionalGraphConcept<Graph> ));
    }
  }
}

TEST_CASE_METHOD(Fixture_object_diamond_with_hole, "Breadth first visit and search", "[breadth]" ){
  GIVEN( "A diamond object with graph properties" ){
    using Graph = FixtureObject ;
    using vertex_descriptor = boost::graph_traits<Graph>::vertex_descriptor ; // ie Object::Vertex
    using vertex_iterator = boost::graph_traits<Graph>::vertex_iterator ;

    // get the property map for coloring vertices.
    using StdColorMap = std::map< vertex_descriptor, boost::default_color_type > ;
    StdColorMap colorMap;
    boost::associative_property_map< StdColorMap > propColorMap( colorMap );
    // get the property map for storing distances
    using StdDistanceMap = std::map< vertex_descriptor, uint64_t > ;
    StdDistanceMap distanceMap;
    boost::associative_property_map< StdDistanceMap > propDistanceMap( distanceMap );
    boost::queue< vertex_descriptor > Q; // std::queue does not have top().
    // Start in +z corner of diamond.
    vertex_descriptor start { Point{ 0, 0, 3 } };

    THEN( "Test IncidenceGraph interface with breadth_first_search" ){
      using PredecessorMap = std::map< vertex_descriptor, vertex_descriptor > ;
      PredecessorMap predecessorMap;
      boost::associative_property_map< PredecessorMap >
        propPredecessorMap( predecessorMap );

      boost::breadth_first_search(
         obj_fixture,
         start,
         Q,
         boost::make_bfs_visitor( boost::record_predecessors( propPredecessorMap, boost::on_tree_edge() ) ), // only record predecessors
         propColorMap  // necessary for the visiting vertices
         );

      INFO( "predecessorMap" );
      INFO( "starting point: " << *( obj_fixture.begin() ) );
      size_t visited{0};
      for(auto && v : predecessorMap){
        ++visited;
        INFO( v.first << " : " << v.second );
      }
      // +1 to count the starting point;
      CHECK((visited + 1) == obj_fixture.size());
    }

    THEN( "Test IncidenceGraph interface with breadth_first_visit" ){

      trace.beginBlock ( "Testing IncidenceGraph interface with breadth_first_visit..." );
      boost::breadth_first_visit // boost graph breadth first visiting algorithm.
        ( obj_fixture, // the graph
          start, // the starting vertex
          Q, // the buffer for breadth first queueing
          boost::make_bfs_visitor( boost::record_distances( propDistanceMap, boost::on_tree_edge() ) ), // only record distances
          propColorMap  // necessary for the visiting vertices
        );

      uint64_t maxD = 0;
      vertex_descriptor furthest = start;
      uint64_t nbV = 0;
      for ( std::pair<vertex_iterator, vertex_iterator>
          vp = boost::vertices( obj_fixture ); vp.first != vp.second; ++vp.first, ++nbV )
      {
        uint64_t d = boost::get( propDistanceMap, *vp.first );
        if ( d > maxD )
        {
          maxD = d;
          furthest = *vp.first;
        }
      }

      REQUIRE( nbV == obj_fixture.size() );
      trace.info() << "- Start: d[ " << start << " ] = " << boost::get( propDistanceMap, start) << std::endl;
      trace.info() << "- Furthest: d[ " << furthest << " ] = " << maxD << std::endl;
      CHECK( maxD == 6 );
      trace.endBlock();

      THEN( "Test Wagner Stoer min-cut"){

        using vertices_size_type = boost::graph_traits<Graph>::vertices_size_type ; // ie Object::Size
        using edge_descriptor = boost::graph_traits<Graph>::edge_descriptor ; // ie Object::Edge

        trace.beginBlock ( "Testing UndirectedGraph interface with Wagner-Stoer min cut ..." );
        // get the property map for weighting edges.
        using weight_type = double ;
        using StdWeightMap = std::map< edge_descriptor, weight_type > ;
        StdWeightMap weightMap;
        boost::associative_property_map< StdWeightMap > propWeightMap( weightMap );
        using StdVertexIndexMap = std::map< vertex_descriptor, vertices_size_type > ;
        StdVertexIndexMap vertexIndexMap;
        boost::associative_property_map< StdVertexIndexMap > propVertexIndexMap( vertexIndexMap );
        vertices_size_type idxV = 0;
        // The weight is smaller for edges traversing plane z=0 than anywhere else.
        // The min cut thus cuts the diamond in two approximate halves.
        for ( auto vp = boost::vertices( obj_fixture );
            vp.first != vp.second; ++vp.first, ++idxV )
        {
          vertex_descriptor v1 = *vp.first;
          vertexIndexMap[ v1 ] = idxV;
          for ( auto ve = boost::out_edges( v1, obj_fixture );
              ve.first != ve.second; ++ve.first )
          {
            auto v2 = boost::target( *ve.first, obj_fixture );
            if ( v1 < v2 )
            {
              weight_type weight = (
                  (v1[2] == Approx(0) && v2[2] != Approx(0) ) ||
                  (v2[2] == Approx(0) && v1[2] != Approx(0) )
                  ) ? 0.01 : 1.0;
              weightMap[ *ve.first ] = weight;
              weightMap[ obj_fixture.opposite( *ve.first ) ] = weight;
            }
          }
        }
        // get the parity map for assigning a set to each vertex.
        using StdParityMap = std::map< vertex_descriptor, bool > ;
        StdParityMap parityMap;
        boost::associative_property_map< StdParityMap > propParityMap( parityMap );

        weight_type total_weight =
          boost::stoer_wagner_min_cut // boost wagner stoer min cut algorithm.
          ( obj_fixture, // the graph
            propWeightMap, // the mapping edge -> weight
            boost::parity_map( propParityMap ) // this map stores the vertex assignation
            .vertex_index_map( propVertexIndexMap )
          );
        INFO( "- total weight = " << total_weight);
        uint64_t nb0 = 0;
        uint64_t nb1 = 0;
        for ( auto vp = boost::vertices( obj_fixture );
            vp.first != vp.second; ++vp.first, ++idxV )
        {
          vertex_descriptor v1 = *vp.first;
          if ( parityMap[ v1 ] ) ++nb1;
          else ++nb0;
        }
        trace.info() << "parityMap: True components: " << nb1 << " False: " << nb0 << std::endl;
        trace.info() << "- parity[ " << start << " ] = " << parityMap[ start ] << std::endl;
        trace.info() << "- parity[ " << furthest << " ] = " << parityMap[ furthest ] << std::endl;
        CHECK( parityMap[start] != parityMap[furthest]);
        CHECK( total_weight < 1.0);

        trace.endBlock();

        THEN( "Test Boykov-Kolmogorov max flow"){

          using edge_iterator = boost::graph_traits<Graph>::edge_iterator ;
          trace.beginBlock ( "Testing EdgeListGraph and IncidenceGraph interfaces with Boykov-Kolmogorov max flow ..." );
          using capacity_type = double ;
          // get the property map for edge capacity.
          using StdEdgeCapacityMap = std::map< edge_descriptor, weight_type > ;
          StdEdgeCapacityMap edgeCapacityMap;
          boost::associative_property_map< StdEdgeCapacityMap > propEdgeCapacityMap( edgeCapacityMap );
          // get the property map for edge residual capacity.
          using StdEdgeResidualCapacityMap = std::map< edge_descriptor, weight_type > ;
          StdEdgeResidualCapacityMap edgeResidualCapacityMap;
          boost::associative_property_map< StdEdgeResidualCapacityMap > propEdgeResidualCapacityMap( edgeResidualCapacityMap );
          // get the property map for reverse edge.
          using StdReversedEdgeMap = std::map< edge_descriptor, edge_descriptor > ;
          StdReversedEdgeMap reversedEdgeMap;
          boost::associative_property_map< StdReversedEdgeMap > propReversedEdgeMap( reversedEdgeMap );
          // get the property map for vertex predecessor.
          using StdPredecessorMap = std::map< vertex_descriptor, edge_descriptor > ;
          StdPredecessorMap predecessorMap;
          boost::associative_property_map< StdPredecessorMap > propPredecessorMap( predecessorMap );
          // We already have vertex color map, vertex distance map and vertex index map.
          uint64_t nbEdges = 0;
          // The weight is smaller for edges traversing plane z=0 than anywhere else.
          // The min cut thus cuts the diamond in two approximate halves.
          for ( std::pair<edge_iterator, edge_iterator>
              ve = boost::edges( obj_fixture ); ve.first != ve.second; ++ve.first, ++nbEdges )
          {
            edge_descriptor e = *ve.first;
            edge_descriptor rev_e = obj_fixture.opposite( e );
            vertex_descriptor v1 = boost::source( e, obj_fixture );
            vertex_descriptor v2 = boost::target( e, obj_fixture );
            ASSERT( boost::source( rev_e, obj_fixture ) == v2 );
            ASSERT( boost::target( rev_e, obj_fixture ) == v1 );
            if ( v1 < v2 )
            {
              capacity_type capacity = (
                  (v1[2] == Approx(0) && v2[2] != Approx(0) ) ||
                  (v2[2] == Approx(0) && v1[2] != Approx(0) )
                  ) ? 0.01 : 1.0;
              edgeCapacityMap[ e ] = capacity;
              edgeCapacityMap[ obj_fixture.opposite( e ) ] = capacity;
              reversedEdgeMap[ e ] = obj_fixture.opposite( e );
              reversedEdgeMap[ obj_fixture.opposite( e ) ] = e;
            }
          }
          trace.info() << "- nb edges = " << nbEdges << std::endl;
          distanceMap.clear();
          colorMap.clear();
          capacity_type max_flow =
            boost::boykov_kolmogorov_max_flow // boykov kolmogorov max flow algorithm.
            ( obj_fixture, // the graph
              propEdgeCapacityMap, propEdgeResidualCapacityMap,
              propReversedEdgeMap, propPredecessorMap, propColorMap, propDistanceMap, propVertexIndexMap,
              start, furthest );
          trace.info() << "- max flow = " << max_flow << std::endl;
          CHECK(abs(max_flow) == Approx(total_weight));
          trace.endBlock();
        }// maxflow
      }// mincut
    }// breath_visit
  }// given
}// scenario

TEST_CASE_METHOD(Fixture_object_diamond_with_hole, "Connected Components", "[connected]" ){
  GIVEN( "A diamond object with graph properties and an isolated vertex" ){
    using Graph = FixtureObject ;
    using vertex_descriptor = boost::graph_traits<Graph>::vertex_descriptor ; // ie Object::Vertex
    using edge_descriptor = boost::graph_traits<Graph>::edge_descriptor ; // ie Object::Edge
    using vertices_size_type = boost::graph_traits<Graph>::vertices_size_type ; // ie Object::Size

    // Add an isolated point in the domain.
    obj_fixture.pointSet().insertNew(FixtureObject::Point(0,0,7));

    THEN( "VertexListGraph interface with connected_components" ){
      // get the property map for labelling vertices.
      // get the property map for coloring vertices.
      using StdColorMap = std::map< vertex_descriptor, boost::default_color_type > ;
      StdColorMap colorMap;
      boost::associative_property_map< StdColorMap > propColorMap( colorMap );

      using StdComponentMap = std::map< vertex_descriptor, vertices_size_type > ;
      StdComponentMap componentMap;
      boost::associative_property_map< StdComponentMap > propComponentMap( componentMap );
      vertices_size_type nbComp =
        boost::connected_components // boost graph connected components algorithm.
        ( obj_fixture, // the graph
          propComponentMap, // the mapping vertex -> label
          boost::color_map( propColorMap ) // this map is used internally when computing connected components.
        );
      CHECK(nbComp == 2);

      THEN( "Filter graph and get components" ){
        using ComponentGraph =
          boost::filtered_graph<
          Graph,
          function<bool(edge_descriptor)>,
          function<bool(vertex_descriptor)>
            >;
        auto &g = obj_fixture;

        std::vector<ComponentGraph> component_graphs;

        for (size_t i = 0; i < nbComp; i++)
          component_graphs.emplace_back(g,
              [componentMap,i,&g](edge_descriptor e) {
              return componentMap.at(boost::source(e,g) )==i
              || componentMap.at(boost::target(e,g))==i;
              },
              [componentMap,i](vertex_descriptor v) {
              return componentMap.at(v)==i;
              });


        CHECK( component_graphs.size() == 2);
        std::vector<FixtureObject> obj_components;
        // Copying object and clear pointSet instead of creating from scratch. Lazy?
        FixtureObject obj_copy(obj_fixture);
        obj_copy.pointSet().clear();

        // Create new object from the component_graph.
      for (auto && c : component_graphs){
        obj_components.push_back(obj_copy);
        for (auto && vp = boost::vertices(c); vp.first != vp.second ; ++vp.first){
          obj_components.back().pointSet().insertNew(*vp.first);
        }
      }

      }// filtered_graph
    }// connected_components
  }//given
}//scenario


TEST_CASE_METHOD(Fixture_object_diamond_with_hole, "Copy graph", "[copy]" ){
  GIVEN( "A diamond object with graph properties" ){
    using Graph = FixtureObject ;
    using vertex_descriptor = boost::graph_traits<Graph>::vertex_descriptor ; // ie Object::Vertex
    using vertices_size_type = boost::graph_traits<Graph>::vertices_size_type ; // ie Object::Size
    THEN( "Test copy_graph"){

      using StdVertexIndexMap = std::map< vertex_descriptor, vertices_size_type > ;
      StdVertexIndexMap vertexIndexMap;
      boost::associative_property_map< StdVertexIndexMap > propVertexIndexMap( vertexIndexMap );
      using BGraph = boost::adjacency_list< boost::vecS, boost::vecS, boost::undirectedS, VertexProperties > ;
      BGraph bG;
      boost::copy_graph( obj_fixture, bG,
          boost::vertex_copy( my_vertex_copier<Graph,BGraph,StdVertexIndexMap>( obj_fixture, bG, vertexIndexMap ) )
          .edge_copy( my_edge_copier<Graph,BGraph>( obj_fixture, bG ) )
          .vertex_index_map( propVertexIndexMap )
          );
      using vertex_descriptor_2 = boost::graph_traits< BGraph >::vertex_descriptor ;
      using vertex_iterator_2 = boost::graph_traits< BGraph >::vertex_iterator ;
      using GraphVertexPositionMap = boost::property_map< BGraph, vertex_position_t>::type ;
      GraphVertexPositionMap vertexPos( boost::get( vertex_position_t(), bG) );
      for ( std::pair<vertex_iterator_2, vertex_iterator_2>
          vp = boost::vertices( bG ); vp.first != vp.second; ++vp.first )
      {
        vertex_descriptor_2 v1 = *vp.first;
        vertex_position pos = boost::get( vertexPos, v1 );
      }
      INFO("after copy: Boost graph has " << num_vertices( bG ) << " vertices.");
      CHECK(boost::num_vertices( bG ) == boost::num_vertices( obj_fixture ));

    }
  }
}


///////////////////////////////////////////////////////////////////////////////
