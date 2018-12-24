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
 * @file SphericalHoughNormalVectorEstimator.h
 * @brief Computes normal vector directions using Hough (spherical)
 * accumulator.
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2016/03/14
 *
 * Header file for module SphericalHoughNormalVectorEstimator.cpp
 *
 * This file is part of the DGtal library.
 *
 */

#if defined(SphericalHoughNormalVectorEstimator_RECURSES)
#error Recursive header files inclusion detected in SphericalHoughNormalVectorEstimator.h
#else // defined(SphericalHoughNormalVectorEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SphericalHoughNormalVectorEstimator_RECURSES

#if !defined SphericalHoughNormalVectorEstimator_h
/** Prevents repeated inclusion of headers. */
#define SphericalHoughNormalVectorEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <DGtal/base/Common.h>
#include <DGtal/topology/SCellsFunctors.h>
#include <vector>
#include "DGtal/geometry/tools/SphericalAccumulator.h"
#include <random>
#include "DGtal/math/linalg/SimpleMatrix.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace functors
  {
    /////////////////////////////////////////////////////////////////////////////
    // template class SphericalHoughNormalVectorEstimator
    /**
     * Description of template class 'SphericalHoughNormalVectorEstimator' <p>
     * \brief Aim: This functor estimates normal vector for a collection of surfels using
     * spherical accumulator based Hough voting.
     *
     * This functors implements @cite BoulchM12 algorithm:
     *   - we first collect the surfels using the @a pushSurfel method;
     *   - we select random triples of surfels and estimate the normal vectors of the associated triangles;
     *   - each normal vector is added to a spherical accumulator (see SphericalAccumulator);
     *   - the estimated normal vector is computed from normal vectors of the bin of the accumulator with maximal vote.
     *
     * To avoid aliasing artefacts of the spherical accumulator, several randomly
     * rotated accumulators are used.
     *
     * Given a random triple of surfels, a threshold on the triangle aspect ratio
     * can be specified to discard bad aspect triangles (e.g. thin ones).
     *
     * This functor is a model of concepts::CLocalEstimatorFromSurfelFunctor
     *
     * @tparam TSurfel type of surfels
     * @tparam TEmbedder type of functors which embed surfel to @f$ \mathbb{R}^3@f$
     */
    template <typename TSurfel, typename TEmbedder>
    class SphericalHoughNormalVectorEstimator
    {
    public:
      
      typedef TSurfel Surfel;
      typedef TEmbedder SCellEmbedder;
      typedef typename SCellEmbedder::RealPoint RealPoint;
      typedef RealPoint Quantity;
      typedef SimpleMatrix<double,3,3> Matrix;
      
      /**
       * Constructor.
       *
       * @param [in] anEmbedder embedder to map surfel to R^n.
       * @param [in] h grid step
       * @param [in] minimalAspectRatio the minimal aspect ratio of triangles to be considered in the accumulator (default=0.001).
       * @param [in] nbTrials number of random triangles in the neighborhood to consider (default=100).
       * @param [in] accumulatorSize size of the spherical accumulators (see SphericalAccumulator, default=10).
       * @param [in] nbAccumulators number of randomly rotated spherical accumulators to consider in order to avoid aliasing artefacts. (default=5)
       */
      SphericalHoughNormalVectorEstimator(ConstAlias<SCellEmbedder> anEmbedder,
                                          const double h,
                                          const double minimalAspectRatio = 0.001,
                                          const unsigned int nbTrials = 100,
                                          const unsigned int accumulatorSize = 10,
                                          const unsigned int nbAccumulators = 5) :
      myEmbedder(&anEmbedder),myH(h), myAspectRatio(minimalAspectRatio),
      myNbTrials( nbTrials), mySize(accumulatorSize) , myNbAccumulators(nbAccumulators)
      {
        SphericalAccumulator<RealPoint> accum(mySize);
        
        //We precompute the random rotations and accumulators
        for(auto i = 0u; i < myNbAccumulators; ++i)
        {
          Matrix m = randomRotation();
          myAccumulators.push_back( accum );
          myRotations.push_back( m );
          myInverseRotations.push_back( m.inverse() );
        }
      }

      /**
       * Disable default constructor.
       */
      SphericalHoughNormalVectorEstimator() = delete;

      
      /**
       * Add the geometrical embedding of a surfel to the point list and
       * update the normal spherical hough voting.
       *
       * @param aSurf a surfel to add
       * @param aDistance  distance of aSurf to the neighborhood boundary (NOT USED HERE)
       */
      void pushSurfel(const Surfel & aSurf,
                      const double aDistance)
      {
        BOOST_VERIFY(aDistance == aDistance);
        RealPoint p = myH * ( myEmbedder->operator()(aSurf) );
        myPoints.push_back(p);
      }
      
      /**
       * Estimate normal vector using spherical accumulator
       * voting.
       *
       * @return the feature score
       */
      Quantity eval( )
      {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(0, myPoints.size() - 1 );
        double aspect;
        
        for(auto t = 0u; t < myNbTrials ; ++t)
        {
          unsigned int i,j,k;
          
          //We pick 3 distinct point indices.
          i = distribution(generator);
          j = distribution(generator);
          while ( (j = distribution(generator)) == i);
          while (( (k = distribution(generator)) == i) || (k == j) );
          
          RealPoint vector = getNormal(i,j,k,aspect);
          if ((vector.norm() > 0.00001) && (aspect > myAspectRatio))
          {
            //we have an admissible triangle, we push both normal vectors
            for(auto acc = 0u; acc < myNbAccumulators; ++acc)
            {
              RealPoint shifted = myRotations[acc]*vector;
              myAccumulators[acc].addDirection( shifted );
              myAccumulators[acc].addDirection( -shifted );
            }
          }
        }
        //We return the max bin orientation summing up all accumulators vote
        typename SphericalAccumulator<RealPoint>::Size posPhi,posTheta;
        RealPoint vote;
        for(auto acc = 0u; acc < myNbAccumulators; ++acc)
        {
          myAccumulators[acc].maxCountBin(posPhi, posTheta);
          RealPoint dir = myInverseRotations[acc]*myAccumulators[acc].representativeDirection(posPhi, posTheta).getNormalized() ;
          
          //We only consider z-oriented normals (since we pushed vector and -vector)
          if ( dir.dot(RealPoint(0,0,1)) > 0.0 )
          vote += dir;
          else
          vote += -dir;
        }
        return vote.getNormalized();
      }
      
      /**
       * Reset the point list.
       *
       */
      void reset()
      {
        myPoints.clear();
        //accumulators cleanup
        for(auto i = 0u; i < myNbAccumulators; ++i)
          myAccumulators[i].clear();
      }
      
    private:
      
      /**
       * @return a random rotation matrix.
       */
      Matrix randomRotation() const
      {
        const double theta = (rand()+0.f)/RAND_MAX * 2* M_PI;
        const double phi = (rand()+0.f)/RAND_MAX * 2* M_PI;
        const  double psi = (rand()+0.f)/RAND_MAX * 2* M_PI;
        Matrix Rt;
        Rt.setComponent(0,0,1);
        Rt.setComponent(1,0,0);
        Rt.setComponent(2,0,0);
        Rt.setComponent(0,1,0);
        Rt.setComponent(1,1,cos(theta));
        Rt.setComponent(2,1,-sin(theta));
        Rt.setComponent(0,2,0);
        Rt.setComponent(1,2,sin(theta));
        Rt.setComponent(2,2,cos(theta));
        
        Matrix Rph;
        Rph.setComponent(0,0,cos(phi));
        Rph.setComponent(1,0,0);
        Rph.setComponent(2,0,sin(phi));
        Rph.setComponent(0,1,0);
        Rph.setComponent(1,1,1);
        Rph.setComponent(2,1,0);
        Rph.setComponent(0,2,-sin(phi));
        Rph.setComponent(1,2,0);
        Rph.setComponent(2,2,cos(phi));
        
        Matrix Rps;
        Rps.setComponent(0,0,cos(psi));
        Rps.setComponent(1,0,-sin(psi));
        Rps.setComponent(2,0,0);
        Rps.setComponent(0,1,sin(psi));
        Rps.setComponent(1,1,cos(psi));
        Rps.setComponent(2,1,0);
        Rps.setComponent(0,2,0);
        Rps.setComponent(1,2,0);
        Rps.setComponent(2,2,1);
        
        return Rt*Rph*Rps;
      }
      
      /**
       * Computes the (unnormalized) normal vector of a triangle defined
       * by triangle (i,j,k).
       * The variable @a aspect returns the aspect ratio of the triangle.
       *
       * @param [in] i a first vertex index.
       * @param [in] j a second vertex index.
       * @param [in] k a third vertex index.
       * @param [out] aspect aspect ratio of the triangle.
       *
       * @return a random rotation matrix.
       */
      Quantity getNormal(const unsigned int i,
                         const unsigned int j,
                         const unsigned int k,
                         double &aspect) const
      {
        ASSERT( i < myPoints.size());
        ASSERT( j < myPoints.size());
        ASSERT( k < myPoints.size());
        
        const RealPoint v = myPoints[i] - myPoints[j];
        const RealPoint u = myPoints[i] - myPoints[k];
        const RealPoint w = myPoints[j] - myPoints[k];
        
        //aspect ratio
        const double a = u.norm() , b = v.norm();
        const double c = w.norm();
        const double s = (a+b+c)/2.0;
        aspect = a*b*c/(8.0*(s-a)*(s-b)*(s-c));
        
        return v.crossProduct(u);
      }
      
      ///Alias of the geometrical embedder
      const SCellEmbedder * myEmbedder;
      
      ///Grid step
      const double myH;
      
      ///Minimal aspect ratio (norm of the cross-product) to consider a given triangle
      const double myAspectRatio;
      
      ///Number of trials in the neignborhood
      const unsigned int myNbTrials;
      
      ///Size of the accumulator
      const unsigned int mySize;
      
      ///Number of randomly shifted spherical accumulators to consider
      const unsigned int myNbAccumulators;
      
      ///vector of embedded surfels
      std::vector<RealPoint> myPoints;
      
      ///Spherical Accumulators
      std::vector< SphericalAccumulator<RealPoint> > myAccumulators;
      
      ///Random rotations
      std::vector< Matrix > myRotations;
      
      ///Random inverse rotations
      std::vector< Matrix > myInverseRotations;
      
      
    }; // end of class SphericalHoughNormalVectorEstimator
  } // namespace functors
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SphericalHoughNormalVectorEstimator_h

#undef SphericalHoughNormalVectorEstimator_RECURSES
#endif // else defined(SphericalHoughNormalVectorEstimator_RECURSES)
