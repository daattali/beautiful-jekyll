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
 * @file
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/02/02
 *
 * Functions for testing the functors on scells.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CUnaryFunctor.h"

#include "DGtal/topology/SCellsFunctors.h"
#include "DGtal/topology/CanonicSCellEmbedder.h"

#include "DGtal/topology/KhalimskySpaceND.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing the scells functors.
///////////////////////////////////////////////////////////////////////////////

template <typename TFunctor, typename TArg, typename TRes >
void checkingConcepts()
{
  BOOST_CONCEPT_ASSERT(( concepts::CUnaryFunctor<TFunctor, TArg, TRes > ));
}


/**
 * Example of a test. To be completed.
 *
 */
bool testSCellsFunctors()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing block ..." );
  
  //0-scell 2 point
  {
    typedef KhalimskySpaceND<3> K3;
    K3 theKSpace; 
    functors::SCellToPoint<K3> m(theKSpace); 
    K3::SCell s = theKSpace.sPointel( K3::Point(3,3,4) );
    K3::Point aPoint = m( s );
    trace.info() << s << aPoint <<std::endl;  
    nbok += ( aPoint == K3::Point(3,3,4) ) ? 1 : 0; 
    nb++;
  }
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  //1-scell 2 point
  {
    typedef KhalimskySpaceND<3> K3;
    K3 theKSpace; 
    functors::SCellToPoint<K3> m(theKSpace); 
    K3::SCell s = theKSpace.sCell(K3::Point(0,0,0), true); //default point and orientation 
    theKSpace.sSetKCoords( s, K3::Point(5,6,8) );
    K3::Point aPoint = m( s );
    trace.info() << s << aPoint <<std::endl;  
    nbok += ( aPoint == K3::Point(3,3,4) ) ? 1 : 0;
    nb++;
  }
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  //scell 2 midPoint
  {
    typedef KhalimskySpaceND<2> K2;
    K2 theKSpace; 
    CanonicSCellEmbedder<K2> m(theKSpace);
    K2::SCell s = theKSpace.sCell( K2::Point(0,1) );
    K2::Space::RealPoint aPoint = m( s );
    trace.info() << s << aPoint <<std::endl;  
    nbok += ( aPoint == K2::Space::RealPoint(-0.5,0) ) ? 1 : 0;
    nb++;
  }  
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

    //scell 2 arrow
  {
    typedef KhalimskySpaceND<2> K2;
    K2 theKSpace; 
    functors::SCellToArrow<K2> m(theKSpace); 
    K2::SCell s = theKSpace.sCell( K2::Point(0,1) );
    std::pair<K2::Point, K2::Vector> aArrow = m( s );
    trace.info() << s << aArrow.first << aArrow.second <<std::endl;  
    K2::Point p(0,1); 
    K2::Vector v(0,-1); 
    nbok += ( ((aArrow.first == p) && (aArrow.second == v)) ) ? 1 : 0; 
    nb++;
  }  
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  
      //scell 2 inner point
  {
    typedef KhalimskySpaceND<2> K2;
    K2 theKSpace; 
    functors::SCellToInnerPoint<K2> m(theKSpace); 
    K2::SCell s = theKSpace.sCell( K2::Point(0,1) );
    K2::Point aPoint = m( s );
    trace.info() << s << aPoint <<std::endl;  
    nbok += ( aPoint == K2::Point(0,0) ) ? 1 : 0; 
    nb++;
  }
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  
    //scell 2 outer point
  {
    typedef KhalimskySpaceND<2> K2;
    K2 theKSpace; 
    functors::SCellToOuterPoint<K2> m(theKSpace); 
    K2::SCell s = theKSpace.sCell( K2::Point(0,1) );
    K2::Point aPoint = m( s );
    trace.info() << s << aPoint <<std::endl;  
    nbok += ( aPoint == K2::Point(-1,0) ) ? 1 : 0; 
    nb++;
  }
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  
    //scell 2 incident pixels
  {
    typedef KhalimskySpaceND<2> K2;
    K2 theKSpace; 
    functors::SCellToIncidentPoints<K2> m(theKSpace); 
    K2::SCell s = theKSpace.sCell( K2::Point(0,1) );
    std::pair<K2::Point, K2::Point> aPair = m( s );
    trace.info() << s << aPair.first << aPair.second <<std::endl;  
    K2::Point p1(0,0); 
    K2::Point p2(-1,0); 
    nbok += ( ((aPair.first == p1) && (aPair.second == p2)) ) ? 1 : 0; 
    nb++;
  }  
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  
   //scell 2 code
  {
    typedef KhalimskySpaceND<2> K2;
    K2 theKSpace; 
    functors::SCellToCode<K2> m(theKSpace); 
    K2::SCell s = theKSpace.sCell( K2::Point(0,1) );
    char aCode = m( s );
    trace.info() << s << aCode <<std::endl;  
    nbok += ( aCode == '3' ) ? 1 : 0; 
    nb++;
  }
  
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  trace.endBlock();
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing SCells functors" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  //concepts
  typedef KhalimskySpaceND<2> K2;
  checkingConcepts<functors::SCellToPoint<K2>, K2::SCell, K2::Point >(); 
  checkingConcepts<CanonicSCellEmbedder<K2>, K2::SCell, K2::Space::RealPoint >();
  checkingConcepts<functors::SCellToArrow<K2>, K2::SCell, std::pair<K2::Point, K2::Vector> >(); 
  checkingConcepts<functors::SCellToInnerPoint<K2>, K2::SCell, K2::Point >(); 
  checkingConcepts<functors::SCellToOuterPoint<K2>, K2::SCell, K2::Point >(); 
  checkingConcepts<functors::SCellToIncidentPoints<K2>, K2::SCell, std::pair<K2::Point, K2::Point> >(); 
  checkingConcepts<functors::SCellToCode<K2>, K2::SCell, char >(); 

  bool res = testSCellsFunctors(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
