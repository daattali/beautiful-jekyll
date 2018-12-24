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
 * @file testKanungo.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/03/06
 *
 * Functions for testing class Kanungo.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/volumes/KanungoNoise.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/kernel/CPointPredicate.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Kanungo.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testKanungo2D()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing 2DNoise ..." );
  
  Z2i::Domain domain(Z2i::Point(0,0), Z2i::Point(128,128));
  
  Z2i::DigitalSet set(domain);
  
  Shapes<Z2i::Domain>::addNorm2Ball( set , Z2i::Point(64,64), 30);
  
  Board2D board;
  board << domain << set;
  board.saveSVG("input-set-kanungo.svg");
  
  board.clear();
  
  //Noisification
  KanungoNoise<Z2i::DigitalSet, Z2i::Domain> nosifiedObject(set,domain,0.5);
  board << domain ;
  for(Z2i::Domain::ConstIterator it = domain.begin(), itend=domain.end(); it != itend; ++it)
    if (nosifiedObject( * it ))
      board << *it;
  board.saveSVG("output-set-kanungo-0.5.svg");
  
  
  board.clear();
  //Noisification
  KanungoNoise<Z2i::DigitalSet, Z2i::Domain> nosifiedObject2(set,domain,0.1);
  board << domain ;
  for(Z2i::Domain::ConstIterator it = domain.begin(), itend=domain.end(); it != itend; ++it)
    if (nosifiedObject2( * it ))
      board << *it;
  board.saveSVG("output-set-kanungo-0.1.svg");
  
  nbok += true ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;
  trace.endBlock();
  
  return nbok == nb;
}

bool CheckingConcept()
{
  BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate < KanungoNoise<Z2i::DigitalSet, Z2i::Domain> > ));
  return true;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class Kanungo" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = CheckingConcept() && testKanungo2D(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
