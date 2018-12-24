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
 * @file FMMPointFunctors.h
 *
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr ) 
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS,
 * France
 *
 * @date 2012/02/21
 *
 * @brief Distance computation within a small neighborhood around a point
 *
 * This file is part of the DGtal library.
 *
 */

#if defined(FMMPointFunctors_RECURSES)
#error Recursive header files inclusion detected in FMMPointFunctors.h
#else // defined(FMMPointFunctors_RECURSES)
/** Prevents recursive inclusion of headers. */
#define FMMPointFunctors_RECURSES

#if !defined FMMPointFunctors_h
/** Prevents repeated inclusion of headers. */
#define FMMPointFunctors_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"

#include "DGtal/kernel/sets/CDigitalSet.h"
#include "DGtal/kernel/CPointFunctor.h"
#include "DGtal/images/CImage.h"
#include "DGtal/images/ImageHelper.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  ///////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  // template class L2FirstOrderLocalDistance
  /**
   * Description of template class 'L2FirstOrderLocalDistance' <p>
   * \brief Aim: Class for the computation of the Euclidean distance
   * at some point p, from the available distance values of some points 
   * lying in the 1-neighborhood of p (ie. points at a L1-distance to p
   * equal to 1). 
   *
   * The computed value is such that the upwind gradient of the 
   * distance map is one, ie. it is the minimum solution \f$ \Phi \f$ 
   * over all quadrants, verifying the following quadratic equation:
   * \f$ \sum_{i = 1 \ldots d } ( \Phi - \Phi_i )^2 = 1 \f$
   * where \f$ \Phi_i \f$ is the distance value of the point preceeding
   * or following p along the \f$ i \f$ axis. 
   *
   * @note This class deals with positive or negative distance values
   * (0 is arbitrarily considered as a positive value, ie. starting with
   * a seed of null value, you must get positive values). 
   * However, the behavior is undefined when there are both positive
   * and negative distance values in the neighborhood of p. 
   *
   * It is a model of CPointFunctor.
   *
   * @tparam TImage model of CImage used for the mapping point-distance value
   * @tparam TSet model of CDigitalSet for storing points whose distance value is known
   *
   * @see FMM
   */
  template <typename TImage, typename TSet>
  class L2FirstOrderLocalDistance
  {

    // ----------------------- Types ------------------------------
  public:


    /// image
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImage> ));
    typedef TImage Image;
    typedef typename Image::Point Point;
    typedef typename Image::Value Value; 

    /// set
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet<TSet> ));
    typedef TSet Set;
    BOOST_STATIC_ASSERT(( boost::is_same< Point, typename TSet::Point >::value ));

  private: 

    typedef std::vector<Value> Values; 
  
    // ----------------------- Data -------------------------------------
  public: 
    /// Aliasing pointer on the underlying image
    Image* myImgPtr; 
    /// Aliasing pointer on the underlying set
    Set* mySetPtr; 


    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Constructor from an image and a set. 
     * NB: only pointers are stored
     *
     * @param aImg any distance map
     * @param aSet any digital set
     */
    L2FirstOrderLocalDistance(Image& aImg, TSet& aSet);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    L2FirstOrderLocalDistance ( const L2FirstOrderLocalDistance & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    L2FirstOrderLocalDistance & operator= ( const L2FirstOrderLocalDistance & other); 

    /**
     * Destructor.
     * Does nothing.
     */
    ~L2FirstOrderLocalDistance(); 

    /** 
     * Euclidean distance computation at @a aPoint , 
     * from the available distance values
     * of the 1-neighbors of @a aPoint  .
     *
     * @param aPoint the point for which the distance is computed
     *
     * @return the distance value at @a aPoint.
     *
     */
    Value operator() (const Point& aPoint);

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    // ----------------------- Internals -------------------------------------

  private: 

    /**
     * Returns an approximation of the Euclidean distance 
     * at some point, knowing the distance of its neighbors
     * 
     * @param aValueList  the distance of (some of) the neighbors
     * @return the computed distance.
     */
    Value compute(Values& aValueList) const; 


    /**
     * Returns the squared euclidean norm of the gradient 
     * of the distance map
     * 
     * @param aValue  the distance value of the point where the gradient is computed
     * @param aValueList  the distance value of (some of) the neighbors
     *
     * @return the computed gradient norm.
     */
    Value gradientNorm(const Value& aValue, const Values& aValueList) const;
  }; 

  /////////////////////////////////////////////////////////////////////////////
  // template class L2SecondOrderLocalDistance
  /**
   * Description of template class 'L2SecondOrderLocalDistance' <p>
   * \brief Aim: Class for the computation of the Euclidean distance
   * at some point p, from the available distance values of some points 
   * lying in the neighborhood of p, such that only one of their
   * coordinate differ from the coordinates of p by at most two. 
   *
   * Like L2FirstOrderLocalDistance, the computed value is such that
   * the upwind gradient of the distance map is one, but instead of 
   * using first-order accurate forward and backward differences, 
   * L2SecondOrderLocalDistance uses second-order accurate forward 
   * and backward difference whenever there are enough points whose
   * distance values are known in order to evaluate these differences. 
   *
   * @note This class deals with positive or negative distance values
   * (0 is arbitrarily considered as a positive value, ie. starting with
   * a seed of null value, you must get positive values). 
   * However, the behavior is undefined when there are both positive
   * and negative distance values in the neighborhood of p. 
   *
   * It is a model of CPointFunctor.
   *
   * @tparam TImage model of CImage used for the mapping point-distance value
   * @tparam TSet model of CDigitalSet for storing points whose distance value is known
   *
   * @see FMM
   */
  template <typename TImage, typename TSet>
  class L2SecondOrderLocalDistance
  {

    // ----------------------- Types ------------------------------
  public:


    /// image
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImage> ));
    typedef TImage Image;
    typedef typename Image::Point Point;
    typedef typename Image::Value Value; 

    /// set
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet<TSet> ));
    typedef TSet Set;
    BOOST_STATIC_ASSERT(( boost::is_same< Point, typename TSet::Point >::value ));

  private: 

    typedef std::pair<double, Value> CoeffValue; 
    typedef std::vector<CoeffValue> List; 
  
    // ----------------------- Data -------------------------------------
  public: 
    /// Aliasing pointer on the underlying image
    Image* myImgPtr; 
    /// Aliasing pointer on the underlying set
    Set* mySetPtr; 


    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Constructor from an image and a set. 
     * NB: only pointers are stored
     *
     * @param aImg any distance map
     * @param aSet any digital set
     */
    L2SecondOrderLocalDistance(Image& aImg, TSet& aSet);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    L2SecondOrderLocalDistance ( const L2SecondOrderLocalDistance & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    L2SecondOrderLocalDistance & operator= ( const L2SecondOrderLocalDistance & other); 

    /**
     * Destructor.
     * Does nothing.
     */
    ~L2SecondOrderLocalDistance(); 

    /** 
     * Euclidean distance computation at @a aPoint , 
     * from the available distance values
     * of the 1-neighbors of @a aPoint  .
     *
     * @param aPoint the point for which the distance is computed
     *
     * @return the distance value at @a aPoint.
     *
     */
    Value operator() (const Point& aPoint);

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    // ----------------------- Internals -------------------------------------

  private: 

    /**
     * Returns an approximation of the Euclidean distance 
     * at some point, knowing the distance of its neighbors
     * 
     * @param aList  the distance of (some of) the neighbors
     * @return the computed distance.
     */
    Value compute(List& aList) const; 


    /**
     * Returns the combination of two distance values 
     * for the second-order accurate difference
     * 
     * @param aValue1 first value
     * @param aValue2 second value
     *
     * @return the resulting value.
     */
    Value getValue(const Value& aValue1, const Value& aValue2) const;
  }; 


  /////////////////////////////////////////////////////////////////////////////
  // template class LInfLocalDistance
  /**
   * Description of template class 'LInfLocalDistance' <p>
   * \brief Aim: Class for the computation of the LInf-distance
   * at some point p, from the available distance values of some points 
   * lying in the 1-neighborhood of p (ie. points at a L1-distance to p
   * equal to 1). 
   *
   * If there is only one available distance value v in the 1-neighborhood of p,
   * the computed value is merely incremented or decremented. 
   * Otherwise, it is the maximum over all
   * the available distance value in the 1-neighborhood of p. 
   *
   * It is a model of CPointFunctor.
   *
   * @tparam TImage model of CImage used for the mapping point-distance value
   * @tparam TSet model of CDigitalSet for storing points whose distance value is known
   *
   * @see FMM
   */
  template <typename TImage, typename TSet>
  class LInfLocalDistance
  {
    // ----------------------- Types ------------------------------
  public:


    /// image
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImage> ));
    typedef TImage Image;
    typedef typename Image::Point Point;
    typedef typename Image::Value Value; 

    /// set
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet<TSet> ));
    typedef TSet Set;
    BOOST_STATIC_ASSERT(( boost::is_same< Point, typename TSet::Point >::value ));

  private: 

    typedef std::vector<Value> Values; 

    // ----------------------- Data -------------------------------------
  public: 
    /// Aliasing pointer on the underlying image
    Image* myImgPtr; 
    /// Aliasing pointer on the underlying set
    Set* mySetPtr; 


    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Constructor from an image and a set. 
     * NB: only pointers are stored
     *
     * @param aImg any distance map
     * @param aSet any digital set
     */
    LInfLocalDistance(Image& aImg, TSet& aSet);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    LInfLocalDistance ( const LInfLocalDistance & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    LInfLocalDistance & operator= ( const LInfLocalDistance & other); 

    /**
     * Destructor.
     * Does nothing.
     */
    ~LInfLocalDistance(); 


    /** 
     * LInf-distance computation at @a aPoint , 
     * from the available distance values
     * of the 1-neighbors of @a aPoint .
     *
     * @param aPoint the point for which the distance is computed
     *
     * @return the distance value at @a aPoint.
     *
     */
    Value operator() (const Point& aPoint);

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    // ----------------------- Internals -------------------------------------

  private: 

    /**
     * Returns the LInf-distance at some point, 
     * knowing the distance of its neighbors
     * 
     * @param aValueList  the distance of (some of) the neighbors
     * @return the computed distance.
     */
    Value compute(Values& aValueList) const; 

  }; 

  /////////////////////////////////////////////////////////////////////////////
  // template class L1LocalDistance
  /**
   * Description of template class 'L1LocalDistance' <p>
   * \brief Aim: Class for the computation of the L1-distance
   * at some point p, from the available distance values of some points 
   * lying in the 1-neighborhood of p (ie. points at a L1-distance to p
   * equal to 1). 
   *
   * The computed value is merely the minimum over all
   * the available distance values in the 1-neighborhood of p, 
   * plus one.  
   *
   * It is a model of CPointFunctor.
   *
   * @tparam TImage model of CImage used for the mapping point-distance value
   * @tparam TSet model of CDigitalSet for storing points whose distance value is known
   *
   * @see FMM
   */
  template <typename TImage, typename TSet>
  class L1LocalDistance
  {
    // ----------------------- Types ------------------------------
  public:


    /// image
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImage> ));
    typedef TImage Image;
    typedef typename Image::Point Point;
    typedef typename Image::Value Value; 

    /// set
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet<TSet> ));
    typedef TSet Set;
    BOOST_STATIC_ASSERT(( boost::is_same< Point, typename TSet::Point >::value ));

  private: 

    typedef std::vector<Value> Values; 

    // ----------------------- Data -------------------------------------
  public: 
    /// Aliasing pointer on the underlying image
    Image* myImgPtr; 
    /// Aliasing pointer on the underlying set
    Set* mySetPtr; 

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Constructor from an image and a set. 
     * NB: only pointers are stored
     *
     * @param aImg any distance map
     * @param aSet any digital set
     */
    L1LocalDistance(Image& aImg, TSet& aSet);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    L1LocalDistance ( const L1LocalDistance & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    L1LocalDistance & operator= ( const L1LocalDistance & other); 

    /**
     * Destructor.
     * Does nothing.
     */
    ~L1LocalDistance(); 

    /** 
     * L1-distance computation at @a aPoint , 
     * from the available distance values
     * of the 1-neighbors of @a aPoint .
     *
     * @param aPoint the point for which the distance is computed
     *
     * @return the distance value at @a aPoint.
     */
    Value operator() (const Point& aPoint);

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    // ----------------------- Internals -------------------------------------

  private: 

    /**
     * Returns the L1-distance at some point, 
     * knowing the distance of its neighbors
     * 
     * @param aValueList  the distance of (some of) the neighbors
     * @return the computed distance.
     */
    Value compute(Values& aValueList) const; 

  }; 


  /////////////////////////////////////////////////////////////////////////////
  // template class L2FirstOrderLocalDistanceFromCells
  /**
   * Description of template class 'L2FirstOrderLocalDistanceFromCells' <p>
   * \brief Aim: Class for the computation of the Euclidean distance
   * at some point p, from the available distance values in the neighborhood of p. 
   * Contrary to L2FirstOrderLocalDistance, the distance values are not available
   * from the points adjacent to p but instead from the (d-1)-cells lying between p 
   * and these points.   
   *
   * @note The stored values are expected to be the distance of the interface
   * to the points directly incident to the cells and must be between 0 and 1. 
   *
   * @tparam TKSpace a model of cellular grid
   * @tparam TMap a model of associative container used for the mapping cells-value
   * @tparam isIndirect a bool equal to 'false' if the tested points are expected to be 
   * directly incident to the cells (default) and 'true' otherwise 
   *
   * @see initFromBelsRange FMM
   */
  template <typename TKSpace, typename TMap, bool isIndirect = false>
  class L2FirstOrderLocalDistanceFromCells
  {

    // ----------------------- Types ------------------------------
  public:


    /// map
    typedef TMap Map;
    typedef typename Map::mapped_type Value; 

    /// cellular grid
    typedef TKSpace KSpace; 
    typedef typename KSpace::Point Point; 
    typedef typename KSpace::Cell Cell; 

  private: 

    typedef std::vector<Value> Values; 
  
    // ----------------------- Data -------------------------------------
  public: 
    /// Aliasing pointer on the underlying cellular grid
    const KSpace* myKSpace; 
    /// Aliasing pointer on the underlying mapping
    Map* myMap; 

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Constructor from a space and a map. 
     * NB: only pointers are stored
     *
     * @param aK   a space.
     * @param aMap any distance map
     */
    L2FirstOrderLocalDistanceFromCells( ConstAlias<KSpace> aK, Map& aMap);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    L2FirstOrderLocalDistanceFromCells ( const L2FirstOrderLocalDistanceFromCells & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    L2FirstOrderLocalDistanceFromCells & operator= ( const L2FirstOrderLocalDistanceFromCells & other); 

    /**
     * Destructor.
     * Does nothing.
     */
    ~L2FirstOrderLocalDistanceFromCells(); 

    /** 
     * Euclidean distance computation at @a aPoint , 
     * from the available distance values
     * of the adjacent cells. 
     *
     * @param aPoint the point for which the distance is computed
     *
     * @return the distance value at @a aPoint.
     *
     */
    Value operator() (const Point& aPoint);

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    // ----------------------- Internals -------------------------------------

  private: 

    /**
     * Returns an approximation of the Euclidean distance 
     * at some point, knowing the distance of its adjacent cells
     * contained in @a aValueList
     * 
     * @param aValueList  the distance of (some of) the neighbors
     * @return the computed distance.
     */
    Value compute(Values& aValueList) const; 

  }; 


  /////////////////////////////////////////////////////////////////////////////
  // template class SpeedExtrapolator
  /**
   * Description of template class 'SpeedExtrapolator' <p>
   * \brief Aim: Class for the computation of the a speed value
   * at some point p, from the available distance values and speed
   * values of some points lying in the 1-neighborhood of p 
   * (ie. points at a L1-distance to p equal to 1) in order to 
   * extrapolate a speed field in the normal direction to the interface. 
   *
   * The computed value is such that the dot product of the gradients
   * of the speed function and of the distance function is zero, ie. 
   * \f$ \nabla S .  \nabla \Phi = 0 \f$. 
   *
   * @note see [Adalsteinsson and Sethian, Fast Construction of 
   * Extension Velocities in Level Set Methods, J. Comput. Phys. 148, 2-22, 1999]
   *
   * It is a model of CPointFunctor.
   *
   * @tparam TDistanceImage model of CImage used for the mapping point-distance value
   * @tparam TSet model of CDigitalSet for storing points whose distance value is known
   * @tparam TSpeedFunctor model of CImage used for the mapping point-speed value
   *
   * @see FMM
   */
  template <typename TDistanceImage, typename TSet, typename TSpeedFunctor>
  class SpeedExtrapolator
  {

    // ----------------------- Types ------------------------------
  public:


    /// image
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TDistanceImage> ));
    typedef TDistanceImage DistanceImage;
    typedef typename DistanceImage::Point Point;
    typedef typename DistanceImage::Value DistanceValue;
    BOOST_CONCEPT_ASSERT(( concepts::CPointFunctor<TSpeedFunctor> ));
    typedef TSpeedFunctor SpeedFunctor;
    BOOST_STATIC_ASSERT(( boost::is_same< Point, typename SpeedFunctor::Point >::value ));
    typedef typename SpeedFunctor::Value Value; 

    /// set
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet<TSet> ));
    typedef TSet Set;
    BOOST_STATIC_ASSERT(( boost::is_same< Point, typename TSet::Point >::value ));
  
    // ----------------------- Data -------------------------------------
  public: 
    /// Aliasing pointer on the underlying image of distance values
    const DistanceImage* myDistImgPtr; 
    /// Aliasing pointer on the underlying set of points 
    /// whose distance value is known
    const Set* mySetPtr; 
    /// Aliasing pointer on the underlying image of speed values
    SpeedFunctor* mySpeedFuncPtr; 


    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Constructor from images and set. 
     * NB: only pointers are stored
     *
     * @param aDistImg any distance map
     * @param aSet any digital set
     * @param aSpeedFunc any speed map
     */
    SpeedExtrapolator(const DistanceImage& aDistImg, const TSet& aSet, SpeedFunctor& aSpeedFunc);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    SpeedExtrapolator ( const SpeedExtrapolator & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    SpeedExtrapolator & operator= ( const SpeedExtrapolator & other); 

    /**
     * Destructor.
     * Does nothing.
     */
    ~SpeedExtrapolator(); 

    /** 
     * Speed value computation at @a aPoint , 
     * from the available distance/speed values
     * of the 1-neighbors of @a aPoint  .
     *
     * @param aPoint the point for which the speed is computed
     *
     * @return the speed value at @a aPoint.
     *
     */
    Value operator() (const Point& aPoint);


  }; 


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/volumes/distance/FMMPointFunctors.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined FMMPointFunctors_h

#undef FMMPointFunctors_RECURSES
#endif // else defined(FMMPointFunctors_RECURSES)
