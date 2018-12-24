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
 * @file testGridCurve.cpp
 * @author Tristan Roussillon (\c
 * tristan.roussillon@liris.cnrs.fr ) Laboratoire d'InfoRmatique en
 * Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS,
 * France
 *
 *
 * @date 2011/06/27

 * Functions for testing class GridCurve
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

#include "DGtal/base/Common.h"

#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/geometry/curves/GridCurve.h"

#include "DGtal/io/boards/Board2D.h"

#include "DGtal/io/boards/CDrawableWithBoard2D.h"

#include "ConfigTest.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class FreemanChain.
///////////////////////////////////////////////////////////////////////////////

/**
 * IO Tests
 *
 */
template <typename KSpace>
bool testIOGridCurve(const string& filename)
{

  unsigned int d = KSpace::Point::dimension;
  GridCurve<KSpace> c; //grid curve

//////////////////////////////////////////
  trace.info() << endl;
  trace.info() << "Reading GridCurve d=" << d << " "; 
  
  ifstream instream; // input stream
  instream.open (filename.c_str(), ifstream::in);

  c.initFromVectorStream(instream);

  trace.info() << "(" << c.size() << ") elts" << std::endl; 
  trace.info() << c << endl;

///////////////////////////////////////////
  std::stringstream s; 
  s << "gridcurve" << d << ".dat"; 

  trace.info() << "Writing GridCurve d=" << d << " in " << s.str() << endl;

  ofstream outstream(s.str().c_str()); //output stream
  if (!outstream.is_open()) return false;
  else {
    c.writeVectorToStream(outstream);
  }
  outstream.close();

  return true;
}


/**
 * Open/Closed
 *
 */
bool testIsOpen(const string &filename, const bool& aFlag)
{

  trace.info() << endl;
  trace.info() << "Open/Closed test" << endl;

  GridCurve<KhalimskySpaceND<2> > c; //grid curve

  ifstream instream; // input stream
  instream.open (filename.c_str(), ifstream::in);
  c.initFromVectorStream(instream);

  trace.info() << c.isOpen() << " == " << aFlag << endl;

  return (c.isOpen() == aFlag);
}

/**
 * Exceptions
 *
 */
bool testExceptions(const string &filename)
{

  GridCurve<KhalimskySpaceND<2> > c; //grid curve

  trace.info() << endl;
  trace.info() << "Trying to read bad file: " << filename << endl;
  
  ifstream instream; // input stream
  instream.open (filename.c_str(), ifstream::in);

  try {
    c.initFromVectorStream(instream);
    trace.info() << "no exception catched!?" << endl;
    return false;
  }  catch (DGtal::ConnectivityException& e) {
    trace.info() << e.what() << endl;
    return true;
  } catch (DGtal::InputException& e) {
    trace.info() << e.what() << endl;
    return true;
  } catch (exception& e) {
    trace.info() << e.what() << endl;
    return true;
  } 
}

/**
 * Display
 *
 */
bool testDrawGridCurve(const string &filename)
{

  GridCurve<KhalimskySpaceND<2> > c; //grid curve

  trace.info() << endl;
  trace.info() << "Displaying GridCurve " << endl;
  
  //reading grid curve
  fstream inputStream;
  inputStream.open (filename.c_str(), ios::in);
  c.initFromVectorStream(inputStream); 
  inputStream.close();

  //displaying it
  Board2D aBoard;
  aBoard.setUnit(Board2D::UCentimeter);
  aBoard << c; 
  aBoard.saveEPS( "GridCurve.eps", Board2D::BoundingBox, 5000 );
#ifdef WITH_CAIRO
  aBoard.saveCairo("GridCurve-cairo.pdf", Board2D::CairoPDF, Board2D::BoundingBox, 5000);
#endif

  return true;
}


/**
 * Ranges
 *
 */
template <typename Range>
bool testRange(const Range &aRange)
{

  trace.info() << endl;
  trace.info() << "Testing Range" << endl;
  
  typedef typename IteratorCirculatorTraits<typename Range::ConstIterator>::Value Value; 
  std::vector<Value> v1,v2,v3,v4; 
  
{
  trace.info() << "Forward" << endl;
  typename Range::ConstIterator i = aRange.begin();
  typename Range::ConstIterator end = aRange.end();
  for ( ; i != end; ++i) {
    //cout << *i << endl;
    v1.push_back(*i); 
  }
}
{
  trace.info() << "Backward" << endl;
  typename Range::ConstReverseIterator i = aRange.rbegin();
  typename Range::ConstReverseIterator end = aRange.rend();
  for ( ; i != end; ++i) {
    //cout << *i << endl;
    v2.push_back(*i); 
  }
}
{
  trace.info() << "Circulator" << endl;
  typename Range::ConstCirculator c = aRange.c();
  typename Range::ConstCirculator cend = aRange.c();
  if (isNotEmpty(c,cend)) 
  {
    do 
    {
      //cout << *c << endl;
      v3.push_back(*c);
      c++;
    } while (c!=cend); 
  }
}

{
  trace.info() << "Reverse Circulator" << endl;
  typename Range::ConstReverseCirculator c = aRange.rc();
  ++c; 
  typename Range::ConstReverseCirculator cend = c;
  if (isNotEmpty(c,cend)) 
  {
    do 
    {
      //cout << *c << endl;
      v4.push_back(*c);
      c++;
    } while (c!=cend); 
  }
}

  return ( std::equal(v1.begin(),v1.end(),v3.begin())
          && std::equal(v2.begin(),v2.end(),v4.begin())
          && std::equal(v1.begin(),v1.end(),v2.rbegin())
          && std::equal(v3.begin(),v3.end(),v4.rbegin()) );
}

template <typename Range>
bool testPairsRange(const Range &aRange)
{

  trace.info() << endl;
  trace.info() << "Testing Range" << endl;
  
{
  trace.info() << "Forward" << endl;
  typename Range::ConstIterator i = aRange.begin();
  typename Range::ConstIterator end = aRange.end();
  for ( ; i != end; ++i) {
    cout << (*i).first << " " << (*i).second << endl;
  }
}
{
  trace.info() << "Backward" << endl;
  typename Range::ConstReverseIterator i = aRange.rbegin();
  typename Range::ConstReverseIterator end = aRange.rend();
  for ( ; i != end; ++i) {
    cout << i->first << " " << i->second << endl;
  }
}
 
  return true;
}

template <typename Range>
bool testDisplayRange(const Range &aRange)
{

  trace.info() << endl;
  trace.info() << "Displaying Range" << endl;
  trace.info() << aRange << endl;
  
  return true;
}

template <typename Range>
bool testDrawRange(const Range &aRange, const string &aName, const string& aDomainMode)
{

  std::stringstream s; 
  s << aName << "Range.eps"; 
  
  trace.info() << endl;
  trace.info() << "Drawing " << s.str() << " " << endl;
  
  //board
  Board2D aBoard;
  aBoard.setUnit(Board2D::UCentimeter);
  //displaying domain
  PointVector<2,int> low(-1,-1);
  PointVector<2,int> up(3,3);
  if (aDomainMode == "Paving") up = PointVector<2,int>(4,4);
  HyperRectDomain< SpaceND<2,int> > aDomain( low,up );
  aBoard << SetMode(aDomain.className(), aDomainMode) << aDomain; 
  //displaying range
  aBoard << aRange; 
  //save
  aBoard.saveEPS( s.str().c_str(), Board2D::BoundingBox, 5000 );
  
  return true;
}

template <typename Range>
void testRangeConceptChecking()
{
    BOOST_CONCEPT_ASSERT(( concepts::CDrawableWithBoard2D<Range> ));
    BOOST_CONCEPT_ASSERT(( concepts::CConstBidirectionalRange<Range> ));
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class GridCurve" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;


  std::string sinus2D4 = testPath + "samples/sinus2D4.dat";
  std::string polyg2D = testPath + "samples/polyg2D.dat";
  std::string sinus3D = testPath + "samples/sinus3D.dat";
  std::string emptyFile = testPath + "samples/emptyFile.dat";
  std::string square = testPath + "samples/smallSquare.dat";

  typedef KhalimskySpaceND<2> K2;
  typedef KhalimskySpaceND<3> K3;

/////////// ranges test
  typedef GridCurve<K2> GridCurve;

testRangeConceptChecking<GridCurve::SCellsRange>();
testRangeConceptChecking<GridCurve::PointsRange>();
testRangeConceptChecking<GridCurve::MidPointsRange>();
testRangeConceptChecking<GridCurve::ArrowsRange>();
testRangeConceptChecking<GridCurve::InnerPointsRange>();
testRangeConceptChecking<GridCurve::OuterPointsRange>();
testRangeConceptChecking<GridCurve::IncidentPointsRange>();

///////// general tests
  bool res = testIOGridCurve<K2>(sinus2D4)
    && testIOGridCurve<K3>(sinus3D)
    && testExceptions(sinus3D)
    && testExceptions(polyg2D)
    && testExceptions(emptyFile)
    && testDrawGridCurve(sinus2D4)
    && testIsOpen(sinus2D4,true)
    && testIsOpen(square,false); 


  //reading grid curve
  GridCurve c; 
  fstream inputStream;
  inputStream.open (square.c_str(), ios::in);
  c.initFromVectorStream(inputStream);
  inputStream.close();

  res = res 
    && testRange<GridCurve::SCellsRange>(c.getSCellsRange())
    && testRange<GridCurve::PointsRange>(c.getPointsRange())
    && testRange<GridCurve::MidPointsRange>(c.getMidPointsRange())
    && testPairsRange<GridCurve::ArrowsRange>(c.getArrowsRange())
    && testRange<GridCurve::InnerPointsRange>(c.getInnerPointsRange())
    && testRange<GridCurve::OuterPointsRange>(c.getOuterPointsRange())
    && testPairsRange<GridCurve::IncidentPointsRange>(c.getIncidentPointsRange())
    && testRange<GridCurve::CodesRange>(c.getCodesRange())
;

  res = res 
    && testDisplayRange<GridCurve::SCellsRange>(c.getSCellsRange())
    && testDisplayRange<GridCurve::PointsRange>(c.getPointsRange())
    && testDisplayRange<GridCurve::MidPointsRange>(c.getMidPointsRange())
    && testDisplayRange<GridCurve::ArrowsRange>(c.getArrowsRange())
    && testDisplayRange<GridCurve::InnerPointsRange>(c.getInnerPointsRange())
    && testDisplayRange<GridCurve::OuterPointsRange>(c.getOuterPointsRange())
    && testDisplayRange<GridCurve::IncidentPointsRange>(c.getIncidentPointsRange())
    && testDisplayRange<GridCurve::CodesRange>(c.getCodesRange())
;

  res = res 
    && testDrawRange<GridCurve::SCellsRange>(c.getSCellsRange(),"1cells","Grid")
    && testDrawRange<GridCurve::PointsRange>(c.getPointsRange(),"Points","Paving")
    && testDrawRange<GridCurve::MidPointsRange>(c.getMidPointsRange(),"MidPoints","Paving")
    && testDrawRange<GridCurve::ArrowsRange>(c.getArrowsRange(),"Arrows","Paving")
    && testDrawRange<GridCurve::InnerPointsRange>(c.getInnerPointsRange(),"InnerPoints","Grid")
    && testDrawRange<GridCurve::OuterPointsRange>(c.getOuterPointsRange(),"OuterPoints","Grid")
    && testDrawRange<GridCurve::IncidentPointsRange>(c.getIncidentPointsRange(),"IncidentPoints","Grid")
;

//////////////////////

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
