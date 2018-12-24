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
 * @file TraceWriter.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/02/17
 * 
 * Header file for module TraceWriter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(TraceWriter_RECURSES)
#error Recursive header files inclusion detected in TraceWriter.h
#else // defined(TraceWriter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define TraceWriter_RECURSES

#if !defined TraceWriter_h
/** Prevents repeated inclusion of headers. */
#define TraceWriter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <ostream>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal 
{
  
  /////////////////////////////////////////////////////////////////////////////
  // class TraceWriter
  /** 
   * Description of class 'TraceWriter' <p>
   * Aim: @brief Virtual Class to implement trace writers.
   *
   * @see testTrace.cpp
   */
  class TraceWriter
  {
    // ----------------------- Standard services ------------------------------
  public:

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


    virtual std::string  prefixWarning() = 0;
    virtual std::string  prefixInfo() = 0;
    virtual std::string  prefixError() = 0;
    virtual std::string  prefixEmphase() = 0;
    virtual std::string  postfixReset() = 0;
    
    std::ostream & outputStream() {return myOutputStream;};

    // ------------------------- Protected Datas ------------------------------
  protected:

    ///Reference to the  output stream
    std::ostream &myOutputStream;


    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
  TraceWriter(std::ostream &aoutputStream) : myOutputStream(aoutputStream) {};
  



  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    TraceWriter( const TraceWriter & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    TraceWriter & operator=( const TraceWriter & other );
  
    // ------------------------- Internals ------------------------------------
  private:
  
  }; // end of class TraceWriter


  /**
   * Overloads 'operator<<' for displaying objects of class 'TraceWriter'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'TraceWriter' to write.
   * @return the output stream after the writing.
   */
  std::ostream&
  operator<<( std::ostream & out, const TraceWriter & object );

  
} // namespace DGtal

                                                                    //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined TraceWriter_h

#undef TraceWriter_RECURSES
#endif // else defined(TraceWriter_RECURSES)
