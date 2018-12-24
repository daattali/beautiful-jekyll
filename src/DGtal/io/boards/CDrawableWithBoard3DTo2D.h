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
 * @file CDrawableWithBoard3DTo2D.h
 * @author Aline Martin
 *
 * @date 2013/07/02
 *
 * Header file for concept CDrawableWithBoard3DTo2D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDrawableWithBoard3DTo2D_RECURSES)
#error Recursive header files inclusion detected in CDrawableWithBoard3DTo2D.h
#else // defined(CDrawableWithBoard3DTo2D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDrawableWithBoard3DTo2D_RECURSES

#if !defined CDrawableWithBoard3DTo2D_h
/** Prevents repeated inclusion of headers. */
#define CDrawableWithBoard3DTo2D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "boost/concept_check.hpp"
#include "DGtal/base/Common.h"
#include "DGtal/io/CDrawableWithDisplay3D.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
    /////////////////////////////////////////////////////////////////////////////
    // class CDrawableWithBoard3DTo2D
    /**
       Description of \b concept '\b CDrawableWithBoard3DTo2D' <p>
       @ingroup Concepts

       @brief Aim:  The concept CDrawableWithBoard3DTo2D specifies what are the classes
       that admit an export with Board3DTo2D.
    
       An object x satisfying this concept may then be used as:
    
       \code
       Board3DTo2D display;
       display << CustomStyle( x.className(), x.defaultStyle() )
               << x;
       \endcode 
   
       ### Refinement of
   
       ### Associated types :
   
       ### Notation
       - \a X : A type that is a model of CDrawableWithBoard3DTo2DD
       - \a x, \a y  : Object of type X
       - \a m  : a string of characters
   
       ### Definitions
   
       ### Valid expressions and semantics

       | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
       |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
       |the default draw style | x.defaultStyle( m = "") | mode \a m: \c std::string | CDrawableWithBoard3DTo2D | | returns a dynamic allocation of the default style for the model \a X in mode \a m | | |
       |the name of the model X | x.className() | | std::string | | returns a string telling the name of the model X | | |
       |the way the object \a x is drawn | x.setStyle(CDrawableWithBoard3DTo2D &display) | | | |draws the object \c x on the \c display stream | | |

       ### Invariants
   
       ### Models
       ArimeticalDSS, FreemanChain, HyperRectDomain, ImageContainerByHashTree, ImageContainerBySTLVector, PointVector, DigitalSetBySTLSet,DigitalSetBySTLVector, Object
   
       ### Notes
       @todo ImageContainerByHashTree does not implement setStyle(display &).
       @todo ImageContainerByHashTree does not implement defaultStyle(std::string&)const.
    */  
  
    template < class S, class KS> class Board3DTo2D;
  
    template <typename T, typename S, typename KS >
    struct CDrawableWithBoard3DTo2D : public concepts::CDrawableWithDisplay3D<T, S , KS>
    {

      BOOST_CONCEPT_USAGE( CDrawableWithBoard3DTo2D )
      {
        //Drawable model should have a className() returning a string
        concepts::ConceptUtils::sameType( myS, myT.className() );

        //Drawable model should be associated to global functions draw and defaultStyle.
        //draw(myD3D, myT);
        //concepts::ConceptUtils::sameType( myD, defaultStyle( myT) );
      }

      // ------------------------- Private Datas --------------------------------
    private:

      T myT;//! the drawable object
      DrawableWithBoard3DTo2D *myD;

      DGtal::Board3DTo2D<S, KS> myD3D;
      std::string myS;

      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CDrawableWithBoard3DTo2D
  } // namespace concepts
} // namespace DGtal



//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDrawableWithBoard3DTo2D_h

#undef CDrawableWithBoard3DTo2D_RECURSES
#endif // else defined(CDrawableWithBoard3DTo2D_RECURSES)
