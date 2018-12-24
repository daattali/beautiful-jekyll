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
 * @file OrderedLinearRegression.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 *
 * @date 2011/06/24
 *
 * Header file for module OrderedLinearRegression
 *
 * This file is part of the DGtal library.
 */

#if defined(OrderedLinearRegression_RECURSES)
#error Recursive header files inclusion detected in OrderedLinearRegression.h
#else // defined(OrderedLinearRegression_RECURSES)
/** Prevents recursive inclusion of headers. */
#define OrderedLinearRegression_RECURSES

#if !defined OrderedLinearRegression_h
/** Prevents repeated inclusion of headers. */
#define OrderedLinearRegression_h


//////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include "DGtal/math/SimpleLinearRegression.h"
//////////////////////////////////////////////////////////////////////////////
namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // class OrderedLinearRegression
  /////////////////////////////////////////////////////////////////////////////
  /**
   * @brief Description of class 'OrderedLinearRegression'
   *
   * Aim: Utility based on SimpleLinearRegression to compute
   * regression on ordered data. Hence, we can obtain linear fitting
   * with interval trust from the left to the right (resp. from the
   * right to the left) of the data.
   *
   * @note  backport from [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene).
   */
  class OrderedLinearRegression
  {
    // ----------------------- Standard services ------------------------------
  public:
    
    /**
     * Destructor.
     */
    ~OrderedLinearRegression()
    {}
    
    /**
     * Constructor.
     * The object is empty (and invalid for regression).
     *
     * @param[in] eps_zero the value below which the absolute value of the
     * determinant is considered null.
     */
    OrderedLinearRegression( double eps_zero = 1e-8 ):
      myEpsilonZero(eps_zero),
      myN(0)
    {}

    /**
     * Clears the data.
     */
    void clear()
    {
      myX.clear();
      myY.clear();
      myN = 0;
    }

    /**
     * Adds the samples (x,y). Does not compute immediately the
     * regression but copies the data. See 'forwardSLR' or
     * 'backwardSLR' for computing the regression with the current
     * samples.
     *
     * @param[in] begin_x an iterator on the first x-data
     * @param[in] end_x an iterator after the last x-data
     * @param[in] begin_y an iterator on the first y-data
     *
     * @see forwardSLR backwardSLR
     */
    template <class XIterator, class YIterator>
    void addSamples( XIterator begin_x, XIterator end_x, YIterator begin_y )
      {
        for ( ; begin_x != end_x; ++begin_x, ++begin_y )
          {
            addSample( *begin_x, *begin_y );
          }
      }


    /**
     * Adds the sample (x,y). Does not compute immediately the
     * regression but copies the data. See 'forwardSLR' or
     * 'backwardSLR' for computing the regression with the current
     * samples.
     *
     * @param[in] x the x data.
     * @param[in] y the y data.
     *
     * @see forwardSLR backwardSLR
     */
    void addSample( const double x, const double y )
    {
      myX.push_back( x );
      myY.push_back( y );
      ++myN;
    }


    // ----------------------- Interface --------------------------------------
    /**
     * Returns the slope of the first straight part of the data. The
     * straightness is evaluated through a statistic test based on a
     * simple linear regression (SLR) model. 
     * It requires two parameters: 
     * @a n is the minimum number of samples to fit a linear model,
     * 1-[ @a alpha] is the proportion of accepted linear model of the
     * test (99%, alpha=0.01, means that 99% of all linear model with
     * a Gaussian noise are accepted).
     *
     * @param[in] n the minimum number of samples greater than 3 (default
     * value is 4).  
     * @param[in] alpha is the proportion of rejected linear
     * model (the ones with big variance, default value is 0.01).
     *
     * @param[out] linearModel the SLR instance of the first straight part of the data.
     */
    void forwardSLR(SimpleLinearRegression &linearModel,
                    const unsigned int n = 4,
                    const double alpha = 0.01) const
    {
      linearModel.setEpsilonZero(myEpsilonZero);
      linearModel.clear();
      std::vector<double>::const_iterator itx = myX.begin(); 
      std::vector<double>::const_iterator itxe = myX.end(); 
      std::vector<double>::const_iterator ity = myY.begin(); 
      linearModel.addSamples( itx, itx + n, ity );
      linearModel.computeRegression();
      itx += n;
      ity += n;
      unsigned int l = myX.size() - n + 1;
      for ( ; itx != itxe; ++itx, ++ity, --l )
        {
          std::pair<double,double> ic;
          ic = linearModel.trustIntervalForY( *itx, alpha );
          if ( ( *ity < ic.first ) || ( *ity > ic.second ) )
            break;
          linearModel.addSample( *itx, *ity );
          linearModel.computeRegression();
        }
    }

    
     /**
     * Returns the slope of the last straight part of the data.  The
     * straightness is evaluated through a statistic test based on a
     * simple linear regression (SLR) model. 
     * It requires two parameters: 
     * @a n is the minimum number of samples to fit a linear model,
     * 1-[ @a alpha] is the proportion of accepted linear model of the
     * test (99%, alpha=0.01, means that 99% of all linear model with
     * a Gaussian noise are accepted).
     *
     * @param[in] n the minimum number of samples greater than 3 (default
     * value is 4).  
     * @param[in] alpha is the proportion of rejected linear
     * model (the ones with big variance, default value is 0.01).
     *
     * @param[out] linearModel the SLR instance of the last straight part of the data.
     */
    void backwardSLR(SimpleLinearRegression &linearModel,
                     const unsigned int n = 4,
                     const double alpha = 0.01 ) const
    {
      linearModel.setEpsilonZero(myEpsilonZero);
      linearModel.clear();
      std::vector<double>::const_reverse_iterator itx = myX.rbegin(); 
      std::vector<double>::const_reverse_iterator itxe = myX.rend(); 
      std::vector<double>::const_reverse_iterator ity = myY.rbegin(); 
      linearModel.addSamples( itx, itx + n, ity );
      linearModel.computeRegression();
      itx += n;
      ity += n;
      unsigned int l = myX.size() - n + 1;
      for ( ; itx != itxe; ++itx, ++ity, --l )
        {
          std::pair<double,double> ic;
          ic = linearModel.trustIntervalForY( *itx, alpha );
          if ( ( *ity < ic.first ) || ( *ity > ic.second ) )
            break;
          linearModel.addSample( *itx, *ity );
          linearModel.computeRegression();
        }
    }
    
    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param that_stream the output stream where the object is written.
     */
    void selfDisplay( std::ostream & that_stream ) const
    {
      that_stream << "[OrderedLinearRegression]  Number of samples="<< myN;
    }
    
    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const
    {
      return true;
    }


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
   

    // ------------------------- Hidden services ------------------------------
  protected:

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    OrderedLinearRegression( const OrderedLinearRegression & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
     OrderedLinearRegression & operator=( const OrderedLinearRegression & other );

    // ------------------------- Internals ------------------------------------
  private:


  };

  /**
   * Overloads 'operator<<' for displaying objects of class 'OrderedLinearRegression'.
   * @param that_stream the output stream where the object is written.
   * @param that_object_to_display the object of class 'OrderedLinearRegression' to write.
   * @return the output stream after the writing.
   */
  std::ostream&
  operator<<( std::ostream & that_stream,
	      const OrderedLinearRegression & that_object_to_display );


} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#endif // !defined OrderedLinearRegression_h

#undef OrderedLinearRegression_RECURSES
#endif // else defined(OrderedLinearRegression_RECURSES)
