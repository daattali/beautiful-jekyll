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
 * @file CDrawableWithBoard2D.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/10/21
 *
 * Header file for concept CDrawableWithBoard2D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDrawableWithBoard2D_RECURSES)
#error Recursive header files inclusion detected in CDrawableWithBoard2D.h
#else // defined(CDrawableWithBoard2D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDrawableWithBoard2D_RECURSES

#if !defined CDrawableWithBoard2D_h
/** Prevents repeated inclusion of headers. */
#define CDrawableWithBoard2D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions

#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/Display2DFactory.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  ///Forward declaration
  class Board2D;
  namespace concepts
  {
   
    /////////////////////////////////////////////////////////////////////////////
    // class CDrawableWithBoard2D
    /**
       Description of \b concept '\b CDrawableWithBoard2D' <p>
       @ingroup Concepts
     
       @brief Aim:  The concept CDrawableWithBoard2D specifies what are the classes
       that admit an export with Board2D.

       An object x satisfying this concept may then be used as:
     
       \code
       Board2D board;
       board << CustomStyle( x.className(), x.defaultStyle() )
             << x;
       \endcode 
   
       ### Refinement of
   
       ### Associated types :
   
       ### Notation
       - \a X : A type that is a model of CDrawableWithBoard2D
       - \a x, \a y  : Object of type X
       - \a m  : a string of characters
   
       ### Definitions
   
       ### Valid expressions and semantics
   
       | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
       |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
       |the default draw style | x.defaultStyle( m ="" ) | \a mode \a m: \c std::string | DrawableWithBoard2D | | returns a dynamic allocation of the default style for the model \a X in mode \a m | | |
       |the name of the model  | x.className()           |  | std::string | | returns a string telling the name of the model | | |
       |the way the objet \a x is drawn | x.setStyle(Board2D &board) | | | | draws the object \c x on the \a board stream | | |
   
       ### Invariants
   
       ### Models
       ArithmeticalDSSComputer, FreemanChain, HyperRectDomain, ImageContainerByHashTree, ImageContainerBySTLVector, PointVector, DigitalSetBySTLSet,DigitalSetBySTLVector, Object
   
       ### Notes
       @todo ImageContainerByHashTree does not implement setStyle(Board2D &).
       @todo ImageContainerByHashTree does not implement defaultStyle(std::string&)const.
    */
    template <typename T>
    struct CDrawableWithBoard2D
    {
      // ----------------------- Concept checks ------------------------------
    public:
      BOOST_CONCEPT_USAGE( CDrawableWithBoard2D )
      {
        //Drawable model should have a className() returning a string
        concepts::ConceptUtils::sameType( myS, myT.className() );

        //Drawable model should be associated to global functions draw and defaultStyle.
        DGtal::Display2DFactory::draw(myB, myT);
        concepts::ConceptUtils::sameType( myD, defaultStyle( myT) );
      }

      // ------------------------- Private Datas --------------------------------
    private:
      T myT;
      DrawableWithBoard2D *myD;
      Board2D myB;
      std::string myS;
    
      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CDrawableWithBoard2D
  }// namespace concepts
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDrawableWithBoard2D_h

#undef CDrawableWithBoard2D_RECURSES
#endif // else defined(CDrawableWithBoard2D_RECURSES)
