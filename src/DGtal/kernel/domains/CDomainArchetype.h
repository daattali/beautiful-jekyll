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
 * @file CDomainArchetype.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/01
 *
 * Header file for module CDomainArchetype.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDomainArchetype_RECURSES)
#error Recursive header files inclusion detected in CDomainArchetype.h
#else // defined(CDomainArchetype_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDomainArchetype_RECURSES

#if !defined CDomainArchetype_h
/** Prevents repeated inclusion of headers. */
#define CDomainArchetype_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <set>
#include <string>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/domains/CDomain.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // template class CDomainArchetype
  /**
    Description of template class 'CDomainArchetype' <p>
    @ingroup Archetypes 
    @brief Aim: The archetype of a class that represents a digital
    domain, i.e. a non mutable subset of points of the given digital
    space.

    Archetype of CDomain.
   */
  template <typename TSpace>
  class CDomainArchetype
  {
  public:

    // ----------------------- associated types -------------------------------
  public:
    typedef CDomainArchetype<TSpace> Domain;
    typedef TSpace Space;
    typedef typename Space::Integer Integer;
    typedef typename Space::Point Point;
    typedef typename Space::Vector Vector;
    typedef typename Space::Size Size;
    typedef typename Space::Dimension Dimension;
    typedef CConstBidirectionalIteratorArchetype<Point> ConstIterator;
    /**
       @todo DigitalSetPredicate
    */
    typedef int Predicate;
    /**
       @todo DigitalSet
    */
    typedef int DigitalSet;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~CDomainArchetype() {}

    /**
     * Coonstructor from set.
     * @param aSet the digital set.
     */
    CDomainArchetype ( const DigitalSet & aSet ) {}


    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    CDomainArchetype ( const CDomainArchetype & other ) {}

    // ----------------------- Domain services --------------------------------
  public:

    /**
     * @return an iterator on the first element of the domain.
     **/
    ConstIterator begin(const Point &aPoint) const 
    { return DummyObject<ConstIterator>::get(); }

    /**
     * @return an iterator on the first element of the domain.
     **/
    ConstIterator begin() const 
    { return DummyObject<ConstIterator>::get(); }

    /**
     * @return an iterator on the element after the last of the domain.
     **/
    ConstIterator end() const
    { return DummyObject<ConstIterator>::get(); }

    /**
     * Returns the lowest point of the space diagonal.
     *
     **/
    const Point &lowerBound() const
    { return DummyObject<Point>::get(); }

    /**
     * Returns the highest point of the space diagonal.
     *
     **/
    const Point &upperBound() const
    { return DummyObject<Point>::get(); }

    /**
     * Returns the size.
     *
     **/
    Size size() const
    { return DummyObject<Size>::get(); }

    /**
     * @param p any point.
     * @return 'true' if point [p] is inside this domain.
     */
    bool isInside( const Point & p ) const
    { return true; }


    /**
     * @return a const reference to the "IsInside" predicate.
     */
    const Predicate & predicate() const
    { return DummyObject<Predicate>::get(); }


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

  }; // end of class CDomainArchetype
  }
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDomainArchetype_h

#undef CDomainArchetype_RECURSES
#endif // else defined(CDomainArchetype_RECURSES)


