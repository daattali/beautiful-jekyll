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
 * @file DigitalSetFromMap.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/16
 *
 * Header file for module DigitalSetFromMap.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DigitalSetFromMap_RECURSES)
#error Recursive header files inclusion detected in DigitalSetFromMap.h
#else // defined(DigitalSetFromMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DigitalSetFromMap_RECURSES

#if !defined DigitalSetFromMap_h
/** Prevents repeated inclusion of headers. */
#define DigitalSetFromMap_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <map>
#include <string>
#include "DGtal/base/Common.h"
#include "DGtal/base/CowPtr.h"

#include "DGtal/base/BasicFunctors.h"
#include "DGtal/base/IteratorAdapter.h"
#include "DGtal/base/ConstIteratorAdapter.h"

//////////////////////////////////////////////////////////////////////////////


namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class DigitalSetFromMap
  /**
     Description of template class 'DigitalSetFromMap' <p>

     \brief Aim: An adapter for viewing an associative image container
     like ImageContainerBySTLMap as a simple digital set. 
     This class is merely based on an aliasing pointer on the image, 
     which must exists elsewhere.  

     Model of CDigitalSet.

     @tparam TMapImage type of associative image container
  */
  template <typename TMapImage>
  class DigitalSetFromMap
  {
  public:

    typedef TMapImage Image;
    typedef std::pair<const typename Image::Point, 
		      typename Image::Value> Pair;
    typedef DigitalSetFromMap<Image> Self; 

    // -------------------------- required types ------------------------------
    typedef typename Image::Domain Domain;
    typedef typename Domain::Point Point;
    typedef typename Domain::Size Size;

    typedef functors::Pair1st<Point> Functor; 
    typedef ConstIteratorAdapter<typename Image::ConstIterator, Functor, Point> ConstIterator;
    typedef ConstIteratorAdapter<typename Image::ConstIterator, Functor, Point> Iterator;

    // ------------------------- Protected Datas ------------------------------
  protected:

    /**
     * Aliasing pointer on the image
     */
    Image* myImgPtr;

    /**
     * Functor transforming pairs point-value into points
     */
    Functor myFun;

    /**
     * Default value for point insertion 
     */
    typename Image::Value myDefault;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~DigitalSetFromMap();

    /**
     * Constructor.
     * Link the adapter to an existing image.
     *
     * @param aImage any associative image container.
     * @param aDefaultValue value assigned to new points 
     * in the underlying image (0 by default). 
     */
    DigitalSetFromMap( Image& aImage, 
		       const typename Image::Value& aDefaultValue = 0);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    DigitalSetFromMap ( const DigitalSetFromMap & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    DigitalSetFromMap& operator= ( const DigitalSetFromMap & other );


    // ----------------------- Standard Set services --------------------------
  public:

    /**
     * @return the embedding domain.
     */
    const Domain & domain() const;

    /**
     * @return a counted pointer on the embedding domain.
     */
    CowPtr<Domain> domainPointer() const;

    /**
     * @return the number of elements in the set.
     */
    Size size() const;

    /**
     * @return 'true' iff the set is empty (no element).
     */
    bool empty() const;
     
    /**
     * Adds point [p] to this set.
     *
     * @param p any digital point.
     * @pre p should belong to the associated domain.
     */
    void insert( const Point & p );

    /**
     * Adds the collection of points specified by the two iterators to
     * this set.
     *
     * @param first the start point in the collection of Point.
     * @param last the last point in the collection of Point.
     * @pre all points should belong to the associated domain.
     */
    template <typename PointInputIterator>
    void insert( PointInputIterator first, PointInputIterator last );

    /**
     * Adds point [p] to this set if the point is not already in the
     * set.
     *
     * @param p any digital point.
     *
     * @pre p should belong to the associated domain.
     * @pre p should not belong to this.
     */
    void insertNew( const Point & p );

    /**
     * Adds the collection of points specified by the two iterators to
     * this set.
     *
     * @param first the start point in the collection of Point.
     * @param last the last point in the collection of Point.
     *
     * @pre all points should belong to the associated domain.
     * @pre each point should not belong to this.
     */
    template <typename PointInputIterator>
    void insertNew( PointInputIterator first, PointInputIterator last );

    /**
     * Removes point [p] from the set.
     * 
     * @param p the point to remove.
     * @return the number of removed elements (0 or 1).
     */
    Size erase( const Point & p );

    /**
     * Removes the point pointed by [it] from the set.
     * 
     * @param it an iterator on this set.
     * Note: generally faster than giving just the point.
     */
    void erase( Iterator it );

    /**
     * Removes the collection of points specified by the two iterators from
     * this set.
     *
     * @param first the start point in this set.
     * @param last the last point in this set.
     */
    void erase( Iterator first, Iterator last );

    /**
     * Clears the set.
     * @post this set is empty.
     */
    void clear();

    /**
     * @param p any digital point.
     * @return a constant iterator pointing on [p] if found, otherwise end().
     */
    ConstIterator find( const Point & p ) const;

    /**
     * @param p any digital point.
     * @return an iterator pointing on [p] if found, otherwise end().
     */
    Iterator find( const Point & p );

    /**
     * @return a const iterator on the first element in this set.
     */
    ConstIterator begin() const;

    /**
     * @return a const iterator on the element after the last in this set.
     */
    ConstIterator end() const;

    /**
     * @return an iterator on the first element in this set.
     */
    Iterator begin();

    /**
     * @return a iterator on the element after the last in this set.
     */
    Iterator end();

    /**
     * set union to left.
     * @param aSet any other set.
     * @tparam TDigitalSet a model of digital set. 
     */
    template< typename TDigitalSet >
    Self & operator+=
    ( const TDigitalSet & aSet );

    // ----------------------- Model of concepts::CPointPredicate -----------------------------
  public:

    /**
       @param p any point.
       @return 'true' if and only if \a p belongs to this set.
    */
    bool operator()( const Point & p ) const;

    // ----------------------- Other Set services -----------------------------
  public:
    
    /**
     * Fill a given set through the output iterator @a ito
     * with the complement of this set in the domain.
     * @param ito the output iterator
     * @tparam TOutputIterator a model of output iterator
     */
    template< typename TOutputIterator >
    void computeComplement(TOutputIterator& ito) const; 

    /**
     * Builds the complement in the domain of the set [other_set] in
     * this.
     *
     * @param otherSet defines the set whose complement is assigned to 'this'.
     * @tparam TDigitalSet a model of digital set. 
     */
    template< typename TDigitalSet >
    void assignFromComplement( const TDigitalSet & otherSet ); 
    
    /**
     * Computes the bounding box of this set.
     *
     * @param lower the first point of the bounding box (lowest in all
     * directions).
     * @param upper the last point of the bounding box (highest in all
     * directions).
     */
    void computeBoundingBox( Point & lower, Point & upper ) const;


    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;


  public:
    


    // --------------- CDrawableWithBoard2D realization ---------------------
  public:

    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;


    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Default Constructor.
     * Forbidden since a Domain is necessary for defining a set.
     */
    DigitalSetFromMap();

  private:


    // ------------------------- Internals ------------------------------------
  private:


  }; // end of class DigitalSetFromMap


  /**
   * Overloads 'operator<<' for displaying objects of class 'DigitalSetFromMap'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'DigitalSetFromMap' to write.
   * @return the output stream after the writing.
   */
  template <typename TMapImage>
  std::ostream&
  operator<< ( std::ostream & out, const DigitalSetFromMap<TMapImage> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/sets/DigitalSetFromMap.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DigitalSetFromMap_h

#undef DigitalSetFromMap_RECURSES
#endif // else defined(DigitalSetFromMap_RECURSES)
