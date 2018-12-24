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
 * @file Assert.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/10/30
 *
 * This file is part of the DGtal library.
 */

#if defined(Assert_RECURSES)
#error Recursive header files inclusion detected in Assert.h
#else // defined(Assert_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Assert_RECURSES

#if !defined Assert_h
/** Prevents repeated inclusion of headers. */
#define Assert_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
//////////////////////////////////////////////////////////////////////////////
#include "DGtal/base/Trace.h"
#include <boost/current_function.hpp>
#include <string>

namespace DGtal
{

  /**
  * DGtal Assert function.
  *
  * ASSERT(expr) and ASSERT_MSG(expr, message) are defined and expr is avaluated only when NDEBUG isn't defined.
  * FATAL_ERROR(expr) and FATAL_ERROR_MSG(expr, message) are always defined.
  *
  **/

  extern Trace trace;

#if defined(NDEBUG)
  #define ASSERT(expr) ((void)0)
#else
  inline
  void
  assert_failed(const std::string& expr, const std::string& function, const std::string& file, long int line)
  {
      trace.error()
          << " Assertion Error - assertion (" << expr << ") failed in " << function << ": "
          << file << '(' << line << ")" << std::endl;
      std::abort();
  }
  #define ASSERT(expr) ((expr) ? ((void)0) : ::DGtal::assert_failed(#expr, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#endif


#if defined(NDEBUG)
  #define ASSERT_MSG(expr, msg) ((void)0)
#else
  inline
  void
  assert_failed_message(const std::string& expr, const std::string& message, const std::string& function, const std::string& file, long int line)
  {
      trace.error()
          << " Assertion Error - assertion (" << expr << ") failed in " << function << ": "
          << file << '(' << line << "): " << std::endl << message << std::endl;
      std::abort();
  }
  #define ASSERT_MSG(expr,msg) ((expr) ? ((void)0) : ::DGtal::assert_failed_message(#expr, msg, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#endif

  inline
  void
  fatal_error_failed(const std::string& expr, const std::string& function, const std::string& file, long int line)
  {
      trace.error()
          << " Fatal Error - assertion (" << expr << ") failed in " << function << ": "
          << file << '(' << line << ")" << std::endl;
      std::abort();
  }
#define FATAL_ERROR(expr) ((expr) ? ((void)0) : ::DGtal::fatal_error_failed(#expr, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))

  inline
  void
  fatal_error_failed_message(const std::string& expr, const std::string& message, const std::string& function, const std::string& file, long int line)
  {
      trace.error()
          << " Fatal Error - assertion (" << expr << ") failed in " << function << ": "
          << file << '(' << line << "): " << std::endl << message << std::endl;
      std::abort();
  }
#define FATAL_ERROR_MSG(expr,msg) ((expr) ? ((void)0) : ::DGtal::fatal_error_failed_message(#expr,msg, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))

} // namespace DGtal

#endif // !defined Assert_h

#undef Assert_RECURSES
#endif // else defined(Assert_RECURSES)
