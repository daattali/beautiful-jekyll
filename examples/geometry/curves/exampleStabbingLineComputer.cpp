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
 * @file geometry/curves/exampleStabbingLineComputer.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/09/21
 *
 * @brief An example file for StabbingLineComputer.
 * @see testStabbingLineComputer examplePreimage
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"

#include "DGtal/geometry/curves/StabbingLineComputer.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i; 


///////////////////////////////////////////////////////////////////////////////
int main( int argc, char** argv )
{
  trace.beginBlock ( "Example for StabbingLineComputer" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;
  
  std::string filename = examplesPath + "samples/DSS.dat";
  ifstream instream; // input stream
  instream.open (filename.c_str(), ifstream::in);
  
  Curve c; //grid curve
  c.initFromVectorStream(instream);


  trace.beginBlock("Simple example");

  //! [StabbingLineComputerUsage]
  Curve::IncidentPointsRange r = c.getIncidentPointsRange(); 
  Curve::IncidentPointsRange::ConstIterator itEnd (r.end()); 

  StabbingLineComputer<Curve::IncidentPointsRange::ConstIterator> s; 
  //extension
  s.init( r.begin() );
  while ( ( s.end() != itEnd )
        &&( s.extendFront() ) ) {}
  //! [StabbingLineComputerUsage]

  trace.info() << s << endl;  

  trace.endBlock();


  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
