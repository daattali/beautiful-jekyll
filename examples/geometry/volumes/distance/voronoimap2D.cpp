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
 * @file geometry/volumes/distance/voronoimap2D.cpp
 * @ingroup Examples
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/01/17
 *
 * An example file named voronoimap2D.
 *
 * This file is part of the DGtal library.
 */

/**
   Example of a Voronoi map construction in dimension 2 for the
   Euclidean metric.

   @see \ref voronoiSect
   \image html voronoimap-dt.png "Distance transformation for the l_2 metric."
   \example geometry/volumes/distance/voronoimap2D.cpp
*/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"

//! [Voro2D-header]
#include "DGtal/kernel/BasicPointPredicates.h"
#include "DGtal/images/SimpleThresholdForegroundPredicate.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/VoronoiMap.h"
#include "DGtal/geometry/volumes/distance/DistanceTransformation.h"

#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/boards/Board2D.h"
//! [Voro2D-header]

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::functors;

///////////////////////////////////////////////////////////////////////////////

int main( int /*argc*/, char** /*argv*/ )
{
  trace.beginBlock ( "Example voronoimap2D" );

  //! [Voro2D-Metric]
  typedef ExactPredicateLpSeparableMetric<Z2i::Space, 2> L2Metric;
  L2Metric l2;
  //! [Voro2D-Metric]

  //! [Voro2D-SmallImage]
  Z2i::Point lower(0,0);
  Z2i::Point upper(16,16);
  Z2i::Domain domain(lower,upper);

  Z2i::DigitalSet set(domain);
  set.insertNew(Z2i::Point(2,3));
  set.insertNew(Z2i::Point(7,15));
  set.insertNew(Z2i::Point(12,5));
  Board2D board;

  board<< domain << set;
  board.saveSVG("voronoimap-inputset.svg");
  //! [Voro2D-SmallImage]

  //! [Voro2D-Predicate]
  typedef NotPointPredicate<Z2i::DigitalSet> NotPredicate;
  NotPredicate notSetPred(set);
  //! [Voro2D-Predicate]

  //! [Voro2D-Voro]
  typedef VoronoiMap<Z2i::Space, NotPredicate, L2Metric > Voronoi2D;
  Voronoi2D voronoimap(domain,notSetPred,l2);
  //! [Voro2D-Voro]

  //! [Voro2D-trace]
  board.clear();
  board << domain;
  for(Voronoi2D::Domain::ConstIterator it = voronoimap.domain().begin(),
      itend = voronoimap.domain().end(); it != itend; ++it)
  {
    Voronoi2D::Value site = voronoimap( *it );   //closest site to (*it)
    if (site != (*it))
      Display2DFactory::draw( board,   site - (*it), (*it)); //Draw an arrow
  }
  board.saveSVG("voronoimap-voro.svg");
  //! [Voro2D-trace]

  //! [Voro2D-traceCell]
  board.clear();
  for(Voronoi2D::Domain::ConstIterator it = voronoimap.domain().begin(),
      itend = voronoimap.domain().end(); it != itend; ++it)
  {
    Voronoi2D::Value site = voronoimap( *it );   //closest site to (*it)
    unsigned char c = (site[1]*13 + site[0] * 7) % 256; //basic hashfunction
    board << CustomStyle( (*it).className(), new CustomColors(Color(c,c,c),Color(c,c,c)))
      << (*it);
  }
  board.saveSVG("voronoimap-cells.svg");
  //! [Voro2D-traceCell]


  //! [Voro2D-l8Metric]
  typedef ExactPredicateLpSeparableMetric<Z2i::Space, 8> L8Metric;
  L8Metric l8;
  typedef VoronoiMap<Z2i::Space, NotPredicate, L8Metric > Voronoi2D_l8;
  Voronoi2D_l8 voronoimap_l8(domain,notSetPred,l8);
  board.clear();
  board << domain;
  for(Voronoi2D_l8::Domain::ConstIterator it = voronoimap_l8.domain().begin(),
      itend = voronoimap_l8.domain().end(); it != itend; ++it)
  {
    Voronoi2D::Value site = voronoimap_l8( *it );   //closest site to (*it)
    unsigned char c = (site[1]*13 + site[0] * 7) % 256; //basic hashfunction
    board << CustomStyle( (*it).className(), new CustomColors(Color(c,c,c),Color(c,c,c)))
          << (*it);
  }
  board.saveSVG("voronoimap-vorol8.svg");
  //! [Voro2D-l8Metric]

  //! [Voro2D-DT]
  typedef DistanceTransformation<Z2i::Space, NotPredicate, L2Metric > DT;
  DT dt(domain,notSetPred,l2);
  board.clear();
  board << domain;

  //Fast max computation on the range value
  DT::Value maxDT=0.0;
  for(DT::ConstRange::ConstIterator it = dt.constRange().begin(), itend = dt.constRange().end();
      it != itend ; ++it)
    if ((*it)>maxDT) maxDT = (*it);

  //Colormap
  HueShadeColorMap<DT::Value,1> hueMap(0.0,maxDT);

  //Drawing
  for(DT::Domain::ConstIterator it = dt.domain().begin(),
      itend = dt.domain().end(); it != itend; ++it)
  {
    DT::Value dist = dt( *it );   //distance to closest site to (*it)
    board << CustomStyle( (*it).className(), new CustomColors( hueMap(dist), hueMap(dist)))
          << (*it);
  }
  board.saveSVG("voronoimap-dt.svg");
  //! [Voro2D-DT]


  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
