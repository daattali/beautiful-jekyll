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
 * @file SimpleLinearRegression.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 *
 * @date 2011/06/24
 *
 * Header file for module SimpleLinearRegression
 *
 * This file is part of the DGtal library.
 */

#if defined(SimpleLinearRegression_RECURSES)
#error Recursive header files inclusion detected in SimpleLinearRegression.h
#else // defined(SimpleLinearRegression_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SimpleLinearRegression_RECURSES

#if !defined SimpleLinearRegression_h
/** Prevents repeated inclusion of headers. */
#define SimpleLinearRegression_h


//////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
//////////////////////////////////////////////////////////////////////////////


namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class SimpleLinearRegression
  /////////////////////////////////////////////////////////////////////////////
  /**
   * @brief Description of class 'SimpleLinearRegression'
   *
   * Aim:
   * Represents a simple linear regression model with 1 regressor
   * constant and 1 variable regressor and n data: Y = X B + U, where
   * U follows Gaussian law N(0, sigma^2 I_n).  Y, U are n-vectors, B
   * is a 2-vector, X is the nx2-matrix [(1 x1) ... (1 xn) ] with rank
   * 2.
   *
   * This class can compute the linear regression coefficients and
   * also performs some tests to check if the data corresponds to a
   * linear model.
   *
   * @note  backport from [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene).
   */
  class SimpleLinearRegression
  {

    // ----------------------- Standard services ------------------------------
  public:
    
    /**
     * Destructor.
     */
    ~SimpleLinearRegression();
    
    /**
     * Constructor.
     * The object is empty (and invalid for regression).
     *
     * @param eps_zero the value below which the absolute value of the
     * determinant is considered null.
     */
    SimpleLinearRegression( double eps_zero = 1e-8 );

    /**
     * Clear all datas.
     */
    void clear();

    /**
     * Adds the samples (y,x). Does not compute immediately the
     * regression. See 'computeRegression' for computing the
     * regression with the current samples.
     *
     * @param begin_x an iterator on the first x-data
     * @param end_x an iterator after the last x-data
     * @param begin_y an iterator on the first y-data
     *
     * @see computeRegression
     */
    template <class XIterator, class YIterator>
    void addSamples( XIterator begin_x, XIterator end_x, YIterator begin_y );

    /**
     * Adds the sample (y,x). Does not compute immediately the
     * regression. See 'computeRegression' for computing the
     * regression with the current samples.
     *
     * @param x the x data.
     * @param y the y data.
     *
     * @see computeRegression
     */
    void addSample( const double x, const double y );

    /**
     * Computes the regression of the current parameters.
     *
     * @return 'true' if the regression was valid (non null number of
     * samples, rank of X is 2), 'false' otherwise.
     */
    bool computeRegression();

    /**
     * @return the slope of the linear regression (B1 in Y=B0+B1*X).
     */
    double slope() const;


    /**
     * @return the intercept of the linear regression (B0 in Y=B0+B1*X).
     */
    double intercept() const;

    /**
     * Given a new x, predicts its y (hat{y}) according to the linear
     * regression model.
     *
     * @param x any value.
     * @return the estimated y value, ie hat{y} = B0 + B1*x.
     */
    double estimateY( double x ) const;

    /**
     * @return the current estimation of the variance of the Gaussian
     * perturbation (i.e. variance of U).
     */
    double estimateVariance() const;

    /**
     * Given a test confidence value (1-[a]), return the expected interval
     * of value for Y, given a new [x], so that the model is still
     * linear. One may thus check if a new pair (y,x) is still in the
     * current linear model or not.
     *
     * @param x any x value.
     * @param a the expected confidence value for the test (a=0.05
     * means 95% of confidence).
     *
     * @return the expected interval [min_y, max_y] such that any
     * value y within confirms the current linear model.
     */
    std::pair<double,double> trustIntervalForY( const double x,
                                                const double a ) const;


    /** 
     * Set the epsilon zero value, value below which the absolute
     * value of the determinant is considered null.
     *
     * @param aEpsilonZero the epsilon zero value.
     */    
    void setEpsilonZero(const double aEpsilonZero)
    {
      myEpsilonZero = aEpsilonZero;
    }

    /** 
     * 
     * @return the epsilon zero value.
     */
    double epsilonZero() const
    {
      return myEpsilonZero;
    }

    /** 
     * 
     * @return the number of samples.
     */
    double size() const
    {
      return myN;
    }

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param that_stream the output stream where the object is written.
     */
    void selfDisplay( std::ostream & that_stream ) const;
    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;


    // ------------------------- Datas ----------------------------------------

  private:

    ///Epsilon zero value
    double myEpsilonZero;

    ///Number of samples
    unsigned int myN;

    ///Ordinate values of sample points
    std::vector<double> myY;
    
    ///Abscissa values of sample points
    std::vector<double> myX;
    
    ///Linear regression line parameters [0] is the intercept and [1]
    ///the slope.
    double myB[ 2 ];

    //Internal quantities.
    std::vector<double> myU;
    double mySumX;
    double mySumX2;
    double mySumY;
    double mySumXY;
    double myD;
    double myNormU2;

    // ------------------------- Hidden services ------------------------------
  protected:

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    SimpleLinearRegression( const SimpleLinearRegression & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
     SimpleLinearRegression & operator=( const SimpleLinearRegression & other );

    // ------------------------- Internals ------------------------------------
  private:


  };

  /**
   * Overloads 'operator<<' for displaying objects of class 'SimpleLinearRegression'.
   * @param that_stream the output stream where the object is written.
   * @param that_object_to_display the object of class 'SimpleLinearRegression' to write.
   * @return the output stream after the writing.
   */
  std::ostream&
  operator<<( std::ostream & that_stream,
	      const SimpleLinearRegression & that_object_to_display );


} // namespace ImaGene


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods if necessary.
#include "DGtal/math/SimpleLinearRegression.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SimpleLinearRegression_h

#undef SimpleLinearRegression_RECURSES
#endif // else defined(SimpleLinearRegression_RECURSES)
