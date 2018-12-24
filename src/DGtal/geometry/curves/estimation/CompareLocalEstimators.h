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
 * @file CompareLocalEstimators.h
 * @brief Functor to compare two local geometric estimators. 
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/06/27
 *
 * Header file for module CompareLocalEstimators.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testTrueLocalEstimator.cpp
 */

#if defined(CompareLocalEstimators_RECURSES)
#error Recursive header files inclusion detected in CompareLocalEstimators.h
#else // defined(CompareLocalEstimators_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CompareLocalEstimators_RECURSES

#if !defined CompareLocalEstimators_h
/** Prevents repeated inclusion of headers. */
#define CompareLocalEstimators_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <cmath>
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/math/Statistic.h"

///////////////
namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // template class CompareLocalEstimators
  /**
   * Description of template struct 'CompareLocalEstimators' <p>
   * \brief Aim: Functor to compare two local geometric estimators. 
   * 
   *
   * @tparam TFirstEsimator  type of the first estimator.
   * @tparam TSecondEstimator type of the second estimator.
   * 
   */
  template <typename TFirstEsimator, typename TSecondEstimator>
  struct CompareLocalEstimators
  {

    // ----------------------- Types ------------------------------
  public:

    typedef TFirstEsimator FirstEstimator;
    typedef TSecondEstimator SecondEstimator;

    typedef typename FirstEstimator::ConstIterator ConstIterator;
    typedef typename FirstEstimator::Quantity Quantity;

    ///Output statistic type.
    typedef Statistic<Quantity> OutputStatistic;
    typedef Statistic<double> OutputVectorStatistic;
    
    ///@todo Assert firstestimator::Quantity==secondestimator::Quantity
    
    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Return the error (difference) between the two estimators at a
     * given point.
     *
     * @pre both estimators must have been initialised with the same
     * parameters (geometry, resolution h, ...).
     *
     * @param aFirstEstimator the first estimator.
     * @param aSecondEstimator the second estimator.
     * @param it the point to evaluate the difference.
     * @return the difference between the two estiamtor values at
     * *it. (firstEstimator value - secondEstimator value). 
     */
    static 
    Quantity compare(FirstEstimator & aFirstEstimator,
         SecondEstimator & aSecondEstimator,
         const ConstIterator &it)
    {
      ASSERT( aFirstEstimator.isValid());
      ASSERT( aSecondEstimator.isValid());
      
      return aFirstEstimator.eval(it) - aSecondEstimator.eval(it);
    }
    
    
   /**
     * Return a statistic on the error (difference) between the two
     * estimators for points ranging from itb to ite.
     *
     * @pre both estimators must have been initialised with the same
     * parameters (geometry, resolution h, ...).
     *
     * @param aFirstEstimator the first estimator.
     * @param aSecondEstimator the second estimator.
     * @param itb starting point of the comparison.
     * @param ite ending point of the comparison.
     * @param storeSamples if true, the instance of Statistic will
     * store all the values.
     * @return the statistic of differences between the two estiamtor values 
     */
    static
    OutputStatistic
    compare(FirstEstimator & aFirstEstimator,
      SecondEstimator & aSecondEstimator,
      const ConstIterator & itb, 
      const ConstIterator & ite,
      const bool storeSamples = false)
    {
      OutputStatistic stats(storeSamples);
      
      for(ConstIterator it = itb; it!= ite; ++it)
  stats.addValue( compare(aFirstEstimator,aSecondEstimator,it));
      
      stats.terminate();
      return stats;
    }
    
    
    /**
     * Return the angular error between the two estimations (if
     * Quantity values are vectors) at a
     * given point.
     *
     * @pre both estimators must have been initialised with the same
     * parameters (geometry, resolution h, ...).
     *
     * @param aFirstEstimator the first estimator.
     * @param aSecondEstimator the second estimator.
     * @param it the point to evaluate the difference.
     * @return the difference between the two estiamtor values at
     * *it. (firstEstimator value - secondEstimator value). 
     */
    static 
    double 
    compareVectors(FirstEstimator & aFirstEstimator,
       SecondEstimator & aSecondEstimator,
       const ConstIterator &it)
    {
      ASSERT( aFirstEstimator.isValid());
      ASSERT( aSecondEstimator.isValid());
      Quantity v1 = aFirstEstimator.eval(it), v2 = aSecondEstimator.eval(it);
      
      ASSERT( v1.norm() != 0.0 );
      ASSERT( v2.norm() != 0.0 );
      double ndot = (double) v1.dot(v2)
  / ( (double) ( v1.norm() * v2.norm() ) );
      return ( ndot > 1.0 ) ? 0.0
  : ( ndot < -1.0 ) ? M_PI : acos( ndot );
      
    }
    
    
   /**
     * Return a statistic on the error (angular error) between the two
     * estimators for points ranging from itb to ite.
     *
     * @pre both estimators must have been initialised with the same
     * parameters (geometry, resolution h, ...).
     *
     * @param aFirstEstimator the first estimator.
     * @param aSecondEstimator the second estimator.
     * @param itb starting point of the comparison.
     * @param ite ending point of the comparison.
     * @param storeSamples if true, the instance of Statistic will
     * store all the values.
     * @return the statistic of differences between the two estiamtor values 
     */
    static
    OutputVectorStatistic
    compareVectors(FirstEstimator & aFirstEstimator,
       SecondEstimator & aSecondEstimator,
       const ConstIterator & itb, 
       const ConstIterator & ite,
       const bool storeSamples = false)
    {
      OutputVectorStatistic stats(storeSamples);
      
      for(ConstIterator it = itb; it!= ite; ++it)
  stats.addValue( compareVectors(aFirstEstimator,aSecondEstimator,it));
      
      stats.terminate();
      return stats;
    }
    
    // ------------------------- Hidden services ------------------------------
  private:
    
    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    CompareLocalEstimators ( const CompareLocalEstimators & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    CompareLocalEstimators & operator= ( const CompareLocalEstimators & other );


  }; // end of class CompareLocalEstimators

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////

#endif // !defined CompareLocalEstimators_h

#undef CompareLocalEstimators_RECURSES
#endif // else defined(CompareLocalEstimators_RECURSES)
