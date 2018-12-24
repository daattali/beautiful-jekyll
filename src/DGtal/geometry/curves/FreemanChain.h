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
 * @file FreemanChain.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 * @author Xavier Proven�al (\c xavier.provencal@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @author Tristan Roussillon (\c
 * tristan.roussillon@liris.cnrs.fr ) Laboratoire d'InfoRmatique en
 * Image et Syst�mes d'information - LIRIS (CNRS, UMR 5205), CNRS,
 * France
 *
 * @date 2010/07/01
 *
 * @brief Header file for module FreemanChain.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(FreemanChain_RECURSES)
#error Recursive header files inclusion detected in FreemanChain.h
#else // defined(FreemanChain_RECURSES)
/** Prevents recursive inclusion of headers. */
#define FreemanChain_RECURSES

#if !defined FreemanChain_h
/** Prevents repeated inclusion of headers. */
#define FreemanChain_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include "DGtal/kernel/PointVector.h"
#include "DGtal/base/OrderedAlphabet.h"
#include "DGtal/base/Circulator.h"
#include "DGtal/arithmetic/ModuloComputer.h"

#include "DGtal/base/CConstSinglePassRange.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/base/ConstAlias.h"


//////////////////////////////////////////////////////////////////////////////


namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class FreemanChain
  /////////////////////////////////////////////////////////////////////////////
  /**
   * Aim: Describes a digital
   * 4-connected contour as a string of '0', '1', '2', and '3' and the
   * coordinate of the first point. When it is a loop, it is the
   * clockwise boundary of the shape.
   
   * Example :
   * @code 
   
   // A Freeman chain code is a string composed by the coordinates of the first
   // pixel, and the list of elementary displacements. 
   std::stringstream ss (stringstream::in | stringstream::out);
   ss << "0 0 00001111222233" << endl;
   
   // Construct the Freeman chain
   FreemanChain<int> fc(ss);
   
   // Compute a bounding box 
   int minX, maxX, minY, maxY;
   fc.computeBoundingBox(minX, minY, maxX, maxY);  
   
   // Compute the list of points of the contour
   vector<FreemanChain<int>::Point> aContourPointVector; 
   fc.getContourPoints(fc, aContourPointVector);
   
   // Draw the Freeman chain
   Board2D aBoard;
   aBoard.setUnit(Board::UMillimeter);
   aBoard << fc;

   * @endcode
   *
   * @tparam TInteger  type of the coordinates of the starting point
   *
   * @see freemanChainDisplay.cpp  freemanChainFromImage.cpp  testFreemanChain.cpp
   */

  template <typename TInteger>
  class FreemanChain
  {

  public :

    BOOST_CONCEPT_ASSERT(( concepts::CInteger<TInteger> ) );
    typedef TInteger Integer;
    typedef FreemanChain<Integer> Self;

    typedef PointVector<2, Integer> Point;
    typedef PointVector<2, Integer> Vector;

    typedef unsigned int Size;
    typedef unsigned int Index;

    // ------------------------- iterator ------------------------------
  public:
    
    ///////////////////////////////////////////////////////////////////////////////
    // class FreemanChain::ConstIterator
    ///////////////////////////////////////////////////////////////////////////////
  
    
    /**
     * This class represents an iterator on points defined by freeman chain,
     * storing the current coordinate.
     */

    class ConstIterator : public 
      std::iterator<std::bidirectional_iterator_tag, Point, int, Point*, Point> 
    {

      // ------------------------- Private data -----------------------

      private:

        /// The Freeman chain visited by the iterator.
        const FreemanChain* myFc;

        /// The current position in the word.
        Index myPos;

        ///The current coordinates of the iterator.
        Point  myXY;

        // ------------------------- Standard services -----------------------
      public:

        /**
         * Default Constructor.
         * The object is not valid.
         */
        ConstIterator()
          : myFc( NULL ), myPos( 0 )
        { }

        /**
         * Constructor.
         * Nb: complexity in O(n).
         *
         * @param aChain a Freeman chain,
         * @param n the position in [chain] (within 0 and chain.size()).
         */
        ConstIterator( ConstAlias<FreemanChain> aChain, Index n =0);


        /**
         * Constructor.
         * It is the user's responsability to make sure that the data's are
         * consistent. No verification is performed.
         *
         * Nb: complexity in O(1).
         *
         * @param aChain a Freeman chain,
         * @param n the position in [chain] (within 0 and chain.size()).
         * @param XY the point corresponding to the 'n'-th position of 'chain'.
         */
        ConstIterator( ConstAlias<FreemanChain> aChain, Index n, const Point & XY)
          : myFc( &aChain ), myPos( n ), myXY ( XY ) 
        { }

        /**
         * Copy constructor.
         * @param aOther the iterator to clone.
         */
        ConstIterator( const ConstIterator & aOther )
          : myFc( aOther.myFc ), myPos( aOther.myPos ), myXY( aOther.myXY )
        { } 

        /**
         * Assignment.
         * @param other the iterator to copy.
         * @return a reference on 'this'.
         */
        ConstIterator& operator= ( const ConstIterator & other );

        /**
         * Destructor. Does nothing.
         */
        ~ConstIterator()
        { }

        // ------------------------- iteration services -------------------------
      public:


        /**
         * @return the current coordinates.
         */
        const Point& operator*() const
        {
          return myXY;
        }

        /**
         * @return the current coordinates.
         */
        const Point& get() const
        {
          return myXY;
        }

        /**
         * Pre-increment.
         * Goes to the next point on the chain.
         */
        ConstIterator& operator++()
        {
          this->next();
          return *this;
        }

        /**
         * Post-increment.
         * Goes to the next point on the chain.
         */
        ConstIterator operator++(int)
        {
          ConstIterator tmp(*this);
          this->next();
          return tmp;
        }


        /**
         * Goes to the next point on the chain.
         */
        void next();

        /**
         * Goes to the next point on the chain as if on a loop.
         */
        void nextInLoop();

        /**
         * @return the current position (as an index in the Freeman chain).
         */
        Index position() const
        {
          return myPos;
        }


        /**
         * @return the associated Freeman chain.
         */
        const FreemanChain * getChain() const
        {
          return myFc;
        }

        /**
         * @return the current Freeman code (specifies the movement to the next
         * point).
         */
        //unsigned int getCode() const
        char getCode() const
        {
          ASSERT( myFc != 0 );
          return myFc->code( myPos );
        }


        /**
         * Pre-decrement.
         * Goes to the previous point on the chain.
         */
        ConstIterator& operator--()
        {
          this->previous();
          return *this;
        }

        /**
         * Post-decrement.
         * Goes to the previous point on the chain.
         */
        ConstIterator operator--(int)
        {
          ConstIterator tmp(*this);
          this->previous();
          return tmp;
        }


        /**
         * Goes to the previous point on the chain if possible.
         */
        void previous();


        /**
         * Goes to the previous point on the chain as if on a loop.
         */
        void previousInLoop();


        /**
         * Equality operator.
         *
         * @param aOther the iterator to compare with (must be defined on
         * the same chain).
         *
         * @return 'true' if their current positions coincide.
         */
        bool operator== ( const ConstIterator & aOther ) const
        {
          ASSERT( myFc == aOther.myFc );
          return myPos == aOther.myPos;
        }


        /**
         * Inequality operator.
         *
         * @param aOther the iterator to compare with (must be defined on
         * the same chain).
         *
         * @return 'true' if their current positions differs.
         */
        bool operator!= ( const ConstIterator & aOther ) const
        {
          ASSERT( myFc == aOther.myFc );
          return myPos != aOther.myPos;
        }

        /**
         * Inferior operator.
         *
         * @param aOther the iterator to compare with (must be defined on
         * the same chain).
         *
         * @return 'true' if the current position of 'this' is before
         * the current position of [aOther].
         */
        bool operator< ( const ConstIterator & aOther ) const 
        {
          ASSERT( myFc == aOther.myFc );
          return myPos < aOther.myPos;
        }

    };


///////////////////////////////////////////////////////////////////////////////
// class CodesRange
///////////////////////////////////////////////////////////////////////////////

/**
* @brief Aim: model of CRange that provides services
* to (circularly)iterate over the letters of the freeman chain.
*
* @see FreemanChain.h testFreemanChain.cpp
*/
class CodesRange
{

  // ------------------------- inner types --------------------------------
public: 

  typedef std::string::const_iterator ConstIterator; 
  typedef std::string::const_reverse_iterator ConstReverseIterator;
  typedef Circulator<ConstIterator> ConstCirculator;
  typedef std::reverse_iterator<ConstCirculator> ConstReverseCirculator;

  // ------------------------- standard services --------------------------------

  /**
   * Default Constructor.
   */
  CodesRange(){}

  /**
   * Constructor.
   */
  CodesRange(const std::string& aChain ): myChain(aChain){}

  /**
   * Copy constructor.
   * @param aOther the iterator to clone.
   */
  CodesRange( const CodesRange & aOther )
    : myChain( aOther.myChain ){}
  
  /**
   * Assignment.
   * @param other the iterator to copy.
   * @return a reference on 'this'.
   */
  CodesRange& operator= ( const CodesRange & other )
  {  
    if ( this != &other )
    {
      myChain = other.myChain;
    }
  return *this;
  }

  /**
   * Destructor. Does nothing.
   */
  ~CodesRange() {}

  /**
   * @return the size of the range
   */
  std::string::size_type size() const 
  {
    return myChain.size();
  }

  /**
   * Checks the validity/consistency of the object.
   * @return 'true' if the object is valid, 'false' otherwise.
   */
  bool isValid() const { return true; }
  
  // ------------------------- display --------------------------------
  /**
   * Writes/Displays the object on an output stream.
   * @param out the output stream where the object is written.
   */
  void selfDisplay ( std::ostream & out ) const 
  {
    typedef typename IteratorCirculatorTraits<ConstIterator>::Value Value; 
    out << "[FreemanChainCodes]" << std::endl;
    out << "\t"; 
    std::copy( this->begin(), this->end(), std::ostream_iterator<Value>(out, "") );
    out << std::endl;
  }
  
  /**
   * Overloads 'operator<<' for displaying objects of class 'CodesRange'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'CodesRange' to write.
   * @return the output stream after the writing.
   */
  friend std::ostream& operator <<(std::ostream & out, const CodesRange & object)
    {
      object.selfDisplay( out );
      return out;
    }
  // ------------------------- private data --------------------------------
  private:
  /**
   * Private member @a myChain is a string of letters
   */    
  const std::string myChain;
  // ------------------------- iterator services --------------------------------
public:

  /**
   * Iterator service.
   * @return begin iterator
   */
  ConstIterator begin() const {
    return myChain.begin();
  }

  /**
   * Iterator service.
   * @return end iterator
   */
  ConstIterator end() const {
    return myChain.end();
  }

  /**
   * Iterator service.
   * @return rbegin iterator
   */
  ConstReverseIterator rbegin() const {
    return myChain.rbegin();
  }

  /**
   * Iterator service.
   * @return rend iterator
   */
  ConstReverseIterator rend() const {
    return myChain.rend();
  }

  /**
   * Circulator service.
   * @return a circulator
   */
  ConstCirculator c() const {
    return ConstCirculator( this->begin(), this->begin(), this->end() );
  }

  /**
   * Circulator service.
   * @return a reverse circulator
   */
  ConstReverseCirculator rc() const {
    return ConstReverseCirculator( this->c() );
  }
};

///////////////////////////////////////////////////////////////////////////////
// end of class CodesRange
///////////////////////////////////////////////////////////////////////////////

    /**
     * @return  an instance of CodesRange.
     */
    CodesRange getCodesRange()
    { 
      return CodesRange(chain); 
    }


    ///////////////////////////////////////////////////////////////////////////////
    // ----------------------- Standard services ------------------------------
    
  public:

    /**
     * Destructor.
     */
    ~FreemanChain()
    { }

    /**
     * Constructor.
     * @param s the chain code.
     * @param x the x-coordinate of the first point.
     * @param y the y-coordinate of the first point.
     */
    FreemanChain( const std::string & s = "", TInteger x = 0, TInteger y = 0 );


    /**
     * Constructor.
     * @param vectPoints the vector containing all the points.
     */
    FreemanChain( const std::vector<Point>& vectPoints);
    
    
    /**
     * Constructor.
     * @param in any input stream,
     */
    FreemanChain(std::istream & in );


    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    FreemanChain( const FreemanChain & other );


    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    FreemanChain & operator=( const FreemanChain & other );


    /**
     * Comparaison operator
     * @param other the object to compare to.
     * @return 'true' both FreemanChain are equals, 'false' otherwise.
     */
    bool operator==( const FreemanChain & other) const
    {
      return (chain == other.chain) && ( x0 == other.x0 ) && ( y0 == other.y0 )
        && ( xn == other.xn ) && ( yn == other.yn );
    }

    /**
     * Comparaison operator
     * @param other the object to compare to.
     * @return 'true' both FreemanChain are different, 'false' otherwise.
     */
    bool operator!=( const FreemanChain & other) const
    {
      return  !( (*this) == other );
    }


    /**
     * @param pos a position in the chain code.
     * @return the code at position [pos].
     *
     * Note, it is assumed that 0 <= pos < this->size()
     */
    //unsigned int code( Index pos ) const;
    char code( Index pos ) const;


    /**
     * @return the length of the Freeman chain code.
     */
    Size size() const;


    /**
     * Returns the subchain of the chain starting at position 'pos' and has 'n'
     * letters long.  
     *
     * @param pos position of a character in the current FreemanChain object to
     * be used as starting character for the subchain.  
     * @param n length of the subchain.
     *
     * @return the subchain starting at 'pos' having 'n' letters long.
     */
    FreemanChain subChain( Index pos, Size n ) const;


    /**
     * Concatenation services.
     *
     * Note: the starting point of 'other' is not considered.
     *
     * @param other the chain to concatenate at the end of this.
     * @return the concatenation of this and other.
     */
    FreemanChain operator+(const FreemanChain& other) const;


    /**
     * Concatenation services.
     *
     * Note: the starting point of 'other' is not considered.
     *
     * @param other the chain to concatenate at the end of this.
     * @return a reference to this.
     */
    FreemanChain& operator+=(const FreemanChain& other);


    /**
     * Computes a bounding box for the Freeman chain code.
     *
     * @param min_x (returns) the minimal x-coordinate.
     * @param min_y (returns) the minimal y-coordinate.
     * @param max_x (returns) the maximal x-coordinate.
     * @param max_y (returns) the maximal y-coordinate.
     */
    void computeBoundingBox( TInteger & min_x, TInteger& min_y,
                             TInteger& max_x, TInteger& max_y ) const;

    /**
     * Finds a quadrant change in 'this' Freeman chain and returns the
     * position as an iterator. A quadrant change is some
     * @code
     abb..bc
     |
     iterator
     * @endcode
     *
     * The alphabet is possibly re-ordered so that a > b > c.
     *
     * @param A (possibly updated) a Freeman chain alphabet, possibly
     * re-ordered so that a > b > c.
     *
     * @return an iterator on 'this' that points on the first letter b.
     */
    //BK
    typename Self::ConstIterator 
      findQuadrantChange( OrderedAlphabet & A ) const;

    /**
     * Finds a quadrant change in 'this' Freeman chain and returns the
     * position as an iterator. A quadrant change is some
     * @code
     (abc)*bc...cd
     |
     iterator
     * @endcode
     *
     * This quadrant change also guarantees that is not a place where a
     * convexity change occurs in the combinatorial MLP algorithm.
     *
     * The alphabet is possibly re-ordered so that b > c > d > a.
     *
     * @param A (possibly updated) a Freeman chain alphabet, possibly
     * re-ordered so that b > c > d > a.
     *
     * @return an iterator on 'this' that points on the first letter c.
     */
    //BK
    typename Self::ConstIterator
      findQuadrantChange4( OrderedAlphabet & A ) const ;


    /**
     * Test if the FreemanChain ends at the same point it starts. Take (1)
     * operation since the last point has been stored at initialization.
     *
     * @return 'true' if the path is closed, 'false' otherwise.
     */
    int isClosed() const ;


    /**
     * This method takes O(n) operations. It determines if the FreemanChain
     * corresponds to a closed contour, and if this is the case, determines how
     * many counterclockwise loops the contour has done. Of course, it the
     * contour has done clockwise loops, then the given number is accordingly
     * negative.
     *
     * @return the number of counterclockwise loops, or '0' if the contour
     * is open or invalid.
     */
    int ccwLoops() const ;


    /**
     * Computes the point where starts the step at position 'pos' of the
     * FreemanChain. If 'pos' is equal to the length of the FreemanChain then
     * the last point is returned.
     *
     * Note: for a chain of length 'n' the computation time in O( min( pos, n-pos ) ).
     *
     * @param pos the position of the point in the FreemanChain
     * @return the point at position 'pos'.
     */
    Point getPoint ( Index pos ) const;
    

    /**
     * @return the starting point of the FreemanChain.
     */
    Point firstPoint ( ) const
    {
      return Point(x0,y0);
    }


    /**
     * @return the starting point of the FreemanChain.
     */
    Point lastPoint ( ) const
    {
      return Point(xn,yn);
    }


    /**
     * @return the vector given by displacement from the first point to the
     * last point.
     */
    Vector totalDisplacement() const
    {
      return lastPoint() -  firstPoint();
    }
   

    /**
     * Add one symbol at the end of the FreemanChain
     * @return reference to this.
     */
    FreemanChain & extend(char code);

    /**
     * Removes 'n' symbols at the end of the FreemanChain.
     * @return reference to this.
     */
    FreemanChain & retract(Size n = 1);

    





    ///////////////////////////////////////////////////////////////////////////////
    // ----------------------- Iteration services ------------------------------
    
    /**
     * Iterator service on points.
     * @return an iterator pointing on the first point of the chain.
     */
    ConstIterator begin() const;


    /**
     * Iterator service on points.
     * @return an iterator pointing after the last point of the chain.
     */
    ConstIterator end() const;

    /**
     * Returns the next position in the chain code. The path coded by the chain
     * code is assumed to be closed so that the position after the last letter
     * is the first one.  
     * @param pos a position in the chain code.
     * @return the next position.
     */
    Index next( Index pos ) const;


    /**
     * Returns the previous position in the chain code. The path coded by the
     * chain code is assumed to be closed so that the position before the first
     * letter is the first last one.  
     * @param pos a position in the chain code.
     * @return the previous position.
     */
    Index previous( Index pos ) const;


    // ------------------------- Static services -----------------------
    
  public:

    /**
     * Outputs the chain [c] to the stream [out].
     * @param out any output stream,
     * @param c a Freeman chain.
     */
    static void write( std::ostream & out, const FreemanChain & c )
    {
      out << c.x0 << " " << c.y0 << " " << c.chain << std::endl;
    }


    /**
     * Reads a chain from the stream [in] and updates [c].
     * @param in any input stream,
     * @param c (returns) the Freeman chain.
     */
    static void read( std::istream & in, FreemanChain & c );

    /**
     * Reads a chain from the points range [ @a itBegin , @a itEnd ) and updates @a c.
     * @param itBegin  begin iterator,
     * @param itEnd  end iterator,
     * @param c  the returned Freeman chain.
     * @tparam TConstIterator  type of iterator
     */
    template<typename TConstIterator>
    static void readFromPointsRange( const TConstIterator& itBegin, const TConstIterator& itEnd, FreemanChain & c );
    
    /**
     * Reads a chain from the points range @a aRange and updates @a c.
     * @param aRange  any points range
     * @param c  the returned Freeman chain
     * @tparam TRange  type of points range
     */
    template<typename TRange>
    static void readFromPointsRange( const TRange& aRange, FreemanChain & c );
    
    /**
     * Return a vector containing all the integer points of the freemanchain.
     *
     * @param fc the FreemanChain
     * @param aVContour (returns) the vector containing all the integer contour points.
     */
    static void getContourPoints(const FreemanChain & fc, 
                                 std::vector<Point> & aVContour );
    

    /**
     * Return a set containing all the linels (given as Signed SCell
     * in a KhalimskySpaceND) of a FreemanChain (given Z2). Since by
     * definition the interpixel elements cannot be represented in Z2,
     * we use a proper KhalimskySpaceND with a shift defined by
     * convention to (-0.5, 0.5).  Notes that this shift is the same
     * that the one used to display FreemanChain object in interpixel
     * mode.
     *     
     * @param aKSpace the KSpace
     * @param fc the FreemanChain
     * @param aSCellContour (returns) the set containing all the linels of the inter-pixels contour.
     * @param aFlagForAppend if set to true the resulting set is appended to initial set.  
     */

    static void getInterPixelLinels(const KhalimskySpaceND<2,  TInteger> & aKSpace, 
                                    const FreemanChain & fc, 
                                    typename KhalimskySpaceND<2, TInteger>::SCellSet & aSCellContour,
                                    bool aFlagForAppend=false);
    

    
    
    /**
     * Translate a point by the displacement given a code from a FreemanChain
     *
     * @param aPoint the point to translate
     * @param aCode  a FreemanChain code
     */
    //static void movePointFromFC(Point & aPoint, unsigned int aCode );
    static void movePointFromFC(Point & aPoint, char aCode );


    // Deprecated
    //
    // /**
    //  * @param aZero (returns) the '0' or 'x' letter for quadrant [quadrant].
    //  * @param aOne (returns) the '1' or 'y' letter for quadrant [quadrant].
    //  * @param aQuadrant the quadrant as any of '0', '1', '2', or '3'.
    //  */
    // static void alphabet( char & aZero, char & aOne, char aQuadrant )


    /**
     * Given two consecutive moves on a Freeman chain code, this
     * method returns the type of movement: 0: return move, 1: turning
     * toward the interior, 2: going straight, 3: turning toward
     * exterior. Interior/exterior is specified by [ccw].
     *
     * @param aCode1 the code of the first step as an integer in 0..3.
     * @param aCode2 the code of the second step as an integer in 0..3.
     * @param ccw 'true' if the contour is seen counterclockwise with
     * its inside to the left.
     * @return the type of movement given by aCode1 and aCode2.
     */
    //static unsigned int movement( unsigned int aCode1, unsigned int aCode2,
    //    bool ccw = true ); 
    static char movement( char aCode1, char aCode2,
        bool ccw = true ); 

    /**
     * Increment (or decrement if negative) the code by 'n'. 
     * '0' + 1 = '1', '1' + 1 = '2', ... , '3' + 1 = '0'
     * @param code the initial code.
     * @param n the number to add/remove to the code
     * @return 'code' increment 'n' times.
     */
    static char addToCode( char code, int n);


    /**
     * @return the Freeman code associated to given points (0,1,2, or
     * 3). If the direction between the two points differs from these
     * directions it returns 8.
     *
     * @param[in] dx  the x-displacement.
     * @param[in] dy  the y-displacement.
     * 
     **/
    static short freemanCode4C(int dx, int dy);

    

    /**
     * Returns the displacement vector of a Freeman code.
     *
     * @param dx (returns) the x-displacement.
     * @param dy (returns) the y-displacement.
     * @param aCode the code.
     */
    // static void displacement( int & dx, int & dy, unsigned int aCode );
    static void displacement( int & dx, int & dy, char aCode );


    
    /**
     * @param aCode a Freeman code (between 0-3).
     * Returns the displacement vector of the Freeman code.
     */
    // static Point displacement( unsigned int aCode );
    static Point displacement( char aCode );


    /**
     * Computes the code obtain from another one after a rotation by pi/2.
     * @param aCode any Freeman code.
     *
     * @param ccw when 'true' turns counterclockwise (or left),
     * otherwise turns clockwise (right).
     *
     * @return the turned code.
     */
    // static unsigned int turnedCode( unsigned int aCode, bool ccw = true );
    static char turnedCode( char aCode, bool ccw = true );


    /**
     * From the Freeman chain [pl_chain] representing a pointel
     * 4-connected contour, constructs the Freeman chain [pix_chain]
     * that represents its inner 4-connected border of pixels. The
     * Freeman chain [pl_chain] has its inside to the left (ie. ccw).
     *
     * Note that chain codes going back and forth are @b never considered
     * useless: it means that the chain is always supposed to have its
     * interior to the left (ccw) or right (cw) even at configurations
     * "02", "13", "20", "31".
     *
     * @param aPixChain (output) the code of the 4-connected inner border.
     *
     * @param aPl2pix (output) the mapping associating pointels to
     * pixels as indices in their respective Freeman chain.
     *
     * @param aPix2pl (output) the inverse mapping associating pixels to
     * pointels as indices in their respective Freeman chain.
     *
     * @param aPlChain the input code of the 4-connected pointel contour.
     */
    static void pointel2pixel( FreemanChain & aPixChain,
             std::vector<unsigned int> & aPl2pix,
             std::vector<unsigned int> & aPix2pl,
             const FreemanChain & aPlChain )
    {
      innerContour( aPixChain, aPl2pix, aPix2pl, aPlChain, true );
    };

    /**
     * From the Freeman chain [outer_chain] representing a 4-connected
     * contour, constructs the Freeman chain [inner_chain] that
     * represents its inner 4-connected contour (which lies in its
     * interpixel space). The boolean [ccw] specifies if the inside is
     * to the left (ccw) or to the right (cw).
     *
     * Note that chain codes going back and forth are @b never considered
     * useless: it means that the chain is always supposed to have its
     * interior to the left (ccw) or right (cw) even at configurations
     * "02", "13", "20", "31".
     *
     * @param aInnerChain (output) the code of the 4-connected inner
     * border, with starting coordinates that are floored to the closest
     * integer.
     *
     * @param aOuter2inner (output) the mapping associating outer to
     * inner elements as indices in their respective Freeman chain.
     *
     * @param aInner2outer (output) the mapping associating inner to
     * outer elements as indices in their respective Freeman chain.
     *
     * @param aOuterChain the input code of the 4-connected contour.
     *
     * @param ccw 'true' if the contour is seen counterclockwise with
     * its inside to the left.
     */
    static void innerContour( FreemanChain & aInnerChain,
            std::vector<unsigned int> & aOuter2inner,
            std::vector<unsigned int> & aInner2outer,
            const FreemanChain & aOuterChain,
            bool ccw = true );


    /**
     * Removes outer spikes along a 4-connected contour, meaning steps
     * "02", "13", "20" or "31", which point outside the shape. The
     * inside is given by parameter [ccw]. Note that 4-connected
     * pointel contours should not have any outer spikes, while
     * 4-connected pixel contours should not have any inner spikes.
     *
     * @param aCleanC (output) the cleaned 4-connected contour.
     *
     * @param aC2clean (output) the mapping associating an element to
     * its clean element.
     *
     * @param aClean2c (output) the inverse mapping associating a
     * clean element to its non-clean element.
     *
     * @param c the input code of the 4-connected contour (should be a loop !).
     *
     * @param ccw 'true' if the contour is seen counterclockwise with
     * its inside to the left.
     *
     * @return 'true' if the contour add an interior, 'false' otherwise.
     */
    static bool cleanOuterSpikes( FreemanChain & aCleanC,
          std::vector<unsigned int> & aC2clean,
          std::vector<unsigned int> & aClean2c,
          const FreemanChain & c,
          bool ccw = true );
    



    // ----------------------- Interface --------------------------------------
    
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const ;


    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const ;



    // ----------------------- Drawing services --------------------------------

  public:

    /**
     * Default drawing style object.
     * @return the dyn. alloc. default style for this object.
     */
    //DrawableWithBoard2D* defaultStyle( std::string mode = "" ) const;
 

    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;

    // ------------------------- Public Datas ------------------------------

  public:
    /**
     * The chain code.
     */
    std::string chain;

    /**
     * the x-coordinate of the first point.
     */
    Integer x0;

    /**
     * the y-coordinate of the first point.
     */
    Integer y0;

    /**
     * the x-coordinate of the last point.
     */
    Integer xn;

    /**
     * the y-coordinate of the last point.
     */
    Integer yn;

    
    // ------------------------- Internals ------------------------------------
    

  private:

    /**
     * Default constructor
     * Not valid.
     */
   // FreemanChain() {};

    /**
     * Computes the coordinates of the last point.
     * nb: in O(n)
     */
    void computeLastPoint();

  public:


  }; // end of class FreemanChain




  /**
   * Overloads 'operator<<' for displaying objects of class 'FreemanChain'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'FreemanChain' to write.
   * @return the output stream after the writing.
   */
  template<typename TInteger>
    std::ostream&
    operator<< ( std::ostream & out, const FreemanChain<TInteger> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods.
#include "DGtal/geometry/curves/FreemanChain.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined FreemanChain_h

#undef FreemanChain_RECURSES
#endif // else defined(FreemanChain_RECURSES)
