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
 * @file AlphaThickSegmentComputer.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 * @author Alexandre Faure
 * @author Fabien Feschet
 * @author Mohammad Said
 * @author Jacques-Olivier Lachaud
 *
 * @date 2015/01/05
 *
 * Header file for module AlphaThickSegmentComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(AlphaThickSegmentComputer_RECURSES)
#error Recursive header files inclusion detected in AlphaThickSegmentComputer.h
#else // defined(AlphaThickSegmentComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define AlphaThickSegmentComputer_RECURSES

#if !defined AlphaThickSegmentComputer_h
/** Prevents repeated inclusion of headers. */
#define AlphaThickSegmentComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ReverseIterator.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/geometry/surfaces/ParallelStrip.h"
#include "DGtal/geometry/tools/MelkmanConvexHull.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBySimple3x3Matrix.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class AlphaThickSegmentComputer
/**
 * Description of class 'AlphaThickSegmentComputer' <p>
 *
 * \brief Aim: This class is devoted to the recognition of alpha thick
 * segments as described in \cite FaureTangential2008 . From a maximal
 * diagonal alphaMax thickness, it recognizes thick segments and may
 * thus take into account some noise in the input contour. Moreover
 * points of the segment may not be (digitally) connected and may have
 * floating point coordinates. Connection is only given by the order
 * of the points.
 *
 * As other solutions like \cite DebledRennessonBlurred2005 the
 * algorithm given here is based on the height/width computation of
 * the convex hull computed from a given set of points. The actual
 * implementation exploits the height/width update defined in
 * the \cite FaureTangential2008 (see \cite FaureTangential2008 page
 * 363) which reduces the complexity from \f$O(n\ log\ n) \f$ in
 * \f$O( log\ n) \f$.  Note that the convexhull update in linear
 * time (with point substraction) proposed by Buzer
 * @cite lilianComputing2007 is not yet implemented.
 *
 *
 *
 * @tparam TInputPoint the type of input points: their dimension must
 * be two but their components may be integers or floating-point
 * values.
 *
 * @tparam TConstIterator the type of iterator of candidate points
 * (used in initialization) which should be readable and forward. By
 * default the iterator is set to the const_iterator of std::vector<
 * TInputPoint > .
 *
 *
 * This class is a model of boost::ForwardContainer and  CForwardSegmentComputer.
 * It is also default constructible, copy  constructible, assignable and equality comparable.
 *
 *
 * Alpha thick segment recognition may be typically done as follows:
 * - If you consider input point with floating coordinates, you can define this type:
 *  @snippet examples/geometry/curves/exampleAlphaThickSegmentNoisy.cpp exampleAlphaThickSegmentNoisyTypedef
 *
 * - Then import possibly a vector containing the input points by using the PointListReader class:
 *  @snippet examples/geometry/curves/exampleAlphaThickSegmentNoisy.cpp exampleAlphaThickSegmentNoisyReadFile
 *
 * - Finally apply the segment recognition (here of maximal thickness 15)  by adding the sequence (forward) of contour points:
 *  @snippet examples/geometry/curves/exampleAlphaThickSegmentNoisy.cpp exampleAlphaThickSegmentNoisInitAndReco
 *  @note The maximal thickness given in initialization is the same than
 *  the width given by the method width() of the ParallelStrip primitive
 *  (not the vertical/horizontal width of the convex hull).
 *
 *
 * - If you use a Board2D display, you can draw the resulting segment like other 2D objects:
 *  @snippet examples/geometry/curves/exampleAlphaThickSegmentNoisy.cpp exampleAlphaThickSegmentDisplay
 *
 * The complete example of segment recognition is given in exampleAlphaThickSegmentNoisy.cpp
 *
 * @note You can also construct the segment by using an input point iterator in initialisation (see @ref moduleAlphaThickSegmentReco for more details)
 *
 * The proposed implementation is mainly a backport from
 * [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene) with some
 * various refactoring.
 */


template <typename TInputPoint,
          typename TConstIterator = typename std::vector< TInputPoint >::const_iterator >

class AlphaThickSegmentComputer
{

  // ----------------------- public types --------------------------------------
  BOOST_STATIC_ASSERT(( TInputPoint::dimension == 2 ));
  BOOST_CONCEPT_ASSERT((boost_concepts::ReadableIterator<TConstIterator>));

public:
  /**
   * Type of input point.
   **/
  typedef TInputPoint InputPoint;

  /**
   * The container type of Input Point
   **/
  typedef std::vector< InputPoint > InputPointContainer;
  typedef typename InputPointContainer::size_type Size;
  typedef typename InputPointContainer::const_iterator ContainerConstIterator;
  typedef typename DGtal::functions::Hull2D::ThicknessDefinition ThicknessDef;

  typedef typename InputPointContainer::iterator Iterator;
  typedef TConstIterator ConstIterator;
  typedef ParallelStrip< SpaceND< 2, DGtal::int32_t > ,true,true> Primitive;  

  /**
   * Type of embedded points
   * @see getBoundingBox, getBoundingBoxFromExtremPoints
   */
  typedef DGtal::PointVector<2, double> PointD;

  typedef AlphaThickSegmentComputer<InputPoint, ConstIterator> Self;
  typedef AlphaThickSegmentComputer<InputPoint, ReverseIterator<ConstIterator> > Reverse;
  typedef DGtal::InHalfPlaneBySimple3x3Matrix<InputPoint, typename InputPoint::Component> Functor;
  typedef typename  DGtal::MelkmanConvexHull<InputPoint, Functor>::ConstIterator ConvexhullConstIterator;

  // ----------------------- internal types --------------------------------------

private:
  struct State{
    DGtal::MelkmanConvexHull<InputPoint, Functor> melkmanCH;
    /** the last point added at the front of the alpha thick segment */
    InputPoint lastFront;
    /** the last point added at the back of the alpha thick segment */
    InputPoint lastBack;
    /** one the convexhull edge point of the (edge, vertex) pair used to compute the convexhull height */
    InputPoint edgePh;
    /** one the convexhull edge point of the (edge, vertex) pair used to compute the convexhull height */
    InputPoint edgeQh;
    /** one the convexhull vertex of the (edge, vertex) pair used to compute the convexhull height */
    InputPoint vertexSh;
    /** the actual thickness of the current segment */
    double actualThickness;
  };


  // ----------------------- Standard services ------------------------------
public:



  /**
   * Constructor.
   * @param[in] maximalThickness the maximal thickness of the segment (default 1).
   * @param[in] thicknessDefinition the definition of the thickness used in the segment extension (can be DGtal::functions::Hull2D::HorizontalVerticalThickness (default) or DGtal::functions::Hull2D::EuclideanThickness).
   * @param[in] thickCompPrecision to adjust the precision of the
   * thickness estimation used in the comparison during the segment
   * extension (default set to 1e-6).
   */
  AlphaThickSegmentComputer(const double maximalThickness = 1.0,
                            const ThicknessDef &thicknessDefinition = functions::Hull2D::HorizontalVerticalThickness,
                            const double thickCompPrecision=1e-6);



  /**
   * Destructor.
   */
  ~AlphaThickSegmentComputer();


  /**
   * Copy constructor.
   *
   * @param[in] other the object to clone.
   */
  AlphaThickSegmentComputer ( const AlphaThickSegmentComputer & other );


  /**
   * Assignment.
   *
   * @param other the object to copy.
   * @return a reference on 'this'.
   */
  AlphaThickSegmentComputer & operator= ( const AlphaThickSegmentComputer & other );


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
   * @return 'true' if the AlphaThickSegment representations
   * and the ranges of the two objects match,
   * 'false' otherwise
   */
  bool operator==( const AlphaThickSegmentComputer & other ) const;

  /**
   * Difference operator.
   * @param other the object to compare with.
   * @return 'false' if equal
   * 'true' otherwise
   */
  bool operator!=( const AlphaThickSegmentComputer & other ) const;



  //-------------------- model of ForwardContainer -----------------------------
public:

  /**
   * @return the number of distinct points stored in the container.
   * @note it returns 0 if segment computer is initialized with a curve
   * iterator without the option of saving samples).
   */
  Size size() const;


  /**
   * @return 'true' if and only if the container contains no point.
   * @note: returns always 'true' if the segment computer is initialized with a curve
   * const iterator without the option of saving samples).
   */
  bool empty() const;


  /**
   * @return a const iterator pointing on the first point given in the
   * container associated to the current alpha thick segment (is empty
   * if the saving option is not selected in the init method).
   */
  ContainerConstIterator containerBegin() const;


  /**
   * @return a const iterator pointing after the last point given in the
   * container associated to the current alpha thick segment (is
   * empty if the saving option is not selected in the init method).
   */
  ContainerConstIterator containerEnd() const;

  /**
   * @return a const iterator pointing on the first point of the
   * convex hull associated to the current alpha thick segment.
   */
  ConvexhullConstIterator convexhullBegin() const;


  /**
   * @return a const iterator pointing after the last point of the
   * convex hull associated to the current alpha thick segment.
   */
  ConvexhullConstIterator convexhullEnd() const;

  /**
   * @return a const iterator pointing on the first point of the
   * current alpha thick segment. Useful only if the initialisation was
   * done with a contour iterator (else, it is empty).
   */
  ConstIterator begin() const;


  /**
   * @returns a const iterator pointing after the last point stored in
   * the current alpha thick segment container. Useful only if the
   * initialisation was done with a contour iterator (else, it is
   * empty).
   */
  ConstIterator end() const;


  /**
   * @return the maximal allowed number of points in the current alpha thick segment.
   */
  Size max_size() const;




  //-------------------- model of CForwardSegmentComputer ----------------

public:

  /**
   * Initialisation with an ConstIterator (to conform to
   * CForwardSegmentComputer).  The maximal thickness corresponds to
   * the width of the ParallelStrip primitive (set to 1 by default).
   *
   * @param[in] it an iterator on input points.
   */
  void init(const ConstIterator &it);


  /**
   * Tries to extend front the current alpha thick segment with the
   * next contour point and checks if we have still an alpha thick
   * segment of thickness less or equal to the initial value
   * alpha_max. If it is the case the new point is added and the
   * segment parameters are updated, otherwise the alpha thick segment
   * is keep in its original state.
   *
   * @return 'true' if the segment has been extended and 'false'
   * otherwise (the object is then in its original state).
   */
  bool extendFront();


  /**
   *  Tests whether the current alpha thick segment can be extended at
   *  the front with the next contour point i.e checks if we have
   *  still an alpha thick segment of width alpha_max after adding the
   *  given point \a aPoint. The segment parameters are keep in its
   *  original state.
   *
   * @return 'true' if the segment can be extended with the given point, 'false' otherwise.
   */
  bool isExtendableFront();


  /**
   *  Tests whether the current alpha thick segment can be extended, i.e
   *  checks if we have still an alpha thick segment of width alpha_max after
   *  adding the given point \a aPoint. The segment parameters are keep
   *  in its original state.
   *
   * @param[in] aPoint the point to be tested for the segment extension.
   * @return 'true' if the segment can be extended with the given point, 'false' otherwise.
   */
  bool isExtendableFront(const InputPoint &aPoint);


  /**
   * Tries to add the point \a aPoint at the front of the current alpha thick
   * segment and checks if we have still an alpha thick segment of thickness
   * less or equal to the initial value alpha_max. If it is the case
   * the new point is added and the segment parameters are updated,
   * otherwise the alpha thick segment is keep in its original state.
   *
   * @param[in] aPoint the new point to extend the current segment.
   * @return 'true' if the segment has been extended and 'false'
   * otherwise (the object is then in its original state).
   */
  bool extendFront(const InputPoint &aPoint);



  //-------------------- Primitive services -----------------------------


  /**
     Returns the current primitive recognized by this computer,
     which is a ParallelStrip of axis width smaller than the one
     specified at instanciation.
  */
  Primitive primitive() const;




    // ----------------------- Interface --------------------------------------
public:


  /**
   * Checks the validity/consistency of the object.
   * @return 'true' if the object is valid, 'false' otherwise.
   */
  bool isValid() const;


  /**
   * Get the extremity points of the segment. These points are not
   * necessary the last point of the segment.
   *
   **/
  std::pair<InputPoint, InputPoint>  getExtremityPoints() const;


  /**
   * @return the antipodal leaning points of the segment (given in the
   * convexhull). The result is given as a pair for which the first
   * element is the pair containing the edge antipodal points and the
   * second element is the vertex of the antipodal pair (see section \ref
   * moduleAlphaThickSegmentRecoIntro for an illustration of such an
   * antipodal pair).
   **/
  std::pair<std::pair<InputPoint, InputPoint>, InputPoint>
  getAntipodalLeaningPoints() const;


  /**
   * Computes the paralell strip params from the current state of the segment.
   * @param[out] mu the minimal value of N.X (with N is the normal vector of the segment).
   * @param[out] N the normal of the vector (not normalized).
   * @param[out] nu the width of the strip.
   *
   **/
  void computeParallelStripParams(double &mu, PointD &N, double &nu) const;


  /**
   * @return the two values of the normal vector given as a Point(a,b)
   * (the normal is oriented toward the segment by considering the
   * edge PQ of the convexhull antipodal pair).
   **/

  PointD getNormal() const;


  /**
   * @return the thickness of the current segment.
   **/
  double getThickness() const;


  /**
   * @return the mu parameter of the current segment (given from the segment ParalellStrip primitive).
   **/
  double getMu() const;


  /**
   * @return the nu parameter the of the current segment (given from the segment ParalellStrip primitive).
   **/
  double getNu() const;


   /**
   * @return the segment length defined from the bouding box (@see getBoundingBox).
   **/
  double getSegmentLength() const;


  /**
   * @return 'true' if the points of the segment computer are stored in the main container.
   **/
  bool isStoringSegmentPoints() const;


  /**
   * @return the total number of points beeing recognized through in the segment construction.
   **/
  unsigned int getNumberSegmentPoints() const;



  // ------------------------- Display services ------------------------------


  /**
   * @return the current alpha thick segment convexhull given as a vector containing the vertex points.
   **/
  std::vector<InputPoint> getConvexHull() const;



  /**
   * Computes the segment bounding box according to two extremity points (\a aFirstPt, \a aLastPt).
   * @param[in] aFirstPt the first extrem point.
   * @param[in] aLastPt the last extrem point.
   * @param[out] pt1LongestSegment1 the first point of one of the longest segment.
   * @param[out] pt2LongestSegment1 the second point of one of the longest segment.
   * @param[out] pt3LongestSegment2 the first point of one of the second longest segment.
   * @param[out] pt4LongestSegment2 the second point of one of the second longest segment.
   * @param[in] minVisibleWidthBounds the minimal width of the resulting bounding box (for drawing issue when the segment thickness is 0).
   * The sequence of resulting points (pt1LongestSegment1,
   * pt2LongestSegment1, pt3LongestSegment2, pt4LongestSegment4) are
   * ccw oriented.
   *
   * @note the segment bounding box can be drawn with the sequence of
   * out parameters pt1LongestSegment1, pt2LongestSegment1,
   * pt3LongestSegment1, pt4LongestSegment1.
   **/
  void getBoundingBoxFromExtremPoints(const InputPoint &aFirstPt,
                                      const InputPoint &aLastPt,
                                      PointD &pt1LongestSegment1,
                                      PointD &pt2LongestSegment1,
                                      PointD &pt3LongestSegment2,
                                      PointD &pt4LongestSegment2,
                                      double minVisibleWidthBounds = 0.2) const;


  /**
   * Computes the segment bounding box defined from the extremity
   * points computed after a scan of the current convexhull. Note that
   * this bouding box differs from the begin/end points bounding box
   * when a large amount of noise is present in the initial curve.
   * The sequence of resulting points (pt1LongestSegment1,
   * pt2LongestSegment1, pt3LongestSegment2, pt4LongestSegment4) are
   * ccw oriented.
   *
   * @param[out] pt1LongestSegment1 the first point of one of the longest segment.
   * @param[out] pt2LongestSegment1 the second point of one of the longest segment.
   * @param[out] pt3LongestSegment2 the first point of one of the second longest segment.
   * @param[out] pt4LongestSegment2 the second point of one of the second longest segment.
   *
   * @note the segment bounding box can be drawn with the sequence of
   * out parameters pt1LongestSegment1, pt2LongestSegment1,
   * pt3LongestSegment1, pt4LongestSegment1.
   **/
  void getBoundingBox(PointD &pt1LongestSegment1,
                      PointD &pt2LongestSegment1,
                      PointD &pt3LongestSegment2,
                      PointD &pt4LongestSegment2) const;





  /**
   * @return the style name used for drawing this object.
   */
  std::string className() const;


  /**
   * Writes/Displays the object on an output stream.
   *
   * @param[out] out the output stream where the object is written.
   */
  void selfDisplay ( std::ostream & out ) const;

    // ------------------------- Protected Datas ------------------------------
protected:


  /**
   * begin iterator (associated to input data)
   **/
  ConstIterator myBegin;

  /**
   * begin iterator (associated to input data)
   **/
  ConstIterator myEnd;




    // ------------------------- Private Datas --------------------------------
private:

  /**
   * The set of points contained in the alpha thick segment which can be changed during computations.
   **/
  mutable InputPointContainer myPointContainer;

  /**
   * The maximal thickness of the segment.
   */
  double myMaximalThickness;

  /**
   * To adjust the precision of the thickness estimation used in the comparison during the segment extension.
   */
  double myThicknessCompPrecision;


  /**
   * To set a specific thickness definition.
   */
  ThicknessDef myThicknessDefinition;


  /**
   * State of the actual computer
   **/
  State myState;

  /**
   * Previous saved computer state
   **/
  mutable State myPreviousState;

  bool myIsStoringPoints;

  /**
   * Used by the size method.
   **/
  unsigned int myNbPointsAddedFromIterators;




    // ------------------------- Hidden services ------------------------------
protected:



  /**
   * Depending on connexity, return true if a convex is valid.
   */
  bool melkmanIsConvexValid() ;


  /**
   *  Updates the main height of the melkman convex hull
   *   and update the antipodal pairs.
   *
   * @return the thickness of the segment (thickness defined by
   * default as the vertical/horizontal width (see @ref
   * moduleAlphaThickSegmentReco for more details).
   **/
  double updateMainHeightAndAntiPodal();



  /**
   * Computes the projection of a Point \a ptC on the real line defined by the two points (\a ptA, \a ptB), and
   * return true if the projected point is inside the segment closed interval [A,B].
   *
   * @param[in] ptA one of the two points defining the straight line.
   * @param[in] ptB one of the two points defining the straight line.
   * @param[in] ptC the point to be projected.
   * @param[out] ptProjected the projected point.
   * @return true if ptProjected is inside the segment [A,B].
   **/
  template<typename TPointD>
  bool projectOnStraightLine(const TPointD & ptA, const TPointD & ptB,
                             const TPointD & ptC, PointD & ptProjected) const;


  /**
   * From an point iterator (\a itBegin and \a itEnd) it computes the
   * two extrem points (\a aFirstExtrPt and \a aLastExtrPt) defined
   * according to the direction of the current segment.
   *
   * @param[in] itBegin the start iterator of the input points.
   * @param[in] itEnd the end iterator of the input points.
   * @param[out] aFirstExtrPt the first extrem point.
   * @param[out] aLastExtrPt the last extrem point.
   *
   **/
  template<typename TConstIteratorG>
  void computeExtremaPoints(const TConstIteratorG & itBegin, const TConstIteratorG & itEnd,
                            InputPoint & aFirstExtrPt, InputPoint & aLastExtrPt) const;


    // ------------------------- Internals ------------------------------------
private:

}; // end of class AlphaThickSegmentComputer


/**
 * Overloads 'operator<<' for displaying objects of class 'AlphaThickSegmentComputer'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'AlphaThickSegmentComputer' to write.
 * @return the output stream after the writing.
 */
template <typename TInputPoint, typename TConstIterator>
std::ostream&
operator<< ( std::ostream & out, const AlphaThickSegmentComputer<TInputPoint, TConstIterator> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#if !defined(BUILD_INLINE)
#include "DGtal/geometry/curves/AlphaThickSegmentComputer.ih"
#endif


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined AlphaThickSegmentComputer_h

#undef AlphaThickSegmentComputer_RECURSES
#endif // else defined(AlphaThickSegmentComputer_RECURSES)
