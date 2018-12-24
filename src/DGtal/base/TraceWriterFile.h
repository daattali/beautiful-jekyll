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
 * @file TraceWriterFile.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/02/17
 * 
 * Header file for module TraceWriterFile.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(TraceWriterFile_RECURSES)
#error Recursive header files inclusion detected in TraceWriterFile.h
#else // defined(TraceWriterFile_RECURSES)
/** Prevents recursive inclusion of headers. */
#define TraceWriterFile_RECURSES

#if !defined TraceWriterFile_h
/** Prevents repeated inclusion of headers. */
#define TraceWriterFile_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <string>
#include "DGtal/base/TraceWriter.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal 
{
  
  /////////////////////////////////////////////////////////////////////////////
  // class TraceWriterFile
  /** 
   * Description of class 'TraceWriterFile' <p>
   * Aim: 
   */
  class TraceWriterFile: public TraceWriter
  {
    // ----------------------- Standard services ------------------------------
  public:

    
    /**
     * Constructor.
     * @param aoutputStream the current output Stream 
     *
     */
    TraceWriterFile(std::ostream &aoutputStream) : TraceWriter(aoutputStream) {};
  



    /**
     * Destructor. 
     */
    ~TraceWriterFile() {};

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
     * Create a Warning Prefix
     * @return the prefix
     */
    std::string  prefixWarning() {return "[WRG]";}

    /**
     * Create an Info Prefix
     * @return the prefix
     */
    std::string  prefixInfo()  {return "";}
    
    /**
     * Create an Error Prefix
     * @return the prefix
     */
    std::string  prefixError() {return "[ERR]";}

    /**
     * Create an Emphase Prefix
     * @return the prefix
     */
    std::string  prefixEmphase() {return "";}
    
    /**
     * Create an Reset postfix
     * @return the postix
     */
    std::string  postfixReset() {return "";}

   
  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    TraceWriterFile( const TraceWriterFile & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    TraceWriterFile & operator=( const TraceWriterFile & other );
  
  }; // end of class TraceWriterFile


  /**
   * Overloads 'operator<<' for displaying objects of class 'TraceWriterFile'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'TraceWriterFile' to write.
   * @return the output stream after the writing.
   */
  std::ostream&
  operator<<( std::ostream & out, const TraceWriterFile & object );

  
} // namespace DGtal



//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined TraceWriterFile_h

#undef TraceWriterFile_RECURSES
#endif // else defined(TraceWriterFile_RECURSES)
