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
 * @file doc-examples/kernelDomain.cpp
 * @ingroup Examples
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/03/05
 *
 * An example file named kernelDomain.
 *
 * This file is part of the DGtal library.
 */



/**
 * Example of DGtal kernel with Domain.
 * @see \ref sectSpace
 * \image html kernel-domain-it-arrow.png "Iteration over a domain with displacements depicted as arrows."
 * \example doc-examples/kernelDomain.cpp
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
  trace.beginBlock ( "Example kernelDomain" );
  
  typedef DGtal::Z2i::Space MySpace; 
  
  //Point lying in the Z2i::Space
  typedef MySpace::Point MyPoint;
  
  MyPoint p(13,-5);
  
  trace.info() << "Point p="<<p<<endl;
  
  //We create a domain
  typedef HyperRectDomain<MySpace> MyDomain;
  MyPoint a(-3,-4);
  MyPoint b(10,4);
  MyDomain domain(a,b);
  
  //We trace  domain information
  trace.info() <<"Domain domain="<<domain<<endl;

  //We generate a board
  Board2D board;
  board << domain;
  board.saveSVG("kernel-domain.svg");

  MyPoint c(5,1);

  if ( domain.isInside(c) )
    trace.info() << "C is inside the domain"<<endl;
  else
    trace.info() << "C is outside the domain"<<endl;
    
  board << c;
  board.saveSVG("kernel-domain-point.svg");
  

  //PointVector example
  MyPoint q;
  MyPoint::Coordinate coord = 24;
  for(MySpace::Dimension d = 0 ; d < MySpace::dimension; d++)
    q[d] = coord;
  trace.info()<<"Q="<<q<<endl;

  MyPoint r;
  for(MyPoint::Iterator it=r.begin(), itend=r.end() ; 
      it != itend;
      ++it)
    (*it) = coord;
  trace.info()<<"R="<<r<<endl;


  //We scan the domain
  for( MyDomain::ConstIterator it = domain.begin(), itend = domain.end();
       it != itend;   
       ++it)
    trace.info() << "Processing point"<< (*it) << endl;
   

  board.clear();
  board << domain;
  //We draw an arrow between two consecutive points during the iteration.
  MyDomain::ConstIterator itPrec = domain.begin();
  MyDomain::ConstIterator it = itPrec;
  MyDomain::Vector shift;
  ++it;

  board << (*itPrec); //We display the first point as a pixel.
  for( MyDomain::ConstIterator itend = domain.end();
       it != itend;   
       ++it, ++itPrec)
    {
      shift =   (*it) -(*itPrec);
      Display2DFactory::draw(board, shift, (*itPrec));
    }
  board.saveSVG("kernel-domain-it-arrow.svg");

  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
