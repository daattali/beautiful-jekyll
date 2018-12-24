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
 * @file ImplicitFunctionDiff1LinearCellEmbedder.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2012/02/14
 *
 * Header file for module ImplicitFunctionDiff1LinearCellEmbedder.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImplicitFunctionDiff1LinearCellEmbedder_RECURSES)
#error Recursive header files inclusion detected in ImplicitFunctionDiff1LinearCellEmbedder.h
#else // defined(ImplicitFunctionDiff1LinearCellEmbedder_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImplicitFunctionDiff1LinearCellEmbedder_RECURSES

#if !defined ImplicitFunctionDiff1LinearCellEmbedder_h
/** Prevents repeated inclusion of headers. */
#define ImplicitFunctionDiff1LinearCellEmbedder_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/kernel/CPointEmbedder.h"
#include "DGtal/topology/CCellularGridSpaceND.h"
#include "DGtal/shapes/implicit/CImplicitFunction.h"
#include "DGtal/shapes/implicit/CImplicitFunctionDiff1.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /// Forward declaration.
  template < typename TKSpace,
             typename TImplicitFunctionDiff1,
             typename TEmbedder >
  class ImplicitFunctionDiff1LinearCellEmbedderGradientMap;

  /////////////////////////////////////////////////////////////////////////////
  /**
    Description of template class 'ImplicitFunctionDiff1LinearCellEmbedder' <p>
    \brief Aim: a cellular embedder for implicit functions,
    (default constructible, copy constructible, assignable). 
    Model of CCellEmbedder and CWithGradientMap.
   
    @tparam TKSpace the cellular grid space definition, a model of CCellularGridSpaceND.
    @tparam TImplicitFunctionDiff1 the type of implicit function, a model of CImplicitFunctionDiff1.
    @tparam TEmbedder the type of digital embedder, a model of CPointEmbedder.

    @todo assert dimensions of space, embedder and implicit function.
   */
  
  template < typename TKSpace,
             typename TImplicitFunctionDiff1,
             typename TEmbedder >
  class ImplicitFunctionDiff1LinearCellEmbedder
  {
    BOOST_CONCEPT_ASSERT(( concepts::CCellularGridSpaceND< TKSpace > ));
    BOOST_CONCEPT_ASSERT(( concepts::CImplicitFunctionDiff1< TImplicitFunctionDiff1 > ));
    BOOST_CONCEPT_ASSERT(( concepts::CPointEmbedder< TEmbedder > ));

  public:
    typedef TKSpace KSpace;
    typedef TImplicitFunctionDiff1 ImplicitFunctionDiff1;
    typedef TEmbedder Embedder;
    typedef typename KSpace::Cell Cell;
    typedef typename KSpace::SCell SCell;
    typedef typename KSpace::Space Space;
    typedef typename Space::Point Point;
    typedef typename Space::RealPoint RealPoint;
    typedef typename Space::RealVector RealVector;
    typedef typename ImplicitFunctionDiff1::Value ImplicitFctValue;
    typedef Cell Argument;
    typedef RealPoint Value;
    typedef ImplicitFunctionDiff1LinearCellEmbedderGradientMap
    < KSpace, ImplicitFunctionDiff1, Embedder > GradientMap;
    
    /** 
        Constructor. The object is not valid.
     */
    ImplicitFunctionDiff1LinearCellEmbedder();
    
    /** 
     * Destructor.
     */    
    ~ImplicitFunctionDiff1LinearCellEmbedder();

    /**
       Copy constructor.
       @param other the object to copy.
     */
    ImplicitFunctionDiff1LinearCellEmbedder( const ImplicitFunctionDiff1LinearCellEmbedder & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    ImplicitFunctionDiff1LinearCellEmbedder & 
    operator= ( const ImplicitFunctionDiff1LinearCellEmbedder & other );

    /**
       Initializes the embedder with the space \a K, the implicit
       function \a f, the digital embedder \a e.
       
       @param K any cellular grid space.
       @param f an implicit function
       @param e a digital embedder (like a GaussDigitizer).
    */
    void init( ConstAlias<KSpace> K, ConstAlias<ImplicitFunctionDiff1> f, 
               ConstAlias<Embedder> e );

    // ----------------------- Interface --------------------------------------
  public:

    /**
       @return the corresponding gradient map. 
    */
    GradientMap gradientMap() const;

    /**
       Maps a digital point to its corresponding point in the Euclidean
       space.
       
       @param p any digital point in the digital space.
       @return its embedding by the current embedder in the Euclidean space.
     */
    RealPoint embed( const Point & p ) const;

    /**
       Maps a cell to its corresponding point in the Euclidean
       space, by a linear guess of its position.
       
       @param cell any cell in the cellular grid space.
       @return its embedding in the Euclidean space.
     */
    RealPoint embedCell( const Cell & cell ) const;

    /**
       Maps a signed cell to its corresponding point in the Euclidean
       space, by a linear guess of its position. NB: the signed is not
       used.
       
       @param scell any cell in the cellular grid space.
       @return its embedding in the Euclidean space.
     */
    RealPoint embedSCell( const SCell & scell ) const;

    /**
       Maps a cell to its corresponding point in the Euclidean
       space, by a linear guess of its position.
       
       @param cell any cell in the cellular grid space.
       @return its embedding in the Euclidean space.
     */
    RealPoint operator()( const Cell & cell ) const;

    /**
       Maps a digital point to its corresponding embedding position
       and gradient vector in the Euclidean space.
       
       @param p any digital point in the digital space.
       @param x its embedding in the Euclidean space.
       @param grad (returns) its gradient vector at the point given by
       the current embedder in the Euclidean space.
     */
    void embed( const Point & p, RealPoint & x, RealVector & grad ) const;

    /**
       Maps a cell to its corresponding gradient vector in the
       Euclidean space, by a linear guess of its position.
       
       @param cell any cell in the cellular grid space.
       @param x its embedding in the Euclidean space.
       @param grad (returns) its gradient vector at the point given by
       the current embedder in the Euclidean space.
     */
    void embedCell( const Cell & cell, 
                    RealPoint & x, RealVector & grad ) const;

    /**
       Maps a signed cell to its corresponding gradient vector in the
       Euclidean space, by a linear guess of its position. NB: the
       signed is not used.
       
       @param scell any cell in the cellular grid space.
       @param x its embedding in the Euclidean space.
       @param grad (returns) its gradient vector at the point given by
       the current embedder in the Euclidean space.
     */
    void embedSCell( const SCell & scell, 
                     RealPoint & x, RealVector & grad ) const;
    
    // ----------------------- Interface --------------------------------------
  public:
    
    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------------- Protected Datas ------------------------------
  protected:
   
    /// A pointer on the cellular grid space.
    const KSpace* myPtrK;
    /// A pointer on the implicit function.
    const ImplicitFunctionDiff1* myPtrFct;
    /// A pointer on the digital embedder.
    const Embedder* myPtrEmbedder;
   
  }; // end of class ImplicitFunctionDiff1LinearCellEmbedder

  /**
     GradientMap class for ImplicitFunctionDiff1LinearCellEmbedder.
     A model of CUnaryFunctor<T, T::Point, T::RealVector>.
  */
  template < typename TKSpace,
             typename TImplicitFunctionDiff1,
             typename TEmbedder >
  class ImplicitFunctionDiff1LinearCellEmbedderGradientMap
    : public ImplicitFunctionDiff1LinearCellEmbedder< TKSpace, 
                                                      TImplicitFunctionDiff1,
                                                      TEmbedder>
  {
  public:
    typedef ImplicitFunctionDiff1LinearCellEmbedderGradientMap
    < TKSpace, TImplicitFunctionDiff1, TEmbedder> Self;
    typedef ImplicitFunctionDiff1LinearCellEmbedder
    < TKSpace, TImplicitFunctionDiff1, TEmbedder> Base;
    typedef typename Base::Cell Cell;
    typedef typename Base::RealPoint RealPoint;
    typedef typename Base::RealVector RealVector;
    typedef Cell Argument;
    typedef RealVector Value;
    using Base::myPtrFct;

    inline
    ImplicitFunctionDiff1LinearCellEmbedderGradientMap
    ( const Base & other )
      : Base( other )
    {}

    inline
    Self & operator=( const Base & other )
    {
      Base::operator=( other );
      return *this;
    }

    inline
    Value operator()( const Argument & arg ) const
    {
      RealPoint x = Base::operator()( arg );
      return myPtrFct->gradient( x );
    }
  };

  /**
   * Overloads 'operator<<' for displaying objects of class 'ImplicitFunctionDiff1LinearCellEmbedder'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ImplicitFunctionDiff1LinearCellEmbedder' to write.
   * @return the output stream after the writing.
   */
  template < typename TKSpace, typename TImplicitFunctionDiff1, typename TEmbedder >
  std::ostream&
  operator<< ( std::ostream & out, 
               const ImplicitFunctionDiff1LinearCellEmbedder<TKSpace, TImplicitFunctionDiff1, TEmbedder> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/implicit/ImplicitFunctionDiff1LinearCellEmbedder.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImplicitFunctionDiff1LinearCellEmbedder_h

#undef ImplicitFunctionDiff1LinearCellEmbedder_RECURSES
#endif // else defined(ImplicitFunctionDiff1LinearCellEmbedder_RECURSES)
