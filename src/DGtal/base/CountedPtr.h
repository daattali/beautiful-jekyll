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
 * @file CountedPtr.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/08
 *
 * Header file for module CountedPtr.cpp
 *
 * Taken from http://ootips.org/yonat/4dev/smart-pointers.html
 *
 * This file is part of the DGtal library.
 */

#if defined(CountedPtr_RECURSES)
#error Recursive header files inclusion detected in CountedPtr.h
#else // defined(CountedPtr_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CountedPtr_RECURSES

#if !defined CountedPtr_h
/** Prevents repeated inclusion of headers. */
#define CountedPtr_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  template <typename T> class CountedPtrOrPtr;
  template <typename T> class CountedConstPtrOrConstPtr;

  /////////////////////////////////////////////////////////////////////////////
  // template class CountedPtr
  /**
   * Description of template class 'CountedPtr' <p>
   * \brief Aim: Smart pointer based on reference counts.
   * 
   * It is a standard smart pointer by reference counts. Of course,
   * only dynamically allocated objects may be pointed by a smart
   * pointer. The CountedPtr<T> holds a pointer to a
   * CountedPtr::Counter object. This Counter object holds the pointer
   * to the dynamically allocated object and an integer representing
   * the number of smart pointers currently pointing to this Counter.
   *
   * @code
   * struct A{};
   * CountedPtr<A> smart_p1( new A );
   * CountedPtr<A> smart_p2( new A );
   * smart_p2 = smart_p1;  // second object is freed, first object is now shared.
   * @endcode
   *
   * @tparam T any data type.
   *
   * Taken from http://ootips.org/yonat/4dev/smart-pointers.html
   */
  template <typename T>
  class CountedPtr
  {
  public:

    /// Friend class which needs to access to CountedPtr.myCounter.
    friend class CountedPtrOrPtr<T>;
    /// Friend class which needs to access to CountedPtr.myCounter.
    friend class CountedConstPtrOrConstPtr<T>;

    // ----------------------- Standard services ------------------------------
  public:
    /// Internal structure for storing a smart pointer. Counts the
    /// number of references to some dynamically allocated object of
    /// type T in memory.
    struct Counter {
      /**
       * Builds a counter, i.e. a pair pointer/integer.
       *
       * @param p either 0 and the counter is invalid, or a pointer to
       * some dynamically allocated object of type T.
       *
       * @param c the number of CountedPtr currently pointing to this
       * counter.
       */
      Counter(T* p = 0, unsigned c = 1) : ptr(p), count(c) {}
      /// A pointer to a (shared) dynamically allocated object of type T.
      T*          ptr;
      /// The number of CountedPtr pointing to this counter.
      unsigned    count;
    };


    /**
     * Default Constructor and constructor from pointer.
     *
     * Creates a new CountedPtr, either null if \a p is 0 or pointing
     * to the given address \a p.
     *
     * @param p either 0 or a pointer on a dynamically allocated object of type T.
     */
    explicit CountedPtr(T* p = 0) : myCounter(0) 
    { 
      if (p) myCounter = new Counter(p);
    }

    /**
     * Destructor. If it was the last CountedPtr pointing on the
     * object, delete it.
     */
    ~CountedPtr()
    { 
      release(); 
    }

    /**
     * Copy Constructor.
     *
     * Performs a smart copy. The CountedPtr only references the same
     * object as \a r. There is now one more reference on the same
     * object.
     * 
     * @param r the object to copy.
     */
    CountedPtr(const CountedPtr& r) noexcept
    {
      acquire(r.myCounter);
    }

    /**
     * Assignment.
     *
     * Performs a smart assignment. The current referenced object is
     * dropped (and possibly freed if it was the last smart pointer
     * pointing on it). Then, this CountedPtr only references the same
     * object as \a r. There is now one more reference on the same
     * object.
     * 
     * @param r the object to copy.
     * @return a reference on 'this'.
     */
   CountedPtr& operator=(const CountedPtr& r)
    {
      if (this != &r)
        {
          release();
          acquire(r.myCounter);
        }
      return *this;
    }

    /**
     * Dereferencing operator. 
     * @return a reference on the object that is pointed by the smart pointer.
     * @pre 'isValid()' is true
     */
    T& operator*()  const noexcept
    {
      return *myCounter->ptr;
    }

    /**
     * Member access operator. 
     * @return a pointer on the object that is pointed by the smart pointer.
     * @pre 'isValid()' is true
     */
    T* operator->() const noexcept
    {
      return myCounter->ptr;
    }

    /**
     * Secured member access operator. 
     *
     * @return a pointer on the object that is pointed by the smart
     * pointer or 0 if the object is not valid ('isValid()' is false).
     */
    T* get()        const noexcept
    {
      return myCounter ? myCounter->ptr : 0;
    }

    /**
     * @return 'true' iff the smart pointer is the sole one pointing
     * on this object or if the smart pointer is invalid ('isValid()' is false).
     */
    bool unique()   const noexcept
    {
      return (myCounter ? myCounter->count == 1 : true);
    }

    /**
       Equality operator ==
       
       @param other any other pointer.
       @return 'true' if 'this' points to \a other.
    */
    bool operator==( const T* other ) const
    {
      return get() == other;
    }

    /**
       Inequality operator !=
       
       @param other any other pointer.
       @return 'true' if 'this' points to a different address than \a other.
    */
    bool operator!=( const T* other ) const
    {
      return get() != other;
    }

    /**
     * @note For debug.
     *
     * @return the number of smart pointers pointing to the same object as 'this'.
     */
    unsigned int count() const      
    {
      return myCounter->count;
    }

    /**
     * Gives back the pointer without deleting him. Deletes only the
     * Counter.
     *
     * @return the address that was pointed by this smart pointer
     * @note Use with care.
     * @pre 'isValid()' and 'unique()'.
     */
    inline T* drop() 
    { 
      ASSERT( isValid() );
      ASSERT( unique() );
      T* tmp = myCounter->ptr;
      delete myCounter;
      myCounter = 0; 
      return tmp;
    }
private:
    /**
     * Tells this smart pointer that it should reference the counter
     * \a c. If \a c is not null, the number of reference counts is
     * incremented.
     * @param c any counter (except this.myCounter).
     */
    void acquire(Counter* c) noexcept
    { // increment the count
        myCounter = c;
        if (c) ++c->count;
    }

    /**
     * Tells this smart pointer to that it should release its current
     * counter. If this counter was shared then the number of
     * reference counts is decremented, else both the object pointed
     * by the counter and the counter are freed.
     * In all cases, this smart pointer becomes invalid.
     */
    void release()
    { // decrement the count, delete if it is 0
        if (myCounter) {
            if (--myCounter->count == 0) {
                delete myCounter->ptr;
                delete myCounter;
            }
            myCounter = 0;
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
    /// The counter object pointed by this smart pointer.
    Counter* myCounter;

    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:


    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class CountedPtr


  /**
   * Overloads 'operator<<' for displaying objects of class 'CountedPtr'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'CountedPtr' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const CountedPtr<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/base/CountedPtr.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CountedPtr_h

#undef CountedPtr_RECURSES
#endif // else defined(CountedPtr_RECURSES)
