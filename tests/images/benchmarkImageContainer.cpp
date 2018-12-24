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
#include <benchmark/benchmark.h>
#include "DGtal/base/Common.h"

#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/ImageSelector.h"

#include "DGtal/helpers/StdDefs.h"
#include <map>
#include <string>

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
/////// Micro Bench

typedef DGtal::ImageContainerBySTLVector< Z2i::Domain, DGtal::int32_t> ImageVector2;
typedef DGtal::ImageContainerBySTLMap< Z2i::Domain, DGtal::int32_t> ImageMap2;
typedef DGtal::experimental::ImageContainerByHashTree< Z2i::Domain, DGtal::int32_t> ImageHash2;

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
BENCHMARK_TEMPLATE(BM_Constructor, ImageVector2)->Range(1<<3 , 1 << 10);
BENCHMARK_TEMPLATE(BM_Constructor, ImageMap2)->Range(1<<3 , 1 << 16);
BENCHMARK_TEMPLATE(BM_Constructor, ImageHash2)->Range(1<<3 , 1 << 16);

template<typename Point>
std::set<Point> ConstructRandomSet(unsigned int size, unsigned int maxWidth) {
  std::set<Point> s;
  Point p;
  for (unsigned int i = 0; i < size; ++i)
    {
      for(unsigned int j=0; j < Point::dimension; j++)
        p[j] = rand() % maxWidth;
      s.insert( p );
    }
  return s;
}


template<typename Q>
static void BM_SetValue(benchmark::State& state)
{
  std::set<typename Q::Point> data = ConstructRandomSet<typename Q::Point>(state.range(0),state.range(0));

  int64_t cpt=0;
  while (state.KeepRunning())
    {
      state.PauseTiming();
      typename Q::Domain dom(typename Q::Point().diagonal(0),
                             typename Q::Point().diagonal(state.range(0)));
      Q image( dom );
      for(typename std::set<typename Q::Point>::const_iterator it = data.begin(), itend=data.end();
          it != itend; ++it)
        {
          state.ResumeTiming();
          image.setValue( *it , 42);
          state.PauseTiming();
          cpt++;
        }
    }
  // const int64_t items_processed =
    // static_cast<int64_t>(state.iterations())*state.range(0);
  state.SetItemsProcessed(cpt);
}
BENCHMARK_TEMPLATE(BM_SetValue, ImageVector2)->Range(1<<3 , 1 << 10);
BENCHMARK_TEMPLATE(BM_SetValue, ImageMap2)->Range(1<<3 , 1 << 16);
BENCHMARK_TEMPLATE(BM_SetValue, ImageHash2)->Range(1<<3 , 1 << 10);

template<typename Q>
static void BM_RangeScan(benchmark::State& state)
{
  std::set<typename Q::Point> data = ConstructRandomSet<typename Q::Point>(state.range(0),state.range(0));
  int sum=0;
  while (state.KeepRunning())
    {
      state.PauseTiming();
      typename Q::Domain dom(typename Q::Point().diagonal(0),
                             typename Q::Point().diagonal(state.range(0)));
      Q image( dom );
      for(typename std::set<typename Q::Point>::const_iterator it = data.begin(), itend=data.end();
          it != itend; ++it)
        image.setValue( *it , 42);
      state.ResumeTiming();
      for(typename Q::Range::ConstIterator it = image.range().begin(), itend=image.range().end();
          it != itend; ++it)
        benchmark::DoNotOptimize(sum += *it);   //to prevent compiler optimization
    }
  std::stringstream ss;
  ss << sum;
  state.SetLabel(ss.str());
}
BENCHMARK_TEMPLATE(BM_RangeScan, ImageVector2)->Range(1<<3 , 1 << 10);
BENCHMARK_TEMPLATE(BM_RangeScan, ImageMap2)->Range(1<<3 , 1 << 10);

template<typename Q>
static void BM_DomainScan(benchmark::State& state)
{
  std::set<typename Q::Point> data = ConstructRandomSet<typename Q::Point>(state.range(0),state.range(0));
  int sum=0;
  while (state.KeepRunning())
    {
      state.PauseTiming();
      typename Q::Domain dom(typename Q::Point().diagonal(0),
                             typename Q::Point().diagonal(state.range(0)));
      Q image( dom );
      for(typename std::set<typename Q::Point>::const_iterator it = data.begin(), itend=data.end();
          it != itend; ++it)
        image.setValue( *it , 42);
      state.ResumeTiming();
      for(typename Q::Domain::ConstIterator it = image.domain().begin(), itend=image.domain().end();
          it != itend; ++it)
        benchmark::DoNotOptimize( sum ++ );
    }
  std::stringstream ss;
  ss << sum;
  state.SetLabel(ss.str());
}
BENCHMARK_TEMPLATE(BM_DomainScan, ImageVector2)->Range(1<<3 , 1 << 10);
BENCHMARK_TEMPLATE(BM_DomainScan, ImageMap2)->Range(1<<3 , 1 << 10);




///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc,  char **argv )
{
  benchmark::Initialize(&argc, argv);

  benchmark::RunSpecifiedBenchmarks();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
