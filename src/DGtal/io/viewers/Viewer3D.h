/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESSpace FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file Viewer3D.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/01/03
 *
 * Header file for module Viewer3D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Viewer3D_RECURSES)
#error Recursive header files inclusion detected in Viewer3D.h
#else // defined(Viewer3D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Viewer3D_RECURSES

#if !defined Viewer3D_h
/** Prevents repeated inclusion of headers. */
#define Viewer3D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/base/Common.h"

#include <iostream>
#include <vector>
#include <algorithm>
#ifdef WIN32
#include <windows.h>
#endif
#ifdef APPLE
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#ifdef WITH_QT5
  #include <QApplication>
#else
  #include <QtGui/qapplication.h>
#endif

#include <QGLViewer/qglviewer.h>
#include <QGLWidget>
#include <QKeyEvent>

#include "DGtal/kernel/SpaceND.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/io/Display3D.h"
#include "DGtal/math/BasicMathFunctions.h"

#include "DGtal/kernel/CSpace.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class Viewer3D
  /**
   * Description of class 'Viewer3D' <p>
   * Aim: Display 3D primitive (like PointVector, DigitalSetBySTLSet,
   * Object ...). This class uses the libQGLViewer library (@see
   * http://www.libqglviewer.com ). It inherits of the class Display3D
   * and displays objects using a simple stream mechanism of
   * "<<".
   *
   * For instance you can display objects as follows:
   *
   * @code
   * #include <QtGui/qapplication.h>
   * #include "DGtal/helpers/StdDefs.h"
   * #include "DGtal/io/viewers/Viewer3D.h"
   * ...
   * using namespace Z3i;
   * ...
   *
   * Point p1( 0, 0, 0 );
   * Point p2( 5, 5 ,5 );
   * Point p3( 2, 3, 4 );
   * Domain domain( p1, p2 );
   * Viewer3D<> viewer;
   * viewer.show();
   * viewer << domain;
   * viewer << p1 << p2 << p3;
   * viewer<< Viewer3D<>::updateDisplay;
   * return application.exec();
   *
   * @endcode
   *

   * This class is parametrized by both the Digital and Khalimsky
   * space used to display object. More precisely, embed methods are
   * used to compute the Euclidean coordinate of digital
   * objects/khalimksy cells.
   *
   * @tparam TSpace any model of Digital 3D Space
   * @tparam TKSpace any mode of Khalimksky 3D space
   *
   * @note You *must* provide a Khalimksy space at instanciation if
   * you wish to display cells with the viewer. If you are not going
   * to display cells, then it is not compulsory to provide it.
   *
   * @see Display3D, Board3DTo2D
   */
  template <typename TSpace  = SpaceND<3>,
            typename TKSpace = KhalimskySpaceND<3>>
  class Viewer3D : public QGLViewer, public Display3D<TSpace, TKSpace>
  {

    BOOST_CONCEPT_ASSERT( (concepts::CSpace<TSpace>));

    //---------------overwritting some functions of Display3D -------------------

    // ----------------------- public types ------------------------------
  public:
  typedef TSpace Space;
  typedef TKSpace KSpace;
  typedef Viewer3D<Space, KSpace> Self;
  typedef Display3D<Space, KSpace> Display;
  typedef typename Display::SelectCallbackFct SelectCallbackFct;
  typedef typename Display::RealPoint RealPoint;
  using Display::getSelectCallback3D;

  enum RenderingMode
  {
    RenderingDefault,
    RenderingMetallic,
    RenderingPlastic,
    RenderingLambertian
  };

  /**
   * Interface that can be used so that one can extend a few service
   * of Viewer3D, like keyPressEvent and others. You may thus give an
   * extension to a Viewer3D by simply handling it a pointer to an
   * object deriving from this class.
   */
  struct Extension
  {
    /// The associated viewer.
    typedef Viewer3D<Space, KSpace> Viewer;

    virtual ~Extension() = default;
    
    /// This method may be overloaded to capture other key
    /// events. It will be called at the beginning of Viewer3D::keyPressEvent.
    ///
    /// @param viewer the viewer calling this method
    /// @param event the key event
    ///
    /// @return 'true' if the event was handled (in this case,
    /// Viewer3D::keyPressEvent will not do anything).
    virtual bool keyPressEvent( Viewer & viewer, QKeyEvent * event )
    {
      boost::ignore_unused_variable_warning( viewer );
      boost::ignore_unused_variable_warning( event );
      return false;
    }

    /// This method may be overloaded and is called at the beginning
    /// of Viewer3D::drawWithNames. This method is useful for
    /// drawing elements with additional information for selection.
    ///
    /// @param viewer the viewer calling this method
    virtual void drawWithNames( Viewer & viewer )
    {
      boost::ignore_unused_variable_warning( viewer );
    }

    /// This method may be overloaded and is called at the beginning
    /// of Viewer3D::draw. This method is called for drawing
    /// elements.
    ///
    /// @param viewer the viewer calling this method
    virtual void draw( Viewer & viewer )
    {
      boost::ignore_unused_variable_warning( viewer );
    }

    /// This method may be overloaded and is called at QGLViewer
    /// initialization. It will be called at the beginning of
    /// Viewer3D::init.
    /// @param viewer the viewer calling this method
    virtual void init( Viewer & viewer )
    {
      boost::ignore_unused_variable_warning( viewer );
    }

    /// This method may be overloaded and is called when pressing
    /// help. It will be added before Viewer3D::helpString.
    ///
    /// @param viewer the viewer calling this method
    /// @return astring corresponding to the help of the viewer (list of
    /// commands, etc)
    virtual QString helpString( const Viewer & viewer ) const
    {
      boost::ignore_unused_variable_warning( viewer );
      return "";
    }

    /// This method may be overloaded to take care of a mouse
    /// selection event. It will be called at the beginning of
    /// Viewer3D::postSelection.
    ///
    /// @param viewer the viewer calling this method
    /// @param point the point clicked by the user in the window
    ///
    /// @return 'true' if the event was handled (in this case,
    /// Viewer3D::postSelection will not do anything).
    virtual bool postSelection( const Viewer & viewer, const QPoint & point )
    {
      boost::ignore_unused_variable_warning( viewer );
      boost::ignore_unused_variable_warning( point );
      return false;
    }

    /// This method may be overloaded to capture other mouse move
    /// events. It will be called at the beginning of Viewer3D::mouseMoveEvent.
    ///
    /// @param viewer the viewer calling this method
    /// @param event the mouse move event
    ///
    /// @return 'true' if the event was handled (in this case,
    /// Viewer3D::mouseMoveEvent will not do anything).
    virtual bool mouseMoveEvent( const Viewer & viewer, QMouseEvent * event )
    {
      boost::ignore_unused_variable_warning( viewer );
      boost::ignore_unused_variable_warning( event );
      return false;
    }

    /// This method may be overloaded to capture other mouse press
    /// events. It will be called at the beginning of Viewer3D::mousePressEvent.
    ///
    /// @param viewer the viewer calling this method
    /// @param event the mouse press event
    ///
    /// @return 'true' if the event was handled (in this case,
    /// Viewer3D::mousePressEvent will not do anything).
    virtual bool mousePressEvent( const Viewer & viewer, QMouseEvent * event )
    {
      boost::ignore_unused_variable_warning( viewer );
      boost::ignore_unused_variable_warning( event );
      return false;
    }

    /// This method may be overloaded to capture other mouse release
    /// events. It will be called at the beginning of
    /// Viewer3D::mouseReleaseEvent.
    ///
    /// @param viewer the viewer calling this method
    /// @param event the mouse release event
    ///
    /// @return 'true' if the event was handled (in this case,
    /// Viewer3D::mouseReleaseEvent will not do anything).
    virtual bool mouseReleaseEvent( const Viewer & viewer, QMouseEvent * event )
    {
      boost::ignore_unused_variable_warning( viewer );
      boost::ignore_unused_variable_warning( event );
      return false;
    }
  };

  // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor
     */
  Viewer3D() : QGLViewer(), Display3D<Space, KSpace>(), myExtension( 0 )
  {
    resize( 800, 600 );
    };

    /**
     *Constructor with a khalimsky space
     * @param KSEmb the Khalimsky space
     */
    Viewer3D( const KSpace & KSEmb )
      : QGLViewer(), Display3D<Space, KSpace>( KSEmb ), myExtension( 0 )
    {
      resize(800,600);
    }

    /// Sets the extension \a ext to the viewer. The object is
    /// acquired by the viewer and should be dynamically allocated.
    /// @param ext any dynamically allocated object deriving from Extension.
    void setExtension( Extension * ext )
    {
      if ( myExtension != 0 )
        delete myExtension;
      myExtension = ext;
    }

    /// Removes the current extension to the viewer or does nothing if
    /// no extension was present.
    void removeExtension()
    {
      if ( myExtension != 0 )
        delete myExtension;
      myExtension = 0;
    }

    /**
     * Set camera position.
     * @param ax x position.
     * @param ay y position.
     * @param az z position.
     */
    void setCameraPosition(double ax, double ay, double az)
    {
      camera_position[0] = ax; camera_position[1] = ay; camera_position[2] = az;
    }

    /**
     * Set camera direction.
     * @param ax x direction.
     * @param ay y direction.
     * @param az z direction.
     */
    void setCameraDirection(double ax, double ay, double az)
    {
      camera_direction[0] = ax; camera_direction[1] = ay; camera_direction[2] = az;
    }

    /**
     * Set camera up-vector.
     * @param ax x coordinate of up-vector.
     * @param ay y coordinate of up-vector.
     * @param az z coordinate of up-vector.
     */
    void setCameraUpVector(double ax, double ay, double az)
    {
      camera_upVector[0] = ax; camera_upVector[1] = ay; camera_upVector[2] = az;
    }

    /**
     * Set near and far distance, too near or too far end up not visible.
     * @param _near near distance.
     * @param _far far distance.
     */
    void setNearFar(double _near, double _far)
    {
      ZNear = _near; ZFar = _far;
    }

    /**
     * Set the open gl scale of x,y,z axis. It doesn't change the
     * geometry of anything, it is just visualisation parameter
     * (useful to produce more realistic 3D volume display)
     * @param sx the scale on the x axis.
     * @param sy the scale on the y axis.
     * @param sz the scale on the z axis.
     *
     **/
    void setGLScale(float sx, float sy, float sz)
    {
      myGLScaleFactorX=sx;
      myGLScaleFactorY=sy;
      myGLScaleFactorZ=sz;
      // In order to have the light source rendering the same as wtih the default scale 1. 
      glEnable(GL_NORMALIZE);  
    }


    /**
     * Changes the light rendering mode (GL_LIGHT_MODEL_TWO_SIDE) for
     * single face primitives (polygons, quads or triangles). It will have no
     * effect for cube or ball primitive which will be always rendered with
     * single face.
     *
     * @param[in] doubleSidedRendering if true (resp. false) the
     * double (resp. single) rendering mode will be activated for
     * polygons, quads and triangles.
     * 
     **/
    void setGLDoubleRenderingMode(bool doubleSidedRendering);

    
    /**
     * Change the light shininess coefficients used in opengl
     * rendering (used in glMaterialf with GL_SPECULAR parameters). 
     *
     * @param[in] matShininessCoeff the value of the shininess coefficient (defined in [0, 128], default 50.0).
     * 
     **/
    void setGLMaterialShininessCoefficient(const GLfloat matShininessCoeff);

    
    /**
     * Change the light ambient coefficients used in opengl
     * rendering (used in glLightfv with GL_AMBIENT parameters). 
     *
     * @param[in] lightAmbientCoeffs the values of specular coefficient of RGBA channels (defined in [0,1], default: {0.0,0.0,0.0,1.0}).

     * 
     **/
    void setGLLightAmbientCoefficients(const GLfloat lightAmbientCoeffs [4]);

    /**
     * Change the material ambient coefficients used in opengl
     * rendering (used in glMaterialf with GL_AMBIENT parameters). 
     *
     * @param[in] lightDiffuseCoeffs the values of specular coefficient of RGBA channels (defined in [0,1], default: {1.0,1.0,1.0,1.0}).

     * 
     **/
    void setGLLightDiffuseCoefficients(const GLfloat lightDiffuseCoeffs [4]);


    /**
     * Change the light specular coefficients used in opengl
     * rendering (used in glLightfv with GL_SPECULAR parameters). 
     *
     * @param[in] lightSpecularCoeffs the values of specular coefficient of RGBA channels (defined in [0,1], default: {1.0,1.0,1.0,1.0}).
     * 
     **/
    void setGLLightSpecularCoefficients(const GLfloat lightSpecularCoeffs [4]);
    


    /**
     *  Change the primitive to display ball (OpenGl points instead
     *  balls created with quads).
     * 
     *
     *  @param[in] useOpenGLPt if true all points will be displayed
     *  with OpenGl points instead the default balls (defined from
     *  quads).
     *
     **/    
    void setUseGLPointForBalls(bool useOpenGLPt);

    
    /**
     * Change the current rendering mode of the viewer.
     * 
     * @param[in] aRenderMode the mode of the rendering.
     * @param[in] displayState if true (default) the viewer will display the current rendering mode.
     * 
     **/
    void updateRenderingCoefficients(const RenderingMode aRenderMode, bool displayState=true);
    
    
    /// the 3 possible axes for the image direction
    enum ImageDirection {xDirection, yDirection, zDirection, undefDirection };
    /// the modes of representation of an image
    enum TextureMode {RGBMode, GrayScaleMode };

    /// the default background color of the viewer
    DGtal::Color myDefaultBackgroundColor;
    /// the default color of the viewer
    DGtal::Color myDefaultColor;
    /// true if the background is default
    bool myIsBackgroundDefault;
    /// objects have shadows which follow the camera if false
    bool myViewWire;
    double myGLPointMinWidth = 1.5; /// to improve the display of gl points    
    double myGLLineMinWidth = 1.5; /// to improve the display of gl line
    /// flag to save automatically or not the Viewer3d state when closing the viewer
    bool myAutoSaveState;
    // define the default rendering mode of the viewer
    RenderingMode myRenderingMode = RenderingDefault;
    
    /**
     * Used to display the 2D domain of an image.
     * @note has to be public because of external functions
     **/
    struct Image2DDomainD3D
    {

      /// The image domain coordinates
      RealPoint point1;
      RealPoint point2;
      RealPoint point3;
      RealPoint point4;
      /// The image domain color
      DGtal::Color color;
      /// the width of the image domain
      unsigned int myDomainWidth;
      /// the height of the image domain
      unsigned int myDomainHeight;
      /// the direction of the domain (x, y or z axe)
      ImageDirection myDirection;
      /// the mode of representation of the image domain
      std::string myMode;
      /// the index of the line of the domain in the lineSetList of the viewer
      std::size_t myLineSetIndex;

      /**
       * Constructor
       * @param aDomain a domain
       * @param normalDir the normal vector direction
       * @param xBottomLeft the x coordinate of bottom left image point.
       * @param yBottomLeft the y coordinate of bottom left image point.
       * @param zBottomLeft the z coordinate of bottom left image point.
       * @param mode the mode of representation
       */
      template<typename TDomain>
      Image2DDomainD3D( TDomain aDomain, ImageDirection normalDir=zDirection,
                        double xBottomLeft=0.0, double yBottomLeft=0.0, double zBottomLeft=0.0, std::string mode= "BoundingBox")
      {
        BOOST_CONCEPT_ASSERT(( concepts::CDomain < TDomain >));
        myMode = mode;
        myDirection=normalDir;
        myDomainWidth = (aDomain.upperBound())[0]-(aDomain.lowerBound())[0]+1;
        myDomainHeight = (aDomain.upperBound())[1]-(aDomain.lowerBound())[1]+1;
        updateDomainOrientation(normalDir, xBottomLeft, yBottomLeft, zBottomLeft);
      }


      /**
       * Update the domain direction from a specific normal direction
       * (Viewer3D::xDirection, Viewer3D::yDirection or Viewer3D::zDirection) and image position
       * from the botton left point.
       * @param normalDir give a predifined normal orientation can be (Viewer3D::xDirection, Viewer3D::yDirection or Viewer3D::zDirection)
       * @param xBottomLeft the x coordinate of bottom left image point.
       * @param yBottomLeft the x coordinate of bottom left image point.
       * @param zBottomLeft the x coordinate of bottom left image point.
       **/
      void updateDomainOrientation( ImageDirection normalDir,
                                    double xBottomLeft, double yBottomLeft, double zBottomLeft);


      /**
       * Translate domain postion.
       * @param xTranslation the image translation in the x direction (default 0).
       * @param yTranslation the image translation in the y direction (default 0).
       * @param zTranslation the image translation in the z direction (default 0).
       **/
      void translateDomain(double xTranslation=0.0,
                           double yTranslation=0.0, double zTranslation=0.0);

    };


    /**
     * Used to display an image as a textured quad image.
     *
     **/
    struct TextureImage
    {

      RealPoint point1;
      RealPoint point2;
      RealPoint point3;
      RealPoint point4;

      ImageDirection myDirection; /// direction of the image (x, y or z axe)

      unsigned int myImageWidth;/// the width of the image
      unsigned int myImageHeight;/// the height of the image
      //TODO complete desc attribute
      unsigned int * myTabImage; /// for each pixel of the image, color or height ?

      bool myDrawDomain; /// true if the draw have a domain
      unsigned int myIndexDomain; /// index of the image domain if exist
      TextureMode myMode; /// the mode of representation of the image

      /**
       * @brief Destructor
       */
      ~TextureImage()
      {
        delete [] myTabImage;
      };

      /**
       * @brief Copy constructor (needed due to myTabImage)
       * @param img the image
       */
      TextureImage(const TextureImage & img): point1(img.point1), point2(img.point2),
                point3(img.point3), point4(img.point4),
                myDirection(img.myDirection), myImageWidth(img.myImageWidth),
                myImageHeight(img.myImageHeight),
                myTabImage(img.myTabImage),
                myDrawDomain(img.myDrawDomain),
                myIndexDomain(img.myIndexDomain),
                myMode(img.myMode)
      {

        if(img.myImageHeight>0 && img.myImageWidth>0)
          {
            myTabImage = new unsigned int [img.myImageWidth*img.myImageHeight];
            for(unsigned int i=0; i<img.myImageWidth*img.myImageHeight; i++)
              {
                myTabImage[i] = img.myTabImage[i];
              }
          }else
          {
            myTabImage=img.myTabImage;
          }
      };



      /**
       * Constructor that fills image parameters from std image (image
       * buffer, dimensions, vertex coordinates, orientation)
       *
       * @tparam TImageType the type of the image given for the
       * constructor (should follow the CConstImage concept).  @tparam
       * TFunctor the functor type (should follow the CUnaryFunctor
       * concept with image value type as input type and unsigned int
       * as output type).
       *
       *
       * @param image the source image.
       * @param aFunctor a functor to transform input values to the output displayed values.
       * @param normalDir the direction of normal vector of the image plane (xDirection, yDirection or zDirection (default)) .
       * @param xBottomLeft the x coordinate of bottom left image point (default 0).
       * @param yBottomLeft the x coordinate of bottom left image point (default 0).
       * @param zBottomLeft the x coordinate of bottom left image point (default 0).
       * @param aMode the mode of representation (default GrayScaleMode).
       */
      template <typename TImageType, typename TFunctor>

      TextureImage( const TImageType & image, const TFunctor &aFunctor,
                    ImageDirection normalDir=zDirection,
                    double xBottomLeft=0.0, double yBottomLeft=0.0, double zBottomLeft=0.0,
                    TextureMode aMode= GrayScaleMode)
      {
        BOOST_CONCEPT_ASSERT(( concepts::CConstImage < TImageType > ));
        BOOST_CONCEPT_ASSERT(( concepts::CUnaryFunctor<TFunctor, typename TImageType::Value, unsigned int> )) ;
        myDrawDomain=false;
        myDirection=normalDir;
        myImageWidth = (image.domain().upperBound())[0]-(image.domain().lowerBound())[0]+1;
        myImageHeight = (image.domain().upperBound())[1]-(image.domain().lowerBound())[1]+1;
        myTabImage = new unsigned int [myImageWidth*myImageHeight];
        updateImageOrientation(normalDir, xBottomLeft, yBottomLeft, zBottomLeft);
        myMode=aMode;
        updateImageDataAndParam(image, aFunctor);
      }

      /**
       * Update the image direction from a specific normal direction
       * (Viewer3D::xDirection, Viewer3D::yDirection or Viewer3D::zDirection) and image position
       * from the botton left point.
       * @param normalDir give a predifined normal orientation can be (Viewer3D::xDirection, Viewer3D::yDirection or Viewer3D::zDirection)
       * @param xBottomLeft the x coordinate of bottom left image point.
       * @param yBottomLeft the x coordinate of bottom left image point.
       * @param zBottomLeft the x coordinate of bottom left image point.
       **/
      void updateImageOrientation( ImageDirection normalDir,
                                   double xBottomLeft, double yBottomLeft, double zBottomLeft);


      /**
       * Update the embedding of the image by updating the image 3D vertex.
       * @param aPoint1 the first image point (lower bound point)
       * @param aPoint2 the second image point (upper bound point in first dimension and lower in the second dimentsion)
       * @param aPoint3 the third image point (upper bound point in first second dimentsion)
       * @param aPoint4 the fourth image point (lower bound point in first dimension and upper in the second dimentsion)
       */
      void
      updateImage3DEmbedding( RealPoint aPoint1,
                              RealPoint aPoint2,
                              RealPoint aPoint3,
                              RealPoint aPoint4)
      {
        point1 = aPoint1;  point2 = aPoint2; point3 = aPoint3;   point4 = aPoint4;
        myDirection=undefDirection;
      }


      /**
       * Update the image parameters from std image (image buffer, vertex coordinates)
       * The new image should be with same dimension than the original.
       *
       * @tparam TImageType the type of the image given for the constructor (should follow the CConstImage concept).
       * @tparam TFunctor the functor type (should follow the
       * CUnaryFunctor concept with image value type as input type
       * and unsigned int as output type).
       *
       * @param image the source image.
       * @param aFunctor a functor to transform input values to the output displayed values.
       * @param xTranslation the image translation in the x direction (default 0).
       * @param yTranslation the image translation in the y direction (default 0).
       * @param zTranslation the image translation in the z direction (default 0).
       **/
      template <typename TImageType, typename TFunctor>
      void updateImageDataAndParam(const TImageType & image, const TFunctor &aFunctor, double xTranslation=0.0,
                                   double yTranslation=0.0, double zTranslation=0.0)
      {
        BOOST_CONCEPT_ASSERT(( concepts::CConstImage < TImageType > ));
        BOOST_CONCEPT_ASSERT(( concepts::CUnaryFunctor<TFunctor, typename TImageType::Value, unsigned int> )) ;
        assert ( (image.domain().upperBound())[0]-(image.domain().lowerBound())[0]+1== static_cast<int>(myImageWidth) &&
                 (image.domain().upperBound())[1]-(image.domain().lowerBound())[1]+1== static_cast<int>(myImageHeight));

        point1[0] += xTranslation; point1[1] += yTranslation; point1[2] += zTranslation;
        point2[0] += xTranslation; point2[1] +=yTranslation; point2[2] += zTranslation;
        point3[0] += xTranslation; point3[1] += yTranslation; point3[2] += zTranslation;
        point4[0] += xTranslation; point4[1] += yTranslation; point4[2] += zTranslation;

        unsigned int pos=0;
        for(typename TImageType::Domain::ConstIterator it = image.domain().begin(), itend=image.domain().end();
            it!=itend; ++it)
          {
            myTabImage[pos]= aFunctor(image(*it));
            pos++;
          }
      }

      /**
       * return the class name to implement the CDrawableWithViewer3D concept.
       **/
      std::string className() const;

    private:
      /**
       * default constructor
       * TextureImage
       */
      TextureImage()
      {};
    };

    /**
     * Set the default color for future drawing.
     * @param aColor a DGtal::Color (allow to set a trasnparency value).
     * @return a reference on 'this'.
     **/
    Viewer3D<Space, KSpace> & operator<< ( const DGtal::Color & aColor );


    /**
     * Set the default color for future drawing.
     * @param key a stream key
     * @return a reference on 'this'.
     **/
    Viewer3D<Space, KSpace> & operator<< ( const typename Viewer3D<Space, KSpace>::StreamKey & key );


    /**
     * Sort all surfels from the camera.
     **/
    void sortSurfelFromCamera();

    /**
     * Sort all triangle from the camera.
     **/
    void sortTriangleFromCamera();

    /**
     * Sort all triangle from the camera.
     **/
    void sortQuadFromCamera();

    /**
     * Sort all polygons from the camera.
     **/
    void sortPolygonFromCamera();



    template <typename TDrawableWithViewer3D>
    /**
     * Draws the drawable [object] in this board. It should satisfy
     * the concept CDrawableWithViewer3D, which requires for instance a
     * method setStyle( Viewer3D<Space, KSpace> & ).
     *
     * @param object any drawable object.
     * @return a reference on 'this'.
     */
    Viewer3D<Space, KSpace> & operator<< ( const TDrawableWithViewer3D & object );



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



    virtual unsigned int getCurrentDomainNumber();

    virtual unsigned int getCurrentGLImageNumber();


    /**
     *  @brief Overload of the QGLViewer method in order to change the
     *  order of display (to fix the QGLViewer axis display trough
     *  transparency).
     **/
    virtual void paintGL();


    /**
     *  @brief Overload QWidget method in order to add a call to
     * updateList() method (to ensure that the lists are well created
     * in the particular case where show() is called at the end of the
     * program).
     **/    
    virtual void show();


    /**
     * Add a TextureImage in the list of image to be displayed.
     * @param image a TextureImage including image data buffer and position, orientation.
     *
     **/
    void addTextureImage(const TextureImage &image);


    /**
     * Update the image parameters from std image (image buffer, vertex coordinates)
     * The new image should be with same dimension than the original.
     * @param imageIndex corresponds to the chronoloigic index given by the fuction (addTextureImage).
     * @param image the new image containing the new buffer (with same dimensions than the other image).
     * @param aFunctor a functor
     * @param xTranslation the image translation in the x direction (default 0).
     * @param yTranslation the image translation in the y direction (default 0).
     * @param zTranslation the image translation in the z direction (default 0).
     * @param rotationAngle the angle of rotation.
      * @param rotationDir the rotation is applied around the given direction.
      **/
    template <typename TImageType, typename TFunctor>

    void updateTextureImage(unsigned int imageIndex, const TImageType & image, const TFunctor & aFunctor,
                            double xTranslation=0.0, double yTranslation=0.0, double zTranslation=0.0,
          double rotationAngle=0.0, ImageDirection rotationDir=zDirection);




    /**
     * Update the image parameters from std image (image buffer, vertex coordinates)
     * The new image should be with same dimension than the original.
     * @param imageIndex corresponds to the chronoloigic index given by the fuction (addTextureImage).
     * @param xPosition the image translation in the x direction (default 0).
     * @param yPosition the image translation in the y direction (default 0).
     * @param zPosition the image translation in the z direction (default 0).
     * @param newDirection a new direction
     */
    void updateOrientationTextureImage(unsigned int imageIndex,
                                       double xPosition, double yPosition,
                                       double zPosition, ImageDirection newDirection);



    /**
     * Update the  vertex coordinates of the image embedded in 3D.
     * @param anImageIndex corresponds to the chronoloigic index given by the fuction (addTextureImage).
     * @param aPoint1 the new first point position embedded in 3D associated the lower point of the 2D image.
     * @param aPoint2 the new second point position embedded in 3D (in CCW order).
     * @param aPoint3 the new third point position embedded in 3D  associated the upper point of the 2D image.
     * @param aPoint4 the new fourth point position  embedded in 3D (in CCW order).
     */
    void updateEmbeddingTextureImage(unsigned int anImageIndex,
                                     typename Space::Point aPoint1, typename Space::Point aPoint2,
                                     typename Space::Point aPoint3, typename Space::Point aPoint4);



    /**
     * add an 2D image in a 3d space
     * @param anImageDomain an image and its domain
     * @param mode mode of representation
     * @param aColor color of the image
     */
    template<typename TDomain>
    void addImage2DDomainD3D(const TDomain &anImageDomain, std::string mode,
                             const DGtal::Color &aColor=DGtal::Color::Red );


    /**
     * update a 2D domain orientation
     * @param imageIndex index of the image in the list
     * @param xPosition the x position
     * @param yPosition the y position
     * @param zPosition the z position
     * @param newDirection the new direction
     */
    void updateAn2DDomainOrientation(unsigned int imageIndex,
                                     double xPosition, double yPosition,
                                     double zPosition, ImageDirection newDirection);

    /**
     * translate a 2D domain
     * @param domainIndex the index of the domain in the list
     * @param xTranslation x part of the translation vector
     * @param yTranslation y part of the translation vector
     * @param zTranslation z part of the translation vector
     */
    void translateAn2DDomain(unsigned int domainIndex, double xTranslation,
                             double yTranslation, double zTranslation);

    /**
     * compute2DDomainLineRepresentation
     * @param anImageDomain the image domain
     * @param delta the delte for computing
     * @return the vector containing the line domain representation.
     */
    std::vector<typename DGtal::Viewer3D< Space , KSpace >::LineD3D>
    compute2DDomainLineRepresentation( Image2DDomainD3D &anImageDomain, double delta );

    /**
     * compute2DDomainLineRepresentation
     * @param anImageDomain the image domain
     * @return the vector containing the line domain representation.
     */
    std::vector<typename DGtal::Viewer3D< Space , KSpace >::LineD3D>
    compute2DDomainLineRepresentation( Image2DDomainD3D &anImageDomain);


    /**
     * Rotate an lineD3D from its two extremity points.
     *
     * @param aLine (returns) the line to be rotated.
     * @param pt the center of rotation.
     * @param angleRotation the angle of rotation.
     * @param dirRotation the rotation will be applied around this direction.
     **/
    template < typename TContainer >
    void  rotateLineD3D(typename DGtal::Display3D<Space, KSpace>::LineD3D &aLine, DGtal::PointVector<3, int, TContainer> pt,
      double angleRotation, ImageDirection dirRotation);



    /**
     * Rotate an Image2DDomainD3D from its bounding points and from its grid line.
     *
     * @param anDom (returns) the domain to be rotated.
     * @param angle the angle of rotation.
     * @param rotationDir the rotation will be applied around this direction.
     **/

    void  rotateDomain(Image2DDomainD3D &anDom, double angle, ImageDirection rotationDir);




    

    // ------------------------- Protected Datas ------------------------------
  private:



  public:
  /// To call the protected method `drawLight`.
  void drawSomeLight( GLenum light ) const
  {
    QGLViewer::drawLight( light );
  }
  /// To call the protected method `drawLight`.
  void drawSomeLight( GLenum light, float zoom ) const
  {
    QGLViewer::drawLight( light, zoom );
  }

  // ------------------------- Hidden services ------------------------------
  // protected:

  /**
   * Permit to update the OpenGL list to be displayed.
   * Need to called after a number of addVoxel or after a
   * sortSurfelFromCamera().
   * @param needToUpdateBoundingBox flag to update the bounding box
   */
  void updateList( bool needToUpdateBoundingBox = true );

  /**
   * Draw a ball by using quads strip primitive.
   * @param[in] aBall the ball to be drawn
   */
  void glDrawGLBall( const typename Viewer3D<Space, KSpace>::BallD3D & aBall );

  /**
   * Used to manage new key event (wich are added from the default
   * QGLviewer keys).
   *
   * Note that when a new key event is taken into account it could be
   * added in the QGLviewer init() method to update automatically the
   * key description in the help QGLviewer window. For instance when
   * a new key is processed in this method you simply should add the following
   * code in the init() method:

   @code
   setKeyDescription(Qt::Key_NEW, "Description of the new Key.");
   @endcode

   *
   * @param e the QKeyEvent
   **/
  virtual void keyPressEvent( QKeyEvent * e );

  /**
   * Used to manage a mouse move event (to handle light move).
   *
   * @param e the QMouseEvent
   **/
  virtual void mouseMoveEvent( QMouseEvent * e );

  /**
   * Used to manage a mouse press event (to handle light move).
   *
   * @param e the QMouseEvent
   **/
  virtual void mousePressEvent( QMouseEvent * e );

  /**
   * Used to manage a mouse release event (to handle light move).
   *
   * @param e the QMouseEvent
   **/
  virtual void mouseReleaseEvent( QMouseEvent * e );

  /**
   * Used to sort pixel from camera
   **/
  struct CompFarthestVoxelFromCamera
  {
    qglviewer::Vec posCam;
    bool operator()( typename Viewer3D<Space, KSpace>::CubeD3D s1,
                     typename Viewer3D<Space, KSpace>::CubeD3D s2 )
    {
      double dist1 =
      sqrt( ( posCam.x - s1.center[ 0 ] ) * ( posCam.x - s1.center[ 0 ] ) +
            ( posCam.y - s1.center[ 1 ] ) * ( posCam.y - s1.center[ 1 ] ) +
            ( posCam.z - s1.center[ 2 ] ) * ( posCam.z - s1.center[ 2 ] ) );
      double dist2 =
      sqrt( ( posCam.x - s2.center[ 0 ] ) * ( posCam.x - s2.center[ 0 ] ) +
            ( posCam.y - s2.center[ 1 ] ) * ( posCam.y - s2.center[ 1 ] ) +
            ( posCam.z - s2.center[ 2 ] ) * ( posCam.z - s2.center[ 2 ] ) );
      return dist1 > dist2;
    }
    };


    /**
     * Used to sort pixel from camera
     **/
    struct CompFarthestTriangleFromCamera
    {
      qglviewer::Vec posCam;
      bool operator() ( typename Viewer3D<Space,KSpace>::TriangleD3D t1,
                        typename Viewer3D<Space,KSpace>::TriangleD3D t2 )
      {
        qglviewer::Vec center1 ( ( t1.point1[0]+t1.point2[0]+t1.point3[0] ) /3.0, ( t1.point1[1]+t1.point2[1]+t1.point3[1] ) /3.0, ( t1.point1[2]+t1.point2[2]+t1.point3[2] ) /3.0 );
        qglviewer::Vec center2 ( ( t2.point1[0]+t2.point2[0]+t2.point3[0] ) /3.0, ( t2.point1[1]+t2.point2[1]+t2.point3[1] ) /3.0, ( t2.point1[2]+t2.point2[2]+t2.point3[2] ) /3.0 );
        double dist1= sqrt ( ( posCam.x-center1.x ) * ( posCam.x-center1.x ) + ( posCam.y-center1.y ) * ( posCam.y-center1.y ) + ( posCam.z-center1.z ) * ( posCam.z-center1.z ) );
        double dist2= sqrt ( ( posCam.x-center2.x ) * ( posCam.x-center2.x ) + ( posCam.y-center2.y ) * ( posCam.y-center2.y ) + ( posCam.z-center2.z ) * ( posCam.z-center2.z ) );

        return dist1>dist2;
      }
    };

    /**
     * Used to sort pixel from camera
     **/
    struct CompFarthestSurfelFromCamera
    {
      qglviewer::Vec posCam;
      bool operator() (typename Viewer3D<Space,KSpace>::QuadD3D q1,
                       typename Viewer3D<Space,KSpace>::QuadD3D q2 )
      {

        qglviewer::Vec center1 ( ( q1.point1[0]+q1.point2[0]+q1.point3[0]+q1.point4[0] ) /4.0, ( q1.point1[1]+q1.point2[1]+q1.point3[1]+q1.point4[1] ) /4.0, ( q1.point1[2]+q1.point2[2]+q1.point3[2]+q1.point4[2] ) /4.0 );
        qglviewer::Vec center2 ( ( q2.point1[0]+q2.point2[0]+q2.point3[0]+q2.point4[0] ) /4.0, ( q2.point1[1]+q2.point2[1]+q2.point3[1]+q2.point4[1] ) /4.0, ( q2.point1[2]+q2.point2[2]+q2.point3[2]+q2.point4[2] ) /4.0 );

        double dist1= sqrt ( ( posCam.x-center1.x ) * ( posCam.x-center1.x ) + ( posCam.y-center1.y ) * ( posCam.y-center1.y ) + ( posCam.z-center1.z ) * ( posCam.z-center1.z ) );
        double dist2= sqrt ( ( posCam.x-center2.x ) * ( posCam.x-center2.x ) + ( posCam.y-center2.y ) * ( posCam.y-center2.y ) + ( posCam.z-center2.z ) * ( posCam.z-center2.z ) );
        return dist1>dist2;
      }
    };

    /**
     * Used to sort pixel from camera
     **/
    struct CompFarthestPolygonFromCamera
    {
      qglviewer::Vec posCam;
      bool operator() ( typename Viewer3D<Space,KSpace>::PolygonD3D q1,
                        typename Viewer3D<Space,KSpace>::PolygonD3D q2 )
      {
        double c1x=0.0, c1y=0.0, c1z=0.0;
        double c2x=0.0, c2y=0.0, c2z=0.0;
        for(unsigned int i=0; i< q1.vertices.size(); i++){
          c1x+=q1.vertices.at(i)[0];
          c1y+=q1.vertices.at(i)[1];
          c1z+=q1.vertices.at(i)[2];
        }
        for(unsigned int i=0; i< q2.vertices.size(); i++){
          c2x+=q2.vertices.at(i)[0];
          c2y+=q2.vertices.at(i)[1];
          c2z+=q2.vertices.at(i)[2];
        }

        qglviewer::Vec center1 ( c1x/(double)q1.vertices.size(),c1y/(double)q1.vertices.size(), c1z/(double)q1.vertices.size() );
        qglviewer::Vec center2 ( c2x/(double)q2.vertices.size(),c2y/(double)q2.vertices.size(), c2z/(double)q2.vertices.size() );

        double dist1= sqrt ( ( posCam.x-center1.x ) * ( posCam.x-center1.x ) + ( posCam.y-center1.y ) * ( posCam.y-center1.y ) + ( posCam.z-center1.z ) * ( posCam.z-center1.z ) );
        double dist2= sqrt ( ( posCam.x-center2.x ) * ( posCam.x-center2.x ) + ( posCam.y-center2.y ) * ( posCam.y-center2.y ) + ( posCam.z-center2.z ) * ( posCam.z-center2.z ) );
        return dist1>dist2;
      }
    };



    /**
     * @brief drawWithNames
     */
    virtual void drawWithNames();

    /**
     * @brief draw
     */
    virtual void draw();

    /**
     * @brief init
     */
    virtual void init();

    /**
     * @return astring corresponding to the help of the viewer (list of commands, etc)
     */
    virtual QString helpString() const;

    /**
     * @brief postSelection
     * @param point a point
     */
    virtual void postSelection ( const QPoint& point );



    /**
     * @brief Overload of the QGLViewer method which returns an XML
     * QDomElement representing the QGLViewer state. This overload adds the light
     * position attribute.
     *
     * @param name the name of the QDomElement tag.  
     * @param document the QDomElement factory used to create QDomElement.
     * @see initFromDOMElement
     */
    virtual  QDomElement domElement(const QString& name, QDomDocument& document) const;
    

    /**
     * @brief Overload of the QGLViewer method which restores the
     * viewer state from a QDomDocument element. This overload
     * recovers and loads default viewer attributes with the add of the
     * the light position.
     *
     * @param element QDomDocument used to apply the restoration.
     *
     * @see domElement
     */    
    virtual void initFromDOMElement(const QDomElement& element);
    
    
    /**
     * @brief Overload the QWidget method to customize the viewer state auto saving.
     * Now it save the viewer state if the flag myAutoSaveState is true (false by default)
     * and call the QGLWidget::closeEvent().
     * @param e the QCloseEvent calling the method.
     */
    
    protected: virtual void closeEvent	(	QCloseEvent * 	e	);
    

    
    // ------------------------- Internals ------------------------------------
  private:


    /**
     * Used to display in OPENGL an image as a textured quad image.
     *
     **/
    struct GLTextureImage
    {
      /// coordinates
      RealPoint point1;
      RealPoint point2;
      RealPoint point3;
      RealPoint point4;

      typename Viewer3D<Space, KSpace>::ImageDirection myDirection;
      unsigned int myImageWidth;
      unsigned int myImageHeight;

      unsigned int myBufferWidth;
      unsigned int myBufferHeight;
      GLuint myTextureName;
      typename Viewer3D<Space, KSpace>::TextureMode myMode;
      unsigned char * myTextureImageBufferGS;
      unsigned char * myTextureImageBufferRGB;
      double vectNormal[3];


      // By definition in OpenGL the image size of texture should power of 2
      double myTextureFitX;
      double myTextureFitY;


      // Destructor
      ~GLTextureImage()
      {
        if(myMode== 1)
          {
            if(myTextureImageBufferGS!=0)
              delete [] myTextureImageBufferGS;
          }
        if(myMode== Viewer3D<Space, KSpace>::RGBMode)
          {
            if(myTextureImageBufferRGB!=0)
              delete [] myTextureImageBufferRGB;
          }

      }

      //Copy constructor from a GLTextureImage
      GLTextureImage(const GLTextureImage &aGLImg): myBufferWidth(aGLImg.myBufferWidth),
                                                    myBufferHeight(aGLImg.myBufferHeight),
                                                    myTextureName(aGLImg.myTextureName),
                                                    myMode(aGLImg.myMode),
                myTextureFitX(aGLImg.myTextureFitX),
                                                    myTextureFitY(aGLImg.myTextureFitY)

      {
        point1[0]=aGLImg.point1[0]; point1[1]=aGLImg.point1[1]; point1[2]=aGLImg.point1[2];
        point2[0]=aGLImg.point2[0]; point2[1]=aGLImg.point2[1]; point2[2]=aGLImg.point2[2];
        point3[0]=aGLImg.point3[0]; point3[1]=aGLImg.point3[1]; point3[2]=aGLImg.point3[2];
        point4[0]=aGLImg.point4[0]; point4[1]=aGLImg.point4[1]; point4[2]=aGLImg.point4[2];
        myImageWidth=aGLImg.myImageWidth; myImageHeight=aGLImg.myImageHeight;
        myDirection = aGLImg.myDirection;
        vectNormal[0]=aGLImg.vectNormal[0];
        vectNormal[1]=aGLImg.vectNormal[1];
        vectNormal[2]=aGLImg.vectNormal[2];

        if(myMode== 1)
          {
            myTextureImageBufferGS = new unsigned char [myBufferHeight*myBufferWidth];
            for(unsigned int i=0; i<myBufferHeight*myBufferWidth;i++)
              {
                myTextureImageBufferGS[i]=aGLImg.myTextureImageBufferGS[i];
              }
          }else if(myMode==Viewer3D<Space, KSpace>::RGBMode)
          {
            myTextureImageBufferRGB = new unsigned char [3*myBufferHeight*myBufferWidth];
            for(unsigned int i=0; i<3*myBufferHeight*myBufferWidth;i+=3)
              {
                myTextureImageBufferRGB[i]=aGLImg.myTextureImageBufferRGB[i];
                myTextureImageBufferRGB[i+1]=aGLImg.myTextureImageBufferRGB[i+1];
                myTextureImageBufferRGB[i+2]=aGLImg.myTextureImageBufferRGB[i+2];
              }
          }
      }


      //Copy constructor from a TextureImage
      GLTextureImage(const typename Viewer3D<Space, KSpace>::TextureImage &aGSImage)
      {
        point1[0]=aGSImage.point1[0]; point1[1]=aGSImage.point1[1]; point1[2]=aGSImage.point1[2];
        point2[0]=aGSImage.point2[0]; point2[1]=aGSImage.point2[1]; point2[2]=aGSImage.point2[2];
        point3[0]=aGSImage.point3[0]; point3[1]=aGSImage.point3[1]; point3[2]=aGSImage.point3[2];
        point4[0]=aGSImage.point4[0]; point4[1]=aGSImage.point4[1]; point4[2]=aGSImage.point4[2];
        myImageWidth=aGSImage.myImageWidth; myImageHeight=aGSImage.myImageHeight;
        myDirection = aGSImage.myDirection;
        myMode= aGSImage.myMode;
        vectNormal[0]= (myDirection == Viewer3D<Space, KSpace>::xDirection)? 1.0: 0.0;
        vectNormal[1]= (myDirection == Viewer3D<Space, KSpace>::yDirection)? -1.0: 0.0;
        vectNormal[2]= (myDirection == Viewer3D<Space, KSpace>::zDirection)? 1.0: 0.0;
        if(myDirection==undefDirection){
          RealPoint v1 = point2-point1;
          RealPoint v2 = point4-point1;
          vectNormal[0] = v1[1]*v2[2] - v1[2]*v2[1];
          vectNormal[1] = v1[2]*v2[0] - v1[0]*v2[2];
          vectNormal[2] = v1[0]*v2[1] - v1[1]*v2[0];
          double norm = sqrt(vectNormal[0]*vectNormal[0]+vectNormal[1]*vectNormal[1]+vectNormal[2]*vectNormal[2]);
          vectNormal[0] /=norm; vectNormal[1] /=norm; vectNormal[2] /=norm;
        }

        myBufferWidth = functions::roundToUpperPowerOfTwo(myImageWidth);
        myBufferHeight = functions::roundToUpperPowerOfTwo(myImageHeight);

        if(myMode== 1)
          {
            myTextureImageBufferGS = new unsigned char [myBufferHeight*myBufferWidth];
            unsigned int pos=0;
            for (unsigned int i=0; i<myBufferHeight; i++)
              {
                for (unsigned int j=0; j<myBufferWidth; j++)
                  {
                    if(i<myImageHeight && j< myImageWidth)
                      {
                        myTextureImageBufferGS[pos]= aGSImage.myTabImage[i*myImageWidth+j];
                      }else{
                      myTextureImageBufferGS[pos]=0;
                    }
                    pos++;
                  }
              }
          }else if(myMode==Viewer3D<Space, KSpace>::RGBMode)
          {
            myTextureImageBufferRGB = new unsigned char [3*myBufferHeight*myBufferWidth];
            unsigned int pos=0;
            for (unsigned int i=0; i<myBufferHeight; i++)
              {
                for (unsigned int j=0; j<myBufferWidth; j++)
                  {
                    if(i<myImageHeight && j< myImageWidth)
                      {
                        DGtal::Color aCol(aGSImage.myTabImage[i*myImageWidth+j]);
                        myTextureImageBufferRGB[pos]= aCol.red();
                        myTextureImageBufferRGB[pos+1]= aCol.green();
                        myTextureImageBufferRGB[pos+2]= aCol.blue();
                      }else{
                      myTextureImageBufferRGB[pos]=0;
                      myTextureImageBufferRGB[pos+1]=0;
                      myTextureImageBufferRGB[pos+2]=0;
                    }
                    pos+=3;
                  }
              }
          }

        myTextureFitX = 1.0-((myBufferWidth-myImageWidth)/(double)myBufferWidth);
        myTextureFitY = 1.0-((myBufferHeight-myImageHeight)/(double)myBufferHeight);
      }
    };



    /**
     *
     * Type associated to the special intern method GLCreateCubeSetList.
     *
     **/
    typedef typename std::vector<typename Viewer3D<Space, KSpace>::CubeD3D> VectorCubes;
    typedef typename std::vector<typename Viewer3D<Space, KSpace>::QuadD3D> VectorQuad;
    typedef typename std::vector<typename Viewer3D<Space, KSpace>::LineD3D> VectorLine;
    typedef typename std::vector<typename Viewer3D<Space, KSpace>::BallD3D> VectorBall;
    typedef typename std::vector<typename Viewer3D<Space, KSpace>::TriangleD3D> VectorTriangle;
    typedef typename std::vector<typename Viewer3D<Space, KSpace>::PolygonD3D> VectorPolygon;
    typedef typename std::vector<typename Viewer3D<Space, KSpace>::TextureImage> VectorTextureImage;


    typedef typename VectorCubes::iterator ItCube;


    /**
     * Creates an OpenGL list of type GL_QUADS from a CubeD3D.  Only
     * one OpenGL list is created but each map compoment (CubeD3D
     * vector) are marked by its identifier through the OpenGl
     * glPushName() function.
     * See @ref moduleQGLInteraction for more details.
     * @param[in] aCubeMap  a map of cube (CubesMap) associating a name to a vector of CubeD3D.
     * @param[in] idList the Id of the list (should be given by glGenLists).
     **/
    void glCreateListCubesMaps(const typename Display3D<Space, KSpace>::CubesMap &aCubeMap, unsigned int idList);



    /**
     * Creates an OpenGL list of type GL_QUADS from a vector of QuadD3D.
     * @param[in] aVectQuad  a vector of quads (QuadD3D) containing the quads to be displayed.
     * @param[in] idList the Id of the list (should be given by glGenLists).
     **/
    void glCreateListQuadD3D(const VectorQuad &aVectQuad, unsigned int idList);


    /**
     * Creates an OpenGL list of type QL_LINES from a vector of LineD3D.
     * @param[in] aVectLine  a vector of lines (LineD3D) containing the quads to be displayed.
     * @param[in] idList the Id of the list (should be given by glGenLists).
     **/
    void glCreateListLines(const VectorLine &aVectLine, unsigned int idList);


    /**
     * Creates an OpenGL list of type  GL_POINTS from a vector of BallD3D.
     * @param[in] aVectBall  a vector of balls (BallD3D) containing the points to be displayed.
     * @param[in] idList the Id of the list (should be given by glGenLists).
     **/
    void glCreateListBalls(const VectorBall &aVectBall, unsigned int idList);


    /**
     * Creates an OpenGL list of type GL_QUADS from a QuadsMap.  Only
     * one OpenGL list is created but each map compoment (QuadD3D
     * vector) are marked by its identifier through the OpenGl
     * glPushName() function.
     * See @ref moduleQGLInteraction for more details.
     * @param[in] aQuadMap  a map of quad (QuadsMap) associating a name to a vector of QuadD3D.
     * @param[in] idList the Id of the list (should be given by glGenLists).
     **/
    void glCreateListQuadMaps(const typename Display3D<Space, KSpace>::QuadsMap &aQuadMap, unsigned int idList);


    /**
     * Creates an OpenGL list of type GL_LINES from a QuadsMap.  Only
     * one OpenGL list is created but each map compoment (QuadD3D
     * vector) are marked by its identifier through the OpenGl
     * glPushName() function.
     * See @ref moduleQGLInteraction for more details.
     * @param[in] aQuadMap  a map of quad (QuadsMap) associating a name to a vector of QuadD3D.
     * @param[in] idList the Id of the list (should be given by glGenLists).
     **/
    void glCreateListQuadMapsWired(const typename Display3D<Space, KSpace>::QuadsMap &aQuadMap, unsigned int idList);


    /**
     * Creates an OpenGL list of type GL_TRIANGLES from a vector of VectorTriangle.
     * All triangles are displayed in the same list.
     * @param[in] aVectTriangle  a vector of VectorTriangle containing the set of triangles to be displayed.
     * @param[in] idList the Id of the list (should be given by glGenLists).
     * @todo change the structure to support interactions as QuadMap do.
     * See \ref moduleQGLInteraction for more details.
     **/
    void glCreateListTriangles(const std::vector<VectorTriangle>  &aVectTriangle, unsigned int idList);


    /**
     * Creates an OpenGL list of type GL_LINES defines from a vector of VectorTriangle.
     * All triangles are displayed in the same list.
     * @param[in] aVectTriangle  a vector of VectorTriangle containing the set of triangles to be displayed.
     * @param[in] idList the Id of the list (should be given by glGenLists).
     * @todo change the structure to support interactions as QuadMap do.
     * See @ref moduleQGLInteraction for more details.
     **/
    void glCreateListTrianglesWired(const std::vector<VectorTriangle>  &aVectTriangle, unsigned int idList);


    /**
     * Creates an OpenGL list of type  GL_POLYGON from a vector of VectorPolygon.
     * All polygons are displayed in the same list.
     * @param  aVectPolygon a vector of VectorPolygon containing the points to be displayed.
     * @param idList the Id of the list (should be given by glGenLists).
     * @todo change the structure to support interactions as QuadMap do.
     * See @ref moduleQGLInteraction for more details.
     **/
    void glCreateListPolygons(const std::vector<VectorPolygon>  &aVectPolygon, unsigned int idList);


    /**
     * Creates an OpenGL list of type  GL_LINES from a vector of VectorPolygon.
     * All polygons are displayed in the same list.
     * @param[in] aVectPolygon  a vector of vector of polygons (VectorPolygon) containing the points to be displayed.
     * @param[in] idList the Id of the list (should be given by glGenLists).
     * @todo change the structure to support interactions as QuadMap do.
     * See @ref moduleQGLInteraction for more details.
     **/
    void glCreateListPolygonsWired(const std::vector<VectorPolygon>  &aVectPolygon, unsigned int idList);


    /**
     * Updates the container of GLTextureImage object with the given vector of TextureImage.
     * @param[in] aVectImage the vector containing
     *
     **/
    void glUpdateTextureImages(const VectorTextureImage  &aVectImage);


    /**
     * Updates opengl light rendering mode (GL_LIGHT_MODEL_TWO_SIDE)
     * according to the values of private attribute
     * myIsDoubleFaceRendering.
     **/
    
    void glUpdateLightRenderingMode() const;

    /**
     * Updates opengl background color according the current mode
     * (default or customized color)
     **/
    void glUpdateBackground() ; 
        
    /**
     * Updates the light source coordinates (myLightPosition) from the
     * camera relative coordinates (myLightPositionRefCamera). It
     * could be useful when the light source position is fix according
     * to camera position.
     **/
    void updateLightCoordsFromCamera();

    /**
     * Updates the camera relative light source coordinates
     *  (myLightPositionRefCamera) from the scene light coordinates
     *  (myLightPosition). It could be useful when the light source
     *  position is fix in the main scene.
     **/
    void updateRelativeCameraFromLightPosition();


    
  public:
    /**
     * Rotates Image2DDomainD3D or TextureImage  vertex from a given
     * angle and a rotation direction. The center of rotation is defined
     * from the image center point.
     *
     * @tparam  TImageORDomain the type object to be rotated (should  be an Image2DDomainD3D or a TextureImage)
     * @param anImageOrDom (returns) the domain or image to be rotated.
     * @param angle the angle of the rotation.
     * @param rotationDir the rotation is applied around this axis direction.
     **/

    template<typename TImageORDomain>
    static
    void
    rotateImageVertex(TImageORDomain &anImageOrDom, double angle, ImageDirection rotationDir){
      double xB = (anImageOrDom.point1[0]+anImageOrDom.point2[0]+anImageOrDom.point3[0]+anImageOrDom.point4[0])/4.0;
      double yB = (anImageOrDom.point1[1]+anImageOrDom.point2[1]+anImageOrDom.point3[1]+anImageOrDom.point4[1])/4.0;
      double zB = (anImageOrDom.point1[2]+anImageOrDom.point2[2]+anImageOrDom.point3[2]+anImageOrDom.point4[2])/4.0;
      rotatePoint( anImageOrDom.point1[0],  anImageOrDom.point1[1], anImageOrDom.point1[2],   xB, yB, zB, angle, rotationDir);
      rotatePoint( anImageOrDom.point2[0],  anImageOrDom.point2[1], anImageOrDom.point2[2],   xB, yB, zB, angle, rotationDir);
      rotatePoint( anImageOrDom.point3[0],  anImageOrDom.point3[1], anImageOrDom.point3[2],   xB, yB, zB, angle, rotationDir);
      rotatePoint( anImageOrDom.point4[0],  anImageOrDom.point4[1], anImageOrDom.point4[2],   xB, yB, zB, angle, rotationDir);

    }

    /**
     * Rotate a vertex from a given angle, a center point and a rotation direction.
     * @tparam TValues the type of coordinate to be rotated.
     * @param  x the x coordinate of the point to rotated (return).
     * @param  y the y coordinate of the point to rotated (return).
     * @param  z the z coordinate of the point to rotated (return).
     * @param cx the x coordinate of the rotation center.
     * @param cy the y coordinate of the rotation center.
     * @param cz the z coordinate of the rotation center.
     * @param rotationAngle the angle of the rotation.
     * @param rotationDir the rotation is applied around this axis direction.
     **/
    
    template <typename TValues>
    static
    void  rotatePoint(TValues &x, TValues &y, TValues &z,
          double cx, double cy, double cz,
          double rotationAngle, ImageDirection rotationDir);





    // ------------------------- Private Datas --------------------------------
  private:

    /// lists of the list to draw
    //GLuint myListToAff;

    GLuint myTriangleSetListId;
    GLuint myTriangleSetListWiredId;

    GLuint myPolygonSetListId;
    GLuint myPolygonSetListWiredId;

    GLuint myLineSetListId;
    GLuint myBallSetListId;
    GLuint myPrismListId;

    GLuint myQuadsMapId;
    GLuint myQuadsMapWiredId;

    GLuint myCubesMapId;
    GLuint myCubeSetListWiredId;

    /// number of lists in myListToAff

    unsigned int myNbListe;
    unsigned int myNbLineSetList;
    unsigned int myNbBallSetList;
    unsigned int myNbPrismSetList;

    /// used to displayed selected elements
    int mySelectedElementId = -1;
    unsigned char mySelectionColorShift = 150;
    
    /// information linked to the navigation in the viewer
    qglviewer::Vec myOrig, myDir, myDirSelector, mySelectedPoint;
    /// a point selected with postSelection @see postSelection
    QPoint myPosSelector;
    /// list of the images textures in this viewer
    std::vector<GLTextureImage> myVectTextureImage;

    bool myIsDoubleFaceRendering = true; ///< true if is double face rendering
    
    double camera_position[3]; ///< camera position
    double camera_direction[3]; ///< camera direction
    double camera_upVector[3]; ///< camera up-vector
    
    bool   myLightPositionFixToCamera = true; // when false the light position is fix according to the scene.
    double myLightTheta; /// the light position (inclination)
    double myLightPhi; /// the light position (azimuth)
    double myLightR; /// the light position (distance)
    GLfloat myLightPosition [4] = {0.0f, 0.0f, 1.0f, 1.0f}; // the light position in cartesian coordinate
    GLfloat myLightPositionRefCameraDefault [3] = {-100.0f, 100.0f, 0.0f}; // the light default position according to the camera position
    GLfloat myLightPositionRefCamera [3] = {0.0f, 0.0f, 0.0f}; // the light position according to the camera position
    GLfloat myMaterialShininessCoeff[1] =  {50.0f} ; // the material shininess coefficient used in opengl rendering 
    GLfloat myMaterialSpecularCoeffs[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // the light specular coefficients used in opengl rendering 
    GLfloat myLightSpecularCoeffs[4] = { 0.3f, 0.3f, 0.3f, 1.0f }; // the light specular coefficients used in opengl rendering 
    GLfloat myLightAmbientCoeffs[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // the material ambient coefficients used in opengl rendering  
    GLfloat myLightDiffuseCoeffs[4] = { 0.7f, 0.7f, 0.7f, 1.0f }; // the material diffuse coefficients used in opengl rendering  

    const GLfloat myDefaultRenderSpec = 0.3f; // default specular coefficients for default mode rendering
    const GLfloat myDefaultRenderDiff = 0.7f; // default diffuse coefficients for metallic mode rendering    
    const GLfloat myLambertRenderSpec = 0.0f; // default specular coefficients for default mode rendering
    const GLfloat myLambertRenderDiff = 0.9f; // default diffuse coefficients for metallic mode rendering
    const GLfloat myMetallicRenderSpec = 0.5f; // default specular coefficients for metallic mode rendering
    const GLfloat myMetallicRenderDiff = 0.5f; // default diffuse coefficients for metallic mode rendering
    const GLfloat myPlasticRenderSpec = 0.8f; // default specular coefficients for platic mode rendering
    const GLfloat myPlasticRenderDiff = 0.2f; // default diffuse coefficients for platic mode rendering
    
    bool myUseGLPointsForBalls =  false; // to display balls with GL points (instead real ball) 

    double ZNear; ///< znear distance
    double ZFar; ///< zfar distance

    //the default width of the mesh line
    float myMeshDefaultLineWidth;

    // To apply openGL ajustment only on visualisation
    float myGLScaleFactorX=1.0;
    float myGLScaleFactorY=1.0;
    float myGLScaleFactorZ=1.0;
    
    // Used to apply interactive light rotation
    double myLigthRotationStep; /// the angle rotation increment used for interactive light move
    int myRefMouseXPos; /// the reference mouse x-position used to determince the light position change (azimuth)
    int myRefMouseYPos; /// the reference mouse y-position used to determince the light position change (inclination)
    bool myIsMovingLight; /// flag to display the ligth source when it is moved by the user

    /// Used to store all displayed images
    std::vector<TextureImage> myGSImageList;
    /// Used to store all the domains
    std::vector<Image2DDomainD3D> myImageDomainList;
    /// Stored a possible extension to the viewer (pointer owned).
    Extension * myExtension;

  }; // end of class Viewer3D

  template <typename TSpace, typename TKSpace>
  /**
   * Overloads 'operator<<' for displaying objects of class 'Viewer3D'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Viewer3D' to write.
   * @return the output stream after the writing.
   */
  std::ostream & operator<<( std::ostream & out,
                             const Viewer3D<TSpace, TKSpace> & object );
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/viewers/Viewer3D.ih"

// //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Viewer3D_h

#undef Viewer3D_RECURSES
#endif // else defined(Viewer3D_RECURSES)
