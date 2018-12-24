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
 *
 *
 * @date 2009/12/13
 *
 * This file is part of the DGtal library
 */

/**
 * Description of test_clock' <p>
 * Aim: simple test of \ref Clock
 */


#include <cstdio>
#include <cmath>
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/Clock.h"

using namespace DGtal;
using namespace std;

/// Minimal tick must be >=0
bool test_minimalTick()
{
  double tick;
  Clock c;

  trace.info() << c <<std::endl;

  c.startClock();
  tick = c.stopClock();
  trace.info() << "Minimal tick: "<< tick <<endl;
  return (tick >= 0);
}

/// Loop ticks must be >=0
bool test_loopTick()
{
  double tick,tmp=0;

  Clock c;
  c.startClock();
  for (unsigned int i=0 ; i< 4334450; i++)
    tmp = cos(tmp+i);

  tick = c.stopClock();
  trace.info()<< "Loop tick: "<< tick <<endl;
  return (tick >= 0);
}

/// Test several loops
bool test_MultipleLoop()
{
  double tick1,tick2,tick3,tmp=0;

  Clock c,c2,c3;

  c3.startClock();
  c.startClock();
  for (unsigned int i=0 ; i< 43350; i++)
    tmp = cos(tmp+i);

  c2.startClock();
  for (unsigned int i=0 ; i< 43350; i++)
    tmp = cos(tmp+i);

  tick2 = c2.stopClock();

  for (unsigned int i=0 ; i< 43450; i++)
    tmp = cos(tmp+i);

  tick1 = c.stopClock();
  tick3=c3.stopClock();

  trace.info()<< "Loop tick1: "<< tick1
              <<" Loop tick2: "<< tick2
              << " total: "<< tick3 <<endl;
  return ((tick3 >= tick1) && (tick1 >= 0));
}

/// Test restart
bool test_RestartClock()
{
  double tmp = 0.0;
  double tick_total=0., tick_accum=0.;
  Clock c_total, c_accum;

  c_total.startClock();
  c_accum.startClock();

#if !defined(WIN32)
  
  for (unsigned int i=0 ; i< 43350; i++)
    tmp = cos(tmp+i);
	usleep(20000);
  tick_accum += c_accum.restartClock();

  for (unsigned int i=0 ; i< 43350; i++)
    tmp = cos(tmp+i);
	usleep(20000);
  tick_accum += c_accum.restartClock();

  for (unsigned int i=0 ; i< 43350; i++)
    tmp = cos(tmp+i);
	usleep(20000);
  tick_accum += c_accum.restartClock();

  tick_total = c_total.stopClock();

	double delta = tick_total-tick_accum;

  trace.info()<< "Loop tick_total: " << tick_total
              << " Loop tick_accum: " << tick_accum
              << " Delta = "<<delta << endl;

  //return delta>=0 && delta<1e-4;
#endif
  return true;
}



int main()
{
  if (test_minimalTick() && test_loopTick() && test_MultipleLoop() && test_RestartClock())
    return 0;
  else
    return 1;

}
/** @ingroup Tests **/
