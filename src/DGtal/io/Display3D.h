/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file Display3D.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/08/08
 *
 * Header file for module Display3D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Display3D_RECURSES)
#error Recursive header files inclusion detected in Display3D.h
#else // defined(Display3D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Display3D_RECURSES

#if !defined Display3D_h
/** Prevents repeated inclusion of headers. */
#define Display3D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/io/Color.h"
#include "DGtal/images/CImage.h"
#include "DGtal/images/CConstImage.h"
#include "DGtal/shapes/Mesh.h"

/// for embedding
#include "DGtal/topology/CanonicCellEmbedder.h"
#include "DGtal/topology/CanonicSCellEmbedder.h"
#include "DGtal/kernel/CanonicEmbedder.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/kernel/CSpace.h"


//////////////////////////////////////////////////////////////////////////////


namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class Display3D
  /**
   * Description of class 'Display3D' <p>
   * \brief Aim: This semi abstract class defines the stream mechanism to
   display 3d primitive (like BallVector, DigitalSetBySTLSet, Object
   ...). The class Viewer3D and Board3DTo2D implement two different
   ways to display 3D objects. The first one (Viewer3D), permits an
   interactive visualisation (based on @a OpenGL ) and the second one
   (Board3dto2d) provides 3D visualisation from 2D vectorial display
   (based on the CAIRO library)
   @see Viewer3D, Board3DTo2D
   *
   * This class is parametrized by both the Digital and Khalimsky
   * space used to display object. More precisely, embed methods are
   * used to compute the Euclidean coordinate of digital
   * objects/khalimksy cells.
   *
   * @tparam Space any model of Digital 3D Space
   * @tparam KSpace any mode of Khalimksky 3D space
   */
  template < typename Space = Z3i::Space, typename KSpace = Z3i::KSpace>
  class Display3D
  {
  public:

    BOOST_CONCEPT_ASSERT((concepts::CSpace<Space>));
  public:

    typedef Display3D<Space,KSpace> Self;
    /// RealPoint type
    typedef typename Space::RealPoint RealPoint;
    /// RealVector type
    typedef typename Space::RealVector RealVector;
    typedef CanonicEmbedder<Space> Embedder;
    typedef CanonicCellEmbedder<KSpace> CellEmbedder;
    typedef CanonicSCellEmbedder<KSpace> SCellEmbedder;

    /// Select callback function type.
    typedef int (*SelectCallbackFct)( void* viewer, DGtal::int32_t name, void* data );

  protected:

    /// Structure for storing select callback functions. The select
    /// callback function is called whenever the user select a
    /// graphical object with "OpenGL name" in [min,max]. The order
    /// relation is used to find quickly the correct function.
    struct SelectCallbackFctStore {
      SelectCallbackFctStore( SelectCallbackFct _fct, 
                              void* _data,
                              DGtal::int32_t _min, DGtal::int32_t _max )
        : fct( _fct ), data( _data ), min( _min ), max( _max ) {}
      bool operator<( const SelectCallbackFctStore& other ) const
      { 
        return ( min < other.min ); // simple since there is no overlap.
      }
      bool isSelected( DGtal::int32_t name ) const
      { return ( min <= name ) && ( name <= max ); }

      SelectCallbackFct fct;
      void*             data;
      DGtal::int32_t    min;
      DGtal::int32_t    max;
    };

    /**
     * Common data to most graphical structures used in Display3D.
     */
    struct CommonD3D {
      DGtal::Color   color; ///< Color used for displaying the graphical structure 
      DGtal::int32_t name;  ///< The "OpenGL name" associated with the graphical structure, used for selecting it (-1 is none).

    protected:
      ~CommonD3D() = default; ///< Protected destructor to disallow polymorphism.
    };

    /**
     * The graphical structure that represents a 3D line segment in Display3D.
     */
    struct LineD3D : public CommonD3D {
      RealPoint point1;
      RealPoint point2;
      double width;
      bool isSigned;
      bool signPos;
    };

    /**
     * The graphical structure that represents a 3D cube in Display3D.
     */
    struct CubeD3D : public CommonD3D {
      /// The center coordinate of the cube.
      RealPoint center;
      /// The width of a cube face
      double width;
    };

    /**
     * The graphical structure that represents a clipping plane (it
     * uses the quadD3D structure)
     *
     * @see Display3D, Viewer3D, Board3DTo2D, quadD3D
     */
    struct ClippingPlaneD3D : public CommonD3D {
      double a,b,c,d;
    };


    /**
     * The graphical structure that represents a quadrilateral in the
     * space. It is used to display clipping planes and the components
     * of the myPrismList (allowing to set normal and color).
     *
     * @see Display3D, Viewer3D, Board3DTo2D
     */
    struct QuadD3D : public CommonD3D {
      RealPoint point1;
      RealPoint point2;
      RealPoint point3;
      RealPoint point4;
      double nx, ny, nz;
    };



    /**
     * The graphical structure that represents a triangle in the space.
     *
     * @see Display3D, Viewer3D, Board3DTo2D
     */
    struct TriangleD3D : public CommonD3D {
      RealPoint point1;
      RealPoint point2;
      RealPoint point3;
      double nx, ny, nz;
    };


  public:



    /// Structure used to display point in 3D
    /// @see addBall
    ///
    //have to be public because of external functions
    struct BallD3D : public CommonD3D
    {
      static const typename RealPoint::Dimension dimension = RealPoint::dimension;
      const double & operator[]( unsigned int i ) const
      {
        assert(i<3);
        return center[i];
      };
      double & operator[]( unsigned int i )
      {
        assert(i<3);
        return center[i];
      };
      RealPoint center;
      bool isSigned;
      bool signPos;
      double radius;
      unsigned int resolution;
    };


    /**
     * This structure is used to display polygonal faces in 3d.
     * @see Display3D, Viewer3D, Board3DTo2D
     **/
    struct PolygonD3D : public CommonD3D
    {
      std::vector<RealPoint> vertices;
      double nx, ny, nz;
      DGtal::Color color;
    };


    enum StreamKey {addNewList, updateDisplay, shiftSurfelVisu};


  public:
    /// The type that maps identifier name -> vector of QuadD3D.
    typedef std::map<DGtal::int32_t, std::vector< QuadD3D > > QuadsMap;
    
    /// The type that maps identifier name -> vector of CubeD3D.
    typedef std::map<DGtal::int32_t, std::vector< CubeD3D > > CubesMap;


  protected:
    /// The Khalimsky space
    KSpace myKSpace;
    /// an embeder from a dgtal space point to a real space point
    Embedder *myEmbedder;
    /// an embeder from a unsigned khalimsky space point to a real space point
    CellEmbedder *myCellEmbedder;
    /// an embeder from a signed khalimsky space point to a real space point
    SCellEmbedder *mySCellEmbedder;




    //----end of private data

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    virtual ~Display3D()
    {
      delete myEmbedder;
      delete mySCellEmbedder;
      delete myCellEmbedder;
    }

    /**
     * Constructor with the Khalimsky Space
     * @param KSEmb the khalimsky space for embedding
     */
    Display3D( const KSpace & KSEmb )
      : myKSpace( KSEmb )
      , myEmbedder( new Embedder() )
      , myCellEmbedder( new CellEmbedder( myKSpace ) )
      , mySCellEmbedder( new SCellEmbedder( myKSpace )  )
      , myBoundingPtEmptyTag( true )
      , myCurrentFillColor( 220, 220, 220 )
      , myCurrentLineColor( 22, 22, 222, 50 )
    {
    }
    
    /**
     * Default constructor
     * Display3D
     */
    Display3D()
      : Display3D( KSpace() )
    {
    }

    /// Copy constructor. Deleted.
    Display3D( const Display3D & ) = delete;

    /// Move constructor. Deleted.
    Display3D( Display3D && ) = delete;

    /// Assignment operator. Deleted.
    Display3D & operator= ( const Display3D & ) = delete;

    /// Move operator. Deleted.
    Display3D & operator= ( Display3D && ) = delete;

    // ----------------------- Interface --------------------------------------
  public:

    /// @return the embedder Point -> RealPoint
    const Embedder& embedder() const 
    { return *myEmbedder; }

    /// @return the embedder Cell -> RealPoint
    const CellEmbedder& cellEmbedder() const 
    { return *myCellEmbedder; }

    /// @return the embedder SCell -> RealPoint
    const SCellEmbedder& sCellEmbedder() const 
    { return *mySCellEmbedder; }

    /// @return the cellular grid space.
    const KSpace& space() const 
    { return myKSpace; }

    /**
     * Used to set the current fill color
     * @param aColor the fill color.
     **/
    virtual void setFillColor(DGtal::Color aColor);

    /**
     * Used to set the alpha value of the current fill color.
     * @param alpha the transparency value (from 0 to 255).
     **/
    virtual void setFillTransparency(unsigned char alpha);


    /**
     * Used to set the line fill color
     * @param aColor the line color.
     **/
    virtual void setLineColor(DGtal::Color aColor);


    /**
     * Used to get the fill color
     * @return the current fill color.
     **/

    virtual DGtal::Color getFillColor();

    /**
     * Used to get the line color
     * @return the current line color.
     **/

    virtual DGtal::Color getLineColor();

    /**
     *  Used to change the Khalimsky 3D Space.
     * @param aKSpace the new Khalimsky space.
     **/
    virtual void  setKSpace( const KSpace & aKSpace );


    /**
     * Sets the "OpenGL name" for next graphical directives.
     * @param name the "OpenGL name", an integer identifier or -1 for none.
     */
    void setName3d( DGtal::int32_t name = -1 );

    /**
     * @return the current "OpenGL name", an integer identifier or -1 if none was set.
     */
    DGtal::int32_t name3d() const;

    /**
     * Sets the callback function called when selecting a graphical
     * object with "OpenGL name" between \a min_name and \a max_name.
     * Note that ranges should not overlap. If several functions can
     * be called, behavior is undefined afterwards.
     *
     * @param fct any function.
     * @param data an arbitrary pointer that is given when calling the callback function.
     * @param min_name the first "OpenGL name" for which \a fct should be called.
     * @param max_name the last "OpenGL name" for which \a fct should be called.
     */
    void setSelectCallback3D( SelectCallbackFct fct, void* data,
                              DGtal::int32_t min_name, DGtal::int32_t max_name );

    /**
     * @param[in]  aName the "OpenGL name" that was selected.
     * @param[out] data a pointer that was given setting the callback function.
     * @return the select callback function that match the given \a
     * name, or 0 if none is associated to this name.
     */
    SelectCallbackFct getSelectCallback3D( DGtal::int32_t aName, void*& data ) const;

    // ----------------------- Graphical directives ----------------------------------
  public:


    /**
     * Add a new 3D Clipping plane represented by ax+by+cz+d = 0
     * A maximal of five clipping plane can be added.
     *
     * @param a a
     * @param b b
     * @param c c
     * @param d d plane equation.
     * @param drawPlane true if the plane should be draw
     **/

    void addClippingPlane(double a, double b, double c, double d, bool drawPlane);




    /**
     * @param objectName the name of the object (generally obtained
     * with a 'object.className()').
     *
     * @return the current mode for the given object name or "" if no
     * specific mode has been set.
     */
    std::string getMode( const std::string & objectName ) const;

    /**
     * Used to create a new list containing new 3D objects
     * (useful to use transparency between different objects).
     * @param s name of the new list
     **/
    void createNewLineList(std::string s= "");


    /**
     * Used to create a new list containing new 3D objects
     * (useful to use transparency between different objects).
     * @param s name of the new list
     **/
    void createNewBallList(std::string s= "");


    /**
     * Used to create a new list containing new 3D objects
     * (useful to use transparency between different objects).
     * @return the new key of the map associated to the new list.
     **/

    DGtal::int32_t createNewCubeList();

    
    /**
     * Delete the cube list identified by a its name.
     * @param[in] name the name of the cube list.
     * @return true if the list was found and removed.
     *
     **/
    bool deleteCubeList(const DGtal::int32_t name);

     /**
      * Used to create a new list containing new 3D objects
      * (useful to use transparency between different objects).
      * @return the new key of the map associated to the new list.
      **/
    DGtal::int32_t createNewQuadList();


    /**
     * Delete the quad list identified by a its name.
     * @param[in] name the name of the quad list.
     * @return true if the list was found and removed.
     *
     **/
    bool deleteQuadList(const DGtal::int32_t name);

    /**
     * Used to create a new list containing new 3D objects
     * (useful to use transparency between different objects).
     * @param s name of the new list
     **/
    void createNewTriangleList(std::string s= "");

    /**
     * Used to create a new list containing new 3D objects
     * (useful to use transparency between different objects).
     * @param s name of the new list
     **/
    void createNewPolygonList(std::string s= "");


    /**
     * Method to add a specific quad (used by @a addClippingPlane or
     * to represent basic surfels from Khalimsky space). The normal is
     * computed from the vertex order.
     *
     * @param p1 the 1st point
     * @param p2 the 2nd point
     * @param p3 the 3rd point
     * @param p4  the 4th point
     *
     */
    void addQuad(const RealPoint &p1, const RealPoint &p2,
                 const RealPoint &p3, const RealPoint &p4);

    /**
     * Method to add a specific quad. The normal vector is specified
     * by the user. Depending on @a enableReorientation, Quad points
     * can be reordered to make its orientation constistant with the
     * normal direction.
     *
     * @param p1 the 1st point
     * @param p2 the 2nd point
     * @param p3 the 3rd point
     * @param p4  the 4th point
     * @param n the normal vector
     * @param enableReorientation if true,  the quad orientation will
     * match with prescribed normal vector (dot product between the
     * normal and the canonical one is >0).
     * @param enableDoubleFace if true, two quad (with opposite normal
     * vector) will be drawn.
     *
     */
    void addQuadWithNormal(const RealPoint &p1, const RealPoint &p2,
                           const RealPoint &p3, const RealPoint &p4,
                           const RealPoint &n,
                           const bool enableReorientation,
                           const bool enableDoubleFace = false);

    /**
     * Method to add a quad representing a surfel given from its center and its orientation.
     *
     * @param baseQuadCenter the surfel center.
     * @param xSurfel indicates that the sufel is in the x axis direction
     * @param ySurfel indicates that the sufel is in the y axis direction
     * @param zSurfel indicates that the sufel is in the z axis direction
     *
     **/
    void addQuadFromSurfelCenter(const RealPoint &baseQuadCenter, 
                                 bool xSurfel, bool ySurfel, bool zSurfel);



    /**
     * Method to add a quad representing a surfel given from its
     * center and its orientation, and attach a unitary normal vector
     * to it.  Depending on @a enableReorientation, Quad points can be
     * reordered to make its orientation constistant with the normal
     * direction.
     *
     * @param baseQuadCenter the surfel center.
     * @param xSurfel indicates that the sufel is in the x axis direction
     * @param ySurfel indicates that the sufel is in the y axis direction
     * @param zSurfel indicates that the sufel is in the z axis
     * direction
     * @param aNormal a unitary normal vector to attach to the quad.
     * @param enableReorientation if true,  the quad orientation will
     * match with prescribed normal vector (dot product between the
     * normal and the canonical one is >0).
     * @param sign if enableReorientation is true, we use this bool to
     * get the surfel sign
     * @param enableDoubleFace if true, two quad (with opposite normal
     * vector) will be drawn.
     *
     **/
    void addQuadFromSurfelCenterWithNormal(const RealPoint &baseQuadCenter, bool xSurfel, bool ySurfel, bool zSurfel,
                                           const RealVector &aNormal,
                                           const bool enableReorientation,
                                           const bool sign,
                                           const bool enableDoubleFace = false);


    /**
     * Method to add a specific quad (used by @a addClippingPlane). The normal is computed from the vertex order.
     * @param p1 the 1st point
     * @param p2 the 2nd point
     * @param p3 the 3rd point
     */
    void addTriangle(const RealPoint &p1, const RealPoint &p2, const RealPoint &p3);


    /**
     * Method to add a specific polygon.
     * @param vertices a vector containing the polygon vertices.
     */
    void addPolygon(const std::vector<RealPoint> &vertices);


    /**
     * Method to add a line to the current display.
     * x1, y1, z1, x2, y2, z2 the two extremty line points.
     * @param p1 the 1st point
     * @param p2  the 2nd point
     * @param width the line width
     *
     */

    void addLine(const RealPoint &p1, const RealPoint &p2, const double width=0.03);


    /**
     * Method to add specific cube. It includes several modes to
     * display the cube with and without the wire visualisation.
     *
     * @param center cube center
     * @param width the cube width.
     */
    void addCube(const RealPoint &center, double width=1.0);


    /**
     * Method to add a point to the current display.
     * @param center ball center x
     * @param radius the ball radius (default 0.5)
     * @param resolution ball resolution (default 30)
     *
     */
    void addBall(const RealPoint &center ,
                 const double radius=0.5,
                 const unsigned int resolution = 30);



    /**
     * Specific to display a surfel from Kahlimsky space. The display can
     * take into accounts the sign of the cell.
     * @param baseQuadCenter  base quad center point
     * @param xSurfel true if the surfel has its main face in the direction of the x-axis
     * @param ySurfel true if the surfel has its main face in the direction of the y-axis
     * @param zSurfel true if the surfel has its main face in the direction of the z-axis
     * @param sizeShiftFactor set the distance between the display of the surfel and potential Cube.
     * @param sizeFactor set the difference between the upper face of the prism and the down face
     * @param isSigned to specify if we want to display an signed or unsigned Cell.
     * @param aSign if @a isSigned is true it will be used to apply a different displays
     * according this boolean parameter (if @a aSign=true oriented in the direct axis orientation)
     */
    void addPrism(const RealPoint &baseQuadCenter,
                        bool xSurfel, bool ySurfel, bool zSurfel, double sizeShiftFactor,
                        double sizeFactor=1.0, bool isSigned= false, bool aSign=true);



    /**
     * Specific to display a surfel from Kahlimsky space from a basic way.
     *
     * @param baseQuadCenter  base quad center point
     * @param xSurfel true if the surfel has its main face in the direction of the x-axis
     * @param ySurfel true if the surfel has its main face in the direction of the y-axis
     * @param zSurfel true if the surfel has its main face in the direction of the z-axis
     */
    void addBasicSurfel(const RealPoint &baseQuadCenter,
                        bool xSurfel, bool ySurfel, bool zSurfel);


    /**
     * Add a signed KSLinel from the Kahlimsky space. Display it as a cone.
     *
     * @param p1  the cone apex
     * @param p2  the cone base
     * @param width the width of the cone (default= 0.08)
     */
    void addCone(const RealPoint &p1, const RealPoint &p2,
                 double width=0.08);


    /**
     * Add a non signed KSLinel from the Kahlimsky space. Display it as a simple cylinder.
     * @param p1  the 1st point
     * @param p2  the 2nd point
     * @param width the width of the cylinder (default= 0.02)
     */
    void addCylinder(const RealPoint  &p1, const RealPoint &p2,
                     const double width=0.02);


    /**
     * Used to update the scene bounding box when objects are added.
     *
     * @param point the point to be taken into accounts.
     */
    void updateBoundingBox(const RealPoint &point);




    /**
     * Export as Mesh the current displayed elements.
     *
     * @param aMesh : (return) the mesh containing the elements of the display.
     *
     **/
    void exportToMesh(Mesh<RealPoint> & aMesh ) const;


    /**
     * Draws the drawable [object] in this board. It should satisfy
     * the concept CDrawableWithViewer3D, which requires for instance a
     * method setStyle( Viewer3D & ).
     *
     * @param object any drawable object.
     * @return a reference on 'this'.
     */
    template <typename TDrawableWithDisplay3D>
    Display3D & operator<<( const TDrawableWithDisplay3D & object );



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
     * Removes all sent data.
     */
    void clear();



    /**
     * Use to embed a DGtal point into space
     * @param dp a DGtal Point
     * @return the point embeded in real space
     */
    RealPoint embed(const typename Space::Point & dp) const ;

    /**
     * Use to embed a signed DGtal kahlimsky cell into space
     * @param cell a kahlimsky cell
     * @return the cell embeded in real space
     */
    RealPoint embedKS( const typename KSpace::SCell & cell ) const;


    /**
     * Use to embed a signed DGtal kahlimsky cell into space
     * @param aTrans a transformed surfel prism
     * @return the cell embeded in real space
     */
    RealPoint embedKS( const DGtal::TransformedPrism& aTrans ) const;


    /**
     * Use to embed an unsigned DGtal kahlimsky cell into space
     * @param cell kahlimsky cell
     * @return the point embeded in real space
     */
    RealPoint embedK( const typename KSpace::Cell & cell ) const;

    //---end interface

    // ------------------------- Protected Datas ------------------------------
  public:

    /**
     * The associated map type for storing possible modes used for
     * displaying for digital objects.
     */
    typedef std::map< std::string, std::string > ModeMapping;

    /**
     * The associated map type for storing the default styles of
     * digital objects.
     */
    typedef std::map< std::string,CountedPtr<DrawableWithDisplay3D> > StyleMapping;


    ModeMapping myModes;
    /**
     * For instance, may associate a new style object T1 to the class
     * "HyperRectDomain": myStyles[ "HyperRectDomain" ] = T1.
     *
     * One can also store a new style T2 for a specific mode used for
     * drawing a class: myStyles[ "HyperRectDomain/Paving" ] = T2.
     *
     * Modes may only be used in objects implementing the concept
     * CDrawableWithBoard2D.
     */
    StyleMapping myStyles;

    /// True if the bounding box is empty (no objects added)
    bool myBoundingPtEmptyTag;
    ///upper point of the bounding box
    double myBoundingPtUp [3];
    /// lower point of the bouding box
    double myBoundingPtLow [3];

  protected:
    //the current fill color of the display
    DGtal::Color myCurrentFillColor;
    //the current line color of the display
    DGtal::Color myCurrentLineColor;

    /// Used to specialized visualisation with KSpace surfels/cubes.
    ///
    double myCurrentfShiftVisuPrisms;

    /// Used to represent all the list of line primitive
    ///
    std::vector< std::vector<LineD3D> > myLineSetList;

    /// Used to represent all the list of point primitive
    ///
    std::vector< std::vector<BallD3D> > myBallSetList;

    /// Represent all the clipping planes added to the scene (of maxSize=5).
    ///
    std::vector< ClippingPlaneD3D > myClippingPlaneList;

    /// Represent truncated prism object to represent surfels of Khalimsky space (used to display Khalimsky Space Cell)
    ///
    std::vector< QuadD3D > myPrismList;

    /// Represents all the planes drawn in the Display3D or to display
    /// Khalimsky Space Cell.  The map int --> vector< QuadD3D>
    /// associates a vector of quads to an integer identifier
    /// (OpenGL name)
    QuadsMap myQuadsMap;

    /// Represents all the triangles drawn in the Display3D
    std::vector<std::vector< TriangleD3D > > myTriangleSetList;

    /// Represents all the polygon drawn in the Display3D
    std::vector<std::vector<PolygonD3D> > myPolygonSetList;


    /// Represents all the cubes drawn in the Display3D.  The map int
    /// --> vector<CubeD3D> associates  a vector of cubes to an
    /// integer identifier (OpenGL name)
    CubesMap myCubesMap;


    /// names of the lists in myCubeSetList
    ///
    std::vector<std::string> myCubeSetNameList;

    /// names of the lists in myLineSetList
    ///
    std::vector<std::string> myLineSetNameList;

    /// names of the lists in myBallSetList
    ///
    std::vector<std::string> myBallSetNameList;
    /// names of the lists in myClippingPlaneList
    ///
    std::vector<std::string> myClippingPlaneNameList;

    /// names of the lists in myPrismList
    ///
    std::vector<std::string> myPrismNameList;

    /// names of the lists in myQuadList
    ///
    std::vector<std::string> myQuadSetNameList;

    /// names of the lists in myTriangleList
    ///
    std::vector<std::string> myTriangleSetNameList;

    /// names of the lists in myPolygonList
    ///
    std::vector<std::string> myPolygonSetNameList;

    /// the "OpenGL name", used for instance by QGLViewer for selecting objects.
    ///
    DGtal::int32_t myName3d;

    /// Stores the callback functions called when selecting a graphical object.
    ///
    std::set<SelectCallbackFctStore> mySelectCallBackFcts;

    bool myBoundingPtChangedTag = false;

    //----end of protected datas

    // ------------------------- Internals ------------------------------------
  protected:

    /**
     * Calculate the cross product of two 3d vectors and return it.
     * @param dst destination vector.
     * @param srcA source vector A.
     * @param srcB source vector B.
     */
    static void cross (double dst[3], double srcA[3], double srcB[3]);

    /**
     * Normalize the input 3d vector.
     * @param vec source & destination vector.
     */
    static void normalize (double vec[3]);


  }; // end of class Display3D

  /**
   * Overloads 'operator<<' for displaying objects of class 'Display3D'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Display3D' to write.
   * @return the output stream after the writing.
   */
  template <typename Space , typename KSpace >
  std::ostream&
  operator<< ( std::ostream & out, const DGtal::Display3D<Space , KSpace > & object );


  template <typename Space , typename KSpace >
  /**
   * Operator ">>" to export a Display3D into a Mesh
   * @param aDisplay3D the Display3D to be exported.
   * @param aMesh (return) the resulting mesh.
   *
   **/
  void
  operator>> ( const Display3D<Space , KSpace > &aDisplay3D,
               DGtal::Mesh< typename Display3D<Space , KSpace >::RealPoint > &aMesh);


  /**
   * Operator ">>" to export a Display3D directly a file
   * @param aDisplay3D the Display3D to be exported.
   * @param aFilename (return) the resulting mesh.
   *
   **/
  template < typename Space , typename KSpace >
  void
  operator>> ( const Display3D< Space , KSpace > &aDisplay3D, std::string aFilename);


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/Display3D.ih"


// //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Display3D_h

#undef Display3D_RECURSES
#endif // else defined(Display3D_RECURSES)
