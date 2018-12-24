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
 * @file testFMM.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr ) Laboratoire d'InfoRmatique en
 * Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/01/16
 *
 * @brief Functions for the fast marching method.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include <functional>

#include "DGtal/base/Common.h"

#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/kernel/BasicPointPredicates.h"
#include "DGtal/kernel/domains/DomainPredicate.h"
#include "DGtal/kernel/sets/DigitalSetFromMap.h"
#include "DGtal/images/ImageContainerBySTLMap.h"
#include "DGtal/images/SimpleThresholdForegroundPredicate.h"

//DT
#include "DGtal/images/ImageSelector.h"
#include "DGtal/geometry/volumes/distance/DistanceTransformation.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"

//FMM
#include "DGtal/geometry/volumes/distance/FMM.h"

//Display
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/boards/Board2D.h"

//shape and digitizer
#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/geometry/curves/GridCurve.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::functors;

//////////////////////////////////////////////////////////////////////////////
// 
template <typename TImage, typename TSet, int norm>
struct DistanceTraits
{
  typedef LInfLocalDistance<TImage, TSet> Distance;  
};
//partial specialization
template <typename TImage, typename TSet>
struct DistanceTraits<TImage, TSet, 1>
{
  typedef L1LocalDistance<TImage, TSet> Distance;  
};

//////////////////////////////////////////////////////////////////////////////
// digital circle generator
template <typename TPoint>
class BallPredicate 
{
public:
  typedef TPoint Point;

public: 

  BallPredicate(double aCx, double aCy, double aR ): 
    myCx(aCx), myCy(aCy), myR(aR)
  { ASSERT(myR > 0); }; 

  bool operator()(const TPoint& aPoint) const 
  {
    double d = std::sqrt( std::pow( (myCx-aPoint[0] ), 2) 
			  + std::pow( (myCy-aPoint[1] ), 2) );  
    if (d <= myR) return true; 
    else return false; 
  };
private: 
  double myCx, myCy, myR; 
};

template <typename TPoint>
class BallFunctor 
{
public:
  typedef TPoint Point;
  typedef double Value; 
public: 

  BallFunctor(double aCx, double aCy, double aR ): 
    myCx(aCx), myCy(aCy), myR(aR)
  { ASSERT(myR > 0); }; 

  Value operator()(const TPoint& aPoint) const 
  {
    double d = std::sqrt( std::pow( (myCx-aPoint[0] ), 2) 
			  + std::pow( (myCy-aPoint[1] ), 2) );  
    return (d - myR);
  };
private: 
  double myCx, myCy, myR; 
};


template<typename TKSpace>
void
ballGenerator(const int& size, double aCx, double aCy, double aR, GridCurve<TKSpace>& gc)
{

  ASSERT( aR < (double) size ); 
 
  // Types
  typedef TKSpace KSpace;  
  typedef typename KSpace::SCell SCell;
  typedef typename KSpace::Space Space;  
  typedef typename Space::Point Point;

  KSpace K;
  bool ok = K.init( Point(-size,-size), Point(size,size), true );
  if ( ! ok )
    {
      std::cerr << " error in creating KSpace." << std::endl;
    }
  try 
    {
      BallPredicate<Point> dig(aCx, aCy, aR); 
      // Extracts shape boundary
      SurfelAdjacency<KSpace::dimension> SAdj( true );
      SCell bel = Surfaces<KSpace>::findABel( K, dig, 10000 );
      // Getting the consecutive surfels of the 2D boundary
      std::vector<Point> points;
      Surfaces<KSpace>::track2DBoundaryPoints( points, K, SAdj, dig, bel );
      gc.initFromVector(points); 
    }
  catch ( InputException e )
    {
      std::cerr << " error in finding a bel." << std::endl;
    }
}

template< typename TIterator >
void draw( const TIterator& itb, const TIterator& ite, const int& size, std::string basename) 
{
  typedef typename std::iterator_traits<TIterator>::value_type Pair; 
  typedef typename Pair::first_type Point; 
  HueShadeColorMap<unsigned char, 2> colorMap(0,3*size);

  Board2D b; 
  b.setUnit ( LibBoard::Board::UCentimeter );

  TIterator it = itb; 
  for ( ; it != ite; ++it)
    {
      Point p = it->first;
      b << CustomStyle( p.className(), new CustomFillColor( colorMap( it->second) ) );
      b << p;
    }

  std::stringstream s; 
  s << basename << ".eps"; 
  b.saveEPS(s.str().c_str());
} 


/**
 * Simple 2d distance transform
 *
 */
bool testDisplayDT2d(int size, int area, double distance)
{

  static const DGtal::Dimension dimension = 2; 

  //Domain
  typedef HyperRectDomain< SpaceND<dimension, int> > Domain; 
  typedef Domain::Point Point; 
  Domain d(Point::diagonal(-size), Point::diagonal(size)); 
  DomainPredicate<Domain> dp(d);

  //Image and set
  typedef ImageContainerBySTLMap<Domain,double> Image; 
  Image map( d, (size*size) ); 
  map.setValue( Point::diagonal(0), 0.0 );
  typedef DigitalSetFromMap<Image> Set; 
  Set set(map); 

  //computation
  trace.beginBlock ( "Display 2d FMM results " );
 
  typedef FMM<Image, Set, DomainPredicate<Domain> > FMM; 
  FMM fmm(map, set, dp, area, distance); 
  fmm.compute(); 
  trace.info() << fmm << std::endl; 

  trace.endBlock();

  //display
  std::stringstream s; 
  s << "DTFrom2dPt-" << size << "-" << area << "-" << distance; 
  draw(map.begin(), map.end(), size, s.str());

  return fmm.isValid(); 
}


///////////////////////////
bool accuracyTest(int size)
{

  static const DGtal::Dimension dimension = 2; 

  //Domain
  typedef HyperRectDomain< SpaceND<dimension, int> > Domain; 
  typedef Domain::Point Point; 
  Domain d(Point::diagonal(-size), Point::diagonal(size)); 
  double h = 1.0/(double)size; 

  //predicate
  int radius = (size/2);
  typedef BallPredicate<Point> Predicate; 
  Predicate predicate( 0, 0, radius ); 

  trace.beginBlock ( "test of accuracy" );
  trace.info() << " # circle of radius 0.5 "
	       << "digitized in a square of size 1 "
	       << "at step h=" << h << endl; 

  //Digital circle generation
  typedef KhalimskySpaceND< dimension, int > KSpace; 
  KSpace K; K.init( Point::diagonal(-size), Point::diagonal(size), true); 
  SurfelAdjacency<KSpace::dimension> SAdj( true );
  KSpace::SCell bel = Surfaces<KSpace>::findABel( K, predicate, 10000 );
  std::vector<KSpace::SCell> vSCells;
  Surfaces<KSpace>::track2DBoundary( vSCells, K, SAdj, predicate, bel );

  double diff1, diff2, diff3 = 0.0; 
  { ///low accuracy
    //Image and set
    typedef ImageContainerBySTLMap<Domain,double> Image; 
    typedef DigitalSetFromMap<Image> Set;
    Image map( d ); 
    Set set(map); 

    //initialisation
    //! [FMMDef]
    typedef FMM<Image, Set, Predicate > FMM;
    //! [FMMDef]

    //! [FMMInit1]
    FMM::initFromBelsRange( K, 
			    vSCells.begin(), vSCells.end(), 
			    map, set, 0.5 ); 
    //! [FMMInit1]

    //computation
    //! [FMMUsage]
    FMM fmm(map, set, predicate); 
    fmm.compute(); 
    trace.info() << fmm << std::endl;
    //! [FMMUsage]

    //max
    double truth = radius*h; 
    double found = ( std::max(std::abs(fmm.max()),std::abs(fmm.min())) )*h;
    double diff = std::abs(found-truth);
    trace.info() << " # radius (low accuracy)" << std::endl; 
    trace.info() << " # truth: " << truth << std::endl; 
    trace.info() << " # found: " << found << std::endl; 
    trace.info() << " # diff.: " << diff << std::endl; 
    
    diff1 = diff; 
  }

  { ///medium accuracy
    //Image and set
    typedef ImageContainerBySTLMap<Domain,double> Image; 
    typedef DigitalSetFromMap<Image> Set; 
    Image map( d ); 
    Set set(map); 

    //initialisation
    typedef FMM<Image, Set, Predicate > FMM;

    typedef BallFunctor<Point> Functor; 
    Functor functor( 0, 0, radius ); 
    //! [FMMInit2]
    FMM::initFromBelsRange( K, 
			    vSCells.begin(), vSCells.end(), 
			    functor, map, set ); 
    //! [FMMInit2]

    //computation
    FMM fmm(map, set, predicate); 
    fmm.compute(); 
    trace.info() << fmm << std::endl;

    //max
    double truth = radius*h; 
    double found = ( std::max(std::abs(fmm.max()),std::abs(fmm.min())) )*h;
    double diff = std::abs(found-truth);
    trace.info() << " # radius (medium accuracy)" << std::endl; 
    trace.info() << " # truth: " << truth << std::endl; 
    trace.info() << " # found: " << found << std::endl; 
    trace.info() << " # diff.: " << diff << std::endl; 

    diff2 = diff; 
  }

  { ///high accuracy
    //Image and set
    typedef ImageContainerBySTLMap<Domain,double> Image; 
    typedef DigitalSetFromMap<Image> Set; 
    Image map( d ); 
    Set set(map); 

    //initialisation
    //! [FMMDef3]
    typedef L2SecondOrderLocalDistance<Image, Set> Distance; 
    typedef FMM<Image, Set, Predicate, Distance > FMM;
    //! [FMMDef3]

    typedef BallFunctor<Point> Functor; 
    Functor functor( 0, 0, radius ); 

    FMM::initFromBelsRange( K, 
			    vSCells.begin(), vSCells.end(), 
			    functor, map, set ); 

    //computation
    Distance distance(map, set); 
    FMM fmm(map, set, predicate, distance); 
    fmm.compute(); 
    trace.info() << fmm << std::endl;

    //max
    double truth = radius*h; 
    double found = ( std::max(std::abs(fmm.max()),std::abs(fmm.min())) )*h;
    double diff = std::abs(found-truth);
    trace.info() << " # radius (high accuracy)" << std::endl; 
    trace.info() << " # truth: " << truth << std::endl; 
    trace.info() << " # found: " << found << std::endl; 
    trace.info() << " # diff.: " << diff << std::endl; 

    diff3 = diff; 
  }

  trace.endBlock();

  return ( (diff1 >= diff2)&&(diff2 >= diff3) );  
}

/**
 * Simple 3d distance transform
 * and slice display
 */
bool testDisplayDT3d(int size, int area, double distance)
{

  static const DGtal::Dimension dimension = 3; 

  //Domain
  typedef HyperRectDomain< SpaceND<dimension, int> > Domain; 
  typedef Domain::Point Point; 
  Domain d(Point::diagonal(-size), Point::diagonal(size)); 
  DomainPredicate<Domain> dp(d);

  //Image and set
  typedef ImageContainerBySTLMap<Domain,double> Image; 
  Image map( d, 0.0 ); 
  map.setValue( Point::diagonal(0), 0.0 );
  typedef DigitalSetFromMap<Image> Set; 
  Set set(map); 

  //computation
  trace.beginBlock ( "Display 3d FMM results " );
 
  typedef FMM<Image, Set, DomainPredicate<Domain> > FMM; 
  FMM fmm(map, set, dp, area, distance); 
  fmm.compute(); 
  trace.info() << fmm << std::endl; 

  trace.endBlock();

  {  //display
    HueShadeColorMap<unsigned char, 2> colorMap(0,2*size);

    Board2D b; 
    b.setUnit ( LibBoard::Board::UCentimeter );

    Domain::ConstIterator it = d.begin(); 
    for ( ; it != d.end(); ++it)
      {
	Point p3 = *it;
	if (p3[2] == 0)
	  {
	    PointVector<2,Point::Coordinate> p2(p3[0], p3[1]); 
	    b << CustomStyle( p2.className(), 
			      new CustomFillColor( colorMap(map(p3)) ) )
	      << p2;
	  }
      }

    std::stringstream s; 
    s << "DTFrom3dPt-" << size << "-" << area << "-" << distance
      << ".eps"; 
    b.saveEPS(s.str().c_str());
  }

  return fmm.isValid(); 
}

bool testDisplayDTFromCircle(int size)
{

  static const DGtal::Dimension dimension = 2; 

  //Domain
  typedef HyperRectDomain< SpaceND<dimension, int> > Domain; 
  typedef Domain::Point Point; 
  Domain d(Point::diagonal(-size), Point::diagonal(size)); 
  DomainPredicate<Domain> dp(d);

  //Image and set
  typedef ImageContainerBySTLMap<Domain,double> Image; 
  typedef DigitalSetFromMap<Image> Set; 

  //Digital circle generation
  typedef KhalimskySpaceND< dimension, int > KSpace; 
  GridCurve<KSpace> gc;   
  double radius = (rand()%size);
  trace.info() << " #ball c(" << 0 << "," << 0 << ") r=" << radius << endl; 
  ballGenerator<KSpace>( size, 0, 0, radius, gc ); 


  unsigned int nbok = 0;
  unsigned int nb = 0;

  double dmaxInt = 0; 
  trace.beginBlock ( "Interior " );
  {
    typedef BallPredicate<Point> Predicate; 
    typedef FMM<Image, Set, Predicate > FMM;

    //init
    Image map( d ); 
    Set set(map); 
    GridCurve<KSpace>::InnerPointsRange r = gc.getInnerPointsRange();
    FMM::initFromPointsRange(r.begin(), r.end(), map, set, 0.5); 

    //computation
    Predicate bp(0,0,radius); 
    FMM fmm(map, set, bp); 
    fmm.compute(); 
    trace.info() << fmm << std::endl;
    nbok += (fmm.isValid()?1:0); 
    trace.info() << nbok << "/" << ++nb << std::endl; 

    //max
    dmaxInt = fmm.getMax(); 

    //display
    std::stringstream s; 
    s << "DTInCircle-" << size; 
    draw(map.begin(), map.end(), size, s.str());

  }
  trace.endBlock();

  double dmaxExt = 0; 
  trace.beginBlock ( "Exterior " );
  {
    typedef NotPointPredicate<BallPredicate<Point> > PointPredicate; 
    typedef BinaryPointPredicate<PointPredicate, 
      DomainPredicate<Domain> > Predicate; 
    typedef FMM<Image, Set, Predicate > FMM;

    //init
    Image map( d ); 
    Set set(map); 
    GridCurve<KSpace>::OuterPointsRange r = gc.getOuterPointsRange();
    FMM::initFromPointsRange(r.begin(), r.end(), map, set, 0.5); 

    //computation
    BallPredicate<Point> bp(0,0,radius); 
    PointPredicate nbp( bp );
    Predicate pred( nbp, dp, andBF2 ); 
    FMM fmm(map, set, pred); 
    fmm.compute(); 
    trace.info() << fmm << std::endl; 
    nbok += (fmm.isValid()?1:0); 
    trace.info() << nbok << "/" << ++nb << std::endl; 

    //max
    dmaxExt = fmm.getMax(); 

    //display
    std::stringstream s; 
    s << "DTOutCircle-" << size; 
    draw(map.begin(), map.end(), size, s.str());
  }
  trace.endBlock();

  double dmin = 0; //2*size*size;
  double dmax = 0; 
  trace.beginBlock ( "Both " );
  {
    typedef DomainPredicate<Domain> Predicate; 
    typedef FMM<Image, Set, Predicate > FMM;

    //init
    Image map( d ); 
    Set set(map); 
    GridCurve<KSpace>::IncidentPointsRange r = gc.getIncidentPointsRange();
    FMM::initFromIncidentPointsRange(r.begin(), r.end(), map, set, 0.5); 

    //computation
    FMM fmm(map, set, dp); 
    fmm.compute(); 
    trace.info() << fmm << std::endl;
    nbok += (fmm.isValid()?1:0); 
    trace.info() << nbok << "/" << ++nb << std::endl; 

    //min, max
    dmin = fmm.getMin(); 
    dmax = fmm.getMax(); 

    //display
    std::stringstream s; 
    s << "DTfromCircle-" << size; 
    draw(map.begin(), map.end(), size, s.str());
  }
  trace.endBlock();

  trace.beginBlock ( "Comparison " );
  {
    double epsilon = 0.0001;
    nbok += ( ( (std::abs(-dmaxInt - dmin) < epsilon) 
    		&& (std::abs(dmaxExt - dmax) < epsilon) )?1:0); 
    trace.info() << nbok << "/" << ++nb << std::endl; 
  }
  trace.endBlock();

  return (nb == nbok); 

}


/**
 * Comparison with the separable distance transform
 *
 */
template<Dimension dim, int norm>
bool testComparison(int size, int area, double dist)
{

  static const DGtal::Dimension dimension = dim; 

  //Domain
  typedef HyperRectDomain< SpaceND<dimension, int> > Domain; 
  typedef typename Domain::Point Point; 
  Domain d(Point::diagonal(-size), Point::diagonal(size)); 
  DomainPredicate<Domain> dp(d);

  //Image and set for FMM
  typedef ImageContainerBySTLVector<Domain, long> Image;
  Image map( d ); 
  map.setValue( Point::diagonal(0), 0);
  typedef DigitalSetBySTLSet<Domain> Set; 
  Set set( d );
  set.insert( Point::diagonal(0) ); 

  //Image for separable DT
  typedef Image Image2;
  Image2 image ( d );
  typename Domain::Iterator dit = d.begin(); 
  typename Domain::Iterator ditEnd = d.end(); 
  for ( ; dit != ditEnd; ++dit)
    {
      image.setValue(*dit, 128); 
    }
  image.setValue(Point::diagonal(0), 0); 

  //computation
  trace.beginBlock ( " FMM computation " ); 
 
  typedef typename DistanceTraits<Image,Set,norm>::Distance Distance; 
  typedef FMM<Image, Set, DomainPredicate<Domain>, Distance > FMM; 
  Distance distance(map, set); 
  FMM fmm( map, set, dp, area, dist, distance ); 
  fmm.compute(); 
  trace.info() << fmm << std::endl; 
				
  trace.endBlock();

  trace.beginBlock ( " DT computation " );
  typedef SimpleThresholdForegroundPredicate<Image> Predicate;
  Predicate aPredicate(image,0);
  typedef ExactPredicateLpSeparableMetric<SpaceND<dimension,int>, norm> LNorm;
  typedef DistanceTransformation<SpaceND<dimension,int>, Predicate, LNorm> DT; 
  LNorm lnorm;
  DT dt(&d,&aPredicate, &lnorm);
  trace.info() << dt << std::endl; 

  trace.endBlock();

  bool flagIsOk = true; 

  trace.beginBlock ( " Comparison " );
  //all points of result must be in map and have the same distance
  typename Domain::ConstIterator it = d.begin(); 
  typename Domain::ConstIterator itEnd = d.end(); 
  for ( ; ( (it != itEnd)&&(flagIsOk) ); ++it)
    {
      if (set.find(*it) == set.end())
	flagIsOk = false; 
      else 
	{
	  if (dt(*it) != map(*it))
	    flagIsOk = false;
	}
    }
  trace.endBlock();

  return flagIsOk; 

}



///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main ( int argc, char** argv )
{
  trace.beginBlock ( "Testing FMM" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  //2d L2 tests
  int size = 50; 
  int area = int( std::pow(double(2*size+1),2) )+1; 
  bool res   
    = testDisplayDT2d( size, area, std::sqrt(2*size*size) )
    && testDisplayDT2d( size, area, size )
    && testDisplayDT2d( size, 2*area, std::sqrt(2*size*size) )
    && testDisplayDTFromCircle(size)   
    && accuracyTest(size)
    ;

  size = 25;
  area = 4*int( std::pow(double(size),3) ); 
  //3d L2 test
  res = res && testDisplayDT3d( size, area, std::sqrt(size*size*size) )
    ; 

  //3d L1 and  comparison
  size = 20; 
  area = int( std::pow(double(2*size+1),3) )+1; 
  res = res  
    && testComparison<3,1>( size, area, 3*size+1 )
    ;
  size = 5; 
  area = int( std::pow(double(2*size+1),4) ) + 1;
  res = res
    && testComparison<4,1>( size, area, 4*size+1 )
    ;

  //&& ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
