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
 * @file ConstImageAdapter.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/07
 *
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/10/12
 *
 * Header file for module ConstImageAdapter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ConstImageAdapter_RECURSES)
#error Recursive header files inclusion detected in ConstImageAdapter.h
#else // defined(ConstImageAdapter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ConstImageAdapter_RECURSES

#if !defined ConstImageAdapter_h
/** Prevents repeated inclusion of headers. */
#define ConstImageAdapter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/images/CImage.h"
#include "DGtal/kernel/domains/CDomain.h"

#include "DGtal/images/DefaultConstImageRange.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
/////////////////////////////////////////////////////////////////////////////
// Template class ConstImageAdapter
/**
 * Description of template class 'ConstImageAdapter' <p>
 * \brief Aim: implements a const image adapter with a given domain
 * (i.e. a subdomain) and 2 functors : g for domain, f for accessing point values.
 *
 * This class is (like Image class) a lightweight proxy on any models of CConstImage.
 * It uses a given Domain (i.e. a subdomain) but work directly (for
 * accessing process) thanks to an alias (i.e. a pointer) on the
 * original Image given in argument.
 *
 * ConstImageAdapter class is also a model of CConstImage.
 *
 * Caution :
 *  - the type of value of Point for the ConstImageAdapter Domain must
 * also be the same than the type of value of Point for the original
 * ImageContainer.
 *
 * @tparam TImageContainer an image container type (model of CConstImage).
 * @tparam TNewDomain a domain.
 * @tparam TFunctorD the functor g that transforms the domain into another one
 * @tparam TNewValue the type of value return by the functor f.
 * @tparam TFunctorV the functor f that transforms the value into another one during reading process
 *
 * The values associated to accessing the point values are adapted
 * with a functor g and a functor f given at construction so that
 * operator() calls f(img(g(aPoint))), instead of calling directly
 * operator() of the underlying image img.
 *
 * Here is the construction of a simple ConstImageAdapter that
 * is a thresholded view of the initial scalar image:
 *
 * @snippet images/exampleConstImageAdapter.cpp ConstImageAdapterForThresholderImage_creation
 *
 * NB: the underlying image as well as the 2 functors
 * are stored in the adapter as aliasing pointer
 * in order to avoid copies.
 * The pointed objects must exist and must not be deleted
 * during the use of the adapter
 */
template <typename TImageContainer,
	  typename TNewDomain,
	  typename TFunctorD,
	  typename TNewValue, typename TFunctorV>
class ConstImageAdapter
{

    // ----------------------- Types ------------------------------

public:
    typedef ConstImageAdapter<TImageContainer, TNewDomain, TFunctorD, TNewValue, TFunctorV> Self;

    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CConstImage<TImageContainer> ));
    BOOST_CONCEPT_ASSERT(( concepts::CDomain<TNewDomain> ));

    typedef TNewDomain Domain;
    typedef typename TNewDomain::Point Point;
    typedef TNewValue Value;


    BOOST_CONCEPT_ASSERT(( concepts::CUnaryFunctor<TFunctorD, Point, typename TImageContainer::Point> ));
    BOOST_CONCEPT_ASSERT(( concepts::CUnaryFunctor<TFunctorV, typename TImageContainer::Value, Value> ));

    ///Types copied from the container
    typedef TImageContainer ImageContainer;

    typedef DefaultConstImageRange<Self> ConstRange;

    // ----------------------- Standard services ------------------------------

public:

    ConstImageAdapter(
                      ConstAlias<ImageContainer> anImage,
                      ConstAlias<Domain> aDomain,
                      ConstAlias<TFunctorD> aFD,
                      ConstAlias<TFunctorV> aFV
      ) :
            myImagePtr(&anImage), mySubDomainPtr(&aDomain), myFD(&aFD), myFV(&aFV)
    {
      defaultValue = 0;
#ifdef DEBUG_VERBOSE
        trace.warning() << "ConstImageAdapter Ctor fromRef " << std::endl;
#endif
    }

    /**
    * Assignment.
    * @param other the object to copy.
    * @return a reference on 'this'.
    */
    ConstImageAdapter & operator= ( const ConstImageAdapter & other )
    {
#ifdef DEBUG_VERBOSE
        trace.warning() << "ConstImageAdapter assignment " << std::endl;
#endif
        if (&other != this)
        {
            myImagePtr = other.myImagePtr;
            mySubDomainPtr = other.mySubDomainPtr;
            myFD = other.myFD;
            myFV = other.myFV;
	    defaultValue = other.defaultValue;
        }
        return *this;
    }


    /**
     * Destructor.
     * Does nothing
     */
    ~ConstImageAdapter() {}

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
     * @return the style name used for drawing this object.
     */
    std::string className() const;


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
    ConstImageAdapter() {
#ifdef DEBUG_VERBOSE
        trace.warning() << "ConstImageAdapter Ctor default " << std::endl;
#endif
    }

    // ------------------------- Private Datas --------------------------------
protected:

    /// Alias on the image container
    const ImageContainer * myImagePtr;

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
     *  Default value returned when point transformed by image functor does not belongs to image.
     *  Initial value is 0.
     */
    Value defaultValue;

private:


    // ------------------------- Internals ------------------------------------
private:

}; // end of class ConstImageAdapter


/**
 * Overloads 'operator<<' for displaying objects of class 'ConstImageAdapter'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'ConstImageAdapter' to write.
 * @return the output stream after the writing.
 */
template <typename TImageContainer, typename TNewDomain, typename TFunctorD, typename TNewValue, typename TFunctorV>
std::ostream&
operator<< ( std::ostream & out, const ConstImageAdapter<TImageContainer, TNewDomain, TFunctorD, TNewValue, TFunctorV> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/images/ConstImageAdapter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ConstImageAdapter_h

#undef ConstImageAdapter_RECURSES
#endif // else defined(ConstImageAdapter_RECURSES)
