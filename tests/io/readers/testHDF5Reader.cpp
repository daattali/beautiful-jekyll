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
 * @file testHDF5Reader.cpp
 * @ingroup Tests
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 *
 * @date 2013/04/16
 *
 * Functions for testing class HDF5Reader.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/writers/PPMWriter.h"
#include "DGtal/io/readers/HDF5Reader.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/io/colormaps/GrayscaleColorMap.h"
#include "ConfigTest.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class HDF5Reader.
///////////////////////////////////////////////////////////////////////////////
bool testHDF5Reader()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;  
  
  trace.beginBlock ( "Testing hdf5 reader ..." );
  nbok += true ? 1 : 0; 
  nb++;
  std::string filename = testPath + "samples/ex_image2.h5";

  trace.info() << "Loading filename: " << filename << std::endl;
  
  typedef GrayscaleColorMap<unsigned char> Gray; // a simple GrayscaleColorMap varying on 'unsigned char' values
  typedef ImageSelector < Z2i::Domain, unsigned char>::Type Image;
  
  Image image = HDF5Reader<Image>::importHDF5( filename, "/image8bit" ); 
  trace.info() << "image8bitFromHDF5image image: " << image << endl;
  PPMWriter<Image,Gray>::exportPPM("image8bitFromHDF5image.ppm", image, Gray(0,255));
  
  image = HDF5Reader<Image>::importHDF5( filename, "/image24bitpixel" ); 
  trace.info() << "image24bitFromHDF5image image: " << image << endl;
  PPMWriter<Image,Gray>::exportPPM("image24bitFromHDF5image.ppm", image, Gray(0,255));
  
  trace.info() << "(" << nbok << "/" << nb << ") " << "true == true" << std::endl;
  trace.endBlock();  
  
  return nbok == nb;
}

bool testHDF5_3DReader()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing hdf5 3D reader ..." );

  typedef SpaceND<3> Space4Type;
  typedef HyperRectDomain<Space4Type> TDomain;
  
  //Default image selector = STLVector
  typedef ImageSelector<TDomain, unsigned char>::Type Image;
  
  
  std::string filename = testPath + "samples/cat10.h5";
  Image image = HDF5Reader<Image>::importHDF5_3D( filename, "/UInt8Array3D" );
  
  trace.info() << image <<endl;
  
  nbok += true ? 1 : 0; 
  nb++;

  unsigned int nbval=0;
  for(Image::ConstIterator it=image.begin(), itend=image.end();
      it != itend;   ++it)
    if ( (*it) != 0)
      nbval++;
  
  trace.info() << "Number of points with (val!=0)  = "<<nbval<<endl;

  nbok += ( nbval == 8043)  ? 1 : 0; 
  nb++;

  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true == true" << std::endl;
  trace.endBlock();
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class HDF5Reader" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testHDF5Reader() && testHDF5_3DReader(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}

//                                                                           //
///////////////////////////////////////////////////////////////////////////////
