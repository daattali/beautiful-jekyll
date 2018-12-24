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
 * @file testBinomialConvolver.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2011/07/06
 *
 * Functions for testing class Signal.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/geometry/curves/BinomialConvolver.h"
#include "DGtal/geometry/curves/estimation/CCurveLocalGeometricEstimator.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Signal.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testBinomialConvolver()
{
  trace.beginBlock ( "Testing block ..." );
  typedef PointVector<2, double> RealPoint;
  std::vector< RealPoint > points;
  points.push_back( RealPoint( { 0.0, 0.0 } ) ); 
  points.push_back( RealPoint( { 1.0, 0.0 } ) ); 
  points.push_back( RealPoint( { 2.0, 0.0 } ) ); 
  points.push_back( RealPoint( { 2.0, 1.0 } ) ); 
  points.push_back( RealPoint( { 2.0, 2.0 } ) ); 
  points.push_back( RealPoint( { 1.0, 2.0 } ) ); 
  points.push_back( RealPoint( { 0.0, 2.0 } ) ); 
  points.push_back( RealPoint( { 0.0, 1.0 } ) ); 
  
  typedef std::vector< RealPoint >::const_iterator ConstIteratorOnPoints;
  typedef BinomialConvolver<ConstIteratorOnPoints, double> MyBinomialConvolver;
  
  for ( unsigned int n = 1; n < 10; ++n )
    {
      trace.info() << "Binomial convolver n=" << n << std::endl;
      MyBinomialConvolver bcc( n );
      bcc.init( 1.0, points.begin(), points.end(), true );
      for ( unsigned int i = 0; i < 8; ++i )
        std::cout << i
            << " " << bcc.x( i ).first
            << " " << bcc.x( i ).second
            << " " << bcc.tangent( i ).first
            << " " << bcc.tangent( i ).second
            << " " << bcc.curvature( i )
            << std::endl;
    }
  unsigned int n = MyBinomialConvolver::suggestedSize( 1.0, points.begin(), points.end() );
  trace.info() << "Binomial convolver suggested n=" 
         << n
         << std::endl;

  typedef TangentFromBinomialConvolverFunctor< MyBinomialConvolver, RealPoint >
    TangentBCFct;
  typedef CurvatureFromBinomialConvolverFunctor< MyBinomialConvolver, double >
    CurvatureBCFct;
  typedef BinomialConvolverEstimator< MyBinomialConvolver, TangentBCFct> BCTangentEstimator;
  typedef BinomialConvolverEstimator< MyBinomialConvolver, CurvatureBCFct> BCCurvatureEstimator;
  BOOST_CONCEPT_ASSERT(( concepts::CCurveLocalGeometricEstimator< BCTangentEstimator > ));
  BOOST_CONCEPT_ASSERT(( concepts::CCurveLocalGeometricEstimator< BCCurvatureEstimator > ));
  BCTangentEstimator tgtEstimator;
  BCCurvatureEstimator curvEstimator;

  tgtEstimator.init( 1.0, points.begin(), points.end(), true );
  curvEstimator.init( 1.0, points.begin(), points.end(), true );
  for ( ConstIteratorOnPoints it = points.begin(), it_end = points.end();
  it != it_end; ++it )
    {
      std::cout << *it 
    << " " << tgtEstimator.eval( it ) 
    << " " << curvEstimator.eval( it ) 
    << std::endl;
    }
  trace.endBlock();
  
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class BinomialConvolver" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testBinomialConvolver(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
