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
 * @file geometry/curves/freemanChainDisplay.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2010/12/01
 * 
 * An example of FreemanChain display with background source image.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include "DGtal/base/Common.h"
///////////////////////////////////////////////////////////////////////////////


#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/base/BasicTypes.h"
#include "DGtal/geometry/curves/FreemanChain.h"
#include "DGtal/io/readers/MagickReader.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/helpers/StdDefs.h"



#include "ConfigExamples.h"


using namespace std;
using namespace DGtal;
using namespace Z2i;



///////////////////////////////////////////////////////////////////////////////

int main()
{
  
  typedef SpaceND<2> Space2;
  typedef HyperRectDomain<Space2> TDomain;

  //Default image selector = STLVector
  typedef ImageSelector<TDomain, unsigned char>::Type Image;
  

  // Creating FreemanChain from file
  std::string freemanChainFilename = examplesPath + "samples/contourS.fc";
  fstream fst;
  fst.open (freemanChainFilename.c_str(), ios::in);
  FreemanChain<Space::Integer> fc(fst);
  fst.close();
  
  
  // Importing image with MagickReader
  MagickReader<Image> reader;
  std::string filenameImage = examplesPath + "samples/contourS.gif";
  Image img = reader.importImage( filenameImage );
  
  Point ptInf = img.domain().lowerBound(); 
  Point ptSup = img.domain().upperBound(); 
  unsigned int width = abs(ptSup[0]-ptInf[0]+1);
  unsigned int height = abs(ptSup[1]-ptInf[1]+1);
  
  // Draw the freemanchain and the contour 
  Board2D dgBoard;
  
  dgBoard.drawImage(filenameImage, 0,height-1, width, height );
  dgBoard << fc;
  
  dgBoard.saveEPS("freemanChainDisplay.eps");
  dgBoard.saveSVG("freemanChainDisplay.svg");
  dgBoard.saveFIG("freemanChainDisplay.fig");
  
  
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
