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
 * @file doc-examples/range.cpp
 * @ingroup Examples
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * @author Guillaume Damiand
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/04/04
 *
 * An example file named range.
 *
 * This file is part of the DGtal library.
 */



/**
 * Example of range on Domain.
 *  @see \ref sectSpace
 *  \example doc-examples/range.cpp
 */


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/io/boards/Board2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main()
{
  trace.beginBlock ( "Example range" );
  
  typedef SpaceND<3> TSpace;  
  TSpace::Point a(1, 1, 1);
  TSpace::Point b(5, 5, 5);
  HyperRectDomain<TSpace> domain(a,b);

  std::vector<TSpace::Dimension> v(2); v[0]=2; v[1]=1;
  TSpace::Point c(3,1,1);
  for( HyperRectDomain<TSpace>::ConstSubRange::ConstReverseIterator 
   it = domain.subRange(v, c).rbegin(), itend =  domain.subRange(v, c).rend();
       it != itend; 
       ++it)
    trace.info() << "Processing point"<< (*it) << endl;

  trace.endBlock();

  trace.beginBlock ( "Example range with CPP11 initializer list" );
  
  for( HyperRectDomain<TSpace>::ConstSubRange::ConstReverseIterator 
   it = domain.subRange({2,1}, c).rbegin(), itend =  domain.subRange({2,1}, c).rend();
       it != itend; 
       ++it)
    trace.info() << "Processing point"<< (*it) << endl;
  
  trace.endBlock();


  HyperRectDomain<TSpace> domain2;
  domain2=domain;

  for( HyperRectDomain<TSpace>::ConstSubRange::ConstReverseIterator 
   it = domain.subRange({2,1}, c).rbegin(), itend =  domain.subRange({2,1}, c).rend();
       it != itend; 
       ++it)
    trace.info() << "Processing point"<< (*it) << endl;

  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
