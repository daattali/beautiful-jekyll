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
 * @file testBenchmark.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/02/26
 *
 * Functions for testing class Benchmark.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <sstream>
#include <benchmark/benchmark.h>
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Benchmark.
///////////////////////////////////////////////////////////////////////////////


#if defined(__GNUC__)
# define BENCHMARK_NOINLINE __attribute__((noinline))
#else
# define BENCHMARK_NOINLINE
#endif


int BENCHMARK_NOINLINE Factorial(uint32_t n) {
  return (n == 1) ? 1 : n * Factorial(n - 1);
}

static void BM_StringCreation(benchmark::State& state)
{
  while (state.KeepRunning())
    std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);


// Define another benchmark
static void BM_StringCopy(benchmark::State& state)
{
  std::string x = "hello";
  while (state.KeepRunning())
    std::string copy(x);
}
BENCHMARK(BM_StringCopy);


static void BM_Factorial(benchmark::State& state) {
  int fac_42 = 0;
  while (state.KeepRunning())
    fac_42 = Factorial(8);
  // Prevent compiler optimizations
  std::stringstream ss;
  ss << fac_42;
  state.SetLabel(ss.str());
}
BENCHMARK(BM_Factorial);

double CalculatePi(int depth) {
  double pi = 0.0;
  for (int i = 0; i < depth; ++i) {
    double numerator = static_cast<double>(((i % 2) * 2) - 1);
    double denominator = static_cast<double>((2 * i) - 1);
    pi += numerator / denominator;
  }
  return (pi - 1.0) * 4;
}

static void BM_CalculatePiRange(benchmark::State& state) {
  double pi = 0.0;
  while (state.KeepRunning())
    pi = CalculatePi(state.range(0));
  std::stringstream ss;
  ss << pi;
  state.SetLabel(ss.str());
}
BENCHMARK_RANGE(BM_CalculatePiRange, 1, 256 * 256);

static void BM_CalculatePi(benchmark::State& state) {
  static const int depth = 256;
  double pi  = 0.0;
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize( pi = CalculatePi(depth) );
  }
}
BENCHMARK(BM_CalculatePi)->Threads(8);
BENCHMARK(BM_CalculatePi)->ThreadRange(1, 16);
BENCHMARK(BM_CalculatePi)->ThreadPerCpu();


static void BM_LongTest(benchmark::State& state) {
  double tracker = 0.0;
  while (state.KeepRunning())
    for (int i = 0; i < state.range(0); ++i)
      benchmark::DoNotOptimize(tracker += i);
}
BENCHMARK(BM_LongTest)->Range(1<<4,1<<6);



// Augment the main() program to invoke benchmarks if specified
// via the --benchmarks command line flag.  E.g.,
//       testBenchmark --benchmark_filter=all
//       testBenchmark --benchmark_filter=BM_StringCreation
//       testBenchmark --benchmark_filter=String
//       testBenchmark --benchmark_filter='Copy|Creation'
int main(int argc, char* argv[])
{
  benchmark::Initialize(&argc, argv);

  benchmark::RunSpecifiedBenchmarks();
  return 0;
}//                                                                           //
///////////////////////////////////////////////////////////////////////////////
