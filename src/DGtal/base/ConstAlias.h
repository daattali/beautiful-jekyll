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
 * @file ConstAlias.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2013/11/5
 *
 * Header file for module ConstAlias.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ConstAlias_RECURSES)
#error Recursive header files inclusion detected in ConstAlias.h
#else // defined(ConstAlias_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ConstAlias_RECURSES

#if !defined ConstAlias_h
/** Prevents repeated inclusion of headers. */
#define ConstAlias_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/base/CountedPtrOrPtr.h"
#include "DGtal/base/CowPtr.h"
#include "DGtal/base/CountedConstPtrOrConstPtr.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class ConstAlias
  /**
     Description of template class 'ConstAlias' <p> \brief Aim: This
     class encapsulates its parameter class so that to indicate to the
     user that the object/pointer will be only const aliased (and
     hence left unchanged). Therefore the \b user is reminded that the
     argument parameter is given to the function without any
     additional cost and may not be modified, while he is aware that
     the lifetime of the argument parameter must be at least as long
     as the object itself. Note that an instance of ConstAlias<T> is
     itself a light object (it holds only an enum and a pointer).

     (For a complete description, see \ref moduleCloneAndReference).

     It is used in methods or functions to encapsulate the parameter
     types. The following conversion from input parameter to data
     member or variable are possible:

     |Argument          |\c const \c T& |\c const \c T* |\c CountedPtr<T>|\c CountedPtrOrPtr<T>|\c CountedConstPtrOrConstPtr<T>|
     |------------------|---------------|---------------|----------------|------------|---|
     |To: \c const T&   | Shared. O(1)  | Shared. O(1)  |                |            |   |
     |To: \c const T*   | Shared. O(1)  | Shared. O(1)  |                |            |   |
     |To: \link CountedConstPtrOrConstPtr CountedConstPtrOrConstPtr<T>\endlink|Shared. O(1)|Shared. O(1)|Shared. O(1), \b secure |Shared. O(1), \b secure| Shared. O(1), \b secure |

     Argument conversion to member is \b automatic except when
     converting to a pointer \c const \c T*: the \b address operator
     (\c operator&) must be used in this case.

     For the last row (case where the \e programmer choose a \ref
     CountedConstPtrOrConstPtr to hold the const alias), the \e user
     can thus enforce a \b secure const aliasing by handling a variant
     of \ref CountedPtr as argument. In this case, even if the aliased
     object is destroyed in the caller context, it still exists in the
     callee context.

     @note The usage of \ref ConstAlias<T> instead of \c const \c T \c
     & or \c const \c T \c * in parameters is \b recommended when the
     lifetime of the parameter must exceed the lifetime of the called
     method/function/constructor (often the case in constructor or
     init methods).

     @note The usage of \c const \c T \c & or \c const \c T \c *
     instead of \ref ConstAlias<T> is \b recommended when the lifetime
     of the parameter is not required to exceed the lifetime of the
     called method/function/constructor (often the case in standard
     methods, where the parameter is only used at some point, but not
     referenced after in some data member).

     @note If the \e developer (not the \e user) wishes to enforce a
     \b secure const aliasing in all cases, he should probably clone
     the argument, hence use class \ref Clone.


     @tparam T is any type.

     @see Alias
     @see Clone

     It can be used as follows. Consider this simple example where
     class \e A is a big object.

     @code
     const int N = 10000;
     struct A { ...
       int table[N];
     };

     // When looking at the signature of B1's constructor, there is an
     // ambiguity on the role of parameter a and its life-time. Here
     // a's lifetime should be longer than the construction. Generally
     // the ambiguity is removed by adding comments or, for the
     // experienced developper, by looking at other parts of the code.

     // Only aliasing, but for a long lifetime.
     struct B1 {
       B1( const A & a ) // ambiguous, cost is O(1) here and lifetime of a should exceed constructor.
       : myA( a ) {}
     ...
       const A & myA;
     };
     @endcode

     Sometimes it is very important that the developper that uses
     the library is conscious that an object, say \a b, may require
     that an instance \a a given as parameter should have a lifetime
     longer than \a b itself (case for an instance of \a B1
     above). Classes \ref Clone, \ref Alias, \ref ConstAlias exist for these
     reasons. The class above may be rewritten as follows.

     @code
     // ConstAliasing for a long lifetime is visible.
     struct B1_v2_1 {
       B1_v2_1( ConstAlias<A> a ) // not ambiguous, cost is O(1) here and lifetime of a should be long enough
       : myA( a ) {}
     ...
       const A & myA;
     };

     // ConstAliasing for a long lifetime is visible.
     struct B1_v2_2 {
       B1_v2_2( ConstAlias<A> a ) // not ambiguous, cost is O(1) here and lifetime of a should be long enough
       : myA( &a ) {} // Note the use of the address operator because of the pointer member
     ...
       const A* myA;
     };

     // ConstAliasing for a long lifetime is visible.
     struct B1_v2_3 {
       B1_v2_3( ConstAlias<A> a ) // not ambiguous, cost is O(1) here and lifetime of a should be long enough
       : myA( a ) {}
     ...
       CountedConstPtrOrConstPtr<A> myA;
     };

     ...
     A a1;
     CountedPtr<A> counted_a1( new A( a1 ) );
     B1 ( a1 ); // not duplicated
     B1_v2_1 ( a1 ); // not duplicated
     B1_v2_2 ( a1 ); // not duplicated
     B1_v2_3 ( counted_a1 );  // not duplicated, even better the user choose a secure variant of const alias.
     @endcode

     @note The user should not use ConstAlias<T> instead of \c const \c T & for data
     members. It works in most cases, but there are some subtle
     differences between the two behaviors.

     @note ConstAlias have a default copy constructor, so as to let the
     user forward an ConstAlias<T> parameter.
   */
  template <typename T>
  class ConstAlias
  {

    // ----------------------- Internal classes ------------------------------
  protected:

    /// Internal class that allows to distinguish the different types of parameters.
    enum Parameter { CONST_LEFT_VALUE_REF, LEFT_VALUE_REF, PTR, CONST_PTR,
        COW_PTR, COUNTED_PTR, RIGHT_VALUE_REF, COUNTED_PTR_OR_PTR,
        COUNTED_CONST_PTR_OR_CONST_PTR };

    // ----------------------- Standard services ------------------------------
  public:

    /**
       Destructor. Does nothing.
     */
    inline ~ConstAlias() {}

    /**
       Constructor from const reference to an instance of T. The object is pointed in
       'this'.
       @param t any const reference to an object of type T.
    */
    inline ConstAlias( const T& t )
      : myParam( CONST_LEFT_VALUE_REF ), myPtr( static_cast<const void*>( &t ) ) {}

    /**
       Constructor from const pointer to an instance of T. The object is pointed in
       'this'.
       @param ptrT any const pointer to an object of type T.
    */
    inline ConstAlias( const T* ptrT )
      : myParam( CONST_PTR ), myPtr( static_cast<const void*>( ptrT ) ) {}


    /**
       Constructor from a const reference to a copy-on-write pointer on T. Deleted.
       
       Const-aliasing a copy-on-write pointer has no meaning. Consider Clone instead.
    */
    ConstAlias( const CowPtr<T>& ) = delete;


    /**
       Constructor from a const reference to a shared pointer on T. The object is pointed in
       'this'.
       @param shT any const reference to a shared pointer to an object of type T.
    */
    inline ConstAlias( const CountedPtr<T>& shT )
      : myParam( COUNTED_PTR ), myPtr( static_cast<const void*>( &shT ) ) {}

    /**
       Constructor from a const reference to a shared or simple const pointer on T. The object is pointed in
       'this'.
       @param shT any const reference to a shared or simple const pointer to an object of type T.
    */
    inline ConstAlias( const CountedPtrOrPtr<T>& shT )
      : myParam( COUNTED_PTR_OR_PTR ), myPtr( static_cast<const void*>( &shT ) ) {}

    /**
       Constructor from a const reference to a shared or simple const pointer on T. The object is pointed in
       'this'.
       @param shT any const reference to a shared or simple const pointer to an object of type T.
    */
    inline ConstAlias( const CountedConstPtrOrConstPtr<T>& shT )
      : myParam( COUNTED_CONST_PTR_OR_CONST_PTR ), myPtr( static_cast<const void*>( &shT ) ) {}

    /**
       Constructor from right-reference value. Delete.
        
       Const-aliasing a rvalue ref has no meaning. Consider Clone instead.
    */
    ConstAlias( T&& ) = delete;

    /**
       Cast operator to a T const-reference. The object is never
       duplicated. Allowed input parameters are:
       - const A & -> const A &     // no duplication
       - const A* -> const A &      // no duplication, exception if null
    */
    inline operator const T&() const
      {
        switch( myParam ) {
          case CONST_LEFT_VALUE_REF:
          case CONST_PTR:
            return *( static_cast< const T* >( myPtr ) );
          default: ASSERT( false && "[ConstAlias::operator const T&() const] Invalid cast for given type. Consider passing a const left-value reference or a const pointer as a parameter." );
                   return *( static_cast< const T* >( myPtr ) );
        }
      }

    /**
       Cast operator to a T const-pointer. The object is never
       duplicated. Allowed input parameters are:
       - const A & -> const A*      // no duplication
       - const A* -> const A*       // no duplication
    */
    inline const T* operator&() const
      {
        switch( myParam ) {
          case CONST_LEFT_VALUE_REF:
          case CONST_PTR:
            return static_cast< const T* >( myPtr );
          default: ASSERT( false && "[const T* ConstAlias::operator&() const] Invalid address operator for given type. Consider passing a const left-value reference or a const pointer as a parameter." );
                   return static_cast< const T* >( myPtr );
        }
    }

    /**
       Cast operator to a shared or simple const pointer. The object is never
       duplicated. Allowed input parameters are:

       - const A&                     -> CountedConstPtrOrConstPtr<A> // no duplication
       - const A*                     -> CountedConstPtrOrConstPtr<A> // no duplication
       - CountedPtr<A>                -> CountedConstPtrOrConstPtr<A> // no duplication
       - CountedPtrOrPtr<A>           -> CountedConstPtrOrConstPtr<A> // no duplication
       - CountedConstPtrOrConstPtr<A> -> CountedConstPtrOrConstPtr<A> // no duplication
    */
    inline operator CountedConstPtrOrConstPtr<T>() const
      {
        switch( myParam ) {
          case CONST_LEFT_VALUE_REF:
          case CONST_PTR:
            return CountedConstPtrOrConstPtr<T>( static_cast< const T* >( myPtr ), false );
          case COUNTED_PTR:
            return CountedConstPtrOrConstPtr<T>( *( static_cast< const CountedPtr<T>* >( myPtr ) ) );
          case COUNTED_PTR_OR_PTR:
            return CountedConstPtrOrConstPtr<T>( *( static_cast< const CountedPtrOrPtr<T>* >( myPtr ) ) );
          case COUNTED_CONST_PTR_OR_CONST_PTR:
            return CountedConstPtrOrConstPtr<T>( *( static_cast< const CountedPtrOrPtr<T>* >( myPtr ) ) );
          default: ASSERT( false && "[ConstAlias::operator CowPtr<T>() const] Invalid cast for given type. Consider passing a CountedPtr or a CowPtr as a parameter." );
                   return CountedConstPtrOrConstPtr<T>( 0, false );
        }
    }

    inline const T* operator->() const
      {
        switch( myParam ) {
          case CONST_LEFT_VALUE_REF:
          case CONST_PTR:
            return static_cast< const T* >( myPtr );
          case COUNTED_PTR:
            return ( static_cast< const CountedPtr<T>* >( myPtr ) )->operator->();
          case COUNTED_PTR_OR_PTR:
            return ( static_cast< const CountedPtrOrPtr<T>* >( myPtr ) )->operator->();
          case COUNTED_CONST_PTR_OR_CONST_PTR:
            return ( static_cast< const CountedConstPtrOrConstPtr<T>* >( myPtr ) )->operator->();
          default: ASSERT( false && "[ConstAlias::operator->() const] Invalid cast for given type. Consider passing a CountedPtr or a CowPtr as a parameter." );
                   return 0;
      }
    }

    // ------------------------- Private Datas --------------------------------
  private:
    /// Characterizes the type of the input parameter at clone instanciation.
    const Parameter myParam;
    /// Stores the address of the input parameter for further use.
    const void* const myPtr;


    // ------------------------- Internals ------------------------------------
  private:

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden (otherwise the user might be tempted to use it as a member).
     */
    ConstAlias & operator= ( const ConstAlias & other );

  }; // end of class ConstAlias

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ConstAlias_h

#undef ConstAlias_RECURSES
#endif // else defined(ConstAlias_RECURSES)
