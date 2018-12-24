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
 * @file RigidTransformation2D.h
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, France
 *
 * @date 2014/06/26
 *
 * This file is part of the DGtal library.
 */

#if defined(RigidTransformation2D_RECURSES)
#error Recursive header files inclusion detected in RigidTransformation2D.h
#else // defined(RigidTransformation2D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define RigidTransformation2D_RECURSES

#if !defined RigidTransformation2D_h
/** Prevents repeated inclusion of headers. */
#define RigidTransformation2D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <cmath>
#include <climits>
#include <utility>
#include <functional>
#include "DGtal/base/Common.h"
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/kernel/domains/CDomain.h>
#include <DGtal/kernel/CSpace.h>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
namespace functors
{
/////////////////////////////////////////////////////////////////////////////
// Template class ForwardRigidTransformation2D
/**
     * Description of template functor like class 'ForwardRigidTransformation2D' <p>
     * \brief Aim: implements forward rigid transformation of point in the 2D integer space.
     * Warring: This version uses closest neighbor interpolation.
     *
     * @tparam TSpace a 2 dimensional space.
     *
     * @see exampleRigidtransformation2d.cpp
     */
template <typename TSpace>
class ForwardRigidTransformation2D
{
    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CSpace<TSpace> ));
    BOOST_STATIC_ASSERT(( TSpace::dimension == 2 ));

    // ----------------------- Types ------------------------------
public:
    typedef typename TSpace::Point Point;
    typedef typename TSpace::RealPoint RealPoint;
    typedef typename TSpace::RealVector RealVector;

    // ----------------------- Interface --------------------------------------
public:
    /**
       * Constructor.
       * @param aOrigin  the center of rotation.
       * @param angle  the angle given in radians.
       * @param aTranslate  the 2D dimensional vector which represents translation.
       */
    ForwardRigidTransformation2D ( const RealPoint & aOrigin, const double & angle, const RealVector & aTranslate )
        :origin(aOrigin), translation(aTranslate)
    {
        t_sin = std::sin ( angle );
        t_cos = std::cos ( angle );
    }

    /**
       * Operator
       *
       * @return the transformed point.
       */
    inline
    Point operator()( const Point& aInput ) const
    {
        Point p;
        p[0] = std::floor ( ( ( t_cos * ( aInput[0] - origin[0] ) -
               t_sin * ( aInput[1] - origin[1] ) ) + translation[0] ) + origin[0] + 0.5 );

        p[1] = std::floor ( ( ( t_sin * ( aInput[0] - origin[0] ) +
               t_cos * ( aInput[1] - origin[1] ) ) + translation[1] ) + origin[1] + 0.5 );
        return p;
    }

    // ------------------------- Protected Datas ------------------------------
protected:
    RealPoint origin;
    double t_sin;
    double t_cos;
    RealVector translation;
};

/////////////////////////////////////////////////////////////////////////////
// Template class BackwardRigidTransformation2D
/**
     * Description of template functor like class 'BackwardRigidTransformation2D' <p>
     * \brief Aim: implements backward rigid transformation of point in the 2D integer space.
     * Warring: This version uses closest neighbor interpolation.
     *
     * @tparam TSpace a 2 dimensional space.
     *
     * @see exampleRigidtransformation2d.cpp
     */
template <typename TSpace>
class BackwardRigidTransformation2D
{
    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CSpace<TSpace> ));
    BOOST_STATIC_ASSERT(( TSpace::dimension == 2 ));

    // ----------------------- Types ------------------------------
public:
    typedef typename TSpace::Point Point;
    typedef typename TSpace::RealPoint RealPoint;
    typedef typename TSpace::RealVector RealVector;

    // ----------------------- Interface --------------------------------------
public:
    /**
       * Constructor.
       * @param aOrigin  the center of rotation.
       * @param angle  the angle given in radians.
       * @param aTranslate  the 2D dimensional vector which represents translation.
       */
    BackwardRigidTransformation2D ( const RealPoint& aOrigin, const double & angle, const RealVector & aTranslate )
        :origin(aOrigin), translation(aTranslate)
    {
        t_sin = std::sin ( angle );
        t_cos = std::cos ( angle );
    }

    /**
       * Operator
       *
       * @return transformed point.
       */
    inline
    Point operator()( const Point& aInput ) const
    {
        Point p;
        p[0] = std::floor ( ( t_cos * (aInput[0] - translation[0] - origin[0] ) +
               t_sin * ( aInput[1] - translation[1] - origin[1] ) ) + origin[0] + 0.5 );

        p[1] = std::floor ( ( -t_sin * ( aInput[0] - translation[0] - origin[0] ) +
               t_cos * ( aInput[1] - translation[1] - origin[1] ) ) + origin[1] + 0.5 );
        return p;
    }

    // ------------------------- Protected Datas ------------------------------
protected:
    RealPoint origin;
    double t_sin;
    double t_cos;
    RealVector translation;
};

/////////////////////////////////////////////////////////////////////////////
// Template class DomainRigidTransformation2D
/**
     * Description of template functor like class 'DomainRigidTransformation2D' <p>
     * \brief Aim: implements bounds of transformed domain.
     *
     * @tparam TDomain a 2 dimensional domain.
     * @tparam TRigidTransformFunctor a functor which represent two dimensional rigid transformation.
     *
     * @see exampleRigidtransformation2d.cpp
     */
template <typename TDomain, typename TRigidTransformFunctor >
class DomainRigidTransformation2D
{
    ///Checking concepts
    BOOST_STATIC_ASSERT(( TDomain::dimension == 2 ));
    BOOST_CONCEPT_ASSERT(( concepts::CDomain<TDomain> ));

    // ----------------------- Types ------------------------------
public:
    typedef std::pair < typename TDomain::Space::Point, typename TDomain::Space::Point > Bounds;

    // ----------------------- Interface --------------------------------------
public:
    /**
       * Constructor.
       * @param aRigidFunctor  - rigid transformation functor.
       */
    DomainRigidTransformation2D ( const  TRigidTransformFunctor & aRigidFunctor ) : transform ( aRigidFunctor ) {}

    /**
       * Operator
       *
       * @return bounds of the transformed domain.
       */
    inline
    Bounds operator()( const TDomain & aInput ) const
    {
        typedef typename TDomain::Point Point;
        Point points[4];
        points[0] = transform ( aInput.lowerBound() );
        points[1] = transform ( aInput.upperBound() );
        points[2] = transform ( Point ( aInput.upperBound()[0], aInput.lowerBound()[1] ) );
        points[3] = transform ( Point ( aInput.lowerBound()[0], aInput.upperBound()[1] ) );

        Point t_min ( INT_MAX, INT_MAX ), t_max ( INT_MIN, INT_MIN );
        for ( unsigned int i = 0; i < 4 ; i++ )
        {
            if ( points[i][0] < t_min[0] )
                t_min[0] = points[i][0];
            if ( points[i][1] < t_min[1] )
                t_min[1] = points[i][1];

            if ( points[i][0] > t_max[0] )
                t_max[0] = points[i][0];
            if ( points[i][1] > t_max[1] )
                t_max[1] = points[i][1];
        }

        Bounds bounds;
        bounds.first = t_min;
        bounds.second = t_max;
        return bounds;
    }

    // ------------------------- Protected Datas ------------------------------
protected:
   const TRigidTransformFunctor & transform;
};

}// namespace DGtal::functors
}// namespace DGtal

#endif // !defined RigidTransformation2D_h

#undef RigidTransformation2D_RECURSES
#endif // else defined(RigidTransformation2D_RECURSES)

