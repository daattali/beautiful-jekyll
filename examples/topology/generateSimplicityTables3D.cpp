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
 * @file topology/generateSimplicityTables3D.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/06/22
 *
 * An example file named generateSimplicityTables3D. Creates precomputed
 * tables for determining whether some point is simple within an
 * object.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <DGtal/topology/tables/NeighborhoodTablesGenerators.h>

// For saving compressed tables.
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

int main( int argc, char** argv )
{
  using namespace Z3i;
  string error_message(
      "Select ForegroundAdjacency for object topology:\n"
      "- 26_6 \n"
      "- 18_6 \n"
      "- 6_18 \n"
      "- 6_26 \n");
  if (argc != 2 ){
    cout << error_message << std::endl;
    return 1;
  }
  std::string input_str = std::string(argv[1]);

  using ConfigMap = std::bitset<67108864> ; // 2^26
  // Too big for stack. Use heap instead.
  unique_ptr<ConfigMap> table(new ConfigMap);
  trace.beginBlock ( "Generate 3d table for " + input_str + " topology" );

  if (input_str == "26_6")
    functions::generateSimplicityTable< Object26_6, ConfigMap >( dt26_6, *table );
  else if (input_str == "18_6")
    functions::generateSimplicityTable< Object18_6, ConfigMap >( dt18_6, *table );
  else if (input_str == "6_18")
    functions::generateSimplicityTable< Object6_18, ConfigMap >( dt6_18, *table );
  else if (input_str == "6_26")
    functions::generateSimplicityTable< Object6_26, ConfigMap >( dt6_26, *table );
  else {
    cout << error_message << endl;
    return 1;
  }
  trace.endBlock();

  // string filename = "simplicity_table" + input_str + ".txt";
  // ofstream file( filename  );
  // file << *table;
  // file.close();
  {
    string filename = "simplicity_table" + input_str + ".zlib";
    ofstream file( filename );
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
