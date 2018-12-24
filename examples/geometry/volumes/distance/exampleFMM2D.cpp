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
 * @file geometry/volumes/distance/exampleFMM2D.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr ) Laboratoire d'InfoRmatique en
 * Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/02/23
 *
 * @brief Computation of a distance field from a given point  
 *
 * This file is part of the DGtal library.
 */


/**
   Example of use the FMM (fast marching method) class in 2D.
@see \ref moduleFMM

This program outputs this image:

@image html DTbyFMM-25.png

\example geometry/volumes/distance/exampleFMM2D.cpp
*/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include <functional>
#include <iostream>

#include "DGtal/base/Common.h"

//space, domain and image
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/kernel/sets/DigitalSetFromMap.h"
#include "DGtal/images/ImageContainerBySTLMap.h"
#include "DGtal/topology/SCellsFunctors.h"

//shape and tracking
#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/shapes/GaussDigitizer.h"


//FMM
//! [FMMHeader]
#include "DGtal/geometry/volumes/distance/FMM.h"
//! [FMMHeader]

//Display
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/boards/Board2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;


//////////////////////////////////////////////////////////////////////////////
/**
 * Function that displays an image with Board2D
 * @param aImg an image
 * @param aMaxValue maximal value used in the color map
 * @param aBasename base name of the file
 * @tparam TImage a model of CImage
 */
template< typename TImage >
void draw( const TImage aImg, const double& aMaxValue, std::string aBasename) 
{
  typedef typename TImage::Domain::ConstIterator ConstIteratorOnPoints; 
  typedef typename TImage::Domain::Point Point; 
  HueShadeColorMap<double, 2> colorMap(0,aMaxValue);

  Board2D b; 
  b.setUnit ( LibBoard::Board::UCentimeter );
 
  for (ConstIteratorOnPoints it = aImg.domain().begin(), itEnd = aImg.domain().end();
       it != itEnd; ++it)
    {
      Point p = *it; 
      b << CustomStyle( p.className(), new CustomFillColor( colorMap( aImg(p) ) ) );
      b << p;
    }

  {
    std::stringstream s; 
    s << aBasename << ".eps"; 
    b.saveEPS(s.str().c_str());
  }
  #ifdef WITH_CAIRO
  {
    std::stringstream s; 
    s << aBasename << ".png"; 
    b.saveCairo(s.str().c_str(), Board2D::CairoPNG);
  }
  #endif
} 

//////////////////////////////////////////////////////////////////////////////
/**
 * @brief We use FMM to compute a distance field from a given point. 
 */
void example()
{

  trace.beginBlock ( "DT by FMM from one point" );

  //Typedefs
  //! [FMMSimpleTypeDef]
  typedef ImageContainerBySTLMap<Z2i::Domain,double> DistanceImage; 
  typedef DigitalSetFromMap<DistanceImage> AcceptedPointSet; 
  typedef Z2i::Domain::Predicate DomainPredicate;
  typedef FMM<DistanceImage, AcceptedPointSet, DomainPredicate> FMM;
  //! [FMMSimpleTypeDef]

  //Constructions
  int size = 25; 
  //! [FMMSimpleExternalData]
  Z2i::Domain domain(Z2i::Point::diagonal(-size), 
		     Z2i::Point::diagonal(size) ); 
  DistanceImage distanceImage( domain ); 
  AcceptedPointSet set( distanceImage );
  //! [FMMSimpleExternalData]

  //! [FMMSimpleInit]
  Z2i::Point origin = Z2i::Point::diagonal(0); 
  set.insert( origin ); 
  distanceImage.setValue( origin, 0.0 ); 
  //! [FMMSimpleInit]

  //! [FMMSimpleCtor]
  FMM fmm( distanceImage, set, domain.predicate() ); 
  //! [FMMSimpleCtor]

  trace.info() << "Init: " << fmm << std::endl;

  //! [FMMSimpleComputation]
  fmm.compute(); 
  //! [FMMSimpleComputation]

  trace.info() << "End: " << fmm << std::endl;

  //display - you should see concentric circles
  //around the center point. 
  std::stringstream s; 
  s << "DTbyFMM-" << size; 
  draw(distanceImage, fmm.max(), s.str());

  trace.endBlock();
}






///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main ( int argc, char** argv )
{
  trace.beginBlock ( "Example 2d FMM" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  //computation
  example(); 

  trace.endBlock();
  return 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
