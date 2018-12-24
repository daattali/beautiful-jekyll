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
 * @file GreedySegmentation.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/07/21
 *
 * @brief Header file for module GreedySegmentation.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(GreedySegmentation_RECURSES)
#error Recursive header files inclusion detected in GreedySegmentation.h
#else // defined(GreedySegmentation_RECURSES)
/** Prevents recursive inclusion of headers. */
#define GreedySegmentation_RECURSES

#if !defined GreedySegmentation_h
/** Prevents repeated inclusion of headers. */
#define GreedySegmentation_h

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
  // template class GreedySegmentation
  /**
   * Description of template class 'GreedySegmentation' <p>
   * \brief Aim: Computes the greedy segmentation of a range 
   * given by a pair of ConstIterators. 
   * The last element of a given segment is the first one
   * one of the next segment.
   *
   * This class is a model of CSegmentation.
   * 
   * @tparam TSegmentComputer at least a model of CForwardSegmentComputer
   * (an online algorithm for the recognition of a given class of segments). 
   *
   * In the short example below, a digital curve stored in a STL vector
   * is decomposed into 8-connected DSSs whose parameters are sent to 
   * the standard output.
   * @code 
   
  //types definition
  typedef PointVector<2,int> Point;
  typedef std::vector<Point> Range;
  typedef Range::const_iterator ConstIterator;
  typedef ArithmeticalDSSComputer<ConstIterator,int,8> SegmentComputer;
  typedef GreedySegmentation<SegmentComputer> Segmentation;

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
   * If you want to get the DSSs segmentation of the digital curve
   * when it is scanned in the reverse way, you can use the reverse
   * iterator of the STL vector:   
   * @code 
...
  typedef Range::const_reverse_iterator ConstReverseIterator;
...
  Segmentation theSegmentation(curve.rbegin(), curve.rend(), recognitionAlgorithm);
...
   * @endcode
   *
   * If you want to get the DSSs segmentation of a part of the 
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
   * Moreover, a part of a digital curve may be processed either
   * as an independant (open) digital curve or as a part whose 
   * segmentation at the ends depends of the underlying digital 
   * curve. That's why 3 processing modes are available:
   * - "Truncate" (default), the extension of the last segment 
   *  (and the segmentation) stops just before endIt.
   * - "Truncate+1", the last segment is extended to endIt too
   * if it is possible, provided that endIt != curve.end(). 
   * - "DoNotTruncate", the last segment is extended as far as 
   * possible, provided that curve.end() is not reached. 
   *
   *
   * In order to set a mode (before getting a SegmentComputerIterator),
   * use the setMode() method as follow: 
   * @code 
  theSegmentation.setMode("DoNotTruncate");
   * @endcode  
   * Note that the default mode will be used for any unknown modes.  
   *
   * @see testSegmentation.cpp 
   */

  template <typename TSegmentComputer>
  class GreedySegmentation
  {

  public: 

    BOOST_CONCEPT_ASSERT(( concepts::CForwardSegmentComputer<TSegmentComputer> ) );
    typedef TSegmentComputer SegmentComputer;
    typedef typename SegmentComputer::ConstIterator ConstIterator;

    // ----------------------- Standard services ------------------------------
  public:



  /////////////////////////////////////////////////////////////////////////////
  // template class SegmentComputerIterator
  /**
   * Description of template class 'SaturatedSegmentation::SegmentComputerIterator'
   *  <p> \brief Aim: Specific iterator to visit all the segments of a greedy segmentation. 
   */
    class SegmentComputerIterator
    {

         // ------------------------- inner Types -----------------------

    public: 
      typedef typename GreedySegmentation::SegmentComputer SegmentComputer;
      typedef typename SegmentComputer::ConstIterator ConstIterator;

         // ------------------------- data -----------------------
    private:

      /**
       * Pointer to the segmentation
       */
      const GreedySegmentation<TSegmentComputer> *myS;

      /**
       * The current segment
       */
      SegmentComputer  mySegmentComputer;
      
      /**
       * A flag equal to TRUE if *this is valid, FALSE otherwise 
       */
      bool  myFlagIsValid;
    
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
       * A flag equal to TRUE if *this has reached the end, FALSE otherwise 
       */
      bool  myFlagIsLast;

      

      // ------------------------- Standard services -----------------------
    public:
       friend class GreedySegmentation<TSegmentComputer>;
         


      /**
       * Constructor.
        *
       * Nb: complexity in O(n).
       *
       * @param aSegmentation  the object that knows the range bounds
       * @param aSegmentComputer  an online segment recognition algorithm
       * @param aFlag  'true' to build a valid object, 'false' otherwise
       */
      SegmentComputerIterator( const GreedySegmentation<TSegmentComputer> *aSegmentation,
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
       * Goes to the next segment (if possible).
        *
       * Nb: complexity in O(n).
       */
      SegmentComputerIterator& operator++();
      
      /**
       * Goes to the next segment (if possible).
        *
       * Nb: complexity in O(n).
       */
      void next();


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
       * Computes the longest possible segment from [it]
       * @param it  a given iterator
       *
       * Nb: complexity in O(n).
       */
      void longestSegment(const ConstIterator& it);
      
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


    };


    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Default constructor.
     *
     * Nb: not valid
     */
    GreedySegmentation() {};

    /**
     * Constructor.
     * @param itb  begin iterator of the underlying range
     * @param ite  end iterator of the underlying range
     * @param aSegmentComputer  an online segment recognition algorithm. 
     */
    GreedySegmentation(const ConstIterator& itb, 
                        const ConstIterator& ite, 
                        const SegmentComputer& aSegmentComputer);

    /**
     * Set a sub-range to process.
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
    ~GreedySegmentation();

    /**
     * ConstIterator service.
     * @return an iterator pointing on the first segment.
     */
    typename GreedySegmentation::SegmentComputerIterator begin() const;

    /**
     * ConstIterator service.
     * @return an iterator pointing after the last segment.
     */
    typename GreedySegmentation::SegmentComputerIterator end() const;


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
     * Mode: either "Truncate" (default), "Truncate+1", or "DoNotTruncate".
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
    GreedySegmentation ( const GreedySegmentation & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    GreedySegmentation & operator= ( const GreedySegmentation & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class GreedySegmentation


  /**
   * Overloads 'operator<<' for displaying objects of class 'GreedySegmentation'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'GreedySegmentation' to write.
   * @return the output stream after the writing.
   */
  template <typename SegmentComputer>
  std::ostream&
  operator<< ( std::ostream & out, const GreedySegmentation<SegmentComputer> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/GreedySegmentation.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined GreedySegmentation_h

#undef GreedySegmentation_RECURSES
#endif // else defined(GreedySegmentation_RECURSES)
