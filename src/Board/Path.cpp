/* -*- mode: c++ -*- */
/**
 * @file   Path.cpp
 * @author Sebastien Fourey <http://www.greyc.ensicaen.fr/~seb>
 * @date   Aug 2009
 * 
 * @brief  
 */
/*
 * \@copyright This File is part of the Board library which is
 * licensed under the terms of the GNU Lesser General Public Licence.
 * See the LICENCE file for further details.
 */

#include "Board/Path.h"
#include "Board/Transforms.h"


namespace LibBoard {

Path &
Path::pop_back()
{
  _points.pop_back();
  return *this;
}

Path &
Path::operator<<( const Point & p )
{
  _points.push_back( p );
  return *this;
}

Point
Path::center() const {
  Rect bbox = boundingBox();
  return Point( bbox.left + bbox.width/2.0, 
    bbox.top  - bbox.height/2.0 );
}

Path &
Path::rotate( double angle, const Point & rotCenter )
{
  std::vector<Point>::iterator i = _points.begin();
  std::vector<Point>::iterator end = _points.end();
  while ( i != end ) {
    i->rotate( angle, rotCenter );
    ++i;
  }
  return *this;
}

Path
Path::rotated( double angle, const Point & rotCenter ) const
{
  Path res(*this);
  std::vector<Point>::iterator i = res._points.begin();
  std::vector<Point>::iterator end = res._points.end();
  while ( i != end ) {
    i->rotate( angle, rotCenter );
    ++i;
  }
  return res;
}

Path &
Path::rotate( double angle )
{
  return Path::rotate( angle, center() );
}

Path
Path::rotated( double angle ) const
{
  Path res(*this);
  return static_cast<Path&>( res.rotate( angle, center() ) );
}

Path &
Path::translate( double dx, double dy )
{
  std::vector<Point>::iterator i = _points.begin();
  std::vector<Point>::iterator end = _points.end();
  Point delta( dx, dy );
  while ( i != end ) {
    (*i) += delta;
    ++i;
  }
  return *this;
}

Path
Path::translated( double dx, double dy ) const
{
  Path res(*this);
  std::vector<Point>::iterator i = res._points.begin();
  std::vector<Point>::iterator end = res._points.end();
  Point delta( dx, dy );
  while ( i != end ) {
    (*i) += delta;
    ++i;
  }
  return res;
}

Path &
Path::scale( double sx, double sy )
{
  Point c = center();
  translate( -c.x, -c.y );
  std::vector<Point>::iterator i = _points.begin();
  std::vector<Point>::iterator end = _points.end();
  while ( i != end ) {
    i->x *= sx;
    i->y *= sy;
    ++i;
  }
  Point delta = c - center();
  translate( delta.x, delta.y );
  return *this;  
}

Path &
Path::scale( double s )
{
  return Path::scale( s, s );
}

Path
Path::scaled( double sx, double sy ) const
{
  return Path(*this).scale( sx, sy );
}

Path
Path::scaled( double s) const
{
  return Path(*this).scale( s, s );
}

void
Path::scaleAll( double s )
{
  std::vector<Point>::iterator it = _points.begin();
  std::vector<Point>::iterator end = _points.end();
  while ( it != end ) {
    (*it) *= s;
    ++it;
  }
}

void
Path::flushPostscript( std::ostream & stream,
           const TransformEPS & transform ) const
{
  if ( _points.empty() )
    return;
  std::vector<Point>::const_iterator i = _points.begin();
  std::vector<Point>::const_iterator end = _points.end();

  stream << transform.mapX( i->x ) << " " << transform.mapY( i->y ) << " m";
  ++i;
  while ( i != end ) {
    stream << " " << transform.mapX( i->x ) << " " << transform.mapY( i->y ) << " l";
    ++i;
  }
  if ( _closed ) stream << " cp";
  stream << " ";
}

void
Path::flushFIG( std::ostream & stream,
    const TransformFIG & transform ) const
{
  if ( _points.empty() )
    return;

  std::vector<Point>::const_iterator i = _points.begin();
  std::vector<Point>::const_iterator end = _points.end();
  while ( i != end ) {
    stream << " " << static_cast<int>( transform.mapX( i->x ) )
     << " " << static_cast<int>( transform.mapY( i->y ) );
    ++i;
  }
  if ( _closed ) { 
    stream << " " << static_cast<int>( transform.mapX( _points.begin()->x ) )
     << " " << static_cast<int>( transform.mapY( _points.begin()->y ) );
  }  
}

void
Path::flushSVGCommands( std::ostream & stream,
      const TransformSVG & transform ) const
{
  if ( _points.empty() )
    return;
  std::vector<Point>::const_iterator i = _points.begin();
  std::vector<Point>::const_iterator end = _points.end();
  int count = 0;
  
  stream << "M " << transform.mapX( i->x ) << " " << transform.mapY( i->y );
  ++i;
  while ( i != end ) {
    stream << " L " << transform.mapX( i->x ) << " " << transform.mapY( i->y );
    ++i;
    count = ( count + 1 ) % 6;
    if ( !count ) stream << "\n                  ";
  }
  if ( _closed ) 
    stream << " Z" << std::endl;
}

void
Path::flushSVGPoints( std::ostream & stream,
          const TransformSVG & transform ) const
{
  if ( _points.empty() )
    return;
  std::vector<Point>::const_iterator i = _points.begin();
  std::vector<Point>::const_iterator end = _points.end();
  int count = 0;
  stream << transform.mapX( i->x ) << "," << transform.mapY( i->y );
  ++i;
  while ( i != end ) {
    stream << " " << transform.mapX( i->x ) << "," << transform.mapY( i->y );
    ++i;
    count = ( count + 1 ) % 6;
    if ( !count ) stream << "\n                  ";
  }
}

#ifdef WITH_CAIRO
void
Path::flushCairoPoints( cairo_t *cr,
     const TransformCairo & transform ) const
{
  if ( _points.empty() )
    return;
  std::vector<Point>::const_iterator i = _points.begin();
  std::vector<Point>::const_iterator end = _points.end();
  int count = 0;
  cairo_move_to (cr, transform.mapX( i->x ), transform.mapY( i->y ));
  ++i;
  while ( i != end ) {
    cairo_line_to (cr, transform.mapX( i->x ), transform.mapY( i->y ));
    ++i;
    count = ( count + 1 ) % 6;
    //if ( !count ) stream << "\n                  ";
  }
}
#endif

void
Path::flushTikZPoints( std::ostream & stream,
		       const TransformTikZ & transform ) const
{
  if ( _points.empty() )
    return;
  std::vector<Point>::const_iterator i = _points.begin();
  std::vector<Point>::const_iterator end = _points.end();
  stream << '(' << transform.mapX( i->x ) << "," << transform.mapY( i->y ) << ')';
  ++i;
  while ( i != end ) {
    stream << " -- "
    << '(' << transform.mapX( i->x ) << "," << transform.mapY( i->y ) << ')';
    ++i;
  }
}

Rect
Path::boundingBox() const
{
  if ( _points.empty() )
    return Rect( 0, 0, 0, 0 );
  Rect rect;
  std::vector< Point >::const_iterator i = _points.begin();
  std::vector< Point >::const_iterator end = _points.end();
  rect.top = i->y;
  rect.left = i->x;
  rect.width = 0.0;
  rect.height = 0.0;
  ++i;
  while ( i != end ) { 
    if ( i->x < rect.left ) { 
      double dw = rect.left - i->x;
      rect.left = i->x;
      rect.width += dw;
    } else if ( i->x > rect.left + rect.width ) {
      rect.width = i->x - rect.left;
    }
    if ( i->y > rect.top ) { 
      double dh = i->y - rect.top;
      rect.top = i->y;
      rect.height += dh;
    } else if ( i->y < rect.top - rect.height ) {
      rect.height = rect.top - i->y;
    }
    ++i;
  }
  return rect;
}

} // namespace LibBoard
