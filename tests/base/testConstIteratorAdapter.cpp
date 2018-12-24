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
 * @file testConstIteratorAdapter.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/09/01
 *
 * Functions for testing class ConstIteratorAdapter.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/kernel/BasicPointFunctors.h"
#include "DGtal/base/ConstIteratorAdapter.h"
#include "DGtal/base/Circulator.h"

#include <boost/concept_check.hpp>


///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ConstIteratorAdapter.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testProjection()
{

  unsigned int nb = 0; 
  unsigned int nbok = 0; 
  
  typedef PointVector<3,int> Point3;
  typedef PointVector<2,int> Point2;
  typedef std::vector<Point3>::iterator Iterator3;

  //projector
  typedef DGtal::functors::Projector<SpaceND<2,int> > Projector2; 

  typedef ConstIteratorAdapter<Iterator3,Projector2,Point2> Adapter; 
  BOOST_CONCEPT_ASSERT(( boost::RandomAccessIterator<Iterator3> ));

  BOOST_CONCEPT_ASSERT(( boost_concepts::ReadableIteratorConcept<Adapter> ));
  BOOST_CONCEPT_ASSERT(( boost_concepts::RandomAccessTraversalConcept<Adapter> ));
  
  //range of 3d Points
  std::vector<Point3> r;
  r.push_back(Point3(0,0,0));
  r.push_back(Point3(1,0,0));
  r.push_back(Point3(2,0,0));
  r.push_back(Point3(2,1,0));
  r.push_back(Point3(2,1,1));
  r.push_back(Point3(3,1,1));
  r.push_back(Point3(4,1,1));
  r.push_back(Point3(4,2,1));
  r.push_back(Point3(4,2,2));
  r.push_back(Point3(5,2,2));
  r.push_back(Point3(6,2,2));
  r.push_back(Point3(6,3,2));
  r.push_back(Point3(6,3,3));
  r.push_back(Point3(6,4,3));
  r.push_back(Point3(6,4,4));
  r.push_back(Point3(6,5,4));
  
  //true projection
  std::vector<Point2> rtrue;
  rtrue.push_back(Point2(0,0));
  rtrue.push_back(Point2(1,0));
  rtrue.push_back(Point2(2,0));
  rtrue.push_back(Point2(2,1));
  rtrue.push_back(Point2(2,1));
  rtrue.push_back(Point2(3,1));
  rtrue.push_back(Point2(4,1));
  rtrue.push_back(Point2(4,2));
  rtrue.push_back(Point2(4,2));
  rtrue.push_back(Point2(5,2));
  rtrue.push_back(Point2(6,2));
  rtrue.push_back(Point2(6,3));
  rtrue.push_back(Point2(6,3));
  rtrue.push_back(Point2(6,4));
  rtrue.push_back(Point2(6,4));
  rtrue.push_back(Point2(6,5));
  
  trace.beginBlock ( "Testing block ..." );

  trace.info() << "2d points after projection (XY)" << endl; 

  Projector2 proj; 
    
  Adapter aitBegin(r.begin(),proj);
  Adapter ait = aitBegin;    
  Adapter aitEnd(r.end(),proj); 

  for ( ; ait != aitEnd; ++ait) 
    {
      trace.info() << *(ait.base()); 
      trace.info() << *ait; 
      trace.info() << "(" << ait->operator[](0) << ", " << ait->operator[](1) << ")" << endl;
    }

  //comparison
  if ( std::equal( rtrue.begin(), rtrue.end(), aitBegin ) == true )
    nbok++; 
  nb++; 
  trace.info() << nbok << "/" << nb << std::endl;   

  //basic operators
  trace.info() << "basic operators (operator==)" << endl; 
  if ( ( ait != aitBegin ) && ( ait == aitEnd ) )
    nbok++; 
  nb++; 
  trace.info() << nbok << "/" << nb << std::endl;   
  
  //random access
  ait = (aitBegin + 3);
  ait += 1;
  ait = 1 + ait; 
  trace.info() << "random access operators (operator+)" << endl; 
  trace.info() << *(aitBegin.base()) << *aitBegin << endl; 
  trace.info() << "+5" << std::endl; 
  trace.info() << *(ait.base()) << *ait << endl; 
  if ( ( *ait == Point2(3,1) ) == true )
    nbok++; 
  nb++; 
  trace.info() << nbok << "/" << nb << std::endl;   

  trace.info() << "backward scanning" << endl; 
  std::reverse_iterator<Adapter> raitBegin( aitEnd ); 
  if ( std::equal( rtrue.rbegin(), rtrue.rend(), raitBegin ) == true )
    nbok++; 
  nb++; 
  trace.info() << nbok << "/" << nb << std::endl;   
  
  trace.info() << "circular scanning" << endl; 
  Circulator<Adapter> caitBegin( aitBegin, aitBegin, aitEnd ); 
  if ( std::equal( rtrue.begin(), rtrue.end(), caitBegin ) == true )
    nbok++; 
  nb++; 
  trace.info() << nbok << "/" << nb << std::endl;   
  

  trace.endBlock();
    
  return (nb == nbok);
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class ConstIteratorAdapter" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testProjection()
  ; // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
