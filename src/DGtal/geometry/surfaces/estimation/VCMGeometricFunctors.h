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
 * @file VCMGeometricFunctors.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2014/02/14
 *
 * Header file for module VCMGeometricFunctors.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(VCMGeometricFunctors_RECURSES)
#error Recursive header files inclusion detected in VCMGeometricFunctors.h
#else // defined(VCMGeometricFunctors_RECURSES)
/** Prevents recursive inclusion of headers. */
#define VCMGeometricFunctors_RECURSES

#if !defined VCMGeometricFunctors_h
/** Prevents repeated inclusion of headers. */
#define VCMGeometricFunctors_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::functors
namespace DGtal {
  namespace functors {

    /**
     * Description of template class 'VCMNormalVectorFunctor' <p> 
     * \brief Aim: A functor Surfel -> Quantity that returns the outer normal
     * vector at given surfel.
     *
     * @tparam TVCMOnDigitalSurface any concrete type of VoronoiCovarianceMeasureOnDigitalSurface
     */
    template <typename TVCMOnDigitalSurface>
    struct VCMNormalVectorFunctor {
      typedef TVCMOnDigitalSurface VCMOnDigitalSurface;
      typedef typename VCMOnDigitalSurface::KSpace KSpace;
      typedef typename VCMOnDigitalSurface::Surfel Surfel;
      typedef typename VCMOnDigitalSurface::VectorN RealVector;
      typedef typename RealVector::Component Scalar;
      typedef Surfel Argument;
      typedef RealVector Quantity;
      
      /**
       * Constructor. A VCM may also be attached at construction.
       *
       * @param aVCMOnDigitalSurface the VCM on surface that stores all the
       * information. The alias can be secured if some counted
       * pointer is handed.
       */
      VCMNormalVectorFunctor( ConstAlias<VCMOnDigitalSurface> aVCMOnDigitalSurface = 0 ) 
        : myVCMOnDigitalSurface( aVCMOnDigitalSurface ) {}
      
      /**
       * Attach a VCM on a digital surface.
       *
       * @param aVCMOnDigitalSurface on surface that stores all the
       * information. The alias can be secured if some counted
       * pointer is handed.
       */
      void attach( ConstAlias<VCMOnDigitalSurface> aVCMOnDigitalSurface )
      {
        myVCMOnDigitalSurface = aVCMOnDigitalSurface;
      }

      /**
         Map operator Surfel -> RealVector giving the normal vector estimated by the VCM object.
         Complexity is \f$ O(log n) \f$, if \a n is the number of surfels of the surface.

         @param s any surfel of the shape.
         @return the normal at point p (as the normalized gradient).
      */
      Quantity operator()( const Surfel & s ) const
      {
        typedef typename VCMOnDigitalSurface::Surfel2Normals Surfel2Normals;
        ASSERT( myVCMOnDigitalSurface != 0 );
        typename Surfel2Normals::const_iterator itSN = myVCMOnDigitalSurface->mapSurfel2Normals().find( s );
        ASSERT( itSN != myVCMOnDigitalSurface->mapSurfel2Normals().end() );
        return - itSN->second.vcmNormal;
      }

    private:
      /// The shape of interest.
      CountedConstPtrOrConstPtr<VCMOnDigitalSurface> myVCMOnDigitalSurface;
    };
    

   /**
     * Description of template class 'VCMAbsoluteCurvatureFunctor' <p> 
     * \brief Aim: A functor Surfel -> Quantity that returns the absolute curvature at
     * given surfel. This class has meaning only in 2D.
     *
     * @tparam TVCMOnDigitalSurface any concrete type of VoronoiCovarianceMeasureOnDigitalSurface
     */
    template <typename TVCMOnDigitalSurface>
    struct VCMAbsoluteCurvatureFunctor {
      typedef TVCMOnDigitalSurface VCMOnDigitalSurface;
      typedef typename VCMOnDigitalSurface::KSpace KSpace;
      typedef typename VCMOnDigitalSurface::Surfel Surfel;
      typedef typename VCMOnDigitalSurface::VectorN RealVector;
      typedef typename RealVector::Component Scalar;
      typedef Surfel Argument;
      typedef Scalar Quantity;
      
      /**
       * Constructor. A VCM may also be attached at construction.
       *
       * @param aVCMOnDigitalSurface the VCM on surface that stores all the
       * information. The alias can be secured if some counted
       * pointer is handed.
       */
      VCMAbsoluteCurvatureFunctor( ConstAlias<VCMOnDigitalSurface> aVCMOnDigitalSurface = 0 ) 
        : myVCMOnDigitalSurface( aVCMOnDigitalSurface ) 
      {
        BOOST_STATIC_ASSERT(( KSpace::dimension == 2 ));
      }
      
      /**
       * Attach a VCM on a digital surface.
       *
       * @param aVCMOnDigitalSurface on surface that stores all the
       * information. The alias can be secured if some counted
       * pointer is handed.
       */
      void attach( ConstAlias<VCMOnDigitalSurface> aVCMOnDigitalSurface )
      {
        myVCMOnDigitalSurface = aVCMOnDigitalSurface;
      }

      /**
         Map operator Surfel -> Scalar giving the absolute curvature estimated by the VCM object.
         Complexity is \f$ O(log n) \f$, if \a n is the number of surfels of the surface.

         @param s any surfel of the shape.
         @return the normal at point p (as the normalized gradient).
      */
      Quantity operator()( const Surfel & s ) const
      {
        ASSERT( myVCMOnDigitalSurface != 0 );
        RealVector lambda;
        bool ok = myVCMOnDigitalSurface->getChiVCMEigenvalues( lambda, s );
        ASSERT( ok ); boost::ignore_unused_variable_warning( ok );

        // The last eigenvalue l1 is approximately the mixed "area" 8pi R^3 r / 3
        // The curvature is related to the first eigenvalue l0.
        // k1^2 = 3*l0 / (l1*r^2)
        return sqrt( 3.0 * lambda[0] / lambda[1] ) / myVCMOnDigitalSurface->r();
      }

    private:
      /// The shape of interest.
      CountedConstPtrOrConstPtr<VCMOnDigitalSurface> myVCMOnDigitalSurface;
    };

   /**
     * Description of template class
     * 'VCMFirstPrincipalAbsoluteCurvatureFunctor' <p> 
     * \brief Aim: A functor Surfel -> Quantity that returns the first principal absolute curvature
     * (greatest curvature) at given surfel. This class has meaning
     * only in 3D.
     *
     * @tparam TVCMOnDigitalSurface any concrete type of VoronoiCovarianceMeasureOnDigitalSurface
     */
    template <typename TVCMOnDigitalSurface>
    struct VCMFirstPrincipalAbsoluteCurvatureFunctor {
      typedef TVCMOnDigitalSurface VCMOnDigitalSurface;
      typedef typename VCMOnDigitalSurface::KSpace KSpace;
      typedef typename VCMOnDigitalSurface::Surfel Surfel;
      typedef typename VCMOnDigitalSurface::VectorN RealVector;
      typedef typename RealVector::Component Scalar;
      typedef Surfel Argument;
      typedef Scalar Quantity;
      
      /**
       * Constructor. A VCM may also be attached at construction.
       *
       * @param aVCMOnDigitalSurface the VCM on surface that stores all the
       * information. The alias can be secured if some counted
       * pointer is handed.
       */
      VCMFirstPrincipalAbsoluteCurvatureFunctor( ConstAlias<VCMOnDigitalSurface> aVCMOnDigitalSurface = 0 ) 
        : myVCMOnDigitalSurface( aVCMOnDigitalSurface ) 
      {
        BOOST_STATIC_ASSERT(( KSpace::dimension == 3 ));
      }
      
      /**
       * Attach a VCM on a digital surface.
       *
       * @param aVCMOnDigitalSurface on surface that stores all the
       * information. The alias can be secured if some counted
       * pointer is handed.
       */
      void attach( ConstAlias<VCMOnDigitalSurface> aVCMOnDigitalSurface )
      {
        myVCMOnDigitalSurface = aVCMOnDigitalSurface;
      }

      /**
         Map operator Surfel -> Scalar giving the first principal absolute curvature estimated by the VCM object.
         Complexity is \f$ O(log n) \f$, if \a n is the number of surfels of the surface.

         @param s any surfel of the shape.
         @return the normal at point p (as the normalized gradient).
      */
      Quantity operator()( const Surfel & s ) const
      {
        ASSERT( myVCMOnDigitalSurface != 0 );
        RealVector lambda;
        bool ok = myVCMOnDigitalSurface->getChiVCMEigenvalues( lambda, s );
        ASSERT( ok ); boost::ignore_unused_variable_warning( ok );
        
        // The last eigenvalue l2 is approximately the mixed "area" 2pi R^3 r^2 / 3
        // The greatest principal curvature is related to the second eigenvalue l1.
        // k1^2 = 4*l1 / (l2*r^2)
        return 2.0 * sqrt( lambda[1] / lambda[2] ) / myVCMOnDigitalSurface->r();
      }

    private:
      /// The shape of interest.
      CountedConstPtrOrConstPtr<VCMOnDigitalSurface> myVCMOnDigitalSurface;
    };

   /**
     * Description of template class
     * 'VCMSecondPrincipalAbsoluteCurvatureFunctor' <p> 
     * \brief Aim: A functor Surfel -> Quantity that returns the second principal absolute curvature
     * (smallest curvature) at given surfel. This class has meaning
     * only in 3D.
     *
     * @tparam TVCMOnDigitalSurface any concrete type of VoronoiCovarianceMeasureOnDigitalSurface
     */
    template <typename TVCMOnDigitalSurface>
    struct VCMSecondPrincipalAbsoluteCurvatureFunctor {
      typedef TVCMOnDigitalSurface VCMOnDigitalSurface;
      typedef typename VCMOnDigitalSurface::KSpace KSpace;
      typedef typename VCMOnDigitalSurface::Surfel Surfel;
      typedef typename VCMOnDigitalSurface::VectorN RealVector;
      typedef typename RealVector::Component Scalar;
      typedef Surfel Argument;
      typedef Scalar Quantity;
      
      /**
       * Constructor. A VCM may also be attached at construction.
       *
       * @param aVCMOnDigitalSurface the VCM on surface that stores all the
       * information. The alias can be secured if some counted
       * pointer is handed.
       */
      VCMSecondPrincipalAbsoluteCurvatureFunctor( ConstAlias<VCMOnDigitalSurface> aVCMOnDigitalSurface = 0 ) 
        : myVCMOnDigitalSurface( aVCMOnDigitalSurface ) 
      {
        BOOST_STATIC_ASSERT(( KSpace::dimension == 3 ));
      }
      
      /**
       * Attach a VCM on a digital surface.
       *
       * @param aVCMOnDigitalSurface on surface that stores all the
       * information. The alias can be secured if some counted
       * pointer is handed.
       */
      void attach( ConstAlias<VCMOnDigitalSurface> aVCMOnDigitalSurface )
      {
        myVCMOnDigitalSurface = aVCMOnDigitalSurface;
      }

      /**
         Map operator Surfel -> Scalar giving the second principal absolute curvature estimated by the VCM object.
         Complexity is \f$ O(log n) \f$, if \a n is the number of surfels of the surface.

         @param s any surfel of the shape.
         @return the normal at point p (as the normalized gradient).
      */
      Quantity operator()( const Surfel & s ) const
      {
        ASSERT( myVCMOnDigitalSurface != 0 );
        RealVector lambda;
        bool ok = myVCMOnDigitalSurface->getChiVCMEigenvalues( lambda, s );
        ASSERT( ok ); boost::ignore_unused_variable_warning( ok );
        
        // The last eigenvalue l2 is approximately the mixed "area" 2pi R^3 r^2 / 3
        // The smallest principal curvature is related to the first eigenvalue l0.
        // k2^2 = 4*l0 / (l2*r^2)
        return 2.0 * sqrt( lambda[0] / lambda[2] ) / myVCMOnDigitalSurface->r();
      }

    private:
      /// The shape of interest.
      CountedConstPtrOrConstPtr<VCMOnDigitalSurface> myVCMOnDigitalSurface;
    };


   /**
     * Description of template class 'VCMMeanAbsoluteCurvatures3DFunctor' <p> 
     * \brief Aim: A functor Surfel -> Quantity that returns the mean of absolute curvatures at
     * given surfel: (abs(k1)+abs(k2))/2. This class has meaning only in 3D.
     *
     * @tparam TVCMOnDigitalSurface any concrete type of VoronoiCovarianceMeasureOnDigitalSurface
     */
    template <typename TVCMOnDigitalSurface>
    struct VCMMeanAbsoluteCurvatures3DFunctor {
      typedef TVCMOnDigitalSurface VCMOnDigitalSurface;
      typedef typename VCMOnDigitalSurface::KSpace KSpace;
      typedef typename VCMOnDigitalSurface::Surfel Surfel;
      typedef typename VCMOnDigitalSurface::VectorN RealVector;
      typedef typename RealVector::Component Scalar;
      typedef Surfel Argument;
      typedef Scalar Quantity;
      
      /**
       * Constructor. A VCM may also be attached at construction.
       *
       * @param aVCMOnDigitalSurface the VCM on surface that stores all the
       * information. The alias can be secured if some counted
       * pointer is handed.
       */
      VCMMeanAbsoluteCurvatures3DFunctor( ConstAlias<VCMOnDigitalSurface> aVCMOnDigitalSurface = 0 ) 
        : myVCMOnDigitalSurface( aVCMOnDigitalSurface ) 
      {
        BOOST_STATIC_ASSERT(( KSpace::dimension == 3 ));
      }
      
      /**
       * Attach a VCM on a digital surface.
       *
       * @param aVCMOnDigitalSurface on surface that stores all the
       * information. The alias can be secured if some counted
       * pointer is handed.
       */
      void attach( ConstAlias<VCMOnDigitalSurface> aVCMOnDigitalSurface )
      {
        myVCMOnDigitalSurface = aVCMOnDigitalSurface;
      }

      /**
         Map operator Surfel -> Scalar giving the mean of absolute curvatures estimated by the VCM object.
         Complexity is \f$ O(log n) \f$, if \a n is the number of surfels of the surface.

         @param s any surfel of the shape.
         @return the normal at point p (as the normalized gradient).
      */
      Quantity operator()( const Surfel & s ) const
      {
        ASSERT( myVCMOnDigitalSurface != 0 );
        RealVector lambda;
        bool ok = myVCMOnDigitalSurface->getChiVCMEigenvalues( lambda, s );
        ASSERT( ok ); boost::ignore_unused_variable_warning( ok );

        // The last eigenvalue l2 is approximately the mixed "area" 2pi R^3 r^2 / 3
        // The greatest principal curvature is related to the second eigenvalue l1.
        // k1^2 = 4*l1 / (l2*r^2)
        Quantity k1 = 2.0 * sqrt( lambda[1] / lambda[2] ) / myVCMOnDigitalSurface->r();

       // The last eigenvalue l2 is approximately the mixed "area" 2pi R^3 r^2 / 3
        // The smallest principal curvature is related to the first eigenvalue l0.
        // k2^2 = 4*l0 / (l2*r^2)
        Quantity k2 = 2.0 * sqrt( lambda[0] / lambda[2] ) / myVCMOnDigitalSurface->r();
        return (k1+k2) * 0.5;
      }

    private:
      /// The shape of interest.
      CountedConstPtrOrConstPtr<VCMOnDigitalSurface> myVCMOnDigitalSurface;
    };

  } //namespace functors
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined VCMGeometricFunctors_h

#undef VCMGeometricFunctors_RECURSES
#endif // else defined(VCMGeometricFunctors_RECURSES)
