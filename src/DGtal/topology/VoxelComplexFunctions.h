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
 * @file VoxelComplexFunctions.h
 * @author Pablo Hernandez-Cerdan (\c pablo.hernandez.cerdan@outlook.com)
 * Institute of Fundamental Sciences. Massey University.
 * Palmerston North, New Zealand
 *
 * @date 2018/01/01
 *
 * Defines functions associated to VoxelComplex.
 *
 * This file is part of the DGtal library.
 */

#if defined(VoxelComplexFunctions_RECURSES)
#error Recursive header files inclusion detected in VoxelComplexFunctions.h
#else // defined(VoxelComplexFunctions_RECURSES)
/** Prevents recursive inclusion of headers. */
#define VoxelComplexFunctions_RECURSES

#if !defined VoxelComplexFunctions_h
/** Prevents repeated inclusion of headers. */
#define VoxelComplexFunctions_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/topology/VoxelComplex.h"
//////////////////////////////////////////////////////////////////////////////
namespace DGtal
{
  namespace functions {

    template < typename TComplex >
    TComplex
    asymetricThinningScheme(
       TComplex & vc ,
       std::function<
       std::pair<typename TComplex::Cell, typename TComplex::Data> (
         const typename TComplex::Clique &)
       > Select ,
       std::function<
       bool(
         const TComplex & ,
         const typename TComplex::Cell & )
       > Skel,
       bool verbose = false
    );

    template < typename TComplex >
    TComplex
    persistenceAsymetricThinningScheme(
       TComplex & vc ,
       std::function<
       std::pair<typename TComplex::Cell, typename TComplex::Data> (
         const typename TComplex::Clique &)
       > Select ,
       std::function<
       bool(
         const TComplex & ,
         const typename TComplex::Cell & )
       > Skel,
       uint32_t persistence,
       bool verbose = false
    );
//////////////////////////////////////////////////////////////////////////////
// Select Functions
    /**
     * Select first voxel of input clique.
     *
     * @tparam TComplex input CubicalComplex
     * @param clique from where cell is chosen.
     *
     * @return first voxel of clique.
     */
    template < typename TComplex >
    std::pair<typename TComplex::Cell, typename TComplex::Data>
    selectFirst(
      const typename TComplex::Clique & clique);

    /**
     * Select random voxel from input clique.
     *
     * @tparam TComplex input CubicalComplex
     * @param clique from where cell is chosen.
     *
     * @return random voxel from input clique.
     */
    template < typename TComplex >
    std::pair<typename TComplex::Cell, typename TComplex::Data>
    selectRandom(
      const typename TComplex::Clique & clique);

    /**
     * Select random voxel from input clique.
     *
     * @tparam TComplex CubicalComplex
     * @tparam TRandomGenerator RandomGenerator
     * @param clique from where cell is chosen
     * @param gen random generator
     *
     * @return random voxel from input clique.
     */
    template < typename TComplex, typename TRandomGenerator >
    std::pair<typename TComplex::Cell, typename TComplex::Data>
    selectRandom(
      const typename TComplex::Clique & clique,
      TRandomGenerator & gen);

    /**
     * Select cell from clique that has max value looking at the input dist_map.
     * The points in the dist_map and in the clique must refer
     * to the same position.
     *
     * If you need to have a
     * std::function<bool(const Clique &)> signature
     * (for using it in thinning algorithms), use a lambda:
     * subsitute skelRandom (for example) for:
     * @code
     * auto selectDistMax =
     * [&dist_map](const Clique & clique){
     *     return selectMaxDistance<TDistMap, TComplex>(dist_map, clique);
     * }
     * @endcode
     *
     * @tparam TDistanceTransform Container type for the distance map.
     * @tparam TComplex input CubicalComplex
     * @param dist_map container holding the values.
     * @param clique from where cell is chosen.
     *
     * @return cell from input clique with highest value.
     *
     * @see DistanceTransformation.h
     */
    template < typename TDistanceTransform, typename TComplex >
    std::pair<typename TComplex::Cell, typename TComplex::Data>
    selectMaxValue(
      const TDistanceTransform & dist_map,
      const typename TComplex::Clique & clique);
//////////////////////////////////////////////////////////////////////////////
// Skeleton Functions
    /**
     * Always returns false.
     * Used in thinning schemes to calculate an ultimate skeleton.
     * An ultimate skeleton only keeps voxels that don't change the topology.
     *
     * @note The number of cells of a thinning using this function is the same
     * as the number of connected components of an object.
     *
     * @see asymetricThinningScheme
     *
     * @tparam TComplex VoxelComplex
     * @param vc input voxel complex.
     * @param cell c apply function on this voxel cell.
     *
     * @return always false.
     */
    template < typename TComplex >
    bool
    skelUltimate(
      const TComplex & vc,
      const typename TComplex::Cell & cell);

    /**
     * Check if input cell only has one neighbor, using @ref Object::topology.
     *
     * @tparam TComplex VoxelComplex
     * @param vc input voxel complex.
     * @param cell c apply function on this voxel cell.
     *
     * @return true if voxel cell only has neighbor.
     */
    template < typename TComplex >
    bool
    skelEnd(
      const TComplex & vc,
      const typename TComplex::Cell & cell);

    /**
     * Check if input cell is simple using @ref VoxelComplex::isSimple interface
     * to @ref Object::isSimple.
     *
     * @see VoxelComplex::isSimple
     * @see Object::isSimple
     *
     * @tparam TComplex VoxelComplex.
     * @param vc input complex.
     * @param cell apply function on input cell.
     *
     * @return true if voxel is simple.
     */
    template < typename TComplex >
    bool
    skelSimple(
      const TComplex & vc,
      const typename TComplex::Cell & cell);

    /**
     * Check if input cell is a 1 or 2 Isthmus.
     *
     * @tparam TComplex VoxelComplex.
     * @param vc input complex.
     * @param cell apply function on input cell.
     *
     * @return oneIsthmus || twoIsthmus
     *
     * @see oneIsthmus
     * @see twoIsthmus
     */
    template < typename TComplex >
    bool
    skelIsthmus(
      const TComplex & vc,
      const typename TComplex::Cell & cell);

    /**
     * Check if input cell is a 1-isthmus.
     * A voxel is a 1-isthmus if, after a thinning,
     * its proper neighborhood is made only by two voxels,
     * ie, it is a 0-Surface @ref isZeroSurface.
     *
     * @see isZeroSurface
     * @see Object::properNeighborhood
     *
     * @tparam TComplex VoxelComplex.
     * @param vc input complex.
     * @param cell apply function on input cell.
     *
     * @return bool
     */
    template < typename TComplex >
    bool
    oneIsthmus(
      const TComplex & vc,
      const typename TComplex::Cell & cell);

    /**
     * Check if input cell is a 2-isthmus.
     * A voxel is a 2-isthmus if, after a thinning,
     * its proper neighborhood is a 1-Surface @ref isOneSurface.
     *
     * @see isOneSurface
     * @see Object::properNeighborhood
     *
     * @tparam TComplex VoxelComplex.
     * @param vc input complex.
     * @param cell apply function on input cell.
     *
     * @return bool
     */
    template < typename TComplex >
    bool
    twoIsthmus(
      const TComplex & vc,
      const typename TComplex::Cell & cell);

    /**
     * Generic predicate to use external tables[configuration]->bool with skel
     * functions. Can be adapted to any table using lambdas.
     *
     * @see LookUpTableFunctions.h
     * @see tests/topology/testVoxelComplex.h
     *
     * If you need to have a
     * std::function<bool(const Complex & vc, const Cell & c )> signature
     * (for using it in thinning algorithms), use a lambda to capture values:
     * subsitute skelIsthmus (for example) for:
     * @code
     * auto skelWithTableIsthmus =
     * [&table, &pointToMaskMap](const Complex & vc, const Cell & cell){
     *     return skelWithTable<TComplex>(table, pointToMaskMap, vc, cell);
     * }
     * @endcode
     *
     * @tparam TComplex input CubicalComplex type.
     *
     * @param table [configuration]->bool
     * @see VoxelComplex::loadTable
     * @see LookUpTableFunctions.h::loadTable
     *
     * @param pointToMaskMap map[neighborhood points] to a bit mask. Used to get
     * the neighborhood configuration.
     * @see VoxelComplex::pointToMask
     * @see LookUpTableFunctions.h::mapPointToBitMask
     *
     * @param vc input complex.
     *
     * @param cell input cell, center from where the neighborhood
     * [configuration] will be checked.
     * Note that only neighborhood are checked to belong to the
     * complex, not the input cell.
     *
     * @return bool from selected table[configuration].
     */
    template < typename TComplex >
    bool
    skelWithTable(
      const boost::dynamic_bitset<> & table,
      const std::unordered_map<typename TComplex::Point, unsigned int> & pointToMaskMap,
      const TComplex & vc,
      const typename TComplex::Cell & cell);
//////////////////////////////////////////////////////////////////////////////
// Helpers for Objects
    /**
     * Check if the object contains, exclusively, two disconnected voxels.
     *
     * @see Object::computeConnectedness
     *
     * @tparam TObject Object Type
     * @param small_obj input object
     *
     * @return bool
     */
    template < typename TObject >
    bool
    isZeroSurface(const TObject & small_obj) ;

    /**
     * Check if input object is a simple closed curve.
     * Object must be:
     * - Connected.
     * - Each voxel is a @ref isZeroSurface.
     *
     * @see isZeroSurface
     *
     * @tparam TObject Object Type
     * @param small_obj input object
     *
     * @return bool
     */
    template < typename TObject >
    bool
    isOneSurface(const TObject & small_obj) ;

    /**
     * Get all connected components of the input object.
     *
     * @return vector of TObject containing the different
     * connected components of the object.
     *
     * @see ObjectBoostGraphInterface.h
     */
    template <typename TObject >
    std::vector< TObject >
    connectedComponents(const TObject & input_obj, bool verbose);


//////////////////////////////////////////////////////////////////////////////
//Operators between VoxelComplexes//

    /**
     * Voxel Complex difference operation. Updates the voxel complex S1 as S1 - S2.
     * @tparam TKSpace the digital space in which lives the voxel complex.
     * @tparam TObject the object type to store voxels and its connectivity.
     * @tparam TCellContainer the associative container used to store cells within the voxel complex.
     *
     * @param[in,out] S1 an input voxel complex, \a S1 - \a S2 as output.
     * @param[in] S2 another input voxel complex.
     *
     * @return a reference to the modified voxel complex S1.
     */
    template <typename TKSpace, typename TObject, typename TCellContainer>
    inline VoxelComplex< TKSpace, TObject, TCellContainer >&
    operator-=( VoxelComplex< TKSpace, TObject, TCellContainer >& S1,
                const VoxelComplex< TKSpace, TObject, TCellContainer >& S2 )
    {
      typedef VoxelComplex< TKSpace, TObject, TCellContainer > VC;
      for ( Dimension i = 0; i <= VC::dimension; ++i )
        setops::operator-=( S1.myCells[ i ],S2.myCells[ i ] );
      // Update Object. Assuming is an AssociativeContainer
      auto & S1ObjPoints = S1.myObject.pointSet();
      const auto & S2ObjPoints = S2.myObject.pointSet();
      for(auto it2 = S2ObjPoints.begin(); it2 != S2ObjPoints.end(); ++it2)
      {
        const auto it_search = S1ObjPoints.find(*it2);
        if(it_search != S1ObjPoints.end())
          S1ObjPoints.erase(it_search);
      }
      return S1;
    }

    /**
     * Voxel Complex difference operation. Returns the difference of \a S1 - \a S2.
     * @tparam TKSpace the digital space in which lives the voxel complex.
     * @tparam TObject the object type to store voxels and its connectivity.
     * @tparam TCellContainer the associative container used to store cells within the voxel complex.
     *
     * @param[in] S1 an input voxel complex
     * @param[in] S2 another input voxel complex.
     *
     * @return the voxel complex \a S1 - \a S2.
     */
    template <typename TKSpace, typename TObject, typename TCellContainer>
    inline VoxelComplex< TKSpace, TObject, TCellContainer >
    operator-( const VoxelComplex< TKSpace, TObject, TCellContainer >& S1,
               const VoxelComplex< TKSpace, TObject, TCellContainer >& S2 )
    {
      typedef VoxelComplex< TKSpace, TObject, TCellContainer > VC;
      VC S = S1;
      for ( Dimension i = 0; i <= VC::dimension; ++i )
        setops::operator-=( S.myCells[ i ],S2.myCells[ i ] );
      // Update Object. Assuming is an AssociativeContainer
      auto & SObjPoints = S.myObject.pointSet();
      const auto & S2ObjPoints = S2.myObject.pointSet();
      for(auto it2 = S2ObjPoints.begin(); it2 != S2ObjPoints.end(); ++it2)
      {
        auto it_search = SObjPoints.find(*it2);
        if(it_search != SObjPoints.end())
          SObjPoints.erase(it_search);
      }
      return S;
    }

  } // namespace functions
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/VoxelComplexFunctions.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined VoxelComplexFunctions_h

#undef VoxelComplexFunctions_RECURSES
#endif // else defined(VoxelComplexFunctions_RECURSES)
