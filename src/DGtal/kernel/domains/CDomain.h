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
 * @file CDomain.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/01
 *
 * Header file for concept CDomain.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDomain_RECURSES)
#error Recursive header files inclusion detected in CDomain.h
#else // defined(CDomain_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDomain_RECURSES

#if !defined CDomain_h
/** Prevents repeated inclusion of headers. */
#define CDomain_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "boost/concept_check.hpp"
#include "DGtal/base/Common.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/base/CConstSinglePassRange.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // class CDomain
  /**
   * DescriptionDescription of \b concept '\b CDomain' <p> \brief Aim: This
   * concept represents a digital domain, i.e. a non mutable subset of
   * points of the given digital space.
   * 
   * <p> Refinement of CConstSinglePassRange
   *
   * <p> Associated types :
   * - Domain : the type itself of the CDomain model.
   * - Space : the embedding digital space.
   * - Point : the point type of the space
   * - Size : the type used for counting elements of the space.
   * - Dimension : the type used for indexing the dimension.
   * - Vector : the vector type of the space
   * - Predicate : the type of the predicate returning true for exactly the points of this domain.  
   * 
   * 
   * <p> Notation
   * - \a X : A type that is a model of CDomain
   * - \a x  : Object of type X
   * - \a p  : Object of type Point
   *
   * <p> Definitions
   *
   * <p> Valid expressions and 
   * <table> <tr> <td> \b Name </td> <td> \b Expression </td>
   * <td> \b Type requirements </td> <td> \b Return type </td>
   * <td> \b Precondition </td> <td> \b Semantics </td> 
   * <td> \b Postcondition </td> <td> \b Complexity </td>
   * </tr>
   * <tr> 
   * <td> lower bound</td> <td> x.lowerBound() </td> 
   * <td> </td> <td> const Point &</td>
   * <td> </td> <td> return the infimum of all points of the domain.</td> <td> </td> <td> O(1) </td>
   * </tr>
   * <tr> 
   * <td> upper bound</td> <td> x.upperBound() </td> 
   * <td> </td> <td> const Point &</td>
   * <td> </td> <td> return the supremum of all points of the domain.</td> <td> </td> <td> O(1) </td>
   * </tr>
   * <tr> 
   * <td> inside domain test</td> <td> x.isInside( p ) </td> 
   * <td> </td> <td> \c bool </td>
   * <td> </td> <td> return 'true' whenever \c p is in the domain.</td> <td> </td> <td>  </td>
   * </tr>
   * <tr> 
   * <td> inside domain predicate object</td> <td> x.predicate() </td> 
   * <td> </td> <td> const Predicate & </td>
   * <td> </td> <td> return a reference to the predicate object equivalent to the isInside(p) test.</td> <td> </td> <td>  </td>
   * </tr>
   * <tr> 
   * <td> size </td> <td> x.size() </td> 
   * <td> </td> <td> Size </td>
   * <td> </td> <td> return the number of points lying in the domain.</td> <td> </td> <td> O(1) </td>
   * </tr>
   * <tr> 
   * <td> iterator from point </td> <td> x.begin(p) </td> 
   * <td> </td> <td> ConstIterator </td>
   * <td> </td> <td> return a ConstIterator on the domain starting
   * from the point p.</td> <td> </td> <td>  </td>
   * </tr>
   * </table>
   *
   * <p> Invariants###
   *
   * <p> Models###
   * HyperRectDomain, DigitalSetDomain 
   *
   * <p> Notes###
   *
   * @todo Complete domain checking.
   */
  template <typename T>
  struct CDomain : public CConstSinglePassRange<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    typedef typename T::Domain Domain;
    typedef typename T::Space Space;
    typedef typename T::Point Point;
    typedef typename T::Vector Vector;
    typedef typename T::Integer Integer;
    typedef typename T::Size Size;
    typedef typename T::Dimension Dimension;
    typedef typename T::Predicate Predicate;
    typedef typename T::ConstIterator ConstIterator;

    BOOST_CONCEPT_USAGE( CDomain )
    {
      // Domain should have a lowerBound() returning a Point.
      ConceptUtils::sameType( myP, myT.lowerBound() );
      // Domain should have an upperBound() returning a Point.
      ConceptUtils::sameType( myP, myT.upperBound() );
      // Domain should have a size() returning a Size.
      ConceptUtils::sameType( mySize, myT.size() );
      // Domain should have a isInside(p) returning a bool.
      ConceptUtils::sameType( myBool, myT.isInside( myP ) );
      // Domain should have a predicate() returning a Predicate.
      ConceptUtils::sameType( myPred, myT.predicate() );
      // Domain should have a begin(Point) method returning an
      // ConstIterator starting from Point
      ConceptUtils::sameType( myIt, myT.begin(myP) );


    }

    // ------------------------- Private Datas --------------------------------
  private:
    T myT;
    Point myP;
    Predicate myPred;
    bool myBool;
    Size mySize; 
    ConstIterator myIt;
    // ------------------------- Internals ------------------------------------
  private:
    
  }; // end of concept CDomain
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDomain_h

#undef CDomain_RECURSES
#endif // else defined(CDomain_RECURSES)
