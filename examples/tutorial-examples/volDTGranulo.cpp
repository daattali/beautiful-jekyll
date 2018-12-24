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
 * @file tutorial-examples/volDTGranulo.cpp
 * @ingroup tutorial-examples
 * @author Tristan Roussillon (tristan.roussillon@liris.cnrs.fr)
 *
 *
 * @date 2010/10/17
 *
 * @brief An example of generating a grid curve from a parametric shape
 * and estimating its length.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <algorithm>
///////////////////////////////////////////////////////////////////////////////

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"

#include "DGtal/images/ImageContainerBySTLVector.h"

#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/writers/VolWriter.h"

#include "DGtal/images/SimpleThresholdForegroundPredicate.h"
#include "DGtal/geometry/volumes/distance/DistanceTransformation.h"
#include "DGtal/shapes/implicit/ImplicitBall.h"
#include "DGtal/base/BasicFunctors.h"

#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/colormaps/GradientColorMap.h"

using namespace DGtal;

int main(int argc, char ** argv)
{

  //Loarding the image
  typedef ImageContainerBySTLVector<Z3i::Domain, unsigned int> Image;
  Image image = VolReader<Image>::importVol(argv[1]);
  trace.info() << image << std::endl;

  //Viewer
  QApplication application(argc,argv);
  Viewer3D<> viewer;
  viewer.show();

  for(Image::Domain::ConstIterator it = image.domain().begin(),
        itend = image.domain().end(); it != itend; ++it)
    if (image(*it) != 0)
      viewer << *it;

  viewer << DGtal::Viewer3D<>::updateDisplay;
  trace.info() << "viewer launched..."<<std::endl;
  bool res = application.exec();


  //DT
  Z3i::L2Metric l2;
  typedef functors::SimpleThresholdForegroundPredicate<Image> Predicate;
  Predicate binaryshape(image, 0);

  typedef DistanceTransformation< Z3i::Space, Predicate, Z3i::L2Metric> DT;

  DT distancemap(image.domain(), binaryshape, l2);

  //Viewer
  QApplication application2(argc,argv);
  Viewer3D<> viewer2;
  viewer2.show();
  DT::Value maxDT = (*std::max_element(distancemap.constRange().begin(),
                                       distancemap.constRange().end()));
  GradientColorMap<DT::Value> gradient( 0, maxDT);
  gradient.addColor(DGtal::Color::Blue);
  gradient.addColor(DGtal::Color::Green);
  gradient.addColor(DGtal::Color::Yellow);
  gradient.addColor(DGtal::Color::Red);
  trace.info() << "we display the dt map"<<std::endl;
  int cpt=0;
  viewer2 << DGtal::ClippingPlane(1,0,0,-10.1);

  for(DT::Domain::ConstIterator it = distancemap.domain().begin(),
  itend = distancemap.domain().end(); it != itend;
      ++it)
    if (distancemap(*it) > 0)
      {
  DT::Value  val= distancemap( *it );
  DGtal::Color c= gradient(val);

  viewer2 <<  DGtal::CustomColors3D(c,c) << *it    ;
        cpt++;
      }
  trace.info() << "Got "<<cpt<<" points."<<std::endl;
  viewer2 << DGtal::Viewer3D<>::updateDisplay;
  trace.info() << "viewer2  launched..."<<std::endl;
  res = res && application2.exec();

  //Granulo
  Image imageGranulo ( image.domain() );
  for(Image::Range::Iterator it = imageGranulo.range().begin(), itend= imageGranulo.range().end();
      it != itend; ++it)
    *it = 0;


  trace.info() << "Computing the granulometry"<<std::endl;
  cpt=0;
  for(Image::Domain::ConstIterator it = imageGranulo.domain().begin(),
        itend = imageGranulo.domain().end(); it != itend; ++it)
    {
      if (distancemap(*it) > 0)
        {
          //Construct the sphere with radius from distancemap(*it)
          Z3i::RealPoint center = *it;
          unsigned int radius = (unsigned int)distancemap(*it);
          ImplicitBall<Z3i::Space> ball(center,radius);
          Z3i::Point low = center - Z3i::Point::diagonal( radius+1 );
          Z3i::Point up = center + Z3i::Point::diagonal( radius+1 );
          Z3i::Domain dom(low,up);


          for(Z3i::Domain::ConstIterator itball = dom.begin(), itendball= dom.end();
              itball != itendball; itball++)
            if (imageGranulo.domain().isInside(*itball) &&
                ( ball(*itball) > 0) &&
                (imageGranulo(*itball) < radius))
              imageGranulo.setValue(*itball, radius);

          cpt++;
        }
    }

  trace.info() << "Granulometry ok nbBalls="<<cpt<< std::endl;
  VolWriter<Image, functors::Cast<unsigned char> >::exportVol("granulo.vol", imageGranulo);
  trace.info() << "Save OK"<< std::endl;


  //Viewer
  QApplication application3(argc,argv);
  Viewer3D<> viewer3;
  viewer3.show();
  Image::Value maxG = (*std::max_element(imageGranulo.constRange().begin(),
                                         imageGranulo.constRange().end()));
  GradientColorMap<Image::Value> gradient2( 0, maxG);
  gradient2.addColor(DGtal::Color::Blue);
  gradient2.addColor(DGtal::Color::Green);
  gradient2.addColor(DGtal::Color::Yellow);
  gradient2.addColor(DGtal::Color::Red);
  viewer3 << DGtal::ClippingPlane(1,0,0,-10.1);
  cpt=0;
  for(Image::Domain::ConstIterator it = imageGranulo.domain().begin(),
  itend = imageGranulo.domain().end(); it != itend;
      ++it)
    if (imageGranulo(*it) > 0)
      {
  Image::Value  val= imageGranulo( *it );
  DGtal::Color c = gradient2(val);
  viewer3 <<  DGtal::CustomColors3D(c,c) << *it    ;
        cpt++;
      }
  trace.info() << "Got "<<cpt<<" points."<<std::endl;
  viewer3 << DGtal::Viewer3D<>::updateDisplay;
  trace.info() << "viewer3  launched..."<<std::endl;
 return application3.exec();

}
