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
 * @file LinearLeastSquareFittingNormalVectorEstimator.h
 * @brief Computes the true quantity to each element of a range associated to a parametric shape.
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/05/31
 *
 * Header file for module LinearLeastSquareFittingNormalVectorEstimator.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testLengthEstimators.cpp, testTrueLocalEstimator.cpp
 */

#if defined(LinearLeastSquareFittingNormalVectorEstimator_RECURSES)
#error Recursive header files inclusion detected in LinearLeastSquareFittingNormalVectorEstimator.h
#else // defined(LinearLeastSquareFittingNormalVectorEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define LinearLeastSquareFittingNormalVectorEstimator_RECURSES

#if !defined LinearLeastSquareFittingNormalVectorEstimator_h
/** Prevents repeated inclusion of headers. */
#define LinearLeastSquareFittingNormalVectorEstimator_h

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
#include <CGAL/linear_least_squares_fitting_3.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace functors
  {
  /////////////////////////////////////////////////////////////////////////////
  // template class LinearLeastSquareFittingNormalVectorEstimator
  /**
   * Description of template class 'LinearLeastSquareFittingNormalVectorEstimator' <p>
   * \brief Aim: Estimates normal vector using CGAL linear least
   * squares plane fitting.
   *
   * model of concepts::CLocalEstimatorFromSurfelFunctor
   *
   *
   * @tparam TSurfel type of surfels
   * @tparam TEmbedder type of functors which embed surfel to R^3
   */
  template <typename TSurfel, typename TEmbedder>
  class LinearLeastSquareFittingNormalVectorEstimator
  {
  public:

    typedef TSurfel Surfel;
    typedef TEmbedder SCellEmbedder;
    typedef typename SCellEmbedder::RealPoint RealPoint;
    typedef RealPoint Quantity;

    typedef CGAL::Cartesian<double> CGALKernel;
    typedef CGALKernel::Point_3  CGALPoint;
    typedef CGALKernel::Plane_3  CGALPlane;
    typedef CGALKernel::Vector_3  CGALVector;

    /**
     * Constructor.
     *
     * @param anEmbedder embedder to map surfel to R^n.
     * @param h gridstep.
     */
    LinearLeastSquareFittingNormalVectorEstimator(ConstAlias<SCellEmbedder> anEmbedder, const double h):
      myEmbedder(&anEmbedder), myH(h)
    {
    }

    /**
     * Add the geometrical embedding of a surfel to the point list
     *
     * @param aSurf a surfel to add
     * @param aDistance distance to the origin surfel
     */
    void pushSurfel(const Surfel & aSurf,
                    const double aDistance)
    {
      BOOST_VERIFY(aDistance == aDistance);
      RealPoint p = myEmbedder->operator()(aSurf);
      CGALPoint pp(p[0],p[1],p[2]);
      myPoints.push_back(pp);
    }

    /**
     * Evaluate the normal vector from linear least squares fitting.
     *
     * @return the mean curvature
     */
    Quantity eval( )
    {
      CGALPlane plane;
      CGAL::linear_least_squares_fitting_3(myPoints.begin(),myPoints.end(), plane, CGAL::Dimension_tag<0>());
      CGALVector v = plane.orthogonal_vector();
      RealPoint vv(v.x(),v.y(),v.z());
      return vv.getNormalized();
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

    ///Grid Step
    double myH;



  }; // end of class LinearLeastSquareFittingNormalVectorEstimator
  }
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined LinearLeastSquareFittingNormalVectorEstimator_h

#undef LinearLeastSquareFittingNormalVectorEstimator_RECURSES
#endif // else defined(LinearLeastSquareFittingNormalVectorEstimator_RECURSES)
