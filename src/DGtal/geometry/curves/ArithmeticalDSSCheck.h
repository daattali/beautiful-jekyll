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
 * @file ArithmeticalDSSCheck.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/10/28
 *
 * @brief Functions that checks the validity of instances of ArithmeticalDSS
 * @see ArithmeticalDSS
 *
 * This file is part of the DGtal library.
 */

#if defined(ArithmeticalDSSCheck_RECURSES)
#error Recursive header files inclusion detected in ArithmeticalDSSCheck.h
#else // defined(ArithmeticalDSSCheck_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ArithmeticalDSSCheck_RECURSES

#if !defined ArithmeticalDSSCheck_h
/** Prevents repeated inclusion of headers. */
#define ArithmeticalDSSCheck_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  //forward declaration of ArithmeticalDSS
  template <typename TCoordinate, 
	    typename TInteger, 
	    unsigned short adjacency>
  class ArithmeticalDSS; 

  namespace functions {

    /**
     * Checks the validity of the DSS when it contains only one point.
     * @param aDSS any DSS
     * @pre the DSS contains only one point
     * @return 'true' if the DSS is valid, 'false' otherwise.
     */
    template <typename TCoordinate, 
	      typename TInteger,  
	      unsigned short adjacency>
    bool checkOnePoint(const ArithmeticalDSS<TCoordinate, TInteger, adjacency>& aDSS);

    /**
     * Checks that the difference between two extremal
     * upper (resp. lower) leaning points is equal to the 
     * direction vector (a,b) scaled by an integer.
     * Checks that there is no pattern between end points
     * and extremal leaning points. 
     * @param aDSS any DSS
     * @pre the DSS contains more than one point, 
     * ie a and b are not both null. 
     * @return 'true' if ok, 'false' otherwise.
     */
    template <typename TCoordinate, 
	      typename TInteger,  
	      unsigned short adjacency>
    bool checkPointsPosition(const ArithmeticalDSS<TCoordinate, TInteger, adjacency>& aDSS); 

    /**
     * Checks the consistency between the parameters and 
     * the leaning points: first and last upper leaning points 
     * should have a remainder equal to mu while firsta and 
     * last lower leaning points should have a remainder equal to 
     * mu + omega - 1. Moreover, front and back points should have a 
     * remainder lying within the range [mu, mu+omega[. 
     * @param aDSS any DSS
     * @pre the DSS contains more than one point, 
     * ie a and b are not both null. 
     * @return 'true' if this property is fulfilled, 'false' otherwise.
     */
    template <typename TCoordinate, 
	      typename TInteger,  
	      unsigned short adjacency>
    bool checkPointsRemainder(const ArithmeticalDSS<TCoordinate, TInteger, adjacency>& aDSS);

    /**
     * Checks whether a DSS is valid or not.
     * NB: in logarithmic time (in order to check
     * that a and b are relatively prime)
     * @param aDSS any DSS
     * @return 'true' if valid, 'false' otherwise.
     */
    template <typename TCoordinate, 
	      typename TInteger,  
	      unsigned short adjacency>
    bool checkAll(const ArithmeticalDSS<TCoordinate, TInteger, adjacency>& aDSS);

  } //end namespace functions

} // end namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/ArithmeticalDSSCheck.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ArithmeticalDSSCheck_h

#undef ArithmeticalDSSCheck_RECURSES
#endif // else defined(ArithmeticalDSSCheck_RECURSES)
