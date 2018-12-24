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
 * @file testSphericalAccumulator.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/09/18
 *
 * Functions for testing class SphericalAccumulator.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/tools/SphericalAccumulator.h"
/////////////////////ddzad//////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class SphericalAccumulator.
///////////////////////////////////////////////////////////////////////////////

bool testSphericalAccumulator()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing Spherical Accumulator ..." );
  
  typedef Z3i::RealVector Vector;

  SphericalAccumulator<Vector> accumulator(10);
  trace.info()<< accumulator << std::endl;

  //testing insert
  accumulator.addDirection( Vector(1,1,1));
  accumulator.addDirection( Vector(1.1,1.1,1.1));
  nbok += (accumulator.samples() == 2) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "insert dirs" << std::endl;
  trace.info()<< accumulator << std::endl;
  
  //testing clear
  accumulator.clear();
  trace.info()<< accumulator << std::endl;
  nbok += (accumulator.samples() == 0) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "clear" << std::endl;
  
  //testing bin
  accumulator.addDirection( Vector(1,1,1));
  accumulator.addDirection( Vector(1.1,1.1,1.1));
  trace.info()<< accumulator << std::endl;
  typedef SphericalAccumulator<Vector>::Size Size;
  Size i,j;
  accumulator.binCoordinates( Vector(1,1,1).getNormalized(), i,j);
  trace.info() << "Got coordinates ("<<i<<","<<j<<")"<<std::endl; 
  trace.info() << "Count(i,j) = "<< accumulator.count(i,j) <<std::endl;
  nbok += (accumulator.count(i,j) == 2) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "bin with 2dirs" << std::endl;
  trace.info()<< accumulator << std::endl;
 
  trace.info() << "Representative(i,j) = "<< accumulator.representativeDirection(i,j) <<std::endl;

  //testing ConstIterator
  trace.info() << "Bin values: ";
  SphericalAccumulator<Vector>::ConstIterator itwith2;
  for(SphericalAccumulator<Vector>::ConstIterator it=accumulator.begin(), itend=accumulator.end();
      it != itend;
      ++it)
    {
      trace.info() << *it<<" ";
      if ( (*it) == 2)
	itwith2=it;
    }
  trace.info() << std::endl;
  trace.info() << "Representative(it) = "<< accumulator.representativeDirection(itwith2) <<std::endl;
  nbok += (accumulator.representativeDirection(i,j) == accumulator.representativeDirection(itwith2)) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "representative directions identical" << std::endl;

  Size ii,jj;
  accumulator.binCoordinates(itwith2, ii,jj);
  trace.info() << "Coordinate from (it) = ("<<ii<<","<<jj<<")"<<std::endl;
  nbok += (( i == ii) && (j==jj)) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "coordinates ok" << std::endl;

  trace.endBlock();
  
  return nbok == nb;
}

bool testSphericalMore()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing Spherical Accumulator with more points ..." );
  
  //! [SphericalAccum-init] 
  typedef Z3i::RealVector Vector;
  SphericalAccumulator<Vector> accumulator(6);
  //! [SphericalAccum-init]
  

  trace.info()<< accumulator << std::endl;
  //! [SphericalAccum-add] 
  //Insert some directions
  accumulator.addDirection( Vector(0,1,0));
  accumulator.addDirection( Vector(1,-0.01,0));
  accumulator.addDirection( Vector(1,0.01,-0.01));
  accumulator.addDirection( Vector(1,-0.01,0.01));
  //! [SphericalAccum-add] 

  accumulator.addDirection( Vector(1,0.01,0.01));
  accumulator.addDirection( Vector(1,-.01,-0.01));
  
  trace.info() << "Bin values: ";
  for(SphericalAccumulator<Vector>::ConstIterator it=accumulator.begin(), itend=accumulator.end();
      it != itend;
      ++it)
      trace.info() << *it<<" ";
  trace.info() << std::endl;
  trace.info() << accumulator<<std::endl;
  

  trace.endBlock();
    
  return nbok == nb;
}

bool testSphericalMoreIntegerDir()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing Spherical Accumulator with more Integer points ..." );
  
  typedef Z3i::Vector Vector;
  SphericalAccumulator<Vector> accumulator(5);
  

  trace.info()<< accumulator << std::endl;
  //Insert some directions
  accumulator.addDirection( Vector(0,1,0));
  accumulator.addDirection( Vector(100,-1,0));
  accumulator.addDirection( Vector(100,1,-1));
  accumulator.addDirection( Vector(100,-1,1));
  accumulator.addDirection( Vector(1,1,1));
  
  trace.info() << "Bin values: ";
  for(SphericalAccumulator<Vector>::ConstIterator it=accumulator.begin(), itend=accumulator.end();
      it != itend;
      ++it)
      trace.info() << *it<<" ";
  trace.info() << std::endl;
  trace.info() << accumulator<<std::endl;

  typedef SphericalAccumulator<Vector>::Size Size;
  Size i,j;
  accumulator.maxCountBin(i,j);
  trace.info() << "Max bin= ("<<i<<","<<j<<")"<<std::endl;
  trace.info() << "Max representative= "<<accumulator.representativeDirection(i,j)<<std::endl;
  nbok += ( accumulator.representativeDirection(i,j) == Vector(300,-1,0 )) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "Representative ok" << std::endl;

  trace.endBlock();
    
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class SphericalAccumulator" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testSphericalAccumulator() && testSphericalMore()
    && testSphericalMoreIntegerDir();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
