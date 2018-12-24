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
 * @file ArithmeticalDSS.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/06/28
 *
 * Header file for module ArithmeticalDSS.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ArithmeticalDSS_RECURSES)
#error Recursive header files inclusion detected in ArithmeticalDSS.h
#else // defined(ArithmeticalDSS_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ArithmeticalDSS_RECURSES

#if !defined ArithmeticalDSS_h
/** Prevents repeated inclusion of headers. */
#define ArithmeticalDSS_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/Exceptions.h"

#include "DGtal/geometry/curves/ArithmeticalDSL.h"
#include "DGtal/geometry/curves/ArithmeticalDSSCheck.h"
#include "DGtal/geometry/curves/ArithmeticalDSSFactory.h"
#include "DGtal/geometry/curves/ArithmeticalDSSConvexHull.h"
#include "DGtal/arithmetic/SternBrocot.h"
#include "DGtal/math/linalg/SimpleMatrix.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class ArithmeticalDSS
  /**
   * \brief Aim: This class represents a naive (resp. standard) 
   * digital straight segment (DSS), ie. the sequence of 
   * simply 8- (resp. 4-)connected digital points contained in a 
   * naive (resp. standard) digital straight line (DSL) between 
   * two points of it. 
   * 
   * Obviously, a given DSS belongs to infinitely many DSLs, but one of them has minimal parameters, 
   * ie has a minimal \f$ \omega \f$. ArithmeticalDSS uses this minimal bounding DSL to represent
   * its slope and its intercept.  
   * ArithmeticalDSS stores as data members not only this minimal bounding DSL,
   * but also its ending points as well as the first and last lower and upper leaning points,
   * due to the role that these points play in the update algorithms. 
   * Indeed, ArithmeticalDSS provides some methods to update its internal representation:
   * - ArithmeticalDSS::extendFront and ArithmeticalDSS::extendBack based on 
   * the incremental recognition algorithm of [Debled and Reveilles, 1995 : \cite Debled_1995_ijprai]. 
   * - ArithmeticalDSS::retractFront and ArithmeticalDSS::retractBack based on 
   * [Lachaud et. al., 2007, Th. 5 : \cite LachaudIVC2007]. 
   *
   * See @ref moduleArithDSSReco for further details. See also
   * NaiveDSS8 and StandardDSS4, which are aliases of this class. 
   *
   * @tparam TCoordinate a model of integer for the DGtal point coordinates and 
   * the slope parameters. 
   * @tparam TInteger a model of integer for the intercepts and the remainders
   * that represents a larger range of integers than TCoordinate. 
   *
   * This class is a model of CPointFunctor and of CConstBidirectionalRange. 
   *
   * @see ArithmeticalDSL NaiveDSL StandardDSL 
   * @see exampleArithmeticalDSL.cpp exampleArithmeticalDSS.cpp
   */
  template <typename TCoordinate, 
	    typename TInteger = TCoordinate, 
	    unsigned short adjacency = 8>
  class ArithmeticalDSS
  {
    friend class ArithmeticalDSSFactory<TCoordinate, TInteger, adjacency>; 

    // ----------------------- static members -----------------------------------
  public:
    /**
     * Adjacency of the DSL. 
     */
    static const unsigned short foregroundAdjacency = adjacency;
 
    // ----------------------- Inner types -----------------------------------
  public:

    /**
     * Type used for the points coordinates
     * and the slope parameters. 
     */
    typedef TCoordinate Coordinate;
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<Coordinate> )); 
    /**
     * Type used for the intercepts and the remainders. 
     */
    typedef TInteger Integer; 
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<Integer> ));

    /**
     * Type of the bounding DSL. 
     */
    typedef ArithmeticalDSL<Coordinate, Integer, adjacency> DSL; 
    /**
     * Type of digital space. 
     */
    typedef typename DSL::Space Space; 
    /**
     * Type of point. 
     */
    typedef typename DSL::Point Point; 
    /**
     * Type of vector. 
     */
    typedef typename DSL::Vector Vector; 
    /**
     * Type of steps (defined as a STL pair of vectors). 
     */
    typedef typename DSL::Steps Steps; 
    /**
     * Type used for the position of a point in the DSL.
     */
    typedef Coordinate Position;
    /**
     * Type of iterator. 
     */
    typedef typename DSL::ConstIterator ConstIterator; 
    /**
     * Type of reverse iterator. 
     */
    typedef typename DSL::ConstReverseIterator ConstReverseIterator; 

    /**
     * Type of embedded points 
     * @see project
     */
    typedef DGtal::PointVector<2, double> PointD; 

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Simple constructor. 
     * All members of the bounding DSL are set to zero
     * and all point members are set to @a aPoint
     */
    ArithmeticalDSS(const Point& aPoint);

    /**
     * Constructor.
     * The user gives all the (redondant) parameters and 
     * should be sure that the resulting DSS is valid. 
     *
     * @see isValid
     *
     * @param aA y-component of the direction vector
     * @param aB x-component of the direction vector
     * @param aLowerBound lower intercept
     * @param aUpperBound upper intercept
     * @param aF the first point
     * @param aL the last point
     * @param aUf the first upper point
     * @param aUl the last upper point
     * @param aLf the first lower point
     * @param aLl the last lower point
     * @param aSteps pair of steps used to iterate over the DSS points
     * @param aShift shift vector 
     */
    ArithmeticalDSS(const Coordinate& aA, const Coordinate& aB, 
		    const Integer& aLowerBound, const Integer& aUpperBound, 
		    const Point& aF, const Point& aL,
		    const Point& aUf, const Point& aUl,
		    const Point& aLf, const Point& aLl, 
		    const Steps& aSteps, const Vector& aShift);

    /**
     * Constructor.
     * The user gives all the (redondant) parameters and 
     * should be sure that the resulting DSS is valid. 
     *
     * @see isValid
     *
     * @param aDSL bounding DSL
     * @param aF the first point
     * @param aL the last point
     * @param aUf the first upper point
     * @param aUl the last upper point
     * @param aLf the first lower point
     * @param aLl the last lower point
     */
    ArithmeticalDSS(const DSL& aDSL, 
		    const Point& aF, const Point& aL,
		    const Point& aUf, const Point& aUl,
		    const Point& aLf, const Point& aLl);
    
    /**
     * Constructor.
     * Minimal set of parameters to build the DSS
     * in constant time. 
     * The user should be sure that the slope is
     * consistent with the position of the leaning 
     * points. 
     *
     * @see isValid
     *
     * @param aA y-component of the direction vector
     * @param aB x-component of the direction vector
     * @param aF the first point
     * @param aL the last point
     * @param aUf the first upper point
     * @param aUl the last upper point
     * @param aLf the first lower point
     * @param aLl the last lower point
     *
     * NB: in O(1)
     */
    ArithmeticalDSS(const Coordinate& aA, const Coordinate& aB,
		    const Point& aF, const Point& aL,
		    const Point& aUf, const Point& aUl,
		    const Point& aLf, const Point& aLl);

    


    /**
     * Construction of a sequence of patterns 
     * (or reversed patterns) from two end points.
     *
     * @param aF the first point
     * @param aL the last point
     * @param areOnTheUpperLine boolean equal to 'true' if the
     * two given end points are upper leaning points (pattern case, default), 
     * 'false' if they are lower leaning points (reversed pattern case).  
     *
     * NB: logarithmic-time in the greatest component of the vector
     * starting from @a aF and pointing to @a aL
     */
    ArithmeticalDSS(const Point& aF, const Point& aL, 
		    const bool& areOnTheUpperLine = true);

    /**
     * Construction as the subsegment of minimal parameters of a given DSL. 
     *
     * @param aDSL bounding DSL
     * @param aF first point of the subsegment
     * @param aL last point of the subsegment
     *
     * NB: logarithmic-time in the greatest component of the direction vector
     * of the subsegment. Uses smartCH algorithm (see Roussillon 2014  \cite RoussillonDGCI2014). 
     * @see ArithmeticalDSSFactory
     */
    ArithmeticalDSS(const DSL& aDSL, const Point& aF, const Point& aL);

    /**
     * Construction as the subsegment of minimal parameters of a greater DSS. 
     *
     * @param aDSS bounding DSS
     * @param aF first point of the subsegment
     * @param aL last point of the subsegment
     *
     * NB: logarithmic-time in the greatest component of the direction vector
     * of the subsegment. Uses reversedSmartCH algorithm (see Roussillon 2014  \cite RoussillonDGCI2014). 
     * @see ArithmeticalDSSFactory
     */
    ArithmeticalDSS(const ArithmeticalDSS& aDSS, const Point& aF, const Point& aL);

    /**
     * Construction from a range of iterator on points. 
     *
     * @param aItb begin iterator
     * @param aIte end iterator
     * @tparam Iterator a model of forward iterator
     *
     * NB: linear-time in the size of the range
     */
    template <typename Iterator>
    ArithmeticalDSS(const Iterator& aItb, const Iterator& aIte);

    /**
     * Copy constructor.
     * @param aOther the object to clone.
     */
    ArithmeticalDSS ( const ArithmeticalDSS & aOther );

    /**
     * Assignment.
     * @param aOther the object to copy.
     * @return a reference on 'this'.
     */
    ArithmeticalDSS& operator= ( const ArithmeticalDSS & aOther );

    /**
     * Returns a copy of '*this' with a reverse orientation, ie. 
     * with parameters -@a myA ,  -@a myB , -@a myUpperBound , -@a myLowerBound
     * and swapped leaning points. 
     * @return the negation of '*this'.
     */
    ArithmeticalDSS negate () const;

    /**
     * Equality.
     * @param aOther the object to compare with.
     * @return 'true' if all the members of the two objects
     * are equal, 'false' otherwise
     */
    bool equalsTo ( const ArithmeticalDSS & aOther ) const;

    /**
     * Equality.
     * @param aOther the object to compare with.
     * @return 'true' the two sets of points that are
     * implicitly defined are equal (without respect to 
     * the orientation), 'false' otherwise
     */
    bool operator== ( const ArithmeticalDSS & aOther ) const;

    /**
     * Difference.
     * @param aOther the object to compare with.
     * @return 'true' the two set of points that are
     * implicitly defined are different, 'false' otherwise
     */
    bool operator!= ( const ArithmeticalDSS & aOther ) const;

    /**
     * Destructor.
     */
    ~ArithmeticalDSS();

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
     *
     * NB: in O( log( max( |@a myA |,| @a myB | ) ) )
     */
    bool isValid() const;

    /**
     * @return the bounding DSL of minimal parameters
     * NB: since we return a const reference, you must
     * copy the result, if you want to keep it beyond 
     * the object's existence. 
     */
    const DSL& dsl() const; 

    /**
     * @return a parameter of the bounding DSL of minimal parameters
     */
    Coordinate a() const; 

    /**
     * @return b parameter of the bounding DSL of minimal parameters
     */
    Coordinate b() const; 

    /**
     * @return mu parameter, 
     * the intercept of the bounding DSL of minimal parameters
     */
    Integer mu() const; 

    /**
     * @return omega parameter, 
     * the thickness of the bounding DSL of minimal parameters
     */
    Integer omega() const; 

    /**
     * @return the shift vector 
     */
    Vector shift() const; 
    /**
     * @return the couple of vectors used to iterate
     * over the DSS point. 
     */
    Steps steps() const; 

    /**
     * @return back point of the DSS, ie. 
     * first visited point equal to * ArithmeticalDSS::begin()
     */
    Point back() const; 

    /**
     * @return front point of the DSS, ie. 
     * last visited point equal to * - - ArithmeticalDSS::end()
     */
    Point front() const; 

    /**
     * @return first upper leaning point of the DSS
     */
    Point Uf() const; 

    /**
     * @return last upper leaning point of the DSS
     */
    Point Ul() const; 

    /**
     * @return first lower leaning point of the DSS
     */
    Point Lf() const; 

    /**
     * @return last lower leaning point of the DSS
     */
    Point Ll() const; 

    /**
     * Returns the remainder of @a aPoint
     * (which does not necessarily belong to the DSS)
     * @return remainder of @a aPoint
     * @param aPoint any point
     */
    Integer remainder(const Point& aPoint) const; 

    /**
     * Returns the position of @a aPoint
     * (which does not necessarily belong to the DSS)
     * computed along the direction that is orthogonal 
     * to the direction vector
     * @param aPoint the point whose position is returned 
     * @return the position
     */
    Integer orthogonalPosition(const Point& aPoint) const; 

    /**
     * Returns the position of @a aPoint
     * (which does not necessarily belong to the DSS)
     * computed along the direction given by @a myShift 
     * @param aPoint the point whose position is returned 
     * @return the position
     */
    Position position(const Point& aPoint) const; 

    /**
     * Returns a boolean equal to 'true' if @a aP1 is 
     * located (strictly) before @a aP2 in the direction 
     * orthogonal to @a myShift, 'false' otherwise. 
     * @param aP1 any point
     * @param aP2 any point
     * @return 'true' is @a aP2 is strictly before @a aP2, 
     * 'false' otherwise
     * @see beforeOrEqual position
     */
    bool before (const Point& aP1, const Point& aP2) const; 

    /**
     * Returns a boolean equal to 'true' if @a aP1 is 
     * located before @a aP2 or is equal to @a aP2, 
     * 'false' otherwise. 
     * @param aP1 any point
     * @param aP2 any point
     * @return 'true' is @a aP2 is before or equal to @a aP2, 
     * 'false' otherwise
     * @see before position
     */
    bool beforeOrEqual (const Point& aP1, const Point& aP2) const; 

    /**
     * @return 'true' if @a aPoint is in the DSL
     * of minimal parameters containing this segment, 
     * 'false' otherwise. 
     * @param aPoint any point
     */
    bool isInDSL(const Point& aPoint) const; 

    /**
     * @return 'true' if @a aPoint is in the DSS
     * 'false' otherwise. 
     * @param aPoint any point
     */
    bool isInDSS(const Point& aPoint) const; 
    
    bool operator()(const Point& aPoint) const; 
    
    
    /** 
     * Returns a boolean equal to true if 'this' belongs to the DSL @a aDSL, false otherwise.
     * @return 'true' if 'this' belongs to the DSL @a aDSL.
     * 'false' otherwise.
     * @param aDSL any DSL
     */
    bool isInDSL(const DSL& aDSL) const;

 
    /** 
     * Returns a boolean equal to true if 'this' belongs to the DSL @a
     * aDSL, false otherwise. Also returns extra information about the
     * leaning points included in 'this' or a point outside @a aDSL. 
     * @param [in] aDSL any DSL
     * @param [in,out] Ulp the list of @a aDSL upper leaning points on 'this', if any
     * @param [in,out] Llp the list of @a aDSL lower leaning points on 'this', if any
     * @param [in,out] outP a point of 'this' that does not belong to @a aDSL, if any
     * @return 'true' if 'this' belongs to the DSL @a aDSL.
     * 'false' otherwise.
     */
    bool isInDSL(const DSL& aDSL, std::vector<Point> &Ulp, std::vector<Point> &Llp, Point& outP) const;

    
   
    /** Compute the union of two DSSs. If the union belongs to a DSL,
	returns the DSS of minimal characteristics that includes the two
	DSSs. Otherwise, returns the void DSS (DSS(Point(0,0)). See
	Sivignon 2014  \cite SivignonDGCI2014). 
	
	@param aOther a DSS
	@return a DSS
	
	nb: runs in O(1) when: 1) the union of the two DSSs is
	not part of a DSL, 2) the two DSSs are connected, 3) the last
	point of the first DSS and the first point of the second DSS
	have the same ordinate (or abscissa). Otherwise, runs in
	O(log(n)) where n is the total length of the union.
     */
    ArithmeticalDSS computeUnion(const ArithmeticalDSS & aOther) const;


    // ----------------------- Iterator services -------------------------------
    /**
     * @return begin iterator,
     * which points to the point returned by ArithmeticalDSS::back() 
     */
    ConstIterator begin() const; 

    /**
     * @return end iterator, 
     * which points after the point returned by ArithmeticalDSS::front() 
     */
    ConstIterator end() const; 

    /**
     * @return begin reverse iterator,
     * which points to the point returned by ArithmeticalDSS::front() 
     */
    ConstReverseIterator rbegin() const; 

    /**
     * @return end iterator, 
     * which points before the point returned by ArithmeticalDSS::back() 
     */
    ConstReverseIterator rend() const; 

    // ----------------------- Dynamic methods --------------------------------

    /**
     * Tests whether the union between a new point, 
     * which is located at the front of the DSS,
     * and the DSS is still a DSS. 
     *
     * @param aNewPoint a point to test
     * 
     * @return an integer equal to 0 if the union between 
     * @a aNewPoint and the segment is not a DSS, but strictly greater 
     * than 0 otherwise. The value gives the way of updating
     *  the members of the DSS: 
     * 1:  initialization of the first step
     * 2:  repetition of the first step
     * 3:  initialization of the second step on the left
     * 4: initialization of the second step on the right
     * 5:  weakly interior on the left
     * 6: weakly interior on the right
     * 7:  weakly exterior on the left
     * 8: weakly exterior on the right
     * 9: strongly interior, nothing to update
     * @see extend isExtendableBack
     */
    unsigned short int isExtendableFront( const Point& aNewPoint ) const;

    /**
     * Tests whether the union between a new point, 
     * which is located at the back of the DSS,
     * and the DSS is still a DSS. 
     *
     * @param aNewPoint the point to test
     * 
     * @return an integer equal to 0 if the union between 
     * @a aNewPoint and the segment is not a DSS, but strictly greater 
     * than 0 otherwise. The value gives the way of updating
     *  the members of the DSS: 
     * 1:  initialization of the first step
     * 2:  repetition of the first step
     * 3:  initialization of the second step on the left
     * 4: initialization of the second step on the right
     * 5:  weakly interior on the left
     * 6: weakly interior on the right
     * 7:  weakly exterior on the left
     * 8: weakly exterior on the right
     * 9: strongly interior, nothing to update
     * @see extend isExtendableFront
     */
    unsigned short int isExtendableBack( const Point& aNewPoint ) const;

    /**
     * Tests whether the union between a point, 
     * which is located at the front of the DSS,
     * and the DSS is still a DSS. 
     * Computes the parameters of the new DSS 
     * with the adding point if true.
     *
     * @param aNewPoint the point to add
     * 
     * @return 'true' if the union is a DSS, 'false' otherwise.
     * @see isExtendableFront extendBack
     */
    bool extendFront( const Point& aNewPoint );
    /**
     * Tests whether the union between a point, 
     * which is located at the back of the DSS,
     * and the DSS is still a DSS. 
     * Computes the parameters of the new DSS 
     * with the adding point if true.
     *
     * @param aNewPoint the point to add
     * 
     * @return 'true' if the union is a DSS, 'false' otherwise.
     * @see isExtendableBack extendFront
     */
    bool extendBack( const Point& aNewPoint );

    /**
     * Removes the front point of the DSS 
     * if it remains strictly more than one point
     *
     * @return 'true' if the retraction has
     * been done, 'false' otherwise
     *
     * @see retract
     */
    bool retractFront();

    /**
     * Removes the back point of the DSS
     * if it remains strictly more than one point
     *
     * @return 'true' if the retraction has
     * been done, 'false' otherwise
     *
     * @see retract
     */
    bool retractBack();

    // ------------------------- Display services ------------------------------
    /**
     * Projects the point @a aM onto the straight line whose points have
     * remainder @a aR.
     *
     * @param aM any point (may not be part of the DSS).
     * @param aR the remainder (may not be an integer).
     *
     * @return the projected point.
     */
    PointD project( const Point& aM, double aR ) const;
    
    /**
     * Projects the point @a aM onto the straight line going through point @a aP.
     *
     * @param aM any point (may not be part of the DSS).
     * @param aP any point (may not be part of the DSS).
     *
     * @return the projected point.
     */
    PointD project( const Point & aM, const Point & aP ) const;

    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Updates the leaning points of the DSS
     * if the end point is a leaning point
     * that has to be removed from the DSS. 
     *
     * @param aDirection direction vector
     * @param aFirst new end of the DSS 
     * @param aLast opposite end of the DSS 
     * @param aBezout weakly exterior point used to 
     * compute the new slope and to update the leaning points
     * @param aFirstAtOppositeSide first leaning point located
     * at the side that is not affected by the removal
     * @param aLastAtOppositeSide last leaning point located
     * at the side that is not affected by the removal but that has 
     * to be updated
     * @param aFirstAtRemovalSide first leaning point that 
     * is removed and has to be updated. 
     * @param aLastAtRemovalSide last leaning point located
     * on the same side than @a aFirstAtRemovalSide 
     *
     * @return 'true' is the slope has to be updated, 
     * 'false' otherwise
     *
     * @see retractFront retractBack
     */
    bool retractUpdateLeaningPoints( const Vector& aDirection, 
				     const Point& aFirst,
				     const Point& aLast, 
				     const Point& aBezout, 
				     const Point& aFirstAtOppositeSide, 
				     Point& aLastAtOppositeSide, 
				     Point& aFirstAtRemovalSide,
				     const Point& aLastAtRemovalSide);

    /**
     * Updates the parameters of the bounding DSL after the retraction. 
     *
     * @param aNewDirection direction vector
     *
     * @see retractFront retractBack
     */
    void retractUpdateParameters( const Vector& aNewDirection );


    // ------------------------- Protected Datas ------------------------------
  protected:

    // -------------------- first and last point, leaning points ---------------
    /**
     * First point
     */
    Point myF;
    /**
     * Last point 
     */
    Point myL;
    /**
     * First upper leaning point ( of remainder @a myMu )
     */
    Point myUf;
    /**
     * Last upper leaning point ( of remainder @a myMu )
     */
    Point myUl;
    /**
     * First lower leaning point ( of remainder @a myMu + @a myOmega - 1 )
     */
    Point myLf;
    /**
     * Last lower leaning point ( of remainder @a myMu + @a myOmega - 1 )
     */
    Point myLl;

    //------------------------ DSL ---------------------------------------------
    /**
     * Bounding DSL of minimal parameters
     */
    DSL myDSL; 

  }; // end of class ArithmeticalDSS


  /**
   * Overloads 'operator<<' for displaying objects of class 'ArithmeticalDSS'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ArithmeticalDSS' to write.
   * @return the output stream after the writing.
   */
  template <typename TCoordinate, typename TInteger, unsigned short adjacency>
  std::ostream&
  operator<< ( std::ostream & out, const ArithmeticalDSS<TCoordinate, TInteger, adjacency> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Aliases
namespace DGtal
{
  /**
   * \brief Aim: This class represents a standard digital straight segment (DSS), 
   * ie. the sequence of simply 4-connected digital points contained in a 
   * standard digital straight line (DSL) between two points of it. 
   * This class is an alias of ArithmeticalDSS. 
   *
   * A 4-connected DSS can be declared and constructed as follows: 
   * @snippet geometry/curves/exampleArithmeticalDSS.cpp ArithmeticalDSSStandardCtor
   *
   * This requires the following include: 
   * @snippet geometry/curves/exampleArithmeticalDSS.cpp ArithmeticalDSSHeader
   *
   * See the documentation of NaiveDSS8 for a longer example 
   * and see @ref moduleArithDSSReco for further details. 
   *
   * @tparam TCoordinate a model of integer for the DGtal point coordinates and 
   * the slope parameters. 
   * @tparam TInteger a model of integer for the intercepts and the remainders
   * that represents a larger range of integers than TCoordinate. 
   *
   * This class is a model of CPointFunctor and of CConstBidirectionalRange. 
   *
   * @see ArithmeticalDSL NaiveDSL StandardDSL 
   * @see exampleArithmeticalDSL.cpp exampleArithmeticalDSS.cpp
   */
  template <typename TCoordinate, typename TInteger = TCoordinate>
  class StandardDSS4: 
    public ArithmeticalDSS<TCoordinate, TInteger, 4>
  {
  public: 
    typedef ArithmeticalDSS<TCoordinate, TInteger, 4> Super;
    typedef typename Super::Point Point;
    typedef typename Super::Coordinate Coordinate;
    typedef typename Super::DSL DSL;

  public: 

    /**
     * Constructor.
     * Minimal set of parameters to build the DSS
     * in constant time. 
     * The user should be sure that the slope is
     * consistent with the position of the leaning 
     * points. 
     *
     * @param aA y-component of the direction vector
     * @param aB x-component of the direction vector
     * @param aF the first point
     * @param aL the last point
     * @param aUf the first upper point
     * @param aUl the last upper point
     * @param aLf the first lower point
     * @param aLl the last lower point
     */
    StandardDSS4(const Coordinate& aA, const Coordinate& aB,
		 const Point& aF, const Point& aL,
		 const Point& aUf, const Point& aUl,
		 const Point& aLf, const Point& aLl);

    /**
     * Construction of a sequence of patterns 
     * (or reversed patterns) from two end points.
     *
     * @param aF the first point
     * @param aL the last point
     * @param isOnTheUpperLine boolean equal to 'true' if the
     * two given end points are upper leaning points (pattern case, default), 
     * 'false' if they are lower leaning points (reversed pattern case).  
     *
     * NB: logarithmic-time in the greatest component of the vector
     * starting from @a aF and pointing to @a aL
     */
    StandardDSS4(const Point& aF, const Point& aL,
		 const bool& isOnTheUpperLine = true);

    /**
     * Construction as the subsegment of minimal parameters of a given DSL. 
     *
     * @param aDSL bounding DSL
     * @param aF first point of the subsegment
     * @param aL last point of the subsegment
     *
     * NB: logarithmic-time in the greatest component of the direction vector
     * of the subsegment. Uses smartCH algorithm. 
     */
    StandardDSS4(const DSL& aDSL, 
		 const Point& aF, const Point& aL);

    /**
     * Construction as the subsegment of minimal parameters of a greater DSS. 
     *
     * @param aDSS bounding DSS
     * @param aF first point of the subsegment
     * @param aL last point of the subsegment
     *
     * NB: logarithmic-time in the greatest component of the direction vector
     * of the subsegment. Uses reversedSmartCH algorithm. 
     * @see ArithmeticalDSSFactory
     */
    StandardDSS4(const StandardDSS4& aDSS, 
		 const Point& aF, const Point& aL);

    /**
     * Construction from a range of iterators on points. 
     *
     * @param aItb begin iterator
     * @param aIte end iterator
     * @tparam Iterator a model of forward iterator
     *
     * NB: linear-time in the size of the range
     */
    template <typename Iterator>
    StandardDSS4(const Iterator& aItb, const Iterator& aIte);

    /**
     * Copy constructor.
     * @param aOther the object to clone.
     */
    StandardDSS4 ( const StandardDSS4 & aOther ); 

    /**
     * Assignment.
     * @param aOther the object to copy.
     * @return a reference on 'this'.
     */
    StandardDSS4 & operator= ( const StandardDSS4 & aOther );

  }; 

  /**
   * \brief Aim: This class represents a standard digital straight segment (DSS), 
   * ie. the sequence of simply 8-connected digital points contained in a 
   * naive digital straight line (DSL) between two points of it. 
   * This class is an alias of ArithmeticalDSS. 
   *
   * A 8-connected naive DSS can be declared and constructed as follows: 
   * @snippet geometry/curves/exampleArithmeticalDSS.cpp ArithmeticalDSSNaiveCtor
   *
   * You can iterate over the whole set of DSS points as follows:  
   * @snippet geometry/curves/exampleArithmeticalDSS.cpp ArithmeticalDSSIteration
   *
   * In addition, you can draw either the points of a DSS or its bounding box with Board2D:  
   * @snippet geometry/curves/exampleArithmeticalDSS.cpp NaiveDSS8DrawingUsage 
   *
   * Extending a DSS to a point simply connected to its front is done as follows: 
   * @snippet geometry/curves/exampleArithmeticalDSS.cpp ArithmeticalDSSUpdateExtension
   * This method implements the algorithm proposed in [Debled and Reveilles, 1995 : \cite Debled_1995_ijprai].
   *
   * The following code just undoes the previous extension: 
   * @snippet geometry/curves/exampleArithmeticalDSS.cpp ArithmeticalDSSUpdateRetraction
   * This method implements the algorithm proposed in [Lachaud et. al., 2007 : \cite LachaudIVC2007]. 
   * 
   * See @ref moduleArithDSSReco for further details. 
   *
   * @tparam TCoordinate a model of integer for the DGtal point coordinates and 
   * the slope parameters. 
   * @tparam TInteger a model of integer for the intercepts and the remainders
   * that represents a larger range of integers than TCoordinate. 
   *
   * This class is a model of CPointFunctor and of CConstBidirectionalRange. 
   *
   * @see ArithmeticalDSL NaiveDSL StandardDSL 
   * @see exampleArithmeticalDSL.cpp exampleArithmeticalDSS.cpp
   */
  template <typename TCoordinate, typename TInteger = TCoordinate>
  class NaiveDSS8: 
    public ArithmeticalDSS<TCoordinate, TInteger, 8>
  {
  public: 
    typedef ArithmeticalDSS<TCoordinate, TInteger, 8> Super;
    typedef typename Super::Point Point;
    typedef typename Super::Coordinate Coordinate;
    typedef typename Super::DSL DSL;

  public: 
    /**
     * Constructor.
     * Minimal set of parameters to build the DSS
     * in constant time. 
     * The user should be sure that the slope is
     * consistent with the position of the leaning 
     * points. 
     *
     * @param aA y-component of the direction vector
     * @param aB x-component of the direction vector
     * @param aF the first point
     * @param aL the last point
     * @param aUf the first upper point
     * @param aUl the last upper point
     * @param aLf the first lower point
     * @param aLl the last lower point
     */
    NaiveDSS8(const Coordinate& aA, const Coordinate& aB,
	      const Point& aF, const Point& aL,
	      const Point& aUf, const Point& aUl,
	      const Point& aLf, const Point& aLl);


    /**
     * Construction of a sequence of patterns 
     * (or reversed patterns) from two end points.
     *
     * @param aF the first point
     * @param aL the last point
     * @param isOnTheUpperLine boolean equal to 'true' if the
     * two given end points are upper leaning points (pattern case, default), 
     * 'false' if they are lower leaning points (reversed pattern case).  
     *
     * NB: logarithmic-time in the greatest component of the vector
     * starting from @a aF and pointing to @a aL
     */
    NaiveDSS8(const Point& aF, const Point& aL,
	      const bool& isOnTheUpperLine = true);

    /**
     * Construction as the subsegment of minimal parameters of a given DSL. 
     *
     * @param aDSL bounding DSL
     * @param aF first point of the subsegment
     * @param aL last point of the subsegment
     *
     * NB: logarithmic-time in the greatest component of the direction vector
     * of the subsegment. Uses smartCH algorithm. 
     */
    NaiveDSS8(const DSL& aDSL, 
	      const Point& aF, const Point& aL);

    /**
     * Construction as the subsegment of minimal parameters of a greater DSS. 
     *
     * @param aDSS bounding DSS
     * @param aF first point of the subsegment
     * @param aL last point of the subsegment
     *
     * NB: logarithmic-time in the greatest component of the direction vector
     * of the subsegment. Uses reversedSmartCH algorithm. 
     * @see ArithmeticalDSSFactory
     */
    NaiveDSS8(const NaiveDSS8& aDSS, 
	      const Point& aF, const Point& aL);

    /**
     * Construction from a range of iterators on points. 
     *
     * @param aItb begin iterator
     * @param aIte end iterator
     * @tparam Iterator a model of forward iterator
     *
     * NB: linear-time in the size of the range
     */
    template <typename Iterator>
    NaiveDSS8(const Iterator& aItb, const Iterator& aIte);

    /**
     * Copy constructor.
     * @param aOther the object to clone.
     */
    NaiveDSS8 ( const NaiveDSS8 & aOther ); 

    /**
     * Assignment.
     * @param aOther the object to copy.
     * @return a reference on 'this'.
     */
    NaiveDSS8 & operator= ( const NaiveDSS8 & aOther );

  }; 
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/ArithmeticalDSS.ih"
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
#endif // !defined ArithmeticalDSS_h

#undef ArithmeticalDSS_RECURSES
#endif // else defined(ArithmeticalDSS_RECURSES)
