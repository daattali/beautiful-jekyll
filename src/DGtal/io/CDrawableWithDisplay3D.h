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
 * @file CDrawableWithDisplay3D.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/08/08
 *
 * Header file for concept CDrawableWithDisplay3D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDrawableWithDisplay3D_RECURSES)
#error Recursive header files inclusion detected in CDrawableWithDisplay3D.h
#else // defined(CDrawableWithDisplay3D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDrawableWithDisplay3D_RECURSES

#if !defined CDrawableWithDisplay3D_h
/** Prevents repeated inclusion of headers. */
#define CDrawableWithDisplay3D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "boost/concept_check.hpp"
#include "DGtal/base/Common.h"
//#include "DGtal/io/Display3D.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
    /////////////////////////////////////////////////////////////////////////////
    // class CDrawableWithDisplay3D
    /**
       Description of \b concept '\b CDrawableWithDisplay3D' <p>
       @ingroup Concepts

       @brief Aim:  The concept CDrawableWithDisplay3D specifies what are the classes
       that admit an export with Display3D.
    
       An object x satisfying this concept may then be used as:
    
       \code
       Display3D display;
       display << CustomStyle( x.className(), x.defaultStyle() )
               << x;
       \endcode 
   
       ### Refinement of
   
       ### Associated types :
   
       ### Notation
       - \a X : A type that is a model of CDrawableWithDisplay3DD
       - \a x, \a y  : Object of type X
       - \a m  : a string of characters
   
       ### Definitions
   
       ### Valid expressions and semantics

       | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
       |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
       |the default draw style | x.defaultStyle( m = "") | mode \a m: \c std::string | CDrawableWithDisplay3D | | returns a dynamic allocation of the default style for the model \a X in mode \a m | | |
       |the name of the model X | x.className() | | std::string | | returns a string telling the name of the model X | | |
       |the way the object \a x is drawn | x.setStyle(CDrawableWithDisplay3D &display) | | | |draws the object \c x on the \c display stream | | |  

       ### Invariants
   
       ### Models
       ArimeticalDSS, FreemanChain, HyperRectDomain, ImageContainerByHashTree, ImageContainerBySTLVector, PointVector, DigitalSetBySTLSet,DigitalSetBySTLVector, Object
   
       ### Notes
       @todo ImageContainerByHashTree does not implement setStyle(display &).
       @todo ImageContainerByHashTree does not implement defaultStyle(std::string&)const.
    */  
  
    template < class S, class KS> class Display3D;
  
    template <typename T, typename Sp, typename KSp>
    struct CDrawableWithDisplay3D
    {

      BOOST_CONCEPT_USAGE( CDrawableWithDisplay3D )
      {
        //Drawable model should have a className() returning a string
        concepts::ConceptUtils::sameType( myS, myT.className() );

        //Drawable model should be associated to global functions draw and defaultStyle.
        //draw(myD3D, myT);
        //concepts::ConceptUtils::sameType( myD, defaultStyle( myT) );
      }

      // ------------------------- Private Datas --------------------------------
    private:

      T myT; //! the drawable class
      DrawableWithDisplay3D *myD;

      DGtal::Display3D< Sp, KSp> myD3D;
      std::string myS;

      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CDrawableWithDisplay3D
  }//namespace concepts
} // namespace DGtal



//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDrawableWithDisplay3D_h

#undef CDrawableWithDisplay3D_RECURSES
#endif // else defined(CDrawableWithDisplay3D_RECURSES)
