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
 * @file topology/ctopo-fillContours.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2014/06/16
 *
 * An example file named ctopo-fillContours.
 *
 * This file is part of the DGtal library.
 */

/**
 *   A simple example illustrating the filling of the
 *   interior/exterior of a given 2D contour. This program outputs
 *   these images:
 *
 * @see \ref dgtal_helpsurf_sec4
 * 
 * @image html ctopo-fillContours.png 
 * \example  topology/ctopo-fillContours.cpp
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ConfigExamples.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/topology/SurfelSetPredicate.h"
#include "DGtal/geometry/curves/FreemanChain.h"
#include "DGtal/io/boards/Board2D.h"


///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int /*argc*/, char** /*argv*/ )
{
  trace.beginBlock ( "Example ctopo-fillContours" );
  DGtal::KhalimskySpaceND< 2, int > K; 
  K.init(Z2i::Point(0, 10),  Z2i::Point(20, 30), false);
  
  // We choose a direct and indirect oriented contour.
  //! [ctopoFillContoursInit]
  FreemanChain<int> fc1 ("001001001001001111101111011222222223222222322233333330301033333003", 6, 14);
  FreemanChain<int> fc2 ("1111000033332222", 6, 20);  
  //! [ctopoFillContoursInit]
  
  Board2D aBoard;
  Board2D aBoard2;
  aBoard << K.lowerBound() << K.upperBound() ;
  aBoard2 << K.lowerBound() << K.upperBound() ;
    
  //From the FreemanChain we can get a vector of SCell wrapped in a SurfelSetPredicate with sign defined from the FreemanChain orientation:
  //! [ctopoFillContoursGetSCells]
  
  typedef  KhalimskySpaceND<2, int>::SCell SCell;
  std::set<DGtal::KhalimskySpaceND< 2, int >::SCell> boundarySCell;
  FreemanChain<int>::getInterPixelLinels(K, fc1, boundarySCell, false); 
  //! [ctopoFillContoursGetSCells]
  
  aBoard << CustomStyle((*boundarySCell.begin()).className(),  new CustomColors(DGtal::Color::Red, DGtal::Color::Red) );
  for( std::set<DGtal::KhalimskySpaceND< 2, int >::SCell>::const_iterator it= boundarySCell.begin();  
       it!= boundarySCell.end(); it++){
    aBoard << *it;
  }
  
  // We can also add other freeman chains with indirect orientation to construct a hole in interior of the shape:
  //! [ctopoFillContoursGetSCellsHole]
  std::set<DGtal::KhalimskySpaceND< 2, int >::SCell> boundarySCellhole;
  FreemanChain<int>::getInterPixelLinels(K, fc2, boundarySCellhole, false); 
  //! [ctopoFillContoursGetSCellsHole]
  
  
  aBoard << CustomStyle((*boundarySCell.begin()).className(),  new CustomColors(DGtal::Color::Blue, DGtal::Color::Blue) );
  aBoard2 << CustomStyle((*boundarySCell.begin()).className(),  new CustomColors(DGtal::Color::Blue, DGtal::Color::Blue) );
  
 
  
   for( std::set<DGtal::KhalimskySpaceND< 2, int >::SCell>::const_iterator it= boundarySCellhole.begin();  it!= boundarySCellhole.end(); it++){
    aBoard << *it;
    aBoard2 << *it;
    boundarySCell.insert(*it);
  }
  
  
  // Now we can compute the unsigned cell associated to interior pixels: 

  //! [ctopoFillContoursFillRegion]
  typedef ImageContainerBySTLMap< Z2i::Domain, bool> BoolImage2D;
  BoolImage2D::Domain imageDomain( Z2i::Point(0,10), Z2i::Point(20,30) );
  BoolImage2D interiorCellImage( imageDomain );
  Surfaces<DGtal::KhalimskySpaceND< 2, int > >::uFillInterior(K, functors::SurfelSetPredicate<std::set<SCell>,SCell>(boundarySCell), 
                                                              interiorCellImage, 1, false);  
  //! [ctopoFillContoursFillRegion]

  aBoard << CustomStyle(K.lowerCell().className(),  new CustomColors(DGtal::Color::None, Color(200, 200, 200)) );
  for(BoolImage2D::Domain::ConstIterator it = interiorCellImage.domain().begin(); 
      it!=interiorCellImage.domain().end(); it++){
    if(interiorCellImage(*it)){
      aBoard << K.uSpel(*it);
    }
  }
  
  
  // We can also compute the unsigned cell associated to interior and exterior pixels: 
  //! [ctopoFillContoursFillRegionHoles]
  BoolImage2D interiorCellHoleImage( imageDomain );
  BoolImage2D exteriorCellHoleImage( imageDomain );

  
  Surfaces<DGtal::KhalimskySpaceND< 2, int > >::uFillInterior(K, functors::SurfelSetPredicate<std::set<SCell>, SCell>(boundarySCellhole), 
                                                              interiorCellHoleImage, 1, true);  
  Surfaces<DGtal::KhalimskySpaceND< 2, int > >::uFillExterior(K, functors::SurfelSetPredicate<std::set<SCell>, SCell>(boundarySCellhole), 
                                                              exteriorCellHoleImage, 1,  false);  
  //! [ctopoFillContoursFillRegionHoles]  

  aBoard2 << CustomStyle(K.lowerCell().className(),
                          new CustomColors(DGtal::Color::None, Color(200, 200, 200)) );
  for(BoolImage2D::Domain::ConstIterator it = interiorCellHoleImage.domain().begin();
      it!=interiorCellHoleImage.domain().end(); it++){
    if(interiorCellHoleImage(*it)){
      aBoard2 << K.uSpel(*it);
    }
  }
  aBoard2 << CustomStyle(K.lowerCell().className(),
                         new CustomColors(DGtal::Color::None, Color(100, 100, 100)) );
  for(BoolImage2D::Domain::ConstIterator it = exteriorCellHoleImage.domain().begin(); 
      it!=exteriorCellHoleImage.domain().end(); it++){
    if(exteriorCellHoleImage(*it)){
      aBoard2 << K.uSpel(*it);
    }
  }
  
  aBoard.saveEPS("example_ctopo-fillContours.eps");
  aBoard.saveFIG("example_ctopo-fillContours.fig");

  aBoard2.saveEPS("example_ctopo-fillContours2.eps");
  aBoard2.saveFIG("example_ctopo-fillContours2.fig");
  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
