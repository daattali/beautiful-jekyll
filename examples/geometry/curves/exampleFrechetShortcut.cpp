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
 * @file geometry/curves/exampleFrechetShortcut.cpp
 * @ingroup Examples
 * @author Isabelle Sivignon (\c isabelle.sivignon@gipsa-lab.grenoble-inp.fr )
 * gipsa-lab Grenoble Images Parole Signal Automatique (CNRS, UMR 5216), CNRS, France
 *
 * @date 2012/03/26
 *
 * An example file named exampleFrechetShortcut.
 *
 * This file is part of the DGtal library.
 */


/**
   This snippet segments a digital curve into Frechet shortcuts.  

@see \ref moduleFrechetShortcut and \ref moduleGridCurveAnalysis

\example geometry/curves/exampleFrechetShortcut.cpp
*/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"

#include "ConfigExamples.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/geometry/curves/FrechetShortcut.h"
#include "DGtal/geometry/curves/GreedySegmentation.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i;




///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
  trace.beginBlock ( "Example FrechetShortcut" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  std::string filename;
  double error;
  
  if(argc == 1)
    {
      trace.info() << "Use default file and error value\n";
      filename = examplesPath + "samples/plant-frechet.dat";
      error = 3;
    }
  else
    if(argc != 3)
      {
	trace.info() << "Please enter a filename and error value.\n";
	return 0;
      }
    else
      {
	filename = argv[1];
	error = atof(argv[2]);
      }
  ifstream instream; // input stream
  instream.open (filename.c_str(), ifstream::in);
  

  
  Curve c; //grid curve
  c.initFromVectorStream(instream);
  
  Board2D board;
  
  // Display the pixels as arrows range to show the way the curve is scanned
  board << c.getArrowsRange();
  
  trace.beginBlock("Simple example");

  //! [FrechetShortcutUsage]
  Curve::PointsRange r = c.getPointsRange(); 
  
  typedef FrechetShortcut<Curve::PointsRange::ConstIterator,int> Shortcut;
  
  // Computation of one shortcut
  Shortcut s(error);
  
  s.init( r.begin() );
  while ( ( s.end() != r.end() )
  	  &&( s.extendFront() ) ) {}
  


  // Computation of a greedy segmentation
  
  typedef GreedySegmentation<Shortcut> Segmentation;
  
  Segmentation theSegmentation( r.begin(), r.end(), Shortcut(error) );
  
  // the segmentation is computed here
  Segmentation::SegmentComputerIterator it = theSegmentation.begin();
  Segmentation::SegmentComputerIterator itEnd = theSegmentation.end();

  for ( ; it != itEnd; ++it) {
    s=Shortcut(*it);
    trace.info() << s << std::endl;
    board << s; 
  }
  
  board.saveEPS("FrechetShortcutExample.eps", Board2D::BoundingBox, 5000 ); 

  //! [FrechetShortcutUsage]
  #ifdef WITH_CAIRO
    board.saveCairo("FrechetShortcutExample.png"); 
  #endif


  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
