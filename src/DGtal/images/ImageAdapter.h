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

#pragma once

/**
 * @file ImageAdapter.h
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/10/12
 *
 * Header file for module ImageAdapter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImageAdapter_RECURSES)
#error Recursive header files inclusion detected in ImageAdapter.h
#else // defined(ImageAdapter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImageAdapter_RECURSES

#if !defined ImageAdapter_h
/** Prevents repeated inclusion of headers. */
#define ImageAdapter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/images/CImage.h"
#include "DGtal/kernel/domains/CDomain.h"

#include "DGtal/images/DefaultConstImageRange.h"
#include "DGtal/images/DefaultImageRange.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
/////////////////////////////////////////////////////////////////////////////
// Template class ImageAdapter
/**
 * Description of template class 'ImageAdapter' <p>
 * \brief Aim: implements an image adapter with a given domain
 * (i.e. a subdomain) and 3 functors : g for domain, f for accessing point values and f-1 for writing point values.
 *
 * This class is (like Image class) a lightweight proxy on ImageContainers (models of CImage).
 * It uses a given Domain (i.e. a subdomain) but work directly (for
 * reading and writing processes) thanks to an alias (i.e. a pointer) on the
 * original Image given in argument.
 * 
 * ImageAdapter class is also a model of CImage.
 * 
 * Caution :
 *  - the type of value of Point for the ImageAdapter Domain must also
 * be the same than the type of value of Point for the original
 * ImageContainer.
 *
 * @tparam TImageContainer an image container type (model of CImage).
 * @tparam TNewDomain a domain.
 * @tparam TFunctorD the functor g that transforms the domain into another one
 * @tparam TNewValue the type of value return by the functor f.
 * @tparam TFunctorV the functor f that transforms the value into another one during reading process
 * @tparam TFunctorVm1 the functor f-1 that transforms the value into another one during writing process
 *
 * The values associated to accessing the point values are adapted  
 * with a functor g and a functor f given at construction so that 
 * operator() calls f(img(g(aPoint))), instead of calling directly 
 * operator() of the underlying image img.
 * 
 * The values associated to writing the points are adapted  
 * with a functor g and a functor f-1 given at construction so that 
 * setValue() is img.setValue(g(aPoint), f-1(aValue))
 * 
 * The use is the same that for ConstImageAdapter so
 * here is the construction of a simple ConstImageAdapter that 
 * is a thresholded view of the initial scalar image: 
 *
 * @snippet images/exampleConstImageAdapter.cpp ConstImageAdapterForThresholderImage_creation
 *
 * NB: the underlying image as well as the 3 functors
 * are stored in the adapter as aliasing pointer
 * in order to avoid copies.  
 * The pointed objects must exist and must not be deleted 
 * during the use of the adapter
 */
template <typename TImageContainer,
          typename TNewDomain,
          typename TFunctorD,
          typename TNewValue,
          typename TFunctorV,
          typename TFunctorVm1>
class ImageAdapter
{

    // ----------------------- Types ------------------------------

public:
    typedef ImageAdapter<TImageContainer, TNewDomain, TFunctorD, TNewValue, TFunctorV, TFunctorVm1> Self; 

    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImageContainer> ));
    BOOST_CONCEPT_ASSERT(( concepts::CDomain<TNewDomain> ));
   
    typedef TNewDomain Domain;
    typedef typename TNewDomain::Point Point;
    typedef TNewValue Value;

    BOOST_CONCEPT_ASSERT(( concepts::CUnaryFunctor<TFunctorD, Point, typename TImageContainer::Point> ));
    BOOST_CONCEPT_ASSERT(( concepts::CUnaryFunctor<TFunctorV, typename TImageContainer::Value, Value > ));
    BOOST_CONCEPT_ASSERT(( concepts::CUnaryFunctor<TFunctorVm1, Value, typename TImageContainer::Value > ));

    ///Types copied from the container
    typedef TImageContainer ImageContainer;

    typedef DefaultConstImageRange<Self> ConstRange; 
    typedef DefaultImageRange<Self> Range; 

    // ----------------------- Standard services ------------------------------

public:

    ImageAdapter(
                 ImageContainer &anImage, 
                 ConstAlias<Domain>       aDomain, 
                 ConstAlias<TFunctorD>    aFD,
                 ConstAlias<TFunctorV>    aFV,
                 ConstAlias<TFunctorVm1>  aFVm1
      ) :
            myImagePtr(&anImage), mySubDomainPtr(&aDomain), myFD(&aFD), myFV(&aFV), myFVm1(&aFVm1)
    {
      defaultValue = 0;
#ifdef DEBUG_VERBOSE
        trace.warning() << "ImageAdapter Ctor fromRef " << std::endl;
#endif
    }

    /**
    * Assignment.
    * @param other the object to copy.
    * @return a reference on 'this'.
    */
    ImageAdapter & operator= ( const ImageAdapter & other )
    {
#ifdef DEBUG_VERBOSE
        trace.warning() << "ImageAdapter assignment " << std::endl;
#endif
        if (&other != this)
        {
            myImagePtr = other.myImagePtr;
            mySubDomainPtr = other.mySubDomainPtr;
            myFD = other.myFD;
            myFV = other.myFV;
            myFVm1 = other.myFVm1;
	    defaultValue = other.defaultValue;
        }
        return *this;
    }


    /**
     * Destructor.
     * Does nothing
     */
    ~ImageAdapter() {}

    // ----------------------- Interface --------------------------------------
public:

    /////////////////// Domains //////////////////

    /**
     * Returns a reference to the underlying image domain.
     *
     * @return a reference to the domain.
     */
    const Domain & domain() const
    {
        return (*mySubDomainPtr);
    }

    /**
     * Returns the range of the underlying image
     * to iterate over its values
     *
     * @return a range.
     */
    ConstRange constRange() const
    {
        return ConstRange( *this );
    }

    /**
     * Returns the range of the underlying image
     * to iterate over its values
     *
     * @return a range.
     */
    Range range()
    {
        return Range( *this );
    }

    /////////////////// Accessors //////////////////


    /**
     * Get the value of an image at a given position given
     * by a Point.
     *
     * @pre the point must be in the domain
     *
     * @param aPoint the point.
     * @return the value at aPoint.
     */
    Value operator()(const Point & aPoint) const
    {
      ASSERT(this->domain().isInside(aPoint));
      
      typename TImageContainer::Point point = myFD->operator()(aPoint);
      if (myImagePtr->domain().isInside(point))
	return myFV->operator()(myImagePtr->operator()(point));
      else
	return defaultValue;
    }
    


    /////////////////// Set values //////////////////

    /**
     * Set a value on an Image at a position specified by a Point.
     *
     * @pre @c it must be a point in the image domain.
     *
     * @param aPoint the point.
     * @param aValue the value.
     */
    void setValue(const Point &aPoint, const  Value &aValue)
    {
        ASSERT(this->domain().isInside(aPoint));
        
        myImagePtr->setValue(myFD->operator()(aPoint), myFVm1->operator()(aValue));
    }



    /////////////////// API //////////////////

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const
    {
        return (myImagePtr->isValid() );
    }


    /**
     * Returns the pointer on the Image container data.
     * @return a const ImagePtr.
     */
    const ImageContainer * getPointer() const
    {
        return myImagePtr;
    }
    
    /**
     * Allows to define a default value returned when point 
     * transformed by domain functor does not belongs to 
     * image domain.
     */
    void setDefaultValue ( Value aValue )
    {
      defaultValue = aValue;
    }
    
    Value getDefaultValue () const
    {
      return defaultValue;
    }

    // ------------------------- Protected Datas ------------------------------
private:
    /**
     * Default constructor.
     */
    ImageAdapter() {
#ifdef DEBUG_VERBOSE
        trace.warning() << "ImageAdapter Ctor default " << std::endl;
#endif
    }
    
    // ------------------------- Private Datas --------------------------------
protected:

    /// Alias on the image container
    ImageContainer * myImagePtr;
    
    /**
     * The image SubDomain
     */
    const Domain *mySubDomainPtr;
    
    /**
     * Aliasing pointer on the underlying Domain functor
     */
    const TFunctorD* myFD;

    /**
     * Aliasing pointer on the underlying Value functor
     */
    const TFunctorV* myFV;
    
    /**
     * Aliasing pointer on the underlying "m-1" Value functor
     */
    const TFunctorVm1* myFVm1;
    
    /**
     *  Default value returned when point transformed by image functor does not belongs to image.
     *  Initial value is 0.
     */
    Value defaultValue;


private:


    // ------------------------- Internals ------------------------------------
private:

}; // end of class ImageAdapter


/**
 * Overloads 'operator<<' for displaying objects of class 'ImageAdapter'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'ImageAdapter' to write.
 * @return the output stream after the writing.
 */
template <typename TImageContainer, typename TNewDomain, typename TFunctorD, typename TNewValue, typename TFunctorV, typename TFunctorVm1>
std::ostream&
operator<< ( std::ostream & out, const ImageAdapter<TImageContainer, TNewDomain, TFunctorD, TNewValue, TFunctorV, TFunctorVm1> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/images/ImageAdapter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImageAdapter_h

#undef ImageAdapter_RECURSES
#endif // else defined(ImageAdapter_RECURSES)
