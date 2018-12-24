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
 * @file
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 *
 *
 * @date 2010/05/30
 *
 * This file is part of the DGtal library
 */

/**
 * Description of test_DomainSpanIterator <p>
 * Aim: simple test of \ref LineDomain
 */

#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"


using namespace DGtal;
using namespace std;


/**
* Simple test of Span iterators on a 4D digital domain
*
**/
bool testIterator()
{

  trace.emphase() << "Iterator 4d: ";
  typedef SpaceND<4> SpaceType4D;
  typedef SpaceType4D::Point TPoint4D;
  const SpaceType4D::Integer t4D[ ] = { 1, 1, 1, 1};
  const SpaceType4D::Integer t4D2[ ] = { 3, 6, 3, 3};
  const SpaceType4D::Integer t4D3[ ] = { 1, 2, 1, 1};
  TPoint4D a4D ( t4D );
  TPoint4D b4D ( t4D2 );
  TPoint4D c4D ( t4D3);

  trace.beginBlock("Span Domain iterator test");
  ///Domain construction
  HyperRectDomain<SpaceType4D> mySpan ( a4D, b4D );


  trace.emphase() << mySpan << std::endl;

  ///iterates from  {1,2,1,1} to { 3,6,3,3} along the dimension 1
  for ( HyperRectDomain<SpaceType4D>::ConstSubRange::ConstIterator 
    it = mySpan.subRange(1, c4D).begin();
  it != mySpan.subRange(1, c4D).end(); ++it )
    trace.info() << ( *it ) << std::endl;

  trace.endBlock();
  return mySpan.isValid();
}


int main()
{

  if ( testIterator() )
    return 0;
  else
    return 1;
}


/** @ingroup Tests **/
