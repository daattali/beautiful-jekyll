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
 * @file testConstImageAdapter.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/13
 * 
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/10/12
 *
 * @brief A test file for ConstImageAdapter.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigTest.h"

#include "DGtal/base/BasicFunctors.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/ConstImageAdapter.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

template <typename R>
void displayRange(const R& r)
{
  typedef typename R::ConstIterator I; 
  for (I it = r.begin(), itEnd = r.end();
       it != itEnd; ++it)
    {
      trace.info() << *it << " "; 
    } 
  trace.info() << std::endl; 
}

///////////////////////////////////////////////////////////////////////////////
int main( int argc, char** argv )
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
    
  trace.beginBlock ( "Test for ConstImageAdapter" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  using namespace Z2i; 

  trace.beginBlock("Image creation");

  //domain
  const Integer size = 5; 
  Point p = Point::diagonal(0); 
  Point q = Point::diagonal(size-1); 
  Domain d(p,q); 

  //image
  typedef ImageSelector<Domain, int >::Type Image; 
  Image img(d); 

  //fill
  const int maximalValue = size*size; 
  Image::Range::OutputIterator it = img.range().outputIterator(); 
  for (int i = 0; i < maximalValue; ++i)
    *it++ = i;

  //display values 
  Image::ConstRange r = img.constRange(); 
  std::copy( r.begin(), r.end(), std::ostream_iterator<int>(cout,", ") ); 
  cout << endl; 
  trace.endBlock();
  

  const int thresholdValue = maximalValue/2; 
  trace.beginBlock("Implicit thresholding");

  //! [ConstImageAdapterConstruction]
  functors::Identity g;
  DGtal::functors::Thresholder<Image::Value> t( thresholdValue );
  typedef ConstImageAdapter<Image, Domain, functors::Identity, bool, DGtal::functors::Thresholder<Image::Value> > MyConstImageAdapter;
  BOOST_CONCEPT_ASSERT(( concepts::CConstImage< MyConstImageAdapter > ));
  MyConstImageAdapter a(img, d, g, t); 
  //! [ConstImageAdapterConstruction]

  //display values 
  //! [ConstImageAdapterRange]
  ConstImageAdapter<Image, Domain, functors::Identity, bool, DGtal::functors::Thresholder<Image::Value> >::ConstRange 
    ra = a.constRange(); 
  std::copy( ra.begin(), ra.end(), std::ostream_iterator<int>(cout,", ") );
  cout << endl;
    
  std::vector<int> to_vector(25);
  std::copy(ra.begin(), ra.end(), to_vector.begin());
  for (int i = 0; i < 25; i++)
  {
    if (i<=12)
    {
     if (to_vector[i]==1)
     {
      cout << "ok, ";
      nbok +=  1 ; nb++;
     }
     else
     {
      cout << "!ok, ";
      nb++;
     }
    }
    else
    {
     if (to_vector[i]==0)
     {
      cout << "ok, ";
      nbok +=  1 ; nb++;
     }
     else
     {
      cout << "!ok, ";
      nb++;
     }
    }
  }
  //! [ConstImageAdapterRange]
  
  cout << endl; 

  trace.endBlock();

  bool res = (nbok == nb);
  
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
