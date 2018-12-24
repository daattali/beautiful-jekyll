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
 * @file   Board3DTo2D.h
 * @author Martial Tola <http://liris.cnrs.fr/martial.tola/>
 * @date   mercredi 22 juin 2011
 *
 * @brief
 *
 * Header file for module Board3DTo2D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Board3DTo2D_RECURSES)
#error Recursive header files inclusion detected in Board3DTo2D.h
#else // defined(Board3DTo2D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Board3DTo2D_RECURSES

#if !defined Board3DTo2D_h
/** Prevents repeated inclusion of headers. */
#define Board3DTo2D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/io/Display3D.h"
#include "DGtal/io/Color.h"

#include "DGtal/kernel/CSpace.h"


//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class Board3DTo2D
/**
   * Description of class 'Board3DTo2D' <p> @brief Class for PDF, PNG,
   * PS, EPS, SVG export drawings with Cairo with 3D->2D projection.
   */
template < typename  Space = Z3i::Space, typename KSpace = Z3i::KSpace>
class Board3DTo2D : public Display3D<Space, KSpace>
{

  BOOST_CONCEPT_ASSERT((concepts::CSpace<Space>));

protected:
  using Display3D<Space, KSpace>::myQuadsMap;

public:
    /**
     * Cairo type for save files.
     */
    enum CairoType { CairoPDF, CairoPNG, CairoPS, CairoEPS, CairoSVG };

    /**
     * Constructor.
     */
    Board3DTo2D();

    /**
    * Constructor with a khalimsky space
    * @param KSEmb the Khalimsky space
    */
    Board3DTo2D( KSpace KSEmb )
        : Display3D<Space,KSpace>( KSEmb )
      {
        init();
      }


    ~Board3DTo2D(){}


    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const
    {
        return "Board3DTo2D";
    }

    /**
     * Set camera position.
     * @param x x position.
     * @param y y position.
     * @param z z position.
     */
    void setCameraPosition(double x, double y, double z)
    { camera_position[0] = x; camera_position[1] = y; camera_position[2] = z; }

    /**
     * Set camera direction.
     * @param x x direction.
     * @param y y direction.
     * @param z z direction.
     */
    void setCameraDirection(double x, double y, double z)
    { camera_direction[0] = x; camera_direction[1] = y; camera_direction[2] = z; }

    /**
     * Set camera up-vector.
     * @param x x coordinate of up-vector.
     * @param y y coordinate of up-vector.
     * @param z z coordinate of up-vector.
     */
    void setCameraUpVector(double x, double y, double z)
    { camera_upVector[0] = x; camera_upVector[1] = y; camera_upVector[2] = z; }

    /**
     * Set near and far distance, too near or too far end up not visible.
     * @param _near near distance.
     * @param _far far distance.
     */
    void setNearFar(double _near, double _far) { ZNear = _near; ZFar = _far; }

    /**
     * Save a Cairo image.
     * @param filename filename of the image to save.
     * @param type type of the image to save (CairoPDF, CairoPNG, CairoPS, CairoEPS, CairoSVG).
     * @param bWidth width of the image to save.
     * @param bHeight height of the image to save.
     */
    void saveCairo(const char *filename, CairoType type, int bWidth, int bHeight);



    /**
     * The associated map type for storing possible modes used for
     * displaying for digital objects.
     */
    //typedef std::map< std::string, std::string > ModeMapping;

    //  /**
    //    * The associated map type for storing the default styles of
    //    * digital objects.
    //    */
    //   typedef std::map< std::string,CountedPtr<DrawableWithDisplay3D> > StyleMapping;


    DGtal::Color myDefaultColor; //!< default color


    /**
     * Set the default color for future drawing.
     *
     * @param aColor a DGtal::Color (allow to set a trasnparency value).
     *
     **/
    Board3DTo2D & operator<<(const DGtal::Color & aColor);


    /**
     * Draws the drawable [object] in this board. It should satisfy
     * the concept CDrawableWithDisplay3D, which requires for instance a
     * method setStyle( Board3DTo2D & ).
     *
     * @param object any drawable object.
     * @return a reference on 'this'.
     */
    template <typename TDrawableWithDisplay3D>
    Board3DTo2D & operator<<( const  TDrawableWithDisplay3D & object );

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

    /**
     * Transpose a 4x4 matrix.
     * @param tmat destination matrix.
     * @param mat source matrix.
     */
    static
    void TransposeMt(double tmat[16], double mat[16]);

    /**
     * Multiply a 3d vector by a 4x4 matrix.
     * @param v destination vector.
     * @param mat source matrix.
     * @param b source vector.
     */
    static
    void MulMt(double v[4], double mat[16], double b[4]);

    /**
     * Compute 4x4 LookAt matrix.
     * @param mat destination matrix.
     * @param eyex x position of eye.
     * @param eyey y position of eye.
     * @param eyez z position of eye.
     * @param dirx x direction of eye.
     * @param diry y direction of eye.
     * @param dirz z director of eye.
     * @param upx x coordinate of up-vector.
     * @param upy y coordinate of up-vector.
     * @param upz z coordinate of up-vector.
     */
    static
    void LookAtMt(double mat[16],
    double eyex, double eyey, double eyez,
    double dirx, double diry, double dirz,
    double upx, double upy, double upz);


    /**
     * Precompute 4x4 projection matrix for 3D->2D projection.
     */
    void precompute_projection_matrix();

    /**
     * Project a 3d point (3D->2D).
     * @param x3d x position of the 3d point.
     * @param y3d y position of the 3d point.
     * @param z3d z position of the 3d point.
     * @param x2d x destination projection position of the 2d point.
     * @param y2d y destination projection position of the 2d point.
     */
    void project(double x3d, double y3d, double z3d, double &x2d, double &y2d);



    int Viewport[4];    //!< 2D viewport
    double matrix[16];     //!< projection matrix

    double camera_position[3];  //!< camera position
    double camera_direction[3];  //!< camera direction
    double camera_upVector[3];  //!< camera up-vector

    double ZNear;      //!< znear distance
    double ZFar;      //!< zfar distance

protected :
    /**
     *  init function (should be in Constructor).
     */
    virtual void init();

private:

}; // end of class Board3DTo2D


template < typename Space, typename KSpace>
/**
   * Overloads 'operator<<' for displaying objects of class 'Board3DTo2D'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Board3DTo2D' to write.
   * @return the output stream after the writing.
   */
std::ostream&
operator<< ( std::ostream & out, const Board3DTo2D<Space,KSpace> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/boards/Board3DTo2D.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Board3DTo2D_h

#undef Board3DTo2D_RECURSES
#endif // else defined(Board3DTo2D_RECURSES)
