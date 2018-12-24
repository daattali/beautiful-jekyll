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
 * @file testNeighborhoodConfigurations.cpp
 * @ingroup Tests
 *
 * @author Pablo Hernandez-Cerdan. Institute of Fundamental Sciences.
 * Massey University. Palmerston North, New Zealand
 *
 * @date 2018/01/01
 *
 * Testing classs of NeighborhoodConfigurations
 * @see NeighborhoodConfigurations.h
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include "DGtalCatch.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/base/Common.h"
#include "DGtal/topology/NeighborhoodConfigurations.h"
#include "DGtal/topology/tables/NeighborhoodTables.h"
using namespace std;
using namespace DGtal;
using namespace DGtal::functions;

template <typename TObject>
TObject
Object3D(const typename TObject::DigitalTopology &dt)
{
  using namespace DGtal;
  using namespace Z3i;
  Point p1( -10, -10, -10 );
  Point p2( 10, 10, 10 );
  Domain domain( p1, p2 );
  Point c( 0, 0, 0 );
  Point r( 3, 0, 0 );
  DigitalSet diamond_set( domain );
  for ( auto it = domain.begin(); it != domain.end(); ++it )
  {
    if ( (*it - c ).norm1() <= 3 ) diamond_set.insertNew( *it );
  }
  diamond_set.erase( c );
  KSpace K;
  K.init( domain.lowerBound(),
      domain.upperBound(), true);

  return TObject(dt, diamond_set);
}

TEST_CASE("Check that each neighborhood point in 3D (26 points) has associated a bit in an unsigned integer (NeighborhoodConfiguration).", "[map][mask][3D]" )
{
    using namespace Z3i;
    using Map = unordered_map<Point, NeighborhoodConfiguration>;
    auto pointToMask3D =
        mapZeroPointNeighborhoodToConfigurationMask< typename Object26_6::Point >();
    Map truth3D;
    truth3D[Point{ -1, -1, -1 }] = 1;        // 0000 x x 0000 x x 0000 0001
    truth3D[Point{  0, -1, -1 }] = 2;        // x x x x x x x 0010
    truth3D[Point{  1, -1, -1 }] = 4;        // x x x x x x x 0100
    truth3D[Point{ -1,  0, -1 }] = 8;        // x x x x x x x 1000
    truth3D[Point{  0,  0, -1 }] = 16;       // x x x x x x 0001 x
    truth3D[Point{  1,  0, -1 }] = 32;       // x x x x x x 0010 x
    truth3D[Point{ -1,  1, -1 }] = 64;       // x x x x x x 0100 x
    truth3D[Point{  0,  1, -1 }] = 128;      // x x x x x x 1000 x
    truth3D[Point{  1,  1, -1 }] = 256;      // x x x x x 0001 x x
    truth3D[Point{ -1, -1,  0 }] = 512;      // x x x x x 0010 x x
    truth3D[Point{  0, -1,  0 }] = 1024;     // x x x x x 0100 x x
    truth3D[Point{  1, -1,  0 }] = 2048;     // x x x x x 1000 x x
    truth3D[Point{ -1,  0,  0 }] = 4096;     // x x x x 0001 x x x
    truth3D[Point{  1,  0,  0 }] = 8192;     // x x x x 0010 x x x
    truth3D[Point{ -1,  1,  0 }] = 16384;    // x x x x 0100 x x x
    truth3D[Point{  0,  1,  0 }] = 32768;    // x x x x 1000 x x x
    truth3D[Point{  1,  1,  0 }] = 65536;    // x x x 0001 x x x x
    truth3D[Point{ -1, -1,  1 }] = 131072;   // x x x 0010 x x x x
    truth3D[Point{  0, -1,  1 }] = 262144;   // x x x 0100 x x x x
    truth3D[Point{  1, -1,  1 }] = 524288;   // x x x 1000 x x x x
    truth3D[Point{ -1,  0,  1 }] = 1048576;  // x x 0001 x x x x x
    truth3D[Point{  0,  0,  1 }] = 2097152;  // x x 0010 x x x x x
    truth3D[Point{  1,  0,  1 }] = 4194304;  // x x 0100 x x x x x
    truth3D[Point{ -1,  1,  1 }] = 8388608;  // x x 1000 x x x x x
    truth3D[Point{  0,  1,  1 }] = 16777216; // x 0001 x x x x x x
    truth3D[Point{  1,  1,  1 }] = 33554432; // x 0010 x x x x x x
    CHECK(*pointToMask3D == truth3D);

}
SCENARIO("Simplicity tables match on-the-fly calculations for all 3D topologies", "[simple][object][diamond][3D]" )
{
  auto mapZeroNeighborhoodToMask = mapZeroPointNeighborhoodToConfigurationMask<Z3i::Point>();
  using namespace Z3i;

  SECTION("26_6 topology using loadTable from string and default table size (2^26)"){
    auto obj = Object3D<Object26_6>(dt26_6);
    const auto & filename = simplicity::tableSimple26_6;
    auto ptable = loadTable( filename );
    CHECK(ptable->size() == 67108864);
    const auto & table = *ptable;
    auto & objSet = obj.pointSet();
    size_t nsimples{0};
    size_t nsimples_tables{0};
    for( const auto & p : objSet){
        auto simple = obj.isSimple(p);
        if( simple ) ++nsimples;
        auto cfg = obj.getNeighborhoodConfigurationOccupancy(p, *mapZeroNeighborhoodToMask);
        auto simple_from_table = table[cfg];
        if( simple_from_table ) ++nsimples_tables;
        INFO("Point: " <<  p << " cfg: " << cfg);
        CHECK(simple == simple_from_table);
    }
    CHECK(nsimples == nsimples_tables);
    auto border_size = obj.border().size();
    CHECK(nsimples == border_size);
  }
  SECTION("18_6 topology using load table with explicit size (2^26)"){
    auto obj = Object3D<Object18_6>(dt18_6);
    const auto & filename = simplicity::tableSimple18_6;
    // known_size is 2^26 (default)
    auto ptable = loadTable(filename, 67108864);
    const auto & table = *ptable;
    auto & objSet = obj.pointSet();
    size_t nsimples{0};
    size_t nsimples_tables{0};
    for( const auto & p : objSet){
        auto simple = obj.isSimple(p);
        if( simple ) ++nsimples;
        auto cfg = obj.getNeighborhoodConfigurationOccupancy(p, *mapZeroNeighborhoodToMask);
        auto simple_from_table = table[cfg];
        if( simple_from_table ) ++nsimples_tables;
        INFO("Point: " <<  p << " cfg: " << cfg);
        CHECK(simple == simple_from_table);
    }
    CHECK(nsimples == nsimples_tables);
    auto border_size = obj.border().size();
    CHECK(nsimples == border_size);
  }

  SECTION("6_26 topology using loadTable with template parameter N=3 (dimension)"){
    auto obj = Object3D<Object6_26>(dt6_26);
    const auto & filename = simplicity::tableSimple6_26;
    auto ptable = loadTable<3>(filename);
    const auto & table = *ptable;
    auto & objSet = obj.pointSet();
    size_t nsimples{0};
    size_t nsimples_tables{0};
    for( const auto & p : objSet){
        auto simple = obj.isSimple(p);
        if( simple ) ++nsimples;
        auto cfg = obj.getNeighborhoodConfigurationOccupancy(p, *mapZeroNeighborhoodToMask);
        auto simple_from_table = table[cfg];
        if( simple_from_table ) ++nsimples_tables;
        INFO("Point: " <<  p << " cfg: " << cfg);
        CHECK(simple == simple_from_table);
    }
    CHECK(nsimples == nsimples_tables);

    auto border_size = obj.border().size();
    CHECK(nsimples != border_size);
  }

  SECTION("6_18 topology"){
    auto obj = Object3D<Object6_18>(dt6_18);
    const auto & filename = simplicity::tableSimple6_18;
    auto ptable = loadTable(filename);
    const auto & table = *ptable;
    auto & objSet = obj.pointSet();
    size_t nsimples{0};
    size_t nsimples_tables{0};
    for( const auto & p : objSet){
        auto simple = obj.isSimple(p);
        if( simple ) ++nsimples;
        auto cfg = obj.getNeighborhoodConfigurationOccupancy(p, *mapZeroNeighborhoodToMask);
        auto simple_from_table = table[cfg];
        if( simple_from_table ) ++nsimples_tables;
        INFO("Point: " <<  p << " cfg: " << cfg);
        CHECK(simple == simple_from_table);
    }
    CHECK(nsimples == nsimples_tables);

    auto border_size = obj.border().size();
    CHECK(nsimples != border_size);
  }
}


struct Objects2D{
  using Object8_4 = DGtal::Z2i::Object8_4;
  using Object4_8 = DGtal::Z2i::Object4_8;
  Object8_4 obj8_4;
  Object4_8 obj4_8;

  Objects2D()
  {
    using namespace DGtal;
    using namespace Z2i;
    Point p1( -17, -17 );
    Point p2( 17, 17 );
    Domain domain( p1, p2 );
    DigitalSet shape_set( domain );
    Shapes<Domain>::addNorm1Ball( shape_set, Point( -10, -8 ), 7 );
    Shapes<Domain>::addNorm1Ball( shape_set, Point( 10, 8 ), 7 );
    Shapes<Domain>::addNorm1Ball( shape_set, Point( 3, 0 ), 6 );
    Shapes<Domain>::addNorm1Ball( shape_set, Point( 0, -3 ), 7 );
    Shapes<Domain>::addNorm1Ball( shape_set, Point( -10, 0 ), 6 );
    Shapes<Domain>::addNorm1Ball( shape_set, Point( -8, 8 ), 6 );
    Shapes<Domain>::addNorm1Ball( shape_set, Point( 0, 9 ), 6 );
    Shapes<Domain>::addNorm1Ball( shape_set, Point( 15, -2 ), 6 );
    Shapes<Domain>::addNorm1Ball( shape_set, Point( 12, -10 ), 4 );
    shape_set.erase( Point( 5, 0 ) );
    shape_set.erase( Point( -1, -2 ) );
    obj8_4 = Object8_4( dt8_4, shape_set );
    obj4_8 = Object4_8( dt4_8, shape_set );
  }

};

TEST_CASE("Check that each neighborhood point in 2D (8 points) has associated a bit in an unsigned integer (NeighborhoodConfiguration).", "[map][mask][2D]" )
{
    using namespace Z2i;
    using Map = unordered_map<Point, NeighborhoodConfiguration>;
    auto pointToMask2D =
        mapZeroPointNeighborhoodToConfigurationMask< typename Object8_4::Point >();
    Map truth2D;
    truth2D[Point{ -1, -1 }] = 1;   // 0000 x x 0000 x x 0000 0001
    truth2D[Point{  0, -1 }] = 2;   // x x x x x x x 0010
    truth2D[Point{  1, -1 }] = 4;   // x x x x x x x 0100
    truth2D[Point{ -1,  0 }] = 8;   // x x x x x x x 1000
    truth2D[Point{  1,  0 }] = 16;  // x x x x x x 0001 x
    truth2D[Point{ -1,  1 }] = 32;  // x x x x x x 0010 x
    truth2D[Point{  0,  1 }] = 64;  // x x x x x x 0100 x
    truth2D[Point{  1,  1 }] = 128; // x x x x x x 1000 x

    CHECK(*pointToMask2D == truth2D);
}

TEST_CASE_METHOD(Objects2D, "Simplicity tables match on-the-fly calculations for all 2D topologies", "[simple][object][balls][2D]" )
{
  auto mapZeroNeighborhoodToMask = mapZeroPointNeighborhoodToConfigurationMask<Z2i::Point>();

  SECTION("8_4 and 4_8 topologies using loadTable with specific table size (2^8) and with template parameter N=2 (dimension)"){
    // 8_4
    {
      const auto & filename = simplicity::tableSimple8_4;
      auto ptable = loadTable(filename, 256);
      const auto & table = *ptable;
      auto & obj = obj8_4;
      auto & objSet = obj.pointSet();
      size_t nsimples{0};
      size_t nsimples_tables{0};
      for( const auto & p : objSet){
        auto simple = obj.isSimple(p);
        if( simple ) ++nsimples;
        auto cfg = obj.getNeighborhoodConfigurationOccupancy(p, *mapZeroNeighborhoodToMask);
        auto simple_from_table = table[cfg];
        if( simple_from_table ) ++nsimples_tables;
        INFO("Point: " <<  p << " cfg: " << cfg);
        CHECK(simple == simple_from_table);
      }
      CHECK(nsimples == nsimples_tables);
    }

    // 4_8
    {
      const auto & filename = simplicity::tableSimple4_8;
      auto ptable = loadTable<2>(filename);
      CHECK(ptable->size() == 256);
      const auto & table = *ptable;
      auto & obj = obj4_8;
      auto & objSet = obj.pointSet();
      size_t nsimples{0};
      size_t nsimples_tables{0};
      for( const auto & p : objSet){
        auto simple = obj.isSimple(p);
        if( simple ) ++nsimples;
        auto cfg = obj.getNeighborhoodConfigurationOccupancy(p, *mapZeroNeighborhoodToMask);
        auto simple_from_table = table[cfg];
        if( simple_from_table ) ++nsimples_tables;
        INFO("Point: " <<  p << " cfg: " << cfg);
        CHECK(simple == simple_from_table);
      }
      CHECK(nsimples == nsimples_tables);
    }
  }
}

SCENARIO( "Load isthmus tables", "[isthmus]" ){
  SECTION("isthmus"){
    const auto & filename = isthmusicity::tableIsthmus;
    auto ptable = loadTable(filename);
    const auto & table = *ptable;
  }
  SECTION("oneIsthmus"){
    const auto & filename = isthmusicity::tableOneIsthmus;
    auto ptable = loadTable(filename);
    const auto & table = *ptable;
  }
  SECTION("twoIsthmus"){
    const auto & filename = isthmusicity::tableTwoIsthmus;
    auto ptable = loadTable(filename);
    const auto & table = *ptable;
  }
}
