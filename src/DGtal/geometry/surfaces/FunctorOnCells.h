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
 * @file FunctorOnCells.h
 * @brief Convert a functor on Digital Point to a Functor on Khalimsky Cell
 *
 * @author Jeremy Levallois (\c jeremy.levallois@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), INSA-Lyon, France
 * LAboratoire de MAthématiques - LAMA (CNRS, UMR 5127), Université de Savoie, France
 *
 * @date 2012/05/11
 *
 * Header file for module FunctorOnCells.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(FunctorOnCells_RECURSES)
#error Recursive header files inclusion detected in FunctorOnCells.h
#else // defined(FunctorOnCells_RECURSES)
/** Prevents recursive inclusion of headers. */
#define FunctorOnCells_RECURSES

#if !defined FunctorOnCells_h
/** Prevents repeated inclusion of headers. */
#define FunctorOnCells_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/Alias.h"
#include "DGtal/base/ConstAlias.h"

#include "DGtal/kernel/CSpace.h"
#include "DGtal/kernel/CPointFunctor.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class FunctorOnCells
  /**
   * Description of template class 'FunctorOnCells' <p>
   *
   * \brief Aim: Convert a functor on Digital Point to a Functor on Khalimsky Cell
   *
   * @tparam TFunctorOnPoints a model of functor on Digital Points.
   * @tparam TKSpace Khalimsky space in which the shape is defined.
   */
  template <typename TFunctorOnPoints, typename TKSpace>
  class FunctorOnCells
  {
    // ----------------------- Standard services ------------------------------
  public:

    typedef FunctorOnCells<TFunctorOnPoints, TKSpace> Self;
    typedef TFunctorOnPoints FunctorOnPoints;
    typedef TKSpace KSpace;
    typedef int Quantity;
    typedef typename FunctorOnPoints::Point Point;
    typedef typename FunctorOnPoints::Value Value;
    typedef typename KSpace::SCell Cell;

    BOOST_CONCEPT_ASSERT(( concepts::CPointFunctor< FunctorOnPoints > ));
    //BOOST_CONCEPT_ASSERT(( CSpace< KSpace > ));

    /**
      * Constructor.
      *
      * @param[in] functor a functor on digital points.
      * @param[in] kspace Khalimsky space in which the shape is defined.
      */
    FunctorOnCells (  Alias< FunctorOnPoints > functor, ConstAlias< KSpace > kspace )
      : f(&functor),
        myKSpace(&kspace)
    {}

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    FunctorOnCells ( const FunctorOnCells & other )
      : f( other.f ), myKSpace( other.myKSpace )
    {}

    /**
     * Destructor.
     */
    ~FunctorOnCells();


    // ----------------------- Interface --------------------------------------
  public:
    /**
     * Call the functor on Point by converting the Cell to a Point.
     *
     * @param[in] aCell any cell in the Khalimsky space.
     *
     * @return 'ONE' if the point is inside the shape, 'ZERO' if it is strictly outside.
     */
    Quantity operator()( const Cell & aCell ) const
    {
      return ( f->operator()( myKSpace->sCoords(aCell) ) == NumberTraits< Value >::ZERO ) ? NumberTraits<Quantity>::ZERO : NumberTraits<Quantity>::ONE;
    }

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

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    FunctorOnCells & operator= ( const FunctorOnCells & other )
    {
      if( this != &other )
        {
          f = other.f;
          myKSpace = other.myKSpace;
        }
      return *this;
    }

    /**
    * @return the cellular grid space in which cells are defined.
    */
    const KSpace& space() const
    {
      return *myKSpace;
    }

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    /// Const pointor on Functor on Points. Used on operator() to get the return value
    FunctorOnPoints * f;

    /// Const pointor on Khalimsky Space. Used to convert Cell -> Point
    const KSpace * myKSpace;

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    FunctorOnCells();

  private:

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class FunctorOnCells


  /**
   * Overloads 'operator<<' for displaying objects of class 'FunctorOnCells'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'FunctorOnCells' to write.
   * @return the output stream after the writing.
   */
  template <typename TF, typename TKS>
  std::ostream&
  operator<< ( std::ostream & out, const FunctorOnCells<TF, TKS> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/surfaces/FunctorOnCells.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined FunctorOnCells_h

#undef FunctorOnCells_RECURSES
#endif // else defined(FunctorOnCells_RECURSES)
