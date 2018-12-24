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
 * @file testDistanceTransformationMetrics.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/12/30
 *
 * Functions for testing class DistanceTransformation on several metrics.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/volumes/distance/DistanceTransformation.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/InexactPredicateLpSeparableMetric.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;


//Generate Random seeds
template<typename Image>
void randomSeeds(Image &input, const unsigned int nb, const int value)
{
  typename Image::Point p, low = input.domain().lowerBound(), up = input.domain().upperBound();
  typename Image::Vector ext;
  
  for (Dimension i = 0; i < Image::Domain::dimension; i++)
    ext[i] = up[i] - low[i] + 1;
  
  
  for (unsigned int k = 0 ; k < nb; k++)
  {
    for (unsigned int dim = 0; dim < Image::dimension; dim++)
    {
      p[dim] = rand() % (ext[dim]) +  low[dim];
    }
    input.setValue(p, value);
  }
}

//Bruteforce quadratic computation of the distance map
template<typename Image, typename Pred, typename Metric>
bool checkVoronoi(Image &result,Pred &pointPredicate, Metric &metric)
{
  typedef typename Image::Domain Domain;
  
  for(typename Domain::ConstIterator it = result.domain().begin(),
          itend=result.domain().end();
        it != itend; ++it)
  {
    typename Metric::Value dist = result(*it);
    
    for(typename Domain::ConstIterator itbis = result.domain().begin(),
        itendbis=result.domain().end();
        itbis != itendbis; ++itbis)
    {
      if (!pointPredicate(*itbis) && (metric(*it, *itbis) < dist))
      {
        trace.error()<< "Error in Voronoi map at "<< *it<<" computed="<<dist<<" but find="<<metric(*it, *itbis) << std::endl;
        return false;
      }
    }
  }
  return true;
}


template <typename Space, int norm>
bool testCompareExactBruteForce(unsigned int size, unsigned int nb)
{
  trace.beginBlock("Checking Exact/Inexct predicate metrics");
  typedef ExactPredicateLpSeparableMetric<Space, norm> MetricEx;
  typedef HyperRectDomain<Space> Domain;
  typedef typename Space::Point Point;
  typedef DigitalSetBySTLSet<Domain> Set;
  typedef functors::NotPointPredicate<Set> NegPredicate;
  
  Point low=Point::diagonal(0),
  up=Point::diagonal(size);
  
  Domain domain(low,up);
  Set set(domain);
  
  for(unsigned int i = 0; i<nb; ++i)
  {
    Point p;
    for(unsigned int dim=0;  dim<Space::dimension;++dim)
      p[dim]  = rand() % size;
    set.insert(p);
  }
  
  trace.info()<< "Testing metrics "<<MetricEx()<<std::endl;
  trace.info()<< "Testing space dimension "<<Space::dimension<<std::endl;
  trace.info()<< "Inserting "<<set.size() << " points."<<std::endl;
  
  NegPredicate negPred(set);
  
  typedef DistanceTransformation<Space, NegPredicate, MetricEx> DTEx;
  MetricEx metricEx;
  DTEx dtex(&domain, &negPred, &metricEx);
  
  bool res=checkVoronoi(dtex, negPred, metricEx);
  
  trace.endBlock();
  return res;
}



template <typename Space>
bool testCompareInexactBruteForce(double norm, unsigned int size, unsigned int nb)
{
  trace.beginBlock("Checking Exact/Inexct predicate metrics");
  typedef InexactPredicateLpSeparableMetric<Space> MetricInex;
  typedef HyperRectDomain<Space> Domain;
  typedef typename Space::Point Point;
  typedef DigitalSetBySTLSet<Domain> Set;
  typedef functors::NotPointPredicate<Set> NegPredicate;
  
  Point low=Point::diagonal(0),
  up=Point::diagonal(size);
  
  Domain domain(low,up);
  Set set(domain);
  
  for(unsigned int i = 0; i<nb; ++i)
  {
    Point p;
    for(unsigned int dim=0;  dim<Space::dimension;++dim)
      p[dim]  = rand() % size;
    set.insert(p);
  }
  
  trace.info()<< "Testing metrics "<<MetricInex(norm)<<std::endl;
  trace.info()<< "Testing space dimension "<<Space::dimension<<std::endl;
  trace.info()<< "Inserting "<<set.size() << " points."<<std::endl;
  
  NegPredicate negPred(set);
  
  typedef DistanceTransformation<Space, NegPredicate, MetricInex> DTIn;
  MetricInex metricInex(norm);
  DTIn dtinex(&domain, &negPred, &metricInex);
  
  bool res=checkVoronoi(dtinex, negPred, metricInex);
  
  trace.endBlock();
  return res;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class DistanceTransformationMetrics" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testCompareExactBruteForce<Z2i::Space, 2>(16, 8)
  && testCompareExactBruteForce<Z2i::Space, 1>(16, 8)
  && testCompareExactBruteForce<Z3i::Space, 2>(16, 8)
  && testCompareExactBruteForce<Z2i::Space, 4>(16, 8)
  && testCompareInexactBruteForce<Z2i::Space>(2.0,16, 8) 
  && testCompareInexactBruteForce<Z2i::Space>(1.33,16, 8)
  && testCompareInexactBruteForce<Z2i::Space>(2.6,16, 8) 
  && testCompareInexactBruteForce<Z3i::Space>(2.44,10, 5)
  && testCompareInexactBruteForce<Z3i::Space>(12.3,10, 5); 
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
