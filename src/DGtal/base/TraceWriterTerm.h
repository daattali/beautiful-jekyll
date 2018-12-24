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
 * @file TraceWriterTerm.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/02/17
 * 
 * Header file for module TraceWriterTerm.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(TraceWriterTerm_RECURSES)
#error Recursive header files inclusion detected in TraceWriterTerm.h
#else // defined(TraceWriterTerm_RECURSES)
/** Prevents recursive inclusion of headers. */
#define TraceWriterTerm_RECURSES

#if !defined TraceWriterTerm_h
/** Prevents repeated inclusion of headers. */
#define TraceWriterTerm_h


//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <string>
#include "DGtal/base/TraceWriter.h"
#include "DGtal/base/Config.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal 
{
  
  /////////////////////////////////////////////////////////////////////////////
  // class TraceWriterTerm
  /** 
   * Description of class 'TraceWriterTerm' <p>
   * Aim: @brief Implements trace prefix for color terminals
   *
   * \todo Detect if the terminal has color capabilities
   * 
   * @see testTrace.cpp
   */
  // ----------------------- Standard services ------------------------------
  class TraceWriterTerm: public TraceWriter
  {
  public:
     
    /**
     * Constructor.
     * @param aoutputStream the current output Stream 
     *
     */
    TraceWriterTerm(std::ostream &aoutputStream=std::cerr) : TraceWriter(aoutputStream) {};
    

    /**
     * Destructor. 
     */
    ~TraceWriterTerm() {};

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    
    /**
     * Create a Wrarning Prefix
     *
     * @return the prefix
     */
    std::string  prefixWarning() 
    {
#if ( !defined(DGTAL_NO_ESCAPED_CHAR_IN_TRACE) && (defined(UNIX)||defined(unix)||defined(linux)) )
      return "\033[0m\033[35m";
#else
      return "";
#endif
    }
    
    /**
     * Create an Info Prefix
     * @return the prefix
     */
    std::string  prefixInfo()  
    {
#if ( !defined(DGTAL_NO_ESCAPED_CHAR_IN_TRACE) && (defined(UNIX)||defined(unix)||defined(linux)) )
      return "\033[0m";
#else
      return "";
#endif
    }

    /**
     * Create an Error Prefix
     * @return the prefix
     */
    std::string  prefixError() 
    {
#if ( !defined(DGTAL_NO_ESCAPED_CHAR_IN_TRACE) && (defined(UNIX)||defined(unix)||defined(linux)) )
      return "\033[0m\033[31m[ERR]";
#else
      return "";
#endif
    }
    
    /**
     * Create an Emphase Prefix
     * @return the prefix
     */
    std::string  prefixEmphase() 
    {
#if ( !defined(DGTAL_NO_ESCAPED_CHAR_IN_TRACE) && (defined(UNIX)||defined(unix)||defined(linux)) )
      return "\033[0m\033[1m";
#else
      return "";
#endif
    }

    /**
     * Create a Reset postfix
     * @return the postfix
     */
    std::string  postfixReset() 
    {
#if ( !defined(DGTAL_NO_ESCAPED_CHAR_IN_TRACE) && (defined(UNIX)||defined(unix)||defined(linux)) )
      return "\033[0m";
#else
      return "";
#endif
    }
   
  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    TraceWriterTerm( const TraceWriterTerm & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    TraceWriterTerm & operator=( const TraceWriterTerm & other );
 
  }; // end of class TraceWriterTerm


  /**
   * Overloads 'operator<<' for displaying objects of class 'TraceWriterTerm'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'TraceWriterTerm' to write.
   * @return the output stream after the writing.
   */
  std::ostream&
  operator<<( std::ostream & out, const TraceWriterTerm & object );

  
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined TraceWriterTerm_h

#undef TraceWriterTerm_RECURSES
#endif // else defined(TraceWriterTerm_RECURSES)
