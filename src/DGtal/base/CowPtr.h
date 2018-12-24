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
 * @file CowPtr.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/08
 *
 * Header file for module CowPtr.cpp
 *
 * Taken from http://ootips.org/yonat/4dev/smart-pointers.html
 *
 * This file is part of the DGtal library.
 */

#if defined(CowPtr_RECURSES)
#error Recursive header files inclusion detected in CowPtr.h
#else // defined(CowPtr_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CowPtr_RECURSES

#if !defined CowPtr_h
/** Prevents repeated inclusion of headers. */
#define CowPtr_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <type_traits>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class CowPtr
  /**
   * Description of template class 'CowPtr' <p> \brief Aim: Copy on
   * write shared pointer.
   *
   * Use reference counting as long as the pointed object is not
   * modified. When it is about to be modified, copy it and modify the
   * copy.
   *
   * Taken from http://ootips.org/yonat/4dev/smart-pointers.html
   */
  template <typename T>
  class CowPtr
  {
    // ----------------------- Standard services ------------------------------
  public:
public:
    typedef T element_type;

    explicit CowPtr(T* p = 0) noexcept           : myPtr(p) {}
    // no need for ~CowPtr - the CountedPtr takes care of everything.
    CowPtr(const CowPtr& r) noexcept             : myPtr(r.myPtr) {}
    /**
     * @todo JOL: check this.
     */
    CowPtr(const CountedPtr<T> & r)    : myPtr( r ) {}
    CowPtr& operator=(const CowPtr& r)
    {
        if (this != &r)
            myPtr = r.myPtr;
        return *this;
    }


    const T& operator*()    const noexcept   {return *myPtr;}
    const T* operator->()   const noexcept   {return myPtr.get();}
    const T* get()          const noexcept   {return myPtr.get();}

    /* The following non-const methods are deactivated if T is a const type.
     * The goal here is to avoid unecessary copies when it is known that
     *   the T object will not be modified.
     *
     * The problem is that C++ uses the non-const methods whenever it's possible
     *   (ie when CowPtr<T> is non-const), even if the full expression doesn't 
     *   modify the object. A solution is to const_cast the CowPtr<T> before
     *   using one of these methods to force the usage of the const versions above.
     *
     * However, in the trivial case when T is a const type, we can simplify this
     *   by deactivating those methods.
     *
     * To do that, we use std::enable_if (see http://en.cppreference.com/w/cpp/types/enable_if )
     *   in the template parameters (it is also possible in the return type or
     *   as a parameter but it will change the signature). It depends on
     *   the constness of T returned by the type trait std::is_const.
     * The `typename U = T` is necessary in order that the SFINAE rule works at the overload
     * resolution step.
     */
    template < typename U = T, typename std::enable_if< ! std::is_const<U>::value >::type* = nullptr >
    T& operator*()                          {copy(); return *myPtr;}

    template < typename U = T, typename std::enable_if< ! std::is_const<U>::value >::type* = nullptr >
    T* operator->()                         {copy(); return myPtr.get();}

    template < typename U = T, typename std::enable_if< ! std::is_const<U>::value >::type* = nullptr >
    T* get()                                {copy(); return myPtr.get();}

    /**
       Equality operator ==

       @param other any other pointer.
       @return 'true' if pointed address is equal to \a other.
    */
    bool operator==( const T* other ) const
    {
      return get() == other;
    }

    /**
       Inequality operator !=

       @param other any other pointer.
       @return 'true' if pointed address is different from \a other.
    */
    bool operator!=( const T* other ) const
    {
      return get() != other;
    }


    /**
     * For debug.
     */
    unsigned int count() const          { return myPtr.count(); }
    inline T* drop() { return myPtr.drop(); }
    inline bool unique() const noexcept { return myPtr.unique(); }

  private:

    // ------------------------- Private Datas --------------------------------
  private:

    CountedPtr<T> myPtr;

    // ------------------------- Internals ------------------------------------
  private:
    void copy()                            // create a new copy of myPtr
    {
        if (!myPtr.unique()) {
            T* old_p = myPtr.get();
            myPtr = CountedPtr<T>(new T(*old_p));
        }
    }


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
  private:

    // ------------------------- Hidden services ------------------------------
  protected:



  }; // end of class CowPtr


  /**
   * Overloads 'operator<<' for displaying objects of class 'CowPtr'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'CowPtr' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const CowPtr<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/base/CowPtr.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CowPtr_h

#undef CowPtr_RECURSES
#endif // else defined(CowPtr_RECURSES)
