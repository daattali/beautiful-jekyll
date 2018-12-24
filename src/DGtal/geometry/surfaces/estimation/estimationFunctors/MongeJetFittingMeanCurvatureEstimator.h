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
 * @file MongeJetFittingMeanCurvatureEstimator.h
 * @brief Computes the true quantity to each element of a range associated to a parametric shape.
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/05/31
 *
 * Header file for module MongeJetFittingMeanCurvatureEstimator.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testLengthEstimators.cpp, testTrueLocalEstimator.cpp
 */

#if defined(MongeJetFittingMeanCurvatureEstimator_RECURSES)
#error Recursive header files inclusion detected in MongeJetFittingMeanCurvatureEstimator.h
#else // defined(MongeJetFittingMeanCurvatureEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MongeJetFittingMeanCurvatureEstimator_RECURSES

#if !defined MongeJetFittingMeanCurvatureEstimator_h
/** Prevents repeated inclusion of headers. */
#define MongeJetFittingMeanCurvatureEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <DGtal/base/Common.h>
#include <DGtal/topology/SCellsFunctors.h>

#ifndef WITH_CGAL
#error You need to have activated CGAL (WITH_CGAL) to include this file.
#endif

//CGAL
#include <CGAL/Cartesian.h>
#include <CGAL/Monge_via_jet_fitting.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace functors
  {
  /////////////////////////////////////////////////////////////////////////////
  // template class MongeJetFittingMeanCurvatureEstimator
  /**
   * Description of template class 'MongeJetFittingMeanCurvatureEstimator' <p>
   * \brief Aim: Estimates Mean curvature using CGAL Jet Fitting and
   * Monge Form.
   *
   * Be carefull, this functor uses a polynomial surface fitting from
   * point set. Curvature information is given from Monge basis which
   * could be up to the orientation of the normal vector. Hence, if
   * the estimated normal @f$ n @f$ is such that @f$ n\cdot n_0>0@f$ with
   * @f$ n_0@f$ being the true normal at the point set center,
   * everything is ok.
   * Otherwise, we have to inverse the princiapl curvature sign:
   * @f$ k_1=-k_2@f$ and @f$ k_2= -k_1@f$.
   *
   * The mean curvature estimation is thus given up to a sign.
   *
   * model of concepts::CLocalEstimatorFromSurfelFunctor.
   *
   *
   * @tparam TSurfel type of surfels
   * @tparam TEmbedder type of functors which embed surfel to @f$ \mathbb{R}^3@f$
   */
  template <typename TSurfel, typename TEmbedder>
  class MongeJetFittingMeanCurvatureEstimator
  {
  public:

    typedef TSurfel Surfel;
    typedef TEmbedder SCellEmbedder;
    typedef double Quantity;
    typedef typename SCellEmbedder::RealPoint RealPoint;

    typedef CGAL::Cartesian<double> CGALKernel;
    typedef CGALKernel::Point_3  CGALPoint;
    typedef CGAL::Monge_via_jet_fitting<CGALKernel>  CGALMongeViaJet;
    typedef CGALMongeViaJet::Monge_form CGALMongeForm;

    /**
     * Constructor.
     *
     * @param anEmbedder embedder to map surfel to R^n.
     * @param h gridstep.
     * @param d degree of the polynomial surface to fit.
     */
    MongeJetFittingMeanCurvatureEstimator(ConstAlias<SCellEmbedder> anEmbedder,
                                          const double h, unsigned int d = 4):
      myEmbedder(&anEmbedder), myH(h), myD(d)
    {
      FATAL_ERROR_MSG(d>=2,"Polynomial surface degree must be greater than 2");
    }

    /**
     * Add the geometrical embedding of a surfel to the point list
     *
     * @param aSurf a surfel to add
     * @param aDistance of aSurf to the neighborhood boundary
     */
    void pushSurfel(const Surfel & aSurf,
                    const double aDistance)
    {
      BOOST_VERIFY(aDistance==aDistance);

      RealPoint p = myEmbedder->operator()(aSurf);
      CGALPoint pp(p[0]*myH,p[1]*myH,p[2]*myH);
      myPoints.push_back(pp);
    }

    /**
     * Evaluate the curvature from Monge form.
     *
     * @return the mean curvature
     */
    Quantity eval()
    {
      CGALMongeForm monge_form;
      CGALMongeViaJet monge_fit;

      monge_form = monge_fit(myPoints.begin() , myPoints.end(), myD, (2<myD)? myD : 2);

      double k1 = monge_form.principal_curvatures ( 0 );
      double k2 = monge_form.principal_curvatures ( 1 );
      return 0.5*(k1+k2);
    }

    /**
     * Reset the point list.
     *
     */
    void reset()
    {
      myPoints.clear();
    }


  private:

    ///Alias of the geometrical embedder
    const SCellEmbedder * myEmbedder;

    ///Array of CGAL points
    std::vector<CGALPoint> myPoints;

    ///Grid step
    double myH;

    ///Degree of the polynomial surface to fit
    unsigned int myD;

  }; // end of class MongeJetFittingMeanCurvatureEstimator
  }
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined MongeJetFittingMeanCurvatureEstimator_h

#undef MongeJetFittingMeanCurvatureEstimator_RECURSES
#endif // else defined(MongeJetFittingMeanCurvatureEstimator_RECURSES)
