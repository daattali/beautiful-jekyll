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
 * @file testCombinDSS.cpp
 * @brief Tests for the class OneBalancedWordComputer
 * @ingroup Tests
 * @author Xavier Provençal (\c xavier.provencal@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/05/02
 *
 * Functions for testing class CombinDSS.
 *
 * This file is part of the DGtal library.
 *
 * @see CombiantorialDSS.h
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/geometry/curves/OneBalancedWordComputer.h"
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
#include "ConfigTest.h"
#include "DGtal/geometry/curves/CDynamicBidirectionalSegmentComputer.h"
#include "DGtal/geometry/curves/GreedySegmentation.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class CombinDSS.
///////////////////////////////////////////////////////////////////////////////


typedef FreemanChain<int> Contour;
typedef FreemanChain<int>::Vector Vector;



/**
 * Test exted and retract function on a complex chape
 */
bool testOneBalancedWordComputer() 
{
  typedef string::const_iterator codeIterator;
  typedef OneBalancedWordComputer< list<char>::iterator, int> OneBalancedWordComputer_list;
  typedef OneBalancedWordComputer<codeIterator, int> OneBalancedWordComputer_string;

  BOOST_CONCEPT_ASSERT(( concepts::CDynamicBidirectionalSegmentComputer<OneBalancedWordComputer_list> ));
  BOOST_CONCEPT_ASSERT(( concepts::CDynamicBidirectionalSegmentComputer<OneBalancedWordComputer_string> ));

  trace.beginBlock ( "Test different initialization methods" );

  std::string filename = testPath + "samples/france.fc";
  std::fstream fst;
  fst.open (filename.c_str(), std::ios::in);
  Contour theContour(fst);

  list<char> l;
  for ( string::const_iterator it = theContour.chain.begin(); it != theContour.chain.end(); ++it )
    {
      l.push_back( *it );
    }

  list<char>::iterator it = l.begin();

  OneBalancedWordComputer_list C1;
  C1.init( it, theContour.firstPoint() );

  OneBalancedWordComputer_list C2;
  C2.init( C1.begin() );

  OneBalancedWordComputer_string C3;
  C3.init( theContour );

  OneBalancedWordComputer_string C4;
  C4.init( theContour.begin() );

  int nbRetract = 0;
  while ( C3.end() != theContour.chain.end() )
    {
      bool b1 = C1.extendFront();
      bool b2 = C2.extendFront();
      bool b3 = C3.extendFront();
      bool b4 = C4.extendFront();
      if ( b1 && b2 && b3 && b4 )
        {
        }
      else if ( !b1 && !b2 && !b3 && !b4 )
        {
          C1.retractBack();
          C2.retractBack();
          C3.retractBack();
          C4.retractBack();
          ++nbRetract;
        }
      else
        {
          cout << b1 << " " << b2 << " " << b3 << " " << b4 << endl;
          cout << C1 << endl;
          cout << C2 << endl;
          cout << C3 << endl;
          cout << C4 << endl;
          return false;
        }
    }
  trace.endBlock();
  return (nbRetract == 3485) ;
}


/**
 * Builds OneBalancedWordComputer and ArithmeticalDSSComputer in the fourth quadrants and
 * compares them, if both are equals, the test is passed.
 */
bool CompareToArithmetical()
{
  typedef string::const_iterator codeIterator;
  typedef OneBalancedWordComputer<codeIterator, int> TestedType;
  typedef ArithmeticalDSSComputer<Contour::ConstIterator,int,4> ReferenceType;

  trace.beginBlock ( "Comparing to ArithmeticalDSSComputer" );

  std::string filename = testPath + "samples/manche.fc";
  std::fstream fst;
  fst.open (filename.c_str(), std::ios::in);
  Contour theContour(fst);
  Contour::ConstIterator it = theContour.begin();
  TestedType C;
  C.init( it );
  ReferenceType A(it);
  A.extendFront(); 
  bool res = true;
  while ( C.end() != theContour.chain.end() ) 
    {
      bool a = A.extendFront();
      bool c = C.extendFront();
      if ( a ^ c )
        {
          res = false;
          cout << "Extension test error\n";
          break;
        }
      else if ( ! a )
        {
          A.retractBack();
          C.retractBack();
        }
      // Compare positions
      if ( ( C.back() != A.back() ) || ( C.front() != A.front() )  )
        {
          res = false;
          cout << "Equality test error\n";
          break;
        }
      // Compare arithmetic parameters
      if ( ( C.getA() != A.a() ) || ( C.getB() != A.b() ) ||
           ( C.getMu() != A.mu() ) || ( C.getOmega() != A.omega() ) ||
           ( C.Uf() != A.Uf() ) || ( C.Ul() != A.Ul() ) ||
           ( C.Lf() != A.Lf() ) || ( C.Ll() != A.Ll() ) 
         )
        {
          cout << "Arithmetic parameters error\n";
          cout <<  C << endl;
          cout <<  A << endl;
          cout << "a()    " <<  C.getA()     << " --- " <<  A.a() << "\n";
          cout << "b()    " <<  C.getB()     << " --- " <<  A.b() << "\n";
          cout << "mu()   " <<  C.getMu()    << " --- " <<  A.mu() << "\n";
          cout << "omega()" <<  C.getOmega() << " --- " <<  A.omega() << "\n";
          cout << "Uf()   " <<  C.Uf()    << " --- " <<  A.Uf() << "\n";
          cout << "Ul()   " <<  C.Ul()    << " --- " <<  A.Ul() << "\n";
          cout << "Lf()   " <<  C.Lf()    << " --- " <<  A.Lf() << "\n";
          cout << "Ll()   " <<  C.Ll()    << " --- " <<  A.Ll() << endl;
          res = false;
          break;
        }
    }
  trace.endBlock();
  return res;
}



bool testInGreedySegmentation( )
{

  typedef OneBalancedWordComputer<string::const_iterator, int> combinDSS;
  typedef GreedySegmentation<combinDSS> combinSegmentation;

  std::string filename = testPath + "samples/BigBall.fc";
  std::fstream fst;
  fst.open (filename.c_str(), std::ios::in);
  Contour theContour(fst);

  trace.beginBlock ( "Test OneBalancedWordComputer in greedy segmentation" );
  combinSegmentation combin_dec( theContour.chain.begin(), theContour.chain.end(), combinDSS() );
  vector<combinDSS> theCombinDSS;
  for ( combinSegmentation::SegmentComputerIterator i = combin_dec.begin();
       i != combin_dec.end(); ++i ) 
    {
      combinDSS c( *i );
      theCombinDSS.push_back( c );
    } 
  bool ok = ( theCombinDSS.size() == 1593 );
  trace.endBlock();

  return ok;
}


/**
 * This test is an adaptation to OneBalancedWordComputer of
 * 'examples/geometre/curves/greedy-dss-decomposition.cpp' where
 * is uses ArithmeticDSS.
 *
 * It produces a slightly different decomposition since in a greedy-segmentation,
 * consecutive ArithmeticDSS overlap a single point while OneBalancedWordComputer 
 * overlap on a code and thus on two points.
 */
bool showGreedySegmantation()
{
  trace.beginBlock ( "Example testCombinDSS-greedy" );

  typedef OneBalancedWordComputer<string::const_iterator,int> combinDSS;
  typedef GreedySegmentation<combinDSS> Decomposition;
  typedef StandardDSS4<int> arithDSS;

  std::stringstream ss(stringstream::in | stringstream::out);
  ss << "31 16 11121212121212212121212212122122222322323233323333333323333323303330330030300000100010010010001000101010101111" << endl;
  Contour theContour( ss );

  Decomposition theDecomposition( theContour.chain.begin(), theContour.chain.end(), combinDSS() );
  Point p1( 0, 0 );
  Point p2( 31, 31 );
  Domain domain( p1, p2 );
  Board2D aBoard;
  aBoard << SetMode( domain.className(), "Grid" )
   << domain
   << SetMode( "PointVector", "Grid" )
   << theContour;
  //for each segment
  Point p;
  p[0] = 31;
  p[1] = 16;
  for ( Decomposition::SegmentComputerIterator i = theDecomposition.begin();
  i != theDecomposition.end(); ++i ) 
    {
      combinDSS segment(*i);
      // set the position of the combinatorilDSS 
      segment.setPosition( p );
      // Since both DSS overlap on one code, the start point of the next one is
      // the penultimate point of the current one.
      p = *( --( --( segment.pointEnd() )));

      // Build an ArithmeticDSS from the OneBalancedWordComputer.
      arithDSS toShow( *segment.pointBegin(), *segment.pointBegin() );
      for (combinDSS::ConstPointIterator it = segment.pointBegin(), 
	     itEnd = segment.pointEnd(); it != itEnd; ++it )
	toShow.extendFront( *it );
      
      aBoard << SetMode( toShow.className(), "BoundingBox" )
	     << CustomStyle( toShow.className()+"/BoundingBox", new CustomPenColor( Color::Blue ) ) 
	     << toShow; // draw each segment
    } 
  aBoard.saveSVG("testCombinDSS-greedy.svg");
  trace.endBlock();
  return 1;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :
int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class CombinDSS" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testOneBalancedWordComputer()     
    && CompareToArithmetical() 
    && testInGreedySegmentation()
    && showGreedySegmantation();

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();

  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
