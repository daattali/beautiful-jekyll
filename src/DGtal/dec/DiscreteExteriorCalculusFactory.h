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
 * @file DiscreteExteriorCalculusFactory.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2015/05/04
 *
 * Header file for DiscreteExteriorCalculusFactory
 *
 * This file is part of the DGtal library.
 */

#if defined(DiscreteExteriorCalculusFactory_RECURSES)
#error Recursive header files inclusion detected in DiscreteExteriorCalculusFactory.h
#else // defined(DiscreteExteriorCalculusFactory_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DiscreteExteriorCalculusFactory_RECURSES

#if !defined DiscreteExteriorCalculusFactory_h
/** Prevents repeated inclusion of headers. */
#define DiscreteExteriorCalculusFactory_h

//////////////////////////////////////////////////////////////////////////////
#include "DGtal/dec/DiscreteExteriorCalculus.h"
#include "DGtal/topology/DigitalSurface.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class DiscreteExteriorCalculusFactory
/**
 * Description of class 'DiscreteExteriorCalculusFactory' <p>
 * \brief Aim:
 * This class provides static members to create DEC structures from various other DGtal structures.
 *
 * @tparam TLinearAlgebraBackend linear algebra backend used (i.e. EigenLinearAlgebraBackend).
 * @tparam TInteger integer type forwarded to khalimsky space.
 */

template <typename TLinearAlgebraBackend, typename TInteger = DGtal::int32_t>
class DiscreteExteriorCalculusFactory
{
    // ----------------------- Standard services ------------------------------
public:

    typedef typename TLinearAlgebraBackend::DenseVector DenseVector;
    typedef typename TLinearAlgebraBackend::DenseMatrix DenseMatrix;
    typedef typename TLinearAlgebraBackend::SparseMatrix SparseMatrix;

    BOOST_CONCEPT_ASSERT(( concepts::CInteger<TInteger> ));

    BOOST_CONCEPT_ASSERT(( concepts::CDynamicVector<DenseVector> ));
    BOOST_CONCEPT_ASSERT(( concepts::CDynamicMatrix<DenseMatrix> ));
    BOOST_CONCEPT_ASSERT(( concepts::CDynamicMatrix<SparseMatrix> ));
    BOOST_CONCEPT_ASSERT(( concepts::CLinearAlgebra<DenseVector, SparseMatrix> ));
    BOOST_CONCEPT_ASSERT(( concepts::CLinearAlgebra<DenseVector, DenseMatrix> ));

    /**
     * Create a DEC structure from digital set.
     * DEC embedded and ambient dimensions are equal to digital set point dimension.
     * Points of the set get attached to primal n-cell <-> dual 0-cell.
     * @tparam TDigitalSet type of digital set passed as argument. must be a model of concepts::CDigitalSet.
     * @param set the set from which to build to DEC structure.
     * @param add_border add border to the computed structure. For a precise definition see section \ref sectDECBorderDefinition.
     */
    template <typename TDigitalSet>
    static
    DiscreteExteriorCalculus<TDigitalSet::Point::dimension, TDigitalSet::Point::dimension, TLinearAlgebraBackend, TInteger>
    createFromDigitalSet(const TDigitalSet& set, const bool add_border = true);

    /**
     * Create a DEC structure from a range of signed n-cells, where n is the embedded dimension.
		 * Signed n-cells may live in an ambient Khamlisky space with dimension greater than n.
     * N-cells get attached to primal n-cell <-> dual 0-cell. See section \ref sectDECEmbedding for more information.
     * @tparam dimEmbedded dimension of emmbedded manifold. All input n-cells must have their dimension equal to dimEmbedded.
     * @tparam TNSCellConstIterator signed cells collection const iterator type.
     * @param begin beginning of iteration range.
     * @param end end of iteration range.
     * @param add_border add border to the computed structure. For a precise definition see section \ref sectDECBorderDefinition.
     */
    template <Dimension dimEmbedded, typename TNSCellConstIterator>
    static
    DiscreteExteriorCalculus<dimEmbedded, TNSCellConstIterator::value_type::Point::dimension, TLinearAlgebraBackend, TInteger>
    createFromNSCells(const TNSCellConstIterator& begin, const TNSCellConstIterator& end, const bool add_border = true);

    /**
     * Create a DEC structure from a range of signed n-cells, where n is the embedded dimension. A functor from cell to its measure is given.
     * Signed n-cells may live in an ambient Khamlisky space with dimension greater than n.
     * N-cells get attached to primal n-cell <-> dual 0-cell. See section \ref sectDECEmbedding for more information.
     * @tparam dimEmbedded dimension of emmbedded manifold. All input n-cells must have their dimension equal to dimEmbedded.
     * @tparam TNSCellConstIterator signed cells collection const iterator type.
     * @param begin beginning of iteration range.
     * @param end end of iteration range.
     * @param normalFunctor functor from a cell to its normal
     * @param h the grid step
     * @param add_border add border to the computed structure. For a precise definition see section \ref sectDECBorderDefinition.
     */
    template <DGtal::Dimension dimEmbedded, typename TNSCellConstIterator, typename TSCellMeasureFunctor>
    static
    DiscreteExteriorCalculus<dimEmbedded, TNSCellConstIterator::value_type::Point::dimension, TLinearAlgebraBackend, TInteger>
    createFromNSCells(const TNSCellConstIterator& begin, const TNSCellConstIterator& end, const TSCellMeasureFunctor& normalFunctor, const double h, const bool add_border = true);

    // ----------------------- Interface --------------------------------------
public:

    // ------------------------- Protected Datas ------------------------------
private:
    // ------------------------- Private Datas --------------------------------
private:

    // ------------------------- Hidden services ------------------------------
protected:

    /**
     * Insert recursively all lower incident cells into cells set, starting from cell.
     * Internal use only.
     * @tparam KSpace Khalimsky space type.
     * @tparam CellsSet cells set type, should be similar to std::set<KSpace::Cell> or std::set<KSpace::SCell>.
     * @param kspace Khalimsky space instance.
     * @param cell starting cell.
     * @param cells_set cells set in which lower incident cells get inserted.
     */
    template <typename KSpace, typename CellsSet>
    static
    void
    insertAllLowerIncidentCells(const KSpace& kspace, const typename CellsSet::value_type& cell, CellsSet& cells_set);

    /**
     * Insert and count recursively all lower incident cells into cells accumulator, starting from cell.
     * Internal use only.
     * @tparam KSpace Khalimsky space type.
     * @tparam CellsAccum cells accumulator type, should be similar to std::map<KSpace::Cell, int> or std::map<KSpace::SCell, int>.
     * Counts are stored as values, cells are stored as keys.
     * @param kspace Khalimsky space instance.
     * @param cell starting cell.
     * @param cells_accum cells accumulator in which lower incident cells get inserted and counted.
     */
    template <typename KSpace, typename CellsAccum>
    static
    void
    accumulateAllLowerIncidentCells(const KSpace& kspace, const typename CellsAccum::key_type& cell, CellsAccum& cells_accum);

    /**
     * Insert and count recursively all lower incident cells into cells accumulator, starting from cell embedding the measure of such cell.
     * Internal use only.
     * @tparam KSpace Khalimsky space type.
     * @tparam CellsAccum cells accumulator type, should be similar to std::map<KSpace::Cell, int> or std::map<KSpace::SCell, int>.
     * Counts are stored as values, cells are stored as keys.
     * @param kspace Khalimsky space instance.
     * @param cell starting cell.
     * @param cells_accum cells accumulator in which lower incident cells get inserted and counted.
     * @param local_accum local cells accumulator for measure embedding
     * @param cell_to_measure a map from cell to its measure
     * @param measure the current measure to be embedded
     */
    template <typename KSpace, typename CellsAccum, typename MeasureAccum>
    static
    void
    accumulateAllLowerIncidentCells(const KSpace& kspace, const typename CellsAccum::key_type& cell, CellsAccum& cells_accum, CellsAccum& local_accum, MeasureAccum& cell_to_measure, const double measure);

private:

    /**
     * Constructor.
     * Forbidden by default.
     */
    DiscreteExteriorCalculusFactory();


    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    DiscreteExteriorCalculusFactory ( const DiscreteExteriorCalculusFactory & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    DiscreteExteriorCalculusFactory & operator= ( const DiscreteExteriorCalculusFactory & other );

    // ------------------------- Internals ------------------------------------
private:

}; // end of class DiscreteExteriorCalculusFactory

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#if !defined(BUILD_INLINE)
#include "DGtal/dec/DiscreteExteriorCalculusFactory.ih"
#endif


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DiscreteExteriorCalculusFactory_h

#undef DiscreteExteriorCalculusFactory_RECURSES
#endif // else defined(DiscreteExteriorCalculusFactory_RECURSES)
