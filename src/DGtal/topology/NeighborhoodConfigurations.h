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
 * @file NeighborhoodConfigurations.h
 *
 * @author Pablo Hernandez-Cerdan. Institute of Fundamental Sciences.
 * Massey University. Palmerston North, New Zealand
 *
 * @date 2018/01/01
 *
 * Generation of Look Up Tables for predicates function in a voxel
 * neighborhood.
 *
 * This file is part of the DGtal library.
 */

#if defined(NeighborhoodConfigurations_RECURSES)
#error Recursive header files inclusion detected in NeighborhoodConfigurations.h
#else // defined(NeighborhoodConfigurations_RECURSES)
/** Prevents recursive inclusion of headers. */
#define NeighborhoodConfigurations_RECURSES

#if !defined NeighborhoodConfigurations_h
/** Prevents repeated inclusion of headers. */
#define NeighborhoodConfigurations_h
//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <bitset>
#include <unordered_map>
#include "boost/dynamic_bitset.hpp"
#include <DGtal/base/CountedPtr.h>
#include <DGtal/topology/helpers/NeighborhoodConfigurationsHelper.h>

namespace DGtal {
  namespace functions {
  /**
   * Load existing look up table existing in file_name, precalculated
   * tables can be accessed including the header:
   * "DGtal/topology/tables/NeighborhoodTables.h"
   *
   * @param input_filename plain text containing the bool table.
   * @param known_size of the bitset, for 2D = 256 (2^8), 3D = 67108864 (2^26)
   * @param compressed true if table to read has been compressed with zlib.
   *
   * @return smart ptr of map[neighbor_configuration] -> bool
   *
   * @note The tables were calculated using the generateTableXXX examples.
   * Compressed files of the tables are distributed in the source code.
   * At build or install time, the header
   * "DGtal/topology/tables/NeighborhoodTables.h" is generated.
   * It has const strings variables with the file names of the tables.
   */
  inline
  DGtal::CountedPtr< boost::dynamic_bitset<> >
  loadTable(const std::string & input_filename, const unsigned int known_size, const bool compressed = true );

  /**
   * Load existing look up table existing in file_name, precalculated
   * tables can be accessed including the header:
   * "DGtal/topology/tables/NeighborhoodTables.h"
   *
   * @tparam dimension of the space input_filename table refers. 2 or 3
   * @param input_filename plain text containing the bool table.
   * @param compressed true if table to read has been compressed with zlib.
   *
   * @return smart ptr of map[neighbor_configuration] -> bool
   *
   * @see NeighborhoodConfigurations::loadTable
   */
  template<unsigned int dimension = 3>
  inline
  DGtal::CountedPtr< boost::dynamic_bitset<> >
  loadTable(const std::string & input_filename, const bool compressed = true);

  /**
   * Maps any point in the neighborhood of point Zero (0,..,0) to its
   * corresponding configuration bit mask. This is a helper to use with tables.
   * The order of the configuration is lexicographic, starting in {-1, -1, ...}.
   * @note the neighborhood is considered to be all points p which ||p-zero|| <= 1
   *
   * Example:
   * Point{ -1, -1, -1 } = 1; // corresponding to mask  x x 0000 0001
   * Point{  0, -1, -1 } = 2; // corresponding to mask  x x 0000 0010
   * Point{  1,  1,  1 } = 2^26; // x 0010 x x x x x x
   *
   * @note NeighborhoodConfiguration is type uint 32 bits,
   * so the max dimension supported is 3.
   *
   * @see HyperRectDomain_Iterator::nextLexicographicOrder
   * @see testNeighborhoodConfigurations.cpp shows the complete mapping.
   *
   * @tparam TPoint type of point to create map and input the desired dimension.
   *
   * @return map[Point]->configuration smart pointer.
   */
  template<typename TPoint>
  inline
  DGtal::CountedPtr<
  std::unordered_map<TPoint, NeighborhoodConfiguration > >
  mapZeroPointNeighborhoodToConfigurationMask();

  } // namespace functions
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/NeighborhoodConfigurations.ih"
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined NeighborhoodConfigurations_h

#undef NeighborhoodConfigurations_RECURSES
#endif // else defined(NeighborhoodConfigurations_RECURSES)
