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
 * @file testITKImage.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/12/09
 *
 * Functions for testing class ITKImage.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/ImageContainerByITKImage.h"
#include <boost/foreach.hpp>

//specific itk method
#if defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#endif
#include <itkExtractImageFilter.h>
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#if defined(__GNUG__)
#endif
#pragma GCC diagnostic pop

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ITKImage.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testITKImage()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "ITK Image init..." );

  typedef DGtal::int32_t Integer;
  typedef SpaceND<3, Integer > Space3Type;
  typedef HyperRectDomain<Space3Type> Domain;
  typedef Domain::Point Point;

  typedef ImageContainerByITKImage<Domain, Integer> Image;

  const Integer t[ ] = { 1, 1, 1};
  const Integer t2[ ] = { 5, 5, 5};
  const Integer t3[ ] = { 2, 2, 2};
  Point a ( t );
  Point b ( t2 );
  Point c ( t3 );
  Integer val;

  Image myImage ( Domain(a, b) );

  trace.info() << myImage << std::endl;
  trace.info() << "getvalue= " << myImage(c) << endl;
  trace.info() << "set value 23 " << endl;
  myImage.setValue( c, 23);

  val =  myImage(c);

  if (val == 23)
    nbok++;
  trace.info() << "getvalue= " << val << endl;
  nb++;

  //Iterator test
  trace.info() << "Simple Iterator=";
  for (Image::ConstIterator it = myImage.begin(), itend = myImage.end();
      it != itend;
      ++it)
    trace.warning() << myImage(it) << " ";
  trace.info() << endl;

  //We rewrite the image
  int nbVal = 0;
  for (Image::Iterator it = myImage.begin(), itend = myImage.end();
      it != itend;
      ++it)
    myImage.setValue(it, nbVal++);

  trace.info() << "Set Iterator=";
  for (Image::ConstIterator it = myImage.begin(), itend = myImage.end();
      it != itend;
      ++it)
    trace.warning() << myImage(it) << " ";
  trace.info() << endl;


  trace.info() << "(" << nbok << "/" << nb << ") "
  << "true == true" << std::endl;
  trace.endBlock();

  return nbok == nb;
}

bool testITKMethod()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Test the use of a pure ITK method..." );

  typedef DGtal::int32_t Integer;
  typedef SpaceND<2, Integer > Space2Type;
  typedef HyperRectDomain<Space2Type> Domain;
  typedef Domain::Point Point;


  typedef ImageContainerByITKImage<Domain, Integer> Image;

  Point a ( 0, 0 );
  Point b ( 9, 9);
  Domain domain(a, b);

  Image myImage(domain);
  trace.info() << myImage << std::endl;

  //We fill the image
  Integer nbVal = 0;
  for (Image::Iterator it = myImage.begin(), itend = myImage.end();
      it != itend;
      ++it)
    myImage.setValue(it, nbVal++);

  trace.info() << "Input image=";
  for (Image::ConstIterator it = myImage.begin(), itend = myImage.end();
      it != itend;
      ++it)
    trace.warning() << myImage(it) << " ";
  trace.info() << endl;


  // We define a cropFilter
  typedef itk::ExtractImageFilter< Image::ITKImage, Image::ITKImage > CropFilter;

  // Crop filter region
  Image::ITKImage::SizeType size;
  size[0] = 5;
  size[1] = 5;

  Image::ITKImage::IndexType index;
  index[0] = 2;
  index[1] = 2;

  Image::ITKImage::RegionType regionToExtract(index,size);

  // Crop filter process
  CropFilter::Pointer cropFilter = CropFilter::New();
  cropFilter->SetInput( myImage.getITKImagePointer() );
  cropFilter->SetExtractionRegion( regionToExtract  );
  cropFilter->Update();

  // Pointer to the filter output
  Image::ITKImagePointer handleOut = cropFilter->GetOutput();
  Image myImageOut ( handleOut );


  trace.info() << "Output image=";
  
  for (Image::ConstIterator it = myImageOut.begin(), itend = myImageOut.end();
       it != itend;
       ++it)
  {
    nbok += (it.Value() == (it.GetIndex()[1]*10 + it.GetIndex()[0]));
    nb++;
    trace.warning() << it.Value() << "(" << (it.GetIndex()[1]*10 + it.GetIndex()[0]) << ")" << " ";
  }
  trace.info() << endl;

  trace.info() << "(" << nbok << "/" << nb << ") " << "true == true" << std::endl;
  trace.endBlock();

  return nbok == 25 && nb == 25;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class ITKImage" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testITKImage() && testITKMethod();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
