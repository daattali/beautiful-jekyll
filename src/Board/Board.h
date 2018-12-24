/* -*- mode: c++ -*- */
/**
 * @file   Board.h
 * @author Sebastien Fourey <http://www.greyc.ensicaen.fr/~seb>
 * @date   Sat Aug 18 2007
 * 
 * @brief  
 */
/*
 * \@copyright This File is part of the Board library which is
 * licensed under the terms of the GNU Lesser General Public Licence.
 * See the LICENCE file for further details.
 */
#ifndef _BOARD_BOARD_H_
#define _BOARD_BOARD_H_

#include <ostream>
#include <string>
#include <vector>

#include "Board/Point.h"
#include "Board/Path.h"
#include "Board/Shapes.h"
#include "Board/ShapeList.h"

#include "DGtal/io/Color.h"

namespace LibBoard {
  
/** 
 * The Board class.
 * @brief Class for EPS, FIG or SVG drawings.
 * @version 0.5
 */
class Board : public ShapeList {
  
public:
  
  // cairo
  enum CairoType { CairoPDF, CairoPNG, CairoPS, CairoEPS, CairoSVG };

  enum PageSize { BoundingBox, A4, Letter };
  enum Unit { UPoint, UInche, UCentimeter, UMillimeter };
  static const double Degree;
  
  /** 
   * Constructs a new board and sets the background color, if any.
   * 
   * @param backgroundColor A color for the drawing's background.
   */
  Board( const DGtal::Color & backgroundColor = DGtal::Color::None );

  /** 
   * Copy constructor.
   * 
   * @param other The object to be copied.
   */
  Board( const Board & other );

  ~Board();

  /** 
   * The operator =
   * 
   * @param other The object to be copied.
   * 
   * @return A reference to the left operand.
   */
  Board & operator=( const Board & other );


  /** 
   * Add a shape to the board, using the current unit factor.
   * 
   * @param shape A shape. (Might be a list of shapes, actually!)
   * 
   * @return The board itself, as a ShapeList.
   */
  Board & operator<<( const Shape & shape );

  /** 
   * Overloaded operator to set the current unit.
   * 
   * @param unit The unit to be used in next drawing functions and shape insertions.
   * 
   * @return The board itself, as a ShapeList.
   */
  Board & operator<<( Unit unit );
  
  /** 
   * Clears the board with a given background color.
   * 
   * @param color The board background color (may be Color::None).
   */
  void clear( const DGtal::Color & color = DGtal::Color::None );

  /** 
   * Clears the board and set the background color from an RGB triple.
   * 
   * @param red red
   * @param green green
   * @param blue blue
   */
  void clear( unsigned char red, unsigned char green, unsigned char blue );

  Shape & rotate( double angle, const Point & center );

  Shape & rotate( double angle );

  Shape & translate( double dx, double dy );

  Shape & scale( double sx, double sy );

  Shape & scale( double s );

  Board rotated( double angle, const Point & center );

  Board rotated( double angle );

  Board translated( double dx, double dy );

  Board scaled( double sx, double sy );

  Board scaled( double s );

  /** 
   * Set the unit used by the drawSomething methods.
   * 
   * @param unit The unit to be used in { PT, IN, CM, MM }.
   */
  void setUnit( Unit unit );

  /** 
   * Set the unit used by the drawSomething methods.
   * 
   * @param factor The factor of the unit.
   * @param unit The unit to be used in { PT, IN, CM, MM }.
   */
  void setUnit( double factor, Unit unit );

  /** 
   * Draws a dot at coordinates (x,y).
   * 
   * @param x First coordinate of the dot.
   * @param y Second coordinate of the dot.
   * @param depthValue Depth of the line.
   */
  void drawDot( double x, double y, int depthValue = -1 );

  /** 
   * Draws a line from (x1,y1) to (x2,y2).
   * 
   * @param x1 First coordinate of the first extremity.
   * @param y1 Second coordinate of the first extremity.
   * @param x2 First coordinate of the second extremity.
   * @param y2 Second coordinate of the second extremity.
   * @param depthValue Depth of the line.
   */
  void drawLine( double x1, double y1, double x2, double y2, 
     int depthValue = -1 );

  /** 
   * Draws a quadratic Bezier curve from (x1,y1) to (x3,y3), 
   * with (x2,y2) as middle control point. 
   * 
   * @param x1 First coordinate of the first point.
   * @param y1 Second coordinate of the first point.
   * @param x2 First coordinate of the middle point.
   * @param y2 Second coordinate of the middle point.
   * @param x3 First coordinate of the last point.
   * @param y3 Second coordinate of the last point.
   * @param depthValue Depth of the line.
   */
  void drawQuadraticBezierCurve( double x1, double y1, double x2, double y2, double x3, double y3,  
     int depthValue = -1 ); 

  /** 
   * Draws a line from (x1,y1) to (x2,y2) with an arrow at (x2,y2).
   * 
   * @param x1 First coordinate of the first extremity.
   * @param y1 Second coordinate of the first extremity.
   * @param x2 First coordinate of the second extremity.
   * @param y2 Second coordinate of the second extremity.
   * @param filled Whether or not the arrow is filled.
   * @param depthValue Depth of the line.
   */
  void drawArrow( double x1, double y1, double x2, double y2,
      bool filled = true,
      int depthValue = -1 );

  /** 
   * Draws a triangle.
   * 
   * @param x1 First coordinate of the first vertex.
   * @param y1 Second coordinate of the first vertex.
   * @param x2 First coordinate of the second vertex.
   * @param y2 Second coordinate of the second vertex.
   * @param x3 First coordinate of the third vertex.
   * @param y3 Second coordinate of the third vertex.
   * @param depthValue Depth of the triangle.
   */
  void drawTriangle( double x1, double y1, 
         double x2, double y2, 
         double x3, double y3, 
         int depthValue = -1 );

  /** 
   * Draws a triangle.
   * 
   * @param p1 First vertex.
   * @param p2 Second vertex.
   * @param p3 Third vertex.
   * @param depthValue Depth of the triangle.
   */
  void drawTriangle( const Point & p1,
         const Point & p2, 
         const Point & p3, 
         int depthValue = -1 );


  /** 
   * Draws an arc.
   * 
   * @param x First coordinate of the arc center. 
   * @param y Second coordinate of the arc center.
   * @param radius arc radius.
   * @param angle1 first angle.
   * @param angle2 second angle.
   * @param neg neg
   * @param depthValue Depth of the arc.
   */
  void drawArc(double x, double y, double radius, double angle1, double angle2, 
	       bool neg, int depthValue = -1 );
  
  /** 
   * Draws a filled triangle.
   * 
   * @param x1 First coordinate of the first vertex.
   * @param y1 Second coordinate of the first vertex.
   * @param x2 First coordinate of the second vertex.
   * @param y2 Second coordinate of the second vertex.
   * @param x3 First coordinate of the third vertex.
   * @param y3 Second coordinate of the third vertex.
   * @param depthValue Depth of the triangle.
   */
  void fillTriangle( double x1, double y1, 
         double x2, double y2, 
         double x3, double y3, 
         int depthValue = -1 );

  /** 
   * Draws a triangle with Gouraud-like shaded colors. 
   * 
   * @param p1 p1
   * @param color1 color1
   * @param p2 p2
   * @param color2  color2
   * @param p3 p3
   * @param color3 color3 
   * @param divisions number of triangle subdivisions.
   * @param depthValue The depth of the triangle.
   */
  void fillGouraudTriangle( const Point & p1,
          const DGtal::Color & color1,
          const Point & p2,
          const DGtal::Color & color2,
          const Point & p3,
          const DGtal::Color & color3,
          unsigned char divisions = 3,
          int depthValue = -1 );

  /** 
   * Draws a triangle with Gouraud-like shaded colors. 
   * 
   * @param x1 x1
   * @param y1 y1
   * @param color1 color1
   * @param x2 x2
   * @param y2 y2
   * @param color2 color2
   * @param x3 x3
   * @param y3 y3
   * @param color3 color3
   * @param divisions number of subdivisions
   * @param depthValue depth
   */
  void fillGouraudTriangle( const double x1, const double y1,
          const DGtal::Color & color1,
          const double x2, const double y2, 
          const DGtal::Color & color2,
          const double x3, const double y3,
          const DGtal::Color & color3,
          unsigned char divisions = 3,
          int depthValue = -1 );
  
  /** 
   * Draws a triangle with a Gouraud-like shaded color according to
   * the current fill color and a brightness value given for each vertex. 
   * @param p1 p1
   * @param brightness1 brightness1
   * @param p2 p2
   * @param brightness2 brightness2
   * @param p3 p3
   * @param brightness3 brightness3
   * @param divisions number of triangle subdivisions.
   * @param depthValue The depth of the triangle.
   */
  void fillGouraudTriangle( const Point & p1,
          const float brightness1,
          const Point & p2,
          const float brightness2,
          const Point & p3,
          const float brightness3,
          unsigned char divisions = 3,
          int depthValue = -1 );

  /** 
   * Draws a triangle with a Gouraud-like shaded color according to
   * the current fill color and a brightness value given for each vertex. 
   * 
   * @param x1 x1
   * @param y1 y1
   * @param brightness1 b1
   * @param x2 x2
   * @param y2 y2
   * @param brightness2 b2
   * @param x3 x3
   * @param y3 y3
   * @param brightness3 b3
   * @param divisions number of sudivisions
   * @param depthValue depth
   */
  void fillGouraudTriangle( const double x1, const double y1,
          const float brightness1,
          const double x2, const double y2, 
          const float brightness2,
          const double x3, const double y3,
          const float brightness3,
          unsigned char divisions = 3,
          int depthValue = -1 );
  

  /** 
   * Draws a filled triangle.
   * 
   * @param p1 First vertex.
   * @param p2 Second vertex.
   * @param p3 Third vertex.
   * @param depthValue Depth of the triangle.
   */
  void fillTriangle( const Point & p1,
         const Point & p2, 
         const Point & p3, 
         int depthValue = -1 );
  
  /** 
   * Draws a rectangle.
   * 
   * @param x First coordinate of the upper left corner.
   * @param y Second coordinate of the upper left corner.
   * @param width Width of the rectangle.
   * @param height Height of the rectangle.
   * @param depthValue Depth of the rectangle.
   */
  void drawRectangle( double x, double y, 
          double width, double height,
          int depthValue = -1 );
  /** 
   * Draws an image.
   * 
   * @param filename filename
   * @param x First coordinate of the upper left corner.
   * @param y Second coordinate of the upper left corner.
   * @param width Width of the rectangle.
   * @param height Height of the rectangle.
   * @param depthValue Depth of the rectangle.
   * @param alpha Transparency used in the image display.
   */
  void drawImage( std::string filename, double x, double y, 
          double width, double height,
      int depthValue = -1, double alpha=1.0 );

  /** 
   * Draws a rectangle filled with the current pen color.
   * 
   * @param x First coordinate of the upper left corner.
   * @param y Second coordinate of the upper left corner.
   * @param width Width of the rectangle.
   * @param height Height of the rectangle.
   * @param depthValue Depth of the rectangle.
   */
  void fillRectangle( double x, double y,
          double width, double height,
          int depthValue = -1 );

  /** 
   * Draws a circle.
   * 
   * @param x First coordinate of the circle's center.
   * @param y Second coordinate of the circle's center.
   * @param radius Radius of the circle.
   * @param depthValue Depth of the circle.
   */
  void drawCircle( double x, double y, double radius,
       int depthValue = -1 );
 
  /** 
   * Draws a circle filled with the current pen color.
   * 
   * @param x First coordinate of the circle's center.
   * @param y Second coordinate of the circle's center.
   * @param radius Radius of the circle.
   * @param depthValue Depth of the circle.
   */
  void fillCircle( double x, double y, double radius,
       int depthValue = -1);

  /** 
   * Draws an ellipse.
   * 
   * @param x First coordinate of the circle's center.
   * @param y Second coordinate of the circle's center.
   * @param xRadius Radius of the circle.
   * @param yRadius Radius of the circle.
   * @param depthValue Depth of the circle.
   */
  void drawEllipse( double x, double y, 
        double xRadius, double yRadius,
        int depthValue = -1);
 
  /** 
   * Draws an ellipse filled with the current pen color.
   * 
   * @param x First coordinate of the circle's center.
   * @param y Second coordinate of the circle's center.
   * @param xRadius X axis radius of the ellipse.
   * @param yRadius Y axis radius of the ellipse.
   * @param depthValue Depth of the circle.
   */
  void fillEllipse( double x, double y, 
        double xRadius, double yRadius,
        int depthValue = -1);

  /** 
   * Draws a polygonal line.
   * 
   * @param points A vector of points.
   * @param depthValue The depth of the polyline.
   */
  void drawPolyline( const std::vector<Point> & points,
         int depthValue = -1 );
  
  /** 
   * Draws a closed polygonal line.
   * 
   * @param points A vector of points.
   * @param depthValue The depth of the polyline.
   */
  void drawClosedPolyline( const std::vector<Point> & points,
         int depthValue = -1 );

  /** 
   * Draws a filled polygon.
   * 
   * @param points A vector of points.
   * @param depthValue The depth of the polygon.
   */
  void fillPolyline( const std::vector<Point> & points,
         int depthValue = -1 );
    
  /** 
   * Draws a string of text.
   * 
   * @param x The first coordinates of the lower left corner.
   * @param y The second coordinates of the lower left corner.
   * @param text The text. 
   * @param depthValue The depth of the text.
   */
  void drawText( double x, double y, const char * text, 
     int depthValue = -1 );

  /** 
   * Draws a string of text.
   * 
   * @param x The first coordinates of the lower left corner.
   * @param y The second coordinates of the lower left corner.
   * @param str The text. 
   * @param depthValue The depth of the text.
   */
  void drawText( double x, double y, 
                 const std::string & str, 
     int depthValue = -1 );

  /** 
   * Changes the current font and font size.
   *
   * @param font The name of the font.
   * @param fontSize The new font size. (The unit is 1pt = 1/72 in).
   * @return The board itself.
   */
  Board & setFont( const Fonts::Font font, double fontSize );
  
  /** 
   * Changes the font size.
   * 
   * @param fontSize The new font size.  (The unit is 1pt = 1/72 in).
   * @return The board itself.
   */
  Board & setFontSize( double fontSize ); 

  /** 
   * Changes the current pen color.
   * 
   * @param red Red component.
   * @param green Green component.
   * @param blue Blue component.
   * @param alpha alpha component.
   * @return The board itself.
   */
  Board & setPenColorRGBi( unsigned char red,
         unsigned char green,
         unsigned char blue,
         unsigned char alpha = 255 );

  /** 
   * Changes the current pen color.
   * 
   * @param red Red
   * @param green green
   * @param blue blue
   * @param alpha alpha
   * @return The board itself.
   */  
  Board & setPenColorRGBf(  float red,
          float green,
          float blue, 
          float alpha = 1.0f );

  /** 
   * Changes the current pen color.
   *
   * In order to use no pen, one may set the pen color to Color::None. 
   * @param color The pen color.
   * @return The board itself.
   */
  Board & setPenColor( const DGtal::Color & color );
  

  /** 
   * Changes the current fill color.
   * 
   * @param red Red component.
   * @param green Green component.
   * @param blue Blue component.
   * @param alpha The opacity. 
   * @return The board itself.
   */
  Board & setFillColorRGBi( unsigned char red,
          unsigned char green,
          unsigned char blue,
          unsigned char alpha = 255 );
  
  /** 
   * Changes the current fill color.
   * 
   * @param red Red component.
   * @param green Green component.
   * @param blue Blue component.
   * @param alpha The opacity.
   * @return The board itself.
   */
  Board & setFillColorRGBf( float red, float green, float blue, float alpha = 1.0f );

  /** 
   * Changes the current fill color.
   * 
   * In order to use no fill color, one may set this color to Color::None. 
   * @param color The fill color.
   * @return The board itself.
   */
  Board & setFillColor( const DGtal::Color & color );
  
  /** 
   * Changes the current line thickness (1/72 inche unit).
   * 
   * @param width The new line thickness.
   * @return The board itself.
   */
  Board & setLineWidth( double width );

  /** 
   * Changes the current line style.
   * 
   * @param style The new line style.
   * @return The board itself.
   */
  Board & setLineStyle( Shape::LineStyle style );
  
  /** 
   * Set the line cap style. 
   * 
   * @param cap The cap-style which can be Shape::ButtCap, 
   * Shape::RoundCap or Shape::SquareCap.
   * 
   * @return The board itself.
   */  
  Board & setLineCap( Shape::LineCap cap ); 
 
  /** 
   * Set the line joine style. 
   * 
   * @param join The join-style which can be Shape::MiterJoin, 
   * Shape::RoundJoin or Shape::BevelJoin.
   * 
   * @return The board itself.
   */  
  Board & setLineJoin( Shape::LineJoin join );

  /** 
   * Changes the background color of the whole drawing.
   * 
   * @param color A color (may be Color::None).
   */
  void backgroundColor( const DGtal::Color & color );

  /** 
   * Draws the current drawing's bounding box as a rectangle.
   * 
   * @param depthValue The depth of the rectangle.
   */
  void drawBoundingBox( int depthValue = -1 );


  /** 
   * Define a clipping rectangle for the whole drawing.
   * 
   * @param x x
   * @param y y
   * @param width width
   * @param height height
   */
  void setClippingRectangle(  double x, double y, 
            double width, double height );

  /** 
   * Define a clipping path for the whole drawing.
   * 
   * @param points A path.
   */
  void setClippingPath(  const std::vector<Point> & points  );

  /** 
   * Define a clipping path for the whole drawing.
   * 
   * @param path A path.
   */
  void setClippingPath( const Path & path );

  /** 
   * Insert duplicates of a shape, n times, starting at its current position
   * and iterating given translations and scalings.
   * 
   * @param shape The shape to be duplicated.
   * @param times The number of duplicates.
   * @param dx The x shift.
   * @param dy The y shift.
   * @param scale A scale factor between each copy.
   */
  void addDuplicates( const Shape & shape,
          unsigned int times,
          double dx, double dy, double scale = 1.0 );

  /** 
   * Insert duplicates of a shape, n times, starting at its current position
   * and iterating a given translation.
   * 
   * @param shape The shape to be duplicated.
   * @param times The number of duplicates.
   * @param dx The x shift.
   * @param dy The y shift.
   * @param scaleX An x scale factor between each copy.
   * @param scaleY A y scale factor between each copy.
   * @param angle An angular increment.
   */
  void addDuplicates( const Shape & shape,
          unsigned int times,
          double dx, double dy,
          double scaleX, 
          double scaleY,
          double angle = 0.0 );

  /** 
   * Save the drawing in an EPS, XFIG or SVG file depending 
   * on the filename extension. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param filename Path of the file to be created.
   * @param size Page size (Either BoundingBox (default), A4 or Letter).
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void save( const char * filename, PageSize size = Board::BoundingBox, double margin = 10.0 ) const; 
  
  /** 
   * Save the drawing in an EPS, XFIG or SVG file depending 
   * on the filename extension. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param filename Path of the file to be created.
   * @param pageWidth Width of the page in millimeters.
   * @param pageHeight Height of the page in millimeters.
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void save( const char * filename, double pageWidth, double pageHeight, double margin = 10.0 ) const; 

  /** 
   * Saves the drawing in an EPS file. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param filename The EPS file name.
   * @param size Page size (Either BoundingBox (default), A4 or Letter).
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void saveEPS( const char * filename, PageSize size = Board::BoundingBox, double margin = 10.0 ) const ;

  /** 
   * Saves the drawing in EPS format through an output stream. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param out The output stream.
   * @param size Page size (Either BoundingBox (default), A4 or Letter).
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void saveEPS(std::ostream &out , PageSize size = Board::BoundingBox, double margin = 10.0 ) const ;


  /** 
   * Saves the drawing in an EPS file. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param filename The EPS file name.
   * @param pageWidth Width of the page in millimeters.
   * @param pageHeight Height of the page in millimeters.
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void saveEPS( const char * filename, double pageWidth, double pageHeight, double margin = 10.0 ) const ;



  /** 
   * Saves the drawing in an EPS format through an output stream. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param out  The output stream.
   * @param pageWidth Width of the page in millimeters.
   * @param pageHeight Height of the page in millimeters.
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void saveEPS( std::ostream &out, double pageWidth, double pageHeight, double margin = 10.0) const ;

  /** 
   * Saves the drawing in an XFig file. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param filename The name of the FIG file.
   * @param size Page size (Either BoundingBox (default), A4 or Letter).
   * @param margin Minimal margin around the figure in the page, in millimeters.
   * @param includeFIGHeader Indicates if the header is included in the exported file. Useful to merge several XFIG figures (default true)
   */
  void saveFIG( const char * filename, PageSize size = Board::BoundingBox, double margin = 10.0,
		bool includeFIGHeader=true) const;

  /** 
   * Saves the drawing in XFig format through an output stream. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param out The output stream.
   * @param size Page size (Either BoundingBox (default), A4 or Letter).
   * @param margin Minimal margin around the figure in the page, in millimeters.
   * @param includeFIGHeader Indicates if the header is included in the output stream. Useful to merge several XFIG figures (default true)
   */
  void saveFIG( std::ostream &out, PageSize size = Board::BoundingBox, double margin = 10.0,
		bool includeFIGHeader=true) const;

  /** 
   * Saves the drawing in an XFig file. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param filename The XFig file name.
   * @param pageWidth Width of the page in millimeters.
   * @param pageHeight Height of the page in millimeters.
   * @param margin Minimal margin around the figure in the page, in millimeters.
   * @param includeFIGHeader Indicates if the header is included in the output stream. Useful to merge several XFIG figures (default true)
   */
  void saveFIG( const char * filename, double pageWidth, double pageHeight, double margin = 10.0,
		bool includeFIGHeader=true) const ;

 /** 
   * Saves the drawing in an XFig format through an output
   * stream. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while
   * keeping its aspect ratio.
   * 
   * @param out  out The output stream.
   * @param pageWidth Width of the page in millimeters.
   * @param pageHeight Height of the page in millimeters.
   * @param margin Minimal margin around the figure in the page, in millimeters.
   * @param includeFIGHeader Indicates if the header is included in the output stream. Useful to merge several XFIG figures (default true)
   */
  void saveFIG( std::ostream &out, double pageWidth, double pageHeight, double margin = 10.0,
		bool includeFIGHeader=true ) const ;

  /** 
   * Save the drawing in an SVG file. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param filename The name of the file.
   * @param size Page size (Either BoundingBox (default), A4 or Letter).
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void saveSVG( const char * filename, PageSize size = Board::BoundingBox, double margin = 10.0 ) const;

  /** 
   * Save the drawing in an SVG format through an output stream. When
   * a size is given (not BoundingBox), the drawing is scaled (up or
   * down) so that it fits within the dimension while keeping its
   * aspect ratio.
   * 
   * @param out The output stream.
   * @param size Page size (Either BoundingBox (default), A4 or Letter).
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void saveSVG( std::ostream &out, PageSize size = Board::BoundingBox, double margin = 10.0 ) const;

  /** 
   * Saves the drawing in an SVG file. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param filename The SVG file name.
   * @param pageWidth Width of the page in millimeters.
   * @param pageHeight Height of the page in millimeters.
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void saveSVG( const char * filename, double pageWidth, double pageHeight, double margin = 10.0 ) const ;

 /** 
   * Saves the drawing in an SVG format through an output stream. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param out The output stream.
   * @param pageWidth Width of the page in millimeters.
   * @param pageHeight Height of the page in millimeters.
   * @param margin Minimal margin around the figure in the page, in
   * millimeters.
   * @param filename default filename
   */
  void saveSVG( std::ostream &out, double pageWidth, double pageHeight, double margin = 10.0,
		std::string filename="output.svg") const ;
  

#ifdef WITH_CAIRO
  // cairo
  /** 
   * Save the drawing with cairo. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param filename The name of the file.
   * @param type Output type: CairoPDF, CairoPNG, CairoPS, CairoSVG.
   * @param size the page size.
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void saveCairo( const char * filename, CairoType type = CairoPNG, 
                  PageSize size = Board::BoundingBox, double margin = 10.0 ) const;

  /** 
   * Save the drawing with cairo. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param filename The name of the file.
   * @param type Output type: CairoPDF, CairoPNG, CairoPS, CairoSVG.
   * @param pageWidth Width of the page in millimeters.
   * @param pageHeight Height of the page in millimeters.
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void saveCairo( const char * filename, CairoType type, double pageWidth, double pageHeight, double margin = 10.0 ) const ;

 
#endif

  /** 
   * Save the drawing in an TikZ file. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param filename The name of the file.
   * @param size Page size (Either BoundingBox (default), A4 or Letter).
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void saveTikZ( const char * filename, PageSize size = Board::BoundingBox, double margin = 10.0 ) const;
  /** 
   * Save the drawing in an TikZ file format through an output
   * stream. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while
   * keeping its aspect ratio.
   * 
   * @param out The output stream.
   * @param size Page size (Either BoundingBox (default), A4 or Letter).
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void saveTikZ( std::ostream &out, PageSize size = Board::BoundingBox, double margin = 10.0 ) const;

  /** 
   * Save the drawing in an TikZ file. When a size is given (not BoundingBox), the drawing is
   * scaled (up or down) so that it fits within the dimension while keeping its aspect ratio.
   * 
   * @param filename The name of the file.
   * @param pageWidth Width of the page in millimeters.
   * @param pageHeight Height of the page in millimeters.
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void saveTikZ( const char * filename, double pageWidth, double pageHeight, double margin = 10.0 ) const ;

  /** 
   * Save the drawing in an TikZ format through an output stream. When
   * a size is given (not BoundingBox), the drawing is scaled (up or
   * down) so that it fits within the dimension while keeping its
   * aspect ratio.
   * 
   * @param out The output stream.
   * @param pageWidth Width of the page in millimeters.
   * @param pageHeight Height of the page in millimeters.
   * @param margin Minimal margin around the figure in the page, in millimeters.
   */
  void saveTikZ( std::ostream &out, double pageWidth, double pageHeight, double margin = 10.0 ) const ;

 protected:

  /**
   * Current graphical state for drawings made by the drawSomething() methods.
   * 
   */
  struct State {
    DGtal::Color penColor;            /**< The pen color. */
    DGtal::Color fillColor;           /**< The fill color. */
    double lineWidth;        /**< The line thickness. */
    Shape::LineStyle lineStyle;  /**< The line style. */
    Shape::LineCap lineCap;      /**< The type of line extremities. */
    Shape::LineJoin lineJoin;   /**< The type of line junction. */
    Fonts::Font font;           /**< The font. */
    double fontSize;               /**< The font size. */
    double unitFactor;        /**< The factor to be applied to arguments of the drawSomething() family. */
    State();
    double unit( const double & x ) { return x * unitFactor; }
    Point unit( const Point & p ) { return Point( p.x * unitFactor, p.y * unitFactor); }
    void unit( Shape & shape ) {  shape.scaleAll( unitFactor ); }
  };
  State _state;       /**< The current state. */
  DGtal::Color _backgroundColor;   /**< The color of the background. */
  Path _clippingPath;
};

} // namespace LibBoard

#include "Board.ih"

#endif
