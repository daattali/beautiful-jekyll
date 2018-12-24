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
 * @file
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2015/04/06
 *
 * Header file for module TickedColorMap.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(TickedColorMap_RECURSES)
#error Recursive header files inclusion detected in TickedColorMap.h
#else // defined(TickedColorMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define TickedColorMap_RECURSES

#if !defined TickedColorMap_h
/** Prevents repeated inclusion of headers. */
#define TickedColorMap_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "DGtal/base/Common.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/CColorMap.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  
  /////////////////////////////////////////////////////////////////////////////
  // template class TickedColorMap
  /**
   * Description of template class 'TickedColorMap' <p>
   *
   * @brief Aim: This class adapts any colormap to add "ticks" in the
   * colormap colors.
   *
   * Ticks are characterized by a position and a width in the adapted
   * colormap range. When the value falls in a tick, the colormap color is
   * replaced by the color provided in the constructor.
   *
   * For example, on a colormap, this class can be used to create white
   * ticks with regular spacing, or locate zero-crossing of a curvature map
   * for instance (i.e. with a single tick at zero).
   *
   * This class is a model of concepts::CColorMap.
   *
   * @tparam TValue The type of the range values.
   * @tparam TColorMap The type of colormap to Adapt (the value type of TColorMap must be TValue).
   *
   */
  template <typename TValue, typename TColorMap>
  class TickedColorMap
  {
    
  public:
    
    ///Value type
    typedef TValue Value;
    
    ///Adapted colormap type.
    typedef TColorMap ColorMap;
    
    BOOST_CONCEPT_ASSERT(( concepts::CColorMap<ColorMap> )) ;
    BOOST_STATIC_ASSERT(( concepts::ConceptUtils::SameType<Value, typename ColorMap::Value>::value));
    
    // ----------------------- Standard services ------------------------------
  public:
    
    /**
     * Constructor.
     *
     * @pre aMin < aMax.
     *
     * @param aMin The lower bound of the value range.
     * @param aMax The upper bound of the value range.
     * @param color the color of the ticks.
     */
    TickedColorMap(const Value & aMin,
                   const Value & aMax,
                   const Color &color = Color::White );
    
    /**
     * Constructor from colormap
     *
     * @pre aMin < aMax.
     *
     * @param other the background colormap (copied).
     * @param color the color of the ticks.
     */
    TickedColorMap( const ColorMap & other,
                    const Color &    color = Color::White );
    
    /**
     * Computes the color associated with a value in a given range.
     *
     * @note This operation has a complexity in @f$ log(N)@f$ where
     * @f$ N@f$ is the number of ticks.
     *
     * @param value A value within the value range.
     * @return A color.
     */
    Color operator()( const Value & value ) const;
    
    /**
     * Destructor.
     */
    ~TickedColorMap();
    
    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    TickedColorMap ( const TickedColorMap & other );
    
    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    TickedColorMap & operator= ( const TickedColorMap & other );
    
    // ----------------------- Interface --------------------------------------
  public:
    
    /**
     * Add a tick at a given position of the
     * range [myMin, myMax].
     *
     * @param position tick position.
     * @param thickness tick thickness.
     */
    void addTick(const Value position,
                 const Value thickness);
    
    /**
     * Add regularly spaced ticks in the range [myMin,myMax].
     *
     * @param nbTicks the number of regular ticks.
     * @param thickness ticks thickness.
     */
    void addRegularTicks(const unsigned int nbTicks,
                         const Value thickness);
    
    /**
     * Finalize the insert ticks (this will sort the tick vector).
     * This method must be called before any color access if you
     * change the tick set.
     *
     */
    void finalize();
    
    /**
     * @return a pointer to the underlying colormap
     */
    ColorMap * colormap() const
    {
      return myColorMap;
    }
    
    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;
    
    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;
    
    /**
     * Returns the lower bound of the value range.
     *
     * @return The lower bound of the value range.
     */
    const Value & min() const;
    
    /**
     * Returns the upper bound of the value range.
     *
     * @return The upper bound of the value range.
     */
    const Value & max() const;
    
    
    // ------------------------- Hidden services ------------------------------
  protected:
    
    Value myMin;    /**< The lower bound of the value range.  */
    Value myMax;           /**< The lower bound of the value range.  */
    ColorMap *myColorMap;  /**< Underlying colormap. */
    Color myTickColor; /**< The tick color. */
    
    ///Sorted vector of ticks.
    std::vector< std::pair<Value,Value> > myTicks;
    
    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    TickedColorMap();
    
  }; // end of class TickedColorMap2d
  
  
  /**
   * Overloads 'operator<<' for displaying objects of class 'TickedColorMap'.
   * @param out the output stream where the object is written.
   * @param object te output stream after the writing.
   */
  template <typename TValue, typename CMAP >
  std::ostream&
  operator<< ( std::ostream & out, const TickedColorMap<TValue,CMAP> & object );
  
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/colormaps/TickedColorMap.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined TickedColorMap_h

#undef TickedColorMap_RECURSES
#endif // else defined(TickedColorMap_RECURSES)
