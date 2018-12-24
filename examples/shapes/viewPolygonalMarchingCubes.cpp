/**
 * @file shapes/viewPolygonalMarchingCubes.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * An example file named viewPolygonalMarchingCubes to display an isosurface from a vol file.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
//! [viewPolygonalMarchingCubes-basicIncludes]
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
#include "DGtal/shapes/PolygonalSurface.h"
#include "DGtal/shapes/MeshHelpers.h"
#include "DGtal/io/viewers/Viewer3D.h"
//! [viewPolygonalMarchingCubes-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////

void usage( int, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <fileName.vol> <minT> <maxT> <Adj>" << std::endl;
  std::cerr << "\t - displays the boundary of the shape stored in vol file <fileName.vol>" << std::endl;
  std::cerr << "\t   as a Marching-Cube triangulated surface (more precisely a dual" << std::endl;
  std::cerr << "\t   surface to the digital boundary)." << std::endl;
  std::cerr << "\t - voxel v belongs to the shape iff its value I(v) follows minT <= I(v) <= maxT." << std::endl;
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
  unsigned int maxThreshold = atoi( argv[ 3 ] );
  bool intAdjacency = atoi( argv[ 4 ] ) == 0;

  typedef ImageSelector < Domain, int>::Type Image;
      
  //! [viewPolygonalMarchingCubes-readVol]
  trace.beginBlock( "Reading vol file into an image." );
  Image image = VolReader<Image>::importVol(inputFilename);
  DigitalSet set3d (image.domain());
  SetFromImage<DigitalSet>::append<Image>(set3d, image,
                                          minThreshold, maxThreshold);
  trace.endBlock();
  //! [viewPolygonalMarchingCubes-readVol]


  //! [viewPolygonalMarchingCubes-KSpace]
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
  //! [viewPolygonalMarchingCubes-KSpace]

  //! [viewPolygonalMarchingCubes-SurfelAdjacency]
  typedef SurfelAdjacency<KSpace::dimension> MySurfelAdjacency;
  MySurfelAdjacency surfAdj( intAdjacency ); // interior in all directions.
  //! [viewPolygonalMarchingCubes-SurfelAdjacency]

  //! [viewPolygonalMarchingCubes-ExtractingSurface]
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
  //! [viewPolygonalMarchingCubes-ExtractingSurface]

  //! [viewPolygonalMarchingCubes-makingMesh]
  trace.beginBlock( "Making triangulated surface. " );
  typedef CanonicEmbedder< Space >                                  TrivialEmbedder;
  typedef ImageLinearCellEmbedder< KSpace, Image, TrivialEmbedder > CellEmbedder;
  typedef CellEmbedder::Value                                       RealPoint;
  typedef PolygonalSurface< RealPoint >                             PolygonMesh;
  typedef Mesh< RealPoint >                                         ViewMesh;
  typedef std::map< MyDigitalSurface::Vertex, PolygonMesh::Index >  VertexMap;
  PolygonMesh     polymesh;
  ViewMesh        viewmesh;
  TrivialEmbedder trivialEmbedder;
  CellEmbedder    cellEmbedder;
  // The +0.5 is to avoid isosurface going exactly through a voxel
  // center, especially for binary volumes.
  cellEmbedder.init( ks, image, trivialEmbedder, 
                     ( (double) minThreshold ) + 0.5 );
  VertexMap vmap; // stores the map Vertex -> Index
  MeshHelpers::digitalSurface2DualPolygonalSurface
    ( digSurf, cellEmbedder, polymesh, vmap );
  trace.info() << "Polygonal surface is " << polymesh << std::endl;
  MeshHelpers::polygonalSurface2Mesh( polymesh, viewmesh );
  trace.info() << "Mesh has " << viewmesh.nbVertex()
               << " vertices and " << viewmesh.nbFaces() << " faces." << std::endl;
  trace.endBlock();
  //! [viewPolygonalMarchingCubes-makingMesh]

  QApplication application(argc,argv);
  Viewer3D<> viewer;
  viewer.show();
  viewer.setLineColor(Color(150,0,0,254));
  viewer << viewmesh;
  viewer << Viewer3D<>::updateDisplay;
  application.exec();
  
}

