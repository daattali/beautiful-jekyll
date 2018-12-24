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
 * @file FrontierPredicate.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/12/10
 *
 * Header file for module FrontierPredicate.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(FrontierPredicate_RECURSES)
#error Recursive header files inclusion detected in FrontierPredicate.h
#else // defined(FrontierPredicate_RECURSES)
/** Prevents recursive inclusion of headers. */
#define FrontierPredicate_RECURSES

#if !defined FrontierPredicate_h
/** Prevents repeated inclusion of headers. */
#define FrontierPredicate_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/images/CConstImage.h"
#include "DGtal/topology/CCellularGridSpaceND.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::functors
namespace DGtal {
  namespace functors {

  /////////////////////////////////////////////////////////////////////////////
  // class FrontierPredicate
  /**
     Description of class 'FrontierPredicate' <p> \brief Aim: The
     predicate on surfels that represents the frontier between two
     regions in an image. It can be used with ExplicitDigitalSurface
     or LightExplicitDigitalSurface so as to define a digital
     surface. Such surfaces may of course be open.
     
     @tparam TKSpace any model of cellular space
     @tparam TImage any model of Image
  */
  template <typename TKSpace, typename TImage>
  class FrontierPredicate
  {
    // ----------------------- public types ------------------------------
  public:
    BOOST_CONCEPT_ASSERT(( concepts::CCellularGridSpaceND< TKSpace > ));
    BOOST_CONCEPT_ASSERT(( concepts::CConstImage< TImage > ));
    typedef TKSpace KSpace;
    typedef TImage Image;
    typedef typename KSpace::Surfel Surfel;
    typedef typename KSpace::Point Point;
    typedef typename KSpace::SCell SCell;
    typedef typename Image::Value Value;
    // KSpace::Point same type as Image::Point
    BOOST_STATIC_ASSERT
    (( concepts::ConceptUtils::SameType< typename KSpace::Point,
       typename Image::Point>::value ));
                                                 

    // ----------------------- Standard services ------------------------------
  public:
  
    /**
     * Destructor.
     */
    ~FrontierPredicate();
  
    /**
       Constructor. The frontier will be defined only with the image
       domain. The space must be large enough to contain the frontier.
       
       @param aSpace a cellular grid space (referenced).
       @param anImage any image (referenced).
       @param l1 a label in the image that defines the inner region.
       @param l2 a label in the image that defines the outer region.
    */
    FrontierPredicate( ConstAlias<KSpace> aSpace, ConstAlias<Image> anImage,
                       const Value & l1, const Value & l2 );
  
    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    FrontierPredicate ( const FrontierPredicate & other );

    /**
     * Assignment. Required by CSurfelPredicate.
     * @param other the object to clone.
     * @return a reference to this object.
     */
    FrontierPredicate& operator=( const FrontierPredicate & other );

    /**
       Predicate operator. 
       
       @param s any surfel

       @return 'true' iff s has its inner voxel that has label
       myLabel1 in image myImage and its outer voxel that has label
       myLabel2 in image myImage.
    */
    bool operator()( const Surfel & s ) const;
    
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

    // ------------------------- Private Datas --------------------------------
  private:

    /// the cellular space where lies the image.
    const KSpace* myPtrSpace;
    // the image of interest
    const Image* myPtrImage;
    /// the label of the inner region that defines the frontier.
    Value myLabel1;
    /// the label of the outer region that defines the frontier.
    Value myLabel2;

    // ------------------------- Hidden services ------------------------------
  protected:
    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class FrontierPredicate

  } // namespace functors

  /**
   * Overloads 'operator<<' for displaying objects of class 'FrontierPredicate'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'FrontierPredicate' to write.
   * @return the output stream after the writing.
   */
  template <typename TKSpace, typename TImage>
  std::ostream&
  operator<< ( std::ostream & out, 
               const DGtal::functors::FrontierPredicate<TKSpace,TImage> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/helpers/FrontierPredicate.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined FrontierPredicate_h

#undef FrontierPredicate_RECURSES
#endif // else defined(FrontierPredicate_RECURSES)
