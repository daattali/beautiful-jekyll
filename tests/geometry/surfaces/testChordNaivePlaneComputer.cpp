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

/**
 * @file testChordNaivePlaneComputer.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/03/05
 *
 * Functions for testing class ChordNaivePlaneComputer.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/geometry/surfaces/CAdditivePrimitiveComputer.h"
#include "DGtal/geometry/surfaces/ChordNaivePlaneComputer.h"
#include "DGtal/geometry/surfaces/ChordGenericNaivePlaneComputer.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::concepts;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ChordNaivePlaneComputer.
///////////////////////////////////////////////////////////////////////////////

template <typename Integer>
Integer getRandomInteger( Integer first, Integer after_last )
{
  Integer r = (Integer) rand();
  return ( r % (after_last - first) ) + first;
}

/**
 * Checks the naive plane d <= ax+by+cz <= d + max(|a|,|b|,|c|)-1
 */
template <typename Integer, typename NaivePlaneComputer>
bool
checkPlane( Integer a, Integer b, Integer c, Integer d,
            int diameter, unsigned int nbtries )
{
  typedef typename NaivePlaneComputer::Point Point;
  typedef typename Point::Component PointInteger;
  IntegerComputer<Integer> ic;
  Integer absA = ic.abs( a );
  Integer absB = ic.abs( b );
  Integer absC = ic.abs( c );
  Integer x, y, z;
  Dimension axis;
  if ( ( absA >= absB ) && ( absA >= absC ) )
    axis = 0;
  else if ( ( absB >= absA ) && ( absB >= absC ) )
    axis = 1;
  else
    axis = 2;
  Point p;
  NaivePlaneComputer plane;
  plane.init( axis, 1, 1 );
  // Checks that points within the naive plane are correctly recognized.
  unsigned int nb = 0;
  unsigned int nbok = 0;
  while ( nb != nbtries )
    {
      p[ 0 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      p[ 1 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      p[ 2 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      x = (Integer) p[ 0 ];
      y = (Integer) p[ 1 ];
      z = (Integer) p[ 2 ];
      switch ( axis ) {
      case 0: p[ 0 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - b * y - c * z, a ) ); break;
      case 1: p[ 1 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - a * x - c * z, b ) ); break;
      case 2: p[ 2 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - a * x - b * y, c ) ); break;
      }
      bool ok_ext = plane.isExtendable( p ); // should be ok
      bool ok = plane.extend( p ); // should be ok
      ++nb, nbok += ok_ext ? 1 : 0;
      ++nb, nbok += ok ? 1 : 0;
      if ( ! ok )
        {
          std::cerr << "[ERROR] p=" << p << " NOT IN plane=" << plane << std::endl;
          for ( typename NaivePlaneComputer::ConstIterator it = plane.begin(), itE = plane.end();
                it != itE; ++it )
            std::cerr << " " << *it;
          std::cerr << endl;
          std::cerr << "d <= a*x+b*y+c*z <= d+max(a,b,c)"
                    << d << " <= " << a << "*" << p[0]
                    << "+" << b << "*" << p[1]
                    << "+" << c << "*" << p[2]
                    << " = " << (a*p[0]+b*p[1]+c*p[2])
                    << std::endl;
          break;
        }
      if ( ! ok_ext )
        {
          std::cerr << "[ERROR] p=" << p << " was NOT extendable IN plane=" << plane << std::endl;
          break;
        }
      // else
      //   std::cerr << "[OK] p=" << p << " IN plane=" << plane << std::endl;
    }

  // Checks that points outside the naive plane are correctly recognized as outliers.
  while ( nb != (nbtries * 11 ) / 10 )
    {
      p[ 0 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      p[ 1 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      p[ 2 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      x = (Integer) p[ 0 ];
      y = (Integer) p[ 1 ];
      z = (Integer) p[ 2 ];
      switch ( axis ) {
      case 0: p[ 0 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - b * y - c * z, a ) ); break;
      case 1: p[ 1 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - a * x - c * z, b ) ); break;
      case 2: p[ 2 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - a * x - b * y, c ) ); break;
      }
      PointInteger tmp = getRandomInteger<PointInteger>( 2, 5 )
        * (2*getRandomInteger<PointInteger>( 0, 2 ) - 1 );
      p[ axis ] += tmp;
      bool ok_ext = ! plane.isExtendable( p ); // should *not* be ok
      bool ok = ! plane.extend( p ); // should *not* be ok
      ++nb, nbok += ok ? 1 : 0;
      ++nb, nbok += ok_ext ? 1 : 0;
      if ( ! ok )
        {
          std::cerr << "[ERROR] p=" << p << " IN plane=" << plane << std::endl;
          break;
        }
      if ( ! ok_ext )
        {
          std::cerr << "[ERROR] p=" << p << " was extendable IN plane=" << plane << std::endl;
          break;
        }
      // else
      //   std::cerr << "[OK] p=" << p << " IN plane=" << plane << std::endl;
    }
  return nb == nbok;
}

/**
 * Checks the naive plane d <= ax+by+cz <= d + max(|a|,|b|,|c|)-1
 */
template <typename Integer, typename NaivePlaneComputer>
bool
checkPlaneGroupExtension( Integer a, Integer b, Integer c, Integer d,
                          int diameter, unsigned int nbtries )
{
  typedef typename NaivePlaneComputer::Point Point;
  typedef typename Point::Component PointInteger;
  IntegerComputer<Integer> ic;
  Integer absA = ic.abs( a );
  Integer absB = ic.abs( b );
  Integer absC = ic.abs( c );
  Integer x, y, z;
  Dimension axis;
  if ( ( absA >= absB ) && ( absA >= absC ) )
    axis = 0;
  else if ( ( absB >= absA ) && ( absB >= absC ) )
    axis = 1;
  else
    axis = 2;
  Point p;
  NaivePlaneComputer plane;
  plane.init( axis, 1, 1 );
  // Checks that points within the naive plane are correctly recognized.
  unsigned int nb = 0;
  unsigned int nbok = 0;
  while ( nb < nbtries )
    {
      std::vector<Point> points( 5 );
      for ( unsigned int i = 0; i < 5; ++i )
        {
          Point & pp = points[ i ];
          pp[ 0 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
          pp[ 1 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
          pp[ 2 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
          x = (Integer) pp[ 0 ];
          y = (Integer) pp[ 1 ];
          z = (Integer) pp[ 2 ];
          switch ( axis ) {
          case 0: pp[ 0 ] = NumberTraits<Integer>::castToInt64_t
              ( ic.ceilDiv( d - b * y - c * z, a ) ); break;
          case 1: pp[ 1 ] = NumberTraits<Integer>::castToInt64_t
              ( ic.ceilDiv( d - a * x - c * z, b ) ); break;
          case 2: pp[ 2 ] = NumberTraits<Integer>::castToInt64_t
              ( ic.ceilDiv( d - a * x - b * y, c ) ); break;
          }
        }
      bool ok_ext = plane.isExtendable( points.begin(), points.end() ); // should be ok
      bool ok = plane.extend( points.begin(), points.end() ); // should be ok
      ++nb, nbok += ok_ext ? 1 : 0;
      ++nb, nbok += ok ? 1 : 0;
      if ( ! ok )
        {
          std::cerr << "[ERROR] p=" << points[ 0 ] << " NOT IN plane=" << plane << std::endl;
          for ( typename NaivePlaneComputer::ConstIterator it = plane.begin(), itE = plane.end();
                it != itE; ++it )
            std::cerr << " " << *it;
          std::cerr << endl;
          std::cerr << "d <= a*x+b*y+c*z <= d+max(a,b,c)"
                    << d << " <= " << a << "*" << p[0]
                    << "+" << b << "*" << p[1]
                    << "+" << c << "*" << p[2]
                    << " = " << (a*p[0]+b*p[1]+c*p[2])
                    << std::endl;
          break;
        }
      if ( ! ok_ext )
        {
          std::cerr << "[ERROR] p=" << p << " was NOT extendable IN plane=" << plane << std::endl;
          break;
        }
      // else
      //   std::cerr << "[OK] p=" << p << " IN plane=" << plane << std::endl;
    }

  // Checks that points outside the naive plane are correctly recognized as outliers.
  while ( nb < (nbtries * 11 ) / 10 )
    {
      p[ 0 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      p[ 1 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      p[ 2 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      x = (Integer) p[ 0 ];
      y = (Integer) p[ 1 ];
      z = (Integer) p[ 2 ];
      switch ( axis ) {
      case 0: p[ 0 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - b * y - c * z, a ) ); break;
      case 1: p[ 1 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - a * x - c * z, b ) ); break;
      case 2: p[ 2 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - a * x - b * y, c ) ); break;
      }
      PointInteger tmp = getRandomInteger<PointInteger>( 2, 5 )
        * (2*getRandomInteger<PointInteger>( 0, 2 ) - 1 );
      p[ axis ] += tmp;
      bool ok_ext = ! plane.isExtendable( p ); // should *not* be ok
      bool ok = ! plane.extend( p ); // should *not* be ok
      ++nb, nbok += ok ? 1 : 0;
      ++nb, nbok += ok_ext ? 1 : 0;
      if ( ! ok )
        {
          std::cerr << "[ERROR] p=" << p << " IN plane=" << plane << std::endl;
          break;
        }
      if ( ! ok_ext )
        {
          std::cerr << "[ERROR] p=" << p << " was extendable IN plane=" << plane << std::endl;
          break;
        }
      // else
      //   std::cerr << "[OK] p=" << p << " IN plane=" << plane << std::endl;
    }
  return nb == nbok;
}



/**
 * Checks the naive plane d <= ax+by+cz <= d + max(|a|,|b|,|c|)-1
 */
template <typename Integer, typename GenericNaivePlaneComputer>
bool
checkGenericPlane( Integer a, Integer b, Integer c, Integer d,
                   int diameter, unsigned int nbtries )
{
  typedef typename GenericNaivePlaneComputer::Point Point;
  typedef typename Point::Component PointInteger;
  IntegerComputer<Integer> ic;
  Integer absA = ic.abs( a );
  Integer absB = ic.abs( b );
  Integer absC = ic.abs( c );
  Integer x, y, z;
  Dimension axis;
  if ( ( absA >= absB ) && ( absA >= absC ) )
    axis = 0;
  else if ( ( absB >= absA ) && ( absB >= absC ) )
    axis = 1;
  else
    axis = 2;
  Point p;
  GenericNaivePlaneComputer plane;
  plane.init( 1, 1 );
  // Checks that points within the naive plane are correctly recognized.
  unsigned int nb = 0;
  unsigned int nbok = 0;
  while ( nb != nbtries )
    {
      p[ 0 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      p[ 1 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      p[ 2 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      x = (Integer) p[ 0 ];
      y = (Integer) p[ 1 ];
      z = (Integer) p[ 2 ];
      switch ( axis ) {
      case 0: p[ 0 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - b * y - c * z, a ) ); break;
      case 1: p[ 1 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - a * x - c * z, b ) ); break;
      case 2: p[ 2 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - a * x - b * y, c ) ); break;
      }
      bool ok_ext = plane.isExtendable( p ); // should be ok
      bool ok = plane.extend( p ); // should be ok
      ++nb, nbok += ok_ext ? 1 : 0;
      ++nb, nbok += ok ? 1 : 0;
      if ( ! ok )
        {
          std::cerr << "[ERROR] p=" << p << " NOT IN plane=" << plane << std::endl;
          for ( typename GenericNaivePlaneComputer::ConstIterator it = plane.begin(), itE = plane.end();
                it != itE; ++it )
            std::cerr << " " << *it;
          std::cerr << endl;
          std::cerr << "d <= a*x+b*y+c*z <= d+max(a,b,c)"
                    << d << " <= " << a << "*" << p[0]
                    << "+" << b << "*" << p[1]
                    << "+" << c << "*" << p[2]
                    << " = " << (a*p[0]+b*p[1]+c*p[2])
                    << std::endl;
          break;
        }
      if ( ! ok_ext )
        {
          std::cerr << "[ERROR] p=" << p << " was NOT extendable IN plane=" << plane << std::endl;
          break;
        }
      // else
      //   std::cerr << "[OK] p=" << p << " IN plane=" << plane << std::endl;
    }

  // Checks that points outside the naive plane are correctly recognized as outliers.
  while ( nb != (nbtries * 11 ) / 10 )
    {
      p[ 0 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      p[ 1 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      p[ 2 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
      x = (Integer) p[ 0 ];
      y = (Integer) p[ 1 ];
      z = (Integer) p[ 2 ];
      switch ( axis ) {
      case 0: p[ 0 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - b * y - c * z, a ) ); break;
      case 1: p[ 1 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - a * x - c * z, b ) ); break;
      case 2: p[ 2 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - a * x - b * y, c ) ); break;
      }
      PointInteger tmp = getRandomInteger<PointInteger>( 2, 5 )
        * (2*getRandomInteger<PointInteger>( 0, 2 ) - 1 );
      p[ axis ] += tmp;
      bool ok_ext = ! plane.isExtendable( p ); // should *not* be ok
      bool ok = ! plane.extend( p ); // should *not* be ok
      ++nb, nbok += ok ? 1 : 0;
      ++nb, nbok += ok_ext ? 1 : 0;
      if ( ! ok )
        {
          std::cerr << "[ERROR] p=" << p << " IN plane=" << plane << std::endl;
          break;
        }
      if ( ! ok_ext )
        {
          std::cerr << "[ERROR] p=" << p << " was extendable IN plane=" << plane << std::endl;
          break;
        }
      // else
      //   std::cerr << "[OK] p=" << p << " IN plane=" << plane << std::endl;
    }
  std::cerr << "plane = " << plane << std::endl;
  return nb == nbok;
}


template <typename Integer, typename NaivePlaneComputer>
bool
checkPlanes( unsigned int nbplanes, int diameter, unsigned int nbtries )
{
  //using namespace Z3i;
  //typedef ChordNaivePlaneComputer<Z3, Integer> NaivePlaneComputer;
  unsigned int nb = 0;
  unsigned int nbok = 0;
  for ( unsigned int nbp = 0; nbp < nbplanes; ++nbp )
    {
      Integer a = getRandomInteger<Integer>( (Integer) 0, (Integer) diameter / 2 );
      Integer b = getRandomInteger<Integer>( (Integer) 0, (Integer) diameter / 2 );
      Integer c = getRandomInteger<Integer>( (Integer) 0, (Integer) diameter / 2 );
      Integer d = getRandomInteger<Integer>( (Integer) 0, (Integer) diameter / 2 );
      if ( ( a != 0 ) || ( b != 0 ) || ( c != 0 ) )
        {
          ++nb, nbok += checkPlane<Integer, NaivePlaneComputer>( a, b, c, d, diameter, nbtries ) ? 1 : 0;
          if ( nb != nbok )
            {
              std::cerr << "[ERROR] (Simple extension) for plane " << a << " * x + "
                        << b << " * y + " << c << " * z = " << d << std::endl;
              break;
            }
          ++nb, nbok += checkPlaneGroupExtension<Integer, NaivePlaneComputer>( a, b, c, d, diameter, nbtries ) ? 1 : 0;
          if ( nb != nbok )
            {
              std::cerr << "[ERROR] (Group extension) for plane " << a << " * x + "
                        << b << " * y + " << c << " * z = " << d << std::endl;
              break;
            }
        }
    }
  return nb == nbok;
}

/**
 * Checks the naive plane d <= ax+by+cz <= d + max(|a|,|b|,|c|)-1
 */
template <typename Integer, typename NaivePlaneComputer>
bool
checkWidth( Integer a, Integer b, Integer c, Integer d,
            int diameter, unsigned int nbtries )
{
  typedef typename NaivePlaneComputer::Point Point;
  typedef typename NaivePlaneComputer::InternalScalar InternalScalar;
  IntegerComputer<Integer> ic;
  Integer absA = ic.abs( a );
  Integer absB = ic.abs( b );
  Integer absC = ic.abs( c );
  Integer x, y, z;
  Dimension axis;
  if ( ( absA >= absB ) && ( absA >= absC ) )
    axis = 0;
  else if ( ( absB >= absA ) && ( absB >= absC ) )
    axis = 1;
  else
    axis = 2;
  // Checks that points within the naive plane are correctly recognized.
  unsigned int nb = 0;
  unsigned int nbok = 0;
  std::vector<Point> points( nbtries );
  for ( unsigned int i = 0; i != nbtries; ++i )
    {
      Point & p = points[ i ];
      p[ 0 ] = getRandomInteger<Integer>( -diameter+1, diameter );
      p[ 1 ] = getRandomInteger<Integer>( -diameter+1, diameter );
      p[ 2 ] = getRandomInteger<Integer>( -diameter+1, diameter );
      x = (Integer) p[ 0 ];
      y = (Integer) p[ 1 ];
      z = (Integer) p[ 2 ];
      switch ( axis ) {
      case 0: p[ 0 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - b * y - c * z, a ) ); break;
      case 1: p[ 1 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - a * x - c * z, b ) ); break;
      case 2: p[ 2 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - a * x - b * y, c ) ); break;
      }
    }
  trace.beginBlock( "Computing axis width." );
  trace.info() << "- plane is "
               << d << " <= " << a << "*x"
               << "+" << b << "*y"
               << "+" << c << "*z"
               << " <= d + max(|a|,|b|,|c|)"
               << std::endl;
  trace.info() << "- " << points.size() << " points tested in diameter " << diameter
               << std::endl;
  double min = -1.0;
  for ( unsigned int i = 0; i < 3; ++i )
    {
      std::pair<InternalScalar, InternalScalar> width
        = NaivePlaneComputer::computeAxisWidth( i, points.begin(), points.end() );
      double wn = NumberTraits<InternalScalar>::castToDouble( width.first );
      double wd = NumberTraits<InternalScalar>::castToDouble( width.second );
      trace.info() << "  (" << i << ") width=" << (wn/wd) << std::endl;
      if ( min < 0.0 ) min = wn/wd;
      else if ( wn/wd < min ) min = wn/wd;
    }
  ++nb, nbok += (min < 1.0 ) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") min width = " << min
               << " < 1.0" << std::endl;
  ++nb, nbok += (0.9 < min ) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") min width = " << min
               << " > 0.9" << std::endl;
  trace.endBlock();
  return nb == nbok;
}

template <typename Integer, typename NaivePlaneComputer>
bool
checkWidths( unsigned int nbplanes, int diameter, unsigned int nbtries )
{
  //using namespace Z3i;
  //typedef ChordNaivePlaneComputer<Z3, Integer> NaivePlaneComputer;
  unsigned int nb = 0;
  unsigned int nbok = 0;
  for ( unsigned int nbp = 0; nbp < nbplanes; ++nbp )
    {
      Integer a = getRandomInteger<Integer>( (Integer) 0, (Integer) diameter / 2 );
      Integer b = getRandomInteger<Integer>( (Integer) 0, (Integer) diameter / 2 );
      Integer c = getRandomInteger<Integer>( (Integer) 0, (Integer) diameter / 2 );
      Integer d = getRandomInteger<Integer>( (Integer) 0, (Integer) diameter / 2 );
      if ( ( a != 0 ) || ( b != 0 ) || ( c != 0 ) )
        {
          ++nb, nbok += checkWidth<Integer, NaivePlaneComputer>( a, b, c, d, diameter, nbtries ) ? 1 : 0;
          if ( nb != nbok )
            {
              std::cerr << "[ERROR] (checkWidth) for plane " << a << " * x + "
                        << b << " * y + " << c << " * z = " << d << std::endl;
              break;
            }
        }
    }
  return nb == nbok;
}


/**
 * Example of a test. To be completed.
 *
 */
bool testChordNaivePlaneComputer()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  typedef DGtal::int64_t Integer;
  typedef DGtal::Z3i::Z3 Space;
  typedef DGtal::Z3i::Point Point;
  typedef ChordNaivePlaneComputer<Space, Point, Integer> NaivePlaneComputer;
  typedef ChordGenericNaivePlaneComputer<Space, Point, Integer> GenericNaivePlaneComputer;

  BOOST_CONCEPT_ASSERT(( CAdditivePrimitiveComputer< NaivePlaneComputer > ));
  BOOST_CONCEPT_ASSERT(( CAdditivePrimitiveComputer< GenericNaivePlaneComputer > ));
  BOOST_CONCEPT_ASSERT(( boost::ForwardContainer< NaivePlaneComputer > ));
  BOOST_CONCEPT_ASSERT(( boost::ForwardContainer< GenericNaivePlaneComputer > ));
  BOOST_CONCEPT_ASSERT(( CPointPredicate< NaivePlaneComputer::Primitive > ));
  BOOST_CONCEPT_ASSERT(( CPointPredicate< GenericNaivePlaneComputer::Primitive > ));

  trace.beginBlock ( "Testing block: ChordNaivePlaneComputer instantiation." );
  NaivePlaneComputer plane;
  Point pt0( 0, 0, 0 );
  plane.init( 2, 1, 1 );
  bool pt0_inside = plane.extend( pt0 );
  ++nb, nbok += pt0_inside == true ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") Plane=" << plane
               << std::endl;
  Point pt1( Point( 2, 0, 0 ) );
  bool pt1_inside = plane.extend( pt1 );
  ++nb, nbok += pt1_inside == true ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") add " << pt1
               << " Plane=" << plane << std::endl;
  Point pt2( Point( 0, 2, 2 ) );
  bool pt2_inside = plane.extend( pt2 );
  ++nb, nbok += pt2_inside == true ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") add " << pt2
               << " Plane=" << plane << std::endl;

  Point pt3( Point( 1, 1, 1 ) );
  bool pt3_inside = plane.extend( pt3 );
  ++nb, nbok += pt3_inside == true ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") add " << pt3
               << " Plane=" << plane << std::endl;

  Point pt4( Point( -10, -10, 10 ) );
  bool pt4_inside = plane.extend( pt4 );
  ++nb, nbok += pt4_inside == false ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") impossible add " << pt4
               << " Plane=" << plane << std::endl;

  Point pt5 = pt2 + Point( 1, 0, 1 );
  bool pt5_inside = plane.extend( pt5 );
  ++nb, nbok += pt5_inside == true ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") add " << pt5
               << " Plane=" << plane << std::endl;

  Point pt6 = pt5 + Point( 6, 0, 2 );
  bool pt6_inside = plane.extend( pt6 );
  ++nb, nbok += pt6_inside == true ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") add " << pt6
               << " Plane=" << plane << std::endl;

  NaivePlaneComputer plane2;
  plane2.init( 2, 1, 1 );
  plane2.extend( Point( 10, 0, 0 ) );
  plane2.extend( Point( 0, 8, 0 ) );
  plane2.extend( Point( 0, 0, 6 ) );
  trace.info() << "(" << nbok << "/" << nb << ") "
               << " Plane2=" << plane2 << std::endl;

  ++nb, nbok += checkPlane<Integer,NaivePlaneComputer>( 11, 5, 19, 20, 100, 100 ) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb
               << ") checkPlane<Integer,NaivePlaneComputer>( 11, 5, 19, 20, 100, 100 )"
               << std::endl;

  ++nb, nbok += checkGenericPlane<Integer,GenericNaivePlaneComputer>( 11, 5, 19, 20, 100, 100 ) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb
               << ") checkGenericPlane<Integer,GenericNaivePlaneComputer>( 11, 5, 19, 20, 100, 100 )"
               << std::endl;
  ++nb, nbok += checkGenericPlane<Integer,GenericNaivePlaneComputer>( 17, 33, 7, 10, 100, 100 ) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb
               << ") checkGenericPlane<Integer,GenericNaivePlaneComputer>( 17, 33, 7, 10, 100, 100 )"
               << std::endl;
  ++nb, nbok += checkPlane<Integer,NaivePlaneComputer>( 15, 8, 13, 15, 100, 100 ) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb
                << ") checkPlane<Integer,NaivePlaneComputer>( 15, 8, 13, 15, 100, 100 )"
                << std::endl;
  ++nb, nbok += checkGenericPlane<Integer,GenericNaivePlaneComputer>( 15, 8, 13, 15, 100, 100 ) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb
               << ") checkGenericPlane<Integer,GenericNaivePlaneComputer>( 15, 8, 13, 15, 100, 100 )"
               << std::endl;
  trace.endBlock();

  {
    trace.beginBlock ( "Testing block: ChordNaivePlaneComputer vertical instantiation." );
    NaivePlaneComputer ppplane;
    Point pppt0( 0, 0, 0 );
    ppplane.init( 2, 5, 2 );
    bool pppt0_inside = ppplane.extend( pppt0 );
    ++nb, nbok += pppt0_inside == true ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") Plane=" << ppplane
                 << std::endl;
    Point pppt1( 3, 2, 2 );
    bool pppt1_inside = ppplane.extend( pppt1 );
    ++nb, nbok += pppt1_inside == true ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") Plane=" << ppplane
                 << std::endl;
    Point pppt2( 0, 0, 1 );
    bool pppt2_inside = ppplane.extend( pppt2 );
    ++nb, nbok += pppt2_inside == true ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") Plane=" << ppplane
                 << std::endl;
    Point pppt3 = pppt1 + Point( 0, 0, 1 );
    bool pppt3_inside = ppplane.extend( pppt3 );
    ++nb, nbok += pppt3_inside == true ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") Plane=" << ppplane
                 << std::endl;
    Point pppt4 = pppt3 + Point( 0, 0, 1 );
    bool pppt4_inside = ppplane.extend( pt4 );
    ++nb, nbok += pppt4_inside == true ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") Plane=" << ppplane
                 << std::endl;
    trace.endBlock();
  }

  {
    trace.beginBlock ( "Testing block: ChordNaivePlaneComputer vertical instantiation 2." );
    NaivePlaneComputer pplane;
    pplane.init( 1, 1, 1 );
    Point ppt0( -6, -3, 5 );
    bool ppt0_inside = pplane.extend( ppt0 );
    ++nb, nbok += ppt0_inside == true ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") Plane=" << pplane
                 << std::endl;
    Point ppt1( 4, 4, -5 );
    bool ppt1_inside = pplane.extend( ppt1 );
    ++nb, nbok += ppt1_inside == true ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") Plane=" << pplane
                 << std::endl;
    Point ppt2( -5, -2, 4 );
    bool ppt2_inside = pplane.extend( ppt2 );
    ++nb, nbok += ppt2_inside == true ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") Plane=" << pplane
                 << std::endl;
    trace.endBlock();
  }

  return nbok == nb;
}

template <typename NaivePlaneComputer>
bool
checkManyPlanes( unsigned int diameter,
                 unsigned int nbplanes,
                 unsigned int nbpoints )
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  typedef typename NaivePlaneComputer::InternalScalar Scalar;
  stringstream ss (stringstream::out);
  ss << "Testing block: Diameter is " << diameter << ". Check " << nbplanes << " planes with " << nbpoints << " points each.";
  trace.beginBlock ( ss.str() );
  ++nb, nbok += checkPlanes<Scalar,NaivePlaneComputer>( nbplanes, diameter, nbpoints ) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb
               << ") checkPlanes<Scalar,NaivePlaneComputer>()"
               << std::endl;
  trace.endBlock();
  return nbok == nb;
}

template <typename GenericNaivePlaneComputer>
bool
checkExtendWithManyPoints( unsigned int diameter,
                           unsigned int nbplanes,
                           unsigned int nbpoints )
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  typedef typename GenericNaivePlaneComputer::InternalScalar Integer;
  typedef typename GenericNaivePlaneComputer::Point Point;
  typedef typename Point::Coordinate PointInteger;
  IntegerComputer<Integer> ic;

  trace.beginBlock( "checkExtendWithManyPoints" );
  for ( unsigned int j = 0; j < nbplanes; ++j )
    {
      Integer a = getRandomInteger<Integer>( (Integer) 0, (Integer) diameter / 2 );
      Integer b = getRandomInteger<Integer>( (Integer) 0, (Integer) diameter / 2 );
      Integer c = getRandomInteger<Integer>( (Integer) 1, (Integer) diameter / 2 );
      Integer d = getRandomInteger<Integer>( (Integer) 0, (Integer) diameter / 2 );
      GenericNaivePlaneComputer plane;
      Dimension axis;
      if ( ( a >= b ) && ( a >= c ) )       axis = 0;
      else if ( ( b >= a ) && ( b >= c ) )  axis = 1;
      else                                  axis = 2;
      plane.init( 1, 1 );

      std::vector<Point> pts;
      for ( unsigned int i = 0; i < nbpoints; ++i )
        {
          Point p;
          p[ 0 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
          p[ 1 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
          p[ 2 ] = getRandomInteger<PointInteger>( -diameter+1, diameter );
          Integer x = (Integer) p[ 0 ];
          Integer y = (Integer) p[ 1 ];
          Integer z = (Integer) p[ 2 ];
          switch( axis ) {
          case 0: p[ 0 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - b * y - c * z, a ) ); break;
          case 1: p[ 1 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - a * x - c * z, b ) ); break;
          case 2: p[ 2 ] = NumberTraits<Integer>::castToInt64_t( ic.ceilDiv( d - a * x - b * y, c ) ); break;
          }
          pts.push_back( p );
        }
      ++nb, nbok += plane.isExtendable( pts.begin(), pts.end() ); // should be ok
      trace.info() << "(" << nbok << "/" << nb
                   << ") plane.isExtendable( pts.begin(), pts.end() )"
                   << std::endl;
      Point & any0 = pts[ getRandomInteger<int>( 0, pts.size() ) ];
      pts.push_back( any0 + Point(1,0,0) );
      Point & any1 = pts[ getRandomInteger<int>( 0, pts.size() ) ];
      pts.push_back( any1 + Point(0,1,0) );
      Point & any2 = pts[ getRandomInteger<int>( 0, pts.size() ) ];
      pts.push_back( any2 + Point(0,0,1) );
      bool check = ! plane.isExtendable( pts.begin(), pts.end() ); // should not be ok
      ++nb, nbok += check ? 1 : 0;
      trace.info() << "(" << nbok << "/" << nb
                   << ") ! plane.isExtendable( pts.begin(), pts.end() )"
                   << std::endl;
      if ( ! check )
        trace.warning() << plane << " last=" << pts.back() << std::endl
                        << "a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
      ++nb, nbok += plane.extend( pts.begin(), pts.end() - 3 ); // should be ok
      trace.info() << "(" << nbok << "/" << nb
                   << ") plane.extend( pts.begin(), pts.end() - 3)"
                   << std::endl;
      ++nb, nbok += ! plane.extend( pts.end() - 3, pts.end() ); // should not be ok
      trace.info() << "(" << nbok << "/" << nb
                   << ") ! plane.extend( pts.end() - 3, pts.end() )"
                   << std::endl;
    }
  trace.endBlock();
  return nb == nbok;
}



///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int /*argc*/, char**/* argv */)
{
  using namespace Z3i;

  trace.beginBlock ( "Testing class ChordNaivePlaneComputer" );
  bool res = true
    && testChordNaivePlaneComputer()
    && checkManyPlanes<ChordNaivePlaneComputer<Z3i::Space, Z3i::Point, DGtal::int32_t> >( 4, 100, 200 )
    && checkManyPlanes<ChordNaivePlaneComputer<Z3i::Space, Z3i::Point, DGtal::int32_t> >( 8, 100, 200 )
    && checkManyPlanes<ChordNaivePlaneComputer<Z3i::Space, Z3i::Point, DGtal::int32_t> >( 20, 100, 200 )
    && checkManyPlanes<ChordNaivePlaneComputer<Z3i::Space, Z3i::Point, DGtal::int32_t> >( 100, 100, 200 )
    && checkManyPlanes<ChordNaivePlaneComputer<Z3i::Space, Z3i::Point, DGtal::int64_t> >( 2000, 100, 200 )
    && checkWidths<DGtal::int64_t, ChordNaivePlaneComputer<Z3i::Space, Z3i::Point, DGtal::int64_t> >( 100, 1000000, 1000 )
    && checkExtendWithManyPoints<ChordGenericNaivePlaneComputer<Z3i::Space, Z3i::Point, DGtal::int64_t> >( 100, 100, 200 );

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
