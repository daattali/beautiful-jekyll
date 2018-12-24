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
 * @file testCloneAndAliases.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 *
 * @date 2012/07/02
 *
 * This file is part of the DGtal library
 */

//#define TRACE_BITS

#include <cstdio>
#include <cmath>
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/Clone.h"
#include "DGtal/base/Alias.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/helpers/StdDefs.h"

using namespace DGtal;
using namespace std;

// Dummy class to test clones and aliases.
struct A1
{
private:
  A1();
public:
  ~A1()
  {
    std::cout << "  ~A1() " << std::endl;
    ++nbDeleted;
  }
  A1( int i ) : data( i )
  {
    std::cout << "  A1( int i ) " << std::endl;
    ++nbCreated;
  }
  A1( const A1 & a ) : data( a.data )
  {
    std::cout << "  A1( const A1 & a ) " << std::endl;
    ++nbCreated;
  }
  A1& operator=( const A1 & a ) 
  {
    data = a.data;
    std::cout << "  A1::operator=( const A1 & a ) " << std::endl;
    return *this;
  }
  static void reset() {
    nbCreated = 0; 
    nbDeleted = 0;
  }

  int data;

  static int nbCreated;
  static int nbDeleted;
};

int A1::nbCreated = 0;
int A1::nbDeleted = 0;

// This class uses standard by-value parameter passing 
// The data member is an instance of A1.
struct DByValue {
  DByValue( A1 a )
    : myA1( a )
  {
    std::cout << "  DByValue( A1 a) " << std::endl;
  }

  int value() const
  {
    return myA1.data;
  }

  A1 myA1;
};

// This class uses the provided explicit by-value parameter passing (with Clone).
// The data member is an instance of A1.
struct DByClone {
  DByClone( Clone<A1> a )
    : myA1( a )
  {
    std::cout << "  DByClone( Clone<A1> a) " << std::endl;
  }

  int value() const
  {
    return myA1.data;
  }

  A1 myA1;
};

// This class uses the provided explicit by-reference parameter passing (with Alias).
// The data member is a pointer to the given instance.
struct EByAlias {
  EByAlias( Alias<A1> a )
    : myA1( &a )
  {
    std::cout << "  EByAlias( Alias<A1> a ) " << myA1 << std::endl;
  }

  int value() const
  {
    return myA1->data;
  }
  
  A1* myA1;
};

// This class uses the provided explicit by-reference parameter passing (with Alias).
// The data member is a const pointer to the given instance.
struct EByConstAlias {
  EByConstAlias( ConstAlias<A1> a )
    : myA1( &a )
  {
    std::cout << "  EByConstAlias( Alias<A1> a ) " << myA1 << std::endl;
  }

  int value() const
  {
    return myA1->data;
  }
  
  const A1* myA1;
};

class MyPoint {
public:
  ~MyPoint() 
  { nbDeleted++; }
  MyPoint( const MyPoint & other ) 
    : _x( other._x ), _y( other._y )
  { nbCreated++; }
  MyPoint( int x, int y ) : _x( x ), _y( y )
  { nbCreated++; }
  MyPoint operator-( const MyPoint & other ) const
  {
    return MyPoint( _x - other._x, _y - other._y );
  }
  double norm() const
  {
    double dx = (double) _x;
    double dy = (double) _y;
    return sqrt( dx * dx + dy * dy );
  }
  static void reset()
  {
    nbCreated = nbDeleted = 0;
  }
  int _x, _y;

  static int nbCreated;
  static int nbDeleted;
};

int MyPoint::nbCreated = 0;
int MyPoint::nbDeleted = 0;

//typedef Z2i::Point Point;
typedef MyPoint Point;

struct TriangleByConstReference {
  TriangleByConstReference( const Point & a, const Point & b, const Point & c )
    : _a( a ), _b( b ), _c( c ) {}
  double perimeter() const
  {
    return (_a - _b).norm() + (_b - _c).norm() + (_c - _a).norm();
  }
  Point _a, _b, _c;
};

struct TriangleByValue {
  TriangleByValue( Point a, Point b, Point c )
    : _a( a ), _b( b ), _c( c ) {}
  double perimeter() const
  {
    return (_a - _b).norm() + (_b - _c).norm() + (_c - _a).norm();
  }
  Point _a, _b, _c;
};

struct TriangleByClone {
  TriangleByClone( Clone<Point> a, Clone<Point> b, Clone<Point> c )
    : _a( a ), _b( b ), _c( c ) {}
  double perimeter() const
  {
    return (_a - _b).norm() + (_b - _c).norm() + (_c - _a).norm();
  }
  Point _a, _b, _c;
};

template <typename Triangle>
double
computeTriangles( int size )
{
  double total = 0.0;
  Point A( 0, 0 );
  for ( int yb = 0; yb < size; ++yb ) 
    for ( int xb = 0; xb < size; ++xb ) 
      {
        Point B( xb, yb );
        for ( int yc = 0; yc < size; ++yc ) 
          for ( int xc = 0; xc < size; ++xc )
            {
              Point C( xc, yc );
              Triangle T( A, B, C );
              total += T.perimeter();
            }
      }
  return total;
}

struct FByCloneHeap {
  FByCloneHeap( Clone<A1> a ) // not ambiguous, cost is O(N) here and lifetime of a is whatever.
    : myA1( &a )
  {
    std::cout << "  FByCloneHeap( Clone<A1> a ) " << myA1 << std::endl;
  }

  ~FByCloneHeap() { if ( myA1 != 0 ) delete myA1; }

  int value() const
  {
    return myA1->data;
  }
  
  A1* myA1;
};

struct FByCloneCowPtr {
  FByCloneCowPtr( Clone<A1> a ) // not ambiguous, cost is O(N) here and lifetime of a is whatever.
    : myA1( a )
  {
    std::cout << "  FByCloneCowPtr( Clone<A1> a ) " << myA1 << std::endl;
  }

  ~FByCloneCowPtr() {}

  int value() const
  {
    return myA1->data;
  }
  
  CowPtr<A1> myA1;
};
 
int main()
{
  unsigned int nb = 0;
  unsigned int nbok = 0;
  trace.beginBlock ( "Number of A1 instances with standard by-value parameter passing." );
  A1 a1( 10 ); // +1/ 0
  DByValue d1( a1 ); //  +2/+1
  trace.info() << "D: d1.value() = " << d1.value() << std::endl;
  ++nb; nbok += A1::nbCreated==3 ? 1 : 0;
  ++nb; nbok += A1::nbDeleted==1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << A1::nbCreated 
               << " nbDeleted=" << A1::nbDeleted << std::endl; 
  trace.endBlock();
  trace.beginBlock ( "Number of A1 instances with explicit by-value parameter passing (Clone)." );
  DByClone dd1( a1 ); // +1/0
  ++nb; nbok += A1::nbCreated==4 ? 1 : 0;
  ++nb; nbok += A1::nbDeleted==1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << A1::nbCreated 
               << " nbDeleted=" << A1::nbDeleted << std::endl; 
  trace.endBlock();
  trace.beginBlock ( "Number of A1 instances with explicit by-reference parameter passing (Alias)." );
  EByAlias e1( a1 ); // +0/0
  ++nb; nbok += A1::nbCreated==4 ? 1 : 0;
  ++nb; nbok += A1::nbDeleted==1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << A1::nbCreated 
               << " nbDeleted=" << A1::nbDeleted << std::endl; 
  trace.endBlock();
  trace.beginBlock ( "Number of A1 instances with explicit by-const reference parameter passing (Alias)." );
  EByConstAlias ee1( a1 ); // +0/0
  ++nb; nbok += A1::nbCreated==4 ? 1 : 0;
  ++nb; nbok += A1::nbDeleted==1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << A1::nbCreated 
               << " nbDeleted=" << A1::nbDeleted << std::endl; 
  trace.endBlock();
  trace.beginBlock ( "Number of A1 instances with explicit by-value parameter passing into heap (Clone)." );
  FByCloneHeap fe1( a1 ); // +1/0
  ++nb; nbok += A1::nbCreated==5 ? 1 : 0;
  ++nb; nbok += A1::nbDeleted==1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << A1::nbCreated 
               << " nbDeleted=" << A1::nbDeleted << std::endl; 
  trace.endBlock();
  trace.beginBlock ( "Number of A1 instances with explicit by-value parameter passing into CowPtr (Clone)." );
  FByCloneCowPtr fe3( a1 ); // +1/0
  ++nb; nbok += A1::nbCreated==6 ? 1 : 0;
  ++nb; nbok += A1::nbDeleted==1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << A1::nbCreated 
               << " nbDeleted=" << A1::nbDeleted << std::endl; 
  trace.endBlock();

  int size = 20;
  trace.beginBlock ( "Total perimeter of triangles with by-value parameter passing." );
  double t1 = computeTriangles<TriangleByValue>( size );
  trace.info() << "Perimeter is " << t1 << std::endl;
  ++nb; nbok += Point::nbCreated == Point::nbDeleted ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " Point nbCreated=" << Point::nbCreated 
               << " nbDeleted=" << Point::nbDeleted << std::endl; 
  int nbC = Point::nbCreated;
  Point::reset();
  trace.endBlock();
  trace.beginBlock ( "Total perimeter of triangles with by-const reference parameter passing." );
  double t2 = computeTriangles<TriangleByConstReference>( size );
  trace.info() << "Perimeter is " << t2 << std::endl;
  ++nb; nbok += Point::nbCreated == Point::nbDeleted ? 1 : 0;
  ++nb; nbok += Point::nbCreated < nbC ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " Point nbCreated=" << Point::nbCreated 
               << " nbDeleted=" << Point::nbDeleted << std::endl; 
  Point::reset();
  trace.endBlock();
  trace.beginBlock ( "Total perimeter of triangles with by Clone parameter passing." );
  double t3 = computeTriangles<TriangleByClone>( size );
  trace.info() << "Perimeter is " << t3 << std::endl;
  ++nb; nbok += Point::nbCreated == Point::nbDeleted ? 1 : 0;
  ++nb; nbok += Point::nbCreated < nbC ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " Point nbCreated=" << Point::nbCreated 
               << " nbDeleted=" << Point::nbDeleted << std::endl; 
  Point::reset();
  trace.endBlock();

  // These two lines should not compile.
  // Clone<A1> clone1( a1 );
  // Clone<A1> clone2( clone2 );  

  return ( nb == nbok ) ? 0 : 1;
}
/** @ingroup Tests **/
