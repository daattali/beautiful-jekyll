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
 * @file testLabelledMap-benchmark.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 *
 * @date 2012/07/02
 *
 * This file is part of the DGtal library
 */

//#define TRACE_BITS

#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <forward_list>
#include <boost/version.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_smallint.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/geometric_distribution.hpp>
#include <boost/random/variate_generator.hpp>

#include "DGtal/base/Common.h"
#include "DGtal/base/LabelledMap.h"

// Before 1.47, random number generation in boost.
// Since 1.47, random number generation in boost::random. 
#define BOOST_MAJOR_VERSION  (BOOST_VERSION / 100000)
#define BOOST_MINOR_VERSION  (( BOOST_VERSION / 100) % 1000)
#define BOOST_SUBMINOR_VERSION  (BOOST_VERSION % 100)


using namespace DGtal;
using namespace std;

// A comparer en 2D
// Array[L][X][Y] of value
// Array[X][Y] of map<L,Value>
// map< <L,X,Y>, Value>
// Array[X][Y] of LabelledMap<L>
// Array[X][Y] of forward_list< pair<L, Value> >

/**
   Array[L][X][Y] of value.  Brute-force. High memory
   consumption. Rather fast except when working with several labels.

   Note that 4000*4000*16 is upper limit on my 8Gb laptop (2Gb).
   Note that 2000*2000*64 is upper limit on my 8Gb laptop (2Gb).
*/
template <typename Value, unsigned int L, unsigned int X, unsigned int Y>
class ArrayLXY {
  Value _data[ L ][ X ][ Y ];
  Value _invalid;

public:
  inline
  ArrayLXY( Value invalid )
  {
    _invalid = invalid;
    clear();
  }

  inline 
  void clear()
  {
    for ( unsigned int l = 0; l < L; ++l )
      for ( unsigned int y = 0; y < Y; ++y )
        for ( unsigned int x = 0; x < X; ++x )
          setValue( _invalid, l, x, y );
  }

  inline 
  const Value & value( unsigned int l, unsigned int x, unsigned int y ) const
  {
    return _data[ l ][ x ][ y ];
  }
  inline 
  unsigned int erase( unsigned int l, unsigned int x, unsigned int y )
  {
    if ( _data[ l ][ x ][ y ] != _invalid )
      {
        _data[ l ][ x ][ y ] = _invalid;
        return 1;
      }
    return 0;
  }

  inline 
  void setValue( const Value & val, unsigned int l, unsigned int x, unsigned int y )
  {
    _data[ l ][ x ][ y ] = val;
  }
  inline 
  void setValueNoNewLabel( const Value & val, unsigned int l, unsigned int x, unsigned int y )
  {
    _data[ l ][ x ][ y ] = val;
  }
  inline
  bool hasLabel( unsigned int l, unsigned int x, unsigned int y ) const
  {
    return value( l, x, y ) != _invalid;
  }
  inline 
  void getLabels( std::vector<unsigned int> & labels, 
                  unsigned int x, unsigned int y ) const
  {
    labels.clear();
    for ( unsigned int l = 0; l < L; ++l )
      if ( hasLabel( l, x, y ) )
        labels.push_back( l );
  }
  inline
  unsigned int nbLabels( unsigned int x, unsigned int y ) const
  {
    unsigned int nb = 0;
    for ( unsigned int l = 0; l < L; ++l )
      if ( hasLabel( l, x, y ) ) ++nb;
    return nb;
  }
  inline 
  void display ( ostream & , unsigned int , unsigned int , unsigned int  )
  {}

  inline
  unsigned long long area() const
  {
    return L * X * Y * sizeof( Value );
  }
};

/**
   Array[X][Y] of map<L,Value> Intermediate approach. Slower (between 30% and 40%) than
   ArrayXYOfLabelledMap and takes 50% to 100% twice as much place.

   Note that 4000*4000*16 takes 861Mb.
   Note that 2000*2000*64 takes 218Mb.
*/
template <typename Value, unsigned int L, unsigned int X, unsigned int Y>
class ArrayXYOfMap {
  typedef typename std::map<unsigned int, Value> MyMap;
  typedef typename MyMap::const_iterator ConstIterator;
  MyMap _data[ X ][ Y ];

public:
  inline
  ArrayXYOfMap()
  {
  }

  inline 
  void clear()
  {
      for ( unsigned int y = 0; y < Y; ++y )
        for ( unsigned int x = 0; x < X; ++x )
          _data[ x ][ y ].clear();
  }

  inline 
  const Value & value( unsigned int l, unsigned int x, unsigned int y )
  {
    return _data[ x ][ y ][ l ];
  }
  inline 
  unsigned int erase( unsigned int l, unsigned int x, unsigned int y )
  {
    return _data[ x ][ y ].erase( l );
  }

  inline 
  void setValue( const Value & val, unsigned int l, unsigned int x, unsigned int y )
  {
    _data[ x ][ y ][ l ] = val;
  }
  inline 
  void setValueNoNewLabel( const Value & val, unsigned int l, unsigned int x, unsigned int y )
  {
    _data[ x ][ y ][ l ] = val;
  }
  inline
  bool hasLabel( unsigned int l, unsigned int x, unsigned int y ) const
  {
    return _data[ x ][ y ].count( l ) != 0;
  }
  inline 
  void getLabels( std::vector<unsigned int> & labels, 
                  unsigned int x, unsigned int y ) const
  {
    labels.clear();
    for ( ConstIterator it = _data[ x ][ y ].begin(), it_end = _data[ x ][ y ].end();
          it != it_end; ++it )
      labels.push_back( (*it).first );
  }
  inline
  unsigned int nbLabels( unsigned int x, unsigned int y ) const
  {
    return _data[ x ][ y ].size();
  }
  inline 
  void display ( ostream & , unsigned int, unsigned int , unsigned int  )
  {}


  inline
  unsigned long long area() const
  {
    unsigned long long total = 0;
    for ( unsigned int y = 0; y < Y; ++y )
      for ( unsigned int x = 0; x < X; ++x )
        {
          unsigned int size = nbLabels( x, y );
          total += ( size + 1 ) *
            ( sizeof( Value ) // one value per node
              + 3 * sizeof( Value* ) // three pointers
              + 2 //_RbTreeColor { _S_red = false, _S_black = true };
              + 8 // dynamic allocation );
              );
        }
    return total;
  }
};


/**
   Array[X][Y] of forward_list< pair<L,Value> > Another intermediate
   approach which favors less memory and more computation time.

   Approximately same memory usage or 20% more as LabelledMap (for
   good values of N and M). Approximately 2 to 4 times slower than
   LabelledMap for most operations.

   Note that 2000*2000*32 takes 216Mb.
*/
template <typename Value, unsigned int L, unsigned int X, unsigned int Y>
class ArrayXYOfList {
  typedef typename std::pair<DGtal::uint16_t, Value> MyPair;
  typedef typename std::forward_list<MyPair> MyList;
  typedef typename MyList::iterator Iterator;
  typedef typename MyList::const_iterator ConstIterator;
  MyList _data[ X ][ Y ];

public:
  inline
  ArrayXYOfList()
  {
  }

  inline 
  void clear()
  {
      for ( unsigned int y = 0; y < Y; ++y )
        for ( unsigned int x = 0; x < X; ++x )
          _data[ x ][ y ].clear();
  }

  inline 
  const Value & value( unsigned int l, unsigned int x, unsigned int y )
  {
    MyList & list = _data[ x ][ y ];
    Iterator it = list.begin(), it_end = list.end(); 
    for ( ; it != it_end; ++it )
      {
        if ( it->first == l ) return it->second;
      }
    ASSERT ( it == it_end ) ;
    list.emplace_front( std::make_pair( l, Value() ) );
    return list.front().second;
  }
  inline 
  unsigned int erase( unsigned int l, unsigned int x, unsigned int y )
  {
    MyList & list = _data[ x ][ y ];
    Iterator it_prev = list.before_begin();
    Iterator it = list.begin(), it_end = list.end(); 
    for ( ; it != it_end; ++it )
      {
        if ( it->first == l )
          {
            list.erase_after( it_prev );
            return 1;
          }
        it_prev = it;
      }
    return 0;
  }

  inline 
  void setValue( const Value & val, unsigned int l, unsigned int x, unsigned int y )
  {
    MyList & list = _data[ x ][ y ];
    Iterator it = list.begin(), it_end = list.end(); 
    for ( ; it != it_end; ++it )
      {
        if ( it->first == l ) 
          {
            it->second = val;
            return;
          }
      }
    if ( it == it_end ) 
        list.emplace_front( std::make_pair( l, val ) );
  }
  inline 
  void setValueNoNewLabel( const Value & val, unsigned int l, unsigned int x, unsigned int y )
  {
    MyList & list = _data[ x ][ y ];
    Iterator it = list.begin(), it_end = list.end(); 
    for ( ; it != it_end; ++it )
      {
        if ( it->first == l ) 
          {
            it->second = val;
            return;
          }
      }
    if ( it == it_end ) 
      list.emplace_front( std::make_pair( l, val ) );
  }
  inline
  bool hasLabel( unsigned int l, unsigned int x, unsigned int y ) const
  {
    const MyList & list = _data[ x ][ y ];
    ConstIterator it = list.begin(), it_end = list.end(); 
    for ( ; it != it_end; ++it )
      {
        if ( it->first == l ) return true;
      }
    return false;
  }
  inline 
  void getLabels( std::vector<unsigned int> & labels, 
                  unsigned int x, unsigned int y ) const
  {
    labels.clear();
    const MyList & list = _data[ x ][ y ];
    ConstIterator it = list.begin(), it_end = list.end(); 
    for ( ; it != it_end; ++it )
      {
        labels.push_back( (*it).first );
      }
  }
  inline
  unsigned int nbLabels( unsigned int x, unsigned int y ) const
  {
    const MyList & list = _data[ x ][ y ];
    ConstIterator it = list.begin(), it_end = list.end(); 
    unsigned int n = 0;
    for ( ; it != it_end; ++it )
      ++n;
    return n;
  }
  inline 
  void display ( ostream & , unsigned int , unsigned int , unsigned int )
  {}


  inline
  unsigned long long area() const
  {
    unsigned long long total = 0;
    for ( unsigned int y = 0; y < Y; ++y )
      for ( unsigned int x = 0; x < X; ++x )
        {
          unsigned int size = nbLabels( x, y );
          total += sizeof( Value* )
            + ( size ) *
            ( sizeof( Value ) // one value per node
              + sizeof( Value* ) // one pointers
              + 2 // uint16_t
              + 8 // dynamic allocation );
              );
        }
    return total;
  }
};


/**
   Array[X][Y] of LabelledMap<L>

   The proposed alternative to the brute-force approach. Generally
   less than 10 times the memory used by brute force for L >= 16.
   Approximately 50% slower in most operations, except initialization
   or used of all labels. In this case outperforms Array[L][X][Y].

   Note that 4000*4000*16 is fine on my 8Gb laptop (529Mb).
   Note that 2000*2000*64 takes 133Mb.
*/
template < typename Value, unsigned int L, unsigned int X, unsigned int Y,
           typename TWord, unsigned int N, unsigned int M >
class ArrayXYOfLabelledMap {
  typedef LabelledMap< Value, L, TWord, N, M> MyLabelledMap;
  MyLabelledMap _data[ X ][ Y ];

public:
  inline
  ArrayXYOfLabelledMap() {}

  inline 
  const Value & value( unsigned int l, unsigned int x, unsigned int y ) const
  {
    return _data[ x ][ y ].fastAt( l );
  }

  inline 
  void setValue( const Value & val, unsigned int l, unsigned int x, unsigned int y )
  {
    _data[ x ][ y ][ l ] = val;
  }

  inline 
  unsigned int erase( unsigned int l, unsigned int x, unsigned int y )
  {
    return _data[ x ][ y ].erase( l );
  }

  inline 
  void setValueNoNewLabel( const Value & val, unsigned int l, unsigned int x, unsigned int y )
  {
    _data[ x ][ y ].fastAt( l ) = val;
  }

  inline
  bool hasLabel( unsigned int l, unsigned int x, unsigned int y ) const
  {
    return _data[ x ][ y ].count( l );
  }

  inline 
  void getLabels( std::vector<unsigned int> & labels, 
                  unsigned int x, unsigned int y ) const
  {
    _data[ x ][ y ].labels().getLabels( labels );
  }

  inline
  unsigned int nbLabels( unsigned int x, unsigned int y ) const
  {
    return _data[ x ][ y ].size();
  }
  inline void display ( ostream & , unsigned int , unsigned int x, unsigned int y )
  {
    std::cerr << _data[ x ][ y ] << endl;
  }

  inline
  unsigned long long area() const
  {
    unsigned long long total = 0;
    for ( unsigned int y = 0; y < Y; ++y )
      for ( unsigned int x = 0; x < X; ++x )
        {
          unsigned int size = nbLabels( x, y );
          total += sizeof( MyLabelledMap );
          if ( size > (N+1) )
            total += ( 1 + ( size - N - 1 ) / M ) * ( M * sizeof( Value ) + 8 );
        }
    return total;
  }

};

// boost::random is different since 1.47
#if (BOOST_MAJOR_VERSION >= 1 ) && (BOOST_MINOR_VERSION >= 47 )
template <typename MapLXY, unsigned int L, unsigned int X, unsigned int Y>
unsigned int
generateData( MapLXY & m, double proba_no_label, double proba_label )
{
  boost::random::mt19937 rng;         // produces randomness out of thin air
  rng.seed( 0 );
  boost::random::uniform_smallint<> diceL(0, L-1);  
  boost::random::uniform_01<> diceDouble;
  boost::random::geometric_distribution<> diceNbLabels( proba_label ); // Y
  // E(Y) = (1-p)/p,  Var(Y) = (1-p)/p^2
  std::cerr << "E(Y)=" << ( (1-proba_label)/proba_label )
            << " Var(Y)=" << ( (1-proba_label)/(proba_label*proba_label) )
            << std::endl;
  unsigned int total = 0;
  for ( unsigned int y = 0; y < Y; ++y )
    for ( unsigned int x = 0; x < X; ++x )
      {
        if ( diceDouble( rng ) >= proba_no_label )
          {
            unsigned int nb = diceNbLabels( rng );
            for ( unsigned int i = 0; i < nb; ++i )
              {
                unsigned int l = diceL( rng );
                double v = diceDouble( rng );
                m.setValue( v, l, x, y );
              }
            total += nb;
          }
      }
  std::cerr << "- " << total << " insertions." << endl;
  return total;
}
#else
// boost::random is different since 1.47, below <= 1.46
template <typename MapLXY, unsigned int L, unsigned int X, unsigned int Y>
unsigned int
generateData( MapLXY & m, double proba_no_label, double proba_label )
{
  boost::mt19937 rng;         // produces randomness out of thin air
  rng.seed( 0 );
  boost::uniform_smallint<> diceL(0, L-1);  
  boost::uniform_01<> diceDouble;
  boost::geometric_distribution<> nbLabelsDist( proba_label ); // Y
  boost::variate_generator
    <boost::mt19937&, 
     boost::geometric_distribution<> > diceNbLabels( rng, nbLabelsDist);
  // E(Y) = (1-p)/p,  Var(Y) = (1-p)/p^2
  std::cerr << "E(Y)=" << ( (1-proba_label)/proba_label )
            << " Var(Y)=" << ( (1-proba_label)/(proba_label*proba_label) )
            << std::endl;
  unsigned int total = 0;
  for ( unsigned int y = 0; y < Y; ++y )
    for ( unsigned int x = 0; x < X; ++x )
      {
        if ( diceDouble( rng ) >= proba_no_label )
          {
            unsigned int nb = diceNbLabels();
            for ( unsigned int i = 0; i < nb; ++i )
              {
                unsigned int l = diceL( rng );
                double v = diceDouble( rng );
                m.setValue( v, l, x, y );
              }
            total += nb;
          }
      }
  std::cerr << "- " << total << " insertions." << endl;
  return total;
}
#endif

template <typename MapLXY, unsigned int L, unsigned int X, unsigned int Y>
double 
sumAllData( MapLXY & m )
{
  double sum = 0.0;
  std::vector<unsigned int> labels;
  for ( unsigned int y = 0; y < Y; ++y )
    for ( unsigned int x = 0; x < X; ++x )
      {
        m.getLabels( labels, x, y );
        for ( unsigned int i = 0; i < labels.size(); ++i )
          sum += m.value( labels[ i ], x, y );
      }
  std::cerr << "- sum = " << sum << "." << endl;
  return sum;
}

template <typename MapLXY, unsigned int L, unsigned int X, unsigned int Y>
double 
sumOneData( MapLXY & m, unsigned int l )
{
  double sum = 0.0;
  for ( unsigned int y = 0; y < Y; ++y )
    for ( unsigned int x = 0; x < X; ++x )
      {
        if ( m.hasLabel( l, x, y ) )
          sum += m.value( l, x, y );
      }
  std::cerr << "- sum = " << sum << "." << endl;
  return sum;
}

template <typename MapLXY, unsigned int L, unsigned int X, unsigned int Y>
unsigned int
locateThreeData( MapLXY & m, unsigned int l1, unsigned int l2, unsigned int l3 )
{
  unsigned int loc3 = 0;
  for ( unsigned int y = 0; y < Y; ++y )
    for ( unsigned int x = 0; x < X; ++x )
      {
        if ( ( m.hasLabel( l1, x, y ) ) 
             && ( m.hasLabel( l2, x, y ) ) 
             && ( m.hasLabel( l3, x, y ) ) )
          ++loc3;
      }
  std::cerr << "- " << loc3 << " places with " << l1 << ", " << l2 << " ," << l3 << endl;
  return loc3;
}

template <typename MapLXY, unsigned int L, unsigned int X, unsigned int Y>
unsigned int 
eraseOneData( MapLXY & m, unsigned int l )
{
  unsigned int nb = 0;
  for ( unsigned int y = 0; y < Y; ++y )
    for ( unsigned int x = 0; x < X; ++x )
      {
        nb += m.erase( l, x, y );
      }
  std::cerr << "- " << nb << " values deleted." << endl;
  return nb;
}

int main()
{
  typedef double Value;
  static const unsigned int X = 100;
  static const unsigned int Y = 100;
  static const unsigned int L = 16;
  typedef DGtal::uint8_t Word;
  static const unsigned int N = 1;
  static const unsigned int M = 5;
  /// Probability that there is no data at this location.
  static const double PROBA_NO_LABEL = 0.75;
  /// If there is a possibility to have a data, this probability is
  /// used to define a geometric distribution that defines the number
  /// of data (ie valid labels) at this place. The smaller, the higher
  /// is the expectation. 0.5 means E(X) = 1.
  static const double PROBA_LABEL = 0.5;

  typedef ArrayLXY<Value, L, X, Y> MyArrayLXY;
  typedef ArrayXYOfMap<Value, L, X, Y> MyArrayXYOfMap;
  typedef ArrayXYOfList<Value, L, X, Y> MyArrayXYOfList;
  typedef ArrayXYOfLabelledMap<Value, L, X, Y, Word, N, M > MyArrayXYOfLabelledMap;

  //----------------------------------------------------------------------
  trace.beginBlock ( "---------- ArrayLXY ---------------" );
  trace.beginBlock ( "Generating ArrayLXY" );
  MyArrayLXY* arrayLXY = new MyArrayLXY( -1.0 );
  generateData< MyArrayLXY, L, X, Y> ( *arrayLXY, PROBA_NO_LABEL, PROBA_LABEL );
  trace.endBlock();

  trace.beginBlock ( "Memory usage in ArrayLXY" );
  std::cerr << arrayLXY->area() << " bytes." << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Sum all values ArrayLXY" );
  sumAllData< MyArrayLXY, L, X, Y> ( *arrayLXY );
  trace.endBlock();

  trace.beginBlock ( "Sum label 0 values ArrayLXY" );
  sumOneData< MyArrayLXY, L, X, Y> ( *arrayLXY, 0 );
  trace.endBlock();

  trace.beginBlock ( "Sum label 15 values ArrayLXY" );
  sumOneData< MyArrayLXY, L, X, Y> ( *arrayLXY, 15 );
  trace.endBlock();

  trace.beginBlock ( "Locate places (3, 7, 8) in ArrayLXY" );
  locateThreeData< MyArrayLXY, L, X, Y> ( *arrayLXY, 3, 7, 8 );
  trace.endBlock();

  trace.beginBlock ( "Erase label 9 in ArrayLXY" );
  eraseOneData< MyArrayLXY, L, X, Y> ( *arrayLXY, 9 );
  trace.endBlock();

  trace.beginBlock ( "Delete ArrayLXY" );
  delete arrayLXY;
  trace.endBlock();
  trace.endBlock();

  //----------------------------------------------------------------------
  trace.beginBlock ( "---------- ArrayXYOfMap ---------------" );
  trace.beginBlock ( "Generating ArrayXYOfMap" );
  MyArrayXYOfMap* arrayXYOfMap = new MyArrayXYOfMap();
  generateData< MyArrayXYOfMap, L, X, Y> ( *arrayXYOfMap, PROBA_NO_LABEL, PROBA_LABEL );
  trace.endBlock();

  trace.beginBlock ( "Memory usage in ArrayXYOfMap" );
  std::cerr << arrayXYOfMap->area() << " bytes." << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Sum all values ArrayXYOfMap" );
  sumAllData< MyArrayXYOfMap, L, X, Y> ( *arrayXYOfMap );
  trace.endBlock();

  trace.beginBlock ( "Sum label 0 values ArrayXYOfMap" );
  sumOneData< MyArrayXYOfMap, L, X, Y> ( *arrayXYOfMap, 0 );
  trace.endBlock();

  trace.beginBlock ( "Sum label 15 values ArrayXYOfMap" );
  sumOneData< MyArrayXYOfMap, L, X, Y> ( *arrayXYOfMap, 15 );
  trace.endBlock();

  trace.beginBlock ( "Locate places (3, 7, 8) in ArrayXYOfMap" );
  locateThreeData< MyArrayXYOfMap, L, X, Y> ( *arrayXYOfMap, 3, 7, 8 );
  trace.endBlock();

  trace.beginBlock ( "Erase label 9 in ArrayXYOfMap" );
  eraseOneData< MyArrayXYOfMap, L, X, Y> ( *arrayXYOfMap, 9 );
  trace.endBlock();

  trace.beginBlock ( "Delete ArrayXYOfMap" );
  delete arrayXYOfMap;
  trace.endBlock();
  trace.endBlock();

  //----------------------------------------------------------------------
  trace.beginBlock ( "---------- ArrayXYOfList ---------------" );
  trace.beginBlock ( "Generating ArrayXYOfList" );
  MyArrayXYOfList* arrayXYOfList = new MyArrayXYOfList();
  generateData< MyArrayXYOfList, L, X, Y> ( *arrayXYOfList, PROBA_NO_LABEL, PROBA_LABEL );
  trace.endBlock();

  trace.beginBlock ( "Memory usage in ArrayXYOfList" );
  std::cerr << arrayXYOfList->area() << " bytes." << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Sum all values ArrayXYOfList" );
  sumAllData< MyArrayXYOfList, L, X, Y> ( *arrayXYOfList );
  trace.endBlock();

  trace.beginBlock ( "Sum label 0 values ArrayXYOfList" );
  sumOneData< MyArrayXYOfList, L, X, Y> ( *arrayXYOfList, 0 );
  trace.endBlock();

  trace.beginBlock ( "Sum label 15 values ArrayXYOfList" );
  sumOneData< MyArrayXYOfList, L, X, Y> ( *arrayXYOfList, 15 );
  trace.endBlock();

  trace.beginBlock ( "Locate places (3, 7, 8) in ArrayXYOfList" );
  locateThreeData< MyArrayXYOfList, L, X, Y> ( *arrayXYOfList, 3, 7, 8 );
  trace.endBlock();

  trace.beginBlock ( "Erase label 9 in ArrayXYOfList" );
  eraseOneData< MyArrayXYOfList, L, X, Y> ( *arrayXYOfList, 9 );
  trace.endBlock();

  trace.beginBlock ( "Delete ArrayXYOfList" );
  delete arrayXYOfList;
  trace.endBlock();
  trace.endBlock();

  //----------------------------------------------------------------------
  trace.beginBlock ( "---------- ArrayXYOfLabelledMap ---------------" );
  trace.beginBlock ( "Generating ArrayXYOfLabelledMap" );
  MyArrayXYOfLabelledMap* arrayXYOfLabelledMap = new MyArrayXYOfLabelledMap;
  generateData< MyArrayXYOfLabelledMap, L, X, Y > ( *arrayXYOfLabelledMap, PROBA_NO_LABEL, PROBA_LABEL );
  trace.endBlock();

  trace.beginBlock ( "Memory usage in ArrayXYOfLabelledMap" );
  std::cerr << arrayXYOfLabelledMap->area() << " bytes." << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Sum all values ArrayXYOfLabelledMap" );
  sumAllData< MyArrayXYOfLabelledMap, L, X, Y> ( *arrayXYOfLabelledMap );
  trace.endBlock();

  trace.beginBlock ( "Sum label 0 values ArrayXYOfLabelledMap" );
  sumOneData< MyArrayXYOfLabelledMap, L, X, Y> ( *arrayXYOfLabelledMap, 0 );
  trace.endBlock();

  trace.beginBlock ( "Sum label 15 values ArrayXYOfLabelledMap" );
  sumOneData< MyArrayXYOfLabelledMap, L, X, Y> ( *arrayXYOfLabelledMap, 15 );
  trace.endBlock();

  trace.beginBlock ( "Locate places (3, 7, 8) in ArrayXYOfLabelledMap" );
  locateThreeData< MyArrayXYOfLabelledMap, L, X, Y> ( *arrayXYOfLabelledMap, 3, 7, 8 );
  trace.endBlock();

  trace.beginBlock ( "Erase label 9 in ArrayXYOfLabelledMap" );
  eraseOneData< MyArrayXYOfLabelledMap, L, X, Y> ( *arrayXYOfLabelledMap, 9 );
  trace.endBlock();

  trace.beginBlock ( "Delete ArrayXYOfLabelledMap" );
  delete arrayXYOfLabelledMap;
  trace.endBlock();
  trace.endBlock();

  return 0;
}
/** @ingroup Tests **/
