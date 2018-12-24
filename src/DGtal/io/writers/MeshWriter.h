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
 * @file  MeshWriter.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2012/07/08
 *
 * Header file for module  MeshWriter
 *
 * This file is part of the DGtal library.
 */

#if defined(MeshWriter_RECURSES)
#error Recursive header files inclusion detected in MeshWriter.h
#else // defined(MeshWriter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MeshWriter_RECURSES

#if !defined MeshWriter_h
/** Prevents repeated inclusion of headers. */
#define MeshWriter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <string>
#include <boost/static_assert.hpp>
#include "DGtal/base/Common.h"
#include "DGtal/shapes/Mesh.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class MeshWriter
  /**
   * Description of template struct 'MeshWriter' <p>
   * \brief Aim: Export a Mesh (Mesh object) in different format as OFF and OBJ).
   * 
   * The exportation can be done automatically according the input file
   * extension with the ">>" operator  
   * 
   * Example of typical use: 
   * First you have to add the following include files:
   * @snippet tests/io/writers/testMeshWriter.cpp MeshWriterUseIncludes
   * Then you create a simple Mesh object:
   * @snippet tests/io/writers/testMeshWriter.cpp MeshWriterUseMeshCreation
   * Finally you can export directly the Mesh object: 
   * @snippet tests/io/writers/testMeshWriter.cpp MeshWriterUseMeshExport
   *
   *
   * @see Mesh MeshWriter
   *
   *
   */
  template <typename TPoint>
  struct MeshWriter
  {
    // ----------------------- Standard services ------------------------------

   


    /** 
     * Export Mesh towards a OFF format. By default the face colors are
     * exported (if they are stored in the Mesh object). 
     * 
     * @param out the output stream of the exported OFF object.
     * @param aMesh the Mesh object to be exported.
     * @param exportColor true to try to export the face colors if they are stored in the Mesh object (default true). 
     * @return true if no errors occur.
     */
    
    static bool export2OFF(std::ostream &out, const  Mesh<TPoint>  &aMesh, 
                           bool exportColor=true);
  
  


    /** 
     * Export a Mesh towards a OBJ format (colors are exported).
     * 
     * @param out the output stream of the exported OBJ object.
     * @param aMesh the Mesh object to be exported.
     * @return true if no errors occur.
     */
    
    static bool export2OBJ(std::ostream &out, const  Mesh<TPoint>  &aMesh);

    /** 
     * Export a Mesh towards a OBJ format including face colors.
     * 
     * @param[out] out the output stream of the exported OBJ object.
     * @param[out] outMTL the output stream associated to the material file.
     * @param[in] nameMTLFile the file name of the material file.
     * @param[in] aMesh the Mesh object to be exported.
     * @return true if no errors occur.
     */
    
    static bool export2OBJ_colors(std::ostream &out, std::ostream &outMTL,
                                  const std::string nameMTLFile,
                                  const  Mesh<TPoint>  &aMesh);
    
    
  };
  




  /**
   *  'operator>>' for exporting objects of class 'Mesh'.
   *  This operator automatically selects the good method according to
   *  the filename extension (off, obj).
   *  
   * @param aMesh the mesh to be exported.
   * @param aFilename the filename of the file to be exported. 
   * @return true, if the export was successful. 
   */
  template <typename TPoint>
  bool
  operator >> (  Mesh<TPoint> & aMesh,  const std::string & aFilename  );
  




  /**
   *  'operator>>' for exporting objects of class 'Mesh' in OFF format.
   *  
   * @param aMesh the mesh to be exported.
   * @param out the output of the OFF exportation. 
   * @return true, if the export was successful. 
   */
  template <typename TPoint>
  bool
  operator >> (  Mesh<TPoint> & aMesh, std::ostream &out );
  



  

			   
}//namespace

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/writers/MeshWriter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined MeshWriter_h

#undef MeshWriter_RECURSES
#endif // else defined(MeshWriter_RECURSES)
