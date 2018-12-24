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
 * @file RayIntersectionPredicates.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/08/14
 *
 * Header file for module RayIntersectionPredicates.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(RayIntersectionPredicates_RECURSES)
#error Recursive header files inclusion detected in RayIntersectionPredicates.h
#else // defined(RayIntersectionPredicates_RECURSES)
/** Prevents recursive inclusion of headers. */
#define RayIntersectionPredicates_RECURSES

#if !defined RayIntersectionPredicates_h
/** Prevents repeated inclusion of headers. */
#define RayIntersectionPredicates_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /**
   * @brief This class implements various intersection predicates between a
   * ray and a triangle, a quad or a surfel in dimension 3.
   *
   * Few details:
   *
   * - Ray-Triangle intersection only uses '+', '*' and '<' operators
   * on Point::Coordinate numbers. It implements "Fast, Minimum
   * Storage Ray/Triangle Intersection", Möller & Trumbore. Journal of
   * Graphics Tools, 1997.
   *
   * - Ray-Quad uses two ray-triangle tests (some redundant
       computations could have been factorized).
   *
   * - Ray-Surfel intersection is performed in KhalimskySpace
   * coordinates for exact computations. For example, a surfel with
   * coordinates (i,j,k) with i being even, is associated to the quad
   * (i,j+/-1,k+/-1).
   *
   * For the later case, this predicate is useful to get the surfel
   * (an iterator on a surfel) of a digital surface intersected by the
   * ray using for instance: 
   *
   * @code
   *   Surface::ConstIterator it = std::find_if(surface.begin(), surface.end(), rayPredicateInstance);
   * @endcode
   *
   * @tparam TPoint type of points.  
   *
   */
  template <typename TPoint>
  struct RayIntersectionPredicate
  {

    ///Only in dimension 3
    BOOST_STATIC_ASSERT( TPoint::dimension == 3);

    ///Type of point
    typedef TPoint Point;
    
    ///Type of vector
    typedef TPoint Vector;
    
    ///Type of point coordinates
    typedef typename TPoint::Component Component;

    /** 
     * Constructor from a ray
     * 
     * @pre dest vector must be not null.
     * 
     * @param origin Origin of the ray 
     * @param dest vector to represent the direction of the ray
     * 
     */    
    RayIntersectionPredicate( const Point &origin, 
                              const Vector &dest)
      : myOrigin(origin), myDest(dest) 
    {
      ASSERT_MSG( dest.norm1() != NumberTraits<typename Point::UnsignedComponent>::ZERO, 
                  "Direction must be non-null vector"); 
    }

    /** 
     * Ray-Triangle intersection predicate (no back-face culling test,
     * i.e., the order of vertices does not matter).
     * 
     * @pre the triangle must be non-degenerate.
     *
     * @param v1 first vertex of the triangle
     * @param v2 second vertex of the triangle
     * @param v3 third vertex of the triangle
     *
     * @return  true if the ray intersects the closed triangle (v1,v2,v3)
     */
    bool operator()(const Point &v1, 
                    const Point &v2,
                    const Point &v3) const
    {
      
      ASSERT((v1 != v2 ) && (v1 != v3) && (v2 != v3));

      Point e1, e2;  //Edge1, Edge2
      Point P, Q, T;
      Component det, u, v;
 
      //Find vectors for two edges sharing V1
      e1 = v2 - v1;
      e2 = v3 - v1;

      //Begin calculating determinant - also used to calculate u parameter
      P = myDest.crossProduct( e2 );
      
      //if determinant is near zero, ray lies in plane of triangle
      det = e1.dot( P );
      if(det == NumberTraits<Component>::ZERO) 
        {
          return false;
        }
      
      //calculate distance from V1 to ray origin
      T =  myOrigin -  v1;
      
      //Calculate u parameter and test bound
      u = T.dot( P );  //* inv_det;
      
      if (det >  NumberTraits<Component>::ZERO)
        {
          if ((u < NumberTraits<Component>::ZERO) ||
              ( u > det))
            {
              return false;
            }
        }
      else
        {
          if ((u > NumberTraits<Component>::ZERO) ||
              ( u < det))
            {
              return false;
            }
        }
 
      //Prepare to test v parameter
      Q = T.crossProduct( e1 );
      
      //Calculate V parameter and test bound
      v = myDest.dot( Q ); 
      
      //The intersection lies outside of the triangle
      if (det >  NumberTraits<Component>::ZERO)
        {
          if ((v < NumberTraits<Component>::ZERO)  ||
              ((u+v) > det)) 
            {
              return false;
            }       
        }
      else
        {
          if ((v > NumberTraits<Component>::ZERO)  ||
              ((u+v) < det)) 
            {
              return false;
            }       
        }

      //distance to triangle must be positive
      Component t = e2.dot( Q ) ;
      if (t*det < NumberTraits<Component>::ZERO)
        return false;
       
      return true;
    }

    /** 
     * Ray-Quad intersection predicate
     * (calls two ray-triangle intersections).
     * 
     * @param v1 first vertex of the quad
     * @param v2 second vertex of the quad
     * @param v3 third vertex of the quad
     * @param v4 fourth vertex of the quad
     *
     * @return  true if the ray intersects the
     * quad (v1,v2,v3,v4)
     */
    bool operator()(const Point &v1, 
                    const Point &v2,
                    const Point &v3,
                    const Point &v4) const
    {
      return (this->operator()(v1,v2,v3) ||
              this->operator()(v1,v4,v3) );
    }

    /** 
     * Ray-Surfel intersection predicate
     * (calls two ray-triangle intersections).
     * 
     * @warning Ray intersection is performed in KhalimskySpace
     * coordinate system. The type @a Point of the
     * RayIntersectionPredicate class must be the same as the 
     * @a Surfel::Point type.
     *
     * @param aSurfel a Khalimsky surfel
     *
     * @return  true if the ray intersects the surfel @a aSurfel
     */
    template < typename Surfel >
    bool operator()(const Surfel &aSurfel) const
    {
      auto const & aPreSurfel = aSurfel.preCell();

      Component x1,x2,x3,x4;
      Component y1,y2,y3,y4;
      Component z1,z2,z3,z4;
      Component ONE = NumberTraits<Component>::ONE;
      
      Point baseQuadCenter =  aPreSurfel.coordinates;
      
      bool yodd = ( NumberTraits<Component>::castToInt64_t(aPreSurfel.coordinates[ 1 ]) & 1 );
      bool zodd = ( NumberTraits<Component>::castToInt64_t(aPreSurfel.coordinates[ 2 ]) & 1 ); 
      
      if(!zodd)
        {
          //zsurfel
          x1= baseQuadCenter[0]-ONE; y1= baseQuadCenter[1]-ONE; z1= baseQuadCenter[2];
          x2= baseQuadCenter[0]+ONE; y2= baseQuadCenter[1]-ONE; z2= baseQuadCenter[2];
          x3= baseQuadCenter[0]+ONE; y3= baseQuadCenter[1]+ONE; z3= baseQuadCenter[2];
          x4= baseQuadCenter[0]-ONE; y4= baseQuadCenter[1]+ONE; z4= baseQuadCenter[2];
        }
      else if(!yodd)
        {
          //ysurfel
          x1= baseQuadCenter[0]-ONE; y1= baseQuadCenter[1]; z1= baseQuadCenter[2]-ONE;
          x2= baseQuadCenter[0]-ONE; y2= baseQuadCenter[1]; z2= baseQuadCenter[2]+ONE;
          x3= baseQuadCenter[0]+ONE; y3= baseQuadCenter[1]; z3= baseQuadCenter[2]+ONE;
          x4= baseQuadCenter[0]+ONE; y4= baseQuadCenter[1]; z4= baseQuadCenter[2]-ONE;
        }
      else
        {
          //xsurfel
          x1= baseQuadCenter[0]; y1= baseQuadCenter[1]-ONE; z1= baseQuadCenter[2]-ONE;
          x2= baseQuadCenter[0]; y2= baseQuadCenter[1]+ONE; z2= baseQuadCenter[2]-ONE;
          x3= baseQuadCenter[0]; y3= baseQuadCenter[1]+ONE; z3= baseQuadCenter[2]+ONE;
          x4= baseQuadCenter[0]; y4= baseQuadCenter[1]-ONE; z4= baseQuadCenter[2]+ONE;
        }
      return this->operator()(Point(x1, y1, z1), Point(x2 ,y2, z2),
                              Point(x3, y3, z3), Point(x4, y4, z4)); 
    }
    
    Point myOrigin;
    Point myDest;    
  }; 

 

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined RayIntersectionPredicates_h

#undef RayIntersectionPredicates_RECURSES
#endif // else defined(RayIntersectionPredicates_RECURSES)
