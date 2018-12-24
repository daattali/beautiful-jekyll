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
 * @file testMeshReader.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2012/07/04
 *
 * Functions for testing class MeshReader.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/shapes/Mesh.h"
#include "DGtal/io/readers/MeshReader.h"
#include "DGtal/helpers/StdDefs.h"

#include "ConfigTest.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;



struct Point3D{  
  static const unsigned int dimension = 3;
  const double & operator[]( unsigned int i ) const{
    assert(i<3);
    switch (i){
    case 0: {return x;}
    case 1: {return y;}
    case 2: {return z;}
    }
    return x;
  };

   double & operator[]( unsigned int i ) {
    assert(i<3);
    switch (i){
    case 0: {return x;}
    case 1: {return y;}
    case 2: {return z;}
    }
    return x;
  };
  
  double  x, y,z;
};


typedef Point3D Point;




 



///////////////////////////////////////////////////////////////////////////////
// Functions for testing class MeshReader.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testMeshReader()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing block ..." );  
  nb++;
  std::string filenameOFF = testPath + "samples/box.off";  
  Mesh<Point> a3DMesh;
  bool importOK = a3DMesh << filenameOFF;
  nbok += importOK ? 1 : 0; 
  
  
  nb++;
  Mesh<Point>::MeshFace aFace = a3DMesh.getFace(0);
  bool isWellImported = (a3DMesh.nbVertex()==8) &&  (a3DMesh.nbFaces()==6) && (aFace.size()==4) && (aFace.at(0)==0);
  nbok+=isWellImported? 1: 0; 
  

  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;


  nb++;
  std::string filenameOFS = testPath + "samples/testMesh.ofs";  
  Mesh<Point> a3DMesh2;
  bool importOK2=  a3DMesh2 << filenameOFS;
  nbok += importOK2 ? 1 : 0; 
  
  nb++;
  Mesh<Point>::MeshFace aFace2 = a3DMesh2.getFace(0);
  bool isWellImported2 = (a3DMesh2.nbVertex()==32) &&  (a3DMesh2.nbFaces()==60) && (aFace2.size()==3) && (aFace2.at(0)==0);
  nbok+=isWellImported2? 1: 0;


  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;
  trace.endBlock();  
  
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class MeshReader" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testMeshReader(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
