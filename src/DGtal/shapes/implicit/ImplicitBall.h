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
 * @file ImplicitBall.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/03/22
 *
 * Header file for module ImplicitBall.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImplicitBall_RECURSES)
#error Recursive header files inclusion detected in ImplicitBall.h
#else // defined(ImplicitBall_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImplicitBall_RECURSES

#if !defined ImplicitBall_h
/** Prevents repeated inclusion of headers. */
#define ImplicitBall_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/shapes/implicit/CImplicitFunction.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  /**
   * Description of template class 'ImplicitBall' <p>
   * \brief Aim: model of CEuclideanOrientedShape and CEuclideanBoundedShape concepts to create a ball in
   * nD..
   *
   * Model of CImplicitFunction
   *
   * @tparam TSpace the Digital space definition.
   */
  
  template <typename TSpace>
  class ImplicitBall
  {

  public:
    typedef ImplicitBall<TSpace> Self;
    typedef TSpace Space;
    typedef typename Space::RealPoint RealPoint;
    typedef typename Space::Integer Integer;
    typedef double Value;

    /** 
     * Constructor. Contructs a ball with center aCenter and radius
     * aRadius.
     * 
     * @param aCenter the ball center. 
     * @param aRadius the ball radius.
     */
    ImplicitBall(const RealPoint &aCenter, const double &aRadius): myCenter(aCenter),
                myRadius(aRadius)
    {};
    
    /** 
     * Destructor.
     * 
     */    
    ~ImplicitBall();


    // ----------------------- Interface --------------------------------------
  public:
    
    inline
    Value operator()(const RealPoint &aPoint) const
    {
        return myRadius - (aPoint - myCenter ).norm();
    }
    
    inline
    Orientation orientation(const RealPoint &aPoint) const
    {
      if (this->operator()(aPoint) > 0.0)
        return INSIDE;
      else
        if (this->operator()(aPoint) < 0.0)
          return OUTSIDE;
        else
          return ON;
    }

    inline
    RealPoint getLowerBound() const
    {
      return (myCenter - RealPoint::diagonal(myRadius));
    }
    
    inline
    RealPoint getUpperBound() const
    {
      return (myCenter + RealPoint::diagonal(myRadius)); 
    }
    


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
  private:
    // ------------------------- Private Datas --------------------------------
  private:
   
    ///Ball center
    RealPoint myCenter;

    ///Ball Radius
    double myRadius;
   
    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    ImplicitBall();

  private:

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    ImplicitBall & operator= ( const ImplicitBall & other );
    
    
  }; // end of class ImplicitBall


  /**
   * Overloads 'operator<<' for displaying objects of class 'ImplicitBall'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ImplicitBall' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const ImplicitBall<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/implicit/ImplicitBall.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImplicitBall_h

#undef ImplicitBall_RECURSES
#endif // else defined(ImplicitBall_RECURSES)
