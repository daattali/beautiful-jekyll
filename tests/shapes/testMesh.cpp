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
 * @file
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2012/07/02
 *
 * Functions for testing class 3DMeshFromPoints.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/writers/MeshWriter.h"
#include "DGtal/shapes/Mesh.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i;



///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Mesh.
///////////////////////////////////////////////////////////////////////////////

/**
 * Test the mesh object construction.
 */
bool testMesh()
{
  
  trace.beginBlock ( "Testing Mesh  ..." );
  bool ok = true;
  trace.beginBlock ( "Testing Mesh contruction  ..." );
  Mesh<Point> aMesh;
  Point p0=Point(0,0);
  Point p1=Point(0,1);
  Point p2=Point(1,2);
  Point p3=Point(3,2);
  Point p4=Point(3,3);
  Point p5=Point(3,4);
    
  aMesh.addVertex(p0);
  aMesh.addVertex(p1);
  aMesh.addVertex(p2);
  aMesh.addVertex(p3);
  aMesh.addVertex(p4);
  aMesh.addVertex(p5);
  
  aMesh.addTriangularFace(0,1,2);
  aMesh.addTriangularFace(3,4,5);
  
  Mesh<Point>::MeshFace tface0 = aMesh.getFace(0);
  Mesh<Point>::MeshFace tface1 = aMesh.getFace(1);
  Point p0f0 = aMesh.getVertex(tface0.at(0));
  Point p1f0 = aMesh.getVertex(tface0.at(1));
  Point p2f0 = aMesh.getVertex(tface0.at(2));

  Point p0f1 = aMesh.getVertex(tface1.at(0));
  Point p1f1 = aMesh.getVertex(tface1.at(1));
  Point p2f1 = aMesh.getVertex(tface1.at(2));
  trace.info() << "Set of points" << endl;
  trace.info() << p0 << p1 << p2 << endl;
  trace.info() << p3 << p4 << p5 << endl;
  
  trace.info() << "Face1 points " << endl;
  trace.info() << p0f0 << p1f0 << p2f0<< endl;

  trace.info() << "Face2 points " << endl;
  trace.info() << p0f1 << p1f1 << p2f1<< endl;
  
  
  bool okMeshConstruct =  (p0==p0f0) && (p1==p1f0) && (p2==p2f0) && 
    (p3==p0f1) && (p4==p1f1) && (p5==p2f1) ;
  
  trace.endBlock();
  bool okMeshIterators = true;
  trace.beginBlock ( "Testing Mesh iterator  ..." );
  unsigned int nb=0;
  // just testing nb iterations on const iterator
  for(  Mesh<Point>::VertexStorage::const_iterator it = aMesh.vertexBegin(); 
       it !=aMesh.vertexEnd(); 
       it++){
    nb++;    
  }
  okMeshIterators = okMeshIterators && (nb == aMesh.nbVertex());
  if (nb == aMesh.nbVertex())
    trace.info() << "vertex iteration test ok"<<std::endl;
  
  // testing to change vertex  on  iterator
  for(  Mesh<Point>::VertexStorage::iterator it = aMesh.vertexBegin(); 
       it !=aMesh.vertexEnd(); 
       it++){
    (*it)[0]+=10.0; (*it)[1]+=5.0;
  }
  // just testing nb iterations on const iterator
  nb=0;
  for(  Mesh<Point>::FaceStorage::const_iterator it = aMesh.faceBegin(); 
       it !=aMesh.faceEnd(); 
       it++){
    nb++;    
  }
  okMeshIterators = okMeshIterators && (nb == aMesh.nbFaces());
  if (nb == aMesh.nbFaces())
    trace.info() << "face iteration test ok"<<std::endl;
  
  nb=0;
  // just testing nb iterations on const iterator
  for(  Mesh<Point>::FaceStorage::iterator it = aMesh.faceBegin(); 
       it !=aMesh.faceEnd(); 
       it++){
    nb++;
  }
  okMeshIterators =  okMeshIterators && ((nb == aMesh.nbFaces()) &&  ((aMesh.getVertex(5))[0]==13)) && aMesh.getFaceBarycenter(0)==Mesh<Point>::RealPoint(31.0/3.0,6.0);
  if ((nb == aMesh.nbFaces()) &&  (aMesh.getVertex(5))[0]==13 && aMesh.getFaceBarycenter(0)==Mesh<Point>::RealPoint(31.0/3.0,6.0))
    trace.info() << "getVertex and getFaceCenter tests ok"<<std::endl;
  
  // testing changing color of individual face:
  aMesh.setFaceColor(1, DGtal::Color::Red);
  bool okMeshColor = (aMesh.getFaceColor(0)==DGtal::Color::White)
                     && (aMesh.getFaceColor(1)==DGtal::Color::Red) ;
  
  trace.endBlock();
  
  trace.beginBlock ( "Testing Mesh Bouding box and scale change  ..." );
  aMesh.changeScale(2.0);
  std::pair<Point, Point> bb = aMesh.getBoundingBox();
  bool boundingBoxOK = (bb.first == Point(20,10)) && (bb.second == Point(26,18));
  trace.info() << "bouding box=" << bb.first <<  " " << bb.second << "(should be (20,10) (26,18)" <<std::endl;
  trace.endBlock();
  trace.beginBlock ( "Testing mesh subdivision  ..." );
  Mesh<RealPoint> aMeshR;
  RealPoint pr0 (0,0);
  RealPoint pr1 (1,0);
  RealPoint pr2 (1,1);
  aMeshR.addVertex(pr0);   aMeshR.addVertex(pr1);   aMeshR.addVertex(pr2);
  aMeshR.addTriangularFace(0,1,2);
  aMeshR.subDivideTriangularFaces(0.5); 

  trace.info() << "nb vertex after subdivision: " << aMeshR.nbVertex() << std::endl;
  trace.info() << "nb faces after subdivision: " << aMeshR.nbFaces() << std::endl;  
  trace.info() << "New point: " << aMeshR.getVertex(aMeshR.nbVertex()-1) << std::endl;    
  bool okSubDivide =  aMeshR.nbVertex()==4 && aMeshR.nbFaces()==3 && 
                      aMeshR.getVertex(aMeshR.nbVertex()-1) == RealPoint(2.0/3.0, 1.0/3.0);
  trace.endBlock();

  trace.beginBlock ( "Testing mesh quad transform  ..." );
  Mesh<RealPoint> aMeshQ;
  RealPoint pq0 (0,0);
  RealPoint pq1 (1,0);
  RealPoint pq2 (1,1);
  RealPoint pq3 (0,1);
  aMeshQ.addVertex(pq0);   aMeshQ.addVertex(pq1);   aMeshQ.addVertex(pq2);
  aMeshQ.addVertex(pq3);
  aMeshQ.addQuadFace(0,1,2,3);
  aMeshQ.quadToTriangularFaces(); 

  trace.info() << "nb faces after quad to triangle transform: " << aMeshQ.nbFaces() << std::endl;  
  bool okQuadToTrans =  aMeshQ.nbFaces() == 2;
  trace.endBlock();


  trace.beginBlock ( "Testing Mesh copy operator  ..." );
  Mesh<Point> aMesh2 = aMesh;
  Mesh<Point> aMesh3 (aMesh2);
  bool okMeshCopy = aMesh.nbFaces() == aMesh2.nbFaces() && aMesh.nbVertex() == aMesh2.nbVertex() &&
                    aMesh.nbFaces() == aMesh3.nbFaces() && aMesh.nbVertex() == aMesh3.nbVertex() &&
                    aMesh.getVertex(0) == aMesh2.getVertex(0) && aMesh.getVertex(0) == aMesh3.getVertex(0);
  trace.endBlock();

  trace.beginBlock ( "Testing face removing  ..." );
  Mesh<Point> aMesh4 = aMesh;
  std::vector<unsigned int> f = {1};
  aMesh4.removeFaces(f);
  bool okRemoveFace = (aMesh4.nbFaces() == aMesh.nbFaces()-1) && (aMesh4.nbVertex() == aMesh.nbVertex()-3);
  
  
  ok = ok & okMeshConstruct &&  okMeshIterators && okMeshColor && okMeshCopy && boundingBoxOK &&
       okSubDivide && okQuadToTrans && okRemoveFace;
  trace.endBlock();
  return ok;

}



/**
 * Test mesh generation from static fonctions.
 */
bool testMeshGeneration()
{
  
  trace.beginBlock ( "Testing Mesh generation  ..." );
  bool ok = true;

  trace.beginBlock ( "Testing Tube generation  ..." );
  //! [testMeshCreateSkeleton]
  std::vector<Z3i::RealPoint> aSkeleton;  
  aSkeleton.push_back(Z3i::RealPoint(0.0, 0.0, 0.0));
  aSkeleton.push_back(Z3i::RealPoint(10.0, 0.0, 0.0));
  aSkeleton.push_back(Z3i::RealPoint(20.0, 0.0, 0.0));
  aSkeleton.push_back(Z3i::RealPoint(30.0, 0.0, 0.0));  
  aSkeleton.push_back(Z3i::RealPoint(35.0, 5.0, 0.0));  
  aSkeleton.push_back(Z3i::RealPoint(40.0, 10.0, 0.0));  
  aSkeleton.push_back(Z3i::RealPoint(40.0, 20.0, 0.0));  
  aSkeleton.push_back(Z3i::RealPoint(40.0, 30.0, 0.0));  
  aSkeleton.push_back(Z3i::RealPoint(40.0, 35.0, 5.0));  
  aSkeleton.push_back(Z3i::RealPoint(40.0, 40.0, 10.0));  
  aSkeleton.push_back(Z3i::RealPoint(40.0, 40.0, 20.0));  
  //! [testMeshCreateSkeleton]

  //! [testMeshCreateTubeMesh]  
  Mesh<Z3i::RealPoint> aMesh(true);
  Mesh<Z3i::RealPoint>::createTubularMesh(aMesh, aSkeleton, 0.5, 0.2, DGtal::Color::Blue);
  //! [testMeshCreateTubeMesh]  

  trace.endBlock();
  trace.info() << "Nb faces: "<< aMesh.nbFaces() << " (sould be 320)" << std::endl;
  trace.info() << "Nb vertices: "<< aMesh.nbVertex() << " (sould be 352)" << std::endl;
  bool okMeshTube1 = aMesh.nbFaces() == 320 && aMesh.nbVertex() == 352;

  trace.beginBlock ( "Testing Tube generation (bis with variable raidii  ..." );
  Mesh<Z3i::RealPoint> aMeshBis(true);
  std::vector<double> vectRadii; 
  vectRadii.push_back(0.5);
  vectRadii.push_back(1.5);
  vectRadii.push_back(2.5);
  Mesh<Z3i::RealPoint>::createTubularMesh(aMeshBis, aSkeleton, vectRadii, 0.2, DGtal::Color::Green);
  
  trace.endBlock();
  trace.info() << "Nb faces: "<< aMeshBis.nbFaces() << " (sould be 320)" << std::endl;
  trace.info() << "Nb vertices: "<< aMeshBis.nbVertex() << " (sould be 352)" << std::endl;
  
  std::ofstream ofbis ("tubeVariableRadiiGeneratedFromTestMesh.off"); 
  DGtal::MeshWriter<Z3i::RealPoint>::export2OFF(ofbis, aMeshBis, true);
  ofbis.close();
  bool okMeshTube1bis = aMeshBis.nbFaces() == 320 && aMeshBis.nbVertex() == 352;
  

  trace.beginBlock("Testing Mesh from Height sequence");
  //! [testMeshCreateHeightSequence]
  std::vector<double> heightSequence;
  heightSequence.push_back(0.1); 
  heightSequence.push_back(0.2); 
  heightSequence.push_back(0.15);

  heightSequence.push_back(1.1); 
  heightSequence.push_back(2.2); 
  heightSequence.push_back(1.15);

  heightSequence.push_back(0.1); 
  heightSequence.push_back(0.2); 
  heightSequence.push_back(0.15);
  //! [testMeshCreateHeightSequence]
  
  //! [testMeshCreateSequenceMesh]  
  Mesh<Z3i::RealPoint>::createMeshFromHeightSequence(aMesh, heightSequence, 3, 10, 10, 3, DGtal::Color::Yellow);
  //! [testMeshCreateSequenceMesh]  
  
  trace.info() << "Nb faces: "<< aMesh.nbFaces() << " (sould be 324)" << std::endl;
  trace.info() << "Nb vertices: "<< aMesh.nbVertex() << " (sould be 361)" << std::endl;
  bool okMeshTube1AndHF = aMesh.nbFaces() == 324 && aMesh.nbVertex() == 361;
  
  //! [testMeshExport]  
  std::ofstream of ("tubeAndHeighFieldGeneratedFromTestMesh.off"); 
  DGtal::MeshWriter<Z3i::RealPoint>::export2OFF(of, aMesh, true);
  of.close();
  //! [testMeshExport]  
  
  ok = ok & okMeshTube1 & okMeshTube1bis & okMeshTube1AndHF;  
  trace.endBlock();
  return ok;
}



/**
 * Test the mesh object construction.
 */
bool testVisualTubularMesh()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock("Testing visual tubular mesh generation (shell mesh):");
  // Generate the center line:
  std::vector<Z3i::RealPoint> centerline;
  unsigned int nbPoints = 0;
  double z = 0.0;
  double radiusSpirale = 13.0;
  double radiusTube = 15.0;
  double alphaMax = 32.0;
  double reduc = 0.05;
  for (double alpha = 0; alpha< alphaMax; alpha += 0.1, z += 0.5-reduc)
    {
      centerline.push_back(Z3i::RealPoint(radiusSpirale*cos(alpha), radiusSpirale*sin(alpha), z  ));
      nbPoints++;
      radiusSpirale -=reduc;
      radiusSpirale = std::max(radiusSpirale, 0.0);
    }    
  // Generate radius:
  std::vector<double> vectRadius;
  for(unsigned int i=0; i<nbPoints; i++)
    {
      vectRadius.push_back(radiusTube);
      radiusTube -=reduc;
      radiusTube = std::max(radiusTube, 0.0);
    }  

  DGtal::Mesh<Z3i::RealPoint> theMeshShell(true);
  DGtal::Mesh<Z3i::RealPoint>::createTubularMesh(theMeshShell, centerline, vectRadius, 0.1);
  
  trace.info() << "Mesh generated with " << theMeshShell.nbFaces()
               << " faces (should be " << (centerline.size()-1)*63 << " )" << std::endl;
  nb++;
  nbok +=  theMeshShell.nbFaces() == (centerline.size()-1)*63;
  theMeshShell >> "spiraleGeneratedFromTestMesh.off";  
  trace.info() << " [done]" << std::endl;
  trace.endBlock();



  trace.beginBlock("Testing visual tubular mesh generation (tube mesh):");
  std::vector<Z3i::RealPoint> centerLine2;
  centerLine2.push_back(Z3i::RealPoint(0.0,0.0,0.0));
  centerLine2.push_back(Z3i::RealPoint(3.3,0.0,0.0));
  centerLine2.push_back(Z3i::RealPoint(6.6,0.0,0.0));
  centerLine2.push_back(Z3i::RealPoint(10.0,0.0,0.0));
  centerLine2.push_back(Z3i::RealPoint(13.3,0.0,0.0));
  centerLine2.push_back(Z3i::RealPoint(16.6,0.0,0.0));
  centerLine2.push_back(Z3i::RealPoint(20.0,0.0,0.0));
  centerLine2.push_back(Z3i::RealPoint(60.0,0.0,0.0));
  centerLine2.push_back(Z3i::RealPoint(63.3,0.0,0.0));
  centerLine2.push_back(Z3i::RealPoint(66.6,0.0,0.0));
  centerLine2.push_back(Z3i::RealPoint(70.0,0.0,0.0));
  centerLine2.push_back(Z3i::RealPoint(71.7,0.1,0.0));
  centerLine2.push_back(Z3i::RealPoint(73.4,0.6,0.0));
  centerLine2.push_back(Z3i::RealPoint(75.0,1.3,0.0));
  centerLine2.push_back(Z3i::RealPoint(76.4,2.3,0.0));
  centerLine2.push_back(Z3i::RealPoint(77.6,3.5,0.0));
  centerLine2.push_back(Z3i::RealPoint(78.6,5.0,0.0));
  centerLine2.push_back(Z3i::RealPoint(79.3,6.5,0.0));
  centerLine2.push_back(Z3i::RealPoint(79.8,8.2,0.0));
  centerLine2.push_back(Z3i::RealPoint(80.0,10.0,0.0));
  centerLine2.push_back(Z3i::RealPoint(80.0,13.8,0.0));
  centerLine2.push_back(Z3i::RealPoint(80.0,86.1,0.0));
  centerLine2.push_back(Z3i::RealPoint(80.0,90.0,0.0));
  centerLine2.push_back(Z3i::RealPoint(80.1,91.7,-0.1));
  centerLine2.push_back(Z3i::RealPoint(80.6,93.4,0.1));
  centerLine2.push_back(Z3i::RealPoint(81.3,95.0,0.1));
  centerLine2.push_back(Z3i::RealPoint(82.3,96.4,-0.1));
  centerLine2.push_back(Z3i::RealPoint(83.5,97.6,-0.1));

  DGtal::Mesh<Z3i::RealPoint> theMeshTube(true);
  DGtal::Mesh<DGtal::Z3i::RealPoint>::createTubularMesh(theMeshTube, centerLine2,
                                                        5.0, 0.2, DGtal::Color::Blue);
  
  trace.info() << "Mesh generated with " << theMeshTube.nbFaces() << " faces (should be "
               << (centerLine2.size()-1)*32 << " )" << std::endl; 
  nb++;
  nbok +=  theMeshTube.nbFaces() == (centerLine2.size()-1)*32;

  theMeshTube >> "tubeGeneratedFromTestMesh.off";  
  trace.endBlock();
  
  return nb == nbok;

}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class Mesh" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testMesh() && testMeshGeneration() && testVisualTubularMesh(); 
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
