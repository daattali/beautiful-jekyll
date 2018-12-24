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
 * @file CountedConstPtrOrConstPtr.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2013/11/06
 *
 * Header file for module CountedConstPtrOrConstPtr.cpp
 *
 * Taken from http://ootips.org/yonat/4dev/smart-pointers.html
 *
 * This file is part of the DGtal library.
 */

#if defined(CountedConstPtrOrConstPtr_RECURSES)
#error Recursive header files inclusion detected in CountedConstPtrOrConstPtr.h
#else // defined(CountedConstPtrOrConstPtr_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CountedConstPtrOrConstPtr_RECURSES

#if !defined CountedConstPtrOrConstPtr_h
/** Prevents repeated inclusion of headers. */
#define CountedConstPtrOrConstPtr_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/base/CountedPtrOrPtr.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class CountedConstPtrOrConstPtr
  /**
   * Description of template class 'CountedConstPtrOrConstPtr' <p>
   * \brief Aim: Smart or simple const pointer on \c T.  It can be a
   * smart pointer based on reference counts or a simple pointer on \a
   * T depending either on a boolean value given at construction or on
   * the constructor used. In the first case, we will call this
   * pointer object \b smart, otherwise we will call it \b simple.
   *
   * This object is useful when instantiating from a ConstAlias<T>
   * object, letting the user specifies if it uses smart pointers or
   * simply pointers. This class should be used as a meta-type for
   * data members, when the programmer wants to hold a const-reference
   * to some object during some period, but also wants to let the user
   * decides whether the class should keep a smart reference or
   * non-smart reference to the object. How and where to use such
   * smart pointers is explained in \ref
   * moduleCloneAndReference_sec24.
   *
   * \code
   * struct B {};
   * struct A {
   *   CountedConstPtrOrConstPtr<B> myPtrB;
   *   A( ConstAlias<B> someB ) : myPtrB( B ) {}
   * };
   * int main() {
   *   B b1;
   *   A a1( b1 ); // a1.myPtrB points to b1, classic pointer
   *   B* b2 = new B;
   *   A a2( b2 ); // a2.myPtrB acquires b2 (and will take care of freeing it)
   *   CountedPtr<B> b3 = CountedPtr<B>( new B ); // smart pointer
   *   A a3( b3 ); // a3.myPtrB smart points to b3.
   * \endcode
   *
   * @tparam T any data type.
   * @see CountedPtr
   * @see ConstAlias
   */
  template <typename T>
  class CountedConstPtrOrConstPtr
  {
  public:

    // ----------------------- Standard services ------------------------------
  public:

    /// The counter is the same as CountedPtr.
    typedef typename CountedPtr<T>::Counter Counter;

    /**
     * Default Constructor and constructor from pointer. The created
     * object is either a \b simple const pointer on \a p (not acquired) if
     * \a isCountedPtr is \c false, or a \b smart const pointer based on
     * reference counts (CountedPtr).
     *
     * @param p is a pointer to some object T. If \a isCountedPtr is
     * \c true, then pointer \a p should point to some dynamically
     * allocated object T, and the pointer is acquired. If \a
     * isCountedPtr is \c false, then this object holds only the
     * pointer \a p, without acquiring it.
     *
     * @param isCountedPtr when 'true', stores \a p as a smart
     * (counted) pointer, otherwise stores \a p directly.
     */
    inline explicit CountedConstPtrOrConstPtr( const T* p = 0, bool isCountedPtr = true )
      : myAny(0), myIsCountedPtr( isCountedPtr )
    { 
      if ( isCountedPtr ) {
	if (p) myAny = static_cast<void*>( new Counter( const_cast<T*>( p ) ) );
      }
      else
	myAny = const_cast<void*>( static_cast<const void*>( p ) );
    }

    /**
     * Destructor. If this pointer object was \b smart, the pointed
     * object is released (and possibly freed if the reference count
     * was 1), otherwise, if this pointer object was \b simple, the
     * destructor does nothing.
     */ 
    ~CountedConstPtrOrConstPtr()
    {
      if ( myIsCountedPtr ) release(); 
    }

    /**
     * Constructor from smart pointer (CountedPtr) \a r. In this case,
     * this pointer object is \b smart and acquire the given smart
     * pointer.
     *
     * @param r the smart pointer to acquire.
     */
    CountedConstPtrOrConstPtr( const CountedPtr<T> & r ) noexcept
      : myIsCountedPtr( true )
    { 
      acquire( r.myCounter ); 
    }

    /**
     * Copy constructor. If \a r is \b smart, then this pointer
     * object is also \b smart and acquires \a r (no
     * duplication). Otherwise, if \a r is \b simple, then this
     * pointer object only points at the same place.
     *
     * @param r the other pointer to clone, which may be \b smart or
     * \b simple.
     */
    CountedConstPtrOrConstPtr(const CountedConstPtrOrConstPtr& r) noexcept
      : myIsCountedPtr( r.myIsCountedPtr )
    { 
      if ( myIsCountedPtr )
	acquire( r.counterPtr() ); 
      else
	myAny = r.myAny;
    }

    /**
     * Constructor from CountedPtrOrPtr. If \a r is \b smart, then this pointer
     * object is also \b smart and acquires \a r (no
     * duplication). Otherwise, if \a r is \b simple, then this
     * pointer object only points at the same place.
     *
     * @param r the other pointer to clone, which may be \b smart or
     * \b simple.
     */
    CountedConstPtrOrConstPtr(const CountedPtrOrPtr<T>& r) noexcept
      : myIsCountedPtr( r.myIsCountedPtr )
    { 
      if ( myIsCountedPtr )
	acquire( r.counterPtr() ); 
      else
	myAny = r.myAny;
    }

    /**
     * Assignment. If 'this' was \b smart, then the shared pointer is
     * released. Then, if \a r is \b smart, then this pointer object
     * is also \b smart and acquires \a r (no duplication). Otherwise,
     * if \a r is \b simple, then this pointer object only points at
     * the same place.
     *
     * @param r the other pointer to clone, which may be \b smart or
     * \b simple.
     *
     * @return a reference to 'this'.
     */
    CountedConstPtrOrConstPtr& operator=(const CountedConstPtrOrConstPtr& r)
    {
      if ( this != & r ) {
	if ( myIsCountedPtr ) release();
	myIsCountedPtr = r.myIsCountedPtr;
	if ( r.myIsCountedPtr ) acquire( r.counterPtr() );
	else myAny = r.myAny;
      }
      return *this;
    }

    /**
     * Assignment with CountedPtrOrPtr. If 'this' was \b smart, then
     * the shared pointer is released. Then, if \a r is \b smart, then
     * this pointer object is also \b smart and acquires \a r (no
     * duplication). Otherwise, if \a r is \b simple, then this
     * pointer object only points at the same place.
     *
     * @param r the other pointer to clone, which may be \b smart or
     * \b simple.
     *
     * @return a reference to 'this'.
     */
    CountedConstPtrOrConstPtr& operator=(const CountedPtrOrPtr<T>& r)
    {
      if ( myIsCountedPtr ) release();
      myIsCountedPtr = r.myIsCountedPtr;
      if ( r.myIsCountedPtr ) acquire( r.counterPtr() );
      else myAny = r.myAny;
      return *this;
    }

    /**
     * Assignment with smart pointer (CountedPtr). If 'this' was \b
     * smart, then the shared pointer is released. Then this pointer
     * object becomes also \b smart and acquires \a r (no
     * duplication). 
     *
     * @param r the other smart pointer to clone.
     *
     * @return a reference to 'this'.
     */
    CountedConstPtrOrConstPtr& operator=(const CountedPtr<T>& r)
    {
      if ( myIsCountedPtr ) release();
      myIsCountedPtr = true;
      acquire( r.myCounter );
      return *this;
    }

    /**
     * @return 'true' iff 'this' pointer object is \b smart.
     */
    bool isSmart() const
    {
      return myIsCountedPtr;
    }

    /**
     * @return 'true' iff 'this' pointer object is \b simple.
     */
    bool isSimple() const
    {
      return ! myIsCountedPtr;
    }

    /**
       Equality operator ==
       
       @param other any other pointer.
       @return 'true' if pointed address is equal to \a other.
    */
    bool operator==( const T* other ) const
    {
      return myIsCountedPtr ? ( myAny ? counterPtr()->ptr : 0 ) == other : ptr() == other;
    }

    /**
       Inequality operator !=
       
       @param other any other pointer.
       @return 'true' if 'this' points to a different address than \a other.
    */
    bool operator!=( const T* other ) const
    {
      return myIsCountedPtr ? ( myAny ? counterPtr()->ptr : 0 ) != other : ptr() != other;
    }

    /**
     * Dereferencing operator. 
     *
     * @return a reference on the object of type \a T that is \b smartly
     * or \b simply pointed by 'this'.
     *
     * @pre 'isValid()' is true
     */
    const T& operator*()  const noexcept
    { 
      // Travis is too slow in Debug mode with this ASSERT.
      ASSERT( isValid() );
      return myIsCountedPtr ? ( * counterPtr()->ptr ) : ( * ptr() ); 
    }

    /**
     * Member access operator. 
     *
     * @return a pointer on the object of type \a T that is \b smartly
     * or \b simply pointed by 'this' or 0 if the object is not valid
     * ('isValid()' is false).
     *
     * @pre 'isValid()' is true
     */
    const T* operator->() const noexcept
    { 
      // Travis is too slow in Debug mode with this ASSERT.
      ASSERT( isValid() );
      return myIsCountedPtr ? counterPtr()->ptr : ptr();
    }

    /**
     * Secured member access operator. 
     *
     * @return a pointer on the object of type \a T that is \b smartly
     * or \b simply pointed by 'this' or 0 if the object is not valid
     * ('isValid()' is false).
     */
    const T* get()        const noexcept
    {
      return myIsCountedPtr ? ( myAny ? counterPtr()->ptr : 0 ) : ptr(); 
    }

    /**
     * @return 'true' iff the smart pointer is the sole one pointing
     * on this object or if the smart pointer is invalid ('isValid()'
     * is false) or if 'this' object is \b simple.
     */
    bool unique()   const noexcept
    {
      return myIsCountedPtr
	? ( myAny ? counterPtr()->count == 1 : true )
	: true;
    }

    /**
     * @note For debug.
     *
     * @return if 'this' object is \b smart, returns the number of
     * smart pointers pointing to the same object as 'this', or 0 if
     * 'this' object is \b simple.
     */
    unsigned int count() const
    { 
      return myIsCountedPtr ? counterPtr()->count : 0; 
    }

    /**
     * Gives back the pointer without deleting him. Deletes only the
     * Counter if 'this' was \b smart.
     *
     * @return the address that was {\b smartly} or {\b simply}
     * pointed by 'this' pointer.
     *
     * @note Use with care.
     * @pre 'isValid()' and, if \b smart, 'unique()'.
     */
    inline const T* drop() 
    { // Gives back the pointer without deleting him. Delete only the counter.
      ASSERT( isValid() );
      if ( myIsCountedPtr ) {
        ASSERT( unique() );
	T* tmp = counterPtr()->ptr;
	delete counterPtr();
	myAny = 0; 
	return tmp;
      } else {
	return ptr();
      }
    }

private:

    /// If \b smart, the counter object pointed by 'this', or if \b
    /// simple, the address of the object pointed by 'this'.
    void* myAny;
    /// If \c true, 'this' pointer object is \b smart, otherwise it is \b simple.
    bool myIsCountedPtr;

	    
    /**
     * @pre 'this' pointer object is \b smart.
     *
     * @return the (possibly shared) counter pointed by \ref myAny.
     */
    inline Counter* counterPtr() const
    { 
      // Travis is too slow in Debug mode with this ASSERT.
      ASSERT( myIsCountedPtr );
      return static_cast<Counter*>( myAny ); 
    }

    /**
     * @pre 'this' pointer object is \b simple.
     *
     * @return the address pointed by \ref myAny.
     */
    inline T* ptr() const
    { 
      // Travis is too slow in Debug mode with this ASSERT.
      ASSERT( ! myIsCountedPtr );
      return static_cast<T*>( myAny ); 
    }

    /**
     * Tells this \b smart pointer that it should reference the counter
     * \a c. If \a c is not null, the number of reference counts is
     * incremented.
     * @param c any counter (except this.myCounter).
     * @pre 'this' pointer object is \b smart.
     */
    inline void acquire(Counter* c) noexcept
    { // increment the count
      // Travis is too slow in Debug mode with this ASSERT.
      ASSERT( myIsCountedPtr );
      myAny = static_cast<void*>( c );
      if (c) ++c->count;
    }

    /**
     * Tells this \b smart pointer to that it should release its
     * current counter. If this counter was shared then the number of
     * reference counts is decremented, else both the object pointed
     * by the counter and the counter are freed.  In all cases, this
     * smart pointer becomes invalid.
     * @pre 'this' pointer object is \b smart.
     */
    void release()
    { // decrement the count, delete if it is 0
      // Travis is too slow in Debug mode with this ASSERT.
      ASSERT( myIsCountedPtr );
      if (myAny) {
        Counter * counter = counterPtr();
        if (--counter->count == 0) {
          delete counter->ptr;
          delete counter;
        }
        myAny = 0;
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
    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:


    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class CountedConstPtrOrConstPtr


  /**
   * Overloads 'operator<<' for displaying objects of class 'CountedConstPtrOrConstPtr'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'CountedConstPtrOrConstPtr' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const CountedConstPtrOrConstPtr<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/base/CountedConstPtrOrConstPtr.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CountedConstPtrOrConstPtr_h

#undef CountedConstPtrOrConstPtr_RECURSES
#endif // else defined(CountedConstPtrOrConstPtr_RECURSES)
