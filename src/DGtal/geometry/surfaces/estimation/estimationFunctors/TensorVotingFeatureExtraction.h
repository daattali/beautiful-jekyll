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
 * @file TensorVotingFeatureExtraction.h
 * @brief Computes the true quantity to each element of a range associated to a parametric shape.
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/07/22
 *
 * Header file for module TensorVotingFeatureExtraction.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testLengthEstimators.cpp, testTrueLocalEstimator.cpp
 */

#if defined(TensorVotingFeatureExtraction_RECURSES)
#error Recursive header files inclusion detected in TensorVotingFeatureExtraction.h
#else // defined(TensorVotingFeatureExtraction_RECURSES)
/** Prevents recursive inclusion of headers. */
#define TensorVotingFeatureExtraction_RECURSES

#if !defined TensorVotingFeatureExtraction_h
/** Prevents repeated inclusion of headers. */
#define TensorVotingFeatureExtraction_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <DGtal/base/Common.h>
#include <DGtal/topology/SCellsFunctors.h>
#include <vector>
#include "DGtal/math/linalg/SimpleMatrix.h"
#include "DGtal/math/linalg/EigenDecomposition.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace functors
  {
    /////////////////////////////////////////////////////////////////////////////
    // template class TensorVotingFeatureExtraction
    /**
     * Description of template class 'TensorVotingFeatureExtraction' <p>
     * \brief Aim: Implements a functor to detect feature points from
     * normal tensor voting strategy.
     *
     *  More precisely, the
     * functor accumulates tensor votes @f$I - vv^T/\|vv^T\|@f$ for each
     * surfel added during the scan (@f$v@f$ being the vector from the
     * center of the neighborhood to the added surfel). Then, the @e eval()
     * method returns the ratio @f$\frac{\lambda_1+\lambda_2}{\lambda_3}@f$
     * of the eigenvalues (@f$ \lambda_1\leq\lambda_2\leq\lambda_3@f$) of
     * the accumulated tensor votes.
     *
     * (see @cite tensor-voting-ParkLL12)    
     *
     * model of concepts::CLocalEstimatorFromSurfelFunctor
     *
     * @tparam TSurfel type of surfels
     * @tparam TEmbedder type of functors which embed surfel to @f$ \mathbb{R}^3@f$
     */
    template <typename TSurfel, typename TEmbedder>
    class TensorVotingFeatureExtraction
    {
    public:

      typedef TSurfel Surfel;
      typedef TEmbedder SCellEmbedder;
      typedef typename SCellEmbedder::RealPoint RealPoint;
      typedef double Quantity;

      /**
       * Constructor.
       *
       * @param anEmbedder embedder to map surfel to R^n.
       * @param h grid step
       */
      TensorVotingFeatureExtraction(ConstAlias<SCellEmbedder> anEmbedder,
                                    const double h):
        myEmbedder(&anEmbedder), myH(h)
      {
        myId.identity();
        myArea = 0.0;
        myFirstSurfel = true;
        myAccum.constant(0.0);
      }

      /**
       * Add the geometrical embedding of a surfel to the point list and
       * update the tensor voting.
       *
       * @param aSurf a surfel to add
       * @param aDistance  distance of aSurf to the neighborhood boundary
       */
      void pushSurfel(const Surfel & aSurf,
                      const double aDistance)
      {
        if (myFirstSurfel)
          {
            myReceiver =  myEmbedder->operator()(aSurf);
            myFirstSurfel = false;
          }
        else
          {
            myArea+= aDistance;
            const RealPoint p = myEmbedder->operator()(aSurf);
            const RealPoint v = p - myReceiver;
          
            double maxcol = 0.0;
            double matnorm = 0.0;
          
            // I - vv^t/||vv^t||
            for(DGtal::Dimension i= 0; i <3; i++)
              {
                maxcol = 0.0;
                for(DGtal::Dimension j=0; j < 3; j++)
                  {
                    myVote.setComponent(i,j, v(i)*v(j));
                    if (std::abs(v(i)*v(j)) > maxcol)
                      maxcol = std::abs(v(i)*v(j));
                  }
                matnorm += maxcol;
              }
        
            myAccum += (myId - myVote/matnorm)*aDistance;
          }
      }

      /**
       * Evaluate the feature score. 
       *
       * I.e. (l_1+l_2)/l_3 of the tensor eigenvalues (l_1<l_2<l_3).
       *
       * @return the feature score
       */
      Quantity eval( )
      {
        SimpleMatrix<double, 3, 3> eigenvectors;
        RealPoint eigenvalues;

        myAccum /= myArea;
        EigenDecomposition<3, double>::getEigenDecomposition( myAccum, eigenvectors, eigenvalues);
  
#ifdef DEBUG
        for( Dimension i_dim = 1; i_dim < 3; ++i_dim )
            ASSERT ( std::abs(eigenValues[i_dim - 1]) <= std::abs(eigenValues[i_dim]) );
#endif
      
        return ((eigenvalues[0] + eigenvalues[1])/(eigenvalues[2]));
      }

      /**
       * Reset the point list.
       *
       */
      void reset()
      {
        myArea = 0.0;
        myFirstSurfel = true;
        myAccum.constant(0.0);
      }


    private:

      ///First surfel flag
      bool myFirstSurfel;
    
      ///Alias of the geometrical embedder
      const SCellEmbedder * myEmbedder;

      //Grid step
      double myH;

      ///Receiver (embedding of the starting surfel)
      RealPoint myReceiver;
    
      ///Covariance accumulator
      SimpleMatrix<double, 3, 3> myAccum, myId, myVote;
    
      ///Convolution kernel area
      double myArea;
    
    }; // end of class TensorVotingFeatureExtraction
  }//namespace functors
}// namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined TensorVotingFeatureExtraction_h

#undef TensorVotingFeatureExtraction_RECURSES
#endif // else defined(TensorVotingFeatureExtraction_RECURSES)
