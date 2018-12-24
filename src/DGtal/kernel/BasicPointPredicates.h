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
 * @file BasicPointPredicates.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @date 2010/07/10
 *
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en PointFunctor et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/02/02
 *
 * This files contains several basic classes representing predicates
 * on points.
 *
 * This file is part of the DGtal library.
 */

#if defined(BasicPointPredicates_RECURSES)
#error Recursive header files inclusion detected in BasicPointPredicates.h
#else // defined(BasicPointPredicates_RECURSES)
/** Prevents recursive inclusion of headers. */
#define BasicPointPredicates_RECURSES

#if !defined BasicPointPredicates_h
/** Prevents repeated inclusion of headers. */
#define BasicPointPredicates_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/BasicBoolFunctors.h"
#include "DGtal/base/CPredicate.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/kernel/CPointFunctor.h"
#include "DGtal/kernel/CPointPredicate.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::functors
namespace DGtal {
  namespace functors {

  /////////////////////////////////////////////////////////////////////////////
  // template class ConstantPointPredicate
  /**
   * Description of template class 'ConstantPointPredicate' <p>
   * \brief Aim: The predicate that returns always the same value boolCst
   *
   * @tparam TPoint any point type
   * @tparam boolCst any boolean value
   */
  template <typename TPoint, bool boolCst>
  struct ConstantPointPredicate
  {
    typedef TPoint Point;

    /**
     * @param p any point.
     * @return the value of the predicate at this point.
     */
    bool operator()( const Point & p ) const;

  }; // end of class ConstantPointPredicates

  /////////////////////////////////////////////////////////////////////////////
  // template class TruePointPredicate
  /**
   * Description of template class 'TruePointPredicate' <p>
   * \brief Aim: The predicate that returns always true.
   *
   * @tparam TPoint any point type
   */
  template <typename TPoint>
  struct TruePointPredicate : public ConstantPointPredicate<TPoint,true>
  {
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class FalsePointPredicate
  /**
   * Description of template class 'FalsePointPredicate' <p>
   * \brief Aim: The predicate that returns always false.
   *
   * @tparam TPoint any point type
   */
  template <typename TPoint>
  struct FalsePointPredicate : public ConstantPointPredicate<TPoint,false>
  {
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class IsLowerPointPredicate
  /**
   * Description of template class 'IsLowerPointPredicate' <p> \brief
   * Aim: The predicate returns true when the point is below (or
   * equal) the given upper bound.
   *
   * @tparam TPoint any point type
   */
  template <typename TPoint>
  struct IsLowerPointPredicate
  {
    typedef TPoint Point;

    /**
     * Constructor from upper bound.
     */
    IsLowerPointPredicate( const Point & upperBound );

    /**
     * @param p any point.
     * @return the value of the predicate at this point.
     */
    bool operator()( const Point & p ) const;

    /// the upper bound.
    Point myUpperBound;
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class IsUpperPointPredicate
  /**
   * Description of template class 'IsUpperPointPredicate' <p> \brief
   * Aim: The predicate returns true when the point is above (or
   * equal) the given lower bound.
   *
   * @tparam TPoint any point type
   */
  template <typename TPoint>
  struct IsUpperPointPredicate
  {
    typedef TPoint Point;

    /**
     * Constructor from lower bound.
     */
    IsUpperPointPredicate( const Point & lowerBound );

    /**
     * @param p any point.
     * @return the value of the predicate at this point.
     */
    bool operator()( const Point & p ) const;

    /// the lower bound.
    Point myLowerBound;
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class IsWithinPointPredicate
  /**
   * Description of template class 'IsWithinPointPredicate' <p> \brief
   * Aim: The predicate returns true when the point is within the given bounds.
   *
   * @tparam TPoint any point type
   */
  template <typename TPoint>
  struct IsWithinPointPredicate
  {
    typedef TPoint Point;

    /**
     * Constructor from lower bound and upper bound.
     */
    IsWithinPointPredicate( const Point & lowerBound,
          const Point & upperBound );

    /**
     * @param p any point.
     * @return the value of the predicate at this point.
     */
    bool operator()( const Point & p ) const;

    /// the upper bound.
    Point myLowerBound;
    /// the lower bound.
    Point myUpperBound;
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class NotPointPredicate
  /**
   * Description of template class 'NotPointPredicate' <p> \brief Aim:
   * The predicate returns true when the point predicate given at
   * construction return false. Thus inverse a predicate: NOT operator.
   *
   * @tparam TPointPredicate the predicate type.
   */
  template <typename TPointPredicate>
  struct NotPointPredicate
  {
    typedef TPointPredicate PointPredicate;
    BOOST_CONCEPT_ASSERT (( concepts::CPointPredicate<PointPredicate> ));
    typedef typename PointPredicate::Point Point;

    /**
     * Constructor from predicates and bool Functor.
     */
    NotPointPredicate( ConstAlias<PointPredicate> pred );

   /**
     * @param p any point.
     * @return the value of the predicate at this point.
     */
    bool operator()( const Point & p ) const;

    /// The PointPredicate that is inversed.
    const PointPredicate* myPred;
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class EqualPointPredicate
  /**
   * Description of template class 'EqualPointPredicate' <p> \brief Aim:
   * The predicate returns true when the point given as argument equals
   * the reference point given at construction.
   *
   * @tparam TPoint point type.
   */
  template <typename TPoint>
  struct EqualPointPredicate
  {
    typedef TPoint Point;

    /**
     * Constructor from a point.
     */
    EqualPointPredicate( const Point & aPoint );

    /**
     * @param p any point.
     * @return the value of the predicate at this point.
     */
    bool operator()( const Point & p ) const;

    /// Reference point.
    Point myPoint;
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class BinaryPointPredicate
  /**
   * Description of template class 'BinaryPointPredicate' <p> \brief
   * Aim: The predicate returns true when the given binary functor
   * returns true for the two PointPredicates given at construction.
   *
   * Note that this class is specialized for DGtal::AndBoolFct2 and 
   * DGtal::OrBoolFct2 in order to guarantee that the second computation
   * is not performed when the first point predicate return false (resp. true)
   * with DGtal::AndBoolFct2 (resp. DGtal::OrBoolFct2). 
   *
   * @tparam TPointPredicate1 the left predicate type.
   * @tparam TPointPredicate2 the right predicate type.
   * @tparam TBinaryFunctor binary functor used for comparison
   */
  template <typename TPointPredicate1, typename TPointPredicate2,
      typename TBinaryFunctor = BoolFunctor2 >
  struct BinaryPointPredicate
  {
    typedef TPointPredicate1 PointPredicate1;
    typedef TPointPredicate2 PointPredicate2;
    typedef typename PointPredicate1::Point Point;
    typedef typename PointPredicate2::Point Point2;

    BOOST_CONCEPT_ASSERT (( concepts::CPointPredicate< PointPredicate1 > ));
    BOOST_CONCEPT_ASSERT (( concepts::CPointPredicate< PointPredicate2 > ));
    BOOST_CONCEPT_ASSERT (( boost::BinaryFunction< TBinaryFunctor, bool, bool, bool > ));
    BOOST_STATIC_ASSERT (( boost::is_same< Point, Point2 >::value ));

    /**
       Constructor from predicates and bool Functor.
       @param pred1 the left predicate.
       @param pred2 the right predicate.
       @param boolFunctor the binary function used to combine pred1
       and pred2.
     */
    BinaryPointPredicate( ConstAlias<PointPredicate1> pred1, ConstAlias<PointPredicate2> pred2, ConstAlias<TBinaryFunctor> boolFunctor );

    /**
     * @param p any point.
     * @return the value of the predicate at this point.
     */
    bool operator()( const Point & p ) const;

    /// aliasing pointer to the left predicate.
    const PointPredicate1* myPred1;
    /// aliasing pointer to the right predicate.
    const PointPredicate2* myPred2;
    /// aliasing pointer to the binary functor.
    const TBinaryFunctor* myBoolFunctor;
  };

  /**
   * Specialization of BinaryPointPredicate for AndBoolFct2
   */
  template <typename TPointPredicate1, typename TPointPredicate2>
  struct BinaryPointPredicate<TPointPredicate1, TPointPredicate2, AndBoolFct2>
  {
    typedef TPointPredicate1 PointPredicate1;
    typedef TPointPredicate2 PointPredicate2;
    typedef typename PointPredicate1::Point Point;
    typedef typename PointPredicate2::Point Point2;

    BOOST_CONCEPT_ASSERT (( concepts::CPointPredicate< PointPredicate1 > ));
    BOOST_CONCEPT_ASSERT (( concepts::CPointPredicate< PointPredicate2 > ));
    BOOST_STATIC_ASSERT (( boost::is_same< Point, Point2 >::value ));

    BinaryPointPredicate( ConstAlias<PointPredicate1> pred1, ConstAlias<PointPredicate2> pred2, ConstAlias<AndBoolFct2> boolFunctor );

    bool operator()( const Point & p ) const;

    const PointPredicate1* myPred1;
    const PointPredicate2* myPred2;
    const AndBoolFct2* myBoolFunctor;
  };

  /**
   * Specialization of BinaryPointPredicate for OrBoolFct2
   */
  template <typename TPointPredicate1, typename TPointPredicate2>
  struct BinaryPointPredicate<TPointPredicate1, TPointPredicate2, OrBoolFct2>
  {
    typedef TPointPredicate1 PointPredicate1;
    typedef TPointPredicate2 PointPredicate2;
    typedef typename PointPredicate1::Point Point;
    typedef typename PointPredicate2::Point Point2;

    BOOST_CONCEPT_ASSERT (( concepts::CPointPredicate< PointPredicate1 > ));
    BOOST_CONCEPT_ASSERT (( concepts::CPointPredicate< PointPredicate2 > ));
    BOOST_STATIC_ASSERT (( boost::is_same< Point, Point2 >::value ));

    BinaryPointPredicate( ConstAlias<PointPredicate1> pred1, ConstAlias<PointPredicate2> pred2, ConstAlias<OrBoolFct2> boolFunctor );

    bool operator()( const Point & p ) const;

    const PointPredicate1* myPred1;
    const PointPredicate2* myPred2;
    const OrBoolFct2* myBoolFunctor;
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class PointFunctorPredicate
  /**
   * Description of template class 'PointFunctorPredicate' <p> \brief
   * Aim: The predicate returns true when the predicate
   * returns true for the value assigned to a given point
   * in the point functor.
   *
   * @tparam TPointFunctor a model of CPointFunctor.
   * @tparam TPredicate a type of predicate on values (model of CPredicate)
   */
  template <typename TPointFunctor, typename TPredicate>
  struct PointFunctorPredicate
  {
    BOOST_CONCEPT_ASSERT (( concepts::CPointFunctor< TPointFunctor > ));
    BOOST_CONCEPT_ASSERT (( concepts::CUnaryFunctor< TPredicate, typename TPointFunctor::Value, bool > ));

    typedef TPointFunctor PointFunctor;
    typedef TPredicate Predicate;
    typedef typename PointFunctor::Point Point;

    /**
       Constructor from an PointFunctor and a predicate
       @param aFun an point functor.
       @param aPred a predicate.
     */
    PointFunctorPredicate( ConstAlias<PointFunctor> aFun, ConstAlias<Predicate> aPred );

    /**
     * @param p any point.
     * @return the value of the predicate at this point.
     */
    bool operator()( const Point & p ) const;

    /// alias of the PointFunctor.
    const PointFunctor* myFun;
    /// alias of the predicate.
    const Predicate* myPred;
  };

} // namespace functors
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/BasicPointPredicates.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined BasicPointPredicates_h

#undef BasicPointPredicates_RECURSES
#endif // else defined(BasicPointPredicates_RECURSES)
