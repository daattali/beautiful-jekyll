/* -*- mode: c++ -*- */
/**
 * @file   Transforms.h
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
#ifndef _BOARD_TRANSFORMS_H_
#define _BOARD_TRANSFORMS_H_

#include <limits>
#include <vector>
#include <cmath>

namespace LibBoard {

struct Rect;
struct Shape;
struct ShapeList;

/**
 * The base class for transforms.
 * @brief base class for transforms.
 */
struct Transform {
public:
  inline Transform();
  virtual ~Transform() { };
  virtual double mapX( double x ) const;
  virtual double mapY( double y ) const = 0;
  virtual void apply( double & x, double & y ) const;
  virtual double scale( double x ) const;
  virtual double rounded( double x ) const;
  virtual void setBoundingBox( const Rect & rect,
             const double pageWidth,
             const double pageHeight,
             const double margin ) = 0;

  static inline double round( const double & x );

protected:
  double _scale;
  double _deltaX;
  double _deltaY;
  double _height;
};

/**
 * The TransformEPS structure.
 * @brief Structure representing a scaling and translation
 * suitable for an EPS output.
 */
struct TransformEPS : public Transform {
public:
  double mapY( double y ) const;
  void setBoundingBox( const Rect & rect,
           const double pageWidth,
           const double pageHeight,
           const double margin );
};

/**
 * The TransformFIG structure.
 * @brief Structure representing a scaling and translation
 * suitable for an XFig output.
 */
struct TransformFIG : public Transform {
public:
  inline TransformFIG();
  double rounded( double x ) const;
  double mapY( double y ) const;
  int mapWidth( double width ) const; 
  void setBoundingBox( const Rect & rect,
           const double pageWidth,
           const double pageHeight,
           const double margin );
  void setDepthRange( const ShapeList & shapes );
  int mapDepth( int depth ) const;
private:
  int _maxDepth;
  int _minDepth;
};

/**
 * The TransformSVG structure.
 * @brief Structure representing a scaling and translation
 * suitable for an SVG output.
 */
struct TransformSVG : public Transform {
public:
  double rounded( double x ) const;
  double mapY( double y ) const;
  double mapWidth( double width ) const; 
  void setBoundingBox( const Rect & rect,
           const double pageWidth,
           const double pageHeight,
           const double margin );
};

#ifdef WITH_CAIRO
/**
 * The TransformCairo structure.
 * @brief Structure representing a scaling and translation
 * suitable for an Cairo output.
 */
struct TransformCairo : public Transform {
public:
  double rounded( double x ) const;
  double mapY( double y ) const;
  double mapWidth( double width ) const; 
  void setBoundingBox( const Rect & rect,
           const double pageWidth,
           const double pageHeight,
           const double margin );
};
#endif

/**
 * The TransformTikZ structure.
 * @brief Structure representing a scaling and translation
 * suitable for an TikZ output.
 */
struct TransformTikZ : public TransformSVG {
};

#include "Transforms.ih"

} // namespace LibBoard

#endif /* _TRANSFORMS_H_ */
