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
 * @file SaturatedSegmentation.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/07/21
 *
 * @brief Header file for module SaturatedSegmentation.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SaturatedSegmentation_RECURSES)
#error Recursive header files inclusion detected in SaturatedSegmentation.h
#else // defined(SaturatedSegmentation_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SaturatedSegmentation_RECURSES

#if !defined SaturatedSegmentation_h
/** Prevents repeated inclusion of headers. */
#define SaturatedSegmentation_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/geometry/curves/SegmentComputerUtils.h"
#include "DGtal/geometry/curves/CForwardSegmentComputer.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  
  /////////////////////////////////////////////////////////////////////////////
  // template class SaturatedSegmentation
  /**
   * Description of template class 'SaturatedSegmentation' <p>
   * \brief Aim: Computes the saturated segmentation, that is
   * the whole set of maximal segments within a range given by 
   * a pair of ConstIterators (maximal segments are segments
   * that cannot be included in greater segments). 
   *
   * This class is a model of CSegmentation.
   * 
   * @tparam TSegmentComputer at least a model of CForwardSegmentComputer
   * (an online algorithm for the recognition of a given class of segments). 
   *
   * In the short example below, a digital curve stored in a STL vector
   * is decomposed into maximal 8-connected DSSs whose parameters are sent to 
   * the standard output.
   * @code 
   
  //types definition
  typedef PointVector<2,int> Point;
  typedef std::vector<Point> Range;
  typedef Range::const_iterator ConstIterator;
  typedef ArithmeticalDSSComputer<ConstIterator,int,8> SegmentComputer;
  typedef SaturatedSegmentation<SegmentComputer> Segmentation;

  //input points
  Range curve;
  curve.push_back(Point(1,1));
  curve.push_back(Point(2,1));
  curve.push_back(Point(3,2));
  curve.push_back(Point(4,2));
  curve.push_back(Point(5,2));
  curve.push_back(Point(6,2));
  curve.push_back(Point(7,2));
  curve.push_back(Point(8,1));
  curve.push_back(Point(9,1));

  //Segmentation
  SegmentComputer recognitionAlgorithm;
  Segmentation theSegmentation(curve.begin(), curve.end(), recognitionAlgorithm);
         
  Segmentation::SegmentComputerIterator i = theSegmentation.begin();
  Segmentation::SegmentComputerIterator end = theSegmentation.end();
  for ( ; i != end; ++i) {
    SegmentComputer current(*i);
    trace.info() << current << std::endl;  //standard output
  } 

   * @endcode
   *
   * If you want to get the saturated segmentation of a part of the 
   * digital curve (not the whole digital curve), you can give 
   * the range to process as a pair of iterators when calling 
   * the setSubRange() method as follow: 
   * @code 
  theSegmentation.setSubRange(beginIt, endIt);
   * @endcode   
   *
   * Obviously, [beginIt, endIt) has to be a valid range included
   * in the wider range [curve.begin(), curve.end()). 
   *
   * Moreover, the segmentation at the ends depends of the 
   * underlying digital curve. Among the whole set of  
   * maximal segments that pass through the first (resp. last) 
   * element of the range, one maximal segment must be chosen
   * as the first (resp. last) retrieved maximal segments. 
   * Several processing modes are therefore available: 
   * - "First" and "First++" 
   * - "MostCentered" (default) and "MostCentered++" 
   * - "Last" and "Last++"
   *
   * The mode i indicates that the segmentation begins with 
   * the i maximal segment passing through the first element
   * and ends with the i maximal segment passing through 
   * the last element. The last retrieved segment of the segmentation
   * is not included in the simple "XXX" modes, but is included
   * in the "XXX++" modes.
   *
   * For instance, in the default mode "MostCentered", the 
   * segmentation begins with the most centered maximal segment
   * passing through the first element and ends (without including it)
   * with the most centered maximal segment passing through the last 
   * element. This mode is basically used to process a whole circular 
   * structure so that the first maximal segment is not retrieved twice.
   * However, in order to include the most centered maximal segment 
   * passing through the last element in a subpart, you should use the 
   * "MostCentered++" mode. 
   * 
   * In order to set a mode (before getting a SegmentComputerIterator),
   * use the setMode() method as follow: 
   * @code 
  theSegmentation.setMode("First");
   * @endcode  
   * 
   * @see testSegmentation.cpp
   */

  template <typename TSegmentComputer>
  class SaturatedSegmentation
  {

  public: 

    BOOST_CONCEPT_ASSERT(( concepts::CForwardSegmentComputer<TSegmentComputer> ));
    typedef TSegmentComputer SegmentComputer;
    typedef typename SegmentComputer::ConstIterator ConstIterator;

  private: 

    typedef typename TSegmentComputer::Reverse ReverseSegmentComputer;
    typedef typename ReverseSegmentComputer::ConstIterator ConstReverseIterator;

    // ----------------------- Standard services ------------------------------
  public:



  /////////////////////////////////////////////////////////////////////////////
  // template class SegmentComputerIterator
  /**
   * Description of template class 'SaturatedSegmentation::SegmentComputerIterator'
   *  <p> \brief Aim: Specific iterator to visit all the maximal segments of a 
   * saturated segmentation. 
   */
    class SegmentComputerIterator
    {

         // ------------------------- inner Types -----------------------

    public: 
      typedef typename SaturatedSegmentation::SegmentComputer SegmentComputer;
      typedef typename SegmentComputer::ConstIterator ConstIterator;

         // ------------------------- data -----------------------
    private:

      /**
       * Pointer to the segmentation
       */
      const SaturatedSegmentation<TSegmentComputer> *myS;

      /**
       * The current segment
       */
      SegmentComputer  mySegmentComputer;
      
      /**
       * A flag equal to TRUE if *this is valid, FALSE otherwise 
       */
      bool  myFlagIsValid;
    
      /**
       * Begin iterator of the last maximal segment of the segmentation
       */
      ConstIterator myLastMaximalSegmentBegin;
      /**
       * End iterator of the last maximal segment of the segmentation
       */
      ConstIterator myLastMaximalSegmentEnd;
      
      /**
       * A flag equal to TRUE if the current segment
       * intersects the next one, FALSE otherwise 
       * (and FALSE if the current segment is the last one) 
       */
      bool  myFlagIntersectNext;

      /**
       * A flag equal to TRUE if the current segment
       * intersects the previous one, FALSE otherwise 
       * (and FALSE if the current segment is the first one) 
       */
      bool  myFlagIntersectPrevious;

      /**
       * A flag equal to TRUE if *this is the last maximal segment,
       * FALSE otherwise 
       */
      bool  myFlagIsLast;



      // ------------------------- Standard services -----------------------
    public:
       friend class SaturatedSegmentation<TSegmentComputer>;
         


      /**
       * Constructor.
       * 
       * Nb: complexity in O(n).
       * @param aSegmentation  the object that knows the range bounds
       * @param aSegmentComputer  an online segment recognition algorithm
       * @param aFlag  'true' to build a valid object, 'false' otherwise
       */
      SegmentComputerIterator( const SaturatedSegmentation<TSegmentComputer> *aSegmentation,
         const TSegmentComputer& aSegmentComputer,
         const bool& aFlag );


      /**
       * Copy constructor.
       * @param aOther the iterator to clone.
       */
      SegmentComputerIterator( const SegmentComputerIterator & aOther );
    
      /**
       * Assignment.
       * @param aOther the iterator to copy.
       * @return a reference on 'this'.
       */
      SegmentComputerIterator& operator=( const SegmentComputerIterator & aOther );
    
      /**
       * Destructor. Does nothing.
       */
      ~SegmentComputerIterator();

      /**
       * Checks the validity/consistency of the object.
       * @return 'true' if the object is valid, 'false' otherwise.
       */
      bool isValid() const { return myFlagIsValid; }
    
      // ------------------------- iteration services -------------------------
    public:
      
      /**
       * @return a constant reference to the current segment
       */
      const SegmentComputer& operator*() const;

      /**
       * @return the current segment.
       */
      SegmentComputer get() const;

      /**
       * @return a constant pointer to the current segment
       */
      const SegmentComputer* operator->() const;

      /**
       * Pre-increment.
       * Goes to the next maximal segment (if possible).
        *
       * Nb: complexity in O(n).
       */
      SegmentComputerIterator& operator++();
      
      /**
       * Equality operator.
       * @param aOther the iterator to compare with 
       * @return 'true' if their current positions coincide.
       * (same front and back iterators)
       */
      bool operator==( const SegmentComputerIterator & aOther ) const;

      /**
       * Inequality operator.
       * @param aOther the iterator to compare with 
       * @return 'true' if their current positions differs.
       * (different front and back iterators)
       */
      bool operator!=( const SegmentComputerIterator & aOther ) const;

    // ----------------------- accessors --------------------------------------

      /**
       * @return TRUE if the current segment intersects
       * the next one, FALSE otherwise.
       */
      bool intersectNext() const;

      /**
       * @return TRUE if the current segment intersects
       * the previous one, FALSE otherwise.
       */
      bool intersectPrevious() const;

      /**
       * @return begin iterator on the segment.
       */
      const ConstIterator begin() const;

      /**
       * @return end iterator on the segment.
       */
      const ConstIterator end() const;

    // ----------------------- hidden services --------------------------------------

      private: 

      

      /**
       * Checks if the current segment intersects the next one.
       * @param it  end of the current segment
       * @param itb  begin iterator of the underlying range
       * @param ite  end iterator of the underlying range
       * @return 'true' if it != itb and it != ite and
       * --it and it form a valid segment, false otherwise
       */
      bool doesIntersectNext(const ConstIterator& it, 
                       const ConstIterator& itb, const ConstIterator& ite);
      bool doesIntersectNext(const ConstIterator& it, 
                       const ConstIterator& itb, const ConstIterator& ite, IteratorType);
      bool doesIntersectNext(const ConstIterator& it, 
                       const ConstIterator& itb, const ConstIterator& ite, CirculatorType);

      /**
       * Checks if the current segment intersects the next one (if exists).
       * @param it  end of the current segment
       * @return 'true' if --it and it form a valid segment, false otherwise
       *
       * NB: no verification
       */
      bool doesIntersectNext(const ConstIterator& it);

      /**
       * Goes to the next maximal segment (if possible).
       */
      void nextMaximalSegment();

      /**
       * Computes the first maximal segment of the segmentation.
       */
      void initFirstMaximalSegment();

      /**
       * Computes the last maximal segment of the segmentation.
       */
      void initLastMaximalSegment();

    };

    //-------------------------------------------------------------------------
    // end class SegmentComputerIterator
    //-------------------------------------------------------------------------


    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Default constructor.
     *
     * Nb: not valid
     */
    SaturatedSegmentation() {};

    /**
     * Constructor.
     * @param itb  begin iterator of the underlying range
     * @param ite  end iterator of the underlying range
     * @param aSegmentComputer  an online segment recognition algorithm. 
     */
    SaturatedSegmentation(const ConstIterator& itb, 
        const ConstIterator& ite, 
        const SegmentComputer& aSegmentComputer);

    /**
     * Set a subrange to process
     * @param itb  begin iterator the range to processed
     * @param ite  end iterator the range to processed
     * 
     * Nb: must be a valid range included in the underlying range.
     */
    void setSubRange(const ConstIterator& itb, 
                     const ConstIterator& ite);


    /**
     * Set processing mode
     * @param aMode one of the 3 available modes :
     * "Truncate" (default), "Truncate+1", "DoNotTruncate". 
     */
    void setMode(const std::string& aMode);


    /**
     * Destructor.
     */
    ~SaturatedSegmentation();

    /**
     * ConstIterator service.
     * @return an iterator pointing on the first segment of a digital curve.
     */
    typename SaturatedSegmentation::SegmentComputerIterator begin() const;

    /**
     * ConstIterator service.
     * @return an iterator pointing after the last segment of a digital curve.
     */
    typename SaturatedSegmentation::SegmentComputerIterator end() const;


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
     * Begin iterator of the underlying range
     */
    ConstIterator myBegin;
    
    /**
     * End iterator of the underlying range
     */
    ConstIterator myEnd;
  
    /**
     * Begin iterator of the subrange to segment
     */
    ConstIterator myStart;

    /**
     * End iterator of the subrange to segment
     */
    ConstIterator myStop;
  
    /**
     * Mode: either "First", "MostCentered" (default), "Last"
     */
    std::string myMode; 

    /**
     * the segment computer.
     */
    SegmentComputer mySegmentComputer;

    // ------------------------- Hidden services ------------------------------


  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    SaturatedSegmentation ( const SaturatedSegmentation & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    SaturatedSegmentation & operator= ( const SaturatedSegmentation & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class SaturatedSegmentation


  /**
   * Overloads 'operator<<' for displaying objects of class 'SaturatedSegmentation'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'SaturatedSegmentation' to write.
   * @return the output stream after the writing.
   */
  template <typename SegmentComputer>
  std::ostream&
  operator<< ( std::ostream & out, const SaturatedSegmentation<SegmentComputer> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/SaturatedSegmentation.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SaturatedSegmentation_h

#undef SaturatedSegmentation_RECURSES
#endif // else defined(SaturatedSegmentation_RECURSES)
