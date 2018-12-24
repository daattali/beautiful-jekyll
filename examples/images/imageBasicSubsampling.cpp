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
 * @file images/imageBasicSubsampling.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2014/05/21
 *
 * An example file named imageBasicSubsampling.
 *
 * This file is part of the DGtal library.
 */


/**
 * Examples of 2D and 3D basic image subsampling.
 *
 * \image html imageBasicSubsamplingExample.png "Illustration of the resulting subsampling produced by this example."
 *
 * \example images/imageBasicSubsampling.cpp
 **/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ConfigExamples.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"

//! [imageBasicSubsamplingHeaders]
#include "DGtal/kernel/BasicPointFunctors.h"
#include "DGtal/images/ConstImageAdapter.h"
//! [imageBasicSubsamplingHeaders]

#include "DGtal/images/ImageContainerBySTLVector.h"

#include "DGtal/io/readers/GenericReader.h"
#include "DGtal/io/writers/GenericWriter.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int /*argc*/, char** /*argv*/ )
{
  
  //! [imageBasicSubsamplingType2D]
  typedef ImageContainerBySTLVector < Z2i::Domain, unsigned char> Image2D;
  typedef ConstImageAdapter<Image2D,  Image2D::Domain, 
                            functors::BasicDomainSubSampler<Image2D::Domain>,  
                            Image2D::Value,
                            functors::Identity > ConstImageAdapterForSubSampling;

  //! [imageBasicSubsamplingType2D]

  //! [imageBasicSubsamplingType3D]
  typedef ImageContainerBySTLVector < Z3i::Domain, unsigned char> Image3D;
  typedef ConstImageAdapter<Image3D,  Image3D::Domain, 
                            functors::BasicDomainSubSampler<Image3D::Domain>,
                            Image3D::Value, 
                            functors::Identity > ConstImageAdapterForSubSampling3D;
  //! [imageBasicSubsamplingType3D]


  trace.beginBlock ( "Example imageBasicSubsampling" );

  std::string imageFilename3D = examplesPath + "samples/Al.100.vol";
  std::string imageFilename2D = examplesPath + "samples/church.pgm";
  Image3D image3D = GenericReader<Image3D>::import( imageFilename3D );
  Image2D image2D = GenericReader<Image2D>::import( imageFilename2D );

  for (unsigned int i=1; i<=20; i*=2){
    std::vector<Z2i::Domain::Size> aGridSize2D;
    aGridSize2D.push_back(i);
    aGridSize2D.push_back(i);
    // Construction of the functor for the 2D domain subsampling from a given grid size and shift.
    //! [imageBasicSubsamplingSubSampler2D]
    DGtal::functors::BasicDomainSubSampler<Image2D::Domain> subSampler2D(image2D.domain(), aGridSize2D, Z2i::Point(0 ,0));
    //! [imageBasicSubsamplingSubSampler2D]

    functors::Identity df;
    // Get the new domain produces from the subsampler and define the ConstImageAdapter:
    //! [imageBasicSubsamplingConstImageAdapterSubSampling2D]
    Image2D::Domain subSampledDomain2D  = subSampler2D.getSubSampledDomain();
    ConstImageAdapterForSubSampling subsampledImage2D (image2D, subSampledDomain2D, subSampler2D, df);
    //! [imageBasicSubsamplingConstImageAdapterSubSampling2D]

    stringstream outputname; 
    outputname << "subSampledImage"<< i<< "x"<< i << ".pgm" ;
    //! [imageBasicSubsamplingExport2D]
    GenericWriter<ConstImageAdapterForSubSampling>::exportFile(outputname.str(), subsampledImage2D );
    //! [imageBasicSubsamplingExport2D]
    trace.info() << "Exporting 2D subsampled image by grid size :" << i << "x"<< i<< " in "<< outputname.str() << std::endl;
  } 

  for (unsigned int i=1; i<=20; i*=2){
    std::vector<Z3i::Domain::Size> aGridSize3D;
    aGridSize3D.push_back(i);
    aGridSize3D.push_back(i);
    aGridSize3D.push_back(i);

        // Construction of the functor for the 3D domain subsampling from a given grid size and shift.
    //! [imageBasicSubsamplingSubSampler3D]
    DGtal::functors::BasicDomainSubSampler<Image3D::Domain> subSampler3D(image3D.domain(), aGridSize3D, Z3i::Point(0 ,0, 0));
    //! [imageBasicSubsamplingSubSampler3D]

    DGtal::functors::Identity df;
    // Get the new domain produces from the subsampler and define the ConstImageAdapter:
    //! [imageBasicSubsamplingConstImageAdapterSubSampling3D]
    Image3D::Domain subSampledDomain3D  = subSampler3D.getSubSampledDomain();
    ConstImageAdapterForSubSampling3D subsampledImage3D (image3D, subSampledDomain3D, subSampler3D, df);
    //! [imageBasicSubsamplingConstImageAdapterSubSampling3D]

    stringstream outputname3D; 
    outputname3D << "subSampledImage3D"<< i<< "x"<< i << ".vol" ;
    //! [imageBasicSubsamplingExport3D]
    GenericWriter<ConstImageAdapterForSubSampling3D>::exportFile(outputname3D.str(), subsampledImage3D );
    //! [imageBasicSubsamplingExport3D]
    trace.info() << "Exporting 3D subsampled image by grid size :" << i << "x"<< i<< "x"<< i<< " in "<< outputname3D.str() << std::endl;
  }

  
  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
