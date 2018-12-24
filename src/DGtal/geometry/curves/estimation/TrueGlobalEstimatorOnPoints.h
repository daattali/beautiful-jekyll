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
 * @file TrueGlobalEstimatorOnPoints.h
 * @brief Computes the true quantity to each element of a range associated to a parametric shape.
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/06/27
 *
 * Header file for module TrueGlobalEstimatorOnPoints.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testLengthEstimators.cpp, testTrueLocalEstimator.cpp
 */

#if defined(TrueGlobalEstimatorOnPoints_RECURSES)
#error Recursive header files inclusion detected in TrueGlobalEstimatorOnPoints
#else // defined(TrueGlobalEstimatorOnPoints_RECURSES)
/** Prevents recursive inclusion of headers. */
#define TrueGlobalEstimatorOnPoints_RECURSES

#if !defined TrueGlobalEstimatorOnPoints_h
/** Prevents repeated inclusion of headers. */
#define TrueGlobalEstimatorOnPoints_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <list>

#include "DGtal/base/Exceptions.h"
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // template class TrueGlobalEstimatorOnPoints
  /**
   * Description of template class 'TrueGlobalEstimatorOnPoints' <p>
   * \brief Aim: Computes the true quantity to each element of a range associated to 
   * a parametric shape.
   *
   * @tparam TConstIteratorOnPoints type of iterator on points used as
   * query points.
   * @tparam TParametricShape type of the parametric shape.
   * @tparam TParametricShapeFunctor type of Functor used to evaluate
   * the quantity.
   */
  template <typename TConstIteratorOnPoints, typename TParametricShape, typename TParametricShapeFunctor>
  class TrueGlobalEstimatorOnPoints
  {

    // ----------------------- Types ------------------------------
  public:

    typedef TConstIteratorOnPoints ConstIteratorOnPoints;

    typedef TParametricShape ParametricShape;
    typedef typename ParametricShape::RealPoint RealPoint; 
    
    typedef TParametricShapeFunctor ParametricShapeFunctor;
    typedef typename ParametricShapeFunctor::Quantity Quantity;


    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Default constructor.
     */
    TrueGlobalEstimatorOnPoints() 
    {
      myFlagIsInit = false;
    }
   
    /**
     * Constructor.
     * @param h grid size (must be >0).
     * @param itb begin iterator
     * @param ite end iterator
     * @param aShape a shape 
     * @param isClosed true if the input range is closed.
     */
    TrueGlobalEstimatorOnPoints(const double h, 
             const ConstIteratorOnPoints& itb, 
             const ConstIteratorOnPoints& ite,
             ParametricShape* aShape,
             const bool& isClosed);
    
    /**
     * Destructor.
     */
    ~TrueGlobalEstimatorOnPoints() {};

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Initialisation.
     * @param h grid size (must be >0).
     * @param itb begin iterator
     * @param ite end iterator
     * @param aShape a shape
     * @param isClosed true if the input range is viewed as closed.
     */
    void init(const double h, 
        const ConstIteratorOnPoints& itb, 
        const ConstIteratorOnPoints& ite,
        ParametricShape* aShape,
        const bool& isClosed);
    
    /**
     * @return the estimated quantity 
     */
    Quantity eval() ;
    
    /**
     * @return the estimated quantity
     * from itb till ite (exculded)
     */
    Quantity eval(const ConstIteratorOnPoints& itb, 
      const ConstIteratorOnPoints& ite); 


    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------------- Protected Datas ------------------------------
  protected:

    // ------------------------- Private Datas --------------------------------
  private:

    ///Grid size
    double myH; 
    
    ///Bool if the curve is closed
    bool myFlagIsClosed;
    
    ///True if the init() has been called.
    bool myFlagIsInit;
    
    ///Parametric quantity functor
    ParametricShapeFunctor myFunctor;
    
    ///Copy of the begin iterator
    ConstIteratorOnPoints myBegin;
    
    ///Copy of the end iterator
    ConstIteratorOnPoints myEnd;

    // ------------------------- Hidden services ------------------------------
  private:
    
    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    TrueGlobalEstimatorOnPoints ( const TrueGlobalEstimatorOnPoints & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    TrueGlobalEstimatorOnPoints & operator= ( const TrueGlobalEstimatorOnPoints & other );


  }; // end of class TrueGlobalEstimatorOnPoints

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/estimation/TrueGlobalEstimatorOnPoints.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined TrueGlobalEstimatorOnPoints_h

#undef TrueGlobalEstimatorOnPoints_RECURSES
#endif // else defined(TrueGlobalEstimatorOnPoints_RECURSES)
