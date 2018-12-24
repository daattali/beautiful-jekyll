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
 * @file geometry/tools/exampleConvexHull2D.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/12/17
 *
 * An example file named exampleConvexHull2D.
 *
 * This file is part of the DGtal library.
 */

/**
Computation of the convex hull of a planar point set by different algorithms: 
- functions::Hull2D::andrewConvexHullAlgorithm \cite Andrew1979
- functions::Hull2D::grahamConvexHullAlgorithm \cite Graham1972
- functions::Hull2D::melkmanConvexHullAlgorithm \cite Melkman1987

@see \ref moduleHull2D


\example geometry/tools/exampleConvexHull2D.cpp
*/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/IteratorCirculatorTraits.h"
#include "DGtal/helpers/StdDefs.h"

//! [Hull2D-Include]
#include "DGtal/geometry/tools/Hull2DHelpers.h"
//! [Hull2D-Include]
#include "DGtal/geometry/tools/PolarPointComparatorBy2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/AvnaimEtAl2x2DetSignComputer.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBySimple3x3Matrix.h"

#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/Shapes.h"

#include "DGtal/topology/DigitalSetBoundary.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/graph/DepthFirstVisitor.h"

#include "DGtal/io/boards/Board2D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
/*
 * @brief Procedure that draws on a board a polygon given by a range of vertices. 
 * @param itb begin iterator
 * @param ite end iterator
 * @param aBoard any board
 * @param isClosed bool equal to 'true' for closed polygon, 'false' otherwise. 
 * @tparam ForwardIterator at least a readable and forward iterator
 * @tparam Board equivalent to Board2D
 */
template <typename ForwardIterator, typename Board>
void drawPolygon(const ForwardIterator& itb, const ForwardIterator& ite, 
		 Board& aBoard, bool isClosed = true)
{
  BOOST_CONCEPT_ASSERT(( boost_concepts::ForwardTraversalConcept<ForwardIterator> )); 
  BOOST_CONCEPT_ASSERT(( boost_concepts::ReadableIteratorConcept<ForwardIterator> )); 
  typedef typename IteratorCirculatorTraits<ForwardIterator>::Value Point; 

  ForwardIterator it = itb; 
  if (it != ite)
    {//for the first point
      Point p1 = *it;
      Point p = p1; 
      //display
      aBoard << SetMode( p.className(), "Grid" )
	     << CustomStyle( p.className()+"/Grid", new CustomPenColor( Color::Red ) )
	     << p 
	     << CustomStyle( p.className()+"/Grid", new CustomPenColor( Color::Black ) ); 
       
      Point prev = p; 
      for (++it; it != ite; ++it, prev = p)
	{//for all other points
	  //conversion
	  p = *it; 
	  //display
	  aBoard << p; 
	  if (prev != p)
	    aBoard.drawArrow(prev[0], prev[1], p[0], p[1]); 
	}

      //display the last edge too
      if (isClosed)
	{
	  if (prev != p1)
	    aBoard.drawArrow(prev[0], prev[1], p1[0], p1[1]); 
	}
    }
}


/**
 * Algorithms that computes the convex hull
 * of a point set
 */
void convexHull()
{
  //Digitization of a disk of radius 6
  Ball2D<Z2i::Space> ball(Z2i::Point(0,0), 6);
  Z2i::Domain domain(ball.getLowerBound(), ball.getUpperBound());
  Z2i::DigitalSet pointSet(domain);   
  Shapes<Z2i::Domain>::euclideanShaper(pointSet, ball);

  //! [Hull2D-Namespace]
  using namespace functions::Hull2D; 
  //! [Hull2D-Namespace]

  //! [Hull2D-Functor]
  typedef InHalfPlaneBySimple3x3Matrix<Z2i::Point, DGtal::int64_t> Functor;  
  Functor functor; 
  //! [Hull2D-Functor]

  { //convex hull in counter-clockwise order
    vector<Z2i::Point> res; 

    //! [Hull2D-StrictPredicateCCW]
    typedef PredicateFromOrientationFunctor2<Functor, false, false> StrictPredicate; 
    StrictPredicate predicate( functor ); 
    //! [Hull2D-StrictPredicateCCW]
    //according to the last two template arguments, neither strictly negative values, nor zeros are accepted: 
    //the predicate returns 'true' only for strictly positive values returned by the underlying functor. 

    //! [Hull2D-AndrewAlgo]
    andrewConvexHullAlgorithm( pointSet.begin(), pointSet.end(), back_inserter( res ), predicate );   
    //! [Hull2D-AndrewAlgo]
    //![Hull2D-Caliper-computeBasic]
    double th = DGtal::functions::Hull2D::computeHullThickness(res.begin(), res.end(), DGtal::functions::Hull2D::HorizontalVerticalThickness);
    //![Hull2D-Caliper-computeBasic]

    //![Hull2D-Caliper-computeAnti]
    Z2i::Point antipodalP, antipodalQ, antipodalS;
    th = DGtal::functions::Hull2D::computeHullThickness(res.begin(), res.end(), DGtal::functions::Hull2D::HorizontalVerticalThickness, antipodalP, antipodalQ, antipodalS);
    //![Hull2D-Caliper-computeAnti]

    
    trace.info() <<" ConvexHull HV thickness: " << th << std::endl;
    //display
    Board2D board;
    drawPolygon( res.begin(), res.end(), board ); 
    //![Hull2D-Caliper-display]
    board.setPenColor(DGtal::Color::Red);
    board.drawCircle( antipodalS[0], antipodalS[1], 0.2) ;
    board.setPenColor(DGtal::Color::Blue);
    board.drawCircle(antipodalP[0], antipodalP[1], 0.2);
    board.drawCircle(antipodalQ[0], antipodalQ[1], 0.2);
    board.drawLine(antipodalP[0], antipodalP[1], antipodalQ[0], antipodalQ[1]);
    //![Hull2D-Caliper-display]
    
    board.saveSVG( "ConvexHullCCW.svg" );  
#ifdef WITH_CAIRO
    board.saveCairo("ConvexHullCCW.png", Board2D::CairoPNG);
#endif
  }

  { //convex hull in counter-clockwise order with all the points lying on the edges
    vector<Z2i::Point> res; 

    //! [Hull2D-LargePredicateCCW]
    typedef PredicateFromOrientationFunctor2<Functor, false, true> LargePredicate; 
    LargePredicate predicate( functor ); 
    //! [Hull2D-LargePredicateCCW]
    //according to the last template argument, zeros are accepted so that  
    //the predicate returns 'true' for all the positive values returned by the underlying functor. 

    //andrew algorithm
    andrewConvexHullAlgorithm( pointSet.begin(), pointSet.end(), back_inserter( res ), predicate );   

    //display
    Board2D board;
    drawPolygon( res.begin(), res.end(), board ); 
    board.saveSVG( "ConvexHullCCWWithPointsOnEdges.svg" );  
#ifdef WITH_CAIRO
    board.saveCairo("ConvexHullCCWWithPointsOnEdges.png", Board2D::CairoPNG);
#endif

  }

  { //convex hull in clockwise order
    vector<Z2i::Point> res; 

    //! [Hull2D-StrictPredicateCW]
    typedef PredicateFromOrientationFunctor2<Functor, true, false> StrictPredicate; 
    StrictPredicate predicate( functor );
    //! [Hull2D-StrictPredicateCW]
    //according to the last two argument template, 
    //the predicate returns 'true' only for strictly negative values returned by the underlying functor. 

    //andrew algorithm
    andrewConvexHullAlgorithm( pointSet.begin(), pointSet.end(), back_inserter( res ), predicate );   

    //display
    Board2D board;
    drawPolygon( res.begin(), res.end(), board ); 
    board.saveSVG( "ConvexHullCW.svg" );  
#ifdef WITH_CAIRO
    board.saveCairo("ConvexHullCW.png", Board2D::CairoPNG);
#endif
  }

  { //convex hull in counter-clockwise order
    vector<Z2i::Point> res; 

    //geometric predicate
    typedef PredicateFromOrientationFunctor2<Functor, false, false> StrictPredicate; 
    StrictPredicate predicate( functor ); 

    //! [Hull2D-GrahamAlgo]
    grahamConvexHullAlgorithm( pointSet.begin(), pointSet.end(), back_inserter( res ), predicate ); 
    //! [Hull2D-GrahamAlgo]

    //display
    Board2D board;
    drawPolygon( res.begin(), res.end(), board ); 
    board.saveSVG( "ConvexHullCCWbis.svg" );  
#ifdef WITH_CAIRO
    board.saveCairo("ConvexHullCCWbis.png", Board2D::CairoPNG);
#endif
  }

  { //convex hull of a simple polygonal line that is not weakly externally visible
    vector<Z2i::Point> polygonalLine;
    polygonalLine.push_back(Z2i::Point(0,0)); 
    polygonalLine.push_back(Z2i::Point(0,4)); 
    polygonalLine.push_back(Z2i::Point(1,4)); 
    polygonalLine.push_back(Z2i::Point(1,1)); 
    polygonalLine.push_back(Z2i::Point(3,1)); 
    polygonalLine.push_back(Z2i::Point(2,2)); 
    polygonalLine.push_back(Z2i::Point(3,4)); 
    polygonalLine.push_back(Z2i::Point(4,4)); 
    polygonalLine.push_back(Z2i::Point(4,0)); 

    vector<Z2i::Point> resGraham, res; 

    typedef PredicateFromOrientationFunctor2<Functor, false, false> StrictPredicate; 
    StrictPredicate predicate( functor ); 
    closedGrahamScanFromAnyPoint( polygonalLine.begin(), polygonalLine.end(), back_inserter( resGraham ), predicate );   

    //! [Hull2D-OnLineMelkmanAlgo]
    DGtal::MelkmanConvexHull<Z2i::Point, Functor> ch( functor ); 
    for (std::vector<Z2i::Point>::const_iterator 
	   it = polygonalLine.begin(), 
	   itEnd = polygonalLine.end(); 
	 it != itEnd; ++it)
      ch.add( *it ); 
    //! [Hull2D-OnLineMelkmanAlgo]

    //! [Hull2D-OffLineMelkmanAlgo]
    melkmanConvexHullAlgorithm( polygonalLine.begin(), polygonalLine.end(), back_inserter( res ), functor );   
    //! [Hull2D-OffLineMelkmanAlgo]

    //display
    Board2D board;
    drawPolygon( polygonalLine.begin(), polygonalLine.end(), board, true ); 
    board.saveSVG( "SimplePolygonalLine.svg" );  
#ifdef WITH_CAIRO
    board.saveCairo("SimplePolygonalLine.png", Board2D::CairoPNG);
#endif
    board.clear(); 
    drawPolygon( resGraham.begin(), resGraham.end(), board ); 
    board.saveSVG( "SimplePolygonalLineGraham.svg" );  
#ifdef WITH_CAIRO
    board.saveCairo("SimplePolygonalLineGraham.png", Board2D::CairoPNG);
#endif
    board.clear(); 
    drawPolygon( res.begin(), res.end(), board ); 
    board.saveSVG( "SimplePolygonalLineMelkman.svg" );  
#ifdef WITH_CAIRO
    board.saveCairo("SimplePolygonalLineMelkman.png", Board2D::CairoPNG);
#endif
    board.clear(); 
    drawPolygon( ch.begin(), ch.end(), board ); 
    board.saveSVG( "SimplePolygonalLineMelkman2.svg" );  
#ifdef WITH_CAIRO
    board.saveCairo("SimplePolygonalLineMelkman2.png", Board2D::CairoPNG);
#endif
  }

  { //order of the points for andrew algorithm
    vector<Z2i::Point> res; 
    std::copy( pointSet.begin(), pointSet.end(), back_inserter( res ) ); 

    std::sort( res.begin(), res.end() ); 

    //display
    Board2D board;
    drawPolygon( res.begin(), res.end(), board, false ); 
    board.saveSVG( "AndrewWEVP.svg" );  
#ifdef WITH_CAIRO
    board.saveCairo("AndrewWEVP.png", Board2D::CairoPNG);
#endif
  }

  { //order of the points for graham algorithm
    vector<Z2i::Point> res; 
    std::copy( pointSet.begin(), pointSet.end(), back_inserter( res ) ); 

    //find an extremal point
    //NB: we choose the point of greatest x-coordinate
    //so that the sort step (by a polar comparator) 
    //returns a weakly externally visible polygon
    std::vector<Z2i::Point>::iterator itMax 
      = std::max_element( res.begin(), res.end() ); 

    //sort around this point with a polar comparator
    functors::PolarPointComparatorBy2x2DetComputer<Z2i::Point> comparator;  
    comparator.setPole( *itMax );
    std::sort( res.begin(), res.end(), comparator ); 

    //display
    Board2D board;
    drawPolygon( res.begin(), res.end(), board, false ); 
    board.saveSVG( "GrahamWEVP.svg" );  
#ifdef WITH_CAIRO
    board.saveCairo("GrahamWEVP.png", Board2D::CairoPNG);
#endif
  }


}

/**
 * Main procedure. 
 * Draw the convex hull
 * of a point set coming from the digitization of a disk. 
 * @param argc number of arguments
 * @param argv array of arguments
 */
int main( int argc, char** argv )
{
  trace.beginBlock ( "Example exampleConvexHull2D" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  convexHull(); 

  trace.endBlock(); 

  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
