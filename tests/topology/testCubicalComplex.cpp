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
 * @file testCubicalComplex.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2015/08/28
 *
 * Functions for testing class CubicalComplex.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <map>
#include <unordered_map>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/KhalimskyCellHashFunctions.h"
#include "DGtal/topology/CubicalComplex.h"
#include "DGtal/topology/CubicalComplexFunctions.h"
#include "DGtalCatch.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;


///////////////////////////////////////////////////////////////////////////////
// Functions for testing class CubicalComplex.
///////////////////////////////////////////////////////////////////////////////

static const int NBCELLS = 1000;

SCENARIO( "CubicalComplex< K3,std::unordered_map<> > unit tests (incidence,...)", "[cubical_complex][incidence]" )
{
  typedef KhalimskySpaceND<3>                       KSpace;
  typedef KSpace::Point                             Point;
  typedef KSpace::Cell                              Cell;
  typedef std::unordered_map<Cell, CubicalCellData> Map;
  typedef CubicalComplex< KSpace, Map >             CC;
  typedef CC::CellMapConstIterator                  CellMapConstIterator;

  srand( 0 );
  KSpace K;
  K.init( Point( 0,0,0 ), Point( 512,512,512 ), true );
  std::vector<int>  nbCoFaces( 4, 0 );
  std::vector<int>  nbFaces( 6, 0 );
  std::vector<int>  nbFaces2( 6, 0 );
  std::vector<int>  nbBdry( 10, 0 );
  std::vector<int>  nbBdry2( 10, 0 );

  GIVEN( "A cubical complex with random 3-cells" ) {
    CC complex( K );
    for ( int n = 0; n < NBCELLS; ++n )
      {
        Point p( (rand() % 512) | 0x1, (rand() % 512) | 0x1, (rand() % 512) | 0x1 );
        Cell cell = K.uCell( p );
        complex.insertCell( cell );
      }
    THEN( "It has only 3-cells and no other type of cells" ) {
      REQUIRE( complex.nbCells( 0 ) == 0 );
      REQUIRE( complex.nbCells( 1 ) == 0 );
      REQUIRE( complex.nbCells( 2 ) == 0 );
      REQUIRE( complex.nbCells( 3 ) > 0 );
    }

    WHEN( "Computing proper faces of these 3-cells" ) {
      std::vector<Cell> faces;
      std::back_insert_iterator< std::vector<Cell> > outIt( faces );
      for ( CellMapConstIterator it = complex.begin( 3 ), itE = complex.end( 3 );
            it != itE; ++it )
        complex.faces( outIt, it->first );
      THEN( "There are no proper faces within this complex" ) {
        REQUIRE( faces.size() == 0 );
      }
    }

    WHEN( "Closing the cubical complex" ) {
      complex.close();
      THEN( "It has cells of all dimensions." ) {
        REQUIRE( complex.nbCells( 0 ) > 0 );
        REQUIRE( complex.nbCells( 1 ) > 0 );
        REQUIRE( complex.nbCells( 2 ) > 0 );
      }

      WHEN( "Computing the direct co-faces of 2-cells" ) {
        for ( CellMapConstIterator it = complex.begin( 2 ), itE = complex.end( 2 );
              it != itE; ++it )
          {
            std::vector<Cell> faces;
            std::back_insert_iterator< std::vector<Cell> > outIt( faces );
            complex.directCoFaces( outIt, it->first );
            int n = static_cast<int>(faces.size());
            if ( n >= 3 ) n = 3; // should not happen
            nbCoFaces[ n ]++;
          }
        THEN( "None of them are incident to zero 3-cells" ) {
          REQUIRE( nbCoFaces[ 0 ] == 0 );
        } AND_THEN ( "Most of them are incident to one 3-cells and some of them to two 3-cells" ) {
          REQUIRE( nbCoFaces[ 1 ] > 10*nbCoFaces[ 2 ] );
        } AND_THEN ("None of them are incident to three or more 3-cells" ) {
          REQUIRE( nbCoFaces[ 3 ] == 0 );
        }
      }

      WHEN( "Computing direct faces of 2-cells" ) {
        for ( CellMapConstIterator it = complex.begin( 2 ), itE = complex.end( 2 );
              it != itE; ++it )
          {
            std::vector<Cell> faces;
            std::back_insert_iterator< std::vector<Cell> > outIt( faces );
            complex.directFaces( outIt, it->first, true );
            auto n = faces.size();
            if ( n < 4 ) n = 3; // should not happen
            if ( n > 4 ) n = 5; // should not happen
            nbFaces[ n ]++;
          }
        for ( CellMapConstIterator it = complex.begin( 2 ), itE = complex.end( 2 );
              it != itE; ++it )
          {
            std::vector<Cell> faces;
            std::back_insert_iterator< std::vector<Cell> > outIt( faces );
            complex.directFaces( outIt, it->first );
            auto n = faces.size();
            if ( n < 4 ) n = 3; // should not happen
            if ( n > 4 ) n = 5; // should not happen
            nbFaces2[ n ]++;
          }
        THEN( "All of them have exactly 4 incident 1-cells when computed with hint closed" ) {
          REQUIRE( nbFaces[ 3 ] == 0 );
          REQUIRE( nbFaces[ 4 ] > 0 );
          REQUIRE( nbFaces[ 5 ] == 0 );
        } AND_THEN( "All of them have exactly 4 incident 1-cells when computed without hint" ) {
          REQUIRE( nbFaces2[ 3 ] == 0 );
          REQUIRE( nbFaces2[ 4 ] > 0 );
          REQUIRE( nbFaces2[ 5 ] == 0 );
        } AND_THEN( "It gives the same number of incident cells with or without hint" ) {
          REQUIRE( nbFaces[ 4 ] == nbFaces2[ 4 ] );
        }
      }

      WHEN( "Computing boundaries of 2-cells" ) {
        for ( CellMapConstIterator it = complex.begin( 2 ), itE = complex.end( 2 );
              it != itE; ++it )
          {
            CC::Cells faces = complex.cellBoundary( it->first, true );
            size_t n = faces.size();
            if ( n < 8 ) n = 7; // should not happen
            if ( n > 8 ) n = 9; // should not happen
            nbBdry[ n ]++;
          }
        for ( CellMapConstIterator it = complex.begin( 2 ), itE = complex.end( 2 );
              it != itE; ++it )
          {
            CC::Cells faces = complex.cellBoundary( it->first, false );
            size_t n = faces.size();
            if ( n < 8 ) n = 7; // should not happen
            if ( n > 8 ) n = 9; // should not happen
            nbBdry2[ n ]++;
          }
        THEN( "All of them contain exactly 8 cells when computed with hint closed" ) {
          REQUIRE( nbBdry[ 7 ] == 0 );
          REQUIRE( nbBdry[ 8 ] > 0 );
          REQUIRE( nbBdry[ 9 ] == 0 );
        } AND_THEN( "All of them contain exactly 8 cells when computed without hint" ) {
          REQUIRE( nbBdry2[ 7 ] == 0 );
          REQUIRE( nbBdry2[ 8 ] > 0 );
          REQUIRE( nbBdry2[ 9 ] == 0 );
        } AND_THEN( "It gives the same number of incident cells with or without hint" ) {
          REQUIRE( nbBdry[ 8 ] == nbBdry2[ 8 ] );
        }
      }
    }  // WHEN( "Closing the cubical complex" ) {
  }
}

SCENARIO( "CubicalComplex< K3,std::unordered_map<> > collapse tests", "[cubical_complex][collapse]" )
{
  typedef KhalimskySpaceND<3>                       KSpace;
  typedef KSpace::Point                             Point;
  typedef KSpace::Cell                              Cell;
  typedef KSpace::Integer                           Integer;
  typedef std::unordered_map<Cell, CubicalCellData> Map;
  typedef CubicalComplex< KSpace, Map >             CC;
  typedef CC::CellMapIterator                       CellMapIterator;

  srand( 0 );
  KSpace K;
  K.init( Point( 0,0,0 ), Point( 512,512,512 ), true );

  GIVEN( "A closed cubical complex made of 3x3x3 voxels with their incident cells" ) {
    CC complex( K );
    std::vector<Cell> S;
    for ( Integer x = 0; x < 3; ++x )
      for ( Integer y = 0; y < 3; ++y )
        for ( Integer z = 0; z < 3; ++z )
          {
            S.push_back( K.uSpel( Point( x, y, z ) ) );
            complex.insertCell( S.back() );
          }
    complex.close();
    CAPTURE( complex.nbCells( 0 ) );
    CAPTURE( complex.nbCells( 1 ) );
    CAPTURE( complex.nbCells( 2 ) );
    CAPTURE( complex.nbCells( 3 ) );

    THEN( "It has Euler characteristic 1" ) {
      REQUIRE( complex.euler() == 1 );
    }

    WHEN( "Fixing two vertices of this big cube and collapsing it" ) {
      CellMapIterator it1 = complex.findCell( 0, K.uCell( Point( 0, 0, 0 ) ) );
      CellMapIterator it2 = complex.findCell( 0, K.uCell( Point( 4, 4, 4 ) ) );
      REQUIRE( it1 != complex.end( 0 ) );
      REQUIRE( it2 != complex.end( 0 ) );
      it1->second.data |= CC::FIXED;
      it2->second.data |= CC::FIXED;
      CC::DefaultCellMapIteratorPriority P;
      functions::collapse( complex, S.begin(), S.end(), P, false, true );
      CAPTURE( complex.nbCells( 0 ) );
      CAPTURE( complex.nbCells( 1 ) );
      CAPTURE( complex.nbCells( 2 ) );
      CAPTURE( complex.nbCells( 3 ) );

      THEN( "It keeps its topology so its euler characteristic is 1" ) {
       REQUIRE( complex.euler() == 1 );
      } AND_THEN( "It has no more 2-cells and 3-cells" ) {
        REQUIRE( complex.nbCells( 2 ) == 0 );
        REQUIRE( complex.nbCells( 3 ) == 0 );
      } AND_THEN( "It has only 0-cells and 1-cells" ) {
        REQUIRE( complex.nbCells( 0 ) > 0 );
        REQUIRE( complex.nbCells( 1 ) > 0 );
      }
    }
  }
}

SCENARIO( "CubicalComplex< K3,std::unordered_map<> > link tests", "[cubical_complex][link]" )
{
  typedef KhalimskySpaceND<3>                       KSpace;
  typedef KSpace::Point                             Point;
  typedef KSpace::Cell                              Cell;
  typedef KSpace::Integer                           Integer;
  typedef std::unordered_map<Cell, CubicalCellData> Map;
  typedef CubicalComplex< KSpace, Map >             CC;

  srand( 0 );
  KSpace K;
  K.init( Point( 0,0,0 ), Point( 512,512,512 ), true );

  GIVEN( "A closed cubical complex made of 10x10x10 voxels with their incident cells" ) {
    CC X( K );
    CC S( K );
    for ( Integer x = 0; x < 10; ++x )
      for ( Integer y = 0; y < 10; ++y )
        for ( Integer z = 0; z < 10; ++z )
          {
            Cell c = K.uSpel( Point( x, y, z ) );
            if ( x*y*z != 0 )
              S.insert( K.uPointel( Point( x, y, z ) ) );
            X.insertCell( c );
          }
    X.close();
    THEN( "It has Euler characteristic 1" ) {
      REQUIRE( X.euler() == 1 );
    }

    WHEN( "Computing the link of its inner pointels without hint" ) {
      CC link_S_v1 = X.link( S );

      THEN( "This link is homeomorphic to a sphere and has euler characteristic 2" ) {
        REQUIRE( link_S_v1.euler() == 2 );
      }
    }

    WHEN( "Computing the link of its inner pointels with full hints" ) {
      CC link_S_v2 = X.link( S, true, true );

      THEN( "This link is again homeomorphic to a sphere and has euler characteristic 2" ) {
        REQUIRE( link_S_v2.euler() == 2 );
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// STD::MAP
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

SCENARIO( "CubicalComplex< K3,std::map<> > unit tests (incidence,...)", "[cubical_complex][incidence]" )
{
  typedef KhalimskySpaceND<3>               KSpace;
  typedef KSpace::Point            Point;
  typedef KSpace::Cell             Cell;
  typedef std::map<Cell, CubicalCellData>   Map;
  typedef CubicalComplex< KSpace, Map >     CC;
  typedef CC::CellMapConstIterator CellMapConstIterator;

  srand( 0 );
  KSpace K;
  K.init( Point( 0,0,0 ), Point( 512,512,512 ), true );
  std::vector<int>  nbCoFaces( 4, 0 );
  std::vector<int>  nbFaces( 6, 0 );
  std::vector<int>  nbFaces2( 6, 0 );
  std::vector<int>  nbBdry( 10, 0 );
  std::vector<int>  nbBdry2( 10, 0 );

  GIVEN( "A cubical complex with random 3-cells" ) {
    CC complex( K );
    for ( int n = 0; n < NBCELLS; ++n )
      {
        Point p( (rand() % 512) | 0x1, (rand() % 512) | 0x1, (rand() % 512) | 0x1 );
        Cell cell = K.uCell( p );
        complex.insertCell( cell );
      }
    THEN( "It has only 3-cells and no other type of cells" ) {
      REQUIRE( complex.nbCells( 0 ) == 0 );
      REQUIRE( complex.nbCells( 1 ) == 0 );
      REQUIRE( complex.nbCells( 2 ) == 0 );
      REQUIRE( complex.nbCells( 3 ) > 0 );
    }

    WHEN( "Computing proper faces of these 3-cells" ) {
      std::vector<Cell> faces;
      std::back_insert_iterator< std::vector<Cell> > outIt( faces );
      for ( CellMapConstIterator it = complex.begin( 3 ), itE = complex.end( 3 );
            it != itE; ++it )
        complex.faces( outIt, it->first );
      THEN( "There are no proper faces within this complex" ) {
        REQUIRE( faces.size() == 0 );
      }
    }

    WHEN( "Closing the cubical complex" ) {
      complex.close();
      THEN( "It has cells of all dimensions." ) {
        REQUIRE( complex.nbCells( 0 ) > 0 );
        REQUIRE( complex.nbCells( 1 ) > 0 );
        REQUIRE( complex.nbCells( 2 ) > 0 );
      }

      WHEN( "Computing the direct co-faces of 2-cells" ) {
        for ( CellMapConstIterator it = complex.begin( 2 ), itE = complex.end( 2 );
              it != itE; ++it )
          {
            std::vector<Cell> faces;
            std::back_insert_iterator< std::vector<Cell> > outIt( faces );
            complex.directCoFaces( outIt, it->first );
            auto n = faces.size();
            if ( n >= 3 ) n = 3; // should not happen
            nbCoFaces[ n ]++;
          }
        THEN( "None of them are incident to zero 3-cells" ) {
          REQUIRE( nbCoFaces[ 0 ] == 0 );
        } AND_THEN ( "Most of them are incident to one 3-cells and some of them to two 3-cells" ) {
          REQUIRE( nbCoFaces[ 1 ] > 10*nbCoFaces[ 2 ] );
        } AND_THEN ("None of them are incident to three or more 3-cells" ) {
          REQUIRE( nbCoFaces[ 3 ] == 0 );
        }
      }

      WHEN( "Computing direct faces of 2-cells" ) {
        for ( CellMapConstIterator it = complex.begin( 2 ), itE = complex.end( 2 );
              it != itE; ++it )
          {
            std::vector<Cell> faces;
            std::back_insert_iterator< std::vector<Cell> > outIt( faces );
            complex.directFaces( outIt, it->first, true );
            auto n = faces.size();
            if ( n < 4 ) n = 3; // should not happen
            if ( n > 4 ) n = 5; // should not happen
            nbFaces[ n ]++;
          }
        for ( CellMapConstIterator it = complex.begin( 2 ), itE = complex.end( 2 );
              it != itE; ++it )
          {
            std::vector<Cell> faces;
            std::back_insert_iterator< std::vector<Cell> > outIt( faces );
            complex.directFaces( outIt, it->first );
            auto n = faces.size();
            if ( n < 4 ) n = 3; // should not happen
            if ( n > 4 ) n = 5; // should not happen
            nbFaces2[ n ]++;
          }
        THEN( "All of them have exactly 4 incident 1-cells when computed with hint closed" ) {
          REQUIRE( nbFaces[ 3 ] == 0 );
          REQUIRE( nbFaces[ 4 ] > 0 );
          REQUIRE( nbFaces[ 5 ] == 0 );
        } AND_THEN( "All of them have exactly 4 incident 1-cells when computed without hint" ) {
          REQUIRE( nbFaces2[ 3 ] == 0 );
          REQUIRE( nbFaces2[ 4 ] > 0 );
          REQUIRE( nbFaces2[ 5 ] == 0 );
        } AND_THEN( "It gives the same number of incident cells with or without hint" ) {
          REQUIRE( nbFaces[ 4 ] == nbFaces2[ 4 ] );
        }
      }

      WHEN( "Computing boundaries of 2-cells" ) {
        for ( CellMapConstIterator it = complex.begin( 2 ), itE = complex.end( 2 );
              it != itE; ++it )
          {
            CC::Cells faces = complex.cellBoundary( it->first, true );
            auto n = faces.size();
            if ( n < 8 ) n = 7; // should not happen
            if ( n > 8 ) n = 9; // should not happen
            nbBdry[ n ]++;
          }
        for ( CellMapConstIterator it = complex.begin( 2 ), itE = complex.end( 2 );
              it != itE; ++it )
          {
            CC::Cells faces = complex.cellBoundary( it->first, false );
            auto n = faces.size();
            if ( n < 8 ) n = 7; // should not happen
            if ( n > 8 ) n = 9; // should not happen
            nbBdry2[ n ]++;
          }
        THEN( "All of them contain exactly 8 cells when computed with hint closed" ) {
          REQUIRE( nbBdry[ 7 ] == 0 );
          REQUIRE( nbBdry[ 8 ] > 0 );
          REQUIRE( nbBdry[ 9 ] == 0 );
        } AND_THEN( "All of them contain exactly 8 cells when computed without hint" ) {
          REQUIRE( nbBdry2[ 7 ] == 0 );
          REQUIRE( nbBdry2[ 8 ] > 0 );
          REQUIRE( nbBdry2[ 9 ] == 0 );
        } AND_THEN( "It gives the same number of incident cells with or without hint" ) {
          REQUIRE( nbBdry[ 8 ] == nbBdry2[ 8 ] );
        }
      }
    }  // WHEN( "Closing the cubical complex" ) {
  }
}

SCENARIO( "CubicalComplex< K3,std::map<> > collapse tests", "[cubical_complex][collapse]" )
{
  typedef KhalimskySpaceND<3>               KSpace;
  typedef KSpace::Point            Point;
  typedef KSpace::Cell             Cell;
  typedef KSpace::Integer          Integer;
  typedef std::map<Cell, CubicalCellData>   Map;
  typedef CubicalComplex< KSpace, Map >     CC;
  typedef CC::CellMapIterator      CellMapIterator;

  srand( 0 );
  KSpace K;
  K.init( Point( 0,0,0 ), Point( 512,512,512 ), true );

  GIVEN( "A closed cubical complex made of 3x3x3 voxels with their incident cells" ) {
    CC complex( K );
    std::vector<Cell> S;
    for ( Integer x = 0; x < 3; ++x )
      for ( Integer y = 0; y < 3; ++y )
        for ( Integer z = 0; z < 3; ++z )
          {
            S.push_back( K.uSpel( Point( x, y, z ) ) );
            complex.insertCell( S.back() );
          }
    complex.close();
    CAPTURE( complex.nbCells( 0 ) );
    CAPTURE( complex.nbCells( 1 ) );
    CAPTURE( complex.nbCells( 2 ) );
    CAPTURE( complex.nbCells( 3 ) );

    THEN( "It has Euler characteristic 1" ) {
      REQUIRE( complex.euler() == 1 );
    }

    WHEN( "Fixing two vertices of this big cube and collapsing it" ) {
      CellMapIterator it1 = complex.findCell( 0, K.uCell( Point( 0, 0, 0 ) ) );
      CellMapIterator it2 = complex.findCell( 0, K.uCell( Point( 4, 4, 4 ) ) );
      REQUIRE( it1 != complex.end( 0 ) );
      REQUIRE( it2 != complex.end( 0 ) );
      it1->second.data |= CC::FIXED;
      it2->second.data |= CC::FIXED;
      CC::DefaultCellMapIteratorPriority P;
      functions::collapse( complex, S.begin(), S.end(), P, false, true );
      CAPTURE( complex.nbCells( 0 ) );
      CAPTURE( complex.nbCells( 1 ) );
      CAPTURE( complex.nbCells( 2 ) );
      CAPTURE( complex.nbCells( 3 ) );

      THEN( "It keeps its topology so its euler characteristic is 1" ) {
       REQUIRE( complex.euler() == 1 );
      } AND_THEN( "It has no more 2-cells and 3-cells" ) {
        REQUIRE( complex.nbCells( 2 ) == 0 );
        REQUIRE( complex.nbCells( 3 ) == 0 );
      } AND_THEN( "It has only 0-cells and 1-cells" ) {
        REQUIRE( complex.nbCells( 0 ) > 0 );
        REQUIRE( complex.nbCells( 1 ) > 0 );
      }
    }
  }
}

SCENARIO( "CubicalComplex< K3,std::map<> > link tests", "[cubical_complex][link]" )
{
  typedef KhalimskySpaceND<3>               KSpace;
  typedef KSpace::Point            Point;
  typedef KSpace::Cell             Cell;
  typedef KSpace::Integer          Integer;
  typedef std::map<Cell, CubicalCellData>   Map;
  typedef CubicalComplex< KSpace, Map >     CC;

  srand( 0 );
  KSpace K;
  K.init( Point( 0,0,0 ), Point( 512,512,512 ), true );

  GIVEN( "A closed cubical complex made of 10x10x10 voxels with their incident cells" ) {
    CC X( K );
    CC S( K );
    for ( Integer x = 0; x < 10; ++x )
      for ( Integer y = 0; y < 10; ++y )
        for ( Integer z = 0; z < 10; ++z )
          {
            Cell c = K.uSpel( Point( x, y, z ) );
            if ( x*y*z != 0 )
              S.insert( K.uPointel( Point( x, y, z ) ) );
            X.insertCell( c );
          }
    X.close();
    THEN( "It has Euler characteristic 1" ) {
      REQUIRE( X.euler() == 1 );
    }

    WHEN( "Computing the link of its inner pointels without hint" ) {
      CC link_S_v1 = X.link( S );

      THEN( "This link is homeomorphic to a sphere and has euler characteristic 2" ) {
        REQUIRE( link_S_v1.euler() == 2 );
      }
    }

    WHEN( "Computing the link of its inner pointels with full hints" ) {
      CC link_S_v2 = X.link( S, true, true );

      THEN( "This link is again homeomorphic to a sphere and has euler characteristic 2" ) {
        REQUIRE( link_S_v2.euler() == 2 );
      }
    }
  }
}

SCENARIO( "CubicalComplex< K3,std::map<> > concept check tests", "[cubical_complex][concepts]" )
{
  typedef KhalimskySpaceND<3>               KSpace;
  typedef KSpace::Cell                      Cell;
  typedef std::map<Cell, CubicalCellData>   Map;
  typedef CubicalComplex< KSpace, Map >     CC;

  BOOST_CONCEPT_ASSERT(( boost::Container<CC> ));
  BOOST_CONCEPT_ASSERT(( boost::ForwardIterator<CC::Iterator> ));
  BOOST_CONCEPT_ASSERT(( boost::ForwardIterator<CC::ConstIterator> ));
}


SCENARIO( "CubicalComplex< K2,std::map<> > set operations and relations", "[cubical_complex][ccops]" )
{
  typedef KhalimskySpaceND<2>               KSpace;
  typedef KSpace::Space                     Space;
  typedef HyperRectDomain<Space>            Domain;
  typedef KSpace::Point                     Point;
  typedef KSpace::Cell                      Cell;
  typedef std::map<Cell, CubicalCellData>   Map;
  typedef CubicalComplex< KSpace, Map >     CC;

  using namespace DGtal::functions;

  KSpace K;
  K.init( Point( 0,0 ), Point( 5,3 ), true );
  Domain domain( Point( 0,0 ), Point( 5,3 ) );
  CC X1( K );
  X1.insertCell( K.uSpel( Point(1,1) ) );
  X1.insertCell( K.uSpel( Point(2,1) ) );
  X1.insertCell( K.uSpel( Point(3,1) ) );
  X1.insertCell( K.uSpel( Point(2,2) ) );
  CC X1c = ~ X1;

  CC X2( K );
  X2.insertCell( K.uSpel( Point(2,2) ) );
  X2.insertCell( K.uSpel( Point(3,2) ) );
  X2.insertCell( K.uSpel( Point(4,2) ) );
  X2.close();
  CC X2c = ~ X2;
  REQUIRE( ( X1 & X2 ).size() < X1.size() );
  bool X1_and_X2_included_in_X1 = ( X1 & X2 ) <= X1;
  bool X1c_and_X2c_included_in_X1c = ( X1c & X2c ) <= X1c;
  CC A = ~( X1 & X2 );
  CC B = ~( *(X1c & X2c) );
  CAPTURE( A );
  CAPTURE( B );
  bool cl_X1_and_X2_equal_to_X1c_and_X2c = A == B;

  REQUIRE( X1_and_X2_included_in_X1 );
  REQUIRE( X1c_and_X2c_included_in_X1c );
  REQUIRE( cl_X1_and_X2_equal_to_X1c_and_X2c );

  CC X1bd = X1c - *X1c;
  CAPTURE( X1bd );
  CAPTURE( X1.boundary() );
  bool X1bd_equal_X1boundary = X1bd == X1.boundary();
  REQUIRE( X1bd_equal_X1boundary );
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
