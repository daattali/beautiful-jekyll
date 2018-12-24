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
 * @file testClone2.cpp
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
#include "DGtal/base/CountedPtr.h"
#include "DGtal/base/CountedPtrOrPtr.h"
#include "DGtal/base/CountedConstPtrOrConstPtr.h"
#include "DGtal/base/CowPtr.h"
#include "DGtal/base/Clone.h"
#include "DGtal/base/Alias.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/helpers/StdDefs.h"

using namespace DGtal;
using namespace std;


namespace DGtal {


  /**
     Tentative Clone.
     Performs without unnecessary duplicates "parameter -> member data"
     - const A & -> A 
     - const A & -> CowPtr<A> 
     - CowPtr<A> -> A
     - CowPtr<A> -> CowPtr<A>
     It uses an intermediate CowPtr<A>, which forces dynamic
     allocation. This slows down too much for small objects.
  */
  template <typename T>
  class NClone 
  {
    // ----------------------- Standard services ------------------------------
  public:

    /**
       Destructor. Does nothing.
     */
    inline ~NClone() {}

    /**
      Copy constructor. Invalid.
    */
    inline NClone ( const NClone & ) { ASSERT( false ); }

    /**
       Constructor from an instance of T. The object is referenced in
       'this' and is generally immediately duplicated by the user to
       instantiate a data member.
       @param t any object of type T.
    */
    inline NClone( const T & t ) : myCowPtr( const_cast<T*>( &t ) ) {}

    /**
       Constructor from a pointer to a valid instance of T. The object is referenced in
       'this' and is generally immediately duplicated by the user to
       instantiate a data member.
       @param ptrT any valid pointer to a object of type T.
       @pre ptrT != 0
    */
    // NClone( const T* ptrT );

    inline NClone( CountedPtr<T> ptr ) : myCowPtr( ptr ) {}
    inline NClone( CowPtr<T> ptr ) : myCowPtr( ptr ) {}

    /**
       Cast operator to a T instance. This is only at this moment that
       the object is duplicated.  This allows things like: A a2 = a1;
       where a1 is of type NClone<A>.
    */
    inline operator T() const 
    { return myCowPtr.unique()
        ? T( *( const_cast< CowPtr<T>& >( myCowPtr ).drop() ) )
        : T( *( myCowPtr.get() ) );
    }
    // { return T( *( const_cast< CowPtr<T>& >( myCowPtr ).drop() ) ); }

    /**
       Cast operator to a CowPtr<T> instance. If the clone was initialized with an This is only at this moment that
       the object is duplicated (and only once).  This allows things like: CountedPtr<A> a2 = a1;
       where a1 is of type NClone<A>. It also allows CowPtr<A> a2 = a1;
    */
    inline operator CowPtr<T>() const 
    { return myCowPtr.unique()
        ? CowPtr<T>( new T( *( const_cast< CowPtr<T>& >( myCowPtr ).drop() ) ) )
        : myCowPtr;
    }
    //{ return myCowPtr; }

    //inline operator CountedPtr<T>() { return CountedPtr<T>( myCowPtr.get() ); }

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    /// The copy-on-write pointer to the T object that is to be duplicated.
    CowPtr<T> myCowPtr;


    // ------------------------- Hidden services ------------------------------
  private:

    /**
     * Constructor.
     * Forbidden.
     */
    NClone();


    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden (otherwise the user might be tempted to use it as a member).
     */
    NClone & operator= ( const NClone & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class NClone

} // namespace DGtal


// Dummy class to test clones and aliases.
struct DummyTbl
{
public:
  typedef int Element;
private:
  DummyTbl();
public:
  ~DummyTbl()
  {
    std::cout << "  ~DummyTbl() this=" << this << " data=" << data << std::endl;
    if ( data != 0 ) {
      std::cout << "    - freed    =" << allocated << std::endl;
      delete[] data;
    }
    else 
      std::cout << "    - nothing to do (already moved)" << std::endl;
    ++nbDeleted;
  }
  DummyTbl( int i, int val )
    : size( 0 ), allocated( i )
  {
    std::cout << "  DummyTbl( " << i << " ) this=" << this << std::endl;
    data = new Element[ allocated ];
    data[ size++ ] = val;
    std::cout << "    - allocated=" << allocated << std::endl;
    std::cout << "    - copied   =" << size << std::endl;
    ++nbCreated;
  }
  DummyTbl( const DummyTbl & a ) : size( a.size ), allocated( a.allocated )
  {
    std::cout << "  DummyTbl( const DummyTbl & a ) this=" << this << " a=" << &a << std::endl;
    data = new Element[ allocated ];
    for ( int i = 0; i < size; ++i ) data[ i ] = a.data[ i ];
    std::cout << "    - allocated=" << allocated << std::endl;
    std::cout << "    - copied   =" << size << std::endl;
    ++nbCreated;
  }

  DummyTbl( DummyTbl && a ) noexcept 
  : size( std::move( a.size ) ), allocated( std::move( a.allocated ) )
  {
    data = a.data; a.data = 0;
    std::cout << "  DummyTbl( DummyTbl && a ) this=" << this << " a=" << &a << std::endl;
    std::cout << "    - check data: a=" << allocated << " s=" << size << std::endl; 
    ++nbCreated;
    ++nbMoved;
  }

  int value() const { return data[ 0 ]; }
  void setValue( int v ) const { data[ 0 ] = v; }

private:
  DummyTbl& operator=( const DummyTbl & a ) 
  {
    data = a.data;
    std::cout << "  DummyTbl::operator=( const DummyTbl & a ) " << std::endl;
    return *this;
  }
public:
  static void reset() {
    nbCreated = 0; 
    nbDeleted = 0;
  }

	  Element* data;
  int size;
  int allocated;

  static int nbCreated;
  static int nbDeleted;
  static int nbMoved;
};

int DummyTbl::nbCreated = 0;
int DummyTbl::nbDeleted = 0;
int DummyTbl::nbMoved = 0;


struct CloneToValueMember {
  inline CloneToValueMember( Clone<DummyTbl> a1 ) : myDummyTbl( a1 ) {}
  inline int value() const { return myDummyTbl.value(); }
  DummyTbl myDummyTbl;
};

struct CloneToCountedMember { // requires explicit duplication
  inline CloneToCountedMember( Clone<DummyTbl> a1 ) // : myDummyTbl( a1 ) {} does not compile
    : myDummyTbl( new DummyTbl( a1 ) ) {}
  inline int value() const { return myDummyTbl->value(); }
  CountedPtr<DummyTbl> myDummyTbl;
};

struct CloneToCowMember {
  inline CloneToCowMember( Clone<DummyTbl> a1 ) : myDummyTbl( a1 ) {}
  inline int value() const { return myDummyTbl->value(); }
  inline void setValue( int v ) { myDummyTbl->setValue( v ); }
  CowPtr<DummyTbl> myDummyTbl;
};

struct CloneToPtrMember {
  inline CloneToPtrMember() : myDummyTbl( 0 ) {}
  inline CloneToPtrMember( Clone<DummyTbl> a1 ) : myDummyTbl( &a1 ) {}
  inline ~CloneToPtrMember() { if ( myDummyTbl != 0 ) delete myDummyTbl; else std::cerr << "[~CloneToPtrMember] error." << std::endl; }
  inline int value() const { return myDummyTbl->value(); }
  inline void setValue( int v ) { myDummyTbl->setValue( v ); }
  DummyTbl* myDummyTbl;
};

struct AliasToRefMember {
  inline AliasToRefMember( Alias<DummyTbl> a1 ) : myDummyTbl( a1 ) {}
  inline int value() const { return myDummyTbl.value(); }
  DummyTbl& myDummyTbl;
};

struct AliasToPtrMember {
  inline AliasToPtrMember( Alias<DummyTbl> a1 ) : myDummyTbl( &a1 ) {}
  inline int value() const { return myDummyTbl->value(); }
  DummyTbl* myDummyTbl;
};


struct AliasToCountedPtrOrPtrMember {
  inline AliasToCountedPtrOrPtrMember( Alias<DummyTbl> a1 ) : myDummyTbl( a1 ) {}
  inline int value() const { return myDummyTbl->value(); }
  CountedPtrOrPtr<DummyTbl> myDummyTbl;
};

struct AliasToConstRefMember { // restricted but valid.
  inline AliasToConstRefMember( Alias<DummyTbl> a1 ) : myDummyTbl( a1 ) {}
  inline int value() const { return myDummyTbl.value(); }
  const DummyTbl& myDummyTbl;
};

struct ConstAliasToConstRefMember {
  inline ConstAliasToConstRefMember( ConstAlias<DummyTbl> a1 ) : myDummyTbl( a1 ) {}
  inline int value() const { return myDummyTbl.value(); }
  const DummyTbl& myDummyTbl;
};

struct ConstAliasToConstPtrMember {
  inline ConstAliasToConstPtrMember( ConstAlias<DummyTbl> a1 ) : myDummyTbl( &a1 ) {}
  inline int value() const { return myDummyTbl->value(); }
  const DummyTbl* myDummyTbl;
};

struct ConstAliasToCountedConstPtrOrConstPtrMember { 
  inline ConstAliasToCountedConstPtrOrConstPtrMember( ConstAlias<DummyTbl> a1 ) : myDummyTbl( a1 ) {}
  inline int value() const { return myDummyTbl->value(); }
  CountedConstPtrOrConstPtr<DummyTbl> myDummyTbl;
};

// struct ConstAliasToRefMember { // invalid
//    inline ConstAliasToRefMember( ConstAlias<DummyTbl> a1 ) : myDummyTbl( a1 ) {}
//    inline int value() const { return myDummyTbl.value(); }
//    DummyTbl& myDummyTbl;
// };



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

class MyPointD {
public:
  ~MyPointD() 
  { nbDeleted++; }
  MyPointD( const MyPointD & other ) 
    : _x( other._x ), _y( other._y )
  { nbCreated++; }
  MyPointD( int x, int y ) : _x( x ), _y( y )
  { nbCreated++; }
  MyPointD( double x, double y ) : _x( x ), _y( y )
  { nbCreated++; }
  MyPointD operator-( const MyPointD & other ) const
  {
    return MyPointD( _x - other._x, _y - other._y );
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
  double _x, _y;

  static int nbCreated;
  static int nbDeleted;
};

int MyPointD::nbCreated = 0;
int MyPointD::nbDeleted = 0;

//typedef Z2i::Point Point;
typedef MyPointD Point;


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

struct TriangleByCloneAndCow {
  TriangleByCloneAndCow( Clone<Point> a, Clone<Point> b, Clone<Point> c )
    : _a( a ), _b( b ), _c( c ) {}
  double perimeter() const
  {
    return (*_a - *_b).norm() + (*_b - *_c).norm() + (*_c - *_a).norm();
  }
  CowPtr<Point> _a, _b, _c;
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

template <typename Triangle>
double
computeTrianglesByCowPtr( int size )
{
  double total = 0.0;
  CowPtr<Point> A( new Point( 0, 0 ) );
  for ( int yb = 0; yb < size; ++yb ) 
    for ( int xb = 0; xb < size; ++xb ) 
      {
        CowPtr<Point> B( new Point( xb, yb ) );
        for ( int yc = 0; yc < size; ++yc ) 
          for ( int xc = 0; xc < size; ++xc )
            {
              CowPtr<Point> C( new Point( xc, yc ) );
              Triangle T( A, B, C );
              total += T.perimeter();
            }
      }
  return total;
}

/**
   Alias: Performs without unnecessary duplicates "parameter -> member data"
   - A& -> A&                       // no duplication                    (checked)
   - A* -> A&                       // no duplication, exception if null (checked)
   - A& -> A*                       // no duplication                    (checked)
   - A* -> A*                       // no duplication                    (checked)
   - CountedPtr<A> -> CountedPtr<A> // shared                            (checked)
   - CountedPtr<A> -> CowPtr<A>     // shared (not logical, but not preventable). (checked)
*/
bool testAliasCases()
{
  unsigned int nb = 0;
  unsigned int nbok = 0;
  DummyTbl a1( 100, 10 ); // +1/0
  DummyTbl* ptr_a2 = new DummyTbl( 100, 18 ); // +1/0
  CountedPtr<DummyTbl> counted_a1( new DummyTbl( 100, 12 ) ); // +1/0
  DummyTbl::reset();
  trace.beginBlock ( "Testing class Alias." );

  /*
     - A& -> A&                       // no duplication
     - A* -> A&                       // no duplication, exception if null
     - A& -> A*                       // no duplication
     - A* -> A*                       // no duplication
     - CountedPtr<A> -> CountedPtr<A> // shared
  */
  trace.beginBlock ( "Alias: #DummyTbl with DummyTbl& to DummyTbl& member. no duplication (0/0)" );
  AliasToRefMember c00( a1 ); // 0/0
  trace.info() << "D: d1.value() = " << c00.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==0 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Alias: #DummyTbl with DummyTbl* to DummyTbl& member. no duplication (0/0)" );
  AliasToRefMember c10( ptr_a2 ); // 0/0
  trace.info() << "D: d1.value() = " << c10.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==0 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Alias: #DummyTbl with DummyTbl& to DummyTbl* member. no duplication (0/0)" );
  AliasToPtrMember c01( a1 ); // 0/0
  trace.info() << "D: d1.value() = " << c01.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==0 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Alias: #DummyTbl with DummyTbl* to DummyTbl* member. no duplication (0/0)" );
  AliasToPtrMember c11( ptr_a2 ); // 0/0
  trace.info() << "D: d1.value() = " << c11.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==0 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Alias: #DummyTbl with DummyTbl& to CountedPtrOrPtr<DummyTbl> member. no duplication (0/0)" );
  AliasToCountedPtrOrPtrMember c06( a1 ); // 0/0
  trace.info() << "D: d1.value() = " << c06.value() << std::endl;
  trace.info() << c06.myDummyTbl << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==0 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Alias: #DummyTbl with DummyTbl* to CountedPtrOrPtr<DummyTbl> member. no duplication (0/0)" );
  AliasToCountedPtrOrPtrMember c16( a1 ); // 0/0
  trace.info() << "D: d1.value() = " << c16.value() << std::endl;
  trace.info() << c16.myDummyTbl << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==0 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  // const DummyTbl& const_a1 = a1; 
  // AliasToRefMember c02( const_a1 ); // does not execute.
  // const DummyTbl* const_ptr_a1 = &a1; 
  // AliasToRefMember c05( const_ptr_a1 ); // does not execute.

  trace.endBlock();

  delete ptr_a2;
  return nbok == nb;
}

/**
   ConstAlias: Performs without unnecessary duplicates "parameter -> member data"
   - const A & -> const A &     // no duplication                    (checked)
   - const A* -> const A &      // no duplication, exception if null (checked)
   - const A & -> const A*      // no duplication                    (checked)
   - const A* -> const A*       // no duplication                    (checked)
   - CountedPtr<A> -> CowPtr<A> // potential lazy duplication        (checked)
   - CowPtr<A> -> CowPtr<A>     // potential lazy duplication        (checked)
*/
bool testConstAliasCases()
{
  unsigned int nb = 0;
  unsigned int nbok = 0;
  DummyTbl a1( 100, 10 ); // +1/0
  DummyTbl* ptr_a2 = new DummyTbl( 100, 18 ); // +1/0
  CountedPtr<DummyTbl> counted_a1( new DummyTbl( 100, 12 ) ); // +1/0
  CowPtr<DummyTbl> cow_a1( new DummyTbl( 100, 16 ) ); // +1/0
  DummyTbl::reset();
  trace.beginBlock ( "Testing class ConstAlias." );

  /*
     - const A & -> const A &     // no duplication
     - const A* -> const A &      // no duplication, exception if null
     - const A & -> const A*      // no duplication
     - const A* -> const A*       // no duplication
     - CountedPtr<A> -> CowPtr<A> // potential lazy duplication
     - CowPtr<A> -> CowPtr<A>     // potential lazy duplication
  */
  trace.beginBlock ( "ConstAlias: #DummyTbl with const DummyTbl& to const DummyTbl& member. no duplication (0/0)" );
  ConstAliasToConstRefMember c00( a1 ); // 0/0
  trace.info() << "D: d1.value() = " << c00.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==0 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "ConstAlias: #DummyTbl with const DummyTbl* to const DummyTbl& member. no duplication (0/0)" );
  ConstAliasToConstRefMember c10( ptr_a2 ); // 0/0
  trace.info() << "D: d1.value() = " << c10.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==0 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "ConstAlias: #DummyTbl with const DummyTbl& to const DummyTbl* member. no duplication (0/0)" );
  ConstAliasToConstPtrMember c01( a1 ); // 0/0
  trace.info() << "D: d1.value() = " << c01.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==0 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "ConstAlias: #DummyTbl with const DummyTbl* to const DummyTbl* member. no duplication (0/0)" );
  ConstAliasToConstPtrMember c11( ptr_a2 ); // 0/0
  trace.info() << "D: d1.value() = " << c11.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==0 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "ConstAlias: #DummyTbl with const DummyTbl* to CountedConstPtrOrConstPtr<DummyTbl> member. No duplication (0/0)" );
  ConstAliasToCountedConstPtrOrConstPtrMember c17( ptr_a2 ); // 0/0
  trace.info() << "D: d1.value() = " << c17.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==0 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "ConstAlias: #DummyTbl with const DummyTbl& to CountedConstPtrOrConstPtr<DummyTbl> member. No duplication (0/0)" );
  ConstAliasToCountedConstPtrOrConstPtrMember c07( a1 ); // 0/0
  trace.info() << "D: d1.value() = " << c07.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==0 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "ConstAlias: #DummyTbl with CountedPtr<DummyTbl> to CountedConstPtrOrConstPtr<DummyTbl> member. No duplication (0/0)" );
  ConstAliasToCountedConstPtrOrConstPtrMember c37( counted_a1 ); // 0/0
  trace.info() << "D: d1.value() = " << c37.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==0 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  // These lines do not compile.
  // DummyTbl& ref_a1 = ConstAlias<DummyTbl>( a1 );
  // DummyTbl* ptr_a1( & ConstAlias<DummyTbl>( a1 ) );

  trace.endBlock();

  delete ptr_a2;
  return nbok == nb;
}

/**
   Clone: Performs without unnecessary duplicates "parameter -> member data"
   - const A & -> A             // immediate duplication (checked)
   - A* -> A                    // immediate duplication, acquired and deleted. (checked)
   - CountedPtr<A> -> A         // immediate duplication (checked)
   - CowPtr<A> -> A             // immediate duplication (checked)
   - A&& -> A                   // move into member      (checked)
   - const A & -> CowPtr<A>     // immediate duplication (checked)
   - A* -> CowPtr<A>            // acquired              (checked)
   - CountedPtr<A> -> CowPtr<A> // lazy duplication      (checked)
   - CowPtr<A> -> CowPtr<A>     // lazy duplication      (checked)
   - A&& -> CowPtr<A>           // move into member      (checked)
   - const A & -> A*            // immediate duplication, should be deleted at the end. (checked)
   - A* -> A*                   // acquired, should be deleted at the end. (checked)      
   - CountedPtr<A> -> A*        // immediate duplication, should be deleted at the end. (checked)         
   - CowPtr<A> -> A*            // immediate duplication, should be deleted at the end. (checked)           
   - A&& -> A*                  // move into member, should be deleted at the end. (checked)
*/  
bool testCloneCases()
{
  unsigned int nb = 0;
  unsigned int nbok = 0;
  DummyTbl a1( 50, 10 ); // +1/0
  CowPtr<DummyTbl> cow_a1( new DummyTbl( 50, 5 ) ); // +1/0
  CountedPtr<DummyTbl> counted_a1( new DummyTbl( 50, 12 ) ); // +1/0
  DummyTbl::reset();
  trace.beginBlock ( "Testing class Clone." );


  trace.beginBlock ( "Clone: #DummyTbl with (const DummyTbl &) to DummyTbl member. Duplication (+1/0)" );
  CloneToValueMember c00( a1 ); // +1/0
  trace.info() << "D: d1.value() = " << c00.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==1 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Clone: #DummyTbl with (CountedPtr<DummyTbl>) to DummyTbl member. Duplication (+1/0)" );
  CloneToValueMember c30( a1 ); // +1/0
  trace.info() << "D: d1.value() = " << c30.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==2 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Clone: #DummyTbl with (const DummyTbl &) to CountedPtr<DummyTbl> member. Duplication (+1/0)" );
  CloneToCountedMember c03( a1 ); // +1/0
  trace.info() << "D: d1.value() = " << c03.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==3 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Clone: #DummyTbl with (const DummyTbl &) to CowPtr<DummyTbl> member. Duplication (+1/0)" );
  CloneToCowMember c02( a1 ); // +1/0
  trace.info() << "D: d1.value() = " << c02.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==4 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Clone: #DummyTbl with (CowPtr<DummyTbl> &) to CowPtr<DummyTbl> member. Lazy duplication (0/0)" );
  CloneToCowMember c22( cow_a1 ); // +0/0
  trace.info() << "D: d1.value() = " << c22.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==4 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  c22.setValue( 17 );
  trace.info() << "D: d1.setValue( 17 ) -> now duplicating " << std::endl;
  trace.info() << "D: d1.value() = " << c22.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==5 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Clone: #DummyTbl with (CountedPtr<DummyTbl> &) to CowPtr<DummyTbl> member. Lazy duplication (0/0)" );
  CloneToCowMember c32( counted_a1 ); // +0/0
  trace.info() << "D: d1.value() = " << c32.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==5 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  c32.setValue( 21 );
  trace.info() << "D: d1.setValue( 21 ) -> now duplicating " << std::endl;
  trace.info() << "D: d1.value() = " << c32.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==6 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Clone: #DummyTbl with (DummyTbl*) to DummyTbl member. Acquisition, duplication, delete (+2/+1)" );
  CloneToValueMember c10( new DummyTbl( 50, 2 ) ); // +2/+1
  trace.info() << "D: d1.value() = " << c10.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==8 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Clone: #DummyTbl with (DummyTbl*) to CowPtr<DummyTbl> member. Acquisition, no duplication (+1/0)" );
  CloneToCowMember c12( new DummyTbl( 50, 15 ) ); // +1/0
  trace.info() << "D: d1.value() = " << c12.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==9 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Clone: #DummyTbl with (const DummyTbl&) to DummyTbl* member. Duplication (+1/0)" );
  CloneToPtrMember c01( a1 ); // +1/0
  trace.info() << "D: d1.value() = " << c01.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==10 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Clone: #DummyTbl with (DummyTbl*) to DummyTbl* member. Acquisition (+1/0)" );
  CloneToPtrMember c11( new DummyTbl( 50, 42 ) ); // +1/0
  trace.info() << "D: d1.value() = " << c11.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==11 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Clone: #DummyTbl with (CowPtr<DummyTbl>) to DummyTbl* member. Duplication (+1/0)" );
  CloneToPtrMember c21( cow_a1 ); // +1/0
  trace.info() << "D: d1.value() = " << c21.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==12 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Clone: #DummyTbl with (CountedPtr<DummyTbl>) to DummyTbl* member. Duplication (+1/0)" );
  CloneToPtrMember c31( counted_a1 ); // +1/0
  trace.info() << "D: d1.value() = " << c31.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==13 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Clone: #DummyTbl with (DummyTbl &&) to DummyTbl member. Duplication by move (+2/+1/+1)" );
  CloneToValueMember c40( DummyTbl( 50, -4 ) ); // +2/+1/+1
  trace.info() << "D: d1.value() = " << c40.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==15 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==2 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbMoved==1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted
               << " nbMoved=" << DummyTbl::nbMoved
	       << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Clone: #DummyTbl with (DummyTbl &&) to CowPtr<DummyTbl> member. Duplication by move (+2/+1/+1)" );
  CloneToCowMember c42( DummyTbl( 50, -9 ) ); // +2/+1/+1
  trace.info() << "D: d1.value() = " << c42.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==17 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==3 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbMoved==2 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted
               << " nbMoved=" << DummyTbl::nbMoved
	       << std::endl; 
  trace.endBlock();

  trace.beginBlock ( "Clone: #DummyTbl with (DummyTbl &&) to DummyTbl* member. Duplication by move (+2/+1/+1)" );
  CloneToCowMember c41( DummyTbl( 50, -12 ) ); // +2/+1/+1
  trace.info() << "D: d1.value() = " << c41.value() << std::endl;
  ++nb; nbok += DummyTbl::nbCreated==19 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbDeleted==4 ? 1 : 0;
  ++nb; nbok += DummyTbl::nbMoved==3 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " nbCreated=" << DummyTbl::nbCreated 
               << " nbDeleted=" << DummyTbl::nbDeleted
               << " nbMoved=" << DummyTbl::nbMoved
	       << std::endl; 
  trace.endBlock();

  trace.endBlock();

  return nbok == nb;
}

bool testCloneTimings()
{
  unsigned int nb = 0;
  unsigned int nbok = 0;
  int size = 10;
  trace.beginBlock ( "Testing Clone timings." );

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
  double t4 = computeTriangles<TriangleByClone>( size );
  trace.info() << "Perimeter is " << t4 << std::endl;
  ++nb; nbok += Point::nbCreated == Point::nbDeleted ? 1 : 0;
  ++nb; nbok += Point::nbCreated < nbC ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " Point nbCreated=" << Point::nbCreated 
               << " nbDeleted=" << Point::nbDeleted << std::endl; 
  Point::reset();
  trace.endBlock();
  trace.beginBlock ( "Total perimeter of triangles with by CloneAndCow parameter passing." );
  double t5 = computeTriangles<TriangleByCloneAndCow>( size );
  trace.info() << "Perimeter is " << t5 << std::endl;
  ++nb; nbok += Point::nbCreated == Point::nbDeleted ? 1 : 0;
  ++nb; nbok += Point::nbCreated < nbC ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " Point nbCreated=" << Point::nbCreated 
               << " nbDeleted=" << Point::nbDeleted << std::endl; 
  Point::reset();
  trace.endBlock();
  trace.beginBlock ( "Total perimeter of triangles with CowPtr by CloneAndCow parameter passing." );
  double t6 = computeTrianglesByCowPtr<TriangleByCloneAndCow>( size );
  trace.info() << "Perimeter is " << t6 << std::endl;
  ++nb; nbok += Point::nbCreated == Point::nbDeleted ? 1 : 0;
  ++nb; nbok += Point::nbCreated < nbC ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")"
               << " Point nbCreated=" << Point::nbCreated 
               << " nbDeleted=" << Point::nbDeleted << std::endl; 
  Point::reset();
  trace.endBlock();

  trace.endBlock();

  return nb == nbok;
}

int main()
{
  bool ok = true
    && testCloneCases() 
    && testCloneTimings()
    && testAliasCases()
    && testConstAliasCases();

  return ok ? 0 : 1;
}
/** @ingroup Tests **/
