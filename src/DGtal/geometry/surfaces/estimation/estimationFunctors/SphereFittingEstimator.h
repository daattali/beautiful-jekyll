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
 * @file SphereFittingEstimator.h
 * @brief Computes the true quantity to each element of a range associated to a parametric shape.
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/05/31
 *
 * Header file for module SphereFittingEstimator.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testLengthEstimators.cpp, testTrueLocalEstimator.cpp
 */

#if defined(SphereFittingEstimator_RECURSES)
#error Recursive header files inclusion detected in SphereFittingEstimator.h
#else // defined(SphereFittingEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SphereFittingEstimator_RECURSES

#if !defined SphereFittingEstimator_h
/** Prevents repeated inclusion of headers. */
#define SphereFittingEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <DGtal/base/Common.h>
#include <DGtal/topology/SCellsFunctors.h>

#ifndef WITH_PATATE
#error You need to have activated Patate (WITH_PATATE) to include this file.
#endif

//Patate includes
#include <Patate/grenaille.h>
#include <Eigen/Eigen>
#include <vector>

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace functors
  {
    /////////////////////////////////////////////////////////////////////////////
    // template class SphereFittingEstimator
    /**
     * Description of template class 'SphereFittingEstimator' <p>
     * \brief Aim: Use Patate library to perform a local sphere fitting.
     *
     * Given a kernel radius, this functor performs a sphere fitting
     * and outputs the parameters of an AlgebraicSphere (please see
     * Patate documentation for details).
     *
     * Model of concepts::CLocalEstimatorFromSurfelFunctor.
     *
     * @tparam TSurfel type of surfels
     * @tparam TEmbedder type of functors which embed surfel to @f$
     * \mathbb{R}^3@f$.
     * @tparam TNormalVectorEstimatorCache the type of normal vector
     * cache to consider (see EstimatorCache class).
     *
     * @see testSphereFitting.cpp
     **/
    template <typename TSurfel,
              typename TEmbedder,
              typename TNormalVectorEstimatorCache>
    class SphereFittingEstimator
    {
    public:

      
      class PatatePoint
      {
      public:
	enum {Dim = 3};
	typedef double Scalar;
	typedef Eigen::Matrix<Scalar, Dim, 1>   VectorType;
	typedef Eigen::Matrix<Scalar, Dim, Dim> MatrixType;
        
	MULTIARCH inline PatatePoint(const VectorType& _pos    = VectorType::Zero(), 
                                     const VectorType& _normal = VectorType::Zero())
          : m_pos(_pos), m_normal(_normal) {}
        
	MULTIARCH inline const VectorType& pos()    const { return m_pos; }  
	MULTIARCH inline const VectorType& normal() const { return m_normal; }

	MULTIARCH inline VectorType& pos()    { return m_pos; }  
	MULTIARCH inline VectorType& normal() { return m_normal; }

      private:
	VectorType m_pos, m_normal;
      };

     
      typedef TSurfel Surfel;
      typedef TEmbedder SCellEmbedder;
      typedef typename SCellEmbedder::RealPoint RealPoint;

      typedef TNormalVectorEstimatorCache NormalVectorEstimatorCache;

      typedef typename PatatePoint::Scalar Scalar;
      typedef typename PatatePoint::VectorType VectorType;
      
      typedef Grenaille::DistWeightFunc<PatatePoint,Grenaille::SmoothWeightKernel<Scalar> > WeightFunc; 
      typedef Grenaille::Basket<PatatePoint,WeightFunc,Grenaille::OrientedSphereFit, Grenaille::GLSParam> Fit;

      ///Quantity type: a 3-sphere (model of CQuantity)
      struct Quantity
      {
        RealPoint center;
        double radius;
        double tau;
        double kappa;
        RealPoint eta;
        
        Quantity(){}
        Quantity(RealPoint p, double rad, double _tau,
                 double _kappa, RealPoint _eta): center(p), radius(rad),
                                                 tau(_tau), kappa(_kappa),
                                                 eta(_eta) {}
        ~Quantity(){}
        bool operator==(Quantity aq) {return (center==aq.center) && (radius==aq.radius);}
        bool operator<(Quantity aq) {return (center<aq.center) && (radius<aq.radius);}        
        bool operator!=(Quantity aq) {return !(*this == aq);}
      };


      /**
       * Constructor.
       *
       * @param [in] anEmbedder embedder to map surfel to R^n.
       * @param [in] h gridstep.
       * @param [in] radius  radius of the convolution kernel (in
       * @f$\mathbb{Z}^n@f$ space).
       * @param [in] anEstimator normal vector estimator on the surface.
       */
      SphereFittingEstimator(ConstAlias<SCellEmbedder> anEmbedder,
                             const double h,
                             const double radius,
                             ConstAlias<NormalVectorEstimatorCache> anEstimator):
        myEmbedder(&anEmbedder), myH(h), myNormalEsitmatorCache(&anEstimator)
      {
        //From Mellado's example
        myFit = new Fit();
        myWeightFunction = new WeightFunc(radius);
        myFit->setWeightFunc(*myWeightFunction);
      }


      /**
       * Destructor.
       */
      ~SphereFittingEstimator( )
      {
        delete myWeightFunction;
        delete myFit ;
      }

      
      /**
       * Add the geometrical embedding of a surfel to the point list
       *
       * @param [in] aSurf a surfel to add
       * @param [in] aDistance of aSurf to the neighborhood boundary
       */
      void pushSurfel(const Surfel & aSurf,
                      const double aDistance)
      {
        BOOST_VERIFY(aDistance==aDistance);

        RealPoint p = myEmbedder->operator()(aSurf);
        RealPoint norm = myNormalEsitmatorCache->eval(aSurf);          
        VectorType pp;
        pp(0) = p[0]*myH;
        pp(1) = p[1]*myH;
        pp(2) = p[2]*myH;
        VectorType normal;
        normal(0) = norm[0];
        normal(1) = norm[1];
        normal(2) = norm[2];
        PatatePoint point(pp,  normal);
        if (myFirstPoint)
          {
            myFirstPoint = false;
            myFit->init(pp);
          }
        else
          myFit->addNeighbor(point);
        
#ifdef DEBUG_VERBOSE
        trace.info() <<"#";
#endif
      }

      /**
       * Evaluate the sphere fitting.
       *
       * @return the fitted sphere 
       */
      Quantity eval()
      {
        myFit->finalize();

#ifdef DEBUG_VERBOSE
        trace.info() <<std::endl;
        
        //Test if the fitting ended without errors
	if(myFit->isStable())
	{
		std::cout << "Center: [" << myFit->center().transpose() << "] ;  radius: " << myFit->radius() << std::endl;

		std::cout << "Pratt normalization" 
			<< (myFit->applyPrattNorm() ? " is now done." : " has already been applied.") << std::endl;

	
		std::cout << "Fitted Sphere: " << std::endl
			<< "\t Tau  : "      << myFit->tau()             << std::endl
			<< "\t Eta  : "      << myFit->eta().transpose() << std::endl
			<< "\t Kappa: "      << myFit->kappa()           << std::endl;

	}
        else
          {
            std::cout << "Ooops... not stable result"<<std::endl;
          }
#endif
        Quantity res;
        res.center = RealPoint((myFit->center())(0),
                               (myFit->center())(1),
                               (myFit->center())(2));
        res.radius =  myFit->radius();
        res.tau = myFit->tau();
        res.kappa = myFit->kappa();
        res.eta = RealPoint((myFit->eta())(0),
                            (myFit->eta())(1),
                            (myFit->eta())(2));
        return res;
      }
                             

      /**
       * Reset the point list.
       *
       */
      void reset()
      {
        delete myFit;
        myFit = new Fit();
        myFirstPoint = true;
        myFit->setWeightFunc(*myWeightFunction);
     }


    private:

      ///Alias of the geometrical embedder
      const SCellEmbedder * myEmbedder;

      ///Fitting object
      Fit *myFit;
      
      ///Grid step
      double myH;

      ///Boolean for initial point
      bool myFirstPoint;
      
      ///NormalVectorCache
      const NormalVectorEstimatorCache *myNormalEsitmatorCache;

      ///const WeightFunction
      const  WeightFunc *myWeightFunction;
      
    }; // end of class SphereFittingEstimator
  }
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SphereFittingEstimator_h

#undef SphereFittingEstimator_RECURSES
#endif // else defined(SphereFittingEstimator_RECURSES)
