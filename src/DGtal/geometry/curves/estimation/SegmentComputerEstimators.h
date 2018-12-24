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
 * @file SegmentComputerEstimators.h
 * @brief Various local estimators from segment computers.
 * @author Tristan Roussillon (\c
 * tristan.roussillon@liris.cnrs.fr ) Laboratoire d'InfoRmatique en
 * Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS,
 * France
 *
 *
 *
 * @date 2011/06/28
 *
 * This file is part of the DGtal library.
 *
 * @see testSegmentComputerEstimators.cpp
 */

#if defined(SegmentComputerEstimators_RECURSES)
#error Recursive header files inclusion detected in SegmentComputerEstimators.h
#else // defined(SegmentComputerEstimators_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SegmentComputerEstimators_RECURSES

#if !defined SegmentComputerEstimators_h
/** Prevents repeated inclusion of headers. */
#define SegmentComputerEstimators_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <cmath>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "boost/utility.hpp"

//////////////////////////////////////////////////////////////////////////////


namespace DGtal
{

  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  namespace detail
  {
    /////////////////////////////////////////////////////////////////////////////
    // class PosIndepScaleIndepSCEstimator
    /////////////////////////////////////////////////////////////////////////////
    /**
     * Description of class 'PosIndepScaleIndepSCEstimator' <p> Aim: 
     * estimates a geometric quantity from a segment computer. 
     * The estimation is neither position-dependent 
     * nor scale-dependent (e.g. tangent or normal 
     * estimation from 'straight' primitives). 
     *
     * @tparam TSegmentComputer a model of segment computer. 
     *
     * The computation is delegated to a functor.  
     *
     * @tparam Functor a unary functor
     *
     * This class is a model of CSegmentComputerEstimator
     */

    template <typename TSegmentComputer, typename Functor, 
	      typename ReturnType = typename Functor::Value>
    class PosIndepScaleIndepSCEstimator
    {

    public: 

      // ----------------------- inner type ------------------------------
      typedef TSegmentComputer SegmentComputer;
      typedef typename SegmentComputer::ConstIterator ConstIterator; 
      typedef ReturnType Quantity;

      // ----------------------- Internal data  ------------------------------
    public:
      /**
       * Begin iterator
       */
      ConstIterator myBegin; 
      /**
       * End iterator
       */
      ConstIterator myEnd;
      /**
       * Aliasing pointer on a constant segment computer
       */
      const SegmentComputer* mySCPtr; 
      /**
       * Functor used for the estimation
       */
      Functor myFunctor; 

      // ----------------------- Standard services ------------------------------
    public:

      /**
       * Checks the validity/consistency of the object.
       * @return 'true' if the object is valid, 'false' otherwise.
       */
      bool isValid() const
      {
	return (mySCPtr != 0); 
      };

      // ----------------------- Interface --------------------------------------
    public:

      /**
       * Default constructor
       */
      PosIndepScaleIndepSCEstimator(): myBegin(), myEnd(), mySCPtr(0), myFunctor() {}

      /**
       * Initialisation.
       * (h grid size unused)
       * @param itb begin iterator
       * @param ite end iterator
       */
      void init(const double /*h*/, const ConstIterator& itb, const ConstIterator& ite)
      {
        myBegin = itb;
        myEnd = ite; 
      }

      /**
       * Attach the estimator to @e aSC
       * @param aSC an instance of segment computer. 
       */
      void attach(const SegmentComputer& aSC) 
      {
	mySCPtr = &aSC; 
      };

      /**
       * Unique estimation 
       * @return the estimated quantity
       */
      Quantity eval(const ConstIterator& /*it*/) const
      {
	ASSERT( mySCPtr ); 
        return myFunctor( *mySCPtr ); 
      }

      /**
       * Estimation for a subrange [@e itb , @e ite )
       * @param itb subrange begin iterator (unused) 
       * @param ite subrange end iterator (unused)    
       * @param result output iterator on the estimated quantity
       *
       * @return the estimated quantity
       * from itb till ite (excluded)
       */
      template <typename OutputIterator>
      OutputIterator eval(const ConstIterator& itb, const ConstIterator& ite, 
			  OutputIterator result) const
      {
	ASSERT( mySCPtr ); 

	// do-while loop to deal with the case of a whole circular range
	if (isNotEmpty(itb, ite))
	  {
	    ConstIterator it = itb; 
	    do
	      {
		*result++ = myFunctor( *mySCPtr ); 
		++it; 
	      } while (it != ite);
	  }

        return result; 
      }

    }; // end of class PosIndepScaleIndepSCEstimator

    /////////////////////////////////////////////////////////////////////////////
    // class PosIndepScaleDepSCEstimator
    /////////////////////////////////////////////////////////////////////////////
    /**
     * Description of class 'PosIndepScaleDepSCEstimator' <p> Aim: 
     * estimates a geometric quantity from a segment computer. 
     * The estimation is not position-dependent,
     * but is scale-dependent (e.g. curvature or radius
     * estimation from 'circular' primitives). 
     *
     * @tparam TSegmentComputer a model of segment computer. 
     *
     * The computation is delegated to a functor.  
     *
     * @tparam Functor a binary functor
     *
     * This class is a model of CSegmentComputerEstimator
     */

    template <typename TSegmentComputer, typename Functor, 
	      typename ReturnType = typename Functor::Value>
    class PosIndepScaleDepSCEstimator
    {

    public: 

      // ----------------------- inner type ------------------------------
      typedef TSegmentComputer SegmentComputer;
      typedef typename SegmentComputer::ConstIterator ConstIterator; 
      typedef ReturnType Quantity;

      // ----------------------- internal data ------------------------------
    public:
      /**
       * Grid step
       */
      double myH; 
      /**
       * Begin iterator
       */
      ConstIterator myBegin; 
      /**
       * End iterator
       */
      ConstIterator myEnd;
      /**
       * Aliasing pointer on a constant segment computer
       */
      const SegmentComputer* mySCPtr; 
      /**
       * Functor used for the estimation
       */
      Functor myFunctor; 

      // ----------------------- Standard services ------------------------------
    public:

      /**
       * Default constructor.
       * NB: not valid.
       */
      PosIndepScaleDepSCEstimator()
	: myH( 0.0 ), myBegin(), myEnd(), mySCPtr(0), myFunctor()
      {
      }
      /**
       * Copy constructor.
       * @param other the object to copy.
       */
      PosIndepScaleDepSCEstimator( const PosIndepScaleDepSCEstimator& other )
	: myH( other.myH ), myBegin( other.myBegin ), myEnd( other.myEnd ), 
	  mySCPtr( other.mySCPtr ), myFunctor( other.myFunctor )
      {
      }
      /**
       * Assignement.
       * @param other the object to copy.
       */
      PosIndepScaleDepSCEstimator& operator=( const PosIndepScaleDepSCEstimator& other )
      {
	if (this != &other)
	  {
	    myH = other.myH; 
	    myBegin = other.myBegin; 
	    myEnd = other.myEnd; 
	    mySCPtr = other.mySCPtr; 
	    myFunctor = other.myFunctor; 
	  }
	return *this; 
      }
      /**
       * Destructor
       */
      ~PosIndepScaleDepSCEstimator() {}

      /**
       * Checks the validity/consistency of the object.
       * @return 'true' if the object is valid, 'false' otherwise.
       */
      bool isValid() const 
      {
	return (myH > 0)&&(mySCPtr != 0); 
      };



      // ----------------------- Interface --------------------------------------
    public:

      /**
       * Initialisation.
       * @param h grid size
       * @param itb begin iterator
       * @param ite end iterator
       */
      void init(const double h, const ConstIterator& itb, const ConstIterator& ite)
      {
        myH = h; 
        myBegin = itb;
        myEnd = ite;
	ASSERT( myH > 0 );  
      }

      /**
       * Attach the estimator to @e aSC
       * @param aSC an instance of segment computer. 
       */
      void attach(const SegmentComputer& aSC) 
      {
	mySCPtr = &aSC; 
	ASSERT( mySCPtr ); 
      };

      /**
       * Estimation depending on @e myH 
       * @return the estimated quantity
       */
      Quantity eval(const ConstIterator& /*it*/) const
      {
	ASSERT( isValid() ); 
        return myFunctor( *mySCPtr, myH ); 
      }

      /**
       * Estimation for a subrange [@e itb , @e ite )
       * @param itb subrange begin iterator
       * @param ite subrange end iterator 
       * @param result output iterator on the estimated quantity
       *
       * @return the estimated quantity
       * from itb till ite (excluded)
       */
      template <typename OutputIterator>
      OutputIterator eval(const ConstIterator& itb, const ConstIterator& ite, 
			  OutputIterator result) const
      {
	ASSERT( isValid() ); 

	// do-while loop to deal with the case of a whole circular range
	if (isNotEmpty(itb, ite))
	  {
	    ConstIterator it = itb; 
	    do
	      {
		*result++ = myFunctor( *mySCPtr, myH ); 
		++it; 
	      } while (it != ite);
	  }

        return result; 
      }

    }; // end of class PosIndepScaleDepSCEstimator

    /////////////////////////////////////////////////////////////////////////////
    // class PosDepScaleIndepSCEstimator
    /////////////////////////////////////////////////////////////////////////////
    /**
     * Description of class 'PosDepScaleIndepSCEstimator' <p> Aim: 
     * estimates a geometric quantity from a segment computer. 
     * The estimation is not scale dependent but position dependent
     * (e.g. tangent or normal estimation from high-order primitives). 
     *
     * @tparam TSegmentComputer a model of segment computer. 
     *
     * The computation is delegated to a functor.  
     *
     * @tparam Functor a binary functor
     *
     * This class is a model of CSegmentComputerEstimator
     */

    template <typename TSegmentComputer, typename Functor, 
	      typename ReturnType = typename Functor::Value>
    class PosDepScaleIndepSCEstimator
    {

    public: 

      // ----------------------- inner type ------------------------------
      typedef TSegmentComputer SegmentComputer;
      typedef typename SegmentComputer::ConstIterator ConstIterator; 
      typedef ReturnType Quantity;

      // ----------------------- Internal data  ------------------------------
    public:
      /**
       * Begin iterator
       */
      ConstIterator myBegin; 
      /**
       * End iterator
       */
      ConstIterator myEnd;
      /**
       * Aliasing pointer on a constant segment computer
       */
      const SegmentComputer* mySCPtr; 
      /**
       * Functor used for the estimation
       */
      Functor myFunctor; 

      // ----------------------- Standard services ------------------------------
    public:

      /**
       * Checks the validity/consistency of the object.
       * @return 'true' if the object is valid, 'false' otherwise.
       */
      bool isValid() const 
      {
	return (mySCPtr != 0); 
      };

      // ----------------------- Interface --------------------------------------
    public:

      /**
       * Default constructor
       */
      PosDepScaleIndepSCEstimator(): myBegin(), myEnd(), mySCPtr(0), myFunctor() {}

      /**
       * Initialisation.
       * @param itb begin iterator
       * @param ite end iterator
       */
      void init(const double /*h*/, const ConstIterator& itb, const ConstIterator& ite)
      {
        myBegin = itb;
        myEnd = ite; 
      }

      /**
       * Attach the estimator to @e aSC
       * @param aSC an instance of segment computer. 
       */
      void attach(const SegmentComputer& aSC) 
      {
	mySCPtr = &aSC; 
      };

      /**
       * Unique estimation 
       * @param it any iterator
       * @return the estimated quantity
       */
      Quantity eval(const ConstIterator& it) const
      {
	ASSERT( mySCPtr ); 
        return myFunctor( it, *mySCPtr ); 
      }

      /**
       * Estimation for a subrange [@e itb , @e ite )
       * @param itb subrange begin iterator
       * @param ite subrange end iterator
       * @param result output iterator on the estimated quantity
       *
       * @return the estimated quantity
       * from itb till ite (excluded)
       */
      template <typename OutputIterator>
      OutputIterator eval(const ConstIterator& itb, const ConstIterator& ite, 
			  OutputIterator result) const
      {
	ASSERT( mySCPtr ); 

	// do-while loop to deal with the case of a whole circular range
	if (isNotEmpty(itb, ite))
	  {
	    ConstIterator it = itb; 
	    do
	      {
		*result++ = myFunctor( it, *mySCPtr ); 
		++it; 
	      } while (it != ite);
	  }

        return result; 
      }

    }; // end of class PosDepScaleIndepSCEstimator

    /////////////////////////////////////////////////////////////////////////////
    // class PosDepScaleDepSCEstimator
    /////////////////////////////////////////////////////////////////////////////
    /**
     * Description of class 'PosDepScaleDepSCEstimator' <p> Aim: 
     * estimates a geometric quantity from a segment computer. 
     * The estimation is both position-dependent and scale-dependent 
     * (typically distance of a point to an underlying curve). 
     *
     * @tparam TSegmentComputer a model of segment computer. 
     *
     * The computation is delegated to a Functor.  
     *
     * @tparam Functor a functor
     *
     * This class is a model of CSegmentComputerEstimator
     */

    template <typename TSegmentComputer, typename Functor, 
	      typename ReturnType = typename Functor::Value>
    class PosDepScaleDepSCEstimator
    {

    public: 

      // ----------------------- inner type ------------------------------
      typedef TSegmentComputer SegmentComputer;
      typedef typename SegmentComputer::ConstIterator ConstIterator; 
      typedef ReturnType Quantity;

      // ----------------------- internal data ------------------------------
    public:
      /**
       * Grid step
       */
      double myH; 
      /**
       * Begin iterator
       */
      ConstIterator myBegin; 
      /**
       * End iterator
       */
      ConstIterator myEnd;
      /**
       * Aliasing pointer on a constant segment computer
       */
      const SegmentComputer* mySCPtr; 
      /**
       * Functor used for the estimation
       */
      Functor myFunctor; 

      // ----------------------- Standard services ------------------------------
    public:

      /**
       * Default constructor.
       * NB: not valid.
       */
      PosDepScaleDepSCEstimator()
	: myH( 0.0 ), myBegin(), myEnd(), mySCPtr(0), myFunctor()
      {
      }
      /**
       * Copy constructor.
       * @param other the object to copy.
       */
      PosDepScaleDepSCEstimator( const PosDepScaleDepSCEstimator& other )
	: myH( other.myH ), myBegin( other.myBegin ), myEnd( other.myEnd ), 
	  mySCPtr( other.mySCPtr ), myFunctor( other.myFunctor )
      {
      }
      /**
       * Assignement.
       * @param other the object to copy.
       */
      PosDepScaleDepSCEstimator& operator=( const PosDepScaleDepSCEstimator& other )
      {
	if (this != &other)
	  {
	    myH = other.myH; 
	    myBegin = other.myBegin; 
	    myEnd = other.myEnd; 
	    mySCPtr = other.mySCPtr; 
	    myFunctor = other.myFunctor; 
	  }
	return *this; 
      }
      /**
       * Destructor
       */
      ~PosDepScaleDepSCEstimator() {}

      /**
       * Checks the validity/consistency of the object.
       * @return 'true' if the object is valid, 'false' otherwise.
       */
      bool isValid() const 
      {
	return (myH > 0)&&(mySCPtr != 0); 
      };



      // ----------------------- Interface --------------------------------------
    public:

      /**
       * Initialisation.
       * @param h grid size
       * @param itb begin iterator
       * @param ite end iterator
       */
      void init(const double h, const ConstIterator& itb, const ConstIterator& ite)
      {
        myH = h; 
        myBegin = itb;
        myEnd = ite;
	ASSERT( myH > 0 );  
      }

      /**
       * Attach the estimator to @e aSC
       * @param aSC an instance of segment computer. 
       */
      void attach(const SegmentComputer& aSC) 
      {
	mySCPtr = &aSC; 
	ASSERT( mySCPtr ); 
      };

      /**
       * Unique estimation 
       * @param it any iterator 
       * @return the estimated quantity
       */
      Quantity eval(const ConstIterator& it) const
      {
	ASSERT( isValid() ); 
        return myFunctor( it, *mySCPtr, myH ); 
      }

      /**
       * Estimation for a subrange [@e itb , @e ite )
       * @param itb subrange begin iterator
       * @param ite subrange end iterator 
       * @param result output iterator on the estimated quantity
       *
       * @return the estimated quantity
       * from itb till ite (excluded)
       */
      template <typename OutputIterator>
      OutputIterator eval(const ConstIterator& itb, const ConstIterator& ite, 
			  OutputIterator result) const 
      {
	ASSERT( isValid() ); 

	// do-while loop to deal with the case of a whole circular range
	if (isNotEmpty(itb, ite))
	  {
	    ConstIterator it = itb; 
	    do
	      {
		*result++ = myFunctor( it, *mySCPtr, myH ); 
		++it; 
	      } while (it != ite);
	  }

        return result; 
      }

    }; // end of class PosDepScaleDepSCEstimator

    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    /**
     * Description of class 'TangentAngleFromDSS' <p> Aim: 
     * computes the tangent orientation of a DSS 
     * (angle in [-pi,+pi] radians between the tangent and the x-axis).
     */
    struct TangentAngleFromDSS
    {      
    public:
      typedef double Value; 


      /**
       * Operator()
       *
       * @return the angle of type double
       * (angle in [-pi,+pi] radians between the tangent and the x-axis).
       *
       * @param aDSS an instance of segment computer
       * devoted to the DSS recognition.
       *
       * @tparam DSS a model of segment computer,
       * which must have methods a() and b()
       * returning the y- and x-component of the tangent vector.
       */
      template<typename DSS>
      Value operator() (const DSS& aDSS) const 
      {
	Value a = (Value) NumberTraits<typename DSS::Integer>
	  ::castToDouble(aDSS.a());      
	Value b = (Value) NumberTraits<typename DSS::Integer>
	  ::castToDouble(aDSS.b());      

	return std::atan2(a,b);
      }
    }; 
    /**
     * Description of class 'NormalizedTangentVectorFromDSS' <p> Aim: 
     * computes the unit vector of a DSS 
     */
    struct NormalizedTangentVectorFromDSS
    {      
    public:
      typedef DGtal::PointVector<2,double> RealVector; 
      typedef RealVector Value;

      /**
       * Operator()
       *
       * @return normalized tangent 
       *
       * @param aDSS an instance of segment computer
       * devoted to the DSS recognition.

       * @tparam DSS a model of segment computer,
       * which must have methods a() and b()
       * returning the y- and x-component of the tangent vector.
       */
      template<typename DSS>
      Value operator() (const DSS& aDSS) const 
      {
	double x = NumberTraits<typename DSS::Integer>
	  ::castToDouble( aDSS.b() ); 
	double y = NumberTraits<typename DSS::Integer>
	  ::castToDouble( aDSS.a() );
	RealVector v(x,y); 
	double norm = v.norm(RealVector::L_2);
	v /= norm; 
	return v;
      }
    }; 
    /**
     * Description of class 'TangentVectorFromDSS' <p> Aim: 
     * computes the tangent vector of a DSS 
     */
    template<typename DSS>
    struct TangentVectorFromDSS
    {      
    public:
      typedef typename DSS::Vector Value;

      /**
       * Operator()
       *
       * @return tangent vector 
       *
       * @param aDSS an instance of segment computer
       * devoted to the DSS recognition.

       */
      Value operator() (const DSS& aDSS) const 
      {
	return Value(aDSS.b(), aDSS.a());
      }
    }; 
    /**
     * Description of class 'CurvatureFromDCA' <p> Aim: 
     * computes the curvature from a geometricDCA
     * at a given grid step.
     *
     * @tparam isCCW boolean equal to 'true' 
     * for a scanning in a counter-clockwise (CCW) 
     * orientation, 'false' otherwise. 
     * For instance, the estimated curvature of 
     * a digital circle, scanned in a CCW (resp. CW)
     * orientation, is positive (resp. negative). 
     */
    template<bool isCCW = true>
    struct CurvatureFromDCA
    {      
    public:
      typedef double Value; 

      /**
       * Operator()
       *
       * @return curvature 
       *
       * @param aDCA an instance of segment computer
       * devoted to the DCA recognition.
       * @param aH grid step
       *
       * @tparam DCA a model of segment computer
       * devoted to the DCA recognition, 
       * basically geometricDCA.
       */
      template<typename DCA>
      Value operator() (const DCA& aDCA, const double& aH = 1.0) const 
      {
  	if ( aDCA.isStraight() )
  	  return 0.0; 
	else
	  return ( aDCA.getSeparatingCircle().getCurvature() / aH );
      }
    }; 
    template<>
    struct CurvatureFromDCA<false>
    {      
    public:
      typedef double Value; 

      template<typename DCA>
      Value operator() (const DCA& aDCA, const Value& aH = 1.0) const 
      {
  	if ( aDCA.isStraight() )
  	  return 0.0; 
	else
	  return - ( aDCA.getSeparatingCircle().getCurvature() / aH );
      }
    }; 
    /**
     * Description of class 'NormalVectorFromDCA' <p> Aim: 
     * estimates the normal at a given position from a geometricDCA. 
     */
    struct NormalVectorFromDCA
    {      
    public:
      typedef PointVector<2,double> Value; 


      /**
       * Operator()
       *
       * @return normal at @e it 
       *
       * @param it position where the estimation has to be done
       * @param aDCA an instance of segment computer
       * devoted to the DCA recognition.
       *
       * @tparam DCA a model of segment computer
       * devoted to the DCA recognition, 
       * basically geometricDCA.
       */
      template<typename DCA>
      Value operator() (const typename DCA::ConstIterator& it, 
			const DCA& aDCA) const 
      {
	typedef typename DCA::Pair Pair; 
	typedef typename DCA::Point Point;
	typedef typename Point::Coordinate Coordinate; 
	
  	if ( !aDCA.isStraight() )
  	  {
  	    //separating circle center
  	    double c0, c1, r; 
  	    aDCA.getSeparatingCircle().getParameters(c0, c1, r);
  	    //point
	    Pair pair = *it; 
	    Point i = pair.first; 
	    Point o = pair.second;
	    double m0 = NumberTraits<Coordinate>::castToDouble(i[0]+o[0]) / 2.0; 
	    double m1 = NumberTraits<Coordinate>::castToDouble(i[1]+o[1]) / 2.0;
	    //normal vector 
	    double v0 = m0 - c0; 
	    double v1 = m1 - c1; 
	    //norm
	    double n = std::sqrt(v0*v0 + v1*v1); 
	    return Value( v0/n, v1/n );
  	  }
  	else
  	  {
	    //separating straight line and normal vector
	    double a, b, c; 
	    aDCA.getStabbingLineComputerPtr()->getParameters(a, b, c);
	    //norm
	    double n = std::sqrt(a*a + b*b); 
  	    return Value( a/n, b/n ); 
  	  }
      }
    }; 

    /**
     * Description of class 'TangentVectorFromDCA' <p> Aim: 
     * estimates the tangent at a given position from a geometricDCA. 
     */
    struct TangentVectorFromDCA
    {      
    public:
      typedef PointVector<2,double> Value; 

      /**
       * Operator()
       *
       * @return tangent at @e it 
       *
       * @param it position where the estimation has to be done
       * @param aDCA an instance of segment computer
       * devoted to the DCA recognition.
       *
       * @tparam DCA a model of segment computer
       * devoted to the DCA recognition, 
       * basically geometricDCA.
       *
       * @see NormalVectorFromDCA
       */
      template<typename DCA>
      Value operator() (const typename DCA::ConstIterator& it, 
			const DCA& aDCA) const 
      {
	NormalVectorFromDCA f; 
	Value normal = f(it, aDCA); 
	return Value( normal[1], normal[0] ); 
      }
    }; 

    /**
     * Description of class 'DistanceFromDCA' <p> Aim: 
     * estimates the distance of a given pair of points
     * to the separating circle of a DCA. 
     */
    struct DistanceFromDCA
    {      
    public:
      typedef std::pair<double,double> Value; 

      /**
       * Operator()
       *
       * @return distances (in a pair) of the 
       * inner and outer points pointed by @e it
       * to the separating circle of @e aDCA
       *
       * @param it position where the estimation has to be done
       * @param aDCA an instance of segment computer
       * devoted to the DCA recognition.
       * @param aH grid step
       *
       * @tparam DCA a model of segment computer
       * devoted to the DCA recognition, 
       * basically geometricDCA.
       */
      template<typename DCA>
      Value operator() (const typename DCA::ConstIterator& it, 
			const DCA& aDCA, const double& aH) const 
      {
	typedef typename DCA::Pair Pair; 
	typedef typename DCA::Point Point;
	typedef typename Point::Coordinate Coordinate; 
	
  	if ( !aDCA.isStraight() )
  	  {
  	    //separating circle center
  	    double c0, c1, r; 
  	    aDCA.getSeparatingCircle().getParameters(c0, c1, r);
  	    //points
	    Pair pair = *it; 
	    Point i = pair.first; 
	    Point o = pair.second;
	    //distances
	    double distI0 = NumberTraits<Coordinate>::castToDouble(i[0]) - c0; 
	    double distI1 = NumberTraits<Coordinate>::castToDouble(i[1]) - c1;
	    double distI = std::sqrt( distI0*distI0 + distI1*distI1 ) - r; 
	    double distO0 = NumberTraits<Coordinate>::castToDouble(o[0]) - c0; 
	    double distO1 = NumberTraits<Coordinate>::castToDouble(o[1]) - c1;
	    double distO = std::sqrt( distO0*distO0 + distO1*distO1 ) - r; 
	    return Value( distI*aH, distO*aH );
  	  }
  	else
  	  {
	    //separating straight line
	    double a, b, c; 
	    aDCA.getStabbingLineComputerPtr()->getParameters(a, b, c); 
	    //norm
	    double n = std::sqrt(a*a + b*b); 
  	    //points
	    Pair pair = *it; 
	    Point i = pair.first; 
	    Point o = pair.second;
	    //distances
	    double rI = NumberTraits<Coordinate>::castToDouble(i[0])*a + 
	      NumberTraits<Coordinate>::castToDouble(i[1])*b + c;
	    double distI = rI / n; 
	    double rO = NumberTraits<Coordinate>::castToDouble(o[0])*a + 
	      NumberTraits<Coordinate>::castToDouble(o[1])*b + c;
	    double distO = rO / n; 
  	    return Value( distI*aH, distO*aH ); 
  	  }
      }
    }; 

  }//namespace detail



  //-------------------------------------------------------------------------------------------
  /**
   * Description of class 'TangentFromDSSEstimator' <p> Aim: 
   * estimates the (normalized) tangent vector from a DSS
   * recognized by some segment computers. 
   *
   * @tparam DSSComputer a model of segment computer
   * devoted the DSS recognition
   */
  template <typename DSSComputer>
  class TangentFromDSSEstimator: 
    public detail::PosIndepScaleIndepSCEstimator<DSSComputer, detail::NormalizedTangentVectorFromDSS>
  {
    typedef 
    detail::PosIndepScaleIndepSCEstimator<DSSComputer, detail::NormalizedTangentVectorFromDSS> 
    Super; 

  public: 
    /**
     * Default Constructor.
     */
    TangentFromDSSEstimator(): Super() {};
    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    TangentFromDSSEstimator( const TangentFromDSSEstimator & other ): Super(other) {};
  }; 

  //-------------------------------------------------------------------------------------------
  /**
   * Description of class 'TangentVectorFromDSSEstimator' <p> Aim: 
   * estimates the (not normalized) tangent vector from the slope
   * parameters of a DSS recognized by a segment computer. 
   *
   * @tparam DSSComputer a model of segment computer
   * devoted the DSS recognition
   */
  template <typename DSSComputer>
  class TangentVectorFromDSSEstimator: 
    public detail::PosIndepScaleIndepSCEstimator<DSSComputer, detail::TangentVectorFromDSS<DSSComputer> >
  {
    typedef 
    detail::PosIndepScaleIndepSCEstimator<DSSComputer, detail::TangentVectorFromDSS<DSSComputer> > 
    Super; 

  public: 
    /**
     * Default Constructor.
     */
    TangentVectorFromDSSEstimator(): Super() {};
    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    TangentVectorFromDSSEstimator( const TangentVectorFromDSSEstimator & other ): Super(other) {};
  }; 

  //-------------------------------------------------------------------------------------------
  /**
   * Description of class 'TangentAngleFromDSSEstimator' <p> Aim: 
   * estimates the tangent angle from a DSS
   * recognized by some segment computers. 
   * (angle in [-pi,+pi] radians between the tangent and the x-axis).
   *
   * @tparam DSSComputer a model of segment computer
   * devoted the DSS recognition
   */
  template <typename DSSComputer>
  class TangentAngleFromDSSEstimator: 
    public detail::PosIndepScaleIndepSCEstimator<DSSComputer, detail::TangentAngleFromDSS>
  {
    typedef 
    detail::PosIndepScaleIndepSCEstimator<DSSComputer, detail::TangentAngleFromDSS> 
    Super; 

  public: 
    /**
     * Default Constructor.
     */
    TangentAngleFromDSSEstimator(): Super() {};
    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    TangentAngleFromDSSEstimator( const TangentAngleFromDSSEstimator & other ): Super(other) {};
  }; 

  //-------------------------------------------------------------------------------------------
  /**
   * Description of class 'CurvatureFromDCAEstimator' <p> Aim: 
   * estimates the curvature from a DCA
   * recognized by a segment computer, 
   * basically geometricDCA.
   *
   * @tparam DCAComputer a model of segment computer
   * devoted the DCA recognition
   *
   * @tparam isCCW boolean equal to 'true' (default)
   * for a scanning in a counter-clockwise (CCW) 
   * orientation, 'false' otherwise, i.e in a 
   * clockwise (CW) orientation. 
   * For instance, the estimated curvature of 
   * a digital circle, scanned in a CCW (resp. CW)
   * orientation, is positive (resp. negative). 
   */
  template <typename DCAComputer, bool isCCW = true>
  class CurvatureFromDCAEstimator: 
    public detail::PosIndepScaleDepSCEstimator<DCAComputer, 
					       detail::CurvatureFromDCA<isCCW> >
  {
    typedef 
    detail::PosIndepScaleDepSCEstimator<DCAComputer, detail::CurvatureFromDCA<isCCW> > 
    Super; 

  public: 
    /**
     * Default Constructor.
     */
    CurvatureFromDCAEstimator(): Super() {};
    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    CurvatureFromDCAEstimator( const CurvatureFromDCAEstimator & other ): Super(other) {};
  }; 

  //-------------------------------------------------------------------------------------------
  /**
   * Description of class 'NormalFromDCAEstimator' <p> Aim: 
   * estimates the (normalized) normal vector at some position from a DCA
   * recognized by a segment computer, basically geometricDCA.
   *
   * @tparam DCAComputer a model of segment computer
   * devoted the DCA recognition
   */
  template <typename DCAComputer>
  class NormalFromDCAEstimator: 
    public detail::PosDepScaleIndepSCEstimator<DCAComputer, 
					       detail::NormalVectorFromDCA>
  {
    typedef 
    detail::PosDepScaleIndepSCEstimator<DCAComputer, detail::NormalVectorFromDCA> 
    Super; 

  public: 
    /**
     * Default Constructor.
     */
    NormalFromDCAEstimator(): Super() {};
    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    NormalFromDCAEstimator( const NormalFromDCAEstimator & other ): Super(other) {};
  }; 

  //-------------------------------------------------------------------------------------------
  /**
   * Description of class 'TangentFromDCAEstimator' <p> Aim: 
   * estimates the (normalized) tangent vector at some position from a DCA
   * recognized by a segment computer, basically geometricDCA.
   *
   * @tparam DCAComputer a model of segment computer
   * devoted the DCA recognition
   */
  template <typename DCAComputer>
  class TangentFromDCAEstimator: 
    public detail::PosDepScaleIndepSCEstimator<DCAComputer, 
					       detail::TangentVectorFromDCA>
  {
    typedef 
    detail::PosDepScaleIndepSCEstimator<DCAComputer, detail::TangentVectorFromDCA> 
    Super; 

  public: 
    /**
     * Default Constructor.
     */
    TangentFromDCAEstimator(): Super() {};
    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    TangentFromDCAEstimator( const TangentFromDCAEstimator & other ): Super(other) {};
  }; 

  //-------------------------------------------------------------------------------------------
  /**
   * Description of class 'DistanceFromDCAEstimator' <p> Aim: 
   * estimates the (Euclidean) distance of some points to 
   * the separating circle of a DCA recognized by a 
   * segment computer, basically geometricDCA.
   *
   * @tparam DCAComputer a model of segment computer
   * devoted the DCA recognition
   */
  template <typename DCAComputer>
  class DistanceFromDCAEstimator: 
    public detail::PosDepScaleDepSCEstimator<DCAComputer, 
					     detail::DistanceFromDCA>
  {
    typedef 
    detail::PosDepScaleDepSCEstimator<DCAComputer, detail::DistanceFromDCA> 
    Super; 

  public: 
    /**
     * Default Constructor.
     */
    DistanceFromDCAEstimator(): Super() {};
    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    DistanceFromDCAEstimator( const DistanceFromDCAEstimator & other ): Super(other) {};
  }; 

  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  namespace detail
  {
    /**
     * Description of class 'CurvatureFromDSSLength' <p> Aim: 
     * Computes the curvature @f$ k @f$ from the discrete length @f$ l @f$ of a DSS 
     * as follow: 
     * @f$ 1/k = l*l/8 + 1/2 @f$
     *
     * @note Adaption from 
     *  Coeurjolly, D. and Miguet, S. and Tougne, L.
     *  "Discrete Curvature Based on Osculating Circle Estimation", 
     * Proc. IWVF, LNCS, vol 2059, pp.303-312, 2001
     */
    struct CurvatureFromDSSLength
    {      
    public:
      typedef double Value; 

      template<typename DSS>
      Value operator() (const DSS& aDSS) const 
      {
	typedef typename DSS::Vector Vector; 
	//length
	Vector v = ( *aDSS.begin() - *boost::prior(aDSS.end()) ); 
	Value l = v.norm(Vector::L_2);
	//result
	return 1/( (l*l)/8 + 0.5 );  
      }
    }; 

    /**
     * Description of class 'CurvatureFromDSSLengthAndWidth' <p> Aim: 
     * computes the curvature @f$ k @f$ from 
     * the length  @f$ l @f$ and the width  @f$ w @f$ of a DSS as follow: 
     *  @f$ 1/k = (l*l)/(8*w) + w/2 @f$
     *
     * @note Adaption from 
     *  Coeurjolly, D. and Miguet, S. and Tougne, L.
     *  "Discrete Curvature Based on Osculating Circle Estimation", 
     * Proc. IWVF, LNCS, vol 2059, pp.303-312, 2001
     */
    struct CurvatureFromDSSLengthAndWidth
    {      
    public:
      typedef double Value; 

      template<typename DSS>
      Value operator() (const DSS& aDSS) const 
      {
	typedef typename DSS::Vector Vector; 
	//length
	Vector v = ( *aDSS.begin() - *boost::prior(aDSS.end()) ); 
	Value l = v.norm(Vector::L_2);
	//width
	Vector t( aDSS.b(), aDSS.a() );
	Value w = 1.0 / v.norm(Vector::L_2); 
	//result
	return 1.0/( (l*l)/(8*w) + w/2 ); 
      }
    }; 

    /////////////////////////////////////////////////////////////////////////////
    // class CurvatureFromDSSBaseEstimator
    /////////////////////////////////////////////////////////////////////////////
    /**
     * Description of class 'CurvatureFromDSSBaseEstimator' <p> Aim: 
     * computes a curvature quantity from the length and/or the width of a DSS.
     *
     * @tparam DSSComputer a model of segment computer 
     * devoted to the DSS recognition.
     *
     * The computation is delegated to a functor. 
     *
     * @tparam Functor a model of unary functor
     * taking a DSS as input and returning a double
     *
     * This class is a model of CSegmentComputerEstimator
     */

    template <typename DSSComputer, typename Functor = detail::CurvatureFromDSSLength >
    class CurvatureFromDSSBaseEstimator
    {

    public: 

      // ----------------------- inner type ------------------------------------
      typedef DSSComputer SegmentComputer; 
      typedef typename DSSComputer::ConstIterator ConstIterator; 
      typedef double Quantity;

      BOOST_CONCEPT_ASSERT(( concepts::CUnaryFunctor< Functor, SegmentComputer, Quantity > ));  

      // ----------------------- internal data ------------------------------
    public:
      /**
       * Grid step
       */
      double myH; 
      /**
       * Begin iterator
       */
      ConstIterator myBegin; 
      /**
       * End iterator
       */
      ConstIterator myEnd;
      /**
       * Aliasing pointer on a constant segment computer
       */
      const SegmentComputer* mySCPtr; 
      /**
       * Functor used for the estimation
       */
      Functor myFunctor; 

      // ----------------------- Standard services ------------------------------
    public:

      /**
       * Default constructor.
       * NB: not valid.
       */
      CurvatureFromDSSBaseEstimator()
	: myH( 0.0 ), myBegin(), myEnd(), mySCPtr(0), myFunctor()
      {
      }
      /**
       * Copy constructor.
       * @param other the object to copy.
       */
      CurvatureFromDSSBaseEstimator( const CurvatureFromDSSBaseEstimator& other )
	: myH( other.myH ), myBegin( other.myBegin ), myEnd( other.myEnd ), 
	  mySCPtr( other.mySCPtr ), myFunctor( other.myFunctor )
      {
      }
      /**
       * Assignement.
       * @param other the object to copy.
       */
      CurvatureFromDSSBaseEstimator& operator=( const CurvatureFromDSSBaseEstimator& other )
      {
	if (this != &other)
	  {
	    myH = other.myH; 
	    myBegin = other.myBegin; 
	    myEnd = other.myEnd; 
	    mySCPtr = other.mySCPtr; 
	    myFunctor = other.myFunctor; 
	  }
	return *this; 
      }
      /**
       * Destructor
       */
      ~CurvatureFromDSSBaseEstimator() {}

      /**
       * Checks the validity/consistency of the object.
       * @return 'true' if the object is valid, 'false' otherwise.
       */
      bool isValid() const
      {
	return (myH > 0)&&(mySCPtr != 0); 
      };

      // ----------------------- Interface --------------------------------------
    public:

      /**
       * Initialisation.
       * @param h grid size
       * @param itb begin iterator
       * @param ite end iterator
       */
      void init(const double h, const ConstIterator& itb, const ConstIterator& ite)
      {
        myH = h; 
        myBegin = itb;
        myEnd = ite;
	ASSERT( myH > 0 );  
      }

      /**
       * Unique estimation 
       * @return the estimated quantity
       */
      Quantity eval(const ConstIterator& /*it*/)
      {
	ASSERT( isValid() ); 

	//types
	typedef typename DSSComputer::Integer Integer; 
	typedef typename DSSComputer::Vector Vector; 

	//curvature value
	Quantity k = 0;  


	//begin and end iterators
	//(back point on the first point)
	//(front point on the last point)
	ConstIterator back = mySCPtr->begin();  
	ConstIterator front = mySCPtr->end();
	bool isConnectedAtBack = isNotEmpty(myBegin, back)
	  &&((*boost::prior(back)-*back).norm(Vector::L_1) <= NumberTraits<Integer>::ONE);  
	bool isConnectedAtFront = isNotEmpty(front, myEnd)
	  &&((*boost::prior(front)-*front).norm(Vector::L_1) <= NumberTraits<Integer>::ONE);  
  

	if (isConnectedAtBack) {
	  if (isConnectedAtFront) {

	    --back;

	    //parameters
	    Integer mu = mySCPtr->mu();
	    Integer omega = mySCPtr->omega();

	    //cases
	    if ( (mySCPtr->remainder(*back)<=mu-1)&&
		 (mySCPtr->remainder(*front)<=mu-1) ) {                //convex
	      k = myFunctor(*mySCPtr) / myH; 
	    } else if ( (mySCPtr->remainder(*back)>=mu+omega)&&
			(mySCPtr->remainder(*front)>=mu+omega) ) {           //concave
	      k = -myFunctor(*mySCPtr) / myH; 
	    } //else                                                  //inflection

	  } else {

	    --back;

	    //parameters
	    Integer mu = mySCPtr->mu();
	    Integer omega = mySCPtr->omega();

	    //cases
	    if ( (mySCPtr->remainder(*back)<=mu-1) ) {                //convex
	      k = myFunctor(*mySCPtr) / myH; 
	    } else if ( (mySCPtr->remainder(*back)>=mu+omega) ) {     //concave
	      k = -myFunctor(*mySCPtr) / myH; 
	    } //else                                                 //inflection

	  }
	} else if (isConnectedAtFront) {

          //parameters
          Integer mu = mySCPtr->mu();
          Integer omega = mySCPtr->omega();

          //cases
          if ( (mySCPtr->remainder(*front)<=mu-1) ) {                //convex
            k = myFunctor(*mySCPtr) / myH; 
          } else if ( (mySCPtr->remainder(*front)>=mu+omega) ) {     //concave
            k = -myFunctor(*mySCPtr) / myH; 
          } //else                                                  //inflection

	} //else cannot be extended: k is set to 0

	return k;

      }

      /**
       * Estimation for a subrange [@e itb , @e ite )
       * @param itb subrange begin iterator
       * @param ite subrange end iterator 
       * @param result output iterator on the estimated quantity
       *
       * @return the estimated quantity
       * from itb till ite (excluded)
       */
      template <typename OutputIterator>
      OutputIterator eval(const ConstIterator& itb, const ConstIterator& ite, 
			  OutputIterator result)
      {
	ASSERT( isValid() ); 

	// do-while loop to deal with the case of a whole circular range
	if (isNotEmpty(itb, ite))
	  {
	    ConstIterator it = itb; 
	    do
	      {
		*result++ = eval( it ); 
		++it; 
	      } while (it != ite);
	  }

        return result; 
      }

      /**
       * Attach the estimator to @e aSC
       * @param aSC an instance of segment computer. 
       */
      void attach(const SegmentComputer& aSC) 
      {
	mySCPtr = &aSC; 
	ASSERT( mySCPtr ); 
      };


    }; // end of class CurvatureFromDSSBaseEstimator

  }//namespace detail



  //-------------------------------------------------------------------------------------------
  /**
   * Description of class 'CurvatureFromDSSLengthEstimator' <p> Aim: 
   * estimates the curvature from a DSS
   * recognized by a segment computer.
   *
   * The curvature @f$ k @f$ is defined from the discrete length @f$ l @f$ 
   * of a DSS as follow: 
   * @f$ 1/k = l*l/8 + 1/2 @f$
   *
   * @note Adaption from 
   *  Coeurjolly, D. and Miguet, S. and Tougne, L.
   *  "Discrete Curvature Based on Osculating Circle Estimation", 
   * Proc. IWVF, LNCS, vol 2059, pp.303-312, 2001
   *
   * In this approach, the DSS is viewed as the chord 
   * at a distance h (the grid step) to the osculating circle. 
   * Unfortunately, maximal DSS are in general too short.
   *
   * @tparam DSSComputer a model of segment computer
   * devoted the DSS recognition
   */
  template <typename DSSComputer>
  class CurvatureFromDSSLengthEstimator: 
    public detail::CurvatureFromDSSBaseEstimator<DSSComputer, detail::CurvatureFromDSSLength >
  {

    typedef detail::CurvatureFromDSSBaseEstimator<DSSComputer, detail::CurvatureFromDSSLength > Super; 
 
  public: 
    /**
     * Default Constructor.
     */
    CurvatureFromDSSLengthEstimator(): Super() {};
    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    CurvatureFromDSSLengthEstimator( const CurvatureFromDSSLengthEstimator & other ): Super(other) {};
  }; 

  //-------------------------------------------------------------------------------------------
  /**
   * Description of class 'CurvatureFromDSSLengthEstimator' <p> Aim: 
   * estimates the curvature from a DSS
   * recognized by a segment computer.
   *
   * The curvature @f$ k @f$ is defined from 
   * the length  @f$ l @f$ and the width  @f$ w @f$ of a DSS as follow: 
   *  @f$ 1/k = (l*l)/(8*w) + w/2 @f$
   *
   * @note Adaption from 
   *  Coeurjolly, D. and Miguet, S. and Tougne, L.
   *  "Discrete Curvature Based on Osculating Circle Estimation", 
   * Proc. IWVF, LNCS, vol 2059, pp.303-312, 2001
   *
   * @tparam DSSComputer a model of segment computer
   * devoted the DSS recognition
   */
  template <typename DSSComputer>
  class CurvatureFromDSSEstimator: 
    public detail::CurvatureFromDSSBaseEstimator<DSSComputer, detail::CurvatureFromDSSLengthAndWidth >
  {

    typedef detail::CurvatureFromDSSBaseEstimator<DSSComputer, detail::CurvatureFromDSSLengthAndWidth > Super; 
 
  public: 
    /**
     * Default Constructor.
     */
    CurvatureFromDSSEstimator(): Super() {};
    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    CurvatureFromDSSEstimator( const CurvatureFromDSSEstimator & other ): Super(other) {};
  }; 


} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SegmentComputerEstimators_h

#undef SegmentComputerEstimators_RECURSES
#endif // else defined(SegmentComputerEstimators_RECURSES)
