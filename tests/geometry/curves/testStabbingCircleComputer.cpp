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
 * @file testStabbingCircleComputer.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/09/26
 *
 * @brief Functions for testing class StabbingCircleComputer.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

//space / domain
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/topology/KhalimskySpaceND.h"

//shape and digitizer
#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/geometry/curves/GridCurve.h"

//Segment computer and DCA
#include "DGtal/geometry/curves/CBidirectionalSegmentComputer.h"

#include "DGtal/geometry/curves/StabbingCircleComputer.h"

#include "DGtal/geometry/curves/SegmentComputerUtils.h"
#include "DGtal/geometry/curves/GreedySegmentation.h"
#include "DGtal/geometry/curves/SaturatedSegmentation.h"

//boards
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/boards/CDrawableWithBoard2D.h"

#include "ConfigTest.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

//////////////////////////////////////////////////////////////////////////////
// digital circle generator
template<typename TKSpace>
GridCurve<TKSpace>
ballGenerator(double aCx, double aCy, double aR, bool aFlagIsCW)
{

  // Types
  typedef TKSpace KSpace;  
  typedef typename KSpace::SCell SCell;
  typedef GridCurve<KSpace> GridCurve; 
  typedef typename KSpace::Space Space;  
  typedef Ball2D<Space> Shape;
  typedef typename Space::Point Point;
  typedef typename Space::RealPoint RealPoint;
  typedef HyperRectDomain<Space> Domain;

  //Forme
  Shape aShape(Point(aCx,aCy), aR);

  // Window for the estimation
  RealPoint xLow ( -aR-1, -aR-1 );
  RealPoint xUp( aR+1, aR+1 );
  GaussDigitizer<Space,Shape> dig;  
  dig.attach( aShape ); // attaches the shape.
  dig.init( xLow, xUp, 1 ); 
  Domain domain = dig.getDomain();
  // Create cellular space
  KSpace K;
  bool ok = K.init( dig.getLowerBound(), dig.getUpperBound(), true );
  if ( ! ok )
  {
      std::cerr << " "
    << " error in creating KSpace." << std::endl;
      return GridCurve();
  }
  try 
  {

    // Extracts shape boundary
    SurfelAdjacency<KSpace::dimension> SAdj( true );
    SCell bel = Surfaces<KSpace>::findABel( K, dig, 10000 );
    // Getting the consecutive surfels of the 2D boundary
    std::vector<Point> points, points2;
    Surfaces<KSpace>::track2DBoundaryPoints( points, K, SAdj, dig, bel );
    //counter-clockwise oriented by default
    GridCurve c; 
    if (aFlagIsCW)
    {
      points2.assign( points.rbegin(), points.rend() );
      c.initFromVector(points2); 
    } 
    else 
    {
      c.initFromVector(points); 
    }
    return c;
  }
  catch ( InputException e )
  {
      std::cerr << " "
    << " error in finding a bel." << std::endl;
      return GridCurve();
  }
}

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class StabbingCircleComputer.
///////////////////////////////////////////////////////////////////////////////

void testStabbingCircleComputerConceptChecking()
{
   typedef std::pair<PointVector<2,int>, PointVector<2,int> > Pair; 
   typedef std::vector<Pair>::const_iterator ConstIterator; 
   typedef StabbingCircleComputer<ConstIterator> GeomDSS; 
   BOOST_CONCEPT_ASSERT(( concepts::CDrawableWithBoard2D<GeomDSS> ));
   BOOST_CONCEPT_ASSERT(( concepts::CBidirectionalSegmentComputer<GeomDSS> ));
}

/*
* simple drawing
*/
template <typename TCurve>
bool drawingTestStabbingCircleComputer(const TCurve& curve, const string& suffix)
{

  typedef typename TCurve::IncidentPointsRange Range; //range
  Range r = curve.getIncidentPointsRange(); //range

  {
    typedef typename Range::ConstIterator ConstIterator; //iterator
    StabbingCircleComputer<ConstIterator> s;
    longestSegment(s,r.begin(),r.end()); 

    Board2D board; 
    board << r << s; 
    std::stringstream ss; 
    ss << "StabbingCircleComputerDrawingTest" << suffix << ".eps"; 
    board.saveEPS(ss.str().c_str()); 
  }

  {
    typedef typename Range::ConstReverseIterator ConstReverseIterator; //iterator
    StabbingCircleComputer<ConstReverseIterator> s;
    longestSegment(s,r.rbegin(),r.rend()); 

    Board2D board;
    board << r << s;       
    std::stringstream ss; 
    ss << "StabbingCircleComputerDrawingTest" << suffix << "2.eps"; 
    board.saveEPS(ss.str().c_str()); 
  }
    
  return true; 
}

/**
 * Basic methods
 */
template <typename TCurve>
bool testStabbingCircleComputer(const TCurve& curve)
{

  typedef typename TCurve::IncidentPointsRange Range; //range
  typedef typename Range::ConstIterator ConstIterator; //iterator
  typedef typename Range::ConstReverseIterator ConstReverseIterator; //reverse iterator

  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Constructors, copy, assignement" );
  {
    Range r = curve.getIncidentPointsRange(); //range

    StabbingCircleComputer<ConstIterator> s1, s2, s3;
    longestSegment(s2, r.begin(), r.end()); 
    longestSegment(s3, r.begin()+1, r.end()); 
    StabbingCircleComputer<ConstIterator> s4(s2); 
    StabbingCircleComputer<ConstIterator> s5(s3);
    s3 = s1; 
    
    trace.info() << s1.isValid() << s1 << endl; 
    trace.info() << s2.isValid() << s2 << endl; 
    trace.info() << s3.isValid() << s3 << endl; 
    trace.info() << s4.isValid() << s4 << endl; 
    trace.info() << s5.isValid() << s5 << endl; 

    bool myFlag = (!s1.isValid())&&(!s3.isValid())
    &&(s2.isValid())&&(s4.isValid())&&(s5.isValid())
    &&(s2 == s4)&&(s2 != s5)&&(s2 != s1)
    &&(s3 != s5)&&(s1 == s3);

    nbok += myFlag ? 1 : 0; 
    nb++;
  }
  trace.endBlock();
    
  
  trace.beginBlock ( "Extension operations" );
  {
    Range r = curve.getIncidentPointsRange(); //range

    StabbingCircleComputer<ConstIterator> s, t;

    trace.info() << "forward extension " << endl; 
    
    ConstIterator itBegin (r.begin()); 
    ConstIterator itEnd (r.end()); 

    s.init( itBegin );
    while ( (s.end() != itEnd) && (s.isExtendableFront()) && (s.extendFront()) ) {}
    trace.info() << s << endl; 

    ConstIterator itLast (s.end()); --itLast;
      
    t.init( itLast ); 
    while ( (t.begin() != itBegin) && (t.extendBack()) ) {}
    trace.info() << t << endl; 
    
    trace.info() << "backward extension " << endl; 
      
    typename StabbingCircleComputer<ConstIterator>::Reverse rs = s.getReverse(); 
    ConstReverseIterator ritBegin ( s.end() ); 
    ConstReverseIterator ritEnd ( itBegin ); 
      
    rs.init( ritBegin );
    while ( (rs.end() != ritEnd) && (rs.isExtendableFront()) && (rs.extendFront()) ) {}
    trace.info() << rs << endl; 
    
    ConstReverseIterator ritLast (rs.end()); --ritLast;
      
    typename StabbingCircleComputer<ConstIterator>::Reverse rt = t.getReverse(); 
    rt.init( ritLast ); 
    while ( (rt.begin() != ritBegin) && (rt.extendBack()) ) {}
    trace.info() << rt << endl; 
    
    trace.info() << "comparison... " << endl; 
    bool myFlag = (s == t)
                      &&(rs == rt); 

    nbok += myFlag ? 1 : 0; 
    nb++;
  }
  trace.endBlock();

  trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  return nbok == nb;
}

/**
 * Recogition of randomly generated digital circles
 */
bool testRecognition()
{

  typedef KhalimskySpaceND<2,int> KSpace; 
  GridCurve<KSpace> c; 
  
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Recognition" );
  
  for (unsigned int i = 0; i < 50; ++i)
  {
    //generate digital circle
    double cx = (rand()%100 ) / 100.0;
    double cy = (rand()%100 ) / 100.0;
    double radius = (rand()%100 )+100;
    c = ballGenerator<KSpace>( cx, cy, radius, ((i%2)==1) ); 
    trace.info() << " #ball #" << i << " c(" << cx << "," << cy << ") r=" << radius << endl; 
    
    //range
    typedef GridCurve<KSpace>::IncidentPointsRange Range; 
    Range r = c.getIncidentPointsRange();
    
    //recognition
    typedef Range::ConstIterator ConstIterator; //iterator
    StabbingCircleComputer<ConstIterator> s;
    longestSegment(s,r.begin(),r.end()); 

    //checking if the circle is separating
    bool flag = true;
    typedef CircleFrom3Points<KSpace::Point> Circle; 
    typedef functors::Point2ShapePredicate<Circle,false,true> 
      FirstInCirclePred; 
    typedef functors::Point2ShapePredicate<Circle,true,true> 
      SecondInCirclePred; 
    for (ConstIterator it = s.begin(); ((it != s.end()) && flag) ; ++it)
    {
      FirstInCirclePred p1( s.getSeparatingCircle() ); 
      SecondInCirclePred p2( s.getSeparatingCircle() ); 
      flag = ( p1(it->first)&&p2(it->second) ); 
    }
    
    //conclusion
    nbok += flag ? 1 : 0; 
    nb++;
  }

  trace.endBlock();
  
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  return nbok == nb;
}

/**
 * Segmentations
 */
template <typename TCurve>
bool testSegmentation(const TCurve& curve)
{

  typedef typename TCurve::IncidentPointsRange Range; //range
  Range r = curve.getIncidentPointsRange(); //range
  
  typedef typename Range::ConstIterator ConstIterator; //iterator
  typedef StabbingCircleComputer<ConstIterator> SegmentComputer; //segment computer
  
  unsigned int nbok = 0;
  unsigned int nb = 0;  

  trace.beginBlock ( "Greedy segmentation" );
  {
    typedef GreedySegmentation<SegmentComputer> Segmentation;
    Segmentation theSegmentation( r.begin(), r.end(), SegmentComputer() );
    
    Board2D board; 
    board << r; 
      
    typename Segmentation::SegmentComputerIterator it = theSegmentation.begin();
    typename Segmentation::SegmentComputerIterator itEnd = theSegmentation.end();
    unsigned int n = 0; 
    unsigned int suml = 0; 
    for ( ; it != itEnd; ++it, ++n) {
      board << SetMode(SegmentComputer().className(), "Sector")
                << (*it); 
      for (ConstIterator i = it->begin(); i != it->end(); ++i)
        suml += 1; 
    }
    
    board.saveSVG("StabbingCircleComputerGreedySegmentationTest.svg", Board2D::BoundingBox, 5000 ); 

    trace.info() << r.size() << ";" << n << ";" << suml << endl;
    //comparison with the results given by another program
    bool flag = ((r.size()==85)&&(n==6)&&(suml==90)&&((r.size()+n-1)==suml)); 
    nbok += flag ? 1 : 0; 
    nb++;
  }
  trace.endBlock();

  trace.beginBlock ( "Saturated segmentation" );
  {
    typedef SaturatedSegmentation<SegmentComputer> Segmentation;
    Segmentation theSegmentation( r.begin(), r.end(), SegmentComputer() );
    theSegmentation.setMode("Last"); 
    
    Board2D board; 
    board << curve; 
    
    typename Segmentation::SegmentComputerIterator it = theSegmentation.begin();
    typename Segmentation::SegmentComputerIterator itEnd = theSegmentation.end();
    unsigned int n = 0; 
    unsigned int suml = 0; 
    for ( ; it != itEnd; ++it, ++n) {
      board << SetMode(SegmentComputer().className(), "Annulus")
                << (*it); 
      for (ConstIterator i = it->begin(); i != it->end(); ++i)
        suml += 1; 
    }
    
    board.saveSVG("StabbingCircleComputerSaturatedSegmentationTest.svg", Board2D::BoundingBox, 5000 ); 

    trace.info() << r.size() << ";" << n << ";" << suml << endl;
    //comparison with the results given by another program
    nbok += ((r.size()==85)&&(n==20)&&(suml==326)) ? 1 : 0; 
    nb++;
  }
  trace.endBlock();
  
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  return (nbok == nb);
}
///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class StabbingCircleComputer" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res; 
  
  {//concept checking
    testStabbingCircleComputerConceptChecking();
  }
  
  {//basic operations
    typedef KhalimskySpaceND<2,int> KSpace; 

    GridCurve<KSpace> c, rc; 
    c = ballGenerator<KSpace>(0,0,6,false); 
    std::vector<PointVector<2,int> > rv; 
    rc = ballGenerator<KSpace>(0,0,6,true); 

    res = testStabbingCircleComputer(c)
  && drawingTestStabbingCircleComputer(c, "CCW")
  && drawingTestStabbingCircleComputer(rc, "CW"); 
  }
  
  {//recognition 
    res = res && testRecognition();
  }
  
  {//segmentations
    std::string filename = testPath + "samples/sinus2D4.dat";
    ifstream instream; // input stream
    instream.open (filename.c_str(), ifstream::in);
    
    typedef KhalimskySpaceND<2,int> KSpace; 
    GridCurve<KSpace> c; //grid curve
    c.initFromVectorStream(instream);
    
    res = res && testSegmentation(c); 
  }
  
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
