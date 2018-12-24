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
 * @file geometry/tools/examplePreimage.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/09/21
 *
 * @brief An example file for Preimage2D.
 *
 * This file is part of the DGtal library.
 */



/**
   Example of Preimage2D.
   \image  html  preimageExample2.png "Example of preimage based arc recognition."
   \example geometry/tools/examplePreimage.cpp
**/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"

#include "DGtal/geometry/tools/Preimage2D.h"
#include "DGtal/shapes/fromPoints/StraightLineFrom2Points.h"
#include "DGtal/shapes/fromPoints/CircleFrom2Points.h"

#include "DGtal/io/boards/Board2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i; 


///////////////////////////////////////////////////////////////////////////////
int main( int argc, char** argv )
{
  trace.beginBlock ( "Example for Preimage computation" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;
  
  std::string filename = examplesPath + "samples/DSS.dat";
  ifstream instream; // input stream
  instream.open (filename.c_str(), ifstream::in);
  
  Curve c; //grid curve
  c.initFromVectorStream(instream);

{
  trace.beginBlock("Simple preimage example");

  //! [PreimageTypedefFromStraightLine]
  typedef StraightLineFrom2Points<Curve::Point> StraightLine;
  StraightLine aStraightLine; //instance of straight line
  typedef Preimage2D<StraightLine> Preimage2D;
  //! [PreimageTypedefFromStraightLine]


  //! [PreimageUsageFromIncidentPointsRange]
  Curve::IncidentPointsRange r = c.getIncidentPointsRange(); //range
  Curve::IncidentPointsRange::ConstIterator it (r.begin()); //iterators
  Curve::IncidentPointsRange::ConstIterator itEnd (r.end()); 

  //preimage computation
  Preimage2D thePreimage(it->first, it->second, aStraightLine);
  ++it; 
  while ( (it != itEnd) &&
              (thePreimage.addFront(it->first, it->second)) )
  {
    ++it;
  }
  trace.info() << thePreimage << endl;
  //display
  Board2D board;
  board.setUnit(Board2D::UCentimeter);
  board << r << thePreimage; 
  board.saveEPS( "PreimageExample.eps" );
  //! [PreimageUsageFromIncidentPointsRange]
  
  trace.endBlock();
}

{
  trace.beginBlock("Preimage example with circles");
  Curve::Point pole(7,2); 

  //! [PreimageTypedefFromCircle]
  typedef CircleFrom2Points<Curve::Point> Circle;
  Circle aCircle( pole ); //instance of circle passing through point 'pole' 
  typedef Preimage2D<Circle> Preimage2D;
  //! [PreimageTypedefFromCircle]

  Curve::IncidentPointsRange r = c.getIncidentPointsRange(); //range
  Curve::IncidentPointsRange::ConstIterator it (r.begin()); //iterators
  Curve::IncidentPointsRange::ConstIterator itEnd (r.end()); 

  //preimage computation
  Preimage2D thePreimage(it->first, it->second, aCircle);
  ++it; 
  while ( (it != itEnd) &&
              (thePreimage.addFront(it->first, it->second)) )
  {
    ++it;
  }
  trace.info() << thePreimage << endl;
  //display
  Board2D board;
  board.setUnit(Board2D::UCentimeter);
  board << r << SetMode(pole.className(),"Grid") << pole << thePreimage; 
  board.saveEPS( "PreimageExample2.eps" );
  board.saveSVG( "PreimageExample2.svg" );  
#ifdef WITH_CAIRO
    board.saveCairo("PreimageExample2.pdf", Board2D::CairoPDF);
#endif

  trace.endBlock();
}

  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
