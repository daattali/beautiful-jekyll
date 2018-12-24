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
 * @file topology/3dKSSurfaceExtraction.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/06/27
 *
 * An example file named 3dKSSurfaceExtraction.
 *
 * This file is part of the DGtal library.
 */

/**
 * A simple example illustrating the extraction of 3d connected set of
 *  KhalimskyCell. This program outputs these images:
 *
 *  @see \ref dgtal_helpsurf_sec3
 *  
 *  @image html KSurfelsConnectedOrientExt.png 
 *  \example  topology/3dKSSurfaceExtraction.cpp
 */


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/base/Common.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/Color.h"

#include "DGtal/images/ImageSelector.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/helpers/Surfaces.h"


///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{

  Point p1( 0, 0,  0 );
  Point p2( 20, 20, 20 );
  Point c( 10, 10, 10 );
  Domain domain( p1, p2);

  // Generate the digital set from randam seeds and distance threshold.
  DigitalSet diamond_set( domain );
  //srand ( time(NULL) );
  unsigned int nbSeeds = 35;
  vector<Point> vCenters;
  vector<uint> vRad;
  for(unsigned int i=0;i<nbSeeds; i++){
    vCenters.push_back(Point(rand()%p2[0], rand()%p2[1],
          rand()%p2[2]));
    vRad.push_back(rand()%7);
  }
  for ( Domain::ConstIterator it = domain.begin(); it != domain.end(); ++it ){
    for(unsigned int i=0;i<nbSeeds; i++){
      if ( (*it - vCenters.at(i)  ).norm1() <= vRad.at(i) && domain.isInside(*it) &&
     domain.isInside(*it+Point(1,1,1)) && domain.isInside(*it-Point(1,1,1)) ){
  diamond_set.insertNew( *it );
  break;
      }
    }
  }


  //A KhalimskySpace is constructed from the domain boundary points.
  KSpace K;
  K.init(p1, p2, true);

  SurfelAdjacency<3> SAdj( true );
  vector<vector<SCell> > vectConnectedSCell;


  //Here since the last argument is set to true, the resulting
  //SignedKhalimskySpaceND are signed in order to indicate the direction
  //of exterior. You can also get the SignefKhalimskySpaceND with default
  //sign:

  Surfaces<KSpace>::extractAllConnectedSCell(vectConnectedSCell,K, SAdj, diamond_set, false);


  QApplication application(argc,argv);
  Viewer3D<> viewer (K);
  viewer.show();


  // Each connected compoments are simply displayed with a specific color.
  GradientColorMap<long> gradient(0, (const long)vectConnectedSCell.size());
  gradient.addColor(Color::Red);
  gradient.addColor(Color::Yellow);
  gradient.addColor(Color::Green);
  gradient.addColor(Color::Cyan);
  gradient.addColor(Color::Blue);
  gradient.addColor(Color::Magenta);
  gradient.addColor(Color::Red);


  for(unsigned int i=0; i< vectConnectedSCell.size();i++){
    DGtal::Color col= gradient(i);
    viewer << CustomColors3D(Color(250, 0,0), Color(col.red(),
                col.green(),
                col.blue()));

    for(unsigned int j=0; j< vectConnectedSCell.at(i).size();j++){
      viewer << vectConnectedSCell.at(i).at(j);
    }
  }


  viewer << CustomColors3D(Color(250, 0,0),Color(250, 200,200, 200));
  viewer << diamond_set;
  //viewer << ClippingPlane(0,1,0.0,-2);
  viewer << Viewer3D<>::updateDisplay;
  return application.exec();
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
