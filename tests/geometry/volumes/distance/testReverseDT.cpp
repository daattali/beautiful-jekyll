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
 * @file testReverseDT.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/03/03
 *
 * Functions for testing class ReverseDT.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/geometry/volumes/distance/DistanceTransformation.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/ReverseDistanceTransformation.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/images/SimpleThresholdForegroundPredicate.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::functors;



template<typename Image>
void randomSeeds(Image &input, const unsigned int nb, const int value)
{
  typename Image::Point p, low = input.lowerBound();
  typename Image::Vector ext;

  ext = input.extent();

  for (unsigned int k = 0 ; k < nb; k++)
  {
    for (unsigned int dim = 0; dim < Image::dimension; dim++)
    {
      p[dim] = rand() % (ext[dim]) +  low[dim];
    }
    input.setValue(p, value);
  }
}



///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ReverseDT.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testReverseDT()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing Reverse DT in 2D ..." );
  
  Z2i::Point a (2, 2 );
  Z2i::Point b ( 15, 15 );

  typedef ImageSelector< Z2i::Domain,  int>::Type Image;
  Image image (Z2i::Domain( a, b ));
  
  for ( unsigned k = 0; k < 49; k++ )
    {
      a[0] = ( k / 7 ) + 5;
      a[1] = ( k % 7 ) + 5;
      image.setValue ( a, 128 );
    }

  a = Z2i::Point(2,2);
 
  typedef SimpleThresholdForegroundPredicate<Image> Predicate;
  Predicate aPredicate(image,0);
 
  typedef ExactPredicateLpSeparableMetric<Z2i::Space, 2> L2Metric;
  Z2i::Domain dom(a,b);
  L2Metric l2;
  DistanceTransformation<Z2i::Space, Predicate, L2Metric > dt(&dom, &aPredicate, &l2);

  trace.info() << dt<< std::endl;
  //ReverseDT  
  trace.warning()<<"DT:"<<endl;
  DistanceTransformation<Z2i::Space, Predicate, L2Metric >::ConstRange::ConstIterator it = dt.constRange().begin();
  for (unsigned int y = 2; y < 16; y++)
    {
    for (unsigned int x = 2; x < 16; x++)
    {
      std::cout << (*it) << " ";
      ++it;
    }
    std::cout << std::endl;
  }

  typedef ReverseDistanceTransformation< DistanceTransformation<Z2i::Space, Predicate, L2Metric > , Z2i::L2PowerMetric > RDT;
  Z2i::L2PowerMetric l2power;
  RDT reverseDT(&dom,&dt,&l2power);
  

  for(unsigned int j=2; j<16; j++)
    {
      for(unsigned int i=2; i<16; i++)
	trace.info()<< reverseDT.getPowerVector(Z2i::Point(i,j))[0]<<","<<reverseDT.getPowerVector(Z2i::Point(i,j))[1]<<" ";
      trace.info()<<std::endl;
    }

  trace.warning()<<"REDT:"<<endl;
  RDT::ConstRange::ConstIterator it2 = reverseDT.constRange().begin();
  for (unsigned int y = 2; y < 16; y++)
    {
    for (unsigned int x = 2; x < 16; x++)
    {
      std::cout << (*it2) << " ";
      ++it2;
    }
    std::cout << std::endl;
  }

  //Checking
  bool ok=true;
  RDT::ConstRange::ConstIterator itrec = reverseDT.constRange().begin(), itend = reverseDT.constRange().end();
  Image::ConstIterator  itinit = image.begin();
  for( ; itrec != itend; ++itrec,++itinit)
    if ((*itrec) >= 0)
      ok = ok & ((*itinit) == 0);

  
  trace.info() << "vector (4,7)= "<< reverseDT.getPowerVector(Z2i::Point(4,7))<<std::endl;
  nbok += (reverseDT.getPowerVector(Z2i::Point(4,7))==Z2i::Point(5,7)) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "ok" << std::endl;
  
  trace.info() << "dist (4,7)= "<< reverseDT.metricPtr()->exactDistanceRepresentation(Z2i::Point(4,7), Z2i::Point(5,7))<<std::endl;
  nbok += (reverseDT.metricPtr()->exactDistanceRepresentation(Z2i::Point(4,7), Z2i::Point(5,7))==1) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true == true" << std::endl;
 
  trace.info() << "power (4,7)= "<< reverseDT(Z2i::Point(4,7))<<std::endl;
  nbok += (reverseDT(Z2i::Point(4,7))==0) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true == true" << std::endl;
 



  nbok += ok ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true == true" << std::endl;
  trace.endBlock();
  
  return nbok == nb;
}

bool testReverseDTL1()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing Reverse DT in 2D with L1 metric ..." );
  
  Z2i::Point a (2, 2 );
  Z2i::Point b ( 15, 15 );

  typedef ImageSelector< Z2i::Domain, unsigned int>::Type Image;
  Image image ( Z2i::Domain( a, b ));
  
  for ( unsigned k = 0; k < 49; k++ )
    {
      a[0] = ( k / 7 ) + 5;
      a[1] = ( k % 7 ) + 5;
      image.setValue ( a, 128 );
    }
  a = Z2i::Point(2, 2 );
 
 
  typedef SimpleThresholdForegroundPredicate<Image> Predicate;
  Predicate aPredicate(image,0);
  Z2i::Domain dom= image.domain();
  typedef ExactPredicateLpSeparableMetric<Z2i::Space, 1> L1Metric;
  L1Metric l1;
  DistanceTransformation<Z2i::Space, Predicate, L1Metric> dt(&dom, &aPredicate, &l1);


  //ReverseDT  
  trace.warning()<<"DT:"<<endl;
  DistanceTransformation<Z2i::Space, Predicate, L1Metric>::ConstRange::ConstIterator it = dt.constRange().begin();
  for (unsigned int y = 2; y < 16; y++)
    {
    for (unsigned int x = 2; x < 16; x++)
    {
      std::cout << (int)(*it) << " ";
      ++it;
    }
    std::cout << std::endl;
  }
 
  typedef ReverseDistanceTransformation< DistanceTransformation<Z2i::Space, Predicate, L1Metric>, Z2i::L1PowerMetric > RDT;
  Z2i::L1PowerMetric l1power;
  RDT reverseDT(&dom, &dt, &l1power);
  
  
  trace.warning()<<"Power"<<std::endl;
  for(unsigned int j=2; j<16; j++)
    {
      for(unsigned int i=2; i<16; i++)
	trace.info()<< reverseDT.getPowerVector(Z2i::Point(i,j))[0]<<","<<reverseDT.getPowerVector(Z2i::Point(i,j))[1]<<" ";
      trace.info()<<std::endl;
    }

  trace.warning()<<"REDT:"<<endl;
  RDT::ConstRange::ConstIterator it2 = reverseDT.constRange().begin();
  for (unsigned int y = 2; y < 16; y++)
    {
    for (unsigned int x = 2; x < 16; x++)
    {
      std::cout << (int)(*it2) << " ";
      ++it2;
    }
    std::cout << std::endl;
  }

  //Checking
  bool ok=true;
  RDT::ConstRange::ConstIterator itrec = reverseDT.constRange().begin(), itend = reverseDT.constRange().end();
  Image::ConstIterator  itinit = image.begin();
  for( ; itrec != itend; ++itrec,++itinit)
    if ((*itrec) >= 0)
      ok = ok & ((*itinit) == 0);
  
  nbok += ok ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true == true" << std::endl;
  trace.endBlock();  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class ReverseDT" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testReverseDT()
    && testReverseDTL1(); // && ... other tests
  
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
