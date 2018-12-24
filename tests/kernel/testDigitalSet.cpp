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
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France

 * @author Sebastien Fourey (\c Sebastien.Fourey@greyc.ensicaen.fr )
 * Groupe de Recherche en Informatique, Image, Automatique et
 * Instrumentation de Caen - GREYC (CNRS, UMR 6072), ENSICAEN, France
 *
 * @date 2010/07/01
 *
 * This file is part of the DGtal library
 */

/**
 * Description of test_DigitalSet <p>
 * Aim: simple tests of models of \ref CDigitalSet
 */

#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <unordered_set>

#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/kernel/sets/CDigitalSet.h"
#include "DGtal/kernel/sets/CDigitalSetArchetype.h"
#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/kernel/domains/CDomainArchetype.h"
#include "DGtal/kernel/sets/DigitalSetBySTLVector.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"
#include "DGtal/kernel/sets/DigitalSetByAssociativeContainer.h"
#include "DGtal/kernel/sets/DigitalSetFromMap.h"
#include "DGtal/kernel/sets/DigitalSetSelector.h"
#include "DGtal/kernel/sets/DigitalSetDomain.h"
#include "DGtal/kernel/sets/DigitalSetInserter.h"

#include "DGtal/images/ImageContainerBySTLMap.h"

#include "DGtal/helpers/StdDefs.h"

#include "DGtal/io/boards/Board2D.h"

#include "DGtal/kernel/PointHashFunctions.h"



using namespace DGtal;
using namespace std;


#define INBLOCK_TEST(x) \
  nbok += ( x ) ? 1 : 0; \
  nb++; \
  trace.info() << "(" << nbok << "/" << nb << ") " \
  << #x << std::endl;

#define INBLOCK_TEST2(x,y) \
  nbok += ( x ) ? 1 : 0; \
  nb++; \
  trace.info() << "(" << nbok << "/" << nb << ") " \
  << y << std::endl;



struct MyDomainStyleCustomRed : public DrawableWithBoard2D
{
  virtual void setStyle(Board2D & aboard) const
  {
    aboard.setFillColorRGBi(255, 0, 0);
    aboard.setPenColorRGBi(0, 255, 0);
  }
};


bool testDigitalSetBoardSnippet()
{
  typedef SpaceND<2> Z2;
  typedef HyperRectDomain<Z2> Domain;
  typedef Z2::Point Point;
  Point p1(  -10, -10  );
  Point p2(  10, 10  );
  Domain domain( p1, p2 );
  typedef DigitalSetSelector < Domain, BIG_DS + HIGH_ITER_DS + HIGH_BEL_DS >::Type SpecificSet;

  BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet< SpecificSet > ));

  SpecificSet mySet( domain );

  Point c(  0, 0  );
  mySet.insert( c );
  Point d(  5, 2  );
  mySet.insert( d );
  Point e(  1, -3  );
  mySet.insert( e );

  Board2D board;
  board.setUnit(LibBoard::Board::UCentimeter);
  board << mySet;
  board.saveSVG("myset-export.svg");

  board.clear();

  board.setUnit(LibBoard::Board::UCentimeter);
  board << SetMode( domain.className(), "Grid" ) << domain << mySet;
  board.saveSVG("simpleSet-grid.svg");

  board.clear();

  board.setUnit(LibBoard::Board::UCentimeter);
  board << SetMode( domain.className(), "Paving" ) << domain;
  board << mySet;
  board.saveSVG("simpleSet-paving.svg");


  board.clear();

  board.setUnit(LibBoard::Board::UCentimeter);
  board << CustomStyle( mySet.className(), new MyDomainStyleCustomRed );
  board << mySet;
  board.saveSVG("simpleSet-color.svg");

  return true;
}

template < typename DigitalSetType >
bool testDigitalSet( const DigitalSetType& aSet1, const DigitalSetType& aSet2 )
{
  BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet< DigitalSetType > ));

  typedef typename DigitalSetType::Domain Domain;
  typedef typename Domain::Point Point;
  typedef typename Point::Coordinate Coordinate;
  unsigned int nbok = 0;
  unsigned int nb = 0;

  //copy, size/empty
  DigitalSetType set1( aSet1 );
  nbok += ( (set1.size() == 0)&&(set1.empty()) ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "Empty set: " << set1 << std::endl;

  //insertion
  std::set<Point> v;
  Coordinate t [] = { 4, 3, 3 , 4};
  Coordinate t2[] = { 2, 5, 3 , 5};
  Coordinate t3[] =  { 2, 5, 3 , 4} ;
  Point a( t );
  Point b( t2 );
  Point c( t3 );
  v.insert( a );
  v.insert( b );
  v.insert( c );

  set1.insert( a );
  set1.insert( b );
  set1.insertNew( c );
  set1.insert( b );
  nbok += set1.size() == 3 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "Insertion (3 elements): " << set1 << std::endl;

  //iterate
  bool flag = true;
  for (typename DigitalSetType::Iterator it = set1.begin();
       it != set1.end(); ++it)
    {
      if (v.find( *it ) == v.end())
	flag = false;
    }
  nbok += (flag) ? 1 : 0;
  nb++;
  trace.info() << "Iterate: (" << nbok << "/" << nb << ") "
  	       << std::endl;

  //erasure
  set1.erase( b );
  nbok += ( (set1.size() == 2)
  	    &&(set1.find( b ) == set1.end()) )? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "Erase one element by key (2 remain): " << set1 << std::endl;

  typename DigitalSetType::Iterator it = set1.find( c );
  set1.erase( it );
  nbok += ( (set1.size() == 1)
  	    &&(set1.find( c ) == set1.end()) )? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "Erase one element by iterator (1 remain): " << set1 << std::endl;

  //other sets
  DigitalSetType set2( aSet2 );
  DigitalSetInserter<DigitalSetType> inserter(set2);
  set1.computeComplement(inserter);
  nbok += (set2.size() == (set2.domain().size()-1))? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "Complement: " << set2 << std::endl;

  set2 += set1;
  nbok += (set2.size() == (set2.domain().size()))? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "Union: " << set2 << std::endl;

  //clear
  set1.clear();
  nbok += ( (set1.size() == 0)&&(set1.empty()) ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "Cleared set: " << set1 << std::endl;

  set1.assignFromComplement(set2); //remains empty
  nbok += ( (set1.size() == 0)&&(set1.empty()) ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << std::endl;

  return nbok == nb;
}

template < typename DigitalDomain, int props >
bool testDigitalSetSelector( const DigitalDomain & domain,
    const std::string & comment )
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Test DigitalSetSelector( " + comment + ")." );

  typedef typename DigitalSetSelector
  < DigitalDomain, props >::Type SpecificSet;
  SpecificSet set1( domain );
  set1.insert( domain.lowerBound() );
  set1.insert( domain.upperBound() );
  nbok += set1.size() == 2 ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << comment << " (2 elements): " << set1 << std::endl;

  trace.endBlock();


  return nbok == nb;
}

bool testDigitalSetDraw()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  typedef SpaceND<2> Z2;
  typedef HyperRectDomain<Z2> Domain;
  typedef Z2::Point Point;
  Point p1(  -10, -10  );
  Point p2(  10, 10  );
  Domain domain( p1, p2 );
  typedef DigitalSetSelector
  < Domain, BIG_DS + HIGH_ITER_DS + HIGH_BEL_DS >::Type SpecificSet;

  BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet< SpecificSet > ));
  SpecificSet disk( domain );
  Point c(  0, 0  );

  trace.beginBlock ( "Creating disk( r=5.0 ) ..." );
  for ( Domain::ConstIterator it = domain.begin();
  it != domain.end();
      ++it )
  {
    if ( (*it - c ).norm() < 5.0 )
      // insertNew is very important for vector container.
      disk.insertNew( *it );
  }

  //Board export test
  trace.beginBlock("SVG Export");
  Board2D board;
  board << SetMode( domain.className(), "Grid" ) << domain;
  board << disk;

  board.scale(10);
  board.saveSVG( "disk-set.svg" );
  trace.endBlock();

  return nbok == nb;
}

bool testDigitalSetDomain()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  typedef SpaceND<2> Z2;
  typedef HyperRectDomain<Z2> Domain;
  typedef Z2::Point Point;
  Point p1(  -49, -49  );
  Point p2(  49, 49  );
  Domain domain( p1, p2 );
  typedef DigitalSetSelector
  < Domain, BIG_DS + HIGH_ITER_DS + HIGH_BEL_DS >::Type SpecificSet;
  BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet< SpecificSet > ));

  SpecificSet disk( domain );
  Point c(  0, 0  );
  Point l(  49, 0  );

  trace.beginBlock ( "Creating disk( r=50.0 ) ..." );
  for ( Domain::ConstIterator it = domain.begin();
  it != domain.end();
  ++it )
    {
      if ( (*it - c ).norm() < 50.0 )
  // insertNew is very important for vector container.
  disk.insertNew( *it );
    }
  disk.erase( c );
  INBLOCK_TEST( disk.size() == 7824 );
  trace.info() << "disk.size()=" << disk.size() << std::endl;
  trace.endBlock();

  typedef DigitalSetDomain< SpecificSet > RestrictedDomain;
  BOOST_CONCEPT_ASSERT(( concepts::CDomain< RestrictedDomain > ));

  RestrictedDomain disk_domain( disk );
  trace.beginBlock ( "Iterating over disk domain ..." );
  unsigned int nb_in_domain = 0;
  for ( RestrictedDomain::ConstIterator it = disk_domain.begin();
      it != disk_domain.end();
      ++it )
  {
    ++nb_in_domain;
  }
  INBLOCK_TEST( nb_in_domain == 7824 );
  INBLOCK_TEST( disk_domain.lowerBound() == Point(  -49, -49 ) );
  INBLOCK_TEST( disk_domain.upperBound() == Point(   49,  49 ) );
  trace.endBlock();

  return nbok == nb;
}

bool testDigitalSetConcept()
{
  BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet<Z2i::DigitalSet> ));
  BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet<Z3i::DigitalSet> ));

  typedef Z2i::Space Space;
  BOOST_CONCEPT_ASSERT(( concepts::CDomain< concepts::CDomainArchetype< Space > > ));
  typedef concepts::CDigitalSetArchetype<Z2i::Domain> DigitalSetArchetype;
  BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet<DigitalSetArchetype> ));

  return true;
}

int main()
{
  typedef SpaceND<4> Space4Type;
  typedef HyperRectDomain<Space4Type> Domain;
  typedef Space4Type::Point Point;

  Space4Type::Integer t[] =  { 1, 2, 3 , 4};
  Point a ( t );
  Space4Type::Integer t2[] = { 5, 5, 3 , 5};
  Point b ( t2);
  trace.beginBlock ( "HyperRectDomain init" );

  ///Domain characterized by points a and b
  Domain domain ( a, b );
  trace.info() << domain << std::endl;
  trace.info() << "Domain size= " << domain.size() << std::endl;
  trace.endBlock();

  trace.beginBlock( "DigitalSetBySTLVector" );
  bool okVector = testDigitalSet< DigitalSetBySTLVector<Domain> >
    ( DigitalSetBySTLVector<Domain>(domain), DigitalSetBySTLVector<Domain>(domain) );
  trace.endBlock();

  trace.beginBlock( "DigitalSetBySTLSet" );
  bool okSet = testDigitalSet< DigitalSetBySTLSet<Domain> >
    ( DigitalSetBySTLSet<Domain>(domain), DigitalSetBySTLSet<Domain>(domain) );
  trace.endBlock();

  trace.beginBlock( "DigitalSetFromMap" );
  typedef ImageContainerBySTLMap<Domain,short int> Map;
  Map map(domain); Map map2(domain);        //maps
  DigitalSetFromMap<Map> setFromMap(map);   //sets from these maps
  DigitalSetFromMap<Map> setFromMap2(map2);
  bool okMap = testDigitalSet< DigitalSetFromMap<Map> >( setFromMap, setFromMap2 );
  trace.endBlock();

  trace.beginBlock( "DigitalSetByAssociativeContainer" );
  typedef std::set<Point> Container;
  bool okAssoctestSet = testDigitalSet< DigitalSetByAssociativeContainer<Domain,Container> >
  ( DigitalSetByAssociativeContainer<Domain, Container>(domain), DigitalSetByAssociativeContainer<Domain, Container>(domain) );
  trace.endBlock();

  trace.beginBlock( "DigitalSetByUnorderedSet" );
  typedef std::unordered_set<Point> ContainerU;
  bool okUnorderedSet = testDigitalSet< DigitalSetByAssociativeContainer<Domain,ContainerU> >
  ( DigitalSetByAssociativeContainer<Domain, ContainerU>(domain), DigitalSetByAssociativeContainer<Domain, ContainerU>(domain) );
  trace.endBlock();

  bool okSelectorSmall = testDigitalSetSelector
      < Domain, SMALL_DS + LOW_VAR_DS + LOW_ITER_DS + LOW_BEL_DS >
      ( domain, "Small set" );

  bool okSelectorBig = testDigitalSetSelector
      < Domain, BIG_DS + LOW_VAR_DS + LOW_ITER_DS + LOW_BEL_DS >
      ( domain, "Big set" );

  bool okSelectorMediumHBel = testDigitalSetSelector
      < Domain, MEDIUM_DS + LOW_VAR_DS + LOW_ITER_DS + HIGH_BEL_DS >
      ( domain, "Medium set + High belonging test" );

  bool okDigitalSetDomain = testDigitalSetDomain();

  bool okDigitalSetDraw = testDigitalSetDraw();

  bool okDigitalSetDrawSnippet = testDigitalSetBoardSnippet();

  bool res = okVector && okSet && okMap
      && okSelectorSmall && okSelectorBig && okSelectorMediumHBel
      && okDigitalSetDomain && okDigitalSetDraw && okDigitalSetDrawSnippet
     && okUnorderedSet && okAssoctestSet;
  trace.endBlock();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  return res ? 0 : 1;
}

/** @ingroup Tests **/
