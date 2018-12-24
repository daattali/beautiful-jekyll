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
 * @file ArithmeticalDSSComputer.h 
 * @author Tristan Roussillon (\c
 * tristan.roussillon@liris.cnrs.fr ) Laboratoire d'InfoRmatique en
 * Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS,
 * France
 *
 * @date 2010/07/01
 *
 * @brief Header file for module ArithmeticalDSSComputer.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see ArithmeticalDSSComputer.cpp testArithDSS.cpp
 */

#if defined(ArithmeticalDSSComputer_RECURSES)
#error Recursive header files inclusion detected in ArithmeticalDSSComputer.h
#else // defined(ArithmeticalDSSComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ArithmeticalDSSComputer_RECURSES

#if !defined ArithmeticalDSSComputer_h
/** Prevents repeated inclusion of headers. */
#define ArithmeticalDSSComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <list>
#include "DGtal/base/Exceptions.h"
#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/base/ReverseIterator.h"
#include "DGtal/geometry/curves/ArithmeticalDSS.h"
//////////////////////////////////////////////////////////////////////////////


namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // class ArithmeticalDSSComputer
  /**
   * \brief Aim: This class is a wrapper around ArithmeticalDSS that is devoted 
   * to the dynamic recognition of digital straight segments (DSS) along any 
   * sequence of digital points. 
   *
   * See @ref moduleArithDSSReco for further details. See also classes 
   * NaiveDSS8Computer and StandardDSS4Computer, which are aliases of this class. 
   *
   * @tparam TIterator type of iterator on 2d digital points,
   * at least readable and forward. 
   * @tparam TInteger type of integers used for the computation of remainders, 
   * which is a model of CInteger.  
   * @tparam adjacency an unsigned integer equal to 4 for standard 
   * (simply 4-connected) DSS or 8 for naive (simply 8-connected) DSS (default). 
   *
   * This class is a model of CDynamicBidirectionalSegmentComputer. 
   * It is also default constructible, copy constructible, assignable and equality comparable. 
   *
   * @see ArithmeticalDSS NaiveDSS StandardDSS 
   * @see exampleArithmeticalDSS.cpp exampleArithmeticalDSSComputer.cpp
   */
  template <typename TIterator, 
    typename TInteger = typename IteratorCirculatorTraits<TIterator>::Value::Coordinate, 
    unsigned short adjacency = 8>
  class ArithmeticalDSSComputer
  {

    // ----------------------- inner types ------------------------------
  public:

    /**
     * Type of iterator, at least readable and forward
     */
    typedef TIterator ConstIterator;
    BOOST_CONCEPT_ASSERT(( boost_concepts::ReadableIteratorConcept<ConstIterator> )); 
    BOOST_CONCEPT_ASSERT(( boost_concepts::ForwardTraversalConcept<ConstIterator> )); 

    /**
     * Type of 2d digital point
     */
    typedef typename IteratorCirculatorTraits<ConstIterator>::Value Point; 
    BOOST_STATIC_ASSERT(( Point::dimension == 2 ));

    /**
     * Type of coordinate
     */
    typedef typename IteratorCirculatorTraits<TIterator>::Value::Coordinate Coordinate; 
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<Coordinate> ));

    /**
     * Type of integer, devoted to remainders (and intercepts)
     */
    typedef TInteger Integer;
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<Integer> ));

    /**
     * Type of objects that represents DSSs 
     */
    typedef ArithmeticalDSS<Coordinate, Integer, adjacency> DSS; 
    //we expect that the iterator type returned DGtal points, used in the DSS representation
    BOOST_STATIC_ASSERT(( concepts::ConceptUtils::SameType< Point, typename DSS::Point >::value ));

    /**
     * Type of primitive representation, defined as an alias of DSS 
     */
    typedef DSS Primitive; 

    /**
     * Type of vector, defined as an alias of point
     */
    typedef Point Vector; 

    typedef ArithmeticalDSSComputer<ConstIterator,TInteger,adjacency> Self; 
    typedef ArithmeticalDSSComputer<ReverseIterator<ConstIterator>,TInteger,adjacency> Reverse;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Default constructor.
     * not valid
     */
    ArithmeticalDSSComputer();

    /**
     * Constructor with initialisation
     * @param it an iterator on 2D points
     * @see init
     */
    ArithmeticalDSSComputer(const ConstIterator& it);

    /**
     * Initialisation.
     * @param it an iterator on 2D points
     */
    void init(const ConstIterator& it);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    ArithmeticalDSSComputer ( const ArithmeticalDSSComputer & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    ArithmeticalDSSComputer& operator= ( const ArithmeticalDSSComputer & other );

    /** 
     * @return a default-constructed instance of Self 
     */
    Self getSelf() const;

    /**
     * @return a default-constructed instance of Reverse
     */
    Reverse getReverse() const;
        
    /**
     * Equality operator.
     * @param other the object to compare with.
     * @return 'true' if the DSS representations
     * and the ranges of the two objects match,
     * 'false' otherwise
     */
    bool operator==( const ArithmeticalDSSComputer & other ) const;

    /**
     * Difference operator.
     * @param other the object to compare with.
     * @return 'false' if equal
     * 'true' otherwise
     */
    bool operator!=( const ArithmeticalDSSComputer & other ) const;

    /**
     * Destructor.
     */
    ~ArithmeticalDSSComputer(){};

    // ----------------------- Interface --------------------------------------
  public:
     
    /**
     * Tests whether the current DSS can be extended at the front.
     *  
     * @return 'true' if yes, 'false' otherwise.
     */
    bool isExtendableFront();

    /**
     * Tests whether the current DSS can be extended at the back.
     *  
     * @return 'true' if yes, 'false' otherwise.
     */
    bool isExtendableBack();
    
    /**
     * Tests whether the current DSS can be extended at the front.
     * Computes the parameters of the extended DSS if yes.
     * @return 'true' if yes, 'false' otherwise.
     */
    bool extendFront();

    /**
     * Tests whether the current DSS can be extended at the back.
     * Computes the parameters of the extended DSS if yes.
     * @return 'true' if yes, 'false' otherwise.
     */
    bool extendBack();

    /**
     * Removes the front point of the DSS 
     * if it has more than two points
     * @return 'true' if the front point is removed, 'false' otherwise.
     */
    bool retractFront();

    /**
     * Removes the back point of the DSS
     * if it has more than two points
     * @return 'true' if the back point is removed, 'false' otherwise.
     */
    bool retractBack();


    // ------------------------- Accessors ------------------------------
    /**
     * @return the current DSS representation.
     * NB: since we return a const reference, you must
     * copy the result, if you want to keep it beyond 
     * the object's existence. 
     */
    const Primitive& primitive() const;
    /**
     * @return a-parameter of the DSS
     */
    Integer a() const;
    /**
     * @return b-parameter of the DSS
     */
    Integer b() const;
    /**
     * @return mu-parameter of the DSS
     */
    Integer mu() const;
    /**
     * @return omega-parameter of the DSS
     */
    Integer omega() const;
    /**
     * @return first upper leaning point.
     */
    Point Uf() const;
    /**
     * @return last upper leaning point.
     */
    Point Ul() const;
    /**
     * @return first lower leaning point.
     */
    Point Lf() const;
    /**
     * @return last lower leaning point.
     */
    Point Ll() const;
    /**
     * @return the first point of the DSS.
     */
    Point back() const ;
    /**
     * @return the last point of the DSS.
     */
    Point front() const ;
    /**
     * @return begin iterator of the DSS range.
     */
    ConstIterator begin() const;
    /**
     * @return end iterator of the DSS range.
     */
    ConstIterator end() const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;


    // ------------------ Useful tools -----------------------------------

    /**
     * Computes the remainder of a point
     * (that does not necessarily belong to the DSS)
     * @param it an iterator on points
     * @return the remainder of @a *it.
     */
    Integer remainder(const ConstIterator & it) const;

    /**
     * Computes the remainder of a point
     * (that does not necessarily belong to the DSS)
     * @param aPoint the point whose remainder is returned 
     * @return the remainder
     */
    Integer remainder( const Point& aPoint ) const;

    /**
     * Computes the position of a point
     * (that does not necessarily belong to the DSS)
     * @param it an iterator on points
     * @return the position of @a *it.
     */
    Integer position(const ConstIterator & it) const;

    /**
     * Computes the position of a point
     * (that does not necessarily belong to the DSS)
     * @param aPoint the point whose position is returned 
     * @return the position of @a aPoint.
     */
    Integer position( const Point& aPoint ) const;

    /**
     * Checks whether a point is in the bounding DSL
     * of minimal parameters 
     * @param aPoint the point to be checked 
     * @return 'true' if yes, 'false' otherwise
     */
    bool isInDSL( const Point& aPoint ) const;

    /**
     * Checks whether a point is in the bounding DSL
     * of minimal parameters 
     * @param it an iterator on the point to be checked
     * @return 'true' if yes, 'false' otherwise
     */
    bool isInDSL(const ConstIterator & it) const;

    /**
     * Checks whether a point belongs to the DSS or not
     * @param aPoint the point to be checked
     * @return 'true' if yes, 'false' otherwise
     */
    bool isInDSS( const Point& aPoint ) const;

    /**
     * Checks whether a point belongs to the DSS or not
     * @param it an iterator on the point to be checked
     * @return 'true' if yes, 'false' otherwise
     */
    bool isInDSS(const ConstIterator & it) const;


    // ------------------------- Hidden services ------------------------------
  private:


    // ------------------------- Protected Datas ------------------------------
  protected:

    /**
    * DSS representation
    */
    DSS myDSS; 
    /**
    * begin iterator
    */
    ConstIterator myBegin; 
    /**
    * end iterator
    */
    ConstIterator myEnd; 
    
    // ------------------ Display ------------------------------------------

  public:
    
    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const; 

    
  }; // end of class ArithmeticalDSSComputer


/**
 * Overloads 'operator<<' for displaying objects of class 'ArithmeticalDSSComputer'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'ArithmeticalDSSComputer' to write.
 * @return the output stream after the writing.
 */
template <typename TIterator, typename TInteger, unsigned short adjacency>
std::ostream&
operator<< ( std::ostream & out,  const ArithmeticalDSSComputer<TIterator,TInteger,adjacency> & object )
{
  object.selfDisplay( out);
  return out;
}

} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////
// Aliases
namespace DGtal
{
  /**
   * \brief Aim: This class is a wrapper around ArithmeticalDSS that is devoted 
   * to the dynamic recognition of standard and simply 4-connected digital 
   * straight segments (DSS) along any sequence of digital points. 
   *
   * Before using a DSS computer, you must include the following header: 
   * @snippet geometry/curves/exampleArithmeticalDSSComputer.cpp ArithmeticalDSSComputerHeader
   *
   * Then, you can construct a DSS computer as follows: 
   * @snippet geometry/curves/exampleArithmeticalDSSComputer.cpp ArithmeticalDSSComputerStandardCtor
   *
   * The extention is simply done as follows: 
   * @snippet geometry/curves/exampleArithmeticalDSSComputer.cpp ArithmeticalDSSComputerStandardExtension
   *
   * See @ref moduleArithDSSReco for further details. 
   *
   * @tparam TIterator type of iterator on 2d digital points,
   * at least readable and forward. 
   * @tparam TInteger type of integers used for the computation of remainders, 
   * which is a model of CInteger.  
   *
   * This class is a model of CDynamicBidirectionalSegmentComputer. 
   * It is also default constructible, copy constructible, assignable and equality comparable. 
   *
   * @see ArithmeticalDSSComputer NaiveDSS8Computer ArithmeticalDSS  
   * @see exampleArithmeticalDSSComputer.cpp exampleArithmeticalDSS.cpp 
   */
  template <typename TIterator, 
	    typename TInteger = typename IteratorCirculatorTraits<TIterator>::Value::Coordinate>
  class StandardDSS4Computer: 
    public ArithmeticalDSSComputer<TIterator, TInteger, 4>
  {
  public: 
    /**
     * Base class
     */
    typedef ArithmeticalDSSComputer<TIterator, TInteger, 4> Super;
    typedef typename Super::ConstIterator ConstIterator;

  public: 

    /**
     * Default constructor.
     * NB: not valid. 
     */
    StandardDSS4Computer (); 

    /**
     * Constructor with initialisation
     * @param it an iterator on 2d points
     */
    StandardDSS4Computer(const ConstIterator& it);

    /**
     * Copy constructor.
     * @param aOther the object to clone.
     */
    StandardDSS4Computer ( const StandardDSS4Computer & aOther ); 

    /**
     * Assignment.
     * @param aOther the object to copy.
     * @return a reference on 'this'.
     */
    StandardDSS4Computer & operator= ( const StandardDSS4Computer & aOther );

  }; 

  /**
   * \brief Aim: This class is a wrapper around ArithmeticalDSS that is devoted 
   * to the dynamic recognition of naive and simply 8-connected digital straight 
   * segments (DSS) along any sequence of digital points. 
   *
   * See @ref moduleArithDSSReco for further details. See also
   * exampleArithmeticalDSSComputer.cpp for a basic example using
   * StandardDSS4Computer. The use of NaiveDSS8Computer is quite similar. 
   *
   * @tparam TIterator type of iterator on 2d digital points,
   * at least readable and forward. 
   * @tparam TInteger type of integers used for the computation of remainders, 
   * which is a model of CInteger.  
   *
   * This class is a model of CDynamicBidirectionalSegmentComputer. 
   * It is also default constructible, copy constructible, assignable and equality comparable. 
   *
   * @see ArithmeticalDSSComputer StandardDSS4Computer ArithmeticalDSS  
   * @see exampleArithmeticalDSSComputer.cpp exampleArithmeticalDSS.cpp 
   */
  template <typename TIterator, 
	    typename TInteger = typename IteratorCirculatorTraits<TIterator>::Value::Coordinate>
  class NaiveDSS8Computer: 
    public ArithmeticalDSSComputer<TIterator, TInteger, 4>
  {
  public: 
    /**
     * Base class
     */
    typedef ArithmeticalDSSComputer<TIterator, TInteger, 4> Super; 
    typedef typename Super::ConstIterator ConstIterator;

  public: 

    /**
     * Default constructor.
     * NB: not valid. 
     */
    NaiveDSS8Computer (); 

    /**
     * Constructor with initialisation
     * @param it an iterator on 2d points
     */
    NaiveDSS8Computer(const ConstIterator& it);

    /**
     * Copy constructor.
     * @param aOther the object to clone.
     */
    NaiveDSS8Computer ( const NaiveDSS8Computer & aOther ); 

    /**
     * Assignment.
     * @param aOther the object to copy.
     * @return a reference on 'this'.
     */
    NaiveDSS8Computer & operator= ( const NaiveDSS8Computer & aOther );

  }; 

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods.
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ArithmeticalDSSComputer_h

#undef ArithmeticalDSSComputer_RECURSES
#endif // else defined(ArithmeticalDSSComputer_RECURSES)
