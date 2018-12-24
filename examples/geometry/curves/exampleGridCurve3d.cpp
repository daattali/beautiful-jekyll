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
 * @file geometry/curves/exampleGridCurve3d.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/06/03
 *
 * An example file for GridCurve, defined as a sequence of 1-scells, in a 3d Khalimsky space.
 *
 * This file is part of the DGtal library.
 */
/**
   This example shows how to use GridCurve as a sequence of 1-scells in a 3d Khalimsky space. 

@verbatim
$ ./examples/geometry/curves/exampleGridCurve3d
@endverbatim

Note that the data type you want to display may be passed as argument as follows: 
@verbatim
$ ./examples/geometry/curves/exampleGridCurve3d points
@endverbatim

This command line produces the following output (points are displayed as voxels): 

@image html exampleGridCurveSinus.png "3d digital curve"
@image latex exampleGridCurveSinus.png "3d digital curve"


@see \ref moduleGridCurveAnalysis

\example geometry/curves/exampleGridCurve3d.cpp
*/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/geometry/curves/GridCurve.h"

#ifdef WITH_VISU3D_QGLVIEWER
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#endif

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;



///////////////////////////////////////////////////////////////////////////////
int main( int argc, char** argv )
{


  trace.info() << "exampleGridCurve3d: the type of data to be displayed "
	       << "may be given as argument as follows: "
	       << argv[0] << " scells" << endl; 
  trace.info() << "Available types are: gridcurve (default), scells, points, midpoints, arrows" << endl;

  string type = (argc > 1) ? string(argv[1]) : "gridcurve";
  trace.info() << "Chosen type: " << type << endl; 

  //curve
  string sinus = examplesPath + "samples/sinus.dat";

  // domain
  Point lowerBound = Point::diagonal( -100 );
  Point upperBound = Point::diagonal( 100 );

  //! [GridCurveDeclaration]
  K3 ks; ks.init( lowerBound, upperBound, true );
  GridCurve<K3> gc( ks );
  //! [GridCurveDeclaration]

  //! [GridCurveFromDataFile]
  fstream inputStream;
  inputStream.open (sinus.c_str(), ios::in);

  gc.initFromVectorStream(inputStream);

  inputStream.close();
  //! [GridCurveFromDataFile]

  bool flag = false;
#ifdef WITH_VISU3D_QGLVIEWER
  QApplication application(argc,argv);
  Viewer3D<Space,K3> viewer(ks);
  viewer.show();

  if (type == "gridcurve")
    {
      viewer  << gc;
    }
  else if (type == "scells")
    {
      viewer << gc.getSCellsRange();
    }
  else if (type == "points")
    {
      viewer << gc.getPointsRange();
    }
  else if (type == "midpoints")
    {
      viewer << gc.getMidPointsRange();
    }
  else if (type == "arrows")
    {
      viewer << gc.getArrowsRange();
    }
  else
    {
      trace.info() << "Display type not known." << std::endl;
    }
  viewer << Viewer3D<Space,K3>::updateDisplay;
  flag = application.exec();
#endif

  return flag;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
