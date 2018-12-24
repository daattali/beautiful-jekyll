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
 * @file testTrace.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 *
 *
 * @date 2009/12/13
 *
 * This file is part of the DGtal library
 */

/**
  * Description of testTrace' <p>
  * Aim: simple test of \ref Trace
  */


#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>

#include "DGtal/base/Config.h"
#include "DGtal/base/Common.h"


using namespace DGtal;
using namespace std;


void testSimple()
{
    trace.info()<< "This is an Info trace"<<endl;
    trace.warning()<< "This is an warning trace"<<endl;
    trace.error()<< "This is an Error trace"<<endl;
    trace.emphase()<< "This is an Emphased trace"<<endl;
    cerr<<endl;
}

void testIndent()
{
    long tmp=0;

    trace.info()<< "This is an Info trace, level 0"<<endl;
    trace.beginBlock("FirstMethod");
    trace.info()<< "This is an Info trace, level 1"<<endl;
    trace.info()<< "This is an Info trace, level 1"<<endl;
    trace.beginBlock("SecondMethod");
    trace.warning()<< "This is an Warning trace, level 2"<<endl;
    trace.warning()<< "This is an Warning trace, level 2"<<endl;
    trace.info()<< "This is an Info trace, level 2"<<endl;
    trace.error()<< "This is an Error trace, level 2 (followed by a loop)"<<endl;

    for (unsigned int i=0 ; i< 450; i++)
        tmp = (long)cos((double)tmp+i);

    trace.endBlock();
    trace.info()<< "This is an Info trace, level 1 (followed by another loop)"<<endl;

    for (unsigned int i=0 ; i< 430; i++)
        tmp = (long)cos((double)tmp+i);

    trace.endBlock();
    trace.info()<< "This is an Info trace, level 0"<<endl<<endl;
}

/**
  * We test the Trace class on file stream.
  *
  * a file "example.txt" must have been created with the traces.
  */
void testFileStream()
{
    trace.beginBlock("testFileStream");
    trace.info() << "Checking the filestream output.. Please check the 'example.txt' file"<<endl;

    ofstream myfile;
    myfile.open ("example.txt");

    TraceWriterFile traceWriterFile(myfile);
    Trace t2(traceWriterFile);

    t2.info()<< "This is an Info trace"<<endl;
    t2.warning()<< "This is an warning trace"<<endl;

    t2.error()<< "This is an Error trace"<<endl;
    t2.emphase()<< "This is an Emphased trace"<<endl;

    t2.beginBlock("FirstMethod");
    t2.info()<< "This is an Info trace, level 1"<<endl;
    t2.info()<< "This is an Info trace, level 1"<<endl;
    t2.endBlock();

    myfile.close();

    trace.endBlock();
}

void testTimings()
{
  size_t duration;
 
  trace.beginBlock("Level0");
  double tmp=1.0;
  
  trace.beginBlock("Level1");
  trace.info()<<"..."<<std::endl;
  for (unsigned int i=0 ; i< 4350; i++)
    tmp = (long)cos((double)tmp+i);
  duration = trace.endBlock();
  
  trace.beginBlock("Level1B");
  trace.info()<<"..."<<std::endl;
  for (unsigned int i=0 ; i< 4350; i++)
    tmp = (long)cos((double)tmp+i);
  
  trace.beginBlock("Level2");
  trace.info()<<"..."<<std::endl;
  for (unsigned int i=0 ; i< 4350; i++)
    tmp = (long)cos((double)tmp+i);
  duration += trace.endBlock();
  
  trace.beginBlock("Level2B");
  trace.info()<<"..."<<std::endl;
  for (unsigned int i=0 ; i< 4350; i++)
    tmp = (long)cos((double)tmp+i);
  duration += trace.endBlock();
  
  trace.beginBlock("Level2C");
  trace.info()<<"..."<<std::endl;
  for (unsigned int i=0 ; i< 4450; i++)
    tmp = (long)cos((double)tmp+i);
  duration += trace.endBlock();
  
  duration += trace.endBlock();
  
  trace.beginBlock("Level1C");
  trace.info()<<"..."<<std::endl;
  for (unsigned int i=0 ; i< 430; i++)
    tmp = (long)cos((double)tmp+i);
  duration += trace.endBlock();

  duration += trace.endBlock();
  trace.info()<<"Duration="<<duration<<std::endl;

}



int main()
{
    testSimple();
    testIndent();
    testFileStream();
    testTimings();
    return 0;
}

