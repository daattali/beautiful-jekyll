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
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2013/11/30
 *
 * Functions for testing class NumbersReader.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/readers/TableReader.h"
#include "DGtal/helpers/StdDefs.h"

#include "ConfigTest.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;


///////////////////////////////////////////////////////////////////////////////
// Functions for testing class TableReader.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testNumberReader()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing reading Integers ..." );  
  std::string filename = testPath + "samples/pointList1.pl";

  vector<unsigned int> vectIntegers = TableReader<unsigned int>::getColumnElementsFromFile(filename, 1);
  for(unsigned int k=0;k < vectIntegers.size(); k++){
    trace.info() << " integer: "<< vectIntegers.at(k)<< endl;
  }
  nbok += (vectIntegers.at(0)==2 && vectIntegers.at(1)==44 && vectIntegers.at(2)==23 
           && vectIntegers.at(3)==1) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "<< std::endl;
  trace.endBlock();

  trace.beginBlock( "Testing reading all numbers from each lines  ..." );

  std::vector<vector<unsigned int>> vectLineIntegers =
  TableReader<unsigned int>::getLinesElementsFromFile( filename );
  for ( unsigned int k = 0; k < vectLineIntegers.size(); k++ )
  {
    for ( unsigned int l = 0; l < vectLineIntegers.at( k ).size(); l++ )
    {
      trace.info() << " integer: " << vectLineIntegers.at( k ).at( l ) << " ";
    }
    trace.info() << endl;
  }

  nbok += ( vectLineIntegers.at( 0 ).at( 0 ) == 1 &&
            vectLineIntegers.at( 2 ).at( 2 ) == 9 &&
            vectLineIntegers.at( 3 ).at( 2 ) == 1 )
          ? 1
          : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing reading string ..." );  

  vector<std::string> vectStrings = TableReader<std::string>::getColumnElementsFromFile(filename, 2);
  for(unsigned int k=0;k < vectStrings.size(); k++){
    trace.info() << " string: "<< vectStrings.at(k)<< endl;
  }
  nbok += (vectStrings.at(0)=="3" && vectStrings.at(1)=="4" && vectStrings.at(2)=="9" 
           && vectStrings.at(3)=="1") ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "<< std::endl;
  trace.endBlock();
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class TableReader" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;
  
  
  bool res = testNumberReader(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
