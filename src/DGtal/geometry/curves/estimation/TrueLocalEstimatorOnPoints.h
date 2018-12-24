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
 * @file TrueLocalEstimatorOnPoints.h
 * @brief Computes the true quantity to each element of a range associated to a parametric shape.
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/06/27
 *
 * Header file for module TrueLocalEstimatorOnPoints.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testLengthEstimators.cpp, testTrueLocalEstimator.cpp
 */

#if defined(TrueLocalEstimatorOnPoints_RECURSES)
#error Recursive header files inclusion detected in TrueLocalEstimatorOnPoints.h
#else // defined(TrueLocalEstimatorOnPoints_RECURSES)
/** Prevents recursive inclusion of headers. */
#define TrueLocalEstimatorOnPoints_RECURSES

#if !defined TrueLocalEstimatorOnPoints_h
/** Prevents repeated inclusion of headers. */
#define TrueLocalEstimatorOnPoints_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // template class TrueLocalEstimatorOnPoints
  /**
   * Description of template class 'TrueLocalEstimatorOnPoints' <p>
   * \brief Aim: Computes the true quantity to each element of a range associated to 
   * a parametric shape.
   *
   * @tparam TConstIteratorOnPoints type of iterator on points used as
   * query points.
   * @tparam TParametricShape type of the parametric shape.
   * @tparam TParametricShapeFunctor type of Functor used to evaluate
   * the quantity.
   */
  template <typename TConstIteratorOnPoints, 
	    typename TParametricShape, 
	    typename TParametricShapeFunctor>
  class TrueLocalEstimatorOnPoints
  {

    // ----------------------- Types ------------------------------
  public:

    typedef TConstIteratorOnPoints ConstIterator;

    typedef TParametricShape ParametricShape;
    typedef typename TParametricShape::RealPoint RealPoint;
    
    typedef TParametricShapeFunctor ParametricShapeFunctor;
    typedef typename ParametricShapeFunctor::Quantity Quantity;


    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Default constructor.
     */
    TrueLocalEstimatorOnPoints();  
   
    
    /**
     * Destructor.
     */
    ~TrueLocalEstimatorOnPoints();

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Initialisation.
     * @param h grid size (must be >0).
     * @param itb begin iterator
     * @param ite end iterator
     */
    void init(const double h, 
	      const ConstIterator& itb, 
	      const ConstIterator& ite);
    
    /**
     * Attach a shape
     * @param aShapePtr parametric shape
     */
    void attach(ParametricShape* aShapePtr);

    /**
     * Estimation at *it
     * @return the estimated quantity at *it
     */
    Quantity eval(const ConstIterator& it) const;
    
    /**
     * Estimation at each element of [@e itb , @e ite )
     * @param itb begin iterator
     * @param ite end iterator
     * @param result  the output iterator to the results.
     * @return the estimated quantity
     * from itb till ite (excluded)
     */
    template <typename OutputIterator>
    OutputIterator eval(const ConstIterator& itb, 
			const ConstIterator& ite, 
                        OutputIterator result) const; 


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
    
    ///Copy of the begin iterator
    ConstIterator myBegin;
    
    ///Copy of the end iterator
    ConstIterator myEnd;

    ///Owning pointer on a parametric shape functor
    ParametricShapeFunctor* myFunctorPtr;

    // ------------------------- Hidden services ------------------------------
  private:
    
    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    TrueLocalEstimatorOnPoints ( const TrueLocalEstimatorOnPoints & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    TrueLocalEstimatorOnPoints & operator= ( const TrueLocalEstimatorOnPoints & other );


  }; // end of class TrueLocalEstimatorOnPoints

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/estimation/TrueLocalEstimatorOnPoints.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined TrueLocalEstimatorOnPoints_h

#undef TrueLocalEstimatorOnPoints_RECURSES
#endif // else defined(TrueLocalEstimatorOnPoints_RECURSES)
