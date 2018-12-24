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
 * @file testGenericWriter.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2013/05/01
 *
 * Functions for testing class GenericWriter.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/io/readers/GenericReader.h"
#include "DGtal/io/writers/GenericWriter.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigTest.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class GenericWriter.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testGenericWriter()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  typedef DGtal::ImageContainerBySTLVector<DGtal::Z3i::Domain, unsigned char > Image3D;
  typedef DGtal::ImageContainerBySTLVector<DGtal::Z3i::Domain, unsigned int > Image3D32bits;
  typedef DGtal::ImageContainerBySTLVector<DGtal::Z2i::Domain,  unsigned char > Image2D;
  typedef DGtal::ImageContainerBySTLVector<DGtal::Z2i::Domain,  unsigned int > Image2D32bits;
  typedef DGtal::ImageContainerBySTLVector<DGtal::Z2i::Domain,  DGtal::Color > Image2DColor;

  Image3D32bits an32bitsImage3D (DGtal::Z3i::Domain(DGtal::Z3i::Point(0,0,0),  DGtal::Z3i::Point(4,4,4)));
  for(unsigned int i =0; i< 5; i++){
    for(unsigned int j =0; j< 5; j++){
      for(unsigned int k =0; k< 5; k++){
        an32bitsImage3D.setValue(DGtal::Z3i::Point(k,j,i), 250000*i*j*k);
      }
    }
  }
  Image2D32bits an32bitsImage2D (DGtal::Z2i::Domain(DGtal::Z2i::Point(0,0),  DGtal::Z2i::Point(4,4)));
  for(unsigned int i =0; i< 5; i++){
    for(unsigned int j =0; j< 5; j++){
      an32bitsImage2D.setValue(DGtal::Z2i::Point(j,i), 250000*i*j*4);
    }
  }

  Image2DColor anColorImage2D (DGtal::Z2i::Domain(DGtal::Z2i::Point(0,0),  DGtal::Z2i::Point(255,255)));


  for(unsigned int i =0; i<= 255; i++){
    for(unsigned int j =0; j<= 255; j++){
      anColorImage2D.setValue(DGtal::Z2i::Point(i,j),DGtal::Color(i,j,(i+j)%255));
    }
  }

  
  trace.beginBlock ( "Testing block ..." );
  std::string filenameImage1 = testPath + "samples/cat10.pgm3d";    
  trace.info() << "Reading 3D image  ... ";  
  Image3D anImportedImage1 = DGtal::GenericReader<Image3D>::import(filenameImage1);  
  trace.info() <<"[done]"  << std::endl;
  trace.info() << "Testing writing PGM3D ... ";  
  bool ok1 = anImportedImage1>> "testGenericWriter.pgm3d";
  trace.info() <<"[done]"  << std::endl;
  
  bool okh5 = true;
  bool okh5bis = true;
#ifdef WITH_HDF5
  trace.info() << "Testing writing HDF5 3D ... ";
  okh5 = anImportedImage1 >> "testGenericWriter.h5";
  trace.info() <<"[done]"  << std::endl;
  trace.info() << "Testing writing HDF5 3D (bis) ... ";  
  okh5bis = DGtal::GenericWriter<Image3D>::exportFile("testGenericWriter_bis.h5", anImportedImage1, "/UInt8Array3D");
  trace.info() <<"[done]"  << std::endl;
#endif
  
  trace.info() << "Testing writing vol ... ";  
  bool ok2 = anImportedImage1 >> "testGenericWriter.vol";
  trace.info() <<"[done]"  << std::endl;
  trace.info() << "Testing writing raw ... ";  
  bool ok3 = anImportedImage1 >>"testGenericWriter.raw";
  trace.info() <<"[done]"  << std::endl;
  trace.info() << "Testing writing raw (bis) ... ";  
  bool ok3bis = DGtal::GenericWriter<Image3D>::exportFile( "testGenericWriter.raw", anImportedImage1);
  trace.info() <<"[done]"  << std::endl;

  std::string filenameImage2 = testPath + "samples/contourS.pgm";    

  trace.info() << "Reading 2D image  ... ";  
  Image2D anImportedImage2 = DGtal::GenericReader<Image2D>::import(filenameImage2);  
  trace.info() <<"[done]"  << std::endl; 
  trace.info() << "Testing writing pgm ... ";  
  bool ok4 = anImportedImage2 >> "testGenericWriter.pgm";
  trace.info() <<"[done]"  << std::endl;
  trace.info() << "Testing writing raw ... ";  
  bool ok5 = anImportedImage2 >> "testGenericWriter.raw";
  trace.info() <<"[done]"  << std::endl;
  bool ok6 = DGtal::GenericWriter<Image3D32bits>::exportFile( "testGenericWriter32bits3D.raw", an32bitsImage3D);
  trace.info() <<"[done]"  << std::endl;
  bool ok7 = DGtal::GenericWriter<Image2D32bits>::exportFile( "testGenericWriter32bits2D.raw", an32bitsImage2D);
  trace.info() <<"[done]"  << std::endl;
  bool ok8 = DGtal::GenericWriter<Image2DColor>::exportFile( "testGenericWriterColorImage.ppm", anColorImage2D);
  trace.info() <<"[done]"  << std::endl;
#ifdef WITH_MAGICK
  bool ok9 = DGtal::GenericWriter<Image2DColor>::exportFile( "testGenericWriterColorImage.png", anColorImage2D);
#else
  bool ok9 = true;
#endif  

  nbok += ((ok1 && okh5 && okh5bis && ok2 && ok3 && ok3bis && ok4 && ok5 && ok6 && ok7 && ok8 && ok9) ? 1 : 0); 
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
  trace.beginBlock ( "Testing class GenericWriter" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testGenericWriter(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
