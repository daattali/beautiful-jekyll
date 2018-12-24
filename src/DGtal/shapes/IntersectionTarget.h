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
 * @file IntersectionTarget.h
 * @brief Description of intersection target according to separation and dimensions
 * @date 2017/06/11
 *
 *
 * This file is part of the DGtal library.
 */

#if !defined IntersectionTarget_h
/** Prevents repeated inclusion of headers. */
#define IntersectionTarget_h

#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/shapes/Mesh.h"
#include "DGtal/shapes/IntersectionTarget.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/sets/CDigitalSet.h"
#include "DGtal/geometry/tools/determinant/PredicateFromOrientationFunctor2.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBySimple3x3Matrix.h"

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  /**
     Description of template class 'IntersectionTarget'

     \brief Aim: A class for intersection target used for voxelization.
   
     @see MeshVoxelizer

     @tparam TSpace space of the digitalset
     @tparam TSeparation strategy of the voxelization (6 or 26)
     @tparam TDimension dimension of the intersection target
  */
  template<typename TSpace, size_t TSeparation, size_t TDimension = 1>
  struct IntersectionTargetTrait
  {
    ///Digital Set dimension Checking
    BOOST_STATIC_ASSERT_MSG( TSpace::dimension == 3, "DigitalSet dimension must be 3");

    ///Separation Checking
    BOOST_STATIC_ASSERT_MSG( TSeparation == 6 || TSeparation == 26, "Separation must be 6 or 26");

    ///Dimension of the intersection target checking
    BOOST_STATIC_ASSERT_MSG( TDimension == 1, "Currently only 1D intersection target is implemented");

    /**
     * Remove of default constructor
     */
    IntersectionTargetTrait() = delete;

    ///Internal intersection target structure
    template<typename Space, size_t Separation, size_t Dimension = 1>
    struct IntersectionTarget;

    /****** Associated types *********************/
    using Space2D  = SpaceND<2, typename TSpace::Integer>;
    using PointR3  = typename TSpace::RealPoint;
    using VectorR3 = typename TSpace::RealPoint;
    using PointR2  = typename Space2D::RealPoint;
    using Type = IntersectionTarget<TSpace, TSeparation, TDimension>;
    /*********************************************/

    ///Internal Edge structure
    struct Edge
    {
      PointR3 myFirst, mySecond;
      Edge() = default;
      Edge(const Edge&) = default;
      Edge(const PointR3& mf, const PointR3& ms) : myFirst(mf), mySecond(ms) {}
    };

    /**
     * Specialization for 6-separated with 1D intersection target
     */
    template<typename Space>
    struct IntersectionTarget<Space, 6, 1>
    {
      // ----------------------- Members ------------------------------

      ///Target
      const std::array<Edge, 3> myTarget {{
          { { 0.5, 0.0, 0.0 }, { -0.5,  0.0,  0.0} } , // AB
          { { 0.0, 0.0, 0.5 }, {  0.0,  0.0, -0.5} } , // CD
          { { 0.0, 0.5, 0.0 }, {  0.0, -0.5,  0.0} }   // EF
        }};

      // ----------------------- Standard services --------------------

      /**
       * Get definition of the target
       * @return intersection target
       */
      const std::array<Edge, 3>& operator()() {
        return myTarget;
      }

      /**
       * Get edge of index i
       * @param i index
       * @return intersection target
       */
      const Edge& operator()(int i) {
        return myTarget[i];
      }

      /**
       * 2D Projection of 3D point on plane with normal represented by edge of index i
       * @param i index of target's edge representing the normal of the plane for the projection
       * @param p 3d point
       * @return 2d point
       */
      PointR2 project(int i, const PointR3& p) const {
        ASSERT( 0 <= i && i <= 2 );

        if(myTarget[i].myFirst[0] == 0.5)
          return { p[1], p[2] }; // ignore x
        else if(myTarget[i].myFirst[1] == 0.5)
          return { p[0], p[2] }; // ignore y
        else
          return { p[0], p[1] }; // ignore z
      }
    };

    /**
     * Specialization for 26-separated with 1D intersection target
     */
    template<typename Space>
    struct IntersectionTarget<Space, 26, 1>
    {
      // ----------------------- Members ------------------------------

      ///Target
      const std::array<Edge, 4> myTarget {{
          { { -0.5, 0.5,  0.5}, {  0.5, -0.5, -0.5} } , // AG
          { {  0.5, 0.5,  0.5}, { -0.5, -0.5, -0.5} } , // BH
          { {  0.5, 0.5, -0.5}, { -0.5, -0.5,  0.5} } , // CE
          { { -0.5, 0.5, -0.5}, {  0.5, -0.5,  0.5} }   // DF
        }};

      ///E1 base for each target's edge
      std::array<VectorR3, 4> myE1base;

      ///E2 base for each target's edge
      std::array<VectorR3, 4> myE2base;

      /**
       * Default constructor
       */
      IntersectionTarget<Space, 26, 1>()
      {
        const double coef = 1. / std::sqrt(3.);

        std::array<VectorR3, 4> myNormal {{
            {  coef, -coef, -coef } ,
            { -coef, -coef, -coef } ,
            { -coef, -coef,  coef } ,
            {  coef, -coef,  coef }
          }};

        // computation of each e1/e2 bases foreach normal
        for(int i = 0; i < 4; i++)
        {
          auto& x = myNormal[i][0];
          auto& y = myNormal[i][1];
          auto& z = myNormal[i][2];

          myE1base[i] = std::move( VectorR3(-y, x, 0).getNormalized() );
          myE2base[i] = std::move( VectorR3(-x*z, -y*z, x*x + y*y).getNormalized() );
        }
      }

      // ----------------------- Standard services --------------------

      /**
       * Get definition of the target
       * @return intersection target
       */
      const std::array<Edge, 4>& operator()() const {
        return myTarget;
      }

      /**
       * Get edge of index i
       * @param i index
       * @return intersection target
       */
      const Edge& operator()(int i) const {
        return myTarget[i];
      }

      /**
       * 2D Projection of 3D point on plane with normal represented by edge of index i
       * @param i index of target's edge representing the normal of the plane for the projection
       * @param p 3d point
       * @return 2d point
       */
      PointR2 project(int i, const PointR3& p) const {
        ASSERT( 0 <= i && i <= 3 );

        return { myE1base[i].dot(p), myE2base[i].dot(p) };
      }
    };
  };
}

#endif // !defined MeshVoxelizer_h
