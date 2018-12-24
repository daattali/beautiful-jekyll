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
 * @author Isabelle Sivignon (\c isabelle.sivignon@gipsa-lab.grenoble-inp.fr )
 * gipsa-lab Grenoble Images Parole Signal Automatique (CNRS, UMR 5216), CNRS, France
 *
 * @date 2013/09/16
 *
 * Functions for testing class DSLSubsegment.
 *
  */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include "DGtal/geometry/curves/DSLSubsegment.h"
#include "DGtal/arithmetic/StandardDSLQ0.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/arithmetic/IntegerComputer.h"
#include "DGtal/arithmetic/SternBrocot.h"
#include "DGtal/arithmetic/LighterSternBrocot.h"
#include "DGtal/arithmetic/LightSternBrocot.h"
#include "DGtal/arithmetic/Pattern.h"
#include "DGtal/geometry/curves/ArithDSSIterator.h"
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
#include "DGtal/base/Clock.h"

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class DSLSubsegment.
///////////////////////////////////////////////////////////////////////////////

//#define CHECK_RES


template <typename Integer,typename Fraction>
bool testDSLSubsegment(Integer modb)
{
  //typedef long double Number;
  typedef DGtal::DSLSubsegment<Integer,Integer> DSLSubseg;
  //typedef DGtal::DSLSubsegment<Integer,Number> DSLSubsegD;


  typedef ArithDSSIterator<Integer,8> DSSIterator;
  typedef NaiveDSS8<Integer> ArithDSS;

  typedef typename DSLSubseg::Point Point;

  typedef StandardDSLQ0<Fraction> DSL;
  typedef typename DSL::Point PointDSL;

  DGtal::IntegerComputer<Integer> ic;


  // Draw random value for b in [0,modb]
  Integer b( rand() % modb +1);
  
  // Draw random value for a in [0,b]
  Integer a( rand() % b +1);
  // Draw a new a while a and b are not coprime (do not divide by
  // the gcd so that b remains in the required interval)
  while(ic.gcd(a,b) !=1)
    a = rand() %b +1;

  // Draw random value for mu in [0,2modb]
  Integer mu = rand() % (2*modb);
  
  Integer l = 200; // max length of the DSSs

  // Draw random values for the subsegment first extremity abscissa
  Integer xf = rand() % modb;
  
  trace.beginBlock("Draw random values for a,b,mu and abscissa of the first point");
  trace.info() << "a b mu xf:" << a << " " << b << " " << mu << " " << xf << std::endl; 
  trace.endBlock();
  trace.info() << std::endl;
  
  int error1 = 0;
  // Consider the subsegment S of the line (a,b,mu), with xf <= x < xf+l
  // Test all the subsegments of S
  
  trace.beginBlock("Compare DSLSubsegment/Farey fan with ArithmeticalDSS algorithm");
  for(unsigned int i = 0; i<l; i++)
    for(unsigned int j = i+1; j<l; j++)
      {
	Integer x1 = xf+i;
	Integer x2 = xf+j;

	Integer y1 = ic.floorDiv(a*x1+mu,b);
	Integer y2 = ic.floorDiv(a*x2+mu,b);
	Point A = Point(x1,y1);
	Point B = Point(x2,y2);
	
	// DSLSubsegment with Farey Fan (O(log(n))
	DSLSubseg DSLsub(a,b,mu,A,B,"farey");
	
	
	// ArithmeticalDSS recognition algorithm (O(n))
	DSSIterator  it(a,b,-mu,A);
	ArithDSS myDSS(*it, *it);
	++it; 
	while ( (*it)[0] <=x2 && myDSS.extendFront(*it))
	  { ++it; }
	
	// If results are different, count an error
	if(DSLsub.getA() != myDSS.a() || DSLsub.getB() != myDSS.b() || DSLsub.getMu() != - myDSS.mu())
	  error1 ++;
      }
  trace.info() << error1 << " errors." << std::endl;
  trace.endBlock();
  trace.info() << std::endl;

  int error2 = 0;
  trace.beginBlock("Compare DSLSubsegment/localCH with DSLSubsegment/FareyFan");
  for(unsigned int i = 0; i<l; i++)
    for(unsigned int j = i+1; j<l; j++)
      {
	Integer x1 = xf+i;
	Integer x2 = xf+j;

	Integer y1 = ic.floorDiv(a*x1+mu,b);
	Integer y2 = ic.floorDiv(a*x2+mu,b);
	Point A = Point(x1,y1);
	Point B = Point(x2,y2);
	
	// DSLSubsegment with local CH (O(log(n))
	DSLSubseg DSLsubCH(a,b,mu,A,B,"localCH");
	
	// DSLSubsegment with Farey Fan (O(log(n))
	DSLSubseg DSLsubF(a,b,mu,A,B,"farey");
	
	
	// If results are different, count an error
	if(DSLsubCH.getA() != DSLsubF.getA() || DSLsubCH.getB() != DSLsubF.getB() || DSLsubCH.getMu() != DSLsubF.getMu())	
	  error2 ++;
	
      }
  trace.info() << error2 << " errors." << std::endl;
  trace.endBlock();
  trace.info() << std::endl;
  
  int error3 = 0;
  trace.beginBlock("Compare DSLSubsegment/FareyFan with ReversedSmartDSS for 4-connected DSL");
  for(unsigned int i = 0; i<l; i++)
    for(unsigned int j = i+1; j<l; j++)
      {
	Integer x1 = xf+i;
	Integer x2 = xf+j;
	
	DSL D( a, b, mu );
	PointDSL AA = D.lowestY( x1 );
	PointDSL BB = D.lowestY( x2 );	
	
	// ReversedSmartDSS algorithm
	DSL S = D.reversedSmartDSS(AA,BB);
	
	// DSLSubsegment algorithm for 4-connected DSL.
	// Application of an horizontal shear transform
	Point A2 = AA;
	A2[0] += A2[1];
	Point B2 = BB;
	B2[0] += B2[1];
		
	// DSLSubsegment algorithm works with the definition 0  <= ab -by + mu <
	// b whereas reversedSmartDSS uses  mu <= ab-by < mu + b 
	// => -mu is introduced in order to compare the results  
	
	DSLSubseg D2(a,a+b,-mu,A2,B2,"farey");
	// The result is (aa,getB()-aa, nu)
	// Compare results of DSLsubseg4 and reversedSmartDSS
	if(!(D2.getA()==S.a() && (D2.getB()-D2.getA())==S.b() && D2.getMu()==-S.mu()))
	  error3 ++;
	
      }
  trace.info() << error3 << " errors." << std::endl;
  trace.endBlock();
  trace.info() << std::endl;
  
  return (error1==0 && error2==0 && error3==0);

}



///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main()
{
  typedef DGtal::int64_t Integer;
  typedef LightSternBrocot<Integer,DGtal::int32_t> LSB;
  typedef LSB::Fraction Fraction;

  trace.beginBlock ( "Testing class DSLSubsegment" );
  trace.info() << std::endl;

  Integer i = 1000;
  srand(time(NULL));
  
  bool res = testDSLSubsegment<Integer,Fraction>(i);
  
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  
  return res ? 0 : 1;
  
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
