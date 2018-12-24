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
//LICENSE-END
/**
 * @file testSegmentation.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 *
 * @date 2011/07/22
 *
 * This file is part of the DGtal library
 */

/**
 * Description of testSegmentation <p>
 * Aim: simple test of \ref GreedySegmentation and \ref SaturatedSegmentation
 */

#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <iterator>




#include "DGtal/base/Common.h"
#include "DGtal/base/Exceptions.h"

#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/Color.h"

#include "DGtal/base/Circulator.h"

#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
#include "DGtal/geometry/curves/FreemanChain.h"
#include "DGtal/geometry/curves/GreedySegmentation.h"
#include "DGtal/geometry/curves/SaturatedSegmentation.h"


#include "ConfigTest.h"


using namespace DGtal;
using namespace std;
using namespace LibBoard;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class GreedySegmentation
///////////////////////////////////////////////////////////////////////////////



/**
 * Drawing a segmentation
 */
template <typename Iterator, typename Board>
void draw(const Iterator& itb, const Iterator& ite, Board& aBoard)
{

  for (Iterator i(itb); i != ite; ++i) {
     
    typename Iterator::SegmentComputer segment(*i); 

    aBoard << SetMode(segment.primitive().className(), "BoundingBox" )
           << segment.primitive(); // draw bounding box
  
  } 

}

/**
 * Drawing a segmentation
 */
template <typename Iterator, typename Board>
void drawCCP(const Iterator& itb, const Iterator& ite, Board& aBoard)
{

  typedef typename Iterator::SegmentComputer::ConstIterator PointIterator; 

  for (Iterator i(itb); i != ite; ++i) {
     
    //choose pen color
    CustomPenColor* aPenColor;

    if ( !(i.intersectNext() && i.intersectPrevious()) ) {

      aPenColor = new CustomPenColor( Color::Black );

    } else {

      //end points

      PointIterator begin = i->begin();  --begin; 
      PointIterator end = i->end();

      //parameters
      int mu = i->mu();
      int omega = i->omega();

      //configurations
      if ( (i->remainder(begin)<=mu-1)&&
           (i->remainder(end)<=mu-1) ) {                //concave
        aPenColor = new CustomPenColor( Color::Green);
      } else if ( (i->remainder(begin)>=mu+omega)&&
            (i->remainder(end)>=mu+omega) ) {           //convex
        aPenColor = new CustomPenColor( Color::Blue );
      } else if ( (i->remainder(begin)>=mu+omega)&&
            (i->remainder(end)<=mu-1) ) {               //convex to concave
        aPenColor = new CustomPenColor( Color::Yellow );
      } else if ( (i->remainder(begin)<=mu-1)&&
            (i->remainder(end)>=mu+omega) ) {           //concave to convex
        aPenColor = new CustomPenColor( Color::Yellow );
      } else {                                                    //pb
        aPenColor = new CustomPenColor( Color::Red );
      }

    }

    // draw each segment
    aBoard << SetMode(i->primitive().className(), "BoundingBox" )
	   << CustomStyle( i->primitive().className(), aPenColor )
           << i->primitive(); 
  
  } 

}

/**
 * Greedy segmentation of a (sub)range
 */
template <typename Iterator, typename Board>
void segmentationIntoDSSs(const Iterator& itb, const Iterator& ite, 
                          const Iterator& sitb, const Iterator& site,
                          const string& aMode, Board& aBoard)
{
  typedef typename IteratorCirculatorTraits<Iterator>::Value::Coordinate Coordinate; 
  typedef ArithmeticalDSSComputer<Iterator,Coordinate,4> RecognitionAlgorithm;
  typedef GreedySegmentation<RecognitionAlgorithm> Segmentation;

  RecognitionAlgorithm algo;
  Segmentation s(itb,ite,algo);
  s.setSubRange(sitb,site);
  s.setMode(aMode);
  
  typename Segmentation::SegmentComputerIterator i = s.begin();
  typename Segmentation::SegmentComputerIterator end = s.end();

  draw<typename Segmentation::SegmentComputerIterator, Board>
  (i,end,aBoard); 

}

/**
 * saturated segmentation of a (sub)range
 */
template <typename Iterator, typename Board>
void segmentationIntoMaximalDSSs(const Iterator& itb, const Iterator& ite, 
                                 const Iterator& sitb, const Iterator& site,
                                 const string& aMode, Board& aBoard)
{
  typedef typename IteratorCirculatorTraits<Iterator>::Value::Coordinate Coordinate; 
  typedef ArithmeticalDSSComputer<Iterator,Coordinate,4> RecognitionAlgorithm;
  typedef SaturatedSegmentation<RecognitionAlgorithm> Segmentation;

  RecognitionAlgorithm algo;
  Segmentation s(itb,ite,algo);
  s.setSubRange(sitb,site);
  s.setMode(aMode);
  
  typename Segmentation::SegmentComputerIterator i = s.begin();
  typename Segmentation::SegmentComputerIterator end = s.end();

  drawCCP<typename Segmentation::SegmentComputerIterator, Board>
  (i,end,aBoard); 

}


/**
 * Simple visual test
 */
bool greedySegmentationVisualTest()
{

  typedef int Coordinate;
  typedef FreemanChain<Coordinate> FC; 
  typedef FreemanChain<Coordinate>::ConstIterator ConstIterator; 



  std::string filename = testPath + "samples/manche.fc";

  std::fstream fst;
  fst.open (filename.c_str(), std::ios::in);
  FC fc(fst);

////////////////////////////////////////////////////////////////////////
// open digital curve

  trace.beginBlock("Segmentation of a whole range (mode1)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 

  segmentationIntoDSSs<ConstIterator,Board2D>
    (fc.begin(),fc.end(),
     fc.begin(),fc.end(),
     "Truncate",aBoard);   

  aBoard.saveEPS("WholeOpenCurveWithItMode1.eps");
}
  trace.endBlock();


  trace.beginBlock("Segmentation of a whole range (mode3)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 

  segmentationIntoDSSs<ConstIterator,Board2D>
    (fc.begin(),fc.end(),
     fc.begin(),fc.end(),
     "DoNotTruncate",aBoard);   

  aBoard.saveEPS("WholeOpenCurveWithItMode3.eps");
}
  trace.endBlock();

  trace.beginBlock("Segmentation of a whole range (mode2)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 

  segmentationIntoDSSs<ConstIterator,Board2D>
    (fc.begin(),fc.end(),
     fc.begin(),fc.end(),
     "Truncate+1",aBoard);   

  aBoard.saveEPS("WholeOpenCurveWithItMode2.eps");
}
  trace.endBlock();


////////////////////////////////////////////////////////////
// subrange

  typedef vector<PointVector<2,Coordinate> > Curve;  
  typedef Curve::const_iterator RAConstIterator;  

  Curve vPts; 
  vPts.assign ( fc.begin(), fc.end() ); 

  RAConstIterator start = vPts.begin()+15;
  RAConstIterator stop = vPts.begin()+200;

trace.info() << *start << " " << *stop << endl;

  trace.beginBlock("Segmentation of a subrange (mode1)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 
  aBoard << SetMode("PointVector", "Paving") << *start << *stop; 

  segmentationIntoDSSs<RAConstIterator,Board2D>
    (vPts.begin(),vPts.end(),
     start,stop,
     "Truncate",aBoard);   

  aBoard.saveEPS("PartOpenCurveWithItMode1.eps");
}
  trace.endBlock();

  trace.beginBlock("Segmentation of a subrange (mode2)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 
  aBoard << SetMode("PointVector", "Paving") << *start << *stop; 

  segmentationIntoDSSs<RAConstIterator,Board2D>
    (vPts.begin(),vPts.end(),
     start,stop,
     "Truncate+1",aBoard);   

  aBoard.saveEPS("PartOpenCurveWithItMode2.eps");
}
  trace.endBlock();


  trace.beginBlock("Segmentation of a subrange (mode3)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 
  aBoard << SetMode("PointVector", "Paving") << *start << *stop; 

  segmentationIntoDSSs<RAConstIterator,Board2D>
    (vPts.begin(),vPts.end(),
     start,stop,
     "DoNotTruncate",aBoard);   

  aBoard.saveEPS("PartOpenCurveWithItMode3.eps");
}
  trace.endBlock();


////////////////////////////////////////////////////////
// using circulators

  typedef Circulator<RAConstIterator> ConstCirculator;
  ConstCirculator c(vPts.begin(),vPts.begin(),vPts.end()); 

  trace.beginBlock("Segmentation of a whole range (mode1) with circulators");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 

  segmentationIntoDSSs<ConstCirculator,Board2D>
    (c,c,c,c,
     "Truncate",aBoard);   

  aBoard.saveEPS("WholeOpenCurveWithCircMode1.eps");
}
  trace.endBlock();

  trace.beginBlock("Segmentation of a whole range (mode2) with circulators");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 

  segmentationIntoDSSs<ConstCirculator,Board2D>
    (c,c,c,c,
     "Truncate+1",aBoard);   

  aBoard.saveEPS("WholeOpenCurveWithCircMode2.eps");
}
  trace.endBlock();


  trace.beginBlock("Segmentation of a whole range (mode3) with circulators");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 

  segmentationIntoDSSs<ConstCirculator,Board2D>
    (c,c,c,c,
     "DoNotTruncate",aBoard);   

  aBoard.saveEPS("WholeOpenCurveWithCircMode3.eps");
}
  trace.endBlock();

///////////////////////////////////////////////////////////////
// subrange with circulators

  ConstCirculator cstart(start,vPts.begin(),vPts.end()); 
  ConstCirculator cstop(stop,vPts.begin(),vPts.end()); 

  trace.beginBlock("Segmentation of a subrange (mode1) with circulators");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 
  aBoard << SetMode("PointVector", "Paving") << *start << *stop; 

  segmentationIntoDSSs<ConstCirculator,Board2D>
    (c,c,
     cstart,cstop,
     "Truncate",aBoard);   

  aBoard.saveEPS("PartOpenCurveWithCircMode1.eps");
}
  trace.endBlock();

  trace.beginBlock("Segmentation of a subrange (mode2) with circulators");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 
  aBoard << SetMode("PointVector", "Paving") << *start << *stop; 

  segmentationIntoDSSs<ConstCirculator,Board2D>
    (c,c,
     cstart,cstop,
     "Truncate+1",aBoard);   

  aBoard.saveEPS("PartOpenCurveWithCircMode2.eps");
}
  trace.endBlock();


  trace.beginBlock("Segmentation of a subrange (mode3) with circulators");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 
  aBoard << SetMode("PointVector", "Paving") << *start << *stop; 

  segmentationIntoDSSs<ConstCirculator,Board2D>
    (c,c,
     cstart,cstop,
     "DoNotTruncate",aBoard);   

  aBoard.saveEPS("PartOpenCurveWithCircMode3.eps");
}
  trace.endBlock();

/////////////////////////////////////////////////////////////
// closed digital curve 

  std::stringstream ss(stringstream::in | stringstream::out);
  ss << "31 16 1112121212121221212121221212212222232232323332333333332333332330333033003030000010001001001000100010101010111" << endl;
  
  // Construct the Freeman chain
  FC fc2(ss);

  Curve vPts2; 
  vPts2.assign( fc2.begin(), fc2.end() ); 
  vPts2.insert( vPts2.end(), fc2.begin(), fc2.end() );
  vPts2.insert( vPts2.end(), fc2.begin(), fc2.end() );

//copy ( vPts2.begin(), vPts2.end(), ostream_iterator<PointVector<2,Coordinate> >(cout,"\n") ) ;

  RAConstIterator start2 = vPts2.begin() + fc2.size()+1; 
  RAConstIterator stop2 = start2 + fc2.size()+1; 

trace.info() << *start2 << " " << *stop2 << endl;

  trace.beginBlock("Segmentation of a subrange of a duplicated range (mode1)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc2; 
  aBoard << SetMode("PointVector", "Paving") << *start2 << *stop2; 

  segmentationIntoDSSs<RAConstIterator,Board2D>
    (vPts2.begin(),vPts2.end(),
     start2,stop2,
     "Truncate",aBoard);   

  aBoard.saveEPS("DuplicatedCurveWithItMode1.eps");
}
  trace.endBlock();

  trace.beginBlock("Segmentation of a subrange of a duplicated range (mode2)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc2; 
  aBoard << SetMode("PointVector", "Paving") << *start2 << *stop2; 

  segmentationIntoDSSs<RAConstIterator,Board2D>
    (vPts2.begin(),vPts2.end(),
     start2,stop2,
     "Truncate+1",aBoard);   

  aBoard.saveEPS("DuplicatedCurveWithItMode2.eps");
}
  trace.endBlock();


  trace.beginBlock("Segmentation of a subrange of a duplicated range (mode3)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc2; 
  aBoard << SetMode("PointVector", "Paving") << *start2 << *stop2; 

  segmentationIntoDSSs<RAConstIterator,Board2D>
    (vPts2.begin(),vPts2.end(),
     start2,stop2,
     "DoNotTruncate",aBoard);   

  aBoard.saveEPS("DuplicatedCurveWithItMode3.eps");
}
  trace.endBlock();


////////////////////////////////////////////////////////
// closed digital curve with circulators

  ConstCirculator c2(start2,start2,stop2); 

  trace.beginBlock("Segmentation of a whole range (mode1) with circulators");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc2; 

  segmentationIntoDSSs<ConstCirculator,Board2D>
    (c2,c2,c2,c2,
     "Truncate",aBoard);   

  aBoard.saveEPS("ClosedCurveWithCircMode1.eps");
}
  trace.endBlock();

  trace.beginBlock("Segmentation of a whole range (mode2) with circulators");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc2; 

  segmentationIntoDSSs<ConstCirculator,Board2D>
    (c2,c2,c2,c2,
     "Truncate+1",aBoard);   

  aBoard.saveEPS("ClosedCurveWithCircMode2.eps");
}
  trace.endBlock();


  trace.beginBlock("Segmentation of a whole range (mode3) with circulators");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc2; 

  segmentationIntoDSSs<ConstCirculator,Board2D>
    (c2,c2,c2,c2,
     "DoNotTruncate",aBoard);   

  aBoard.saveEPS("ClosedCurveWithCircMode3.eps");
}
  trace.endBlock();


////////////////////////////////////////////////////////////
  return true;
}


///////////////////////////////////////////////////////////////////////////////
// Functions for testing class SaturatedSegmentation
///////////////////////////////////////////////////////////////////////////////



/**
 * Simple visual test
 */
bool SaturatedSegmentationVisualTest()
{

  typedef int Coordinate;
  typedef FreemanChain<Coordinate> FC; 
  typedef FreemanChain<Coordinate>::ConstIterator ConstIterator; 

  std::string filename = testPath + "samples/manche.fc";

  std::fstream fst;
  fst.open (filename.c_str(), std::ios::in);
  FC fc(fst);

///////////////////////////////////////////////////////
// whole open curve

  trace.beginBlock("Simple saturated Segmentation (mode=First)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 

  segmentationIntoMaximalDSSs<ConstIterator,Board2D>
    (fc.begin(),fc.end(),
     fc.begin(),fc.end(),
     "First",aBoard);   

  aBoard.saveEPS("MSOpenCurve2.eps");
}
  trace.endBlock();

  trace.beginBlock("Simple saturated Segmentation (mode=MostCentered)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 

  segmentationIntoMaximalDSSs<ConstIterator,Board2D>
    (fc.begin(),fc.end(),
     fc.begin(),fc.end(),
     "MostCentered",aBoard);   

  aBoard.saveEPS("MSOpenCurve3.eps");
}
  trace.endBlock();

  trace.beginBlock("Simple saturated Segmentation (mode=Last)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 

  segmentationIntoMaximalDSSs<ConstIterator,Board2D>
    (fc.begin(),fc.end(),
     fc.begin(),fc.end(),
     "Last",aBoard);   

  aBoard.saveEPS("MSOpenCurve4.eps");
}
  trace.endBlock();

////////////////////////////////////////////////////////////
// subrange

  typedef vector<PointVector<2,Coordinate> > Curve;  
  typedef Curve::const_iterator RAConstIterator;  

  Curve vPts; 
  vPts.assign ( fc.begin(), fc.end() ); 

  RAConstIterator start = vPts.begin()+190;
  RAConstIterator stop = vPts.begin()+400;

trace.info() << *start << " " << *stop << endl;


  trace.beginBlock("saturated Segmentation of a subrange (mode=First)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 
  aBoard << SetMode("PointVector", "Paving") << *start << *stop; 

  segmentationIntoMaximalDSSs<RAConstIterator,Board2D>
    (vPts.begin(),vPts.end(),
     start,stop,
     "First",aBoard);   

  aBoard.saveEPS("MSOpenCurvePart2.eps");
}
  trace.endBlock();

  trace.beginBlock("saturated Segmentation of a subrange (mode=MostCentered)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 
  aBoard << SetMode("PointVector", "Paving") << *start << *stop; 

  segmentationIntoMaximalDSSs<RAConstIterator,Board2D>
    (vPts.begin(),vPts.end(),
     start,stop,
     "MostCentered",aBoard);   

  aBoard.saveEPS("MSOpenCurvePart3.eps");
}
  trace.endBlock();

  trace.beginBlock("saturated Segmentation of a subrange (mode=Last)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 
  aBoard << SetMode("PointVector", "Paving") << *start << *stop; 

  segmentationIntoMaximalDSSs<RAConstIterator,Board2D>
    (vPts.begin(),vPts.end(),
     start,stop,
     "Last",aBoard);   

  aBoard.saveEPS("MSOpenCurvePart4.eps");
}
  trace.endBlock();


////////////////////////////////////////////////////////
// using circulators

  typedef Circulator<RAConstIterator> ConstCirculator;
  ConstCirculator c(vPts.begin(),vPts.begin(),vPts.end()); 


  trace.beginBlock("Segmentation of a range bounded by circulators (mode=First)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 

  segmentationIntoMaximalDSSs<ConstCirculator,Board2D>
    (c,c,c,c,
     "First",aBoard);   

  aBoard.saveEPS("MSOpenCurveWithCirc2.eps");
}
  trace.endBlock();

  trace.beginBlock("Segmentation of a range bounded by circulators (mode=MostCentered)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 

  segmentationIntoMaximalDSSs<ConstCirculator,Board2D>
    (c,c,c,c,
     "MostCentered",aBoard);   

  aBoard.saveEPS("MSOpenCurveWithCirc3.eps");
}
  trace.endBlock();

  trace.beginBlock("Segmentation of a range bounded by circulators (mode=Last)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 

  segmentationIntoMaximalDSSs<ConstCirculator,Board2D>
    (c,c,c,c,
     "Last",aBoard);   

  aBoard.saveEPS("MSOpenCurveWithCirc4.eps");
}
  trace.endBlock();


///////////////////////////////////////////////////////////////
// subrange with circulators

  ConstCirculator cstart(start,vPts.begin(),vPts.end()); 
  ConstCirculator cstop(stop,vPts.begin(),vPts.end()); 


  trace.beginBlock("Segmentation of a subrange with circulators (mode=First)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 
  aBoard << SetMode("PointVector", "Paving") << *cstart << *cstop; 

  segmentationIntoMaximalDSSs<ConstCirculator,Board2D>
    (c,c,cstart,cstop,
     "First",aBoard);   

  aBoard.saveEPS("MSOpenCurvePartWithCirc2.eps");
}
  trace.endBlock();

  trace.beginBlock("Segmentation of a subrange with circulators (mode=MostCentered)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 
  aBoard << SetMode("PointVector", "Paving") << *cstart << *cstop; 

  segmentationIntoMaximalDSSs<ConstCirculator,Board2D>
    (c,c,cstart,cstop,
     "MostCentered",aBoard);   

  aBoard.saveEPS("MSOpenCurvePartWithCirc3.eps");
}
  trace.endBlock();

  trace.beginBlock("Segmentation of a subrange with circulators (mode=Last)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc; 
  aBoard << SetMode("PointVector", "Paving") << *cstart << *cstop; 

  segmentationIntoMaximalDSSs<ConstCirculator,Board2D>
    (c,c,cstart,cstop,
     "Last",aBoard);   

  aBoard.saveEPS("MSOpenCurvePartWithCirc4.eps");
}
  trace.endBlock();

/////////////////////////////////////////////////////////////
// closed digital curve with circulators

  std::stringstream ss(stringstream::in | stringstream::out);
  ss << "31 16 1112121212121221212121221212212222232232323332333333332333332330333033003030000010001001001000100010101010111" << endl;
  
  // Construct the Freeman chain
  FC fc2(ss);

  Curve vPts2; 
  vPts2.assign( fc2.begin(), fc2.end() ); 
  vPts2.insert( vPts2.end(), fc2.begin(), fc2.end() );
  vPts2.insert( vPts2.end(), fc2.begin(), fc2.end() );

  RAConstIterator start2 = vPts2.begin() + fc2.size()+1; 
  RAConstIterator stop2 = start2 + fc2.size()+1; 

  trace.info() << *start2 << " " << *stop2 << endl;

  trace.beginBlock("Satured Segmentation of a duplicated range (mode2)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc2; 
  aBoard << SetMode("PointVector", "Paving") << *start2 << *stop2; 

  segmentationIntoMaximalDSSs<RAConstIterator,Board2D>
    (vPts2.begin(),vPts2.end(),
     start2,stop2,
     "First",aBoard);   

  aBoard.saveEPS("MSClosedCurveWithIt2.eps");
}
  trace.endBlock();

  trace.beginBlock("Satured Segmentation of a duplicated range (mode3)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc2; 
  aBoard << SetMode("PointVector", "Paving") << *start2 << *stop2; 

  segmentationIntoMaximalDSSs<RAConstIterator,Board2D>
    (vPts2.begin(),vPts2.end(),
     start2,stop2,
     "MostCentered",aBoard);   

  aBoard.saveEPS("MSClosedCurveWithIt3.eps");
}
  trace.endBlock();


  trace.beginBlock("Satured Segmentation of a duplicated range (mode4)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc2; 
  aBoard << SetMode("PointVector", "Paving") << *start2 << *stop2; 

  segmentationIntoMaximalDSSs<RAConstIterator,Board2D>
    (vPts2.begin(),vPts2.end(),
     start2,stop2,
     "Last",aBoard);   

  aBoard.saveEPS("MSClosedCurveWithIt4.eps");
}
  trace.endBlock();


/////////////////////////////////////////////////////////////////
////////// closed digital curve with circulators

  Curve vPts3; 
  vPts3.assign( fc2.begin(), fc2.end() ); 

  ConstCirculator c2(vPts3.begin(),vPts3.begin(),vPts3.end()); 

  trace.beginBlock("saturated Segmentation of a closed digital curve (mode=First)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc2; 
  aBoard << SetMode("PointVector", "Paving") << *c2; 

  segmentationIntoMaximalDSSs<ConstCirculator,Board2D>
    (c2,c2,c2,c2,
     "First",aBoard);   

  aBoard.saveEPS("MSClosedCurveWithCirc2.eps");
}
  trace.endBlock();

  trace.beginBlock("saturated Segmentation of a closed digital curve (mode=MostCentered)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc2; 
  aBoard << SetMode("PointVector", "Paving") << *c2; 

  segmentationIntoMaximalDSSs<ConstCirculator,Board2D>
    (c2,c2,c2,c2,
     "MostCentered",aBoard);   

  aBoard.saveEPS("MSClosedCurveWithCirc3.eps");
}
  trace.endBlock();

  trace.beginBlock("saturated Segmentation of a closed digital curve (mode=Last)");
{
  Board2D aBoard;
  aBoard << SetMode("PointVector", "Grid") << fc2; 
  aBoard << SetMode("PointVector", "Paving") << *c2; 

  segmentationIntoMaximalDSSs<ConstCirculator,Board2D>
    (c2,c2,c2,c2,
     "Last",aBoard);   

  aBoard.saveEPS("MSClosedCurveWithCirc4.eps");
}
  trace.endBlock();

///////////////////////////////////////////////////////////

  return true; 

}


/**
 * Simple visual test
 */
bool SaturatedSegmentationTest()
{

  typedef int Coordinate;
  typedef FreemanChain<Coordinate> FC; 

  std::string filename = testPath + "samples/BigBall2.fc";

  std::fstream fst;
  fst.open (filename.c_str(), std::ios::in);
  FC fc(fst);

  typedef PointVector<2,Coordinate> Point; 

  vector<Point> vPts; 
  vPts.assign(fc.begin(),fc.end()); 
 
  typedef vector<Point>::const_iterator ConstIterator; 
  typedef Circulator<ConstIterator> ConstCirculator; 

  Circulator<ConstIterator> c(vPts.begin(), vPts.begin(), vPts.end() ); 

  typedef ArithmeticalDSSComputer<ConstCirculator,Coordinate,4> RecognitionAlgorithm;
  typedef SaturatedSegmentation<RecognitionAlgorithm> Segmentation;

  trace.beginBlock("saturated Segmentation");
  trace.info() << filename << endl;

  RecognitionAlgorithm algo;
  Segmentation s(c,c,algo);
  s.setMode("First"); 
  
  Segmentation::SegmentComputerIterator begin = s.begin();
  Segmentation::SegmentComputerIterator end = s.end();

  unsigned int compteur = 0; 
  for (Segmentation::SegmentComputerIterator i(begin); i != end; ++i) {
    ++compteur; 
  } 

  trace.info() << "# nbpts nbsegments " << endl;
  trace.info() << fc.size()+1 << " " << compteur << endl;

  trace.endBlock();

  return (compteur == 4295);
}

/////////////////////////////////////////////////////////////////////////
//////////////// MAIN ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
  
  trace.beginBlock ( "Testing class GreedyDecomposition and SaturatedSegmentation" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = greedySegmentationVisualTest()
&& SaturatedSegmentationVisualTest()
&& SaturatedSegmentationTest()
;

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();

  return res ? 0 : 1;

}
