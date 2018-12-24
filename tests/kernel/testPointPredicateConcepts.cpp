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
 * @file testPointPredicateConcepts.cpp
 * @ingroup Tests
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/11/07
 *
 * Functions for testing class PointPredicateConcepts.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <functional>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/BasicPointPredicates.h"
#include "DGtal/images/ImageSelector.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::functors;
using namespace DGtal::concepts;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class PointPredicateConcepts.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
template <typename PointFunctor1,typename Predicate1, typename PointFunctor2, typename Predicate2>
bool
testPointPredicateConcepts()
{
    // PointFunctorPredicate
    typedef PointFunctorPredicate<PointFunctor1, Predicate1> PointPredicate1;
    BOOST_CONCEPT_ASSERT (( concepts::CPointPredicate< PointPredicate1 > ));
    typedef PointFunctorPredicate<PointFunctor2, Predicate2> PointPredicate2;
    BOOST_CONCEPT_ASSERT (( concepts::CPointPredicate< PointPredicate2 > ));

    // Binary PointPredicate
    typedef std::logical_and<bool> BinaryFunctor;
    BOOST_CONCEPT_ASSERT (( concepts::CPointPredicate< BinaryPointPredicate<PointPredicate1, PointPredicate2, BinaryFunctor> > ));

    // NotPointPredicate
    BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate< NotPointPredicate<PointPredicate1> > ));
    BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate< NotPointPredicate<PointPredicate2> > ));

    typedef typename PointFunctor1::Point Point;
    // EqualPointPredicate
    BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate< EqualPointPredicate<Point> > ));
    // IsWithinPointPredicate
    BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate< IsWithinPointPredicate<Point> > ));
    // IsUpperPointPredicate
    BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate< IsUpperPointPredicate<Point> > ));
    // IsLowerPointPredicate
    BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate< IsLowerPointPredicate<Point> > ));
    // TruePointPredicate
    BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate< TruePointPredicate<Point> > ));
    // FalsePointPredicate
    BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate< FalsePointPredicate<Point> > ));

    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing PointPredicate Concepts" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = true;
  typedef ImageSelector<Z3i::Domain, int>::Type IntImage;
  using IntPredicate = std::function<bool(int)>;
  typedef ImageSelector<Z3i::Domain, float>::Type FloatImage;
  using FloatPredicate = std::function<bool(float)>;
  res &= testPointPredicateConcepts<IntImage, IntPredicate, FloatImage, FloatPredicate>();

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
