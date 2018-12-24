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
 * @file testOwningOrAliasingPtr.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/11/14
 *
 * Functions for testing class OwningOrAliasingPtr.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/OwningOrAliasingPtr.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class OwningOrAliasingPtr.
///////////////////////////////////////////////////////////////////////////////

template<typename Ptr, typename Value>
bool testAccessOperators(const Ptr& aPtr, const Value& aValue)
{
  return ( (aPtr.operator->() == aPtr.get()) && (*aPtr == aValue) ); 
}

template<typename Ptr>
bool testCopyAndAssignement(const Ptr& aPtr)
{
  Ptr p1(aPtr); //copy
  Ptr p2(0); //construction
  Ptr p3 = p2; //copy
  p3 = aPtr; //assignement

  if (aPtr.isOwning())
    {
      return ( ( (p1.get() != aPtr.get()) && (*p1 == *aPtr) )
	       && ( (p2.get() != aPtr.get()) && (*p2 != *aPtr) )
	       && ( (p3.get() != aPtr.get()) && (*p3 == *aPtr) ) ); 
    }
  else
    {
      return ( ( (p1.get() == aPtr.get()) && (*p1 == *aPtr) )
	       && ( (p2.get() != aPtr.get()) && (*p2 != *aPtr) )
	       && ( (p3.get() == aPtr.get()) && (*p3 == *aPtr) ) ); 
    }
}

/**
 * Unit tests
 *
 */
bool testOwningOrAliasingPtr()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  

  int i = 10; 

  ////////////////////////////////////////////

  trace.beginBlock ( "Owning pointer (1/2)..." );

  OwningOrAliasingPtr<int> owningPtr(i);
  trace.info() << owningPtr << std::endl; 
  if ( (owningPtr.isOwning()) && (owningPtr.get() != &i) && (owningPtr.isValid()) )
    nbok++; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( testAccessOperators(owningPtr, i) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( testCopyAndAssignement(owningPtr) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  trace.endBlock();

  ////////////////////////////////////////////

  trace.beginBlock ( "Owning pointer (2/2)..." );

  OwningOrAliasingPtr<int> owningPtr2(new int(10), true);
  trace.info() << owningPtr2 << std::endl; 
  if ( (owningPtr2.isOwning()) && (owningPtr2.get() != &i) && (owningPtr2.isValid()) )
    nbok++; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( testAccessOperators(owningPtr2, *owningPtr2) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( testCopyAndAssignement(owningPtr2) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  trace.endBlock();

  /////////////////////////////////////////////

  trace.beginBlock ( "Aliasing pointer ..." );

  OwningOrAliasingPtr<int> aliasingPtr(&i);
  trace.info() << aliasingPtr << std::endl; 
  if ( (!aliasingPtr.isOwning()) && (aliasingPtr.get() == &i) && (aliasingPtr.isValid()) )
    nbok++; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl; 
  if ( testAccessOperators(owningPtr, i) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( testCopyAndAssignement(owningPtr) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  trace.endBlock();
   

  //conlusion  
  return nbok == nb;
}

class DummyBigObject
{
};

template<typename T>
class Dummy1
{
public: 
  OwningOrAliasingPtr<T> myPtr; 
public: 
  Dummy1():myPtr(new T(), true) {} //default-construction (owning)
  Dummy1(T* aPtr):myPtr(aPtr) {}   //construction from an existing object (aliasing)
}; 

template<typename T>
class Dummy2
{
public: 
  OwningOrAliasingPtr<T> myPtr; 
public: 
  Dummy2(T* aPtr):myPtr(aPtr) {}   //construction from an existing object (aliasing)
  Dummy2(T data):myPtr(data) {}    //construction with copy (owning)
}; 


/**
 * Basic usage
 *
 */
bool basicUsage()
{
  trace.beginBlock ( "Basic usage ..." );

  //1) existing or default-constructed object
  int obj = 5; 
  Dummy1<int> d1;       //default-constructed
  Dummy1<int> d2(&obj); //construction from an existing object

  //2) choice with/without copy
  int smallObj = 5; 
  Dummy2<int> d3(smallObj);           //small object copied
  DummyBigObject bigObj; 
  Dummy2<DummyBigObject> d4(&bigObj); //big object not copied

  trace.endBlock();

  return true; 
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class OwningOrAliasingPtr" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testOwningOrAliasingPtr() && basicUsage();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
