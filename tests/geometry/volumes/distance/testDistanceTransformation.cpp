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
 * @file testDistanceTransformation.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/09/30
 *
 * Functions for testing class DistanceTransformation.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include "DGtal/base/Common.h"

#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/geometry/volumes/distance/DistanceTransformation.h"
#include "DGtal/geometry/volumes/distance/VoronoiMap.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/InexactPredicateLpSeparableMetric.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/colormaps/GrayscaleColorMap.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/images/SimpleThresholdForegroundPredicate.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::functors;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class DistanceTransformation.
///////////////////////////////////////////////////////////////////////////////

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



/**
 * Example of a test. To be completed.
 *
 */
bool testDistanceTransformation()
{
  bool allfine;

  trace.beginBlock ( "Testing the whole DT computation" );

  typedef SpaceND<2> TSpace;
  typedef TSpace::Point Point;
  typedef HyperRectDomain<TSpace> Domain;
  typedef GrayscaleColorMap<unsigned char> Gray;
  Point a ( 2, 2 );
  Point b ( 15, 15 );
  typedef ImageSelector<Domain, unsigned int>::Type Image;
  Image image ( Domain(a, b ));

  for ( unsigned k = 0; k < 49; k++ )
    {
      a[0] = ( k / 7 ) + 5;
      a[1] = ( k % 7 ) + 5;
      image.setValue ( a, 128 );
    }
  a= Point(2,2);

  typedef SimpleThresholdForegroundPredicate<Image> Predicate;
  Predicate aPredicate(image,0);

  typedef ExactPredicateLpSeparableMetric<TSpace,2> L2Metric;
  L2Metric l2;
  Domain dom(a,b);
  DistanceTransformation<TSpace, Predicate , L2Metric> dt(&dom,&aPredicate,&l2);
  VoronoiMap<Z2i::Space, Predicate, L2Metric> voro(&dom,&aPredicate,&l2);

  Board2D board;
  board.setUnit ( LibBoard::Board::UCentimeter );
  Display2DFactory::drawImage<Gray>(board, image, (unsigned int)0, (unsigned int)255);
  board.saveSVG ( "image-preDT.svg" );
  //We just iterate on the Domain points and print out the point coordinates.
  std::copy ( image.begin(),
              image.end(),
              std::ostream_iterator<unsigned int> ( std::cout, " " ) );

  trace.info()<<std::endl;
  for(int i=2;i<=15;++i)
    {
      for(int j=2;j<=15;++j)
        trace.info()<< image(Point(i,j))<<" ";
      trace.info()<<std::endl;
    }


  trace.warning() << dt << endl;
  trace.info() <<std::endl;

  DistanceTransformation<TSpace, Predicate , L2Metric>::ConstRange::ConstIterator it = dt.constRange().begin();
  DistanceTransformation<TSpace, Predicate , L2Metric>::ConstRange::ConstIterator itend = dt.constRange().end();

  for (; it != itend; ++it)
    {
      std::cout << (*it) << " ";
    }
  std::cout << std::endl;

  trace.info()<<std::endl;
  for(int i=2;i<=15;++i)
    {
      for(int j=2;j<=15;++j)
        trace.info()<< dt(Point(i,j))<<" ";
      trace.info()<<std::endl;
    }


  trace.info()<<std::endl;
  for(int i=2;i<=15;++i)
    {
      for(int j=2;j<=15;++j)
        {
          Point p= dt.getVoronoiVector(Point(i,j));
          if (p==Point(i,j))
            trace.info()<<"-,- ";
          else
            trace.info()<< p[0]<<","<<p[1]<<" ";
        }
      trace.info()<<std::endl;
    }


  allfine = true;

  trace.info()<<std::endl;
  for(int i=2;i<=15;++i)
    {
      for(int j=2;j<=15;++j)
        {
          Point p= voro(Point(i,j));
          if (p != dt.getVoronoiVector(Point(i,j)))
            allfine = false;
          if (p==Point(i,j))
            trace.info()<<"-,- ";
          else
            trace.info()<< p[0]<<","<<p[1]<<" ";
        }
      trace.info()<<std::endl;
    }

  board.clear();
  Display2DFactory::drawImage<Gray>(board, dt, (DGtal::int64_t)0, (DGtal::int64_t)16);
  board.saveSVG ( "image-postDT.svg" );
  trace.info() << dt << endl;
  trace.endBlock();

  return allfine;
}
/**
 * Example of a test. To be completed.
 *
 */
bool testDistanceTransformationNeg()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing the Neg DT computation" );

  typedef Z2i::Space TSpace;
  typedef TSpace::Point Point;
  typedef Z2i::Domain Domain;
  typedef GrayscaleColorMap<unsigned char> Gray;
  Point a ( -10, -10 );
  Point b ( 10, 10 );
  typedef ImageSelector<Domain, unsigned int>::Type Image;
  Image image ( Domain( a, b ));

  for(int y=-10; y<=10;y++)
    for(int x=-10; x<=10;x++)
      {
        if ((abs(x)<7) && (abs(y)<5))
          image.setValue(Point(x,y),1);
        else
          image.setValue(Point(x,y),0);
      }

  typedef SimpleThresholdForegroundPredicate<Image> Predicate;
  Predicate aPredicate(image,0);

  typedef ExactPredicateLpSeparableMetric<TSpace,2> L2Metric;
  L2Metric l2;
  Board2D board;
  board.setUnit ( LibBoard::Board::UCentimeter );
  Display2DFactory::drawImage<Gray>(board, image, (unsigned int)0, (unsigned int)1);
  board.saveSVG ( "image-preDT-neg.svg" );


  for(int y=-10; y<=10;y++)
    {
      for(int x=-10; x<=10;x++)
        {
          std::cout<<image(Point(x,y))<<"  ";
        }
      std::cout<<std::endl;
    }

  trace.info()<<"Domain "<<Domain(a,b)<<std::endl;
  Domain dom(a,b);
  DistanceTransformation<TSpace, Predicate , L2Metric> dt(&dom, &aPredicate, &l2);

  DistanceTransformation<TSpace, Predicate , L2Metric>::Value maxv=0.0;
  for(DistanceTransformation<TSpace, Predicate , L2Metric>::ConstRange::ConstIterator it = dt.constRange().begin(),
        itend = dt.constRange().end();
      it != itend ; ++it)
    if ((*it) > maxv)
      maxv = (*it);

  for(int y=-10; y<=10;y++)
    {
      for(int x=-10; x<=10;x++)
        {
          std::cout<<dt(Point(x,y))<<"  ";
        }
      std::cout<<std::endl;
    }



  trace.warning() << dt << endl;
  trace.warning() << dt.domain() << endl;


  trace.info() << "Exporting..." << endl;
  board.clear();
  Display2DFactory::drawImage<Gray>(board, dt, 0, maxv);
  board.saveSVG ( "image-postDT-neg.svg" );

  trace.info() << "Done..." << endl;

  trace.info() << dt << endl;

  trace.endBlock();

  return nbok == nb;
}


bool testDTFromSet()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing the whole DT computation from a Set" );

  typedef SpaceND<2> TSpace;
  typedef HueShadeColorMap<DGtal::uint64_t, 2> Hue;


  Board2D board;

  AccFlower2D<Z2i::Space> flower(Z2i::Point(0,0), 30, 5,2,0);
  Z2i::Domain domain(flower.getLowerBound(), flower.getUpperBound());
  Z2i::DigitalSet aSet(domain);

  Shapes<Z2i::Domain>::euclideanShaper(aSet, flower);

  // Since 0.6, models of CDigitalSet are models of CPointPredicate.
  // SetPredicate<Z2i::DigitalSet> aPredicate(aSet);
  typedef ExactPredicateLpSeparableMetric<Z2i::Space,2> L2Metric;
  typedef DistanceTransformation<TSpace, Z2i::DigitalSet, L2Metric> L2DT;
  L2Metric l2;
  L2DT dt(&domain,&aSet, &l2);
  typedef ExactPredicateLpSeparableMetric<Z2i::Space,1> L1Metric;
  typedef DistanceTransformation<TSpace, Z2i::DigitalSet, L1Metric> L1DT;
  L1Metric l1;
  L1DT dt1(&domain,&aSet, &l1);

  L2DT::Value maxv = 0;
  for ( L2DT::ConstRange::ConstIterator it = dt.constRange().begin(), itend = dt.constRange().end();
	it != itend; ++it)
    if ( (*it) > maxv)
      maxv = (*it);
  trace.error() << "MaxV="<<maxv<<std::endl;
  Display2DFactory::drawImage<Hue>(board, dt, 0, maxv+1);
  board.saveSVG ( "image-DTSet.svg" );

  board.clear();
  maxv = 0;
  for ( L1DT::ConstRange::ConstIterator it = dt1.constRange().begin(), itend = dt1.constRange().end();
	it != itend; ++it)
    if ( (*it) > maxv)
      maxv = (*it);
  trace.error() << "MaxV="<<maxv<<std::endl;
  Display2DFactory::drawImage<Hue>(board, dt1, 0, maxv+1);
  board.saveSVG ( "image-DTSet-l1.svg" );
  trace.endBlock();

  return nbok == nb;
}

/**
 * Example of a test. To be completed.
 *
 */
bool testDistanceTransformationBorder()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing DT computation with Infinity values at the first step" );

  typedef SpaceND<2> TSpace;
  typedef TSpace::Point Point;
  typedef HyperRectDomain<TSpace> Domain;
  typedef HueShadeColorMap<DGtal::uint64_t, 2> Hue;

  Point a (0, 0 );
  Point b ( 128, 128 );

  typedef ImageSelector<Domain, unsigned int>::Type Image;
  Image image ( Domain(a, b ));

  for ( Image::Iterator it = image.begin(), itend = image.end();it != itend; ++it)
    *it = 128 ;


  randomSeeds(image, 19, 0);

  typedef SimpleThresholdForegroundPredicate<Image> Predicate;
  Predicate aPredicate(image,0);

  typedef ExactPredicateLpSeparableMetric<TSpace, 2> L2Metric;
  L2Metric l2;
  Domain dom(a,b);
  DistanceTransformation<TSpace, Predicate, L2Metric> dt(&dom, &aPredicate, &l2);

  Board2D board;
  board.setUnit ( LibBoard::Board::UCentimeter );
  Display2DFactory::drawImage<Hue>(board, image, (unsigned int)0, (unsigned int)150);
  board.saveSVG ( "image-preDT-border.svg" );

  DistanceTransformation<TSpace, Predicate, L2Metric>::Value maxv = 0;
  for ( DistanceTransformation<TSpace, Predicate, L2Metric>::ConstRange::ConstIterator it = dt.constRange().begin(), itend = dt.constRange().end();it != itend; ++it)
    if ( (*it) > maxv)
      maxv = (*it);

  DistanceTransformation<TSpace, Predicate, L2Metric>::ConstRange::ConstIterator it = dt.constRange().begin();
  for (unsigned int y = 0; y < 33; y++)
    {
      for (unsigned int x = 0; x < 33; x++)
        {
          std::cout << std::setw(4) << (*it) << " ";
          ++it;
        }
      std::cout << std::endl;
    }

  trace.warning() << dt << "MaxV = " << maxv << endl;


  board.clear();
  Display2DFactory::drawImage<Hue>(board, dt, (DGtal::int64_t)0, (DGtal::int64_t)maxv+1);
  board.saveSVG ( "image-postDT-border.svg" );


  trace.info() << dt << endl;

  trace.endBlock();

  return nbok == nb;
}


/**
 * Example of a test. To be completed.
 *
 */
bool testDistanceTransformation3D()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing 3D DT computation" );

  typedef SpaceND<3> TSpace;
  typedef TSpace::Point Point;
  typedef HyperRectDomain<TSpace> Domain;
  Point a ( 0, 0, 0 );
  Point b ( 15, 15, 15 );
  typedef ImageSelector<Domain, unsigned int>::Type Image;
  Image image ( Domain(a, b ));
  Point c(8, 8, 8);
  Domain dom(a, b);

  for (Domain::ConstIterator it = dom.begin(),
       itend = dom.end(); it != itend; ++it)
    {
      if ( ((*it) - c).norm() < 7)
	image.setValue ( *it, 128 );
    }

  typedef SimpleThresholdForegroundPredicate<Image> Predicate;
  Predicate aPredicate(image,0);

  typedef ExactPredicateLpSeparableMetric<TSpace,2> L2Metric;
  L2Metric l2;
  DistanceTransformation<TSpace, Predicate, L2Metric> dt(&dom, &aPredicate,&l2);

  //We display the values on a 2D slice
  for (unsigned int y = 0; y < 16; y++)
    {
      for (unsigned int x = 0; x < 16; x++)
        {
          Point p(x, y, 8);
          std::cout << dt(p) << "   ";
        }
      std::cout << std::endl;
    }


  trace.warning() << dt << endl;

  trace.endBlock();

  return nbok == nb;
}


bool testChessboard()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing DT computation with Infinity values at the first step" );

  typedef SpaceND<2> TSpace;
  typedef TSpace::Point Point;
  typedef HyperRectDomain<TSpace> Domain;
  typedef HueShadeColorMap<DGtal::uint64_t, 2> Hue;

  Point a (0, 0 );
  Point b ( 128, 128 );
  Domain dom(a,b);

  typedef ImageSelector<Domain, unsigned int>::Type Image;
  Image image (  dom );

  for ( Image::Iterator it = image.begin(), itend = image.end();it != itend; ++it)
    (*it) = 128;


  randomSeeds(image, 19, 0);

  typedef SimpleThresholdForegroundPredicate<Image> Predicate;
  Predicate aPredicate(image,0);


  // L_euc metric
  typedef ExactPredicateLpSeparableMetric<TSpace,2> L2Metric;
  L2Metric l2;
  typedef DistanceTransformation<TSpace,Predicate, L2Metric> DT2;
  DT2 dt2(&dom, &aPredicate, &l2);
  DT2 dt2_periodic( &dom, &aPredicate, &l2, {true, true} );

  //L_infinity metric
  //typedef DistanceTransformation<TSpace,Predicate, 0> DT;
  //DT dt(Domain(a,b), aPredicate);;

  //L_1 metric
  typedef ExactPredicateLpSeparableMetric<TSpace,1> L1Metric;
  L1Metric l1;
  typedef DistanceTransformation<TSpace,Predicate, L1Metric> DT1;
  DT1 dt1(&dom,&aPredicate,&l1);
  DT1 dt1_periodic( &dom, &aPredicate, &l1, {true, true} );

  DGtal::int64_t maxv = 0;
  for ( DistanceTransformation<TSpace,Predicate, L2Metric>::ConstRange::ConstIterator it = dt2.constRange().begin(), itend = dt2.constRange().end();it != itend; ++it)
    if ( (*it) > maxv)
      maxv = (*it);

  trace.warning() << dt2 << "MaxV = " << maxv << endl;
  //We display the values on a 2D slice
  for (unsigned int y = 0; y < 16; y++)
    {
      for (unsigned int x = 0; x < 16; x++)
        {
          Point p(x, y);
          std::cout << std::setw(4) << dt2(p) << " ";
        }
      std::cout << std::endl;
    }

  trace.info()<< "Exporting to SVG"<<endl;

  Board2D board;
  board.setUnit ( LibBoard::Board::UCentimeter );
  Display2DFactory::drawImage<Hue>(board, dt2, (DGtal::int64_t)0, (DGtal::int64_t)maxv+1);
  board.saveSVG ( "image-DT-l2.svg" );

  board.clear();
  Display2DFactory::drawImage<Hue>(board, dt2_periodic, (DGtal::int64_t)0, (DGtal::int64_t)maxv+1);
  board.saveSVG ( "image-DT-l2-periodic.svg" );

  trace.info()<< "done"<<endl;



  trace.info()<< "max  L1"<<endl;
  maxv = 0;
  for ( DistanceTransformation<TSpace,Predicate, L1Metric>::ConstRange::ConstIterator it2 = dt1.constRange().begin(),
        itend = dt1.constRange().end();
        it2 != itend; ++it2)
    {
      if ( *it2 > maxv)
        maxv = (*it2);
    }

  trace.info()<< "Exporting to SVG L1"<<endl;
  board.clear();
  Display2DFactory::drawImage<Hue>(board, dt1, (DGtal::int64_t)0, (DGtal::int64_t)maxv+1);
  board.saveSVG ( "image-DT-l1.svg" );

  board.clear();
  Display2DFactory::drawImage<Hue>(board, dt1_periodic, (DGtal::int64_t)0, (DGtal::int64_t)maxv+1);
  board.saveSVG ( "image-DT-l1-periodic.svg" );

  trace.info()<< "done"<<endl;


  trace.endBlock();

  return nbok == nb;
}

template <typename Space, int norm>
bool testCompareExactInexact(unsigned int size, unsigned int nb)
{
  trace.beginBlock("Checking Exact/Inexct predicate metrics");
  typedef ExactPredicateLpSeparableMetric<Space, norm> MetricEx;
  typedef InexactPredicateLpSeparableMetric<Space> MetricInex;
  typedef HyperRectDomain<Space> Domain;
  typedef typename Space::Point Point;
  typedef DigitalSetBySTLSet<Domain> Set;
  // typedef NotPointPredicate<SetPredicate<Set> > NegPredicate;
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

  trace.info()<< "Testing metrics "<<MetricEx()<<" "<<MetricInex(norm)<<std::endl;
  trace.info()<< "Testing space dimension "<<Space::dimension<<std::endl;
  trace.info()<< "Inserting "<<set.size() << " points."<<std::endl;

  // SetPredicate<Set> setPred(set);
  NegPredicate negPred(set);

  typedef DistanceTransformation<Space, NegPredicate, MetricEx> DTEx;
  typedef DistanceTransformation<Space, NegPredicate, MetricInex> DTIn;
  MetricEx metricEx;
  MetricInex metricInex(norm);
  DTEx dtex(&domain, &negPred, &metricEx);
  DTIn dtinex(&domain, &negPred, &metricInex);

  double MSE=0.0;
  typename DTEx::ConstRange::ConstIterator it=dtex.constRange().begin(), itend=dtex.constRange().end();
  typename DTIn::ConstRange::ConstIterator it2 = dtinex.constRange().begin();
  for( ; it != itend; ++it, ++it2)
    MSE += ((*it) - (*it2))*((*it) - (*it2));

  trace.warning()<<"Resulting MSE= "<<MSE;
  trace.endBlock();
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main ( int argc, char** argv ){

  trace.beginBlock ( "Testing class DistanceTransformation" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res =  testDistanceTransformation() && testDistanceTransformationNeg()
    && testDTFromSet()
    && testDistanceTransformationBorder()
    && testDistanceTransformation3D()
    && testChessboard()
    && testDTFromSet()
    && testCompareExactInexact<Z2i::Space, 2>(50, 50)
    && testCompareExactInexact<Z3i::Space, 2>(50, 50)
    && testCompareExactInexact<Z2i::Space, 4>(50, 50)
    && testCompareExactInexact<Z3i::Space, 4>(50, 50)
    ;
  //&& ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
