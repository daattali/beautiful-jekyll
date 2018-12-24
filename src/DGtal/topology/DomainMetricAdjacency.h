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
 * @file DomainMetricAdjacency.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/10
 *
 * Header file for module DomainMetricAdjacency.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DomainMetricAdjacency_RECURSES)
#error Recursive header files inclusion detected in DomainMetricAdjacency.h
#else // defined(DomainMetricAdjacency_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DomainMetricAdjacency_RECURSES

#if !defined DomainMetricAdjacency_h
/** Prevents repeated inclusion of headers. */
#define DomainMetricAdjacency_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace deprecated
  {
    /////////////////////////////////////////////////////////////////////////////
    // template class DomainMetricAdjacency
    /**
     * Description of template class 'DomainMetricAdjacency' <p>
     * \brief Aim:
     * Describes digital adjacencies in a digital domain that are defined
     * with the 1-norm and the infinity-norm.
     *
     * It induces the classical 4 and 8 adjacencies in 2D, the 6, 18 and
     * 26 adjacencies in 3D, and the \f$ \omega \f$ and \f$ \alpha \f$
     * adjacencies in nD.
     *
     * \b Model of a CAdjacency.
     *
     * @tparam Domain any domain of a digital space (see concept CDomain).
     *
     * @tparam maxNorm1 defines which points are adjacent. More
     * precisely, two points are adjacent iff their norm-infinity is
     * less or equal than 1 and if their norm-1 is less or equal than
     * maxNorm1.
     *
     */
    template <typename Domain, Dimension maxNorm1, 
        Dimension dimension = Domain::Space::dimension >
    class DomainMetricAdjacency
    {
      BOOST_CONCEPT_ASSERT(( concepts::CDomain<Domain> ));
      // ----------------------- public types ------------------------------
    public:
      typedef typename Domain::Space Space;
      typedef typename Space::Point Point;
      typedef typename Space::Vector Vector;

      // ----------------------- Standard services ------------------------------
    public:

      /**
       * Constructor from domain.
       * @param aDomain any domain.
       */
      DomainMetricAdjacency( ConstAlias<Domain> aDomain );

      /**
       * Copy constructor.
       * @param other the object to clone.
       */
      DomainMetricAdjacency ( const DomainMetricAdjacency & other );

      /**
       * Destructor.
       */
      ~DomainMetricAdjacency();

      // ----------------------- Adjacency services -----------------------------
    public:

      /**
       * @param p1 any point in this space.
       * @param p2 any point in this space.
       *
       * @return 'true' iff p1 is adjacent to p2 according to this
       * adjacency relation.
       */
      bool isAdjacentTo( const Point & p1, const Point & p2 ) const; 

      /**
       * @param p1 any point in this space.
       * @param p2 any point in this space.
       *
       * @return 'true' iff p1 is adjacent to p2 according to this
       * adjacency relation and p1 != p2.
       */
      bool isProperlyAdjacentTo( const Point & p1, const Point & p2 ) const; 

      /**
       * Outputs the whole neighborhood of point [p] as a sequence of
       * *out_it++ = ...
       *
       * @tparam OutputIterator any output iterator (like
       * std::back_insert_iterator< std::vector<int> >).
       *
       * @param p any point of this space.
       * @param out_it any output iterator.
       */
      template <typename OutputIterator>
      void writeNeighborhood( const Point & p, OutputIterator & out_it ) const;

      /**
       * Outputs the whole proper neighborhood of point [p] (thus
       * without [p] itself) as a sequence of *out_it++ = ...
       *
       * @tparam OutputIterator any output iterator (like
       * std::back_insert_iterator< std::vector<int> >).
       *
       * @param p any point of this space.
       * @param out_it any output iterator.
       */
      template <typename OutputIterator>
      void writeProperNeighborhood( const Point & p, 
            OutputIterator & out_it ) const;

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
       * The associated domain.
       */
      const Domain & myDomain;

      // ------------------------- Hidden services ------------------------------
    protected:

      /**
       * Constructor.
       * Forbidden by default (protected to avoid g++ warnings).
       */
      DomainMetricAdjacency();

    private:


      /**
       * Assignment.
       * @param other the object to copy.
       * @return a reference on 'this'.
       * Forbidden by default.
       */
      DomainMetricAdjacency & operator= ( const DomainMetricAdjacency & other );

      // ------------------------- Internals ------------------------------------
    private:

    }; // end of class DomainMetricAdjacency


    /**
     * Overloads 'operator<<' for displaying objects of class 'DomainMetricAdjacency'.
     * @param out the output stream where the object is written.
     * @param object the object of class 'DomainMetricAdjacency' to write.
     * @return the output stream after the writing.
     */
    template <typename Domain, Dimension maxNorm1>
    std::ostream&
    operator<< ( std::ostream & out, 
     const DomainMetricAdjacency< Domain, maxNorm1,
     Domain::Space::dimension > & object );
  } //deprecated
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/DomainMetricAdjacency.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DomainMetricAdjacency_h

#undef DomainMetricAdjacency_RECURSES
#endif // else defined(DomainMetricAdjacency_RECURSES)
