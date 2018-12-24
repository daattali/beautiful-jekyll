/* -*- mode: c++ -*- */
/**
 * @file   ShapeList.cpp
 * @author Sebastien Fourey <http://www.greyc.ensicaen.fr/~seb>
 * @date   Sat Aug 18 2007
 *
 * @brief  Definition of the ShapeList and Group classes.
 */
/*
 * \@copyright This File is part of the Board library which is
 * licensed under the terms of the GNU Lesser General Public Licence.
 * See the LICENCE file for further details.
 */
#include "Board/ShapeList.h"
#include "Board/Tools.h"
#include <algorithm>
#include <typeinfo>

#if defined( max )
#undef max
#endif

namespace LibBoard {

//
// Definition of the ShapeList methods.
//

const std::string ShapeList::_name("ListOfShapes");

const std::string &
ShapeList::name() const
{
    return _name;
}

ShapeList::~ShapeList()
{
    free();
}

ShapeList &
ShapeList::clear()
{
    free();
    _shapes.clear();
    _nextDepth = std::numeric_limits<int>::max() - 1;
    return *this;
}

void
ShapeList::free()
{
    std::vector<Shape*>::const_iterator i = _shapes.begin();
    std::vector<Shape*>::const_iterator end = _shapes.end();
    while ( i != end ) {
        delete *i;
        ++i;
    }
}

ShapeList::ShapeList( const ShapeList & other ) : Shape( other )
{
    if ( ! other._shapes.size() ) return;
    _shapes.resize( other._shapes.size(), 0 );
    std::vector<Shape*>::iterator t = _shapes.begin();
    std::vector<Shape*>::const_iterator i = other._shapes.begin();
    std::vector<Shape*>::const_iterator end = other._shapes.end();
    while ( i != end ) {
        *t = (*i)->clone();
        ++i;
        ++t;
    }
}

ShapeList &
ShapeList::operator=( const ShapeList & other )
{
    free();
    if ( ! other._shapes.size() ) return *this;
    _shapes.resize( other._shapes.size(), 0 );
    std::vector<Shape*>::iterator t = _shapes.begin();
    std::vector<Shape*>::const_iterator i = other._shapes.begin();
    std::vector<Shape*>::const_iterator end = other._shapes.end();
    while ( i != end ) {
        *t = (*i)->clone();
        ++i;
        ++t;
    }
    return *this;
}

ShapeList &
ShapeList::operator<<( const Shape & shape )
{
    if ( typeid( shape ) == typeid( ShapeList ) ) {
        // Insertion on top, respecting the same depth order.
        const ShapeList & sl = dynamic_cast<const ShapeList &>( shape );
        std::vector<Shape*> shapes = sl._shapes;
        stable_sort( shapes.begin(), shapes.end(), shapeGreaterDepth );
        std::vector<Shape*>::iterator i = shapes.begin();
        std::vector<Shape*>::iterator end = shapes.end();
        while ( i != end ) {
            Shape * s = (*i)->clone();
            s->depth( _nextDepth-- );
            _shapes.push_back( s );
            ++i;
        }
    } else {
        Shape * s = shape.clone();
        if ( s->depth() == -1 )
            s->depth( _nextDepth-- );
        _shapes.push_back( s );
        if ( typeid( shape ) == typeid( Group ) ) {
            _nextDepth = dynamic_cast<const Group&>(shape).minDepth() - 1;
        }
    }
    return *this;
}

void
ShapeList::addShape( const Shape & shape, double scaleFactor )
{
    if ( typeid( shape ) == typeid( ShapeList ) ) {
        // Insertion on top, respecting the same depth order.
        const ShapeList & sl = dynamic_cast<const ShapeList &>( shape );
        std::vector<Shape*> shapes = sl._shapes;
        stable_sort( shapes.begin(), shapes.end(), shapeGreaterDepth );
        std::vector<Shape*>::iterator i = shapes.begin();
        std::vector<Shape*>::iterator end = shapes.end();
        while ( i != end ) {
            Shape * s = (*i)->clone();
            s->depth( _nextDepth-- );
            if ( scaleFactor != 1.0 )
                s->scaleAll( scaleFactor );
            _shapes.push_back( s );
            ++i;
        }
    } else {
        Shape * s = shape.clone();
        if ( s->depth() == -1 )
            s->depth( _nextDepth-- );
        if ( scaleFactor != 1.0 )
            s->scaleAll( scaleFactor );
        _shapes.push_back( s );
        if ( typeid( shape ) == typeid( Group ) ) {
            _nextDepth = dynamic_cast<const Group&>(shape).minDepth() - 1;
        }
    }
}

ShapeList &
ShapeList::dup( unsigned int count )
{
    if ( ! _shapes.size() ) {
        warning << "dup() called with an empty list of shapes.\n";
        return *this;
    }
    while ( count-- ) {
        (*this) << (*_shapes.back());
    }
    return *this;
}

ShapeList &
ShapeList::operator+=( const Shape & shape )
{
    if ( typeid( shape ) == typeid( ShapeList ) ) {
        const ShapeList & sl = dynamic_cast<const ShapeList &>( shape );
        std::vector<Shape*>::const_iterator i = sl._shapes.begin();
        std::vector<Shape*>::const_iterator end = sl._shapes.end();
        while ( i != end ) {
            Shape * s = (*i)->clone();
            _shapes.push_back( s );
            ++i;
        }
    } else {
        _shapes.push_back( shape.clone() );
    }
    return *this;
}

ShapeList &
ShapeList::insert( const Shape & , int /* depth */ )
{
    warning << "ShapeList::insert() not implemented yet.\n";
    return *this;
}


Point
ShapeList::center() const {
    std::vector<Shape*>::const_iterator i = _shapes.begin();
    std::vector<Shape*>::const_iterator end = _shapes.end();
    double f = 1.0 / _shapes.size();
    Point r(0,0);
    while ( i != end ) {
        r += f * (*i)->center();
        ++i;
    }
    return r;
}

Shape &
ShapeList::rotate( double angle, const Point & rotCenter )
{
    std::vector<Shape*>::iterator i = _shapes.begin();
    std::vector<Shape*>::iterator end = _shapes.end();
    while ( i != end ) {
        (*i)->rotate( angle, rotCenter );
        ++i;
    }
    return *this;
}

ShapeList
ShapeList::rotated( double angle, const Point & rotCenter )
{
    ShapeList r( *this );
    return static_cast<ShapeList&>( r.rotate( angle, rotCenter ) );
}

Shape &
ShapeList::rotate( double angle )
{
    return ShapeList::rotate( angle, center() );
}

ShapeList
ShapeList::rotated( double angle )
{
    return static_cast<ShapeList&>( ShapeList( *this ).rotate( angle, center() ) );
}

Shape &
ShapeList::translate( double dx, double dy )
{
    std::vector<Shape*>::iterator i = _shapes.begin();
    std::vector<Shape*>::iterator end = _shapes.end();
    while ( i != end ) {
        (*i)->translate( dx, dy );
        ++i;
    }
    return *this;
}

ShapeList
ShapeList::translated( double dx, double dy )
{
    return static_cast<ShapeList&>( ShapeList( *this ).translate( dx, dy ) );
}

Shape &
ShapeList::scale( double sx, double sy )
{
    Point c = center();
    Point delta;
    std::vector<Shape*>::iterator i = _shapes.begin();
    std::vector<Shape*>::iterator end = _shapes.end();
    while ( i != end ) {
        delta = (*i)->center() - c;
        delta.x *= sx;
        delta.y *= sy;
        (*i)->scale( sx, sy );
        delta = ( c + delta ) - (*i)->center();
        (*i++)->translate( delta.x, delta.y );
    }
    return *this;
}

Shape &
ShapeList::scale( double s )
{
    return ShapeList::scale( s, s );
}

ShapeList
ShapeList::scaled( double sx, double sy )
{
    return static_cast<ShapeList&>( ShapeList( *this ).scale( sx, sy ) );
}

ShapeList
ShapeList::scaled( double s )
{
    return static_cast<ShapeList&>( ShapeList( *this ).scale( s, s ) );
}

void
ShapeList::scaleAll( double s )
{
    std::vector<Shape*>::iterator i = _shapes.begin();
    std::vector<Shape*>::iterator end = _shapes.end();
    while ( i != end ) {
        (*i++)->scaleAll( s );
    }
}

void
ShapeList::flushPostscript( std::ostream & stream,
                            const TransformEPS & transform ) const
{
    std::vector< Shape* > shapes = _shapes;
    stable_sort( shapes.begin(), shapes.end(), shapeGreaterDepth );
    std::vector< Shape* >::const_iterator i = shapes.begin();
    std::vector< Shape* >::const_iterator end = shapes.end();
    stream << "%%% Begin ShapeList\n";
    while ( i != end ) {
        (*i++)->flushPostscript( stream, transform );
    }
    stream << "%%% End ShapeList\n";
}

void
ShapeList::flushFIG( std::ostream & stream,
                     const TransformFIG & transform,
                     std::map<DGtal::Color,int> & colormap ) const
{
    std::vector< Shape* > shapes = _shapes;
    stable_sort( shapes.begin(), shapes.end(), shapeGreaterDepth );
    std::vector< Shape* >::const_iterator i = shapes.begin();
    std::vector< Shape* >::const_iterator end = shapes.end();
    while ( i != end ) {
        (*i)->flushFIG( stream, transform, colormap );
        ++i;
    }
}

void
ShapeList::flushSVG( std::ostream & stream,
                     const TransformSVG & transform ) const
{
    std::vector< Shape* > shapes = _shapes;
    stable_sort( shapes.begin(), shapes.end(), shapeGreaterDepth );
    std::vector< Shape* >::const_iterator i = shapes.begin();
    std::vector< Shape* >::const_iterator end = shapes.end();
    //stream << "<g>\n";
    while ( i != end ) {
        (*i)->flushSVG( stream, transform );
        ++i;
    }
    //stream << "</g>\n";
}

#ifdef WITH_CAIRO
void
ShapeList::flushCairo( cairo_t *cr,
     const TransformCairo & transform ) const
{
    std::vector< Shape* > shapes = _shapes;
    stable_sort( shapes.begin(), shapes.end(), shapeGreaterDepth );
    std::vector< Shape* >::const_iterator i = shapes.begin();
    std::vector< Shape* >::const_iterator end = shapes.end();

    while ( i != end ) {
        (*i)->flushCairo( cr, transform );
        ++i;
    }
}
#endif

void
ShapeList::flushTikZ( std::ostream & stream,
                      const TransformTikZ & transform ) const
{
    std::vector< Shape* > shapes = _shapes;
    stable_sort( shapes.begin(), shapes.end(), shapeGreaterDepth );
    std::vector< Shape* >::const_iterator i = shapes.begin();
    std::vector< Shape* >::const_iterator end = shapes.end();
    stream << "\\begin{scope}\n";
    while ( i != end ) {
        (*i)->flushTikZ( stream, transform );
        ++i;
    }
    stream << "\\end{scope}\n";
}

Rect
ShapeList::boundingBox() const
{
    Rect r;
    std::vector< Shape* >::const_iterator i = _shapes.begin();
    std::vector< Shape* >::const_iterator end = _shapes.end();
    if ( i == end ) return r;
    r = (*i)->boundingBox();
    ++i;
    while ( i != end ) {
        r = r || (*i)->boundingBox();
        ++i;
    }
    return r;
}

int
ShapeList::minDepth() const
{
    int res = std::numeric_limits<int>::max();
    int d;
    ShapeList * sl;
    std::vector< Shape* >::const_iterator i = _shapes.begin();
    std::vector< Shape* >::const_iterator end = _shapes.end();
    while ( i != end ) {
        sl = dynamic_cast<ShapeList*>( *i );
        if ( sl ) {
            d = sl->minDepth();
        } else {
            d = (*i)->depth();
        }
        if ( d < res ) res = d;
        ++i;
    }
    return res;
}

#if defined( min )
#undef min 
#define _HAS_MSVC_MIN_ true
#endif

int
ShapeList::maxDepth() const
{
    int res = std::numeric_limits<int>::min();
    int d;
    ShapeList * sl;
    std::vector< Shape* >::const_iterator i = _shapes.begin();
    std::vector< Shape* >::const_iterator end = _shapes.end();
    while ( i != end ) {
        sl = dynamic_cast<ShapeList*>( *i );
        if ( sl ) {
            d = sl->maxDepth();
        } else {
            d = (*i)->depth();
        }
        if ( d > res ) res = d;
        ++i;
    }
    return res;
}

#if defined( _HAS_MSVC_MIN_ )
#define min(A,B) ((A)<(B)?(A):(B))
#endif

void
ShapeList::shiftDepth( int shift )
{
    std::vector< Shape* >::const_iterator i = _shapes.begin();
    std::vector< Shape* >::const_iterator end = _shapes.end();
    while ( i != end ) {
        (*i++)->shiftDepth( shift );
    }
}

Shape *
ShapeList::clone() const
{
    return new ShapeList( *this );
}

Shape &
ShapeList::last( const unsigned int position )
{
    return last<Shape>( position );
}

Shape &
ShapeList::top()
{
    return last<Shape>( 0 );
}


//
// Definition of the Group methods.
//

const std::string Group::_name("GroupOfShapes");

const std::string &
Group::name() const
{
    return _name;
}

Shape &
Group::rotate( double angle, const Point & rotCenter )
{
    ShapeList::rotate( angle, rotCenter );
    _clippingPath.rotate( angle, rotCenter );
    return (*this);
}

Shape &
Group::rotate( double angle )
{
    ShapeList::rotate( angle );
    _clippingPath.rotate( angle, center() );
    return (*this);
}

Shape &
Group::translate( double dx, double dy )
{
    ShapeList::translate( dx, dy );
    _clippingPath.translate( dx, dy );
    return (*this);
}

Shape &
Group::scale( double sx, double sy )
{
    Point delta = _clippingPath.center() - center();
    delta.x *= sx;
    delta.y *= sy;
    _clippingPath.scale( sx, sy );
    ShapeList::scale( sx, sy );
    delta = ( center() + delta ) - _clippingPath.center();
    _clippingPath.translate( delta.x, delta.y );
    return (*this);
}

Shape &
Group::scale( double s )
{
    Point delta = _clippingPath.center() - center();
    delta *= s;
    _clippingPath.scale( s );
    ShapeList::scale( s );
    delta = ( center() + delta ) - _clippingPath.center();
    _clippingPath.translate( delta.x, delta.y );
    return (*this);
}

Group
Group::rotated( double angle, const Point & rotCenter )
{
    return static_cast<const Group &>( Group( *this ).rotate( angle, rotCenter ) );
}

Group
Group::rotated( double angle )
{
    return static_cast<const Group &>( Group( *this ).rotate( angle ) );
}

Group
Group::translated( double dx, double dy )
{
    return static_cast<const Group &>( Group( *this ).translate( dx, dy ) );
}

Group
Group::scaled( double sx, double sy )
{
    return static_cast<const Group &>( Group( *this ).scale( sx, sy ) );
}

Group
Group::scaled( double s )
{
    return static_cast<const Group &>( Group( *this ).scale( s ) );
}


void
Group::setClippingRectangle(  float x, float y, float width, float height )
{
    _clippingPath.clear();
    _clippingPath << Point( x, y );
    _clippingPath << Point( x + width, y );
    _clippingPath << Point( x + width, y - height);
    _clippingPath << Point( x , y - height );
}

void
Group::setClippingPath(  const std::vector<Point> & points  )
{
    _clippingPath.clear();
    std::vector<Point>::const_iterator it = points.begin();
    std::vector<Point>::const_iterator end = points.end();
    while ( it != end ) {
        _clippingPath <<  *it;
        ++it;
    }
}

void
Group::setClippingPath(  const Path & path  )
{
    _clippingPath = path;
    _clippingPath.setClosed( true );
    if ( _clippingPath.size() > 1 ) {
        if ( _clippingPath[0] == _clippingPath[ _clippingPath.size() - 1 ] )
            _clippingPath.pop_back();
    }
}

void
Group::flushPostscript( std::ostream & stream,
                        const TransformEPS & transform ) const
{
    if ( _clippingPath.size() > 2 ) {
        stream << "%%% Begin Clipped Group " << _clippingCount << "\n";
        stream << " gsave n ";
        _clippingPath.flushPostscript( stream, transform );
        stream << " 0 slw clip " << std::endl;
        ShapeList::flushPostscript( stream, transform );
        stream << " grestore\n";
        stream << "%%% End Clipped Group " << _clippingCount << "\n";
        ++ _clippingCount;
    } else {
        stream << "%%% Begin Group\n";
        ShapeList::flushPostscript( stream, transform );
        stream << "%%% End Group\n";
    }
}

void
Group::flushFIG( std::ostream & stream,
                 const TransformFIG & transform,
                 std::map<DGtal::Color,int> & colormap ) const
{
    Rect box = boundingBox();
    stream << "# Begin group\n";
    stream << "6 "
    << transform.mapX( box.left ) << " "
    << transform.mapY( box.top ) << " "
    << transform.mapX( box.left + box.width ) << " "
    << transform.mapY( box.top - box.height ) << "\n";
    ShapeList::flushFIG( stream, transform, colormap );
    stream << "-6\n";
    stream << "# End Group\n";
}

void
Group::flushSVG( std::ostream & stream,
                 const TransformSVG & transform ) const
{
    if ( _clippingPath.size() > 2 ) {
        stream << "<g clip-rule=\"nonzero\">\n"
        << " <clipPath id=\"LocalClipPath" << _clippingCount << "\">\n"
        << "  <path clip-rule=\"evenodd\"  d=\"";
        _clippingPath.flushSVGCommands( stream, transform );
        stream << "\" />\n";
        stream << " </clipPath>\n";
        stream << "<g clip-path=\"url(#LocalClipPath" << _clippingCount <<")\">\n";
        ++ _clippingCount;
        ShapeList::flushSVG( stream, transform );
        stream << "</g>\n";
        stream << "</g>\n";
    } else {
        stream << "<g>\n";
        ShapeList::flushSVG( stream, transform );
        stream << "</g>\n";
    }
}

#ifdef WITH_CAIRO
void
Group::flushCairo( cairo_t * /*cr*/,
		   const TransformCairo & /*transform*/ ) const
{
    //todo
    //ShapeList::flushCairo( cr, transform );
}
#endif

void
Group::flushTikZ( std::ostream & stream,
		  const TransformTikZ & transform ) const
{
  // FIXME: implement clipping
  stream << "\\begin{scope}\n";
  ShapeList::flushTikZ( stream, transform );
  stream << "\\end{scope}\n";
}

Rect
Group::boundingBox() const
{
    if ( _clippingPath.size() > 2 )
        return ShapeList::boundingBox() && _clippingPath.boundingBox();
    else
        return ShapeList::boundingBox();
}


Shape *
Group::clone() const
{
    return new Group( *this );
}

Group &
Group::operator=( const Group & other )
{
    ShapeList::operator=( other );
    return *this;
}

unsigned int Group::_clippingCount = 0;

} // namespace LibBoard
