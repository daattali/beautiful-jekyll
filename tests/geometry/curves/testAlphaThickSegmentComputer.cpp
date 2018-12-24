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
 * @file testAlphaThickSegmentComputer.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2015/01/07
 *
 * Functions for testing class AlphaThickSegmentComputer.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/curves/AlphaThickSegmentComputer.h"
#include "DGtal/io/readers/PointListReader.h"
#include "DGtal/io/boards/Board2D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class AlphaThickSegmentComputer.
///////////////////////////////////////////////////////////////////////////////

/**
 * Test the convexhull and box of a the alpha-thick segment computer.
 */
bool testAlphaThickSegmentConvexHullAndBox()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  Board2D aBoard;
  typedef  AlphaThickSegmentComputer< Z2i::Point > AlphaThickSegmentComputer2D;
  trace.beginBlock ( "Testing convexhull and boxes of alpha-thick segment on noisy discrete contour." );
  std::vector<Z2i::Point> aContour;
  std::string fileContour = testPath + "samples/contourNoiseSample.sdp";
  aContour = PointListReader<Z2i::Point>::getPointsFromFile(fileContour);
  bool res = true;
  AlphaThickSegmentComputer2D anAlphaThickSegmentComputer(5);
  anAlphaThickSegmentComputer.init(aContour.begin());
  AlphaThickSegmentComputer2D anAlphaThickSegmentComputer2(10);
  anAlphaThickSegmentComputer2.init(aContour.begin());
  AlphaThickSegmentComputer2D anAlphaThickSegmentComputer3(2);
  anAlphaThickSegmentComputer3.init(aContour.begin());
  AlphaThickSegmentComputer2D anAlphaThickSegmentComputer4(1);
  anAlphaThickSegmentComputer4.init(aContour.begin());


  while (anAlphaThickSegmentComputer.end() != aContour.end() &&
         anAlphaThickSegmentComputer.extendFront()){}
  while (anAlphaThickSegmentComputer2.end() != aContour.end() &&
         anAlphaThickSegmentComputer2.extendFront() ){}
  while (anAlphaThickSegmentComputer3.end() != aContour.end() &&
         anAlphaThickSegmentComputer3.extendFront()){}
  while (anAlphaThickSegmentComputer4.end() != aContour.end() &&
         anAlphaThickSegmentComputer4.extendFront()){}


  // Display convexhull
  aBoard.setLineWidth(5);
  aBoard.setPenColor(DGtal::Color::Purple);
  for (AlphaThickSegmentComputer2D::ConvexhullConstIterator it = anAlphaThickSegmentComputer.convexhullBegin();
       it != anAlphaThickSegmentComputer.convexhullEnd(); it++){
    if ((it+1) != anAlphaThickSegmentComputer.convexhullEnd()){
      aBoard.drawLine((*it)[0], (*it)[1],
                      (*(it+1))[0],
                      (*(it+1))[1]);
    }else{
      aBoard.drawLine((*it)[0], (*it)[1],
                      (*(anAlphaThickSegmentComputer.convexhullBegin()))[0],
                      (*(anAlphaThickSegmentComputer.convexhullBegin()))[1]);
    }
  }


  // Display boundingbox
  aBoard << SetMode((*anAlphaThickSegmentComputer.begin()).className(), "Grid");
  aBoard << CustomStyle( anAlphaThickSegmentComputer2.className(),
                         new CustomColors( DGtal::Color::Green, DGtal::Color::None ) );
  aBoard << anAlphaThickSegmentComputer2;
  aBoard << CustomStyle( anAlphaThickSegmentComputer.className(),
                         new CustomColors( DGtal::Color::Blue, DGtal::Color::None ) );
  aBoard << anAlphaThickSegmentComputer;
  aBoard << CustomStyle( anAlphaThickSegmentComputer3.className(),
                         new CustomColors( DGtal::Color::Yellow, DGtal::Color::None ) );
  aBoard << anAlphaThickSegmentComputer3;
  aBoard << CustomStyle( anAlphaThickSegmentComputer4.className(),
                         new CustomColors( DGtal::Color::Magenta, DGtal::Color::None ) );
  aBoard << anAlphaThickSegmentComputer4;


  // Display the input curve
  aBoard << SetMode((*aContour.begin()).className(), "Grid");
  for (std::vector<Z2i::Point>::const_iterator it = aContour.begin();
       it != aContour.end(); it++){
    aBoard << *it;
    if (it+1 != aContour.end()){
      Z2i::Point next = *(it+1);
      aBoard.setPenColor(DGtal::Color::Gray);
      aBoard.drawLine((*it)[0], (*it)[1], next[0], next[1]);
    }
  }

  aBoard.saveEPS("testAlphaThickSegmentComputer_Convexhull.eps");
  trace.info() << " Alpha Thick with alpha 5, size (awaited be 41) = " << anAlphaThickSegmentComputer.getNumberSegmentPoints();
  res = anAlphaThickSegmentComputer.getNumberSegmentPoints()==41;
  nbok += res ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  trace.endBlock();

  trace.beginBlock("Testing access to extremity points");
  trace.info() << "First extremity point: " << anAlphaThickSegmentComputer.getExtremityPoints().first <<
    " ( should be " << *(aContour.begin())<<  ")" << std::endl;
  trace.info() << "Second extremity point: " << anAlphaThickSegmentComputer.getExtremityPoints().second <<
    " ( should be (80, 18) )" << std::endl;

  res = anAlphaThickSegmentComputer.getExtremityPoints().first == *(aContour.begin())&&
        anAlphaThickSegmentComputer.getExtremityPoints().second == Z2i::Point(80,18);
  nbok += res ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  trace.endBlock();


  trace.beginBlock("Testing access to anti podal points");
  std::pair<std::pair<Z2i::Point, Z2i::Point>,
            Z2i::Point> pairAntipodal =  anAlphaThickSegmentComputer.getAntipodalLeaningPoints();

  Z2i::Point p = pairAntipodal.first.first;
  Z2i::Point q = pairAntipodal.first.second;
  Z2i::Point s = pairAntipodal.second;
  aBoard.setPenColor(DGtal::Color::Red);
  aBoard.drawLine(p[0], p[1], q[0], q[1]);
  aBoard.fillCircle(s[0], s[1], 0.2);
  aBoard.saveEPS("testAlphaThickSegmentComputer_ConvexhullAntipodal.eps");

  trace.info() << "Antipodal pair: p " << p << ", q:" << q << ", s: "<< s << std::endl;
  trace.info() << "Should be  " << Z2i::Point(78,16) << " " << Z2i::Point(79,6) << Z2i::Point(83,13) <<std::endl;

  res = p==Z2i::Point(78,16) && q==Z2i::Point(79,6) && s == Z2i::Point(83,13);
  nbok += res ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;


  trace.beginBlock("Testing getter of segment parameters");
  pairAntipodal =  anAlphaThickSegmentComputer4.getAntipodalLeaningPoints();
  p = pairAntipodal.first.first;
  q = pairAntipodal.first.second;
  s = pairAntipodal.second;

  Z2i::RealPoint  vectDir =   (p-q)[0]>0? p-q: q-p;

  trace.info() << "Segment4 params: vect Dir: " << vectDir << std::endl;
  trace.info() << "Should be:   " << Z2i::RealPoint(1,1)  <<std::endl;

  res = vectDir == Z2i::RealPoint(1,1);
  nbok += res ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  trace.endBlock();
  return nbok == nb;
}



/**
 * Test alpha thick segment with floating points.
 */
bool testAlphaThickSegmentComputerFloatingPointContour()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  Board2D aBoard;
  typedef  AlphaThickSegmentComputer< Z2i::RealPoint> AlphaThickSegmentComputer2D;
  typedef  AlphaThickSegmentComputer< Z2i::RealPoint>::Primitive Primitive;

  trace.beginBlock ( "Testing alpha-thick segment on contour composed of floating coords ..." );
  std::vector<Z2i::RealPoint> aContour;
  std::string fileContour = testPath + "samples/contourNoiseSample2.sdp";
  aContour = PointListReader<Z2i::RealPoint>::getPointsFromFile(fileContour);

  AlphaThickSegmentComputer2D anAlphaThickSegmentComputer(2);
  anAlphaThickSegmentComputer.init(aContour.begin()+10);

  while (anAlphaThickSegmentComputer.end()!= aContour.end() &&
         anAlphaThickSegmentComputer.extendFront()){
  }


  // Display alpha thick segment
  aBoard << SetMode((*anAlphaThickSegmentComputer.begin()).className(), "Grid");
  aBoard << anAlphaThickSegmentComputer;


  // Test primitive of parallelStrip and display the input curve
  Primitive pStrip = anAlphaThickSegmentComputer.primitive();
  unsigned int nbInStrip = 0;

  aBoard << SetMode((*aContour.begin()).className(), "Grid");
  for (std::vector<Z2i::RealPoint>::const_iterator it = aContour.begin();
       it != aContour.end(); it++){
    if (it+1 != aContour.end()){
      Z2i::RealPoint next = *(it+1);
      aBoard.setLineWidth(2);
      aBoard.setPenColor(DGtal::Color::Gray);
      aBoard.drawLine((*it)[0], (*it)[1], next[0], next[1]);
    }
    if (pStrip(*it)){
      nbInStrip++;
      aBoard << *it;
    }
  }
  trace.info() << "Nb contour points in the segment parallel strip (awaited 32)  = " << nbInStrip << std::endl;

  nbok += nbInStrip==32;
  nb++;

  nbok += anAlphaThickSegmentComputer.getNumberSegmentPoints()==31 ? 1 : 0;
  nb++;

  trace.info() << "Segment size (awaited 31): " << anAlphaThickSegmentComputer.getNumberSegmentPoints() << std::endl;
  aBoard.saveEPS("testAlphaThickSegmentComputer_FloatingPt.eps");

  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  trace.endBlock();
  return nbok == nb;
}





/**
 * Test  alpha thick segment computer on Freeman Chain.
 */
bool testAlphaThickSegmentFreeman()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  typedef FreemanChain<Z2i::Space::Integer>::ConstIterator FCConstIterator;
  typedef  AlphaThickSegmentComputer< Z2i::Space::Point, FCConstIterator > AlphaThickSegmentComputer2D;

  Board2D aBoard;



  trace.beginBlock ( "Testing AlphaThickSegmentComputer2D on Freeman chain ..." );

  // Reading input contour
  std::string freemanChainFilename = testPath + "samples/klokan.fc";
  fstream fst;
  fst.open (freemanChainFilename.c_str(), ios::in);
  FreemanChain<Z2i::Space::Integer> fc(fst);
  fst.close();
  aBoard << fc;


  AlphaThickSegmentComputer2D anAlphaThickSegmentComputer(70.0);
  anAlphaThickSegmentComputer.init(fc.begin());
  while (anAlphaThickSegmentComputer.end() != fc.end() &&
         anAlphaThickSegmentComputer.extendFront()){
  }


  // Display segment
  aBoard << SetMode((*anAlphaThickSegmentComputer.begin()).className(), "Grid");
  aBoard << anAlphaThickSegmentComputer;
  trace.info() << "Segment size (awaited 642): " << anAlphaThickSegmentComputer.getNumberSegmentPoints() << std::endl;
  nbok += anAlphaThickSegmentComputer.getNumberSegmentPoints()==642 ? 1 : 0;
  nb++;

  // Display points inside the parallel strip
  unsigned int nbInStrip = 0;
  AlphaThickSegmentComputer2D::Primitive parallelStrip = anAlphaThickSegmentComputer.primitive();

  for(FCConstIterator it  = fc.begin(); it != fc.end(); it++){
    if(parallelStrip(*it)){
      aBoard.setPenColor(DGtal::Color::Blue);
      aBoard.drawCircle( (*it)[0],(*it)[1], 1.0) ;
      nbInStrip++;
    }
  }
  aBoard.setPenColor(DGtal::Color::Green);
  aBoard.fillCircle( (*(fc.begin()))[0],(*(fc.begin()))[1], 1.0) ;

  trace.info() << "Nb contour points in the segment parallel strip  (awaited 818)  = " << nbInStrip << std::endl;


  nbok +=  nbInStrip==818 ? 1 : 0;
  nb++;

  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  trace.endBlock();
  aBoard.saveEPS("testAlphaThickSegmentComputer_Freeman.eps");

  return nbok == nb;

}


/**
 * Test special cases on various initialisations.
 */
bool testAlphaThickSpecialInit()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  Board2D aBoard, aBoard2;
  typedef  AlphaThickSegmentComputer< Z2i::RealPoint> AlphaThickSegmentComputer2D;
  trace.beginBlock ( "Test special cases on various initialisations ..." );

  AlphaThickSegmentComputer2D segment(1.3);
  std::vector<Z2i::RealPoint> aContour;
  aContour.push_back(Z2i::RealPoint(29,20));
  aContour.push_back(Z2i::RealPoint(30,20.01 ));
  aContour.push_back(Z2i::RealPoint(31, 21));
  aContour.push_back(Z2i::RealPoint(32,20));
  segment.init(aContour.begin());
  segment.extendFront();
  while (segment.end()!= aContour.end() &&
         segment.extendFront()){
  }
  nb++;
  nbok  = segment.getNumberSegmentPoints()==4;

  // Display alpha thick segment
  for( std::vector<Z2i::RealPoint>::const_iterator it = aContour.begin(); it != aContour.end(); it++){
    aBoard << *it;
  }
  // Display alpha thick segment
  aBoard << SetMode((*segment.begin()).className(), "Grid");
  aBoard << segment;

  Z2i::Point p = segment.getAntipodalLeaningPoints().first.first;
  Z2i::Point q = segment.getAntipodalLeaningPoints().first.second;
  Z2i::Point s = segment.getAntipodalLeaningPoints().second;
  aBoard.setPenColor(DGtal::Color::Blue);
  aBoard.drawLine(p[0], p[1], q[0], q[1]);
  aBoard.setPenColor(DGtal::Color::Green);
  aBoard.fillCircle(s[0], s[1], 0.2);
  aBoard.saveEPS("testSpecialInit.eps");

  trace.info() << "Segment size: " << segment.getNumberSegmentPoints() << "(awaited : " << 4 <<")"<< std::endl;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  trace.endBlock();
  aBoard.saveEPS("testSpecialInit.eps");

  return nbok==nb;
}



/**
 * Test multi width segment computer
 **/
bool testMultiWidth()
{
  Board2D aBoard;
  typedef  AlphaThickSegmentComputer< Z2i::RealPoint> AlphaThickSegmentComputer2D;
  unsigned nb=0;
  unsigned nbok =0;
  trace.beginBlock ( "Testing alpha-thick segment with multi width ..." );
  std::vector<Z2i::RealPoint> aContour;
  std::string fileContour = testPath + "samples/contourNoiseSample2.sdp";
  aContour = PointListReader<Z2i::RealPoint>::getPointsFromFile(fileContour);
  HueShadeColorMap<double> hueMap(0.0, 10);
  unsigned int pos=0;
  unsigned int nbTotalAdded=0;
  for (double width=0.5; width<10; width+= 0.2, pos += 1) {
    AlphaThickSegmentComputer2D anAlphaThickSegmentComputer(width);
    anAlphaThickSegmentComputer.init(aContour.begin()+pos);
    nbTotalAdded++;
    while (anAlphaThickSegmentComputer.end()!= aContour.end() &&
           anAlphaThickSegmentComputer.extendFront()){
      nbTotalAdded++;
    }
    aBoard << SetMode((*anAlphaThickSegmentComputer.begin()).className(), "Grid");

    aBoard << CustomStyle( anAlphaThickSegmentComputer.className(),
                          new CustomColors( hueMap(width), DGtal::Color::None   ) );
    aBoard << anAlphaThickSegmentComputer;
  }
  trace.info() << "Nb total points added: " << nbTotalAdded << "(awaited:  2300) " << std::endl;
  trace.endBlock();
  aBoard.saveEPS("testMultiWidth.eps");
  nb++;
  nbok += nbTotalAdded == 2300;
  return nb==nbok;
}





/**
 * Test euclidean two thickness definitions
 **/
bool
testThicknessDefinitions(){
  Board2D aBoardHVthickness;
  Board2D aBoardEuclthickness;
  typedef  AlphaThickSegmentComputer<Z2i::Point> AlphaThickSegmentComputer2D;
  unsigned nb=0;
  unsigned nbok =0;
  trace.beginBlock ( "Testing alpha-thick segment with different thickness definitions:" );

  AlphaThickSegmentComputer2D anAlphaSegmentHV(1.35, functions::Hull2D::HorizontalVerticalThickness);
  AlphaThickSegmentComputer2D anAlphaSegmentEucl(1.35, functions::Hull2D::EuclideanThickness);

  Z2i::Domain adom(Z2i::Point(99,45), Z2i::Point(106,55));
  aBoardEuclthickness << adom;
  aBoardHVthickness << adom;

  std::vector<Z2i::Point> aVect;
  aVect.push_back(Z2i::Point(104, 54));
  aVect.push_back(Z2i::Point(104, 53));
  aVect.push_back(Z2i::Point(103, 53));
  aVect.push_back(Z2i::Point(103, 52));
  aVect.push_back(Z2i::Point(102, 52));
  aVect.push_back(Z2i::Point(102, 51));
  aVect.push_back(Z2i::Point(102, 50));
  aVect.push_back(Z2i::Point(101, 50));
  aVect.push_back(Z2i::Point(101, 49));
  aVect.push_back(Z2i::Point(101, 48));
  aVect.push_back(Z2i::Point(100, 48));
  aVect.push_back(Z2i::Point(100, 47));
 // Display the input curve
  aBoardEuclthickness << SetMode((*aVect.begin()).className(), "Grid");
  aBoardHVthickness << SetMode((*aVect.begin()).className(), "Grid");
  for (std::vector<Z2i::Point>::const_iterator it = aVect.begin();
       it != aVect.end(); it++){
    aBoardHVthickness << *it;
    aBoardEuclthickness << *it;
    if (it+1 != aVect.end()){
      Z2i::Point next = *(it+1);
      aBoardEuclthickness.setPenColor(DGtal::Color::Gray);
      aBoardHVthickness.setPenColor(DGtal::Color::Gray);
      aBoardEuclthickness.drawLine((*it)[0], (*it)[1], next[0], next[1]);
      aBoardHVthickness.drawLine((*it)[0], (*it)[1], next[0], next[1]);
    }
  }

  anAlphaSegmentEucl.init(aVect.begin());
  while(anAlphaSegmentEucl.end() != aVect.end()
        && anAlphaSegmentEucl.extendFront()){
  }
  anAlphaSegmentHV.init(aVect.begin());
  while(anAlphaSegmentHV.end() != aVect.end()
        && anAlphaSegmentHV.extendFront()){
  }


  trace.info() << "Euclidean thickness based segment, th= " << anAlphaSegmentEucl.getThickness() << std::endl;
  trace.info() << "Horizontal/Vertical thickness based segment, th= " << anAlphaSegmentHV.getThickness() << std::endl;


  aBoardHVthickness  << CustomStyle( anAlphaSegmentEucl.className(), new CustomColors( DGtal::Color::Blue, DGtal::Color::None ) );
  aBoardEuclthickness  << CustomStyle( anAlphaSegmentHV.className(), new CustomColors( DGtal::Color::Blue, DGtal::Color::None ) );
  aBoardHVthickness << anAlphaSegmentHV;
  aBoardEuclthickness << anAlphaSegmentEucl;

  std::vector<Z2i::Point> hullHV = anAlphaSegmentHV.getConvexHull();
  std::vector<Z2i::Point> hullEucl = anAlphaSegmentEucl.getConvexHull();
  aBoardEuclthickness.setLineWidth(5);
  aBoardHVthickness.setLineWidth(5);
  aBoardEuclthickness.setPenColor(DGtal::Color::Purple);
  aBoardHVthickness.setPenColor(DGtal::Color::Purple);
  for (unsigned int i = 0; i < hullEucl.size(); i++){
    aBoardEuclthickness.drawLine(hullEucl.at(i)[0], hullEucl.at(i)[1],
                                 hullEucl.at((i+1)%hullEucl.size())[0],
                                 hullEucl.at((i+1)%hullEucl.size())[1]);
  }
  for (unsigned int i = 0; i < hullHV.size(); i++){
    aBoardHVthickness.drawLine(hullHV.at(i)[0], hullHV.at(i)[1],
                               hullHV.at((i+1)%hullHV.size())[0],
                               hullHV.at((i+1)%hullHV.size())[1]);
  }

  Z2i::Point pEucl = anAlphaSegmentEucl.getAntipodalLeaningPoints().first.first;
  Z2i::Point qEucl = anAlphaSegmentEucl.getAntipodalLeaningPoints().first.second;
  Z2i::Point sEucl = anAlphaSegmentEucl.getAntipodalLeaningPoints().second;

  Z2i::Point pHV = anAlphaSegmentHV.getAntipodalLeaningPoints().first.first;
  Z2i::Point qHV = anAlphaSegmentHV.getAntipodalLeaningPoints().first.second;
  Z2i::Point sHV = anAlphaSegmentHV.getAntipodalLeaningPoints().second;
  aBoardEuclthickness.setPenColor(DGtal::Color::Red);
  aBoardHVthickness.setPenColor(DGtal::Color::Red);

  aBoardEuclthickness.drawCircle( pEucl[0], pEucl[1], 0.25);
  aBoardHVthickness.drawCircle( pHV[0], pHV[1], 0.25);

  aBoardEuclthickness.drawCircle( qEucl[0], qEucl[1], 0.25);
  aBoardHVthickness.drawCircle( qHV[0], qHV[1], 0.25);

  aBoardEuclthickness.setPenColor(DGtal::Color::Green);
  aBoardHVthickness.setPenColor(DGtal::Color::Green);

  aBoardEuclthickness.drawCircle( sEucl[0], sEucl[1], 0.25);
  aBoardHVthickness.drawCircle( sHV[0], sHV[1], 0.25);

  aBoardEuclthickness.saveEPS("testAlphaThickEucl.eps");
  aBoardHVthickness.saveEPS("testAlphaThickHV.eps");

  trace.endBlock();
  return nb==nbok;
}




///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class AlphaThickSegmentComputer" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res =  testAlphaThickSegmentConvexHullAndBox() && testAlphaThickSegmentComputerFloatingPointContour() &&
    testAlphaThickSegmentFreeman() && testAlphaThickSpecialInit() && testMultiWidth() && testThicknessDefinitions();

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;


  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
