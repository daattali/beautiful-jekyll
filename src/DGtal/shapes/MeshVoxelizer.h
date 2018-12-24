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
 * @file MeshVoxelizer.h
 * @brief Compute a voxelization of a Mesh into a DigitalSet
 * @date 2016/01/24
 *
 * Header file for module MeshVoxelizer.ih
 *
 * This file is part of the DGtal library.
 */

#if !defined MeshVoxelizer_h
/** Prevents repeated inclusion of headers. */
#define MeshVoxelizer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/shapes/Mesh.h"
#include "DGtal/shapes/IntersectionTarget.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/sets/CDigitalSet.h"
#include "DGtal/geometry/tools/determinant/PredicateFromOrientationFunctor2.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBySimple3x3Matrix.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  /**
   Description of template class 'MeshVoxelizer'

   \brief Aim: A class for computing the digitization of a triangle or
   a Mesh.

   This class is parametrized by a Separation strategy (either 6 or
   26). This value corresponds to the separability of a digitized
   continuous plane. For instance, if the value is set to 6, then
   the digitization of an Euclidean plane is such that no 6-path
   exists to go from one side to the other of the Euclidean plane (see
   @cite KletteRosenfeld_book).
   
   From the separability parameter, a template is constructed. A voxel
   belongs to the digitization if and only if the template centered at
   a given voxel intersects the triangle.

   This approach is a CPU straightforward implementation of
   @cite Laine13.

   6 and 26 templates are the following ones:

   @image html 6-sep.png "Template for 6-separating digitization"
   @image html 26-sep.png "Template for 26-separating digitization"


   @tparam TDigitalSet a DigitalSet (model of concepts::CDigitalSet)
   @tparam Separation strategy of the voxelization (6 or 26)
   */
  template <typename TDigitalSet, int Separation = 6>
  class MeshVoxelizer
  {

  public:

    ///Concept Checking
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet<TDigitalSet> ));

    ///Digital Set Type
    typedef TDigitalSet DigitalSet;
    BOOST_STATIC_ASSERT_MSG( DigitalSet::Space::dimension == 3, "DigitalSet dimension must be 3");

    ///Separation Checking
    BOOST_STATIC_ASSERT_MSG( Separation == 6 || Separation == 26, "Separation must be 6 or 26");

    /****** Associated types *********************/
    using Space = typename DigitalSet::Space;
    using Space2D = SpaceND<2, typename Space::Integer>;
    using MeshFace = std::vector< unsigned int >;
    using Domain   = typename DigitalSet::Domain;
    using PointR3  = typename Space::RealPoint;
    using VectorR3 = typename Space::RealPoint;
    using PointR2  = typename Space2D::RealPoint;
    using PointZ3  = typename Space::Point;
    using OrientationFunctor = InHalfPlaneBySimple3x3Matrix<PointR2, double>;
    using IntersectionTarget = typename IntersectionTargetTrait<Space, Separation, 1>::Type;
    /*********************************************/

  public:

    /**
     * Constructor of the voxelizer
     */
    MeshVoxelizer() = default;

    // ----------------------- Standard services ------------------------------
    /**
     * Voxelize the mesh into the digital set.
     * @warning if the mesh has non-trianuglar faces, we naively triangulate
     * using a triangle fan at zero. If the face is not convex, the output
     * will not be correct.
     *
     * If one voxel is outside the digtial set (@a outputSet) domain, the voxel
     * is skipped.
     *
     * @param [out] outputSet the set that collects the voxels.
     * @param [in] aMesh the mesh to voxelize (vertex coordinates will
     * be casted to @e PointR3 points.
     * @param [in] scaleFactor the scale factor to apply to the mesh
     * (default=1.0)
     * @tparam MeshPoint the type of point of the mesh.
     */
    template<typename MeshPoint>
    void voxelize(DigitalSet &outputSet,
                  const Mesh<MeshPoint> &aMesh,
                  const double scaleFactor = 1.0);

    /**
     * Voxelize a unique triangle (a,b,c) into the digital set.
     * voxels are inserted to the @e outputSet.
     *
     * @param [out] outputSet the set that collects the voxels.
     * @param [in] a the first point of the triangle
     * @param [in] b the second point of the triangle
     * @param [in] c the third point of the triangle
     * @param [in] scaleFactor the scale factor to apply to the triangle (default=1.0)
     * @tparam MeshPoint the type of point of the triangle (casted to
     * PointR3 later).
     *
     */
    template<typename MeshPoint>
    void voxelize(DigitalSet &outputSet,
                  const MeshPoint &a, const MeshPoint &b, const MeshPoint &c,
                  const double scaleFactor = 1.0);



    // ----------------------- Internal services ------------------------------
    ///Enum type when deciding if a 2D point belongs to a 2D triangle.
    enum TriangleOrientation { OUTSIDE, INSIDE, ONEDGE, ONVERTEX };

    /**
     * Compute (unsigned) distance between @a p and the Euclidean plane
     * defined by normal vector @a n and point @a M
     * @param M point
     * @param n normal
     * @param p point p
     * @return distance the distance to the plane
     */
    static
    double distance(const PointR3& M,
                    const VectorR3& n,
                    const PointZ3& p) ;

    /**
     * Predicate to know if @a p (2D point) is inside ABC (2D triangle)
     * @param A Point A
     * @param B Point B
     * @param C Point C
     * @param p point p
     * @return TriangleOrientation either  {OUTSIDE, INSIDE, ONEDGE, ONVERTEX}
     */
    static
    TriangleOrientation pointIsInside2DTriangle(const PointR2& A,
                                                const PointR2& B,
                                                const PointR2& C,
                                                const PointR2& p) ;

    /**
     * Predicate to decide if a real point @a P is inside voxel @a v
     * @param P point P
     * @param v voxel v
     * @return true if P is inside v
     */
    static
    bool pointIsInsideVoxel(const PointR3& P,
                            const PointZ3& v) ;

    /**
     * Voxelize ABC to the digitalSet
     * @param [out] outputSet the set that collects the voxels.
     * @param A Point A
     * @param B Point B
     * @param C Point C
     * @param n normal of ABC
     * @param bbox bounding box of ABC
     */
    void voxelizeTriangle(DigitalSet &outputSet,
                          const PointR3& A,
                          const PointR3& B,
                          const PointR3& C,
                          const VectorR3& n,
                          const std::pair<PointR3, PointR3>& bbox);

    // ----------------------- Members ------------------------------

  private:

    ///Intersection target
    IntersectionTarget myIntersectionTarget;
  };
}

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/MeshVoxelizer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined MeshVoxelizer_h
