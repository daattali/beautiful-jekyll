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
 * @file Common.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2009/12/10
 *
 * Header file for module Common.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Common_RECURSES)
#error Recursive header files inclusion detected in Common.h
#else // defined(Common_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Common_RECURSES

#if !defined Common_h
#define Common_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions

#ifdef WITH_VISU3D_QGLVIEWER
#include <QGLViewer/qglviewer.h>
#include <QGLWidget>
#include <QKeyEvent>
#endif

#include <iostream>
#include <exception>
#include <algorithm>
#include <boost/version.hpp>
#include <boost/concept_check.hpp>
#include <boost/static_assert.hpp>
#include <boost/concept/assert.hpp>
#include <boost/concept/requires.hpp>
#include <boost/iterator/iterator_concepts.hpp>
#include <boost/concept_archetype.hpp>
#include <boost/static_assert.hpp>

#ifdef _MSC_VER
#define NOMINMAX
#include <windows.h>
#ifdef M_PI
#undef M_PI
#endif

//C++ exception specification ignored except
//to indicate a function is not __declspec(nothrow)
#pragma warning(disable : 4290)
//C++ Perf Warning int <- bool
#pragma warning(disable : 4800)
#endif


#if defined( WIN32 )
#define _USE_MATH_DEFINES
#include <math.h>
#else
#include <cmath>
#endif //win32

// Explicit M_PI definition if needed
// (issue https://github.com/DGtal-team/DGtal/issues/1204)
#ifndef M_PI
#define M_PI           (3.14159265358979323846)
#endif
#ifndef M_PI_2
#define M_PI_2         (1.57079632679489661923)
#endif


#if defined( WIN32 )
#define secured_sprintf sprintf_s
#else
#include <stdio.h>
#define secured_sprintf snprintf
#endif // defined( WIN32 )

#include "DGtal/base/Config.h"
#include "DGtal/base/Trace.h"
#include "DGtal/base/TraceWriterTerm.h"
#include "DGtal/base/TraceWriterFile.h"
#include "DGtal/base/Assert.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/base/BasicTypes.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/base/BasicArchetypes.h"
#include "DGtal/base/Exceptions.h"

//////////////////////////////////////////////////////////////////////////////
namespace DGtal
{

  /**
   * Global static type to represent the dimension in DGtal
   */
  typedef DGtal::uint32_t Dimension;

  /**
   * Global enum definition for orientation.
   */
  enum Orientation { INSIDE = 0, ON = 1, OUTSIDE = 2};

  /**
   * Global enum definition for closest point test (geometry/volumes/distance/..).
   */
  enum Closest { ClosestFIRST = 0, ClosestSECOND = 1, ClosestBOTH = 2};


  /** DGtal Global variables
   *
   **/
  extern TraceWriterTerm traceWriterTerm;
  extern Trace trace;

  class Board2D;

  template < class Space, class KSpace>  class Display3D;


#if defined( WITH_CAIRO )
  template < class Space, class KSpace> class Board3DTo2D;
#endif
#if defined( WITH_VISU3D_QGLVIEWER )
  template < class Space, class KSpace> class Viewer3D;
#endif


#if defined( WITH_CAIRO )
  /**
   * Interface that specifies that an object can draw itself on a
   *  3Dto2D Board
   * (BK)
   */
  struct DrawableWithBoard3DTo2D {
    /**
     * Operation to override. Does nothing by default.
     */
    template < typename S, typename KS>

void setStyle( Board3DTo2D< S, KS> &  ) const {}
    virtual ~DrawableWithBoard3DTo2D() {}
  };
#endif

#if defined( WITH_VISU3D_QGLVIEWER )
  /**
   * Interface that specifies that an object can draw itself on a
   *  3D Viewer
   * (BK)
   */
  struct DrawableWithViewer3D {
    /**
     * Operation to override. Does nothing by default.
     */
    template < typename S, typename KS>
    void setStyle( Viewer3D< S, KS> &  ) const {}
    virtual ~DrawableWithViewer3D() {}
  };
#endif

  /**
   * Interface that specifies that an object can draw itself on a
   *  3DDisplay
   * (BK)
   */
  struct DrawableWithDisplay3D {
    /**
     * Operation to override. Does nothing by default.
     */
    template < typename Sp, typename KSp>
    void setStyle( Display3D< Sp, KSp> &  ) const {}
    virtual ~DrawableWithDisplay3D() {}
  };

  /**
   * Interface that specifies that an object can draw itself on a
   * board.
   * @todo (JOL) Put this class elsewhere.
   */
  struct DrawableWithBoard2D {
    /**
     * Operation to override. Does nothing by default.
     *
     */
    virtual void setStyle( Board2D &  ) const {}
    virtual ~DrawableWithBoard2D() {}
  };

} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Common_h

#undef Common_RECURSES
#endif // else defined(Common_RECURSES)
