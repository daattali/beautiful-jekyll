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
 * @file DrawWithViewer3DModifier.h
 * @author Aline Martin
 *
 * @date 2013/07/02
 *
 * Header file for module DrawWithViewer3DModifier.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DrawWithViewer3DModifier_RECURSES)
#error Recursive header files inclusion detected in DrawWithViewer3DModifier.h
#else // defined(DrawWithViewer3DModifier_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DrawWithViewer3DModifier_RECURSES

#if !defined DrawWithViewer3DModifier_h
/** Prevents repeated inclusion of headers. */
#define DrawWithViewer3DModifier_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/Alias.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/images/CConstImage.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /**
   *@brief Base class specifying the methods for classes which intend to
   * modify a Viewer3D stream.
   *
   */
  struct DrawWithViewer3DModifier : public DrawWithDisplay3DModifier
  {
    std::string className() const;
  };


#ifndef DrawWithBoard3DTo2DModifier_h
  /**
   * @brief  CameraPosition class to set camera position.
   */
  struct CameraPosition : public DrawWithViewer3DModifier
  {
    /**
     * Constructor.
     *
     * @param x x position.
     * @param y y position.
     * @param z z position.
     */
    CameraPosition( const double x, const double y, const double z ):eyex(x), eyey(y), eyez(z)
    {
    }

    double eyex, eyey, eyez;
  };


  /**
   * @brief CameraDirection class to set camera direction.
   */
  struct CameraDirection : public DrawWithViewer3DModifier
  {
    /**
     * Constructor.
     *
     * @param x x direction.
     * @param y y direction.
     * @param z z direction.
     */
    CameraDirection( const double x, const double y, const double z ): dirx(x), diry(y), dirz(z)
    {
    }

    double dirx, diry, dirz;
  };


  /**
   * @brief CameraUpVector class to set camera up-vector.
   */
  struct CameraUpVector : public DrawWithViewer3DModifier
  {
    /**
     * Constructor.
     *
     * @param x x coordinate of up-vector.
     * @param y y coordinate of up-vector.
     * @param z z coordinate of up-vector.
     */
    CameraUpVector( const double x, const double y, const double z ): upx(x), upy(y), upz(z)
    {
      upx=x; upy=y; upz=z;
    }

    double upx, upy, upz;
  };



  /**
   * @brief CameraZNearFar class to set near and far distance.
   */
  struct CameraZNearFar : public DrawWithViewer3DModifier
  {
    /**
     * Constructor.
     *
     * @param near near distance.
     * @param far far distance.
     */
    CameraZNearFar( const double near, const double far ): ZNear(near), ZFar(far)
    {
    }
    double ZNear, ZFar;
  };

#endif


  

  /**
   *
   * @brief class to modify the 3d embedding  of the image (useful to display not only 2D slice images).
   * The embdding can be explicitly given from the 3D position of the four bounding points. 
   */
  template < typename Space, typename KSpace>
  struct UpdateImage3DEmbedding : public DrawWithViewer3DModifier
  {

    /**
     * Constructor given from the four embedded 3D points.
     * The first (resp. third) point correspondts to the lower (res. upper) point according the 3 directions and the order should be given CCW. 
     *
     * @param anIndex the index of the image to be modified (should be less than the number of image added in the current Viewer3D).
     * @param aPoint1 the new first point position embedded in 3D associated the lower point of the 2D image.  
     * @param aPoint2 the new second point position embedded in 3D (in CCW order).
     * @param aPoint3 the new third point position embedded in 3D  associated the upper point of the 2D image.  
     * @param aPoint4 the new fourth point position  embedded in 3D (in CCW order).
     *
     **/
    UpdateImage3DEmbedding(unsigned int anIndex, 
                           typename Space::Point aPoint1, typename Space::Point aPoint2,
                           typename Space::Point aPoint3, typename Space::Point aPoint4): myIndex(anIndex),
                                                                                          myNewPoint1(aPoint1),
                                                                                          myNewPoint2(aPoint2),
                                                                                          myNewPoint3(aPoint3),
                                                                                          myNewPoint4(aPoint4)
    {
    }
    unsigned int myIndex;
    typename Space::Point myNewPoint1;
    typename Space::Point myNewPoint2;
    typename Space::Point myNewPoint3;
    typename Space::Point myNewPoint4;
  };
    
    
  /**
   *
   * @brief class to modify the position and orientation of an textured 2D image.
   *
   */
  template < typename Space, typename KSpace>
  struct UpdateImagePosition : public DrawWithViewer3DModifier
  {

    /**
     * Constructor given from an specific image index, a new direction
     * (associated to the normal of the image plane), and and a new
     * position of the bottom-left point.
     * @param anIndex the index of the image to be modified (should be less than the number of image added in the current Viewer3D).
     * @param newDir give the new direction of the image normal vector.
     * @param posXbottomLeft the x position of the bottom left point.
     * @param posYbottomLeft the y position of the bottom left point.
     * @param posZbottomLeft the z position of the bottom left point.
     *
     */
    UpdateImagePosition(unsigned int anIndex,typename Viewer3D<Space,KSpace>::ImageDirection newDir,
                        double posXbottomLeft, double posYbottomLeft, double posZbottomLeft ):  myIndex(anIndex),
                                                                                                myPosXBottomLeft(posXbottomLeft),
                                                                                                myPosYBottomLeft(posYbottomLeft),
                                                                                                myPosZBottomLeft(posZbottomLeft),
                                                                                                myNewDirection(newDir)
    {}

    unsigned int myIndex;
    double  myPosXBottomLeft;
    double  myPosYBottomLeft;
    double  myPosZBottomLeft;
    typename Viewer3D<Space,KSpace>::ImageDirection myNewDirection;
  };



  /**
   *
   * @brief class to insert a custom 2D textured image by using a
   * conversion functor and allows to change the default mode
   * (GrayScale mode) to color mode.
   *
   * @tparam TImageType the type of the used as texture (should follow the concept of CConstImage).
   * @tparam TFunctor  the functor type to transform source image scalar value into the one of the image being displayed.
   *
   * A typical use can be illustrated by displaying a grayscale source
   * image with artificial color defined from a colormap (see
   * viewer3D-8-2DSliceImages.cpp ):
   * We can first add a functor to convert grayscale value into RGB int:
   * @snippet io/viewers/viewer3D-8-2DSliceImages.cpp ExampleViewer3D2DImagesExtractImagesColorHeader
   *
   * @snippet io/viewers/viewer3D-8-2DSliceImages.cpp ExampleViewer3D2DImagesExtractImagesColorFct
   *
   * Then you can define and add the object AddTextureImage2DWithFunctor in a viewer:
   * @snippet io/viewers/viewer3D-8-2DSliceImages.cpp ExampleViewer3D2DImagesDisplayImagesColor
   *
   * @note If you change the image date don't forget to specify again.
   * @snippet io/viewers/viewer3D-8-2DSliceImages.cpp ExampleViewer3D2DModifImagesColor
   *
   * @see AddTextureImage3DWithFunctor viewer3D-8-2DSliceImages.cpp viewer3D-9-3Dimages.cpp
   */
  template <typename TImageType, typename TFunctor, typename Space, typename KSpace>
  struct AddTextureImage2DWithFunctor : public DrawWithViewer3DModifier
  {
    BOOST_CONCEPT_ASSERT((  concepts::CConstImage<TImageType> )) ;
    typedef typename Viewer3D<Space,KSpace>::TextureMode TTextureMode;
    
    /**
     * Constructor given from an 2D image and a Functor to apply specific conversion.
     *
     */
    AddTextureImage2DWithFunctor(ConstAlias<TImageType> anImage,
                                 Clone<TFunctor> aFunctor,
                                 TTextureMode aMode = TTextureMode::GrayScaleMode): my2DImage(&anImage),
                                                                                    myFunctor(aFunctor),
                                                                                    myMode(aMode)
    {

    }
    const TImageType *my2DImage;
    const TFunctor myFunctor;
    TTextureMode myMode;
  };

  /**
   *
   * @brief class to insert a custom 3D textured image by using a
   * conversion functor and allows to change the default mode
   * (GrayScale mode) to color mode.
   *
   * @tparam TImageType the type of the used as texture (should follow the concept of CConstImage).
   * @tparam TFunctor  the functor type to transform source image scalar value into the one of the image being displayed.
   *
   * A typical use can be illustrated by displaying a grayscale source
   * image with artificial color defined from a colormap (see
   * viewer3D-8-2DSliceImages.cpp viewer3D-9-3Dimages.cpp):
   * We can first add a functor to convert grayscale value into RGB int:
   * @snippet io/viewers/viewer3D-8-2DSliceImages.cpp ExampleViewer3D2DImagesExtractImagesColorHeader
   *
   * @snippet io/viewers/viewer3D-8-2DSliceImages.cpp ExampleViewer3D2DImagesExtractImagesColorFct
   *
   * Then you can define and add the object AddTextureImage2DWithFunctor in a viewer:
   * @snippet io/viewers/viewer3D-9-3Dimages.cpp ExampleViewer3D3DImagesDisplayImagesColor
   *
   * @note If you change the image date don't forget to specify again the functor with the UpdateImageData object.
   *
   * @see AddTextureImage2DWithFunctor viewer3D-8-2DSliceImages.cpp viewer3D-9-3Dimages.cpp
   */
  template <typename TImageType, typename TFunctor, typename Space, typename KSpace>
  struct AddTextureImage3DWithFunctor : public DrawWithViewer3DModifier
  {
    BOOST_CONCEPT_ASSERT((  concepts::CConstImage<TImageType> )) ;
    typedef typename Viewer3D<Space,KSpace>::TextureMode TTextureMode;
    /**
     * Constructor given from an 2D image and a Functor to apply specific conversion.
     *
     */
    AddTextureImage3DWithFunctor(ConstAlias<TImageType> anImage,
                                 Clone<TFunctor> aFunctor,
                                 TTextureMode aMode =
                                 TTextureMode::GrayScaleMode): my3DImage(&anImage),
                                                                         myFunctor(aFunctor),
                                                                         myMode(aMode)
    {

    }
    const TImageType *my3DImage;
    const TFunctor myFunctor;
    TTextureMode myMode;
  };



  /**
   *
   * @brief class to modify the position and orientation of an textured 2D image.
   *
   */
  template < typename Space, typename KSpace>
  struct UpdateLastImagePosition : public DrawWithViewer3DModifier
  {

    /**
     * Constructor given from an specific image index, a new direction
     * (associated to the normal of the image plane), and and a new
     * position of the bottom-left point.
     * @param newDir give the new direction of the image normal vector.
     * @param posXbottomLeft the x position of the bottom left point.
     * @param posYbottomLeft the y position of the bottom left point.
     * @param posZbottomLeft the z position of the bottom left point.
     *
     */
    UpdateLastImagePosition( typename Viewer3D<Space, KSpace>::ImageDirection newDir,
                             double posXbottomLeft, double posYbottomLeft, double posZbottomLeft ):
      myPosXBottomLeft(posXbottomLeft),
      myPosYBottomLeft(posYbottomLeft),
      myPosZBottomLeft(posZbottomLeft),
      myNewDirection(newDir)
    {

    }
    double  myPosXBottomLeft;
    double  myPosYBottomLeft;
    double  myPosZBottomLeft;
    typename Viewer3D<Space, KSpace>::ImageDirection myNewDirection;
  };




  /**
   * @brief class to modify the data of an given image and also the
   * possibility to translate it (optional).
   *
   */
  template<typename TImageType, typename TFunctor= functors::Cast<unsigned int> >
  struct UpdateImageData : public DrawWithViewer3DModifier
  {

    /**
     * Constructor given from an specific image index, a new image
     * (should be of dimension 2 and with the same size than the
     * orginal), and a possible (optional translation).
     *
     * @param anIndex the index of the image to be modified (should be less than the number of image added in the current Viewer3D).
     * @param anImage the new image which will be used to update the source image  data.
     * @param translateX the x translation value.
     * @param translateY the y translation value.
     * @param translateZ the y translation value.
     * @param rotationAngle the angle of rotation. 
     * @param dirRotation the rotation is applyed arount the given direction (default zDirection).
     * @param aFunctor a functor.
     */
    UpdateImageData(unsigned int anIndex, ConstAlias<TImageType> anImage, double translateX=0,
                    double translateY=0, double translateZ=0,
		    double rotationAngle=0.0, typename Viewer3D<>::ImageDirection dirRotation=Viewer3D<>::zDirection,
		    Clone<TFunctor> aFunctor = TFunctor() ): myIndex(anIndex),
							   myImage(&anImage),
							   myTranslateX (translateX),
							   myTranslateY (translateY),
							   myTranslateZ (translateZ),
							   myFunctor(aFunctor),
							   myRotationAngle(rotationAngle),
							   myRotationDir(dirRotation)
    {}

    unsigned int myIndex;
    const TImageType *myImage;
    int myTranslateX;
    int myTranslateY;
    int myTranslateZ;
    const TFunctor myFunctor;
    double myRotationAngle;
    typename Viewer3D<>::ImageDirection  myRotationDir;
   };




  /**
   * @brief class to modify the data of an given image and also the
   * possibility to translate it (optional).
   *
   */
  struct Translate2DDomain : public DrawWithViewer3DModifier
  {

    /**
     * Constructor given from an specific image index, a new image
     * (should be of dimension 2 and with the same size than the
     * orginal), and a possible (optional translation).
     *
     * @param anIndex the index of the image to be modified (should be less than the number of image added in the current Viewer3D).
     * @param translateX the x translation value.
     * @param translateY the y translation value.
     * @param translateZ the y translation value.
     *
     */
    Translate2DDomain(unsigned int anIndex, double translateX=0,
                      double translateY=0, double translateZ=0 ): myIndex(anIndex),
                                                                  myTranslateX (translateX),
                                                                  myTranslateY (translateY),
                                                                  myTranslateZ (translateZ)
    { }

    unsigned int myIndex;
    int myTranslateX;
    int myTranslateY;
    int myTranslateZ;
  };






  /**
   *
   * @brief class to modify the position and orientation of an 2D domain.
   *
   */
  template < typename Space, typename KSpace>
  struct Update2DDomainPosition : public DrawWithViewer3DModifier
  {

    /**
     * Constructor given from an specific 2D domain index, a new direction
     * (associated to the normal of the 2D domain plane), and and a new
     * position of the bottom-left point.
     * @param anIndex the index of the 2D domain to be modified (should be less than the number of domain added in the current Viewer3D).
     * @param newDir give the new direction of the domain normal vector.
     * @param posXbottomLeft the x position of the bottom left point.
     * @param posYbottomLeft the y position of the bottom left point.
     * @param posZbottomLeft the z position of the bottom left point.
     *
     */
    Update2DDomainPosition(unsigned int anIndex, typename Viewer3D<Space,KSpace>::ImageDirection newDir,
                           double posXbottomLeft, double posYbottomLeft, double posZbottomLeft ):  myIndex(anIndex),
                                                                                                   myPosXBottomLeft(posXbottomLeft),
                                                                                                   myPosYBottomLeft(posYbottomLeft),
                                                                                                   myPosZBottomLeft(posZbottomLeft),
      myNewDirection(newDir)
    { }

    unsigned int myIndex;
    double  myPosXBottomLeft;
    double  myPosYBottomLeft;
    double  myPosZBottomLeft;
    typename Viewer3D<Space, KSpace>::ImageDirection myNewDirection;
  };




} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DrawWithViewer3DModifier_h

#undef DrawWithViewer3DModifier_RECURSES
#endif // else defined(DrawWithViewer3DModifier_RECURSES)
