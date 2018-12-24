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
 * @file testDigitalSurface.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2011/09/01
 *
 * Functions for testing class DigitalSurface.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CConstSinglePassRange.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/DigitalSetBoundary.h"
#include "DGtal/topology/ImplicitDigitalSurface.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/topology/ExplicitDigitalSurface.h"
#include "DGtal/topology/LightExplicitDigitalSurface.h"
#include "DGtal/graph/BreadthFirstVisitor.h"
#include "DGtal/topology/helpers/FrontierPredicate.h"
#include "DGtal/topology/helpers/BoundaryPredicate.h"
#include "DGtal/graph/CUndirectedSimpleLocalGraph.h"
#include "DGtal/graph/CUndirectedSimpleGraph.h"

#include "DGtal/shapes/Shapes.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::concepts;
using namespace DGtal::functors;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class DigitalSurface.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testDigitalSetBoundary()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing block ... DigitalSetBoundary" );
  using namespace Z2i;
  typedef DigitalSetBoundary<KSpace,DigitalSet> Boundary;
  typedef Boundary::SurfelConstIterator ConstIterator;
  typedef Boundary::Tracker Tracker;
  typedef Boundary::Surfel Surfel;
  Point p1( -10, -10 );
  Point p2( 10, 10 );
  Domain domain( p1, p2 );
  DigitalSet dig_set( domain );
  Shapes<Domain>::addNorm2Ball( dig_set, Point( 0, 0 ), 5 );
  Shapes<Domain>::removeNorm2Ball( dig_set, Point( 0, 0 ), 1 );
  KSpace K;
  nbok += K.init( domain.lowerBound(), domain.upperBound(), true ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "K.init() is ok" << std::endl;
  Boundary boundary( K, dig_set );
  unsigned int nbsurfels = 0;
  for ( ConstIterator it = boundary.begin(), it_end = boundary.end();
        it != it_end; ++it )
    {
      ++nbsurfels;
    }
  trace.info() << nbsurfels << " surfels found." << std::endl;
  ++nb; nbok += nbsurfels == ( 12 + 44 ) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "nbsurfels == (12 + 44 )" << std::endl;
  for ( ConstIterator it = boundary.begin(), it_end = boundary.end();
        it != it_end; ++it )
    {
      Tracker* ptrTracker = boundary.newTracker( *it );
      Surfel s = ptrTracker->current();
      Dimension trackDir = * K.sDirs( s );
      Surfel s1, s2;
      unsigned int m1 = ptrTracker->adjacent( s1, trackDir, true ); 
      unsigned int m2 = ptrTracker->adjacent( s2, trackDir, false ); 
      trace.info() << "s = " << s << std::endl;
      trace.info() << "s1 = " << s1 << " m1 = " << m1 << std::endl;
      trace.info() << "s2 = " << s2 << " m2 = " << m2 << std::endl;
      ++nb; nbok += boundary.isInside( s1 ) ? 1 : 0;
      trace.info() << "(" << nbok << "/" << nb << ") "
                   << "boundary.isInside( s1 )" << std::endl;
      ++nb; nbok += boundary.isInside( s2 ) ? 1 : 0;
      trace.info() << "(" << nbok << "/" << nb << ") "
                   << "boundary.isInside( s2 )" << std::endl;
      delete ptrTracker;
    }
  trace.endBlock();
  return nbok == nb;
}

template <typename TPoint3>
struct ImplicitDigitalEllipse3 {
  typedef TPoint3 Point;
  inline
  ImplicitDigitalEllipse3( double a, double b, double c )
    : myA( a ), myB( b ), myC( c )
  {}
  inline
  bool operator()( const TPoint3 & p ) const
  {
    double x = ( (double) p[ 0 ] / myA );
    double y = ( (double) p[ 1 ] / myB );
    double z = ( (double) p[ 2 ] / myC );
    return ( x*x + y*y + z*z ) <= 1.0;
  }
  double myA, myB, myC;
};

bool testImplicitDigitalSurface()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing block ... ImplicitDigitalSurface" );
  using namespace Z3i;
  typedef ImplicitDigitalEllipse3<Point> ImplicitDigitalEllipse;
  typedef ImplicitDigitalSurface<KSpace,ImplicitDigitalEllipse> Boundary;
  typedef Boundary::SurfelConstIterator ConstIterator;
  typedef Boundary::Tracker Tracker;
  typedef Boundary::Surfel Surfel;
  Point p1( -10, -10, -10 );
  Point p2( 10, 10, 10 );
  KSpace K;
  nbok += K.init( p1, p2, true ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "K.init() is ok" << std::endl;
  ImplicitDigitalEllipse ellipse( 6.0, 4.5, 3.4 );
  Surfel bel = Surfaces<KSpace>::findABel( K, ellipse, 10000 );
  Boundary boundary( K, ellipse, 
                     SurfelAdjacency<KSpace::dimension>( true ), bel );
  unsigned int nbsurfels = 0;
  for ( ConstIterator it = boundary.begin(), it_end = boundary.end();
        it != it_end; ++it )
    {
      ++nbsurfels;
    }
  trace.info() << nbsurfels << " surfels found." << std::endl;
  // ++nb; nbok += nbsurfels == ( 12 + 44 ) ? 1 : 0;
  // trace.info() << "(" << nbok << "/" << nb << ") "
  //              << "nbsurfels == (12 + 44 )" << std::endl;
  for ( ConstIterator it = boundary.begin(), it_end = boundary.end();
        it != it_end; ++it )
    {
      Tracker* ptrTracker = boundary.newTracker( *it );
      Surfel s = ptrTracker->current();
      Dimension trackDir = * K.sDirs( s );
      Surfel s1, s2;
      unsigned int m1 = ptrTracker->adjacent( s1, trackDir, true ); 
      unsigned int m2 = ptrTracker->adjacent( s2, trackDir, false ); 
      trace.info() << "s = " << s << std::endl;
      trace.info() << "s1 = " << s1 << " m1 = " << m1 << std::endl;
      trace.info() << "s2 = " << s2 << " m2 = " << m2 << std::endl;
      ++nb; nbok += boundary.isInside( s1 ) ? 1 : 0;
      trace.info() << "(" << nbok << "/" << nb << ") "
                   << "boundary.isInside( s1 )" << std::endl;
      ++nb; nbok += boundary.isInside( s2 ) ? 1 : 0;
      trace.info() << "(" << nbok << "/" << nb << ") "
                   << "boundary.isInside( s2 )" << std::endl;
      delete ptrTracker;
    }
  trace.endBlock();
  return nbok == nb;
}

//-----------------------------------------------------------------------------
// Testing LightImplicitDigitalSurface
//-----------------------------------------------------------------------------
bool testLightImplicitDigitalSurface()
{
  using namespace Z3i;
  typedef ImplicitDigitalEllipse3<Point> ImplicitDigitalEllipse;
  typedef LightImplicitDigitalSurface<KSpace,ImplicitDigitalEllipse> Boundary;
  typedef Boundary::SurfelConstIterator ConstIterator;
  typedef Boundary::Tracker Tracker;
  typedef Boundary::Surfel Surfel;

  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing block ... LightImplicitDigitalSurface" );
  Point p1( -10, -10, -10 );
  Point p2( 10, 10, 10 );
  KSpace K;
  nbok += K.init( p1, p2, true ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "K.init() is ok" << std::endl;
  ImplicitDigitalEllipse ellipse( 6.0, 4.5, 3.4 );
  Surfel bel = Surfaces<KSpace>::findABel( K, ellipse, 10000 );
  Boundary boundary( K, ellipse, 
                     SurfelAdjacency<KSpace::dimension>( true ), bel );
  unsigned int nbsurfels = 0;
  for ( ConstIterator it = boundary.begin(), it_end = boundary.end();
        it != it_end; ++it )
    {
      ++nbsurfels;
    }
  trace.info() << nbsurfels << " surfels found." << std::endl;
  trace.beginBlock ( "Checks if adjacent surfels are part of the surface." );

  for ( ConstIterator it = boundary.begin(), it_end = boundary.end();
        it != it_end; ++it )
    {
      Tracker* ptrTracker = boundary.newTracker( *it );
      Surfel s = ptrTracker->current();
      Dimension trackDir = * K.sDirs( s );
      Surfel s1, s2;
      // unsigned int m1 = 
      ptrTracker->adjacent( s1, trackDir, true ); 
      // unsigned int m2 = 
      ptrTracker->adjacent( s2, trackDir, false ); 
      // trace.info() << "s = " << s << std::endl;
      // trace.info() << "s1 = " << s1 << " m1 = " << m1 << std::endl;
      // trace.info() << "s2 = " << s2 << " m2 = " << m2 << std::endl;
      ++nb; nbok += boundary.isInside( s1 ) ? 1 : 0;
      // trace.info() << "(" << nbok << "/" << nb << ") "
      //              << "boundary.isInside( s1 )" << std::endl;
      ++nb; nbok += boundary.isInside( s2 ) ? 1 : 0;
      // trace.info() << "(" << nbok << "/" << nb << ") "
      //              << "boundary.isInside( s2 )" << std::endl;
      delete ptrTracker;
    }
  trace.info() << "(" << nbok << "/" << nb << ") isInside tests." << std::endl;
  trace.endBlock();
  trace.endBlock();
  return nbok == nb;
}

template <typename Image3D>
void fillImage3D( Image3D & img, 
                  typename Image3D::Point low, 
                  typename Image3D::Point up, 
                  typename Image3D::Value value )
{
  typedef typename Image3D::Point Point;
  typedef typename Image3D::Integer Integer;
  for ( Integer z = low[ 2 ]; z <= up[ 2 ]; ++z )
    for ( Integer y = low[ 1 ]; y <= up[ 1 ]; ++y )
      for ( Integer x = low[ 0 ]; x <= up[ 0 ]; ++x )
        img.setValue( Point( x, y, z ), value );
}

//-----------------------------------------------------------------------------
// Testing ExplicitDigitalSurface
//-----------------------------------------------------------------------------
bool testExplicitDigitalSurface()
{
  using namespace Z3i;
  typedef ImageContainerBySTLVector<Domain,DGtal::uint8_t> Image;
  typedef FrontierPredicate<KSpace, Image> SurfelPredicate;
  typedef ExplicitDigitalSurface<KSpace,SurfelPredicate> Frontier;
  typedef Frontier::SurfelConstIterator ConstIterator;
  typedef Frontier::SCell SCell;

  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing block ... ExplicitDigitalSurface" );
  Point p1( -5, -5, -5 );
  Point p2( 5, 5, 5 );
  KSpace K;
  nbok += K.init( p1, p2, true ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "K.init() is ok" << std::endl;
  Image image( Domain(p1, p2) );
  fillImage3D( image, p1, p2, 0 );
  fillImage3D( image, Point(-2,-2,-2 ), Point( 2, 2, 2 ), 1 );
  fillImage3D( image, Point( 0, 0,-2 ), Point( 0, 0, 2 ), 2 );
  fillImage3D( image, Point(-1,-1, 2 ), Point( 1, 1, 2 ), 2 );
  {
    SCell vox2  = K.sSpel( Point( 0, 0, 2 ), K.POS );
    SCell bel20 = K.sIncident( vox2, 2, true );
    SurfelPredicate surfPredicate( K, image, 2, 0 );
    Frontier frontier20( K, surfPredicate,
                         SurfelAdjacency<KSpace::dimension>( true ), 
                         bel20 );
    unsigned int nbsurfels = 0;
    for ( ConstIterator it = frontier20.begin(), it_end = frontier20.end();
          it != it_end; ++it )
      {
        ++nbsurfels;
      }
    trace.info() << nbsurfels << " surfels found." << std::endl;
    ++nb; nbok += nbsurfels == 9 ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") "
                 << "frontier20: nbsurfels == 9" << std::endl;
  }
  {
    SCell vox1  = K.sSpel( Point( 2, 0, 0 ), K.POS );
    SCell bel10 = K.sIncident( vox1, 0, true );
    SurfelPredicate surfPredicate( K, image, 1, 0 );
    Frontier frontier10( K, surfPredicate,
                         SurfelAdjacency<KSpace::dimension>( true ), 
                         bel10 );
    unsigned int nbsurfels = 0;
    for ( ConstIterator it = frontier10.begin(), it_end = frontier10.end();
          it != it_end; ++it )
      {
        ++nbsurfels;
      }
    trace.info() << nbsurfels << " surfels found." << std::endl;
    ++nb; nbok += nbsurfels == 140 ? 1 : 0; // 4*25(sides) + 16(top) + 24(bot)
    trace.info() << "(" << nbok << "/" << nb << ") "
                 << "frontier10: nbsurfels == 140" << std::endl;
  }
  {
    SCell vox1  = K.sSpel( Point( 1, 0, 0 ), K.POS );
    SCell bel12 = K.sIncident( vox1, 0, false );
    SurfelPredicate surfPredicate( K, image, 1, 2 );
    Frontier frontier12( K, surfPredicate,
                         SurfelAdjacency<KSpace::dimension>( true ), 
                         bel12 );
    unsigned int nbsurfels = 0;
    for ( ConstIterator it = frontier12.begin(), it_end = frontier12.end();
          it != it_end; ++it )
      {
        ++nbsurfels;
      }
    trace.info() << nbsurfels << " surfels found." << std::endl;
    ++nb; nbok += nbsurfels == 36 ? 1 : 0; // 8+12(top) + 16(axis) 
    trace.info() << "(" << nbok << "/" << nb << ") "
                 << "frontier12: nbsurfels == 36" << std::endl;
  }
  {
    typedef BoundaryPredicate<KSpace, Image> SecondSurfelPredicate;
    typedef ExplicitDigitalSurface<KSpace,SecondSurfelPredicate> Boundary;
    typedef Boundary::SurfelConstIterator EConstIterator;
    // typedef Boundary::Tracker Tracker;
    // typedef Boundary::SCell SCell;
    // typedef Boundary::Surfel Surfel;
    SCell vox1  = K.sSpel( Point( 1, 0, 0 ), K.POS );
    SCell bel1x = K.sIncident( vox1, 0, false );
    SecondSurfelPredicate surfPredicate( K, image, 1 );
    Boundary boundary1x( K, surfPredicate,
                         SurfelAdjacency<KSpace::dimension>( true ), 
                         bel1x );
    unsigned int nbsurfels = 0;
    for ( EConstIterator it = boundary1x.begin(), it_end = boundary1x.end();
          it != it_end; ++it )
      {
        ++nbsurfels;
      }
    trace.info() << nbsurfels << " surfels found." << std::endl;
    ++nb; nbok += nbsurfels == 176 ? 1 : 0; 
    trace.info() << "(" << nbok << "/" << nb << ") "
                 << "boundary1x: nbsurfels == 176" << std::endl;
  }
  trace.endBlock();
  return nbok == nb;
}

//-----------------------------------------------------------------------------
// Testing LightExplicitDigitalSurface
//-----------------------------------------------------------------------------
bool testLightExplicitDigitalSurface()
{
  using namespace Z3i;
  typedef ImageContainerBySTLVector<Domain,DGtal::uint8_t> Image;
  typedef FrontierPredicate<KSpace, Image> SurfelPredicate;
  typedef LightExplicitDigitalSurface<KSpace,SurfelPredicate> Frontier;
  typedef Frontier::SurfelConstIterator ConstIterator;
  typedef Frontier::SCell SCell;

  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing block ... LightExplicitDigitalSurface" );
  Point p1( -5, -5, -5 );
  Point p2( 5, 5, 5 );
  KSpace K;
  nbok += K.init( p1, p2, true ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "K.init() is ok" << std::endl;
  Image image( Domain(p1, p2) );
  fillImage3D( image, p1, p2, 0 );
  fillImage3D( image, Point(-2,-2,-2 ), Point( 2, 2, 2 ), 1 );
  fillImage3D( image, Point( 0, 0,-2 ), Point( 0, 0, 2 ), 2 );
  fillImage3D( image, Point(-1,-1, 2 ), Point( 1, 1, 2 ), 2 );
  {
    SCell vox2  = K.sSpel( Point( 0, 0, 2 ), K.POS );
    SCell bel20 = K.sIncident( vox2, 2, true );
    SurfelPredicate surfPredicate( K, image, 2, 0 );
    Frontier frontier20( K, surfPredicate,
                         SurfelAdjacency<KSpace::dimension>( true ), 
                         bel20 );
    unsigned int nbsurfels = 0;
    for ( ConstIterator it = frontier20.begin(), it_end = frontier20.end();
          it != it_end; ++it )
      {
        ++nbsurfels;
      }
    trace.info() << nbsurfels << " surfels found." << std::endl;
    ++nb; nbok += nbsurfels == 9 ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") "
                 << "frontier20: nbsurfels == 9" << std::endl;
  }
  {
    SCell vox1  = K.sSpel( Point( 2, 0, 0 ), K.POS );
    SCell bel10 = K.sIncident( vox1, 0, true );
    SurfelPredicate surfPredicate( K, image, 1, 0 );
    Frontier frontier10( K, surfPredicate,
                         SurfelAdjacency<KSpace::dimension>( true ), 
                         bel10 );
    unsigned int nbsurfels = 0;
    for ( ConstIterator it = frontier10.begin(), it_end = frontier10.end();
          it != it_end; ++it )
      {
        ++nbsurfels;
      }
    trace.info() << nbsurfels << " surfels found." << std::endl;
    ++nb; nbok += nbsurfels == 140 ? 1 : 0; // 4*25(sides) + 16(top) + 24(bot)
    trace.info() << "(" << nbok << "/" << nb << ") "
                 << "frontier10: nbsurfels == 140" << std::endl;
  }
  {
    SCell vox1  = K.sSpel( Point( 1, 0, 0 ), K.POS );
    SCell bel12 = K.sIncident( vox1, 0, false );
    SurfelPredicate surfPredicate( K, image, 1, 2 );
    Frontier frontier12( K, surfPredicate,
                         SurfelAdjacency<KSpace::dimension>( true ), 
                         bel12 );
    unsigned int nbsurfels = 0;
    for ( ConstIterator it = frontier12.begin(), it_end = frontier12.end();
          it != it_end; ++it )
      {
        ++nbsurfels;
      }
    trace.info() << nbsurfels << " surfels found." << std::endl;
    ++nb; nbok += nbsurfels == 36 ? 1 : 0; // 8+12(top) + 16(axis) 
    trace.info() << "(" << nbok << "/" << nb << ") "
                 << "frontier12: nbsurfels == 36" << std::endl;
  }
  {
    typedef BoundaryPredicate<KSpace, Image> SecondSurfelPredicate;
    typedef LightExplicitDigitalSurface<KSpace,SecondSurfelPredicate> Boundary;
    typedef Boundary::SurfelConstIterator LEConstIterator;
    //typedef Boundary::Tracker Tracker;
    //typedef Boundary::SCell SCell;
    //typedef Boundary::Surfel Surfel;
    SCell vox1  = K.sSpel( Point( 1, 0, 0 ), K.POS );
    SCell bel1x = K.sIncident( vox1, 0, false );
    SecondSurfelPredicate surfPredicate( K, image, 1 );
    Boundary boundary1x( K, surfPredicate,
                         SurfelAdjacency<KSpace::dimension>( true ), 
                         bel1x );
    unsigned int nbsurfels = 0;
    for ( LEConstIterator it = boundary1x.begin(), it_end = boundary1x.end();
          it != it_end; ++it )
      {
        ++nbsurfels;
      }
    trace.info() << nbsurfels << " surfels found." << std::endl;
    ++nb; nbok += nbsurfels == 176 ? 1 : 0; 
    trace.info() << "(" << nbok << "/" << nb << ") "
                 << "boundary1x: nbsurfels == 176" << std::endl;
  }
  trace.endBlock();
  return nbok == nb;
}



template <typename KSpace>
bool testDigitalSurface()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  std::string msg( "Testing block ... DigitalSurface in K" );
  msg += '0' + KSpace::dimension;
  trace.beginBlock ( msg );
  //"Testing block ... DigitalSurface " + std::string( KSpace.dimension ) );
  typedef typename KSpace::Space Space;
  typedef typename KSpace::Size Size;
  typedef typename Space::Point Point;
  typedef HyperRectDomain<Space> Domain;
  typedef typename DigitalSetSelector < Domain, BIG_DS + HIGH_ITER_DS + HIGH_BEL_DS >::Type DigitalSet;

  trace.beginBlock ( "Creating object and DigitalSurfaceContainer" );
  Point p0 = Point::diagonal( 0 );
  Point p1 = Point::diagonal( -6 );
  Point p2 = Point::diagonal( 6 );
  Domain domain( p1, p2 );
  DigitalSet dig_set( domain );
  Shapes<Domain>::addNorm2Ball( dig_set, p0, 3 );
  Shapes<Domain>::removeNorm2Ball( dig_set, p0, 1 );
  KSpace K;
  nbok += K.init( domain.lowerBound(), domain.upperBound(), true ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "K.init() is ok" << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing DigitalSurface" );
  typedef DigitalSetBoundary<KSpace,DigitalSet> DSContainer;
  typedef DigitalSurface<DSContainer> MyDS;

  //Checking the type as a model of CSinglePassConstRange
  BOOST_CONCEPT_ASSERT(( CConstSinglePassRange < MyDS> ));
  BOOST_CONCEPT_ASSERT(( CUndirectedSimpleLocalGraph < MyDS> ));
  BOOST_CONCEPT_ASSERT(( CUndirectedSimpleGraph < MyDS> ));
  

  typedef typename MyDS::Surfel Surfel;
  DSContainer* ptrBdry = new DSContainer( K, dig_set );
  MyDS digsurf( ptrBdry ); // acquired
  Size nbsurfels = 
    ( K.dimension == 2 ) ? 12+28 :
    ( K.dimension == 3 ) ? 30+174 :
    ( K.dimension == 4 ) ? 56+984 : 
    ( K.dimension == 5 ) ? 4340 : 0;
  ++nb; nbok += digsurf.size() == nbsurfels ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "digsurf.size() = " << digsurf.size() 
               << " == " << nbsurfels << std::endl;
  for ( typename MyDS::ConstIterator it = digsurf.begin(),
          it_end = digsurf.end();
        it != it_end;
        ++it )
    {
      Surfel s = *it;
      ++nb; nbok += digsurf.degree( s ) == 2*(K.dimension-1) ? 1 : 0;
    }
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "digsurf.degree( s ) == "
               << 2*(K.dimension-1) << std::endl;
  trace.endBlock();
  trace.beginBlock ( "Testing BreadthFirstVisitor on DigitalSurface" );
  BreadthFirstVisitor< MyDS > visitor( digsurf, *digsurf.begin() );
  typedef typename BreadthFirstVisitor< MyDS >::Node BFVNode;
  typedef typename BreadthFirstVisitor< MyDS >::MarkSet BFVMarkSet;
  unsigned int nb_dist_1 = 0;
  BFVNode node;
  while ( ! visitor.finished() )
    {
      node = visitor.current();
      if ( node.second == 1 ) ++nb_dist_1;
      visitor.expand();
    }
  trace.info() << "last node v=" << node.first << " d=" << node.second << std::endl;
  ++nb; nbok += nb_dist_1 == 2*(K.dimension-1) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "nb surfels at distance 1 == "
               << 2*(K.dimension-1) << std::endl;
  const BFVMarkSet & visitedVtx = visitor.markedVertices();
  Size nbsurfelsComp1 = 
    ( K.dimension == 2 ) ? 28 :
    ( K.dimension == 3 ) ? 174 :
    ( K.dimension == 4 ) ? 984 : 0;
  ++nb; nbok += visitedVtx.size() == nbsurfelsComp1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "nb visited = " << visitedVtx.size() << " == "
               << nbsurfelsComp1 << std::endl;

  trace.endBlock();
  

  trace.endBlock();
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class DigitalSurface" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testDigitalSetBoundary()
    && testImplicitDigitalSurface()
    && testLightImplicitDigitalSurface()
    && testExplicitDigitalSurface()
    && testLightExplicitDigitalSurface()
    && testDigitalSurface<KhalimskySpaceND<2> >()
    && testDigitalSurface<KhalimskySpaceND<3> >()
    && testDigitalSurface<KhalimskySpaceND<4> >();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
