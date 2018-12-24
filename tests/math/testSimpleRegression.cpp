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
 * @file testSimpleRegression.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/26
 *
 * Functions for testing class SimpleRegression.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/math/SimpleLinearRegression.h"
#include "DGtal/math/OrderedLinearRegression.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class SimpleRegression.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testSimpleRegression()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing SimpleLinearRegression ..." );

  SimpleLinearRegression SLR;

  SLR.addSample(0,0);
  SLR.addSample(1,1);
  SLR.addSample(34,34);
  SLR.addSample(3,3);

  nbok += SLR.computeRegression() ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "Regression == true" << std::endl;

  trace.info() << "Got slope= "<< SLR.slope()<<std::endl;
  trace.info() << "Got Intercept= "<< SLR.intercept()<<std::endl;


  nbok += ( std::abs(SLR.slope() - 1) < 0.01)  ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "slope == 1" << std::endl;
  nbok += ( std::abs(SLR.intercept() - 0.0) < 0.01)  ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "intercept == 0" << std::endl;
  trace.endBlock();

  return nbok == nb;
}


/**
 * Example of a test. To be completed.
 *
 */
bool testSimpleRegression2()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing SimpleLinearRegression2..." );

  SimpleLinearRegression SLR;

  std::vector<double> x;
  x.push_back(0);
  x.push_back(2);
  x.push_back(34);
  x.push_back(3);
  std::vector<double> y;
  y.push_back(0);
  y.push_back(2);
  y.push_back(33);
  y.push_back(2.7);

  SLR.addSamples( x.begin(), x.end(), y.begin());

  nbok += SLR.computeRegression() ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "Regression == true" << std::endl;

  trace.info() << "Got slope= "<< SLR.slope()<<std::endl;
  trace.info() << "Got Intercept= "<< SLR.intercept()<<std::endl;


  nbok += ( std::abs(SLR.slope() - 1) < 0.1)  ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "|slope| =~= 1" << std::endl;
  nbok += ( std::abs(SLR.intercept() ) < 0.1)  ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "|intercept| < (10^-1)" << std::endl;
  trace.endBlock();

  return nbok == nb;
}

/**
 * Example of a test. To be completed.
 *
 */
bool testSimpleRegression3()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing SimpleLinearRegression3..." );

  SimpleLinearRegression SLR;

  double x[] = {5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10, 10.5, 11, 11.5, 12, 12.5, 13, 13.5, 14, 14.5, 15, 15.5, 16, 16.5, 17, 17.5, 18, 18.5, 19, 19.5, 20};

  double y[] = {0.00366568,0.0376311,0.0173014,0.0205614,0.00139069,0.0108356,0.000985302,0.00360493,0.00808965,0.014353,0.00497899,0.0115723,0.00651013,0.00758458,0.00392271,0.00752993,0.00597875,0.00841424,0.00704232,0.00848176,0.00676336,0.00564121,0.00584509,0.00702953,0.00591087,0.00745775,0.00618557,0.00727818,0.00534952,0.0053612,0.00426009};

  std::vector<double> xx(31),yy(31);
  for(unsigned int i=0; i < 31; ++i)
    {
      xx[i] = std::log(x[i]);
      yy[i] = std::log(y[i]);
    }

  SLR.addSamples( xx.begin(), xx.end(), yy.begin());

  nbok += SLR.computeRegression() ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "Regression == true" << std::endl;

  trace.info() << "Got slope= "<< SLR.slope()<<std::endl;
  trace.info() << "Got Intercept= "<< SLR.intercept()<<std::endl;


  nbok += ( std::abs(SLR.slope() + 0.25) < 0.1)  ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "|slope| =~= 1" << std::endl;
  trace.endBlock();

  return nbok == nb;
}

/**
 *
 */
bool testSimpleRegressionOrdered()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing OrderedLinearRegression..." );

  double x[] = {1, 2, 2.5, 3, 4 ,5 , 6};
  double y[] = {1, 2, 2.5, 2.9, 4.1, 15, 25.9};

  OrderedLinearRegression OLR;
  OLR.addSamples( &x[0] , &x[7], &y[0]);
  
  SimpleLinearRegression SLR;
  SLR.addSamples( &x[0] , &x[7], &y[0]);

  SimpleLinearRegression forward; 
  SimpleLinearRegression backward;
  
  OLR.forwardSLR(forward, 4);
  OLR.backwardSLR(backward, 3);
    
  SLR.computeRegression();

  trace.info() << "SLR slope = " << SLR.slope() <<std::endl;
  nbok += ( SLR.slope() < 5 ) ? 1 : 0;
  nb++;
  trace.info() << "Forward slope = " << forward.slope() << " " << forward.size() << std::endl;
  nbok += (( forward.size() == 5 ) && ( forward.slope() < 1.05 ))  ? 1 : 0;
  nb++;
  trace.info() << "Backward slope = " << backward.slope() << " " << backward.size() << std::endl;
  nbok += (( backward.slope() < 11 ) && ( backward.slope() > 10 ))  ? 1 : 0;
  nb++;
  
  trace.endBlock();

  return nbok == nb;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class SimpleRegression" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testSimpleRegression()
    && testSimpleRegression2()
    && testSimpleRegression3()
    && testSimpleRegressionOrdered(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
