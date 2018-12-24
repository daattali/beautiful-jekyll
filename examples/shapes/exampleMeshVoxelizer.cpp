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
 * @file exampleMeshVoxelizer.cpp
 * @ingroup Examples
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2017/11/16
 *
 * An example file named exampleMeshVoxelizer
 *
 * This file is part of the DGtal library.
 */


/**
 * \image html  resultCube.png  "Resulting digitization of a cube"
 * 
 *   \example shapes/exampleMeshVoxelizer.cpp
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ConfigExamples.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"
#include "DGtal/shapes/Mesh.h"
//! [MeshVoxelizerInc]
#include "DGtal/shapes/MeshVoxelizer.h"
//! [MeshVoxelizerInc]
#include "DGtal/io/boards/Board3D.h"
#include "DGtal/io/writers/MeshWriter.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( )
{
  trace.beginBlock ( "Example MeshVoxelizer" );


  //! [MeshVoxelizerCreatingMesh]
  using namespace Z3i;
  Mesh<Point> aMesh;

  trace.info()<<"Creating a cube"<<std::endl;
  //Creating a cube
  aMesh.addVertex(Point(0,0,0));
  aMesh.addVertex(Point(1,0,0));
  aMesh.addVertex(Point(1,1,0));
  aMesh.addVertex(Point(0,1,0));
  aMesh.addVertex(Point(0,1,1));
  aMesh.addVertex(Point(1,1,1));
  aMesh.addVertex(Point(1,0,1));
  aMesh.addVertex(Point(0,0,1));
  
  aMesh.addQuadFace(0,1,2,3);
  aMesh.addQuadFace(1,2,5,6);
  aMesh.addQuadFace(7,6,5,4);
  aMesh.addQuadFace(3,2,5,4);
  aMesh.addQuadFace(0,3,4,7);
  aMesh.addQuadFace(0,1,6,7);
  //! [MeshVoxelizerCreatingMesh]
  

  //! [MeshVoxelizerDig]
  Domain domain(Point(0,0,0), Point(128,128,128));
  DigitalSet outputSet(domain);
  
  MeshVoxelizer<DigitalSet, 6> voxelizer;

  trace.info()<<"Digitization..."<<std::endl;
  voxelizer.voxelize(outputSet, aMesh, 15.0);

  trace.info()<<"Got "<< outputSet.size() << " voxels."<<std::endl;
  //! [MeshVoxelizerDig]

  //! [MeshVoxelizerExport]
  Board3D<> board;
  for(auto voxel : outputSet)
    board << voxel;
  board.saveOBJ("voxelizedCube.obj");
  //! [MeshVoxelizerExport]
  
  
  
  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
