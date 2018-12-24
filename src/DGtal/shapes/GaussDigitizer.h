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
 * @file GaussDigitizer.h
 * @brief Computes the Gauss digitization of some Euclidean shape.
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/06/29
 *
 * Header file for module GaussDigitizer.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testGaussDigitizer.cpp, testTrueLocalEstimator.cpp, testLengthEstimators.cpp
 */

#if defined(GaussDigitizer_RECURSES)
#error Recursive header files inclusion detected in GaussDigitizer.h
#else // defined(GaussDigitizer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define GaussDigitizer_RECURSES

#if !defined GaussDigitizer_h
/** Prevents repeated inclusion of headers. */
#define GaussDigitizer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/base/CountedConstPtrOrConstPtr.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/kernel/RegularPointEmbedder.h"
#include "DGtal/shapes/CEuclideanOrientedShape.h"
#include "DGtal/shapes/CEuclideanBoundedShape.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class GaussDigitizer
  /**
     Description of template class 'GaussDigitizer' <p> \brief Aim: A
     class for computing the Gauss digitization of some Euclidean
     shape, i.e. its intersection with some \f$ h_1 Z \times h_2 Z
     \times \cdots \times h_n Z \f$. Note that the real point (0,...,0)
     is mapped onto the digital point (0,...,0).
     
     GaussDigitizer is a model of CDigitalEuclideanShape and
     CDigitalBoundedShape. It is thus a model of concepts::CPointPredicate.
     A Gauss digitizer owns a RegularPointEmbedder, a model of CPointEmbedder.

     @tparam TSpace the type of digital Space where the digitized
     object lies.

     @tparam TEuclideanShape a model of CEuclideanOrientedShape and CEuclideanBoundedShape
   */
  template <typename TSpace, typename TEuclideanShape>
  class GaussDigitizer
  {
    // ----------------------- Standard services ------------------------------
  public:
    typedef TSpace Space;
    typedef typename Space::Integer Integer;
    typedef typename Space::Point Point;
    typedef typename Space::Vector Vector;
    typedef typename Space::RealPoint RealPoint;
    typedef typename Space::RealPoint RealVector;
    typedef TEuclideanShape EuclideanShape;
    typedef HyperRectDomain<Space> Domain;
    typedef RegularPointEmbedder<Space> PointEmbedder;

    BOOST_CONCEPT_ASSERT(( concepts::CEuclideanOrientedShape<TEuclideanShape> ));
   
    /**
     * Destructor.
     */
    ~GaussDigitizer();

    /**
     * Constructor. The object is not valid.
     */
    GaussDigitizer();

    /**
     * Assignment. Required by concepts::CPointPredicate.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    GaussDigitizer & operator= ( const GaussDigitizer & other );

    /**
       @param shape the digitizer now references the given shape.
    */
    void attach( ConstAlias<EuclideanShape> shape );

    /**
       Initializes the digital bounds of the digitizer so as to cover
       at least the space specified by [xLow] and [xUp]. The real
       value [gridStep] specifies the same grid step in every
       direction.

       @param xLow Euclidean lower bound for the digitizer.
       @param xUp Euclidean upper bound for the digitizer.

       @param gridStep the grid step (distance between two embedded
       adjacent digital points) identical in every direction.
    */
    void init( const RealPoint & xLow, const RealPoint & xUp, 
               typename RealVector::Component gridStep );

    /**
       Initializes the digital bounds of the digitizer so as to cover
       at least the space specified by [xLow] and [xUp]. The real
       vector [gridSteps] specifies the grid steps in each
       direction.

       @param xLow Euclidean lower bound for the digitizer.
       @param xUp Euclidean upper bound for the digitizer.

       @param gridSteps the grid steps in each direction.
    */
    void init( const RealPoint & xLow, const RealPoint & xUp, 
         const RealVector & gridSteps );

    /**
       @return the associated point embedder.
    */
    const PointEmbedder & pointEmbedder() const;

    /**
       @return the domain chosen for the digitizer.
       @see init
    */
    Domain getDomain() const;
    
    /**
       @param p any point in the Euclidean space.
       @return the digital point floor( p / gridSteps ).
    */
    Point floor( const RealPoint & p ) const;

    /**
       @param p any point in the Euclidean space.
       @return the digital point ceil( p / gridSteps ).
    */
    Point ceil( const RealPoint & p ) const;

    /**
       @param p any point in the Euclidean space.

       @return the digital point round( p / gridSteps ), i.e. the
       "closest" digital point.
    */
    Point round( const RealPoint & p ) const;

    /**
     * Map a digital point to its corresponding point in the Eucldiean
     * space.
     *
     *   @param p any digital point in the digital space.
     *   @return its centroid embedding in the Euclidean space.
     */
    RealPoint embed( const Point & p ) const;

    /** 
     * Orientation method to match with CDigitalOrientedShape concept.
     * 
     * @param p  a digital point
     * 
     * @return negative orientation if the point is inside the shape,
     * 0 if it is on the shape and positive orientation otherwise.
     */
    Orientation orientation(const Point &p) const
    { 
      return myEShape->orientation(embed(p));
    }

    /**
     * @param p any point in the digital plane.
     *
     * @return 'true' if the point is inside the shape, 'false' if it
     * is strictly outside.
     */
    bool operator()( const Point & p ) const;

    /**
       @return the lowest admissible digital point.
       @see init
    */
    const Point & getLowerBound() const;

    /**
       @return the highest admissible digital point.
       @see init
    */
    const Point & getUpperBound() const;
    
    /**
       @return the resolution in each direction.
    */
    Vector resolution() const;

    /**
       @return the grid steps in each direction.
    */
    RealVector gridSteps() const;


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
    /// The referenced shape or 0 if not initialized.
    CountedConstPtrOrConstPtr<EuclideanShape> myEShape;

    /// The embedder
    RegularPointEmbedder<Space> myPointEmbedder;

    /// Digital lowest point 
    Point myLowerPoint;

    /// Digital uppest point 
    Point myUpperPoint;
    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  private:

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class GaussDigitizer


  /**
   * Overloads 'operator<<' for displaying objects of class 'GaussDigitizer'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'GaussDigitizer' to write.
   * @return the output stream after the writing.
   */
  template <typename TSpace, typename TEuclideanShape>
  std::ostream&
  operator<< ( std::ostream & out, 
         const GaussDigitizer<TSpace,TEuclideanShape> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/GaussDigitizer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined GaussDigitizer_h

#undef GaussDigitizer_RECURSES
#endif // else defined(GaussDigitizer_RECURSES)
