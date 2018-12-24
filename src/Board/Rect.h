/* -*- mode: c++ -*- */
/**
 * @file   Rect.h
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
#ifndef _BOARD_RECT_H_
#define _BOARD_RECT_H_

#include <iostream>
#include "Board/Point.h"

namespace LibBoard {

/**
 * The Rectangle structure.
 * @brief Struct representing a rectangle on the plane. 
 */
struct Rect {
  
  double left;      /**< Coordinate of the left side. */
  double top;      /**< Coordinate of the upper side. */
  double width;      /**< Width of the rectangle. */
  double height;    /**< Height of the rectangle. */
  
  /** 
   * Rect constructor.
   * 
   * @param leftX left X
   * @param topY  top Y
   * @param rectWidth width
   * @param rectHeight height
   *
   */
  Rect( double leftX = 0.0f, double topY = 0.0f, double rectWidth = 0.0f, double rectHeight = 0.0f )
    :left( leftX ), top( topY ), width( rectWidth ), height( rectHeight ) { } 

  Point topLeft() { return Point( left, top ); }
  Point topRight() { return Point( left + width, top ); }
  Point bottomLeft() { return Point( left, top - height ); }
  Point bottomRight() { return Point( left + width, top - height ); }
};

/** 
 * Computes the bounding box of two bounding boxes.
 * 
 * @param rectA A first rectangle.
 * @param rectB A second rectangle.
 * 
 * @return The smallest rectangle that contains both rectA and rectB.
 */
Rect operator||( const Rect & rectA, const Rect & rectB );

/** 
 * Computes the intersection of two bounding boxes.
 * 
 * @param rectA A first rectangle.
 * @param rectB A second rectangle.
 * 
 * @return The intersecting rectangle of two bounding boxes.
 */
Rect operator&&( const Rect & rectA, const Rect & rectB );


} // mamespace BoardLib

/** 
 * Stream output operator for Rect structure.
 * 
 * @param out An output stream.
 * @param rect A Rect struct.
 * 
 * @return The output stream.
 */
std::ostream & operator<<( std::ostream & out, const LibBoard::Rect & rect );

#endif // _RECT_H_
