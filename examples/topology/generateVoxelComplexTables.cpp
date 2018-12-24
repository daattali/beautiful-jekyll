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
 * @file generateVoxelComplexTables.cpp
 * @ingroup Examples
 * @author Pablo Hernandez-Cerdan (\c pablo.hernandez.cerdan@outlook.com)
 * Institute of Fundamental Sciences. Massey University.
 * Palmerston North, New Zealand
 *
 * @date 2018/01/01
 *
 * Creates precomputed tables for all possible configurations of the
 * neighborhood of a voxel in 3D with a topology of 26 neighbors.
 * The table is a map between all this configurations and the result of applying
 * an input selected predicate function to a center voxel.
 * The options for the functions are the Skel function from
 * @see VoxelComplexFunctions.h.
 *
 * The options are:
 *  skelFunction = functions::oneIsthmus<VoxelComplex>;
 *  skelFunction = functions::twoIsthmus<VoxelComplex>;
 *  skelFunction = functions::skelIsthmus<VoxelComplex>;
 *
 *  where the latest is equivalent to (oneIsthmus OR twoIsthmus)
 *
 *  Isthmuses are implemented to work with 3D cubical(voxel) complexes. Right now the tables are only generated with 26_6 topology, but other 3D topologies can be added.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/VoxelComplexFunctions.h"
#include "DGtal/topology/tables/NeighborhoodTablesGenerators.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////



int main( int argc, char** argv )
{
  typedef std::bitset<67108864> ConfigMap; // 2^26

  using namespace Z3i;
  using DigitalSet = DigitalSetByAssociativeContainer<
	    Domain, std::unordered_set< typename Domain::Point> >;
  using Object = Object<DT26_6, DigitalSet>;
  using VoxelComplex = VoxelComplex<KSpace, Object>;

  std::function< bool(
		 const VoxelComplex & ,
		 const typename VoxelComplex::Cell & )
	       > skelFunction;
  string error_message(
      "Provide one of the following arguments for select function:\n"
      "- skelIsthmus \n "
      "- oneIsthmus \n "
      "- twoIsthmus \n ");
  if (argc != 2 ){
    cout << error_message << std::endl;
    return 1;
  }
  std::string input_str = std::string(argv[1]);
  if (input_str == "skelIsthmus")
    skelFunction = functions::skelIsthmus<VoxelComplex>;
  else if (input_str == "oneIsthmus")
    skelFunction = functions::oneIsthmus<VoxelComplex>;
  else if (input_str == "twoIsthmus")
    skelFunction = functions::twoIsthmus<VoxelComplex>;
  else{
    cout << error_message << endl;
    return 1;
  }

  trace.beginBlock ( "Generate " + input_str + " table for 26_6 topology" );
  // Too big for stack. Use heap instead.
  auto table26_6 = make_shared<ConfigMap>();
  functions::generateVoxelComplexTable< VoxelComplex >(
      *table26_6,
      skelFunction );

  string filename = input_str + "_table26_6.txt";
  trace.info() << "Save to file... " + filename << std::endl;
  ofstream file26_6( filename );
  file26_6 << *table26_6;
  file26_6.close();

  trace.endBlock();

  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
