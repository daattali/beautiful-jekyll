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
 * @file CPolarPointComparator2D.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/12/09
 *
 * Header file for concept CPolarPointComparator2D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CPolarPointComparator2D_RECURSES)
#error Recursive header files inclusion detected in CPolarPointComparator2D.h
#else // defined(CPolarPointComparator2D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CPolarPointComparator2D_RECURSES

#if !defined CPolarPointComparator2D_h
/** Prevents repeated inclusion of headers. */
#define CPolarPointComparator2D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
 namespace concepts
 {
  /////////////////////////////////////////////////////////////////////////////
  // class CPolarPointComparator2D
  /**
     Description of \b concept '\b CPolarPointComparator2D' <p>
     @ingroup Concepts
     @brief Aim: This concept gathers classes that are able to 
     compare the position of two given points \f$ P, Q \f$ around a pole \f$ O \f$. 
     More precisely, they compare the oriented angles lying between the horizontal line
     passing by \f$ O \f$ and the rays \f$ [OP) \f$ and \f$ [OQ) \f$ 
     (in a counter-clockwise orientation). This is equivalent to compare the angle in radians 
     from 0 (included) to 2 &pi; (excluded).
     
     The main method is the operator() applied on two points. It returns 'true' if the first 
     point is located strictly before the second one, 'false' otherwise. A point \f$ P \f$ 
     is located strictly before a point \f$ Q \f$ iff the oriented angle done by \f$ P \f$ is
     smaller than the one of \f$ Q \f$ or its euclidean norm is shorter if \f$ O, P, Q \f$ are
     aligned. Note that it returns 'false' if \f$ P = Q \f$.

     ### Refinement of default constructible, copy constructible, assignable

     ### Associated types :
     - Point : type of points

     ### Notation
     - \e X : A type that is a model of CPolarPointComparator2D
     - \e x : object of type X
     - \e P : type of points
     - \e p, \e p1, \e p2 : objects type P

     ### Definitions

     ### Valid expressions and semantics

     | Name                | Expression   | Type requirements    | Return type | Precondition | Semantics                                             | Post condition | Complexity      |
     |---------------------+--------------+----------------------+-------------+--------------+-------------------------------------------------------+----------------+-----------------|
     | pole setter         | x.setPole(p) | p is of type P       |             |              | the pole is set to p                                  |                | O(1)            |
     | comparison function | x(p1, p2)    | p1, p2 are of type P | bool        |              | tells whether p1 is located strictly before p2 or not |                | model-dependant |

     ### Models

     PolarPointComparator2DBy2x2DetComputer.

     @tparam T the type that should be a model of CPolarPointComparator2D.
  */
  template <typename T>
  struct CPolarPointComparator2D
    : boost::DefaultConstructible<T>, boost::CopyConstructible<T>, boost::Assignable<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    typedef typename T::Point Point; 

    BOOST_CONCEPT_USAGE( CPolarPointComparator2D )
    {
      myX.setPole( myP ); 

      checkConstConstraints();
    }
    void checkConstConstraints() const
    {
      // const method dummyConst should take parameter myA of type A and return
      // something of type B
      concepts::ConceptUtils::sameType( myB, myX( myP, myP ) );
    }
    // ------------------------- Private Datas --------------------------------
  private:
    T myX; // do not require T to be default constructible.
    Point myP;
    bool myB; 


  }; // end of concept CPolarPointComparator2D
 }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CPolarPointComparator2D_h

#undef CPolarPointComparator2D_RECURSES
#endif // else defined(CPolarPointComparator2D_RECURSES)
