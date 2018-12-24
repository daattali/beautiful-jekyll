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
 * @file LatticePolytope2D.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 * @author Emilie Charrier
 *
 * @date 2012/04/19
 *
 * Header file for module LatticePolytope2D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(LatticePolytope2D_RECURSES)
#error Recursive header files inclusion detected in LatticePolytope2D.h
#else // defined(LatticePolytope2D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define LatticePolytope2D_RECURSES

#if !defined LatticePolytope2D_h
/** Prevents repeated inclusion of headers. */
#define LatticePolytope2D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CSpace.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/arithmetic/IntegerComputer.h"
#include "DGtal/arithmetic/ClosedIntegerHalfPlane.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class LatticePolytope2D
  /**
     Description of template class 'LatticePolytope2D' <p> \brief Aim:
     Represents a 2D polytope, i.e. a convex polygon, in the
     two-dimensional digital plane. The list of points must follow the
     \b clockwise ordering.

     It is a model of boost::CopyConstructible,
     boost::DefaultConstructible, boost::Assignable. It is also a
     model of boost::Container (it contains the sequence of
     points). It is also displayable on a Board2D object with two
     modes: "" or "Transparent", "Filled".

     It contains no more data than the sequence of points, except mutable
     data for intermediate computations.

     It is a backport of <a
     href="https://gforge.liris.cnrs.fr/projects/imagene">ImaGene</a>.

     @tparam TSpace an arbitrary 2-dimensional model of CSpace.
     @tparam TSequence a model of boost::Sequence whose elements are points (TSpace::Point). Default is list of points.
   */
  template < typename TSpace, 
             typename TSequence = std::list< typename TSpace::Point > >
  class LatticePolytope2D 
  {
    BOOST_CONCEPT_ASSERT(( concepts::CSpace< TSpace > ));
    BOOST_STATIC_ASSERT(( TSpace::dimension == 2 ));
    BOOST_CONCEPT_ASSERT(( boost::Sequence< TSequence > ));

  public:
    typedef LatticePolytope2D<TSpace,TSequence> Self;
    typedef TSequence ClockwiseVertexSequence;

    typedef TSpace Space;
    typedef typename Space::Integer Integer;
    typedef typename Space::Point Point;
    typedef typename Space::Vector Vector;
    typedef IntegerComputer<Integer> MyIntegerComputer;
    typedef HyperRectDomain< Space > Domain; 
    typedef ClosedIntegerHalfPlane< Space > HalfSpace;

    typedef typename ClockwiseVertexSequence::value_type value_type;
    typedef typename ClockwiseVertexSequence::reference reference;
    typedef typename ClockwiseVertexSequence::const_reference const_reference;
    typedef typename ClockwiseVertexSequence::iterator iterator;
    typedef typename ClockwiseVertexSequence::const_iterator const_iterator;
    typedef typename ClockwiseVertexSequence::const_pointer const_pointer;
    typedef typename ClockwiseVertexSequence::size_type size_type;
    typedef typename ClockwiseVertexSequence::difference_type difference_type;

    typedef typename ClockwiseVertexSequence::value_type Value;
    typedef typename ClockwiseVertexSequence::iterator Iterator;
    typedef typename ClockwiseVertexSequence::const_iterator ConstIterator;
    typedef typename std::size_t Size;
    typedef std::pair<Size,Size> SizeCouple;

    // The sequence must contain points.
    BOOST_STATIC_ASSERT
    (( concepts::ConceptUtils::SameType< Value, Point >::value ));
    
    // Point2I and Point should be the same type.
    typedef typename MyIntegerComputer::Point2I Point2I;
    typedef typename MyIntegerComputer::Vector2I Vector2I;
    typedef typename MyIntegerComputer::Point3I Point3I;
    typedef typename MyIntegerComputer::Vector3I Vector3I;
    BOOST_STATIC_ASSERT(( concepts::ConceptUtils::SameType< Point2I, Point >::value ));
    BOOST_STATIC_ASSERT(( concepts::ConceptUtils::SameType< Vector2I, Vector >::value ));

    // ----------------------- Standard services ------------------------------
  public:

    /**
       Destructor.
     */
    ~LatticePolytope2D();

    /**
     * Constructor.
     */
    LatticePolytope2D();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    LatticePolytope2D ( const Self & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    Self & operator= ( const Self & other );

    /**
       @return the object that performs integer calculation.
    */
    MyIntegerComputer & ic() const;

    /**
       Useful to visit the list of vertices in order.
       @return a const iterator (a forward iterator) pointing on the first vertex.
    */
    ConstIterator begin() const;

    /**
       Useful to visit the list of vertices in order.
       @return a const iterator (a forward iterator) pointing after the last vertex.
    */
    ConstIterator end() const;

    /**
       Useful to visit the list of vertices in order.
       @return an iterator (a forward iterator) pointing on the first vertex.
    */
    Iterator begin();

    /**
       Useful to visit the list of vertices in order.
       @return an iterator (a forward iterator) pointing after the last vertex.
    */
    Iterator end();

    /**
       @return 'true' if the lattice polytope has no vertex, false otherwise.
    */
    bool empty() const;

    /**
       @return the number of vertices (or edges) of the lattice polytope.
    */
    Size size() const;

    /**
       @return the maximal possible number of vertices (or edges) that
       can be stored (here, greatest possible Size integer).
    */
    Size max_size() const;

    /**
       Clears the lattice polytope. Afterwards, it is composed of 0 vertices.
    */
    void clear();

    /**
       Erases the vertex pointed by \a it.
       @param it an iterator pointing on the vertex to erase.
       @return an iterator pointing on the next vertex (the one that follows \a it).
    */
    Iterator erase( Iterator it );

    /**
       @return the bounding domain of this polygon, i.e. the smallest
       bounding box containing all the points of this polygon.
    */
    Domain boundingBoxDomain() const;

    /**
     * Removes (duplicate) consecutive vertices.
     * NB: complexity is O(N), where N is the number of vertices.
     */
    void purge();

    /**
     * Inserts the point K to the lattice polytope before position "pos".
     * @param pos any iterator
     * @param K the point to add
     * @return an iterator on the newly created element.
     *
     * @pre if C_1, ..., C_N is the lattice polytope, then C_1, C_pos-1,
     * K ..., C_N should be the vertices of the output lattice polytope.
     */
    Iterator insertBefore( const Iterator & pos, const Point & K );

    /**
       adds the point K to the end of the polygon.
       @param K the point to add

       @pre if C_1, ..., C_N is the lattice polytope, then C_1, ...,
       C_N, K should be the vertices of the output lattice polytope.
    */
    void pushBack( const Point & K );

    /**
       Adds the point K to the beginning of the polygon (stl version)
       @param K the point to add

       @pre if C_1, ..., C_N is the lattice polytope, then K, C_1, ...,
       C_N should be the vertices of the output lattice polytope.
       @see push_front
    */
    void pushFront( const Point & K );

    /**
       Adds the point K to the end of the polygon (stl version for BackInsertable).
       @param K the point to add

       @pre if C_1, ..., C_N is the lattice polytope, then C_1, ...,
       C_N, K should be the vertices of the output lattice polytope.
       @see pushBack
    */
    void push_back( const Point & K );

    /**
       Adds the point K to the beginning of the polygon (stl version)
       @param K the point to add

       @pre if C_1, ..., C_N is the lattice polytope, then K, C_1, ...,
       C_N should be the vertices of the output lattice polytope.
       @see pushFront
    */
    void push_front( const Point & K );

    /**
     * @return 2*area of polygon.
     */
    const Integer & twiceArea() const;

    /**
     * if the area of this polygon is not 0, computes centroid, else,
     * if the polygon is reduced to 2 points, computes the middle of
     * the straight line segment, else returns the point itself.
     *
     * The centroid is a 2D rational point but it is represented as a
     * 3D integer point (a/d,b/d) corresponds to (a,b,d).
     *
     * @return the centroid. The centroid is \b not in reduced form.
     * @pre The polygon should not be empty.
     *
     * @see centroid( const Integer & ) const
     */
    Point3I centroid() const;
    
    /**
       This form is faster than centroid if you have already computed the area.

       if the area of this polygon is not 0, computes centroid, else,
       if the polygon is reduced to 2 points, computes the middle of
       the straight line segment, else returns the point itself.
     
       The centroid is a 2D rational point but it is represented as a
       3D integer point (a/d,b/d) corresponds to (a,b,d).

       @param twice_area the area*2 of this polygon.
       @return the centroid. The centroid is \b not in reduced form.
       @pre The polygon should not be empty.

       @see centroid() const
     */
    Point3I centroid( const Integer & twice_area ) const;

    /**
       @return the exact number of digital points on the polygon
       boundary (greater or equal to the number of vertices.  NB:
       complexity in O(n log(D) ), where n is the number of vertices.
    */
    Integer numberBoundaryPoints() const;

    /**
       @return the exact number of digital points in the polygon
       interior. 

       Calls numberBoundaryPoints and twiceArea. Uses Pick's formula. 

       NB: complexity in O(n log(D) ), where n is the number of vertices.
    */
    Integer numberInteriorPoints() const;
 
    // ----------------------- halfspace services -------------------------------
  public:

    /**
       Given some half-plane \a hs, finds the edges/vertices of this polygon
       that crosses/borders this half-plane.

       Complexity is O(n), where n is size().

       @param it_next_is_outside (returns) either the vertex that is
       in \a hs and whose successor is not in \a hs, or end() if none
       exists.

       @param it_next_is_inside (returns) either the vertex that is not
       in \a hs and whose successor is in \a hs, or end() if none
       exists.

       @param hs  The half-plane.

       @return the couple (number of vertices that are in \a hs, number of vertices).
     */
    SizeCouple findCut( Iterator & it_next_is_outside, Iterator & it_next_is_inside, 
                        const HalfSpace & hs );

    /**
       Cuts the lattice polytope with the given half-space constraint.
       
       @param hs any half-space constraint.
       @return 'true' if the polygon was modified, 'false' otherwise.

       NB: complexity is O(N) for finding the involved edges, then
       log(D) for applying the cut.
     */
    bool cut( const HalfSpace & hs );

    /**
       Computes the constraint of the form N.P<=c whose supporting
       line passes through point *it and *(it+1), such that the other
       points of the polygon are inside. Parameters of the hafl-space
       are minimal. Complexity is O(log(D)).

       @param it an iterator on a point of this polygon.
       @return the corresponding half-space.
       @pre the polygon should have at least two vertices.
     */
    HalfSpace halfSpace( ConstIterator it ) const;

    /**
       Computes the constraint of the form N.P<=c whose supporting
       line passes through A and B such that the point \a inP
       satisfies the constraint.
       
       @param A any point.
       @param B any point different from A.
       @param inP any point not on the straight line (AB).
       @return  the corresponding half-space.

       NB: It is not a static method because this method uses the
       internal IntegerComputer object member.
     */
    HalfSpace halfSpace( const Point & A, const Point & B, const Point & inP ) const;


    /**
       Computes the set \a aSet all the digital points that belongs to
       this polygon (interior plus boundary).

       @param aSet (returns) the set that contains as output all the
       digital points of this polygon.

       @todo this method is for now not efficient and is just for
       visualization purposes.
    */
    template <typename DigitalSet>
    void getIncludedDigitalPoints( DigitalSet & aSet ) const;

    // ----------------------- Helper methods ----------------------------------
    
    /**
       Given a point \a inPt on the boundary of \a hs1, computes the
       closest integer points along the boundary of \a hs1 that are
       separated by \a hs2. Either the intersection is exact and the
       returned points lies at this intersection, or \a inPt
       designates the point that satisfies \a hs2 while \a outPt does
       not satisfy \a hs2. The two points are then separated by the
       direction vector of the half-space.

       @param v (returns) the Bezout vector of the direction vector
       between \a inPt and \a outPt.

       @param inPt (in/out) as input, a point on \a hs1, as output, a
       point on \a hs1 satisfying \a hs2. @pre \a inPt must belong to \a hs1.

       @param outPt (returns) a point on \a hs1 not satisfying \a hs2.

       @param hs1 The first half-space.
       @param hs2 The second half-space.

       @return 'true' iff the intersection oh \a hs1 and \a hs2 is
       exact. In this case, outPt is equal to inPt and is at the
       intersection of the two half-space boundaries.
     */
    bool getFirstPointsOfHull( Vector & v, 
                               Point & inPt, // must belong to hs1.
                               Point & outPt,
                               const HalfSpace & hs1,
                               const HalfSpace & hs2 ) const;

    /**
       Computes the border of the upper and of the lower convex hull
       from the starting points inPts[0] (up) and outPts[0]
       down, along the constraint N2.p <= c2 while the vertices
       satisfy the constraint N3.p <= c3. The vertices of the two
       borders are stored at the end of inPts and outPts.
       
       @param inPts (in, out) as input, contains the first point, as
       output the sequence of points satisfying \a hs2 and \a hs3.
       
       @param outPts (in, out) as input, contains the first point, as
       output the sequence of points not satisfying \a hs2 and satisfying
       \a hs3.
       
       @param BV the Bezout vector of the vector between inPts[ 0 ] and outPts[ 0 ].
       
       @param hs2 the half-space that is approached by the two sequences of points.
       @param hs3 the limiting half-space which defines the bounds of
       the approximation.
    */
    void getAllPointsOfHull( std::vector<Point> & inPts,
                             std::vector<Point> & outPts,
                             const Vector & BV, 
                             const HalfSpace & hs2,
                             const HalfSpace & hs3 ) const;

    /**
       Compute the convex hull of grid points satisfying the
       constraints N1.P<=c1, N2.P<=c2 and N3.P>=c3.
       
       N2.P<=c2 corresponds to the cut two parts of computation: from
       constraint 1 to constraint 3 and from constraint 3 to
       constraint 1.
       
       The computed vertices are outputed with the output iterator @a itOut.

       @a pointRefC1 and @a pointRefC3 corresponds to grid point lying on
       the supporting lines of C1 and of C3 resp.
       
     
       NB: the method also computes grid point satisfying N1.P<=c1 and
       N3.P>=c3 but not satisfying N2.P<=c2. The algorithm uses
       these points that's why they appear in the code.

       @param itOut       The output iterator.
       @param pointRefC1  The grid point lying on @a C1.
       @param pointRefC3  The grid point lying on @a C3.
       @param hs1         The first half-space.
       @param hs2         The second half-space.
       @param hs3         The third half-space.

       @todo proper parameters documentation.
    */
    template <typename OutputIterator>
    OutputIterator computeConvexHullBorder( OutputIterator itOut,
                                            const Point & pointRefC1, 
                                            const Point & pointRefC3,
                                            const HalfSpace & hs1,
                                            const HalfSpace & hs2,
                                            const HalfSpace & hs3 ) const;

    /**
       Swaps the content of this object with other. O(1) complexity.
       @param other any other LatticePolytope2D.
    */
    void swap( LatticePolytope2D & other );

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

    /**
     * @return the class name. It is notably used for drawing this object.
     */
    std::string className() const;


    // ------------------------- Protected Datas ------------------------------
  protected:
    // The (circular) sequence of vertices along the lattice polytope.
    // The vertices are ordered \b clockwise.
    ClockwiseVertexSequence myVertices;

    // ------------------------- Private Datas --------------------------------
  private:
    /// A utility object to perform computation on integers. Need not
    /// to be copied when cloning this object. Avoids many dynamic
    /// allocations when using big integers.
    mutable MyIntegerComputer _ic;
    mutable Integer _a, _b, _c, _c1, _c3, _den, _g, _fl, _ce;
    mutable Point _A, _B, _A1, _B1, _A2, _B2;
    mutable Vector _N, _DV, _u, _v;
    mutable std::vector<Point> _inPts, _outPts;

    // ------------------------- Hidden services ------------------------------
  protected:

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class LatticePolytope2D


  /**
   * Overloads 'operator<<' for displaying objects of class 'LatticePolytope2D'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'LatticePolytope2D' to write.
   * @return the output stream after the writing.
   */
  template <typename TSpace, typename TSequence>
  std::ostream&
  operator<< ( std::ostream & out, 
               const LatticePolytope2D<TSpace,TSequence> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/arithmetic/LatticePolytope2D.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined LatticePolytope2D_h

#undef LatticePolytope2D_RECURSES
#endif // else defined(LatticePolytope2D_RECURSES)
