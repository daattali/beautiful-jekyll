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


#include <iostream>
#include <vector>
#include <itkImage.h>
#include <itkVector.h>

using namespace std;

/*
 * @author David Coeurjolly
 * @date 14/03/2012
 * This test may fail if ITK was compiled without the cpp0x extension.
 *
 */

int main()
{
  typedef itk::Image< int, 2> ITKImage;
  ITKImage::Pointer ITKImagePointer = ITKImage::New();

  return 1;
}
