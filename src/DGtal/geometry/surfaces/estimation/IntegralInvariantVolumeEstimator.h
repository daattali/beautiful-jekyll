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
 * @file IntegralInvariantVolumeEstimator.h
 * @author Jeremy Levallois (\c jeremy.levallois@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), INSA-Lyon, France
 * LAboratoire de MAthématiques - LAMA (CNRS, UMR 5127), Université de Savoie, France
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2014/04/24
 *
 * Header file for module IntegralInvariantVolumeEstimator.ih
 *
 * This file is part of the DGtal library.
 */

#if defined(IntegralInvariantVolumeEstimator_RECURSES)
#error Recursive header files inclusion detected in IntegralInvariantVolumeEstimator.h
#else // defined(IntegralInvariantVolumeEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define IntegralInvariantVolumeEstimator_RECURSES

#if !defined IntegralInvariantVolumeEstimator_h
/** Prevents repeated inclusion of headers. */
#define IntegralInvariantVolumeEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/kernel/BasicPointFunctors.h"
#include "DGtal/kernel/CPointPredicate.h"
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
// template class IntegralInvariantVolumeEstimator
/**
* Description of template class 'IntegralInvariantVolumeEstimator' <p>
* \brief Aim: This class implement an Integral Invariant estimator which computes for each surfel the volume of the intersection of the shape with a ball of given radius centered on the surfel.
*
*
* @cite Coeurjo-CVIU-2014
*
* The algorithm we propose uses a kernel (2D: Ball2D, 3D: Ball3D) that
* is moved along the surface. The volume of this kernel intersected
* with the shape carries local geometric information. It can be used to
* compute the mean curvature in 2D and 3D. Theorical multigrid
* convergence is proved, with a convergence speed of O(h^1/3) with
* hypothesis about the shape geometry and the convolution kernel
* radius.  Experimental results confirm the multigrid convergence.
*
* Optimization is available when we give a range of 0-adjacent
* surfels to the estimator. Note that you should use
* IntegralInvariantCovarianceEstimator instead when trying to estimate
* the normal or principal curvature directions, the Gaussian curvature
* or individual principal curvature values.
*
* @tparam TKSpace a model of CCellularGridSpaceND, the cellular space
* in which the shape is defined.
*
* @tparam TPointPredicate a model of concepts::CPointPredicate, a predicate
* Point -> bool that defines a digital shape as a characteristic
* function.
*
* @tparam TVolumeFunctor a model of functor Real -> Quantity, that
* defines how the volume computed by the Integral Invariant estimator
* is transformed into e.g. a curvature, etc. Models include
* IIGeometricFunctors::IICurvatureFunctor,
* IIGeometricFunctors::IIMeanCurvature3DFunctor.
*
* @note In opposition to IntegralInvariantMeanCurvatureEstimator and
* IntegralInvariantGaussianCurvatureEstimator, this class is
* parameterized by a point predicate instead of a functor spel ->
* {0,1}. The two latter classes should evolve as this one in a further release.
*
* @see testIntegralInvariantVolumeEstimator.cpp
*/
template <typename TKSpace, typename TPointPredicate, typename TVolumeFunctor>
class IntegralInvariantVolumeEstimator
{
public:
  typedef IntegralInvariantVolumeEstimator< TKSpace, TPointPredicate, TVolumeFunctor> Self;
  typedef TKSpace KSpace;
  typedef TPointPredicate PointPredicate;
  typedef TVolumeFunctor VolumeFunctor;

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
  typedef typename VolumeFunctor::Quantity Quantity;
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
  BOOST_CONCEPT_ASSERT (( concepts::CUnaryFunctor< VolumeFunctor, Component, Quantity > ));
  BOOST_STATIC_ASSERT (( concepts::ConceptUtils::SameType< typename Convolver::Quantity, 
                                                 typename VolumeFunctor::Argument >::value ));


  // ----------------------- Standard services ------------------------------
public:

  /**
  * Default constructor. The object is invalid. The user needs to call
  * setParams and attach.
  * 
  * @param[in] fct the functor for transforming the volume into
  * some quantity. If not precised, a default object is instantiated.
  */
  IntegralInvariantVolumeEstimator( VolumeFunctor fct = VolumeFunctor() );

  /**
  * Constructor.
  *
  * @param[in] K the cellular grid space in which the shape is defined.
  * @param[in] aPointPredicate the shape of interest. The alias can be secured
  * if a some counted pointer is handed.
  * @param[in] fct the functor for transforming the volume into
  * some quantity. If not precised, a default object is instantiated.
  */
  IntegralInvariantVolumeEstimator ( ConstAlias< KSpace > K, 
                                     ConstAlias< PointPredicate > aPointPredicate,
                                     VolumeFunctor fct = VolumeFunctor() );

  /**
  * Destructor.
  */
  ~IntegralInvariantVolumeEstimator();

  /**
  * Copy constructor.
  * @param other the object to clone.
  */
  IntegralInvariantVolumeEstimator ( const Self& other );

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
  * @param[in] dRadius the "digital" radius of the kernel (buy may be non integer).
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
  * Compute the integral invariant volume at surfel *it of
  * a shape, then apply the VolumeFunctor to extract some
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
  * Compute the integral invariant volume for a range of
  * surfels [itb,ite) on a shape, then apply the
  * VolumeFunctor to extract some geometric information.
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

  VolumeFunctor myFct;            ///< The volume functor that transforms the volume into a quantity.
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
  Scalar myRadius;                          ///< "digital" radius of the kernel (buy may be non integer).

private:


}; // end of class IntegralInvariantVolumeEstimator

  /**
  * Overloads 'operator<<' for displaying objects of class 'IntegralInvariantVolumeEstimator'.
  * @param out the output stream where the object is written.
  * @param object the object of class 'IntegralInvariantVolumeEstimator' to write.
  * @return the output stream after the writing.
  */
  template <typename TKSpace, typename TPointPredicate, typename TVolumeFunctor>
  std::ostream&
  operator<< ( std::ostream & out, 
               const IntegralInvariantVolumeEstimator<TKSpace, TPointPredicate, TVolumeFunctor> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/surfaces/estimation/IntegralInvariantVolumeEstimator.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined IntegralInvariantVolumeEstimator_h

#undef IntegralInvariantVolumeEstimator_RECURSES
#endif // else defined(IntegralInvariantVolumeEstimator_RECURSES)
