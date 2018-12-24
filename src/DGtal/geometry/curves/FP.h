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
 * @file FP.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/01/26
 *
 * @brief Header file for module FP.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(FP_RECURSES)
#error Recursive header files inclusion detected in FP.h
#else // defined(FP_RECURSES)
/** Prevents recursive inclusion of headers. */
#define FP_RECURSES

#if !defined FP_h
/** Prevents repeated inclusion of headers. */
#define FP_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <list>
#include "DGtal/kernel/CInteger.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
#include "DGtal/base/Circulator.h"
#include "DGtal/base/Exceptions.h"
#include "DGtal/base/Common.h"
#include "DGtal/io/Color.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace detail 
  {
    /////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Aim: Abstract DSSDecorator for ArithmeticalDSSComputer.
     * Has 2 virtual methods returning the first and last leaning point: 
     * - firstLeaningPoint()
     * - lastLeaningPoint()
     *
     * @see DSSDecorator4ConvexPart DSSDecorator4ConcavePart
     * 
     * @tparam TDSS type devoted to DSS recognition
     * Must have a nested type 'Point' and four accessors: 
     *  Uf(), Ul(), Lf(), Ll()
     *
     */
    template <typename TDSS>
    class DSSDecorator 
    {
    public: 
      /**
       * Type of the underlying DSS
       */
      typedef TDSS DSS; 
    protected:
      /**
       *  Aliasing pointer to an instance of TDSS
       */
      TDSS* myDSS;
    public:
      /**
       * Tells whether the underlying segment can be extended or not
       * @return 'true' if extendable, 'false' otherwise
       */
      bool isExtendableFront() const
      {
        return myDSS->isExtendableFront(); 
      }
      /**
       * Extends the underlying segment (if possible)
       * @return 'true' if the segment has been extended,
       * 'false' otherwise
       */
      bool extendFront()
      {
        return myDSS->extendFront(); 
      }
      /**
       * Retracts the underlying segment (if possible)
       * @return 'true' if the segment has been retracted,
       * 'false' otherwise
       */
      bool retractBack()
      {
        return myDSS->retractBack(); 
      }
      /**
       * End of the underlying segment
       * @return end iterator of the underlying segment
       */
      typename DSS::ConstIterator end()
      {
        return myDSS->end(); 
      }

      /**
       * Destructor 
       * ( virtual to disable warnings [-Wdelete-non-virtual-dtor] )
       */
      virtual ~DSSDecorator() {}
      /**
       * First leaning point accessor 
       * @return the first upper or lower leaning point
       */
      virtual typename TDSS::Point firstLeaningPoint() const = 0;
      /**
       * Last leaning point accessor 
       * @return the last upper or lower leaning point
       */
      virtual typename TDSS::Point lastLeaningPoint() const = 0;
      /**
       * Tells whether it adapts a DSS computer for convex parts or not
       * @return 'true' for convex parts, 'false' for concave parts
       */
      virtual bool isInConvexPart() const = 0;
    };

    /**
     * \brief Aim: adapter for TDSS used by FP in CONVEX parts.
     * Has 2 methods: 
     * - firstLeaningPoint()
     * - lastLeaningPoint()
     *
     * They respectively return the first and last UPPER leaning point 
     * of the underlying instance of TDSS. 
     * 
     * @tparam TDSS type devoted to DSS recognition
     * Must have a nested type 'Point' and four accessors: 
     *  Uf(), Ul(), Lf(), Ll()
     *
     * @see DSSDecorator FP
     */
    template <typename TDSS>
    class DSSDecorator4ConvexPart : public DSSDecorator<TDSS> 
    {
    public:
      /**
       * Constructor
       * @param aDSS the DSS to decorate
       */
      DSSDecorator4ConvexPart(TDSS& aDSS)
      {
	this->myDSS = &aDSS;
      }
      /**
       * First leaning point accessor 
       * @return the first upper leaning point
       */
      typename TDSS::Point firstLeaningPoint() const 
      {
        return this->myDSS->Uf();
      }
      /**
       * Last leaning point accessor 
       * @return the last upper leaning point
       */
      typename TDSS::Point lastLeaningPoint() const
      {
        return this->myDSS->Ul();
      }
      /**
       * Tells whether it adapts a DSS computer for convex parts or not
       * @return 'true'
       */
      bool isInConvexPart() const { return true; }

    };

    /**
     * \brief Aim: adapter for TDSS used by FP in CONCAVE parts.
     * Has 2 methods: 
     * - firstLeaningPoint()
     * - lastLeaningPoint()
     *
     * They respectively return the first and last LOWER leaning point 
     * of the underlying instance of TDSS. 
     * 
     * @tparam TDSS type devoted to DSS recognition
     * Must have a nested type 'Point' and four accessors: 
     *  Uf(), Ul(), Lf(), Ll()
     *
     * @see DSSDecorator FP
     */
    template <typename TDSS>
    class DSSDecorator4ConcavePart : public DSSDecorator<TDSS> 
    {
    public:
      /**
       * Constructor
       * @param aDSS the DSS to decorate
       */
      DSSDecorator4ConcavePart(TDSS& aDSS)
      {
        this->myDSS = &aDSS;
      }
      /**
       * First leaning point accessor 
       * @return the first lower leaning point
       */
      typename TDSS::Point firstLeaningPoint() const 
      {
        return this->myDSS->Lf();
      }
      /**
       * Last leaning point accessor 
       * @return the last lower leaning point
       */
      typename TDSS::Point lastLeaningPoint() const
      {
        return this->myDSS->Ll();
      }
      /**
       * Tells whether it adapts a DSS computer for convex parts or not
       * @return 'false'
       */
      bool isInConvexPart() const { return false; }
    };

  } //end namespace detail
  /////////////////////////////////////////////////////////////////////////////


  /////////////////////////////////////////////////////////////////////////////
  // template class FP
  /**
   * \brief Aim: Computes the faithful polygon (FP)
   * of a range of 4/8-connected 2D Points. 
   * 
   * The FP has several interesting properties: 
   *  - its vertices are points of the underlying digital curve, thus with integer coordinates, 
   *  - it respects the convex and concave parts of the underlying digital curve,
   *  - it is reversible, 
   *  - it is unique for digital curves that are not digital straight segments,
   *  - it is closed to the minimum length polygon (MLP) (and converges toward the MLP
   * as the resolution tends to the infinity) for closed digital curves.  
   *
   * It is computed in the course of the maximal digital straight segments computation,
   * because in convex parts (resp. concave parts), the first and last upper (resp. lower) 
   * leaning points of segments that are maximal at the front or at the back are also
   * vertices of the FP.
   * 
   * @see ArithmeticalDSSComputer DSSDecorator DSSDecorator4ConvexPart DSSDecorator4ConcavePart
   *
   * @note T. ROUSSILLON and I. SIVIGNON, 
   * Faithful polygonal representation of the convex and concave parts of a digital curve, 
   * Pattern Recognition, Volume 44, Issues 10-11, October-November 2011, Pages 2693-2700. 
   *
   * Usage:
   * @code
   //r is a range of 4-connected 2D points
   FP<ConstIterator, Integer, 4> theFP( r .begin(), r.end() );
   * @endcode
   *
   * Once the FP is computed, copyFP() is a way of geting its vertices. 
   * In the same way, copyMLP() is a way of getting the vertices of the MLP. 
   * 
   * @tparam TIterator  type ConstIterator on 2D points, 
   * @tparam TInteger (satisfying CInteger) 
   * @tparam connectivity
   * 4 for standard (4-connected) DSS or 8 for naive (8-connected) DSS. 
   * (Any other integers act as 8). 
   *
   * @see testFP.cpp
   */
  template <typename TIterator, typename TInteger, int connectivity>
  class FP
  {

    // ----------------------- Types ------------------------------
  public:


    BOOST_CONCEPT_ASSERT(( concepts::CInteger<TInteger> ) );
    
    typedef DGtal::PointVector<2,TInteger> Point;
    typedef DGtal::PointVector<2,TInteger> Vector;
    
    typedef DGtal::PointVector<2, double> RealPoint;
    typedef DGtal::PointVector<2, double> RealVector;
    
    typedef DGtal::ArithmeticalDSSComputer<TIterator,TInteger,connectivity> DSSComputer;
    
    typedef std::list<Point> Polygon;
    


    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor.
     * @param itb  begin iterator
     * @param ite  end iterator
     */
    FP(const TIterator& itb, const TIterator& ite);
  
    /**
     * Destructor.
     */
    ~FP();

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * @return the list where each vertex of the FP is stored.
     */
    const Polygon& polygon() const;
    
    /**
     * @return true if the list has to be consider as circular.
     */
    bool isClosed() const;


    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;


    /**
     * @return number of FP vertices
     */
    typename Polygon::size_type size() const;


    /**
     * @return the vertices of the FP
     * NB: O(n)
     */
    template <typename OutputIterator>
    OutputIterator copyFP(OutputIterator result) const; 

    /**
     * @return the vertices of the MLP
     * NB: O(n)
     */
    template <typename OutputIterator>
    OutputIterator copyMLP(OutputIterator result) const; 


    // ------------------------- Protected Datas ------------------------------
  private:
    
    // ------------------------- Private Datas --------------------------------
  private:

    /**
     * List where each vertex of the FP is stored
     */
    Polygon myPolygon;

  protected:



    // ------------------------- Hidden services ------------------------------
  private:

    /**
     * A DSS adapter is returned according to the local convexity/concavity
     * @param aDSS a DSS lying on the range to process
     * @return an adapter to @a aDSS for convex or concave part
     *
     * @tparam Adapter type that adapts a DSS computer 
     * @see details::DSSDecorator details::DSSDecorator4ConvexParts details::DSSDecorator4ConcaveParts
     */
    template<typename Adapter>
    Adapter* initConvexityConcavity( typename Adapter::DSS &aDSS );

    /**
     * Removing step
     * @param adapter an Adapter to the current DSS
     * @return 'false' if the underlying digital curve 
     * is detected as disconnected and 'true' otherwise
     *
     * @tparam Adapter type that adapts a DSS computer 
     * @see details::DSSDecorator details::DSSDecorator4ConvexParts details::DSSDecorator4ConcaveParts
     */
    template<typename Adapter>
    bool removingStep( Adapter* adapter );

    /**
     * Adding step in the open case
     * @param adapter an Adapter to the current DSS
     * @param itEnd end iterator used to stop the algorithm 
     * (when @a currentDSS.end() == @a itEnd )
     * @return 'false' if the algorithm has to stop
     * and 'true' otherwise
     *
     * @tparam Adapter type that adapts a DSS computer 
     * @see details::DSSDecorator details::DSSDecorator4ConvexParts details::DSSDecorator4ConcaveParts
     */
    template<typename Adapter>
    bool addingStep( Adapter* adapter, 
		     const typename Adapter::DSS::ConstIterator& itEnd );

    /**
     * Adding step in the closed case
     * @param adapter an Adapter to the current DSS
     *
     * @tparam Adapter type that adapts a DSS computer 
     * @see details::DSSDecorator details::DSSDecorator4ConvexParts details::DSSDecorator4ConcaveParts
     */
    template<typename Adapter>
    void addingStep( Adapter* adapter );


    /**
     * Main algorithm
     * @param itb  begin iterator
     * @param ite  end iterator
     */
    void algorithm(const TIterator& itb, const TIterator& ite);

    /**
     * Main algorithm overloading for classic iterator types
     * (process as open)
     * @param itb  begin iterator
     * @param ite  end iterator
     */
    void algorithm(const TIterator& itb, const TIterator& ite, IteratorType );

    /**
     * Main algorithm overloading for circular iterator types
     * (process as closed)
     * @param itb  begin iterator
     * @param ite  end iterator
     */
    void algorithm(const TIterator& itb, const TIterator& ite, CirculatorType );



    // ------------------------- Hidden helpers ------------------------------

    /**
     * Checks if a turn defined by three consecutive vertices of the FP is valid or not
     * @param a previous vertex of the FP
     * @param b current vertex of the FP
     * @param c next vertex of the FP
     * @return 'true' if valid, 'false' otherwise.
     */
    bool isValid(const Point& a,const Point& b, const Point& c) const;

    /**
     * Returns the quadrant number of a vector
     * @param v any vector
     * @param q a quandrant number (0,1,2 or 3)
     * @return 'true' if @a v lies in quadrant number @a q, 'false' otherwise
     */
    bool quadrant (const Vector& v, const int& q) const;

    /**
     * Gets a MLP vertex from three consecutive vertices of the FP.
     * @param a previous vertex of the FP
     * @param b current vertex of the FP
     * @param c next vertex of the FP
     * @return vertex of the MLP, which is 
     * the tranlated of @a b by (+- 0.5, +- 0.5)
     */
    RealPoint getRealPoint (const Point& a,const Point& b, const Point& c) const;


    // ----------------------------------------------------------------------
    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    FP ( const FP & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    FP & operator= ( const FP & other );

    // ------------------------- Display ------------------------------------
  public: 

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;
    
    
    // --------------- CDrawableWithBoard2D realization --------------------
  public:

    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;

  }; // end of class FP


  /**
   * Overloads 'operator<<' for displaying objects of class 'FP'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'FP' to write.
   * @return the output stream after the writing.
   */
  template <typename TIterator, typename TInteger, int connectivity>
  std::ostream&
  operator<< ( std::ostream & out, const FP<TIterator,TInteger,connectivity> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/FP.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined FP_h

#undef FP_RECURSES
#endif // else defined(FP_RECURSES)
