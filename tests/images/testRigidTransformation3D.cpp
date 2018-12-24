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
 * @file testRigidTransformation3D.cpp
 * @ingroup Tests
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, France
 *
 * @date 2014/06/28
 *
 * Functions for testing class RigidTransformation3D.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <boost/graph/graph_concepts.hpp>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include <DGtal/images/ImageSelector.h>
#include <DGtal/images/ImageContainerBySTLVector.h>
#include "DGtal/images/ConstImageAdapter.h"
#include "DGtal/images/RigidTransformation3D.h"
#include "DGtal/io/readers/PGMReader.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/writers/GenericWriter.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;
using namespace functors;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class RigidTransformation3D.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
class testRigidTransformation3D
{
  typedef ImageSelector<Domain, unsigned char >::Type Image;
  typedef ForwardRigidTransformation3D < Space > ForwardTrans;
  typedef BackwardRigidTransformation3D < Space > BackwardTrans;
  typedef ConstImageAdapter<Image, Domain, BackwardTrans, Image::Value, Identity > MyImageBackwardAdapter;
  typedef DomainRigidTransformation3D < Domain, ForwardTrans > DomainTrans;
  typedef DomainTrans::Bounds Bounds;
private:
  Image binary;
  ForwardTrans forwardTrans;
  BackwardTrans backwardTrans;
  Identity idD;
  DomainTrans domainForwardTrans;
public:
  // Setup part
  testRigidTransformation3D() : 
  binary ( PGMReader<Image>::importPGM3D ( testPath + "samples/cat10.pgm3d" ) ),
  forwardTrans ( RealPoint ( 5, 5, 5 ), RealVector ( 1, 0, 1 ), M_PI_4, RealVector( 3, -3, 3 ) ),
  backwardTrans( RealPoint ( 5, 5, 5 ), RealVector ( 1, 0, 1 ), M_PI_4, RealVector( 3, -3, 3 ) ),
  domainForwardTrans(forwardTrans)
  {}
  
  bool forwardTransformation ()
  {
    Bounds bounds = domainForwardTrans ( binary.domain() );
    Domain d ( bounds.first, bounds.second );
    Image transformed ( d );
    for ( Domain::ConstIterator it = binary.domain().begin(); it != binary.domain().end(); ++it )
    {
      transformed.setValue ( forwardTrans ( *it ), binary ( *it ) );
    }
    transformed >> "binary_after_forward.pgm3d";
    return true;
  }
  bool backwardTransformation ()
  {
    Bounds bounds = domainForwardTrans ( binary.domain() );
    Domain d ( bounds.first, bounds.second );
    MyImageBackwardAdapter adapter ( binary, d, backwardTrans, idD );
    adapter >> "binary_after_backward.pgm3d";
    return true;
  }
};

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int, char** )
{
  bool res = true;
  testRigidTransformation3D rigidTest;
  trace.beginBlock ( "Testing RigidTransformation3D" );
    res &= rigidTest.forwardTransformation();
    res &= rigidTest.backwardTransformation();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
