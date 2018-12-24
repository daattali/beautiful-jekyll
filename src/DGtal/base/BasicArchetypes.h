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
 * @file BasicArchetypes.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2011/09/02
 *
 * Header file for concept BasicArchetypes.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(BasicArchetypes_RECURSES)
#error Recursive header files inclusion detected in BasicArchetypes.h
#else // defined(BasicArchetypes_RECURSES)
/** Prevents recursive inclusion of headers. */
#define BasicArchetypes_RECURSES

#if !defined BasicArchetypes_h
/** Prevents repeated inclusion of headers. */
#define BasicArchetypes_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // List of basic archetypes, grouped in this file.

 
  /**
     Description of \b archetype '\b CSinglePassIteratorArchetype' <p>
     @ingroup Archetypes
     @brief An archetype of SingePassIterator.
  */
  template <typename T> 
  struct CSinglePassIteratorArchetype : 
    public boost::input_iterator_archetype<T>
  {};

  /**
     Description of \b archetype '\b CBidirectionalIteratorArchetype' <p>
     @ingroup Archetypes
     @brief An archetype of BidirectionalIterator.
  */
  template <typename T> 
  struct CBidirectionalIteratorArchetype : 
    public boost::mutable_bidirectional_iterator_archetype<T>
  {};

  /**
     Description of \b archetype '\b CConstBidirectionalIteratorArchetype' <p>
     @ingroup Archetypes
     @brief An archetype of ConstBidirectionalIterator.
  */
  template <typename T> 
  struct CConstBidirectionalIteratorArchetype : 
    public boost::bidirectional_iterator_archetype<T>
  {};

  // {
  //   CBidirectionalIteratorArchetype( const boost::mutable_bidirectional_iterator_archetype<T> & ) {}
  //   CBidirectionalIteratorArchetype &
  //   operator=( const boost::mutable_bidirectional_iterator_archetype<T> & ) 
  //   { return *this; }
  // };

  /**
     Description of \b archetype '\b CForwardIteratorArchetype' <p>
     @ingroup Archetypes
     @brief An archetype of ForwardIterator.
  */
  template <typename T> 
  struct CForwardIteratorArchetype 
    : public boost::forward_iterator_archetype<T>
  {};
  
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined BasicArchetypes_h

#undef BasicArchetypes_RECURSES
#endif // else defined(BasicArchetypes_RECURSES)
