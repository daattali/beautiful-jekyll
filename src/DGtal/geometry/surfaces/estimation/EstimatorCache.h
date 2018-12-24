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
 * @file EstimatorCache.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/09/30
 *
 * Header file for module EstimatorCache.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(EstimatorCache_RECURSES)
#error Recursive header files inclusion detected in EstimatorCache.h
#else // defined(EstimatorCache_RECURSES)
/** Prevents recursive inclusion of headers. */
#define EstimatorCache_RECURSES

#if !defined EstimatorCache_h
/** Prevents repeated inclusion of headers. */
#define EstimatorCache_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <map>
#include "DGtal/base/Common.h"
#include "DGtal/base/Alias.h"
#include "DGtal/geometry/surfaces/estimation/CSurfelLocalEstimator.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  
  /////////////////////////////////////////////////////////////////////////////
  // template class EstimatorCache
  /**
   * Description of template class 'EstimatorCache' <p>
   * \brief Aim: this class adapts any local surface estimator to cache the estimated
   * values in a associative container (Surfel <-> estimated value).
   *
   * The use-case of this class is when you want to estimate the same quantity
   * several times.
   *
   * This class implements eval() methods for surfel iterators as in
   * concepts::CSurfelLocalEstimator concept. Addtitionnaly, we also
   * have an eval method from a surfel.
   *
   * This class is also a model of concepts::CSurfelLocalEstimator
   *
   * @see testEstimatorCache.cpp

   * @tparam TEstimator any model of CSurfelLocalEstimator
   * @tparam TContainer the associative container to use (default type: std::map<Surfel,Quantity>)
   */
  template <typename TEstimator,
            typename TContainer = std::map<typename TEstimator::Surfel,
                                           typename TEstimator::Quantity> >
  class EstimatorCache
  {
    // ----------------------- Standard services ------------------------------
  public:
    
    
    ///Estimator type
    typedef TEstimator Estimator;
    BOOST_CONCEPT_ASSERT(( concepts::CSurfelLocalEstimator<TEstimator> ));
    
    ///Container type
    typedef TContainer Container;
    BOOST_CONCEPT_ASSERT(( boost::PairAssociativeContainer<TContainer> ));
    
    //Concept of CSurfelLocalEstimator
    
    ///Surfel type
    typedef typename Estimator::Surfel Surfel;
    
    ///Quantity type
    typedef typename Estimator::Quantity Quantity;
    
    ///Self
    typedef EstimatorCache<Estimator,Container> Self;

    /**
     * Default constructor.
     */
    EstimatorCache(): myInit(false)
    {}
    
    /**
     * Constructor from estimator instance.
     *
     */
    EstimatorCache( Alias<Estimator> anEstimator): myEstimator(&anEstimator),
                                                   myInit(false)
    {}
    
    /**
     * Destructor.
     */
    ~EstimatorCache()
    {}
    
    /**
     * Copy constructor.
     */
    EstimatorCache(const Self &other): myContainer(other.myContainer),
                                       myEstimator(other.myEstimator),
                                       myInit(other.myInit)
    {}
   
    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    Self & operator= ( const Self & other )
    {
      myContainer = other.myContainer;
      myEstimator = other.myEstimator;
      myInit = other.myInit;
      
      return *this;
    }
    
    // ----------------------- CSurfelLocalEstimator Interface --------------------------------------
    
    /**
     * Estimator initialization. This method initializes the underlying
     * estimator and caches all estimated quantity between @a itb and @a ite. 
     *
     * @tparam  SurfelConstIterator a const iterator on surfels.
     * @param[in] aH the gridstep
     * @param[in] ite iterator on the first surfel of the surface.
     * @param[in] itb iterator after the last surfel of the surface.
     *
     */
    template <typename SurfelConstIterator>
    void init(const double aH, SurfelConstIterator itb, SurfelConstIterator ite)
    {
      ASSERT(myEstimator);
      myEstimator->init(aH,itb,ite);
      myContainer.clear();

      //We estimate and store the quantities
      //(since SurfelConstIterator models are usually SinglePass, we
      //cannot use the optimized "range" eval on the estimator)
      for(SurfelConstIterator it = itb; it != ite; ++it)
        myContainer.insert( std::pair<Surfel, Quantity>(*it, myEstimator->eval(it) ) );
      
      myInit = true;
    }
    
    /**
     * Cached evaluation of the estimator at iterator @a it
     *
     * @pre init() method must have been called first.
     *
     * @tparam  SurfelConstIterator a const iterator on surfels.
     * @param [in] it the iterator to the surfel to estimate.
     * @return the estimated quantity.
     */
    template <typename SurfelConstIterator>
    Quantity eval(const SurfelConstIterator it) const
    {
      ASSERT_MSG(myInit, " init() method must have been called first.");
      return myContainer.find( *it )->second;
    }
    
    /**
     * Cached evaluation of the estimator at a surfel @a s
     *
     * @pre init() method must have been called first.
     *
     * @param [in] s the iterator to the surfel to estimate.
     * @return the estimated quantity.
     */
    Quantity eval(const Surfel s) const
    {
      ASSERT_MSG(myInit, " init() method must have been called first.");
      return myContainer.find( s )->second;
    }
    
    
    /**
     * Cached range evaluation of the estimator between @a itb
     * and @a ite.
     *
     * @pre init() method must have been called first.
     *
     *
     * @tparam  SurfelConstIterator a const iterator on surfels.
     * @param [in] itb the begin iterator to the surfel to estimate.
     * @param [in] ite the end iterator to the surfel to estimate.
     * @param [in] result an output iterator on the result.
     * @return the estimated quantity.
     */
    template <typename SurfelConstIterator,typename OutputIterator>
    OutputIterator eval(SurfelConstIterator itb,
                        SurfelConstIterator ite,
                        OutputIterator result ) const
    {
      ASSERT_MSG(myInit, " init() method must have been called first.");
      for(SurfelConstIterator it = itb; it != ite; ++it)
        *result++ = this->eval(it);
      
      return result;
    }
    
    /**
     * @return the gridstep.
     *
     *
     * @pre init() method must have been called first.
     *
     */
    double h() const
    {
      return myEstimator->h();
    }
    
    // ----------------------- Interface --------------------------------------
  public:

    /** 
     * @pre init() method must have been called first.
     * @return the number of cached elements. 
     */
    typename Container::size_type size() const
    {
      ASSERT_MSG(myInit, " init() method must have been called first.");
      return myContainer.size();
    }

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const
    {
      out<< "[EstimatorCache] number of surfels="<<myContainer.size();
    }
    
    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const
    {
      return myEstimator && myEstimator->isValid();
    }
    
    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    
    
    ///Instance of estimator
    Container myContainer;
    
    ///Alias of the estimator
    Estimator *myEstimator;

    ///Init flag
    bool myInit;
    
    // ------------------------- Internals ------------------------------------
  private:
    
  }; // end of class EstimatorCache
  
  
  /**
   * Overloads 'operator<<' for displaying objects of class 'EstimatorCache'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'EstimatorCache' to write.
   * @return the output stream after the writing.
   */
  template <typename T, typename TC>
  std::ostream&
  operator<< ( std::ostream & out, const EstimatorCache<T,TC> & object )
  {
    object.selfDisplay( out );
    return out;
  }
  
} // namespace DGtal
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined EstimatorCache_h

#undef EstimatorCache_RECURSES
#endif // else defined(EstimatorCache_RECURSES)
