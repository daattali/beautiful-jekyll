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
 * @file testPNMReader.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/04/29
 *
 * Functions for testing class PNMReader.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/readers/PPMReader.h"
#include "DGtal/io/readers/PGMReader.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "ConfigTest.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class PNMReader.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testPNMReader()
{
  trace.beginBlock ( "Testing pgm reader ..." );
  std::string filename = testPath + "samples/circleR10.pgm";

  trace.info() << "Loading filename: "<< filename<<std::endl;

  typedef ImageSelector < Z2i::Domain, unsigned int>::Type Image;
  Image image = PGMReader<Image>::importPGM( filename ); 
  
  Z2i::DigitalSet set2d (image.domain());
  SetFromImage<Z2i::DigitalSet>::append<Image>(set2d, image, 0, 255);
   
  Board2D board;
  board << image.domain() << set2d; // display domain and set
  
  board.saveEPS( "testPNMReaderPGM.eps");
  trace.endBlock();

  trace.beginBlock ( "Testing ppm reader ..." );
  std::string filenamePPM = testPath + "samples/color64.ppm";

  trace.info() << "Loading filename: "<< filenamePPM <<std::endl;

  typedef ImageSelector < Z2i::Domain, unsigned int>::Type Image;
  Image imagePPM = PPMReader<Image>::importPPM( filenamePPM ); 
  
  Z2i::DigitalSet set2dPPM (imagePPM.domain());
  SetFromImage<Z2i::DigitalSet>::append<Image>(set2dPPM, imagePPM, 0, 0xFFFFFEu);
   
  Board2D boardPPM;
  boardPPM << imagePPM.domain() << set2dPPM; // display domain and set
  
  boardPPM.saveEPS( "testPNMReaderPPM.eps");
  trace.endBlock();  

  return true;
}
/**
 * Example of a test. To be completed.
 *
 */
bool testPNM3DReader()
{
  trace.beginBlock ( "Testing pgm3D reader ..." );
  std::string filename = testPath + "samples/simple.pgm3d";

  trace.info() << "Loading filename: "<< filename<<std::endl;

  typedef ImageSelector < Z3i::Domain, unsigned int>::Type Image;
  Image image = PGMReader<Image>::importPGM3D( filename ); 
  
  trace.info() << "Image 3D = "<<image<<std::endl;
  
  trace.endBlock();
  return true;
}

bool testPNM3DASCIIReader()
{
    trace.beginBlock ( "Testing P2 pgm3D reader ..." );
    std::string filename = testPath + "samples/ascii_ball.pgm3d";

    trace.info() << "Loading filename: "<< filename<<std::endl;

    typedef ImageSelector < Z3i::Domain, unsigned int>::Type Image;
    Image image = PGMReader<Image>::importPGM3D( filename );

    trace.info() << "Image 3D = "<<image<<std::endl;

    trace.endBlock();
    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class PNMReader" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testPNMReader() && testPNM3DReader() && testPNM3DASCIIReader(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
