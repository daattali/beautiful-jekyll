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
 * @file geometry/curves/exampleArithmeticalDSL.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/11/09
 *
 * An example file named exampleArithmeticalDSL.
 *
 * This file is part of the DGtal library.
 */

/**
   This example 
- shows the basic usage of a naive/standard DSL, 
- displays the steps of a DSL for all octants. 

@see \ref moduleArithDSSReco

\example geometry/curves/exampleArithmeticalDSL.cpp
*/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"

#include "DGtal/io/boards/Board2D.h"

//! [ArithmeticalDSLHeader]
#include "DGtal/geometry/curves/ArithmeticalDSL.h"
//! [ArithmeticalDSLHeader]
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function that illustrates the basic usage of
 * a naive DSL. 
 */
void exampleNaiveDSL()
{
  trace.beginBlock ( "Naive DSL" );

  using namespace Z2i; 

  //! [ArithmeticalDSLNaiveCtor]
  // Construct a naive DSL from a, b, mu
  NaiveDSL<Integer> line( 2, 5, 0 ); 
  //! [ArithmeticalDSLNaiveCtor]

  // Trace to the standard output
  // the two representations 
  // corresponding to the same set of points
  trace.info() << line << line.negate(); 

  // Construct a (rectangular) domain
  Point bottomLeft( 0, 0 ); 
  Point topRight( 10, 5 ); 
  Domain domain( bottomLeft, topRight ); 
		        
  // Display the DSL points within the domain with Board2D
  Board2D board;

  Point firstPoint( bottomLeft[0], (line.a()*bottomLeft[0]/line.b()) ); 
  Point lastPoint( topRight[0], (line.a()*topRight[0]/line.b()) ); 

  //! [ArithmeticalDSLIteration]
  // Draw the DSL points between firstPoint and lastPoint
  for ( NaiveDSL<Integer>::ConstIterator 
	  it = line.begin(firstPoint), 
	  ite = line.end(lastPoint);
	it != ite; ++it )
    {
      board << SetMode( it->className(), "Paving" )
	    << *it; //Draw the point
    }
  //! [ArithmeticalDSLIteration]
  
  // Draw the grid
  board << SetMode(domain.className(), "Grid")
	<< domain;    

  // Draw the orthonormal base
  board.drawArrow(0.0, 0.0, 1.0, 0.0); 
  board.drawArrow(0.0, 0.0, 0.0, 1.0); 

  // Save
  board.saveSVG("NaiveDSL.svg");
  #ifdef WITH_CAIRO
  board.saveCairo("NaiveDSL.png", Board2D::CairoPNG);
  #endif

  trace.endBlock();
}

/**
 * @brief Function that illustrates the basic usage of
 * a standard DSL. 
 */
void exampleStandardDSL()
{
  trace.beginBlock ( "Standard DSL" );

  using namespace Z2i; 

  //! [ArithmeticalDSLStandardCtor]
  // Construct a standard DSL from a, b, mu
  StandardDSL<Integer> line( 2, 5, 0 ); 
  //! [ArithmeticalDSLStandardCtor]

  // Trace to the standard output
  // the two representations 
  // corresponding to the same set of points
  trace.info() << line << line.negate(); 

  // Construct a (rectangular) domain
  Point bottomLeft( 0, 0 ); 
  Point topRight( 10, 5 ); 
  Domain domain( bottomLeft, topRight ); 
		        
  // Display the DSL points within the domain with Board2D
  Board2D board;

  Point firstPoint( bottomLeft[0], (line.a()*bottomLeft[0]/line.b()) ); 
  Point lastPoint( topRight[0], (line.a()*topRight[0]/line.b()) ); 

  // Draw the DSL points between firstPoint and lastPoint
  for ( StandardDSL<Integer>::ConstIterator 
	  it = line.begin(firstPoint), 
	  ite = line.end(lastPoint);
	it != ite; ++it )
    {
      board << SetMode( it->className(), "Paving" )
	    << *it; //Draw the point
    }
  
  // Draw the grid
  board << SetMode(domain.className(), "Grid")
	<< domain;    

  // Draw the orthonormal base
  board.drawArrow(0.0, 0.0, 1.0, 0.0); 
  board.drawArrow(0.0, 0.0, 0.0, 1.0); 

  // Save
  board.saveSVG("StandardDSL.svg");
  #ifdef WITH_CAIRO
  board.saveCairo("StandardDSL.png", Board2D::CairoPNG);
  #endif

  trace.endBlock();
}

/**
 * @brief Function that draws the steps and the shift vector
 * of a DSL of slope @a a / @a b and intercept 0. 
 * @param a a-parameter of the DSL
 * @param b b-parameter of the DSL
 * @param octant octant index for tracing (from 0 to 7). 
 * @param n number of points to draw
 * @tparam DSL type of a naive or standard DSL
 */
template<typename DSL>
void drawArithmeticalDSL(typename DSL::Integer a, 
			 typename DSL::Integer b, 
			 unsigned short octant, 
			 unsigned int n)
{
  std::stringstream ssTitle; 
  ssTitle << " Arithmetical DSL "
	  << "(" << a << ", " << b << ", 0)"
	  << " in octant " << octant; 
  trace.beginBlock ( ssTitle.str().c_str() );

  using namespace Z2i; 

  // Construct the DSL to draw
  DSL line( a, b, 0 ); 

  // Vectors to draw
  Vector v = line.steps().first; 
  Vector w = line.steps().second; 
  Vector s = line.shift(); 
		        
  // Display the DSL points within the domain with Board2D
  Board2D board;

  // Draw the DSL points of the DSS
  typename DSL::ConstIterator it;
  it = line.begin( Point(0,0) ); 
  unsigned int c;  
  for (c = 0; c < n; ++it, ++c )
    {
      Point p = *it;
 
      // Draw the point
      board << SetMode( p.className(), "Paving" )
	    << p;
    }

  // Construct the domain
  Point topRight, bottomLeft; 
  Point firstPoint(0,0); 
  Point lastPoint = *it; 
  if (b > 0)
    {
      if (a > 0)
	{
	  bottomLeft = firstPoint; 
	  topRight = lastPoint; 
	}
      else
	{
	  bottomLeft = Point( firstPoint[0], lastPoint[1] ); 
	  topRight = Point( lastPoint[0], firstPoint[1] ); 
	}
    }
  else
    {
      if (a > 0)
	{
	  bottomLeft = Point( lastPoint[0], firstPoint[1] ); 
	  topRight = Point( firstPoint[0], lastPoint[1] ); 
	}
      else
	{
	  bottomLeft = lastPoint; 
	  topRight = firstPoint; 
	}
    }
  Domain domain( bottomLeft, topRight ); 


  // Draw the vectors
  it = line.begin( Point(0,0) );  
  for (c = 0; c < n; ++c )
    {
      Point p = *it;
      
      // Draw the shift vector
      if ( line.remainder( p ) == line.mu() )
	{ 
	  board.setPenColorRGBi(250, 0, 0);
	  board.drawArrow(p[0], p[1], p[0]+s[0], p[1]+s[1]); 
	}

      // Draw the steps
      ++it; 
      if (c < (n-1))
	{
	  Point q = *it; 
	  if ( (q-p) == v )
	    board.setPenColorRGBi(0, 0, 250);
	  else if ( (q-p) == w )
	    board.setPenColorRGBi(0, 250, 0);
	  else
	    board.setPenColorRGBi(0, 0, 0);

	  board.drawArrow(p[0], p[1], q[0], q[1]); 
	}
    }

  // Draw the grid
  board << SetMode(domain.className(), "Grid")
	<< domain;    

  // Draw the orthonormal base
  board.setPenColorRGBi(0, 0, 0);
  board.drawArrow(0.0, 0.0, 1.0, 0.0); 
  board.drawArrow(0.0, 0.0, 0.0, 1.0); 

  // Save
  std::stringstream ssFileName; 
  ssFileName << "ArithmeticalDSL"
	     << "-" << DSL::foregroundAdjacency
	     << "-" << octant
	     << "-" << a << "-" << b
	     << ".png"; 
  #ifdef WITH_CAIRO
  board.saveCairo(ssFileName.str().c_str(), Board2D::CairoPNG);
  #endif

  trace.endBlock();

}

/**
 * @brief Function that draws the steps and the shift vector
 * of a naive and a standard DSL in each octant. 
 * @see drawArithmeticalDSL
 */
void exampleArithmeticalDSLOctant()
{
  using namespace Z2i; 

  drawArithmeticalDSL<NaiveDSL<Integer> >( 0, 1, 0, 15 ); 
  drawArithmeticalDSL<NaiveDSL<Integer> >( 5, 8, 0, 15 ); 
  drawArithmeticalDSL<NaiveDSL<Integer> >( 1, 1, 1, 15 ); 
  drawArithmeticalDSL<NaiveDSL<Integer> >( 8, 5, 1, 15 );
  drawArithmeticalDSL<NaiveDSL<Integer> >( 1, 0, 2, 15 ); 
  drawArithmeticalDSL<NaiveDSL<Integer> >( 8, -5, 2, 15 );
  drawArithmeticalDSL<NaiveDSL<Integer> >( 1, -1, 3, 15 ); 
  drawArithmeticalDSL<NaiveDSL<Integer> >( 5, -8, 3, 15 );
  drawArithmeticalDSL<NaiveDSL<Integer> >( 0, -1, 4, 15 ); 
  drawArithmeticalDSL<NaiveDSL<Integer> >( -5, -8, 4, 15 );
  drawArithmeticalDSL<NaiveDSL<Integer> >( -1, -1, 5, 15 ); 
  drawArithmeticalDSL<NaiveDSL<Integer> >( -8, -5, 5, 15 );
  drawArithmeticalDSL<NaiveDSL<Integer> >( -1, 0, 6, 15 ); 
  drawArithmeticalDSL<NaiveDSL<Integer> >( -8, 5, 6, 15 );
  drawArithmeticalDSL<NaiveDSL<Integer> >( -1, 1, 7, 15 ); 
  drawArithmeticalDSL<NaiveDSL<Integer> >( -5, 8, 7, 15 );

  drawArithmeticalDSL<StandardDSL<Integer> >( 0, 1, 0, 21 ); 
  drawArithmeticalDSL<StandardDSL<Integer> >( 5, 8, 0, 21 ); 
  drawArithmeticalDSL<StandardDSL<Integer> >( 1, 1, 1, 21 ); 
  drawArithmeticalDSL<StandardDSL<Integer> >( 8, 5, 1, 21 );
  drawArithmeticalDSL<StandardDSL<Integer> >( 1, 0, 2, 21 ); 
  drawArithmeticalDSL<StandardDSL<Integer> >( 8, -5, 2, 21 );
  drawArithmeticalDSL<StandardDSL<Integer> >( 1, -1, 3, 21 ); 
  drawArithmeticalDSL<StandardDSL<Integer> >( 5, -8, 3, 21 );
  drawArithmeticalDSL<StandardDSL<Integer> >( 0, -1, 4, 21 ); 
  drawArithmeticalDSL<StandardDSL<Integer> >( -5, -8, 4, 21 );
  drawArithmeticalDSL<StandardDSL<Integer> >( -1, -1, 5, 21 ); 
  drawArithmeticalDSL<StandardDSL<Integer> >( -8, -5, 5, 21 );
  drawArithmeticalDSL<StandardDSL<Integer> >( -1, 0, 6, 21 ); 
  drawArithmeticalDSL<StandardDSL<Integer> >( -8, 5, 6, 21 );
  drawArithmeticalDSL<StandardDSL<Integer> >( -1, 1, 7, 21 ); 
  drawArithmeticalDSL<StandardDSL<Integer> >( -5, 8, 7, 21 );

}

/**
 * @brief Function that creates a naive DSL with different types. 
 */
void exampleArithmeticalDSLTypes()
{
  trace.beginBlock ( "Naive DSLs" );

  // // Do not use the default type for the intercepts ! 
  // NaiveDSL<DGtal::int16_t> line1( 17711, 28657, 1607895256 ); 
  // //NB: 1 607 895 256 is not representable by the type DGtal::int16_t, 
  // //even if it is the remainder of the point (32 767,-32 767)
  // //whose coordinates are representable by the type DGtal::int16_t
  // trace.info() << line1; //KO

  //! [ArithmeticalDSLNaiveCtorTypes]
  NaiveDSL<DGtal::int16_t, DGtal::int32_t> line2( 17711, 28657, 1607895256 ); 
  //NB: 1 607 895 256 is the remainder of the point (32 767,-32 767), 
  //whose coordinates are representable by the type DGtal::int16_t
  trace.info() << line2 << line2.isValid(); //ok 
  //! [ArithmeticalDSLNaiveCtorTypes]

  trace.endBlock(); 
}


/**
 * @brief Program that illustrates the basic usages of instances of 
 * ArithmeticalDSL
 * @param argc number of arguments
 * @param argv list of arguments
 */
int main( int argc, char** argv )
{
  trace.beginBlock ( "Example exampleArithmeticalDSL" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  exampleNaiveDSL(); 
  exampleStandardDSL(); 
  exampleArithmeticalDSLOctant(); 
  exampleArithmeticalDSLTypes(); 

  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
