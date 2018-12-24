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
 * @file Clock.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2009/12/11
 *
 * Header file for module Clock.cpp
 *
 * This file is part of the DGtal library (backported from Imagene)
 */

#ifdef Clock_RECURSES
#error Recursive header files inclusion detected in Clock.h
#else // defined(Clock_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Clock_RECURSES

#ifndef Clock_h
/** Prevents repeated inclusion of headers. */
#define Clock_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <cstdlib>

#if ( (defined(UNIX)||defined(unix)||defined(linux)) )
#include <sys/time.h>
#include <time.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#ifdef WIN32
#include <time.h>
#endif



//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class Clock
  /**
   * Description of class 'Clock' <p>
   * Aim: To provide functions to start and stop a timer. Is useful to get
   * performance of algorithms.
   *
   * The following code snippet demonstrates how to use \p Clock
   *
   *  \code
   *  #include <DGtal/base/Clock.h>
   *
   *   Clock c;
   *   long duration;
   *
   *   c.startClock();
   *   ...
   *   //do something
   *   ...
   *   duration = c.stopClock();
   *
   *   std::cout<< "Duration in ms. : "<< duration <<endl;
   *  \endcode
   *
   * @see testClock.cpp
   */
  class Clock
  {
    // ----------------------- Standard services ------------------------------
    // -------------------------- timing services -------------------------------
  public:
    /**
    * Starts a clock.
    */
    void startClock();

    /**
     * Stops the clock.
     * @return the time (in ms) since the last 'startClock()' or 'restartClock()'.
     */
    double stopClock() const;

    /**
     * Restart the clock.
     * @return the time (in ms) since the last 'startClock()' or 'restartClock()'.
     */
    double restartClock();

    /**
     * Constructor.
     *
     */
    Clock();

    /**
     * Destructor.
     */
    ~Clock();

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

    // ------------------------- Private Datas --------------------------------
  private:

    ///internal timer object;
#ifdef WIN32
    clock_t myFirstTick;
#else
    struct timespec myTimerStart;
#endif

  }; // end of class Clock


  /**
   * Overloads 'operator<<' for displaying objects of class 'Clock'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Clock' to write.
   * @return the output stream after the writing.
   */
  inline
  std::ostream&
  operator<<( std::ostream & out, const Clock & object )
    {
      object.selfDisplay( out );
      return out;
    }


} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////
// Inline methods
#include "DGtal/base/Clock.ih"

#endif // !defined Clock_h

#undef Clock_RECURSES
#endif // else defined(Clock_RECURSES)
