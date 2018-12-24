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
 * @file ModuloComputer.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/02
 *
 * Header file for module ModuloComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ModuloComputer_RECURSES)
#error Recursive header files inclusion detected in ModuloComputer.h
#else // defined(ModuloComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ModuloComputer_RECURSES

#if !defined ModuloComputer_h
/** Prevents repeated inclusion of headers. */
#define ModuloComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/kernel/CInteger.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class ModuloComputer
  /**
   * Description of template class 'ModuloComputer' <p>
   *
   * \brief implements basic functions on modular arithmetic.
   * 
   * @tparam TInteger type of integer.
   *
   * Example:
   *
   *  @code
   *   ...
   *   //Construct an arithmetic modulo 15
   *   // Note that MyInteger must be a model of the concept CInteger
   *   ModuloComputer<MyInteger> modular(15);
   *   typedef MyInteger::UnsignedVersion myUnsignedInteger;
   *
   *   myUnsignedInteger a;
   *
   *   a = modular.cast( 2 );   //a contains the value 2
   *   a = modular.cast( -1 );  //a contains the value 14
   *   modular.increment( a ); //a contains the value 0
   *   ...
   *  @endcode
   */
  template <typename TInteger>
  class ModuloComputer
  {
  public:    
    typedef TInteger Integer;
    typedef typename NumberTraits<Integer>::ParamType IntegerParamType;

    typedef typename NumberTraits<TInteger>::UnsignedVersion UnsignedInteger;
    typedef typename NumberTraits<UnsignedInteger>::ParamType UnsignedIntegerParamType;

    BOOST_CONCEPT_ASSERT((concepts::CInteger<Integer>));
    
    /**
     * Initializes the modulo computer with the value [m].
     * @param m any non-zero integer.
     */
    ModuloComputer( UnsignedIntegerParamType m );
    
    /**
     * Increment the value [i] modulo.
     * @param i any value between 0 and [k] (excluded).
     */
    void increment( UnsignedInteger & i ) const;

    /**
     * Decrement the value [i] modulo.
     * @param i any value between 0 and [k] (excluded).
     */
    void decrement( UnsignedInteger  & i ) const;

    /**
     * @param i any value between 0 and [k] (excluded).
     * @return the incremented value of [i] modulo [k].
     */
    UnsignedInteger next( UnsignedIntegerParamType i ) const;

    /**
     * @param i any value between 0 and [k] (excluded).
     * @return the decremented value of [i] modulo [k].
     */
    UnsignedInteger previous( UnsignedIntegerParamType i ) const;

    /**
     * @param i any integer value.
     * @return the value of [i] modulo [k].
     * NB: O ( i/k ) operation.
     */
    UnsignedInteger cast( IntegerParamType i ) const;
    
    /**
     * Less comparator modulo. Be careful, modulo comparisons have no
     * sense when the absolute difference of the values are around k / 2.
     *
     * @param i any value between 0 and [k] (excluded).
     * @param j any value between 0 and [k] (excluded).
     * @return 'true' if [i] strictly precedes [j] in a window 'floor([k]/2)'.
     */
    bool less( UnsignedIntegerParamType i, UnsignedIntegerParamType j ) const;

    /**
     * Performs j - i modulo, assuming less(i,j) is true.
     *
     * @param j any value between 0 and [k] (excluded).
     * @param i any value between 0 and [k] (excluded).
     * @return the value j - i, always positive. 
     */
    UnsignedInteger posDiff( UnsignedIntegerParamType j, UnsignedIntegerParamType i ) const;
    
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

    // ------------------------- Private Datas --------------------------------
  private:
    /**
     * Modulo of all computations.
     */
    UnsignedInteger k;

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    ModuloComputer();

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    ModuloComputer ( const ModuloComputer & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    ModuloComputer & operator= ( const ModuloComputer & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class ModuloComputer

  /**
     Displays \c object on the output stream \c out.

     @tparam T the type of integer for the modulo computer.
     @param out the output stream
     @param object the object to display.
  */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, 
         const ModuloComputer<T> & object )
  {
    object.selfDisplay( out );
    return out;
  }
  
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/arithmetic/ModuloComputer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ModuloComputer_h

#undef ModuloComputer_RECURSES
#endif // else defined(ModuloComputer_RECURSES)
