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
 * @file OwningOrAliasingPtr.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/11/14
 *
 * Header file for module OwningOrAliasingPtr.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(OwningOrAliasingPtr_RECURSES)
#error Recursive header files inclusion detected in OwningOrAliasingPtr.h
#else // defined(OwningOrAliasingPtr_RECURSES)
/** Prevents recursive inclusion of headers. */
#define OwningOrAliasingPtr_RECURSES

#if !defined OwningOrAliasingPtr_h
/** Prevents repeated inclusion of headers. */
#define OwningOrAliasingPtr_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class OwningOrAliasingPtr
  /**
   * Description of template class 'OwningOrAliasingPtr' <p>
   * \brief Aim:
   * This class describes a smart pointer that is, 
   * given the constructor called by the user, 
   * either an alias pointer on existing data 
   * or an owning pointer on a copy. 
   *
   * Such a pointer may be used for a (big) member of class, 
   * which can be either given at construction (aliasing pointer)
   * or default-constructed (owning pointer).
   * 
   * Such a pointer may be also used to make the user be able to decide 
   * whether the data should be copied (owning pointer) or not (aliasing pointer).  
   *
   * Obviously, the data are free'd at destruction in the case of an owning pointer. 
   *
   * @tparam T a model of boost::CopyConstructible
   */
  template <typename T>
  class OwningOrAliasingPtr
  {

    BOOST_CONCEPT_ASSERT(( boost::CopyConstructible<T> ));
 
    // ----------------------- Inner types       ------------------------------
  public:
    typedef T Value; 
    typedef T* Pointer;
    typedef T& Reference;   

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor with copy. 
     * @param aValue value, @a myPtr owns a copy of which.
     */
    OwningOrAliasingPtr( const T& aValue );

    /**
     * Constructor without copy. 
     * @param aPtr any pointer assigned to @a myPtr
     * @param isOwning 'true' if @a myPtr must be an owning pointer
     * 'false' if @a myPtr must be only an alias (default).
     */
    OwningOrAliasingPtr( Pointer aPtr, bool isOwning = false ); 

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    OwningOrAliasingPtr ( const OwningOrAliasingPtr & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    OwningOrAliasingPtr & operator= ( const OwningOrAliasingPtr & other );

    /**
     * Destructor.
     */
    ~OwningOrAliasingPtr();

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Indirection.
     * @return the pointer.
     */
    Pointer operator->() const;

    /**
     * Access to the underlying pointer.
     * @return the pointer.
     */
    Pointer get() const;

    /**
     * Dereferencement.
     * @return the data.
     */
    Reference operator*() const;

    /**
     * Tells whether the pointer owns the data or not.
     * @return boolean equal to 'true' if @a myPtr owns the data
     * 'false' otherwise.
     */
    bool isOwning() const;

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
  private:
    // ------------------------- Private Datas --------------------------------
  private:

    /**
     * Owning or aliasing pointer to the data
     */
    Pointer myPtr; 
 
    /**
     * Boolean that is equal to 'true' if @a myPtr owns the data
     * 'false' otherwise
     */
    bool myFlagIsOwning; 


    // ------------------------- Hidden services ------------------------------
  protected:


  private:


    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class OwningOrAliasingPtr


  /**
   * Overloads 'operator<<' for displaying objects of class 'OwningOrAliasingPtr'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'OwningOrAliasingPtr' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const OwningOrAliasingPtr<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/base/OwningOrAliasingPtr.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined OwningOrAliasingPtr_h

#undef OwningOrAliasingPtr_RECURSES
#endif // else defined(OwningOrAliasingPtr_RECURSES)
