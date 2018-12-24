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
 * @file Morton.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/09/10
 *
 * Header file for module Morton.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Morton_RECURSES)
#error Recursive header files inclusion detected in Morton.h
#else // defined(Morton_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Morton_RECURSES

#if !defined Morton_h
/** Prevents repeated inclusion of headers. */
#define Morton_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <boost/array.hpp>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/kernel/CUnsignedNumber.h"
#include "DGtal/kernel/CIntegralNumber.h"
#include "DGtal/kernel/CInteger.h"

#include "DGtal/base/Bits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class Morton
  /**
   * Description of template class 'Morton' <p>
   * @brief Aim: Implements the binary Morton code construction in nD.
   *
   * Given a point in nD @f$(x_1,\ldots, x_n)@f$, a Morton code
   * consists in interleaving bits of @f$x_i@f$ coordinate values (plus a prefix
   * for the HashTree construction.
   *
   * Main methods in this class are keyFromCoordinates to generate a
   * key and CoordinatesFromKey to generate a point from a code.
   *
   * @tparam THashKey type to store the morton code (should have
   * enough capacity to store the interleaved binary word).
   * @tparam TPoint type of points. 
   *
   * @see testImageContainerByHashTree.cpp
   */
  template <typename THashKey, typename TPoint >
  class Morton
  {
  public:
    typedef THashKey HashKey;
    typedef TPoint Point;
    typedef typename Point::Coordinate Coordinate;

    BOOST_CONCEPT_ASSERT(( concepts::CUnsignedNumber<THashKey> ));
    BOOST_CONCEPT_ASSERT(( concepts::CIntegralNumber<THashKey> ));
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<Coordinate> ));

    BOOST_STATIC_CONSTANT(Dimension, dimension = TPoint::dimension);

    /**
     * Constructor
     *
     */
    Morton();
    
    /**
     * Interleave the bits of the nbIn inputs.
     * @param aPoint an array of the nbIn values to mix in.
     * @param output The result
     */ 
    void interleaveBits(const Point  & aPoint, HashKey & output) const;


    /**
     * Returns the key corresponding to the coordinates passed in the parameters.
     *
     * @param treeDepth The depth at which the coordinates are to be
     * read (usualy corresponds to the deepest leave).  
     *
     * @param coordinates An array containing the coordinates to
     * convert into a key.
     */
    HashKey keyFromCoordinates(const std::size_t treeDepth, const Point & coordinates) const;

    /**
     * Computes the coordinates correspponding to a key.
     *
     * @param key The key.
     * @param coordinates Will contain the resulting coordinates.
     */
    void coordinatesFromKey(const HashKey key, Point & coordinates) const;

    /**
     * Returns the parent key of a key passed in parameter.
     *
     * @param key The key.
     */ 
    inline HashKey parentKey(const HashKey key) const
    {
      return key >> dimension;
    }

    /**
     * Computes the brother keys (ie the keys having the same parent)
     * of the key passed in parameter.
     *
     * @param key The key.
     * @param result Will contain the resulting brother keys.
     */ 
    void brotherKeys(const HashKey key, HashKey* result ) const;

    
    /**
     * Computes the children keys of the key passed in parameter.
     *
     * @param key The key.
     * @param result Will contain the resulting children keys.
     */ 
    void childrenKeys(const HashKey key, HashKey* result ) const;
    
  private: 
    
    ///@todo Implements dilateMasks
    //boost::array< HashKey,LOG2<sizeof(HashKey)*8>::VALUE> myDilateMasks;
    //boost::array< HashKey,LOG2<sizeof(HashKey)*8>::VALUE> myContractMasks;
  };
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Includes inline functions
#include "DGtal/images/Morton.ih"

#endif // !defined Morton_h

#undef Morton_RECURSES
#endif // else defined(Morton_RECURSES)
