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
 * @file CDigitalSet.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @author Sebastien Fourey (\c Sebastien.Fourey@greyc.ensicaen.fr )
 * Groupe de Recherche en Informatique, Image, Automatique et
 * Instrumentation de Caen - GREYC (CNRS, UMR 6072), ENSICAEN, France
 *
 * @date 2010/07/01
 *
 * Header file for concept CDigitalSet.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDigitalSet_RECURSES)
#error Recursive header files inclusion detected in CDigitalSet.h
#else // defined(CDigitalSet_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDigitalSet_RECURSES

#if !defined CDigitalSet_h
/** Prevents repeated inclusion of headers. */
#define CDigitalSet_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "boost/concept_check.hpp"
#include "DGtal/base/Common.h"
#include "DGtal/base/CowPtr.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/kernel/domains/CDomain.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // class CDigitalSet
  /////////////////////////////////////////////////////////////////////////////
  // class CDigitalSet
/**
   Description of \b concept '\b CDigitalSet' <p>
   @ingroup Concepts
   @brief Aim: Represents a set of points within the given
   domain. This set of points is modifiable by the user. It is thus
   very close to the STL concept of simple associative container
   (like set std::set<Point>), except that there is a notion of
   maximal set of points (the whole domain).
     
 ### Refinement of 
   - boost::CopyConstructible
   - concepts::CPointPredicate

@todo add boost::Container ? Not for now, since coding style do not
 match with STL (e.g. Iterator instead of iterator).

@note It is also a refinement of boost::Assignable from concepts::CPointPredicate.
    
 ### Associated types :

   - \c Domain: the domain in which points are defined, a model of concept CDomain.
   - \c Size: the type for couting elements of the set.
   - \c Iterator: the iterator type for visiting elements of the set, as
     well as modify the set. The iterator should be readable (model of
     boost_concepts::ReadableIteratorConcept) and should allow single pass
     traversal (model of
     boost_concepts::SinglePassIteratorConcept). Its value has
     type \c Point (defined in concepts::CPointPredicate).
   - \c ConstIterator: the type for visiting elements of the set. Note
     that types for Iterator and ConstIterator should be the same,
     similarly to STL simple associative containers.
    
 ### Notation
     - \c X : A type that is a model of CDigitalSet
     - \a x, \a y : objects of type \c X
     - \a p, \a p1, \a p2 : objects of type \c Point
     - \a it : object of type \c Iterator
    
 ### Definitions
    
 ### Valid expressions and semantics

| Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
|---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
| Get domain    | \a x.domain() |                  | \c Domain   |                  | returns the domain of this set | | O(1), should be returned by reference |         
| Get counted pointer on domain    | \a x.domainPointer() |                  | \c CountedPtr<Domain>   |                  | returns a counted pointer on the domain of this set | | O(1) |         
| Number of elements | \a x.size() |                 | \c Size     |                  | returns the number of elements of this set. | | at most linear in the number of elements |         
| Empty container test | \a x.empty() |            | \c bool     |                  | returns true iff the number of elements is zero, always faster than \c x.size() == 0 | | amortized constant time |         
| Insert point  | \a x.insert( p ) |               |             |                  | Inserts point \a p in the set | | |         
| Insert new point | \a x.insertNew( p ) |         |             | \a p is not already in \a x | Inserts point \a p in the set, assuming it is not already inside | | faster than \a insert |         
| Erase point   | \a x.erase( p ) |                | \c Size     |                  | Erase point \a p from the set \a x, returns the number of points effectively removed from the set (thus either 0 or 1) | | |         
| Erase point from iterator   | \a x.erase( it ) | |             | \a it != \a x.end() | Erase the point pointed by valid iterator \a it from the set \a x | | |         
| Removes all points | \a x.clear() |              |             |                  | Removes all the points from the set \a x, \a x.empty() is true afterwards | | |         
| Get iterator on first element | \a x.begin() |   | \c Iterator |                  | Returns the iterator on the first element of the set | | Constant time. |         
| Get iterator after the last element | \a x.end() | | \c Iterator |                | Returns the iterator after the last element of the set | | Constant time. |         
| Get iterator on first element | \a x.begin() |   | \c ConstIterator |             | Returns the const iterator on the first element of the set | | Constant time. |         
| Get iterator after the last element | \a x.end() | | \c ConstIterator |           | Returns the const iterator after the last element of the set | | Constant time. |         
| Set union to left | \a x += \a y |               | \c X &      | Elements of \a y should be included in the domain of \a x | Adds all elements of \a y to \a x. Returns a reference to itself. | | |         
| Complement of set | \a x.computeComplement(\a outIt) | \a outIt is an output iterator on \c Point | | | Outputs the complement set of \a x in the given output iterator. | | |         
| Complement of set | \a x.assignFromComplement(\a y) | |      | Domain of \a x should contain the domain of \a y | The set \a x is the complement of set \a y afterwards. | | |         
| Bounding box   | \a x.computeBoundingBox(\a p1,\a p2) | |   |                  | Points \a p1 and \a p2 define respectively the lower and upper bound of the bounding box of all points of \a x. | | Linear in \a x.size() |         
| Search point  | \a x.find( p ) |                 | \c Iterator |                  | Returns an iterator pointing on point \a p if it was found in the set \a x, or \a x.end() otherwise. | | |         
| Search point  | \a x.find( p ) |                 | \c ConstIterator |             | Returns a const iterator pointing on point \a p if it was found in the set \a x, or \a x.end() otherwise. | | |         
    
 ### Invariants
    
 ### Models

- DigitalSetBySTLVector, DigitalSetBySTLSet, DigitalSetFromMap, DigitalSetFromAssociativeContainer
    
 ### Notes

@tparam T the type that should be a model of CDigitalSet.
   */
  template <typename T> 
  struct CDigitalSet :
    boost::CopyConstructible< T >, 
    concepts::CPointPredicate< T >
  {
    // ----------------------- Concept checks ------------------------------
  public:
    // 1. define first provided types (i.e. inner types), like
    typedef typename T::Domain Domain;
    typedef typename T::Point Point;
    typedef typename T::Size Size;
    typedef typename T::Iterator Iterator;
    typedef typename T::ConstIterator ConstIterator;

    BOOST_CONCEPT_ASSERT(( concepts::CDomain<Domain> ));
    BOOST_CONCEPT_ASSERT(( boost_concepts::ReadableIteratorConcept<ConstIterator > ));
    BOOST_CONCEPT_ASSERT(( boost_concepts::SinglePassIteratorConcept<ConstIterator > ));
    
    // 2. then check the presence of data members, operators and methods with
    BOOST_CONCEPT_USAGE( CDigitalSet )
    {
      checkConstConstraints();
      checkNonConstConstraints();
    }
    /**
       This method checks const methods when a non-const version exist.
    */
    void checkConstConstraints() const
    {
      ConceptUtils::sameType( myDomain, myX.domain() );
      ConceptUtils::sameType( myDomainPtr, myX.domainPointer() );
      ConceptUtils::sameType( mySize, myX.size() );
      ConceptUtils::sameType( myBool, myX.empty() );

      ConceptUtils::sameType( myConstIterator, myX.find( myPoint ) );
      ConceptUtils::sameType( myConstIterator, myX.begin() );
      ConceptUtils::sameType( myConstIterator, myX.end() );
    }

    /**
       This method checks non-const methods when a const version exist.
    */
    void checkNonConstConstraints()
    {
      myX.insert( myPoint );
      // template <typename PointInputIterator>
      //   BOOST_CONCEPT_REQUIRES
      //   ( ((boost::InputIterator<PointInputIterator>)),
      //     (void) )
      //   myX.insert( PointInputIterator, PointInputIterator );
      myX.insertNew( myPoint );
      ConceptUtils::sameType( mySize, myX.erase( myPoint ) );
      myX.erase( myIterator );
      myX.erase( myIterator, myIterator );
      myX.clear();
      ConceptUtils::sameType( myX, myX.operator+=( myX ) );
      myX.computeComplement( myOutputIt );
      myX.assignFromComplement( myX );
      myX.computeBoundingBox( myPoint, myPoint );
      ConceptUtils::sameType( myIterator, myX.find( myPoint ) );
      ConceptUtils::sameType( myIterator, myX.begin() );
      ConceptUtils::sameType( myIterator, myX.end() );
    }

    // ------------------------- Private Datas --------------------------------
  private:
    T myX; // only if T is default constructible.
    Domain myDomain;
    CowPtr<Domain> myDomainPtr;
    Size mySize;
    bool myBool;
    Point myPoint;
    Iterator myIterator;
    ConstIterator myConstIterator;
    Point* myOutputIt; 
    // ------------------------- Internals ------------------------------------
  private:
    
  }; // end of concept CDigitalSet
  }  
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDigitalSet_h

#undef CDigitalSet_RECURSES
#endif // else defined(CDigitalSet_RECURSES)
