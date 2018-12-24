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
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 *
 *
 * @date 2010/05/25
 *
 * This file is part of the DGtal library
 */

/**
 * Description of test_ImageSpanIterators <p>
 * Aim: simple test of ImageContainerBySTLMap
 */

#include <cstdio>
#include <cmath>
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/ImageContainerBySTLVector.h"

using namespace DGtal;
using namespace std;


bool testSpanIterators()
{
    typedef SpaceND<3> Space3Type;
    typedef Space3Type::Point Point;
    typedef HyperRectDomain<Space3Type> TDomain;
    typedef ImageContainerBySTLVector<TDomain, double> TContainerV;

    const Point::Component t[ ] = { 0, 0, 0};
    const Point::Component t2[ ] = { 5, 5, 5};
    const Point::Component t3[ ] = { 0, 0, 0};
    Point a ( t );
    Point b ( t2 );
    Point c( t3 );

    trace.beginBlock("Test of Concepts");
    TContainerV myImageV ( TDomain(a,b ));

    double cpt=0;
    //Image Construction
    for ( TContainerV::Iterator it = myImageV.begin();
            it != myImageV.end();
            ++it)
    {
      (*it) = cpt ;
      cpt++;
    }


    //We process a 1D slice
    trace.info()<<"Slice dim 0 ";
    for ( TContainerV::SpanIterator it = myImageV.spanBegin(c,0), itend = myImageV.spanEnd(c,0);
    it != itend;
    ++it)
      trace.info() << (*it)<<" ";
    trace.info() << endl;

    //We process a 1D slice
    trace.info()<<"Slice dim 1 ";
    for ( TContainerV::SpanIterator it = myImageV.spanBegin(c,1), itend = myImageV.spanEnd(c,1);
    it != itend;
    ++it)
      trace.info() << (*it)<<" ";
    trace.info() << endl;

    //We process a 1D slice
    trace.info()<<"Slice dim 2 ";
    for ( TContainerV::SpanIterator it = myImageV.spanBegin(c,2), itend = myImageV.spanEnd(c,2);
    it != itend;
    ++it)
      trace.info() << (*it)<<" ";
    trace.info() << endl;


    //We process a 1D slice to set a value
    trace.info()<<"SetValue Slice dim 1 "<<endl;
    for ( TContainerV::SpanIterator it = myImageV.spanBegin(c,1), itend = myImageV.spanEnd(c,1);
    it != itend;
    ++it)
      myImageV.setValue(it, 12);

    //We check the a 1D slice
    trace.info()<<"Check Slice dim 1 ";
    for ( TContainerV::SpanIterator it = myImageV.spanBegin(c,1), itend = myImageV.spanEnd(c,1);
    it != itend;
    ++it)
      trace.info() << (*it)<<" ";
    trace.info() << endl;



    trace.endBlock();

    return true;

}



int main()
{

    if ( testSpanIterators())
        return 0;
    else
        return 1;
}

/** @ingroup Tests **/
