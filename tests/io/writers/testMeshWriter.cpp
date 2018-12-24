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
 * @file testMeshWriter.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2012/07/08
 *
 * Functions for testing class MeshWriter.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h" 
//! [MeshWriterUseIncludes]
#include "DGtal/shapes/Mesh.h"
#include "DGtal/io/writers/MeshWriter.h"
//! [MeshWriterUseIncludes]
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class MeshWriter.
///////////////////////////////////////////////////////////////////////////////


/**
 * Example of a test. To be completed.
 *
 */
bool testMeshWriter()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  //! [MeshWriterUseMeshCreation]
  // Constructing the mesh to export in OFF format
  Mesh<Point> aMesh(true);  
  vector<Point> vectVertex;
  Point p1(0, 0, 0);
  Point p2(1, 0, 0);
  Point p3(1, 1, 0);
  Point p4(0, 1, 0);  
  Point p11(0, 0, 1);
  Point p21(1, 0, 1);
  Point p31(1, 1, 1);
  Point p41(0, 1, 1);  
  aMesh.addVertex(p1);
  aMesh.addVertex(p2);
  aMesh.addVertex(p3);
  aMesh.addVertex(p4);  
  aMesh.addVertex(p11);
  aMesh.addVertex(p21);
  aMesh.addVertex(p31);
  aMesh.addVertex(p41);  

  vector<DGtal::Color> vectColor;
  DGtal::Color col (250,0,0, 200);
  DGtal::Color col2 (250,250,0, 200);
  
  aMesh.addQuadFace(0,1,2,3, col);
  aMesh.addQuadFace(4,5,6,7, col2);
  aMesh.addQuadFace(0,1,5,4, col);

  //! [MeshWriterUseMeshCreation]
  //! [MeshWriterUseMeshExport]
  bool isOK = aMesh >> "test.off";
  //! [MeshWriterUseMeshExport]
  nb++;
  bool isOK2 = aMesh >> "testColor.obj";
  nb++;
  std::fstream exportObj;
  exportObj.open("test.obj", std::fstream::out);
  bool isOK3 = MeshWriter<Point>::export2OBJ(exportObj, aMesh);
  
  nb++;
  
  trace.beginBlock ( "Testing block ..." );
  nbok += isOK ? 1 : 0; 
  nbok += isOK2 ? 1 : 0; 
  nbok += isOK3 ? 1 : 0; 
 
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;
  trace.endBlock();
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class MeshWriter" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testMeshWriter(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


