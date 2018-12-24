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
 * @file ParDirCollapse.h
 * @author Mohamad ONAYSSI (\c mohamad.onayssi@edu.esiee.fr )
 * @author Bibiana MARTINEZ (\c bibiana.martinez@edu.esiee.fr )
 * @author Mohamed MELLOULI (\c mohamed.mellouli@edu.esiee.fr )
 * ESIEE Paris
 *
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, France
 *
 *
 * @date 2015/12/22
 *
 *
 * This file is part of the DGtal library.
 */

#if defined(ParDirCollapse_RECURSES)
#error Recursive header files inclusion detected in ParDirCollapse.h
#else // defined(ParDirCollapse_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ParDirCollapse_RECURSES

#if !defined ParDirCollapse_h
/** Prevents repeated inclusion of headers. */
#define ParDirCollapse_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
// Cellular grid
#include "DGtal/topology/CubicalComplex.h"
#include "DGtal/topology/CubicalComplexFunctions.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
/////////////////////////////////////////////////////////////////////////////
// class ParDirCollapse
/**
 * Description of class 'ParDirCollapse' <p>
 * \brief Aim: Implements thinning algorithms in cubical complexes.
 * The implementation supports any model of cubical complex,
 * for instance a DGtal::CubicalComplex< KhalimskySpaceND< 3, int > >.
 * Three approaches are provided. The first---ParDirCollapse---bases
 * on directional collapse of free pairs of faces. Second---CollapseSurface---is an
 * extension of ParDirCollapse such that faces of dimension one lower than
 * the dimension of the complex are kept. The last approach ---CollapseIsthmus---is
 * also an extension of ParDirCollapse such that faces of dimension one lower than
 * the complex are preserved when they do not contain free faces of dimension two
 * lower than the complex.
 * Paper: Chaussard, J. and Couprie, M., Surface Thinning in 3D Cubical Complexes,
 * Combinatorial Image Analysis, (2009)
 * @tparam CC cubical complex.
 */
template < typename CC >
class ParDirCollapse
{
    BOOST_STATIC_ASSERT(( CC::KSpace::dimension >= 2 ));
    BOOST_CONCEPT_ASSERT(( boost::Container< CC > ));
    // ----------------------- Types ------------------------------
public:
    /// Any model of concepts::CCellularGridSpaceND, i.e. a type that models a Khalimsky space.
    typedef typename CC::KSpace KSpace;
    /// Type of integer point
    typedef typename CC::Point Point;
    /// Type of containers size
    typedef typename CC::Size Size;
    /// Type of cells in Khalimsky space
    typedef typename KSpace::Cell Cell;
    /// Type of collection of cells
    typedef typename KSpace::Cells Cells;
    /// Type of const iterator over a map of cells.
    typedef typename CC::CellMapConstIterator CellMapConstIterator;

    // ----------------------- Standard services ------------------------------
    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ----------------------- Interface --------------------------------------
public:
    /**
     * Constructor.
     * @param k -- const reference to Khalimsky space
     */
    ParDirCollapse ( const KSpace & k );

     /**
     * This method should be use to point to a complex
     * to which one wish to apply one of the thinning
     * algorithms.
     * @param pComplex -- Cubical complex
     */
    void attach ( Alias< CC > pComplex );

     /**
     * This method applies a given number of iterations to a complex
     * provided by the attach() method.
     * @param iterations -- number of iterations
     * @return total number of removed cells.
     */
    unsigned int eval ( unsigned int iterations );

    /**
     * Extension of basic algorithm---ParDirCollapse---which preserve
     * KSpace::dimension - 1 faces which are not included in any
     * KSpace::dimension cells.
     */
    void collapseSurface();

    /**
     * Extension of basic algorithm---ParDirCollapse---which preserve
     * KSpace::dimension - 1 faces which are not included in any
     * KSpace::dimension cells. Moreover, cells to be kept have not to
     * be collapsible.
     */
    void collapseIsthmus();

    // ------------------------- Internals ------------------------------------
private:
    /**
     * Calculate an orientation of a freepair.
     * @param F -- cell of a dimension one lower than G.
     * @param G -- cell of a dimension one higher than F.
     */
    int getOrientation ( const Cell& F, const Cell& G ) const;

     /**
     * Calculate an orientation of a freepair.
     * @param F -- cell of a dimension one lower than G.
     * @param G -- cell of a dimension one higher than F.
     */
    int getDirection ( const Cell& F, const Cell& G ) const;

     /**
     * Calculate an orientation of a freepair.
     * @param F -- cell of a dimension one lower than G.
     * @param G -- cell of a dimension one higher than F.
     * @param orient -- freepair orientation
     * @param dir -- freepair direction
     * @return -- true if G was found as collapisble, false
     * otherwise.
     */
    bool completeFreepair ( CellMapConstIterator F, Cell& G, int orient, int dir );

    /**
     * Check if a given face of dimension n is included in a face of dimmension n + 1.
     * @param F -- cell of dimension smaller than KSpace::dimension.
     * @return true if a face is not included in any other and false otherwise.
     */
    bool isNotIncludedInUpperDim (  CellMapConstIterator F );

    /**
     * Check if a given face of dimension: KSpace::dimension - 1, does not constitute a freepair.
     * Note that, a given face has to not be included in any face of dimension: KSpace::dimension.
     * @param F -- cell of dimension one lower than KSpace.
     * @return true if F does not constitute a freepair and false otherwise.
     */
    bool isIsthmus ( CellMapConstIterator F );

    // ------------------------- Hidden services ------------------------------
protected:
    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    ParDirCollapse();

private:
    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    ParDirCollapse ( const ParDirCollapse & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    ParDirCollapse & operator= ( const ParDirCollapse & other );


    // ------------------------- Private Datas --------------------------------
private:

    /// Reference to Khalimsky space in which a given complex is embedded.
    const KSpace& K;
    /// Pointer to complex.
    CC * complex;

}; // end of class ParDirCollapse

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#if !defined(BUILD_INLINE)
#include "DGtal/topology/ParDirCollapse.ih"
#endif


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ParDirCollapse_h

#undef ParDirCollapse_RECURSES
#endif // else defined(ParDirCollapse_RECURSES)
