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

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif


/**
 * @file CDigitalSetArchetype.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/01
 *
 * Header file for module CDigitalSetArchetype.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDigitalSetArchetype_RECURSES)
#error Recursive header files inclusion detected in CDigitalSetArchetype.h
#else // defined(CDigitalSetArchetype_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDigitalSetArchetype_RECURSES

#if !defined CDigitalSetArchetype_h
/** Prevents repeated inclusion of headers. */
#define CDigitalSetArchetype_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <set>
#include <string>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/kernel/sets/CDigitalSet.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // template class CDigitalSetArchetype
  /**
    Description of template class 'CDigitalSetArchetype' <p>

    @ingroup Archetypes
    @brief Aim: The archetype of a container class for storing sets of
    digital points within some given domain.

    Archetype of CDigitalSet.
   */
  template <typename TDomain>
  class CDigitalSetArchetype
  {
  public:
    typedef TDomain Domain;
    typedef typename Domain::Point Point;
    typedef typename Domain::Size Size;
    //typedef boost::bidirectional_iterator_archetype<Point> Iterator;
    typedef CSinglePassIteratorArchetype<Point> Iterator;
    typedef Iterator ConstIterator;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~CDigitalSetArchetype() {}

    /**
     * Constructor.
     * Creates the empty set in the domain [d].
     *
     * @param d any domain.
     */
    CDigitalSetArchetype( const Domain & d ) {}

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    CDigitalSetArchetype ( const CDigitalSetArchetype & other ) {}

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    CDigitalSetArchetype & operator= ( const CDigitalSetArchetype & other ) 
    { return *this; }

    /**
     * @return the embedding domain.
     */
    const Domain & domain() const { return DummyObject<Domain>::get(); }

    /**
     * @return the embedding domain.
     */
    CowPtr<Domain> domainPointer() const { return DummyObject< CowPtr<Domain> >::get(); }

    // ----------------------- Standard Set services --------------------------
  public:

    /**
     * @return the number of elements in the set.
     */
    Size size() const { return 0; }

    /**
     * @return 'true' iff the set is empty (no element).
     */
    bool empty() const { return true; }
     
    /**
     * Adds point [p] to this set.
     *
     * @param p any digital point.
     * @pre p should belong to the associated domain.
     */
    void insert( const Point & p ) {}

    /**
     * Adds the collection of points specified by the two iterators to
     * this set.
     *
     * @param first the start point in the collection of Point.
     * @param last the last point in the collection of Point.
     * @pre all points should belong to the associated domain.
     */
    template <typename PointInputIterator>
    void insert( PointInputIterator first, PointInputIterator last ) {}

    /**
     * Adds point [p] to this set if the point is not already in the
     * set.
     *
     * @param p any digital point.
     *
     * @pre p should belong to the associated domain.
     * @pre p should not belong to this.
     */
    void insertNew( const Point & p ) {}

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
    void insertNew( PointInputIterator first, PointInputIterator last ) {}

    /**
     * Removes point [p] from the set.
     * 
     * @param p the point to remove.
     * @return the number of removed elements (0 or 1).
     */
    Size erase( const Point & p ) { return 0; }

    /**
     * Removes the point pointed by [it] from the set.
     * 
     * @param it an iterator on this set.
     * Note: generally faster than giving just the point.
     */
    void erase( Iterator it ) {}

    /**
     * Removes the collection of points specified by the two iterators from
     * this set.
     *
     * @param first the start point in this set.
     * @param last the last point in this set.
     */
    void erase( Iterator first, Iterator last ) {}

    /**
     * Clears the set.
     * @post this set is empty.
     */
    void clear() {}

    /**
     * @param p any digital point.
     */
    ConstIterator find( const Point & p ) const 
    { return DummyObject<ConstIterator>::get(); }

    /**
     * @param p any digital point.
     * @return an iterator pointing on [p] if found, otherwise end().
     */
    Iterator find( const Point & p )
    { return DummyObject<Iterator>::get(); }

    /**
     * @return a const iterator on the first element in this set.
     */
    ConstIterator begin() const
    { return DummyObject<ConstIterator>::get(); }

    /**
     * @return a const iterator on the element after the last in this set.
     */
    ConstIterator end() const
    { return DummyObject<ConstIterator>::get(); }

    /**
     * @return an iterator on the first element in this set.
     */
    Iterator begin()
    { return DummyObject<Iterator>::get(); }

    /**
     * @return a iterator on the element after the last in this set.
     */
    Iterator end()
    { return DummyObject<Iterator>::get(); }

    /**
     * set union to left.
     * @param aSet any other set.
     */
    CDigitalSetArchetype<Domain> & operator+=
    ( const CDigitalSetArchetype<Domain> & aSet )
    { return *this; }

    // ----------------------- Model of concepts::CPointPredicate -----------------------------
  public:

    /**
       @param p any point.
       @return 'true' if and only if \a p belongs to this set.
    */
    bool operator()( const Point & p ) const
    { return p == p; }

    // ----------------------- Other Set services -----------------------------
  public:
    
    /**
     * Computes the complement in the domain of this set
     * @param ito an output iterator
     * @tparam TOutputIterator a model of output iterator
     */
   template< typename TOutputIterator >
    void computeComplement(TOutputIterator& ito) const {}

    /**
     * Builds the complement in the domain of the set [other_set] in
     * this.
     *
     * @param other_set defines the set whose complement is assigned to 'this'.
     */
    void assignFromComplement( const CDigitalSetArchetype<Domain> & other_set )
    {}
    
    /**
     * Computes the bounding box of this set.
     *
     * @param lower the first point of the bounding box (lowest in all
     * directions).
     * @param upper the last point of the bounding box (highest in all
     * directions).
     */
    void computeBoundingBox( Point & lower, Point & upper ) const {}


    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const {}

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const { return true; }


  }; // end of class CDigitalSetArchetype
  }
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDigitalSetArchetype_h

#undef CDigitalSetArchetype_RECURSES
#endif // else defined(CDigitalSetArchetype_RECURSES)


