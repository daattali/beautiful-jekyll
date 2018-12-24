
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
 * @file topology/ctopo-2.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/04/28
 *
 * An example file named ctopo-2.
 *
 * This file is part of the DGtal library.
 */


/**
 *  A simple example illustrating the extraction of the sequence of
 *  surfels boudary. This program outputs this image.
 *
 *  @see \ref dgtal_helpsurf_sec1
 *
 * @image html ctopo2c.png 
 *
 * \example topology/ctopo-2.cpp
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/helpers/Surfaces.h"

#include "DGtal/io/readers/PGMReader.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/Color.h"

#include "ConfigExamples.h"




///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int /*argc*/, char** /*argv*/ )
{
  typedef ImageSelector < Z2i::Domain, int>::Type Image;
  std::string inputFilename = examplesPath + "samples/circleR10modif.pgm"; 
  Image image = PGMReader<Image>::importPGM( inputFilename ); 
  
  Z2i::DigitalSet set2d (image.domain());
  SetFromImage<Z2i::DigitalSet>::append<Image>(set2d, image, 0, 255);
  Board2D board;
  board << image.domain() << set2d; // display domain and set
  
  Board2D board2;
  board2 << image.domain() << set2d; // display domain and set

  Board2D board3;
  board3 << image.domain() << set2d; // display domain and set


  // Construct the Khalimsky space from the image domain
  Z2i::KSpace ks;
  bool space_ok = ks.init( image.domain().lowerBound(), image.domain().upperBound(), true );
  


  //Extract a boundary cell
  Z2i::SCell aCell = Surfaces<Z2i::KSpace>::findABel(ks, set2d );

  // Getting the consecutive surfels of the 2D boundary
  std::vector<Z2i::SCell> vectBdrySCell;
  SurfelAdjacency<2> SAdj( true );
  Surfaces<Z2i::KSpace>::track2DBoundary( vectBdrySCell,
            ks, SAdj, set2d, aCell );
  
  board << CustomStyle( (*(vectBdrySCell.begin())).className(), 
      new CustomColors(  Color( 255, 255, 0 ),
             Color( 192, 192, 0 ) ));
  
  GradientColorMap<int> cmap_grad( 0, (const int)vectBdrySCell.size() );
  cmap_grad.addColor( Color( 50, 50, 255 ) );
  cmap_grad.addColor( Color( 255, 0, 0 ) );
  cmap_grad.addColor( Color( 255, 255, 10 ) );

  unsigned int d=0;
  std::vector<Z2i::SCell>::iterator it;
  for ( it=vectBdrySCell.begin() ; it != vectBdrySCell.end(); it++ ){
    board<< CustomStyle((*it).className() ,
      new CustomColors( Color::Black,
            cmap_grad( d )))<< *it;
    d++;
  }


  // Extract all boundaries:
  std::set<Z2i::SCell> bdry;
  // Z2i::Cell low = ks.uFirst(ks.uSpel(ks.lowerBound()));
  // Z2i::Cell upp = ks.uLast(ks.uSpel(ks.upperBound()));
  Surfaces<Z2i::KSpace>::sMakeBoundary
    ( bdry,
      ks, set2d, ks.lowerBound(), ks.upperBound() );

  
  std::set<Z2i::SCell>::iterator itB;
  for ( itB=bdry.begin() ; itB != bdry.end(); itB++ ){
    board2<< CustomStyle((*itB).className() ,
       new CustomColors( Color::Black,
             cmap_grad( d )))<< *itB;
    d++;
  }
  
  std::vector< std::vector<Z2i::SCell> > vectContoursBdrySCell;
  Surfaces<Z2i::KSpace>::extractAll2DSCellContours( vectContoursBdrySCell,
                ks, SAdj, set2d );
  GradientColorMap<int> cmap_grad3( 0, (const int)vectContoursBdrySCell.size() );
  cmap_grad3.addColor( Color( 50, 50, 255 ) );
  cmap_grad3.addColor( Color( 255, 0, 0 ) );
  cmap_grad3.addColor( Color( 20, 200, 0 ) );
  cmap_grad3.addColor( Color( 200, 200, 200 ) );
  cmap_grad3.addColor( Color( 20, 200, 200 ) );
  cmap_grad3.addColor( Color( 200, 20, 200 ) );
  
  d=0;
  for(unsigned int i=0; i< vectContoursBdrySCell.size(); i++){
    d++;
    for(unsigned int j=0; j< vectContoursBdrySCell.at(i).size(); j++){
      board3<< CustomStyle(vectContoursBdrySCell.at(i).at(j).className() ,
         new CustomColors( Color::Black,
               cmap_grad3( d )))<<vectContoursBdrySCell.at(i).at(j) ;
      
    }
  }



 
    board << aCell;  
    board.saveEPS( "ctopo-2.eps");
    board.saveFIG( "ctopo-2.fig");

    board2.saveEPS( "ctopo-2d.eps");
    board2.saveFIG( "ctopo-2d.fig");
    
    board3.saveEPS( "ctopo-2e.eps");
    board3.saveFIG( "ctopo-2e.fig");
    
    return (space_ok);
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
