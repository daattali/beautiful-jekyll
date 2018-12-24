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
 * @file SpatialCubicalSubdivision.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2014/02/11
 *
 * Header file for module SpatialCubicalSubdivision.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SpatialCubicalSubdivision_RECURSES)
#error Recursive header files inclusion detected in SpatialCubicalSubdivision.h
#else // defined(SpatialCubicalSubdivision_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SpatialCubicalSubdivision_RECURSES

#if !defined SpatialCubicalSubdivision_h
/** Prevents repeated inclusion of headers. */
#define SpatialCubicalSubdivision_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/base/Clone.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class SpatialCubicalSubdivision
  /**
     Description of template class 'SpatialCubicalSubdivision' <p> \brief
     Aim: This class is a data structure that subdivides a rectangular
     domains into cubical domains of size \f$ r^n \f$ in order to
     store points into different bins (each cubical domain is a bin,
     characterized by one coordinate). This data structure may be used
     for proximity queries, generally to get the points at distance
     \a r from a given point.

     Bins are characterized by one Point and are organized as a
     rectangular domain with lowest bin at coordinates (0,...,0).
     
     @tparam TSpace the digital space, a model of CSpace.

     Model of CopyConstructible
   */
  template <typename TSpace>
  class SpatialCubicalSubdivision
  {
    BOOST_CONCEPT_ASSERT(( concepts::CSpace< TSpace > ));
  public:
    typedef TSpace Space;
    typedef typename Space::Point Point;
    typedef typename Space::Vector Vector;
    typedef typename Point::Coordinate Coordinate;
    typedef HyperRectDomain<Space> Domain;
    typedef std::vector<Point> Storage;
    typedef ImageContainerBySTLVector<Domain,Storage*> StorageArray;
    typedef typename StorageArray::ConstRange BinConstRange;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~SpatialCubicalSubdivision();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    SpatialCubicalSubdivision ( const SpatialCubicalSubdivision & other );

    /**
       Constructor from rectangular domain given by lowest and uppermost point.
       
       @param lo the lowest point of the domain of interest.
       @param up the uppermost point of the domain of interest.
       @param size the edge size of each cubical bin (an integer >= 2 ).
    */
    SpatialCubicalSubdivision( Point lo, Point up, Coordinate size );

    /// @return the rectangular domain of interest
    const Domain& domain() const;

    /// @return the rectangular domain of bins, which is a coarser grid than domain().
    const Domain& binDomain() const;

    /**
       @param p any point within domain().
       @return the bin in which lies \a p.
    */
    Point bin( Point p ) const;

    /**
       @param b any valid bin of binDomain().
       @return its lowest possible point.
    */
    Point lowest( Point b ) const;

    /**
       @param b any valid bin of binDomain().
       @return its uppermost possible point.
    */
    Point uppermost( Point b ) const;

    /**
       Pushes the point \a p into its bin (beware, if you push the same
       point several times, there are as many copies of this point
       into the bin).

       @param p any point within domain().
    */
    void push( const Point& p );

    /**
       Pushes the range of points [it, itE) into the corresponding bins
       (beware, if you push the same point several times, there are as
       many copies of this point into its bin).

       @tparam PointConstIterator the type of const iterator on point.
       @param it an iterator pointing at the beginning of the range.
       @param itE an iterator pointing after the end of the range.
    */
    template <typename PointConstIterator>
    void push( PointConstIterator it, PointConstIterator itE );

    /**
       Pushes back in \a pts all the points in the bin domain [\a
       bin_lo, \a bin_up] which satisfy the predicate \a pred.
       
       @tparam PointPredicate the type of a point predicate.
       @param[out] pts the vector where points are pushed back for output.
       @param bin_lo the lowest bin of the bin domain.
       @param bin_up the uppermost bin of the bin domain.
       @param pred an arbitrary predicate on point.
    */
    template <typename PointPredicate>
    void getPoints( std::vector<Point> & pts, 
                    Point bin_lo, Point bin_up, const PointPredicate & pred ) const;

    /**
       Pushs back in \a pts all the points in the bin domain [\a
       bin_lo, \a bin_up].
       
       @param[out] pts the vector where points are pushed back for output.
       @param bin_lo the lowest bin of the bin domain.
       @param bin_up the uppermost bin of the bin domain.
    */
    void getPoints( std::vector<Point> & pts, 
                    Point bin_lo, Point bin_up ) const;

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

    // ------------------------- Protected Datas ------------------------------
  protected:
    
    /// the rectangular domain representing the useful points of the space.
    Domain myDomain;
    /// the edge size of each bin.
    Coordinate mySize;
    /// the image that associates to each bin its dyn. allocated
    /// vector of points. If 0, no point is stored in this bin.
    StorageArray myArray;
    // ------------------------- Private Datas --------------------------------
  private:
    /// a precomputed point to improve performance of uppermost() method.
    Point myDiag;

    // ------------------------- Hidden services ------------------------------
  protected:

    // ------------------------- Internals ------------------------------------
  private:

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * forbidden.
     */
    SpatialCubicalSubdivision & operator= ( const SpatialCubicalSubdivision & other );

  }; // end of class SpatialCubicalSubdivision


  /**
   * Overloads 'operator<<' for displaying objects of class 'SpatialCubicalSubdivision'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'SpatialCubicalSubdivision' to write.
   * @return the output stream after the writing.
   */
  template <typename TSpace>
  std::ostream&
  operator<< ( std::ostream & out, const SpatialCubicalSubdivision<TSpace> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/tools/SpatialCubicalSubdivision.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SpatialCubicalSubdivision_h

#undef SpatialCubicalSubdivision_RECURSES
#endif // else defined(SpatialCubicalSubdivision_RECURSES)
