/* -*- mode: c++ -*- */
/**
 * @file   Point.h
 * @author Sebastien Fourey <http://www.greyc.ensicaen.fr/~seb>
 * @date   Sat Aug 18 2007
 * 
 * @brief  The Point structure.
 */
/*
 * \@copyright This File is part of the Board library which is
 * licensed under the terms of the GNU Lesser General Public Licence.
 * See the LICENCE file for further details.
 */
#ifndef _BOARD_POINT_H_
#define _BOARD_POINT_H_

#include <cmath>
#include "DGtal/io/Color.h"

namespace LibBoard {


/**
 * The Point structure.
 * @brief Struct representing a 2D point. 
 */
struct Point {

  double x;      /**< The point's first coordinate */
  double y;      /**< The point's second coordinate */

  /** 
   * Point constructor.
   * 
   */
  Point():x(0.0),y(0.0) { } 

  /** 
   * Point constructor.
   * 
   * @param other point to copy
   */
  Point( const Point & other ):x(other.x),y(other.y) { } 

  /** 
   * Point constructor.
   * 
   * @param xc The point's first coordinate.
   * @param yc The point's second coordinate.
   */
  Point( double xc, double yc ):x(xc),y(yc) { } 
  
  /** 
   * Rotate the point with a given angle around the origin (0,0)
   * 
   * @param angle The rotation angle.
   */
  inline Point & rotate( double angle );

  /** 
   * Get the values of the x and y values.
   * 
   * @param xout Reference to the x to be set.
   * @param yout Reference to the y to be set.
   */
  inline void get( double & xout, double & yout ) const;
  
  /** 
   * Rotate the point with a given angle around the origin (0,0)
   * 
   * @param angle The rotation angle.
   * 
   * @return The rotated point.
   */
  inline Point rotated( double angle ) const;

  inline Point & rotate( double angle, const Point & center );
  
  inline Point  rotated( double angle, const Point & center ) const;

  inline Point & operator+=( const Point & other );

  inline Point & operator-=( const Point & other );

  inline Point & operator*=( double s );
  
  inline Point & operator/=( double s );

  inline Point operator-();
  
  inline double norm() const;
  
};

inline void
Point::get( double & xout, double & yout ) const
{
  xout = x;
  yout = y;
}

inline Point
operator+( const Point & a, const Point & b )
{
  return Point( a.x + b.x, a.y + b.y );
}

inline Point
operator-( const Point & a, const Point & b )
{
  return Point( a.x - b.x, a.y - b.y );
}

inline double
operator*( const Point & a, const Point & b )
{
  return a.x * b.x + a.y * b.y;
}

inline Point
operator*( const Point & p, double s  )
{
  return Point( p.x * s, p.y * s );
}

inline Point
operator*( double s, const Point & p )
{
  return Point( s * p.x, s * p.y );
}

inline Point
operator/( const Point & p, double s )
{
  return Point( p.x / s, p.y / s );
}

inline Point &
Point::operator+=( const Point & other )
{
  x += other.x;
  y += other.y;
  return *this;
}

inline Point &
Point::operator-=( const Point & other )
{
  x -= other.x;
  y -= other.y;
  return *this;
}

inline Point &
Point::operator*=( double s )
{
  x *= s;
  y *= s;
  return *this;
}

inline Point &
Point::operator/=( double s )
{
  x /= s;
  y /= s;
  return *this;
}

inline bool
operator==( const Point & a, const Point & b )
{
  return ( a.x == b.x ) && ( a.y == b.y ) ;
}

inline bool
operator!=( const Point & a, const Point & b )
{
  return ( a.x != b.x ) || ( a.y != b.y ) ;
}

Point &
Point::rotate( double angle )
{
  double newx = cos( angle ) * Point::x - sin( angle ) * Point::y; 
  double newy = sin( angle ) * Point::x + cos( angle ) * Point::y;
  x = newx;
  y = newy;
  return *this;
}

Point
Point::rotated( double angle ) const
{
  return Point(*this).rotate( angle );
}

Point &
Point::rotate( double angle, const Point & center )
{
  (*this) -= center;
  (*this).rotate( angle );
  (*this) += center;
  return *this;
}

Point
Point::rotated( double angle, const Point & center ) const
{
  return Point(*this).rotate( angle, center );
}

double
Point::norm() const
{
  return sqrt( x*x + y*y );
}

Point Point::operator-()
{
  return Point( -x, -y );
}

} // mamespace BoardLib

#endif // _POINT_H_

