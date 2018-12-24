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
 * @file AngleComputer.h
 *
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @author (backported by) Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/08/31
 *
 * Header file for module AngleComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(AngleComputer_RECURSES)
#error Recursive header files inclusion detected in AngleComputer.h
#else // defined(AngleComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define AngleComputer_RECURSES

#if !defined AngleComputer_h
/** Prevents repeated inclusion of headers. */
#define AngleComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /**
   * A simple class to perform angle computations. All angles are in [0:2pi[
   */
  struct AngleComputer 
  {
    /**
     * @param i any angle.
     * @return the corresponding angle in [0:2pi[
     */
     static float cast( float i );
    
    /**
     * Less comparator modulo. Be careful, modulo comparisons have no
     * sense when the absolute difference of the values are around pi.
     *
     * @param i any angle in [0:2pi[
     * @param j any angle in [0:2pi[
     * @return 'true' if [i] strictly precedes [j] in a window 'pi'.
     */
     static bool less( float i, float j );

    /**
     * Performs j - i modulo 2pi, assuming less(i,j) is true.
     *
     * @param j any angle in [0:2pi[
     * @param i any angle in [0:2pi[
     * @return the value j - i, always positive. 
     */
     static float posDiff( float j, float i );

    /**
     * Performs j - i, assuming th result is in [-pi:pi[
     *
     * @param j any angle in [0:2pi[
     * @param i any angle in [0:2pi[
     * @return the value j - i, always positive. 
     */
     static float deviation( float j, float i );

    /**
     * Equivalent to 'less( i, j ) ? i : j'.
     *
     * @param i any angle in [0:2pi[
     * @param j any angle in [0:2pi[
     * @return the smallest angle of [i] and [j] in a window 'pi'.
     */
    static float min( float i, float j );

    /**
     * Equivalent to 'less( i, j ) ? j : i'.
     *
     * @param i any angle in [0:2pi[
     * @param j any angle in [0:2pi[
     * @return the greatest angle of [i] and [j] in a window 'pi'.
     */
    static float max( float i, float j );


    /**
     * @param i any angle.
     * @return the corresponding angle in [0:2pi[
     */
    static double cast( double i );
    
    /**
     * Less comparator modulo. Be careful, modulo comparisons have no
     * sense when the absolute difference of the values are around pi.
     *
     * @param i any angle in [0:2pi[
     * @param j any angle in [0:2pi[
     * @return 'true' if [i] strictly precedes [j] in a window 'pi'.
     */
    static bool less( double i, double j );

    /**
     * Performs j - i modulo 2pi, assuming less(i,j) is true.
     *
     * @param j any angle in [0:2pi[
     * @param i any angle in [0:2pi[
     * @return the value j - i, always positive. 
     */
    static double posDiff( double j, double i );

    /**
     * Performs j - i, assuming th result is in [-pi:pi[
     *
     * @param j any angle in [0:2pi[
     * @param i any angle in [0:2pi[
     * @return the value j - i, always positive. 
     */
    static double deviation( double j, double i );

    /**
     * Equivalent to 'less( i, j ) ? i : j'.
     *
     * @param i any angle in [0:2pi[
     * @param j any angle in [0:2pi[
     * @return the smallest angle of [i] and [j] in a window 'pi'.
     */
    static double min( double i, double j );

    /**
     * Equivalent to 'less( i, j ) ? j : i'.
     *
     * @param i any angle in [0:2pi[
     * @param j any angle in [0:2pi[
     * @return the greatest angle of [i] and [j] in a window 'pi'.
     */
    static double max( double i, double j );

    
  };

 
  

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/math/AngleComputer.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined AngleComputer_h

#undef AngleComputer_RECURSES
#endif // else defined(AngleComputer_RECURSES)
