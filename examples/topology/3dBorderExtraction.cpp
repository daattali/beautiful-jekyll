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
 * @file topology/3dBorderExtraction.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/03/25
 *
 * An example file named 3dBorderExtraction.
 *
 * This file is part of the DGtal library.
 */


/**
 * Objects have a border, which are the points which touch the
 * complement in the sense of background adjacency. A border of an
 * object is itself an object, with the same topology as the object.
 *  
 * @see \ref dgtal_topology_sec3_3
 *
 * @image html visuBorderExtraction.png  "Border extraction visualisation" 
 *
 * \example topology/3dBorderExtraction.cpp
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/Color.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"


///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
 typedef SpaceND< 3,int > Z3;
 typedef MetricAdjacency< Z3, 1 > Adj6;
 typedef MetricAdjacency< Z3, 2 > Adj18;
 typedef DigitalTopology< Adj6, Adj18 > DT6_18;

 Adj6 adj6;
 Adj18 adj18;
 DT6_18 dt6_18( adj6, adj18, JORDAN_DT );

 typedef Z3::Point Point;
 typedef HyperRectDomain< Z3 > Domain;
 typedef Domain::ConstIterator DomainConstIterator;
 typedef DigitalSetSelector< Domain, BIG_DS+HIGH_BEL_DS >::Type DigitalSet;
 typedef Object<DT6_18, DigitalSet> ObjectType;

 Point p1( -50, -50, -50 );
 Point p2( 50, 50, 50 );
 Domain domain( p1, p2 );
 Point c( 0, 0 );
 // diamond of radius 30
 DigitalSet diamond_set( domain );
 for ( DomainConstIterator it = domain.begin(); it != domain.end(); ++it )
   {
     if ( (*it - c ).norm1() <= 30 ) diamond_set.insertNew( *it );
   }
 ObjectType diamond( dt6_18, diamond_set );
 // The following line takes almost no time.
 ObjectType diamond_clone( diamond );
 // Since one of the objects is modified, the set is duplicated at the following line
 diamond_clone.pointSet().erase( c );
 ObjectType bdiamond = diamond.border(); // one component
 ObjectType bdiamond_clone = diamond_clone.border(); // two components

 QApplication application(argc,argv);
 typedef Viewer3D<> MyViewer;
 MyViewer viewer;
 viewer.show();
 viewer<<  CustomColors3D(Color(250, 250,250),Color(250, 250,250));
 viewer << bdiamond_clone;
 viewer << bdiamond ;
 viewer << ClippingPlane(1,1,0,5, false) << MyViewer::updateDisplay;
 return application.exec();

}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
