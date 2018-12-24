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
 * @file testFreemanChain.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2010/07/05
 *
 * Functions for testing class FreemanChain.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <sstream>
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/curves/FreemanChain.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/io/boards/Board2D.h"
#include "ConfigTest.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace LibBoard;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class FreemanChain.
///////////////////////////////////////////////////////////////////////////////
typedef SpaceND<2,int> Space2Type;
typedef HyperRectDomain<Space2Type> Domain2D;


/**
 * Test Constructors
 */
bool testConstructors()
{
  typedef FreemanChain<Space2Type::Integer> FreemanChain;
  typedef FreemanChain::ConstIterator Iterator;

  trace.beginBlock ( "Testing FreemanChain constructors" );

  trace.info() << "Constructor from string and coordinates" << endl;
  std::string s = "00001030003222321222";
  FreemanChain c1(s, -42, 12);

  trace.info() << "Constructor from point vector" << endl;
  std::vector<Space2Type::Point> myVector;
  for (Iterator i = c1.begin(); i != c1.end(); i++)
    myVector.push_back(*i);
  FreemanChain c2(myVector);

  trace.info() << "Constructor from input stream" << endl;
  std::stringstream ss;
  ss << "-42 12 " << s << "\n";
  FreemanChain c3(ss);

  trace.info() << "Copy constructor" << endl;
  FreemanChain c4(c1);

  trace.info() << "Copy operator" << endl;
  FreemanChain c5("0123" , 0, 0);
  FreemanChain c6(c5);

  c5 = c1;

  trace.info() << "c1 = " << c1 << endl;
  trace.info() << "c2 = " << c2 << endl;
  trace.info() << "c3 = " << c3 << endl;
  trace.info() << "c4 = " << c4 << endl;
  trace.info() << "c5 = " << c5 << endl;
  trace.info() << "c6 = " << c6 << endl;

  bool res = (
         (c1 == c2) && (c1 == c3) && (c1 == c4) && (c1 == c5) && (c1 != c6)
      && (c2 == c1) && (c2 == c3) && (c2 == c4) && (c2 == c5) && (c2 != c6)
      && (c3 == c1) && (c3 == c2) && (c3 == c4) && (c3 == c5) && (c3 != c6)
      && (c4 == c1) && (c4 == c2) && (c4 == c3) && (c4 == c5) && (c4 != c6)
      && (c5 == c1) && (c5 == c2) && (c5 == c3) && (c5 == c4) && (c4 != c6)
      && (c6 != c1) && (c6 != c2) && (c6 != c3) && (c6 != c4) && (c6 != c5)
      );
  trace.endBlock();
  return res;
}



/**
 * Test public services
 */
bool testPublicSercives()
{
  typedef FreemanChain<Space2Type::Integer> FreemanChain;
  typedef FreemanChain::Point Point;
  typedef FreemanChain::ConstIterator Iterator;

  trace.beginBlock ( "Testing public sercives" );

  FreemanChain fc("000103000322232122", 0, 0);
  int nbOk = 0;

  // unsigned int code( Index pos ) const;
  bool test = ( fc.code(5) == '3' );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 1 " << ((test) ? "passed" : "failed" ) << endl;

  // Size size() const;
  test = ( fc.size() == 18 );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 2 " << ((test) ? "passed" : "failed" ) << endl;

  // FreemanChain subChain( Index pos, Size n ) const;
  test = ( fc.subChain(3, 3) == FreemanChain("103", 3, 0) );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 3 " << ((test) ? "passed" : "failed" ) << endl;

  // FreemanChain operator+(const FreemanChain& other) const;
  // FreemanChain operator+=(const FreemanChain& other) const;
  FreemanChain fcA("001",0,0);
  FreemanChain fcB("001",0,0);
  FreemanChain fcC("003",0,0);
  fcB += fcC + fcB;
  test = ( fcB == FreemanChain("001003001", 0, 0) ) &&
    ( fcB.totalDisplacement() == fcA.totalDisplacement()*2 + fcC.totalDisplacement() );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 4 " << ((test) ? "passed" : "failed" ) << endl;

  // void computeBoundingBox( TInteger & min_x, TInteger& min_y,
  //        TInteger& max_x, TInteger& max_y ) const;
  int min_x, min_y, max_x, max_y;
  fc.computeBoundingBox( min_x, min_y, max_x, max_y );
  test = ( (min_x == 0) && (min_y == -2) && (max_x == 7) && (max_y == 1) );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 5 " << ((test) ? "passed" : "failed" ) << endl;

  //  typename Self::ConstIterator
  //    findQuadrantChange( OrderedAlphabet & A ) const;
  OrderedAlphabet oa( '0', 4 );
  Iterator it = fc.findQuadrantChange( oa );
  test = ( it.position() == 4 );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 6 " << ((test) ? "passed" : "failed" ) << endl;

  //  typename Self::ConstIterator
  //    findQuadrantChange4( OrderedAlphabet & A ) const;
  it = fc.findQuadrantChange4( oa );
  test = ( it.position() == 9 );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 7 " << ((test) ? "passed" : "failed" ) << endl;

  // int isClosed() const ;
  test = ( ! fc.isClosed() && ( fc + FreemanChain("21") ).isClosed() );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 8 " << ((test) ? "passed" : "failed" ) << endl;


  // int ccwLoops() const;
  test = ( FreemanChain("0001212323", 12, 21).ccwLoops() == 1 ) &&
         ( FreemanChain("0003232121", 12, 21).ccwLoops() == -1 ) &&
         ( FreemanChain("000323212", 12, 21).ccwLoops() == 0 ) &&
         ( FreemanChain("012301230123", 12, 21).ccwLoops() == 3 );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 9 " << ((test) ? "passed" : "failed" ) << endl;



  // Point getPoint ( Index pos ) const;
  it = fc.begin();
  test = true;
  for (unsigned int i=0; i <= fc.size(); ++i, ++it)
  {
    test = ( fc.getPoint(i) == *it );
    if (!test) break;
  }
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 10 " << ((test) ? "passed" : "failed" ) << endl;

  // Point firstPoint ( ) const
  // Point lastPoint ( ) const
  test = ( ( fc.subChain(4,3).firstPoint() == Point(3,1) ) &&
      ( fc.subChain(4,3).lastPoint() == Point(5,0) ) );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 11 " << ((test) ? "passed" : "failed" ) << endl;

  // FreemanChain & extend(char code);
  // FreemanChain & retract(char code);
  fcA = fc;
  fcA.extend('2');
  fcB = fcA.extend('1');
  test = ( (fcB == fc + FreemanChain("21",0,0) ) &&  fcA.isClosed()
          && ( fcB.retract().retract() == fc ) );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 12 " << ((test) ? "passed" : "failed" ) << endl;

  trace.endBlock();

  return ( nbOk == 12);

}




/**
 * test iterators
 */
bool testPointsIterators()
{
  typedef int Coordinate;
  typedef FreemanChain<Coordinate> FreemanChain;
  typedef FreemanChain::Point Point;
  typedef FreemanChain::ConstIterator PointIterator;
  typedef std::reverse_iterator<PointIterator> ReverseIterator;

  trace.beginBlock ( "Testing FreemanChain Iterator" );

  std::stringstream ss;
  std::string myString = "0 0 000011112222333";
  ss << myString << std::endl;
  FreemanChain seq(ss);

  trace.info()<< "Freeman chain set to " << myString << endl;
  trace.info()<< seq << endl;

  trace.info()<< "Iterates on points." << endl;
  std::stack<Point> myStack;

  unsigned int nbPts = 0;
  for (PointIterator i = seq.begin(); i != seq.end(); ++i)
  {
    myStack.push(*i);
    nbPts++;
  }

  trace.info()<< "Test reverse iterator." << endl;
  bool samePoints = true;
  for (ReverseIterator ri(seq.end());
      ri != ReverseIterator(seq.begin());
      ++ri)
  {
    if ( !myStack.empty() && ( *ri == myStack.top() ) )
    {
      myStack.pop();
    }
    else
    {
      samePoints = false;
      break;
    }
  }
  trace.endBlock();
  return myStack.empty() && samePoints && ( nbPts == seq.size() + 1);
}

/**
 * test codes iterators
 */
bool testCodesIterators()
{
  typedef int Coordinate;
  typedef FreemanChain<Coordinate> FreemanChain;
  typedef FreemanChain::CodesRange Range;
//  typedef Range::ConstIterator PointIterator;
//  typedef std::reverse_iterator<PointIterator> ReverseIterator;

  trace.beginBlock ( "Testing CodesRange Iterator" );

  std::stringstream ss;
  std::string myString = "0 0 000011112222333";
  ss << myString << std::endl;
  FreemanChain seq(ss);

  trace.info()<< "Freeman chain set to " << myString << endl;
  trace.info()<< seq << endl;
  Range r = seq.getCodesRange();
  trace.info()<< r << endl;

  trace.info()<< "Iterates on letters." << endl;
  std::stack<char> myStack;

  unsigned int nbLetters = 0;
  for (Range::ConstIterator i = r.begin(); i != r.end(); ++i)
  {
    myStack.push(*i);
    nbLetters++;
  }

  trace.info()<< "Test reverse iterator." << endl;
  bool samePoints = true;
  for (Range::ConstReverseIterator ri = r.rbegin();
      ri != r.rend();
      ++ri)
  {
    if ( !myStack.empty() && ( *ri == myStack.top() ) )
    {
      myStack.pop();
    }
    else
    {
      samePoints = false;
      break;
    }
  }
  trace.endBlock();
  return myStack.empty() && samePoints && ( nbLetters == seq.size() );
}

/**
 * Test static services
 */
bool testStaticServices()
{
  typedef FreemanChain<int> FreemanChain;
  typedef FreemanChain::Point Point;
  typedef std::vector<unsigned int> numVector;
  bool test = false;
  int nbOk = 0;

  trace.beginBlock ( "Testing static services" );

  //  static void write( std::ostream & out, const FreemanChain & c )
  //  static void read( std::istream & in, FreemanChain & c );
  std::string s1("0001");
  int x0 = -1;
  int y0 = -1;
  stringstream ss1, ss2;
  ss1 << x0 << " " << y0 << " " << s1 << std::endl;;
  FreemanChain f;
  FreemanChain::read(ss1, f);
  FreemanChain::write(ss2, f);
  int x, y;
  std::string s2;
  ss2 >> x >> y >> s2;
  test = (x == x0) && (y == y0) && (s1 == s2);
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 1 " << ((test) ? "passed" : "failed" ) << endl;

  //  static void getContourPoints(const FreemanChain & fc,
  //      std::vector<Point> & aVContour );
  Point p0, p1(-1,-1), p2(0,-1), p3(1,-1), p4(2,-1), p5(2,0);
  vector<Point> pointVecRef, pointVecTest;
  pointVecRef.push_back(p1);
  pointVecRef.push_back(p2);
  pointVecRef.push_back(p3);
  pointVecRef.push_back(p4);
  pointVecRef.push_back(p5);
  FreemanChain::getContourPoints( f, pointVecTest );
  test = pointVecRef == pointVecTest;
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 2 " << ((test) ? "passed" : "failed" ) << endl;


  // static void movePointFromFC(Point & aPoint, unsigned int aCode )
  Point P0(10,10), P1(10,10), P2(10,10), P3(10,10);
  FreemanChain::movePointFromFC( P0, '0'); FreemanChain::movePointFromFC( P1, '1');
  FreemanChain::movePointFromFC( P2, '2'); FreemanChain::movePointFromFC( P3, '3');
  test = ( P0 == Point(11,10) ) && ( P1 == Point(10,11) ) &&
    (P2 == Point(9,10) ) && ( P3 == Point(10,9) ) ;
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 3 " << ((test) ? "passed" : "failed" ) << endl;


  //  static unsigned int movement( unsigned int aCode1, unsigned int aCode2,
  //      bool ccw = true );
  test = ( FreemanChain::movement ( '0' , '0' , true ) == '2' ) &&
         ( FreemanChain::movement ( '0' , '1' , true ) == '1' ) &&
         ( FreemanChain::movement ( '0' , '2' , true ) == '0' ) &&
         ( FreemanChain::movement ( '0' , '3' , true ) == '3' ) &&
         ( FreemanChain::movement ( '0' , '0' , false ) == '2' ) &&
         ( FreemanChain::movement ( '0' , '1' , false ) == '3' ) &&
         ( FreemanChain::movement ( '0' , '2' , false ) == '0' ) &&
         ( FreemanChain::movement ( '0' , '3' , false ) == '1' );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 4 " << ((test) ? "passed" : "failed" ) << endl;

  // static char addToCode( char code, int n);
  test = ( FreemanChain::addToCode( '0' , 1 ) == '1' ) &&
         ( FreemanChain::addToCode( '1' , 1 ) == '2' ) &&
         ( FreemanChain::addToCode( '2' , 1 ) == '3' ) &&
         ( FreemanChain::addToCode( '3' , 1 ) == '0' ) &&
         ( FreemanChain::addToCode( '0' , -1 ) == '3' ) &&
         ( FreemanChain::addToCode( '1' , -1 ) == '0' ) &&
         ( FreemanChain::addToCode( '2' , -1 ) == '1' ) &&
         ( FreemanChain::addToCode( '3' , -1 ) == '2' ) &&
         ( FreemanChain::addToCode( '1' , 0 ) == '1' ) &&
         ( FreemanChain::addToCode( '1' , 2 ) == '3' ) &&
         ( FreemanChain::addToCode( '1' , 3 ) == '0' ) &&
         ( FreemanChain::addToCode( '1' , 4 ) == '1' ) &&
         ( FreemanChain::addToCode( '1' , 5 ) == '2' ) &&
         ( FreemanChain::addToCode( '1' , -2 ) == '3' ) &&
         ( FreemanChain::addToCode( '1' , -3 ) == '2' ) &&
         ( FreemanChain::addToCode( '1' , -4 ) == '1' ) &&
         ( FreemanChain::addToCode( '1' , -5 ) == '0' );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 5 " << ((test) ? "passed" : "failed" ) << endl;


  // static void displacement( int & dx, int & dy, unsigned int aCode );
  // static Point displacement( unsigned int aCode );
  int X[4], Y[4];
  FreemanChain::displacement( X[0] , Y[0], '0');
  FreemanChain::displacement( X[1] , Y[1], '1');
  FreemanChain::displacement( X[2] , Y[2], '2');
  FreemanChain::displacement( X[3] , Y[3], '3');

  p0 = FreemanChain::displacement( '0' );
  p1 = FreemanChain::displacement( '1' );
  p2 = FreemanChain::displacement( '2' );
  p3 = FreemanChain::displacement( '3' );

  test = (X[0] ==  1) && (Y[0] ==  0) && (p0 == Point( 1, 0)) &&
         (X[1] ==  0) && (Y[1] ==  1) && (p1 == Point( 0, 1)) &&
         (X[2] == -1) && (Y[2] ==  0) && (p2 == Point(-1, 0)) &&
         (X[3] ==  0) && (Y[3] == -1) && (p3 == Point( 0,-1)) ;
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 6 " << ((test) ? "passed" : "failed" ) << endl;


  // static void pointel2pixel( FreemanChain & aPixChain,
  //     std::vector<unsigned int> & aPl2pix,
  //     std::vector<unsigned int> & aPix2pl,
  //     const FreemanChain & aPlChain )
  f = FreemanChain("000112321233", 0, 0);
  numVector pl2pix, pix2pl;
  FreemanChain pixChain;
  FreemanChain::pointel2pixel( pixChain, pl2pix, pix2pl, f );
  numVector pl2pixExpected;
  pl2pixExpected.push_back( 0 ); pl2pixExpected.push_back( 1 ); pl2pixExpected.push_back( 2 );
  pl2pixExpected.push_back( 2 ); pl2pixExpected.push_back( 3 ); pl2pixExpected.push_back( 3 );
  pl2pixExpected.push_back( 3 ); pl2pixExpected.push_back( 5 ); pl2pixExpected.push_back( 7 );
  pl2pixExpected.push_back( 7 ); pl2pixExpected.push_back( 7 ); pl2pixExpected.push_back( 8 );
  numVector pix2plExpected;
  pix2plExpected.push_back( 0 ); pix2plExpected.push_back( 1 ); pix2plExpected.push_back( 3 );
  pix2plExpected.push_back( 6 ); pix2plExpected.push_back( 7 ); pix2plExpected.push_back( 7 );
  pix2plExpected.push_back( 8 ); pix2plExpected.push_back( 10 );
  test = ( pixChain == FreemanChain("00132213", 0, 0) ) &&
         ( pl2pix == pl2pixExpected ) &&
         ( pix2pl == pix2plExpected );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 7 " << ((test) ? "passed" : "failed" ) << endl;


  //  static void innerContour( FreemanChain & aInnerChain,
  //          std::vector<unsigned int> & aOuter2inner,
  //          std::vector<unsigned int> & aInner2outer,
  //          const FreemanChain & aOuterChain,
  //          bool ccw = true );
  FreemanChain innerChain;
  numVector outer2inner, inner2outer;
  FreemanChain::innerContour ( innerChain, outer2inner, inner2outer, f, true);
  test = ( innerChain == FreemanChain("00132213", 0, 0 ) ) &&
         ( outer2inner == pl2pixExpected ) &&
         ( inner2outer == pix2plExpected );
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 8 " << ((test) ? "passed" : "failed" ) << endl;


  //  static bool cleanOuterSpikes( FreemanChain & aCleanC,
  //        std::vector<unsigned int> & aC2clean,
  //        std::vector<unsigned int> & aClean2c,
  //        const FreemanChain & c,
  //        bool ccw = true );
  FreemanChain c( "0000112312213233", 0, 0 );
  numVector c2clean, clean2c;
  FreemanChain cleanC;
  bool cleaned = FreemanChain::cleanOuterSpikes( cleanC, c2clean, clean2c, c, true );
  FreemanChain cleanCExpected("22233000011231", 3, 2);
  numVector c2cleanExpected;
  c2cleanExpected.push_back( 5 ); c2cleanExpected.push_back( 6 ); c2cleanExpected.push_back( 7 );
  c2cleanExpected.push_back( 8 ); c2cleanExpected.push_back( 9 ); c2cleanExpected.push_back(10 );
  c2cleanExpected.push_back(11 ); c2cleanExpected.push_back(12 ); c2cleanExpected.push_back(13 );
  c2cleanExpected.push_back( 0 ); c2cleanExpected.push_back( 1 ); c2cleanExpected.push_back( 2 );
  c2cleanExpected.push_back( 2 ); c2cleanExpected.push_back( 2 ); c2cleanExpected.push_back( 3 );
  c2cleanExpected.push_back( 4 );
  numVector clean2cExpected;
  clean2cExpected.push_back( 9 ); clean2cExpected.push_back(10 ); clean2cExpected.push_back(13 );
  clean2cExpected.push_back(14 ); clean2cExpected.push_back(15 ); clean2cExpected.push_back( 0 );
  clean2cExpected.push_back( 1 ); clean2cExpected.push_back( 2 ); clean2cExpected.push_back( 3 );
  clean2cExpected.push_back( 4 ); clean2cExpected.push_back( 5 ); clean2cExpected.push_back( 6 );
  clean2cExpected.push_back( 7 ); clean2cExpected.push_back( 8 );
  test = cleaned && (cleanC == cleanCExpected) && (c2clean == c2cleanExpected)
    && (clean2c == clean2cExpected);
  nbOk += (test) ? 1 : 0;
  trace.info() << "Test 9 " << ((test) ? "passed" : "failed" ) << endl;
  trace.info() << "All tests="<<nbOk<<std::endl;
  trace.endBlock();
  return test;
}



/**
 * testDisplay
 *
 */
bool testDisplay()
{
  typedef FreemanChain<int> FreemanChain;
  //typedef FreemanChain::Point Point;
  //typedef FreemanChain::Vector Vector;
  //typedef FreemanChain::ConstIterator Iterator;
  //typedef std::vector<unsigned int> numVector;

  Board2D aBoard;
  aBoard.setUnit(Board::UCentimeter);

  fstream fst;
  fst.open ((testPath + "samples/contourS.fc").c_str() , ios::in);
  FreemanChain fc(fst);

  aBoard.setPenColor(Color::Red);

  //aBoard << DrawPavingPixel();

  aBoard << fc;

  std::string filenameImage = testPath + "samples/contourS.png"; // ! only PNG with Cairo for the moment !
  LibBoard::Image image( 0, 84, 185, 85, filenameImage, 20 );
  image.shiftDepth(500);
  LibBoard::Board & board = aBoard;
  board << image;

  aBoard.saveSVG( "testDisplayFC.svg", Board::BoundingBox, 5000 );
  aBoard.saveEPS( "testDisplayFC.eps", Board::BoundingBox, 5000 );
  aBoard.saveFIG( "testDisplayFC.fig", Board::BoundingBox, 5000 );

#ifdef WITH_CAIRO
  aBoard.saveCairo("testDisplayFC-cairo.pdf", Board2D::CairoPDF, Board::BoundingBox, 5000);
  aBoard.saveCairo("testDisplayFC-cairo.png", Board2D::CairoPNG, Board::BoundingBox, 5000);
  aBoard.saveCairo("testDisplayFC-cairo.ps",  Board2D::CairoPS,  Board::BoundingBox, 5000);
  aBoard.saveCairo("testDisplayFC-cairo.svg", Board2D::CairoSVG, Board::BoundingBox, 5000);
#endif

  return true;
}





///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class FreemanChain" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res =
    testConstructors() &&
    testPublicSercives() &&
    testPointsIterators() &&
    testCodesIterators() &&
    testStaticServices() &&
    testDisplay();

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;

  trace.endBlock();

  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
