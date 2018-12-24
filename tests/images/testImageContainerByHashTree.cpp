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
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/22
 *
 * Functions for testing class ImageContainerBenchmark.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include <cmath>
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/ImageContainerByHashTree.h"

///////////////////////////////////////////////////////////////////////////////

#define dim experimental::ImageContainerByHashTree<Domain , T, DGtal::uint64_t >::dim
#define defHashKey typename experimental::ImageContainerByHashTree<Domain , int,  DGtal::uint64_t >::HashKey

using namespace DGtal;

int iRand ( int iMin, int iMax )
{
  double f = ( double ) rand() / RAND_MAX;
  return (int) (iMin + static_cast<double> ( f * ( iMax - iMin ) ));
}

template<typename Domain, typename T >
bool test_setVal (experimental::ImageContainerByHashTree<Domain , T, DGtal::uint64_t >& container, bool checkAfterEachSet )
{
  srand ( (unsigned int)time ( NULL ) );

  //phase 1
  trace.info() << "Test: set" <<std::endl;
  trace.info() << "phase 1..." <<std::endl;
  //unsigned DepthMask = container.ROOT_KEY << container.getDepth()*dim;
  unsigned DepthMask = 100000;
  //cerr << "DepthMask = " << DepthMask << std::endl;
  for ( int key = DepthMask; key > 1; --key )
    {
      if ( !container.isKeyValid ( key ) )
        {
          continue;
        }
      //count ++;
      container.setValue ( key, iRand ( 0, 100 ) );
      if ( checkAfterEachSet )
  { 
    if ( !container.checkIntegrity() )
      {
        trace.info() << "test_set: failure in phase 1" << std::endl
       << "at key " << Bits::bitString ( key ) << std::endl;
        return false;
      }
    else
      trace.info() << "ok"<<std::endl;
  }
    }
  trace.info() << "checking the container's validity..." << std::endl;
  if ( !container.checkIntegrity() )
    {

      trace.info() << "test_set: failure in phase 1" << std::endl;
      return false;
    }

  //phase 2
  trace.info() << "phase 2..." <<std::endl;
  for ( unsigned key = container.ROOT_KEY; key < DepthMask; ++key )
    {
      if ( !container.isKeyValid ( key ) )
        {
          continue;
        }
      container.setValue ( key, iRand ( 0, 100 ) );
      if ( checkAfterEachSet )
        if ( !container.checkIntegrity() )
          {
            trace.info() << "test_set: failure in phase 2" << std::endl
                 << "at key " << Bits::bitString ( key ) << std::endl;
            return false;
          }
    }

  if ( !container.checkIntegrity() )
    {
      trace.info() << "test_set: failure in phase 2" << std::endl;
      return false;
    }

  trace.info() << "test_set: success !" << std::endl;
  return true;
}


template<typename Domain, typename T >
bool test_get ( experimental::ImageContainerByHashTree<Domain, T, DGtal::uint64_t >& container, bool  )
{
  srand ( (unsigned int)time ( NULL ) );
  unsigned count = 0;
  //unsigned DepthMask = container.ROOT_KEY << container.getDepth()*dim;
  unsigned DepthMask = 100000;
  //trace.info() << "DepthMask "<< DepthMask << std::endl;
  for ( unsigned key = DepthMask; key > container.ROOT_KEY; --key )
    {
      if ( !container.isKeyValid ( key ) )
        {
          //trace.info() << "invalid key "<< Bits::bitString(key) << std::endl;
          continue;
        }
      ++count;
      T val = iRand ( 0, 100 );
      //trace.info() << "plop1" << std::endl;
      //trace.info() << "___________________________ set: " << Bits::bitString(key, 16) << std::endl;
      container.setValue ( key, val );


      typename experimental::ImageContainerByHashTree<Domain , T, DGtal::uint64_t >::HashKey key2 = key;
      while ( container.isKeyValid ( key2 ) )
        {
          key2 = key2 << dim;
          if ( val != container.get ( key2 ) )
            {
              trace.info() << "test_get: failure" << std::endl
                   << "at key " << Bits::bitString ( key2 ) << std::endl;
              return false;
            }
          //trace.info() << "check " << Bits::bitString(key2) << " ok." << std::endl;
        }
      //key2 <<=dim;
    }
  trace.info() << "test_get: success !" << std::endl
       << "tested with " << count << " keys" << std::endl;
  return true;
}



int main ( int argc, char** argv )
{
  trace.beginBlock ( "Testing class ImageContainerBenchmark" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << std::endl;

  typedef SpaceND<5> Space;
  typedef HyperRectDomain<Space> Dom;
  typedef DGtal::experimental::ImageContainerByHashTree<Dom, int, DGtal::uint64_t> Tree;
  Tree tree ( 12,5,1 );
  // Do not pass concept.
  //BOOST_CONCEPT_ASSERT((CDrawableWithBoard2D<Tree>));

  //tree.printInternalState(cerr, 12);
  Dom::Point p1, p2, p3;
  trace.info() << "azertyuiop" << std::endl;
  p1[0] = -32;
  p1[1] = -10;
  p1[2] = -30;
  p1[3] =  20;
  p1[4] =  0;

  p2[0] = 32;
  p2[1] = 32;
  p2[2] = 20;
  p2[3] = 64;
  p2[4] = 120;

  p3[0] = 1;
  p3[1] = 1;
  p3[2] = 1;
  p3[3] = 1;
  p3[4] = 1;
  trace.info() << "azertyuiop" << std::endl;
  DGtal::experimental::ImageContainerByHashTree<Dom, int, DGtal::uint64_t> tree2 ( 12,p1, p2,1 );
  trace.info() << "azertyuiop" << std::endl;
  trace.info() << "coord get " << tree2.get ( p1 ) << std::endl;
  trace.info() << "_-_-_-_-_-_-_-_-_-_-_-_-" << std::endl;
  trace.info() << "coord get " << tree2.get ( p3 ) << std::endl;
  trace.info() << "coord get " << tree2.get ( p1+=p3 ) << std::endl;
  trace.info() << "coord get " << tree2.get ( p1+=p3 ) << std::endl;
  trace.info() << "coord get " << tree2.get ( p1+=p3 ) << std::endl;
  trace.info() << "coord get " << tree2.get ( p1+=p3 ) << std::endl;

  // check that the iterator stuff compiles as it should
  typedef DGtal::experimental::ImageContainerByHashTree<Dom, int, DGtal::uint64_t>::Iterator HashTreeIterator;
  HashTreeIterator it = tree.begin();
  for ( it = tree.begin(); it != tree.end(); ++it )
    tree ( *it );



  bool res =
    (
      test_setVal ( tree, false ) &&
      test_get ( tree, false )
    );



  trace.emphase() << ( res ? "Passed." : "Error." ) << std::endl;
  trace.endBlock();
  return res ? 0 : 1;
}
