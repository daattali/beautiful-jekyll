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
 * @file testCheckImageConcept.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/11/28
 *
 * Functions for testing the models of the Image concept.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include "DGtal/helpers/StdDefs.h"
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ImageContainerBySTLMap.h"
#ifdef WITH_ITK
#include "DGtal/images/ImageContainerByITKImage.h"
#endif
#include "DGtal/images/ImageContainerByHashTree.h"
#include "DGtal/images/CImage.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class CheckImageConcept.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testCheckImageConcept()
{
  trace.beginBlock ( "Testing block ..." );
  
  typedef ImageContainerBySTLVector<Domain, int> ImageVector;
  typedef ImageContainerBySTLVector<Domain, int> ImageMap;
 
#ifdef WITH_ITK
 typedef ImageContainerByITKImage<Domain, int> ImageITK;
#endif

  //HashTree is not (yet) a model of CImage
  typedef experimental::ImageContainerByHashTree<Domain, int>  ImageHash;

  BOOST_CONCEPT_ASSERT(( concepts::CImage< ImageVector >));
  BOOST_CONCEPT_ASSERT(( concepts::CImage< ImageMap >));
#ifdef WITH_ITK
  BOOST_CONCEPT_ASSERT(( concepts::CImage< ImageITK >));
#endif

  BOOST_CONCEPT_ASSERT(( concepts::CImage< ImageHash >));

  trace.endBlock();
  
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class CheckImageConcept" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testCheckImageConcept(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
