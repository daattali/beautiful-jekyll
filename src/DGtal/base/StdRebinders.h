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
 * @file StdRebinders.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/03/29
 *
 * This files contains type rebinders for standard types.
 *
 * This file is part of the DGtal library.
 */

#if defined(StdRebinders_RECURSES)
#error Recursive header files inclusion detected in StdRebinders.h
#else // defined(StdRebinders_RECURSES)
/** Prevents recursive inclusion of headers. */
#define StdRebinders_RECURSES

#if !defined StdRebinders_h
/** Prevents repeated inclusion of headers. */
#define StdRebinders_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <map>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /**
     Rebinder for map type std::map. Use inner type Type. Useful when
     passing a templated map type as a template argument.

     @code
     template <typename TMap>
     class Example {
       struct Key { ... };
       struct Node { ... };
       typedef typename TMap:: template Rebinder<Key, Node>::Type MapKeyToNode;
       ...
       MapKeyToNode myMap;
     };

     main() 
     {
       Example<StdMapRebinder> example;
       ...
     }
     @endcode
  */
  struct StdMapRebinder
  {
    template <typename Key, typename Value>
    struct Rebinder {
      typedef std::map<Key, Value> Type;
    };
  };

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined StdRebinders_h

#undef StdRebinders_RECURSES
#endif // else defined(StdRebinders_RECURSES)
