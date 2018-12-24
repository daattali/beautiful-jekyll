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
 * @file DigitalShapesDecorator.h
 * @author Jeremy Levallois (\c jeremy.levallois@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), INSA-Lyon, France
 * LAboratoire de MAthématiques - LAMA (CNRS, UMR 5127), Université de Savoie, France
 *
 * @date 2012/08/28
 *
 * This file is part of the DGtal library.
 */

#if defined(DigitalShapesDecorator_RECURSES)
#error Recursive header files inclusion detected in DigitalShapesDecorator.h
#else // defined(DigitalShapesDecorator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DigitalShapesDecorator_RECURSES

#if !defined DigitalShapesDecorator_h
/** Prevents repeated inclusion of headers. */
#define DigitalShapesDecorator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"

#include "DGtal/shapes/CDigitalBoundedShape.h"
#include "DGtal/shapes/CDigitalOrientedShape.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

    /////////////////////////////////////////////////////////////////////////////
  // template class DigitalShapesCSG
  /**
   * Description of template class 'DigitalShapesCSG' <p>
   * \brief Aim: Constructive Solid Geometry (CSG) between models of CDigitalBoundedShape and CDigitalOrientedShape
   * Use CSG operation (union, intersection, minus) from a shape of Type ShapeA with one (or more) shapes of Type ShapeB.
   * Can combine differents operations.
   * Limitations: Since we don't have a class derived by all shapes, operations can be done by only one type of shapes.
   * Use CSG of CSG to go beyond this limitation.
   *
   * @tparam ShapeA type of a first shape. Must be a model of CDigitalBoundedShape and CDigitalOrientedShape
   * @tparam ShapeB type of a second shape. Must be a model of CDigitalBoundedShape and CDigitalOrientedShape
   */
  template <typename ShapeA, typename ShapeB>
  class DigitalShapesCSG
  {
  protected:
    enum e_operator
    {
      e_plus,
      e_intersection,
      e_minus
    };

  public:
    BOOST_CONCEPT_ASSERT (( concepts::CDigitalBoundedShape< ShapeA > ));
    BOOST_CONCEPT_ASSERT (( concepts::CDigitalOrientedShape< ShapeA > ));

    typedef typename ShapeA::Space Space;
    typedef typename ShapeA::Point Point;

    /**
      * Default constructor. DigitalShapesCSG will be not valid without setParams(ShapeA).
      *
      */
    DigitalShapesCSG( )
      : bIsValid(false)
    {}

    /**
      * Copy constructor.
      *
      * @param[in] other a DigitalShapesCSG to copy
      */
    DigitalShapesCSG ( const DigitalShapesCSG & other )
      : myShapeA(other.myShapeA), v_shapes(other.v_shapes),
        myLowerBound(other.myLowerBound), myUpperBound(other.myUpperBound),
        bIsValid(other.bIsValid)
    {}


    /**
      * Constructor. DigitalShapesCSG will be valid.
      *
      * @param[in] a a model of CDigitalBoundedShape and CDigitalOrientedShape
      */
    DigitalShapesCSG( ConstAlias<ShapeA> a )
      : myShapeA( a )
    {
      myLowerBound = myShapeA->getLowerBound();
      myUpperBound = myShapeA->getUpperBound();

      bIsValid = true;
    }

    /**
      * Copy operator.
      *
      * @param[in] other a DigitalShapesCSG to copy
      *
      * @return this
      */
    DigitalShapesCSG & operator= ( const DigitalShapesCSG & other )
    {
      myShapeA = other.myShapeA;
      v_shapes = other.v_shapes;

      myLowerBound = other.myLowerBound;
      myUpperBound = other.myUpperBound;

      bIsValid = other.bIsValid;

      return *this;
    }

    /**
      * Add a (unique) ShapeA for the CSG computation. DigitalShapesCSG will be valid after. If a ShapeA was already set, the previous one will be override.
      *
      * @param[in] a a ShapeA, model of CDigitalBoundedShape and CDigitalOrientedShape
      */
    void setParams( ConstAlias<ShapeA> a )
    {
      myShapeA = a;

      myLowerBound = myShapeA->getLowerBound();
      myUpperBound = myShapeA->getUpperBound();

      bIsValid = true;
    }

    /**
      * Union between a shape (ShapeA, gived at construction) and b (ShapeB). If an operation was already set, the
      * union will be between the CSG shape and b (ShapeB).
      *
      * @param[in] b a ShapeB, model of CDigitalBoundedShape and CDigitalOrientedShape
      */
    void plus( ConstAlias<ShapeB> b )
    {
      BOOST_CONCEPT_ASSERT (( concepts::CDigitalBoundedShape< ShapeB > ));
      BOOST_CONCEPT_ASSERT (( concepts::CDigitalOrientedShape< ShapeB > ));

      FATAL_ERROR_MSG( isValid(), "Operation invalid. Maybe you don't set a ShapeA object." );

      std::pair<e_operator, CountedConstPtrOrConstPtr< ShapeB > > shape( e_plus, b );

      for(Dimension i =0; i < Space::dimension; ++i)
      {
        myLowerBound[i] = std::min(myLowerBound[i], b->getLowerBound()[i]);
        myUpperBound[i] = std::max(myUpperBound[i], b->getUpperBound()[i]);
      }

      v_shapes.push_back(shape); 
    }

    /**
      * Intersection between a (ShapeA) and b (ShapeB). If an operation was already set, the
      * intersection will be between the CSG shape and b (ShapeB).
      *
      * @param[in] b a ShapeB, model of CDigitalBoundedShape and CDigitalOrientedShape
      */
    void intersection( ConstAlias<ShapeB> b )
    {
      BOOST_CONCEPT_ASSERT (( concepts::CDigitalBoundedShape< ShapeB > ));
      BOOST_CONCEPT_ASSERT (( concepts::CDigitalOrientedShape< ShapeB > ));

      FATAL_ERROR_MSG( isValid(), "Operation invalid. Maybe you don't set a ShapeA object." );

      std::pair<e_operator, CountedConstPtrOrConstPtr< ShapeB > > shape( e_intersection, b );

      for(Dimension i=0; i < Space::dimension; ++i)
      {
        myLowerBound[i] = std::max(myLowerBound[i], b->getLowerBound()[i]);
        myUpperBound[i] = std::min(myUpperBound[i], b->getUpperBound()[i]);
      }

      v_shapes.push_back(shape); 
    }

    /**
      * Minus between a (ShapeA) and b (ShapeB). If an operation was already set, the
      * minus will be between the CSG shape and b (ShapeB).
      *
      * @param[in] b a ShapeB, model of CDigitalBoundedShape and CDigitalOrientedShape
      */
    void minus( ConstAlias<ShapeB> b )
    {
      BOOST_CONCEPT_ASSERT (( concepts::CDigitalBoundedShape< ShapeB > ));
      BOOST_CONCEPT_ASSERT (( concepts::CDigitalOrientedShape< ShapeB > ));

      FATAL_ERROR_MSG( isValid(), "Operation invalid. Maybe you don't set a ShapeA object." );

      std::pair<e_operator, CountedConstPtrOrConstPtr< ShapeB > > shape( e_minus, b );

      v_shapes.push_back(shape);

    }

    /**
     * @return the lower bound of the shape bounding box.
     *
     */
    Point getLowerBound() const
    {
      FATAL_ERROR_MSG( isValid(), "Operation invalid. Maybe you don't set a ShapeA object." );

      return myLowerBound;
    }

    /**
     * @return the upper bound of the shape bounding box.
     *
     */
    Point getUpperBound() const
    {
      FATAL_ERROR_MSG( isValid(), "Operation invalid. Maybe you don't set a ShapeA object." );

      return myUpperBound;
    }

    /**
     * Return the orientation of a point with respect to a shape. Resolve all operations done
     * with operators in the order they are set.
     *
     * @param[in] p input point
     *
     * @return the orientation of the point (0 = INSIDE, 1 = ON, 2 = OUTSIDE)
     */
    Orientation orientation( const Point & p ) const
    {
      FATAL_ERROR_MSG( isValid(), "Operation invalid. Maybe you don't set a ShapeA object." );

      Orientation orient = myShapeA->orientation( p );

      for(unsigned int i = 0; i < v_shapes.size(); ++i)
      {
        if( v_shapes[i].first == e_minus )
        {
          if (( v_shapes[i].second->orientation( p ) == INSIDE ) || ( v_shapes[i].second->orientation( p ) == ON ))
          {
            orient = OUTSIDE;
          }
        }
        else if( v_shapes[i].first == e_intersection )
        {
          if (( orient == ON ) && ( v_shapes[i].second->orientation( p ) != OUTSIDE ))
          {
            orient = ON;
          }
          else if (( v_shapes[i].second->orientation( p ) == ON ) && ( orient != OUTSIDE ))
          {
            orient = ON;
          }
          else if (( orient == INSIDE ) && ( v_shapes[i].second->orientation( p ) == INSIDE ))
          {
            orient = INSIDE;
          }
          else
          {
            orient = OUTSIDE;
          }
        }
        else /// e_plus
        {
          if (( orient == INSIDE ) || ( v_shapes[i].second->orientation( p ) == INSIDE ))
          {
            orient = INSIDE;
          }
          else if (( orient == ON ) || ( v_shapes[i].second->orientation( p ) == ON ))
          {
            orient = ON;
          }
          else
          {
            orient = OUTSIDE;
          }
        }
      }

      return orient;
    }

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
    bool isValid() const
    {
      return bIsValid;
    }

    // ------------------------- Internals ------------------------------------
  private:

    /// Base Shape.
    CountedConstPtrOrConstPtr< ShapeA > myShapeA;

    /// Vector of all operations (ordered) of ShapeB.
    std::vector< std::pair<e_operator,  CountedConstPtrOrConstPtr< ShapeB > > > v_shapes;

    /// Domain lower bound.
    Point myLowerBound;

    /// Domain upper bound.
    Point myUpperBound;

    /// if the CSG is valid.
    bool bIsValid;

  };

namespace deprecated
{

/////////////////////////////////////////////////////////////////////////////
// template class DigitalShapesUnion
/**
 * Description of template class 'DigitalShapesUnion' <p>
 * \brief Aim: Union between two models of CDigitalBoundedShape and CDigitalOrientedShape
 *
 * @tparam ShapeA type of the first shape. Must be a model of CDigitalBoundedShape and CDigitalOrientedShape
 * @tparam ShapeB type of the second shape. Must be a model of CDigitalBoundedShape and CDigitalOrientedShape
 */
template <typename ShapeA, typename ShapeB>
class DigitalShapesUnion
{
  // ----------------------- Standard services ------------------------------
public:
  BOOST_CONCEPT_ASSERT (( concepts::CDigitalBoundedShape< ShapeA > ));
  BOOST_CONCEPT_ASSERT (( concepts::CDigitalOrientedShape< ShapeA > ));
  BOOST_CONCEPT_ASSERT (( concepts::CDigitalBoundedShape< ShapeB > ));
  BOOST_CONCEPT_ASSERT (( concepts::CDigitalOrientedShape< ShapeB > ));

  typedef typename ShapeA::Space Space;
  typedef typename ShapeA::Point Point;

  /**
    * Constructor.
    *
    * @param[in] a a model of CDigitalBoundedShape and CDigitalOrientedShape
    * @param[in] b a model of CDigitalBoundedShape and CDigitalOrientedShape
    */
  DigitalShapesUnion( ConstAlias< ShapeA > a, ConstAlias< ShapeB > b )
    : myShapeA( a ),
      myShapeB( b )
  {
    Point shapeALowerBoundary = myShapeA.getLowerBound();
    Point shapeBLowerBoundary = myShapeB.getLowerBound();
    Point shapeAUpperBoundary = myShapeA.getUpperBound();
    Point shapeBUpperBoundary = myShapeB.getUpperBound();
    for ( unsigned int i = 0; i < myLowerBound.size(); ++i )
    {
      myLowerBound[ i ] = std::min( shapeALowerBoundary[ i ], shapeBLowerBoundary[ i ] );
      myUpperBound[ i ] = std::max( shapeAUpperBoundary[ i ], shapeBUpperBoundary[ i ] );
    }
  }


  /**
   * @return the lower bound of the shape bounding box.
   *
   */
  Point getLowerBound() const
  {
    return myLowerBound;
  }

  /**
   * @return the upper bound of the shape bounding box.
   *
   */
  Point getUpperBound() const
  {
    return myUpperBound;
  }

  /**
   * Return the orientation of a point with respect to a shape.
   *
   * @param[in] p input point
   *
   * @return the orientation of the point (0 = INSIDE, 1 = ON, 2 = OUTSIDE)
   */
  Orientation orientation( const Point & p ) const
  {
    if (( myShapeA.orientation( p ) == INSIDE ) || ( myShapeB.orientation( p ) == INSIDE ))
      {
          return INSIDE;
      }
    else if (( myShapeA.orientation( p ) == ON ) || ( myShapeB.orientation( p ) == ON ))
      {
          return ON;
      }
      return OUTSIDE;
  }

  /**
   * Destructor.
   */
  ~DigitalShapesUnion(){}

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

  // ------------------------- Hidden services ------------------------------
protected:

  /**
   * Constructor.
   * Forbidden by default (protected to avoid g++ warnings).
   */
  DigitalShapesUnion();

private:

  /**
   * Copy constructor.
   * @param other the object to clone.
   * Forbidden by default.
   */
  DigitalShapesUnion ( const DigitalShapesUnion & other );

  /**
   * Assignment.
   * @param other the object to copy.
   * @return a reference on 'this'.
   * Forbidden by default.
   */
  DigitalShapesUnion & operator= ( const DigitalShapesUnion & other );

  // ------------------------- Internals ------------------------------------
private:
  const ShapeA & myShapeA;
  const ShapeB & myShapeB;

  Point myLowerBound;
  Point myUpperBound;

}; // end of class DigitalShapesUnion

/////////////////////////////////////////////////////////////////////////////
// template class DigitalShapesIntersection
/**
 * Description of template class 'DigitalShapesIntersection' <p>
 * \brief Aim: Intersection between two models of CDigitalBoundedShape and CDigitalOrientedShape
 *
 * @tparam ShapeA type of the first shape. Must be a model of CDigitalBoundedShape and CDigitalOrientedShape
 * @tparam ShapeB type of the second shape. Must be a model of CDigitalBoundedShape and CDigitalOrientedShape
 */
template <typename ShapeA, typename ShapeB>
class DigitalShapesIntersection
{
  // ----------------------- Standard services ------------------------------
public:
  BOOST_CONCEPT_ASSERT (( concepts::CDigitalBoundedShape< ShapeA > ));
  BOOST_CONCEPT_ASSERT (( concepts::CDigitalOrientedShape< ShapeA > ));
  BOOST_CONCEPT_ASSERT (( concepts::CDigitalBoundedShape< ShapeB > ));
  BOOST_CONCEPT_ASSERT (( concepts::CDigitalOrientedShape< ShapeB > ));

  typedef typename ShapeA::Space Space;
  typedef typename ShapeA::Point Point;

  /**
    * Constructor.
    *
    * @param[in] a a model of CDigitalBoundedShape and CDigitalOrientedShape
    * @param[in] b a model of CDigitalBoundedShape and CDigitalOrientedShape
    */
  DigitalShapesIntersection( ConstAlias< ShapeA > a, ConstAlias< ShapeB > b )
    : myShapeA( a ),
      myShapeB( b )
  {
    Point shapeALowerBoundary = myShapeA.getLowerBound();
    Point shapeBLowerBoundary = myShapeB.getLowerBound();
    Point shapeAUpperBoundary = myShapeA.getUpperBound();
    Point shapeBUpperBoundary = myShapeB.getUpperBound();
    for ( unsigned int i = 0; i < myLowerBound.size(); ++i )
    {
      myLowerBound[ i ] = std::min( shapeALowerBoundary[ i ], shapeBLowerBoundary[ i ] );
      myUpperBound[ i ] = std::max( shapeAUpperBoundary[ i ], shapeBUpperBoundary[ i ] );
    }
  }


  /**
   * @return the lower bound of the shape bounding box.
   *
   */
  Point getLowerBound() const
  {
    return myLowerBound;
  }

  /**
   * @return the upper bound of the shape bounding box.
   *
   */
  Point getUpperBound() const
  {
    return myUpperBound;
  }

  /**
   * Return the orientation of a point with respect to a shape.
   *
   * @param[in] p input point
   *
   * @return the orientation of the point (0 = INSIDE, 1 = ON, 2 = OUTSIDE)
   */
  Orientation orientation( const Point & p ) const
  {
    if (( myShapeA.orientation( p ) == ON ) && ( myShapeB.orientation( p ) != OUTSIDE ))
    {
      return ON;
    }
    else if (( myShapeB.orientation( p ) == ON ) && ( myShapeA.orientation( p ) != OUTSIDE ))
    {
      return ON;
    }
    else if (( myShapeA.orientation( p ) == INSIDE ) && ( myShapeB.orientation( p ) == INSIDE ))
    {
      return INSIDE;
    }

    return OUTSIDE;
  }


  /**
   * Destructor.
   */
  ~DigitalShapesIntersection(){}

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

  // ------------------------- Hidden services ------------------------------
protected:

  /**
   * Constructor.
   * Forbidden by default (protected to avoid g++ warnings).
   */
  DigitalShapesIntersection();

private:

  /**
   * Copy constructor.
   * @param other the object to clone.
   * Forbidden by default.
   */
  DigitalShapesIntersection ( const DigitalShapesIntersection & other );

  /**
   * Assignment.
   * @param other the object to copy.
   * @return a reference on 'this'.
   * Forbidden by default.
   */
  DigitalShapesIntersection & operator= ( const DigitalShapesIntersection & other );

  // ------------------------- Internals ------------------------------------
private:
  const ShapeA & myShapeA;
  const ShapeB & myShapeB;

  Point myLowerBound;
  Point myUpperBound;

}; // end of class DigitalShapesIntersection

/////////////////////////////////////////////////////////////////////////////
// template class DigitalShapesMinus
/**
 * Description of template class 'DigitalShapesMinus' <p>
 * \brief Aim: Minus between two models of CDigitalBoundedShape and CDigitalOrientedShape
 *
 * @tparam ShapeA type of the first shape. Must be a model of CDigitalBoundedShape and CDigitalOrientedShape
 * @tparam ShapeB type of the second shape. Must be a model of CDigitalBoundedShape and CDigitalOrientedShape
 */
template <typename ShapeA, typename ShapeB>
class DigitalShapesMinus
{
  // ----------------------- Standard services ------------------------------
public:
  BOOST_CONCEPT_ASSERT (( concepts::CDigitalBoundedShape< ShapeA > ));
  BOOST_CONCEPT_ASSERT (( concepts::CDigitalOrientedShape< ShapeA > ));
  BOOST_CONCEPT_ASSERT (( concepts::CDigitalBoundedShape< ShapeB > ));
  BOOST_CONCEPT_ASSERT (( concepts::CDigitalOrientedShape< ShapeB > ));

  typedef typename ShapeA::Space Space;
  typedef typename ShapeA::Point Point;

  /**
    * Constructor.
    *
    * @param[in] a a model of CDigitalBoundedShape and CDigitalOrientedShape
    * @param[in] b a model of CDigitalBoundedShape and CDigitalOrientedShape
    */
  DigitalShapesMinus( ConstAlias< ShapeA > a, ConstAlias< ShapeB > b )
    : myShapeA( a ),
      myShapeB( b )
  {
    Point shapeALowerBoundary = myShapeA.getLowerBound();
    Point shapeBLowerBoundary = myShapeB.getLowerBound();
    Point shapeAUpperBoundary = myShapeA.getUpperBound();
    Point shapeBUpperBoundary = myShapeB.getUpperBound();
    for ( unsigned int i = 0; i < myLowerBound.size(); ++i )
    {
      myLowerBound[ i ] = std::min( shapeALowerBoundary[ i ], shapeBLowerBoundary[ i ] );
      myUpperBound[ i ] = std::max( shapeAUpperBoundary[ i ], shapeBUpperBoundary[ i ] );
    }
  }


  /**
   * @return the lower bound of the shape bounding box.
   *
   */
  Point getLowerBound() const
  {
    return myLowerBound;
  }

  /**
   * @return the upper bound of the shape bounding box.
   *
   */
  Point getUpperBound() const
  {
    return myUpperBound;
  }

  /**
   * Return the orientation of a point with respect to a shape.
   *
   * @param[in] p input point
   *
   * @return the orientation of the point (0 = INSIDE, 1 = ON, 2 = OUTSIDE)
   */
  Orientation orientation( const Point & p ) const
  {
    if (( myShapeB.orientation( p ) == INSIDE ) || ( myShapeB.orientation( p ) == ON ))
    {
      return OUTSIDE;
    }
    return myShapeA.orientation( p );
  }


  /**
   * Destructor.
   */
  ~DigitalShapesMinus(){}

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

  // ------------------------- Hidden services ------------------------------
protected:

  /**
   * Constructor.
   * Forbidden by default (protected to avoid g++ warnings).
   */
  DigitalShapesMinus();

private:

  /**
   * Copy constructor.
   * @param other the object to clone.
   * Forbidden by default.
   */
  DigitalShapesMinus ( const DigitalShapesMinus & other );

  /**
   * Assignment.
   * @param other the object to copy.
   * @return a reference on 'this'.
   * Forbidden by default.
   */
  DigitalShapesMinus & operator= ( const DigitalShapesMinus & other );

  // ------------------------- Internals ------------------------------------
private:
  const ShapeA & myShapeA;
  const ShapeB & myShapeB;

  Point myLowerBound;
  Point myUpperBound;

}; // end of class DigitalShapesMinus
}

  /**
   * Overloads 'operator<<' for displaying objects of class 'DigitalShapesDecorator'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'DigitalShapesDecorator' to write.
   * @return the output stream after the writing.
   */
  template <typename ShapeA, typename ShapeB>
  std::ostream&
  operator<< ( std::ostream & out, const deprecated::DigitalShapesUnion< ShapeA, ShapeB > & object );

  template <typename ShapeA, typename ShapeB>
  std::ostream&
  operator<< ( std::ostream & out, const deprecated::DigitalShapesIntersection< ShapeA, ShapeB > & object );

  template <typename ShapeA, typename ShapeB>
  std::ostream&
  operator<< ( std::ostream & out, const deprecated::DigitalShapesMinus< ShapeA, ShapeB > & object );

} // namespace DGtal



#endif // !defined DigitalShapesDecorator_h

#undef DigitalShapesDecorator_RECURSES
#endif // else defined(DigitalShapesDecorator_RECURSES)
