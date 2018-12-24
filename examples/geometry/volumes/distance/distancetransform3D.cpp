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
 * @file geometry/volumes/distance/distancetransform3D.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/01/04
 *
 * This file is part of the DGtal library.
 */

/**
   Example of distance transformation in dimension 3 with DGtal Viewer3D.
This program outputs this image:
@see \ref moduleVolumetric

@image html example-DT-3D.png

\example geometry/volumes/distance/distancetransform3D.cpp
*/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/io/readers/VolReader.h"

#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/viewers/Viewer3D.h"

#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/ImageSelector.h"

#include "DGtal/geometry/volumes/distance/DistanceTransformation.h"
#include "DGtal/images/SimpleThresholdForegroundPredicate.h"
#include "DGtal/helpers/StdDefs.h"

#include "ConfigExamples.h"

#include "DGtal/helpers/StdDefs.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////


/**
 * Set to a given value a random set of @a nb points.
 *
 * @param image the  image
 * @param nb the number of random points to insert
 * @param value the value to add at each random point
 */
template<typename Image>
void randomSeeds(Image &image, const unsigned int nb, const int value)
{
  typename Image::Point p, low = image.domain().lowerBound();
  typename Image::Vector ext;
  srand ( time(NULL) );

  ext = image.extent();

  for (unsigned int k = 0 ; k < nb; k++)
    {
      for (unsigned int dim = 0; dim < Image::dimension; dim++)
        p[dim] = rand() % (ext[dim]) +  low[dim];

      image.setValue(p, value);
    }
}

using namespace DGtal;

int main( int argc, char** argv )
{

  std::string inputFilename = examplesPath + "samples/Al.100.vol";

  //------------
  QApplication application(argc,argv);
  Viewer3D<> viewer;
  viewer.setWindowTitle("simpleViewer");
  viewer.show();



  //Default image selector = STLVector
  typedef ImageSelector<Z3i::Domain, unsigned char>::Type Image;
  Image image = VolReader<Image>::importVol( inputFilename );
  Z3i::Domain domain = image.domain();


  Image imageSeeds ( domain);
  for ( Image::Iterator it = imageSeeds.begin(), itend = imageSeeds.end();it != itend; ++it)
    (*it)=1;
  Z3i::Point p0(10,10,10);
  //imageSeeds.setValue(p0, 0 );
  randomSeeds(imageSeeds, 70, 0);


  //Distance transformation computation
  typedef functors::SimpleThresholdForegroundPredicate<Image> Predicate;
  Predicate aPredicate(imageSeeds,0);

  typedef  DistanceTransformation<Z3i::Space,Predicate, Z3i::L2Metric> DTL2;
  DTL2 dtL2(&domain, &aPredicate, &Z3i::l2Metric);

  unsigned int min = 0;
  unsigned int max = 0;
  for(DTL2::ConstRange::ConstIterator it = dtL2.constRange().begin(),
        itend=dtL2.constRange().end();
      it!=itend;
      ++it)
    {
      if(  (*it) < min )
        min=(*it);
      if( (*it) > max )
        max=(*it);
    }


  GradientColorMap<long> gradient( 0,30);
  gradient.addColor(Color::Red);
  gradient.addColor(Color::Yellow);
  gradient.addColor(Color::Green);
  gradient.addColor(Color::Cyan);
  gradient.addColor(Color::Blue);
  gradient.addColor(Color::Magenta);
  gradient.addColor(Color::Red);


  viewer << SetMode3D( (*(domain.begin())).className(), "Paving" );

  for(Z3i::Domain::ConstIterator it = domain.begin(), itend=domain.end();
      it!=itend;
      ++it){

    double valDist= dtL2( (*it) );
    Color c= gradient(valDist);

    if(dtL2(*it)<=30 && image(*it)>0){
      viewer << CustomColors3D(Color((float)(c.red()),
                                     (float)(c.green()),
                                     (float)(c.blue(),205)),
                               Color((float)(c.red()),
                                     (float)(c.green()),
                                     (float)(c.blue()),205));
      viewer << *it ;
    }
  }
  viewer<< Viewer3D<>::updateDisplay;

  return application.exec();
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

