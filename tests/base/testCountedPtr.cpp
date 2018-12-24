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
 * @file testCountedPtr.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2012/05/31
 *
 * Functions for testing class CountedPtr.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class CountedPtr.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testCountedPtr()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing CountedPtr ..." );

  int *value=new int(5);
  CountedPtr<int> p( value );
  nbok += p.unique() ? 1 : 0;
  nb++;
  trace.info() << p << " value=" << *p<< std::endl;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "unique" << std::endl;

  *p = 6;
  trace.info() << p << " value=" << *p<< std::endl;
  nbok += p.unique() ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "unique" << std::endl;

  trace.endBlock();

  return nbok == nb;
}


bool testCountedPtrCopy()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing CountedPtr copy..." );

  int *value= new int(5);
  CountedPtr<int> p( value );
  nbok += p.unique() ? 1 : 0;
  nb++;
  trace.info() << p <<std::endl;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "unique" << std::endl;

  CountedPtr<int> q ( p );

  nbok += p.unique() ? 0: 1;
  nb++;
  trace.info() << p <<std::endl;
  trace.info() << q<<std::endl;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "not unique anymore" << std::endl;


  trace.endBlock();

  return nbok == nb;
}

struct A {
  A( int _a ) : a( _a ) 
  {
    ++nb;
    trace.info() << "#" << nb << " A::A( int ), a is " << a << std::endl;
  }
  A( const A& other ) : a( other.a ) 
  {
    ++nb;
    trace.info() << "#" << nb << " A::A( const A& ), a is " << a << std::endl;
  }
  A& operator=( const A& other )
  {
    if ( this != &other )
      a = other.a;
    trace.info() << "#" << nb << " A::op=( const A& ), a is " << a << std::endl;
    return *this;
  }
  ~A()
  {
    --nb;
    trace.info() << "#" << nb << " A::~A(), a was " << a << std::endl;
  }
  static int nb;
  int a;
};

int A::nb = 0;

bool testCountedPtrMemory()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing CountedPtr memory managment..." );

  trace.beginBlock ( "An invalid CountedPtr does not create any instance." );
  {
    CountedPtr<A> cptr;
  }
  ++nb; nbok += A::nb == 0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") " << "A::nb == 0" << std::endl;
  trace.endBlock();

  trace.beginBlock ( "CountedPtr can be used as a simple pointer with automatic deallocation." );
  {
    CountedPtr<A> cptr( new A( 10 ) );
    ++nb; nbok += A::nb == 1 ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") " << "A::nb == 1" << std::endl;
  }
  ++nb; nbok += A::nb == 0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") " << "A::nb == 0" << std::endl;
  trace.endBlock();

  trace.beginBlock ( "CountedPtr can be initialized with = CountedPtr<A>( pointer )." );
  {
    CountedPtr<A> cptr =  CountedPtr<A>( new A( 5 ) );
    ++nb; nbok += A::nb == 1 ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") " << "A::nb == 1" << std::endl;
  }
  ++nb; nbok += A::nb == 0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") " << "A::nb == 0" << std::endl;
  trace.endBlock();

  trace.beginBlock ( "CountedPtr allows to share objects." );
  {
    CountedPtr<A> cptr( new A( 7 ) );
    CountedPtr<A> cptr2 = cptr;
    ++nb; nbok += A::nb == 1 ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") " << "A::nb == 1" << std::endl;
    ++nb; nbok += cptr.get() == cptr2.get() ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") " << "cptr.get() == cptr2.get()" << std::endl;
    ++nb; nbok += cptr.count() == 2 ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") " << "cptr.count() == 2" << std::endl;
    ++nb; nbok += cptr2.count() == 2 ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") " << "cptr2.count() == 2" << std::endl;
  }
  ++nb; nbok += A::nb == 0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") " << "A::nb == 0" << std::endl;
  trace.endBlock();

  trace.beginBlock ( "CountedPtr are smart wrt assignment." );
  {
    CountedPtr<A> cptr( new A( 3 ) );
    CountedPtr<A> cptr2( new A( 12 ) );
    ++nb; nbok += A::nb == 2 ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") " << "A::nb == 2" << std::endl;
    ++nb; nbok += cptr.get() != cptr2.get() ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") " << "cptr.get() != cptr2.get()" << std::endl;
    cptr = cptr2;
    ++nb; nbok += A::nb == 1 ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") " << "A::nb == 1" << std::endl;
    ++nb; nbok += cptr.get()->a == 12 ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") " << "cptr.get()->a == 12" << std::endl;
    ++nb; nbok += cptr.get() == cptr2.get() ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") " << "cptr.get() == cptr2.get()" << std::endl;
    ++nb; nbok += cptr.count() == 2 ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") " << "cptr.count() == 2" << std::endl;
    ++nb; nbok += cptr2.count() == 2 ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") " << "cptr2.count() == 2" << std::endl;
  }
  ++nb; nbok += A::nb == 0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") " << "A::nb == 0" << std::endl;
  trace.endBlock();

  trace.endBlock();
  return nb == nbok;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class CountedPtr" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testCountedPtr()
    && testCountedPtrCopy()
    && testCountedPtrMemory();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
