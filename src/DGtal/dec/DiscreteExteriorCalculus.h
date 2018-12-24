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
 * @file DiscreteExteriorCalculus.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/27
 *
 * Header file for module DiscreteExteriorCalculus.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DiscreteExteriorCalculus_RECURSES)
#error Recursive header files inclusion detected in DiscreteExteriorCalculus.h
#else // defined(DiscreteExteriorCalculus_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DiscreteExteriorCalculus_RECURSES

#if !defined DiscreteExteriorCalculus_h
/** Prevents repeated inclusion of headers. */
#define DiscreteExteriorCalculus_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <boost/array.hpp>
#include <boost/unordered_map.hpp>
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/base/Common.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/dec/Duality.h"
#include "DGtal/dec/KForm.h"
#include "DGtal/dec/LinearOperator.h"
#include "DGtal/dec/VectorField.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/topology/CanonicSCellEmbedder.h"

#include <DGtal/kernel/sets/CDigitalSet.h>
#include <DGtal/math/linalg/CDynamicMatrix.h>
#include <DGtal/math/linalg/CDynamicVector.h>
#include <DGtal/math/linalg/CLinearAlgebra.h>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  // forward factory declaration
  template <typename TLinearAlgebraBackend, typename TInteger>
  class DiscreteExteriorCalculusFactory;

  /**
   * Hash function for Khalimsky unsigned cells.
   * @param cell input signed cell.
   * @return hash value.
   */
  template <Dimension dim, typename TInteger>
  size_t
  hash_value(const KhalimskyCell<dim, TInteger>& cell);

  /////////////////////////////////////////////////////////////////////////////
  // template class DiscreteExteriorCalculus
  /**
   * Description of template class 'DiscreteExteriorCalculus' <p>
   * \brief Aim:
   * DiscreteExteriorCalculus represents a calculus in the dec package.
   * This is the main structure in the dec package.
   * This is used to describe the space on which the dec is build and to compute various operators.
   * Once operators or kforms are created, this structure should not be modified.
   *
   * @tparam dimEmbedded dimension of emmbedded manifold.
   * @tparam dimAmbient dimension of ambient manifold.
   * @tparam TLinearAlgebraBackend linear algebra backend used (i.e. EigenSparseLinearAlgebraBackend).
   * @tparam TInteger integer type forwarded to khalimsky space.
   */
  template <Dimension dimEmbedded, Dimension dimAmbient, typename TLinearAlgebraBackend, typename TInteger = DGtal::int32_t>
  class DiscreteExteriorCalculus
  {
    // ----------------------- Standard services ------------------------------
  public:

    friend class DiscreteExteriorCalculusFactory<TLinearAlgebraBackend, TInteger>;

    typedef DiscreteExteriorCalculus<dimEmbedded, dimAmbient, TLinearAlgebraBackend, TInteger> Self;

    typedef TLinearAlgebraBackend LinearAlgebraBackend;
    typedef typename LinearAlgebraBackend::DenseVector::Index Index;
    typedef typename LinearAlgebraBackend::DenseVector::Scalar Scalar;
    typedef typename LinearAlgebraBackend::DenseVector DenseVector;
    typedef typename LinearAlgebraBackend::DenseMatrix DenseMatrix;
    typedef typename LinearAlgebraBackend::SparseMatrix SparseMatrix;

    BOOST_CONCEPT_ASSERT(( concepts::CInteger<TInteger> ));

    BOOST_CONCEPT_ASSERT(( concepts::CDynamicVector<DenseVector> ));
    BOOST_CONCEPT_ASSERT(( concepts::CDynamicMatrix<DenseMatrix> ));
    BOOST_CONCEPT_ASSERT(( concepts::CDynamicMatrix<SparseMatrix> ));
    BOOST_CONCEPT_ASSERT(( concepts::CLinearAlgebra<DenseVector, SparseMatrix> ));
    BOOST_CONCEPT_ASSERT(( concepts::CLinearAlgebra<DenseVector, DenseMatrix> ));

    BOOST_STATIC_ASSERT(( boost::is_same<Dimension, Order>::value ));

    /**
     * Static dimensions.
     */
    BOOST_STATIC_ASSERT(( dimAmbient >=  dimEmbedded ));

    BOOST_STATIC_CONSTANT( Dimension, dimensionEmbedded = dimEmbedded );
    BOOST_STATIC_CONSTANT( Dimension, dimensionAmbient = dimAmbient );

    typedef DGtal::KhalimskySpaceND<dimAmbient, TInteger> KSpace;
    typedef typename KSpace::Cell Cell;
    typedef typename KSpace::SCell SCell;
    typedef typename KSpace::Point Point;

    /**
     * @struct Property
     * @brief Holds size 'primal_size', 'dual_size', 'index' and 'flipped' for each cell of the DEC object.
     * To avoid inserting both positive and negative cells in a DEC object,
     * only non signed cells are stored internally.
     * @var Property::flipped
     * To retrieve the sign of the cell, one must look at the 'flipped' boolean:
     * if 'flipped' is true, the associated signed cell is negative,
     * if 'flipped' is false, the associated signed cell is positive.
     * @var Property::index
     * 'index' give the index of the discrete k-form value in the k-form container.
     * @var Property::dual_size
     * 'dual_size' is the dual cell size, has the same dimension as the dual cell.
     * @var Property::primal_size
     * 'primal_size' is the primal cell size, has the same dimension as the primal cell.
     */
    struct Property
    {
        Scalar primal_size;
        Scalar dual_size;
        Index index;
        bool flipped;
    };

    /**
     * Cells properties map typedef.
     */
    typedef boost::unordered_map<Cell, Property> Properties;

    /**
     * Indices to cells map typedefs.
     */
    typedef std::vector<SCell> SCells;
    typedef boost::array<SCells, dimEmbedded+1> IndexedSCells;

    /**
     * Vector field typedefs.
     */
    typedef VectorField<Self, PRIMAL> PrimalVectorField;
    typedef VectorField<Self, DUAL> DualVectorField;

    /**
     * KForms typedefs.
     */
    typedef KForm<Self, 0, PRIMAL> PrimalForm0;
    typedef KForm<Self, 1, PRIMAL> PrimalForm1;
    typedef KForm<Self, 2, PRIMAL> PrimalForm2;
    typedef KForm<Self, 3, PRIMAL> PrimalForm3;
    typedef KForm<Self, 0, DUAL> DualForm0;
    typedef KForm<Self, 1, DUAL> DualForm1;
    typedef KForm<Self, 2, DUAL> DualForm2;
    typedef KForm<Self, 3, DUAL> DualForm3;

    /**
     * Derivative linear operator typedefs.
     */
    typedef LinearOperator<Self, 0, PRIMAL, 1, PRIMAL> PrimalDerivative0;
    typedef LinearOperator<Self, 1, PRIMAL, 2, PRIMAL> PrimalDerivative1;
    typedef LinearOperator<Self, 2, PRIMAL, 3, PRIMAL> PrimalDerivative2;
    typedef LinearOperator<Self, 0, DUAL, 1, DUAL> DualDerivative0;
    typedef LinearOperator<Self, 1, DUAL, 2, DUAL> DualDerivative1;
    typedef LinearOperator<Self, 2, DUAL, 3, DUAL> DualDerivative2;

    /**
     * Antiderivative linear operator typedefs.
     */
    typedef LinearOperator<Self, 1, PRIMAL, 0, PRIMAL> PrimalAntiderivative1;
    typedef LinearOperator<Self, 2, PRIMAL, 1, PRIMAL> PrimalAntiderivative2;
    typedef LinearOperator<Self, 3, PRIMAL, 2, PRIMAL> PrimalAntiderivative3;
    typedef LinearOperator<Self, 1, DUAL, 0, DUAL> DualAntiderivative1;
    typedef LinearOperator<Self, 2, DUAL, 1, DUAL> DualAntiderivative2;
    typedef LinearOperator<Self, 3, DUAL, 2, DUAL> DualAntiderivative3;

    /**
     * Hodge duality linear operator typedefs.
     */
    typedef LinearOperator<Self, 0, PRIMAL, dimEmbedded-0, DUAL> PrimalHodge0;
    typedef LinearOperator<Self, 1, PRIMAL, dimEmbedded-1, DUAL> PrimalHodge1;
    typedef LinearOperator<Self, 2, PRIMAL, dimEmbedded-2, DUAL> PrimalHodge2;
    typedef LinearOperator<Self, 3, PRIMAL, dimEmbedded-3, DUAL> PrimalHodge3;
    typedef LinearOperator<Self, 0, DUAL, dimEmbedded-0, PRIMAL> DualHodge0;
    typedef LinearOperator<Self, 1, DUAL, dimEmbedded-1, PRIMAL> DualHodge1;
    typedef LinearOperator<Self, 2, DUAL, dimEmbedded-2, PRIMAL> DualHodge2;
    typedef LinearOperator<Self, 3, DUAL, dimEmbedded-3, PRIMAL> DualHodge3;

    /**
     * Identity linear operator typedefs.
     */
    typedef LinearOperator<Self, 0, PRIMAL, 0, PRIMAL> PrimalIdentity0;
    typedef LinearOperator<Self, 1, PRIMAL, 1, PRIMAL> PrimalIdentity1;
    typedef LinearOperator<Self, 2, PRIMAL, 2, PRIMAL> PrimalIdentity2;
    typedef LinearOperator<Self, 3, PRIMAL, 3, PRIMAL> PrimalIdentity3;
    typedef LinearOperator<Self, 0, DUAL, 0, DUAL> DualIdentity0;
    typedef LinearOperator<Self, 1, DUAL, 1, DUAL> DualIdentity1;
    typedef LinearOperator<Self, 2, DUAL, 2, DUAL> DualIdentity2;
    typedef LinearOperator<Self, 3, DUAL, 3, DUAL> DualIdentity3;

    /**
     * Constructor.
     * Initialize empty discrete exterior calculus.
     */
    DiscreteExteriorCalculus();

    /**
     * Init Khalimsky space boundaries.
     * @tparam TDomain type of digital domain.
     * @param domain domain used to initialize Khalimsky space.
     */
    template <typename TDomain>
    void
    initKSpace(ConstAlias<TDomain> domain);

    // ----------------------- Iterators on property map -----------------------

    /**
     * Const iterator typedef.
     */
    typedef typename Properties::const_iterator ConstIterator;

    /**
     * Begin const iterator.
     */
    ConstIterator begin() const;

    /**
     * End const iterator.
     */
    ConstIterator end() const;

    /**
     * Iterator typedef.
     */
    typedef typename Properties::iterator Iterator;

    /**
     * Begin iterator.
     */
    Iterator begin();

    /**
     * End iterator.
     */
    Iterator end();

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Associated Khalimsky space.
     */
    KSpace myKSpace;

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay(std::ostream& out) const;

    /**
     * Get class name string "Calculus".
     */
    std::string className() const;

    /**
     * Manually insert signed cell into calculus with unit primal and dual size.
     * Should call updateIndexes() when structure modification is finished.
     * Be sure to insert all adjacent lower order primal cells.
     * @param signed_cell the signed cell to be inserted.
     * @return true if cell was not already inserted, false if only cell was already inserted (cell properties are always updated).
     */
    bool
    insertSCell(const SCell& signed_cell);

    /**
     * Manually insert signed cell into calculus.
     * Should call updateIndexes() when structure modification is finished.
     * Be sure to insert all adjacent lower order primal cells.
     * @param signed_cell the signed cell to be inserted.
     * @param primal_size size (length, area, volume, ...) of primal cell. Primal size of 0-cell should be equal to 1.
     * @param dual_size size (length, area, volume, ...) of dual cell. Dual size of n-cell should be equal to 1.
     * @return true if cell was not already inserted, false if only cell was already inserted (cell properties are always updated).
     */
    bool
    insertSCell(const SCell& signed_cell, const Scalar& primal_size, const Scalar& dual_size);

    /**
     * Manually erase cell from calculus.
     * Should call updateIndexes() when structure modification is finished.
     * @param cell the cell to be removed.
     * @return true if cell was removed, false if cell was not in calculus.
     */
    bool
    eraseCell(const Cell& cell);

    /**
     * Update indexes for all cells.
     * Cell insertion order == index may not be preserved.
     */
    void
    updateIndexes();

    /**
     * Get all cells properties.
     * @return associative container from Cell to Property.
     */
    const Properties&
    getProperties() const;

    /**
     * Get all signed cells with specific @a order and @a duality in index order.
     * @tparam order order of signed cells.
     * @tparam duality duality of signed cells.
     * @return index ordered signed cells.
     */
    template <Order order, Duality duality>
    const SCells&
    getIndexedSCells() const;

    /**
     * Reorder operator from _order_-forms to _order_-forms.
     * Reorder indexes from internal index order to iterator range traversal induced order.
     * @tparam order input and output order of reorder operator.
     * @tparam duality input and output duality of reorder operator.
     * @tparam TConstIterator const iterator to signed cell type.
     * @return identity operator.
     */
    template <Order order, Duality duality, typename TConstIterator>
    LinearOperator<Self, order, duality, order, duality>
    reorder(const TConstIterator& begin_range, const TConstIterator& end_range) const;

    /**
     * Identity operator from _order_-forms to _order_-forms.
     * @tparam order input and output order of identity operator.
     * @tparam duality input and output duality of identity operator.
     * @return identity operator.
     */
    template <Order order, Duality duality>
    LinearOperator<Self, order, duality, order, duality>
    identity() const;

    /**
     * Derivative operator from _order_-forms to _(order+1)_-forms.
     * @tparam order order of input k-form.
     * @tparam duality duality of input k-form.
     * @return derivative operator.
     */
    template <Order order, Duality duality>
    LinearOperator<Self, order, duality, order+1, duality>
    derivative() const;

    /**
     * Antiderivative operator from _order_-forms to _(order-1)_-forms.
     * @tparam order order of input k-form.
     * @tparam duality duality of input k-form.
     * @return antiderivative operator.
     */
    template <Order order, Duality duality>
    LinearOperator<Self, order, duality, order-1, duality>
    antiderivative() const;

    /**
     * Laplace operator from duality 0-forms to duality 0-forms.
     * @return Laplace operator.
     */
    template <Duality duality>
    LinearOperator<Self, 0, duality, 0, duality>
    laplace() const;

    /**
     * Convolutional Laplace operator from duality 0-forms to duality 0-forms. See \ref secHowToHeatLaplace.
     * @param h the grid step
     * @param t the time parameter for the convolution
     * @param K the multiplier for the integration. Must be at least 2.
     * @return Heat Laplace operator.
     */
    template <Duality duality>
    LinearOperator<Self, 0, duality, 0, duality>
    heatLaplace(const typename DenseVector::Scalar& h, const typename DenseVector::Scalar& t, const typename DenseVector::Scalar& K) const;

    /**
     * Hodge operator from duality _order_-form to opposite duality _(dimEmbedded-order)_-forms.
     * @tparam order order of input k-form.
     * @tparam duality duality of input k-form.
     * @return hodge operator.
     */
    template <Order order, Duality duality>
    LinearOperator<Self, order, duality, dimEmbedded-order, OppositeDuality<duality>::duality>
    hodge() const;

    /**
     * Construct 1-form from vector field.
     * @tparam duality input vector field and output 1-form duality.
     * @param vector_field vector field.
     * @return 1-form.
     */
    template <Duality duality>
    KForm<Self, 1, duality>
    flat(const VectorField<Self, duality>& vector_field) const;

    /**
     * Get directional flat operator that transforms 0-form containing vector field coordinates along direction dir into 1-form.
     * Invert of sharp(1-form).coordAlongDirection(dir).
     * @tparam duality input 0-form and output 1-form duality.
     * @param dir direction of projection.
     * @return linear operator.
     */
    template <Duality duality>
    LinearOperator<Self, 0, duality, 1, duality>
    flatDirectional(const Dimension& dir) const;

    /**
     * Construct vector field from 1-form.
     * @tparam duality input 1-form and output vector field duality.
     * @param one_form 1-form.
     * @return vector field.
     */
    template <Duality duality>
    VectorField<Self, duality>
    sharp(const KForm<Self, 1, duality>& one_form) const;

    /**
     * Get directional sharp operator that transforms 1-form into 0-form containing vector field coordinates along direction dir.
     * Equivalent to sharp(1-form).coordAlongDirection(dir).
     * @tparam duality input 1-form and output 0-form duality.
     * @param dir direction of projection.
     * @return linear operator.
     */
    template <Duality duality>
    LinearOperator<Self, 1, duality, 0, duality>
    sharpDirectional(const Dimension& dir) const;

    /**
     * Get signed cell from k-form index.
     * @param order k-form order.
     * @param duality k-form duality.
     * @param index index valid on a k-form container.
     * @return associated Khalimsky cell.
     */
    SCell
    getSCell(const Order& order, const Duality& duality, const Index& index) const;

    /**
     * Check if cell is flipped in display.
     * @param cell the tested cell.
     */
    bool
    isCellFlipped(const Cell& cell) const;

    /**
     * Check is structure contains cell.
     * @param cell the tested cell.
     */
    bool
    containsCell(const Cell& cell) const;

    /**
     * Get k-form index from cell.
     * @param cell Khalimsky cell.
     * @return associated k-form index.
     */
    Index
    getCellIndex(const Cell& cell) const;

    /**
     * Return number of elements in discrete k-form.
     * @param order k-form order.
     * @param duality k-form duality.
     */
    Index
    kFormLength(const Order& order, const Duality& duality) const;

    /**
     * Return actual order of k-forms in the dec package representation.
     * Used internally mostly.
     * @param order order.
     * @param duality duality.
     * @return order if primal, dimEmbedded-order if dual.
     */
    Order
    actualOrder(const Order& order, const Duality& duality) const;

    /**
     * Return sign of hodge operator.
     * Used internally mostly.
     * @param cell Khalimsky cell.
     * @param duality duality.
     */
    Scalar
    hodgeSign(const Cell& cell, const Duality& duality) const;

    /**
     * Return edge direction relative to primal.
     * @param cell Khalimsky cell.
     * @param duality duality.
     */
    Dimension
    edgeDirection(const Cell& cell, const Duality& duality) const;

    /**
     * Reset all primal to dual cell sizes to 1.
     */
    void
    resetSizes();

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool
    isValid() const;

    // ------------------------- Private Datas --------------------------------
  private:

    /**
     * Cells properties.
     */
    Properties myCellProperties;

    /**
     * Cells indexed by their order.
     * Usefull for finding cell from index and order.
     */
    IndexedSCells myIndexSignedCells;

    /**
     * Cached flat operator matrix.
     */
    boost::array<boost::array<SparseMatrix, dimAmbient>, 2> myFlatOperatorMatrixes;

    /**
     * Cached sharp operator matrix.
     */
    boost::array<boost::array<SparseMatrix, dimAmbient>, 2> mySharpOperatorMatrixes;

    /**
     * Cached flat and sharp operators generation flag.
     */
    bool myCachedOperatorsNeedUpdate;

    /**
     * Indexes generation flag.
     */
    bool myIndexesNeedUpdate;


    // ------------------------- Hidden services ------------------------------
  protected:

    // ------------------------- Internals ------------------------------------
  private:

    /**
     * Update sharp and flat operators cache.
     */
    void
    updateCachedOperators();

    /**
     * Update flat operator cache.
     * @tparam duality duality of updated flat operator.
     */
    template <Duality duality>
    void
    updateFlatOperator();

    /**
     * Update sharp operator cache.
     * @tparam duality duality of updated sharp operator.
     */
    template <Duality duality>
    void
    updateSharpOperator();

  }; // end of class DiscreteExteriorCalculus


  /**
   * Overloads 'operator<<' for displaying objects of class 'DiscreteExteriorCalculus'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'DiscreteExteriorCalculus' to write.
   * @return the output stream after the writing.
   */
  template <Dimension dimEmbedded, Dimension dimAmbient, typename TLinearAlgebraBackend, typename TInteger>
  std::ostream&
  operator<<(std::ostream& out, const DiscreteExteriorCalculus<dimEmbedded, dimAmbient, TLinearAlgebraBackend, TInteger>& object);

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/dec/DiscreteExteriorCalculus.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DiscreteExteriorCalculus_h

#undef DiscreteExteriorCalculus_RECURSES
#endif // else defined(DiscreteExteriorCalculus_RECURSES)
