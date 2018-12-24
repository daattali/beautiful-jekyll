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
#if __GXX_EXPERIMENTAL_CXX0X__  && ( __GNUC__ >= 4 ) && ( __GNUC_MINOR__ >= 6 )
#include <forward_list>
#endif
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
template <typename Value>
class DynArrayLXY {
public:
  typedef Value ValueType;
  const unsigned int L;
  const unsigned int X;
  const unsigned int Y;

private:
  Value* _data;
  Value _invalid;

public:
  inline
  DynArrayLXY( unsigned int _L, unsigned int _X, unsigned int _Y, Value invalid )
    : L( _L ), X( _X ), Y( _Y )
  {
    _invalid = invalid;
    _data = new Value[ L * X * Y ];
    clear();
  }
  inline
  ~DynArrayLXY()
  {
    delete[] _data;
  }
  inline 
  void clear()
  {
    for ( unsigned int l = 0; l < L; ++l )
      for ( unsigned int x = 0; x < X; ++x )
        for ( unsigned int y = 0; y < Y; ++y )
          setValue( _invalid, l, x, y );
  }

  inline
  size_t offset( unsigned int l, unsigned int x, unsigned int y ) const
  {
    return ( ( l * X ) + x ) * Y + y;
  }
  inline 
  const Value & value( unsigned int l, unsigned int x, unsigned int y ) const
  {
    return _data[ offset( l, x, y ) ];
  }
  inline 
  unsigned int erase( unsigned int l, unsigned int x, unsigned int y )
  {
    size_t offs = offset( l, x, y ); 
    if ( _data[ offs ] != _invalid )
      {
        _data[ offs ] = _invalid;
        return 1;
      }
    return 0;
  }

  inline 
  void setValue( const Value & val, unsigned int l, unsigned int x, unsigned int y )
  {
    _data[ offset( l, x, y ) ] = val;
  }
  inline 
  void setValueNoNewLabel( const Value & val, unsigned int l, unsigned int x, unsigned int y )
  {
    _data[ offset( l, x, y ) ] = val;
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
template <typename Value>
class DynArrayXYOfMap {
  typedef typename std::map<unsigned int, Value> MyMap;
  typedef typename MyMap::const_iterator ConstIterator;

public:
  typedef Value ValueType;
  const unsigned int L;
  const unsigned int X;
  const unsigned int Y;

private:
  MyMap* _data;

public:
  inline
  DynArrayXYOfMap( unsigned int _L, unsigned int _X, unsigned int _Y )
    : L( _L ), X( _X ), Y( _Y )
  {
    _data = new MyMap[ X * Y ];
  }
  inline
  ~DynArrayXYOfMap()
  {
    delete[] _data;
  }
  inline
  size_t offset( unsigned int x, unsigned int y ) const
  {
    return x * Y + y;
  }

  inline 
  void clear()
  {
    for ( unsigned int x = 0; x < X; ++x )
      for ( unsigned int y = 0; y < Y; ++y )
        _data[ offset( x, y ) ].clear();
  }

  inline 
  const Value & value( unsigned int l, unsigned int x, unsigned int y )
  {
    return _data[ offset( x, y ) ][ l ];
  }
  inline 
  unsigned int erase( unsigned int l, unsigned int x, unsigned int y )
  {
    return _data[ offset( x, y ) ].erase( l );
  }

  inline 
  void setValue( const Value & val, unsigned int l, unsigned int x, unsigned int y )
  {
    _data[ offset( x, y ) ][ l ] = val;
  }
  inline 
  void setValueNoNewLabel( const Value & val, unsigned int l, unsigned int x, unsigned int y )
  {
    _data[ offset( x, y ) ][ l ] = val;
  }
  inline
  bool hasLabel( unsigned int l, unsigned int x, unsigned int y ) const
  {
    return _data[ offset( x, y ) ].count( l ) != 0;
  }
  inline 
  void getLabels( std::vector<unsigned int> & labels, 
                  unsigned int x, unsigned int y ) const
  {
    labels.clear();
    for ( ConstIterator it = _data[ offset( x, y ) ].begin(), 
            it_end = _data[ offset( x, y ) ].end();
          it != it_end; ++it )
      labels.push_back( (*it).first );
  }
  inline
  unsigned int nbLabels( unsigned int x, unsigned int y ) const
  {
    return _data[ offset( x, y ) ].size();
  }
  inline 
  void display ( ostream & , unsigned int , unsigned int , unsigned int  )
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


#if __GXX_EXPERIMENTAL_CXX0X__  && ( __GNUC__ >= 4 ) && ( __GNUC_MINOR__ >= 6 )

/**
   Array[X][Y] of forward_list< pair<L,Value> > Another intermediate
   approach which favors less memory and more computation time.

   Approximately same memory usage or 20% more as LabelledMap (for
   good values of N and M). Approximately 2 to 4 times slower than
   LabelledMap for most operations.

   Note that 2000*2000*32 takes 216Mb.
*/
template <typename Value>
class DynArrayXYOfList {
  typedef typename std::pair<uint16_t, Value> MyPair;
  typedef typename std::forward_list<MyPair> MyList;
  typedef typename MyList::iterator Iterator;
  typedef typename MyList::const_iterator ConstIterator;
public:
  typedef Value ValueType;
  const unsigned int L;
  const unsigned int X;
  const unsigned int Y;

private:
  MyList* _data;


public:
  inline
  DynArrayXYOfList( unsigned int _L, unsigned int _X, unsigned int _Y )
    : L( _L ), X( _X ), Y( _Y )
  {
    _data = new MyList[ X * Y ];
  }
  inline
  ~DynArrayXYOfList()
  {
    delete[] _data;
  }
  inline
  size_t offset( unsigned int x, unsigned int y ) const
  {
    return x * Y + y;
  }

  inline 
  void clear()
  {
      for ( unsigned int y = 0; y < Y; ++y )
        for ( unsigned int x = 0; x < X; ++x )
          _data[ offset( x, y ) ].clear();
  }

  inline 
  const Value & value( unsigned int l, unsigned int x, unsigned int y )
  {
    MyList & list = _data[ offset( x, y ) ];
    Iterator it = list.begin(), it_end = list.end(); 
    for ( ; it != it_end; ++it )
      {
        if ( it->first == l ) return it->second;
      }
    ASSERT(it == it_end);
    list.emplace_front( std::make_pair( l, Value() ) );
    return list.front().second;
  }
  inline 
  unsigned int erase( unsigned int l, unsigned int x, unsigned int y )
  {
    MyList & list = _data[ offset( x, y ) ];
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
    MyList & list = _data[ offset( x, y ) ];
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
    MyList & list = _data[ offset( x, y ) ];
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
    const MyList & list = _data[ offset( x, y ) ];
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
    const MyList & list = _data[ offset( x, y ) ];
    ConstIterator it = list.begin(), it_end = list.end(); 
    for ( ; it != it_end; ++it )
      {
        labels.push_back( (*it).first );
      }
  }
  inline
  unsigned int nbLabels( unsigned int x, unsigned int y ) const
  {
    const MyList & list = _data[ offset( x, y ) ];
    ConstIterator it = list.begin(), it_end = list.end(); 
    unsigned int n = 0;
    for ( ; it != it_end; ++it )
      ++n;
    return n;
  }
  inline 
  void display ( ostream & , unsigned int , unsigned int , unsigned int  )
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

#endif

/**
   Array[X][Y] of LabelledMap<L>

   The proposed alternative to the brute-force approach. Generally
   less than 10 times the memory used by brute force for L >= 16.
   Approximately 50% slower in most operations, except initialization
   or used of all labels. In this case outperforms Array[L][X][Y].

   Note that 4000*4000*16 is fine on my 8Gb laptop (529Mb).
   Note that 2000*2000*64 takes 133Mb.
*/
template < typename Value, unsigned int L,
           typename TWord, unsigned int N, unsigned int M >
class DynArrayXYOfLabelledMap {
  typedef LabelledMap< Value, L, TWord, N, M> MyLabelledMap;
public:
  typedef Value ValueType;
  const unsigned int X;
  const unsigned int Y;

private:
  MyLabelledMap* _data;

public:
  inline
  DynArrayXYOfLabelledMap( unsigned int _X, unsigned int _Y )
    : X( _X ), Y( _Y )
  {
    _data = new MyLabelledMap[ X * Y ];
  }
  inline
  ~DynArrayXYOfLabelledMap()
  {
    delete[] _data;
  }
  inline
  size_t offset( unsigned int x, unsigned int y ) const
  {
    return x * Y + y;
  }

  inline 
  void clear()
  {
      for ( unsigned int y = 0; y < Y; ++y )
        for ( unsigned int x = 0; x < X; ++x )
          _data[ offset( x, y ) ].clear();
  }

  inline 
  const Value & value( unsigned int l, unsigned int x, unsigned int y ) const
  {
    return _data[ offset( x, y ) ].fastAt( l );
  }

  inline 
  void setValue( const Value & val, unsigned int l, unsigned int x, unsigned int y )
  {
    _data[ offset( x, y ) ][ l ] = val;
  }

  inline 
  unsigned int erase( unsigned int l, unsigned int x, unsigned int y )
  {
    return _data[ offset( x, y ) ].erase( l );
  }

  inline 
  void setValueNoNewLabel( const Value & val, unsigned int l, unsigned int x, unsigned int y )
  {
    _data[ offset( x, y ) ].fastAt( l ) = val;
  }

  inline
  bool hasLabel( unsigned int l, unsigned int x, unsigned int y ) const
  {
    return _data[ offset( x, y ) ].count( l );
  }

  inline 
  void getLabels( std::vector<unsigned int> & labels, 
                  unsigned int x, unsigned int y ) const
  {
    _data[ offset( x, y ) ].labels().getLabels( labels );
  }

  inline
  unsigned int nbLabels( unsigned int x, unsigned int y ) const
  {
    return _data[ offset( x, y ) ].size();
  }
  inline void display ( ostream & , unsigned int , unsigned int x, unsigned int y )
  {
    std::cerr << _data[ offset( x, y ) ] << endl;
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


// template <typename MapLXY>
// unsigned int
// generateData( MapLXY & m, unsigned int L, double proba_no_label, double proba_label )
// {
//   BOOST_RANDOM_NAMESPACE::mt19937 rng;         // produces randomness out of thin air
//   rng.seed( 0 );
//   BOOST_RANDOM_NAMESPACE::uniform_smallint<> diceL(0, L-1);  
//   BOOST_RANDOM_NAMESPACE::uniform_01<> diceDouble;
//   BOOST_RANDOM_NAMESPACE::geometric_distribution<> diceNbLabels( proba_label ); // Y
//   // E(Y) = (1-p)/p,  Var(Y) = (1-p)/p^2
//   std::cerr << "E(Y)=" << ( (1-proba_label)/proba_label )
//             << " Var(Y)=" << ( (1-proba_label)/(proba_label*proba_label) )
//             << std::endl;
//   unsigned int X = m.X;
//   unsigned int Y = m.Y;
//   unsigned int total = 0;
//   for ( unsigned int y = 0; y < Y; ++y )
//     for ( unsigned int x = 0; x < X; ++x )
//       {
//         if ( diceDouble( rng ) >= proba_no_label )
//           {
//             unsigned int nb = diceNbLabels( rng );
//             for ( unsigned int i = 0; i < nb; ++i )
//               {
//                 unsigned int l = diceL( rng );
//                 double v = diceDouble( rng );
//                 // if ( ( x == 408 ) && ( y == 171 ) )
//                 //   {
//                 //     std::cerr << "+ Insert( " << l << ", " << v << " ) l=";
//                 //     m.display ( std::cerr, l, x, y );
//                 //   }
//                 m.setValue( v, l, x, y );
//               }
//             total += nb;
//           }
//       }
//   std::cerr << "- " << total << " insertions." << endl;
//   return total;
// }

// boost::random is different since 1.47
#if (BOOST_MAJOR_VERSION >= 1 ) && (BOOST_MINOR_VERSION >= 47 )
template <typename MapLXY>
unsigned int
generateData( MapLXY & m, unsigned int L, double proba_no_label, double proba_label )
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
  unsigned int X = m.X;
  unsigned int Y = m.Y;
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
template <typename MapLXY>
unsigned int
generateData( MapLXY & m, unsigned int L, double proba_no_label, double proba_label )
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
  unsigned int X = m.X;
  unsigned int Y = m.Y;
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

template <typename MapLXY>
double 
sumAllData( MapLXY & m )
{
  unsigned int X = m.X;
  unsigned int Y = m.Y;
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

template <typename MapLXY>
double 
sumOneData( MapLXY & m, unsigned int l )
{
  unsigned int X = m.X;
  unsigned int Y = m.Y;
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

template <typename MapLXY>
unsigned int
locateThreeData( MapLXY & m, unsigned int l1, unsigned int l2, unsigned int l3 )
{
  unsigned int X = m.X;
  unsigned int Y = m.Y;
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

template <typename MapLXY>
unsigned int 
eraseOneData( MapLXY & m, unsigned int l )
{
  unsigned int X = m.X;
  unsigned int Y = m.Y;
  unsigned int nb = 0;
  for ( unsigned int y = 0; y < Y; ++y )
    for ( unsigned int x = 0; x < X; ++x )
      {
        nb += m.erase( l, x, y );
      }
  return nb;
}

template <typename MapLXY>
void generateStatsMultiMapXY( const string & name,
                               MapLXY & m,
                               const unsigned int L,
                               const unsigned int X,
                               const unsigned int Y,
                               double PROBA_NO_LABEL, 
                               double PROBA_LABEL )
{
  typedef typename MapLXY::ValueType Value;
  //----------------------------------------------------------------------
  string msg = "Generating statistics for " + name;
  trace.beginBlock ( msg.c_str() );
  trace.beginBlock ( "Generating data." );
  generateData< MapLXY > ( m, L, PROBA_NO_LABEL, PROBA_LABEL );
  long tgen = trace.endBlock();

  trace.beginBlock ( "Memory usage." );
  unsigned long long mem = m.area();
  trace.info() << mem << " bytes." << std::endl;
  long tmem = trace.endBlock();

  trace.beginBlock ( "Sum all values." );
  double sumAll = sumAllData< MapLXY > ( m );
  trace.info() << "- sum_all = " << sumAll << "." << endl;
  long tsumall = trace.endBlock();

  trace.beginBlock ( "Sum label 0 values." );
  double sum0 = sumOneData< MapLXY > ( m, 0 );
  trace.info() << "- sum_0 = " << sum0 << "." << endl;
  long tsum0 = trace.endBlock();

  trace.beginBlock ( "Sum label 15 values." );
  double sum15 = sumOneData< MapLXY > ( m, 15 );
  trace.info() << "- sum_15 = " << sum15 << "." << endl;
  long tsum15 = trace.endBlock();

  trace.beginBlock ( "Locate places (3, 7, 8)." );
  unsigned int nbThree =   locateThreeData< MapLXY > ( m, 3, 7, 8 );
  trace.info() << "- " << nbThree << " places (3, 7, 8) detected." << endl;
  long tthree = trace.endBlock();

  trace.beginBlock ( "Erase label 9." );
  unsigned int nbErased = eraseOneData< MapLXY > ( m, 9 );
  trace.info() << "- " << nbErased << " values deleted." << endl;
  long terase9 = trace.endBlock();

  trace.beginBlock ( "Clear data" );
  m.clear();
  long tclear = trace.endBlock();
  trace.endBlock();

  std::cout << name << " " << L << " " << X << " " << Y 
            << " " << PROBA_NO_LABEL << " " << PROBA_LABEL
            << " " << sizeof(Value) << " " << sizeof(Value*) << " " << mem 
            << " " << tgen << " " << tmem 
            << " " << tsumall << " " << tsum0  << " " << tsum15 
            << " " << tthree << " " << terase9  << " " << tclear 
            << " " << sumAll << " " << sum0  << " " << sum15
            << " " << nbThree << " " << nbErased 
            << std::endl;
}

#define GENERATE_STATS_NM( Word, N , M )            \
  { \
  typedef DynArrayXYOfLabelledMap<Value,L,Word,N,M> MyArrayXYOfLabelledMap; \
  MyArrayXYOfLabelledMap* anArrayXYOfLabelledMap = new MyArrayXYOfLabelledMap( X, Y ); \
  generateStatsMultiMapXY( "DynArrayXYOfLabelledMap<double," #Word "," #N "," #M ">", \
                           *anArrayXYOfLabelledMap, L, X, Y, PROB_NO_DATA, PROB_ONE_DATA ); \
  delete anArrayXYOfLabelledMap; \
  }


///////////////////////////////////////////////////////////////////////////////


int main( int /*argc*/, char** /*argv*/ )
{
  typedef double Value;
  static const unsigned int L = 16;
  trace.info()<< "Test several multi-map structures and compute some statistics." <<std::endl << "With parameter: "<<std::endl
	      << "\t tested image size: 500  500"<<std::endl
	      <<"Probability that there is no data at all at an image position (Bernouilli distribution): 0.5"
	      << "Probability for the geometric distribution of the number of data per image position (E(Y)=(1-p)/p, Var(Y)=(1-p)/p^2 :0.5"<< std::endl;
  
  

  unsigned int X =  100;
  unsigned int Y =  100;
  /// Probability that there is no data at this location.
  double PROB_NO_DATA =  0.5;
  /// If there is a possibility to have a data, this probability is
  /// used to define a geometric distribution that defines the number
  /// of data (ie valid labels) at this place. The smaller, the higher
  /// is the expectation. 0.5 means E(X) = 1.
  double PROB_ONE_DATA = 0.5;

  typedef DynArrayLXY<Value> MyArrayLXY;
  MyArrayLXY* anArrayLXY = new MyArrayLXY( L, X, Y, -1.0 );
  generateStatsMultiMapXY( "DynArrayLXY<double>", 
                         *anArrayLXY, L, X, Y, PROB_NO_DATA, PROB_ONE_DATA );
  delete anArrayLXY;

  typedef DynArrayXYOfMap<Value> MyArrayXYOfMap;
  MyArrayXYOfMap* anArrayXYOfMap = new MyArrayXYOfMap( L, X, Y );
  generateStatsMultiMapXY( "DynArrayXYOfMap<double>", 
                         *anArrayXYOfMap, L, X, Y, PROB_NO_DATA, PROB_ONE_DATA );
  delete anArrayXYOfMap;

#if __GXX_EXPERIMENTAL_CXX0X__  && ( __GNUC__ >= 4 ) && ( __GNUC_MINOR__ >= 6 )
  typedef DynArrayXYOfList<Value> MyArrayXYOfList;
  MyArrayXYOfList* anArrayXYOfList = new MyArrayXYOfList( L, X, Y );
  generateStatsMultiMapXY( "DynArrayXYOfList<double>", 
                         *anArrayXYOfList, L, X, Y, PROB_NO_DATA, PROB_ONE_DATA );
  delete anArrayXYOfList;
#endif

  GENERATE_STATS_NM( DGtal::uint8_t, 1, 2 )
  GENERATE_STATS_NM( DGtal::uint8_t, 1, 3 )
  GENERATE_STATS_NM( DGtal::uint8_t, 1, 4 )
  GENERATE_STATS_NM( DGtal::uint8_t, 1, 5 )
  GENERATE_STATS_NM( DGtal::uint8_t, 1, 6 )
  GENERATE_STATS_NM( DGtal::uint8_t, 1, 7 )
  GENERATE_STATS_NM( DGtal::uint8_t, 1, 8 )

  GENERATE_STATS_NM( DGtal::uint8_t, 2, 2 )
  GENERATE_STATS_NM( DGtal::uint8_t, 2, 3 )
  GENERATE_STATS_NM( DGtal::uint8_t, 2, 4 )
  GENERATE_STATS_NM( DGtal::uint8_t, 2, 5 )
  GENERATE_STATS_NM( DGtal::uint8_t, 2, 6 )
  GENERATE_STATS_NM( DGtal::uint8_t, 2, 7 )
  GENERATE_STATS_NM( DGtal::uint8_t, 2, 8 )

  GENERATE_STATS_NM( DGtal::uint8_t, 3, 2 )
  GENERATE_STATS_NM( DGtal::uint8_t, 3, 3 )
  GENERATE_STATS_NM( DGtal::uint8_t, 3, 4 )
  GENERATE_STATS_NM( DGtal::uint8_t, 3, 5 )
  GENERATE_STATS_NM( DGtal::uint8_t, 3, 6 )
  GENERATE_STATS_NM( DGtal::uint8_t, 3, 7 )
  GENERATE_STATS_NM( DGtal::uint8_t, 3, 8 )

  GENERATE_STATS_NM( DGtal::uint8_t, 4, 2 )
  GENERATE_STATS_NM( DGtal::uint8_t, 4, 3 )
  GENERATE_STATS_NM( DGtal::uint8_t, 4, 4 )
  GENERATE_STATS_NM( DGtal::uint8_t, 4, 5 )
  GENERATE_STATS_NM( DGtal::uint8_t, 4, 6 )
  GENERATE_STATS_NM( DGtal::uint8_t, 4, 7 )
  GENERATE_STATS_NM( DGtal::uint8_t, 4, 8 )

  GENERATE_STATS_NM( DGtal::uint8_t, 5, 2 )
  GENERATE_STATS_NM( DGtal::uint8_t, 5, 3 )
  GENERATE_STATS_NM( DGtal::uint8_t, 5, 4 )
  GENERATE_STATS_NM( DGtal::uint8_t, 5, 5 )
  GENERATE_STATS_NM( DGtal::uint8_t, 5, 6 )
  GENERATE_STATS_NM( DGtal::uint8_t, 5, 7 )
  GENERATE_STATS_NM( DGtal::uint8_t, 5, 8 )


  return 0;
}
/** @ingroup Tests **/
