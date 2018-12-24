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
 * @file testLatticePolytope2D.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/04/19
 *
 * Functions for testing class LatticePolytope2D.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>

//#define DEBUG_LatticePolytope2D

#include "DGtal/base/Common.h"
#include "DGtal/arithmetic/LatticePolytope2D.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/io/boards/Board2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class LatticePolytope2D.
///////////////////////////////////////////////////////////////////////////////

template <typename LatticePolytope2D>
bool
checkCut( LatticePolytope2D & cip,
          typename LatticePolytope2D::HalfSpace hs )
{
  trace.beginBlock ( "Check cut, see <cip.eps> and <cip2.eps>" );
  typedef typename LatticePolytope2D::Domain Domain;
  typedef typename DigitalSetSelector< Domain, BIG_DS+HIGH_BEL_DS >::Type DigitalSet;
  typedef typename DigitalSet::ConstIterator ConstIterator;

  Domain d = cip.boundingBoxDomain();
#ifdef DEBUG_LatticePolytope2D
  Board2D board;
  board << SetMode( d.className(), "Grid" ) << d;
  DigitalSet aSet( d );
  Shapes<Domain>::makeSetFromPointPredicate( aSet, hs );
  Color col1( 100, 100, 255 );
  Color col2( 180, 180, 255 );
  board << CustomStyle( aSet.className(), new CustomColors( col1, col2 ) )
        << aSet;
  board << SetMode( cip.className(), "Transparent" ) << cip;
  board.saveEPS( "cip.eps" );
  board.clear();
#endif

  DigitalSet cipSet( d );
  DigitalSet cipSet2( d );
  cip.getIncludedDigitalPoints( cipSet );
  cip.cut( hs );
  cip.getIncludedDigitalPoints( cipSet2 );
#ifdef DEBUG_LatticePolytope2D
  board << SetMode( d.className(), "Grid" ) << d;
  board << CustomStyle( aSet.className(), new CustomColors( col1, col2 ) )
        << cipSet;
  board << CustomStyle( aSet.className(), new CustomColors( Color( 255, 180, 20 ), Color( 200, 170, 0 ) ) )
        << cipSet2;
  board << SetMode( cip.className(), "Transparent" ) << cip;
  board.saveEPS( "cip2.eps" );
#endif

  unsigned int nbok = 0;
  unsigned int nb = 0;
  for ( ConstIterator it = cipSet2.begin(), it_end = cipSet2.end();
        it != it_end; ++it )
    {
      nbok += ( cipSet.find( *it ) != cipSet.end() ) ? 1 : 0;
      ++nb;
      nbok += hs( *it );
      ++nb;
    }
  for ( ConstIterator it = cipSet.begin(), it_end = cipSet.end();
        it != it_end; ++it )
    {
      if ( cipSet2.find( *it ) == cipSet2.end() )
        nbok += ! hs( *it );
      else
        nbok += hs( *it );
      ++nb;
    }
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " cip.size()=" << cip.size()
               << " #before=" << cipSet.size()
               << " #after=" << cipSet2.size()
               << std::endl;
  trace.endBlock();
  return nbok == nb;
}

/**
 * Example of a test. To be completed.
 *
 */
template <typename Space>
bool testLatticePolytope2D()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing block LatticePolytope2D area and centroid" );
  typedef typename Space::Point Point;
  typedef typename Space::Vector Vector;
  typedef typename Space::Integer Integer;
  typedef LatticePolytope2D<Space> CIP;
  typedef typename CIP::Point3I Point3I;
  typedef typename CIP::Domain Domain;
  typedef typename CIP::HalfSpace HalfSpace;
  typedef typename CIP::Iterator Iterator;
  typedef typename DigitalSetSelector< Domain, BIG_DS+HIGH_BEL_DS >::Type DigitalSet;

  CIP cip;
  cip.pushBack( Point( 0, 0 ) );
  cip.pushBack( Point( 5, 0 ) );
  cip.pushBack( Point( 0, 3 ) );
  Integer area2 = cip.twiceArea();
  trace.info() << "- 2*area   = " << area2 << std::endl;
  ++nb, nbok += ( area2 == 15 ) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "2*area == 15" << std::endl;
  Point3I c = cip.centroid( area2 );
  trace.info() << "- centroid = " << c << std::endl;
  ++nb, nbok += ( c == Point3I( 75, 45, 45 ) ) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "centroid == [75,45,45]" << std::endl;
  Domain d = cip.boundingBoxDomain();
  trace.info() << "- domain = " << d << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Output LatticePolytope2D in <cip.eps>" );
  cip.pushBack( Point( -4, 4 ) );
  cip.pushBack( Point( -7, 2 ) );
  cip.pushBack( Point( -5, 1 ) );
  Board2D board;
  d = cip.boundingBoxDomain();
  board << SetMode( d.className(), "Grid" ) << d;
  DigitalSet aSet( d );
  HalfSpace h( Vector( 1, 3 ), 8 );
  //HalfSpace h = cip.halfSpace( ++cip.begin() );
  Shapes<Domain>::makeSetFromPointPredicate( aSet, h );
  Color col1( 100, 100, 255 );
  Color col2( 180, 180, 255 );
  board << CustomStyle( aSet.className(), new CustomColors( col1, col2 ) )
        << aSet;
  cip.getIncludedDigitalPoints( aSet );
  board << CustomStyle( aSet.className(), new CustomColors( Color( 255, 180, 20 ), Color( 200, 130, 0 ) ) )
        << aSet;
  board << SetMode( cip.className(), "Transparent" ) << cip;
  Iterator itA1, itB2;
  //SizeCouple nbs =
  cip.findCut( itA1, itB2, h );
  Iterator itB1 = itA1; ++itB1;
  if ( itB1 == cip.end() ) itB1 = cip.begin();
  Iterator itA2 = itB2; ++itA2;
  if ( itA2 == cip.end() ) itA2 = cip.begin();
  Color col3( 0, 255, 0 );
  Color col4( 255, 0, 0 );
  board << CustomStyle( Point().className(), new CustomColors( col3, col3 ) )
        << *itA1 << *itA2;
  board << CustomStyle( Point().className(), new CustomColors( col4, col4 ) )
        << *itB1 << *itB2;
  board.saveEPS( "cip.eps" );
  board.saveSVG( "cip.svg" );
  trace.endBlock();

  trace.beginBlock ( "Output cut LatticePolytope2D in <cip2.eps>" );
  board.clear();
  board << SetMode( d.className(), "Grid" ) << d;
  board << SetMode( cip.className(), "Transparent" ) << cip;
  bool wasCut = cip.cut( h );
  FATAL_ERROR(wasCut);
  board << SetMode( cip.className(), "Filled" ) << cip;
  board.saveEPS( "cip2.eps" );
  board.saveSVG( "cip2.svg" );
  trace.endBlock();

  checkCut( cip, HalfSpace( Vector( -2, 3 ), 4 ) );

  return nbok == nb;
}

int myRand( int nb )
{
  return rand() % nb;
}

/**
 * Example of a test. To be completed.
 *
 */
template <typename Space>
bool exhaustiveTestLatticePolytope2D()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing block LatticePolytope2D area and centroid" );
  typedef typename Space::Point Point;
  typedef typename Space::Vector Vector;
  typedef typename Space::Integer Integer;
  typedef LatticePolytope2D<Space> CIP;
  typedef typename CIP::Point3I Point3I;
  typedef typename CIP::Domain Domain;
  typedef typename CIP::HalfSpace HalfSpace;

  CIP cip;
  cip.pushBack( Point( 0, 0 ) );
  cip.pushBack( Point( 8, -3 ) );
  cip.pushBack( Point( 17, 2 ) );
  cip.pushBack( Point( 21, 13 ) );
  cip.pushBack( Point( 13, 19 ) );
  cip.pushBack( Point( 6, 17 ) );
  cip.pushBack( Point( -3, 6 ) );
  Integer area2 = cip.twiceArea();
  trace.info() << "- 2*area   = " << area2 << std::endl;
  Point3I c = cip.centroid( area2 );
  trace.info() << "- centroid = " << c << std::endl;
  Domain d = cip.boundingBoxDomain();
  trace.info() << "- domain = " << d << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Check cuts..." );
  for ( unsigned int j = 0; j < 100; ++j )
    {
      CIP cip2 = cip;
      int x = 0;
      int y = 0;
      while ( ( x == 0 ) && ( y == 0 ) )
        {
          x = myRand( 63 ) - 31;
          y = myRand( 63 ) - 31;
        }
      int g = IntegerComputer<int>::staticGcd( x , y );
      x /= g; y /= g;
      int cc = myRand( 4 ) *x + myRand( 4 ) * y + myRand( 40 ) + 40;
      for ( unsigned int i = 0; i < 10; ++i, cc -= myRand( 40 ) )
        {
          HalfSpace h( Vector( x, y ), cc );
          trace.info() << "[" << j << " size=" << cip2.size() << "]"
                       << " cut by (" << x << "," << y << ")," << c << std::endl;
          ++nb, nbok += checkCut( cip2, h ) ? 1 : 0;
          trace.info() << "(" << nbok << "/" << nb << ") cuts" << std::endl;
          //std::cerr << " " << cip2.size() << flush;
          if ( nb != nbok ) break;
        }
      std::cerr << std::endl;
      if ( nb != nbok ) break;
    }
  trace.endBlock();
  return nbok == nb;
}

/**
 * Example of a test. To be completed.
 *
 */
template <typename Space>
bool specificTestLatticePolytope2D()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  typedef typename Space::Point Point;
  typedef typename Space::Vector Vector;
  typedef LatticePolytope2D<Space> CIP;
  typedef typename CIP::Domain Domain;
  typedef typename CIP::HalfSpace HalfSpace;
  typedef typename CIP::ConstIterator ConstIterator;
  typedef typename DigitalSetSelector< Domain, BIG_DS+HIGH_BEL_DS >::Type DigitalSet;

  CIP cip;
  cip.pushBack( Point( 0, 0 ) );
  cip.pushBack( Point( 8, -3 ) );
  cip.pushBack( Point( 17, 2 ) );
  cip.pushBack( Point( 21, 13 ) );
  cip.pushBack( Point( 13, 19 ) );
  cip.pushBack( Point( 6, 17 ) );
  cip.pushBack( Point( -3, 6 ) );
  HalfSpace hs1( Vector( -5, 11 ), 8 ); //12
  HalfSpace hs2( Vector( -3, -11 ), 8 ); //-37
  ++nb, nbok += checkCut( cip, hs1 ) ? 1 : 0;

  Domain d = cip.boundingBoxDomain();
  Board2D board;
  board << SetMode( d.className(), "Grid" ) << d;
  DigitalSet aSet( d );
  ConstIterator itv = cip.begin();
  ++itv; ++itv; ++itv; ++itv; ++itv; ++itv; ++itv;
  HalfSpace hs( cip.halfSpace( itv ) );
  Shapes<Domain>::makeSetFromPointPredicate( aSet, hs );
  Color col1( 100, 180, 100 );
  Color col2( 130, 200, 130 );
  board << CustomStyle( aSet.className(), new CustomColors( col1, col2 ) )
        << aSet;
  board << SetMode( cip.className(), "Transparent" ) << cip;
  Point p( 0, 0 );
  board << CustomStyle( p.className(), new CustomColors( Color::Red, Color::Red ) )
        << p;
  board.saveEPS( "cip3.eps" );
  board.clear();

  ++nb, nbok += checkCut( cip, hs2 ) ? 1 : 0;
  return nbok == nb;
}

template <typename Space>
bool
checkOutputConvexHullBorder()
{
  typedef typename Space::Point Point;
  typedef typename Space::Vector Vector;
  typedef typename Space::Integer Integer;
  typedef LatticePolytope2D<Space> CIP;
  typedef typename CIP::Domain Domain;
  typedef typename CIP::HalfSpace HalfSpace;
  typedef typename DigitalSetSelector< Domain, BIG_DS+HIGH_BEL_DS >::Type DigitalSet;
  IntegerComputer<Integer> ic;

  BOOST_CONCEPT_ASSERT(( boost::Container< CIP > ));

  Point c1( 0, 0 );
  Point c3( 30, 0 );
  Point A( -10, -2 );
  Point B( 40, 27 );
  Point In( 1, 0 );
  HalfSpace hs1( c1, c1 + Vector( 0, 1 ), In, ic );
  HalfSpace hs2( A, B, In, ic );
  HalfSpace hs3( c3, c3 + Vector( 0, 1 ), In, ic );
  CIP cip;
  cip.pushBack( c1 );
  cip.computeConvexHullBorder( std::back_inserter( cip ), c1, c3, hs1, hs2, hs3 );
  cip.pushBack( c3 );

  Domain d = cip.boundingBoxDomain();
  Board2D board;
  board << SetMode( d.className(), "Grid" ) << d;
  DigitalSet aSet( d );
  Shapes<Domain>::makeSetFromPointPredicate( aSet, hs2 );
  Color col1( 100, 180, 100 );
  Color col2( 220, 250, 220 );
  board << CustomStyle( aSet.className(), new CustomColors( col1, col2 ) )
        << aSet;
  board << SetMode( cip.className(), "Transparent" ) << cip;
  // Point p( 0, 0 );
  // board << CustomStyle( p.className(), new CustomColors( Color::Red, Color::Red ) )
  //       << p;
  board.saveEPS( "cip4.eps" );
  board.clear();
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int, char** )
{
  trace.beginBlock ( "Testing class LatticePolytope2D" );

  typedef SpaceND<2, DGtal::int64_t> Z2;
  typedef SpaceND<2, DGtal::BigInteger> Z2I;
  bool res = testLatticePolytope2D<Z2>()
    && testLatticePolytope2D<Z2I>()
    && exhaustiveTestLatticePolytope2D<Z2>()
    && checkOutputConvexHullBorder<Z2>();
  //&& specificTestLatticePolytope2D<Z2>();
  //&& exhaustiveTestLatticePolytope2D<Z2I>();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
