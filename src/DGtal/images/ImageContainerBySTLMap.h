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
 * @file ImageContainerBySTLMap.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * @author Guillaume Damiand
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/06/15
 *
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/13
 *
 * Header file for module ImageContainerBySTLMap.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImageContainerBySTLMap_RECURSES)
#error Recursive header files inclusion detected in ImageContainerBySTLMap.h
#else // defined(ImageContainerBySTLMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImageContainerBySTLMap_RECURSES

#if !defined ImageContainerBySTLMap_h
/** Prevents repeated inclusion of headers. */
#define ImageContainerBySTLMap_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <map>

#include "DGtal/base/Common.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/base/CowPtr.h"
#include "DGtal/base/Clone.h"
#include "DGtal/images/DefaultConstImageRange.h"
#include "DGtal/images/DefaultImageRange.h"
#include "DGtal/images/SetValueIterator.h"
#include "DGtal/base/CLabel.h"
#include "DGtal/kernel/domains/CDomain.h"

//////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
#pragma warning(disable : 4290)
#endif

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class ImageContainerBySTLMap
  /**
   * Description of class 'ImageContainerBySTLMap' <p>
   * Aim: Model of CImage implementing the association Point<->Value
   * using an STL map.
   *
   * Once constructed, the image is valid, i.e. every point of the
   * image domain has a value, which can be read and overwritten.
   * Note that the default value (returned for points that are not
   * stored in the underlying STL map) can be chosen by the user.
   *
   * As a model of concepts::CImage, this class provides two ways of accessing values:
   * - through the range of points returned by the domain() method
   * combined with the operator() that takes a point and returns its associated value.
   * - through the range of values returned by the range() method,
   * which can be used to directly iterate over the values of the image
   *
   * This class also provides a setValue() method and an output iterator,
   * which is returned by the outputIterator() method for writting purposes.
   *
   * @see testImage.cpp
   */

  template <typename TDomain, typename TValue>
  class ImageContainerBySTLMap:
    public std::map<typename TDomain::Point, TValue >
  {

  public:

    typedef ImageContainerBySTLMap<TDomain,TValue> Self;
    typedef std::map<typename TDomain::Point, TValue > Parent;

    /// domain
    BOOST_CONCEPT_ASSERT(( concepts::CDomain<TDomain> ));
    typedef TDomain Domain;
    typedef typename Domain::Point Point;
    typedef typename Domain::Vector Vector;
    typedef typename Domain::Integer Integer;
    typedef typename Domain::Size Size;
    typedef typename Domain::Dimension Dimension;
    typedef Point Vertex;

    // Pointer to the (const) Domain given at construction.
    typedef CowPtr< const Domain >  DomainPtr;

    /// static constants
    static const typename Domain::Dimension dimension;

    /// range of values
    BOOST_CONCEPT_ASSERT(( concepts::CLabel<TValue> ));
    typedef TValue Value;
    typedef DefaultConstImageRange<Self> ConstRange;
    typedef DefaultImageRange<Self> Range;

    /// output iterator
    typedef SetValueIterator<Self> OutputIterator;

    /////////////////// Data members //////////////////
  private:

    /// Shared pointer on the image domain,
    /// Since the domain is not mutable, not assignable,
    /// it is shared by all the copies of *this
    DomainPtr myDomainPtr;

    /// Default value
    Value myDefaultValue;

    /////////////////// standard services //////////////////

  public:

    /**
     * Constructor from a pointer to a domain.
     *
     * If Domain is a heavy type, consider giving instead a smart pointer on the domain (like CountedPtr).
     *
     * @param aDomain the image domain.
     * @param aValue a default value associated to the domain points
     * that are not contained in the underlying map.
     */
    ImageContainerBySTLMap( Clone<const Domain> aDomain, const Value& aValue = 0);

    /**
     * Copy operator
     *
     * @param other the object to copy.
     */
    ImageContainerBySTLMap(const ImageContainerBySTLMap& other);

    /**
     * Assignement operator
     *
     * @param other the object to copy.
     * @return this
     */
    ImageContainerBySTLMap& operator=(const ImageContainerBySTLMap& other);

    /**
     * Destructor.
     *
    */
    ~ImageContainerBySTLMap();


    /////////////////// Interface //////////////////

      /**
     * Get the value of an image at a given position given
     * by a Point.
     *
     * @pre the point must be in the domain
     *
     * @param aPoint the point.
     * @return the value at aPoint.
     */
    Value operator()(const Point & aPoint) const;

    /**
     * Set a value on an Image at a position specified by a Point.
     *
     * @pre @c it must be a point in the image domain.
     *
     * @param aPoint the point.
     * @param aValue the value.
     */
    void setValue(const Point &aPoint, const Value &aValue);


    /**
     * @return the domain associated to the image.
     */
    const Domain &domain() const;

    /**
     * @return the const range providing constant
     * iterators to iterate over the values of the image.
     */
    ConstRange constRange() const;

    /**
     * @return the range providing constant iterators
     * and output iterators on the values of the image.
     */
    Range range();

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;


    /**
     * @return the validity of the Image
     */
    bool isValid() const;

    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;


    /// built-in iterators
    typedef typename std::map<Point,Value>::iterator Iterator;
    typedef typename std::map<Point,Value>::const_iterator ConstIterator;
    typedef typename std::map<Point,Value>::reverse_iterator ReverseIterator;
    typedef typename std::map<Point,Value>::const_reverse_iterator ConstReverseIterator;

    /**
     * Construct a Iterator on the image
     *
     *
     * @return a Iterator      */
    OutputIterator outputIterator();


  };

  /**
   * Overloads 'operator<<' for displaying objects of class 'Image'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Image' to write.
   * @return the output stream after the writing.
   */
  template <typename TDomain, typename TValue>
  inline
  std::ostream&
  operator<< ( std::ostream & out,
               const ImageContainerBySTLMap<TDomain,TValue> & object )
  {
    object.selfDisplay ( out );
    return out;
  }


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions
#include "DGtal/images/ImageContainerBySTLMap.ih"
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImageContainerBySTLMap_h

#undef ImageContainerBySTLMap_RECURSES
#endif // else defined(ImageContainerBySTLMap_RECURSES)
