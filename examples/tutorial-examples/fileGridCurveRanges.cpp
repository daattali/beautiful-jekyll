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
 * @file tutorial-examples/fileGridCurveRanges.cpp
 * @ingroup tutorial-examples
 * @author Tristan Roussillon (tristan.roussillon@liris.cnrs.fr)
 *
 *
 * @date 2010/10/17
 * 
 * @brief An example of reading and displaying a gridcurve and its ranges. 
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <algorithm>
///////////////////////////////////////////////////////////////////////////////

//! [fileGridCurveRanges-basicIncludes]
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"
//! [fileGridCurveRanges-basicIncludes]

//! [fileGridCurveRanges-displayIncludes]
#include "DGtal/io/boards/Board2D.h"
//! [fileGridCurveRanges-displayIncludes]


using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main()
{
  
  //! [fileGridCurveRanges-declaration]
  Z2i::Curve c; 
  //! [fileGridCurveRanges-declaration]

  //! [fileGridCurveRanges-ex]
  std::string square = examplesPath + "samples/smallSquare.dat";  
  //! [fileGridCurveRanges-ex]

  //! [fileGridCurveRanges-read]
  std::fstream inputStream;
  inputStream.open (square.c_str(), std::ios::in);
  c.initFromVectorStream(inputStream);
  inputStream.close();  
  //! [fileGridCurveRanges-read]

  //! [fileGridCurveRanges-board]
  DGtal::Board2D aBoard;
  //! [fileGridCurveRanges-board]
  
  //displaying domain
  Z2i::Point low(-1,-1);
  Z2i::Point up(3,3);
  Z2i::Domain aDomain( low,up );
  aBoard << SetMode(aDomain.className(), "Paving") << aDomain; 
  
  //! [fileGridCurveRanges-displayCurve]
  aBoard << c;  
  aBoard.saveEPS("DisplayGridCurveTuto.eps");
  //! [fileGridCurveRanges-displayCurve]
  
  //! [fileGridCurveRanges-displayInnerPoints]
  Z2i::Curve::InnerPointsRange r1 = c.getInnerPointsRange(); 
  aBoard << r1; 
  //! [fileGridCurveRanges-displayInnerPoints]
  aBoard.saveEPS("DisplayInnerPointsTuto.eps");

  //! [fileGridCurveRanges-displayIncidentPoints]
  Z2i::Curve::IncidentPointsRange r2 = c.getIncidentPointsRange(); 
  aBoard << r2; 
  //! [fileGridCurveRanges-displayIncidentPoints]
  aBoard.saveEPS("DisplayIncidentPointsTuto.eps");


  return 0;

}

///////////////////////////////////////////////////////////////////////////////
