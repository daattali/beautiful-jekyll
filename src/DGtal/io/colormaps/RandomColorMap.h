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
 * @file RandomColorMap.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/07/18
 *
 * Header file for module RandomColorMap.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(RandomColorMap_RECURSES)
#error Recursive header files inclusion detected in RandomColorMap.h
#else // defined(RandomColorMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define RandomColorMap_RECURSES

#if !defined RandomColorMap_h
/** Prevents repeated inclusion of headers. */
#define RandomColorMap_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class RandomColorMap
/**
 * Description of class 'RandomColorMap' <p>
 * \brief Aim: access to random color from a gradientColorMap
 *
 *
 */
class RandomColorMap
{
    // ----------------------- Standard services ------------------------------
public:


  typedef unsigned int Value;



  /**
   * Copy constructor.
   * @param other the object to clone.
   * Forbidden by default.
   */
  RandomColorMap ( const RandomColorMap & other );

  /**
   * Assignment.
   * @param anOther the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
  RandomColorMap & operator= ( const RandomColorMap & anOther );
  

  /**
   * Constructor from two unsigned intergers and two Colors.
   *
   **/
  
  RandomColorMap(const unsigned int &aFirstIndex, const unsigned int & aLastIndex, 
     const Color &aFirstColor=Color::White, const Color &aLastColor=Color::Red);


  //  RandomColorMap(const unsigned int &aFirstIndex, const unsigned int & aLastIndex);
  

  
  /** 
   * Adds a color to the list of color steps.
   * 
   * @param aColor A color.
   */
  void addColor( const Color & aColor ) ;
  

  /** 
   * Computes the color associated with a value in a given range.
   * 
   * @param aValue A value within the value range.
   * @return A random color identified by an unique [aValue] within the current range.
   */
  Color operator()( const unsigned int & aValue ) const;
  

   /** 
     * Returns the lower bound of the value range.
     *
     * @return The lower bound of the value range.
     */
    const unsigned int & min() const;

  /** 
     * Returns the upper bound of the value range.
     *
     * @return The upper bound of the value range.
     */
  const unsigned int  & max() const;


  /**
   * Destructor.
   */
  ~RandomColorMap();

    // ----------------------- Interface --------------------------------------
public:

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

    // ------------------------- Protected Datas ------------------------------
protected:
  unsigned int myMin;    /**< The lower bound of the value range.  */
  unsigned int myMax;            /**< The lower bound of the value range.  */

  
  
  
    // ------------------------- Private Datas --------------------------------
private:
  GradientColorMap<unsigned int> *myGradientMap;
  std::vector<unsigned int>  myColorIndex;
  std::vector<unsigned int>  myFreeColorIndex;
  
  
  void associateRandomIndexColor();
  
    // ------------------------- Hidden services ------------------------------
protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    RandomColorMap();

private:


    // ------------------------- Internals ------------------------------------
private:

}; // end of class RandomColorMap


/**
 * Overloads 'operator<<' for displaying objects of class 'RandomColorMap'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'RandomColorMap' to write.
 * @return the output stream after the writing.
 */
std::ostream&
operator<< ( std::ostream & out, const RandomColorMap & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/colormaps/RandomColorMap.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined RandomColorMap_h

#undef RandomColorMap_RECURSES
#endif // else defined(RandomColorMap_RECURSES)
