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
 * @file tutorial-examples/FMMErosion.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/06/19
 *
 * An example file named FMMErosion.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

#include "ConfigExamples.h"

//image
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ImageContainerBySTLMap.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/kernel/BasicPointPredicates.h"

//IO
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/writers/VolWriter.h"

//frontier
#include "DGtal/topology/SurfelAdjacency.h"
#include "DGtal/topology/helpers/FrontierPredicate.h"
#include "DGtal/topology/LightExplicitDigitalSurface.h"

// FMM
#include "DGtal/geometry/volumes/distance/FMM.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
int main( int argc, char** argv )
{
  trace.beginBlock ( "Example FMMErosion" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  DGtal::trace.beginBlock("image reading..."); 

  //! [FMMErosionImageReading]
  string imageFileName = examplesPath + "samples/cat10.vol"; 
  trace.info() << imageFileName <<std::endl; 
  typedef ImageContainerBySTLVector<Domain, bool> BinaryImage; 
  BinaryImage binaryImage = VolReader<BinaryImage>::importVol( imageFileName);
  //! [FMMErosionImageReading]

  DGtal::trace.endBlock(); 

  DGtal::trace.beginBlock("Search for a bel..."); 

  //space and starting bel
  //! [FMMErosionStartingBel]
  KSpace ks;
  Domain domain = binaryImage.domain(); 
  ks.init( domain.lowerBound(), domain.upperBound(), true ); 
  KSpace::SCell bel;

  try { 
    //getting a bel
    bel = Surfaces<KSpace>::findABel( ks, binaryImage, domain.size() );
    trace.info() << "starting bel: " << bel << std::endl;
 
  } catch (DGtal::InputException i) {
    trace.emphase() << "starting bel not found" << std::endl; 
    return 0; 
  }
  //! [FMMErosionStartingBel]

  DGtal::trace.endBlock(); 

  DGtal::trace.beginBlock("Implicit frontier..."); 

  //implicit frontier 
  //! [FMMErosionTracking]
  typedef functors::FrontierPredicate<KSpace, BinaryImage> SurfelPredicate;
  typedef LightExplicitDigitalSurface<KSpace, SurfelPredicate> Frontier;
  functors::SCellToIncidentPoints<KSpace> toIncidentPoints( ks );
  std::pair<Point,Point> bpair = toIncidentPoints( bel );    
  SurfelPredicate surfelPredicate( ks, binaryImage, 
				   binaryImage( bpair.first ), 
				   binaryImage( bpair.second ) );  
  Frontier frontier( ks, surfelPredicate, 
		     SurfelAdjacency<KSpace::dimension>( true ), bel ); 
  //! [FMMErosionTracking]

  DGtal::trace.endBlock();

  const double maximalDistance = 3.0; 

  DGtal::trace.beginBlock("FMM..."); 

  //! [FMMErosionFMMTypes]
  typedef ImageContainerBySTLMap<Domain,double> DistanceImage; 
  typedef DigitalSetFromMap<DistanceImage> AcceptedPointSet; 
  typedef FMM<DistanceImage, AcceptedPointSet, BinaryImage > FMM;
  //! [FMMErosionFMMTypes]

  //! [FMMErosionFMMInit]
  DistanceImage imageDistance( domain, 0.0 );
  AcceptedPointSet pointSet( imageDistance );
  functors::SCellToInnerPoint<KSpace> toInnerPoint( ks );
  for (Frontier::SurfelConstIterator it = frontier.begin(), itEnd = frontier.end(); 
       it != itEnd; ++it) 
    {
      pointSet.insert( toInnerPoint(*it) ); 
      imageDistance.setValue( toInnerPoint(*it), 0.5 ); 
    }
  //! [FMMErosionFMMInit]

  //! [FMMErosionFMM]
  FMM fmm( imageDistance, pointSet, binaryImage,
	   domain.size(), maximalDistance );
  fmm.compute(); 
  trace.info() << fmm << std::endl;  
  //! [FMMErosionFMM]

  DGtal::trace.endBlock();

  DGtal::trace.beginBlock("Erosion"); 
  trace.info() << "Erosion of radius: " << maximalDistance << std::endl;

  //! [FMMErosionErosion]
  for (AcceptedPointSet::ConstIterator it = pointSet.begin(), itEnd = pointSet.end(); 
       it != itEnd; ++it) 
    {
      binaryImage.setValue(*it, 0); 
    }
  //! [FMMErosionErosion]

  DGtal::trace.endBlock();

  DGtal::trace.beginBlock("image writing..."); 

  //! [FMMErosionImageWriting]
  string outputFileName = "eroded.vol"; 
  trace.info() << "to " << outputFileName << std::endl; 
  VolWriter<BinaryImage,functors::Cast<unsigned char> >::exportVol(outputFileName, binaryImage);
  //! [FMMErosionImageWriting]

  DGtal::trace.endBlock(); 


  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
