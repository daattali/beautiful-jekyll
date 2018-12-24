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
 * @file tutorial-examples/shapeDTViewer.cpp
 * @ingroup tutorial-examples
 * @author David Coeurjolly (david.coeurjolly@liris.cnrs.fr)
 *
 *
 * @date 2011/10/17
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

//! [shapeDTViewer-basicIncludes]
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"

#include "DGtal/shapes/Shapes.h"
#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/viewers/Viewer3D.h"

#include "DGtal/geometry/volumes/distance/DistanceTransformation.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/helpers/StdDefs.h"
//!  [shapeDTViewer-basicIncludes]
///////////////////////////////////////////////////////////////////////////////

using namespace DGtal;

int main(int argc, char **argv)
{
  QApplication application(argc,argv);

  DGtal::Viewer3D<> viewer;

  DGtal::Z3i::Point center(0,0,0);
  DGtal::ImplicitRoundedHyperCube<Z3i::Space> myCube( center, 20, 2.8);
  DGtal::Z3i::Domain domain(myCube.getLowerBound(),
          myCube.getUpperBound());

  DGtal::Z3i::DigitalSet mySet(domain);

  DGtal::Shapes<DGtal::Z3i::Domain>::euclideanShaper( mySet, myCube);


  viewer.show();
  // viewer << mySet << DGtal::Display3D::updateDisplay;


  //! [ImageSetDT-DT]
  typedef DGtal::DistanceTransformation<Z3i::Space, DGtal::Z3i::DigitalSet, Z3i::L2Metric> DTL2;
  DTL2 dt(&domain,&mySet,&Z3i::l2Metric );
  //! [ImageSetDT-DT]

  DTL2::Value maxDT = (*std::max_element(dt.constRange().begin(),
                                         dt.constRange().end()));


  GradientColorMap<DTL2::Value> gradient( 0, maxDT);
  gradient.addColor(DGtal::Color::Blue);
  gradient.addColor(DGtal::Color::Green);
  gradient.addColor(DGtal::Color::Yellow);
  gradient.addColor(DGtal::Color::Red);


  for(Z3i::Domain::ConstIterator it = domain.begin(),
  itend = domain.end(); it != itend;
      ++it)
    if (dt(*it) != 0)
      {
  DTL2::Value  val= dt( *it );
  DGtal::Color c= gradient(val);

  viewer <<  DGtal::CustomColors3D(c,c) << *it    ;

      }


  viewer << DGtal::ClippingPlane(1,0,0,0);
  //@todo updateDisplay is in Display3D or Viewer3D (cf doc)?
  viewer << DGtal::Viewer3D<>::updateDisplay;

  return application.exec();


}

///////////////////////////////////////////////////////////////////////////////
