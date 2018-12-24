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
 * @file Exceptions.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/10/06
 *
 * Header file for module Exceptions.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Exceptions_RECURSES)
#error Recursive header files inclusion detected in Exceptions.h
#else // defined(Exceptions_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Exceptions_RECURSES

#if !defined Exceptions_h
/** Prevents repeated inclusion of headers. */
#define Exceptions_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /**
   * IOException derived class.
   */ 
  class IOException: public std::exception
  {
    virtual const char* what() const noexcept
    {
      return "DGtal IO error";
    }
  };

  /**
   * InputException derived class.
   */ 
  class InputException: public std::exception
  {
    public:
    virtual const char* what() const noexcept
    {
      return "DGtal bad input error";
    }
  };

  /**
   * ConnectivityException derived class.
   */ 
  class ConnectivityException: public std::exception
  {
    public:
    virtual const char* what() const noexcept
    {
      return "DGtal bad connectivity error";
    }
  };

  /**
   * MemoryException derived class.
   */ 
  class MemoryException: public std::exception
  {
    virtual const char* what() const noexcept
    {
      return "DGtal memory error";
    }
  };

  /**
   * InfiniteNumberException derived class.
   */ 
  class InfiniteNumberException: public std::exception
  {
    virtual const char* what() const noexcept
    {
      return "DGtal infinite number error";
    }
  };


} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Exceptions_h

#undef Exceptions_RECURSES
#endif // else defined(Exceptions_RECURSES)
