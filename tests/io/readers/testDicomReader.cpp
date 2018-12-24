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
 * @file testDicomReader.cpp
 * @ingroup Tests
 * @author Adrien Krähenbühl (\c adrien.krahenbuhl@loria.fr )
 * LORIA (CNRS, UMR 7503), Université de Lorraine, France
 *
 * @date 2013/10/14
 *
 * Functions for testing class DicomReader.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/readers/DicomReader.h"

#include "ConfigTest.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class DicomReader.
///////////////////////////////////////////////////////////////////////////////

/**
 * Example of a test. To be completed.
 *
 */
bool testDicomReader()
{
  //Default image selector = STLVector
  typedef ImageContainerBySTLVector<Z3i::Domain,  unsigned char > Image3D;

  std::string filename = testPath + "samples/dicomSample/1629.dcm";
  Image3D image = DicomReader< Image3D >::importDicom( filename );

  trace.info() << image <<endl;

  unsigned int nbVal=0, nbPos = 0;
  for ( Image3D::ConstIterator it=image.begin(), itend=image.end() ; it != itend ; ++it )
  {
    nbVal++;
	  if ( (*it) > 0 ) nbPos++;
  }

  trace.info() << "Number of points with (val>0) = " << nbVal << endl;

  return nbVal==2130048 && nbPos==296030;
}


bool testIOException()
{
  //Default image selector = STLVector
  typedef ImageContainerBySTLVector<Z3i::Domain,  int > Image3D;

  std::string filename = testPath + "samples/null.dcm";
  try {
	  Image3D image = DicomReader< Image3D >::importDicom( filename );
  }
  catch(exception& e) {
	  trace.info() << "Exception catched. Message : " << e.what()<<endl;
    return true;
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class DicomReader" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
	trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testDicomReader() && testIOException();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();

  return !res;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
