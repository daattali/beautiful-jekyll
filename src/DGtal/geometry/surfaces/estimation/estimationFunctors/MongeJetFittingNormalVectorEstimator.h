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
 * @file MongeJetFittingNormalVectorEstimator.h
 * @brief Computes the true quantity to each element of a range associated to a parametric shape.
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/05/31
 *
 * Header file for module MongeJetFittingNormalVectorEstimator.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testLengthEstimators.cpp, testTrueLocalEstimator.cpp
 */

#if defined(MongeJetFittingNormalVectorEstimator_RECURSES)
#error Recursive header files inclusion detected in MongeJetFittingNormalVectorEstimator.h
#else // defined(MongeJetFittingNormalVectorEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MongeJetFittingNormalVectorEstimator_RECURSES

#if !defined MongeJetFittingNormalVectorEstimator_h
/** Prevents repeated inclusion of headers. */
#define MongeJetFittingNormalVectorEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <DGtal/base/Common.h>
#include <DGtal/topology/SCellsFunctors.h>

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
  // template class MongeJetFittingNormalVectorEstimator
  /**
   * Description of template class 'MongeJetFittingNormalVectorEstimator' <p>
   * \brief Aim: Estimates normal vector using CGAL Jet Fitting and
   * Monge Form.
   *
   * As discussed in MongeJetFittingMeanCurvatureEstimator, only the
   * estimated normal vector is given up to a sign. Hence, depending
   * on the local orientation of the surface, you would problably have
   * to reverse the estimated vector @f$ \vec{n} @f$ to @f$
   * -\vec{n}@f$.
   *
   * model of concepts::CLocalEstimatorFromSurfelFunctor
   *
   *
   * @tparam TSurfel type of surfels
   * @tparam TEmbedder type of functors which embed surfel to @f$ \mathbb{R}^3@f$
   */
  template <typename TSurfel, typename TEmbedder>
  class MongeJetFittingNormalVectorEstimator
  {
  public:

    typedef TSurfel Surfel;
    typedef TEmbedder SCellEmbedder;
    typedef typename SCellEmbedder::RealPoint RealPoint;
    typedef RealPoint Quantity;

    typedef CGAL::Cartesian<double> CGALKernel;
    typedef CGALKernel::Point_3  CGALPoint;
    typedef CGALKernel::Vector_3  CGALVector;
    typedef CGAL::Monge_via_jet_fitting<CGALKernel>  CGALMongeViaJet;
    typedef CGALMongeViaJet::Monge_form CGALMongeForm;

    /**
     * Constructor.
     *
     * @param anEmbedder embedder to map surfel to R^n.
     * @param h grid step
     * @param d degree of the polynomial surface to fit (default d=4).
     */
    MongeJetFittingNormalVectorEstimator(ConstAlias<SCellEmbedder> anEmbedder,
                                         const double h, unsigned int d = 4):
      myEmbedder(&anEmbedder), myH(h), myD(d)
    {
      FATAL_ERROR_MSG(d>=2, "Polynomial surface degree must be greater than 2");
    }

    /**
     * Add the geometrical embedding of a surfel to the point list
     *
     * @param aSurf a surfel to add
     * @param aDistance  distance of aSurf to the neighborhood boundary
     */
    void pushSurfel(const Surfel & aSurf,
                    const double aDistance)
    {
      BOOST_VERIFY(aDistance == aDistance);

      RealPoint p = myEmbedder->operator()(aSurf);
      CGALPoint pp(p[0]*myH,p[1]*myH,p[2]*myH);
      myPoints.push_back(pp);
    }

    /**
     * Evaluate the normal vector from Monge form.
     *
     * @return the mean curvature
     */
    Quantity eval( )
    {
      CGALMongeForm monge_form;
      CGALMongeViaJet monge_fit;

      monge_form = monge_fit(myPoints.begin() , myPoints.end(), myD, (2<myD)? myD : 2);

      CGALVector v= monge_form.normal_direction (  );

      return RealPoint(v.x(),v.y(),v.z());
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

     //Grid step
    double myH;

    ///Degree of the polynomial surface to fit
    unsigned int myD;

  }; // end of class MongeJetFittingNormalVectorEstimator
  }
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined MongeJetFittingNormalVectorEstimator_h

#undef MongeJetFittingNormalVectorEstimator_RECURSES
#endif // else defined(MongeJetFittingNormalVectorEstimator_RECURSES)
