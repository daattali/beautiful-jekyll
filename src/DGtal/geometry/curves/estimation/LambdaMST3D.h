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
 * @file LambdaMST3D.h
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, France
 *
 * @date 2014/10/06
 *
 * This file is part of the DGtal library.
 */

#if defined(LAMBDAMST3D_RECURSES)
#error Recursive header files inclusion detected in LambdaMST3D.h
#else // defined(LAMBDAMST3D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define LAMBDAMST3D_RECURSES

#if !defined LAMBDAMST3D_h
/** Prevents repeated inclusion of headers. */
#define LAMBDAMST3D_h

#include <algorithm>
#include <iterator>
#include <cmath>
#include <map>
#include <DGtal/base/Common.h>
#include <DGtal/helpers/StdDefs.h>
#include "DGtal/kernel/CSpace.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/geometry/curves/estimation/FunctorsLambdaMST.h"
#include "DGtal/geometry/curves/CForwardSegmentComputer.h"
#include "DGtal/geometry/curves/estimation/CLMSTTangentFromDSS.h"

namespace DGtal {
  /**
   * Aim: Implement Lambda MST tangent estimators. This class is a model of CCurveLocalGeometricEstimator.
   * @tparam TSpace model of CSpace
   * @tparam TSegmentation tangential cover obtained by a segmentation of a 2D digital curve by maximal straight segments
   * @tparam Functor model of CLMSTTangentFrom2DSS
   */
  template < typename TSpace, typename TSegmentation, typename Functor >
  class LambdaMST3DEstimator
  {
  public: 
    //Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CSpace<TSpace> ));
    BOOST_STATIC_ASSERT(( TSpace::dimension == 3 ));
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
    
    // ----------------------- Standard services ------------------------------
  public:
    //! Default constructor.
    LambdaMST3DEstimator();
    
    /**
     * Initialization.
     * @param itb begin iterator
     * @param ite end iterator
     */
    void init ( const ConstIterator& itb, const ConstIterator& ite );
    
    /**
     * @param segmentComputer - DSS segmentation algorithm
     */
    void attach ( Alias<TSegmentation> segmentComputer );
    
    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;
    
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
    
    // ------------------------- Internals ------------------------------------
  protected:
    
    /**
     * @brief Accumulate partial results obtained for each point.
     * In 3D it can happen that DSSs' direction vectors over same point are opposite.
     * To avoid this problem we measure angle between segments' direction vectors and if this angle
     * is bigger than \f$\pi/2\f$, then one of the vectors is reversed. 
     * Finally, tangent direction is estimated and stored.
     * 
     * @tparam OutputIterator writable iterator.
     * @param outValues partial results for each point
     * @param itb begin iterator
     * @param ite end iterator
     * @param result writable iterator over a container which stores estimated tangent directions.
     */
    template <typename OutputIterator>
    void accumulate ( std::multimap < Point, Value > & outValues, const ConstIterator& itb, const ConstIterator& ite, OutputIterator & result );
    
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
     * Pointer to a curve segmentation algorithm.
     */
    TSegmentation * dssSegments;
    /**
     * Functor which takes:
     * reference to digital straight segment - DSS, position of given point in DSS and length of DSS
     * and returns DSS's direction and the eccentricity of the point in the DSS.
     */
    Functor myFunctor;
    
  }; // end of class LambdaTangentFromDSSEstimator
  
  //-------------------------------------------------------------------------------------------
  
  // Template class LambdaMST3D
  /**
   * \brief Aim: Simplify creation of Lambda MST tangent estimator.
   * @tparam DSSSegmentationComputer tangential cover obtained by segmentation of a 2D digital curve by maximal straight segments
   * @tparam LambdaFunction Lambda functor @see FunctorsLambdaMST.h
   */
  template < typename DSSSegmentationComputer, typename LambdaFunction = functors::Lambda64Function>
  class LambdaMST3D:
  public LambdaMST3DEstimator<Z3i::Space, DSSSegmentationComputer,
    TangentFromDSS3DFunctor< typename DSSSegmentationComputer::SegmentComputer, LambdaFunction> >
    {
      typedef 
      LambdaMST3DEstimator<Z3i::Space, DSSSegmentationComputer,
      TangentFromDSS3DFunctor< typename DSSSegmentationComputer::SegmentComputer, LambdaFunction> > Super;
      
    public: 
      /**
       * Default Constructor.
       */
      LambdaMST3D() : Super() {}
    };
}// namespace DGtal

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions
#include "DGtal/geometry/curves/estimation/LambdaMST3D.ih"
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined LAMBDAMST3D_h

#undef LAMBDAMST3D_RECURSES
#endif // else defined(LAMBDAMST3D_RECURSES)
