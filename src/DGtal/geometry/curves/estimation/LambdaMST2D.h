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
 * @file LambdaMST2D.h
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, France
 *
 * @date 2014/10/03
 *
 * This file is part of the DGtal library.
 */

#if defined(LAMBDAMST2D_RECURSES)
#error Recursive header files inclusion detected in LambdaMST2D.h
#else // defined(LAMBDAMST2D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define LAMBDAMST2D_RECURSES

#if !defined LAMBDAMST2D_h
/** Prevents repeated inclusion of headers. */
#define LAMBDAMST2D_h

#include <algorithm>
#include <iterator>
#include <cmath>
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/CSpace.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/geometry/curves/estimation/FunctorsLambdaMST.h"
#include "DGtal/geometry/curves/CForwardSegmentComputer.h"
#include "DGtal/geometry/curves/estimation/CLMSTTangentFromDSS.h"

namespace DGtal {
  /**
   * Aim: Implementation of Lambda MST tangent estimators. This class is a model of CCurveLocalGeometricEstimator.
   * @tparam TSpace model of CSpace
   * @tparam TSegmentation tangential cover obtained by a segmentation of a 2D digital curve by maximal straight segments
   * @tparam Functor model of CLMSTTangentFrom2DSS
   */
  template < typename TSpace, typename TSegmentation, typename Functor >
  class LambdaMST2DEstimator
  {
    //Checking concepts
    BOOST_STATIC_ASSERT(( TSpace::dimension == 2 ));
    BOOST_CONCEPT_ASSERT(( concepts::CSpace<TSpace> ));
    BOOST_CONCEPT_ASSERT(( concepts::CLMSTTangentFromDSS<Functor> ));
    BOOST_CONCEPT_ASSERT(( concepts::CForwardSegmentComputer<typename TSegmentation::SegmentComputer> ));
    // ----------------------- Types ------------------------------
  public:
    /// Tangential cover algorithm
    typedef TSegmentation Segmentation;
    /// Curve segmentation algorithm
    typedef typename TSegmentation::SegmentComputer SegmentComputer;
    /// Type of iterator, at least readable and forward
    typedef typename SegmentComputer::ConstIterator ConstIterator;
    /// Type returned by model of CLMSTTangentFrom2DSS
    typedef typename Functor::Value Value;
    /// Type of 3d real vector
    typedef typename TSpace::RealVector RealVector;
    /// Type of 3d real point
    typedef typename TSpace::Point Point;
    
    // ----------------------- Interface --------------------------------------
  public:
    //! Default constructor.
    LambdaMST2DEstimator();
    
    /**
     * Initialization.
     * @param itb begin iterator
     * @param ite end iterator
     */
    void init ( const ConstIterator & itb, const ConstIterator & ite );
    
    /**
     * Attach tangential cover computer.
     * @param SegmentComputer - DSS segmentation algorithm
     */
    void attach ( Alias<TSegmentation> SegmentComputer );
    
    /**
     * @param it ConstIterator defined over the underlying curve
     * @return tangent direction
     */
    RealVector eval ( const ConstIterator & it );
    
    /**
     * @tparam OutputIterator writable iterator.
     * More efficient way to compute tangent directions for all points of a curve.
     * @param itb begin iterator
     * @param ite end iterator
     * @param result writable iterator over a container which stores estimated tangent directions.
     */
    template <typename OutputIterator>
    OutputIterator eval ( const ConstIterator & itb, const ConstIterator & ite, 
                         OutputIterator result );
    
    // ----------------------- Standard services ------------------------------
  public:
    
    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;
    // ------------------------- Internals ------------------------------------
  protected:
    
    /**
     * @brief Accumulate partial results obtained for each point.
     * 
     * @tparam OutputIterator writable iterator.
     * @param outValues partial results for each point
     * @param result writable iterator over a container which stores estimated tangent directions.
     */
    template <typename OutputIterator>
    void accumulate ( std::vector < Value > & outValues, OutputIterator & result );
    
    // ------------------------- Private Datas --------------------------------
  private:
    
    /**
     * Iterator which corresponds to the beginning of a valid range - [myBegin, myEnd)
     */
    ConstIterator myBegin;
    /**
     * Iterator which corresponds to the end of a valid range - [myBegin, myEnd)
     */
    ConstIterator myEnd;
    /**
     * Functor which takes:
     * reference to digital straight segment - DSS, position of given point in DSS and length of DSS
     * and returns DSS's direction and the eccentricity of the point in the DSS.
     */
    Functor myFunctor;
    /**
     * Pointer to a curve segmentation algorithm.
     */
    TSegmentation * dssSegments;
    
  }; // end of class LambdaMST2DEstimator
  
  //-------------------------------------------------------------------------------------------
  
  // Template class LambdaMST2D
  /**
   * \brief Aim: Simplify creation of Lambda MST tangent estimator.
   * @tparam DSSSegmentationComputer tangential cover obtained by segmentation of a 2D digital curve by maximal straight segments
   * @tparam LambdaFunction Lambda functor @see FunctorsLambdaMST.h
   */
  template < typename DSSSegmentationComputer, typename LambdaFunction = functors::Lambda64Function >
  class LambdaMST2D: 
  public LambdaMST2DEstimator < Z2i::Space, DSSSegmentationComputer,
    TangentFromDSS2DFunctor < typename DSSSegmentationComputer::SegmentComputer, LambdaFunction > >
    {
      typedef LambdaMST2DEstimator < Z2i::Space, DSSSegmentationComputer,
      TangentFromDSS2DFunctor < typename DSSSegmentationComputer::SegmentComputer, LambdaFunction> > Super;
      
    public: 
      /**
       * Default Constructor.
       */
      LambdaMST2D (): Super() {}
    };
}// namespace DGtal

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions
#include "DGtal/geometry/curves/estimation/LambdaMST2D.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined LAMBDAMST2D_h

#undef LAMBDAMST2D_RECURSES
#endif // else defined(LAMBDAMST2D_RECURSES)
