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
 * @file testSurfaceHelper.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2014/04/07
 *
 * Functions for testing class SurfaceHelper.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/curves/FreemanChain.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/topology/SurfelSetPredicate.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/base/ConstAlias.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::functors;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class SurfaceHelper.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */



bool testComputeInterior()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  typedef SpaceND<2, int> Space;
  typedef KhalimskySpaceND<2, int> KSpace;
  typedef HyperRectDomain< Space > Domain;
  typedef KSpace::SCell SCell;
  typedef KSpace::Point Point;
  typedef ImageContainerBySTLMap< Domain, bool> BoolImage2D;


  trace.beginBlock ( "Testing computation of interior from a freeman chain ..." );
  std::string freemanChainFilename = testPath + "samples/contourS.fc";
  std::string freemanChainFilename2 = testPath + "samples/SmallBall.fc";
  fstream fst;
  fst.open (freemanChainFilename.c_str(), ios::in);
  FreemanChain<Space::Integer> fc(fst);
  fst.close();
  fst.open (freemanChainFilename2.c_str(), ios::in);
  FreemanChain<Space::Integer> fc2(fst);
  fst.close();
  std::set<SCell> boundaryCell;
  std::set<SCell> boundaryCell2;
  KSpace K, Ko;

  int minx, miny, maxx, maxy;
  fc.computeBoundingBox(minx, miny, maxx, maxy);

  BoolImage2D::Domain dom(Point(minx-5,miny-5), Point(maxx+5, maxy+5));
  trace.info() << "Domain defined by :" << dom.lowerBound() << " " << dom.upperBound() << std::endl;
  K.init(dom.lowerBound(), dom.upperBound(), true);
  Ko.init(dom.lowerBound(), dom.upperBound(), false);
  FreemanChain<Space::Integer>::getInterPixelLinels(K, fc, boundaryCell );

  BoolImage2D interiorImage(dom);
  unsigned int nbInt = Surfaces<KSpace>::uFillInterior(K, SurfelSetPredicate<std::set<SCell>, SCell>(boundaryCell),
                                                                                   interiorImage, 1, false);
  trace.info() << "Interior size: " << nbInt << " (awaited:  3082)" <<  std::endl;

  BoolImage2D exteriorImage(dom);
  unsigned int nbExt = Surfaces< KSpace >::uFillExterior(K ,SurfelSetPredicate<std::set<SCell>, SCell>(boundaryCell),
                                                                                   exteriorImage, 1, true);
  unsigned int nbExto = Surfaces< KSpace >::uFillExterior(Ko ,SurfelSetPredicate<std::set<SCell>, SCell>(boundaryCell),
                                                                                    exteriorImage, 1, true);
  trace.info() << "Exterior size: (KhalimskySpaceND open) " << nbExto << " (awaited:   9182)" <<  std::endl;
  trace.info() << "Exterior size: (KhalimskySpaceND close)" << nbExt << " (awaited:   9182)" <<  std::endl;


  KSpace K2, K2c;
  int minx2, miny2, maxx2, maxy2;
  fc2.computeBoundingBox(minx2, miny2, maxx2, maxy2);
  BoolImage2D::Domain dom2(Point(minx2-5,miny2-5), Point(maxx2+5, maxy2+5));
  K2.init(dom2.lowerBound(), dom2.upperBound(), false);
  K2c.init(dom2.lowerBound(), dom2.upperBound(), true);
  FreemanChain<Space::Integer>::getInterPixelLinels(K2, fc2, boundaryCell2 );

  BoolImage2D interiorImage2(dom2);
  unsigned int nbInt2 = Surfaces< KSpace >::uFillInterior(K2, SurfelSetPredicate<std::set<SCell>,SCell>(boundaryCell2),
                                                                                    interiorImage2, 1, false);
 trace.info() << "Interior size2: (KhalimskySpaceND open) " << nbInt2 << " (awaited:  196316)" <<  std::endl;
 unsigned int nbInt2c = Surfaces< KSpace >::uFillInterior(K2c, SurfelSetPredicate<std::set<SCell>,SCell>(boundaryCell2),
                                                                                    interiorImage2, 1, false);
 trace.info() << "Interior size2: (KhalimskySpaceND closed) " << nbInt2c << " (awaited:  196316)" <<  std::endl;

  // Displaying interiorCell
  Board2D aBoard, aBoard2, aBoard3;

  for( BoolImage2D::Domain::ConstIterator it = interiorImage.domain().begin();  it!= interiorImage.domain().end(); ++it){
    if(interiorImage(*it)){
      aBoard << *it;
    }
  }

  for( BoolImage2D::Domain::ConstIterator it = exteriorImage.domain().begin();  it!= exteriorImage.domain().end(); it++){
    if(exteriorImage(*it)){
      aBoard3 << *it;
    }
  }

  for( BoolImage2D::Domain::ConstIterator it = interiorImage2.domain().begin();  it!= interiorImage2.domain().end(); it++){
    if(interiorImage2(*it)){
      aBoard2 << *it;
    }
  }

  aBoard<< CustomStyle( (*(boundaryCell.begin())).className(),
                        new CustomColors(  Color::Red,  Color::None ) );
  aBoard3<< CustomStyle( (*(boundaryCell.begin())).className(),
                        new CustomColors(  Color::Red,  Color::None ) );
  aBoard2<< CustomStyle( (*(boundaryCell.begin())).className(),
                        new CustomColors(  Color::Red,  Color::None ) );
  for( std::set<SCell>::const_iterator it= boundaryCell.begin();  it!= boundaryCell.end(); it++){
    aBoard << *it;
    aBoard3 << *it;
  }

  for( std::set<SCell>::const_iterator it= boundaryCell2.begin();  it!= boundaryCell2.end(); it++){
    aBoard2 << *it;
  }

  aBoard << CustomStyle( fc.className(),
                        new CustomColors(  Color::Red,  Color::None ) );
  aBoard3 << CustomStyle( fc.className(),
                        new CustomColors(  Color::Red,  Color::None ) );
  aBoard2 << CustomStyle( fc.className(),
                        new CustomColors(  Color::Red,  Color::None ) );
  aBoard << SetMode( fc.className(), "InterGrid" );
  aBoard3 << SetMode( fc.className(), "InterGrid" );
  aBoard2 << SetMode( fc.className(), "InterGrid" );
  aBoard << fc;
  aBoard3 << fc;
  aBoard2 << fc2;

  aBoard.saveEPS("testSurfaceHelperComputeInterior.eps");
  aBoard3.saveEPS("testSurfaceHelperComputeExterior.eps");
  aBoard2.saveEPS("testSurfaceHelperComputeInterior2.eps");
  nbok += (nbInt == 3082 && nbInt2 == 196316 && nbInt2c == 196316 && nbExt== 9182 && nbExto== 9182)? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << nbInt << " (interiorCell.size()) == 3014 and "
               << nbInt2 << " (interiorCell2.size()) == 60196 "
               << std::endl;
  trace.endBlock();

  return nbok == nb;
}


bool
test3dSurfaceHelper()
{
  typedef DGtal::DigitalSetBySTLSet<DGtal::Z3i::Domain> Set;
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing extraction of 3D connected component ..." );
  // import point from a vol file
  typedef ImageContainerBySTLVector< Z3i::Domain, unsigned char> Image3dChar;
  Image3dChar image = VolReader<Image3dChar>::importVol( testPath + "samples/cat10.vol");
  Set aSet(image.domain());
   for(auto const &p: image.domain())
     {
      if(image(p)>0)
        {
          aSet.insert(p);
        }
     }
   Z3i::KSpace Kc;
   Kc.init(image.domain().lowerBound(),
          image.domain().upperBound(), true);
   SurfelAdjacency<3> SAdj( false );
   std::vector<std::vector<DGtal::Z3i::SCell> > vectConnectedSCell;
   Surfaces<DGtal::Z3i::KSpace>::extractAllConnectedSCell(vectConnectedSCell,Kc, SAdj, aSet, false);
   nb++;
   nbok += vectConnectedSCell.size()==1;
   trace.info() << "Connected component :" << vectConnectedSCell.size() << " (should be 1) "  << std::endl;
   trace.endBlock();

   trace.beginBlock("Test 3D filling interior of surface (in an closed KhalimskySpaceND ) ...");
   Image3dChar imageFilled(image.domain());
   std::set<Z3i::SCell> setSCell; for (auto const &s: vectConnectedSCell[0]) setSCell.insert(s);
   functors::SurfelSetPredicate<std::set<Z3i::SCell>,Z3i::SCell> surfacePred (setSCell);

   unsigned int nbFilled = DGtal::Surfaces<DGtal::Z3i::KSpace>::uFillInterior(Kc, surfacePred, imageFilled, 1);
   trace.info() << "Nb voxel filled:" << nbFilled << " (should be " << aSet.size() << " )"  << std::endl;
   nb++;
   nbok += nbFilled == aSet.size();
   trace.endBlock();


   trace.beginBlock("Test 3D filling interior of surface (in an open  KhalimskySpaceND ) ...");
   Z3i::KSpace ko;
   ko.init(image.domain().lowerBound(),
           image.domain().upperBound(), false);
   unsigned int nbFilled2 = DGtal::Surfaces<DGtal::Z3i::KSpace>::uFillInterior(ko, surfacePred, imageFilled, 1);
   trace.info() << "Nb voxel filled:" << nbFilled2 << " (should be " << aSet.size() << " )"  << std::endl;
   nb++;
   nbok += nbFilled2 == aSet.size();
   trace.endBlock();


   trace.beginBlock("Test 3D filling exterior of surface (in an closed KhalimskySpaceND ) ...");
   unsigned int nbFilled3 = DGtal::Surfaces<DGtal::Z3i::KSpace>::uFillExterior(Kc, surfacePred, imageFilled, 1);
   trace.info() << "Nb voxel filled:" << nbFilled3 << " (should be " << aSet.size() << " )"  << std::endl;
   nb++;
   nbok += nbFilled3 == imageFilled.size()-aSet.size();
   trace.endBlock();



   trace.beginBlock("Test 3D filling exterior of surface (in an open  KhalimskySpaceND ) ...");
   unsigned int nbFilled4 = DGtal::Surfaces<DGtal::Z3i::KSpace>::uFillExterior(ko, surfacePred, imageFilled, 1);
   trace.info() << "Nb voxel filled:" << nbFilled4 << " (should be " << aSet.size() << " )"  << std::endl;
   nb++;
   nbok += nbFilled4 == imageFilled.size()-aSet.size();
   trace.endBlock();




  return nb == nbok;
}


/**
* Checks that method Surfaces::findABel can take in argument any pair
* of points (one inside, one outside) to determine a boundary surfel
* by dichotomy.
*/
template <typename KSpace3D>
bool testFindABel()
{
  typedef KSpace3D                   KSpace;
  typedef typename KSpace::Space     Space;
  typedef typename KSpace::Point     Point;
  typedef typename KSpace::SCell     SCell;
  typedef HyperRectDomain<Space>     Domain;
  typedef DigitalSetBySTLSet<Domain> DigitalSet;
  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing Surfaces::findABel." );
  Point pts[ 8 ];
  Point p1( -5, -5, -5 );
  Point p2(  5,  5,  5 );
  pts[ 0 ] = p1;
  pts[ 1 ] = p2;
  pts[ 2 ] = Point(  5, -5, -5 );
  pts[ 3 ] = Point( -5,  5, -5 );
  pts[ 4 ] = Point(  5,  5, -5 );
  pts[ 5 ] = Point( -5, -5,  5 );
  pts[ 6 ] = Point(  5, -5,  5 );
  pts[ 7 ] = Point( -5,  5,  5 );
  KSpace K; K.init( p1, p2, true );
  Domain domain( p1, p2 );
  DigitalSet aSet( domain );
  Shapes<Domain>::addNorm2Ball( aSet, Point::zero, 2 );
  for ( unsigned int i = 0; i < 8; ++i )
    {
      SCell bel = Surfaces<KSpace>::findABel( K, aSet, pts[ i ], Point::zero );
      trace.info() << "- Exterior point is " << pts[ i ] << std::endl;
      trace.info() << "  - Found bel = " << bel << std::endl;
      ++nb; nbok += K.sDim( bel ) == 2;
      trace.info() << "(" << nbok << "/" << nb << ") "
                   << " K.sDim( bel ) == " <<  K.sDim( bel ) << " (should be 2)" << std::endl;
      SCell vox_in = K.sDirectIncident( bel, K.sOrthDir( bel ) );
      SCell vox_out = K.sIndirectIncident( bel, K.sOrthDir( bel ) );
      ++nb; nbok += aSet( K.sCoords( vox_in ) ) ? 1 : 0;
      trace.info() << "(" << nbok << "/" << nb << ") "
                   << " vox_in should be inside the shape." << std::endl;
      ++nb; nbok += aSet( K.sCoords( vox_out ) ) ? 0 : 1;
      trace.info() << "(" << nbok << "/" << nb << ") "
                   << " vox_out should be outside the shape." << std::endl;
    }
  return nbok == nb;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class SurfaceHelper" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testComputeInterior()
    && testFindABel< KhalimskySpaceND<3,int> >()  && test3dSurfaceHelper();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
