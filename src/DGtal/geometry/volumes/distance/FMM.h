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
 * @file FMM.h
 *
 * @author Tristan Roussillon (\c
 * tristan.roussillon@liris.cnrs.fr ) Laboratoire d'InfoRmatique en
 * Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS,
 * France
 *
 * @date 2012/01/17
 *
 * @brief Fast Marching Method for incremental distance transform
 *
 * This file is part of the DGtal library.
 *
 */

#if defined(FMM_RECURSES)
#error Recursive header files inclusion detected in FMM.h
#else // defined(FMM_RECURSES)
/** Prevents recursive inclusion of headers. */
#define FMM_RECURSES

#if !defined FMM_h
/** Prevents repeated inclusion of headers. */
#define FMM_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/images/CImage.h"
#include "DGtal/images/ImageHelper.h"
#include "DGtal/kernel/sets/CDigitalSet.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/kernel/CPointFunctor.h"
#include "DGtal/geometry/volumes/distance/FMMPointFunctors.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace detail
  {
  /////////////////////////////////////////////////////////////////////////////
  // template class PointValueCompare
  /**
   * Description of template class 'PointValueCompare' <p>
   * \brief Aim: Small binary predicate to order candidates points 
   * according to their (absolute) distance value. 
   *
   * @tparam T model of pair Point-Value
   */
    template<typename T>
    class PointValueCompare {
    public: 
      /**
       * Comparison function
       *
       * @param a an object of type T
       * @param b another object of type T
       *
       * @return true if a < b but false otherwise
       */
      bool operator()(const T& a, const T& b) const
      {
	if ( std::abs(a.second) == std::abs(b.second) ) 
	  { //point comparison
	    return (a.first < b.first); 
	  }
	else //distance comparison
	  //(in absolute value in order to deal with
	  //signed distance values) 
	  return ( std::abs(a.second) < std::abs(b.second) ); 
      }
    };
  }

  /////////////////////////////////////////////////////////////////////////////
  // template class FMM
  /**
   * Description of template class 'FMM' <p>
   * \brief Aim: Fast Marching Method (FMM) for nd distance transforms.
   *
   * In this approach, a signed distance function is computed at 
   * each digital point by marching out from an initial set of points, 
   * for which the values of the signed distance are known. This set
   * is an initialization of the so-called @e accepted @e point @e set. 
   * Each digital point adjacent to one of the accepted points is
   * put into the so-called @e candidate @e point @e set. 
   * A tentative value is computed for its signed distance, using 
   * only the values of the accepted points lying in its neighborhood. 
   * This task is delegated to an instance of a point functor, 
   * which is defined as L2FirstOrderLocalDistance by default. 
   * However, you are free to use L2SecondOrderLocalDistance, which provides
   * more accurate distance values, L1LocalDistance and 
   * LInfLocalDistance for other norms. 
   *
   * Then the point of smallest tentative value is added to the set of
   * accepted points. The tentative values of the candidates adjacent 
   * to the newly added point are updated using the distance value
   * of the newly added point. The search of the point of smallest
   * tentative value is accelerated using a STL set of pairs (point, 
   * tentative value).  
   *
   * @tparam TImage  any model of CImage
   * @tparam TSet  any model of CDigitalSet
   * @tparam TPointPredicate  any model of concepts::CPointPredicate, 
   * used to bound the computation within a domain 
   * @tparam TPointFunctor  any model of CPointFunctor,
   * used to compute the new distance value
   *
   * You can define the FMM type as follows: 
   @snippet geometry/volumes/distance/exampleFMM3D.cpp FMMSimpleTypeDef3D
   *
   * You can construct and initialize the external data structures as follows: 
   @snippet geometry/volumes/distance/exampleFMM3D.cpp FMMSimpleInit3D
   *
   * Then, the algorithm is ran as follows: 
   @snippet geometry/volumes/distance/exampleFMM3D.cpp FMMUsage3D
   *
   * @see exampleFMM2D.cpp
   * @see exampleFMM3D.cpp
   * @see testFMM.cpp
   */
  template <typename TImage, typename TSet, typename TPointPredicate, 
	    typename TPointFunctor = L2FirstOrderLocalDistance<TImage,TSet> >
  class FMM
  {

    // ----------------------- Types ------------------------------
  public:


    //concept assert
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImage> ));
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet<TSet> ));
    BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate<TPointPredicate> ));
    BOOST_CONCEPT_ASSERT(( concepts::CPointFunctor<TPointFunctor> ));

    typedef TImage Image; 
    typedef TSet AcceptedPointSet; 
    typedef TPointPredicate PointPredicate; 

    //points
    typedef typename Image::Point Point;
    BOOST_STATIC_ASSERT(( boost::is_same< Point, typename AcceptedPointSet::Point >::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< Point, typename PointPredicate::Point >::value ));

    //dimension
    typedef typename Point::Dimension Dimension;
    static const Dimension dimension; 

    //distance
    typedef TPointFunctor PointFunctor; 
    typedef typename PointFunctor::Value Value; 


  private: 

    //intern data types
    typedef std::pair<Point, Value> PointValue; 
    typedef std::set<PointValue,
		     detail::PointValueCompare<PointValue> > CandidatePointSet; 
    typedef DGtal::uint64_t Area;

    // ------------------------- Private Datas --------------------------------
  private:
    
    /**
     * Reference on the image
     */
    Image& myImage; 

    /**
     * Reference on the set of accepted points
     */
    AcceptedPointSet& myAcceptedPoints; 

    /**
     * Set of candidate points
     */
    CandidatePointSet myCandidatePoints; 

    /**
     * Pointer on the point functor used to deduce 
     * the distance of a new point
     * from the distance of its neighbors
     */
    PointFunctor* myPointFunctorPtr; 

    /**
     * 'true' if @a myPointFunctorPtr is an owning pointer
     * (default case), 'false' if it is an aliasing pointer
     * on a point functor given at construction
     */
    const bool myFlagIsOwning; 

    /**
     * Constant reference on a point predicate that returns 
     * 'true' inside the domain 
     * where the distance transform is performed
     */
    const PointPredicate& myPointPredicate; 

    /**
     * Area threshold (in number of accepted points) 
     * above which the propagation stops
     */
    Area myAreaThreshold; 

    /**
     * Value threshold above which the propagation stops
     */
    Value myValueThreshold; 

    /**
     * Min value
     */
    Value myMinValue; 

    /**
     * Max value
     */
    Value myMaxValue; 


    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor.
     *
     * @see init
     */
    FMM(Image& aImg, AcceptedPointSet& aSet,
        ConstAlias<PointPredicate> aPointPredicate);
    
    /**
     * Constructor.
     *
     * @see init
     */
    FMM(Image& aImg, AcceptedPointSet& aSet, 
        ConstAlias<PointPredicate> aPointPredicate, 
        const Area& aAreaThreshold, const Value& aValueThreshold);
    
    /**
     * Constructor.
     *
     * @see init
     */
    FMM(Image& aImg, AcceptedPointSet& aSet,
        ConstAlias<PointPredicate> aPointPredicate, 
        PointFunctor& aPointFunctor );
    
    /**
     * Constructor.
     *
     * @see init
     */
    FMM(Image& aImg, AcceptedPointSet& aSet, 
        ConstAlias<PointPredicate> aPointPredicate, 
        const Area& aAreaThreshold, const Value& aValueThreshold,
        PointFunctor& aPointFunctor );
    
    /**
     * Destructor.
     */
    ~FMM();

  
    // ----------------------- Interface --------------------------------------
  public:
    
    /** 
     * Computation of the signed distance function by marching out
     * from the initial set of accepted points. 
     * While it is possible, the candidate of min distance is 
     * inserted into the set of accepted points. 
     *
     * @see computeOneStep
     */
    void compute();
 
    /** 
     * Inserts the candidate of min distance into the set 
     * of accepted points if it is possible and then 
     * updates the distance values associated to the candidate points. 
     *
     * @param aPoint inserted point (if inserted)
     * @param aValue its distance value (if inserted)
     *
     * @return 'true' if the point of min distance is accepted
     * 'false' otherwise.
     *
     * @see addNewAcceptedPoint
     */
    bool computeOneStep(Point& aPoint, Value& aValue);

    /** 
     * Minimal distance value in the set of accepted points. 
     *
     * @return minimal distance value.
     */
    Value min() const;

    /** 
     * Maximal distance value in the set of accepted points. 
     *
     * @return maximal distance value
     */
    Value max() const;

    /** 
     * Computes the minimal distance value in the set of accepted points. 
     *
     * NB: in O(n log n) where n is the size of the set
     *
     * @return minimal distance value.
     */
    Value getMin() const;

    /** 
     * Computes the maximal distance value in the set of accepted points. 
     *
     * NB: in O(n log n) where n is the size of the set
     *
     * @return maximal distance value.
     */
    Value getMax() const;

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

    // ------------------------- static functions for init --------------------


    /**
     * Initialize @a aImg and @a aSet from the points of the range [@a itb , @a ite ) 
     * Assign a distance equal to @a aValue  
     *
     * @param itb begin iterator (on points)
     * @param ite end iterator (on points)
     * @param aImg the distance image
     * @param aSet the set of points for which the distance has been assigned
     * @param aValue distance default value
     */
    template <typename TIteratorOnPoints>
    static void initFromPointsRange(const TIteratorOnPoints& itb, const TIteratorOnPoints& ite, 
				Image& aImg, AcceptedPointSet& aSet, 
				const Value& aValue);

    /**
     * Initialize @a aImg and @a aSet from the points 
     * incident to the signed cells of the range [@a itb , @a ite ) 
     * Assign to the inner points a distance equal to - @a aValue 
     * if @a aFlagIsPositive is 'true' (default) but @a aValue otherwise, 
     * and conversely for the outer points.  
     *
     * @param aK a Khalimsky space in which the signed cells live.
     * @param itb begin iterator (on signed cells)
     * @param ite end iterator (on signed cells)
     * @param aImg the distance image
     * @param aSet the set of points for which the distance has been assigned
     * @param aValue distance default value
     * @param aFlagIsPositive The flag controlling the \a aValue sign assigned to inner points.
     */
    template <typename KSpace, typename TIteratorOnBels>
    static void initFromBelsRange(const KSpace& aK, 
				  const TIteratorOnBels& itb, const TIteratorOnBels& ite, 
				  Image& aImg, AcceptedPointSet& aSet, 
				  const Value& aValue, 
				  bool aFlagIsPositive = true);

    /**
     * Initialize @a aImg and @a aSet from the points 
     * incident to the signed cells of the range [@a itb , @a ite ). 
     * If @a aFlagIsPositive is 'true' (default), assign to the 
     * inner points a negative distance interpolated from 
     * the distance values of the neighbors given by the function @a aF 
     * and assign to the outer points a positive distance interpolated 
     * from the distance values of the neighbors given by the function @a aF. 
     * Swap the signs if @a aFlagIsPositive is 'false'. 
     *
     * @param aK a Khalimsky space in which the signed cells live.
     * @param itb begin iterator (on signed cells)
     * @param ite end iterator (on signed cells)
     * @param aF any implicit function
     * @param aImg the distance image
     * @param aSet the set of points for which the distance has been assigned
     * @param aFlagIsPositive The flag controlling the \a aValue sign assigned to inner points.
     */
    template <typename KSpace, typename TIteratorOnBels, typename TImplicitFunction>
    static void initFromBelsRange(const KSpace& aK, 
				  const TIteratorOnBels& itb, const TIteratorOnBels& ite,
				  const TImplicitFunction& aF, 
				  Image& aImg, AcceptedPointSet& aSet, 
				  bool aFlagIsPositive = true);


    /**
     * Initialize @a aImg and @a aSet from the inner and outer points 
     * of the range [@a itb , @a ite ) of pairs of points.  
     * Assign to the inner points a distance equal to - @a aValue 
     * if @a aFlagIsPositive is 'true' (default) but @a aValue otherwise, 
     * and conversely for the outer points.  
     *
     * @param itb begin iterator (on points)
     * @param ite end iterator (on points)
     * @param aImg the distance image
     * @param aSet the set of points for which the distance has been assigned
     * @param aValue distance default value
     * @param aFlagIsPositive The flag controlling the \a aValue sign assigned to inner points.
     */
    template <typename TIteratorOnPairs>
    static void initFromIncidentPointsRange(const TIteratorOnPairs& itb, const TIteratorOnPairs& ite, 
				   Image& aImg, AcceptedPointSet& aSet, 
				   const Value& aValue, 
				   bool aFlagIsPositive = true);

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    FMM ( const FMM & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    FMM & operator= ( const FMM & other );

    // ------------------------- Internals ------------------------------------
  private:

    /** 
     * Initialize the set of candidate points
     */
    void init();
    
    /** 
     * Inserts the candidate of min distance into the set 
     * of accepted points and updates the distance values
     * of the candidate points. 
     *
     * @param aPoint inserted point (if true)
     * @param aValue distance value of the inserted point (if true)
     *
     * @return 'true' if the point of min distance is accepted
     * 'false' otherwise.
     */
    bool addNewAcceptedPoint(Point& aPoint, Value& aValue);

    /** 
     * Updates the distance values of the neighbors of @a aPoint
     * belonging to the set of accepted points
     *
     * @param aPoint any point
     */
    void update(const Point& aPoint);

    /** 
     * Tests a new point as a candidate. 
     * If it is not yet accepted 
     * and if the point predicate returns 'true', 
     * computes its distance and inserts it 
     * into the set of candidate points. 
     *
     * @param aPoint any point
     *
     * @return 'true' if inserted,
     * 'false' otherwise.
     */
    bool addNewCandidate(const Point& aPoint);


  }; // end of class FMM


  /**
   * Overloads 'operator<<' for displaying objects of class 'FMM'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'FMM' to write.
   * @return the output stream after the writing.
   */
  template <typename TImage, typename TSet, typename TPointPredicate, typename TPointFunctor >
  std::ostream&
  operator<< ( std::ostream & out, const FMM<TImage, TSet, TPointPredicate, TPointFunctor> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/volumes/distance/FMM.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined FMM_h

#undef FMM_RECURSES
#endif // else defined(FMM_RECURSES)
