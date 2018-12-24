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
 * @file MeshHelpers.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2017/02/11
 *
 * Header file for module MeshHelpers.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(MeshHelpers_RECURSES)
#error Recursive header files inclusion detected in MeshHelpers.h
#else // defined(MeshHelpers_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MeshHelpers_RECURSES

#if !defined MeshHelpers_h
/** Prevents repeated inclusion of headers. */
#define MeshHelpers_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/topology/CCellEmbedder.h"
#include "DGtal/topology/CDigitalSurfaceContainer.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/shapes/TriangulatedSurface.h"
#include "DGtal/shapes/PolygonalSurface.h"
#include "DGtal/shapes/Mesh.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class MeshHelpers
  /**
   * Description of template class 'MeshHelpers' <p>
   * \brief Aim: Static class that provides builder and converters between meshes.
   */
  class MeshHelpers
  {
    // ----------------------- Static services ------------------------------
  public:
    /// Builds a triangulated surface (class TriangulatedSurface) from
    /// a mesh (class Mesh). Note that a triangulated surface contains
    /// only triangles, so polygonal faces (0,1,2,3,4,...) of the
    /// input mesh are (naively) triangulated (triangles (0,1,2),
    /// (0,2,3), (0,3,4), etc). Furthermore, the output triangulated
    /// surface rebuilds a topology between faces.
    ///
    /// @tparam Point the type for points.
    /// @param[in]  mesh the input mesh.
    /// @param[out] trisurf the output triangulated surface mesh.
    ///
    /// @return 'true' on success, 'false' if the input \a mesh was
    /// not a combinatorial surface.
    template <typename Point>
      static
      bool mesh2TriangulatedSurface
      ( const Mesh<Point>& mesh,
        TriangulatedSurface<Point>& trisurf );

    /// Builds a polygon mesh (class PolygonalSurface) from
    /// a mesh (class Mesh). The output polygonal
    /// surface rebuilds a topology between faces.
    ///
    /// @tparam Point the type for points.
    /// @param[in]  mesh the input mesh.
    /// @param[out] polysurf the output polygonal surface mesh.
    ///
    /// @return 'true' on success, 'false' if the input \a mesh was
    /// not a combinatorial surface.
    template <typename Point>
      static
      bool mesh2PolygonalSurface
      ( const Mesh<Point>& mesh,
        PolygonalSurface<Point>& polysurf );

    /// Builds a polygonal surface from a triangulated
    /// surface. Polygonal faces are triangulated according to \a
    /// centroid: when 'true', creates a vertex in each non triangular
    /// face, otherwise creates triangles (0,i,i+1) in face (0, 1,
    /// ..., n) for i < n-1.
    ///
    /// @tparam Point the type for points.
    /// @param[in]  polysurf the input polygonal surface mesh.
    /// @param[out] trisurf the output triangulated surface.
    ///
    /// @param[in] centroid when 'true' creates a vertex in the middle
    /// of non triangular faces and a fan around it, otherwise naively
    /// subdivides the face as a fan around the first vertex.
    ///
    /// @note The vertices of \a trisurf are the same as the one of \a
    /// polysurf, except if there are newly created vertices (centroid
    /// case) which are put at the end.
    ///
    /// @note Be \b very \b careful \b with \b "Naive" \b subdivision,
    /// since it may create non-manifold edges on general polygonal
    /// surfaces. Indeed, take the closed surface made of faces (0, 1,
    /// 2, 3) and (3, 2, 1, 0). Depending on how faces are
    /// triangulated, it is still a valid combinatorial triangulated
    /// 2-manifold (e.g. (0,1,2,3) gives (0,1,2) and (2,0,3) and
    /// (3,2,1,0) gives (3,2,1) and (1,3,0)) or a non-valid one
    /// (e.g. (0,1,2,3) gives (0,1,2) and (2,0,3) and (3,2,1,0) gives
    /// (3,2,0) and (0,2,1): then edge {2,0} is shared by four faces).
    template <typename Point>
      static
      void polygonalSurface2TriangulatedSurface
      ( const PolygonalSurface<Point>& polysurf,
        TriangulatedSurface<Point>&    trisurf,
        bool  centroid = true );

    /// Builds a triangulated surface (class TriangulatedSurface) from
    /// the dual graph of a 2-dimensional digital surface in K^3 (class
    /// DigitalSurface).
    ///
    /// @note that a triangulated surface contains only triangles, so
    /// faces of the input dual graph of the digital surface mesh are
    /// triangulated by adding a new vertex at the barycenter of the
    /// face vertices.
    ///
    /// @tparam DigitalSurfaceContainer the container chosen for the digital surface.
    /// @tparam CellEmbedder the embedder chosen for the digital surface.
    ///
    /// @param[in]  dsurf the input digital surface.
    /// @param[in]  cembedder the embedder for 2-cells of the digital surface, which are vertices in the output triangulated surface.
    /// @param[out] trisurf the output triangulated surface mesh.
    /// @param[out] vertexmap the output mapping between a Vertex of \a dsurf and an Index in \a trisurf.
    template < typename DigitalSurfaceContainer,
      typename CellEmbedder,
      typename VertexMap >
      static
      void digitalSurface2DualTriangulatedSurface
      ( const DigitalSurface<DigitalSurfaceContainer>& dsurf,
        const CellEmbedder& cembedder,
        TriangulatedSurface<typename CellEmbedder::Value>& trisurf,
        VertexMap& vertexmap );

    /// Builds a polygonal surface (class PolygonalSurface) from
    /// the dual graph of a 2-dimensional digital surface in K^3 (class
    /// DigitalSurface).
    ///
    /// @tparam DigitalSurfaceContainer the container chosen for the digital surface.
    /// @tparam CellEmbedder the embedder chosen for the digital surface.
    ///
    /// @param[in]  dsurf the input digital surface.
    /// @param[in]  cembedder the embedder for 2-cells of the digital surface, which are vertices in the output polygonal surface.
    /// @param[out] polysurf the output polygonal surface mesh.
    /// @param[out] vertexmap the output mapping between a Vertex of \a dsurf and an Index in \a polysurf.
    template < typename DigitalSurfaceContainer,
      typename CellEmbedder,
      typename VertexMap >
      static
      void digitalSurface2DualPolygonalSurface
      ( const DigitalSurface<DigitalSurfaceContainer>& dsurf,
        const CellEmbedder& cembedder,
        PolygonalSurface<typename CellEmbedder::Value>& polysurf,
        VertexMap& vertexmap );

    /// Builds a polygonal surface (class PolygonalSurface) from
    /// the primal graph of a 2-dimensional digital surface in K^3 (class
    /// DigitalSurface).
    ///
    /// @tparam DigitalSurfaceContainer the container chosen for the digital surface.
    /// @tparam CellEmbedder the embedder chosen for the digital surface.
    /// @tparam CellMap the type for encoding the map 0-cell -> Index.
    ///
    /// @param[in]  dsurf the input digital surface.
    /// @param[in]  cembedder the embedder for 0-cells of the digital surface, which are vertices in the output polygonal surface.
    /// @param[out] polysurf the output polygonal surface mesh.
    /// @param[out] cellmap the output mapping between a 0-cell of \a dsurf and an Index in \a polysurf.
    /// @return 'true' if it was able to build the primal polygonal surface, otherwise the digital surface was not a combinatorial 2-manifold and is not valid.
    template < typename DigitalSurfaceContainer,
      typename CellEmbedder,
      typename CellMap >
      static
      bool digitalSurface2PrimalPolygonalSurface
      ( const DigitalSurface<DigitalSurfaceContainer>& dsurf,
        const CellEmbedder& cembedder,
        PolygonalSurface<typename CellEmbedder::Value>& polysurf,
        CellMap& cellmap );
    
    
    /// Builds a mesh (class Mesh) from a triangulated surface (class
    /// TriangulatedSurface). Note that the mesh looses the topology
    /// of the triangulated surface, since it is essentially a soup of
    /// triangles.
    ///
    /// @tparam Point the type for points.
    /// @param[in]  trisurf the input triangulated surface mesh.
    /// @param[in,out] mesh the output mesh (which should be empty).
    template <typename Point>
      static
      void triangulatedSurface2Mesh
      ( const TriangulatedSurface<Point>& trisurf,
        Mesh<Point>& mesh );

    /// Builds a mesh (class Mesh) from a polygon mesh (class
    /// PolygonalSurface). Note that the mesh looses the topology
    /// of the polygonal surface, since it is essentially a soup of
    /// triangles.
    ///
    /// @tparam Point the type for points.
    /// @param[in]     polysurf the input polygonal surface (ie a polygon mesh).
    /// @param[in,out] mesh the output mesh (which should be empty).
    template <typename Point>
      static
      void polygonalSurface2Mesh
      ( const PolygonalSurface<Point>& polysurf,
        Mesh<Point>& mesh );

    /// Exports a triangulated surface as an OBJ file (with topology)
    /// into the given output stream.
    ///
    /// @tparam Point the type for points.
    /// @param[in,out] output an output stream
    /// @param[in]     trisurf the input triangulated surface mesh.
    template <typename Point>
      static
      bool exportOBJ
      ( std::ostream& output,
        const TriangulatedSurface<Point>& trisurf );

    /// Exports a polygonal surface as an OBJ file (with topology)
    /// into the given output stream.
    ///
    /// @tparam Point the type for points.
    /// @param[in,out] output an output stream
    /// @param[in]     polysurf the input polygonal surface mesh.
    template <typename Point>
      static
      bool exportOBJ
      ( std::ostream& output,
        const PolygonalSurface<Point>& polysurf );


    /// Exports a triangulated or polygonal surface as an OBJ file
    /// (with topology) into the given output stream. It can also
    /// specifies normals per face and colors per face.
    ///
    /// @tparam TTriangulatedOrPolygonalSurface either some TriangulatedSurface or some PolygonalSurface.
    /// @param[in,out] output_obj an output stream where the OBJ file is written.
    /// @param[in]     mtl_filename the name of the material filename (stores colors).
    /// @param[in]     polysurf the input triangulated or polygonal surface mesh.
    /// @param[in]     normals either empty or a vector of size `polysurf.nbFaces` specifying the normal vector for each face.
    /// @param[in]     diffuse_colors either empty or a vector of size `polysurf.nbFaces` specifying the diffuse color for each face.
    /// @param[in]     ambient_color the ambient color of all faces.
    /// @param[in]     diffuse_color the diffuse color of all faces if \a diffuse_colors was empty.
    /// @param[in]     specular_color the specular color of all faces.
    template <typename TTriangulatedOrPolygonalSurface>
      static
      bool exportOBJwithFaceNormalAndColor
      ( std::ostream& output_obj,
        const std::string&             mtl_filename,
        const TTriangulatedOrPolygonalSurface& polysurf,
        const std::vector< typename TTriangulatedOrPolygonalSurface::Point >&    normals,
        const std::vector< Color >&    diffuse_colors,
        const Color&                   ambient_color  = Color( 32, 32, 32 ),
        const Color&                   diffuse_color  = Color( 200, 200, 255 ),
        const Color&                   specular_color = Color::White );

    
    /// Exports a new material in a MTL stream.
    ///
    /// @param[in,out] output_mtl an output stream into a MTL file
    /// @param[in]     idxMaterial the index of the new material.
    /// @param[in]     ambient_color the ambient color for the material.
    /// @param[in]     diffuse_color the diffuse color for the material.
    /// @param[in]     specular_color the specular color for the material.
    static
      bool exportMTLNewMaterial
      ( std::ostream& output_mtl,
        unsigned int idxMaterial,
        const Color& ambient_color,
        const Color& diffuse_color,
        const Color& specular_color );

  }; // end of class MeshHelpers

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/MeshHelpers.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined MeshHelpers_h

#undef MeshHelpers_RECURSES
#endif // else defined(MeshHelpers_RECURSES)
