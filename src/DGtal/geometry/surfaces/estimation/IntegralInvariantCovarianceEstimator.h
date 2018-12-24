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
 * @file IntegralInvariantCovarianceEstimator.h
 * @author Jeremy Levallois (\c jeremy.levallois@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), INSA-Lyon, France
 * LAboratoire de MAthématiques - LAMA (CNRS, UMR 5127), Université de Savoie, France
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2014/04/24
 *
 * Header file for module IntegralInvariantCovarianceEstimator.ih
 *
 * This file is part of the DGtal library.
 */

#if defined(IntegralInvariantCovarianceEstimator_RECURSES)
#error Recursive header files inclusion detected in IntegralInvariantCovarianceEstimator.h
#else // defined(IntegralInvariantCovarianceEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define IntegralInvariantCovarianceEstimator_RECURSES

#if !defined IntegralInvariantCovarianceEstimator_h
/** Prevents repeated inclusion of headers. */
#define IntegralInvariantCovarianceEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/kernel/BasicPointFunctors.h"
#include "DGtal/topology/CCellFunctor.h"
#include "DGtal/topology/CCellularGridSpaceND.h"
#include "DGtal/geometry/surfaces/FunctorOnCells.h"

#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/shapes/Shapes.h"

#include "DGtal/geometry/surfaces/DigitalSurfaceConvolver.h"
#include "DGtal/geometry/surfaces/estimation/IIGeometricFunctors.h"
#include "DGtal/shapes/EuclideanShapesDecorator.h"

#include "DGtal/shapes/implicit/ImplicitBall.h"
//////////////////////////////////////////////////////////////////////////////


namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// template class IntegralInvariantCovarianceEstimator
/**
* Description of template class 'IntegralInvariantCovarianceEstimator' <p>
* \brief Aim: This class implement an Integral Invariant estimator which computes for each surfel the covariance matrix of the intersection of the shape with a ball of given radius centered on the surfel.
*
* @cite Coeurjo-CVIU-2014
*
* The algorithm we propose uses a kernel (2D: Ball2D, 3D: Ball3D) that
* is moved along the surface. The covariance matrix of this kernel
* intersected with the shape carries local geometric information. It
* can be used to compute normal and curvature directions, and
* curvature values also. Theorical multigrid convergence is proved,
* with a convergence speed of O(h^1/3) with hypothesis about the shape
* geometry and the convolution kernel radius.  Experimental results
* confirm the multigrid convergence.
*
* Optimization is available when we give a range of 0-adjacent
* surfels to the estimator. Note that you should use
* IntegralInvariantVolumeEstimator instead when trying to estimate the
* 2D curvature or the mean curvature.
*
* @tparam TKSpace a model of CCellularGridSpaceND, the cellular space
* in which the shape is defined.
*
* @tparam TPointPredicate a model of concepts::CPointPredicate, a predicate
* Point -> bool that defines a digital shape as a characteristic
* function.
*
* @tparam TCovarianceMatrixFunctor a model of functor Matrix ->
* Quantity, that defines how the covariance matrix computed by the
* Integral Invariant estimator is transformed into e.g. a normal
* direction, a curvature, etc. Models include
* IIGeometricFunctors::IINormalDirectionFunctor,
* IIGeometricFunctors::IITangentDirectionFunctor,
* IIGeometricFunctors::IIFirstPrincipalDirectionFunctor,
* IIGeometricFunctors::IISecondPrincipalDirectionFunctor.
*
* @note In opposition to IntegralInvariantMeanCurvatureEstimator and
* IntegralInvariantGaussianCurvatureEstimator, this class is
* parameterized by a point predicate instead of a functor spel ->
* {0,1}. The two latter classes should evolve as this one in a further release.
*
* @see testIntegralInvariantCovarianceEstimator.cpp
*/
template <typename TKSpace, typename TPointPredicate, typename TCovarianceMatrixFunctor>
class IntegralInvariantCovarianceEstimator
{
public:
  typedef IntegralInvariantCovarianceEstimator< TKSpace, TPointPredicate, TCovarianceMatrixFunctor> Self;
  typedef TKSpace KSpace;
  typedef TPointPredicate PointPredicate;
  typedef TCovarianceMatrixFunctor CovarianceMatrixFunctor;

  BOOST_CONCEPT_ASSERT (( concepts::CCellularGridSpaceND< KSpace > ));
  BOOST_CONCEPT_ASSERT (( concepts::CPointPredicate< PointPredicate > ));

  typedef typename KSpace::Space Space;
  typedef HyperRectDomain<Space> Domain;
  typedef typename Space::Point Point;
  typedef typename Space::RealPoint RealPoint;
  typedef typename Space::RealVector RealVector;
  typedef typename DigitalSetSelector<Domain,  BIG_DS + HIGH_VAR_DS>::Type DigitalSet;
  typedef typename KSpace::SCell Spel;
  typedef typename KSpace::Surfel Surfel;
  typedef typename KSpace::SurfelSet SurfelSet;
  typedef typename SurfelSet::const_iterator ConstIteratorKernel;

  /// The returned type of the estimator, depends on the functor
  typedef typename CovarianceMatrixFunctor::Quantity Quantity;
  /// The type used for convolutions
  typedef int Value;

  /// A wrapper around point predicate (functor Point -> bool) that
  /// transforms it into a functor Point -> unsigned int (0 or 1).
  typedef functors::PointFunctorFromPointPredicateAndDomain< PointPredicate, Domain, unsigned int > ShapePointFunctor;
  /// Adapts the a functor Point -> unsigned int (0 or 1) to a functor Cell ->
  /// unsigned int (0 ot 1), where Cell is a spel. Needed by DigitalSurfaceConvolver.
  typedef FunctorOnCells< ShapePointFunctor, KSpace > ShapeSpelFunctor;


  typedef functors::ConstValueCell<Value, Spel> KernelSpelFunctor;
  typedef ImplicitBall<Space> KernelSupport;
  typedef EuclideanShapesCSG< KernelSupport, KernelSupport > EuclideanMinus;
  typedef GaussDigitizer< Space, KernelSupport > DigitalShapeKernel;
  typedef GaussDigitizer< Space, EuclideanMinus > DigitalShape;

  typedef DigitalSurfaceConvolver<ShapeSpelFunctor, KernelSpelFunctor, 
                                  KSpace, DigitalShapeKernel> Convolver;
  typedef typename Convolver::PairIterators PairIterators;
  typedef typename Convolver::CovarianceMatrix Matrix;
  typedef typename Matrix::Component Component;
  typedef double Scalar;
  BOOST_CONCEPT_ASSERT (( concepts::CCellFunctor< ShapeSpelFunctor > ));
  BOOST_CONCEPT_ASSERT (( concepts::CUnaryFunctor< CovarianceMatrixFunctor, Matrix, Quantity > ));
  BOOST_STATIC_ASSERT (( concepts::ConceptUtils::SameType< typename Convolver::CovarianceMatrix, 
                                                 typename CovarianceMatrixFunctor::Argument >::value ));


  // ----------------------- Standard services ------------------------------
public:

  /**
  * Default constructor. The object is invalid. The user needs to call
  * setParams and attach.
  * 
  * @param fct the functor for transforming the covariance matrix into
  * some quantity. If not precised, a default object is instantiated.
  */
  IntegralInvariantCovarianceEstimator( CovarianceMatrixFunctor fct = CovarianceMatrixFunctor() );

  /**
  * Constructor.
  *
  * @param[in] K the cellular grid space in which the shape is defined.
  * @param[in] aPointPredicate the shape of interest. The alias can be secured
  * if a some counted pointer is handed.
  * @param fct the functor for transforming the covariance matrix into
  * some quantity. If not precised, a default object is instantiated.
  */
  IntegralInvariantCovarianceEstimator ( ConstAlias< KSpace > K, 
                               ConstAlias< PointPredicate > aPointPredicate,
                               CovarianceMatrixFunctor fct = CovarianceMatrixFunctor() );

  /**
  * Destructor.
  */
  ~IntegralInvariantCovarianceEstimator();

  /**
  * Copy constructor.
  * @param other the object to clone.
  */
  IntegralInvariantCovarianceEstimator ( const Self& other );

  /**
  * Assignment.
  * @param other the object to copy.
  * @return a reference on 'this'.
  */
  Self& operator= ( const Self& other );

  /**
  * Clears the object. It is now invalid.
  */
  void clear();

  // ----------------------- Interface --------------------------------------
public:

  /// @return the grid step.
  Scalar h() const;

  /**
  * Attach a shape, defined as a functor spel -> boolean
  *
  * @param[in] K the cellular grid space in which the shape is defined.
  * @param aPointPredicate the shape of interest. The alias can be secured
  * if a some counted pointer is handed.
  */
  void attach( ConstAlias< KSpace > K, 
               ConstAlias<PointPredicate> aPointPredicate );

  /**
  * Set specific parameters: the radius of the ball.
  *
  * @param[in] dRadius the "digital" radius of the kernel (but may be non integer).
  */
  void setParams( const double dRadius );
  
  /**
  * Model of CDigitalSurfaceLocalEstimator. Initialisation.
  *
  * @tparam SurfelConstIterator any model of forward readable iterator on Surfel.
  * @param[in] _h grid size (must be >0).
  * @param[in] ite iterator on the first surfel of the surface.
  * @param[in] itb iterator after the last surfel of the surface.
  */
  template <typename SurfelConstIterator>
  void init( const double _h, SurfelConstIterator itb, SurfelConstIterator ite );

  /**
  * -- Estimation -- 
  *
  * Compute the integral invariant covariance matrix at surfel *it of
  * a shape, then apply the CovarianceMatrixFunctor to extract some
  * geometric information.
  *
  * @tparam SurfelConstIterator type of Iterator on a Surfel
  *
  * @param[in] it iterator pointing on the surfel of the shape where
  * we wish to evaluate some geometric information.
  *
  * @return quantity (normal vector) at surfel *it
  */
  template< typename SurfelConstIterator >
  Quantity eval ( SurfelConstIterator it ) const;


  /**
  * -- Estimation -- 
  *
  * Compute the integral invariant covariance matrix for a range of
  * surfels [itb,ite) on a shape, then apply the
  * CovarianceMatrixFunctor to extract some geometric information.
  * Return the result on an OutputIterator (param).
  *
  * @tparam OutputIterator type of Iterator of an array of Quantity
  * @tparam SurfelConstIterator type of Iterator on a Surfel
  *
  * @param[in] itb iterator defining the start of the range of surfels
  * where we wish to compute some geometric information.
  *
  * @param[in] ite iterator defining the end of the range of surfels
  * where we wish to compute some geometric information.
  *
  * @param[in] result output iterator of results of the computation.
  * @return the updated output iterator after all outputs.
  */
  template <typename OutputIterator, typename SurfelConstIterator>
  OutputIterator eval( SurfelConstIterator itb,
                       SurfelConstIterator ite,
                       OutputIterator result ) const;

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

  // ------------------------- Private Datas --------------------------------
private:

  CovarianceMatrixFunctor myFct;            ///< The covariance matrix functor that transforms the II covariance matrix into a quantity.
  const KernelSpelFunctor myKernelFunctor;  ///< Kernel functor (on Spel)
  std::vector< PairIterators > myKernels;   ///< array of begin/end iterator of shifting masks.
  std::vector< DigitalSet * > myKernelsSet; ///< Array of shifting masks. Size = 9 for each shifting (0-adjacent and full kernel included)
  CountedPtr<KernelSupport>      myKernel;      ///< Euclidean kernel
  CountedPtr<DigitalShapeKernel> myDigKernel;   ///< Digital kernel
  CountedConstPtrOrConstPtr<PointPredicate> myPointPredicate; ///< Smart pointer (if required) on a point predicate.
  CountedPtr<Domain>             myShapeDomain; ///< Smart pointer on domain         
  CountedPtr<ShapePointFunctor>  myShapePointFunctor; ///< Smart pointer on functor point -> {0,1}
  CountedPtr<ShapeSpelFunctor>   myShapeSpelFunctor;  ///< Smart pointer on functor spel ->  {0,1}
  CountedPtr<Convolver>          myConvolver;   ///< Convolver
  Scalar myH;                               ///< precision of the grid
  Scalar myRadius;                          ///< "digital" radius of the kernel (but may be non integer).

private:


}; // end of class IntegralInvariantCovarianceEstimator

  /**
  * Overloads 'operator<<' for displaying objects of class 'IntegralInvariantCovarianceEstimator'.
  * @param out the output stream where the object is written.
  * @param object the object of class 'IntegralInvariantCovarianceEstimator' to write.
  * @return the output stream after the writing.
  */
  template <typename TKSpace, typename TPointPredicate, typename TCovarianceMatrixFunctor>
  std::ostream&
  operator<< ( std::ostream & out, 
               const IntegralInvariantCovarianceEstimator<TKSpace, TPointPredicate, TCovarianceMatrixFunctor> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/surfaces/estimation/IntegralInvariantCovarianceEstimator.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined IntegralInvariantCovarianceEstimator_h

#undef IntegralInvariantCovarianceEstimator_RECURSES
#endif // else defined(IntegralInvariantCovarianceEstimator_RECURSES)
