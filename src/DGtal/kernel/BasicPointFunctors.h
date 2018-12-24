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
 * @file BasicPointFunctors.h
 *
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/02/02
 *
 * This files contains several basic classes representing Functors
 * on points.
 *
 * This file is part of the DGtal library.
 */

#if defined(BasicPointFunctors_RECURSES)
#error Recursive header files inclusion detected in BasicPointFunctors.h
#else // defined(BasicPointFunctors_RECURSES)
/** Prevents recursive inclusion of headers. */
#define BasicPointFunctors_RECURSES

#if !defined BasicPointFunctors_h
/** Prevents repeated inclusion of headers. */
#define BasicPointFunctors_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <iterator>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/base/BasicBoolFunctors.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/base/CQuantity.h"
#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/base/ConstAlias.h"
#include <array>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
namespace functors
  {
  /////////////////////////////////////////////////////////////////////////////
  // template class Projector
  /**
   * Description of template class 'Projector' <p>
   * \brief Aim: Functor that maps
   * a point P of dimension i
   * to a point Q of dimension j.
   * The member @a myDims is an array containing the
   * coordinates - (0, 1, ..., j-1) by default -
   * that are copied from P to Q.
   *
   * Ex: for i = 3 and j = 2, the first two coordinates
   * (numbered 0 and 1) are copied so that point (x,y,z) is
   * is mapped to point (x,y).
   *
   * All kth coordinates (0 < k < j) that are greater than i,
   * are set to a value given at construction (0 by defaut).
   *
   * Ex: for i = 2 and j = 3, the first two coordinates
   * (numbered 0 and 1) are copied so that point (x,y) is
   * is mapped to point (x,y,0).
   *
   * Instead of using the default order, you can define your own
   * orthonormal basis as shown below:
   *
   * @code

   PointVector<3,int> p(3,1,5):

   Projector<SpaceND<2,int> > proj;
   proj( p ) //== (3,1)

   ...
   //v (2, 0): selection of the 2nd and 0th basis vectors
   proj.init(v.begin(), v.end());
   proj( p ) //== (5,3)

   * @endcode
   *
   * @tparam S type for the space where must lie the projected point
   */
  template <typename S = SpaceND< 2, DGtal::Z2i::Integer > >
  struct Projector
  {
    typedef S Space;
    typedef typename Space::Dimension Dimension;
    BOOST_STATIC_CONSTANT( Dimension, dimension = Space::dimension );
    typedef typename Space::Integer Integer;
    typedef typename Space::Point Point;

    /**
     * Default constructor
     */
    Projector(const Integer& aDefaultInteger = NumberTraits<Integer>::zero());


    /**
     * Initialization of the array of relevant dimensions
     * @param itb begin iterator on dimensions.
     * @param ite end iterator on dimensions.
     */
    template<typename TIterator>
    void init ( const TIterator& itb, const TIterator& ite );


    /**
     *  Initialisation by removing a given dimension.
     *  @param dimRemoved the removed dimension.
     */
    void initRemoveOneDim ( const Dimension  &dimRemoved );

    /**
     *  Initialisation by adding a given dimension.
     *  @param newDim the new dimension.
     */
    void initAddOneDim ( const Dimension & newDim );


    /**
     *  Main operator
     * @param aPoint any point.
     * @return the projected point.
     */
    template<typename TInputPoint>
    Point operator()( const TInputPoint& aPoint ) const;

  private:
    /**
     * Array storing the coordinates that are copied from
     * the input point to its projection (order matters)
     */
    std::array<Dimension, dimension> myDims;

    /**
     * Default integer set to coordinates of the projected point
     * not in the input point
     */
    Integer myDefaultInteger;

  }; // end of class ConstantPointFunctors





  /**
   * Description of template class 'SliceRotator2D' <p> \brief Special
   * Point Functor that adds one dimension to a 2D point and apply on
   * it a rotation of angle alpha according to a given direction and
   * the domain center. It also checks if the resulting point is
   * inside the 3D domain, else it returns a particular point (by
   * default the point at domain origin (from the domain method
   * lowerBound()).
   *
   * Ex: a Point P (10, 9) in the domain (defined (0,0,0) (10,10,10))
   * given in 3D by adding the dimension in Z (2) with slice num 7: =>
   * P(10, 9, 7) and after a rotation of PI from center of slice domain (5,5, 7)
   * will give P(0,1,7).
   * To apply this example you can test it with:
   * @code
   // Defining the domain
   PointVector<3, int> pt1(0,0, 0);
   PointVector<3, int> pt2(10,10, 10);
   HyperRectDomain<SpaceND<3, int> >  domain (pt1, pt2);
   // The functor on axis rotation set to 2 with new Z slice num=7 and angle 3.15:
   SliceRotator2D< HyperRectDomain<SpaceND<3, int> >, int> sliceRot2(2, domain, 7, 2, 3.14);
   PointVector<2, int> pt_2(10, 9);
   trace.info() <<  sliceRot2(pt_2);
   @endcode
   *
   *
   * @tparam TDomain3D the type of the 3d domain.
   * @tparam TInteger specifies the integer number type used to define the space.
   *
   */
  template <typename TDomain3D, typename TInteger =  DGtal::Z3i::Integer >
  class SliceRotator2D
  {
  public:

    typedef SpaceND< 3, TInteger>  Space;
    typedef typename Space::Dimension Dimension;
    typedef typename Space::Point Point;
    typedef typename Space::Integer Integer;
    /**
     * Constructor.
     * (default point is defined from lower point of the domain)
     * @param dimAdded  the index of the new dimension inserted.
     * @param aDomain3DImg the 3D domain used to keep the resulting point in the domain.
     * @param sliceIndex the value that is used to fill the dimension for a given N-1 point (equivalently the slice index).
     * @param dimRotated the index of the rotation axis.
     * @param rotationAngle the angle of rotation (in radians).
     */

    SliceRotator2D( const Dimension &dimAdded, const TDomain3D &aDomain3DImg,
                    const Integer &sliceIndex,  const Dimension &dimRotated,
                    double rotationAngle):
      myPosDimAdded(dimAdded), mySliceIndex(sliceIndex), myDomain(aDomain3DImg),
      myDimRotated(dimRotated), myRotationAngle(rotationAngle), myDefaultPoint (aDomain3DImg.lowerBound())
    {
      myCenter[0] = aDomain3DImg.lowerBound()[0]+((aDomain3DImg.upperBound())[0]-(aDomain3DImg.lowerBound())[0])/2.0;
      myCenter[1] = aDomain3DImg.lowerBound()[1]+((aDomain3DImg.upperBound())[1]-(aDomain3DImg.lowerBound())[1])/2.0;
      myCenter[2] = aDomain3DImg.lowerBound()[2]+((aDomain3DImg.upperBound())[2]-(aDomain3DImg.lowerBound())[2])/2.0;
      myCenter[dimAdded]=sliceIndex;
    };

    /**
     * Constructor.
     * @param dimAdded  the index of the new dimension inserted.
     * @param aDomain3DImg the 3D domain used to keep the resulting point in the domain.
     * @param sliceIndex the value that is used to fill the dimension for a given N-1 point (equivalently the slice index).
     * @param dimRotated the index of the rotation axis.
     * @param rotationAngle the angle of rotation (in radians).
     * @param defaultPoint the point given when the resulting point is outside the domain.
     */

    SliceRotator2D( const Dimension &dimAdded, const TDomain3D &aDomain3DImg,
                    const Integer &sliceIndex,  const Dimension &dimRotated,
                    double rotationAngle,  const Point &defaultPoint):
      myPosDimAdded(dimAdded), mySliceIndex(sliceIndex), myDomain(aDomain3DImg),
      myDimRotated(dimRotated), myRotationAngle(rotationAngle), myDefaultPoint (defaultPoint)
    {
      myCenter[0] = aDomain3DImg.lowerBound()[0]+((aDomain3DImg.upperBound())[0]-(aDomain3DImg.lowerBound())[0])/2.0;
      myCenter[1] = aDomain3DImg.lowerBound()[1]+((aDomain3DImg.upperBound())[1]-(aDomain3DImg.lowerBound())[1])/2.0;
      myCenter[2] = aDomain3DImg.lowerBound()[2]+((aDomain3DImg.upperBound())[2]-(aDomain3DImg.lowerBound())[2])/2.0;
      myCenter[dimAdded]=sliceIndex;
    };

    /**
     * Constructor.
     * @param dimAdded  the index of the new dimension inserted.
     * @param aDomain3DImg the 3D domain used to keep the resulting point in the domain.
     * @param sliceIndex the value that is used to fill the dimension for a given N-1 point (equivalently the slice index).
     * @param dimRotated the index of the rotation axis.
     * @param ptCenter the rotation center.
     * @param rotationAngle the angle of rotation (in radians).
     * @param defaultPoint the point given when the resulting point is outside the domain.
     */

    SliceRotator2D( const Dimension &dimAdded, const TDomain3D &aDomain3DImg, const Integer &sliceIndex,
                    const Dimension &dimRotated,  const Point &ptCenter, double rotationAngle, const Point &defaultPoint):
      myPosDimAdded(dimAdded), mySliceIndex(sliceIndex), myDomain(aDomain3DImg),
      myDimRotated(dimRotated), myRotationAngle(rotationAngle), myCenter(ptCenter), myDefaultPoint (defaultPoint)
    {
    };

    /**
     * Constructor.
     * (default point is defined from lower point of the domain)
     * @param dimAdded  the index of the new dimension inserted.
     * @param aDomain3DImg the 3D domain used to keep the resulting point in the domain.
     * @param sliceIndex the value that is used to fill the dimension for a given N-1 point (equivalently the slice index).
     * @param dimRotated the index of the rotation axis.
     * @param ptCenter the rotation center.
     * @param rotationAngle the angle of rotation (in radians).
     */

    SliceRotator2D( const Dimension &dimAdded, const TDomain3D &aDomain3DImg, const Integer &sliceIndex,
                    const Dimension &dimRotated,  const Point &ptCenter, double rotationAngle):
      myPosDimAdded(dimAdded), mySliceIndex(sliceIndex), myDomain(aDomain3DImg),
      myDimRotated(dimRotated), myRotationAngle(rotationAngle), myCenter(ptCenter), myDefaultPoint (aDomain3DImg.lowerBound())
    {
    };

    /**
     * The operator just recover the 3D Point associated to the SliceRotator2D parameters.
     * @param[in] aPoint point of the input domain (of dimension N-1).
     *
     * @return the point of dimension 3.
     */
    template <typename TPointDimMinus>
    inline
    Point  operator()(const TPointDimMinus& aPoint) const
    {
      Point pt;
      Dimension pos=0;
      std::vector<Dimension> indexesRotate;
      for( Dimension i=0; i<pt.size(); i++)
        {
          if(i!=myPosDimAdded)
            {
              pt[i]= aPoint[pos];
              pos++;
            }else
            {
              pt[i]=mySliceIndex;
            }
        }
      for( Dimension i=0; i<pt.size(); i++)
        {
          if(i!=myDimRotated)
            indexesRotate.push_back(i);
        }
      double d1 = pt[indexesRotate[0]] - myCenter[indexesRotate[0]];
      double d2 = pt[indexesRotate[1]] - myCenter[indexesRotate[1]];

      pt[indexesRotate[0]] = myCenter[indexesRotate[0]] + static_cast<Integer>(round(d1*cos(myRotationAngle)-d2*sin(myRotationAngle) ));
      pt[indexesRotate[1]] = myCenter[indexesRotate[1]] + static_cast<Integer>(round(d1*sin(myRotationAngle)+d2*cos(myRotationAngle) ));

      if(myDomain.isInside(pt))
        return pt;
      else
        return  myDefaultPoint;
    }
  private:
    // position of insertion of the new dimension
    Dimension myPosDimAdded;
    // the index of the slice associated to the new domain.
    Integer mySliceIndex;
    TDomain3D myDomain;
    Dimension myDimRotated;
    double myRotationAngle;
    PointVector<3, double> myCenter;
    Point myDefaultPoint;
  };


  /**
   * Description of template class 'Point2DEmbedderIn3D' <p> \brief
   * Aim: Functor that embeds a 2D point into a 3D space from two axis
   * vectors and an origin point given in the 3D space.
   *
   * It also checks if the resulting point is inside the 3D domain,
   * else it returns a particular point (by default the point at
   * domain origin (from the domain method lowerBound())).
   *
   * It can be used to extract 2D images from volumetric files. For
   * instance (see full example images/extract2DImagesFrom3D.cpp):
   *
   * - First some image types and ConstImageAdapter are defined to exploit the functor:
   * @snippet images/extract2DImagesFrom3D.cpp extract2DImagesFrom3DType
   *
   * - Then, we define the origin point and axis vector used to extract 2D image values and we also deduce the associated 2D domain:
   * @snippet images/extract2DImagesFrom3D.cpp extract2DImagesFrom3DOrigin3D
   *
   * - The 2D image we can now be  constructed from the embeder and from the ConstImageAdapter class:
   * @snippet images/extract2DImagesFrom3D.cpp extract2DImagesFrom3DOExtract
   *
   * - Alternatively, you can also construct the same functor from a reference center point, a normal, and a size:
   * @snippet images/extract2DImagesFrom3D.cpp extract2DImagesFrom3DOExtract2
   *
   *
   * @see tests/kernel/testBasicPointFunctors.cpp
   * @tparam TDomain3D the type of the 3d domain.
   * @tparam TInteger specifies the integer number type used to define the space.
   *
   */
  template <typename TDomain3D, typename TInteger =  DGtal::Z3i::Integer >
  class Point2DEmbedderIn3D
  {
  public:

    typedef SpaceND< 3, TInteger>  Space;
    typedef typename Space::Point Point;
    typedef typename Space::Integer Integer;

    /**
     * Constructor.
     * Construct the functor from an origin 3D point, and two other 3D points defining the upper part of the 2D domain.
     * @param aDomain3DImg  the 3D domain used to keep the resulting point in the domain.
     * @param anOriginPoint the origin point given in the 3D domain.
     * @param anUpperPointOnAxis1 the upper point given in the 3D domain to define the first axis of the 2D domain.
     * @param anUpperPointOnAxis2 the upper point given in the 3D domain to define the second axis of the 2D domain.
     * @param aDefautPoint the point given when the resulting point is outside the domain (default Point(0,0,0)).
     */

    Point2DEmbedderIn3D( const TDomain3D &aDomain3DImg,
                         const Point &anOriginPoint, const Point &anUpperPointOnAxis1,
                         const Point &anUpperPointOnAxis2,
                         const Point &aDefautPoint = Point(0,0,0)): myDomain(aDomain3DImg),
                                                                    myOriginPointEmbeddedIn3D(anOriginPoint),
                                                                    myDefaultPoint (aDefautPoint),
                                                                    myFirstAxisEmbeddedDirection(Point(anUpperPointOnAxis1[0]-anOriginPoint[0],
                                                                                                       anUpperPointOnAxis1[1]-anOriginPoint[1],
                                                                                                       anUpperPointOnAxis1[2]-anOriginPoint[2])),
      mySecondAxisEmbeddedDirection(Point(anUpperPointOnAxis2[0]-anOriginPoint[0],
                                          anUpperPointOnAxis2[1]-anOriginPoint[1],
                                          anUpperPointOnAxis2[2]-anOriginPoint[2]))


    {
      myFirstAxisEmbeddedDirection /= myFirstAxisEmbeddedDirection.norm();
      mySecondAxisEmbeddedDirection /= mySecondAxisEmbeddedDirection.norm();
    }


    /**
     * Constructor.
     * Construct the functor from an origin 3D point, an normal vector (normal to the 2D domain), and a width.
     * The points of an 2D domain are embedded in 3D by using a normal vector giving the direction of the 2D domain embedded in the 3D space.
     * @param aDomain3DImg  the 3D domain used to keep the resulting point in the domain.
     * @param anOriginPoint the center point given in the 3D domain.
     * @param anNormalVector the normal vector to the 2d domain embedded in 3D.
     * @param anWidth the width to determine the 2d domain bounds (the resulting 2d domain will be a square of length anWidth).
     * @param aDefautPoint the point given when the resulting point is outside the domain (default Point(0,0,0)).
     *
     */

    Point2DEmbedderIn3D( const TDomain3D &aDomain3DImg,
                         const Point &anOriginPoint, const typename Space::RealPoint & anNormalVector,
                         const typename Point::Component  &anWidth,
                         const Point &aDefautPoint = Point(0,0,0)): myDomain(aDomain3DImg),
                                                                    myDefaultPoint (aDefautPoint)
    {
      double d = -anNormalVector[0]*anOriginPoint[0] - anNormalVector[1]*anOriginPoint[1] - anNormalVector[2]*anOriginPoint[2];
      typename Space::RealPoint pRefOrigin;
      if(anNormalVector[0]!=0){
        pRefOrigin [0]= -d/anNormalVector[0];
        pRefOrigin [1]= 0.0;
        pRefOrigin [2]= 0.0;
        if(pRefOrigin==anOriginPoint){
          pRefOrigin[1]=-1.0;
        }
      }else if (anNormalVector[1]!=0){
        pRefOrigin [0]= 0.0;
        pRefOrigin [1]= -d/anNormalVector[1];
        pRefOrigin [2]= 0.0;
        if(pRefOrigin==anOriginPoint){
          pRefOrigin[0]=-1.0;
        }
      }else if (anNormalVector[2]!=0){
        pRefOrigin [0]= 0.0;
        pRefOrigin [1]= 0.0;
        pRefOrigin [2]= -d/anNormalVector[2];
        if(pRefOrigin==anOriginPoint){
          pRefOrigin[0]=-1.0;
        }
      }
      typename Space::RealPoint uDir1;
      uDir1=(pRefOrigin-anOriginPoint)/((pRefOrigin-anOriginPoint).norm());
      typename Space::RealPoint uDir2;
      uDir2[0] = uDir1[1]*anNormalVector[2]-uDir1[2]*anNormalVector[1];
      uDir2[1] = uDir1[2]*anNormalVector[0]-uDir1[0]*anNormalVector[2];
      uDir2[2] = uDir1[0]*anNormalVector[1]-uDir1[1]*anNormalVector[0];

      uDir2/=uDir2.norm();

      myOriginPointEmbeddedIn3D = anOriginPoint + uDir1*anWidth/2 + uDir2*anWidth/2;
      myFirstAxisEmbeddedDirection = -uDir1;
      mySecondAxisEmbeddedDirection = -uDir2;

    }




    /**
     * The operator just recover the 3D Point associated to the Point2DEmbederIn3D parameters.
     * @param[in] aPoint point of the input domain (of dimension 2).
     * @param checkInsideDomain if 'true', checks that the point lies inside the domain.
     *
     * @return the digital point of dimension 3 (value rounded downward with floor).
     */
    template <typename TPoint2D>
    inline
    Point  operator()(const TPoint2D& aPoint, bool checkInsideDomain=true) const
    {
      Point pt = myOriginPointEmbeddedIn3D;
      for( Dimension i=0; i<pt.size(); i++){

        pt[i] = pt[i]+static_cast<Integer>(floor(NumberTraits<Integer>::castToDouble(aPoint[0])
                                                 *myFirstAxisEmbeddedDirection[i]));
        pt[i] = pt[i]+static_cast<Integer>(floor(NumberTraits<Integer>::castToDouble(aPoint[1])
                                                 *mySecondAxisEmbeddedDirection[i]));
      }

      if(myDomain.isInside(pt)|| !checkInsideDomain)
        {
          return pt;
        }
      else
        {
#ifdef DEBUG_VERBOSE
          trace.warning() << "Warning pt outside the 3D domain " << pt << std::endl;
#endif
          return  myDefaultPoint;
        }
    }

  private:
    TDomain3D myDomain;

    // Origin (or lower point) of the 2D image embedded in the 3D domain
    Point  myOriginPointEmbeddedIn3D;

    Point myDefaultPoint;

    // Point giving the direction of the embedded first axis of the 2D image.
    typename Space::RealPoint myFirstAxisEmbeddedDirection;

    // Point giving the direction of the embedded second axis of the 2D image.
    typename Space::RealPoint mySecondAxisEmbeddedDirection;

  };


  /**
   * \brief Create a point functor from a point predicate and a domain.
   */
  template< typename TPointPredicate, typename TDomain, typename TValue=typename TDomain::Integer >
  struct PointFunctorFromPointPredicateAndDomain
  {
      typedef TPointPredicate PointPredicate;
      typedef TDomain Domain;
      typedef TValue Value;
      typedef typename Domain::Point Point;

      BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate< PointPredicate > ));
      BOOST_CONCEPT_ASSERT(( concepts::CDomain< Domain > ));
      BOOST_CONCEPT_ASSERT(( concepts::CQuantity< Value > ));

      /**
       * @brief Constructor.
       * @param[in] aPtrPredicate a predicate on digital point
       * @param[in] aDomain a domain on digital point
       * @param[in] aTrueValue the returned value when a given point is inside the domain and when the predicate return true
       * @param[in] aFalseValue the returned value when a given point is outside the domain or when the predicate return false
       */
      PointFunctorFromPointPredicateAndDomain( ConstAlias< PointPredicate > aPtrPredicate, ConstAlias< Domain > aDomain,
                                               const Value aTrueValue, const Value aFalseValue );

      PointFunctorFromPointPredicateAndDomain( const PointFunctorFromPointPredicateAndDomain & other  );

      /**
       * @brief operator ()
       * @param[in] aPoint evaluated digital point.
       * @return aTrueValue when aPoint is inside the domain and when the predicate return true, aFalseValue else.
       */
      Value operator()( const Point& aPoint ) const;

      /**
         * Assignment.
         * @param other the object to copy.
         * @return a reference on 'this'.
         * Forbidden by default.
         */
      PointFunctorFromPointPredicateAndDomain & operator= ( const PointFunctorFromPointPredicateAndDomain & other );

  private:
      const PointPredicate * myPtrPredicate;
      const Domain * myDomain;
      Value myTrueValue;
      Value myFalseValue;

  };


  /**
   * Description of template class 'BasicDomainSubSampler' <p> \brief
   * Aim: Functor that subsamples an initial domain by given a grid
   * size and a shift vector. By this way, for a given point
   * considered in a new domain, it allows to recover the point
   * coordinates in the source domain.  Such functor can be usefull to
   * apply basic image subsampling in any dimensions by using
   * ImageAdapter class.
   *
   *
   * @see tests/kernel/testBasicPointFunctors.cpp
   * @tparam TDomain the type of the domain.
   * @tparam TInteger specifies the integer number type used to define the space.
   *
   * @tparam TValue specify the type of the value which define the
   * grid size (generally type int (default) when subsampling with large grid size
   * and double to re sampling with grid size less than 1).
   */

 template <typename TDomain, typename TInteger =  DGtal::int32_t, typename TValue = DGtal::uint32_t >
 class BasicDomainSubSampler
  {
  public:
    typedef typename TDomain::Space  Space;
    typedef typename TDomain::Size Size;
    typedef typename Space::Dimension Dimension;
    typedef typename Space::Point Point;

    /**
     * Constructor.
     * Construct the functor from a source domain, a grid size, and a shift vector.
     * The points of the resulting domain are defined as the upper left of the sampling grid.
     *
     * @param aSourceDomain  the source domain.
     * @param aGridSize the subsampling grid size.
     * @param aGridShift the shift applied to the sampling grid.
     *
     */

    BasicDomainSubSampler(const TDomain &aSourceDomain, const std::vector<TValue> &aGridSize,
                          const Point  &aGridShift): mySourceDomain(aSourceDomain),
                                                     myGridShift(aGridShift),
                                                     myGridSize(aGridSize)
    {
      Point domainUpperBound=aSourceDomain.upperBound();
      Point domainLowerBound=aSourceDomain.lowerBound();

      for (Dimension dim=0; dim< Space::dimension; dim++){
        domainLowerBound[dim] /= aGridSize[dim];
        domainUpperBound[dim] /= aGridSize[dim];
      }
      myNewDomain = TDomain(domainLowerBound,
                            domainUpperBound);
      Point upperGrid;
      for (Dimension dim=0; dim < Space::dimension; dim++)
        upperGrid[dim] = myGridSize[dim];
      myGridSampleDomain = TDomain(Point::diagonal(0), upperGrid);
    };


    /**
     * The operator computes the coordinates of the point in the
     * subsampled domain.  By default it returns the first lower point
     * of the window associated to the sampling grid. If the resulting
     * point is outside the source domain it scans this window and
     * returns a point belonging to the source domain. If such a point
     * does not exits it return the point with null coordinates.
     *
     * @param aPoint a point which should  belong to the new domain.
     * @return the point to be taken in the subsampled domain.
     *
     */

    inline
    Point  operator()(const Point& aPoint) const
    {
      Point ptRes = Point::diagonal(0);
      if(!myNewDomain.isInside(aPoint)){
        trace.error() << " The point is not in the source domain: "<<  aPoint << std::endl;
        return ptRes;
      }

      for (Dimension dim=0; dim< Space::dimension; dim++){
        ptRes[dim] = static_cast<TInteger>(floor(NumberTraits<TInteger>::castToDouble(aPoint[dim])*
                                                 NumberTraits<TValue>::castToDouble(myGridSize[dim])));
      }
      ptRes +=myGridShift;

      if(!mySourceDomain.isInside(ptRes)){
        // we are looking for a point inside the domain
        for(typename TDomain::ConstIterator it = myGridSampleDomain.begin();
            it!= myGridSampleDomain.end(); it++){
          if (mySourceDomain.isInside(ptRes+(*it)))
            return ptRes+(*it);
        }
      }
      return ptRes;
    }

    /**
     * This method can be usefull to directely recover the new domain
     * associated to the resulting subsampled domain.
     * @return the new subsampled domain.
     */

    inline
    const TDomain & getSubSampledDomain(){
      return myNewDomain;
    }

  private:
    TDomain mySourceDomain;
    TDomain myNewDomain;
    // used to search a point when the resulting point is outside the source domain.
    TDomain myGridSampleDomain;
    Point myGridShift;
    std::vector<TValue> myGridSize;
 };


  /**
   * Description of template class 'FlipDomainAxis' <p> \brief Aim:
   * Functor that flips the domain coordinate system from some
   * selected axis.  For instance, if a flip on the y axis is applied
   * on a domain of bounds (0, 0, 0) (MaxX, MaxY, MaxZ), then the
   * coordinate of P(x,y,z) will transformed in P(x, MaxY-y, z).
   *
   * Such functor can be useful to apply basic image
   * flip from some specific axis directions.
   *
   *
   * @see tests/kernel/testBasicPointFunctors.cpp
   *
   * @tparam TDomain the type of the domain.
   *
   */

 template <typename TDomain>
 class FlipDomainAxis
  {
  public:
    typedef typename TDomain::Space  Space;
    typedef typename TDomain::Size Size;
    typedef typename Space::Dimension Dimension;
    typedef typename Space::Point Point;

    /**
     * Constructor.
     * Construct the functor from a source domain and a vector defining the axis being flipped.
     * Such a vector should contain the dimension number associated to the axis to be flipped.
     * For instance to flip the x and z axis of a given 3d domain you have to give a vector
     * containing 1 and 2.
     *
     * @param aSourceDomain  the source domain.
     * @param axisFlipped a vector containing  the indices of the dimension to be flipped.
     *
     */

    FlipDomainAxis(const TDomain &aSourceDomain, const std::vector<Size> & axisFlipped): mySourceDomain(aSourceDomain),
                                                                                         myAxisFlipped(axisFlipped){
    };


    /**
     * The operator computes the coordinates of the point in the
     * flipped domain.
     *
     * @param aPoint a source point.
     * @return the point with flipped coordinates according the source domain.
     *
     */

    inline
    Point  operator()(const Point& aPoint) const
    {
      Point ptRes;
      for (Dimension dim=0; dim< Space::dimension; dim++){
        ptRes[dim] = aPoint[dim];
      }
      for(Dimension i = 0; i< myAxisFlipped.size(); i++){
        ptRes[myAxisFlipped[i]] = mySourceDomain.upperBound()[myAxisFlipped[i]]-aPoint[myAxisFlipped[i]];
      }
      return ptRes;
    }

  private:
    TDomain mySourceDomain;
    std::vector<Size> myAxisFlipped;
 };









  }//namespace functors
} // namespace dgtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/BasicPointFunctors.ih"
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined BasicPointFunctors_h
#undef BasicPointFunctors_RECURSES
#endif // else defined(BasicPointFunctors_RECURSES)
