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
 * @file VoronoiCovarianceMeasure.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2014/02/09
 *
 * Header file for module VoronoiCovarianceMeasure.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(VoronoiCovarianceMeasure_RECURSES)
#error Recursive header files inclusion detected in VoronoiCovarianceMeasure.h
#else // defined(VoronoiCovarianceMeasure_RECURSES)
/** Prevents recursive inclusion of headers. */
#define VoronoiCovarianceMeasure_RECURSES

#if !defined VoronoiCovarianceMeasure_h
/** Prevents repeated inclusion of headers. */
#define VoronoiCovarianceMeasure_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <cmath>
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/math/BasicMathFunctions.h"
#include "DGtal/kernel/BasicPointPredicates.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/math/linalg/SimpleMatrix.h"
#include "DGtal/kernel/Point2ScalarFunctors.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/geometry/volumes/distance/VoronoiMap.h"
#include "DGtal/geometry/tools/SpatialCubicalSubdivision.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class VoronoiCovarianceMeasure
  /**
   * Description of template class 'VoronoiCovarianceMeasure' <p>
   * \brief Aim: This class precomputes the Voronoi Covariance Measure
   * of a set of points. It can compute the covariance measure of an
   * arbitrary function with given support.
   *
   * You may obtain the whole sequence (Point,VCM) by accessing the
   * map \ref vcmMap.
   *
   * @note Documentation in \ref moduleVCM_sec2.
   *
   * @tparam TSpace type of Digital Space (model of CSpace).
   *
   * @tparam TSeparableMetric a model of CSeparableMetric used for
   * computing the Voronoi map (e.g. Euclidean metric is
   * DGtal::ExactPredicateLpSeparableMetric<TSpace, 2> )
   */
  template <typename TSpace, typename TSeparableMetric>
  class VoronoiCovarianceMeasure
  {
    BOOST_CONCEPT_ASSERT(( concepts::CSpace< TSpace > ));
    BOOST_CONCEPT_ASSERT(( concepts::CSeparableMetric<TSeparableMetric> ));

  public:
    typedef TSpace Space;                         ///< the type of digital space
    typedef TSeparableMetric Metric;              ///< the type of metric
    typedef typename Space::Point Point;          ///< the type of digital point
    typedef typename Space::Size Size;            ///< the type for counting elements
    typedef typename Space::Integer Integer;      ///< the type of each digital point coordinate, some integral type
    typedef DGtal::HyperRectDomain<Space> Domain; ///< the type of rectangular domain of the VCM.
    typedef DGtal::ImageContainerBySTLVector<Domain,bool> CharacteristicSet; ///< the type of a binary image that is the characteristic function of K.
    typedef DGtal::SpatialCubicalSubdivision<Space> ProximityStructure; ///< the structure used for proximity queries.

    /**
       A predicate that returns 'true' whenever the given binary image contains 'true'.
       Model of concepts::CPointPredicate.
       @note Internal use.
    */
    struct CharacteristicSetPredicate {
      typedef CharacteristicSetPredicate Self;
      typedef typename Space::Point Point;          ///< the type of digital point
      CharacteristicSetPredicate() : ptrSet( 0 ) {}
      CharacteristicSetPredicate( ConstAlias<CharacteristicSet> aSet) : ptrSet( &aSet ) {}
      CharacteristicSetPredicate( const Self& other ) : ptrSet( other.ptrSet ) {}
      Self& operator=( const Self& other ) { ptrSet = other.ptrSet; return *this; }
      bool operator()( const Point& p ) const
      { 
        ASSERT( ptrSet != 0 );
        return (*ptrSet)( p );
      }
    private:
      const CharacteristicSet* ptrSet;
    };
    typedef DGtal::functors::NotPointPredicate<CharacteristicSetPredicate> NotPredicate; ///< the type of the point predicate used by the voronoi map.
    typedef DGtal::VoronoiMap<Space, NotPredicate, Metric > Voronoi; ///< the type of the Voronoi map.

    typedef double Scalar;                                    ///< the type for "real" numbers.
    typedef DGtal::SimpleMatrix< Scalar,
                                 Space::dimension, 
                                 Space::dimension > MatrixNN; ///< the type for nxn matrix of real numbers.
    typedef typename MatrixNN::RowVector VectorN;             ///< the type for N-vector of real numbers
    typedef std::vector<Point> PointContainer;                ///< the list of points
    typedef std::map<Point,MatrixNN> Point2MatrixNN;          ///< Associates a matrix to points.

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor.
     *
     * @param _R the offset radius for the set of points. Voronoi cells
     * are intersected with this offset. The unit corresponds to a step in the digital space.
     *
     * @param _r (an upper bound of) the radius of the support of
     * forthcoming kernel functions (\f$ \chi_r \f$). The unit
     * corresponds to a step in the digital space. This parameter is
     * used for preparing the data structure that answers to proximity
     * queries.
     *
     * @param aMetric an instance of the metric.
     * @param verbose if 'true' displays information on ongoing computation.
     */
    VoronoiCovarianceMeasure( double _R, double _r, Metric aMetric = Metric(), bool verbose = false );

    /**
     * Destructor.
     */
    ~VoronoiCovarianceMeasure();

    /// @return the parameter R in the VCM, i.e. the offset radius for
    /// the compact set K.
    Scalar R() const;
    /// @return the parameter r in VCM(chi_r), i.e. an upper bound for
    /// the diameter of the support of kernel functions.
    Scalar r() const;
 
    /**
       Cleans intermediate data structure likes the characteristic set and the voronoi map.
       @note Further calls to voronoiMap are no more valid.
    */
    void clean();

    /**
       Computes the Voronoi Covariance Measure for the set of points given by range [itb,ite)
       
       @tparam PointInputIterator an input iterator on digital points.
       @param itb the start of the range
       @param ite the end of the range.
       @pre \a itb != \a ite.
       @pre [itb,ite) is a valid range (\a ite can be reached from \a itb).
    */
    template <typename PointInputIterator>
    void init( PointInputIterator itb, PointInputIterator ite );

    /// @return the domain of computation
    const Domain& domain() const;

    /// @return the current Voronoi map 
    /// @pre init must have been called before.
    const Voronoi& voronoiMap() const;

    /// @return the Voronoi Covariance Matrix of each Voronoi cell as
    /// a map Point -> Matrix
    /// @note empty if \ref init has not been called.
    const Point2MatrixNN& vcmMap() const;

    /**
    Computes the Voronoi Covariance Measure of the function \a chi_r.
    
    @tparam Point2ScalarFunction the type of a functor
    Point->Scalar. For instance functors::HatPointFunction and
    functors::BallConstantPointFunction are models of this type.
    
    @param chi_r the kernel function whose support is included in
    the cube centered on the origin with edge size 2r (see \ref
    VoronoiCovarianceMeasure).
    
    @param p the point where the kernel function is moved. It must lie within domain.
    */
    template <typename Point2ScalarFunction>
    MatrixNN measure( Point2ScalarFunction chi_r, Point p ) const;

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
  private:
    // ------------------------- Private Datas --------------------------------
  private:

    /// The parameter R in the VCM, i.e. the offset radius for the compact set K.
    double myBigR;  
    /// The parameter r in VCM(chi_r), i.e. an upper bound for the
    /// diameter of the support of kernel functions.
    double mySmallR;  
    /// The metric chosen for the Voronoi map.
    Metric myMetric;
    /// Tells if it is verbose mode.
    bool myVerbose;
    /// The domain in which all computations are done.
    Domain myDomain;
    /// A binary image that defines the characteristic set of K.
    CharacteristicSet* myCharSet;
    /// Stores the voronoi map.
    Voronoi* myVoronoi;
    /// The map point -> VCM
    Point2MatrixNN myVCM;
    /// The structure used for proximity queries.
    ProximityStructure* myProximityStructure;

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    VoronoiCovarianceMeasure();

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    VoronoiCovarianceMeasure ( const VoronoiCovarianceMeasure & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    VoronoiCovarianceMeasure & operator= ( const VoronoiCovarianceMeasure & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class VoronoiCovarianceMeasure


  /**
   * Overloads 'operator<<' for displaying objects of class 'VoronoiCovarianceMeasure'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'VoronoiCovarianceMeasure' to write.
   * @return the output stream after the writing.
   */
  template <typename TSpace, typename TSeparableMetric>
  std::ostream&
  operator<< ( std::ostream & out, 
               const VoronoiCovarianceMeasure<TSpace, TSeparableMetric> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/volumes/estimation/VoronoiCovarianceMeasure.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined VoronoiCovarianceMeasure_h

#undef VoronoiCovarianceMeasure_RECURSES
#endif // else defined(VoronoiCovarianceMeasure_RECURSES)
