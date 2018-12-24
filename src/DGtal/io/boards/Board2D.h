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
 * @file Board2D.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/10/11
 *
 * Header file for module Board2D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Board2D_RECURSES)
#error Recursive header files inclusion detected in Board2D.h
#else // defined(Board2D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Board2D_RECURSES

#if !defined Board2D_h
/** Prevents repeated inclusion of headers. */
#define Board2D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "Board/Board.h"
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/io/Color.h"
//////////////////////////////////////////////////////////////////////////////



namespace DGtal
{
  /**
   * Specifies the drawing mode for domains.
   */
  enum DomainDrawMode { GRID = 0, PAVING = 1 };


  /////////////////////////////////////////////////////////////////////////////
  // class Board2D
  /**
   * Description of class 'Board2D' <p> \brief Aim: This class
   * specializes a 'Board' class so as to display DGtal objects more
   * naturally (with <<). The user has simply to declare a Board2D
   * object and uses stream operators to display most digital
   * objects. Furthermore, one can use this class to modify the current
   * style for drawing.
   */
  class Board2D : public LibBoard::Board
  {
    // ----------------------- local types ------------------------------
  public:
    /**
     * The associated map type for storing the default styles of
     * digital objects.
     */
    typedef std::map< std::string,CountedPtr<DrawableWithBoard2D> > StyleMapping;

    /**
     * The associated map type for storing possible modes used for
     * displaying for digital objects.
     */
    typedef std::map< std::string, std::string > ModeMapping;

    typedef LibBoard::Shape Shape;

    // ----------------------- Standard services ------------------------------
  public:
    
    /**
     * Destructor.
     */
    ~Board2D();
    
    /** 
     * Constructs a new board and sets the background color, if any.
     * 
     * @param aBackgroundColor A color for the drawing's background.
     */
    Board2D( const Color & aBackgroundColor = Color::None );

    /** 
     * Copy constructor.
     * 
     * @param other The object to be copied.
     */
    Board2D( const Board2D & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    Board2D & operator= ( const Board2D & other );

    /**
     * @param objectName the name of the object (generally obtained
     * with a 'object.className()').
     *
     * @return the current mode for the given object name or "" if no
     * specific mode has been set.
     */
    std::string getMode( const std::string & objectName ) const;

    /**
     * Draws the drawable [object] in this board. It should satisfy
     * the concept CDrawableWithBoard2D, which requires for instance a
     * method setStyle( Board2D & ).
     *
     * @param object any drawable object.
     * @return a reference on 'this'.
     */
    template <typename TDrawableWithBoard2D>
    Board2D & operator<<( const TDrawableWithBoard2D & object );


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

    // ------------------------- Public Datas ------------------------------
  public:
    /**
     * For instance, may associate a new style object T1 to the class
     * "HyperRectDomain": myStyles[ "HyperRectDomain" ] = T1.
     *
     * One can also store a new style T2 for a specific mode used for
     * drawing a class:  myStyles[ "HyperRectDomain/Paving" ] = T2.
     *
     * Modes may only be used in objects implementing the concept
     * CDrawableWithBoard2D.
     */
    StyleMapping myStyles;

    /**
     * May associate a current mode for a given class.
     * myModes[ "HyperRectDomain" ] = "Paving".
     *
     * Next display of a HyperRectDomain object will used the mode
     * "Paving".  Modes may only be used in objects implementing the
     * concept CDrawableWithBoard2D.
     */
    ModeMapping myModes;
    // ------------------------- Private Datas --------------------------------
  private:

  }; // end of class Board2D


  /**
   * Overloads 'operator<<' for displaying objects of class 'Board2D'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Board2D' to write.
   * @return the output stream after the writing.
   */
  std::ostream&
  operator<< ( std::ostream & out, const Board2D & object );

  /**
   * Base class specifying the methods for classes which intend to
   * modify a Board2D stream.
   * @todo merge DrawableWithBoard2D and DrawWithBoardModifier 
   */
  struct DrawWithBoardModifier {
    std::string className() const
    {
      return "DrawWithBoardModifier";
    }

    /*DrawableWithBoard2D* defaultStyle( std::string = "" ) const
    {
      return 0;
    }*/

    /*virtual void setStyle( Board2D &  ) const 
    {}*/
  };


  /**
   * Modifier class in a Board2D stream. Useful to choose your own
   * style for a given class. Realizes the concept
   * CDrawableWithBoard2D.
   */
  struct CustomStyle : public DrawWithBoardModifier {
    /**
     * @param classname the name of the class to which the style is associated.
     *
     * @param style a pointer on a dynamically allocated style, which
     * is acquired by the class.
     */
    CustomStyle( std::string classname, DrawableWithBoard2D* style )
      : myClassname( classname ), myStyle( style )
    {}

    std::string className() const
    {
      return "CustomStyle";
    }

    /*void setStyle( Board2D & board ) const
    {
      board.myStyles[ myClassname ] = myStyle;
    }*/

    std::string myClassname;
    CountedPtr<DrawableWithBoard2D> myStyle;
  };

  /**
   * @brief Modifier class in a Board2D stream. Useful to choose your own
   * mode for a given class. Realizes the concept
   * CDrawableWithBoard2D.
   */
  struct SetMode : public DrawWithBoardModifier {
    /**
     * @param classname the name of the class to which the style is associated.
     *
     * @param mode a pointer on a dynamically allocated style, which
     * is acquired by the class.
     */
    SetMode( std::string classname, std::string mode )
      : myClassname( classname ), myMode( mode )
    {}
    
    /*void setStyle( Board2D & board ) const
    {
      board.myModes[ myClassname ] = myMode;
    }*/
    
    std::string myClassname;
    std::string myMode;
  };

  /**
   * @brief  Custom style class redefining the pen color and the fill
   * color. You may use Board2D::Color::None for transparent color.
   *
   \code
   Board2D board;
   board << CustomColors( Board2D::Color::Red, Board2D::Color::None );
   ...
   \endcode
   * @see Board2D
   */
  struct CustomColors : public DrawableWithBoard2D
  {
    Color myPenColor;
    Color myFillColor;

    /**
     * Constructor.
     *
     * @param penColor specifies the pen color.
     * @param fillColor specifies the fill color.
     */
    CustomColors( const Color & penColor,
      const Color & fillColor )
      : myPenColor( penColor ), myFillColor( fillColor )
    {}
    
    virtual void setStyle( Board2D & aboard) const
    {
      aboard.setFillColor( myFillColor);
      aboard.setPenColor( myPenColor );
    }
  };

  /**
   * @brief Custom style class redefining the pen color. You may use
   * Board2D::Color::None for transparent color.
   *
   \code
   Board2D board;
   board << CustomPenColor( Board2D::Color::Green );
   ...
   \endcode
   * @see Board2D
   */
  struct CustomPenColor : public DrawableWithBoard2D
  {
    Color myPenColor;

    /**
     * Constructor.
     *
     * @param penColor specifies the pen color.
     */
    CustomPenColor( const Color & penColor )
      : myPenColor( penColor )
    {}
    
    virtual void setStyle( Board2D & aboard) const
    {
      aboard.setPenColor( myPenColor );
    }
  };

  /**
   * @brief Custom style class redefining the fill color. You may use
   * Board2D::Color::None for transparent color.
   *
   \code
   Board2D board;
   board << CustomFillColor( Board2D::Color::Green );
   ...
   \endcode
   * @see Board2D
   */
  struct CustomFillColor : public DrawableWithBoard2D
  {
    Color myFillColor;

    /**
     * Constructor.
     *
     * @param fillColor specifies the fill color.
     */
    CustomFillColor( const Color & fillColor )
      : myFillColor( fillColor )
    {}
    
    virtual void setStyle( Board2D & aboard) const
    {
      aboard.setFillColor( myFillColor );
    }
  };

  /**
   * @brief Custom style class redefining the pen attributes. You may use
   * Board2D::Color::None for transparent color.
   *
   \code
   Board2D board;
   board << CustomPen( Board2D::Color::Green, Board2D::Color::Black,
                       3.0 );
   ...
   \endcode
   * @see Board2D
   */
  struct CustomPen : public DrawableWithBoard2D
  {
    Color myPenColor;
    Color myFillColor;
    double myLineWidth;
    Board2D::Shape::LineStyle myLineStyle; /**< The line style (solid, dashed, etc.). */
    Board2D::Shape::LineCap myLineCap; /**< The linecap attribute. (The way line terminates.) */
    Board2D::Shape::LineJoin myLineJoin; /**< The linejoin attribute. (The shape of line junctions.) */
    int myDepth;        /**< The depth of the shape. */

    /**
     * Constructor.
     *
     * @param penColor specifies the pen color.
     * @param fillColor specifies the fill color.
     * @param lineWidth specifies the width of the drawing line.
     *
     * @param lineStyle specifies the drawing line style (SolidStyle,
     *      DashStyle, DotStyle, DashDotStyle, DashDotDotStyle,
     *      DashDotDotDotStyle )
     *  
     * @param lineCap specifies the drawing line cap (ButtCap,
     * RoundCap, SquareCap )
     *
     * @param lineJoin specifies the drawing line join (MiterJoin, RoundJoin, BevelJoin )
     *
     */
    CustomPen( const Color & penColor,
         const Color & fillColor,
         double lineWidth = 1.0,
         Board2D::Shape::LineStyle lineStyle = Board2D::Shape::SolidStyle,
         Board2D::Shape::LineCap lineCap = Board2D::Shape::ButtCap,
         Board2D::Shape::LineJoin lineJoin = Board2D::Shape::MiterJoin )
      : myPenColor( penColor ), myFillColor( fillColor ),
  myLineWidth( lineWidth ), 
  myLineStyle( lineStyle ), myLineCap ( lineCap ), myLineJoin( lineJoin )
    {}
    
    virtual void setStyle( Board2D & aboard) const
    {
      aboard.setPenColor( myPenColor );
      aboard.setFillColor( myFillColor );
      aboard.setLineWidth( myLineWidth );
      aboard.setLineStyle( myLineStyle );
      aboard.setLineCap( myLineCap );
      aboard.setLineJoin( myLineJoin );
    }
  };

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.

#include "DGtal/io/Display2DFactory.h"
#include "DGtal/io/Style2DFactory.h"
#include "DGtal/io/boards/Board2D.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Board2D_h

#undef Board2D_RECURSES
#endif // else defined(Board2D_RECURSES)
