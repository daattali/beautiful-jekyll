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
 * @file geometry/curves/exampleArithmeticalDSS.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/07/08
 *
 * An example file named exampleArithmeticalDSS.
 *
 * This file is part of the DGtal library.
 */

/**
   This example shows the basic usage of a 8-connected and a 4-connected 
arithmetical DSS.  

@see \ref moduleArithDSSReco

\example geometry/curves/exampleArithmeticalDSS.cpp
*/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <exception>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/boards/Board2D.h"

//! [ArithmeticalDSSHeader]
#include "DGtal/geometry/curves/ArithmeticalDSS.h"
//! [ArithmeticalDSSHeader]
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i; 
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Function that illustrates the basic usage of
 * a naive DSS. 
 */
void exampleNaiveDSS()
{
  trace.beginBlock ( "Naive DSS" );

  using namespace Z2i; 

  //! [ArithmeticalDSSNaiveCtor]
  // Construct a naive DSS
  NaiveDSS8<Integer> segment( 5, 8,                   //slope
			      Point(0,0), Point(8,5), //ending points 
			      Point(0,0), Point(8,5), //upper points
			      Point(3,1), Point(3,1)  //lower points
			      );
  //! [ArithmeticalDSSNaiveCtor]

  // Trace to the standard output
  trace.info() << segment << std::endl; 

  //! [ArithmeticalDSSIteration]
  // Trace the position and remainder of each point
  for (NaiveDSS8<Integer>::ConstIterator 
	 it = segment.begin(), 
	 ite = segment.end(); 
       it != ite; ++it )
    {
      trace.info() << "(" 
		   << segment.position( *it ) << ","
		   << segment.remainder( *it ) 
		   << ") "; 
    }
  //! [ArithmeticalDSSIteration]
  trace.info() << std::endl; 

  //! [NaiveDSS8DrawingUsage]
  Board2D board;
  
  // Draw the grid
  Domain domain( Point(0,0), Point(8,5) );
  board << SetMode(domain.className(), "Grid")
	<< domain;    
  
  //Draw the points of the DSS
  board << SetMode("PointVector", "Both");
  board << SetMode(segment.className(), "Points") 
	<< segment;

  // Draw the bounding box
  board << SetMode(segment.className(), "BoundingBox") 
  	<< segment;
  //! [NaiveDSS8DrawingUsage]


  // Save
  board.saveSVG("NaiveDSS8.svg");
#ifdef WITH_CAIRO
  board.saveCairo("NaiveDSS8.png", Board2D::CairoPNG);
#endif

  trace.endBlock();
}


/**
 * @brief Function that illustrates the basic usage of
 * a standard DSS. 
 */
void exampleStandardDSS()
{
  trace.beginBlock ( "Standard DSS" );

  using namespace Z2i; 

  //! [ArithmeticalDSSStandardCtor]
  // Construct a standard DSS
  StandardDSS4<Integer> segment( 5, 8,                   //slope
				 Point(0,0), Point(8,5), //ending points 
				 Point(0,0), Point(8,5), //upper points
				 Point(4,1), Point(4,1)  //lower points
				 );
  //! [ArithmeticalDSSStandardCtor]

  // Trace to the standard output
  trace.info() << segment << std::endl; 

  // Display the DSS with a domain on a board
  Domain domain( Point(0,0), Point(8,5) );
  Board2D board;

  //! [StandardDSS4DrawingUsage] 
  // Draw the grid
  board << SetMode(domain.className(), "Grid")
	<< domain;    

  // Draw the points of the DSS
  board << SetMode("PointVector", "Grid")
	<< SetMode(segment.className(), "Points") 
	<< segment;

  // Draw the bounding box
  board << SetMode(segment.className(), "BoundingBox") 
	<< segment;
  //! [StandardDSS4DrawingUsage]

  // Save
  board.saveSVG("StandardDSS4.svg");
#ifdef WITH_CAIRO
  board.saveCairo("StandardDSS4.png", Board2D::CairoPNG);
#endif

  board.clear(); 
  //! [ArithmeticalDSSDrawingUsage]
  // Draw the pixels
  board << SetMode(domain.className(), "Paving")
	<< domain;    
  
  //Draw the points of the DSS
  board << SetMode("PointVector", "Both");
  board << SetMode(segment.className(), "Points") 
	<< segment;

  // Draw the bounding box
  board << SetMode(segment.className(), "BoundingBox") 
	<< segment;
  //! [ArithmeticalDSSDrawingUsage]

  board.saveSVG("StandardDSS4bis.svg");
#ifdef WITH_CAIRO
  board.saveCairo("StandardDSS4bis.png", Board2D::CairoPNG);
#endif

  trace.endBlock();
}

/**
 * @brief Function showing the different ways
 * of constructing DSSs. 
 */
void exampleConstructors()
{
  trace.beginBlock ( "DSSs constructions" );

  using namespace Z2i; 

  {
    //! [ArithmeticalDSSNaiveCtorUpperPoints]
    // Construct a naive DSS from two upper leaning points
    NaiveDSS8<Integer> segment( Point(0,0), Point(8,5), true ); 
    //or simply NaiveDSS8<Integer> segment( Point(0,0), Point(8,5) ); 
    //! [ArithmeticalDSSNaiveCtorUpperPoints]
    trace.info() << segment << std::endl; 
  }

  {
    //! [ArithmeticalDSSNaiveCtorLowerPoints]
    // Construct a naive DSS from two lower leaning points
    NaiveDSS8<Integer> segment( Point(0,0), Point(8,5), false ); 
    //! [ArithmeticalDSSNaiveCtorLowerPoints]
    trace.info() << segment << std::endl; 
  }

  {
    //! [ArithmeticalDSSNaiveCtorDSL]
    // Construct a naive DSS as a DSL subsegment
    NaiveDSS8<Integer> segment( NaiveDSL<Integer>(5,8,0), Point(0,0), Point(8,5) ); 
    //! [ArithmeticalDSSNaiveCtorDSL]
    trace.info() << segment << std::endl; 
  }

  {
    NaiveDSS8<Integer> bigDSS( NaiveDSL<Integer>(5,8,0), Point(-8,-5), Point(16,10) );  
    //! [ArithmeticalDSSNaiveCtorDSS]
    // Construct a naive DSS as a subsegment of a greater DSS
    NaiveDSS8<Integer> segment( bigDSS, Point(0,0), Point(8,5) ); 
    //! [ArithmeticalDSSNaiveCtorDSS]
    trace.info() << segment << std::endl; 
  }

  std::vector<Point> r; //container for DSS points
  {
    //! [ArithmeticalDSSNaiveCtorParam]
    // Custom a naive DSS 
    NaiveDSS8<Integer> segment( 5, 8,                   //slope
				Point(0,0), Point(8,5), //ending points 
				Point(0,0), Point(8,5), //upper points
				Point(3,1), Point(3,1)  //lower points
				);
    //You should be sure that your object is valid before using it
    if (!segment.isValid()) throw std::exception(); 
    //! [ArithmeticalDSSNaiveCtorParam]
    trace.info() << segment << std::endl; 

    //copy the DSS points into the container r
    std::copy( segment.begin(), segment.end(), std::back_inserter(r) ); 
  }

  {
    //! [ArithmeticalDSSNaiveCtorRange]
    // Construct a DSS from a range of points  
    NaiveDSS8<Integer> segment( r.begin(), r.end() );
    //! [ArithmeticalDSSNaiveCtorRange]
    trace.info() << segment << std::endl; 
  }


  trace.endBlock();
}

/**
 * @brief Function showing how a DSS can be extended and retracted. 
 */
void exampleUpdate()
{
  trace.beginBlock ( "DSS update" );

  using namespace Z2i; 

  //Construction --------------------------------------------------
  //! [ArithmeticalDSSUpdateInit]
  Point M(11, 7); 
  NaiveDSS8<Integer> S( 5, 8,       //slope 
			Point(0,0), Point(10,6), //ending points 
			Point(0,0), Point(8,5), //upper points
			Point(3,1), Point(3,1)  //lower points
			);
  //! [ArithmeticalDSSUpdateInit]

  //this segment should be valid: 
  if (!S.isValid()) throw std::exception();
  // Store a copy before any operation
  NaiveDSS8<Integer> copyOfS = S; 

  trace.info() << S << std::endl;


  //Display ------------------------------------------------------  
  {
    Board2D board;

    // Draw the grid
    Domain domain( Point(0,0), M );
    board << SetMode(domain.className(), "Grid")
	  << domain;    
    // Draw the points of the DSS and its bounding box
    board << SetMode("PointVector", "Both");
    board << SetMode(S.className(), "Points") 
	  << S
	  << SetMode(S.className(), "BoundingBox") 
	  << S;
    // Draw the orthonormal base
    board.drawArrow(0.0, 0.0, 1.0, 0.0); 
    board.drawArrow(0.0, 0.0, 0.0, 1.0); 
    // Draw M
    board << SetMode(M.className(), "Both")
	  << CustomStyle( M.className(), new CustomColors( Color(255,0,0), Color(192, 0, 0)) )
	  << M; 


    // Save
    board.saveSVG("NaiveDSS8ExtInit.svg");
#ifdef WITH_CAIRO
    board.saveCairo("NaiveDSS8ExtInit.png", Board2D::CairoPNG);
#endif
  }

  // Extension -----------------------------------------------------
  //! [ArithmeticalDSSUpdateExtension]
  bool resExtention = S.extendFront( M ); 
  //! [ArithmeticalDSSUpdateExtension]
  //this segment should be extended: 
  if (!resExtention) throw std::exception(); 

  trace.info() << S << std::endl; 

  //Display ------------------------------------------------------  
  {
    Board2D board;

    // Draw the grid
    Domain domain( Point(0,0), M );
    board << SetMode(domain.className(), "Grid")
	  << domain;    
    // Draw the points of the DSS and its bounding box
    board << SetMode("PointVector", "Both");
    board << SetMode(S.className(), "Points") 
	  << S
	  << SetMode(S.className(), "BoundingBox") 
	  << S;
    // Draw the orthonormal base
    board.drawArrow(0.0, 0.0, 1.0, 0.0); 
    board.drawArrow(0.0, 0.0, 0.0, 1.0); 

    // Save
    board.saveSVG("NaiveDSS8ExtDone.svg");
#ifdef WITH_CAIRO
    board.saveCairo("NaiveDSS8ExtDone.png", Board2D::CairoPNG);
#endif
  }
    
  // Retraction ----------------------------------------------------
  //! [ArithmeticalDSSUpdateRetraction]
  bool resRetraction = S.retractFront(); 
  //! [ArithmeticalDSSUpdateRetraction]
  //this segment should be retracted: 
  if (!resRetraction) throw std::exception(); 

  trace.info() << S << std::endl; 

  // Comparaison ----------------------------------------------------
  //! [ArithmeticalDSSUpdateConclu]
  //this segment and the previous copy should be equal: 
  if ( !S.equalsTo(copyOfS) ) throw std::exception(); 
  //! [ArithmeticalDSSUpdateConclu]

  trace.endBlock();
}


///////////////////////////////////////////////////////////////////////////////
int main( int argc, char** argv )
{
  trace.beginBlock ( "Example exampleArithmeticalDSS" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  exampleNaiveDSS(); 
  exampleStandardDSS(); 
  exampleConstructors(); 
  exampleUpdate(); 

  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
