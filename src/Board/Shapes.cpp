/**
 * @file   Shapes.cpp
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
#include "Board/Rect.h"
#include "Board/Shapes.h"
#include "Board/Tools.h"
#include "Board/PSFonts.h"
#include <cmath>
#include <cstring>
#include <vector>
#include <sstream>

#include <assert.h>

#ifndef M_PI
#define M_PI    3.14159265358979323846  /* pi */
#endif

#ifdef _MSC_VER
//#define NOMINMAX
//#include <windows.h>
#endif

namespace {
const char * xFigDashStylesPS[] = {
    " [] 0 sd ", // SolidStyle
    " [1 1] 0 sd ", // DashStyle
    " [1.5 4.5] 45 sd ", // DotStyle
    " [4.5 2.3 1.5 2.3] 0 sd ", // DashDotStyle
    " [4.5 2.0 1.5 1.5 1.5 2.0] 0 sd ", // DashDotDotStyle
    " [4.5 1.8 1.5 1.4 1.5 1.4 1.5 1.8 ] 0 sd " // DashDotDotDotStyle
};

const char * xFigDashStylesSVG[] = {
    "", // SolidStyle
    "stroke-dasharray:1,1;stroke-dashoffset:0", // DashStyle
    "stroke-dasharray:1.5,4.5;stroke-dashoffset:45", // DotStyle
    "stroke-dasharray:4.5,2.3,1.5,2.3;stroke-dashoffset:0", // DashDotStyle
    "stroke-dasharray:4.5,2.0,1.5,1.5,1.5,2.0;stroke-dashoffset;0", // DashDotDotStyle
    "stroke-dasharray:4.5,1.8,1.5,1.4,1.5,1.4,1.5,1.8;stroke-dashoffset:0" // DashDotDotDotStyle
};

const char * xFigDashStylesTikZ[] = {
    "", // SolidStyle
    "dash pattern=on 1pt off 1pt,", // DashStyle
    "dotted,", // DotStyle
    "dashdotted,", // DashDotStyle
    "dashdotdotted,", // DashDotDotStyle
    "dash pattern=on 2pt off 3pt on 4pt off 4pt," // DashDotDotDotStyle
};

#ifdef WITH_CAIRO
// cairo
cairo_line_cap_t cairoLineCap[] = {
    CAIRO_LINE_CAP_BUTT,
    CAIRO_LINE_CAP_ROUND,
    CAIRO_LINE_CAP_SQUARE
};

cairo_line_join_t cairoLineJoin[] = {
    CAIRO_LINE_JOIN_MITER,
    CAIRO_LINE_JOIN_ROUND,
    CAIRO_LINE_JOIN_BEVEL
};

#define ARRAY_SIZE(A) (sizeof(A)/sizeof(A[0]))

const double cairoSolidStyle[] = {1, 0}; const double cairoSolidStyle_offset = 0;
const double cairoDashStyle[] = {1, 1}; const double cairoDashStyle_offset = 0;
const double cairoDotStyle[] = {1.5, 4.5}; const double cairoDotStyle_offset = 45;
const double cairoDashDotStyle[] = {4.5, 2.3, 1.5, 2.3}; const double cairoDashDotStyle_offset = 0;
const double cairoDashDotDotStyle[] = {4.5, 2.0, 1.5, 1.5, 1.5, 2.0}; const double cairoDashDotDotStyle_offset = 0;
const double cairoDashDotDotDotStyle[] = {4.5, 1.8, 1.5, 1.4, 1.5, 1.4, 1.5, 1.8}; const double cairoDashDotDotDotStyle_offset = 0;
// cairo
#endif
}

//todo cairo: gouraudtriangle, text (?)
//todo cairo: group (?)

namespace LibBoard {

extern const char * XFigPostscriptFontnames[];

bool
shapeGreaterDepth( const Shape *s1, const Shape *s2 )
{
    return s1->depth() > s2->depth();
}

const std::string Shape::_name("AbstractShape");

const std::string &
Shape::name() const
{
    return _name;
}

std::string
Shape::svgProperties( const TransformSVG & transform ) const
{
    static const char * capStrings[3] = { "butt", "round", "square" };
    static const char * joinStrings[3] = { "miter", "round", "bevel" };
    std::stringstream str;
    if ( _penColor != DGtal::Color::None ) {
        str << " fill=\"" << _fillColor.svg() << '"'
        << " stroke=\"" << _penColor.svg() << '"'
        << " stroke-width=\"" << transform.mapWidth( _lineWidth ) << "mm\""
        << " style=\"stroke-linecap:" << capStrings[ _lineCap ]
        << ";stroke-linejoin:" << joinStrings[ _lineJoin ];
        if ( _lineStyle != SolidStyle )
            str << ";" << xFigDashStylesSVG[ _lineStyle ];
        str << '"'
        << _fillColor.svgAlpha( " fill" )
        << _penColor.svgAlpha( " stroke" );
    } else  {
        str << " fill=\"" << _fillColor.svg() << '"'
//   << " stroke=\"" << _fillColor.svg() << '"'
//   << " stroke-width=\"0.5px\""
        << " stroke=\"none\""
        << " stroke-width=\"0\""
        << " style=\"stroke-linecap:round;stroke-linejoin:round;"
        << '"'
        << _fillColor.svgAlpha( " fill" )
        << _fillColor.svgAlpha( " stroke" );
    }
    return str.str();
}

std::string
Shape::postscriptProperties() const
{
    std::stringstream str;
    str << _lineWidth << " slw ";
    str << _lineCap << " slc ";
    str << _lineJoin << " slj";
    str << xFigDashStylesPS[ _lineStyle ];

    return str.str();
}

#ifdef WITH_CAIRO
void
Shape::setCairoDashStyle(cairo_t *cr, LineStyle type) const
{
    switch (type)
    {
      case SolidStyle:
  cairo_set_dash (cr, cairoSolidStyle, ARRAY_SIZE(cairoSolidStyle), cairoSolidStyle_offset); break;
      case DashStyle:
  cairo_set_dash (cr, cairoDashStyle, ARRAY_SIZE(cairoDashStyle), cairoDashStyle_offset); break;
      case DotStyle:
  cairo_set_dash (cr, cairoDotStyle, ARRAY_SIZE(cairoDotStyle), cairoDotStyle_offset); break;
      case DashDotStyle:
  cairo_set_dash (cr, cairoDashDotStyle, ARRAY_SIZE(cairoDashDotStyle), cairoDashDotStyle_offset); break;
      case DashDotDotStyle:
  cairo_set_dash (cr, cairoDashDotDotStyle, ARRAY_SIZE(cairoDashDotDotStyle), cairoDashDotDotStyle_offset); break;
      case DashDotDotDotStyle:
  cairo_set_dash (cr, cairoDashDotDotDotStyle, ARRAY_SIZE(cairoDashDotDotDotStyle), cairoDashDotDotDotStyle_offset); break;
  
      default: // SolidStyle
  cairo_set_dash (cr, cairoSolidStyle, ARRAY_SIZE(cairoSolidStyle), cairoSolidStyle_offset);
    }
}
#endif

std::string
Shape::tikzProperties( const TransformTikZ & transform ) const
{
    static const char * capStrings[3] = { "" /* initial value "butt" */, "line cap=round,", "line cap=rect," };
    static const char * joinStrings[3] = { "" /* initial value "miter" */, "line join=round", "line join=bevel" };

    std::stringstream str;
    str << "fill=" << _fillColor.tikz() << ',';
    str << "draw=" << _penColor.tikz() << ',';
    str << "line width=" << transform.mapWidth( _lineWidth ) << "mm,";
    str << xFigDashStylesTikZ[ _lineStyle ];
    str << capStrings[ _lineCap ];
    str << joinStrings[ _lineJoin ];

    return str.str();
}

void
Shape::depth( int d )
{
    _depth = d;
}

void
Shape::shiftDepth( int shift )
{
    _depth += shift;
}

/*
 * Dot
 */

const std::string Dot::_name("Dot");

const std::string &
Dot::name() const
{
    return _name;
}

Point
Dot::center() const {
    return Point( _x, _y );
}

Dot &
Dot::rotate( double angle, const Point & rotCenter )
{
    Point( _x, _y ).rotate( angle, rotCenter ).get( _x, _y );
    return *this;
}

Dot
Dot::rotated( double angle, const Point & rotCenter ) const
{
    return Dot(*this).rotate( angle, rotCenter );
}

Dot &
Dot::rotate( double )
{
    return *this;
}

Dot
Dot::rotated( double ) const
{
    return *this;
}

Dot &
Dot::translate( double dx, double dy )
{
    _x += dx;
    _y += dy;
    return *this;
}

Dot
Dot::translated( double dx, double dy ) const
{
    return Dot(*this).translate( dx, dy );
}

Shape &
Dot::scale( double , double )
{
    return *this;
}

Shape &
Dot::scale( double )
{
    return *this;
}

Dot
Dot::scaled( double , double ) const
{
    return *this;
}

Dot
Dot::scaled( double ) const
{
    return *this;
}

void
Dot::scaleAll( double s )
{
    _x *= s;
    _y *= s;
}

void
Dot::flushPostscript( std::ostream & stream,
                      const TransformEPS & transform ) const
{
    stream << "\n% Dot\n";
    stream << postscriptProperties() << " "
    << "n "
    << transform.mapX( _x ) << " "
    << transform.mapY( _y ) << " "
    << "m "
    << transform.mapX( _x ) << " "
    << transform.mapY( _y ) << " "
    << "l " << _penColor.postscript() << " srgb stroke" << std::endl;
}

void
Dot::flushFIG( std::ostream & stream,
               const TransformFIG & transform,
               std::map<DGtal::Color,int> & colormap ) const
{
    stream << "2 1 0 ";
    // Thickness
    stream << ( _penColor.valid()?transform.mapWidth( _lineWidth ):0 ) << " ";
    // Pen color
    stream << colormap[ _penColor ] << " ";
    // Fill color
    stream << "0 ";
    // Depth
    stream << transform.mapDepth( _depth ) << " ";
    // Pen style
    stream <<  "-1 ";
    // Area fill, style val, join style, cap style, radius, f_arrow, b_arrow
    stream << "-1 0.000 " << _lineJoin << " " << _lineCap << " -1 0 0 ";
    // Number of points
    stream << "2\n";
    stream << "         ";
    stream << static_cast<int>( transform.mapX( _x ) ) << " "
    << static_cast<int>( transform.mapY( _y ) ) << " "
    << static_cast<int>( transform.mapX( _x ) ) << " "
    << static_cast<int>( transform.mapY( _y ) ) << std::endl;
}

void
Dot::flushSVG( std::ostream & stream,
               const TransformSVG & transform ) const
{
    stream << "<line x1=\"" << transform.mapX( _x ) << "\""
    << " y1=\"" << transform.mapY( _y ) << "\""
    << " x2=\"" << transform.mapX( _x ) << "\""
    << " y2=\"" << transform.mapY( _y ) << "\""
    << svgProperties( transform )
    << " />" << std::endl;
}

#ifdef WITH_CAIRO
void
Dot::flushCairo( cairo_t *cr,
     const TransformCairo & transform ) const
{
    cairo_save (cr);
    
      cairo_set_source_rgba (cr, _penColor.red()/255.0, _penColor.green()/255.0, _penColor.blue()/255.0, 1.);
      
      cairo_move_to (cr, transform.mapX( _x ), transform.mapY( _y ));
      cairo_line_to (cr, transform.mapX( _x ), transform.mapY( _y ));
      
      cairo_set_line_width (cr, _lineWidth);
      cairo_set_line_cap (cr, cairoLineCap[_lineCap]);
      cairo_set_line_join (cr, cairoLineJoin[_lineJoin]);
      setCairoDashStyle (cr, _lineStyle);

      cairo_stroke (cr);
    
    cairo_restore (cr);
}
#endif

void
Dot::flushTikZ( std::ostream & stream,
                const TransformTikZ & /*transform*/ ) const

{
  // FIXME: unimplemented
  stream << "% FIXME: Dot::flushTikZ unimplemented" << std::endl;
}

Rect
Dot::boundingBox() const
{
    return Rect( _x, _y, 0.0, 0.0 );
}

Dot *
Dot::clone() const {
    return new Dot(*this);
}

/*
 * Line
 */

const std::string Line::_name("Line");

const std::string &
Line::name() const
{
    return _name;
}

Point
Line::center() const {
    return 0.5 * Point( _x1 + _x2, _y1 + _y2 );
}

Line &
Line::rotate( double angle, const Point & rotCenter )
{
    Point( _x1, _y1 ).rotate( angle, rotCenter ).get( _x1, _y1 );
    Point( _x2, _y2 ).rotate( angle, rotCenter ).get( _x2, _y2 );
    return *this;
}

Line &
Line::rotate( double angle )
{
    return Line::rotate( angle, center() );
}

Line
Line::rotated( double angle, const Point & rotCenter ) const
{
    Line res(*this);
    Point( _x1, _y1 ).rotate( angle, rotCenter ).get( res._x1, res._y1 );
    Point( _x2, _y2 ).rotate( angle, rotCenter ).get( res._x2, res._y2 );
    return res;
}

Line
Line::rotated( double angle ) const
{
    Line res(*this);
    Point c = center();
    Point( _x1, _y1 ).rotate( angle, c ).get( res._x1, res._y1 );
    Point( _x2, _y2 ).rotate( angle, c ).get( res._x2, res._y2 );
    return res;
}

Line &
Line::translate( double dx, double dy )
{
    _x1 += dx;
    _x2 += dx;
    _y1 += dy;
    _y2 += dy;
    return *this;
}

Line
Line::translated( double dx, double dy ) const
{
    Line res(*this);
    res._x1 += dx;
    res._x2 += dx;
    res._y1 += dy;
    res._y2 += dy;
    return *this;
}

Shape &
Line::scale( double sx, double sy )
{
    Point c = center();
    _x1 *= sx;
    _x2 *= sx;
    _y1 *= sy;
    _y2 *= sy;
    Point delta = c - center();
    translate( delta.x, delta.y );
    return *this;
}

Shape &
Line::scale( double s )
{
    scale( s, s );
    return (*this);
}

Line
Line::scaled( double sx, double sy ) const
{
    Line res(*this);
    Point c = center();
    res._x1 *= sx;
    res._x2 *= sx;
    res._y1 *= sy;
    res._y2 *= sy;
    Point delta = c - res.center();
    return res.translate( delta.x, delta.y );
}

Line
Line::scaled( double s ) const
{
    return Line::scaled( s , s );
}

void
Line::scaleAll( double s )
{
    _x1 *= s;
    _y1 *= s;
    _x2 *= s;
    _y2 *= s;
}

Line *
Line::clone() const {
    return new Line(*this);
}

void
Line::flushPostscript( std::ostream & stream,
                       const TransformEPS & transform ) const
{
    stream << "\n% Line\n";
    stream << postscriptProperties() << " "
    << "n "
    << transform.mapX( _x1 ) << " "
    << transform.mapY( _y1 ) << " "
    << "m "
    << transform.mapX( _x2 ) << " "
    << transform.mapY( _y2 ) << " "
    << "l " << _penColor.postscript() << " srgb stroke" << std::endl;
}

void
Line::flushFIG( std::ostream & stream,
                const TransformFIG & transform,
                std::map<DGtal::Color,int> & colormap ) const
{
    stream << "2 1 ";
    // Line style
    stream << _lineStyle << " ";
    // Thickness
    stream << ( _penColor.valid()?transform.mapWidth( _lineWidth ):0 ) << " ";
    // Pen color
    stream << colormap[ _penColor ] << " ";
    // Fill color
    stream << "0 ";
    // Depth
    stream << transform.mapDepth( _depth ) << " ";
    // Pen style
    stream <<  "-1 ";
    // Area fill, style val, join style, cap style, radius, f_arrow, b_arrow
    stream << "-1 " << (_lineStyle?"4.000 ":"0.000 ") << _lineJoin << " " << _lineCap << " -1 0 0 ";
    // Number of points
    stream << "2\n";
    stream << "         ";
    stream << static_cast<int>( transform.mapX( _x1 ) ) << " "
    << static_cast<int>( transform.mapY( _y1 ) ) << " "
    << static_cast<int>( transform.mapX( _x2 ) ) << " "
    << static_cast<int>( transform.mapY( _y2 ) ) << std::endl;
}

void
Line::flushSVG( std::ostream & stream,
                const TransformSVG & transform ) const
{
    stream << "<line x1=\"" << transform.mapX( _x1 ) << "\""
    << " y1=\"" << transform.mapY( _y1 ) << "\""
    << " x2=\"" << transform.mapX( _x2 ) << "\""
    << " y2=\"" << transform.mapY( _y2 ) << "\""
    << svgProperties( transform )
    << " />" << std::endl;
}

#ifdef WITH_CAIRO
void
Line::flushCairo( cairo_t *cr,
                const TransformCairo & transform ) const
{
    cairo_save (cr);
    
      cairo_set_source_rgba (cr, _penColor.red()/255.0, _penColor.green()/255.0, _penColor.blue()/255.0, 1.);
      
      cairo_move_to (cr, transform.mapX( _x1 ), transform.mapY( _y1 ));
      cairo_line_to (cr, transform.mapX( _x2 ), transform.mapY( _y2 ));
      
      cairo_set_line_width (cr, _lineWidth);
      cairo_set_line_cap (cr, cairoLineCap[_lineCap]);
      cairo_set_line_join (cr, cairoLineJoin[_lineJoin]);
      setCairoDashStyle (cr, _lineStyle);

      cairo_stroke (cr);
    
    cairo_restore (cr);
}
#endif

void
Line::flushTikZ( std::ostream & stream,
                 const TransformTikZ & transform ) const
{
    stream << "\\path[" << tikzProperties(transform) << "] ("
    << transform.mapX( _x1 ) << ',' << transform.mapY( _y1 )
    << ") -- ("
    << transform.mapX( _x2 ) << ',' << transform.mapY( _y2 )
    << ");" << std::endl;
}

Rect
Line::boundingBox() const
{
    Rect rect;
    if ( _x1 > _x2 ) {
        rect.width = _x1 - _x2;
        rect.left = _x2;
    } else {
        rect.width = _x2 - _x1;
        rect.left = _x1;
    }
    if ( _y1 > _y2 ) {
        rect.top = _y1;
        rect.height = _y1 - _y2;
    } else {
        rect.top = _y2;
        rect.height = _y2 - _y1;
    }
    return rect;
}



/*
 * Image
 */

const std::string Image::_name("Image");

const std::string &
Image::name() const
{
    return _name;
}

Image *
Image::clone() const {
  return new Image(*this);
}

void
Image::flushFIG( std::ostream & stream,
                const TransformFIG & transform,
                std::map<DGtal::Color,int> & colormap ) const

{
  stream << "2 5 ";
  // Line style
  stream << _lineStyle << " ";
  // Thickness
  stream << ( _penColor.valid()?transform.mapWidth( _lineWidth ):0 ) << " ";
  // Pen color
  stream << colormap[ _penColor ] << " ";
  // Fill color
  stream << "0 ";
  // Depth
  stream << transform.mapDepth( _depth ) << " "
         << "-1 -1 0.000 0 0 -1 0 0 5" << std::endl <<" 0 "     
   << _filename << std::endl;
  _path.flushFIG( stream, transform );
  stream << std::endl;
}



void
Image::flushSVG( std::ostream & stream,
     const TransformSVG & transform ) const
{

  stream << "<image x=\"" << transform.mapX( _path[0].x ) << '"'
   << " y=\"" << transform.mapY( _path[0].y )  << '"'
   << " width=\"" << transform.scale( (_path[1] - _path[0]).norm() ) << '"'
   << " height=\"" << transform.scale( (_path[0] - _path[3]).norm() ) << '"'
   << "  xlink:href=\""<< _filename << "\" >"  << std::endl
   << " <title>My image</title>"<<std::endl
       << " </image>" << std::endl;


}

#ifdef WITH_CAIRO
void
Image::flushCairo( cairo_t *cr,
     const TransformCairo & transform ) const
{
  int w, h;
  cairo_surface_t *image;
  cairo_save (cr);
  std::string extension = _filename.substr(_filename.find_last_of(".") + 1);
  ASSERT(extension=="png");
  image = cairo_image_surface_create_from_png (_filename.c_str());
  assert(cairo_surface_status (image) == CAIRO_STATUS_SUCCESS);
  w = cairo_image_surface_get_width (image);
  h = cairo_image_surface_get_height (image);
  
  // tr
  cairo_translate (cr, transform.mapX( _path[0].x ), transform.mapY( _path[0].y ));
  //cairo_scale (cr, transform.scale( _path[1].x - _path[0].x )/w, transform.scale( _path[0].y - _path[3].y )/h);
  cairo_scale (cr, transform.scale( (_path[1] - _path[0]).norm() )/w, transform.scale( (_path[0] - _path[3]).norm() )/h);
  // tr
  
  cairo_set_source_surface (cr, image, 0, 0);
  cairo_paint_with_alpha(cr, _alpha);
  cairo_surface_destroy (image);
  
  cairo_restore (cr);
}
#endif

void
Image::flushTikZ( std::ostream & stream,
                const TransformTikZ & transform ) const

{
  stream << "\\node [below right=0pt] at ("
         << transform.mapX( _path[0].x ) << "pt,"
         << transform.mapY( _path[0].y ) << "pt) {\\pgfimage["
	 << "width=" << transform.scale( (_path[1] - _path[0]).norm() ) << "pt,"
	 << "height=" << transform.scale( (_path[0] - _path[3]).norm() ) << "pt,"
         << "]{" << _filename << "}};" << std::endl;
}

/*
 * Arrow
 */

const std::string Arrow::_name("Arrow");

const std::string &
Arrow::name() const
{
    return _name;
}

Arrow
Arrow::rotated( double angle, const Point & rotCenter ) const
{
    Arrow res(*this);
    Point( _x1, _y1 ).rotate( angle, rotCenter ).get( res._x1, res._y1 );
    Point( _x2, _y2 ).rotate( angle, rotCenter ).get( res._x2, res._y2 );
    return res;
}

Arrow
Arrow::rotated( double angle ) const
{
    Arrow res(*this);
    Point c = center();
    Point( _x1, _y1 ).rotate( angle, c ).get( res._x1, res._y1 );
    Point( _x2, _y2 ).rotate( angle, c ).get( res._x2, res._y2 );
    return res;
}

Arrow
Arrow::translated( double dx, double dy ) const
{
    Arrow res(*this);
    res._x1 += dx;
    res._x2 += dx;
    res._y1 += dy;
    res._y2 += dy;
    return res;
}

Arrow
Arrow::scaled( double sx, double sy ) const
{
    Arrow res(*this);
    Point c = center();
    res._x1 *= sx;
    res._x2 *= sx;
    res._y1 *= sy;
    res._y2 *= sy;
    Point delta = c - res.center();
    return static_cast<Arrow &>( res.translate( delta.x, delta.y ) );
}

Arrow
Arrow::scaled( double s ) const
{
    return Arrow::scaled( s, s );
}

Arrow *
Arrow::clone() const {
    return new Arrow(*this);
}

void
Arrow::flushPostscript( std::ostream & stream,
                        const TransformEPS & transform ) const
{
    double dx = _x1 - _x2;
    double dy = _y1 - _y2;
    double norm = sqrt( dx*dx + dy*dy );
    dx /= norm;
    dy /= norm;
    dx *= 10*_lineWidth;
    dy *= 10*_lineWidth;

    //   double back_x = 0.8 * dx + _x2;
    //   double back_y = 0.8 * dy + _y2;

    double ndx1 = dx*cos(0.3)-dy*sin(0.3);
    double ndy1 = dx*sin(0.3)+dy*cos(0.3);
    double ndx2 = dx*cos(-0.3)-dy*sin(-0.3);
    double ndy2 = dx*sin(-0.3)+dy*cos(-0.3);

    stream << "\n% Arrow\n";
    stream << _penColor.postscript() << " srgb "
    << postscriptProperties() << " "
    << "n "
    << transform.mapX( _x1 ) << " "
    << transform.mapY( _y1 ) << " "
    << "m "
    << transform.mapX( _x2 + ( dx * cos(0.3) ) ) << " "
    << transform.mapY( _y2 + ( dy * cos(0.3) ) ) << " "
    << "l stroke" << std::endl;

    if ( filled() ) {
        stream << "n "
        << transform.mapX( _x2 ) + transform.scale( ndx1 ) << " "
        << transform.mapY( _y2 ) + transform.scale( ndy1 ) << " "
        << "m "
        << transform.mapX( _x2 ) << " "
        << transform.mapY( _y2 ) << " l "
        << transform.mapX( _x2 ) + transform.scale( ndx2 ) << " "
        << transform.mapY( _y2 ) + transform.scale( ndy2 ) << " ";
        stream  << "l cp " << _penColor.postscript() << " srgb  fill" << std::endl;
    }

    stream << "n "
    << transform.mapX( _x2 ) + transform.scale( ndx1 ) << " "
    << transform.mapY( _y2 ) + transform.scale( ndy1 ) << " "
    << "m "
    << transform.mapX( _x2 ) << " "
    << transform.mapY( _y2 ) << " l "
    << transform.mapX( _x2 ) + transform.scale( ndx2 ) << " "
    << transform.mapY( _y2 ) + transform.scale( ndy2 ) << " l"
    << " " << _penColor.postscript() << " srgb cp [] 0 sd stroke" << std::endl;
}

void
Arrow::flushFIG( std::ostream & stream,
                 const TransformFIG & transform,
                 std::map<DGtal::Color,int> & colormap ) const
{
    stream << "2 1 ";
    // Line style
    stream << _lineStyle << " ";
    // Thickness
    stream << ( _penColor.valid()?transform.mapWidth( _lineWidth ):0 ) << " ";
    // Pen color
    stream << colormap[ _penColor ] << " ";
    // Fill color
    stream << colormap[ _penColor ] << " ";
    // Depth
    stream << transform.mapDepth( _depth ) << " ";
    // Pen style
    stream <<  "-1 ";
    // Area fill, style val, join style, cap style, radius, f_arrow, b_arrow
    stream << "-1 " << (_lineStyle?"4.000 ":"0.000 ") << _lineJoin << " " << _lineCap << " -1 1 0 ";
    // Number of points
    stream << "2\n";
    if ( filled() )
        stream << "       1 1 1.00 60.00 120.00\n";
    else
        stream << "       1 0 1.00 60.00 120.00\n";
    stream << "         ";
    stream << static_cast<int>( transform.mapX( _x1 ) ) << " "
    << static_cast<int>( transform.mapY( _y1 ) ) << " "
    << static_cast<int>( transform.mapX( _x2 ) ) << " "
    << static_cast<int>( transform.mapY( _y2 ) ) << std::endl;
}

void
Arrow::flushSVG( std::ostream & stream,
                 const TransformSVG & transform ) const
{
    double dx = _x1 - _x2;
    double dy = _y1 - _y2;
    double norm = sqrt( dx*dx + dy*dy );
    dx /= norm;
    dy /= norm;
    dx *= 10 * _lineWidth;
    dy *= 10 * _lineWidth;

    //   double back_x = 0.8 * dx + _x2;
    //   double back_y = 0.8 * dy + _y2;

    double ndx1 = dx*cos(0.3)-dy*sin(0.3);
    double ndy1 = dx*sin(0.3)+dy*cos(0.3);
    double ndx2 = dx*cos(-0.3)-dy*sin(-0.3);
    double ndy2 = dx*sin(-0.3)+dy*cos(-0.3);

    stream << "<g>" << std::endl;
    // The line
    stream << " <path "
    << "d=\"M " << transform.mapX( _x1 ) << " " << transform.mapY( _y1 )
    << " L " << transform.mapX( _x2 + ( dx * cos(0.3) ) )
    << " " << transform.mapY( _y2 + ( dy * cos(0.3) ) ) << " z\""
    << " fill=\"none\" stroke=\"" << _penColor.svg() << "\""
    << _penColor.svgAlpha( " stroke" );
    if ( _lineStyle != SolidStyle )
        stream << " style=\"" <<   xFigDashStylesSVG[ _lineStyle ] << '"';
    stream << " stroke-width=\"" << transform.mapWidth( _lineWidth ) << "mm\" />";

    // The arrow
    stream << " <polygon";
    stream << " fill=\"" << _fillColor.svg() << "\"";
    stream << " stroke=\"" << _penColor.svg() << "\""
    << " stroke-width=\"" << transform.mapWidth( /* 0.33 * */ _lineWidth ) << "mm\""
    << " style=\"stroke-linecap:butt;stroke-linejoin:miter\""
    << _fillColor.svgAlpha( " fill" )
    << _penColor.svgAlpha( " stroke" )
    << " points=\""
    << transform.mapX( _x2 ) + transform.scale( ndx1 ) << ","
    << transform.mapY( _y2 ) - transform.scale( ndy1 ) << " "
    << transform.mapX( _x2 ) << ","
    << transform.mapY( _y2 ) << " "
    << transform.mapX( _x2 ) + transform.scale( ndx2 ) << ","
    << transform.mapY( _y2 ) - transform.scale( ndy2 ) << " "
    << transform.mapX( _x2 ) + transform.scale( ndx1 ) << ","
    << transform.mapY( _y2 ) - transform.scale( ndy1 ) << "\" />" << std::endl;
    stream << "</g>" << std::endl;
}

#ifdef WITH_CAIRO
void
Arrow::flushCairo( cairo_t *cr,
     const TransformCairo & transform ) const
{
    double dx = _x1 - _x2;
    double dy = _y1 - _y2;
    double norm = sqrt( dx*dx + dy*dy );
    dx /= norm;
    dy /= norm;
    dx *= 10 * _lineWidth;
    dy *= 10 * _lineWidth;

    //   double back_x = 0.8 * dx + _x2;
    //   double back_y = 0.8 * dy + _y2;

    double ndx1 = dx*cos(0.3)-dy*sin(0.3);
    double ndy1 = dx*sin(0.3)+dy*cos(0.3);
    double ndx2 = dx*cos(-0.3)-dy*sin(-0.3);
    double ndy2 = dx*sin(-0.3)+dy*cos(-0.3);
    
    cairo_save (cr);
    
      // The line
      cairo_set_source_rgba (cr, _penColor.red()/255.0, _penColor.green()/255.0, _penColor.blue()/255.0, 1.);
      
      cairo_move_to (cr, transform.mapX( _x1 ), transform.mapY( _y1 ));
      cairo_line_to (cr, transform.mapX( _x2 + ( dx * cos(0.3) ) ), transform.mapY( _y2 + ( dy * cos(0.3) ) ));
      
      cairo_set_line_width (cr, _lineWidth);
      cairo_set_line_cap (cr, cairoLineCap[_lineCap]);
      cairo_set_line_join (cr, cairoLineJoin[_lineJoin]);
      setCairoDashStyle (cr, _lineStyle);
      
      cairo_stroke (cr);
      
      // The arrow
      cairo_set_source_rgba (cr, _fillColor.red()/255.0, _fillColor.green()/255.0, _fillColor.blue()/255.0, 1.);
      
      cairo_move_to (cr, transform.mapX( _x2 ) + transform.scale( ndx1 ), transform.mapY( _y2 ) - transform.scale( ndy1 ));
      cairo_line_to (cr, transform.mapX( _x2 ), transform.mapY( _y2 ));
      cairo_line_to (cr, transform.mapX( _x2 ) + transform.scale( ndx2 ), transform.mapY( _y2 ) - transform.scale( ndy2 ));
      cairo_close_path (cr);

      if ( filled() )
      {
  if ( _penColor != DGtal::Color::None )
    cairo_fill_preserve (cr);
  else
    cairo_fill (cr);
      }
      
      //
      
      if ( _penColor != DGtal::Color::None )
      {
  cairo_set_source_rgba (cr, _penColor.red()/255.0, _penColor.green()/255.0, _penColor.blue()/255.0, 1.);
  
  cairo_set_line_width (cr, _lineWidth);
  cairo_set_line_cap (cr, cairoLineCap[ButtCap]);
  cairo_set_line_join (cr, cairoLineJoin[MiterJoin]);
  setCairoDashStyle (cr, SolidStyle);

  cairo_stroke (cr);
      }
    
    cairo_restore (cr);
}
#endif

void
Arrow::flushTikZ( std::ostream & stream,
                  const TransformTikZ & transform ) const
{
    //stream << "\\path[-triangle 45," << tikzProperties(transform) << "] (" // Requires \usetikzlibrary{arrows}
    stream << "\\path[-latex," << tikzProperties(transform) << "] ("
    << transform.mapX( _x1 ) << ',' << transform.mapY( _y1 )
    << ") -- ("
    << transform.mapX( _x2 ) << ',' << transform.mapY( _y2 )
    << ");" << std::endl;
}

/*
 * Ellipse
 */

const std::string Ellipse::_name("Ellipse");

const std::string &
Ellipse::name() const
{
    return _name;
}

Point
Ellipse::center() const {
    return _center;
}

Ellipse &
Ellipse::rotate( double angle, const Point & rotCenter )
{
    Point c( _center );
    Point e = (c + Point( _xRadius, 0 )).rotate( _angle, c );
    Point rc = c.rotated( angle, rotCenter );
    Point re = e.rotated( angle, rotCenter );
    Point axis = re - rc;
    _angle = atan( axis.y / axis.x );
    _center = rc;
    return *this;
}

Ellipse
Ellipse::rotated( double angle, const Point & rotCenter ) const
{
    return Ellipse(*this).rotate( angle, rotCenter );
}

Ellipse &
Ellipse::rotate( double angle )
{
    return Ellipse::rotate( angle, center() );
}

Ellipse
Ellipse::rotated( double angle ) const
{
    return Ellipse(*this).rotate( angle, center() );
}

Ellipse &
Ellipse::translate( double dx, double dy )
{
    _center += Point( dx, dy );
    return *this;
}

Ellipse
Ellipse::translated( double dx, double dy ) const
{
    return Ellipse(*this).translate( dx, dy );
}

Shape &
Ellipse::scale( double sx, double sy )
{
  // Thanks to Freddie Exall for pointing an error with the first version
  // of this function, and for pointing to a fix as well!
  if ( _angle != 0 ) {
    double co = cos( _angle );
    double si = sin( _angle );

    // current transformation matrix
    double m00 = ( 1 / _xRadius ) * co;
    double m01 = ( 1 / _xRadius ) * si;
    double m10 = - ( 1 / _yRadius ) * si;
    double m11 = ( 1 / _yRadius ) * co;

    // Implicit function of ellipse at current
    // ax^2 + bxy + cy^2 = 1
    double a = ( m00 * m00 ) + ( m10 * m10 );
    double b = 2 * ( ( m00 * m01 ) + ( m10 * m11 ) );
    double c = ( m01 * m01 ) + ( m11 * m11 );

    // Scale coefficients ( x_new = sx * x, y_new = sy * y )
    a = a / ( sx * sx );
    b = b / ( sx * sy );
    c = c / ( sy * sy );

    if ( b == 0 ) {
      _angle = 0;
    } else if ( a == c ) {
      _angle = M_PI / 4;
      a += ( b / 2 );
      c -= ( b / 2 );
    } else {
      _angle = 0.5 * atan( b / ( a - c ) );
      double k = 1 + ( ( b * b ) / ( ( a - c ) * ( a - c ) ) );
      k = sqrt( k );
      k *= ( a - c );
      c += a;
      a = 0.5 * ( c + k );
      c = 0.5 * ( c - k );
    }
    _xRadius = 1 / sqrt( a );
    _yRadius = 1 / sqrt( c );
  } else {
    _xRadius = _xRadius * sx;
    _yRadius = _yRadius * sy;
  }
  return *this;
}

Shape &
Ellipse::scale( double s )
{
    return Ellipse::scale( s, s );
}

Ellipse
Ellipse::scaled( double sx, double sy ) const
{
    return static_cast<Ellipse &>( Ellipse(*this).scale( sx, sy ) );
}

Ellipse
Ellipse::scaled( double s ) const
{
    return static_cast<Ellipse &>( Ellipse(*this).scale( s, s ) );
}

void
Ellipse::scaleAll( double s )
{
    _xRadius *= s;
    _yRadius *= s;
    _center *= s;
}

Ellipse *
Ellipse::clone() const {
    return new Ellipse(*this);
}

void
Ellipse::flushPostscript( std::ostream & stream,
                          const TransformEPS & transform ) const
{
    double yScale = _yRadius / _xRadius;
    stream << "\n% Ellipse\n";
    if ( filled() ) {
        stream << "gs "
        << transform.mapX( _center.x ) << " " << transform.mapY( _center.y ) << " tr";
        if ( _angle != 0.0 ) stream << " " << (_angle*180/M_PI) << " rot ";
        if ( ! _circle ) stream << " " << 1.0 << " " << yScale << " sc";
        stream << " n " << transform.scale( _xRadius ) << " 0 m "
        << " 0 0 " << transform.scale( _xRadius ) << " 0.0 360.0 arc ";
        stream << " " << _fillColor.postscript() << " srgb";
        stream << " fill gr" << std::endl;
    }

    if ( _penColor != DGtal::Color::None ) {
        stream << postscriptProperties() << "\n";
        stream << "gs " << transform.mapX( _center.x ) << " " << transform.mapY( _center.y ) << " tr";
        if ( _angle != 0.0 ) stream << " " << (_angle*180/M_PI) << " rot ";
        if ( ! _circle ) stream << " " << 1.0 << " " << yScale << " sc";
        stream << " n " << transform.scale( _xRadius ) << " 0 m "
        << " 0 0 " << transform.scale( _xRadius ) << " 0.0 360.0 arc ";
        stream << " " << _penColor.postscript() << " srgb";
        stream << " stroke gr" << std::endl;
    }
}

void
Ellipse::flushFIG( std::ostream & stream,
                   const TransformFIG & transform,
                   std::map<DGtal::Color,int> & colormap ) const
{
    // Ellipse, Sub type, Line style, Thickness
    if ( _circle )
        stream << "1 3 " << _lineStyle << " ";
    else
        stream << "1 1 " << _lineStyle << " ";
    stream << ( _penColor.valid()?transform.mapWidth( _lineWidth ):0 ) << " ";
    // Pen color, Fill color
    stream << colormap[ _penColor ] << " " << colormap[ _fillColor ] << " ";
    // Depth, Pen style, Area fill, Style val, Direction, angle
    if ( filled() )
        stream << transform.mapDepth( _depth ) << " -1 20 " << (_lineStyle?"4.000 ":"0.000 ") << "  1 " << _angle << " ";
    else
        stream << transform.mapDepth( _depth ) << " -1 -1 " << (_lineStyle?"4.000 ":"0.000 ") << " 1 " << _angle << " ";
    stream << static_cast<int>( transform.mapX( _center.x ) ) << " "
    << static_cast<int>( transform.mapY( _center.y ) ) << " "
    << static_cast<int>( transform.scale( _xRadius ) ) << " "
    << static_cast<int>( transform.scale( _yRadius ) ) << " "
    << static_cast<int>( transform.mapX( _center.x ) ) << " "
    << static_cast<int>( transform.mapY( _center.y ) ) << " "
    << static_cast<int>( transform.mapX( _center.x ) + transform.scale( _xRadius ) ) << " "
    << static_cast<int>( transform.mapY( _center.y ) ) << "\n";
}

void
Ellipse::flushSVG( std::ostream & stream,
                   const TransformSVG & transform ) const
{
    stream << "<ellipse cx=\"" << transform.mapX( _center.x ) << '"'
    << " cy=\"" << transform.mapY( _center.y ) << '"'
    << " rx=\"" << transform.scale( _xRadius ) << '"'
    << " ry=\"" << transform.scale( _yRadius ) << '"'
    << svgProperties( transform ) ;
    if ( _angle != 0.0 ) {
        stream << " transform=\"rotate( "
        << -(_angle*180/M_PI) << ", "
        << transform.mapX( _center.x ) << ", "
        << transform.mapY( _center.y ) << " )\" ";
    }
    stream << " />" << std::endl;
}

#ifdef WITH_CAIRO
void
Ellipse::flushCairo( cairo_t *cr,
     const TransformCairo & transform ) const
{
  cairo_save (cr);

    cairo_set_source_rgba (cr, _fillColor.red()/255.0, _fillColor.green()/255.0, _fillColor.blue()/255.0, 1.);
    
    // tr
    cairo_translate (cr, transform.mapX( _center.x ), transform.mapY( _center.y ));
    if ( _angle != 0.0 )
      cairo_rotate (cr, _angle);
    cairo_scale (cr, transform.scale( _xRadius ), transform.scale( _yRadius ));
    // tr
    
    cairo_arc (cr, 0, 0, 1, 0, 2*M_PI);
    
    if ( filled() )
    {
      if ( _penColor != DGtal::Color::None )
  cairo_fill_preserve (cr);
      else
  cairo_fill (cr);
    }
    
    //
    
    if ( _penColor != DGtal::Color::None )
    {
      cairo_set_source_rgba (cr, _penColor.red()/255.0, _penColor.green()/255.0, _penColor.blue()/255.0, 1.);
  
      cairo_set_line_width (cr, _lineWidth);
      cairo_set_line_cap (cr, cairoLineCap[_lineCap]);
      cairo_set_line_join (cr, cairoLineJoin[_lineJoin]);
      setCairoDashStyle (cr, _lineStyle);

      cairo_stroke (cr);
    }
  
  cairo_restore (cr);
}
#endif

void
Ellipse::flushTikZ( std::ostream & stream,
		    const TransformTikZ & transform ) const
{
  // FIXME: unimplemented
  stream << "% FIXME: Ellipse::flushTikZ unimplemented" << std::endl;
  stream << "\\path[" << tikzProperties(transform) << "] ("
	 << transform.mapX( _center.x ) << ','
	 << transform.mapY( _center.y ) << ')'
	 << " circle [x radius=" << transform.scale( _xRadius ) << ','
         <<          "y radius=" << transform.scale( _yRadius ) << ','
	 <<          "rotate=" << -(_angle*180/M_PI)
	 << "];"
	 << std::endl;
}

Rect
Ellipse::boundingBox() const
{
    if ( _angle == 0.0 )
        return Rect( _center.x - _xRadius, _center.y + _yRadius,
                     2 * _xRadius, 2 * _yRadius );

    double angleXmax = -atan( (_yRadius/_xRadius)*(tan(_angle) ) );
    double angleXmin = -atan( (_yRadius/_xRadius)*(tan(_angle) ) ) + M_PI;
    double angleYmax =  atan( (_yRadius/_xRadius)*(1/tan(_angle) ) );
    double angleYmin =  M_PI + atan( (_yRadius/_xRadius)*(1/tan(_angle) ) );

    if ( _angle < 0.0 ) {
        angleYmax += M_PI;
        angleYmin -= M_PI;
    }

    return Rect( _center.x + _xRadius*cos(angleXmin)*cos(_angle) - _yRadius*sin(angleXmin)*sin(_angle),
                 _center.y + _xRadius*cos(angleYmax)*sin(_angle) + _yRadius*sin(angleYmax)*cos(_angle),
                 ( _xRadius*cos(angleXmax)*cos(_angle) - _yRadius*sin(angleXmax)*sin(_angle) ) -
                 ( _xRadius*cos(angleXmin)*cos(_angle) - _yRadius*sin(angleXmin)*sin(_angle) ),
                 ( _xRadius*cos(angleYmax)*sin(_angle) + _yRadius*sin(angleYmax)*cos(_angle) ) -
                 ( _xRadius*cos(angleYmin)*sin(_angle) + _yRadius*sin(angleYmin)*cos(_angle) ) );
}

/*
 * Circle
 */

const std::string Circle::_name("Circle");

const std::string &
Circle::name() const
{
    return _name;
}

Point
Circle::center() const {
    return _center;
}

Circle &
Circle::rotate( double angle, const Point & rotCenter )
{
    if ( _circle ) {
        if ( rotCenter == _center ) return *this;
        _center.rotate( angle, rotCenter );
        return *this;
    }
    Ellipse::rotate( angle, rotCenter );
    return *this;
}

Circle
Circle::rotated( double angle, const Point & rotCenter ) const
{
    return Circle(*this).rotate( angle, rotCenter );
}

Circle &
Circle::rotate( double angle )
{
    if ( !_circle )
        Ellipse::rotate( angle );
    return *this;
}

Circle
Circle::rotated( double angle ) const
{
    return Circle(*this).rotate( angle );
}

Circle &
Circle::translate( double dx, double dy )
{
    _center += Point( dx, dy );
    return *this;
}

Circle
Circle::translated( double dx, double dy ) const
{
    return Circle(*this).translate( dx, dy );
}

Shape &
Circle::scale( double sx, double sy )
{
    return Ellipse::scale( sx, sy );
}

Shape &
Circle::scale( double s )
{
    return Ellipse::scale( s );
}

Circle
Circle::scaled( double sx, double sy ) const
{
    return static_cast<Circle &>( Circle(*this).scale( sx, sy ) );
}

Circle
Circle::scaled( double s ) const
{
    return static_cast<Circle &>( Circle(*this).scale( s, s ) );
}

void
Circle::scaleAll( double s )
{
    _center *= s;
    _xRadius *= s;
    _yRadius *= s;
}

Circle *
Circle::clone() const {
    return new Circle(*this);
}

void
Circle::flushSVG( std::ostream & stream,
                  const TransformSVG & transform ) const
{
    if ( ! _circle )
        Ellipse::flushSVG( stream, transform );
    else {
        stream << "<circle cx=\"" << transform.mapX( _center.x ) << '"'
        << " cy=\"" << transform.mapY( _center.y ) << '"'
        << " r=\"" << transform.scale( _xRadius ) << '"'
        << svgProperties( transform )
        << " />" << std::endl;
    }
}

#ifdef WITH_CAIRO
void
Circle::flushCairo( cairo_t *cr,
     const TransformCairo & transform ) const
{
    if ( ! _circle )
        Ellipse::flushCairo( cr, transform );
    else
    {
      cairo_save (cr);

  cairo_set_source_rgba (cr, _fillColor.red()/255.0, _fillColor.green()/255.0, _fillColor.blue()/255.0, 1.);
    
  cairo_arc (cr, transform.mapX( _center.x ), transform.mapY( _center.y ), transform.scale( _xRadius ), 0, 2*M_PI);
  
  if ( filled() )
  {
    if ( _penColor != DGtal::Color::None )
      cairo_fill_preserve (cr);
    else
      cairo_fill (cr);
  }
  
  //
  
  if ( _penColor != DGtal::Color::None )
  {
    cairo_set_source_rgba (cr, _penColor.red()/255.0, _penColor.green()/255.0, _penColor.blue()/255.0, 1.);
      
    cairo_set_line_width (cr, _lineWidth);
    cairo_set_line_cap (cr, cairoLineCap[_lineCap]);
    cairo_set_line_join (cr, cairoLineJoin[_lineJoin]);
    setCairoDashStyle (cr, _lineStyle);

    cairo_stroke (cr);
  }
      
      cairo_restore (cr);
    }
}
#endif

void
Circle::flushTikZ( std::ostream & stream,
                   const TransformTikZ & transform ) const
{
    if ( ! _circle )
        Ellipse::flushTikZ( stream, transform );
    else {
	stream << "\\path[" << tikzProperties(transform) << "] ("
	<< transform.mapX( _center.x ) << ','
        << transform.mapY( _center.y ) << ')'
	<< " circle (" << transform.scale( _xRadius ) << ");"
        << std::endl;
    }
}

/*
 * Arc
 */

const std::string Arc::_name("Arc");

const std::string &
Arc::name() const
{
    return _name;
}

#ifdef WITH_CAIRO
void
Arc::flushCairo( cairo_t *cr,
     const TransformCairo & transform ) const
{
    cairo_save (cr);

      cairo_set_source_rgba (cr, _fillColor.red()/255.0, _fillColor.green()/255.0, _fillColor.blue()/255.0, 1.);

      if (_negative) // important: here for Cairo we must inverse 'cairo_arc' and 'cairo_arc_negative' and change alpha with 2.*M_PI-alpha
  cairo_arc (cr, transform.mapX( _center.x ), transform.mapY( _center.y ), transform.scale( _xRadius ), 2.*M_PI-_angle1, 2.*M_PI-_angle2);
      else
  cairo_arc_negative (cr, transform.mapX( _center.x ), transform.mapY( _center.y ), transform.scale( _xRadius ), 2.*M_PI-_angle1, 2.*M_PI-_angle2);
      
      if ( filled() )
      {
  if ( _penColor != DGtal::Color::None )
    cairo_fill_preserve (cr);
  else
    cairo_fill (cr);
      }
      
      //
      
      if ( _penColor != DGtal::Color::None )
      {
  cairo_set_source_rgba (cr, _penColor.red()/255.0, _penColor.green()/255.0, _penColor.blue()/255.0, 1.);
    
  cairo_set_line_width (cr, _lineWidth);
  cairo_set_line_cap (cr, cairoLineCap[_lineCap]);
  cairo_set_line_join (cr, cairoLineJoin[_lineJoin]);
  setCairoDashStyle (cr, _lineStyle);

  cairo_stroke (cr);
      }
    
    cairo_restore (cr);
}
#endif

void
Arc::flushPostscript( std::ostream & stream,
		      const TransformEPS & transform ) const
{
  
//The arc is generated by sweeping a line segment of length r, and tied at the point (x-coord y-coord), in a counter-clockwise direction from an angle _angle1 to an angle _angle2. 
//Thus, we have to swap _angle1 and _angle2 according to bool _negative
  double a1, a2; 
  if (_negative == true)
  {
    a1 = _angle2;
    a2 = _angle1;
  } 
  else 
  {
    a1 = _angle1;
    a2 = _angle2;
  }

  stream << "\n% Arc\n";
    if ( filled() ) {
      stream << "gs "
	     << transform.mapX( _center.x ) << " " << transform.mapY( _center.y ) << " "
	     << transform.scale( _xRadius )<< " " << (a1*180/M_PI) << " "
	     << (a2*180/M_PI) << " "<< "arc ";
      stream << " " << _fillColor.postscript() << " srgb";
      stream << " fill gr" << std::endl;
    }

    if ( _penColor != DGtal::Color::None ) {

      stream << "gs "
	     << transform.mapX( _center.x ) << " " << transform.mapY( _center.y ) << " "
	     << transform.scale( _xRadius )<< " " << (a1*180/M_PI) << " "
	     << (a2*180/M_PI) << " "<< "arc ";
      _penColor.flushPostscript( stream );
      stream << " stroke gr" << std::endl;
    }
}

void
Arc::flushSVG( std::ostream & stream,
                  const TransformSVG & transform ) const
{

double fx = _center.x + _xRadius*std::cos(_angle1);
double fy = _center.y + _xRadius*std::sin(_angle1);
double lx = _center.x + _xRadius*std::cos(_angle2);
double ly = _center.y + _xRadius*std::sin(_angle2);

stream << "<path ";
stream << svgProperties( transform ) << " ";
//first point 
stream << "d='M " << transform.mapX( fx );
stream << "," << transform.mapY( fy );
//arc
stream << " A " << transform.scale( _xRadius ) << " " << transform.scale( _xRadius );
//something
stream << " 0"; 
//orientation and center position
if (_negative) 
{
  if ( (std::cos(_angle1)*std::sin(_angle2) - std::sin(_angle1)*std::cos(_angle2))<0 ) 
  {
    stream << " 0 1";
  } else
  {
    stream << " 1 1";
  }
} else 
{
  if ( (std::cos(_angle1)*std::sin(_angle2) - std::sin(_angle1)*std::cos(_angle2))<0 ) 
  {
    stream << " 1 0";
  } else
  {
    stream << " 0 0";
  }
}
//last point
stream << " " << transform.mapX( lx );
stream << "," << transform.mapY( ly );
stream << "' />";

}

void
Arc::flushTikZ( std::ostream & stream,
		const TransformTikZ & transform ) const
{
    stream << "\\path[" << tikzProperties(transform) << "] ("
	   << transform.mapX( _center.x ) << ',' << transform.mapY( _center.y ) << ')'	// center
	   << " +(" << -_angle1/M_PI*180. << ':' << transform.scale( _xRadius) << ')'	// first point of arc
           << " arc (" << -_angle1/M_PI*180. << ':' << -_angle2/M_PI*180. + _negative * 360. << ':' << transform.scale( _xRadius ) << ");"
	   << std::endl;
}

/*
 * Polyline
 */

const std::string Polyline::_name("Polyline");

const std::string &
Polyline::name() const
{
    return _name;
}

Polyline &
Polyline::operator<<( const Point & p )
{
    _path << p;
    return *this;
}

Point
Polyline::center() const {
    return _path.center();
}

Polyline &
Polyline::rotate( double angle, const Point & rotCenter )
{
    _path.rotate( angle, rotCenter );
    return *this;
}

Polyline
Polyline::rotated( double angle, const Point & rotCenter ) const
{
    return Polyline(*this).rotate( angle, rotCenter );
}

Polyline &
Polyline::rotate( double angle )
{
    _path.rotate( angle, center() );
    return *this;
}

Polyline
Polyline::rotated( double angle ) const
{
    return Polyline(*this).rotate( angle, center() );
}

Polyline &
Polyline::translate( double dx, double dy )
{
    _path.translate( dx, dy );
    return *this;
}

Polyline
Polyline::translated( double dx, double dy ) const
{
    return Polyline(*this).translate( dx, dy );
}

Shape &
Polyline::scale( double sx, double sy )
{
    _path.scale( sx, sy );
    return *this;
}

Shape &
Polyline::scale( double s )
{
    Polyline::scale( s, s );
    return *this;
}

Polyline
Polyline::scaled( double sx, double sy ) const
{
    return static_cast<Polyline &>( Polyline(*this).scale( sx, sy ) );
}

Polyline
Polyline::scaled( double s) const
{
    return static_cast<Polyline &>( Polyline(*this).scale( s, s ) );
}

void
Polyline::scaleAll( double s )
{
    _path.scaleAll( s );
}

Polyline *
Polyline::clone() const {
    return new Polyline(*this);
}

void
Polyline::flushPostscript( std::ostream & stream,
                           const TransformEPS & transform ) const
{
    if ( _path.empty() ) return;
    stream << "\n% Polyline\n";
    if ( filled() ) {
        stream << "n ";
        _path.flushPostscript( stream, transform );
        stream << " ";
        _fillColor.flushPostscript( stream );
  stream << " " << postscriptProperties();
        stream << " fill" << std::endl;
    }
    if ( _penColor != DGtal::Color::None ) {
        stream << " " << postscriptProperties() << "\n";
        stream << "n ";
        _path.flushPostscript( stream, transform );
        stream << " ";
        _penColor.flushPostscript( stream );
        stream << " stroke" << std::endl;
    }
}

void
Polyline::flushFIG( std::ostream & stream,
                    const TransformFIG & transform,
                    std::map<DGtal::Color,int> & colormap ) const
{
    if ( _path.empty() )
        return;
    if ( _path.closed() )
        stream << "2 3 " << _lineStyle << " ";
    else
        stream << "2 1 " << _lineStyle << " ";
    // Thickness
    stream << ( _penColor.valid()?transform.mapWidth( _lineWidth ):0 ) << " ";
    // Pen color
    stream << colormap[ _penColor ] << " ";
    // Fill color
    stream << colormap[ _fillColor ] << " ";
    // Depth
    stream << transform.mapDepth( _depth ) << " ";
    // Pen style
    stream <<  "-1 ";
    // Area fill, style val, join style, cap style, radius, f_arrow, b_arrow
    if ( filled() )
        stream << "20 " << (_lineStyle?"4.000 ":"0.000 ") << _lineJoin << " " << _lineCap << " -1 0 0 ";
    else
        stream << "-1 " << (_lineStyle?"4.000 ":"0.000 ")  << _lineJoin << " " << _lineCap << " -1 0 0 ";
    // Number of points
    stream << _path.size() + _path.closed() << std::endl;
    _path.flushFIG( stream << "         ", transform );
    stream << std::endl;
}

void
Polyline::flushSVG( std::ostream & stream,
                    const TransformSVG & transform ) const
{
    if ( _path.empty() )
        return;
    if ( _path.closed() )
        stream << "<polygon";
    else
        stream << "<polyline";
    stream << svgProperties( transform ) << std::endl;
    stream << "          points=\"";
    _path.flushSVGPoints( stream, transform );
    stream << "\" />" << std::endl;
}

#ifdef WITH_CAIRO
void
Polyline::flushCairo( cairo_t *cr,
     const TransformCairo & transform ) const
{
    if ( _path.empty() )
        return;
    
    cairo_save (cr);
    
      cairo_set_source_rgba (cr, _fillColor.red()/255.0, _fillColor.green()/255.0, _fillColor.blue()/255.0, 1.);
  
      _path.flushCairoPoints( cr, transform );
      if ( _path.closed() )
  cairo_close_path (cr);
      
      if ( filled() )
      {
  if ( _penColor != DGtal::Color::None )
    cairo_fill_preserve (cr);
  else
    cairo_fill (cr);
      }
      
      //
      
      if ( _penColor != DGtal::Color::None )
      {
  cairo_set_source_rgba (cr, _penColor.red()/255.0, _penColor.green()/255.0, _penColor.blue()/255.0, 1.);
  
  cairo_set_line_width (cr, _lineWidth);
  cairo_set_line_cap (cr, cairoLineCap[_lineCap]);
  cairo_set_line_join (cr, cairoLineJoin[_lineJoin]);
  setCairoDashStyle (cr, _lineStyle);

  cairo_stroke (cr);
      }
    
    cairo_restore (cr);
}
#endif

void
Polyline::flushTikZ( std::ostream & stream,
                     const TransformTikZ & transform ) const
{
    if ( _path.empty() )
        return;

    stream << "\\path[" << tikzProperties(transform) << "] ";
    //stream << svgProperties( transform ) << std::endl;

    _path.flushTikZPoints( stream, transform );

    if ( _path.closed() )
        stream << " -- cycle";
    stream << ";" << std::endl;
}

Rect
Polyline::boundingBox() const
{
    return _path.boundingBox();
}

/*
 * Rectangle
 */

const std::string Rectangle::_name("Rectangle");

const std::string &
Rectangle::name() const
{
    return _name;
}

Rectangle
Rectangle::rotated( double angle, const Point & rotCenter ) const
{
    return static_cast<Rectangle &>( Rectangle(*this).rotate( angle, rotCenter ) );
}

Rectangle
Rectangle::rotated( double angle ) const
{
    return static_cast<Rectangle &>( Rectangle(*this).rotate( angle, center() ) );
}

Rectangle
Rectangle::translated( double dx, double dy ) const
{
    return static_cast<Rectangle &>( Rectangle(*this).translate( dx, dy ) );
}

Rectangle
Rectangle::scaled( double sx, double sy ) const
{
    return static_cast<Rectangle &>( Rectangle(*this).scale( sx, sy ) );
}

Rectangle
Rectangle::scaled( double s ) const
{
    return static_cast<Rectangle &>( Rectangle(*this).scale( s, s ) );
}

void
Rectangle::scaleAll( double s )
{
    _path.scaleAll( s );
}

Rectangle *
Rectangle::clone() const {
    return new Rectangle(*this);
}

void
Rectangle::flushFIG( std::ostream & stream,
                     const TransformFIG & transform,
                     std::map<DGtal::Color,int> & colormap ) const
{
  if ( _path[0].y != _path[1].y ) {
        Polyline::flushFIG( stream, transform, colormap );
        return;
    }
    if ( _path[0].x != _path[3].x ) {
        Polyline::flushFIG( stream, transform, colormap );
        return;
    }
    {
        double x1 = _path[1].x - _path[0].x;
        double y1 = _path[1].y - _path[0].y;
        double x2 = _path[3].x - _path[0].x;
        double y2 = _path[3].y - _path[0].y;
        if ( fabs(x1*x2 + y1*y2) > 0.01 ) {
            Polyline::flushFIG( stream, transform, colormap );
            return;
        }
    }

    stream << "2 2 " << _lineStyle << " ";
    // Thickness
    stream << ( _penColor.valid()?transform.mapWidth( _lineWidth ):0 ) << " ";
    // Pen color
    stream << colormap[ _penColor ] << " ";
    // Fill color
    stream << colormap[ _fillColor ] << " ";
    // Depth
    stream << transform.mapDepth( _depth ) << " ";
    // Pen style
    stream <<  "-1 ";
    // Area fill, style val, join style, cap style, radius, f_arrow, b_arrow, number of points
    if ( filled() )
        stream << "20 " << (_lineStyle?"4.000 ":"0.000 ") << _lineJoin << " " << _lineCap << " -1 0 0 5\n";
    else
        stream << "-1 " << (_lineStyle?"4.000 ":"0.000 ") << _lineJoin << " " << _lineCap << " -1 0 0 5\n";
    stream << "         ";
    _path.flushFIG( stream, transform );
    stream << std::endl;
}

void
Rectangle::flushSVG( std::ostream & stream,
                     const TransformSVG & transform ) const
{
    {
        double x1 = _path[1].x - _path[0].x;
        double y1 = _path[1].y - _path[0].y;
        double x2 = _path[3].x - _path[0].x;
        double y2 = _path[3].y - _path[0].y;
        if ( fabs(x1*x2 + y1*y2) > 0.01  ) {
            Polyline::flushSVG( stream, transform );
            return;
        }
    }

    if ( _path[0].y == _path[1].y ) {
        stream << "<rect x=\"" << transform.mapX( _path[0].x ) << '"'
        << " y=\"" << transform.mapY( _path[0].y )  << '"'
        << " width=\"" << transform.scale( _path[1].x - _path[0].x ) << '"'
        << " height=\"" << transform.scale( _path[0].y - _path[3].y ) << '"'
        << svgProperties( transform )
        << " />" << std::endl;
    } else {
        Point v = _path[1] - _path[0];
        v /= v.norm();
        double angle = ( _path[1].y > _path[0].y ) ? acos( v * Point(1,0) ) : -acos( v * Point( 1, 0 ) );
        angle = ( angle * 180 ) / M_PI;
        stream << "<rect x=\"" << transform.mapX( _path[0].x ) << '"'
        << " y=\"" << transform.mapY( _path[0].y )  << '"'
        << " width=\"" << transform.scale( (_path[1] - _path[0]).norm() ) << '"'
        << " height=\"" << transform.scale( (_path[0] - _path[3]).norm() ) << '"'
        << svgProperties( transform ) << ' '
        << " transform=\"rotate(" << -angle << ", "
        << transform.mapX( _path[0].x ) << ", " << transform.mapY( _path[0].y ) << ") \" "
        << " />" << std::endl;
    }
}

#ifdef WITH_CAIRO
void
Rectangle::flushCairo( cairo_t *cr,
     const TransformCairo & transform ) const
{
    {
        double x1 = _path[1].x - _path[0].x;
        double y1 = _path[1].y - _path[0].y;
        double x2 = _path[3].x - _path[0].x;
        double y2 = _path[3].y - _path[0].y;
        if ( fabs(x1*x2 + y1*y2) > 0.01  ) {
            Polyline::flushCairo( cr, transform );
            return;
        }
    }
    
    cairo_save (cr);
    
      cairo_set_source_rgba (cr, _fillColor.red()/255.0, _fillColor.green()/255.0, _fillColor.blue()/255.0, 1.);
  
      if ( _path[0].y == _path[1].y )
  cairo_rectangle (cr, transform.mapX( _path[0].x ), transform.mapY( _path[0].y ), transform.scale( _path[1].x - _path[0].x ), transform.scale( _path[0].y - _path[3].y ));
      else
      {
  Point v = _path[1] - _path[0];
        v /= v.norm();
        double angle = ( _path[1].y > _path[0].y ) ? acos( v * Point(1,0) ) : -acos( v * Point( 1, 0 ) );
  
  // tr
  cairo_translate (cr, transform.mapX( _path[0].x )+transform.scale( _path[1].x - _path[0].x )/2., transform.mapY( _path[0].y )+transform.scale( _path[0].y - _path[3].y )/2.);
  cairo_rotate (cr, angle);
  // tr
  
  cairo_rectangle (cr, -transform.scale( _path[1].x - _path[0].x )/2., -transform.scale( _path[0].y - _path[3].y )/2., transform.scale( (_path[1] - _path[0]).norm() ), transform.scale( (_path[0] - _path[3]).norm() ));
      }
      
      if ( filled() )
      {
  if ( _penColor != DGtal::Color::None )
    cairo_fill_preserve (cr);
  else
    cairo_fill (cr);
      }
      
      //
      
      if ( _penColor != DGtal::Color::None )
      {
  cairo_set_source_rgba (cr, _penColor.red()/255.0, _penColor.green()/255.0, _penColor.blue()/255.0, 1.);
  
  cairo_set_line_width (cr, _lineWidth);
  cairo_set_line_cap (cr, cairoLineCap[_lineCap]);
  cairo_set_line_join (cr, cairoLineJoin[_lineJoin]);
  setCairoDashStyle (cr, _lineStyle);

  cairo_stroke (cr);
      }
    
    cairo_restore (cr);
}
#endif

void
Rectangle::flushTikZ( std::ostream & stream,
                      const TransformTikZ & transform ) const
{
    Polyline::flushTikZ( stream, transform );
    return;

    stream << "\\path[" << tikzProperties(transform) << "] ("
      << _path[0].x << ',' << _path[0].y << ')'
      << " rectangle ("
      << _path[1].x << ',' << _path[3].y << "); ";
}

/*
 * GouraudTriangle
 */

const std::string GouraudTriangle::_name("GouraudTriangle");

const std::string &
GouraudTriangle::name() const
{
    return _name;
}

GouraudTriangle::GouraudTriangle( const Point & p0, const DGtal::Color & color0,
                                  const Point & p1, const DGtal::Color & color1,
                                  const Point & p2, const DGtal::Color & color2,
                                  int subdivisions,
                                  int depthValue )
        : Polyline( std::vector<Point>(), true, DGtal::Color::None, DGtal::Color::None,
                    0.0f, SolidStyle, ButtCap, MiterJoin, depthValue ),
        _color0( color0 ), _color1( color1 ), _color2( color2 ), _subdivisions( subdivisions ) {
    _path << p0;
    _path << p1;
    _path << p2;

    Shape::_fillColor.red( ( color0.red() + color1.red() + color2.red() ) / 3 );
    Shape::_fillColor.green( ( color0.green() + color1.green() + color2.green() ) / 3 );
    Shape::_fillColor.blue( ( color0.blue() + color1.blue() + color2.blue() ) / 3 );
}

GouraudTriangle::GouraudTriangle( const Point & p0, float brightness0,
                                  const Point & p1, float brightness1,
                                  const Point & p2, float brightness2,
                                  const DGtal::Color & fill,
                                  int subdivisions,
                                  int depthValue )
        : Polyline( std::vector<Point>(), true, DGtal::Color::None, DGtal::Color::None,
                    0.0f, SolidStyle, ButtCap, MiterJoin, depthValue ),
    _color0( fill ), _color1( fill ), _color2( fill ), _subdivisions( subdivisions )
{
    _path << p0;
    _path << p1;
    _path << p2;
    _color0.red( static_cast<unsigned char>( std::min( 255.0f, _color0.red() * brightness0 ) ) );
    _color0.green( static_cast<unsigned char>( std::min( 255.0f, _color0.green() * brightness0 ) ) );
    _color0.blue( static_cast<unsigned char>( std::min( 255.0f, _color0.blue() * brightness0 ) ) );
    _color1.red( static_cast<unsigned char>( std::min( 255.0f, _color1.red() * brightness1 ) ) );
    _color1.green( static_cast<unsigned char>( std::min( 255.0f, _color1.green() * brightness1 ) ) );
    _color1.blue( static_cast<unsigned char>( std::min( 255.0f, _color1.blue() * brightness1 ) ) );
    _color2.red( static_cast<unsigned char>( std::min( 255.0f, _color2.red() * brightness2 ) ) );
    _color2.green( static_cast<unsigned char>( std::min( 255.0f, _color2.green() * brightness2 ) ) );
    _color2.blue( static_cast<unsigned char>( std::min( 255.0f, _color2.blue() * brightness2 ) ) );

    Shape::_fillColor.red( ( _color0.red() + _color1.red() + _color2.red() ) / 3 );
    Shape::_fillColor.green( ( _color0.green() + _color1.green() + _color2.green() ) / 3 );
    Shape::_fillColor.blue( ( _color0.blue() + _color1.blue() + _color2.blue() ) / 3 );
}

Point
GouraudTriangle::center() const {
    return ( _path[0] + _path[1] + _path[2] ) / 3.0;
}

GouraudTriangle &
GouraudTriangle::rotate( double angle, const Point & rotCenter )
{
    _path.rotate( angle, rotCenter );
    return *this;
}

GouraudTriangle
GouraudTriangle::rotated( double angle, const Point & rotCenter ) const
{
    return GouraudTriangle(*this).rotate( angle, rotCenter );
}

GouraudTriangle &
GouraudTriangle::rotate( double angle )
{
    return GouraudTriangle::rotate( angle, center() );
}

GouraudTriangle
GouraudTriangle::rotated( double angle ) const
{
    return GouraudTriangle(*this).rotate( angle, center() );
}

GouraudTriangle
GouraudTriangle::translated( double dx, double dy ) const
{
    return static_cast<GouraudTriangle &>( GouraudTriangle(*this).translate( dx, dy ) );
}

GouraudTriangle
GouraudTriangle::scaled( double sx, double sy ) const
{
    return static_cast<GouraudTriangle &>( GouraudTriangle(*this).scale( sx, sy ) );
}

GouraudTriangle
GouraudTriangle::scaled( double s ) const
{
    return static_cast<GouraudTriangle &>( GouraudTriangle(*this).scale( s, s ) );
}

void
GouraudTriangle::scaleAll( double s )
{
    _path.scaleAll( s );
}

GouraudTriangle *
GouraudTriangle::clone() const {
    return new GouraudTriangle(*this);
}

void
GouraudTriangle::flushPostscript( std::ostream & stream,
                                  const TransformEPS & transform ) const
{
    if ( ! _subdivisions ) {
        Polyline::flushPostscript( stream, transform );
        return;
    }
    const Point & p0 = _path[0];
    const Point & p1 = _path[1];
    const Point & p2 = _path[2];
    Point p01( 0.5*(p0.x+p1.x), 0.5*(p0.y+p1.y) );
    DGtal::Color c01( (_color0.red() + _color1.red())/2,
               (_color0.green() + _color1.green())/2,
               (_color0.blue() + _color1.blue())/2 );
    Point p12( 0.5*(p1.x+p2.x), 0.5*(p1.y+p2.y) );
    DGtal::Color c12( (_color1.red() + _color2.red())/2,
               (_color1.green() + _color2.green())/2,
               (_color1.blue() + _color2.blue())/2 );
    Point p20( 0.5*(p2.x+p0.x), 0.5*(p2.y+p0.y) );
    DGtal::Color c20( (_color2.red() + _color0.red())/2,
               (_color2.green() + _color0.green())/2,
               (_color2.blue() + _color0.blue())/2 );
    GouraudTriangle( p0, _color0, p20, c20, p01, c01, _subdivisions - 1, _depth ).flushPostscript( stream, transform );
    GouraudTriangle( p1, _color1, p01, c01, p12, c12, _subdivisions - 1, _depth ).flushPostscript( stream, transform );
    GouraudTriangle( p2, _color2, p20, c20, p12, c12, _subdivisions - 1, _depth ).flushPostscript( stream, transform );
    GouraudTriangle( p01, c01, p12, c12, p20, c20,  _subdivisions - 1, _depth ).flushPostscript( stream, transform );
}

void
GouraudTriangle::flushFIG( std::ostream & stream,
                           const TransformFIG & transform,
                           std::map<DGtal::Color,int> & colormap ) const
{

    DGtal::Color c( static_cast<unsigned char>((_color0.red() + _color1.red() + _color2.red() )/3.0),
             static_cast<unsigned char>((_color0.green() + _color1.green() + _color2.green())/3.0),
             static_cast<unsigned char>((_color0.blue() + _color1.blue() + _color2.blue())/3.0 ));
    Polyline( _path, DGtal::Color::None, c, 0.0f ).flushFIG( stream, transform, colormap );

    // if ( ! _subdivisions ) {
    // Polyline::flushFIG( stream, transform, colormap );
    // return;
    // }
// TODO : Handle extended colormap through clustering...
//   const Point & p0 = _points[0];
//   const Point & p1 = _points[1];
//   const Point & p2 = _points[2];
//   Point p01( 0.5*(p0.x+p1.x), 0.5*(p0.y+p1.y) );
//   DGtal::Color c01( (_color0.red() + _color1.red())/2,
//        (_color0.green() + _color1.green())/2,
//        (_color0.blue() + _color1.blue())/2 );
//   Point p12( 0.5*(p1.x+p2.x), 0.5*(p1.y+p2.y) );
//   DGtal::Color c12( (_color1.red() + _color2.red())/2,
//        (_color1.green() + _color2.green())/2,
//        (_color1.blue() + _color2.blue())/2 );
//   Point p20( 0.5*(p2.x+p0.x), 0.5*(p2.y+p0.y) );
//   DGtal::Color c20( (_color2.red() + _color0.red())/2,
//        (_color2.green() + _color0.green())/2,
//        (_color2.blue() + _color0.blue())/2 );
//   GouraudTriangle( p0, _color0, p20, c20, p01, c01, _subdivisions - 1, _depth ).flushFIG( stream, transform, colormap );
//   GouraudTriangle( p1, _color1, p01, c01, p12, c12, _subdivisions - 1, _depth ).flushFIG( stream, transform, colormap );
//   GouraudTriangle( p2, _color2, p20, c20, p12, c12, _subdivisions - 1, _depth ).flushFIG( stream, transform, colormap );
//   GouraudTriangle( p01, c01, p12, c12, p20, c20,  _subdivisions - 1, _depth ).flushFIG( stream, transform, colormap );
}

void
GouraudTriangle::flushSVG( std::ostream & stream,
                           const TransformSVG & transform ) const
{
    if ( ! _subdivisions ) {
        Polyline::flushSVG( stream, transform );
        return;
    }
    const Point & p0 = _path[0];
    const Point & p1 = _path[1];
    const Point & p2 = _path[2];
    Point p01( 0.5*(p0.x+p1.x), 0.5*(p0.y+p1.y) );
    DGtal::Color c01( (_color0.red() + _color1.red())/2,
               (_color0.green() + _color1.green())/2,
               (_color0.blue() + _color1.blue())/2 );
    Point p12( 0.5*(p1.x+p2.x), 0.5*(p1.y+p2.y) );
    DGtal::Color c12( (_color1.red() + _color2.red())/2,
               (_color1.green() + _color2.green())/2,
               (_color1.blue() + _color2.blue())/2 );
    Point p20( 0.5*(p2.x+p0.x), 0.5*(p2.y+p0.y) );
    DGtal::Color c20( (_color2.red() + _color0.red())/2,
               (_color2.green() + _color0.green())/2,
               (_color2.blue() + _color0.blue())/2 );
    GouraudTriangle( p0, _color0, p20, c20, p01, c01,
                     _subdivisions - 1, _depth ).flushSVG( stream, transform );
    GouraudTriangle( p1, _color1, p01, c01, p12, c12,
                     _subdivisions - 1, _depth ).flushSVG( stream, transform );
    GouraudTriangle( p2, _color2, p20, c20, p12, c12,
                     _subdivisions - 1, _depth ).flushSVG( stream, transform );
    GouraudTriangle( p01, c01, p12, c12, p20, c20,
                     _subdivisions - 1, _depth ).flushSVG( stream, transform );
}

#ifdef WITH_CAIRO
void
GouraudTriangle::flushCairo( cairo_t * /*cr*/,
			     const TransformCairo & /*transform*/ ) const
{
}
#endif

void
GouraudTriangle::flushTikZ( std::ostream & stream,
			    const TransformTikZ & /*transform*/ ) const
{
  // FIXME: unimplemented
  stream << "% FIXME: GouraudTriangle::flushTikZ unimplemented" << std::endl;
}

/*
 * Triangle
 */

const std::string Triangle::_name("Triangle");

const std::string &
Triangle::name() const
{
    return _name;
}

Triangle
Triangle::rotated( double angle ) const
{
    return static_cast<Triangle &>( Triangle( *this ).rotate( angle ) );
}

Triangle
Triangle::translated( double dx, double dy ) const
{
    return static_cast<Triangle &>( Triangle( *this ).translate( dx, dy ) );
}

Triangle
Triangle::scaled( double sx, double sy ) const
{
    return static_cast<Triangle &>( Triangle( *this ).scale( sx, sy ) );
}

Triangle
Triangle::scaled( double s ) const
{
    return static_cast<Triangle &>( Triangle( *this ).scale( s ) );
}

Triangle *
Triangle::clone() const {
    return new Triangle(*this);
}

/*
 * QuadraticBezierCurve
 */
const std::string QuadraticBezierCurve::_name("QuadraticBezierCurve");

const std::string &
QuadraticBezierCurve::name() const
{
    return _name;
}

void
QuadraticBezierCurve::flushPostscript( std::ostream & stream,
                           const TransformEPS & transform ) const
{
  double x1, y1, x2, y2, x3, y3, x4, y4; //coordinates of the control points
  _path[ 0 ].get(x1, y1);
  _path[ 1 ].get(x3, y3);
  _path[ 2 ].get(x4, y4);
  //we compute the two middle control points of a cubic Bezier curve
  //from the three control points of the quadratic Bezier curve
  x2 = x1 + 2/3.0*(x3-x1); 
  y2 = y1 + 2/3.0*(y3-y1); 
  x3 = x2 + 1/3.0*(x4-x1); 
  y3 = y2 + 1/3.0*(y4-y1); 

  stream << std::endl << "% Bezier curve" << std::endl;
  if ( _fillColor != DGtal::Color::None ) {
    stream << "n "
	   << transform.mapX( x1 ) << " "
	   << transform.mapY( y1 ) << " "
	   << "m "
	   << transform.mapX( x2 ) << " "
	   << transform.mapY( y2 ) << " "
	   << transform.mapX( x3 ) << " "
	   << transform.mapY( y3 ) << " "
	   << transform.mapX( x4 ) << " "
	   << transform.mapY( y4 ) << " "
	   << "curveto ";  
      _fillColor.flushPostscript( stream );
      stream << " " << postscriptProperties();
      stream << " fill" << std::endl;
  }
  if ( _penColor != DGtal::Color::None ) {
    stream << " " << postscriptProperties() << " "; 
    stream << "n "
	   << transform.mapX( x1 ) << " "
	   << transform.mapY( y1 ) << " "
	   << "m "
	   << transform.mapX( x2 ) << " "
	   << transform.mapY( y2 ) << " "
	   << transform.mapX( x3 ) << " "
	   << transform.mapY( y3 ) << " "
	   << transform.mapX( x4 ) << " "
	   << transform.mapY( y4 ) << " "
	   << "curveto ";  
    _penColor.flushPostscript( stream );
    stream << " stroke" << std::endl;
  }
}

void
QuadraticBezierCurve::flushFIG( std::ostream & stream,
     const TransformFIG & transform,
     std::map<DGtal::Color,int> & colormap ) const
{
  stream << "#FIXME: quadratic Bezier curve unimplemented" << std::endl; 
  Triangle::flushFIG(stream, transform, colormap); 
}

void
QuadraticBezierCurve::flushSVG( std::ostream & stream,
                           const TransformSVG & transform ) const
{
  double x1, y1, x2, y2, x3, y3; //coordinates of the control points
  _path[ 0 ].get(x1, y1);
  _path[ 1 ].get(x2, y2);
  _path[ 2 ].get(x3, y3);

  stream << "<path ";
  stream << svgProperties( transform ) << " ";
  //first point 
  stream << "d='M " << transform.mapX( x1 );
  stream << "," << transform.mapY( y1 );
  //arc
  stream << " Q " << transform.mapX( x2 ) << "," << transform.mapY( y2 );
  //last point
  stream << " " << transform.mapX( x3 );
  stream << "," << transform.mapY( y3 );
  stream << "' />";
}

#ifdef WITH_CAIRO
void
QuadraticBezierCurve::flushCairo( cairo_t *cr,
     const TransformCairo & transform ) const
{
  double x1, y1, x2, y2, x3, y3, x4, y4; //coordinates of the control points
  _path[ 0 ].get(x1, y1);
  _path[ 1 ].get(x3, y3);
  _path[ 2 ].get(x4, y4);
  //we compute the two middle control points of a cubic Bezier curve
  //from the three control points of the quadratic Bezier curve
  x2 = x1 + 2/3.0*(x3-x1); 
  y2 = y1 + 2/3.0*(y3-y1); 
  x3 = x2 + 1/3.0*(x4-x1); 
  y3 = y2 + 1/3.0*(y4-y1); 

  cairo_save (cr);

  cairo_set_source_rgba (cr, _fillColor.red()/255.0, _fillColor.green()/255.0, _fillColor.blue()/255.0, 1.);

  cairo_move_to( cr, transform.mapX( x1 ), transform.mapY( y1 ) ); 
  cairo_curve_to( cr, transform.mapX( x2 ), transform.mapY( y2 ), 
		  transform.mapX( x3 ), transform.mapY( y3 ), 
		  transform.mapX( x4 ), transform.mapY( y4 ) ); 

  if ( filled() )
    {
      if ( _penColor != DGtal::Color::None )
  	cairo_fill_preserve (cr);
      else
  	cairo_fill (cr);
    }
      
  if ( _penColor != DGtal::Color::None )
    {
      cairo_set_source_rgba (cr, _penColor.red()/255.0, _penColor.green()/255.0, _penColor.blue()/255.0, 1.);
    
      cairo_set_line_width (cr, _lineWidth);
      cairo_set_line_cap (cr, cairoLineCap[_lineCap]);
      cairo_set_line_join (cr, cairoLineJoin[_lineJoin]);
      setCairoDashStyle (cr, _lineStyle);

      cairo_stroke (cr);
    }
    
  cairo_restore (cr);
}
#endif

void
QuadraticBezierCurve::flushTikZ( std::ostream & stream,
                           const TransformTikZ & transform ) const
{
  double x1, y1, x2, y2, x3, y3, x4, y4; //coordinates of the control points
  _path[ 0 ].get(x1, y1);
  _path[ 1 ].get(x3, y3);
  _path[ 2 ].get(x4, y4);
  //we compute the two middle control points of a cubic Bezier curve
  //from the three control points of the quadratic Bezier curve
  x2 = x1 + 2/3.0*(x3-x1); 
  y2 = y1 + 2/3.0*(y3-y1); 
  x3 = x2 + 1/3.0*(x4-x1); 
  y3 = y2 + 1/3.0*(y4-y1); 

  stream << "\\draw[" << tikzProperties(transform) << "] ("
	 << transform.mapX( x1 ) << ',' << transform.mapY( y1 )
	 << ") .. controls ("
	 << transform.mapX( x2 ) << ',' << transform.mapY( y2 )
	 << ") and ("
	 << transform.mapX( x3 ) << ',' << transform.mapY( y3 )
	 << ") .. ("
	 << transform.mapX( x4 ) << ',' << transform.mapY( y4 )
	 << ");" << std::endl;
}


/*
 * Text
 */

const std::string Text::_name("Text");

const std::string &
Text::name() const
{
    return _name;
}

Point
Text::center() const {
    return _position;
}

Text &
Text::rotate( double angle, const Point & rotCenter )
{
    Point endPos = _position + Point( 10000 * cos( _angle ), 10000 * sin( _angle ) );
    _position.rotate( angle, rotCenter );
    endPos.rotate( angle, rotCenter );
    Point v = endPos - _position;
    v /= v.norm();
    if ( v.x >= 0 ) _angle = asin( v.y );
    else if ( v.y > 0 ) _angle = (M_PI/2.0) + acos( v.y );
    else _angle = (-M_PI/2.0) - acos( -v.y );
    return *this;
}

Text
Text::rotated( double angle, const Point & rotCenter ) const
{
    return Text(*this).rotate( angle, rotCenter );
}

Text &
Text::rotate( double angle )
{
    _angle += angle;
    if ( _angle < 0 )
        while ( _angle < M_PI ) _angle += 2 * M_PI;
    if ( _angle > 0 )
        while ( _angle > M_PI ) _angle -= 2 * M_PI;
    return *this;
}

Text
Text::rotated( double angle ) const
{
    return Text(*this).rotate( angle );
}

Text &
Text::translate( double dx, double dy )
{
    _position += Point( dx, dy );
    return *this;
}

Text
Text::translated( double dx, double dy ) const
{
    return static_cast<Text&>( Text(*this).translate( dx, dy ) );
}

Shape &
Text::scale( double sx, double sy )
{
    _xScale = sx;
    _yScale = sy;
    return *this;
}

Shape &
Text::scale( double s )
{
    _xScale = _yScale = s;
    return *this;
}

Text
Text::scaled( double sx, double sy ) const
{
    return static_cast<Text &>( Text(*this).scale( sx, sy ) );
}

Text
Text::scaled( double s ) const
{
    return static_cast<Text &>( Text(*this).scale( s, s ) );
}

void
Text::scaleAll( double s )
{
    _position *= s;
}

Text *
Text::clone() const {
    return new Text(*this);
}

void
Text::flushPostscript( std::ostream & stream,
                       const TransformEPS & transform ) const
{
    stream << "\n% Text\n";
    stream << "gs /" << PSFontNames[ _font ] << " ff " << _size << " scf sf";
    stream << " " << transform.mapX( _position.x ) << " " << transform.mapY( _position.y ) << " m";
    if ( _angle != 0.0 ) stream << " " << (_angle/M_PI)*180.0 << " rot ";
    stream << " (" << _text << ")"
    << " " << _penColor.postscript() << " srgb"
    << " sh gr" << std::endl;
}

void
Text::flushFIG( std::ostream & stream,
                const TransformFIG & transform,
                std::map<DGtal::Color,int> & colormap ) const
{
    stream << "4 0 " ;
    // Color, depth, unused, Font
    stream << colormap[ _penColor ] <<  " " << transform.mapDepth( _depth ) << " -1 " << _font << " ";
    // Font size, Angle, Font flags
    stream << _size << " " << _angle << " 4 ";
    // Height
    stream << static_cast<int>(  _size * 135 / 12.0 ) << " ";
    // Width
    stream << static_cast<int>( _text.size() * _size * 135 / 12.0 ) << " ";
    // x y
    stream << static_cast<int>( transform.mapX( _position.x ) ) << " "
    << static_cast<int>( transform.mapY( _position.y ) ) << " ";
    stream << _text << "\\001\n";
}

void
Text::flushSVG( std::ostream & stream,
                const TransformSVG & transform ) const
{
    if ( _angle != 0.0f ) {
        stream << "<g transform=\"translate("
        << transform.mapX( _position.x ) << ","
        << transform.mapY( _position.y ) << ")\" >"
        << "<g transform=\"rotate(" << (-_angle*180.0/M_PI) << ")\" >"
        << "<text x=\"0\" y=\"0\""
        << " font-family=\"" << ( _svgFont.length() ? _svgFont : PSFontNames[ _font ] ) << "\""
        << " font-size=\"" << _size << "\""
        << " fill=\"" << _penColor.svg() << "\""
        << _fillColor.svgAlpha( " fill" )
        << _penColor.svgAlpha( " stroke" )
        << ">"
        << _text
        << "</text></g></g>" << std::endl;
    } else {
        stream << "<text x=\"" << transform.mapX( _position.x )
        << "\" y=\"" << transform.mapY( _position.y ) << "\" "
        << " font-family=\"" << ( _svgFont.length() ? _svgFont : PSFontNames[ _font ] ) << "\""
        << " font-size=\"" << _size << "\""
        << " fill=\"" << _penColor.svg() << "\""
        << _fillColor.svgAlpha( " fill" )
        << _penColor.svgAlpha( " stroke" )
        << ">"
        << _text
        << "</text>" << std::endl;
    }
}

#ifdef WITH_CAIRO
void
Text::flushCairo( cairo_t * /*cr*/,
		  const TransformCairo & /*transform*/ ) const
{
}
#endif

void
Text::flushTikZ( std::ostream & stream,
		 const TransformTikZ & transform ) const
{
  // FIXME: honor font-size
#define BOLD_FONT	0x01
#define ITALIC_FONT	0x02
#define MONOSPACE_FONT	0x04
#define SANSSERIF_FONT	0x08
    char fontTraits[] = {
	0,						// TimesRoman,
	ITALIC_FONT,					// TimesItalic,
	BOLD_FONT,					// TimesBold,
	BOLD_FONT | ITALIC_FONT,			// TimesBoldItalic,
	SANSSERIF_FONT,					// AvantGardeBook,
	SANSSERIF_FONT | ITALIC_FONT,			// AvantGardeBookOblique,
	SANSSERIF_FONT,					// AvantGardeDemi,
	SANSSERIF_FONT | ITALIC_FONT,			// AvantGardeDemiOblique,
	0,						// BookmanLight,
	ITALIC_FONT,					// BookmanLightItalic,
	0,						// BookmanDemi,
	ITALIC_FONT,					// BookmanDemiItalic,
	MONOSPACE_FONT,					// Courier,
	MONOSPACE_FONT | ITALIC_FONT,			// CourierOblique,
	MONOSPACE_FONT | BOLD_FONT,			// CourierBold,
	MONOSPACE_FONT | BOLD_FONT | ITALIC_FONT,	// CourierBoldOblique,
	SANSSERIF_FONT,					// Helvetica,
	SANSSERIF_FONT | ITALIC_FONT,			// HelveticaOblique,
	SANSSERIF_FONT | BOLD_FONT,			// HelveticaBold,
	SANSSERIF_FONT | BOLD_FONT | ITALIC_FONT,	// HelveticaBoldOblique,
	SANSSERIF_FONT,					// HelveticaNarrow,
	SANSSERIF_FONT | ITALIC_FONT,			// HelveticaNarrowOblique,
	SANSSERIF_FONT | BOLD_FONT,			// HelveticaNarrowBold,
	SANSSERIF_FONT | BOLD_FONT | ITALIC_FONT,	// HelveticaNarrowBoldOblique,
	0,						// NewCenturySchoolbookRoman,
	ITALIC_FONT,					// NewCenturySchoolbookItalic,
	BOLD_FONT,					// NewCenturySchoolbookBold,
	BOLD_FONT | ITALIC_FONT,			// NewCenturySchoolbookBoldItalic,
	0,						// PalatinoRoman,
	ITALIC_FONT,					// PalatinoItalic,
	BOLD_FONT,					// PalatinoBold,
	BOLD_FONT | ITALIC_FONT,			// PalatinoBoldItalic,
	0,						// Symbol,
	ITALIC_FONT,					// ZapfChanceryMediumItalic,
	0						// ZapfDingbats
    };

    stream << "\\path[" << tikzProperties(transform) << "] ("
	   << transform.mapX( _position.x ) << ',' << transform.mapY( _position.y )
	   << ") node {"
	   << (fontTraits[ _font ] & ITALIC_FONT ? "\\itshape " : "")
	   << (fontTraits[ _font ] & BOLD_FONT ? "\\bfseries " : "")
	   << (fontTraits[ _font ] & MONOSPACE_FONT ? "\\ttfamily " : "")
	   << (fontTraits[ _font ] & SANSSERIF_FONT ? "\\sffamily " : "")
           << _text
           << "};" << std::endl;
}

Rect
Text::boundingBox() const
{
    return Rect( _position.x, _position.y, 0, 0 );
}

} // namespace LibBoard
