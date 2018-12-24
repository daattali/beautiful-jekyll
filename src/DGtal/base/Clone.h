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
 * @file Clone.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2013/11/5
 *
 * Header file for module Clone.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Clone_RECURSES)
#error Recursive header files inclusion detected in Clone.h
#else // defined(Clone_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Clone_RECURSES

#if !defined Clone_h
/** Prevents repeated inclusion of headers. */
#define Clone_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/base/CowPtr.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class Clone
  /**
     Description of template class 'Clone' <p> \brief Aim: This class
     encapsulates its parameter class to indicate that the given
     parameter is required to be duplicated (generally, this is done
     to have a longer lifetime than the function itself). On one hand,
     the user is reminded of the possible cost of duplicating the
     argument parameter, while he is also aware that the lifetime of
     the parameter is not a problem for the function. On the other
     hand, the Clone class is smart enough to enforce duplication \b
     only \b if \b needed. Substantial speed-up can be achieve through
     this mechanism.

     (For a complete description, see \ref moduleCloneAndReference).

     The class Clone is used in methods or functions to encapsulate
     the parameter types. The following conversion from input
     parameter to data member or variable are sumed up in the
     following table:

     |Argument type:    |\c const \c T& |    \c T*      |\c CountedPtr<T>| \c CowPtr<T>   |\c T&& (c++11)|
     |------------------|---------------|---------------|----------------|----------------|--------------|
     |To:\c T           | Dupl.  O(N)   |Acq. Dupl. O(N)| Dupl. O(N)     | Dupl. O(N)     | Move. O(1)   |
     |To:\c T*          | Dupl.  O(N)   |   Acq. O(1)   | Dupl. O(N)     | Dupl. O(N)     | Move. O(1)   |
     |To:\link CowPtr CowPtr<T>\endlink   | Dupl.  O(N)   |   Acq. O(1)   | Lazy. O(1)/O(N)| Lazy. O(1)/O(N)| Move. O(1)   |

     with abbreviations:
     - \b Dupl. Object is duplicated.
     - \b Lazy. Object is lazily duplicated, meaning only when the user writes on it (which may be never).
     - \b Acq. Dynamically allocated pointer is acquired. User should take care himself of deletion only if storing the parameter with a pointer.
     - \b Move. The object is moved into the new object. This is  generally much faster than copy. This is true for instance for all classical STL containers. You can also write a specific \c  move constructor for your class.

     It is clear that worst case is duplication while sometimes \ref Clone
     is constant time (while guaranteeing object invariance and
     life-time).


     @note The usage of \c Clone<T> instead of \c const \c T \c & or
     \c const \c T \c * in parameters is \b always \b recommended when
     the user duplicates the parameter and stores a clone of it as a
     data member for later use. The usage \c Clone<T> instead of \c T
     is \b recommended whenever \c T is big (the object is sometimes
     duplicated twice). When the object is small, writing either \c
     Clone<T> or \c T is acceptable. If your member is a CowPtr<T>,
     then you should use a Clone<T> as parameter.  Depending on your
     data member, we advise the following \a parameter \a definition
     when \b duplication is asked for.

     |member type:|     \c T          |  big \c T |\c CowPtr<T>|     \c T* |
     |----------|-------------------|-----------|------------|-----------|
     |parameter|\c T or \c Clone<T>|\c Clone<T>|\c Clone<T> |\c Clone<T>|

     \note A conversion to \c T* means pointer acquisition. Hence the programmer should take care of deletion of the object.
     Otherwise, deletion is automatic for \c T or \c CowPtr<T> member. Furthermore, a conversion to a \c T* requires the use of the address operator (\c operator&) by the \e developer. If argument is `Clone<T> a`, and member name is `b`:

     |member type:|     \c T          |     \c T*  |\c CowPtr<T>|
     |-----------|-------------------|------------|-----------|
     |member deletion:|  automatic   |  \b manual | automatic |
     |conversion:| automatic: `b(a)` |  address: `b(&a)`| automatic: `b(a)` |

     \note When choosing a `Clone<T>` parameter, the \e programmer should really consider using a `CowPtr<T>` member to store it, since it is the most versatile and optimizable variant. The only advantage of the two others storing methods (\c T  and  \c T*) is that there is one less indirection.

     @note Note that an instance of Clone<T> is itself a light object (it
     holds only a const enum and const pointer), the duplication (if
     necessary) takes place when the user instantiates its member of
     type T (or CowPtr<T> or T* member).


     @tparam T is any type.

     @see Alias
     @see ConstAlias

     @note (Speed) Even on a small type (here a pair<int,int>), it is
     much faster than NClone and has the advantage (wrt Clone<T>) to
     handle nicely both const T& and CowPtr<T> as input. It may be
     slightly slower than deprecated::Clone (and by value or by const ref
     parameter passing) for small objects like a pair<int,int>. This
     is certainly due to the fact that it uses one more integer
     register for \a myParam data member.

     | Type   | Context  | value    | const ref | deprecated::Clone  | Clone |
     |--------|----------|----------|-----------|--------|--------|
     | 2xint  |i7 2.4GHz |    48ms |     48ms  |   48ms |   59ms |
     |2xdouble|i7 2.4GHz |    48ms |     48ms  |   48ms |   49ms |
     | 2xint  |Xeon 2.67GHz|    54ms |     54ms  |   54ms |   54ms |
     |2xdouble|Xeon 2.67GHz|    54ms |     54ms  |   54ms | 53.5ms |


     @note It prevents direct assignment to CountedPtr<T> since their
     meaning is "shared_ptr".


     It can be used as follows. Consider this simple example where
     class \e A is a big object. Then we define three classes \e B1,
     \e B2 and \e B3, that uses some instance of \e A.

     @code
     const int N = 10000;
     struct A { ...
     int table[N];
     };

     // Each B1, B2 or B3 uses A, but we do not know if A will be copied
     // or just referenced by only looking at the declaration of
     // the method. Generally the ambiguity is removed by adding
     // comments or, for the experienced developper, by looking at
     // other parts of the code.

     // Only aliasing, but for a long lifetime.
     struct B1 {
     B1( const A & a ) // ambiguous, cost is O(1) here and lifetime of a should exceed constructor.
     : myA( a ) {}
     ...
     const A & myA;
     };
     // Copying as data member (stack or heap depending on B2 instance)
     struct B2 {
     B2( const A & a ) // ambiguous, cost is O(N) here
     : myA( a ) {}
     ...
     A myA;
     };
     // Copying on heap and data member pointing on it.
     struct B3 {
     B3( const A & a ) // ambiguous, cost is O(N) here
     { myA = new A( a ); }
     ~B3()
     { if ( myA != 0 ) delete myA; }
     ...
     A* myA;
     };
     @endcode

     Sometimes it is also very important that the developper that uses
     the library is conscious that an object, say \a b, may require
     that an instance \a a given as parameter should have a lifetime
     longer than \a b itself (case for an instance of \a B1
     above). Classes Clone, Alias, ConstAlias exist for these
     reasons. The classes above may be rewritten as follows.

     @code
     // Aliasing for a long lifetime is visible.
     struct B1 {
     B1( ConstAlias<A> a ) // not ambiguous, cost is O(1) here and lifetime of a should be long enough
     : myA( a ) {}
     ...
     const A & myA;
     // or Const A* myA;
     };
     // Cloning as data member is visible.
     struct B2 {
     B2( Clone<A> a ) // not ambiguous, cost is O(N) here and lifetime of a is whatever.
     : myA( a ) {}
     ...
     A myA;
     };
     // Cloning on the heap requires address operator, so that the user remembers calling \c delete.
     struct B3_v1 {
     B3_v1( Clone<A> a ) // not ambiguous, cost is O(N) here and lifetime of a is whatever.
     : myA( &a ) {}
     ~B3_v1() { if ( myA != 0 ) delete myA; }
     ...
     A* myA;
     };
     // Cloning on the heap with CountedPtr mechanism is straightforward.
     struct B3_v2 {
     B3_v2( Clone<A> a ) // not ambiguous, cost is O(N) here and lifetime of a is whatever.
     : myA( a ) {}
     ~B3_v2() {} // CountedPtr takes care of delete.
     ...
     CountedPtr<A> myA;
     };
     // Cloning on the heap with CowPtr mechanism is straightforward.
     struct B3_v3 {
     B3_v3( Clone<A> a ) // not ambiguous, cost is O(N) here and lifetime of a is whatever.
     : myA( a ) {}
     ~B3_v3() {} // CountedPtr takes care of delete.
     ...
     CowPtr<A> myA;
     };
     ...
     A a1;
     B1 b( a1 );    // do not duplicate a1
     B2 bb( a1 );   // duplicate a1
     B2 bbb( &a1 ); // also duplicate a1 !
     B3_v1 c1( a1 ); // duplicate a1 on the heap
     B3_v2 c1( a1 ); // duplicate a1 on the heap
     B3_v3 c1( a1 ); // duplicate a1 on the heap
     @endcode

     A last question could be why are we not just passing the instance
     of A by value. This, for sure, would tell the developper that the
     instance is duplicated somehow. The problem is that it induces
     generally two duplications, and not only one ! It may be possible
     that the compiler optimizes things nicely but it is unclear if
     the compiler will always do it. Furthermore, sometimes, no
     duplication is needed (when duplicating a CowPtr for instance).

     @code
     struct B4 {
     B4( A a ) // not ambiguous, but cost is O(2N) here.
     : myA( a ) {}
     ...
     A myA;
     };
     A a1;
     B4 b4( a1 ) // The object \a a1 is copied once on the heap as the parameter \a a, and once as the member \a b3.myA.
     @endcode

     @note The user should not used Clone<T> for data members, only as a type for parameters.
*/
  template <typename T>
  class Clone
  {
    // ----------------------- Internal classes ------------------------------
  protected:

    /// Internal class that allows to distinguish the different types of parameters.
    enum Parameter { CONST_LEFT_VALUE_REF, LEFT_VALUE_REF, PTR, CONST_PTR,
		     COW_PTR, COUNTED_PTR, RIGHT_VALUE_REF, COUNTED_PTR_OR_PTR,
		     COUNTED_CONST_PTR_OR_CONST_PTR };

    /// Internal class that is used for a late deletion of an acquired pointer.
    struct TempPtr {
      /**
	 Constructor from pointer.
	 @param ptr Any pointer that is acquired by 'this'.
      */
      inline TempPtr( T* ptr ) : _ptr( ptr ) {}
      /**
	 Destructor. Performs delete on _ptr member.
      */
      inline ~TempPtr() { ASSERT( _ptr != 0 ); delete _ptr; }
      /// Acquired pointer.
      T* _ptr;
    };

    // ----------------------- Standard services ------------------------------
  public:

    /**
       Destructor. Does nothing.
     */
    inline ~Clone() {}

    /**
      Copy constructor. The cloning is just forwarded.
      @param other the clone object to clone
    */
    inline Clone( const Clone & other )
      : myParam( other.myParam ), myPtr( other.myPtr ) {}

    /**
       Constructor from an instance of T. The object is pointed in
       'this'. It is duplicated (or not) when the user claims it.
       @param t any object of type T.
    */
    inline Clone( const T & t )
      : myParam( CONST_LEFT_VALUE_REF ), myPtr( static_cast<const void*>( &t ) ) {}

    /**
       Constructor from a pointer to a valid instance of T. The object is pointed in
       'this'. It is duplicated (or not) when the user claims it.
       @param ptrT any valid pointer to a object of type T.
       @pre ptrT != 0
    */
    inline Clone( T* ptrT )
      : myParam( PTR ), myPtr( static_cast<const void*>( ptrT ) ) {}

    /**
       Constructor from CowPtr<T>.  The object is pointed in
       'this'. It is duplicated (or not) when the user claims it.

       @param ptrT any copy-on-write pointer to a object of type T.
    */
    inline Clone( const CowPtr<T> & ptrT )
      : myParam( COW_PTR ), myPtr( static_cast<const void*>( &ptrT ) ) {}

    /**
       Constructor from CountedPtr<T>.  The object is pointed in
       'this'. It is duplicated (or not) when the user claims it.

       @param ptrT any shared pointer to a object of type T.
    */
    inline Clone( const CountedPtr<T> & ptrT )
      : myParam( COUNTED_PTR ), myPtr( static_cast<const void*>( &ptrT ) ) {}

    /**
       Constructor from right-reference value.  The object is pointed in
       'this'. It is duplicated (or not) when the user claims it.

       @param t any shared pointer to a object of type T.
    */
    inline Clone( T && t )
      : myParam( RIGHT_VALUE_REF ), myPtr( static_cast<const void*>( &t ) ) {}


    /**
       Cast operator to a T instance. The object is duplicated or not
       depending on the type of input parameter.

      - const T & -> T             // immediate duplication (checked)
      - T* -> T                    // immediate duplication, acquired and deleted. (checked)
      - CountedPtr<T> -> T         // immediate duplication (checked)
      - CowPtr<T> -> T             // immediate duplication (checked)
      - T&& -> T                   // move into member      (checked)
    */
    inline operator T() const
    {
      switch( myParam ) {
      case CONST_LEFT_VALUE_REF:
	return T( * static_cast< const T* >( myPtr ) );
      case PTR: {
        TempPtr tmp( const_cast< T* >( static_cast< const T* >( myPtr ) ) );
        return T( * static_cast< const T* >( myPtr ) );
      } // destroy acquired pointer.
      case COW_PTR:
	return T( * static_cast< const CowPtr<T>* >( myPtr )->get() );
      case COUNTED_PTR:
	return T( * static_cast< const CountedPtr<T>* >( myPtr )->get() );
      case RIGHT_VALUE_REF:
	return T( std::move( * const_cast<T*>( static_cast< const T* >( myPtr ) ) ) );
      default: ASSERT( false && "[Clone::operator T() const] Invalid cast for given type. " );
        return T( * static_cast< const T* >( myPtr ) );
      }
    }

    /**
       Cast operator to a copy-on-write pointer on T instance. The object is duplicated or not
       depending on the type of input parameter.

      - const T & -> CowPtr<T>     // immediate duplication (checked)
      - T* -> CowPtr<T>            // acquired (checked)
      - CountedPtr<T> -> CowPtr<T> // lazy duplication      (checked)
      - CowPtr<T> -> CowPtr<T>     // lazy duplication      (checked)
      - T&& -> CowPtr<T>           // move into member      (checked)
    */
    inline operator CowPtr<T>() const
    {
      switch( myParam ) {
      case CONST_LEFT_VALUE_REF:
	return CowPtr<T>( new T( * static_cast< const T* >( myPtr ) ) );
      case PTR:
	return CowPtr<T>( const_cast<T*>( static_cast< const T* >( myPtr ) ) );
      case COW_PTR:
	return CowPtr<T>( * static_cast< const CowPtr<T>* >( myPtr ) );
      case COUNTED_PTR:
	return CowPtr<T>( * static_cast< const CountedPtr<T>* >( myPtr ) );
      case RIGHT_VALUE_REF:
	return CowPtr<T>( new T( std::move( * const_cast<T*>( static_cast< const T* >( myPtr ) ) ) ) );
      default: ASSERT( false && "[Clone::operator CowPtr<T>() const] Invalid cast for given type. " );
        return CowPtr<T>( 0 );
      }
    }

    /**
       Address operator that returns the address of the given T
       instance.  The object is duplicated or not depending on the
       type of input parameter.

       @return a pointer on an instance of T.

     - const T & -> T*            // immediate duplication, should be deleted at the end. (checked)
     - CowPtr<T> -> T*            // immediate duplication, should be deleted at the end. (checked)
     - CountedPtr<T> -> T*        // immediate duplication, should be deleted at the end. (checked)
     - T* -> T*                   // acquired, should be deleted at the end. (checked)
     - T&& -> T*                  // move into member, should be deleted at the end. (checked)
    */
    inline T* operator&() const
    {
      switch( myParam ) {
      case CONST_LEFT_VALUE_REF:
	return new T( * static_cast< const T* >( myPtr ) );
      case PTR:
	return const_cast<T*>( static_cast< const T* >( myPtr ) );
      case COW_PTR:
	return new T( *( static_cast< const CowPtr<T>* >( myPtr )->get() ) );
      case COUNTED_PTR:
	return new T( *( static_cast< const CountedPtr<T>* >( myPtr )->get() ) );
      case RIGHT_VALUE_REF:
	return new T( std::move( * const_cast<T*>( static_cast< const T* >( myPtr ) ) ) );
      default: ASSERT( false && "[T* Clone::operator&() const] Invalid address for given type. " );
        return 0;
      }
    }

    // ------------------------- Private Datas --------------------------------
  private:
    /// Characterizes the type of the input parameter at clone instanciation.
    const Parameter myParam;
    /// Stores the address of the input parameter for further use.
    const void* const myPtr;


    // ------------------------- Hidden services ------------------------------
  private:

    /**
     * Constructor.
     * Forbidden.
     */
    Clone();


    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden (otherwise the user might be tempted to use it as a member).
     */
    Clone & operator= ( const Clone & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Clone

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Clone_h

#undef Clone_RECURSES
#endif // else defined(Clone_RECURSES)
