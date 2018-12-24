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
 * @file DigitalSetByAssociativeContainer.h
 *
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire LIRIS  (CNRS, UMR 5205), Université de Lyon, France
 *
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @author Sebastien Fourey (\c Sebastien.Fourey@greyc.ensicaen.fr )
 * Groupe de Recherche en Informatique, Image, Automatique et
 * Instrumentation de Caen - GREYC (CNRS, UMR 6072), ENSICAEN, France
 *
 * @date 2010/07/01
 *
 * Header file for module DigitalSetByAssociativeContainer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DigitalSetByAssociativeContainer_RECURSES)
#error Recursive header files inclusion detected in DigitalSetByAssociativeContainer.h
#else // defined(DigitalSetByAssociativeContainer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DigitalSetByAssociativeContainer_RECURSES

#if !defined DigitalSetByAssociativeContainer_h
/** Prevents repeated inclusion of headers. */
#define DigitalSetByAssociativeContainer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <set>
#include <string>
#include "DGtal/base/Common.h"
#include "DGtal/base/CowPtr.h"
#include "DGtal/base/Clone.h"
#include "DGtal/base/Alias.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/base/CSTLAssociativeContainer.h"
//////////////////////////////////////////////////////////////////////////////

//#include "DGtal/io/Display3D.h"


namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class DigitalSetByAssociativeContainer
  /**
    Description of template class 'DigitalSetByAssociativeContainer' <p>

    \brief Aim: A wrapper class around a STL associative container for
    storing sets of digital points within some given domain.
   
    Model of CDigitalSet.

    @since 0.7 Domains are now hold with copy on write pointers and no more
    only aliased. The problem was related to returning sets with a
    locally constructed domain. With CowPtr, you are sure that the
    domain remains valid during the lifetime of your set.
   
   * @tparam TDomain type of domain on which the set will be defined (model of concepts::CDomain).
   * @tparam TContainer STL associative container to store points (model of concepts::CSTLAssociativeContainer).
   *
   */
  template <typename TDomain, typename TContainer >
  class DigitalSetByAssociativeContainer
  {
  public:
    
    ///Domain type.
    typedef TDomain Domain;
  
    ///Container type.
    typedef TContainer Container;
    
    ///Self Type.
    typedef DigitalSetByAssociativeContainer<Domain, Container> Self;
    ///Type of digital space.
    typedef typename Domain::Space Space;
    ///Type of points in the space.
    typedef typename Domain::Point Point;
    ///Iterator type of the container.
    typedef typename Container::iterator Iterator;
    ///ConstIterator type of the container;
    typedef typename Container::const_iterator ConstIterator;
    ///Value type of the container.
    typedef typename Container::value_type value_type;
    ///Size type of the container;
    typedef typename Container::size_type Size;
    
    ///Concept checks
    BOOST_CONCEPT_ASSERT(( concepts::CDomain< TDomain > ));
    BOOST_CONCEPT_ASSERT(( concepts::CSTLAssociativeContainer< TContainer > ));
    BOOST_STATIC_ASSERT(( boost::is_same<typename Container::key_type, Point>::value ));
    
    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~DigitalSetByAssociativeContainer();

    /**
     * Constructor.
     * Creates the empty set in the domain [d].
     *
     * @param d any domain.
     */
    DigitalSetByAssociativeContainer( Clone<Domain> d );

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    DigitalSetByAssociativeContainer ( const DigitalSetByAssociativeContainer & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    DigitalSetByAssociativeContainer & operator= ( const DigitalSetByAssociativeContainer & other );

    /**
     * @return the embedding domain.
     */
    const Domain & domain() const;

    /**
     * @return a copy on write pointer on the embedding domain.
     */
    CowPtr<Domain> domainPointer() const;

    // ----------------------- Standard Set services --------------------------
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
     */
    DigitalSetByAssociativeContainer<Domain, Container> & operator+=
    ( const DigitalSetByAssociativeContainer<Domain, Container> & aSet );

    // ----------------------- Model of concepts::CPointPredicate -----------------------------
  public:

    /**
       @param p any point.
       @return 'true' if and only if \a p belongs to this set.
    */
    bool operator()( const Point & p ) const;

    // ----------------------- Other Set services -----------------------------

    /**
     * Computes the complement in the domain of this set
     * @param ito an output iterator
     * @tparam TOutputIterator a model of output iterator
     */
   template< typename TOutputIterator >
    void computeComplement(TOutputIterator& ito) const;

    /**
     * Builds the complement in the domain of the set [other_set] in
     * this.
     *
     * @param other_set defines the set whose complement is assigned to 'this'.
     */
    void assignFromComplement( const DigitalSetByAssociativeContainer<Domain, Container> & other_set );

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

    // ------------------------- Protected Datas ------------------------------
  protected:

    /**
     * The associated domain. The pointed domain may be changed but it
     * remains valid during the lifetime of the set.
     */
    CowPtr<Domain> myDomain;

    /**
     * The container storing the points of the set.
     */
    Container mySet;

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
    DigitalSetByAssociativeContainer();

  }; // end of class DigitalSetByAssociativeContainer


  /**
   * Overloads 'operator<<' for displaying objects of class 'DigitalSetByAssociativeContainer'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'DigitalSetByAssociativeContainer' to write.
   * @return the output stream after the writing.
   */
  template <typename Domain, typename Container>
  std::ostream&
  operator<< ( std::ostream & out, const DigitalSetByAssociativeContainer<Domain, Container> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/sets/DigitalSetByAssociativeContainer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DigitalSetByAssociativeContainer_h

#undef DigitalSetByAssociativeContainer_RECURSES
#endif // else defined(DigitalSetByAssociativeContainer_RECURSES)
