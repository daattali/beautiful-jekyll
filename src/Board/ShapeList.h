/* -*- mode: c++ -*- */
/**
 * @file   ShapeList.h
 * @author Sebastien Fourey <http://www.greyc.ensicaen.fr/~seb>
 * @date   Sat Aug 18 2007
 * 
 * @brief  Classes ShapeList and Group
 *
 */
/*
 * \@copyright This File is part of the Board library which is
 * licensed under the terms of the GNU Lesser General Public Licence.
 * See the LICENCE file for further details.
 */
#ifndef _BOARD_SHAPELIST_H_
#define _BOARD_SHAPELIST_H_

#include "Board/Shapes.h"
#include "Board/Tools.h"

namespace LibBoard {

   
/**
 * The ShapeList structure.
 * @brief A group of shapes
 */
struct ShapeList : public Shape {
  
  
  inline ShapeList( int depth = -1 );

  ShapeList( const ShapeList & other );

  ~ShapeList();

  /** 
   * Returns the generic name of the shape (e.g., Circle, Rectangle, etc.)
   * 
   * @return object name.
   */
  const std::string & name() const;
  
  ShapeList & clear();

  Point center() const;

  Shape & rotate( double angle, const Point & center );

  ShapeList rotated( double angle, const Point & center );

  Shape & rotate( double angle );

  ShapeList rotated( double angle );

  Shape & translate( double dx, double dy );

  ShapeList translated( double dx, double dy );

  Shape & scale( double sx, double sy );

  Shape & scale( double s );

  ShapeList scaled( double sx, double sy );

  ShapeList scaled( double s );

  /** 
   * Scales all the values (positions, dimensions, etc.) associated
   * with the shape.
   * 
   * @param s The scaling factor.
   */
  void scaleAll( double s );
  
  void flushPostscript( std::ostream & stream,
      const TransformEPS & transform ) const;
  
  void flushFIG( std::ostream & stream,
     const TransformFIG & transform,
     std::map<DGtal::Color,int> & colormap ) const;

  void flushSVG( std::ostream & stream,
     const TransformSVG & transform ) const;

#ifdef WITH_CAIRO
  void flushCairo( cairo_t *cr,
     const TransformCairo & transform ) const;
#endif

  void flushTikZ( std::ostream & stream,
     const TransformTikZ & transform ) const;

  Rect boundingBox() const;
  
  virtual int minDepth() const;

  virtual int maxDepth() const;

  void shiftDepth( int shift );

  Shape * clone() const;
  
  ShapeList & operator=( const ShapeList & other );

  /** 
   * Adds a shape to the shape list. If the shape has no given depth
   * or is a compound shape (ShapeList) then it is placed on top of
   * the shapes stack. Otherwise, the shape depth is left unchanged.
   * 
   * @param shape the shape to add.
   * 
   * @return updated shapelist.
   */
  ShapeList & operator<<( const Shape & shape ); 

  /** 
   * Adds a shape to the list of shape, always preserving the shape's depth.
   * 
   * @param shape shape to add.
   * 
   * @return updated shapelist.
   */
  ShapeList & operator+=( const Shape & shape ); 
  
  /** 
   * Insert the shape at a given depth. If the shape is ShapeList or a Board, 
   * then all shapes above it will be shifted.
   * 
   * @param shape shape
   * @param depth depth
   * 
   * @return shapelist
   */
  ShapeList & insert( const Shape & shape, int depth );

  /** 
   * Duplicates the last inserted shape.
   * 
   * @param copies The number of copies.
   */
  ShapeList & dup( unsigned int copies  = 1 );
  
  /** 
   * Return the last inserted shape with its actual type, if specified (otherwise, a Shape &).
   * 
   * @param position The position. 0 is the last inserted shape, 1 is the one before, etc.
   * @return A reference to the addressed shape.
   */
  template<typename T>
  T & last( const unsigned int position = 0 );

  Shape & last( const unsigned int position = 0 );

  /** 
   * Convenience function that simply calls last(0).
   * 
   * @return top shape.
   */
  Shape & top();

private:
  static const std::string _name; /**< The generic name of the shape. */
  
protected:

  void addShape( const Shape & shape, double scaleFactor );

  std::vector<Shape*> _shapes;  /**< The vector of shapes. */
  int _nextDepth;    /**< The depth of the next figure to be added.  */

  /** 
   * Free the memory used by the shapes in the shape vector.
   */
  void free();
};

/**
 * The Group structure.
 * @brief A group of shapes. A group is basically a ShapeList except that
 * when rendered in either an SVG of a FIG file, it is a true compound element.
 */
struct Group : public ShapeList {
  
  Group( int depthValue = -1 )
    : ShapeList( depthValue ), _clippingPath( true /* closed path */ ) { }
  
  Group( const Group & other ) 
    : ShapeList( other ), _clippingPath( other._clippingPath ) { }

  ~Group() { };
  
  /** 
   * Returns the generic name of the shape (e.g., Circle, Rectangle, etc.)
   * 
   * @return object name
   */
  const std::string & name() const;

  Shape & rotate( double angle, const Point & center );

  Shape & rotate( double angle );
  
  Group rotated( double angle, const Point & center );
  
  Group rotated( double angle );
  
  Shape & translate( double dx, double dy );
  
  Group translated( double dx, double dy );
  
  Shape & scale( double sx, double sy );
  
  Shape & scale( double s );
  
  Group scaled( double sx, double sy );
  
  Group scaled( double s );
  
  /** 
   * Define a clipping rectangle for the group.
   * 
   * @param x lower corner of the rectangle
   * @param y lower corner of the rectangle
   * @param width width
   * @param height height
   */
  void setClippingRectangle(  float x, float y, 
            float width, float height );

  /** 
   * Define a clipping path for the group.
   * 
   * @param points A path.
   */
  void setClippingPath(  const std::vector<Point> & points  );

  /** 
   * Define a clipping path for the group.
   * 
   * @param path A path.
   */
  void setClippingPath( const Path & path );


  void flushPostscript( std::ostream & stream,
      const TransformEPS & transform ) const;
  
  void flushFIG( std::ostream & stream,
     const TransformFIG & transform,
     std::map<DGtal::Color,int> & colormap ) const;

  void flushSVG( std::ostream & stream,
     const TransformSVG & transform ) const;

#ifdef WITH_CAIRO
  void flushCairo( cairo_t *cr,
     const TransformCairo & transform ) const;
#endif

  void flushTikZ( std::ostream & stream,
     const TransformTikZ & transform ) const;

  Group & operator=( const Group & other );

  Shape * clone() const;

  Rect boundingBox() const;

private:
  static const std::string _name; /**< The generic name of the shape. */
  Path _clippingPath;
  static unsigned int _clippingCount;
};


#include "ShapeList.ih"


} // namespace LibBoard

#endif /* _SHAPELIST_H_ */

