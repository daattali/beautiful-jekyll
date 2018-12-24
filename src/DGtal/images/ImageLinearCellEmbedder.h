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
 * @file ImageLinearCellEmbedder.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2012/02/14
 *
 * Header file for module ImageLinearCellEmbedder.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImageLinearCellEmbedder_RECURSES)
#error Recursive header files inclusion detected in ImageLinearCellEmbedder.h
#else // defined(ImageLinearCellEmbedder_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImageLinearCellEmbedder_RECURSES

#if !defined ImageLinearCellEmbedder_h
/** Prevents repeated inclusion of headers. */
#define ImageLinearCellEmbedder_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/images/CImage.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  /**
    Description of template class 'ImageLinearCellEmbedder' <p> \brief
    Aim: a cellular embedder for images.  (default constructible, copy
    constructible, assignable). Model of CCellEmbedder.
   
    @tparam TKSpace the cellular grid space definition.
    @tparam TImage the type of implicit function, a model of CImage.
    @tparam TEmbedder the type of digital embedder.

    @todo assert dimensions of space, embedder and implicit function.
   */
  
  template < typename TKSpace,
             typename TImage,
             typename TEmbedder >
  class ImageLinearCellEmbedder
  {
    BOOST_CONCEPT_ASSERT(( concepts::CImage< TImage > ));

  public:
    typedef TKSpace KSpace;
    typedef TImage Image;
    typedef TEmbedder Embedder;
    typedef typename KSpace::Cell Cell;
    typedef typename KSpace::SCell SCell;
    typedef typename KSpace::Space Space;
    typedef typename Space::Point Point;
    typedef typename Space::RealPoint RealPoint;
    typedef typename Space::RealVector RealVector;
    typedef typename Space::Integer Integer;
    typedef typename Image::Value ImageValue;
    typedef Cell Argument;
    typedef RealPoint Value;
    
    /** 
        Constructor. The object is not valid.
     */
    ImageLinearCellEmbedder();
    
    /** 
     * Destructor.
     */    
    ~ImageLinearCellEmbedder();

    /**
       Copy constructor.
       @param other the object to copy.
     */
    ImageLinearCellEmbedder( const ImageLinearCellEmbedder & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    ImageLinearCellEmbedder & 
    operator= ( const ImageLinearCellEmbedder & other );

    /**
       Initializes the embedder with the space \a K, the implicit
       function \a f, the digital embedder \a e.
       
       @param K any cellular grid space.
       @param f an image
       @param e a digital embedder (like a GaussDigitizer).
       @param iso_value the threshold value that defines the linear embedding.
    */
    void init( ConstAlias<KSpace> K, ConstAlias<Image> f, 
               ConstAlias<Embedder> e, double iso_value );

    // ----------------------- Interface --------------------------------------
  public:

    /**
       Maps a digital point to its corresponding point in the Euclidean
       space.
       
       @param p any digital point in the digital space.
       @return its embedding by the current embedder in the Euclidean space.
     */
    RealPoint embed( const Point & p ) const;

    /**
       Maps a cell to its corresponding point in the Euclidean
       space, by a linear guess of its position.
       
       @param cell any cell in the cellular grid space.
       @return its embedding in the Euclidean space.
     */
    RealPoint embedCell( const Cell & cell ) const;

    /**
       Maps a signed cell to its corresponding point in the Euclidean
       space, by a linear guess of its position. NB: the signed is not
       used.
       
       @param scell any cell in the cellular grid space.
       @return its embedding in the Euclidean space.
     */
    RealPoint embedSCell( const SCell & scell ) const;

    /**
       Maps a cell to its corresponding point in the Euclidean
       space, by a linear guess of its position.
       
       @param cell any cell in the cellular grid space.
       @return its embedding in the Euclidean space.
     */
    RealPoint operator()( const Cell & cell ) const;

    
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
   
    /// A pointer on the cellular grid space.
    const KSpace* myPtrK;
    /// A pointer on the image.
    const Image* myPtrImage;
    /// A pointer on the digital embedder.
    const Embedder* myPtrEmbedder;
    /// The threshold value for the linear embedding.
    double myIsoValue;
    
    // ------------------------- Hidden services ------------------------------
  protected:

  private:    
    
  }; // end of class ImageLinearCellEmbedder


  /**
   * Overloads 'operator<<' for displaying objects of class 'ImageLinearCellEmbedder'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ImageLinearCellEmbedder' to write.
   * @return the output stream after the writing.
   */
  template < typename TKSpace, typename TImage, typename TEmbedder >
  std::ostream&
  operator<< ( std::ostream & out, 
               const ImageLinearCellEmbedder<TKSpace, TImage, TEmbedder> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/images/ImageLinearCellEmbedder.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImageLinearCellEmbedder_h

#undef ImageLinearCellEmbedder_RECURSES
#endif // else defined(ImageLinearCellEmbedder_RECURSES)
