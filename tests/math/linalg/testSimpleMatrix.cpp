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
 * @file testSimpleMatrix.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/07/10
 *
 * Functions for testing class SimpleMatrix.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/math/linalg/SimpleMatrix.h"
#include "DGtal/math/linalg/CStaticMatrix.h"
#include "DGtal/math/linalg/CDenseMatrix.h"
#include "DGtal/math/linalg/CStaticVector.h"
#include "DGtal/math/linalg/CDenseVector.h"
#include "DGtal/math/linalg/CLinearAlgebra.h"
#include "DGtal/helpers/StdDefs.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class SimpleMatrix.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testSimpleMatrix()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing create ..." );

  typedef SimpleMatrix<double,3,4> M34d;

  M34d m34d;
  trace.info() << m34d<<std::endl;

  m34d.setComponent(1,2, 0.5);
  trace.info() << m34d<<std::endl;

  nbok += (m34d(1,2) == 0.5) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true == true" << std::endl;

  M34d matrix;
  bool res=true;

  matrix.constant(12.3);
  trace.info() << matrix;
  for(DGtal::Dimension i = 0; i< 3; ++i)
    for(DGtal::Dimension j = 0; j< 4; ++j)
        res = res && (matrix(i,j) == 12.3);
  nbok += res ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "all equals to 12.3" << std::endl;


  trace.endBlock();

  return nbok == nb;
}

bool testArithm()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;


  typedef SimpleMatrix<double,3,4> M34d;
  typedef SimpleMatrix<double,4,3> M43d;
  typedef SimpleMatrix<double,3,3> M33d;

  M34d m34d, two,four;
  M34d m34dbis, resadd, ressub;

  two.constant(2);
  four.constant(4);

  for(DGtal::Dimension i = 0; i< 3; ++i)
    for(DGtal::Dimension j = 0; j< 4; ++j)
      {
        m34d.setComponent(i,j,i*j);
        m34dbis.setComponent(i,j,i+j);
        resadd.setComponent(i,j,i*j+i+j);
        ressub.setComponent(i,j,i*j-(double)i-(double)j);
      }


  trace.info() << m34d <<std::endl;
  trace.info() << m34dbis<<std::endl;

  trace.beginBlock ( "Testing add ..." );
  nbok += ((m34d + m34dbis) == resadd) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "ok" << std::endl;
  nbok += ((m34dbis + m34d) == resadd) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "ok commutative" << std::endl;

  M34d other;
  other += m34d;
  nbok += (other == m34d) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "ok +=" << std::endl;

  trace.endBlock();

  trace.beginBlock ( "Testing substraction ..." );
  nbok += ((m34d - m34dbis) == ressub) ? 1 : 0;
  nb++;
  trace.info()<<ressub<<std::endl;
  trace.info()<<m34d - m34dbis<<std::endl;

  trace.info() << "(" << nbok << "/" << nb << ") "
         << "ok simple" << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing scalar product/divide ..." );
  nbok += ( (two*2.0) == four) ? 1 : 0;
  nb++;
  trace.info()<<ressub<<std::endl;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << " [2]*2 == [4]" << std::endl;

  nbok += ( two == four/2.0) ? 1 : 0;
  nb++;
  trace.info()<<ressub<<std::endl;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << " [2]= [4]/2" << std::endl;
  trace.endBlock();


  trace.beginBlock ( "Testing transpose ..." );
  M43d transp = m34d.transpose();
  nbok += (transp.transpose() == m34d) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
           << "ok idem potent" << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing product ..." );

  M43d one;
  M33d eight33;

  one.constant(1);
  eight33.constant(8);
  trace.info() << two * one<<std::endl;
  nbok += (two * one  == eight33) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
           << " [2]*[1] = [8]" << std::endl;
  trace.endBlock();



  return nbok == nb;

}

bool testColRow()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  DGtal::SimpleMatrix<double,3,4> mat;
  for(DGtal::Dimension i = 0; i< 3; ++i)
    for(DGtal::Dimension j = 0; j< 4; ++j)
      mat.setComponent(i,j,i+j);

  trace.beginBlock("Get Row");
  trace.info() << mat <<std::endl;
  DGtal::SimpleMatrix<double,3,4>::RowVector row;
  row = mat.row(1);
  trace.info() << row << std::endl;
  nbok += (row[1] == 2 ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
           << " row value" << std::endl;
  trace.endBlock();

  trace.beginBlock("Get Col");
  DGtal::SimpleMatrix<double,3,4>::ColumnVector col;
  col = mat.column(1);
  trace.info() << row << std::endl;
  nbok += (col[1] == 2 ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
           << " col value" << std::endl;
  trace.endBlock();



  trace.beginBlock("Prod Matrix x Row^t");
  //Row vector is a dim 4 vector
  DGtal::SimpleMatrix<double,3,4>::RowVector r(1,2,3,4);
  DGtal::SimpleMatrix<double,3,4>::ColumnVector c;
  c = mat*r;
  DGtal::SimpleMatrix<double,3,4>::ColumnVector expected(20,30,40);

  trace.info() << c << std::endl;
  nbok += (c == expected) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
           << " mat*row^t" << std::endl;
  trace.endBlock();

  return nbok == nb;
}

bool testDetCofactor()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  typedef DGtal::SimpleMatrix<double,2,2> MAT2;
  MAT2 mat2;
  mat2.setComponent(0,0,1);
  mat2.setComponent(1,1,2);

  trace.beginBlock("det2x2 tests...");
  trace.info() << mat2<<std::endl;
  trace.info() << mat2.determinant() << std::endl;
  nbok += (mat2.determinant() == 2) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
           << " 2" << std::endl;
  trace.endBlock();

  typedef DGtal::SimpleMatrix<double,3,3> MAT;
  MAT mat;
  mat.setComponent(0,0,1);
  mat.setComponent(1,1,2);
  mat.setComponent(2,2,4);

  trace.beginBlock("det3x3 tests...");
  trace.info() << mat<<std::endl;
  nbok += (mat.determinant() == 8) ? 1 : 0;
   nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
           << " 8" << std::endl;
  trace.endBlock();


  typedef DGtal::SimpleMatrix<double,4,4> MAT44;
  MAT44 mat44;
  mat44.setComponent(0,0,1);
  mat44.setComponent(1,1,2);
  mat44.setComponent(2,2,4);
  mat44.setComponent(3,3,4);

  trace.beginBlock("det4x4 tests...");
  trace.info() << mat44 <<std::endl;
  trace.info() << mat44.determinant() << std::endl;
  nbok += (mat44.determinant() == 32) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
           << " 32" << std::endl;
  trace.endBlock();


  return nbok == nb;
}

bool testM1Matrix()
{
  trace.beginBlock("Mx1 matrix test");
  SimpleMatrix<double, 3,1> mat;
  trace.info() << mat<<std::endl;
  trace.endBlock();
  return true;
}

bool testInverse()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock("Inverse tests 2X2...");

  typedef DGtal::SimpleMatrix<double,2,2> MAT2;
  MAT2 mat2;
  mat2.setComponent(0,0,1);
  mat2.setComponent(1,1,2);

  MAT2 Id2;
  Id2.identity();

  trace.info() << mat2<<std::endl;
  trace.info() << mat2.inverse() << std::endl;
  nbok += (( mat2 * mat2.inverse() )== Id2 ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
           << " M*M^-1=Id" << std::endl;

  trace.endBlock();

  trace.beginBlock("Inverse tests 6x6 random...");

  typedef DGtal::SimpleMatrix<double,6,6> MAT6;
  MAT6 mat;

  for(unsigned int i=0; i< 6; i++)
    for(unsigned int j=0; j< 6; j++)
      mat.setComponent(i,j, rand() % 10);

  MAT6 Id6;
  Id6.identity();

  trace.info() << "M= "<<mat<<std::endl;
  trace.info() << "M^-1=" <<mat.inverse() << std::endl;
  trace.info() << "det(M)= "<<mat.determinant() <<std::endl;
  trace.info() << "M*M^-1= "<<mat.inverse()*mat << std::endl;



  trace.endBlock();


  return nbok == nb;
}

bool testConstructor()
{
  unsigned int nbok = 0;
  unsigned int nb   = 0;

  trace.beginBlock( "Initilizer-list constructor test" );
  SimpleMatrix<double, 3, 3> mat = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  trace.info() << mat << std::endl;

  trace.info() << "Testing values: ";
  trace.info() << mat( 0, 0 );
  nbok += ( mat( 0, 0 ) == 1 ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") ";

  trace.info() << mat( 0, 1 );
  nbok += ( mat( 0, 1 ) == 2 ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") ";

  trace.info() << mat( 2, 2 );
  nbok += ( mat( 2, 2 ) == 9 ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") ";

  trace.info() << std::endl;
  trace.endBlock();
  return nbok == nb;
}

bool testConcepts()
{
  typedef DGtal::SimpleMatrix<double,3,3> Matrix;
  typedef Matrix::ColumnVector Vector;

  BOOST_CONCEPT_ASSERT(( concepts::CStaticVector<Vector> ));
  BOOST_CONCEPT_ASSERT(( concepts::CDenseVector<Vector> ));
  BOOST_CONCEPT_ASSERT(( concepts::CStaticMatrix<Matrix> ));
  BOOST_CONCEPT_ASSERT(( concepts::CDenseMatrix<Matrix> ));
  BOOST_CONCEPT_ASSERT(( concepts::CLinearAlgebra<Vector, Matrix> ));
  BOOST_CONCEPT_ASSERT(( concepts::CStaticVector<DGtal::Z3i::Space::Vector> ));
  BOOST_CONCEPT_ASSERT(( concepts::CDenseVector<DGtal::Z3i::Space::Vector> ));

  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class SimpleMatrix" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testSimpleMatrix() && testArithm() && testColRow() &&
             testDetCofactor() && testM1Matrix() && testInverse() &&
             testConcepts() && testConstructor();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
