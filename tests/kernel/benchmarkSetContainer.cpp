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
 * @file benchmarkSetContainer.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2015/14/06
 *
 * Functions for benchmarking digitalset containers.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <benchmark/benchmark.h>
#include <unordered_set>

#include "DGtal/base/Common.h"
#include "DGtal/kernel/domains/CDomainArchetype.h"
#include "DGtal/kernel/sets/DigitalSetBySTLVector.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"
#include "DGtal/kernel/sets/DigitalSetByAssociativeContainer.h"
#include "DGtal/kernel/sets/DigitalSetFromMap.h"

#include "DGtal/kernel/PointHashFunctions.h"

#include "DGtal/helpers/StdDefs.h"
#include <map>
#include <string>

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;


typedef DGtal::DigitalSetBySTLSet< Z2i::Domain> FromSet;
typedef DGtal::DigitalSetBySTLVector< Z2i::Domain> FromVector;
typedef DGtal::DigitalSetByAssociativeContainer< Z2i::Domain, std::unordered_set<Z2i::Point> > FromUnordered;

typedef DGtal::DigitalSetBySTLSet< Z3i::Domain> FromSet3;
typedef DGtal::DigitalSetBySTLVector< Z3i::Domain> FromVector3;
typedef DGtal::DigitalSetByAssociativeContainer< Z3i::Domain, std::unordered_set<Z3i::Point> > FromUnordered3;

template<typename Q>
static void BM_Constructor(benchmark::State& state)
{
  while (state.KeepRunning())
    {
      state.PauseTiming();
      typename Q::Domain dom(typename Q::Point().diagonal(0),
                             typename Q::Point().diagonal(state.range(0)));
      state.ResumeTiming();
      Q image( dom );
    }
}
BENCHMARK_TEMPLATE(BM_Constructor, FromVector)->Range(1<<3 , 1 << 8);
BENCHMARK_TEMPLATE(BM_Constructor, FromSet)->Range(1<<3 , 1 << 8);
BENCHMARK_TEMPLATE(BM_Constructor, FromUnordered)->Range(1<<3 , 1 << 8);
BENCHMARK_TEMPLATE(BM_Constructor, FromVector3)->Range(1<<3 , 1 << 8);
BENCHMARK_TEMPLATE(BM_Constructor, FromSet3)->Range(1<<3 , 1 << 8);
BENCHMARK_TEMPLATE(BM_Constructor, FromUnordered3)->Range(1<<3 , 1 << 8);


template<typename Q>
static void BM_insert(benchmark::State& state)
{
  Q myset(typename Q::Domain( Q::Point::diagonal(0), Q::Point::diagonal(2048) ));
  while (state.KeepRunning())
    {
      state.PauseTiming();
      typename Q::Point p;
      for(unsigned int j=0; j < Q::Point::dimension; j++)
        p[j] = rand() % 2048;
      state.ResumeTiming();

      myset.insert( p );
   }
}
BENCHMARK_TEMPLATE(BM_insert, FromVector);
BENCHMARK_TEMPLATE(BM_insert, FromSet);
BENCHMARK_TEMPLATE(BM_insert, FromUnordered);
BENCHMARK_TEMPLATE(BM_insert, FromVector3);
BENCHMARK_TEMPLATE(BM_insert, FromSet3);
BENCHMARK_TEMPLATE(BM_insert, FromUnordered3);



template<typename Q>
static void BM_iterate(benchmark::State& state)
{
  Q myset(typename Q::Domain( Q::Point::diagonal(0), Q::Point::diagonal(2048) ));
  for(unsigned int i= 0; i < state.range(0); ++i)
    {
      typename Q::Point p;
      for(unsigned int j=0; j < Q::Point::dimension; j++)
        p[j] = rand() % 2048;
      myset.insert( p );
    }
  while (state.KeepRunning())
    {
      for(typename Q::ConstIterator it= myset.begin(), itend=myset.end(); it != itend;
          ++it)
        benchmark::DoNotOptimize(it);
    }
}
BENCHMARK_TEMPLATE(BM_iterate, FromVector)->Range(1<<3 , 1 << 10);;
BENCHMARK_TEMPLATE(BM_iterate, FromSet)->Range(1<<3 , 1 << 10);;
BENCHMARK_TEMPLATE(BM_iterate, FromUnordered)->Range(1<<3 , 1 << 10);;
BENCHMARK_TEMPLATE(BM_iterate, FromVector3)->Range(1<<3 , 1 << 10);;
BENCHMARK_TEMPLATE(BM_iterate, FromSet3)->Range(1<<3 , 1 << 10);;
BENCHMARK_TEMPLATE(BM_iterate, FromUnordered3)->Range(1<<3 , 1 << 10);;


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc,  char**argv )
{
  benchmark::Initialize(&argc, argv);

  benchmark::RunSpecifiedBenchmarks();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
