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
 * @file KanungoNoise.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/03/06
 *
 * Header file for module KanungoNoise.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(KanungoNoise_RECURSES)
#error Recursive header files inclusion detected in KanungoNoise.h
#else // defined(KanungoNoise_RECURSES)
/** Prevents recursive inclusion of headers. */
#define KanungoNoise_RECURSES

#if !defined KanungoNoise_h
/** Prevents repeated inclusion of headers. */
#define KanungoNoise_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/base/Clone.h"
#include "DGtal/kernel/sets/CDigitalSet.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"
#include "DGtal/geometry/volumes/distance/DistanceTransformation.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/kernel/BasicPointPredicates.h"
#include "DGtal/kernel/CPointPredicate.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class KanungoNoise
  /**
   * Description of template class 'KanungoNoise' <p>
   * \brief Aim: From a point predicate (model of concepts::CPointPredicate), this class 
   * constructs another point predicate as a noisy version of the input one.
   *
   * The noise model used here, called Kanungo noise, can be defined as follows:
   * for each point on a domain, we compute the distance @f$ d @f$ to the "border" of the
   * point predicate (see below) and the point label (true/false) is reverted with
   * probability:
   * @f[ \alpha^d @f]
   * for @f$ 0< \alpha < 1@f$ specified at construction step.
   *
   * @note This class explicitely stores the noisy point predicate in a digital set container
   * model. Furthermore, the distance is given by the DistanceTransformation class with the
   * Eucliean metric (the distance is computed on both true and false points from the point
   * predicate in the given domain).
   *
   * @tparam TPointPredicate any model of point predicate concept (concepts::CPointPredicate)
   * @tparam TDomain any model of CDomain
   * @tparam TDigitalSetContainer container type to store the point predicate (default: DigitalSetBySTLSet)
   *
   */
  template <typename TPointPredicate, typename TDomain,
            typename TDigitalSetContainer=DigitalSetBySTLSet<TDomain> >
  class KanungoNoise
  {
    // ----------------------- Standard services ------------------------------
  public:

    ///Concept checks
    BOOST_CONCEPT_ASSERT(( concepts::CDomain< TDomain > ));
    BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate<TPointPredicate> ));
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet<TDigitalSetContainer> ));
    
    ///Object type
    typedef TPointPredicate PointPredicate;
    
    ///Point type
    typedef typename TDomain::Point Point;
    
    ///Domain type
    typedef TDomain Domain;
    
    ///DigitalSet type
    typedef TDigitalSetContainer DigitalSet;
   
    /**
     * Constructor.
     * This constructor will compute the distance transformations and the explicit
     * noisy point predicate as a digitalset.
     *
     * @param aPredicate input point predicate defining the input objects.
     * @param aDomain domain used for the distance transformation computation.
     * @param anAlpha noise parameter between ]0,1[.
     */
    KanungoNoise(ConstAlias<PointPredicate> aPredicate,
                 ConstAlias<Domain> aDomain,
                 const double anAlpha);
     
    /**
     * Destructor.
     */
    ~KanungoNoise();

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    KanungoNoise & operator= ( const KanungoNoise & other );
    
    // ----------------------- Interface --------------------------------------
  public:

    /**
     * PointPredicate concept method.
     *
     * @param aPoint point to probe the predicate at.
     * @return true if the point is inside the nosified object.
     *
     **/
    bool operator()(const Point &aPoint) const;
    
    
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

     // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    KanungoNoise();

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    KanungoNoise ( const KanungoNoise & other );

       // ------------------------- Internals ------------------------------------
  private:
    ///Pointeur to the object
    const PointPredicate &myPredicate;
    
    ///Explicit set to store the noisfied object points
    DigitalSet * mySet;
    
    ///Pointeur to the domain
    const Domain & myDomain;
    
    ///Noise parameter
    double myAlpha;
    
  }; // end of class KanungoNoise


  /**
   * Overloads 'operator<<' for displaying objects of class 'KanungoNoise'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'KanungoNoise' to write.
   * @return the output stream after the writing.
   */
  template <typename TO, typename TD, typename TS>
  std::ostream&
  operator<< ( std::ostream & out, const KanungoNoise<TO,TD,TS> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/volumes//KanungoNoise.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined KanungoNoise_h

#undef KanungoNoise_RECURSES
#endif // else defined(KanungoNoise_RECURSES)
