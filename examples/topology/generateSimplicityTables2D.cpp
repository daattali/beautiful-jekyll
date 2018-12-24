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
 * @file topology/generateSimplicityTables2D.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/06/22
 *
 * An example file named generateSimplicityTables2D. Creates precomputed
 * tables for determining whether some point is simple within an
 * object.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include "DGtal/topology/tables/NeighborhoodTablesGenerators.h"
#include <vector>
#include "DGtal/shapes/Shapes.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/Color.h"

// For saving compressed tables.
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

/**
   Given a digital topology \a dt and a mapping configuration -> bool
   \a map, displays the simplicity tables in the given board.

   @tparam Object the type of object whose simpleness we wish to
   precompute. Includes the topology.

   @tparam Map the type used to store the mapping configuration -> bool.

   @param board (updated) the board where the tables are displayed.
   UNUSED_PARAM dt an instance of the digital topology.
   @param map the mapping configuration -> bool.
*/
template <typename Object, typename Map>
void
displaySimplicityTable( Board2D & board,
			const typename Object::DigitalTopology & /*dt*/,
			const Map & map )
{
  typedef typename Object::DigitalSet DigitalSet;
  typedef typename Object::Point Point;
  typedef typename DigitalSet::Domain Domain;
  typedef typename Domain::ConstIterator DomainConstIterator;

  Point p1 = Point::diagonal( -1 );
  Point p2 = Point::diagonal(  1 );
  Point c = Point::diagonal( 0 );
  Domain domain( p1, p2 );

  Point q1 = Point::diagonal( -1 );
  Point q2 = Point::diagonal( 4*16-1 );
  Domain fullDomain( q1, q2 );
  board << SetMode( fullDomain.className(), "Paving" );
  unsigned int cfg = 0;
  for ( unsigned int y = 0; y < 16; ++y )
    for ( unsigned int x = 0; x < 16; ++x, ++cfg )
      {
	bool simple = map[ cfg ];
	Point base( x*4, y*4 );
	unsigned int mask = 1;
	for ( DomainConstIterator it = domain.begin();
	      it != domain.end(); ++it )
	  {
	    Point q = base + (*it);
	    if ( *it == c )
	      board << CustomStyle( q.className(),
				    new CustomColors( Color( 0, 0, 0 ),
						      Color( 30, 30, 30 ) ) );
	    else
	      {
		if ( cfg & mask )
		  board <<
		    CustomStyle( q.className(),
				 simple
				 ? new CustomColors( Color( 0, 0, 0 ),
						     Color( 10, 255, 10 ) )
				 : new CustomColors( Color( 0, 0, 0 ),
						     Color( 255, 10, 10 ) ) );
		else
		  board <<
		    CustomStyle( q.className(),
				 simple
				 ? new CustomColors( Color( 0, 0, 0 ),
						     Color( 245, 255, 245 ) )
				 : new CustomColors( Color( 0, 0, 0 ),
						     Color( 255, 245, 245 ) ) );
		mask <<= 1;
	      }
	    board << q;
	  }
      }
}

/**
   Output simplicity configuration table as a C(++) array.
*/
template <typename Map>
void
outputTableAsArray( ostream & out,
		    const Map & map,
		    const string & tableName )
{
  typedef typename Map::const_iterator MapConstIterator;
  out << "const bool " << tableName << "[ " << map.size() << " ] = { ";
  for ( MapConstIterator it = map.begin(), it_end = map.end();
	it != it_end; )
    {
      out << *it;
      ++it;
      if ( it != it_end ) out << ", ";
    }
  out << " };" << std::endl;
}


int main( int /*argc*/, char** /*argv*/ )
{
  typedef std::vector<bool> ConfigMap;

  using namespace Z2i;
  trace.beginBlock ( "Generate 2d table for 4-8 topology" );
  ConfigMap table4_8( 256 );
  functions::generateSimplicityTable< Object4_8 >( dt4_8, table4_8 );
  trace.endBlock();

  trace.beginBlock ( "Generate 2d table for 8-4 topology" );
  ConfigMap table8_4( 256 );
  functions::generateSimplicityTable< Object8_4 >( dt8_4, table8_4 );
  trace.endBlock();

  Board2D board;
  trace.beginBlock ( "Display 2d table for 4-8 topology" );
  displaySimplicityTable< Object4_8 >( board, dt4_8, table4_8 );
  board.saveEPS( "table4_8.eps" );
  trace.endBlock();

  board.clear();
  trace.beginBlock ( "Display 2d table for 8-4 topology" );
  displaySimplicityTable< Object8_4 >( board, dt8_4, table8_4 );
  board.saveEPS( "table8_4.eps" );
  trace.endBlock();

  outputTableAsArray( std::cout, table4_8, "simplicityTable4_8" );
  outputTableAsArray( std::cout, table8_4, "simplicityTable8_4" );

  /* Output bitset tables to files,
   * for using with NeighborhoodConfigurations.h interface.
   * These tables can be accesed from NeighborhoodTables.h header.
   */
  using ConfigMapBit = std::bitset<256> ; // 2^8
  ConfigMapBit bit_table8_4;
  ConfigMapBit bit_table4_8;
  functions::generateSimplicityTable< Object8_4 >( dt8_4, bit_table8_4 );
  functions::generateSimplicityTable< Object4_8 >( dt4_8, bit_table4_8 );
  // string filename = "simplicity_table8_4.txt";
  // ofstream file1( filename );
  // file1 << bit_table8_4;
  // file1.close();
  {
    string filename = "simplicity_table8_4.zlib";
    ofstream file( filename );
    ConfigMapBit* table = &bit_table8_4;
    std::stringstream table_stream;
    table_stream << *table;
    namespace io = boost::iostreams;
    io::filtering_streambuf<io::input> filter;
    filter.push(io::zlib_compressor());
    filter.push(table_stream);
    io::copy(filter,file);
    file.close();
  }

  // string filename = "simplicity_table4_8.txt";
  // ofstream file2( filename );
  // file2 << bit_table4_8;
  // file2.close();
  {
    string filename = "simplicity_table4_8.zlib";
    ofstream file( filename );
    ConfigMapBit* table = &bit_table4_8;
    std::stringstream table_stream;
    table_stream << *table;
    namespace io = boost::iostreams;
    io::filtering_streambuf<io::input> filter;
    filter.push(io::zlib_compressor());
    filter.push(table_stream);
    io::copy(filter,file);
    file.close();
  }

  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
