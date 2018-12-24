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
 * @file Trace.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2009/12/19
 *
 * Header file for module Trace.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Trace_RECURSES)
#error Recursive header files inclusion detected in Trace.h
#else // defined(Trace_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Trace_RECURSES

#if !defined Trace_h
/** Prevents repeated inclusion of headers. */
#define Trace_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <ostream>
#include <string>
#include <stack>

#include "DGtal/base/Config.h"
#include "DGtal/base/Clock.h"
#include "DGtal/base/TraceWriter.h"
#include "DGtal/base/TraceWriterTerm.h"
//////////////////////////////////////////////////////////////////////////////


namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class Trace
  /**
   * Description of class 'Trace' <p>
   * Aim: @brief implementation of basic methods to trace out messages with indentation levels.
   *
   * Trace objects use a TraceWriter to switch between terminal and file outputs.
   * Methods postfixed with "Debug" contain no code if the compilation flag DEBUG is not set.
   *
   *
   * For usage examples, see the testtrace.cpp file.
   *
   * @see testTrace.cpp
   *
   * \todo Create a default constructor on TraceWriterTerm(std::cerr)
   */
  class Trace
  {
    // ----------------------- Standard services ------------------------------
  public:

    /// Pattern to be used to indent the messages.
#define TRACE_PATTERN "  "
#define PROGRESSBARWIDTH 60


    /**
     * Constructor.
     *
     * @param writer  the output writer that will receive the traces.
     *
     */
    Trace(TraceWriter & writer);


    /**
     * Destructor.
     */
    ~Trace();

   /**
    * Reset all the variables of the Trace object (indentation level and keyword stack)
    *
    */
   void reset();



    /**
     * Enter a new block and increase the indentation level
     * @param keyword contains a label to the new block
     *
     */
    void beginBlock(const std::string &keyword = "");

    /**
     * Leave a current block, decrease the indentation level and display the associate keyword
     *
     * @return  the ellapsed time in the block in milliseconds (Class Clock).
     */
    double endBlock();

    /**
     * Create a string with an indentation prefix for a normal trace.
     * @return the cerr output stream with the prefix
     */
    std::ostream & info();

    /**
     * Create a string with an indentation prefix for a warning trace.
     *  the string is postfixed by the keyword "[WRNG]"
     * @return the cerr output stream with the prefix
     */
     std::ostream & warning();


    /**
     * Create a string with an indentation prefix for an error trace.
     *  the string is postfixed by the keyword "[ERR]"
     * @return the cerr output stream with the prefix
     */
    std::ostream &  error();


    /**
     * Create a string with an indentation prefix for an emphased trace.
     *
     * @return the cerr output stream with the prefix
     */
    std::ostream &  emphase();

    /**
     * Display a progress bar in the terminal.
     *
     * @param currentValue current step of the progress bar
     * @param maximalValue expected maximal value (must be >0)
     */
    void progressBar(const double currentValue,
                     const double maximalValue);


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

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    ///The indentation level
    unsigned int myCurrentLevel;
    ///The indentation prefix string
    std::string myCurrentPrefix;

    ///A stack to store the block keywords
    std::stack<std::string> myKeywordStack;

    ///A reference to the output writer
    TraceWriter &myWriter;

    ///A stack to store the block clocks
    std::stack<Clock*> myClockStack;

    ///Progress bar current position
    int myProgressBarCurrent;

    ///Progress bar rotation position
    unsigned int myProgressBarRotation;

    ///True if the style has changed
    bool myStyle;

    // ------------------------- Hidden services ------------------------------
  protected:

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    Trace( const Trace & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    Trace & operator=( const Trace & other );




    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Trace


  /**
   * Overloads 'operator<<' for displaying objects of class 'Trace'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Trace' to write.
   * @return the output stream after the writing.
   */
  std::ostream&
  operator<<( std::ostream & out, const Trace & object );


} // namespace DGtal

#include "DGtal/base/Assert.h"

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions
#include "DGtal/base/Trace.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Trace_h

#undef Trace_RECURSES
#endif // else defined(Trace_RECURSES)
