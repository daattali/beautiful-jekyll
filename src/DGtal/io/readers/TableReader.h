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
 * @file TableReader.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2013/11/30
 *
 * Header file for module TableReader.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(TableReader_RECURSES)
#error Recursive header files inclusion detected in TableReader.h
#else // defined(TableReader_RECURSES)
/** Prevents recursive inclusion of headers. */
#define TableReader_RECURSES

#if !defined TableReader_h
/** Prevents repeated inclusion of headers. */
#define TableReader_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/curves/FreemanChain.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class TableReader
  /**
   * Description of class 'TableReader' <p>
   *  \brief Aim: Implements method to read a set of numbers represented in each
   *line of a file.
   *
   *
   *  The main method to read a set of numbers where each number is
   * given in a single line. Each elements are identified between
   * space or tab characters. Blank line or line beginning with "#" are skipped.
   *
   *
   * Simple example:
   *
   *  @code
   *  #include "DGtal/helpers/StdDefs.h"
   *  #include "DGtal/io/readers/TableReader.h"
   *  ....
   *  string filename= "testFile.dat";
   *  vector<unsigned int> vectPoints = TableReader<unsigned
   *int>::getColumnElementsFromFile(filename);
   * @endcode
   * and you can specifying the point position:
   *  @code
   *  vector<unsigned int> vectPoints = TableReader<unsigned
   *int>::getColumnElementsFromFile(filename, 2);
   *  @endcode
   *
   * @see testTableReader.cpp
   * @tparam TQuantity the type fo the integer to be read.
   **/

  template <typename TQuantity>
  struct  TableReader
  {
    // ----------------------- Standard services ------------------------------
  public:
  /**
   * Method to import a vector containing a list of elements given
   * in an input stream. One element is extracted on each line of
   * the input stream.  Each elements are identified between space
   * or tab characters. Blank line or line beginning with "#" are
   * skipped.
   *
   * @param aFilename a file name
   * @param aPosition the position of indices where the element has to be
   *extracted.
   * @return a vector containing the set of elements.
   **/
  static std::vector<TQuantity>
  getColumnElementsFromFile( const std::string & aFilename,
                             unsigned int aPosition );

  /**
   * Method to import a vector containing a list of elements given
   * in a file. One element is extracted on each line of the input
   * file.  Each elements are identified between space or tab
   * characters. Blank line or line beginning with "#" are skipped.
   *
   * @param in the input file.
   * @param aPosition the position of indices where the elements has to be
   *extracted.
   * @return a vector containing the set of elements.
   **/

  static std::vector<TQuantity>
  getColumnElementsFromInputStream( std::istream & in, unsigned int aPosition );

  /**
   * Method to import a vector where each element contains the line
   * elements of a given file.  Each elements are identified between
   * space or tab characters. Blank line or line beginning with "#"
   * are skipped.
   *
   * @param aFilename the input file.
   * @return a vector containing a vector which contains each line elements.
   **/
  static std::vector<std::vector<TQuantity>>
  getLinesElementsFromFile( const std::string & aFilename );

  /**
   * Method to import a vector where each element contains the line
   * elements of a given file.  Each elements are identified between
   * space or tab characters. Blank line or line beginning with "#"
   * are skipped.
   *
   * @param in the input file.
   * @return a vector containing a vector which contains each line elements.
   **/

  static std::vector<std::vector<TQuantity>>
  getLinesElementsFromInputStream( std::istream & in );

  }; // end of class TableReader



} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/readers/TableReader.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined TableReader_h

#undef TableReader_RECURSES
#endif // else defined(TableReader_RECURSES)
