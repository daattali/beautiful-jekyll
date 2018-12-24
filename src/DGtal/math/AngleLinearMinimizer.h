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
 * @file AngleLinearMinimizer.h
 *
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @author (backported from ImaGene by) Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/08/31
 *
 * Header file for module AngleLinearMinimizer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(AngleLinearMinimizer_RECURSES)
#error Recursive header files inclusion detected in AngleLinearMinimizer.h
#else // defined(AngleLinearMinimizer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define AngleLinearMinimizer_RECURSES

#if !defined AngleLinearMinimizer_h
/** Prevents repeated inclusion of headers. */
#define AngleLinearMinimizer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/math/AngleComputer.h" 
#include "DGtal/arithmetic/ModuloComputer.h" 
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class AngleLinearMinimizer
/**
 * Description of class 'AngleLinearMinimizer' <p>
 * \brief Aim: Used to minimize the angle variation between different angles while taking into accounts min and max constraints.
 * Example (@see math/testAngleLinearMinimizer.cpp) 
  \snippet testAngleLinearMinimizer.cpp optimization
  
 *
 */
class AngleLinearMinimizer
{
  
public:
  /**
   * Stores the information linked to the value to optimize.
   */
  struct ValueInfo
  {
    /**
     * The current value. Should be between [min] and [max].
     */
    double value;

    /**
     * The old value. Useful during optimization. 
     */
    double oldValue; 
    
    /**
     * The lower bound for the value.
     */
    double min;

    /**
     * The upper bound for the value.
     */
    double max;

    /**
     * This is the distance between this value and the next one.
     */
    double distToNext;
    
  };
  


    // ----------------------- Standard services ------------------------------
public:
  
  /**
   * Destructor.
   */
  virtual ~AngleLinearMinimizer();
  
  /**
   * Constructor.
   */
  AngleLinearMinimizer();
  
  /**
   * Reset all. The object is as if it has just been created.
   */
  void reset();

  /**
   * (Re-)initializes the linear minimizer.
   *
   * @param nbMax an upper bound for the number of values to optimize.
   */
  void init( unsigned int nbMax );
  

  /**
   * @return a reference on the information structure of the [i]th value.
   */
   ValueInfo & rw( unsigned int i );

  
   /**
   * @return a const reference on the information structure of the [i]th value.
   */
   const ValueInfo & ro( unsigned int i ) const;
  
  /**
   * @return the maximum number of values stored in the object.
   */
   unsigned int maxSize() const;

  /**
   * @return the number of values stored in the object.
   */
   unsigned int size() const;

  /**
   * Specifies the exact number of valid values.
   * @param nb any number below 'maxSize()'.
   */
   void setSize( unsigned int nb );

  /**
   * Specifies if the curve is open or not.
   * @param is_curve_open when 'true' the curve is open and the last
   * value does not depend on the first one, otherwise the curve is
   * closed and the last value is linked to the first one.
   */
   void setIsCurveOpen( bool is_curve_open = false );


 
  
  // ------------------------- Optimization services --------------------------

public:
  
  /**
   * @param i1 the first value to be optimized (between 0 and 'size()-1').
   * @param i2 the value after the last to be optimized (between 0 and 'size()-1') 
   * @return the current energy of the system.
   */
  double getEnergy( unsigned int i1, unsigned int i2 ) const;
  
  /**
   * @param i1 the first value to be optimized (between 0 and 'size()-1').
   * @param i2 the value after the last to be optimized (between 0 and 'size()-1') 
   * @return the former energy of the system.
   */
  double getFormerEnergy( unsigned int i1, unsigned int i2 ) const;  
  
  
  /**
   * @return the energy gradient computed at the current position.
   */
  std::vector<double> getGradient() const;


  /**
   * @return the energy gradient computed at the former position.
   */
  std::vector<double> getFormerGradient() const;
  
  /**
   * Move each value on the straight line joining its neighboring
   * values while maintaining the value between its bounds.  The
   * optimization is performed on all values. After preparing datas,
   * calls oneStep, which may be overriden.
   *
   * @return the sum of the displacements.
   * @see oneStep
   */
  double optimize();
  
  
  /**
   * Move each value on the straight line joining its neighboring
   * values while maintaining the value between its bounds.  The
   * optimization is performed on values [i1] included to [i2]
   * excluded.  After preparing datas, calls oneStep, which may be
   * overriden. Then, computes max and sum of displacements.
   *
   * @param i1 the first value to be optimized (between 0 and 'size()-1').
   * @param i2 the value after the last to be optimized (between 0 and 'size()-1').
   * @return the sum of the displacements.
   * @see oneStep
   */
  double optimize( unsigned int i1, unsigned int i2 );
  
  
  /**
   * Sum of all the absolute displacements of the last optimisation step.
   */
   double sum() const;



  /**
   * Max of all the absolute displacements of the last optimisation step.
   */
   double max() const;

 
protected:

  /**
   * The method which performs the optimization effectively. The user
   * may override it. The optimization is performed on values [i1]
   * included to [i2] excluded. Afterwards, the field ValueInfo::value
   * should contain the new value.
   *
   * @param i1 the first value to be optimized (between 0 and 'size()-1').
   * @param i2 the value after the last to be optimized (between 0 and 'size()-1').
   */
  virtual void oneStep( unsigned int i1, unsigned int i2 );


public:
  /**
   * Should be used to stop the minimization process. The smaller is
   * this value, the more the optimization is at an end. May have
   * several meanings, like the infinite norm of the last displacement
   * or the infinite norm of the projected gradient.
   *
   * @return an upper bound on the norm of the last displacement. 
   */
  virtual double lastDelta() const; 





    // --------------- CDrawableWithBoard2D realization -------------------
  public:

  /**
   * @return the style name used for drawing this object.
   */
  std::string className() const;

  // ----------------------- Interface --------------------------------------
public:

  
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

protected:
  /**
   * Indicates if the curve is open.
   */
  bool myIsCurveOpen;
  
  /**
   * The dynamically allocated array of values and the associated constraints.
   */
  ValueInfo* myValues;
  
  /**
   * The meaningful size of the array [myValues], ie the number of
   * valid entries.
   */
  unsigned int mySize;

private:
  
  /**
   * The size of the array @a myValues, ie the maximal number of valid values.
   */
  unsigned int myMaxSize;


    // ------------------------- Private Datas --------------------------------
private:
  /**
   * Sum of all the absolute displacements of the last optimisation step.
   */
  double mySum;
  
  /**
   * Max of all the absolute displacements of the last optimisation step.
   */
  double myMax;

  // ------------------------- Hidden services ------------------------------

  

private:
 /**
   * Copy constructor.
   * @param other the object to clone.
   * Forbidden by default.
   */
   AngleLinearMinimizer( const AngleLinearMinimizer & other );
  /**
   * Assignment.
   * @param other the object to copy.
   * @return a reference on 'this'.
   * Forbidden by default.
   */
   AngleLinearMinimizer & operator=( const AngleLinearMinimizer & other );
  

  
  // ------------------------- Internals ------------------------------------
private:

}; // end of class AngleLinearMinimizer




  /**
   * Specializes LinearMinimizer to optimize with a relaxation method.
   */
  class AngleLinearMinimizerByRelaxation : public AngleLinearMinimizer
  {
  public:
    /**
     * Default constructor. Does nothing.
     */
     AngleLinearMinimizerByRelaxation();

    /**
     * Destructor. Does nothing.
     */
     virtual ~AngleLinearMinimizerByRelaxation();

  protected:
    
    /**
     * The method which performs the optimization effectively. Use a
     * relaxation technique. The optimization is performed on values
     * [i1] included to [i2] excluded. 
     *
     * @param i1 the first value to be optimized (between 0 and 'size()-1').
     * @param i2 the value after the last to be optimized (between 0 and 'size()-1').
     */
    virtual void oneStep( unsigned int i1, unsigned int i2 );

public:
    /**
     * Should be used to stop the minimization process. The smaller is
     * this value, the more the optimization is at an end. May have
     * several meanings, like the infinite norm of the last displacement
     * or the infinite norm of the projected gradient.
     *
     * @return an upper bound on the norm of the last displacement. 
     */
    virtual double lastDelta() const; 

    // ----------------------- Interface --------------------------------------
  public:
    /**
     * Writes/Displays the object on an output stream.
     * @param aStream the output stream where the object is written.
     */
    virtual void selfDisplay( std::ostream & aStream ) const;

  };
  


  /**
   * Specializes AngleLinearMinimizer to optimize with a gradient descent method.
   */
  class AngleLinearMinimizerByGradientDescent : public AngleLinearMinimizer
  {
  private:

    /**
     * The step for the gradient descent.
     */
    double myStep;

  public:
    /**
     * Default constructor. Does nothing.
     */
     AngleLinearMinimizerByGradientDescent( double step = 0.1 );

    /**
     * Destructor. Does nothing.
     */
     virtual ~AngleLinearMinimizerByGradientDescent();

  protected:
    
    /**
     * The method which performs the optimization effectively. Use a
     * relaxation technique. The optimization is performed on values
     * [i1] included to [i2] excluded. 
     *
     * @param i1 the first value to be optimized (between 0 and 'size()-1').
     * @param i2 the value after the last to be optimized (between 0 and 'size()-1').
     */
    virtual void oneStep( unsigned int i1, unsigned int i2 );

public:
    /**
     * Should be used to stop the minimization process. The smaller is
     * this value, the more the optimization is at an end. May have
     * several meanings, like the infinite norm of the last displacement
     * or the infinite norm of the projected gradient.
     *
     * @return an upper bound on the norm of the last displacement. 
     */
    virtual double lastDelta() const; 

    // ----------------------- Interface --------------------------------------
  public:
    /**
     * Writes/Displays the object on an output stream.
     * @param aStream the output stream where the object is written.
     */
    virtual void selfDisplay( std::ostream & aStream ) const;

  };


  /**
   * Specializes AngleLinearMinimizer to optimize with an adaptive step
   * gradient descent method.
   */
  class AngleLinearMinimizerByAdaptiveStepGradientDescent : public AngleLinearMinimizer
  {
  private:

    /**
     * The current step for the gradient descent.
     */
    double myStep;

  public:
    /**
     * Default constructor. Does nothing.
     */
     AngleLinearMinimizerByAdaptiveStepGradientDescent( double step = 0.1 );

    /**
     * Destructor. Does nothing.
     */
     virtual ~AngleLinearMinimizerByAdaptiveStepGradientDescent();

  protected:
    
    /**
     * The method which performs the optimization effectively. Use a
     * relaxation technique. The optimization is performed on values
     * [i1] included to [i2] excluded. 
     *
     * @param i1 the first value to be optimized (between 0 and 'size()-1').
     * @param i2 the value after the last to be optimized (between 0 and 'size()-1').
     */
    virtual void oneStep( unsigned int i1, unsigned int i2 );

public:
    /**
     * Should be used to stop the minimization process. The smaller is
     * this value, the more the optimization is at an end. May have
     * several meanings, like the infinite norm of the last displacement
     * or the infinite norm of the projected gradient.
     *
     * @return an upper bound on the norm of the last displacement. 
     */
    virtual double lastDelta() const; 

    // ----------------------- Interface --------------------------------------
  public:
    /**
     * Writes/Displays the object on an output stream.
     * @param aStream the output stream where the object is written.
     */
    virtual void selfDisplay( std::ostream & aStream ) const;

  };
  
  


/**
 * Overloads 'operator<<' for displaying objects of class 'AngleLinearMinimizer'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'AngleLinearMinimizer' to write.
 * @return the output stream after the writing.
 */
std::ostream&
operator<< ( std::ostream & out, const AngleLinearMinimizer & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/math/AngleLinearMinimizer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined AngleLinearMinimizer_h

#undef AngleLinearMinimizer_RECURSES
#endif // else defined(AngleLinearMinimizer_RECURSES)
