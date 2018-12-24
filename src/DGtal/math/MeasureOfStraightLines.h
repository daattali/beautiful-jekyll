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

/** 
 * @file MeasureOfStraightLines.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/03/04
 * 
 * Header file for module MeasureOfStraightLines.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(MeasureOfStraightLines_RECURSES)
#error Recursive header files inclusion detected in MeasureOfStraightLines.h
#else // defined(MeasureOfStraightLines_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MeasureOfStraightLines_RECURSES

#if !defined MeasureOfStraightLines_h
/** Prevents repeated inclusion of headers. */
#define MeasureOfStraightLines_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal 
{
  
  /////////////////////////////////////////////////////////////////////////////
  // class MeasureOfStraightLines
  /** 
   * Description of class 'MeasureOfStraightLines' <p>
   * Aim: 
   *
   * @brief The aim of this class is to compute the measure in the Lebesgues
   * sense of the set of straight lines associated to domains defined
   * as polygons in the (a,b)-parameter space. This parameter space
   * maps the line $ax-y+b=0$ to the point $(a,b)$.
   *
   *
   * \verbatim
   * @inproceedings{COEURJOLLY:2009:HAL-00432711:1,
   *   title = { {M}easure of {S}traight {L}ines and its {A}pplications in {D}igital {G}eometry},
   *   author = {{C}oeurjolly, {D}avid and {S}ivignon, {I}sabelle},
   *   booktitle = {13th {I}nternational {W}orkshop on {C}ombinatorial {I}mage {A}nalysis 13th {I}nternational {W}orkshop on {C}ombinatorial {I}mage {A}nalysis },
   *   publisher = {{R}esearch {P}ublishing {S}ervices },
   *   pages = {1-12 },
   *   address = {{C}ancun {M}exique },
   *   audience = {internationale },
   *   year = {2009},
   *   URL = {http://hal.archives-ouvertes.fr/hal-00432711/PDF/mesure.pdf},
   * }
   * \endverbatim
   *
   * @see testMeasure.cpp
   *
   * \todo Create a vector<Point> interface
   */
  class MeasureOfStraightLines
  {
    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor. 
     */
    MeasureOfStraightLines();



    /**
     * Destructor. 
     */
    ~MeasureOfStraightLines();

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;


    /**
     * Compute the measure of the polygon {(a_i,b_i)} in the (a,b)-parameter space
     * 
     * REQUIREMENTS: 
     *   - The polygon is given counter-clockwise 
     *   - a_i > 0
     * 
     * @param a the a-value of polygon vertices
     * @param b the b-value of polygon vertices
     * @return the measure value (positive value)
     */
    double computeMeasure(const std::vector<double> &a,const std::vector<double> &b);

    
    /**
     * Compute the abscissa of the centroid of the polygon {(a_i,b_i)}
     * in the (a,b)-parameter space with respect to the measure of lines.
     * 
     * REQUIREMENTS: 
     *   - The polygon is given counter-clockwise 
     *   - a_i > 0
     * 
     * @param a the a-value of polygon vertices
     * @param b the b-value of polygon vertices
     * @return the measure value (positive value)
     */
    double computeCentroidA(const std::vector<double> &a,const std::vector<double> &b);

    
    /**
     * Compute the ordinate of the centroid of the polygon {(a_i,b_i)}
     * in the (a,b)-parameter space with respect to the measure of
     * lines. Note that there is a numerical approximation is
     * performed.
     * 
     * REQUIREMENTS: 
     *   - The polygon is given counter-clockwise 
     *   - a_i > 0
     * 
     * @param a the a-value of polygon vertices
     * @param b the b-value of polygon vertices
     * @return the measure value (positive value)
     */
    double computeCentroidB(const std::vector<double> &a,const std::vector<double> &b);


    /**
     * Set the internal Epsilon threshold for the numerical
     * approximation.
     *
     * @param aValue the new epsilon value
     */
    void setEpsilon(const double aValue);
    

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    double myEpsilon;

    // ------------------------- Hidden services ------------------------------
  protected:

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    MeasureOfStraightLines( const MeasureOfStraightLines & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    MeasureOfStraightLines & operator=( const MeasureOfStraightLines & other );
    
  
    // ------------------------- Internals ------------------------------------
  private:

    /**
     * Compute the measure associated to an edge (a0,b0)-(a1,b1)
     * It returns the measure of the triangle defined by the origin and the edge.
     *
     * @param a0 abscissa first point.
     * @param b0 ordinate of the first point.
     * @param a1 abscissa of the second point.
     * @param b1 ordinate of the second point.
     * @return the measure
     */
    double computeMeasureEdge ( double a0,double b0, double a1, double b1 );

    /**
     * Compute the abscissa of the centroid associated to an edge (a0,b0)-(a1,b1)
     * It returns the measure of the triangle defined by the origin and the edge.
     *
     * @param a0 abscissa first point.
     * @param b0 ordinate of the first point.
     * @param a1 abscissa of the second point.
     * @param b1 ordinate of the second point.
     * @return the measure
     */
    double computeCentroidEdge_a ( double a0,double b0, double a1, double b1 );

    /**
     * Compute the ordinate of the centroid associated to an edge (a0,b0)-(a1,b1)
     * It returns the measure of the triangle defined by the origin and the edge.
     *
     * @param a0 abscissa first point.
     * @param b0 ordinate of the first point.
     * @param a1 abscissa of the second point.
     * @param b1 ordinate of the second point.
     * @return the measure
     */  
    double computeCentroidEdge_b ( double a0,double b0, double a1, double b1 );
    
    /**
     * Approximate  the centroid on 'b' on the triangle (0,0)-(a0,b0)-(a1,b1) 
     * (internal function)
     *
     *
     * @param a0 abscissa first point.
     * @param b0 ordinate of the first point.
     * @param a1 abscissa of the second point.
     * @param b1 ordinate of the second point.
     **/
    double __computeCentroidTriApprox_b ( double a0, double b0,double a1,double b1 );
    
    /**
    * Approximate  the centroid on 'b' on the trapezioid  (a0,0)-(a0,b0)-(a1,b1)-(a1,0)
    * (internal function)
    *
    * @param a0 abscissa first point.
    * @param b0 ordinate of the first point.
    * @param a1 abscissa of the second point.
    * @param b1 ordinate of the second point.
    **/
    double  __computeCentroidEdgeApprox_b ( double a0, double b0,double a1,double b1 );


    /**
    * Compute the centroid on 'b' on the rectangular domain with vertices (x1,,y1) - (x2,y2)
    * @pre  y1<y2
    *
    * @param x1 abscissa first point.
    * @param y1 ordinate of the first point.
    * @param x2 abscissa of the second point.
    * @param y2 ordinate of the second point.
    **/
    double __computeCentroidSquare_b ( double x1, double y1, double x2,double y2 );


    /**
     * @param a a value
     * @return the sign of a number (1 or -1)
     **/
    int sign ( const double a );
     


  }; // end of class MeasureOfStraightLines


  /**
   * Overloads 'operator<<' for displaying objects of class 'MeasureOfStraightLines'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'MeasureOfStraightLines' to write.
   * @return the output stream after the writing.
   */
  std::ostream&
  operator<<( std::ostream & out, const MeasureOfStraightLines & object );

  
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods if necessary.
#include "DGtal/math/MeasureOfStraightLines.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined MeasureOfStraightLines_h

#undef MeasureOfStraightLines_RECURSES
#endif // else defined(MeasureOfStraightLines_RECURSES)
