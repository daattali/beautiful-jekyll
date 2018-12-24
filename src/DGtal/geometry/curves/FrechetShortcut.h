
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
 * @file FrechetShortcut.h
 * @author Isabelle Sivignon (\c isabelle.sivignon@gipsa-lab.grenoble-inp.fr )
 * gipsa-lab Grenoble Images Parole Signal Automatique (CNRS, UMR 5216), CNRS, France
 *
 * @date 2012/02/24
 *
 * @brief Header file for module FrechetShortcut.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(FrechetShortcut_RECURSES)
#error Recursive header files inclusion detected in FrechetShortcut.h
#else // defined(FrechetShortcut_RECURSES)
/** Prevents recursive inclusion of headers. */
#define FrechetShortcut_RECURSES

#if !defined FrechetShortcut_h
/** Prevents repeated inclusion of headers. */
#define FrechetShortcut_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/base/Common.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/arithmetic/IntegerComputer.h"
#include <boost/icl/interval_set.hpp>
#include <map>

//////////////////////////////////////////////////////////////////////////////

#include "DGtal/geometry/curves/SegmentComputerUtils.h"

namespace DGtal
{
  
  /////////////////////////////////////////////////////////////////////////////
  // class FrechetShortcut
  /**
   * Description of class 'FrechetShortcut' <p>
   * @brief Aim:
   * On-line computation Computation of the longest shortcut according to the Fréchet
   * distance for a given error. See related article:
   *       Sivignon, I., (2011). A Near-Linear Time Guaranteed Algorithm
   *       for Digital Curve Simplification under the Fréchet
   *       Distance. DGCI 2011. Retrieved from 
   *       http://link.springer.com/chapter/10.1007/978-3-642-19867-0_28
   *      
   *
   
   The algorithm we propose uses an approximation of the Fréchet distance,
   but a guarantee over the quality of the simplification is
   proved. Moreover, even if the theoretical complexity of the algorithm is
   in @f$ O(n log(n)) @f$, experiments show a linear behaviour in practice. 
   
   We denote by @f$ error(i,j) @f$ the Fréchet distance between the
   segment @f$[p_ip_j]@f$ and the part of the curve between the points
   @f$p_i@f$ and @f$p_j@f$. 
   The approximation of the Fréchet distance is based on the fact that
   @f$ error(i,j) @f$ can be upper and lower bounded by a function of
   two values, namely @f$ w(i,j)$ @f$ and @f$ b(i,j) @f$, where @f$
   w(i,j)$ @f$ is the width of the points between @f$p_i@f$ and
   @f$p_j@f$ in the direction @f$ p_ip_j @f$ and @f$ b(i,j) @f$ is the
   length of the longest backpath in this direction. 

   Then, the algorithm consists in greedily reading the points of the
   curves from a first point given by myBegin, while updating the values
   @f$ w(i,j) @f$ and @f$ b(i,j) @f$ on the fly. 
   
   * This class is a model of the concept CForwardSegmentComputer
   *
   * It should be used with the Curve object (defined in StdDefs.h) and
   *its PointsRange as follows:
   *
   * @snippet geometry/curves/exampleFrechetShortcut.cpp FrechetShortcutUsage
   *
   *@tparam TIterator Iterator type on 2D digital points, TInteger type
   *of integer  
   *
   *@see exampleFrechetShortcut.cpp testFrechetShortcut.cpp
   *
   */
  
  
  template <typename TIterator,typename TInteger = typename IteratorCirculatorTraits<TIterator>::Value::Coordinate>
    class FrechetShortcut
    {
      // ----------------------- Standard services ------------------------------
    public:
    
    //entier
    
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<TInteger> ) );
    typedef TInteger Integer;
    
    
    
    //required types
    typedef TIterator ConstIterator;
    typedef FrechetShortcut<ConstIterator,Integer> Self; 
    typedef FrechetShortcut<std::reverse_iterator<ConstIterator>,Integer> Reverse;
    
    //2D point and 2D vector
    typedef typename IteratorCirculatorTraits<ConstIterator>::Value Point; 
    typedef typename IteratorCirculatorTraits<ConstIterator>::Value Vector; 
    typedef typename Vector::Coordinate Coordinate;
    
    /**
     Class backpath: data structures and methods to handle the backpath
     update
  */
  class Backpath
  {
  private:
    /**
     * Pointer to the FrechetShortcut
     */
    const FrechetShortcut<ConstIterator,Integer> *myS;
    
  protected: 
    
    /**  
	 Attributes of occulter points: angles min and max for which
	the point is an occulter 
    */
    typedef struct occulter_attributes{
      double angle_min; // 
      double angle_max; // 
    } occulter_attributes;
    
    /**
       Map between the point and their attributes if they are
       occulters 
    */
    typedef std::map <ConstIterator,occulter_attributes > occulter_list;
    
  public:
    friend class FrechetShortcut<ConstIterator,Integer>;
    
    
  public:
    
    typedef boost::icl::interval_set<double> IntervalSet;
    
      /** 
	  Octant of work 
      */
      int myQuad; 
      
      /** 
	  Current state myFlag=true if we are on a backpath, false
	  otherwise
      */
      bool myFlag;   
      
      occulter_list myOcculters;
      
      /**
	 List of forbidden intervals: intervals of angle for which there
	 exist a backpath of length greater than the error 
      */ 
      IntervalSet myForbiddenIntervals;
      
      /** 
	  pointer to the next point to be scanned: set to myEnd + 1 
       */
      ConstIterator myIt; 
      
      /** 
	  Default constructor 
      */
      Backpath();
      
      /**
	 Constructor 
	 @param s to a shortcut s
	 @param q q
      */
      Backpath(const FrechetShortcut<ConstIterator,Integer> *s ,int q);

      /**
	 Copy constructor
	 @param other a backpath
      */
      Backpath(const Backpath & other);

      
      /**
	 Assignement
	 @param other another backpath
	 @return a reference on 'this'
      */
      Backpath& operator=(const Backpath & other);
    

      /**
	 Destructor 
      */
      ~Backpath();
      
      /**
	 Resets the backpath (myFlag, myOcculters)
       */
      void reset();
      
      /**
	 Updates the backpath when a positive point is added
       */
      void addPositivePoint();

      /**
	 Updates the backpath when a negative poitn is added
       */
      void addNegativePoint();

      /**
	 General update procedure: call to addNegativePoint or
	 addPositivePoint according to the point *myIt.
	 Each octant is treated as if it was the first one, the chain
	 code between *myIt-1 and *myIt is rotated accordingly.
       */
      void updateBackPathFirstQuad(int d, const ConstIterator&);
      
      /**
	 Updates the list of occulters
       */
      void updateOcculters();

      /**
	 Updates the list of intervals
       */
      void updateIntervals();
      
   
    }; // End of class Backpath


  /**
     Class Cone: data structures and methods to handle the cone update
     used to test if the width of the shortcut is lower than the error. 
  */
  class Cone{
    
  public:
    /**
       Angle min of the cone
    */
    double myMin;
    
    /** 
	Angle max of the cone
    */
    double myMax;
    
    /**
       Boolean: true if the cone is infinite
     */
    bool myInf; // true if the cone is infinite (the whole plane)
    
    Cone();
    
    /**
       Constructor from two angles
       @param a0 an angle
       @param a1 a second angle
    */
    Cone(double a0, double a1);

    /**
       Constructor from three points x, x0, x1. The cone is defined by
       the two lines (xx0) and (xx1)
       @param x x
     @param y y
     @param x0 x0
     @param y0 y0
     @param x1 x1
     @param y1 y1
    */
    Cone(double x, double y, double x0, double y0, double x1, double y1);
    
    /**
       Test if the cone is empty
       @return true if empty, false otherwise
    */
    bool isEmpty();

    /**
       Assignement
       @param c another cone
       @return a reference on 'this'
     */
    Cone& operator=(const Cone& c);
    
    /**
       Intersect two cones: modifies 'this'
       @param c a cone to intersect with 'this'
    */
    void intersectCones(Cone c);
    
    /**
       Intersect two half cones
       @param c a cone to intersection with 'this'
       @return a cone
    */
    Cone intersectConesSimple(Cone c);
    
    /** 
	Computes the symmetrical half cone
	@return a cone
    */
    Cone symmetricalCone();
    
    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out) const;
    
    };
    
    

    
    struct Tools
    {
      /** 
	  Determines if i is between a and b in the oriented toric space
	  modulo n
	  @param i i 
	  @param a a
	  @param b b
	  @param n n
	  @return true if i is between a anb d, false otherwise
      */
      static  bool isBetween(double i, double a, double b, double n)
      {
	if(a<=b)
	  return (i>=a && i<=b);
	else
	  return ((i>=a && i<=n) || (i>=0 && i<=b));
      }
      
      
      // Code by Tim Voght
      // http://local.wasp.uwa.edu.au/~pbourke/geometry/2circle/tvoght.c
      
      /* circle_circle_intersection() *
       * Determine the points where 2 circles in a common plane intersect.
       *
       * int circle_circle_intersection(
       *                                // center and radius of 1st circle
       *                                double x0, double y0, double r0,
       *                                // center and radius of 2nd circle
       *                                double x1, double y1, double r1,
       *                                // 1st intersection point
       *                                double *xi, double *yi,              
       *                                // 2nd intersection point
       *                                double *xi_prime, double *yi_prime)
       *
       * This is a public domain work. 3/26/2005 Tim Voght
       *
       */
      /**
	 Determine the points where two circles in a common plane
	 intersect
	 Parameters: three doubles per circle (center, radius), pointers to
	 the two intersection points
	 @return 0 if the circles do not intersect each other, 1 otherwise
      */
      static int  circle_circle_intersection(double x0, double y0, double r0,
					     double x1, double y1, double r1,
					     double *xi, double *yi,
					     double *xi_prime, double *yi_prime)
      {
	double a, dx, dy, d, h, rx, ry;
	double x2, y2;
	
	/* dx and dy are the vertical and horizontal distances between
	 * the circle centers.
	 */
	dx = x1 - x0;
	dy = y1 - y0;
	
	/* Determine the straight-line distance between the centers. */
	//d = sqrt((dy*dy) + (dx*dx));
	d = hypot(dx,dy); // Suggested by Keith Briggs
	
	/* Check for solvability. */
	if (d > (r0 + r1))
	{
	  /* no solution. circles do not intersect. */
	  std::cerr  << "Warning : the two circles do not intersect -> should never happen" << std::endl;
	  return 0; //I. Sivignon 05/2010 should never happen for our specific use.
	}
	if (d < fabs(r0 - r1))
	  {
	    /* no solution. one circle is contained in the other */
	    return 0;
	  }
	
	/* 'point 2' is the point where the line through the circle
	 * intersection points crosses the line between the circle
	 * centers.  
	 */
	
	/* Determine the distance from point 0 to point 2. */
	a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;
	
	/* Determine the coordinates of point 2. */
	x2 = x0 + (dx * a/d);
	y2 = y0 + (dy * a/d);
	
	/* Determine the distance from point 2 to either of the
       * intersection points.
       */
	h = sqrt((r0*r0) - (a*a));
	
	/* Now determine the offsets of the intersection points from
	 * point 2.
	 */
	rx = -dy * (h/d);
	ry = dx * (h/d);
	
	/* Determine the absolute intersection points. */
	*xi = x2 + rx;
	*xi_prime = x2 - rx;
	*yi = y2 + ry;
	*yi_prime = y2 - ry;
	
	return 1;
      }
      


      /**
        Given a point X and a circle of center X1, compute the two
        points Xi and Xi' of the circle the tangent of which go through
        X. Since the triangle XXiX1 is a right triangle on Xi, the
        middle point M between X and X1 is equidistant to X, X1 and
        Xi. Thus, Xi belongs to the intersection of the circle (X1,r1)
        and the circle of center M and radius ||XX1||/2.   
        
        @param[in] x  the first coordinate of X.
        @param[in] y  the second coordinate of X.
        @param[in] x1 the first coordinate of the circle center X1.
        @param[in] y1 the second coordinate of the circle center X1.
        @param[in] r1 the circle radius.
        @param[out] xi  pointer to the first coordinate of the first intersection point.
        @param[out] yi  pointer to the second coordinate of the first intersection point.
        @param[out] xi_prime  pointer to the first coordinate of the second intersection point.
        @param[out] yi_prime  pointer to the second coordinate of the second intersection point.
        @return result of the call to circle_circle_intersection
      */ 
      static int circleTangentPoints(double x, double y, double x1, double y1, double r1, double *xi, double *yi, 
			      double *xi_prime, double *yi_prime)
      {
	double x0 = (x+x1)/2;
	double y0 = (y+y1)/2;
	double r0 = sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1))/2;
	
	int res =
	  circle_circle_intersection(x0,y0,r0,x1,y1,r1,xi,yi,xi_prime,yi_prime);
	
	return res;
	
      }
    

      /**
	 Compute the angle of the line passing through two points. Angle in
      [0,2pi]
      @param x0 x0
      @param y0 y0
      @param x1 x1
      @param y1 y1
      @return an angle
      */
      static double computeAngle(double x0, double y0, double x1, double y1)
      {
	double x = x1-x0;
	double y = y1-y0;
	
	if(x!=0)
	  {
	    double alpha = y/x;
	  
	    if(x>0 && y>=0)
	      return atan(alpha);
	    else
	      if(x>0 && y<0)
		return atan(alpha)+2*M_PI;
	      else
		if(x<0)
		  return atan(alpha)+M_PI;
	  }
	else
	  {
	    if(y>0)
	      return M_PI_2;
	    else
	      return 3*M_PI_2;
	  }
	return -1;
      }      
      
      
      
      /**
	 Angle between two vectors
	 @param u and @param v two vectors
	 @return an angle
      */
      static double angleVectVect(Vector u, Vector v)
      {
	IntegerComputer<Integer> ic;
 	return acos((double)ic.dotProduct(u,v)/(u.norm()*v.norm()));
      }
	
      /**
	 Computes the chain code between two 8-connected pixels
	 @param p and @param q two points
	 @return an int
      */
      static  int computeChainCode(Point p, Point q)
      {
	int d;
	Coordinate x2 = q[0];
	Coordinate y2 = q[1];
	Coordinate x1 = p[0];
	Coordinate y1 = p[1];
	
	if(x2-x1==0)
	  if(y2-y1==1)
	    d=2;
	  else
	    d=6;
	else
	  if(x2-x1==1)
	    if(y2-y1==0)
	      d=0;
	    else
	      if(y2-y1==1)
		d=1;
	      else
		d=7;
	  else
	    if(y2-y1==0)
	      d=4;
	    else
	      if(y2-y1==1)
		d=3;
	      else
		d=5;
	return d;
      }
    
      /**
	 Computes the octant of the direction pq
	 @param p and @param q two points
	 @return an int
      */
    static int computeOctant(Point p, Point q)
    {
      int d = 0;
      Coordinate x = q[0]-p[0];
      Coordinate y = q[1]-p[1];
      
      if(x>=0)
	{
	  if(y>=0)
	    {
	      if(x>y)
		d=0; // 0 <= y < x  
	      else
		if(x!=0)
		  d=1; // 0 <= x <= y
	    }
	  else
	    {
	      if(x>=abs(y)) 
		d=7; // 0 < abs(y) <= x 
	      else
		d=6; // 0 <= x < abs(y)
	    }
	}
      if(x<=0)
	{
	  if(y>0)
	    if(abs(x)>=y)
	      d=3; // 
	    else
	      d=2;
	  else
	    {
	      if(abs(x)>abs(y))
		d=4;
	      else
		if(x!=0)
		  d=5;
	    }
	}
      return d;
      
    }
    
      /**
	 Rotate the chain code d to put it in the frame where the octant 'quad' is
	 treated as the first octant.
	 @param d a chain code
	 @param quad the octant
	 @return an int (the new chain code)
      */
      
      static int rot(int d, int quad)
      {
	return (d-quad+8)%8;
      }
      
      /**
	 Converts a chain code into a vector
	 @param d an int
	 @return a vector
      */
    static Vector chainCode2Vect(int d)
    {
      Vector v;
      switch(d){
	
      case 0:{
	v[0] = 1;
	v[1] = 0;
	break;
      }
      case 1:{
	v[0] = 1;
	v[1] = 1;
	break;
      }
      case 2:{
	v[0] = 0;
	v[1] = 1;
	break;
      }
      case 3:{
	v[0] = -1;
	v[1] = 1;
	break;
      }
      case 4:{
	v[0] = -1;
	v[1] = 0;
	break;
      }
      case 5:{
	v[0] = -1;
	v[1] = -1;
	break;
      }
      case 6:{
	v[0] = 0;
	v[1] = -1;
	break;
      }
      case 7:{
	v[0] = 1;
	v[1] = -1;
	break;
      } 
	
      }
      
      return v;
    }
    
    
  };
  
    
  /**
   * Default constructor.
   * not valid
   */
  FrechetShortcut();
  
  /**
   * Constructor with initialisation
   * @param error an iterator on 2D points
   */
  FrechetShortcut(double error);

  /**
   * Initialisation.
   * @param it an iterator on 2D points
   */

  void init(const ConstIterator& it);
  
  FrechetShortcut getSelf();

  /**
   * Copy constructor.
   * @param other the object to clone.
   */
  FrechetShortcut ( const Self & other );
  
  /**
   * Assignment.
   * @param other the object to copy.
   * @return a reference on 'this'.
   */
  FrechetShortcut & operator= ( const Self & other );

    /**
     * @return a reverse version of '*this'.
     */
  Reverse getReverse() const;
  
  /**
   * Equality operator.
   * @param other the object to compare with.
   * @return 'true' if the objects are equal, false otherwise
   */
  
  bool operator==( const Self & other ) const;
    
    /**
     * Difference operator.
     * @param other the object to compare with.
     * @return 'false' if equal
     * 'true' otherwise
     */
  bool operator!=( const Self & other ) const;
  

  
  /**
   * Destructor.
   */
  ~FrechetShortcut(){};

    // ----------------------- Interface --------------------------------------
public:

  /**
   * Tests whether the FrechetShortcut can be extended at the front.
   *  
   * @return 'true' if yes, 'false' otherwise.
   */
  bool isExtendableFront();
  
  /**
   * Tests whether the FrechetShortcut can be extended at the front.
   * Extend the FrechetShortcut if yes.
   * @return 'true' if yes, 'false' otherwise.
   */
  bool extendFront();
    
  
  // ---------------------------- Accessors ----------------------------------
  
  
  /**
   *  
   * @return begin iterator of the FrechetShortcut range.
     */
  ConstIterator begin() const;
  /**
   * @return end iterator of the FrechetShortcut range.
   */
  ConstIterator end() const;
  

  

  public:  
  
  /**
   * @return the name of the class.
   */
  std::string className() const;
  
  
  /**
   * Checks the validity/consistency of the object.
   * @return 'true' if the object is valid, 'false' otherwise.
   */
  bool isValid() const;
  
  // ------------------------- Protected Datas ------------------------------
 protected:
  
  /**
     Error parameter used to compute the shortcut
  */
    double myError;
    
  /**
     Vector of 8 backpaths, one per octant. Stores all the information
     needed to update the length of the longest backpath. 
  */
    std::vector <Backpath> myBackpath;
  
  /** 
      Cone used to update the width 
  */
    Cone myCone;
  
  /**
   * ConstIterator pointing to the back of the shortcut
   */
  ConstIterator myBegin;
  /**
   * ConstIterator pointing to the front of the shortcut
   */
  ConstIterator myEnd;
  

  
  // ------------------------- Private Datas --------------------------------
 private:

    
  
  // ------------------------- Hidden services ------------------------------
 
 public:

  /**
     Updates the backpaths (one per octant) according to the new point
     @return 'true' if the length of the longest backpath is lower than
     the threshold, false otherwise
  */

  bool updateBackpath(); 

  /** 
      Test if there exist a backpath of length greater than the threshold
      after the addition of the point pointed by *myEnd+1, but does not
      modify myBackpath.
  */
  bool testUpdateBackpath();
  
  /** 
      Test if there exist a backpath of length greater than the
      threshold
  */
  bool isBackpathOk();
  
  /** 
      Reset the backpaths before the computation of a new shortcut
  */
  void resetBackpath();
  
  /**
     Reset the cone before the computation of a new shortcut
  */
  void resetCone();
  
  /**
     Test if the new direction belongs to the new cone, but does not
     modify myCone
  */
  bool testUpdateWidth();
  
  /**
     Computes the cone defined by the point *myBegin and the new point
     *myEnd + 1 and intersect it with myCone (unchanged)
     @return the new cone
   */
  Cone computeNewCone();
  
  /** 
      Updates the width according to the new point
      @return  true if the width is lower than the error, false otherwise
  */
  bool updateWidth();
  
    

    
  /**
   * Writes/Displays the object on an output stream.
   * @param out the output stream where the object is written.
   */
  void selfDisplay ( std::ostream & out ) const ; 
  
  
  
  // ------------------------- Internals ------------------------------------
 private:
  
  }; // end of class FrechetShortcut
  

  // Utils
  
  
  /**
   * Overloads 'operator<<' for displaying objects of class 'FrechetShortcut'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'FrechetShortcut' to write.
   * @return the output stream after the writing.
   */
  template <typename TIterator,typename TInteger>
  std::ostream&
    operator<< ( std::ostream & out, const FrechetShortcut<TIterator,TInteger> & object );


  
  
  
  
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/FrechetShortcut.ih"
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined FrechetShortcut_h

#undef FrechetShortcut_RECURSES
#endif // else defined(FrechetShortcut_RECURSES)
