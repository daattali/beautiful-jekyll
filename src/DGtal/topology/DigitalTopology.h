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
 * @file DigitalTopology.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/07
 *
 * Header file for module DigitalTopology.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DigitalTopology_RECURSES)
#error Recursive header files inclusion detected in DigitalTopology.h
#else // defined(DigitalTopology_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DigitalTopology_RECURSES

#if !defined DigitalTopology_h
/** Prevents repeated inclusion of headers. */
#define DigitalTopology_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/topology/CAdjacency.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /**
   * Possible properties of digital topologies.
   */
  enum DigitalTopologyProperties { UNKNOWN_DT = 0, 
           NOT_JORDAN_DT = 1,
           JORDAN_DT = 2 };

  /////////////////////////////////////////////////////////////////////////////
  // template class DigitalTopology
  /**
   * Description of template class 'DigitalTopology' <p> \brief Aim:
   * Represents a digital topology as a couple of adjacency relations.
   *
   * The most famous are the (4,8) and (8,4) topologies on Z^2 (see
   * seminal Rosenfeld paper). The two given adjacency relations
   * should be defined for all digital points used afterwards. For
   * instance, they should operate on points of the same dimension.
   * The first adjacency defines the foreground topology while the
   * second adjacency defines the background topology. The opposite
   * topology is the reverse couple. Both adjacencies should be
   * instantiable.
   *
   * A digital topology is classically denoted by a couple
   * \f$ (\kappa,\lambda) \f$, which explains the notations in the class.
   *
   * @code
   typedef SpaceND< int, 2 > Zi2;
   typedef MetricAdjacency< Zi2, 1 > Adj4;
   typedef MetricAdjacency< Zi2, 2 > Adj8;
   Adj4 adj4;
   Adj8 adj8;
   typedef DigitalTopology< Adj4, Adj8 > DT48;
   typedef DT48::ReverseTopology DT84;
   DT48 dt( adj4, adj8, JORDAN_DT );
   cout << dt << std::endl;
   DT84 opp_dt = dt.reverseTopology();
   cout << opp_dt << std::endl;
   * @endcode
   *
   * @tparam TForegroundAdjacency any model of CAdjacency.
   * @tparam TBackgroundAdjacency any model of CAdjacency.
   */
  template <typename TForegroundAdjacency, typename TBackgroundAdjacency>
  class DigitalTopology
  {
    // ----------------------- Standard services ------------------------------
  public:
    typedef TForegroundAdjacency ForegroundAdjacency;
    typedef TBackgroundAdjacency BackgroundAdjacency;
    typedef typename ForegroundAdjacency::Point Point;
    // should be the same as Point.
    typedef typename BackgroundAdjacency::Point BackPoint; 
    
    BOOST_CONCEPT_ASSERT(( concepts::CAdjacency< ForegroundAdjacency > ));
    BOOST_CONCEPT_ASSERT(( concepts::CAdjacency< BackgroundAdjacency > ));
    
    /**
     * Opposite topology type.
     */
    typedef DigitalTopology<BackgroundAdjacency,ForegroundAdjacency> 
    ReverseTopology;


    /**
     * Defines the digital topology (kappa,lambda).
     *
     * @param aKappa a const reference to the adjacency object chosen
     * for the foreground topology.
     *
     * @param aLambda a const reference to the adjacency object chosen
     * for the background topology.
     *
     * @param props an hint of the properties of this digital
     * topology, default is UNKNOWN.
     */
    DigitalTopology( ConstAlias<ForegroundAdjacency> aKappa, 
         ConstAlias<BackgroundAdjacency> aLambda,
         DigitalTopologyProperties props = UNKNOWN_DT );

    /**
     * Destructor.
     */
    ~DigitalTopology();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    DigitalTopology ( const DigitalTopology & other );


    /**
     * @return a const reference to the foreground connectedness.
     */
    const ForegroundAdjacency & kappa() const;

    /**
     * @return a const reference to the background connectedness.
     */
    const BackgroundAdjacency & lambda() const;

    /**
     * @return JORDAN iff the topology is Jordan, NOT_JORDAN iff the
     * topology is known to be NOT_JORDAN, UNKNOWN otherwise.
     */
    DigitalTopologyProperties properties() const;

    /**
     * @return a digital topology object which is the reverse
     * topology of this (ie. \f[ (\lambda,\kappa) \f].
     */
    ReverseTopology reverseTopology() const;

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    /**
     * a const reference to the adjacency object chosen for the
     * foreground topology.
     */
    const ForegroundAdjacency & myKappa;

    /**
     * a const reference to the adjacency object chosen for the
     * background topology.
     */
    const BackgroundAdjacency & myLambda;

    /**
     * an hint of the properties of this digital topology, default is
     * UNKNOWN.
     */
    const DigitalTopologyProperties myProps;

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    DigitalTopology();

  private:

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    DigitalTopology & operator= ( const DigitalTopology & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class DigitalTopology


  /**
   * Overloads 'operator<<' for displaying objects of class 'DigitalTopology'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'DigitalTopology' to write.
   * @return the output stream after the writing.
   */
  template <typename TForegroundAdjacency, typename TBackgroundAdjacency>
  std::ostream&
  operator<< ( std::ostream & out, 
         const DigitalTopology<TForegroundAdjacency,TBackgroundAdjacency> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/DigitalTopology.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DigitalTopology_h

#undef DigitalTopology_RECURSES
#endif // else defined(DigitalTopology_RECURSES)
