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
 * @file VoronoiCovarianceMeasureOnDigitalSurface.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2014/02/13
 *
 * Header file for module VoronoiCovarianceMeasureOnDigitalSurface.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(VoronoiCovarianceMeasureOnDigitalSurface_RECURSES)
#error Recursive header files inclusion detected in VoronoiCovarianceMeasureOnDigitalSurface.h
#else // defined(VoronoiCovarianceMeasureOnDigitalSurface_RECURSES)
/** Prevents recursive inclusion of headers. */
#define VoronoiCovarianceMeasureOnDigitalSurface_RECURSES

#if !defined VoronoiCovarianceMeasureOnDigitalSurface_h
/** Prevents repeated inclusion of headers. */
#define VoronoiCovarianceMeasureOnDigitalSurface_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedConstPtrOrConstPtr.h"
#include "DGtal/kernel/Point2ScalarFunctors.h"
#include "DGtal/math/linalg/EigenDecomposition.h"
#include "DGtal/topology/CDigitalSurfaceContainer.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/geometry/volumes/distance/CSeparableMetric.h"
#include "DGtal/geometry/volumes/estimation/VoronoiCovarianceMeasure.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /// Possible embeddings for surfel as point(s)
  enum Surfel2PointEmbedding { Pointels = 0, InnerSpel = 1, OuterSpel = 2 };

  /////////////////////////////////////////////////////////////////////////////
  // template class VoronoiCovarianceMeasureOnDigitalSurface
  /**
   * Description of template class
   * 'VoronoiCovarianceMeasureOnDigitalSurface' <p> \brief Aim: This
   * class specializes the Voronoi covariance measure for digital
   * surfaces. It adds notably the embedding of surface elements, the
   * diagonalisation of the VCM, and the orientation of the first VCM
   * eigenvector toward the interior of the surface.
   *
   * @note Documentation in \ref moduleVCM_sec3_1.
   *
   * @see VoronoiCovarianceMeasure
   *
   * @tparam TDigitalSurfaceContainer the type of digital surface
   * container (model of CDigitalSurfaceContainer).
   *
   * @tparam TSeparableMetric a model of CSeparableMetric used for
   * computing the Voronoi map (e.g. Euclidean metric is
   * DGtal::ExactPredicateLpSeparableMetric<TSpace, 2> )
   *
   * @tparam TKernelFunction the type of the kernel function chi_r used
   * for integrating the VCM, a map: Point -> Scalar.
   */
  template <typename TDigitalSurfaceContainer, typename TSeparableMetric,
            typename TKernelFunction>
  class VoronoiCovarianceMeasureOnDigitalSurface
  {
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSurfaceContainer< TDigitalSurfaceContainer > ));
    BOOST_CONCEPT_ASSERT(( concepts::CSeparableMetric<TSeparableMetric> ));
    // ----------------------- public types ------------------------------
  public:
    typedef TDigitalSurfaceContainer DigitalSurfaceContainer; ///< the chosen container
    typedef TSeparableMetric                         Metric;  ///< the chosen metric
    typedef TKernelFunction                  KernelFunction;  ///< the kernel function
    typedef DigitalSurface<DigitalSurfaceContainer> Surface;  ///< the chosen digital surface
    typedef typename DigitalSurfaceContainer::KSpace KSpace;  ///< the cellular space
    typedef typename DigitalSurfaceContainer::Surfel Surfel;  ///< the n-1 cells
    typedef typename KSpace::SCell                    SCell;  ///< the signed cells
    typedef typename KSpace::Space                    Space;  ///< the digital space
    typedef typename KSpace::Point                    Point;  ///< the digital points
    typedef VoronoiCovarianceMeasure<Space,Metric>      VCM;  ///< the Voronoi Covariance Measure
    typedef typename VCM::Scalar                     Scalar;  ///< the "real number" type
    typedef typename Surface::ConstIterator   ConstIterator;  ///< the iterator for traversing the surface
    typedef EigenDecomposition<KSpace::dimension,Scalar> LinearAlgebraTool;  ///< diagonalizer (nD).
    typedef typename VCM::VectorN                   VectorN;  ///< n-dimensional R-vector
    typedef typename VCM::MatrixNN                 MatrixNN;  ///< nxn R-matrix

    BOOST_CONCEPT_ASSERT(( concepts::CUnaryFunctor<KernelFunction, Point, Scalar> ));

    /// Structure to hold a diagonalized matrix.
    struct EigenStructure {
      VectorN values;   ///< eigenvalues from the smallest to the biggest
      MatrixNN vectors; ///< corresponding eigenvectors
    };
    /// Structure to hold the normals for each surfel (the VCM one and the trivial one).
    struct Normals {
      VectorN vcmNormal;
      VectorN trivialNormal;
    };
    typedef std::map<Point,EigenStructure> Point2EigenStructure;  ///< the map Point -> EigenStructure
    typedef std::map<Surfel,Normals>           Surfel2Normals;    ///< the map Surfel -> Normals

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~VoronoiCovarianceMeasureOnDigitalSurface();

    /**
     * Constructor. Computes the VCM of the given \a surface.
     *
     * @param _surface the digital surface that is aliased in this. The
     * user can \b secure the aliasing by passing a
     * CountedConstPtrOrConstPtr.
     *
     * @param _surfelEmbedding the chosen embedding for surfels.
     *
     * @param _R the offset radius for the set of points. Voronoi cells
     * are intersected with this offset. The unit corresponds to a step in the digital space.
     *
     * @param _r (an upper bound of) the radius of the support of the
     * kernel function \a chi_r (note \f$\chi_r\f$ in the VCM
     * paper). The unit corresponds to a step in the digital
     * space. This parameter is used for preparing the data structure
     * that answers to proximity queries.
     *
     * @param chi_r the kernel function whose support has radius less
     * or equal to \a r.
     *
     * @param t the radius for the trivial normal estimator, which is
     * used for finding the correct orientation inside/outside for the
     * VCM.
     *
     * @param aMetric an instance of the metric.
     *
     * @param verbose if 'true' displays information on ongoing computation.
     */
    VoronoiCovarianceMeasureOnDigitalSurface( ConstAlias< Surface > _surface, 
                                              Surfel2PointEmbedding _surfelEmbedding,
                                              Scalar _R, Scalar _r, 
                                              KernelFunction chi_r,
                                              Scalar t = 2.5, Metric aMetric = Metric(), 
                                              bool verbose = false );

    /// the const-aliased digital surface.
    CountedConstPtrOrConstPtr< Surface > surface() const;
    /// the chosen embedding Surfel -> Point(s)
    Surfel2PointEmbedding surfelEmbedding() const;
    /// @return the parameter R in the VCM, i.e. the offset radius for
    /// the compact set K.
    Scalar R() const;
    /// @return the parameter r in VCM(chi_r), i.e. an upper bound for
    /// the diameter of the support of kernel functions.
    Scalar r() const;

    /// @return the radius for the trivial normal estimator, which is
    /// used for finding the correct orientation inside/outside for
    /// the VCM.
    Scalar radiusTrivial() const;

    /**
       @param[in] outIt an output iterator on Point to write the point(s) associated to surfel \a s. 
       @param[in] s the surfel that is embedded in the digital space according to mySurfelEmbedding.
       @return the (modified) output iterator after the write operations.
    */
    template <typename PointOutputIterator>
    PointOutputIterator getPoints( PointOutputIterator outIt, Surfel s ) const; 

    /// @return a const-reference to the map Surfel -> Normals (vcm and trivial normal).
    const Surfel2Normals& mapSurfel2Normals() const;

    /// @return a const-reference to the map Point ->
    /// EigenStructure of the chi_r VCM (eigenvalues and
    /// eigenvectors).
    const Point2EigenStructure& mapPoint2ChiVCM() const;

    /**
       Gets the eigenvalues of the chi_r VCM at surfel \a s sorted from lowest to highest.
       @param[out] values the eigenvalues of the chi_r VCM at \a s.
       @param[in] s the surfel
       @return 'true' is the surfel \a s was valid.
    */
    bool getChiVCMEigenvalues( VectorN& values, Surfel s ) const;

    /**
       Gets the eigen decomposition of the chi_r VCM at surfel \a s.
       @param[out] values the eigenvalues of the chi_r VCM at \a s sorted from lowest to highest..
       @param[out] vectors the eigenvectors of the chi_r VCM at \a s associated to \a values.
       @param[in] s the surfel
       @return 'true' is the surfel \a s was valid.
    */
    bool getChiVCMEigenStructure( VectorN& values, MatrixNN& vectors, Surfel s ) const;

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
    /// (possibly secure) alias of the digital surface
    CountedConstPtrOrConstPtr< Surface > mySurface;
    /// The chosen embedding for the surfels.
    Surfel2PointEmbedding mySurfelEmbedding;
    /// The kernel function chi_r
    KernelFunction myChi;
    /// Stores the voronoi covariance measure of the point embedding of the surface.
    VCM myVCM;
    /// Stores the radius for the trivial normal estimator, which is
    /// used for finding the correct orientation inside/outside for
    /// the VCM.
    Scalar myRadiusTrivial;
    /// Stores for each point p its convolved VCM, i.e. VCM( chi_r( p ) )
    Point2EigenStructure myPt2EigenStructure;
    /// Stores for each surfel its vcm normal and its trivial normal.
    Surfel2Normals mySurfel2Normals;

    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    VoronoiCovarianceMeasureOnDigitalSurface();

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    VoronoiCovarianceMeasureOnDigitalSurface ( const VoronoiCovarianceMeasureOnDigitalSurface & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    VoronoiCovarianceMeasureOnDigitalSurface & operator= ( const VoronoiCovarianceMeasureOnDigitalSurface & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class VoronoiCovarianceMeasureOnDigitalSurface


  /**
   * Overloads 'operator<<' for displaying objects of class 'VoronoiCovarianceMeasureOnDigitalSurface'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'VoronoiCovarianceMeasureOnDigitalSurface' to write.
   * @return the output stream after the writing.
   */
  template <typename TDigitalSurfaceContainer, typename TSeparableMetric, typename TKernelFunction>
  std::ostream&
  operator<< ( std::ostream & out, 
               const VoronoiCovarianceMeasureOnDigitalSurface<TDigitalSurfaceContainer, TSeparableMetric, TKernelFunction> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/surfaces/estimation/VoronoiCovarianceMeasureOnDigitalSurface.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined VoronoiCovarianceMeasureOnDigitalSurface_h

#undef VoronoiCovarianceMeasureOnDigitalSurface_RECURSES
#endif // else defined(VoronoiCovarianceMeasureOnDigitalSurface_RECURSES)
