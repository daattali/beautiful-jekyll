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
 * @file DigitalMetricAdapter.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/07/02
 *
 * Header file for module DigitalMetricAdapter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DigitalMetricAdapter_RECURSES)
#error Recursive header files inclusion detected in DigitalMetricAdapter.h
#else // defined(DigitalMetricAdapter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DigitalMetricAdapter_RECURSES

#if !defined DigitalMetricAdapter_h
/** Prevents repeated inclusion of headers. */
#define DigitalMetricAdapter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/volumes/distance/CMetricSpace.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/kernel/NumberTraits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class DigitalMetricAdapter
  /**
   * Description of template class 'DigitalMetricAdapter' <p>
   * \brief Aim: simple adapter class which adapts any models of
   * concepts::CMetricSpace to  a model of
   * concepts::CDigitalMetricSpace.
   *
   * This class uses the ceil function to perform the adaptation.
   * This class is thus a model of CDigitalMetricSpace
   *
   * @tparam TMetric any model of concepts::CMetricSpace.
   * @tparam TInteger any model of concepts::CInteger to be used as
   * value type. By default, it corresponds to the Integer type of the
   * digital space in which the TMetric is defined.
   */
  template <typename TMetric, typename TInteger = typename TMetric::Space::Integer>
  class DigitalMetricAdapter
  {
    // ----------------------- Standard services ------------------------------
  public:

    ///Input metric type
    typedef TMetric Metric;
    BOOST_CONCEPT_ASSERT(( concepts::CMetricSpace<Metric> ));

    ///Values are integer numbers
    typedef TInteger Value;
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<Value> ));

    // ----------------------- CDigitalMetric------------------------------------
    ///Point type
    typedef typename Metric::Point Point;

    ///Space type
    typedef typename Metric::Space Space;

    ///RawValue type
    typedef Value RawValue;
    
       
    /** 
     * Constructor from a CMetricSpace model.
     * 
     * @param aMetric  the metric to adapt.
     */
    DigitalMetricAdapter(ConstAlias<Metric> aMetric):
      myMetric(&aMetric) {}

    
    /** 
     * Copy Constructor
     * 
     * @param anotherMetric the digital metric adapter to copy.
     */
    DigitalMetricAdapter(const DigitalMetricAdapter &anotherMetric)
    {
       if (this != &anotherMetric)
         this->myMetric = anotherMetric.myMetric;
    }
      

    /**
     * Destructor.
     */
    ~DigitalMetricAdapter() {}

    // ----------------------- Interface --------------------------------------
  public:

    // ----------------------- CDigitalMetricSpace --------------------------------------

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    DigitalMetricAdapter & operator= ( const DigitalMetricAdapter & other )
    {
      myMetric = other.myMetric;
      return *this;
    }

    /** 
     * Distance operator.
     * 
     * @param [in] p a first point.
     * @param [in] q a second point.
     * @return the casted distance from p to q
     */
    Value operator() (const Point &p, const Point &q) const
    {
      return static_cast<Value>( std::ceil ( NumberTraits<typename Metric::Value>::castToDouble( myMetric->operator()(p,q))));
    }

    /** 
     * RawDistance operator.
     * 
     * @param [in] p a first point.
     * @param [in] q a second point.
     * @return the casted distance from p to q
     */
    Value rawDistance(const Point &p, const Point &q) const
    {
      return this->operator()(p,q);
    }

    /** 
     * closest operator.
     * 
     * @param [in] a the origin point.
     * @param [in] p a first point.
     * @param [in] q a second point.
     * @return decides which point from p and  q is closer to a.
     */
    DGtal::Closest closest(const Point &a,
                           const Point &p,
                           const Point &q) const
    {
      if (this->operator()(a,p) < this->operator()(a,q))
        return DGtal::ClosestFIRST;
      if (this->operator()(a,p) > this->operator()(a,q))
        return DGtal::ClosestSECOND;
      return DGtal::ClosestBOTH;
    }

  

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const
    {
      out << "[DigitalMetricAdapter] adapted from "<< *myMetric;
    }

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const { return (myMetric != NULL); }

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:

    const Metric *myMetric;
    
    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    DigitalMetricAdapter();

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class DigitalMetricAdapter


  /**
   * Overloads 'operator<<' for displaying objects of class 'DigitalMetricAdapter'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'DigitalMetricAdapter' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const DigitalMetricAdapter<T> & object );

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DigitalMetricAdapter_h

#undef DigitalMetricAdapter_RECURSES
#endif // else defined(DigitalMetricAdapter_RECURSES)
