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
 * @file ParametricShapeTangentFunctor.h
 * @brief Computes the tangent vector at a given point of a parametric shape.
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/06/30
 *
 * Header file for module ParametricShapeTangentFunctor.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testLengthEstimators.cpp, testTrueLocalEstimator.cpp
 */

#if defined(ParametricShapeTangentFunctor_RECURSES)
#error Recursive header files inclusion detected in ParametricShapeTangentFunctor.h
#else // defined(ParametricShapeTangentFunctor_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ParametricShapeTangentFunctor_RECURSES

#if !defined ParametricShapeTangentFunctor_h
/** Prevents repeated inclusion of headers. */
#define ParametricShapeTangentFunctor_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class ParametricShapeTangentFunctor
  /**
   * Description of template class 'ParametricShapeTangentFunctor' <p>
   * \brief Aim: implements a functor that computes the tangent vector
   * at a given point of a parametric shape.
   *
   * @tparam TParametricShape a model of parametric shape.
   */
  template <typename TParametricShape>
  class ParametricShapeTangentFunctor
  {
    
    // ----------------------- Standard services ------------------------------
  public:

    ///Type of parametric shape.
    typedef TParametricShape ParametricShape;

    ///Type of points.
    typedef typename TParametricShape::RealPoint RealPoint;

    ///Type of the functor output.
    typedef typename TParametricShape::RealPoint Quantity;

    /**
     * Constructor.
     */
    ParametricShapeTangentFunctor(){}


    /**
     * Constructor..
     *
     * @param aShape the input shape.
     */
    ParametricShapeTangentFunctor(ParametricShape *aShape): myShape(aShape) {};
    
    
    /**
     * Destructor.
     */
    ~ParametricShapeTangentFunctor(){}

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    ParametricShapeTangentFunctor & operator= ( const ParametricShapeTangentFunctor & other )
    {
      myShape = other.myShape;
      return *this;
    }

   
    /** 
     * Compute the tangent at [aPoint]
     *
     * @param aPoint the point at which the tangent is computed. 
     * @return the tangent at [aPoint].
     */
    Quantity operator()(const RealPoint &aPoint)
    {
      ASSERT(myShape);

      double t = myShape->parameter( aPoint );   
      return  myShape->tangent( t );
    }
    

    // ------------------------- Private Datas --------------------------------
  private:
    
    ///Copy of the implicit shape.
    ParametricShape *myShape;
    
    // ------------------------- Internals ------------------------------------
  private:
    
  }; // end of class ParametricShapeTangentFunctor
  
} // namespace DGtal

                                                                        //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ParametricShapeTangentFunctor_h

#undef ParametricShapeTangentFunctor_RECURSES
#endif // else defined(ParametricShapeTangentFunctor_RECURSES)
