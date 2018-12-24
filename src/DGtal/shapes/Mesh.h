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
 * @file Mesh.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2012/06/29
 *
 * Header file for module Mesh.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Mesh_RECURSES)
#error Recursive header files inclusion detected in Mesh.h
#else // defined(Mesh_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Mesh_RECURSES

#if !defined Mesh_h
/** Prevents repeated inclusion of headers. */
#define Mesh_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/io/Color.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  
  /////////////////////////////////////////////////////////////////////////////
  // template class Mesh
  /**
   * Description of template class 'Mesh' <p> \brief Aim: This class
   * is defined to represent a surface mesh through a set of vertices
   * and faces.  By using the default constructor, the mesh does not
   * store any color information (it can be changed  by setting the default
   * constructor parameter saveFaceColor to 'true').
   *
   * The mesh object stores explicitly each vertex and each face are
   * represented with the list of point index.
   *
   * @note This class is a preliminary version of a mesh strucuture
   * (the method to access neigborhing facets or to a given facet are
   * not yet given)
   *
   * This class was defined to import and display a mesh from different formats like OFF file format. 
   * Since it realized the concept of CDrawableWithDisplay3D we can display an Mesh with a Display3D object:
   *
   * First we have to include the following header files:
   @snippet examples/shapes/mesh3DConstructionAndVisualisation.cpp MeshUseInclude 
   *
   * Prepare display using QGLviewer: Viewer3D
   @snippet examples/shapes/mesh3DConstructionAndVisualisation.cpp MeshUseInitDisplay 
   *
   * Construct a Mesh with various faces:
   @snippet examples/shapes/mesh3DConstructionAndVisualisation.cpp MeshUseMeshCreation
   
   * Displaying the result:
   @snippet examples/shapes/mesh3DConstructionAndVisualisation.cpp MeshUseDisplay
   *
   * 
   *
   * @see  MeshReader MeshWriter  .
   *
   */
  template <typename TPoint >
  class Mesh
  {   

    
    // ----------------------- associated types ------------------------------
  public:

    
    /**
     * Main type associated to the mesh vertices.
     **/    
    typedef TPoint Point;    

    
    
    /**
     * Type to represent real points which can be obtained from  various methods (like getFaceBarycenter).
     **/    
    typedef  typename DGtal::PointVector<TPoint::dimension, double> RealPoint;

    
    /**
     * Structure for representing the faces from the vertex index.
     **/

    typedef std::vector<unsigned int> MeshFace;
    
    
    /**
     * Define the type to store each mesh vertex. 
     **/
    typedef  std::vector<TPoint> VertexStorage; 
    
    /**
     * Define the type to store the faces of the mesh. 
     **/
    typedef  std::vector<MeshFace> FaceStorage; 

    /**
     * Define the type to store the color associated to each face
     **/
    typedef  std::vector<DGtal::Color> ColorStorage; 
     

    /**
     * Define the type of the const iterator on vertex.
     **/
    typedef typename VertexStorage::const_iterator ConstIterator;

    /**
     * Define the type of the iterator on vertex.
     **/
    typedef typename VertexStorage::iterator Iterator;

    /**
     * Define the size type of the containers.
     **/
    typedef typename std::size_t Size;



    // ----------------------- Standard services ------------------------------
  public:
    /**
     * Constructor.
     * By default the constructed mesh does not store color information about the mesh.
     * If you want to include color in the Mesh object you have to set the constructor parameter saveFaceColor to true. 
     *
     * @param saveFaceColor used to memorize the color of a face (default= false) 
     */
    Mesh(bool saveFaceColor=false);    

    /**
     * Constructor.
     * The constructed mesh will store an unique default color information about the mesh.
     * 
     * @param aColor used to memorize the color of a face (default= false) 
     */
    Mesh(const DGtal::Color &aColor);    
    
    /**
     * Constructor by usung a vertex set as init.
     * The color are not stored in this case.
     * @param vertexSet the set of vertex. 
     */    
    Mesh(const std::vector<TPoint> &vertexSet);

    /**
     * Destructor.
     */
    ~Mesh();

   /**
     * Copy constructor.
     * @param other the object to clone.
     */
    Mesh ( const Mesh & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    Mesh & operator= ( const Mesh & other );



    // --------------- CDrawableWithDisplay3D  realization -------------------
  public:    
    
    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;



    
    // ----------------------- Interface --------------------------------------
  public:
    
    
    /**
     * Adding new vertex.
     *
     **/
    void addVertex(const TPoint &vertex);
      
    
  
    /**
     * Add a triangle face given from index position.
     *
     * @param indexVertex1 the index of the first vertex face.
     * @param indexVertex2 the index of the second vertex face.
     * @param indexVertex3 the index of the third vertex face.
     * @param aColor       the triangle face color.
     * 
     * @note If you want to follow the OBJ format convention, you have
     * to order the vertices in CCW (to have the correct normal orientation).
     *
     **/    
    void addTriangularFace(unsigned int indexVertex1, unsigned int indexVertex2, unsigned int indexVertex3, 
			   const DGtal::Color &aColor=DGtal::Color::White);


    /**
     * Add a quad face given from index position.
     *
     * @param indexVertex1 the index of the first vertex face.
     * @param indexVertex2 the index of the second vertex face.
     * @param indexVertex3 the index of the third vertex face.
     * @param indexVertex4 the index of the fourth vertex face.
     * @param aColor       the quad face color.
     *
     * @note If you want to follow the OBJ format convention, you have
     * to order the vertices in CCW (to have the correct normal orientation).
     *
     **/    
    void addQuadFace(unsigned int indexVertex1, unsigned int indexVertex2, 
		     unsigned int indexVertex3, unsigned int indexVertex4,
		     const DGtal::Color & aColor=DGtal::Color::White);
    
    
   /**
    * Add a quad face given from index position.
    *
    * @note If you want to follow the OBJ format convention, you have
    * to order the vertices of the face in CCW (to have the correct
    * normal orientation).
    * 
    **/    
    void addFace(const MeshFace &aFace, const DGtal::Color &aColor=DGtal::Color::White);
    

    /**
     * Remove faces from the mesh. @note the vertexes which are no
     * more associated to any face are also removed.
     * 
     * @param[in] facesIndex the index of the face to be removed.
     **/
    void removeFaces(const std::vector<unsigned int>  &facesIndex);
   
 
    /**
     * @param i the index of the vertex.
     * @return a const reference to the vertex of index i. 
     **/
    const TPoint & getVertex(unsigned int i) const;

    /**
     * @param i the index of the vertex.
     * @return a reference to the vertex of index i. 
     **/
    TPoint & getVertex(unsigned int i);
    
    
    
    /**
     * @param i the index of the face.
     * @return a const reference to the face of index i. 
     **/
    const MeshFace & getFace(unsigned int i) const;


    /**
     * @param i the index of the face.
     * @return barycenter (RealPoint) of the face of index i.
     **/
    RealPoint getFaceBarycenter(unsigned int i) const;    


    
    /**
     * @param i the index of the face.
     * @return a const reference to the face of index i. 
     **/
    MeshFace & getFace(unsigned int i);
    


    /**
     * Return a reference to a  face Color of index i.
     * @param i the index of the face.
     * @return the color of the face of index i. 
     **/
    const Color & getFaceColor(unsigned int i) const;



    /**
     * @return the bounding box of the mesh represented as a pair of points.
     **/
    std::pair<TPoint, TPoint>  getBoundingBox() const;


    /**
     *  Set the color of a particular face of the mesh. If the mesh
     *  does not yet store the color of all individual faces
     *  (isStoringFaceColors to false) it fills each face color with
     *  the default color and the value of isStoringFaceColors is set
     *  to true.
     *
     * @param[in] i the index of the face
     * @param[in] aColor the color for the considered face.
     *
     **/

    void setFaceColor(unsigned int i, const DGtal::Color &aColor) ; 
    

    /**
     * @return true if the Mesh is storing a color for each faces. 
     * 
     **/
    bool isStoringFaceColors() const;


    /**
     * @return an const_iterator pointing to the first vertex of the mesh.  
     * 
     **/
    ConstIterator 
    vertexBegin() const {
      return myVertexList.begin();
    }
    
    
    /**
     * @return an const_iterator pointing after the end of the last vertex of the mesh.
     *
     **/
    ConstIterator 
    vertexEnd() const {
      return myVertexList.end();
    }


    /**
     * @return an iterator pointing to the first vertex of the mesh.  
     * 
     **/
    Iterator
    vertexBegin()  {
      return myVertexList.begin();
    }
    
    

    /**
     * @return an iterator pointing after the end of the last vertex of the mesh.
     *
     **/
    Iterator
    vertexEnd()  {
      return myVertexList.end();
    }

    
    
    /**
     * @return a const iterator pointing to the first face of the mesh.  
     *
     **/
    
    FaceStorage::const_iterator 
    faceBegin() const {
      return myFaceList.begin();
    }
    


    /**
     * @return a const iterator pointing after the end of the last face of the mesh.
     *
     **/
    
    FaceStorage::const_iterator 
    faceEnd() const {
      return myFaceList.end();
    }    
    

    /**
     * @return a const iterator pointing to the first face of the mesh.  
     *
     **/
    
    FaceStorage::iterator 
    faceBegin()  {
      return myFaceList.begin();
    }
    


    /**
     * @return a const iterator pointing after the end of the last face of the mesh.
     *
     **/
    
    FaceStorage::iterator 
    faceEnd()  {
      return myFaceList.end();
    }    
    
    

    /**
     * Return the number of faces contained on the mesh object.
     * @return the number of faces.
     **/
    Size nbFaces() const;

    /**
     * Return the number of faces contained on the mesh object.
     * @return the number of faces.
     **/
    Size  nbVertex() const;
    
    
    
    /**
     * Invert the face order (useful when normal is deducted from vertex order).
     *
     **/    
    void invertVertexFaceOrder();
    
    /**
     * Clear all faces of the mesh.
     **/
    void clearFaces();
    
    /**
     * Change the scale of the mesh (i.e all vertex coordinates are multiplied by a given factor aScale).
     * @param[in] aScale the scale factor. 
     **/
    void changeScale(const double aScale);
    
    /**
     * SubDivide triangular mesh if triangle area is less than the given parameter.
     * @param[in] minArea the minimum area factor. 
     * @return the new max triangle area.
     **/
    double subDivideTriangularFaces(const double minArea);
    
    /**
     * Transform quad faces of the mesh to triangular one.
     * @return the number of quads which were transformed.
     **/
    unsigned int quadToTriangularFaces();
        
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
    FaceStorage  myFaceList;
    VertexStorage myVertexList;    
    ColorStorage myFaceColorList;
    bool mySaveFaceColor;
    DGtal::Color myDefaultColor;
    

    

  
    // ------------------------- Mesh generation ------------------------------

  public:
    
    /**
     * Generates a tube mesh (of constant radius) from a set of points
     * representing the tube skeleton.  Each circular section is
     * connected with quads.  @note The vertices of circular sections
     * are associated from nearest point according to the tube
     * direction.
     *
     * @param[out] aMesh the mesh in which the new tube mesh will be created.
     * @param[in] aSkeleton the set of points which defines the tube skeleton.
     * @param[in] aRadius the tube radius.
     * @param[in] angleStep the circular precision of the tube approximation. 
     * @param[in] aMeshColor the color given to the generated tube mesh. 
     *
     **/
    static
    void
    createTubularMesh(Mesh<TPoint> &aMesh,  const std::vector<TPoint> &aSkeleton, const double aRadius, 
                      const double angleStep = 0.2, const DGtal::Color &aMeshColor = DGtal::Color::White );



    /**
     * Generates a tube mesh from a tube skeleton and from its
     * associated circular section radii. Each circular section is
     * connected with quads.   @note The vertices of circular sections
     * are associated from nearest point according to the tube
     * direction.
     *
     * @param[out] aMesh the mesh in which the new tube mesh will be created.
     * @param[in] aSkeleton the set of points which defines the tube skeleton.
     * @param[in] aVectOfRadius the vector containing all circular sections (if it contains not enougth it value, the next values will be taken from the begining of the vector).
     * @param[in] angleStep the circular precision of the tube approximation. 
     * @param[in] aMeshColor the color given to the generated tube mesh. 
     *
     **/
    static
    void
    createTubularMesh(Mesh<TPoint> &aMesh,  const std::vector<TPoint> &aSkeleton, const std::vector<double> &aVectOfRadius, 
                      const double angleStep = 0.2, const DGtal::Color &aMeshColor = DGtal::Color::White );

    /**
     * Generates a surface mesh defined from a sequence of 2D
     * height values (can be seen as a height map).
     *
     * @param[out] aMesh the mesh in which the new surface mesh will be created.
     * @param[in] anValueSequence the sequence of values defining the height
     *points.
     * @param[in] lengthSequence the number of points constituing a line in the
     *height map.
     * @param[in] stepX the x grid step to define the scale of the resulting
     *mesh.
     * @param[in] stepY the y grid step to define the scale of the resulting
     *mesh.
     * @param[in] stepZ the z grid step to define the scale of the resulting
     *mesh.
     *
     * @param[in] aMeshColor the color given to the generated tube mesh.
     *
     **/
    template <typename TValue>
    static
    void
    createMeshFromHeightSequence(Mesh<TPoint> &aMesh,  const std::vector<TValue> & anValueSequence, 
                                 const unsigned int lengthSequence,
                                 double stepX, double stepY, double stepZ, 
                                 const DGtal::Color &aMeshColor = DGtal::Color::White );
    
    
    




 

    // ------------------------- Internals ------------------------------------
  private:
    
    struct CompPoints
    {
      CompPoints(typename TPoint::Dimension d): myDim(d){};
      bool operator() (const TPoint &p1, const TPoint &p2){return p1[myDim]<p2[myDim];};
      typename TPoint::Dimension myDim;
    };
 

    
    




  }; // end of class Mesh


  /**
   * Overloads 'operator<<' for displaying objects of class 'Mesh'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Mesh' to write.
   * @return the output stream after the writing.
   */
  template <typename TPoint>
  std::ostream&
  operator<< ( std::ostream & out, const Mesh<TPoint> & object );



} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/Mesh.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Mesh_h

#undef Mesh_RECURSES
#endif // else defined(Mesh_RECURSES)
