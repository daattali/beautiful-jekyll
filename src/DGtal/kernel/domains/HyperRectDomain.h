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
 * @file HyperRectDomain.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * @author Guillaume Damiand
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/05/25
 *
 * Header file for module HyperRectDomain.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(HyperRectDomain_RECURSES)
#error Recursive header files inclusion detected in HyperRectDomain.h
#else // defined(HyperRectDomain_RECURSES)
/** Prevents recursive inclusion of headers. */
#define HyperRectDomain_RECURSES

#if !defined HyperRectDomain_h
/** Prevents repeated inclusion of headers. */
#define HyperRectDomain_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/kernel/CSpace.h"
#include "DGtal/kernel/BasicPointPredicates.h"
#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/kernel/domains/HyperRectDomain_Iterator.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/base/CConstBidirectionalRange.h"

namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // class HyperRectDomain
  /**
   * Description of class 'HyperRectDomain' <p> \brief Aim:
   * Parallelepidec region of a digital space, model of a 'CDomain'.
   *
   * The following code snippet demonstrates how to use \p HyperRectDomain
   *
   *  \code
   *  #include <DGtal/kernel/Space.h>
   *  #include <DGtal/kernel/domains/HyperRectDomain.h>
   * ...
   *
   * //We create a digital Space based on 'int' integers and in dimension 4
   * typedef DGtal::Space<4> Space4D;
   * typedef Space4D::TPoint Point4D;
   *
   * const int rawA[ ] = { 1, 2, 3 ,4};
   * const int rawB[ ] = { 5, 5, 3 ,4};
   * Point4D A ( rawA );
   * Point4D B ( rawB );
   *
   * //Domain construction from two points
   * DGtal::HyperRectDomain<Space4D> myDomain ( A, B );
   *
   * //We iterate on the Domain points and print out the point coordinates.
   * std::copy ( myDomain.begin(),
   *             myDomain.end(),
   *             std::ostream_iterator<Point4D> ( std::cout, " " ) );
   *  \endcode
   *
   *
   * \see testHyperRectDomain.cpp
   * \see testHyperRectDomain-snippet.cpp
   */
  template<typename TSpace>
  class HyperRectDomain
  {
    BOOST_CONCEPT_ASSERT(( concepts::CSpace<TSpace> ));

    // ----------------------- Standard services ------------------------------
  public:

    typedef HyperRectDomain<TSpace> Self;
    
    // typedef TSpace DigitalSpace;
    // typedef TSpace Space;
    typedef TSpace Space;

    typedef HyperRectDomain<Space> Domain;
    typedef typename Space::Point Point;
    typedef typename Space::Integer Integer;
    typedef typename Space::Vector Vector;
    typedef typename Space::Dimension Dimension;
    typedef typename Space::Size Size;
    typedef typename Point::Coordinate Coordinate; // TODO REVOIR LES NOMS.... RECUPERER DANS SPACE

    BOOST_STATIC_CONSTANT(Dimension, dimension = Space::dimension); 

    ///Typedef of domain iterators
    typedef HyperRectDomain_Iterator<Point> Iterator;
    typedef myreverse_iterator<Iterator> ReverseIterator;
    typedef Iterator ConstIterator;
    typedef ReverseIterator ConstReverseIterator;
    
    typedef functors::IsWithinPointPredicate<Point> Predicate;

    /**
     * Default Constructor.
     */
    HyperRectDomain();

    /**
     * Constructor from  two points \param aPointA and \param aPointB
     * defining the space diagonal.
     *
     */
    HyperRectDomain ( const Point &aPointA, const Point &aPointB );


    /**
     * Destructor.
     */
    ~HyperRectDomain();

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    HyperRectDomain ( const HyperRectDomain & other );


    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    HyperRectDomain & operator= ( const HyperRectDomain & other );

    /**
     * begin method.
     * @return ConstIterator on the beginning of the range.
     */
    const ConstIterator& begin() const
      { 
        return myIteratorBegin;
      }
    
    /**
     * begin method from a given point.
     * @param aPoint the initial point.
     * @return a ConstIterator initialized to aPoint.
     * @pre aPoint must belong to the range.
     */
    ConstIterator begin(const Point& aPoint) const
      { 
        ASSERT_MSG(
            isInside(aPoint) || aPoint == myLowerBound || aPoint == myUpperBound,
            "The point must be inside the domain or be equal to one of his bound."
        );

        return ConstIterator(aPoint, myLowerBound, myUpperBound);
      }
    
    /**
     * end method.
     * @return ConstIterator on the end of the range.
     */
    const ConstIterator& end() const
      { 
        return myIteratorEnd;
      }
    
    /**
     * reverse begin method.
     * @return ConstIterator on the beginning of the reverse range.
     */
    ConstReverseIterator rbegin() const
      { 
        return ConstReverseIterator(end());
      }
    
    /**
     * reverse begin method from a given point.
     * @param aPoint the initial point.
     * @return a ConstIterator initialized to aPoint.
     * @pre aPoint must belong to the range.
     */
    ConstReverseIterator rbegin(const Point& aPoint) const
      {  
        ASSERT_MSG(
            isInside(aPoint) || aPoint == myLowerBound || aPoint == myUpperBound,
            "The point must be inside the domain or be equal to one of his bound."
        );

        ConstIterator it(begin(aPoint)); ++it;
        return ConstReverseIterator(it);
      }
    
    /**
     * reverse end method.
     * @return ConstIterator on the end of the reverse range.
     */
    ConstReverseIterator rend() const
      { 
        return ConstReverseIterator(begin());
      }
    
    /**
     * Description of class 'ConstSubRange' <p> \brief Aim:
     * range through some subdomain of all the points in the domain.
     * Defines a constructor taking a domain in parameter plus some
     * additional parameters to specify the subdomain,
     * begin and end methods returning ConstIterator, and
     * rbegin and rend methods returning ConstReverseIterator.
     */
    struct ConstSubRange 
    {
      typedef HyperRectDomain_subIterator<Point> ConstIterator;
      typedef myreverse_iterator<ConstIterator> ConstReverseIterator;

      /**
       * ConstSubRange constructor from a given domain.
       * @param domain the domain.
       * @param permutation a vector containing the dimensions used for
       *        the subrange. Dimensions are iterated in the given order.
       * @param startingPoint the initial point.
       * @pre startingPoint must belong to the range.     
       */
      ConstSubRange(const HyperRectDomain<TSpace>& domain,
          const std::vector<Dimension> & permutation,
          const Point & startingPoint)
        : myLowerBound(domain.myLowerBound),
          myUpperBound(domain.myUpperBound),
          myStartingPoint(startingPoint)
        {
          ASSERT_MSG(
              domain.isInside(startingPoint) || startingPoint == myLowerBound || startingPoint == myUpperBound,
              "The point must be inside the given domain or be equal to one of his bound."
          );

          myPermutation.reserve( permutation.size() );
          std::copy(permutation.begin(), permutation.end(), std::back_inserter(myPermutation));
          myLowerBound.partialCopyInv(myStartingPoint, myPermutation);
          myUpperBound.partialCopyInv(myStartingPoint, myPermutation);
        }

      /**
       * ConstSubRange constructor from a given domain.
       * @param domain the domain.
       * @param permutation an initializer_list containing the dimensions used for
       *        the subrange. Dimensions are iterated in the given order.
       * @param startingPoint the initial point.
       * @pre startingPoint must belong to the range.     
       */
      ConstSubRange(const HyperRectDomain<TSpace>& domain,
          std::initializer_list<Dimension> permutation,
          const Point & startingPoint)
        : myLowerBound(domain.myLowerBound),
          myUpperBound(domain.myUpperBound),
          myStartingPoint(startingPoint)
        {
          ASSERT_MSG(
              domain.isInside(startingPoint) || startingPoint == myLowerBound || startingPoint == myUpperBound, 
              "The point must be inside the given domain or be equal to one of his bound."
          );

          myPermutation.reserve( permutation.size() );
          for ( const unsigned int *c = permutation.begin(); c != permutation.end(); ++c )
            {
              myPermutation.push_back( *c );
            }
          myLowerBound.partialCopyInv(myStartingPoint, myPermutation);
          myUpperBound.partialCopyInv(myStartingPoint, myPermutation);
        }

      /**
       * ConstSubRange constructor from a given domain for one dimension.
       * @param domain the domain.
       * @param adim the dimension used for the subrange. 
       * @param startingPoint the initial point.
       * @pre startingPoint must belong to the range.     
       */
      ConstSubRange(const HyperRectDomain<TSpace>& domain,
          Dimension adim,
          const Point & startingPoint)
        : myLowerBound(domain.myLowerBound),
          myUpperBound(domain.myUpperBound),
          myStartingPoint(startingPoint)
        {
          ASSERT_MSG(
              domain.isInside(startingPoint) || startingPoint == myLowerBound || startingPoint == myUpperBound,
              "The point must be inside the given domain or be equal to one of his bound."
          );

          myPermutation.push_back( adim );
          myLowerBound.partialCopyInv(myStartingPoint, myPermutation);
          myUpperBound.partialCopyInv(myStartingPoint, myPermutation);
        }
      
      /**
       * ConstSubRange constructor from a given domain for two dimensions.
       * @param domain the domain.
       * @param adim1 the first dimension used for the subrange.
       * @param adim2 the second dimension used for the subrange. 
       * @param startingPoint the initial point.
       * @pre startingPoint must belong to the range.     
       */
      ConstSubRange(const HyperRectDomain<TSpace>& domain,
          Dimension adim1, Dimension adim2,
          const Point & startingPoint)
        : myLowerBound(domain.myLowerBound),
          myUpperBound(domain.myUpperBound),
          myStartingPoint(startingPoint)
        {
          ASSERT_MSG(
              domain.isInside(startingPoint) || startingPoint == myLowerBound || startingPoint == myUpperBound,
              "The point must be inside the given domain or be equal to one of his bound."
          );

          myPermutation.push_back( adim1 );
          myPermutation.push_back( adim2 );
          myLowerBound.partialCopyInv(myStartingPoint, myPermutation);
          myUpperBound.partialCopyInv(myStartingPoint, myPermutation);
        }
      
      /**
       * ConstSubRange constructor from a given domain for two dimensions.
       * @param domain the domain.
       * @param adim1 the first dimension used for the subrange.
       * @param adim2 the second dimension used for the subrange.
       * @param adim3 the third dimension used for the subrange. 
       * @param startingPoint the initial point.
       * @pre startingPoint must belong to the range.     
       */
      ConstSubRange(const HyperRectDomain<TSpace>& domain,
          Dimension adim1, Dimension adim2, Dimension adim3,
          const Point & startingPoint)
        : myLowerBound(domain.myLowerBound),
          myUpperBound(domain.myUpperBound),
          myStartingPoint(startingPoint)
        {
          ASSERT_MSG(
              domain.isInside(startingPoint) || startingPoint == myLowerBound || startingPoint == myUpperBound,
              "The point must be inside the given domain or be equal to one of his bound."
          );
          
          myPermutation.push_back( adim1 );
          myPermutation.push_back( adim2 );
          myPermutation.push_back( adim3 );
          myLowerBound.partialCopyInv(myStartingPoint, myPermutation);
          myUpperBound.partialCopyInv(myStartingPoint, myPermutation);
        }
      
      /**
       * begin method.
       * @return ConstIterator on the beginning of the range.
       */
      ConstIterator begin() const
        {
          return ConstIterator(myLowerBound, myLowerBound, myUpperBound, myPermutation);
        }
      
      /**
       * begin method from a given point.
       * @param aPoint the initial point.
       * @return a ConstIterator initialized to aPoint.
       * @pre aPoint must belong to the range.
       */
      ConstIterator begin(const Point& aPoint) const
        { 
          ASSERT(aPoint.partialEqualInv(myLowerBound, myPermutation) );
          ASSERT_MSG( 
            ( myLowerBound.isLower(aPoint) && aPoint.isLower(myUpperBound) ) || aPoint == myLowerBound || aPoint == myUpperBound,
            "The point must be inside the given domain or be equal to one of his bound."
          );

          return ConstIterator(aPoint, myLowerBound, myUpperBound, myPermutation);
        }

      /**
       * end method.
       * @return ConstIterator on the end of the range.
       */
      ConstIterator end() const
        {
          ConstIterator it = ConstIterator(myUpperBound, myLowerBound, myUpperBound, myPermutation);
          ++it;
          return it;
        }

      /**
       * reverse begin method.
       * @return ConstIterator on the beginning of the reverse range.
       */
      ConstReverseIterator rbegin() const
        {
          return ConstReverseIterator(end());
        }

      /**
       * reverse begin method from a given point.
       * @param aPoint the initial point.
       * @return a ConstIterator initialized to aPoint.
       * @pre aPoint must belong to the range.
       */
      ConstReverseIterator rbegin(const Point& aPoint) const
        { 
          ConstIterator it(begin(aPoint));
          ++it;
          return ConstReverseIterator(it);
        }

      /**
       * reverse end method.
       * @return ConstIterator on the end of the reverse range.
       */
      ConstReverseIterator rend() const
        { 
          return ConstReverseIterator(begin());
        }

    private:
      /// Lower bound of the subrange.
      Point                  myLowerBound;
      /// Upper bound of the subrange.
      Point                  myUpperBound;
      /// Starting point of the subrange.
      Point                  myStartingPoint;
      /// Permutation on dimensions used in the subrange.
      std::vector<Dimension> myPermutation;
    }; // ConstSubRange

    /**
     * get a subRange.
     * @param permutation a vector containing the dimensions used for
     *        the subrange. Dimensions are iterated in the given order.
     * @return a sub-range of the domain for the given permutation.
     */
    ConstSubRange subRange(const std::vector<Dimension> & permutation) const
      { 
        return ConstSubRange(*this, permutation, myLowerBound);
      }

    /**
     * get a subRange from an initial point.
     * @param permutation a vector containing the dimensions used for
     *        the subrange. Dimensions are iterated in the given order.
     * @param startingPoint the initial point.
     * @return a sub-range of the domain for the given permutation.
     * @pre startingPoint must belong to the range.     
     */
    ConstSubRange subRange(const std::vector<Dimension> & permutation,
        const Point & startingPoint) const
      {
        return ConstSubRange(*this, permutation, startingPoint);
      }
    
    /**
     * get a subRange of one dimension.
     * @param adim the dimension of the subrange.
     * @param startingPoint the initial point.
     * @return a sub-range of the domain for the given dimension.
     * @pre startingPoint must belong to the range.     
     */
    ConstSubRange subRange(Dimension adim,
        const Point & startingPoint) const
      { 
        return ConstSubRange(*this, adim, startingPoint);
      }
    
    /**
     * get a subRange of two dimensions.
     * @param adim1 the first dimension of the subrange.
     * @param adim2 the second dimension of the subrange.
     * @param startingPoint the initial point.
     * @return a sub-range of the domain for the given two dimensions.
     * @pre startingPoint must belong to the range.     
     */
    ConstSubRange subRange(Dimension adim1, Dimension adim2,
        const Point & startingPoint) const
      { 
        return ConstSubRange(*this, adim1, adim2, startingPoint);
      }
    
    /**
     * get a subRange of three dimensions.
     * @param adim1 the first dimension of the subrange.
     * @param adim2 the second dimension of the subrange.
     * @param adim3 the third dimension of the subrange.
     * @param startingPoint the initial point.
     * @return a sub-range of the domain for the given three dimensions.
     * @pre startingPoint must belong to the range.     
     */
    ConstSubRange subRange(Dimension adim1, Dimension adim2, Dimension adim3,
        const Point & startingPoint) const
      { 
        return ConstSubRange(*this, adim1, adim2, adim3, startingPoint);
      }
    
    /**
     * get a subRange.
     * @param permutation an initializer_list containing the dimensions used for
     *        the subrange. Dimensions are iterated in the given order.
     * @return a sub-range of the domain for the given permutation.
     */
    ConstSubRange subRange(std::initializer_list<Dimension> permutation)
      { 
        return ConstSubRange(*this, permutation, myLowerBound);
      }

    /**
     * get a subRange from an initial point.
     * @param permutation an initializer_list containing the dimensions used for
     *        the subrange. Dimensions are iterated in the given order.
     * @param startingPoint the initial point.
     * @return a sub-range of the domain for the given permutation.
     * @pre startingPoint must belong to the range.     
     */
    ConstSubRange subRange(std::initializer_list<Dimension> permutation,
        const Point & startingPoint)
      { 
        return ConstSubRange(*this, permutation, startingPoint);
      }
    
    // ----------------------- Interface --------------------------------------
  public:

    /**
     * @return  the size (number of points) of the HyperRectDomain
     *
     **/
    Size size() const
      {
        Size res = 1;
        Point p = Point::diagonal(1);
        Vector e =  (myUpperBound - myLowerBound) + p;
        typename Vector::ConstIterator it, itEnd; 
        for ( it = e.begin(), itEnd = e.end(); it != itEnd; ++it)
          {
            res *= *it; 
          }
        return res; 
      }

    /**
     * Returns the lowest point of the space diagonal.
     *
     **/
    const Point &lowerBound() const;

    /**
     * Returns the highest point of the space diagonal.
     *
     **/
    const Point &upperBound() const ;

    /**
     * @param p any point.
     * @return 'true' if point [p] is inside this domain.
     */
    bool isInside( const Point & p ) const;

    /**
     * @return true if the domain is empty.
     */
    bool isEmpty() const;

    /**
     * @return a const reference to the "IsInside" predicate.
     *
     * NB: Could have used template class DomainPredicate but, for
     * performance reason, directly used the IsWithinPointPredicate
     * which fits perfectly.
     */
    const Predicate & predicate() const;

    // ------------------------- Private Datas --------------------------------
  private:



    // --------------- CDrawableWithBoard2D realization --------------------
  public:
    
    /**
     * Default drawing style object.
     * @return the dyn. alloc. default style for this object.
     */
    //DrawableWithBoard2D* defaultStyle( std::string mode = "" ) const;
    
    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;

    
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
  //private:
    ///The lowest point of the space diagonal
    Point myLowerBound;
    ///The highest point of the space diagonal
    Point myUpperBound;
        
  private:

    /// "IsInside" predicate.
    Predicate myPredicate;

    /// Begin iterator
    ConstIterator myIteratorBegin;
    /// End iterator
    ConstIterator myIteratorEnd;
  }; // end of class HyperRectDomain

  
  /**
   * Overloads 'operator<<' for displaying objects of class 'HyperRectDomain'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'HyperRectDomain' to write.
   * @return the output stream after the writing.
   */
  template<typename TSpace>
  std::ostream&
  operator<< ( std::ostream& out, const HyperRectDomain<TSpace> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/domains/HyperRectDomain.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined HyperRectDomain_h

#undef HyperRectDomain_RECURSES
#endif // else defined(HyperRectDomain_RECURSES)
