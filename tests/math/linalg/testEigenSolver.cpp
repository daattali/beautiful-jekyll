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
 * @file testEigenSolver.cpp
 * @ingroup Tests
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/26
 *
 * Functions for testing class EigenSolver.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <list>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/math/linalg/CLinearAlgebraSolver.h"
#include "DGtal/math/linalg/CSparseMatrix.h"
#include "DGtal/math/linalg/CDynamicMatrix.h"
#include "DGtal/math/linalg/CDenseVector.h"
#include "DGtal/math/linalg/CDynamicVector.h"
#include "DGtal/math/linalg/EigenSupport.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing Eigen solvers classes concepts
///////////////////////////////////////////////////////////////////////////////
/**
 * Test eigen linear algebra concepts
 *
 */
bool testEigenSolverConcepts()
{
    typedef EigenLinearAlgebraBackend LAB;
    typedef LAB::DenseVector Vector;
    typedef LAB::SparseMatrix Matrix;
    typedef LAB::Triplet Triplet;
    typedef std::vector<Triplet> TripletsVector;
    typedef std::list<Triplet> TripletsList;
    BOOST_CONCEPT_ASSERT(( concepts::CDynamicVector<Vector> ));
    BOOST_CONCEPT_ASSERT(( concepts::CDenseVector<Vector> ));
    BOOST_CONCEPT_ASSERT(( concepts::CDynamicMatrix<Matrix> ));
    BOOST_CONCEPT_ASSERT(( concepts::CSparseMatrix<Matrix, TripletsVector::const_iterator> ));
    BOOST_CONCEPT_ASSERT(( concepts::CSparseMatrix<Matrix, TripletsList::const_iterator> ));
    BOOST_CONCEPT_ASSERT(( concepts::CLinearAlgebraSolver<LAB::SolverSimplicialLLT, Vector, Matrix> ));
    BOOST_CONCEPT_ASSERT(( concepts::CLinearAlgebraSolver<LAB::SolverSimplicialLDLT, Vector, Matrix> ));
    BOOST_CONCEPT_ASSERT(( concepts::CLinearAlgebraSolver<LAB::SolverConjugateGradient, Vector, Matrix> ));
    BOOST_CONCEPT_ASSERT(( concepts::CLinearAlgebraSolver<LAB::SolverBiCGSTAB, Vector, Matrix> ));
    BOOST_CONCEPT_ASSERT(( concepts::CLinearAlgebraSolver<LAB::SolverSparseLU, Vector, Matrix> ));
    BOOST_CONCEPT_ASSERT(( concepts::CLinearAlgebraSolver<LAB::SolverSparseQR, Vector, Matrix> ));

    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class EigenSolver" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testEigenSolverConcepts();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
