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
 * @file images/exampleArrayImageAdapter.cpp
 * @ingroup Examples
 * @author Roland Denis (\c roland.denis@univ-smb.fr )
 * LAboratory of MAthematics - LAMA (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2015/10/14
 *
 * @brief An example file for ArrayImageAdapter.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include <DGtal/base/Common.h>
#include <DGtal/helpers/StdDefs.h>

#include <DGtal/io/boards/Board2D.h>

//! [include]
#include <new>
#include <cmath>
#include <algorithm>
#include <DGtal/io/colormaps/HueShadeColorMap.h>
#include <DGtal/images/ImageContainerBySTLVector.h>
#include <DGtal/images/ArrayImageAdapter.h>
//! [include]

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
///////////////////////////////////////////////////////////////////////////////

void ArrayImageAdapter_example()
{
//! [ArrayImageAdapter_example]
  using Space = SpaceND<2>;
  using Domain = HyperRectDomain<Space>;
  using Value = double;

  const Domain domain{ {0, 1}, {4, 3} };

  Value* data = new Value[ domain.size() ];

  // Convert this allocated memory to a CImage model.
  ArrayImageAdapter< Value*, Domain > image( data, domain );
  // Alternative syntax using the helpers:
  // auto image = makeArrayImageAdapterFromIterator( data, domain );

  // Fill the image with first coordinate of the point
  for ( auto it = image.begin(); it != image.end(); ++it )
    {
      *it = it.getPoint()[0];
    }

  // Get a constant view on a sub-domain.
  const Domain sub_domain{ {1, 1}, {3, 2} };
  ArrayImageAdapter< Value const*, Domain > cst_image( data, domain, sub_domain );
  // Alternative syntax using the helpers:
  // auto const cst_image = makeArrayImageAdapterFromImage( image, sub_domain );

  // Display it.
  for ( auto value : cst_image )
    {
      std::cout << value << " ";
    }
  std::cout << std::endl;
//! [ArrayImageAdapter_example]
}

void moduleImages_example()
{
  using namespace Z2i;

  Board2D aBoard;

//! [def]
  using Value = double; // value type  of the image
  using HueShadeDouble = HueShadeColorMap<Value>;   // a simple HueShadeColorMap varying on 'double' values
//! [def]

  trace.beginBlock("image");

//! [raw_image_creation]
  const Domain domain(Point(1,1), Point(16,16));
  Value* data = new Value[ domain.size() ];
  ArrayImageAdapter< Value*, Domain > image( data, domain );
//! [raw_image_creation]

//! [image_filling]
  Value i = 0;
  for ( auto & value : image )
    value = i++;
//! [image_filling]

  aBoard.clear();
  Display2DFactory::drawImage<HueShadeDouble>(aBoard, image, 0, domain.size()-1);
  aBoard.saveSVG("ArrayImageAdapter_image.svg");

  trace.endBlock();

  trace.beginBlock("subImage");

//! [ConstArrayImageAdapterForSubImage_creation]
  Domain subDomain(Point(1,1), Point(8,8));
  ArrayImageAdapter< Value const*, Domain > constSubImage( data, domain, subDomain );
//! [ConstArrayImageAdapterForSubImage_creation]

  aBoard.clear();
  Display2DFactory::drawImage<HueShadeDouble>(aBoard, constSubImage, 0, domain.size()-1);
  aBoard.saveSVG("ArrayImageAdapter_subImage.svg");

  trace.endBlock();

  trace.beginBlock("modifying subImage through domain iterator");
  {
//! [ArrayImageAdapterForSubImage_creation]
  ArrayImageAdapter< Value*, Domain > subImage( data, domain, subDomain );
//! [ArrayImageAdapterForSubImage_creation]
  }

//! [ArrayImageAdapterForSubImage_alternateCreation]
  auto subImage = makeArrayImageAdapterFromIterator( data, domain, subDomain );
//! [ArrayImageAdapterForSubImage_alternateCreation]


//! [ArrayImageAdapterForSubImage_modifByDomain]
  for ( auto point : subImage.domain() )
    {
      Value coord = (point - Point(4,4)).norm();
      subImage.setValue( point, 25*(cos(coord)+1) );
    }
//! [ArrayImageAdapterForSubImage_modifByDomain]

  aBoard.clear();
  Display2DFactory::drawImage<HueShadeDouble>(aBoard, image, 0, domain.size()-1);
  aBoard.saveSVG("ArrayImageAdapter_subImage_modifByDomain.svg");
  
  trace.endBlock();
  
  trace.beginBlock("modifying subImage through image iterator");
//! [ArrayImageAdapterForSubImage_modifByImage]
  for ( auto it = subImage.begin(), it_end = subImage.end(); it != it_end; ++it )
    {
      Value coord = (it.getPoint() - Point(4,4)).norm();
      *it = 25*(sin(coord)+1);
    }
//! [ArrayImageAdapterForSubImage_modifByImage]

  aBoard.clear();
  Display2DFactory::drawImage<HueShadeDouble>(aBoard, image, 0, domain.size()-1);
  aBoard.saveSVG("ArrayImageAdapter_subImage_modifByImage.svg");
  
  trace.endBlock();

  trace.beginBlock("subImage from an ImageContainerBySTLVector");
//! [ImageSTL_creation]
  ImageContainerBySTLVector<Domain, Value> anIterableImage(domain);
  for (auto& value : anIterableImage)
    value = 0;
//! [ImageSTL_creation]

//! [ArrayImageAdapterFromImageSTL]
  {
  ArrayImageAdapter< ImageContainerBySTLVector<Domain,Value>::Iterator, Domain > subImageSTL( anIterableImage.begin(), domain, subDomain );
  }
//! [ArrayImageAdapterFromImageSTL]

//! [ArrayImageAdapterFromImageSTL_alternate]
  auto subImageSTL = makeArrayImageAdapterFromImage( anIterableImage, subDomain );
//! [ArrayImageAdapterFromImageSTL_alternate]

  trace.endBlock();
  
  trace.beginBlock("using std::copy on ArrayImageAdapter");
//! [ArrayImageAdapterFromImageSTL_copy]
  std::copy( subImage.cbegin(), subImage.cend(), subImageSTL.begin() );
//! [ArrayImageAdapterFromImageSTL_copy]

  aBoard.clear();
  Display2DFactory::drawImage<HueShadeDouble>(aBoard, anIterableImage, 0, domain.size()-1);
  aBoard.saveSVG("ArrayImageAdapter_subImage_copyToImageSTL.svg");
  
  trace.endBlock();

  delete[] data;
}

int main()
{
  ArrayImageAdapter_example();
  moduleImages_example();
  return 0;
}

//                                                                           //
///////////////////////////////////////////////////////////////////////////////
