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
 * @file testSimpleExpander.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/09/20
 *
 * Functions for testing class SimpleExpander.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/DomainPredicate.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/kernel/sets/DigitalSetSelector.h"
#include "DGtal/kernel/sets/DigitalSetConverter.h"
#include "DGtal/topology/MetricAdjacency.h"
#include "DGtal/topology/DomainMetricAdjacency.h"
#include "DGtal/topology/DomainAdjacency.h"
#include "DGtal/topology/DigitalTopology.h"
#include "DGtal/topology/Object.h"
#include "DGtal/graph/Expander.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/io/Color.h"
#include "DGtal/helpers/StdDefs.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;



struct MyStyleCustom : public DrawableWithBoard2D
{
  virtual void setStyle(Board2D & aboard) const
  {
    aboard.setFillColorRGBi(0, 169, 0);
  }
};

struct MyStyleCustomRed : public DrawableWithBoard2D
{
  virtual void setStyle(Board2D & aboard) const
  {
    aboard.setFillColorRGBi(169, 0, 0);
  }
};
///////////////////////////////////////////////////////////////////////////////
// Functions for testing class SimpleExpander.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testSimpleExpander()
{
  trace.beginBlock ( "(4,8) Filling ..." );

  //typedef int Integer;                // choose your digital line here.
  typedef SpaceND<2> Z2;          // Z^2
  typedef Z2::Point Point;
  typedef MetricAdjacency<Z2, 1> Adj4; // 4-adjacency type
  typedef MetricAdjacency<Z2, 2> Adj8; // 8-adjacency type
  typedef DigitalTopology< Adj8, Adj4 > DT8_4; //8,4 topology type
  typedef HyperRectDomain< Z2 > Domain;
  //typedef Domain::ConstIterator DomainConstIterator;
  typedef DigitalSetSelector < Domain, BIG_DS + HIGH_BEL_DS >::Type DigitalSet;
  typedef Object<DT8_4, DigitalSet> ObjectType;


  typedef Object<DT8_4::ReverseTopology, DigitalSet> ObjectTypeReverseTopo;

  typedef Expander<ObjectTypeReverseTopo> ObjectExpanderReverseTopo;
  typedef Expander<ObjectType> ObjectExpander;

  Point p1( -5, -5 );
  Point p2( 5, 5 );
  Domain domain( p1, p2 );

  Adj4 adj4;                          // instance of 4-adjacency
  Adj8 adj8;                          // instance of 8-adjacency
  DT8_4 dt8_4(adj8, adj4, JORDAN_DT );
  DT8_4::ReverseTopology dt4_8(adj4, adj8, JORDAN_DT );

  //We construct a simple "house" set
  DigitalSet houseSet( domain );

  for ( int k = -3; k < 3 ; k++)
  {
    houseSet.insert(Point(k, -3));
    houseSet.insert(Point(-3, k));
    houseSet.insert(Point(3, k));
    houseSet.insert(Point(k, 3));
  }

  //We compute the complement
  DigitalSet houseSetCompl( domain);
  houseSetCompl.assignFromComplement( houseSet );

  //We create the objects associated to the sets
  ObjectType house8( dt8_4, houseSet );
  ObjectType houseCompl8( dt8_4, houseSetCompl );
  ObjectTypeReverseTopo house4(dt4_8, houseSet);
  ObjectTypeReverseTopo houseCompl4( dt4_8, houseSetCompl );


  //Board Export init
  Board2D board;
  board.setUnit(LibBoard::Board::UCentimeter);

  //Border=4 Filling=4
  board.clear();
  board << SetMode( domain.className(), "Grid" ) << domain;
  board << SetMode( house4.className(), "DrawAdjacencies" ) << house4;
  ObjectExpanderReverseTopo expander(houseCompl4, Point(0, 0));
  while (!expander.finished())
  {
   for ( ObjectExpander::ConstIterator it = expander.begin();
        it != expander.end();
        ++it )
      std::cout << " " << *it;

    expander.nextLayer();
  }
  board << CustomStyle(expander.core().className(), new MyStyleCustom) << expander.core();
  board.saveSVG("house4-4.svg");

  //Border=4 Filling=8
  board.clear();
  board << SetMode( domain.className(), "Grid" ) << domain;
  board << SetMode( house4.className(), "DrawAdjacencies" ) << house4;
  ObjectExpander expander8(houseCompl8, Point(0, 0));
  while (!expander8.finished())
  {
    for ( ObjectExpander::ConstIterator it = expander8.begin();
        it != expander8.end();
        ++it )
      std::cout << " " << *it;

    expander8.nextLayer();
  }
  board << CustomStyle(expander8.core().className(), new MyStyleCustom) << expander8.core();
  board.saveSVG("house4-8.svg");

  //Border=8 Filling=8
  board.clear();
  board << SetMode( domain.className(), "Grid" ) << domain;
  board << SetMode( house8.className(), "DrawAdjacencies" ) << house8;
  ObjectExpander expander88(houseCompl8, Point(0, 0));
  while (!expander88.finished())
  {
    for ( ObjectExpander::ConstIterator it = expander88.begin();
        it != expander88.end();
        ++it )
      std::cout << " " << *it;

    expander88.nextLayer();
  }
  board << CustomStyle(expander88.core().className(), new MyStyleCustom) << expander88.core();
  board.saveSVG("house8-8.svg");

  //Border=8 Filling=4
  board.clear();
  board << SetMode( domain.className(), "Grid" ) << domain;
  board << SetMode( house8.className(), "DrawAdjacencies" ) << house8;
  ObjectExpanderReverseTopo expander84(houseCompl4, Point(0, 0));
  while (!expander84.finished())
  {
    for ( ObjectExpander::ConstIterator it = expander84.begin();
        it != expander84.end();
        ++it )
      std::cout << " " << *it;

    expander84.nextLayer();
  }
  board << CustomStyle(expander.core().className(), new MyStyleCustom) << expander84.core();
  board.saveSVG("house8-4.svg");


  trace.endBlock();

  return true;
}

using namespace DGtal::Z2i;

bool testLayers()
{

  GradientColorMap<int> cmap_grad( 0, 30 );
  cmap_grad.addColor( Color( 128, 128, 255 ) );
  cmap_grad.addColor( Color( 255, 255, 128 ) );
  cmap_grad.addColor( Color( 128, 255, 128 ) );
  cmap_grad.addColor( Color( 128, 128, 128 ) );
  //cmap_grad.addColor( Color( 220, 130, 25 ) );

  trace.beginBlock ( "(4,8) Filling ..." );

  //typedef Domain::ConstIterator DomainConstIterator;
  typedef Object8_4 ObjectType;
  typedef Object4_8 ObjectTypeReverseTopo;
  typedef Expander<ObjectTypeReverseTopo> ObjectExpanderReverseTopo;
  typedef Expander<ObjectType> ObjectExpander;

  Point p1( -5, -5 );
  Point p2( 5, 5 );
  Domain domain( p1, p2 );


  //We construct a simple "house" set
  DigitalSet houseSet( domain );

  for ( int k = -3; k < 3 ; k++)
  {
    houseSet.insert(Point(k, -3));
    houseSet.insert(Point(-3, k));
    houseSet.insert(Point(3, k));
    houseSet.insert(Point(k, 3));
  }

  //We compute the complement
  DigitalSet houseSetCompl( domain);
  houseSetCompl.assignFromComplement( houseSet );

  //We create the objects associated to the sets
  ObjectType house8( dt8_4, houseSet );
  ObjectType houseCompl8( dt8_4, houseSetCompl );
  ObjectTypeReverseTopo house4( dt4_8, houseSet);
  ObjectTypeReverseTopo houseCompl4( dt4_8, houseSetCompl );


  //Board Export init
  Board2D board;
  board.setUnit(LibBoard::Board::UCentimeter);

  //Border=4 Filling=4
  board.clear();
  board << SetMode( domain.className(), "Grid" ) << domain;
  board << SetMode( house4.className(), "DrawAdjacencies" ) << house4;
  ObjectExpanderReverseTopo expander(houseCompl4, Point(0, 0));
  board << CustomStyle( expander.core().className(), 
      new CustomFillColor( cmap_grad( 0 ) ) )
  << expander.core();
  while (!expander.finished())
    {
      for ( ObjectExpander::ConstIterator it = expander.begin();
      it != expander.end();
      ++it )
  std::cout << " " << *it;
      board << CustomStyle( expander.layer().className(), 
          new CustomFillColor
          ( cmap_grad( expander.distance() ) ) )
      << expander.layer();
      
      expander.nextLayer();
    }
  board.saveSVG("house-layers4-4.svg");

  //Border=4 Filling=8
  board.clear();
  board << SetMode( domain.className(), "Grid" ) << domain;
  board << SetMode( house4.className(), "DrawAdjacencies" ) << house4;
  ObjectExpander expander8(houseCompl8, Point(0, 0));
  board << CustomStyle( expander.core().className(), 
      new CustomFillColor( cmap_grad( 0 ) ) )
  << expander8.core();
  while (!expander8.finished())
    {
      for ( ObjectExpander::ConstIterator it = expander8.begin();
      it != expander8.end();
      ++it )
  std::cout << " " << *it;
      
      board << CustomStyle( expander8.layer().className(), 
          new CustomFillColor
          ( cmap_grad( expander8.distance() ) ) )
      << expander8.layer();
      expander8.nextLayer();
    }
  board.saveSVG("house-layers4-8.svg");

  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testSimpleExpander()
    && testLayers();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
