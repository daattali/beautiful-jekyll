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
 * @file RigidTransformation3D.h
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, France
 *
 * @date 2014/06/28
 *
 * Header file for module RigidTransformation3D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(RigidTransformation3D_RECURSES)
#error Recursive header files inclusion detected in RigidTransformation3D.h
#else // defined(RigidTransformation3D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define RigidTransformation3D_RECURSES

#if !defined RigidTransformation3D_h
/** Prevents repeated inclusion of headers. */
#define RigidTransformation3D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <cmath>
#include <climits>
#include <utility>
#include <exception>
#include "DGtal/base/Common.h"
#include <DGtal/kernel/domains/CDomain.h>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
namespace functors
{
/////////////////////////////////////////////////////////////////////////////
// Template class ForwardRigidTransformation3D
/**
     * Description of template functor like class 'ForwardRigidTransformation3D' <p>
     * \brief Aim: implements forward rigid transformation of point in 3D integer space around any arbitrary axis.
     * This implementation uses the
     * <a href="http://mathworld.wolfram.com/RodriguesRotationFormula.html">Rodrigues' rotation formula</a>.
     * Warring: This version uses closest neighbor interpolation.
     *
     * @tparam TSpace a 3 dimensional space.
     *
     * @see exampleRigidtransformation3d.cpp
     */
template <typename TSpace>
class ForwardRigidTransformation3D
{
    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CSpace<TSpace> ));
    BOOST_STATIC_ASSERT(( TSpace::dimension == 3 ));

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
       * @param aAxis  the axis of rotation.
       * @param angle  the angle given in radians.
       * @param aTranslate  the 3D dimensional vector which represents translation.
       */
    ForwardRigidTransformation3D ( const RealPoint & aOrigin, const RealVector & aAxis,
                                   const double & angle, const RealVector & aTranslate )
        : axis(aAxis.getNormalized()), origin(aOrigin), trans(aTranslate)


    {
        if ( std::isnan( axis.norm() ) )
            throw std::runtime_error ( "Axis of rotation can not be set as a vector of length 0!" );
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

        p[0] = std::floor ( ( ( ( ( t_cos + ( axis[0] * axis[0] ) * ( 1. - t_cos ) ) * ( aInput[0] - origin[0] ) )
                + ( ( axis[0] * axis[1] * ( 1. - t_cos ) - axis[2] * t_sin ) * ( aInput[1] - origin[1] ) )
                + ( ( axis[1] * t_sin + axis[0] * axis[2] * ( 1. - t_cos )  ) * ( aInput[2] - origin[2] ) ) ) + trans[0] ) + origin[0] + 0.5 );

        p[1] = std::floor ( ( ( ( ( axis[2] * t_sin + axis[0] * axis[1] * ( 1. - t_cos ) ) *  ( aInput[0] - origin[0] ) )
                + ( ( t_cos + ( axis[1] * axis[1] ) * ( 1. - t_cos ) ) * ( aInput[1] - origin[1] ) )
                + ( ( -axis[0] * t_sin + axis[1] * axis[2] * ( 1. - t_cos ) ) * ( aInput[2] - origin[2] ) ) ) + trans[1] ) + origin[1] + 0.5 );

        p[2] = std::floor ( ( ( ( ( -axis[1] * t_sin + axis[0] * axis[2] * ( 1. - t_cos ) ) * ( aInput[0] - origin[0] ) )
                + ( ( axis[0] * t_sin + axis[1] * axis[2] * ( 1. - t_cos ) ) * ( aInput[1] - origin[1] ) )
                + ( ( t_cos + ( axis[2] * axis[2] ) * ( 1. - t_cos ) ) * ( aInput[2] - origin[2] ) ) ) + trans[2] ) + origin[2] + 0.5 );

        return p;
    }

    // ------------------------- Protected Datas ------------------------------
protected:
    RealVector axis;
    RealPoint origin;
    double t_sin;
    double t_cos;
    RealVector trans;
};

/////////////////////////////////////////////////////////////////////////////
// Template class BackwardRigidTransformation3D
/**
     * Description of template functor like class 'BackwardRigidTransformation3D' <p>
     * \brief Aim: implements backward rigid transformation of point in 3D integer space around any arbitrary axis.
     * This implementation uses the
     * <a href="http://mathworld.wolfram.com/RodriguesRotationFormula.html">Rodrigues' rotation formula</a>.
     * Warring: This version uses closest neighbor interpolation.
     *
     * @tparam TSpace a 3 dimensional space.
     *
     * @see exampleRigidtransformation3d.cpp
     */
template <typename TSpace>
class BackwardRigidTransformation3D
{
    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CSpace<TSpace> ));
    BOOST_STATIC_ASSERT(( TSpace::dimension == 3 ));

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
       * @param aAxis  the axis of rotation.
       * @param angle  the angle given in radians.
       * @param aTranslate  the 3D dimensional vector which represents translation.
       */
    BackwardRigidTransformation3D ( const RealPoint & aOrigin, const RealVector & aAxis,
                                    const double & angle, const RealVector & aTranslate )
        : axis(aAxis.getNormalized()), origin(aOrigin), trans(aTranslate)
    {
        if ( std::isnan( axis.norm() ) )
            throw std::runtime_error ( "Axis of rotation can not be set as a vector of length 0!" );

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

        p[0] = std::floor ( ( ( ( ( t_cos + ( axis[0] * axis[0] ) * ( 1. - t_cos ) ) * ( aInput[0] - trans[0] - origin[0] ) )
                + ( ( axis[2] * t_sin + axis[0] * axis[1] * ( 1. - t_cos ) ) * ( aInput[1] - trans[1] - origin[1] ) )
                + ( ( -axis[1] * t_sin + axis[0] * axis[2] * ( 1. - t_cos ) ) * ( aInput[2] - trans[2] - origin[2] ) ) ) ) + origin[0] + 0.5 );

        p[1] = std::floor ( ( ( ( ( axis[0] * axis[1] * ( 1. - t_cos ) - axis[2] * t_sin )  * ( aInput[0] - trans[0] - origin[0] ) )
                + ( ( t_cos + ( axis[1] * axis[1] ) * ( 1. - t_cos ) ) * ( aInput[1] - trans[1] - origin[1] ) )
                + ( ( axis[0] * t_sin + axis[1] * axis[2] * ( 1. - t_cos ) ) * ( aInput[2] - trans[2] - origin[2] ) ) ) ) + origin[1] + 0.5 );

        p[2] = std::floor ( ( ( ( ( axis[1] * t_sin + axis[0] * axis[2] * ( 1. - t_cos )  ) * ( aInput[0] - trans[0] - origin[0] ) )
                + ( ( -axis[0] * t_sin + axis[1] * axis[2] * ( 1. - t_cos ) ) * ( aInput[1] - trans[1] - origin[1] ) )
                + ( ( t_cos + ( axis[2] * axis[2] ) * ( 1. - t_cos ) ) * ( aInput[2] - trans[2] - origin[2] ) ) ) ) + origin[2] + 0.5 );
        return p;
    }

    // ------------------------- Protected Datas ------------------------------
private:
    RealVector axis;
    RealPoint origin;
    double t_sin;
    double t_cos;
    RealVector trans;
};

/////////////////////////////////////////////////////////////////////////////
// Template class DomainRigidTransformation3D
/**
     * Description of template functor like class 'DomainRigidTransformation3D' <p>
     * \brief Aim: implements bounds of transformed domain.
     *
     * @tparam TDomain a 3 dimensional domain.
     * @tparam TRigidTransformFunctor a functor which represent three dimensional rigid transformation.
     *
     * @see exampleRigidtransformation3d.cpp
     */
template <typename TDomain, typename TRigidTransformFunctor >
class DomainRigidTransformation3D
{
    ///Checking concepts
    BOOST_STATIC_ASSERT(( TDomain::dimension == 3 ));
    BOOST_CONCEPT_ASSERT(( concepts::CDomain<TDomain> ));

    // ----------------------- Types ------------------------------
public:
    typedef std::pair < typename TDomain::Space::Point, typename TDomain::Space::Point > Bounds;

    // ----------------------- Interface --------------------------------------
public:
    /**
       * Constructor.
       * @param aRigidFunctor  - functor to rigid transformation.
       */
    DomainRigidTransformation3D ( const TRigidTransformFunctor & aRigidFunctor ) : transform ( aRigidFunctor ) {}

    /**
       * Operator
       *
       * @return bounds of the transformed domain.
       */
    inline
    Bounds operator()( const TDomain & aInput ) const
    {
        typedef typename TDomain::Point Point;

        Point points[8];
        points[0] = transform ( aInput.lowerBound() );
        points[1] = transform ( aInput.upperBound() );
        points[2] = transform ( Point ( aInput.upperBound()[0], aInput.lowerBound()[1], aInput.lowerBound()[2] ) );
        points[3] = transform ( Point ( aInput.lowerBound()[0], aInput.upperBound()[1], aInput.upperBound()[2] ) );
        points[4] = transform ( Point ( aInput.upperBound()[0], aInput.lowerBound()[1], aInput.upperBound()[2] ) );
        points[5] = transform ( Point ( aInput.lowerBound()[0], aInput.upperBound()[1], aInput.lowerBound()[2] ) );
        points[6] = transform ( Point ( aInput.lowerBound()[0], aInput.lowerBound()[1], aInput.upperBound()[2] ) );
        points[7] = transform ( Point ( aInput.upperBound()[0], aInput.upperBound()[1], aInput.lowerBound()[2] ) );

        typename Point::Component cmax = std::numeric_limits<typename Point::Component>::max();
        typename Point::Component cmin = std::numeric_limits<typename Point::Component>::min();
        Point t_min ( cmax, cmax, cmax ), t_max ( cmin, cmin, cmin );
        for ( int i = 0; i < 8; i++ )
        {
            if ( points[i][0] < t_min[0] )
                t_min[0] = points[i][0];
            if ( points[i][1] < t_min[1] )
                t_min[1] = points[i][1];
            if ( points[i][2] < t_min[2] )
                t_min[2] = points[i][2];

            if ( points[i][0] > t_max[0] )
                t_max[0] = points[i][0];
            if ( points[i][1] > t_max[1] )
                t_max[1] = points[i][1];
            if ( points[i][2] > t_max[2] )
                t_max[2] = points[i][2];
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
} // namespace DGtal::functors
} // namespace DGtal


#endif // !defined RigidTransformation3D_h

#undef RigidTransformation3D_RECURSES
#endif // else defined(RigidTransformation3D_RECURSES)
