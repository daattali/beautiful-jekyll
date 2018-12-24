/* -*- mode: c++ -*- */
/**
 * @file   Transforms.cpp
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
#include "Board/ShapeList.h"
#include "Board/Transforms.h"
#include <cmath>

namespace {
  const float ppmm = 720.0f / 254.0f;
  const float fig_ppmm = 1143 / 25.4f;
}

namespace LibBoard {

//
// Transform
// 

double
Transform::rounded( double x ) const
{
  return Transform::round( 1000000*x ) / 1000000;
} 

double
Transform::mapX( double x ) const
{
  return rounded( x * _scale + _deltaX );
}

double
Transform::scale( double x ) const
{
  return rounded( x * _scale );
}

void
Transform::apply( double & x, double & y ) const
{
  x = mapX( x );
  y = mapY( y );
}

//
// TransformEPS
// 

double
TransformEPS::mapY( double y ) const
{
  return rounded( y * _scale + _deltaY );
}

void
TransformEPS::setBoundingBox( const Rect & rect,
            const double pageWidth,
            const double pageHeight,
            const double margin )
{
  if ( pageWidth <= 0 || pageHeight <= 0 ) {
    _scale = 1.0f;
    // _deltaX = - rect.left;
    _deltaX = 0.5 * 210 * ppmm - ( rect.left + 0.5 * rect.width );
    // _deltaY = - ( rect.top - rect.height );
    _deltaY = 0.5 * 297 * ppmm - ( rect.top - 0.5 * rect.height );  
    _height = rect.height;
  } else {
    const double w = pageWidth - 2 * margin;
    const double h = pageHeight - 2 * margin;
    if ( ( rect.height / rect.width ) > ( h / w ) ) {
      _scale = h * ppmm / rect.height;
    } else {
      _scale = w * ppmm / rect.width;
    }
    _deltaX = 0.5 * pageWidth * ppmm - _scale * ( rect.left + 0.5 * rect.width );
    _deltaY = 0.5 * pageHeight * ppmm - _scale * ( rect.top - 0.5 * rect.height );  
    _height = pageHeight * ppmm;
  }
}

//
// TransformFIG
// 

double
TransformFIG::rounded( double x ) const
{
  return Transform::round( x );
}

double
TransformFIG::mapY( double y ) const
{
  return rounded( _height - ( y * _scale + _deltaY ) );
}

int
TransformFIG::mapWidth( double width ) const
{
  // FIG width unit is 1/160 inch
  // Postscript points are 1/72 inch
  if ( width == 0.0 ) return 0;
  int result = static_cast<int>( Transform::round( 160 * ( width / 72.0 ) ) );
  return result>0?result:1;
}

void
TransformFIG::setBoundingBox( const Rect & rect,
            const double pageWidth,
            const double pageHeight,
            const double margin )
{
  if ( pageWidth <= 0 || pageHeight <= 0 ) {
    _scale = fig_ppmm / ppmm;
    _deltaX = 0.5 * 210 * fig_ppmm - _scale * ( rect.left + 0.5 * rect.width );
    //_deltaX = - rect.left;
    _deltaY = 0.5 * 297 * fig_ppmm - _scale * ( rect.top - 0.5 * rect.height );  
    // _deltaY = - rect.top;
    // _deltaY = - ( rect.top - rect.height );
    //_height = rect.height;
    _height = 297 * fig_ppmm;
  } else {
    const double w = pageWidth - 2 * margin;
    const double h = pageHeight - 2 * margin;
    if ( rect.height / rect.width > ( h / w ) ) {
      _scale = ( h * fig_ppmm ) / rect.height;
    } else {
      _scale = ( w * fig_ppmm ) / rect.width;
    }
    _deltaX = 0.5 * pageWidth * fig_ppmm - _scale * ( rect.left + 0.5 * rect.width );
    _deltaY = 0.5 * pageHeight * fig_ppmm - _scale * ( rect.top - 0.5 * rect.height );  
    _height = pageHeight * fig_ppmm;
  }
  // float ppmm = (1200/25.4);
}

void
TransformFIG::setDepthRange( const ShapeList & shapes )
{
  _maxDepth = shapes.maxDepth();
  _minDepth = shapes.minDepth();
}

int
TransformFIG::mapDepth( int depth ) const
{
  if ( depth > _maxDepth ) return 999;
  if ( _maxDepth - _minDepth > 998 ) {
    double range = _maxDepth - _minDepth;
    int r = static_cast<int>( 1 + Transform::round( ( ( depth - _minDepth ) / range ) * 998 ) );
    return r>=0?r:0;
  } else {
    int r = 1 + depth - _minDepth;
    return r>=0?r:0;
  }
}

//
// TransformSVG
// 

double
TransformSVG::rounded( double x ) const
{
  return Transform::round( 100*x ) / 100.0f;
} 

double
TransformSVG::mapY( double y ) const
{
  return rounded( _height - ( y * _scale + _deltaY ) );
}

double
TransformSVG::mapWidth( double width ) const
{
  // return Transform::round( 1000 * width / ppmm ) / 1000.0;
  return Transform::round( 1000 * width  / ppmm  ) / 1000.0;
}

void
TransformSVG::setBoundingBox( const Rect & rect,
            const double pageWidth,
            const double pageHeight,
            const double margin )  
{
  if ( pageWidth <= 0 || pageHeight <= 0 ) {
    _scale = 1.0f;
    // _deltaX = 0.5 * 210 * ppmm - ( rect.left + 0.5 * rect.width );
    _deltaX = - rect.left;
    // _deltaY = 0.5 * 297 * ppmm - ( rect.top - 0.5 * rect.height );
    _deltaY = - ( rect.top - rect.height );
    // _height = 297 * fig_ppmm;
    _height = rect.height;
  } else {
    const double w = pageWidth - 2 * margin;
    const double h = pageHeight - 2 * margin;
    if ( rect.height / rect.width > ( h / w ) ) {
      _scale = h * ppmm / rect.height;
    } else {
      _scale = w * ppmm / rect.width;
    }
    _deltaX = 0.5 * pageWidth * ppmm - _scale * ( rect.left + 0.5 * rect.width );
    _deltaY = 0.5 * pageHeight * ppmm - _scale * ( rect.top - 0.5 * rect.height );
    _height = pageHeight * ppmm;
  }
}

#ifdef WITH_CAIRO
//
// TransformCairo
// 

double
TransformCairo::rounded( double x ) const
{
  return Transform::round( 100*x ) / 100.0f;
} 

double
TransformCairo::mapY( double y ) const
{
  return rounded( _height - ( y * _scale + _deltaY ) );
}

double
TransformCairo::mapWidth( double width ) const
{
  // return Transform::round( 1000 * width / ppmm ) / 1000.0;
  return Transform::round( 1000 * width  / ppmm  ) / 1000.0;
}

void
TransformCairo::setBoundingBox( const Rect & rect,
            const double pageWidth,
            const double pageHeight,
            const double margin )  
{
  if ( pageWidth <= 0 || pageHeight <= 0 ) {
    _scale = 1.0f;
    // _deltaX = 0.5 * 210 * ppmm - ( rect.left + 0.5 * rect.width );
    _deltaX = - rect.left;
    // _deltaY = 0.5 * 297 * ppmm - ( rect.top - 0.5 * rect.height );
    _deltaY = - ( rect.top - rect.height );
    // _height = 297 * fig_ppmm;
    _height = rect.height;
  } else {
    const double w = pageWidth - 2 * margin;
    const double h = pageHeight - 2 * margin;
    if ( rect.height / rect.width > ( h / w ) ) {
      _scale = h * ppmm / rect.height;
    } else {
      _scale = w * ppmm / rect.width;
    }
    _deltaX = 0.5 * pageWidth * ppmm - _scale * ( rect.left + 0.5 * rect.width );
    _deltaY = 0.5 * pageHeight * ppmm - _scale * ( rect.top - 0.5 * rect.height );
    _height = pageHeight * ppmm;
  }
}
#endif

} // namespace LibBoard
