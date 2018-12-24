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
 * @file images/exampleRigidtransformation2d.cpp
 * @ingroup Examples
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, France
 *
 * @date 2014/06/28
 *
 * An example file named rigidtransformation2d.
 *
 * This file is part of the DGtal library.
 */

/**
*  Example of 2D rigid transformation using forward and backward model.
   @see @ref moduleGeometricTransform
   \image html church_backward.jpg "Result for backward model" 
*  \example images/exampleRigidtransformation2d.cpp
**/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cmath>
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ConstImageAdapter.h"
#include "ConfigExamples.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"
#include "DGtal/io/readers/PGMReader.h"
#include "DGtal/io/writers/GenericWriter.h"
//! [include]
#include "DGtal/images/RigidTransformation2D.h"
//! [include]
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace functors;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////

int main( int , char** )
{
  typedef ImageSelector<Domain, unsigned char >::Type Image;
  //! [def]
  typedef ForwardRigidTransformation2D < Space > ForwardTrans;
  typedef BackwardRigidTransformation2D < Space > BackwardTrans;
  typedef ConstImageAdapter<Image, Domain, BackwardTrans, Image::Value, Identity > MyImageBackwardAdapter;
  typedef DomainRigidTransformation2D < Domain, ForwardTrans > MyDomainTransformer;
  typedef MyDomainTransformer::Bounds Bounds;
  //! [def]
  trace.beginBlock ( "Example rigidtransformation2d" );
    //! [trans]
    ForwardTrans forwardTrans( RealPoint ( 5, 5 ), M_PI_4, RealVector( 3, -3 ) );
    BackwardTrans backwardTrans( RealPoint ( 5, 5 ), M_PI_4, RealVector( 3, -3 ) );
    //! [trans]
    //![init_domain_helper]
    MyDomainTransformer domainTransformer ( forwardTrans );
    //![init_domain_helper]
    Identity idD;

    Image image = PGMReader<Image>::importPGM ( examplesPath + "samples/church.pgm" );
    //! [domain]
    Bounds bounds = domainTransformer ( image.domain() );
    Domain transformedDomain ( bounds.first, bounds.second );
    //! [domain]
    
    trace.beginBlock ( "Backward - Eulerian model" );
    //! [backward]
      MyImageBackwardAdapter backwardImageAdapter ( image, transformedDomain , backwardTrans, idD );
    //! [backward]
      backwardImageAdapter >> "backward_transform.pgm";
    trace.endBlock();
    
    trace.beginBlock( "Forward - Lagrangian model" );
      Image forwardTransformedImage ( transformedDomain );
     //! [forward]
      for ( Domain::ConstIterator it = image.domain().begin(); it != image.domain().end(); ++it )
      {
	forwardTransformedImage.setValue ( forwardTrans ( *it ), image ( *it ) );
      }
     //! [forward]
      forwardTransformedImage >> "forward_transform.pgm";
    trace.endBlock();
  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
