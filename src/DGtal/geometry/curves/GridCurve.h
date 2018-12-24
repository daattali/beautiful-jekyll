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
 * @file GridCurve.h
 * @author Tristan Roussillon (\c
 * tristan.roussillon@liris.cnrs.fr ) Laboratoire d'InfoRmatique en
 * Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS,
 * France
 *
 *
 * @date 2011/06/27
 *
 * @brief Header file for module GridCurve.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(GridCurve_RECURSES)
#error Recursive header files inclusion detected in GridCurve.h
#else // defined(GridCurve_RECURSES)
/** Prevents recursive inclusion of headers. */
#define GridCurve_RECURSES

#if !defined GridCurve_h
/** Prevents repeated inclusion of headers. */
#define GridCurve_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstddef>
#include <utility>

#include "DGtal/base/Common.h"
#include "DGtal/io/readers/PointListReader.h"
#include "DGtal/base/ConstAlias.h"

#include "DGtal/base/BasicFunctors.h"
#include "DGtal/base/Circulator.h"
#include "DGtal/base/ConstRangeAdapter.h"
#include "DGtal/base/ConstIteratorAdapter.h"

#include "DGtal/topology/CCellularGridSpaceND.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/SCellsFunctors.h"
#include "DGtal/topology/CanonicSCellEmbedder.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{



  /////////////////////////////////////////////////////////////////////////////
  // class GridCurve
  /////////////////////////////////////////////////////////////////////////////
    /**
    * @brief Aim: describes, in a cellular space of dimension n, 
    a closed or open sequence of signed d-cells (or d-scells), 
    d being either equal to 1 or (n-1). 

    For instance, the topological boundary of a simply connected 
    digital set is a closed sequence of 1-scells in 2d. 
     
    @tparam TKSpace Khalimsky space, a model of CCellularGridSpaceND
    
    Using the namespace Z2i, defined in StdDefs.h, you can instanciate a grid curve as follows:
    @snippet geometry/curves/exampleGridCurve2d.cpp GridCurveDeclaration

     This object provides several IO services. 
     For instance, you can read a grid curve from a data file, 
     which contains the (digital) coordinates of the 0-cells (pointels) in nd: 
    @snippet geometry/curves/exampleGridCurve2d.cpp GridCurveFromDataFile
    Note that if the first and last 0-scells of the file have the same coordinates (i)
     or if only one of their coordinates differ by 1 (ii), then the grid curve is considered
     as closed, ie. scells directly incident to the last signed cell and indirectly incident 
     to the first signed cell are the same.
     
     You can also build a grid curve from the contour of a digital set as follows: 
    @snippet geometry/curves/exampleGridCurve2d.cpp GridCurveFromDigitalSet
    
     To save a grid curve in a data file, GridCurve provides the special method writeVectorToStream():
    @snippet geometry/curves/exampleGridCurve2d.cpp GridCurveToDataFile
    
     The stream mechanism is used to display the true content of the grid curve: 
    @snippet geometry/curves/exampleGridCurve2d.cpp GridCurveStandardOutput

     In 2d, the grid curve can be drawn in a vector graphics file as follows:
    @snippet geometry/curves/exampleGridCurve2d.cpp GridCurveToGraphics
     See @ref moduleBoard2D to learn more about the 2d drawing mechanism
     used in DGtal. 

     Moreover, this object provides several ranges as nested types: 
    
     - SCellsRange to iterate over the d-scells
     - PointsRange to iterate over the digital coordinates of the 0-scells
     that are directly incident to the d-scells
     - MidPointsRange to iterate over the real coordinates of the d-scells
     - ArrowsRange to iterate over the arrows coding the 1-scells.
     Note that an arrow is a pair point-vector:
     the point codes the digital coordinates of the 1-scell, 
     the vector gives the topology and sign of the 1-scell. 
     - InnerPointsRange to iterate over the digital coordinates of the n-scells
     that are @e directly incident to the (n-1)-scells.  
      - OuterPointsRange to iterate over the digital coordinates of the n-scells
     that are @e indirectly incident to the (n-1)-scells.
     - IncidentPointsRange to iterate over the pairs of inner and outer points
     (defined as above)
     - CodesRange to iterate over the codes {0,1,2,3} of the 1-scells 
     (only available if n = 2)
    
     You can get an access to these eight ranges through the following methods: 

    - getSCellsRange()
    - getPointsRange()
    - getMidPointsRange()
    - getArrowsRange()
    - getInnerPointsRange()
    - getOuterPointsRange()
    - getIncidentPointsRange()
    - getCodesRange()
    
    Each range can be displayed in the standard output or can be drawn
    (except CodesRange) in a vector graphics file as shown in the 
    following snippet: 
    @snippet geometry/curves/exampleGridCurve2d.cpp GridCurveIncidentPointsRangeIO
    
     Moreover, each range has the following inner types: 

     - ConstIterator
     - ConstReverseIterator
     - ConstCirculator
     - ConstReverseCirculator

     And each range provides these (circular)iterator services: 

     - begin() : begin ConstIterator
     - end() : end ConstIterator
     - rbegin() : begin ConstReverseIterator
     - rend() : end ConstReverseIterator
     - c() : ConstCirculator
     - rc() : ConstReverseCirculator
     
     You can use these services to iterate over the elements of a given range
     as follows: 
     @snippet geometry/curves/exampleGridCurve2d.cpp GridCurveRangeIterators
         
    * @see exampleGridCurve2d.cpp testGridCurve.cpp
    */

  template <typename TKSpace = KhalimskySpaceND<2> >
  class GridCurve
  {

  public: 
    typedef TKSpace KSpace; 
    BOOST_CONCEPT_ASSERT(( concepts::CCellularGridSpaceND< KSpace > )); 
  
    typedef typename KSpace::Point Point;
    typedef typename KSpace::Point Vector;

    typedef typename KSpace::SCell SCell;
    typedef typename std::vector<SCell> Storage; 

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~GridCurve();

    /**
     * Constructor.
     * @param aKSpace the Khalimsky space where the grid curve lies. 
     */
    GridCurve( ConstAlias<KSpace> aKSpace);

    /**
     * Default Constructor.
     * (the underlying Khalimsky space is default constructed). 
     */
    GridCurve();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    GridCurve( const GridCurve & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    GridCurve & operator=( const GridCurve & other );

    // ----------------------- common ------------------------------

    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;

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

    // ----------------------- streams ------------------------------

    /**
     * Init.
     * @param in any input stream,
     */
    bool initFromVectorStream(std::istream & in );

    /**
     * Outputs the grid curve to the stream @a out.
     * @param out any output stream,
     */
    void writeVectorToStream( std::ostream & out );

    // ----------------------- Initializations ------------------------------

    /**
     * Deprecated name, use initFromPointsVector instead
     * Init.
     * @param aVectorOfPoints the vector containing a sequence of grid points (digital coordinates).
     * @see initFromPointsRange
     */
    bool initFromVector( const std::vector<Point>& aVectorOfPoints );

    /**
     * Init from a STL vector of points.
     * @param aVectorOfPoints the vector containing a sequence of grid points (digital coordinates).
     * @see initFromPointsRange
     */
    bool initFromPointsVector( const std::vector<Point>& aVectorOfPoints ); 

    /**
     * Init from a range of points.
     * @param itb begin iterator
     * @param ite end iterator
     */
    template <typename TIterator>
    bool initFromPointsRange( const TIterator& itb, const TIterator& ite );

    /**
     * Init from a STL vector of signed cells.
     * @param aVectorOfSCells the vector containing the sequence of signed cells. 
     * @see initFromSCellsRange
     */
    bool initFromSCellsVector( const std::vector<SCell>& aVectorOfSCells );

    /**
     * Init from a range of signed cells.
     * @param itb begin iterator
     * @param ite end iterator
     */
    template <typename TIterator>
    bool initFromSCellsRange( const TIterator& itb, const TIterator& ite );


    // ----------------------- open/closed ------------------------------


    /**
     * Checks whether the grid curve is open or closed. 
     * Signed cells directly incident to the last scell
     * and indirectly incident to the first scell
     * should be the same in case of a closed grid curve.
     *
     * @return 'true' if grid curve is closed, 'false' otherwise
     */
    bool isClosed() const;

    /**
     * @return 'true' if the grid curve is not closed, 'false' otherwise
     * @see isClosed
     */
    bool isOpen() const;

    // ----------------------- container interface ------------------------------

    typedef typename Storage::const_iterator const_iterator; 
    typedef typename Storage::const_iterator ConstIterator; 
    typedef typename Storage::const_reverse_iterator const_reverse_iterator; 
    typedef typename Storage::const_reverse_iterator ConstReverseIterator; 

    /**
     * @return begin iterator on scells
     */
    ConstIterator begin() const; 

    /**
     * @return end iterator on scells
     */
    ConstIterator end() const; 
     
    /**
     * @return reverse begin iterator on scells
     */
    ConstReverseIterator rbegin() const; 

    /**
     * @return reverse end iterator on scells
     */
    ConstReverseIterator rend() const; 

    /**
     * @return last scell
     */
    SCell back() const; 

    /**
     * Back insertion of @e aSCell
     * @param aSCell any signed cell
     * @see pushBack
     * NB: this alias is kept for STL compliance
     */
    void push_back(const SCell& aSCell); 

    /**
     * Back insertion of @e aSCell
     * @param aSCell any signed cell
     */
    void pushBack(const SCell& aSCell); 

    /**
     * @return number of scells
     */
    typename Storage::size_type size() const; 

    // ------------------------- private Datas --------------------------------
  private:
    /**
     * Pointer on a Khalimsky space
     */
    const KSpace* myKPtr;
    /**
     * bool equal to 'true' if this owns the Khalimsky space
     * but 'false' otherwise
     */
    bool myFlagIsOwned;

    /**
     * list of signed cells
     */
    Storage mySCells; 


    // ------------------------- Public Datas --------------------------------
  public:



    // ------------------------- Internal --------------------------------
  private:

    /**
     * @param aPoint any point
     * @param aVector any vector of L1 norm equal to 1
     * @return the signed 1-cell associated to a pair point - shift vector 
     * (both in digital coordinates)
     */
    SCell PointVectorTo1SCell(const Point& aPoint, const Vector& aVector);
    /**
     * @param aSCell any signed cell
     * @return 'true' if @a aSCell is within the underlying Khalimsky space
     * and 'false' otherwise
     */
    bool isInside(const SCell& aSCell) const;
    

    
    // ------------------------- inner classes --------------------------------

  public: 

    ///////////////////////// SCellsRange

    typedef ConstRangeAdapter< typename Storage::const_iterator, functors::Identity, SCell >  SCellsRange;

    /**
     * @return an instance of SCellsRange
     */
    SCellsRange getSCellsRange() const {
      return SCellsRange(mySCells.begin(), mySCells.end(), new functors::Identity() );
    } 

    ///////////////////////// PointsRange

    typedef ConstRangeAdapter< typename Storage::const_iterator, functors::SCellToPoint<KSpace>, Point >  PointsRange;

    /**
     * @return an instance of PointsRange
     */
    PointsRange getPointsRange() const {
      return PointsRange(mySCells.begin(), mySCells.end(), new functors::SCellToPoint<KSpace>(*myKPtr) );
    } 

    ///////////////////////// MidPointsRange

    typedef ConstRangeAdapter< typename Storage::const_iterator, CanonicSCellEmbedder<KSpace>,
                               typename KSpace::Space::RealPoint >  MidPointsRange; 

    /**
     * @return an instance of MidPointsRange
     */
    MidPointsRange getMidPointsRange() const {
      return MidPointsRange(mySCells.begin(), mySCells.end(), new CanonicSCellEmbedder<KSpace>(*myKPtr) );
    } 

    ///////////////////////// ArrowsRange

    typedef ConstRangeAdapter< typename Storage::const_iterator, functors::SCellToArrow<KSpace>, 
                               std::pair<Point,Vector> >  ArrowsRange; 

    /**
     * @return an instance of ArrowsRange
     */
    ArrowsRange getArrowsRange() const {
      return ArrowsRange(mySCells.begin(), mySCells.end(), new functors::SCellToArrow<KSpace>(*myKPtr) );
    } 

    ///////////////////////// InnerPointsRange

    typedef ConstRangeAdapter< typename Storage::const_iterator, functors::SCellToInnerPoint<KSpace>, 
                               Point >  InnerPointsRange; 

    /**
     * @return an instance of ArrowsRange
     */
    InnerPointsRange getInnerPointsRange() const {
      return InnerPointsRange(mySCells.begin(), mySCells.end(), new functors::SCellToInnerPoint<KSpace>(*myKPtr) );
    } 

    ///////////////////////// OuterPointsRange

    typedef ConstRangeAdapter< typename Storage::const_iterator, functors::SCellToOuterPoint<KSpace>, 
                               Point >  OuterPointsRange; 

    /**
     * @return an instance of OuterPointsRange
     */
    OuterPointsRange getOuterPointsRange() const {
      return OuterPointsRange(mySCells.begin(), mySCells.end(), new functors::SCellToOuterPoint<KSpace>(*myKPtr) );
    } 

    ///////////////////////// IncidentPointsRange

    typedef ConstRangeAdapter< typename Storage::const_iterator, functors::SCellToIncidentPoints<KSpace>, 
                               std::pair<Point, Point> >  IncidentPointsRange; 

    /**
     * @return an instance of IncidentPointsRange
     */
    IncidentPointsRange getIncidentPointsRange() const {
      return IncidentPointsRange(mySCells.begin(), mySCells.end(), new functors::SCellToIncidentPoints<KSpace>(*myKPtr) );
    } 
    ///////////////////////// CodesRange

    typedef ConstRangeAdapter< typename Storage::const_iterator, functors::SCellToCode<KSpace>, char >  CodesRange; 

    /**
     * @return an instance of CodesRange
     */
    typename GridCurve::CodesRange getCodesRange() const {
      return CodesRange( mySCells.begin(), mySCells.end(), new functors::SCellToCode<KSpace>(*myKPtr) );    
    } 

  }; // end of class GridCurve



  /**
   * Overloads 'operator<<' for displaying objects of class 'GridCurve'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'GridCurve' to write.
   * @return the output stream after the writing.
   */
  template<typename TKSpace>
  std::ostream&
  operator<< ( std::ostream & out, const GridCurve<TKSpace> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods.
#include "DGtal/geometry/curves/GridCurve.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined GridCurve_h

#undef GridCurve_RECURSES
#endif // else defined(GridCurve_RECURSES)
