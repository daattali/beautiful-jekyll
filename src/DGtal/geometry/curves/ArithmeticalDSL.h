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
 * @file ArithmeticalDSL.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/06/28
 *
 * Header file for module ArithmeticalDSL.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ArithmeticalDSL_RECURSES)
#error Recursive header files inclusion detected in ArithmeticalDSL.h
#else // defined(ArithmeticalDSL_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ArithmeticalDSL_RECURSES

#if !defined ArithmeticalDSL_h
/** Prevents repeated inclusion of headers. */
#define ArithmeticalDSL_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <utility>
#include "DGtal/base/Common.h"
#include "DGtal/base/Exceptions.h"
#include "DGtal/base/ReverseIterator.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/kernel/CSignedNumber.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/arithmetic/IntegerComputer.h"

#include "DGtal/geometry/curves/ArithmeticalDSLKernel.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  //forward declaration of ArithmeticalDSS for the friendship
  template <typename TCoordinate,
	    typename TInteger,
	    unsigned short adjacency>
  class ArithmeticalDSS;

  /////////////////////////////////////////////////////////////////////////////
  // template class ArithmeticalDSL
  /**
   * \brief Aim: This class represents a naive (resp. standard)
   * digital straight line (DSL), ie. the set of digital points
   * \f$ (x,y) \in \mathbb{Z}^2 \f$ such that \f$ \mu \leq ax - by < \mu + \omega \f$
   * with \f$ a,b,\mu,\omega \in \mathbb{Z} \f$, \f$ \gcd(a,b) = 1 \f$
   * and \f$ \omega = \max(|a|,|b|) \f$ (resp. \f$ \omega = |a| + |b| \f$).
   * Note that any DSL such that \f$ \omega = \max(|a|,|b|) \f$ (resp. \f$ \omega = |a| + |b| \f$)
   * is simply 8-connected (resp. 4-connected).
   *
   * [Reveilles, 1991 : \cite Reveilles_1991_thesis].
   *
   * A naive DSL can be declared and constructed as follows:
   @code
   #include "DGtal/arithmetic/geometry/curves/ArithmeticalDSL.h"
   ...
   ArithmeticalDSL<DGtal::int32_t, DGtal::int64_t, 8> line( 17711, 28657, 1607895256 );
   // equivalent to ArithmeticalDSL<DGtal::int32_t, DGtal::int64_t> line( 17711, 28657, 1607895256 );
   @endcode
   *
   * See @ref moduleArithDSSReco for further details.
   *
   * This class is a model of CPointFunctor and of CConstBidirectionalRange.
   *
   * In the standard case, it is enough to replace 8 by 4.
   * @tparam TCoordinate a model of integer for the DGtal point coordinates and
   * the slope parameters.
   * @tparam TInteger a model of integer for the intercepts and the remainders
   * that represents a larger range of integers than TCoordinate.
   * @tparam adjacency an unsigned integer equal to 8 (default) for naive DSL,
   * and 4 for standard DSL.
   *
   * @see ArithmeticalDSL NaiveDSL StandardDSL
   * @see exampleArithmeticalDSL.cpp
   */
  template <typename TCoordinate,
	    typename TInteger = TCoordinate,
	    unsigned short adjacency = 8>
  class ArithmeticalDSL
  {

    // ----------------------- Friend class -----------------------------------
  public:
    friend class ArithmeticalDSS<TCoordinate, TInteger, adjacency>;

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
     * Type of digital plane.
     */
    typedef typename ArithmeticalDSLKernel<Coordinate,adjacency>::Space Space;
    /**
     * Type of point.
     */
    typedef typename Space::Point Point;
    /**
     * Type of vector.
     */
    typedef typename Space::Vector Vector;
    /**
     * Type of step vectors, defined as STL pair of vectors.
     */
    typedef std::pair<Vector,Vector> Steps;
    /**
     * Type used for the position of a point in the DSL.
     */
    typedef Coordinate Position;

  /**
   * Type of the octant values, defined as a STL pair of int
   */
  typedef std::pair<unsigned char, unsigned char> Octant;

  

    /**
     * \brief Aim: This class aims at representing an iterator
     * that provides a way to scan the points of a DSL.
     * It is both a model of readable iterator and of
     * bidirectional iterator.
     *
     * Instances of this class are returned by begin and end methods
     * of DSL classes as follows:
     * @snippet geometry/curves/exampleArithmeticalDSL.cpp ArithmeticalDSLIteration
     *
     * See @ref moduleArithDSSReco for further details.
     *
     * @see ArithmeticalDSL NaiveDSL StandardDSL
     * @see exampleArithmeticalDSL.cpp
     */
    class ConstIterator
      : public boost::iterator_facade<ConstIterator, //derived type, the ConstIterator class itself
				      Point const,   //value type
				      boost::random_access_traversal_tag, //traversal tag
				      Point const,    //reference type
				      //NB: since there is no underlying container,
				      //we cannot return a reference.
				      Position  //difference type
				      >
    {

      // ------------------------- Private data -----------------------
    private:

      /// Constant aliasing pointer to the DSL visited by the iterator
      const ArithmeticalDSL* myDSLPtr;

      /// The current point
      Point  myCurrentPoint;

      /// Quantity to add to the current remainder
      Integer  myQuantityToAdd;

      /// Quantity to remove to the current remainder
      Integer  myQuantityToRemove;

      /// Remainder of the current point
      Integer  myCurrentRemainder;

      // ------------------------- Standard services -----------------------
    public:

      /**
       * Default constructor (not valid).
       */
      ConstIterator();

      /**
       * Constructor.
       * @param aDSL an arithmetical DSL
       * @param aPoint a point of the DSL containing @a aDSL
       */
      ConstIterator( const ArithmeticalDSL* aDSL, const Point& aPoint );

      /**
       * Copy constructor.
       * @param aOther the iterator to clone.
       */
      ConstIterator( const ConstIterator & aOther );
      /**
       * Assignment.
       * @param aOther the iterator to copy.
       * @return a reference on 'this'.
       */
      ConstIterator& operator= ( const ConstIterator & aOther );

      /**
       * Destructor. Does nothing.
       */
      ~ConstIterator();
 
      // ------------------------- useful services -------------------------
   public: 
      /**
       * @return the remainder of the current point
       * (without any computation)
       */
      Integer remainder() const;

      // ------------------------- iteration services -------------------------
    private:
      friend class boost::iterator_core_access;

      /**
       * Dereference operator
       * @return the current point
       */
      Point const dereference() const;

      /**
       * Moves @a myCurrentPoint to the next point of the DSL
       */
      void increment();

      /**
       * Moves @a myCurrentPoint to the previous point of the DSL
       */
      void decrement();

      /**
       * Equality operator.
       *
       * @param aOther the iterator to compare with
       * (must be defined on the same DSL).
       *
       * @return 'true' if their current points coincide.
       */
      bool equal(const ConstIterator& aOther) const;

      /**
       * Moves @a myCurrentPoint lying at position i to the 
       * point of the DSL lying at position i + @a aShift
       * @param aShift position difference
       * NB: in O(1)
       */
      void advance(const Position& aShift);

      /**
       * Computes the distance between *this and @a aOther, ie.
       * the difference between their positions
       * @param aOther any other iterator 
       * @return distance between the two iterators
       */
      Position distance_to(const ConstIterator& aOther) const; 

    };

    /**
     * Type of const reverse iterator, adapted from ConstIterator.
     */
    typedef DGtal::ReverseIterator<ConstIterator> ConstReverseIterator;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor.
     * The user gives all the (redondant) parameters and
     * should be sure that the resulting DSL is valid.
     *
     * @see isValid
     *
     * @param aA y-component of the direction vector
     * @param aB x-component of the direction vector
     * @param aLowerIntercept lower intercept
     * @param aUpperIntercept upper intercept
     * @param aSteps pair of steps used to iterate over the DSL points
     * @param aShift shift vector
     */
    ArithmeticalDSL(const Coordinate& aA, const Coordinate& aB,
		    const Integer& aLowerIntercept, const Integer& aUpperIntercept,
		    const Steps& aSteps, const Vector& aShift);

    /**
     * Constructor with the minimal set of parameters.
     *
     * @param aA y-component of the direction vector
     * @param aB x-component of the direction vector
     * @param aMu intercept
     */
    ArithmeticalDSL(const Coordinate& aA, const Coordinate& aB,
		    const Integer& aMu);


    /**
     * Copy constructor.
     * @param aOther the object to clone.
     */
    ArithmeticalDSL ( const ArithmeticalDSL & aOther );

    /**
     * Assignment.
     * @param aOther the object to copy.
     * @return a reference on 'this'.
     */
    ArithmeticalDSL& operator= ( const ArithmeticalDSL & aOther );

    /**
     * Returns a copy of '*this' with a reverse orientation, ie. with parameters
     * ( -@a myA , -@a myB , -@a myUpperIntercept , -@a myLowerIntercept).
     * @return the negation of '*this'.
     */
    ArithmeticalDSL negate () const;

    /**
     * Equality.
     * @param aOther the object to compare with.
     * @return 'true' if the parameters of the DSL
     * are equal (orientation matters), 'false' otherwise
     */
    bool equalsTo ( const ArithmeticalDSL & aOther ) const;

    /**
     * Equality.
     * @param aOther the object to compare with.
     * @return 'true' the two sets of points that are
     * implicitly defined are equal (without respect to
     * the orientation), 'false' otherwise
     * @see equalsTo
     */
    bool operator== ( const ArithmeticalDSL & aOther ) const;

    /**
     * Difference.
     * @param aOther the object to compare with.
     * @return 'true' the two set of points that are
     * implicitly defined are different, 'false' otherwise
     */
    bool operator!= ( const ArithmeticalDSL & aOther ) const;

  /**
   * Test if DSLs lie in the same octant.
   * @param aOther the object to compare with.
   * @param[out] theOctant  where to store the common octant if the DSLs are in the same octant.
   * @return 'true' if the two DSLs lie in the same octant, 'false' otherwise
   * @see sameOctant
   */
  bool sameOctant ( const ArithmeticalDSL & aOther, typename Octant::first_type *theOctant ) const;


  /**
   * Test if a point is an upper leaning point of *this
   * @param aPoint a point
   * @return 'true' if aPoint is an upper leaning point of *this, false otherwise
   */
  bool isUpperLeaningPoint(const Point& aPoint) const;
  
  /**
   * Test if a point is a lower leaning point of *this
   * @param aPoint a point
   * @return 'true' if aPoint is a lower leaning point of *this, false otherwise
   */
  bool isLowerLeaningPoint(const Point& aPoint) const;
  

  /**
   * Returns the octants of the DSL  as a
   * pair of integers. If the parameters are such that \f$ abs(@a myA) =
   * abs(@a myB) \f$ or \f$ @a myA = 0 \f$ or \f$ @a myB = 0 \f$, it returns
   * two octants (for instance octants 0 and 7 if \f$ @a myA = 0 \f$).  
   *
   * @return the octants as a pair of integers
   */
  
  Octant octant() const;


    /**
     * Destructor.
     */
    ~ArithmeticalDSL();

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the consistency between the slope parameters, ie.
     * @a myA , @a myB and the translating vectors @a myShift ,
     * @a mySteps
     * @return 'true' if ok, 'false' otherwise
     * @pre @a myA and @a myB must not be both null
     */
    bool checkShiftAndSteps() const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     *
     * NB: runs in O( log( max( |@a myA |,| @a myB | ) ) )
     * because it checks if @a myA and @a myB are relatively primes.
     */
    bool isValid() const;

    /**
     * @return a parameter (y-component of the direction vector)
     */
    Coordinate a() const;

    /**
     * @return b parameter (x-component of the direction vector)
     */
    Coordinate b() const;

    /**
     * @return mu parameter, the intercept \f$ \mu \f$
     */
    Integer mu() const;

    /**
     * @return the arithmetical thickness \f$ \omega \f$
     * @see patternLength
     */
    Integer omega() const;

    /**
     * @return the pattern length (equal to \f$ omega \f$)
     * @see omega
     */
    Position patternLength() const;

    /**
     * @return the shift vector (translating a point
     * of remainder \f$ r \f$ to a point of remainder \f$ r+\omega \f$).
     */
    Vector shift() const;

    /**
     * @return the two vectors used to iterate over the DSL points.
     */
    Steps steps() const;

    /**
     * Returns the remainder of @a aPoint
     * with respect to the direction vector
     * of components @a aA and @a aB
     * @param aA y-component of the direction vector
     * @param aB x-component of the direction vector
     * @param aPoint any point
     * @return remainder of @a aPoint
     */
    static Integer remainder(const Coordinate& aA,
			     const Coordinate& aB,
			     const Point& aPoint);

    /**
     * Returns the remainder of @a aPoint
     * (which does not necessarily belong to the DSL)
     * @return remainder of @a aPoint
     * @param aPoint any point
     */
    Integer remainder(const Point& aPoint) const;

    /**
     * Returns the position of @a aPoint
     * (which does not necessarily belong to the DSL)
     * computed along the direction that is orthogonal
     * to the direction vector
     * @param aPoint the point whose position is returned
     * @return the position
     */
    Integer orthogonalPosition(const Point& aPoint) const;

    /**
     * Returns the position of @a aPoint
     * (which does not necessarily belong to the DSL)
     * computed along the direction orthogonal to @a myShift
     * @param aPoint the point whose position is returned
     * @return the position
     */
    Position position(const Point& aPoint) const;

    /**
     * Returns the unique point of the DSL located at position zero
     * in O(1). 
     * @pre the arithmetical thickness is not equal to zero
     * @return the point of the DSL located at position zero
     */
    Point getPoint() const;

    /**
     * Returns the unique point of the DSL located at position @a aPosition
     * in O(1). 
     * @pre the arithmetical thickness is not equal to zero
     * @param aPosition position of the returned point
     * @return the point of the DSL located at position @a aPosition
     */
    Point getPoint(const Position& aPosition) const;

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
     * 'false' otherwise.
     * @param aPoint any point
     */
    bool isInDSL(const Point& aPoint) const;

  
  
    /**
     * @return 'true' if @a aPoint is in the DSL
     * 'false' otherwise.
     * @param aPoint any point
     * @see isInDSL
     */
    bool operator()(const Point& aPoint) const;


    // ----------------------- Iterator services -------------------------------
    /**
     * @param aPoint any point of the DSL
     * @pre aPoint should belong to the DSL
     * @return begin iterator,
     * which points to @a aPoint
     */
    ConstIterator begin(const Point& aPoint) const;

    /**
     * @param aPoint any point of the DSL
     * @pre aPoint should belong to the DSL
     * @return end iterator,
     * which points to the point located after @a aPoint
     */
    ConstIterator end(const Point& aPoint) const;

    /**
     * @param aPoint any point of the DSL
     * @pre aPoint sould belongs to the DSL
     * @return begin reverse iterator,
     * which points to @a aPoint
     */
    ConstReverseIterator rbegin(const Point& aPoint) const;

    /**
     * @param aPoint any point of the DSL
     * @pre aPoint sould belongs to the DSL
     * @return end iterator,
     * which points to the point located before @a aPoint
     */
    ConstReverseIterator rend(const Point& aPoint) const;


    // ------------------------- Other services ------------------------------
  public:
    static Coordinate toCoordinate(const Integer& aI); 

    // ------------------------- Protected Datas ------------------------------
  protected:

    // -------------------------vectors ---------------------------------------
    /**
     * Pair of steps used to iterate over the DSL points. They are computed
     * from @a myA and @a myB in ArithmeticalDSLKernel.
     * @see ArithmeticalDSLKernel::steps
     */
    Steps mySteps;
    /**
     * Shift vector. It is computed from @a myA and @a myB in ArithmeticalDSLKernel.
     * @see ArithmeticalDSLKernel::shift
     */
    Vector myShift;

    //------------------------ parameters of the DSL --------------------------
    /**
     * y-component of the direction vector
     */
    Coordinate myA;
    /**
     * x-component of the direction vector
     */
    Coordinate myB;
    /**
     * Lower intercept. Invariants:
     * - for any upper leaning point U, we have remainder(U) == @a myLowerBound.
     * - @a myLowerBound <= @a myUpperBound
     */
    Integer myLowerBound;
    /**
     * Upper intercept. Invariants:
     * - for any lower leaning point L, we have remainder(L) == @a myUpperBound.
     * - if @a myA and @a myB are not both null, @a myUpperBound == @a myLowerBound + omega() - 1
     * - @a myLowerBound <= @a myUpperBound
     */
    Integer myUpperBound;



  }; // end of class ArithmeticalDSL


  /**
   * Overloads 'operator<<' for displaying objects of class 'ArithmeticalDSL'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ArithmeticalDSL' to write.
   * @return the output stream after the writing.
   */
  template <typename TCoordinate, typename TInteger, unsigned short adjacency>
  std::ostream&
  operator<< ( std::ostream & out, const ArithmeticalDSL<TCoordinate, TInteger, adjacency> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Aliases
namespace DGtal
{
  /**
   * \brief Aim: This class is an alias of ArithmeticalDSS for standard DSL.
   * It represents a standard digital straight line (DSL), ie. the set of digital points
   * \f$ (x,y) \in \mathbb{Z}^2 \f$ such that \f$ \mu \leq ax - by < \mu + \omega \f$
   * with \f$ a,b,\mu,\omega \in \mathbb{Z} \f$, \f$ \gcd(a,b) = 1 \f$
   * and \f$ \omega = |a| + |b| \f$. Note that any DSL such that
   * \f$ \omega = |a| + |b| \f$ is simply 4-connected.
   *
   * [Reveilles, 1991 : \cite Reveilles_1991_thesis].
   *
   * A standard DSL can be declared and constructed as follows:
   * @snippet geometry/curves/exampleArithmeticalDSL.cpp ArithmeticalDSLStandardCtor
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
   * @see exampleArithmeticalDSL.cpp
   */
  template <typename TCoordinate, typename TInteger = TCoordinate>
  class StandardDSL:
    public ArithmeticalDSL<TCoordinate, TInteger, 4>
  {
  public:
    /**
     * Type of base class.
     */
    typedef ArithmeticalDSL<TCoordinate, TInteger, 4> Super;
    typedef typename Super::Coordinate Coordinate;
    typedef typename Super::Integer Integer;

  public:
    /**
     * Constructor.
     *
     * @param aA y-component of the direction vector
     * @param aB x-component of the direction vector
     * @param aMu intercept
     */
    StandardDSL (const Coordinate& aA,
		 const Coordinate& aB,
		 const Integer& aMu);

    /**
     * Copy constructor.
     * @param aOther the object to clone.
     */
    StandardDSL ( const StandardDSL & aOther );

    /**
     * Assignment.
     * @param aOther the object to copy.
     * @return a reference on 'this'.
     */
    StandardDSL & operator= ( const StandardDSL & aOther );

  };

  /**
   * \brief Aim: This class is an alias of ArithmeticalDSS for naive DSL.
   * It represents a naive digital straight line (DSL), ie. the set of digital points
   * \f$ (x,y) \in \mathbb{Z}^2 \f$ such that \f$ \mu \leq ax - by < \mu + \omega \f$
   * with \f$ a,b,\mu,\omega \in \mathbb{Z} \f$, \f$ \gcd(a,b) = 1 \f$
   * and \f$ \omega = \max(|a|,|b|) \f$. Note that any DSL such that
   * \f$ \omega = \max(|a|,|b|) \f$ is simply 8-connected.
   *
   * [Reveilles, 1991 : \cite Reveilles_1991_thesis].
   *
   * As a quick start, a naive DSL can be declared and constructed as follows:
   * @snippet geometry/curves/exampleArithmeticalDSL.cpp ArithmeticalDSLNaiveCtor
   *
   * Then, within a window defined by two points (called firstPoint and lastPoint below),
   * you can iterate over the DSL points:
   * @snippet geometry/curves/exampleArithmeticalDSL.cpp ArithmeticalDSLIteration
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
   * @see exampleArithmeticalDSL.cpp
   */
  template <typename TCoordinate, typename TInteger = TCoordinate>
  class NaiveDSL:
    public ArithmeticalDSL<TCoordinate, TInteger, 8>
  {
  public:
    /**
     * Type of base class.
     */
    typedef ArithmeticalDSL<TCoordinate, TInteger, 8> Super;
    typedef typename Super::Coordinate Coordinate;
    typedef typename Super::Integer Integer;

  public:
    /**
     * Constructor.
     *
     * @param aA y-component of the direction vector
     * @param aB x-component of the direction vector
     * @param aMu intercept
     */
    NaiveDSL (const Coordinate& aA,
	      const Coordinate& aB,
	      const Integer& aMu);


    /**
     * Copy constructor.
     * @param aOther the object to clone.
     */
    NaiveDSL ( const NaiveDSL & aOther );

    /**
     * Assignment.
     * @param aOther the object to copy.
     * @return a reference on 'this'.
     */
    NaiveDSL & operator= ( const NaiveDSL & aOther );

  };
} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////
// Tools
namespace DGtal
{
  namespace detail {
    
    /**
     * Description of template class 'functors::CastForSignedIntegers' <p>
     * \brief Aim: Define a simple functor that can cast 
     * a signed integer (possibly a DGtal::BigInteger) into another.
     *
     * @tparam TInput type of the input value
     * @tparam TOutput type of the return value
     */
    template <typename TInput, typename TOutput >
    struct toCoordinateImpl
    {
      BOOST_CONCEPT_ASSERT(( concepts::CSignedNumber<TInput> ));
      BOOST_CONCEPT_ASSERT(( concepts::CSignedNumber<TOutput> ));
      BOOST_CONCEPT_ASSERT(( concepts::CInteger<TInput> ));
      BOOST_CONCEPT_ASSERT(( concepts::CInteger<TOutput> ));
      /**
       * cast operator
       * @return the conversion of @a aInput into an object of type TOutput.
       */
      inline
      static TOutput cast(const TInput& aInput) 
      {
	return static_cast<TOutput>(aInput);
      }
    };
#ifdef WITH_BIGINTEGER
    //specialized versions for DGtal::BigInteger
    template <typename TOutput>
    struct toCoordinateImpl<DGtal::BigInteger, TOutput>
    {
      BOOST_CONCEPT_ASSERT(( concepts::CSignedNumber<TOutput> ));
      BOOST_CONCEPT_ASSERT(( concepts::CInteger<TOutput> ));

      inline
      static TOutput cast(const DGtal::BigInteger& aInput)
      {
	ASSERT( (aInput <= static_cast<DGtal::BigInteger>(std::numeric_limits<TOutput>::max())) &&
		(aInput >= static_cast<DGtal::BigInteger>(std::numeric_limits<TOutput>::min())) ); 
	return static_cast<TOutput>(aInput.get_si()); 
      }
    };
    template <>
    struct toCoordinateImpl<DGtal::BigInteger, DGtal::BigInteger>
    {

      inline
      static DGtal::BigInteger cast(const DGtal::BigInteger& aInput)
      {
	return aInput; 
      }
    };
#endif

  } //namespace detail

} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/ArithmeticalDSL.ih"
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
#endif // !defined ArithmeticalDSL_h

#undef ArithmeticalDSL_RECURSES
#endif // else defined(ArithmeticalDSL_RECURSES)
