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
 * @file PointListReader.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/03/31
 *
 * Header file for module PointListReader.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(PointListReader_RECURSES)
#error Recursive header files inclusion detected in PointListReader.h
#else // defined(PointListReader_RECURSES)
/** Prevents recursive inclusion of headers. */
#define PointListReader_RECURSES

#if !defined PointListReader_h
/** Prevents repeated inclusion of headers. */
#define PointListReader_h

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
  // class PointListReader
  /**
   * Description of class 'PointListReader' <p> 
   *  \brief Aim: Implements method to read a set of points represented in each line of a file.
   *
   *
   *  The main method to read a set of points as a simple format where
   * each elements is represented in a single line. Blank line or line beginning with
   * "#" are skipped.
   *
   *  
   * Simple example:
   * 
   *  @code
   *  #include "DGtal/helpers/StdDefs.h"
   *  .... 
   *  string filename= "testFile.dat"; 
   *  vector<Z2i::Point> vectPoints = PointListReader<Z2i::Point>::getPointsFromFile(filename);
   * @endcode 
   * and you can specifying the point position:
   *  @code
   vector<unsigned int> vIndice;
   vIndice.push_back(1); // select for X coordinate the second position number of the line.
   vIndice.push_back(2); // select for Y coordinate the third position number of the line.
   vector<Z2i::Point> vectPoints = PointListReader<Z2i::Point>::getPointsFromFile(filename,vectPos);
   *  @endcode
   *   
   * @see testPointListReader.cpp
   **/

  template <typename TPoint>
  struct  PointListReader
  {
    // ----------------------- Standard services ------------------------------
  public:

    /** 
     * Main method to import a vector containing a list of points
     * defined in a file where each line defines a point. 
     * Blank line or line beginning with
     * "#" are skipped.
     * 
     * @param in the input stream.
     * @param aVectPosition used to specify the position of indices of
     * value points  (default set to 0,..,dimension).
     * @return a vector containing the set of points.
     **/
    static std::vector< TPoint>  
    getPointsFromInputStream (std::istream &in, 
            std::vector<unsigned int> aVectPosition=std::vector<unsigned int>());
  

    /** 
     * Main method to import a vector containing a list of points
     * defined in a file where each line defines a point.  Blank line
     * or line beginning with "#" are skipped.
     *
     * @param filename a filename 
     * @param aVectPosition used to specify the position of indices of
     * value points  (optional: default set to 0,..,dimension) 
     * @return a vector containing the set of points.
     **/
    static std::vector< TPoint>  
    getPointsFromFile (const std::string &filename, 
           std::vector<unsigned int>  aVectPosition=std::vector<unsigned int>());
  




    /** 
     * Import a vector containing all polygons defined on each line of
     * a given file.
     * 
     * 
     * @param [in] filename input filename 
     * @return a vector containing the vector of polygons.
     **/
  
    static std::vector<std::vector< TPoint> >  
    getPolygonsFromFile (const std::string &filename);
  
  
    /** 
     * Import a vector containing all polygons defined on each line of
     * a given istream.
     * 
     * 
     * @param in the input stream.  
     * @return a vector containing the vector of polygons.
     **/
    static std::vector<std::vector< TPoint> >  
    getPolygonsFromInputStream ( std::istream &in );
  
  


    /** 
     * Main method to FreemanChain contours.  Each line of the file
     * should represent a FreemanChain
     * 
     * @param [in] filename  the input filename
   
     * @return the vector containing the set of FreemanChain.
     **/
    template < typename TInteger > 
    static std::vector< FreemanChain< TInteger > > 
    getFreemanChainsFromFile (const std::string &filename);
  
  
  

  }; // end of class PointListReader



} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/readers/PointListReader.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined PointListReader_h

#undef PointListReader_RECURSES
#endif // else defined(PointListReader_RECURSES)
