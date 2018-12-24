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
 * @file   Board3D.h
 * @author Aline Martin
 * @date   vendredi 7 juin 2013
 *
 * @brief
 *
 * Header file for module Board3D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Board3D_RECURSES)
#error Recursive header files inclusion detected in Board3D.h
#else // defined(Board3D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Board3D_RECURSES

#if !defined Board3D_h
/** Prevents repeated inclusion of headers. */
#define Board3D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/io/Display3D.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/Color.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{


  /////////////////////////////////////////////////////////////////////////////
  // class Board3D
  /**
   * @brief The class Board3D is a type of Display3D which export the figures in the format OBJ/MTL
   * when calling the method saveOBJ.
   *
   * The format OBJ/MTL is a geometry definition file format, this format has been adopted by many
   * 3D graphics application vendors (pbrt, blender, etc.).
   * to learn more about OBJ see <http://en.wikipedia.org/wiki/Wavefront_.obj_file>
   *
   * When exporting Board3D regroup objects by they list name. If two lists have the same name
   * they will melt in the same mesh eventually. If a list doesn't have a name the program will try
   * to give it an unique name so it will become a separate mesh.
   * Each list have a material description which correspond to its first element color.
   * If two lists have the same name and merge the final mesh will have two materials (one per list).
   *
   * @tparam Space a model of digital space (default type=Z3i::Space)
   * @tparam KSpace a model of Khalimsky space (default type=Z3i::KSpace)
   *
   */
  template < typename Space = Z3i::Space, typename KSpace = Z3i::KSpace>
  class Board3D : public Display3D<Space, KSpace>
  {
  public:


    /**
     * Constructor.
     */
    Board3D();

    /**
     * Constructor with a khalimsky space
     * @param KSEmb the Khalimsky space
     */
    Board3D(const  KSpace &KSEmb):Display3D<Space,KSpace>(KSEmb)
    {
      init();
    }


    /*!
     * Destructor.
     */
    ~Board3D(){};

    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const
    {
      return "Board3D";
    }

    /**
     * Save a OBJ image.
     * @param filename filename of the image to save.
     * @param isNormalized if true, we use the bounding box to scale
     * all objects such that they fit in [-1/2,1/2]^3 domain (default false),
     */
    void saveOBJ(const std::string & filename, 
                 const bool isNormalized = false);



    DGtal::Color myDefaultColor;  //!< default color


    /**
     * Set the default color for future drawing.
     *
     * @param aColor a DGtal::Color (allow to set a trasnparency value).
     *
     **/
    Board3D & operator<<(const DGtal::Color & aColor);


    /**
     * Draws the drawable [object] in this board. It should satisfy
     * the concept CDrawableWithDisplay3D, which requires for instance a
     * method setStyle( Board3D & ).
     *
     * @param object any drawable object.
     * @return a reference on 'this'.
     */
    template <typename TDrawableWithDisplay3D>
    Board3D & operator<<( const  TDrawableWithDisplay3D & object );


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

    /**
     * Check if the material associated woth the color exists. If it
     * does, the method returns the material index. Otherwise, the new
     * material is created.
     *
     * @param aColor a color
     *
     * @return the material index associated  with the color
     */
    unsigned int getMaterialIndex(const DGtal::Color &aColor);

    // ------------------------- Private Datas --------------------------------
  private:


    ///Material Map
    std::map<DGtal::Color,unsigned int> myMaterialMap;
    ///Last Material index
    unsigned int myMaterialIndex;
    ///Material buffer
    std::stringstream myMTLBuffer;


  protected :
    /**
     *  init function (should be in Constructor).
     */
    void init();

  }; // end of class Board3D


  /**
   * Overloads 'operator<<' for displaying objects of class 'Board3D'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Board3D' to write.
   * @return the output stream after the writing.
   */
  template < typename Space, typename KSpace>
  std::ostream&
  operator<< ( std::ostream & out, const Board3D<Space, KSpace> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/boards/Board3D.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Board3D_h

#undef Board3D_RECURSES
#endif // else defined(Board3D_RECURSES)
