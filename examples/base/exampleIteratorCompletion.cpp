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
 * @file base/exampleIteratorCompletion.cpp
 * @ingroup Examples
 * @author Roland Denis (\c roland.denis@univ-smb.fr )
 * LAboratory of MAthematics - LAMA (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2015/10/15
 *
 * @brief An example file for IteratorCompletion.
 *
 * This file is part of the DGtal library.
 */

//! [includes]
#include <new>
#include <cstddef>
#include <algorithm>
#include <iostream>

#include <DGtal/base/Common.h>
#include <DGtal/base/IteratorCompletion.h>
#include <DGtal/kernel/domains/HyperRectDomain.h>
#include <DGtal/kernel/domains/Linearizer.h>
#include <DGtal/kernel/SpaceND.h>
#include <DGtal/images/CImage.h>
//! [includes]

//! [MyImageHeader]

// A minimal image from a C-style array with reverse-iterators and ranges.
template < typename T, DGtal::Dimension N >
class MyImage
  : public DGtal::IteratorCompletion< MyImage<T, N> >   // CRTP
{
public:

  // Typedefs
  typedef MyImage<T, N>   Self;
  typedef typename DGtal::IteratorCompletionTraits<Self>::Iterator       Iterator; // to be coherent with the traits that use IteratorCompletion
  typedef typename DGtal::IteratorCompletionTraits<Self>::ConstIterator  ConstIterator; // same ...

  typedef T                               Value;  // The image values type
  typedef DGtal::SpaceND<N>               Space;  // The image space type
  typedef DGtal::HyperRectDomain<Space>   Domain; // The image domain type
  typedef typename Space::Point           Point;  // The associated point type
  typedef DGtal::Linearizer<Domain, DGtal::ColMajorStorage>    Linearizer; ///< Linearization of the points.
  
  // Contructor
  MyImage( Domain const& aDomain = Domain() )
    : myDomain(aDomain), myData( new T[ myDomain.size() ] )
    {}

  // Destructor
  ~MyImage()
    {
      delete[] myData;
    }

//! [MyImageHeader]

//! [CImageBasicInterface]
 
  // Unary Functor
  Value operator() ( Point const& aPoint ) const
    {
      return myData[ Linearizer::getIndex(aPoint, myDomain) ];
    }

  // Getter
  Value getValue( Point const& aPoint ) const
    {
      return operator()(aPoint);
    }

  // Setter
  void setValue( Point const& aPoint, Value const& aValue )
    {
      myData[ Linearizer::getIndex(aPoint, myDomain) ] = aValue;
    }

  // Returns the associated domain
  Domain const& domain() const
    {
      return myDomain;
    }

  // Assignability (needed for CImage concept)
  Self& operator= ( Self const& other )
    {
      if ( this != &other )
        {
          myDomain = other.domain();
          delete[] myData;
          myData = new Value[ myDomain.size() ];
          std::copy( other.begin(), other.end(), begin() );
        }

      return *this;
    }

//! [CImageBasicInterface]

//! [BasicIteratorInterface]

// Begin mutable iterator
  Iterator begin()
    {
      return myData;
    }

  // Begin constant iterator
  ConstIterator begin() const
    {
      return myData;
    }

  // End mutable iterator
  Iterator end()
    {
      return myData + myDomain.size();
    }

  // End constant iterator
  ConstIterator end() const
    {
      return myData + myDomain.size();
    }
  
//! [BasicIteratorInterface]

//! [PrivateMembers]
private:
  Domain myDomain;
  T* myData;

};
//! [PrivateMembers]

//! [IteratorCompletionTraits]
namespace DGtal
{
  // Specialization of IteratorCompletionTraits for MyVector
  template < typename T, Dimension N >
  class IteratorCompletionTraits< MyImage<T, N> >
    {
    public:
      typedef MyImage<T, N> Self;
      typedef T*            Iterator;
      typedef T const*      ConstIterator;
      
      class DistanceFunctor
        {
        public:
          typedef typename Self::Domain     Domain;
          typedef typename Self::Point      Point;
          typedef typename Self::Difference Difference;

          DistanceFunctor( Self const* aVector )
            : myDomain(aVector->domain())
            {}

          Difference operator() ( Point const& aPoint ) const
            {
              return Self::Linearizer::getIndex( aPoint, myDomain );
            }

        private:
          Domain myDomain;
        };
      
    };
}
//! [IteratorCompletionTraits]

int main()
{

//! [UsageExample]
  using namespace std;

  // Typedefs
  typedef MyImage<double, 2>  My2DImage;
  typedef My2DImage::Value    Value;
  typedef My2DImage::Domain   Domain;
  typedef My2DImage::Point    Point;
  
  // Checks CImage concept
  BOOST_CONCEPT_ASSERT( (DGtal::concepts::CImage<My2DImage>) );

  // Construction
  My2DImage image( Domain( Point(0,0), Point(2,3) ) );

  // Filling
  Value i = 0;
  for ( My2DImage::Iterator it = image.begin(), it_end = image.end() ; it != it_end; ++it )
    {
      *it = ++i;
    }

  // Modifying a value
  image.setValue( Point(1,1), -1 );

  // Forward reading using range
  My2DImage::ConstRange range = image.constRange();
  copy( range.begin(), range.end(), ostream_iterator<Value>( cout, " " ) );
  cout << endl;

  // Backward reading using reverse iterators
  copy( image.rbegin(), image.rend(), ostream_iterator<Value>( cout, " " ) );
  cout << endl;

//! [UsageExample]

}
