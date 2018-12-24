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
 * @file geometry/curves/exampleGridCurve2d.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/09/09
 *
 * @brief An example file for GridCurve.
 *
 * This file is part of the DGtal library.
 */


/**
   This snippet shows how to construct, scan and display a 2d grid curve. 

@see \ref moduleGridCurveAnalysis

\example geometry/curves/exampleGridCurve2d.cpp
*/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"

#include "DGtal/geometry/curves/FreemanChain.h"
#include "DGtal/geometry/curves/GridCurve.h"

#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/io/boards/Board2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i; 

///////////////////////////////////////////////////////////////////////////////
//! [GridCurveGenericFunctionDisplayAll]
template <typename CI>
void displayAll( const CI& ciBegin, const CI& ciEnd ) 
{
  if ( isNotEmpty(ciBegin, ciEnd) ) 
  { //if the range is not empty
    CI i( ciBegin); 
    do 
    {
      trace.info() << *i;
      i++;
    } while (i != ciEnd);
    trace.info() << endl;    
  }    
}
//! [GridCurveGenericFunctionDisplayAll]

///////////////////////////////////////////////////////////////////////////////
int main( int argc, char** argv )
{
  trace.beginBlock ( "Example for 2d gridcurves" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  string square = examplesPath + "samples/smallSquare.dat";
  string S = examplesPath + "samples/contourS.fc";
  
    // domain
    Point lowerBound( -50, -50 );
    Point upperBound( 50, 50 );

  //! [GridCurveDeclaration]
  //default construction
  Curve c1; 

  //from a Khalimsky space
  K2 ks; ks.init( lowerBound, upperBound, true ); 
  Curve c2( ks ); 
  //! [GridCurveDeclaration]
  
  trace.emphase() << "Input" << endl;
  trace.info() << "\t from a data file " << endl;
  {
    //! [GridCurveFromDataFile]
    fstream inputStream;
    inputStream.open (square.c_str(), ios::in);
    c1.initFromVectorStream(inputStream);
    inputStream.close();
    //! [GridCurveFromDataFile]
  }
  trace.info() << "\t from a digital set " << endl;
  {

    // digital set: diamond of radius 30 centered at the origin
    Point o( 0, 0 );
    Domain domain( lowerBound, upperBound );
    DigitalSet set( domain );
    for ( Domain::ConstIterator it = domain.begin(); it != domain.end(); ++it )
    {
     if ( (*it - o ).norm1() <= 30 ) set.insertNew( *it );
    }
    
    //! [GridCurveFromDigitalSet]
    vector<SCell> contour;                           //contour
    SurfelAdjacency<K2::dimension> sAdj( true );     //adjacency

    //tracking and init grid curve
    SCell s = Surfaces<KSpace>::findABel( ks, set, 1000 );
    Surfaces<KSpace>::track2DBoundary( contour, ks, sAdj, set, s );
    c2.initFromSCellsVector( contour );
    //! [GridCurveFromDigitalSet]
  }
  
  trace.info() << "\t from a FreemanChain (from a file) " << endl; 
  {
    fstream inputStream;
    inputStream.open (S.c_str(), ios::in);
    FreemanChain<int> fc(inputStream);
    inputStream.close();

    Curve c; 
    //! [GridCurveFromFreemanChain]
    c.initFromPointsRange( fc.begin(), fc.end() ); 
    //! [GridCurveFromFreemanChain]

  }

  trace.emphase() << "Output" << endl;
  trace.info() << "\t standard output " << endl;
  {
    //! [GridCurveStandardOutput]
    trace.info() << c1 << std::endl;
    //! [GridCurveStandardOutput]
  }
  trace.info() << "\t into a data file " << endl;
  {
    //! [GridCurveToDataFile]
    ofstream outputStream("myGridCurve.dat"); 
    if (outputStream.is_open()) 
      c2.writeVectorToStream(outputStream);
    outputStream.close();
    //! [GridCurveToDataFile]
  }
  trace.info() << "\t into a vector graphics file " << endl;
  {
    //! [GridCurveToGraphics]
    Board2D aBoard;
    aBoard.setUnit(Board2D::UCentimeter);
    aBoard << c2; 
    aBoard.saveEPS( "myGridCurve.eps", Board2D::BoundingBox, 5000 );
    //! [GridCurveToGraphics]
  }
  
  trace.info() << "\t into a FreemanChain " << endl; 
  {
    //! [GridCurveToFreemanChain]
    typedef FreemanChain<Curve::KSpace::Integer> FreemanChain; 
    FreemanChain fc;
    FreemanChain::readFromPointsRange( c1.getPointsRange(), fc ); 
    trace.info() << "\t" << fc << endl;
    //! [GridCurveToFreemanChain]
  }
  
  trace.emphase() << "Ranges Ouput" << endl;
  {
    Board2D aBoard;
    aBoard.setUnit(Board2D::UCentimeter);

    Point low(-1,-1);
    Point up(3,3);
    Domain aDomain( low,up );

    {//1cellsRange
      Curve::SCellsRange r = c1.getSCellsRange(); 
      
      trace.info() << r << endl;
      
      aBoard << SetMode(aDomain.className(), "Grid") << aDomain; 
      aBoard << r; 
      aBoard.saveEPS( "My1CellsRange.eps", Board2D::BoundingBox, 5000 );
      aBoard.clear(); 
    }
    {//IncidentPointsRange
      //! [GridCurveIncidentPointsRangeIO]
      Curve::IncidentPointsRange r = c1.getIncidentPointsRange(); 
      
      trace.info() << r << endl;
      
      aBoard << SetMode(aDomain.className(), "Grid") << aDomain; 
      aBoard << r; 
      aBoard.saveEPS( "MyIncidentPointsRange.eps", Board2D::BoundingBox, 5000 );
      //! [GridCurveIncidentPointsRangeIO]
      aBoard.clear(); 
    }
    {//CodesRange
      Curve::CodesRange r = c1.getCodesRange(); 
      
      trace.info() << r << endl;
    }
  }
  
  trace.emphase() << "Ranges Iterators" << endl;
  {
    typedef Curve::CodesRange Range; 
    Range r = c1.getCodesRange(); 
    
    //! [GridCurveRangeIterators]
    trace.info() << "\t iterate over the range" << endl;
    Range::ConstIterator it = r.begin(); 
    Range::ConstIterator itEnd = r.end(); 
    for ( ; it != itEnd; ++it)
    {
      trace.info() << *it;
    }
    trace.info() << endl;
    
    trace.info() << "\t iterate over the range in the reverse way" << endl;
    Range::ConstReverseIterator rit = r.rbegin(); 
    Range::ConstReverseIterator ritEnd = r.rend(); 
    for ( ; rit != ritEnd; ++rit) 
    {
      trace.info() << *rit;
    }
    trace.info() << endl;
      
    trace.info() << "\t iterate over the range in a circular way" << endl;
    Range::ConstCirculator c = r.c();
    //set the starting element wherever you want... 
    for (unsigned i = 0; i < 20; ++i) ++c; 
    //... and circulate
    Range::ConstCirculator cend( c );
    do 
    {
      trace.info() << *c;
      c++;
    } while (c!=cend);
    trace.info() << endl;
    //! [GridCurveRangeIterators]    
    
    trace.info() << "\t Generic function working with any (circular)iterator" << endl;
    displayAll<Range::ConstIterator>(r.begin(),r.end()); 
    displayAll<Range::ConstReverseIterator>(r.rbegin(),r.rend()); 
    displayAll<Range::ConstCirculator>(r.c(),r.c()); 
    
  }
  
  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
