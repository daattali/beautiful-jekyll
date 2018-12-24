/**
 * @file shapes/viewMarchingCubes.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * An example file named viewMarchingCubes to display an isosurface from a vol file.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
//! [viewMarchingCubes-basicIncludes]
#include <iostream>
#include <queue>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CanonicEmbedder.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/images/ImageLinearCellEmbedder.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/SetOfSurfels.h"
#include "DGtal/shapes/Mesh.h"
#include "DGtal/shapes/TriangulatedSurface.h"
#include "DGtal/shapes/MeshHelpers.h"
#include "DGtal/io/viewers/Viewer3D.h"
//! [viewMarchingCubes-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////

void usage( int, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <fileName.vol> <minT> [<maxT>=255] [<Adj>=0]" << std::endl;
  std::cerr << "\t - displays the boundary of the shape stored in vol file <fileName.vol>" << std::endl;
  std::cerr << "\t   as a Marching-Cube triangulated surface (more precisely a dual" << std::endl;
  std::cerr << "\t   surface to the digital boundary)." << std::endl;
  std::cerr << "\t - voxel v belongs to the shape iff its value I(v) follows minT < I(v) <= maxT." << std::endl;
  std::cerr << "\t - minT is the iso-surface level." << std::endl;
  std::cerr << "\t - maxT should be equal to the maximum possible value in the image." << std::endl;
  std::cerr << "\t - 0: interior adjacency, 1: exterior adjacency (rules used to connect surface elements unambiguously)." << std::endl;
}

int main( int argc, char** argv )
{
  if ( argc < 5 )
    {
      usage( argc, argv );
      return 1;
    }
  std::string inputFilename = argv[ 1 ];
  unsigned int minThreshold = atoi( argv[ 2 ] );
  unsigned int maxThreshold = argc > 3 ? atoi( argv[ 3 ] ) : 255;
  bool intAdjacency = argc > 4 ? (atoi( argv[ 4 ] ) == 0) : true;

  typedef ImageSelector < Domain, int>::Type Image;
      
  //! [viewMarchingCubes-readVol]
  trace.beginBlock( "Reading vol file into an image." );
  Image image = VolReader<Image>::importVol(inputFilename);
  DigitalSet set3d (image.domain());
  SetFromImage<DigitalSet>::append<Image>(set3d, image,
                                          minThreshold, maxThreshold);
  trace.endBlock();
  //! [viewMarchingCubes-readVol]


  //! [viewMarchingCubes-KSpace]
  trace.beginBlock( "Construct the Khalimsky space from the image domain." );
  KSpace ks;
  bool space_ok = ks.init( image.domain().lowerBound(),
                           image.domain().upperBound(), true );
  if (!space_ok)
    {
      trace.error() << "Error in the Khamisky space construction."<<std::endl;
      return 2;
    }
  trace.endBlock();
  //! [viewMarchingCubes-KSpace]

  //! [viewMarchingCubes-SurfelAdjacency]
  typedef SurfelAdjacency<KSpace::dimension> MySurfelAdjacency;
  MySurfelAdjacency surfAdj( intAdjacency ); // interior in all directions.
  //! [viewMarchingCubes-SurfelAdjacency]

  //! [viewMarchingCubes-ExtractingSurface]
  trace.beginBlock( "Extracting boundary by scanning the space. " );
  typedef KSpace::SurfelSet SurfelSet;
  typedef SetOfSurfels< KSpace, SurfelSet > MySetOfSurfels;
  typedef DigitalSurface< MySetOfSurfels > MyDigitalSurface;
  MySetOfSurfels theSetOfSurfels( ks, surfAdj );
  Surfaces<KSpace>::sMakeBoundary( theSetOfSurfels.surfelSet(),
                                   ks, set3d,
                                   image.domain().lowerBound(),
                                   image.domain().upperBound() );
  MyDigitalSurface digSurf( theSetOfSurfels );
  trace.info() << "Digital surface has " << digSurf.size() << " surfels."
               << std::endl;
  trace.endBlock();
  //! [viewMarchingCubes-ExtractingSurface]

  //! [viewMarchingCubes-makingMesh]
  trace.beginBlock( "Making triangulated surface. " );
  typedef CanonicEmbedder< Space >                                  TrivialEmbedder;
  typedef ImageLinearCellEmbedder< KSpace, Image, TrivialEmbedder > CellEmbedder;
  typedef CellEmbedder::Value                                       RealPoint;
  typedef TriangulatedSurface< RealPoint >                          TriMesh;
  typedef Mesh< RealPoint >                                         ViewMesh;
  typedef std::map< MyDigitalSurface::Vertex, TriMesh::Index >      VertexMap;
  TriMesh         trimesh;
  ViewMesh        viewmesh;
  TrivialEmbedder trivialEmbedder;
  CellEmbedder    cellEmbedder;
  // The +0.5 is to avoid isosurface going exactly through a voxel
  // center, especially for binary volumes.
  cellEmbedder.init( ks, image, trivialEmbedder, 
                     ( (double) minThreshold ) + 0.5 );
  VertexMap vmap; // stores the map Vertex -> Index
  MeshHelpers::digitalSurface2DualTriangulatedSurface
    ( digSurf, cellEmbedder, trimesh, vmap );
  trace.info() << "Triangulated surface is " << trimesh << std::endl;
  MeshHelpers::triangulatedSurface2Mesh( trimesh, viewmesh );
  trace.info() << "Mesh has " << viewmesh.nbVertex()
               << " vertices and " << viewmesh.nbFaces() << " faces." << std::endl;
  trace.endBlock();
  //! [viewMarchingCubes-makingMesh]

  QApplication application(argc,argv);
  Viewer3D<> viewer;
  viewer.show();
  viewer.setLineColor(Color(150,0,0,254));
  viewer << viewmesh;
  viewer << Viewer3D<>::updateDisplay;
  application.exec();
  
}

