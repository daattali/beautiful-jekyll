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
 * @file DigitalSurfaceConvolver.h
 * @brief Compute a convolution between a border on a nD-shape and a convolution kernel : (f*g)(t).
 * An optimization is available when you convolve your shape on adjacent cells using eval(itbegin, itend, output)
 *
 * @author Jeremy Levallois (\c jeremy.levallois@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), INSA-Lyon, France
 * LAboratoire de MAthématiques - LAMA (CNRS, UMR 5127), Université de Savoie, France
 *
 * @date 2012/03/27
 *
 * This file is part of the DGtal library.
 *
 * @see IntegralInvariantMeanCurvatureEstimator.h IntegralInvariantGaussianCurvatureEstimator.h
 */

#if defined(DigitalSurfaceConvolver_RECURSES)
#error Recursive header files inclusion detected in DigitalSurfaceConvolver.h
#else // defined(DigitalSurfaceConvolver_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DigitalSurfaceConvolver_RECURSES

#if !defined DigitalSurfaceConvolver_h
/** Prevents repeated inclusion of headers. */
#define DigitalSurfaceConvolver_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/math/linalg/SimpleMatrix.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/base/Alias.h"
#include "DGtal/base/Clone.h"
#include "DGtal/topology/CCellFunctor.h"
#include "DGtal/topology/CanonicSCellEmbedder.h"
#include "DGtal/topology/SCellsFunctors.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// template class DigitalSurfaceConvolver
/**
   * Description of class 'DigitalSurfaceConvolver' <p>
   *
   * Aim: Compute a convolution between a border on a nD-shape and a convolution kernel : (f*g)(t).
   * An optimization is available when you convolve your shape on adjacent cells using eval(itbegin, itend, output)
   *
   * @tparam TFunctor a model of a functor for the shape to convolve ( f(x) ).
   * @tparam TKernelFunctor a model of a functor for the convolution kernel ( g(x) ).
   * @tparam TKSpace space in which the shape is defined.
   * @tparam TDigitalKernel type of a convolution kernel (ImplicitBall in general case).
   */
template< typename TFunctor, typename TKernelFunctor, typename TKSpace, typename TDigitalKernel, Dimension dimension = TKSpace::dimension >
class DigitalSurfaceConvolver
{
public:

  typedef TFunctor Functor;
  typedef TKSpace KSpace;
  typedef TKernelFunctor KernelFunctor;
  typedef TDigitalKernel DigitalKernel;

  typedef Z2i::Domain Domain;

  typedef double Quantity;
  typedef PointVector< dimension, Quantity > VectorQuantity;
  typedef SimpleMatrix< Quantity, dimension, dimension > MatrixQuantity;
  typedef SimpleMatrix< double, dimension, dimension > CovarianceMatrix;

  typedef typename KSpace::SCell Spel;
  typedef typename KSpace::Point Point;
  typedef typename KSpace::Space::RealPoint RealPoint;
  typedef Z2i::DigitalSet::ConstIterator KernelConstIterator;

  typedef std::pair< KernelConstIterator, KernelConstIterator > PairIterators;
  typedef CanonicSCellEmbedder< KSpace > Embedder;

  BOOST_CONCEPT_ASSERT (( concepts::CCellFunctor< Functor > ));
  BOOST_CONCEPT_ASSERT (( concepts::CCellFunctor< KernelFunctor > ));

  // ----------------------- Standard services ------------------------------

public:

  /**
  * Constructor.
  *
  * @param[in] f a functor f(x).
  * @param[in] g a functor g(x).
  * @param[in] space space in which the shape is defined.
  */
  DigitalSurfaceConvolver ( ConstAlias< Functor > f, ConstAlias< KernelFunctor > g, ConstAlias< KSpace > space );

  /**
  * Copy constructor.
  * @param other the object to clone.
  */
  DigitalSurfaceConvolver ( const DigitalSurfaceConvolver & other );


  /**
  * Destructor.
  */
  ~DigitalSurfaceConvolver () {}

  // ----------------------- Interface --------------------------------------

public:

  /**
  * Initialize the convolver using masks - allow to use the optimization with adjacent cells.
  *
  * Stores the full kernel explicitly: choose this init if you have a lot of memory or if your kernel is small.
  *
  * @param[in] pOrigin center (digital point) of the kernel support.
  * @param[in] fullKernel pair of iterators of the full kernel. first is the first iterator (of spel) of the kernel support, second is the last iterator (of spel, excluded).
  * @param[in] masks Vector of iterators (of spel) of the first and last spel of each masks. They must be ordered using a trit ({0,1,2}) encoded array.
  * trit 0 => shifting_coord = -1
  * trit 1 => shifting_coord = 0
  * trit 2 => shifting_coord = 1
  * Example in 3D :      zyx                 x  y  z
  * mask[0] : base3(0) = 000 => shifting = {-1,-1,-1}
  * mask[5] : base3(5) = 012 => shifting = { 1, 0,-1}
  */
  void init ( const Point & pOrigin,
              ConstAlias< PairIterators > fullKernel,
              ConstAlias< std::vector< PairIterators > > masks );

  /**
  * Intitialize the convolver using masks - allow to use the optimization with adjacent cells.
  *
  * Stores the kernel implicitly: choose this init if you have not a lot of memory available or if your kernel size is big.
  *
  * @param[in] pOrigin center (digital point) of the kernel support.
  * @param[in] fullKernel pointer of the digital (full) kernel.
  * @param[in] masks Vector of iterators (of spel) of the first and last spel of each masks. They must be ordered using a trit ({0,1,2}) encoded array.
  * trit 0 => shifting_coord = -1
  * trit 1 => shifting_coord = 0
  * trit 2 => shifting_coord = 1
  * Example in 3D :      zyx                 x  y  z
  * mask[0] : base3(0) = 000 => shifting = {-1,-1,-1}
  * mask[5] : base3(5) = 012 => shifting = { 1, 0,-1}
  */
  void init ( const Point & pOrigin,
              ConstAlias< DigitalKernel > fullKernel,
              ConstAlias< std::vector< PairIterators > > masks );

  /**
  * Convolve the kernel at a position \a it.
  *
  * @param[in] it (iterator of a) surfel of the shape where the convolution is computed.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  *
  * @return the estimated quantity at *it : (f*g)(t)
  */
  template< typename SurfelIterator >
  Quantity eval ( const SurfelIterator & it ) const;


  /**
  * Convolve the kernel at a position \a it and applies the functor \a functor on the result.
  *
  * @param[in] it (iterator of a) surfel of the shape where the convolution is computed.
  * @param[in] functor functor called with the result of the convolution.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam EvalFunctor type of functor on Quantity.
  *
  * @return the return quantity of functor after giving in parameter the result of the convolution at *it
  */
  template< typename SurfelIterator, typename EvalFunctor >
  typename EvalFunctor::Value eval ( const SurfelIterator & it,
                                     EvalFunctor functor ) const;


  /**
  * Convolve the kernel at all positions of the range [itBegin, itEnd[ and outputs results sequentially with \a result iterator.
  *
  * @param[in] itbegin (iterator of the) first surfel of the shape where the convolution is computed.
  * @param[in] itend (iterator of the) last (excluded) surfel of the shape where the convolution is computed.
  * @param[out] result iterator of an array where estimates quantities are set ( the estimated quantity from *itbegin till *itend (excluded)).
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam OutputIterator type of iterator on an array when Quantity are stored.
  */
  template< typename SurfelIterator, typename OutputIterator >
  void eval ( const SurfelIterator & itbegin,
              const SurfelIterator & itend,
              OutputIterator & result ) const;

  /**
  * Convolve the kernel at all positions of the range [itBegin, itEnd[ and applies the functor \a functor on results outputed sequentially with \a result iterator.
  *
  * @param[in] itbegin (iterator of the) first surfel of the shape where the convolution is computed.
  * @param[in] itend (iterator of the) last (excluded) surfel of the shape where the convolution is computed.
  * @param[out] result iterator of an array where estimates quantities are set ( the estimated quantity from *itbegin till *itend (excluded)).
  * @param[in] functor functor called with the result of the convolution.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam OutputIterator type of iterator on an array when Quantity are stored.
  * @tparam EvalFunctor type of functor on Quantity.
  */
  template< typename SurfelIterator, typename OutputIterator, typename EvalFunctor >
  void eval ( const SurfelIterator & itbegin,
              const SurfelIterator & itend,
              OutputIterator & result,
              EvalFunctor functor ) const;


  /**
  * Convolve the kernel at a position \a it.
  *
  * @param[in] it (iterator of a) surfel of the shape where the covariance matrix is computed.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  *
  * @return the covariance matrix at *it
  */
  template< typename SurfelIterator >
  CovarianceMatrix evalCovarianceMatrix ( const SurfelIterator & it ) const;

  /**
  * Convolve the kernel at a position \a it and applies the functor \a functor on the result.
  *
  * @param[in] it (iterator of a) surfel of the shape where the covariance matrix is computed.
  * @param[in] functor functor called with the result of the convolution.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam EvalFunctor type of functor on CovarianceMatrix.
  *
  * @return the result of the functor with the covariance matrix.
  */
  template< typename SurfelIterator, typename EvalFunctor >
  typename EvalFunctor::Value evalCovarianceMatrix ( const SurfelIterator & it,
                                                     EvalFunctor functor ) const;

  /**
  * Convolve the kernel at all positions of the range [itBegin, itEnd[ and outputs results sequentially with \a result iterator.
  *
  * @param[in] itbegin (iterator of the) first surfel of the shape where the covariance matrix is computed.
  * @param[in] itend (iterator of the) last (excluded) surfel of the shape where the covariance matrix is computed.
  * @param[out] result iterator of an array where estimates covariance matrix are set ( the covariance matrix from *itbegin till *itend (excluded)).
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam OutputIterator type of iterator on an array when Quantity are stored.
  */
  template< typename SurfelIterator, typename OutputIterator >
  void evalCovarianceMatrix ( const SurfelIterator & itbegin,
                              const SurfelIterator & itend,
                              OutputIterator & result ) const;

  /**
  * Convolve the kernel at all positions of the range [itBegin, itEnd[ and applies the functor \a functor on results outputed sequentially with \a result iterator.
  *
  * @param[in] itbegin (iterator of the) first surfel of the shape where the covariance matrix is computed.
  * @param[in] itend (iterator of the) last (excluded) surfel of the shape where the covariance matrix is computed.
  * @param[out] result iterator of an array where results of functor are set.
  * @param[in] functor functor called with the result of the convolution.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam OutputIterator type of iterator on an array when Quantity are stored.
  * @tparam EvalFunctor type of functor on CovarianceMatrix.
  */
  template< typename SurfelIterator, typename OutputIterator, typename EvalFunctor >
  void evalCovarianceMatrix ( const SurfelIterator & itbegin,
                              const SurfelIterator & itend,
                              OutputIterator & result,
                              EvalFunctor functor ) const;


  /**
  * Checks the validity/consistency of the object.
  * @return 'true' if the object is valid, 'false' otherwise.
  */
  bool isValid () const;

protected:

  /**
   * @brief computeCovarianceMatrix compute the covariance matrix from matrix of moments.
   *
   * @param[in] aMomentMatrix a matrix of digital moments
   * [ sum(1)
   *   sum(y) sum (x)
   *   sum(x*y) sum(y*y) sum(x*x)
   * ]
   * @param[out] aCovarianceMatrix the result covariance matrix
   */
  void computeCovarianceMatrix( const Quantity * aMomentMatrix, CovarianceMatrix & aCovarianceMatrix ) const;

  /**
   * @brief fillMoments fill the matrix of moments with a given spel.
   *
   * @param[out] aMomentMatrix a matrix of digital moments
   * [ sum(1)
   *   sum(y) sum (x)
   *   sum(x*y) sum(y*y) sum(x*x)
   * ]
   * @param[in] aSpel current spel
   * @param[in] direction true if we add the current spel, false if we remove it.
   */
  void fillMoments( Quantity* aMomentMatrix, const Spel & aSpel, double direction ) const;

  static const int nbMoments; ///< the number of moments is dependent to the dimension. In 2D, they are 6 moments such that p+q <= 2 (see method fillMoments())
  static Spel defaultInnerSpel; ///< default Spel, used as default parameter in core_eval and core_evalCovarianceMatrix functions
  static Spel defaultOuterSpel; ///< default Spel, used as default parameter in core_eval and core_evalCovarianceMatrix functions
  static Quantity defaultInnerMoments[ 6 ]; ///< default array of Quantity, used as default parameter in core_evalCovarianceMatrix function
  static Quantity defaultOuterMoments[ 6 ]; ///< default array of Quantity, used as default parameter in core_evalCovarianceMatrix function
  static Quantity defaultInnerSum; ///< default Quantity, used as default parameter in core_eval function
  static Quantity defaultOuterSum; ///< default Quantity, used as default parameter in core_eval function

  /**
   * @brief core_eval method used ( in intern by eval() ) to compute the Quantity on a given surfel (*it)
   *
   * @param[in] it (iterator of a) surfel of the shape where the convolution is computed.
   * @param[out] innerSum the result Quantity when centering with the innerSpel.
   * @param[out] outerSum the result Quantity when centering with the outerSpel.
   * @param[in] useLastResults if we can use last results (optimisation with masks)
   * @param[in,out] lastInnerSpel last inner spel. Override at end of function with current inner spel (from surfel *it). Set empty if useLastResults is false.
   * @param[in,out] lastOuterSpel last outer spel. Override at end of function with current outer spel (from surfel *it). Set empty if useLastResults is false.
   * @param[in] lastInnerSum last Quantity when centering with inner spel. Set empty if useLastResults is false.
   * @param[in] lastOuterSum last Quantity when centering with outer spel. Set empty if useLastResults is false.
   *
   * @tparam SurfelIterator type of iterator on surfel
   */
  template< typename SurfelIterator >
  bool core_eval ( const SurfelIterator & it,
                   Quantity & innerSum,
                   Quantity & outerSum,
                   bool useLastResults = false,
                   Spel & lastInnerSpel = defaultInnerSpel,
                   Spel & lastOuterSpel = defaultOuterSpel,
                   Quantity & lastInnerSum = defaultInnerSum,
                   Quantity & lastOuterSum = defaultOuterSum ) const;

  /**
   * @brief core_evalCovarianceMatrix method used ( in intern by evalCovarianceMatrix() ) to compute the covariance matrix on a given surfel (*it)
   *
   * @param[in] it (iterator of a) surfel of the shape where the convolution is computed.
   * @param[out] innerMatrix the result covariance matrix when centering with the innerSpel.
   * @param[out] outerMatrix the result covariance matrix when centering with the outerSpel.
   * @param[in] useLastResults if we can use last results (optimisation with masks)
   * @param[in,out] lastInnerSpel last inner spel. Override at end of function with current inner spel (from surfel *it). Set empty if useLastResults is false.
   * @param[in,out] lastOuterSpel last outer spel. Override at end of function with current outer spel (from surfel *it). Set empty if useLastResults is false.
   * @param[in,out] lastInnerMoments last inner moments when centering with inner spel. Override at end of function with current inner moments (from surfel *it). Set empty if useLastResults is false.
   * @param[in,out] lastOuterMoments last inner moments when centering with inner spel. Override at end of function with current outer moments (from surfel *it). Set empty if useLastResults is false.
   *
   * @tparam SurfelIterator type of iterator on surfel
   */
  template< typename SurfelIterator >
  bool core_evalCovarianceMatrix ( const SurfelIterator & it,
                                   CovarianceMatrix & innerMatrix,
                                   CovarianceMatrix & outerMatrix,
                                   bool useLastResults = false,
                                   Spel & lastInnerSpel = defaultInnerSpel,
                                   Spel & lastOuterSpel = defaultOuterSpel,
                                   Quantity * lastInnerMoments = defaultInnerMoments,
                                   Quantity * lastOuterMoments = defaultOuterMoments ) const;



  // ------------------------- Private Datas --------------------------------

private:

  const Functor & myFFunctor; ///< Const ref of the shape functor

  const KernelFunctor & myGFunctor; ///< Const ref of the kernel functor


  const KSpace & myKSpace; ///< Const ref of the shape Kspace

  Embedder myEmbedder; ///< Converter Digital point -> Euclidean point

  bool isInitFullMasks; ///< If the user uses init with masks. See init() for more information.

  bool isInitKernelAndMasks; ///< If the user uses init with masks and digital (full) kernel. See init() for more information.

  const std::vector< PairIterators > * myMasks; ///< Pointer of vector of iterators for kernel partial masks

  const DigitalKernel * myKernel; ///< Two choice to iterate over the full kernel. See init() for more information.
  const PairIterators * myKernelMask; ///< Two choice to iterate over the full kernel. See init() for more information.

  Spel myKernelSpelOrigin; ///< Copy of the origin cell of the kernel.

  // ------------------------- Hidden services ------------------------------

protected:
  /**
  * Constructor.
  * Forbidden by default (protected to avoid g++ warnings).
  */
  DigitalSurfaceConvolver ();

private:

  /**
  * Assignment.
  * @param other the object to copy.
  * @return a reference on 'this'.
  * Forbidden by default.
  */
  DigitalSurfaceConvolver & operator= ( const DigitalSurfaceConvolver & other );

  // ------------------------- Internals ------------------------------------

private:

}; // end of class DigitalSurfaceConvolver

template< typename TFunctor, typename TKernelFunctor, typename TKSpace, typename TDigitalKernel >
class DigitalSurfaceConvolver< TFunctor, TKernelFunctor, TKSpace, TDigitalKernel, 2 >
{
  // ----------------------- Types ------------------------------------------

public:

  typedef TFunctor Functor;
  typedef TKSpace KSpace;
  typedef TKernelFunctor KernelFunctor;
  typedef TDigitalKernel DigitalKernel;

  typedef Z2i::Domain Domain;

  typedef double Quantity;
  typedef PointVector< 2, Quantity > VectorQuantity;
  typedef SimpleMatrix< Quantity, 2, 2 > MatrixQuantity;
  typedef SimpleMatrix< double, 2, 2 > CovarianceMatrix;

  typedef typename KSpace::SCell Spel;
  typedef typename KSpace::Point Point;
  typedef typename KSpace::Space::RealPoint RealPoint;
  typedef Z2i::DigitalSet::ConstIterator KernelConstIterator;

  typedef std::pair< KernelConstIterator, KernelConstIterator > PairIterators;
  typedef CanonicSCellEmbedder< KSpace > Embedder;

  BOOST_CONCEPT_ASSERT (( concepts::CCellFunctor< Functor > ));
  BOOST_CONCEPT_ASSERT (( concepts::CCellFunctor< KernelFunctor > ));

  // ----------------------- Standard services ------------------------------

public:

  /**
  * Constructor.
  *
  * @param[in] f a functor f(x).
  * @param[in] g a functor g(x).
  * @param[in] space space in which the shape is defined.
  */
  DigitalSurfaceConvolver ( ConstAlias< Functor > f, ConstAlias< KernelFunctor > g, ConstAlias< KSpace > space );

  /**
  * Copy constructor.
  * @param other the object to clone.
  */
  DigitalSurfaceConvolver ( const DigitalSurfaceConvolver & other );

  /**
  * Destructor.
  */
  ~DigitalSurfaceConvolver () {}

  // ----------------------- Interface --------------------------------------

public:

  /**
  * Initialize the convolver using masks - allow to use the optimization with adjacent cells.
  *
  * Stores the full kernel explicitly: choose this init if you have a lot of memory or if your kernel is small.
  *
  * @param[in] pOrigin center (digital point) of the kernel support.
  * @param[in] fullKernel pair of iterators of the full kernel. first is the first iterator (of spel) of the kernel support, second is the last iterator (of spel, excluded).
  * @param[in] masks Vector of iterators (of spel) of the first and last spel of each masks. They must be ordered using a trit ({0,1,2}) encoded array.
  * trit 0 => shifting_coord = -1
  * trit 1 => shifting_coord = 0
  * trit 2 => shifting_coord = 1
  * Example in 3D :      zyx                 x  y  z
  * mask[0] : base3(0) = 000 => shifting = {-1,-1,-1}
  * mask[5] : base3(5) = 012 => shifting = { 1, 0,-1}
  */
  void init ( const Point & pOrigin,
              ConstAlias< PairIterators > fullKernel,
              ConstAlias< std::vector< PairIterators > > masks );

  /**
  * Intitialize the convolver using masks - allow to use the optimization with adjacent cells.
  *
  * Stores the kernel implicitly: choose this init if you have not a lot of memory available or if your kernel size is big.
  *
  * @param[in] pOrigin center (digital point) of the kernel support.
  * @param[in] fullKernel pointer of the digital (full) kernel.
  * @param[in] masks Vector of iterators (of spel) of the first and last spel of each masks. They must be ordered using a trit ({0,1,2}) encoded array.
  * trit 0 => shifting_coord = -1
  * trit 1 => shifting_coord = 0
  * trit 2 => shifting_coord = 1
  * Example in 3D :      zyx                 x  y  z
  * mask[0] : base3(0) = 000 => shifting = {-1,-1,-1}
  * mask[5] : base3(5) = 012 => shifting = { 1, 0,-1}
  */
  void init ( const Point & pOrigin,
              ConstAlias< DigitalKernel > fullKernel,
              ConstAlias< std::vector< PairIterators > > masks );

  /**
  * Convolve the kernel at a position \a it.
  *
  * @param[in] it (iterator of a) surfel of the shape where the convolution is computed.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  *
  * @return the estimated quantity at *it : (f*g)(t)
  */
  template< typename SurfelIterator >
  Quantity eval ( const SurfelIterator & it ) const;


  /**
  * Convolve the kernel at a position \a it and applies the functor \a functor on the result.
  *
  * @param[in] it (iterator of a) surfel of the shape where the convolution is computed.
  * @param[in] functor functor called with the result of the convolution.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam EvalFunctor type of functor on Quantity.
  *
  * @return the return quantity of functor after giving in parameter the result of the convolution at *it
  */
  template< typename SurfelIterator, typename EvalFunctor >
  typename EvalFunctor::Value eval ( const SurfelIterator & it,
                                     EvalFunctor functor ) const;


  /**
  * Convolve the kernel at all positions of the range [itBegin, itEnd[ and outputs results sequentially with \a result iterator.
  *
  * @param[in] itbegin (iterator of the) first surfel of the shape where the convolution is computed.
  * @param[in] itend (iterator of the) last (excluded) surfel of the shape where the convolution is computed.
  * @param[out] result iterator of an array where estimates quantities are set ( the estimated quantity from *itbegin till *itend (excluded)).
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam OutputIterator type of iterator on an array when Quantity are stored.
  */
  template< typename SurfelIterator, typename OutputIterator >
  void eval ( const SurfelIterator & itbegin,
              const SurfelIterator & itend,
              OutputIterator & result ) const;

  /**
  * Convolve the kernel at all positions of the range [itBegin, itEnd[ and applies the functor \a functor on results outputed sequentially with \a result iterator.
  *
  * @param[in] itbegin (iterator of the) first surfel of the shape where the convolution is computed.
  * @param[in] itend (iterator of the) last (excluded) surfel of the shape where the convolution is computed.
  * @param[out] result iterator of an array where estimates quantities are set ( the estimated quantity from *itbegin till *itend (excluded)).
  * @param[in] functor functor called with the result of the convolution.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam OutputIterator type of iterator on an array when Quantity are stored.
  * @tparam EvalFunctor type of functor on Quantity.
  */
  template< typename SurfelIterator, typename OutputIterator, typename EvalFunctor >
  void eval ( const SurfelIterator & itbegin,
              const SurfelIterator & itend,
              OutputIterator & result,
              EvalFunctor functor ) const;


  /**
  * Convolve the kernel at a position \a it.
  *
  * @param[in] it (iterator of a) surfel of the shape where the covariance matrix is computed.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  *
  * @return the covariance matrix at *it
  */
  template< typename SurfelIterator >
  CovarianceMatrix evalCovarianceMatrix ( const SurfelIterator & it ) const;

  /**
  * Convolve the kernel at a position \a it and applies the functor \a functor on the result.
  *
  * @param[in] it (iterator of a) surfel of the shape where the covariance matrix is computed.
  * @param[in] functor functor called with the result of the convolution.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam EvalFunctor type of functor on CovarianceMatrix.
  *
  * @return the result of the functor with the covariance matrix.
  */
  template< typename SurfelIterator, typename EvalFunctor >
  typename EvalFunctor::Value evalCovarianceMatrix ( const SurfelIterator & it,
                                                     EvalFunctor functor ) const;

  /**
  * Convolve the kernel at all positions of the range [itBegin, itEnd[ and outputs results sequentially with \a result iterator.
  *
  * @param[in] itbegin (iterator of the) first surfel of the shape where the covariance matrix is computed.
  * @param[in] itend (iterator of the) last (excluded) surfel of the shape where the covariance matrix is computed.
  * @param[out] result iterator of an array where estimates covariance matrix are set ( the covariance matrix from *itbegin till *itend (excluded)).
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam OutputIterator type of iterator on an array when Quantity are stored.
  */
  template< typename SurfelIterator, typename OutputIterator >
  void evalCovarianceMatrix ( const SurfelIterator & itbegin,
                              const SurfelIterator & itend,
                              OutputIterator & result ) const;

  /**
  * Convolve the kernel at all positions of the range [itBegin, itEnd[ and applies the functor \a functor on results outputed sequentially with \a result iterator.
  *
  * @param[in] itbegin (iterator of the) first surfel of the shape where the covariance matrix is computed.
  * @param[in] itend (iterator of the) last (excluded) surfel of the shape where the covariance matrix is computed.
  * @param[out] result iterator of an array where results of functor are set.
  * @param[in] functor functor called with the result of the convolution.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam OutputIterator type of iterator on an array when Quantity are stored.
  * @tparam EvalFunctor type of functor on CovarianceMatrix.
  */
  template< typename SurfelIterator, typename OutputIterator, typename EvalFunctor >
  void evalCovarianceMatrix ( const SurfelIterator & itbegin,
                              const SurfelIterator & itend,
                              OutputIterator & result,
                              EvalFunctor functor ) const;


  /**
  * Checks the validity/consistency of the object.
  * @return 'true' if the object is valid, 'false' otherwise.
  */
  bool isValid () const;

protected:

  /**
   * @brief computeCovarianceMatrix compute the covariance matrix from matrix of moments.
   *
   * @param[in] aMomentMatrix a matrix of digital moments
   * [ sum(1)
   *   sum(y) sum (x)
   *   sum(x*y) sum(y*y) sum(x*x)
   * ]
   * @param[out] aCovarianceMatrix the result covariance matrix
   */
  void computeCovarianceMatrix( const Quantity * aMomentMatrix, CovarianceMatrix & aCovarianceMatrix ) const;

  /**
   * @brief fillMoments fill the matrix of moments with a given spel.
   *
   * @param[out] aMomentMatrix a matrix of digital moments
   * [ sum(1)
   *   sum(y) sum (x)
   *   sum(x*y) sum(y*y) sum(x*x)
   * ]
   * @param[in] aSpel current spel
   * @param[in] direction true if we add the current spel, false if we remove it.
   */
  void fillMoments( Quantity* aMomentMatrix, const Spel & aSpel, double direction ) const;

  static const int nbMoments; ///< the number of moments is dependent to the dimension. In 2D, they are 6 moments such that p+q <= 2. (see method fillMoments())
  static Spel defaultInnerSpel; ///< default Spel, used as default parameter in core_eval and core_evalCovarianceMatrix functions
  static Spel defaultOuterSpel; ///< default Spel, used as default parameter in core_eval and core_evalCovarianceMatrix functions
  static Quantity defaultInnerMoments[ 6 ]; ///< default array of Quantity, used as default parameter in core_evalCovarianceMatrix function
  static Quantity defaultOuterMoments[ 6 ]; ///< default array of Quantity, used as default parameter in core_evalCovarianceMatrix function
  static Quantity defaultInnerSum; ///< default Quantity, used as default parameter in core_eval function
  static Quantity defaultOuterSum; ///< default Quantity, used as default parameter in core_eval function

  /**
   * @brief core_eval method used ( in intern by eval() ) to compute the Quantity on a given surfel (*it)
   *
   * @param[in] it (iterator of a) surfel of the shape where the convolution is computed.
   * @param[out] innerSum the result Quantity when centering with the innerSpel.
   * @param[out] outerSum the result Quantity when centering with the outerSpel.
   * @param[in] useLastResults if we can use last results (optimisation with masks)
   * @param[in,out] lastInnerSpel last inner spel. Override at end of function with current inner spel (from surfel *it). Set empty if useLastResults is false.
   * @param[in,out] lastOuterSpel last outer spel. Override at end of function with current outer spel (from surfel *it). Set empty if useLastResults is false.
   * @param[in] lastInnerSum last Quantity when centering with inner spel. Set empty if useLastResults is false.
   * @param[in] lastOuterSum last Quantity when centering with outer spel. Set empty if useLastResults is false.
   *
   * @tparam SurfelIterator type of iterator on surfel
   */
  template< typename SurfelIterator >
  bool core_eval ( const SurfelIterator & it,
                   Quantity & innerSum,
                   Quantity & outerSum,
                   bool useLastResults = false,
                   Spel & lastInnerSpel = defaultInnerSpel,
                   Spel & lastOuterSpel = defaultOuterSpel,
                   Quantity & lastInnerSum = defaultInnerSum,
                   Quantity & lastOuterSum = defaultOuterSum ) const;

  /**
   * @brief core_evalCovarianceMatrix method used ( in intern by evalCovarianceMatrix() ) to compute the covariance matrix on a given surfel (*it)
   *
   * @param[in] it (iterator of a) surfel of the shape where the convolution is computed.
   * @param[out] innerMatrix the result covariance matrix when centering with the innerSpel.
   * @param[out] outerMatrix the result covariance matrix when centering with the outerSpel.
   * @param[in] useLastResults if we can use last results (optimisation with masks)
   * @param[in,out] lastInnerSpel last inner spel. Override at end of function with current inner spel (from surfel *it). Set empty if useLastResults is false.
   * @param[in,out] lastOuterSpel last outer spel. Override at end of function with current outer spel (from surfel *it). Set empty if useLastResults is false.
   * @param[in,out] lastInnerMoments last inner moments when centering with inner spel. Override at end of function with current inner moments (from surfel *it). Set empty if useLastResults is false.
   * @param[in,out] lastOuterMoments last inner moments when centering with inner spel. Override at end of function with current outer moments (from surfel *it). Set empty if useLastResults is false.
   *
   * @tparam SurfelIterator type of iterator on surfel
   */
  template< typename SurfelIterator >
  bool core_evalCovarianceMatrix ( const SurfelIterator & it,
                                   CovarianceMatrix & innerMatrix,
                                   CovarianceMatrix & outerMatrix,
                                   bool useLastResults = false,
                                   Spel & lastInnerSpel = defaultInnerSpel,
                                   Spel & lastOuterSpel = defaultOuterSpel,
                                   Quantity * lastInnerMoments = defaultInnerMoments,
                                   Quantity * lastOuterMoments = defaultOuterMoments ) const;



  // ------------------------- Private Datas --------------------------------

private:

  const Dimension dimension; ///< Current dimension (= 2)

  const Functor & myFFunctor; ///< Const ref of the shape functor

  const KernelFunctor & myGFunctor; ///< Const ref of the kernel functor


  const KSpace & myKSpace; ///< Const ref of the shape Kspace

  Embedder myEmbedder; ///< Converter Digital point -> Euclidean point

  bool isInitFullMasks; ///< If the user uses init with masks. See init() for more information.

  bool isInitKernelAndMasks; ///< If the user uses init with masks and digital (full) kernel. See init() for more information.

  const std::vector< PairIterators > * myMasks; ///< Pointer of vector of iterators for kernel partial masks

  const DigitalKernel * myKernel; ///< Two choice to iterate over the full kernel. See init() for more information.
  const PairIterators * myKernelMask; ///< Two choice to iterate over the full kernel. See init() for more information.

  Spel myKernelSpelOrigin; ///< Copy of the origin cell of the kernel.

  // ------------------------- Hidden services ------------------------------

protected:
  /**
  * Constructor.
  * Forbidden by default (protected to avoid g++ warnings).
  */
  DigitalSurfaceConvolver ();

private:

  /**
  * Assignment.
  * @param other the object to copy.
  * @return a reference on 'this'.
  * Forbidden by default.
  */
  DigitalSurfaceConvolver & operator= ( const DigitalSurfaceConvolver & other );

  // ------------------------- Internals ------------------------------------

private:

}; // end of class DigitalSurfaceConvolver

template< typename TFunctor, typename TKernelFunctor, typename TKSpace, typename TDigitalKernel >
class DigitalSurfaceConvolver< TFunctor, TKernelFunctor, TKSpace, TDigitalKernel, 3 >
{
  // ----------------------- Types ------------------------------------------

public:

  typedef TFunctor Functor;
  typedef TKSpace KSpace;
  typedef TKernelFunctor KernelFunctor;
  typedef TDigitalKernel DigitalKernel;

  typedef Z3i::Domain Domain;

  typedef double Quantity;
  typedef PointVector< 3, Quantity > VectorQuantity;
  typedef SimpleMatrix< Quantity, 3, 3 > MatrixQuantity;
  typedef SimpleMatrix< double, 3, 3 > CovarianceMatrix;

  typedef typename KSpace::SCell Spel;
  typedef typename KSpace::Point Point;
  typedef typename KSpace::Space::RealPoint RealPoint;
  typedef Z3i::DigitalSet::ConstIterator KernelConstIterator;


  typedef std::pair< KernelConstIterator, KernelConstIterator > PairIterators;
  typedef CanonicSCellEmbedder< KSpace > Embedder;

  BOOST_CONCEPT_ASSERT (( concepts::CCellFunctor< Functor > ));
  BOOST_CONCEPT_ASSERT (( concepts::CCellFunctor< KernelFunctor > ));

  // ----------------------- Standard services ------------------------------

public:

  /**
  * Constructor.
  *
  * @param[in] f a functor f(x).
  * @param[in] g a functor g(x).
  * @param[in] space space in which the shape is defined.
  */
  DigitalSurfaceConvolver ( ConstAlias< Functor > f,
                            ConstAlias< KernelFunctor > g,
                            ConstAlias< KSpace > space );

  /**
  * Copy constructor.
  * @param other the object to clone.
  */
  DigitalSurfaceConvolver ( const DigitalSurfaceConvolver & other );

  /**
  * Destructor.
  */
  ~DigitalSurfaceConvolver() {}

  // ----------------------- Interface --------------------------------------

public:

  /**
   * Initialize the convolver using masks - allow to use the optimization with adjacent cells.
   *
   * Stores the full kernel explicitly: choose this init if you have a lot of memory or if your kernel is small
   *
   * @param[in] pOrigin center (digital point) of the kernel support.
   * @param[in] fullKernel pair of iterators of the full kernel. first is the first iterator (of spel) of the kernel support, second is the last iterator (of spel, excluded).
   * @param[in] masks Vector of iterators (of spel) of the first and last spel of each masks. They must be ordered using a trit ({0,1,2}) encoded array.
   * trit 0 => shifting_coord = -1
   * trit 1 => shifting_coord = 0
   * trit 2 => shifting_coord = 1
   * Example in 3D :      zyx                 x  y  z
   * mask[0] : base3(0) = 000 => shifting = {-1,-1,-1}
   * mask[5] : base3(5) = 012 => shifting = { 1, 0,-1}
   */
  void init ( const Point & pOrigin,
              ConstAlias< PairIterators > fullKernel,
              ConstAlias< std::vector< PairIterators > > masks );

  /**
  * Intitialize the convolver using masks - allow to use the optimization with adjacent cells.
  *
  * Stores the kernel implicitly: choose this init if you have not a lot of memory available or if your kernel size is big.
  *
  * @param[in] pOrigin center (digital point) of the kernel support.
  * @param[in] fullKernel pointer of the digital (full) kernel.
  * @param[in] masks Vector of iterators (of spel) of the first and last spel of each masks. They must be ordered using a trit ({0,1,2}) encoded array.
  * trit 0 => shifting_coord = -1
  * trit 1 => shifting_coord = 0
  * trit 2 => shifting_coord = 1
  * Example in 3D :      zyx                 x  y  z
  * mask[0] : base3(0) = 000 => shifting = {-1,-1,-1}
  * mask[5] : base3(5) = 012 => shifting = { 1, 0,-1}
  */
  void init ( const Point & pOrigin,
              ConstAlias< DigitalKernel > fullKernel,
              ConstAlias< std::vector< PairIterators > > masks );

  /**
  * Convolve the kernel at a position \a it.
  *
  * @param[in] it (iterator of a) surfel of the shape where the convolution is computed.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  *
  * @return the estimated quantity at *it : (f*g)(t)
  */
  template< typename SurfelIterator >
  Quantity eval ( const SurfelIterator & it ) const;


  /**
  * Convolve the kernel at a position \a it and applies the functor \a functor on the result.
  *
  * @param[in] it (iterator of a) surfel of the shape where the convolution is computed.
  * @param[in] functor functor called with the result of the convolution.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam EvalFunctor type of functor on Quantity.
  *
  * @return the return quantity of functor after giving in parameter the result of the convolution at *it
  */
  template< typename SurfelIterator, typename EvalFunctor >
  typename EvalFunctor::Value eval ( const SurfelIterator & it,
                                     EvalFunctor functor ) const;


  /**
  * Convolve the kernel at all positions of the range [itBegin, itEnd[ and outputs results sequentially with \a result iterator.
  *
  * @param[in] itbegin (iterator of the) first surfel of the shape where the convolution is computed.
  * @param[in] itend (iterator of the) last (excluded) surfel of the shape where the convolution is computed.
  * @param[out] result iterator of an array where estimates quantities are set ( the estimated quantity from *itbegin till *itend (excluded)).
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam OutputIterator type of iterator on an array when Quantity are stored.
  */
  template< typename SurfelIterator, typename OutputIterator >
  void eval ( const SurfelIterator & itbegin,
              const SurfelIterator & itend,
              OutputIterator & result ) const;

  /**
  * Convolve the kernel at all positions of the range [itBegin, itEnd[ and applies the functor \a functor on results outputed sequentially with \a result iterator.
  *
  * @param[in] itbegin (iterator of the) first surfel of the shape where the convolution is computed.
  * @param[in] itend (iterator of the) last (excluded) surfel of the shape where the convolution is computed.
  * @param[out] result iterator of an array where estimates quantities are set ( the estimated quantity from *itbegin till *itend (excluded)).
  * @param[in] functor functor called with the result of the convolution.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam OutputIterator type of iterator on an array when Quantity are stored.
  * @tparam EvalFunctor type of functor on Quantity.
  */
  template< typename SurfelIterator, typename OutputIterator, typename EvalFunctor >
  void eval ( const SurfelIterator & itbegin,
              const SurfelIterator & itend,
              OutputIterator & result,
              EvalFunctor functor ) const;


  /**
  * Convolve the kernel at a position \a it.
  *
  * @param[in] it (iterator of a) surfel of the shape where the covariance matrix is computed.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  *
  * @return the covariance matrix at *it
  */
  template< typename SurfelIterator >
  CovarianceMatrix evalCovarianceMatrix ( const SurfelIterator & it ) const;

  /**
  * Convolve the kernel at a position \a it and applies the functor \a functor on the result.
  *
  * @param[in] it (iterator of a) surfel of the shape where the covariance matrix is computed.
  * @param[in] functor functor called with the result of the convolution.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam EvalFunctor type of functor on CovarianceMatrix.
  *
  * @return the result of the functor with the covariance matrix.
  */
  template< typename SurfelIterator, typename EvalFunctor >
  typename EvalFunctor::Value evalCovarianceMatrix ( const SurfelIterator & it,
                                                     EvalFunctor functor ) const;

  /**
  * Convolve the kernel at all positions of the range [itBegin, itEnd[ and outputs results sequentially with \a result iterator.
  *
  * @param[in] itbegin (iterator of the) first surfel of the shape where the covariance matrix is computed.
  * @param[in] itend (iterator of the) last (excluded) surfel of the shape where the covariance matrix is computed.
  * @param[out] result iterator of an array where estimates covariance matrix are set ( the covariance matrix from *itbegin till *itend (excluded)).
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam OutputIterator type of iterator on an array when Quantity are stored.
  */
  template< typename SurfelIterator, typename OutputIterator >
  void evalCovarianceMatrix ( const SurfelIterator & itbegin,
                              const SurfelIterator & itend,
                              OutputIterator & result ) const;

  /**
  * Convolve the kernel at all positions of the range [itBegin, itEnd[ and applies the functor \a functor on results outputed sequentially with \a result iterator.
  *
  * @param[in] itbegin (iterator of the) first surfel of the shape where the covariance matrix is computed.
  * @param[in] itend (iterator of the) last (excluded) surfel of the shape where the covariance matrix is computed.
  * @param[out] result iterator of an array where results of functor are set.
  * @param[in] functor functor called with the result of the convolution.
  *
  * @tparam SurfelIterator type of iterator of a surfel on the shape.
  * @tparam OutputIterator type of iterator on an array when Quantity are stored.
  * @tparam EvalFunctor type of functor on CovarianceMatrix.
  */
  template< typename SurfelIterator, typename OutputIterator, typename EvalFunctor >
  void evalCovarianceMatrix ( const SurfelIterator & itbegin,
                              const SurfelIterator & itend,
                              OutputIterator & result,
                              EvalFunctor functor ) const;

  /**
   * Checks the validity/consistency of the object.
   * @return 'true' if the object is valid, 'false' otherwise.
   */
  bool isValid() const;

protected:

  /**
   * @brief computeCovarianceMatrix compute the covariance matrix from matrix of moments.
   *
   * @param[in] aMomentMatrix a matrix of digital moments
   * [ sum(1)
   *   sum(z) sum(y) sum (x)
   *   sum(y*z) sum(x*z) sum(x*y)
   *   sum(z*z) sum(y*y) sum(x*x)
   * ]
   * @param[out] aCovarianceMatrix the result covariance matrix
   */
  void computeCovarianceMatrix ( const Quantity * aMomentMatrix, CovarianceMatrix & aCovarianceMatrix ) const;

  /**
   * @brief fillMoments fill the matrix of moments with a given spel.
   *
   * @param[out] aMomentMatrix a matrix of digital moments
   * [ sum(1)
   *   sum(z) sum(y) sum (x)
   *   sum(y*z) sum(x*z) sum(x*y)
   *   sum(z*z) sum(y*y) sum(x*x)
   * ]
   * @param[in] aSpel current spel
   * @param[in] direction true if we add the current spel, false if we remove it.
   */
  void fillMoments ( Quantity * aMomentMatrix, const Spel & aSpel, double direction ) const;

  static const int nbMoments; ///< the number of moments is dependent to the dimension. In 3D, they are 10 moments such that p+q+s <= 2 (see method fillMoments())
  static Spel defaultInnerSpel; ///< default Spel, used as default parameter in core_eval and core_evalCovarianceMatrix functions
  static Spel defaultOuterSpel; ///< default Spel, used as default parameter in core_eval and core_evalCovarianceMatrix functions
  static Quantity defaultInnerMoments[ 10 ]; ///< default array of Quantity, used as default parameter in core_evalCovarianceMatrix function
  static Quantity defaultOuterMoments[ 10 ]; ///< default array of Quantity, used as default parameter in core_evalCovarianceMatrix function
  static Quantity defaultInnerSum; ///< default Quantity, used as default parameter in core_eval function
  static Quantity defaultOuterSum; ///< default Quantity, used as default parameter in core_eval function

  /**
   * @brief core_eval method used ( in intern by eval() ) to compute the Quantity on a given surfel (*it)
   *
   * @param[in] it (iterator of a) surfel of the shape where the convolution is computed.
   * @param[out] innerSum the result Quantity when centering with the innerSpel.
   * @param[out] outerSum the result Quantity when centering with the outerSpel.
   * @param[in] useLastResults if we can use last results (optimisation with masks)
   * @param[in,out] lastInnerSpel last inner spel. Override at end of function with current inner spel (from surfel *it). Set empty if useLastResults is false.
   * @param[in,out] lastOuterSpel last outer spel. Override at end of function with current outer spel (from surfel *it). Set empty if useLastResults is false.
   * @param[in] lastInnerSum last Quantity when centering with inner spel. Set empty if useLastResults is false.
   * @param[in] lastOuterSum last Quantity when centering with outer spel. Set empty if useLastResults is false.
   *
   * @tparam SurfelIterator type of iterator on surfel
   */
  template< typename SurfelIterator >
  bool core_eval ( const SurfelIterator & it,
                   Quantity & innerSum,
                   Quantity & outerSum,
                   bool useLastResults = false,
                   Spel & lastInnerSpel = defaultInnerSpel,
                   Spel & lastOuterSpel = defaultOuterSpel,
                   Quantity & lastInnerSum = defaultInnerSum,
                   Quantity & lastOuterSum = defaultOuterSum ) const;

  /**
   * @brief core_evalCovarianceMatrix method used ( in intern by evalCovarianceMatrix() ) to compute the covariance matrix on a given surfel (*it)
   *
   * @param[in] it (iterator of a) surfel of the shape where the convolution is computed.
   * @param[out] innerMatrix the result covariance matrix when centering with the innerSpel.
   * @param[out] outerMatrix the result covariance matrix when centering with the outerSpel.
   * @param[in] useLastResults if we can use last results (optimisation with masks)
   * @param[in,out] lastInnerSpel last inner spel. Override at end of function with current inner spel (from surfel *it). Set empty if useLastResults is false.
   * @param[in,out] lastOuterSpel last outer spel. Override at end of function with current outer spel (from surfel *it). Set empty if useLastResults is false.
   * @param[in,out] lastInnerMoments last inner moments when centering with inner spel. Override at end of function with current inner moments (from surfel *it). Set empty if useLastResults is false.
   * @param[in,out] lastOuterMoments last inner moments when centering with inner spel. Override at end of function with current outer moments (from surfel *it). Set empty if useLastResults is false.
   *
   * @tparam SurfelIterator type of iterator on surfel
   */
  template< typename SurfelIterator >
  bool core_evalCovarianceMatrix ( const SurfelIterator & it,
                                   CovarianceMatrix & innerMatrix,
                                   CovarianceMatrix & outerMatrix,
                                   bool useLastResults = false,
                                   Spel & lastInnerSpel = defaultInnerSpel,
                                   Spel & lastOuterSpel = defaultOuterSpel,
                                   Quantity * lastInnerMoments = defaultInnerMoments,
                                   Quantity * lastOuterMoments = defaultOuterMoments ) const;


  // ------------------------- Private Datas --------------------------------

private:

  const Dimension dimension; ///< Current dimension (= 3)

  const Functor & myFFunctor; ///< Const ref of the shape functor

  const KernelFunctor & myGFunctor; ///< Const ref of the kernel functor


  const KSpace & myKSpace; ///< Const ref of the shape Kspace

  Embedder myEmbedder; ///< Converter Digital point -> Euclidean point

  bool isInitFullMasks; ///< If the user uses init with masks. See init() for more information.

  bool isInitKernelAndMasks; ///< If the user uses init with masks and digital (full) kernel. See init() for more information.

  const std::vector< PairIterators > * myMasks; ///< Pointer of vector of iterators for kernel partial masks

  const DigitalKernel * myKernel; ///< Two choice to iterate over the full kernel. See init() for more information.
  const PairIterators * myKernelMask; ///< Two choice to iterate over the full kernel. See init() for more information.

  Spel myKernelSpelOrigin; ///< Copy of the origin cell of the kernel.

  // ------------------------- Hidden services ------------------------------

protected:
  /**
  * Constructor.
  * Forbidden by default (protected to avoid g++ warnings).
  */
  DigitalSurfaceConvolver ();

private:

  /**
  * Assignment.
  * @param other the object to copy.
  * @return a reference on 'this'.
  * Forbidden by default.
  */
  DigitalSurfaceConvolver & operator= ( const DigitalSurfaceConvolver & other );

  // ------------------------- Internals ------------------------------------

private:

}; // end of class DigitalSurfaceConvolver



/**
   * Overloads 'operator<<' for displaying objects of class 'DigitalSurfaceConvolver'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'DigitalSurfaceConvolver' to write.
   * @return the output stream after the writing.
   */
template< typename TF,  typename TKF, typename TKS, typename TDK, Dimension dimension >
std::ostream&
operator<< ( std::ostream & out, const DGtal::DigitalSurfaceConvolver< TF, TKF, TKS, TDK, dimension > & object );

template< typename TF,  typename TKF, typename TKS, typename TDK >
std::ostream&
operator<< ( std::ostream & out, const DGtal::DigitalSurfaceConvolver< TF, TKF, TKS, TDK, 2 > & object );

template< typename TF,  typename TKF, typename TKS, typename TDK >
std::ostream&
operator<< ( std::ostream & out, const DGtal::DigitalSurfaceConvolver<TF, TKF, TKS, TDK, 3 > & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/surfaces/DigitalSurfaceConvolver.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DigitalSurfaceConvolver_h

#undef DigitalSurfaceConvolver_RECURSES
#endif // else defined(DigitalSurfaceConvolver_RECURSES)
