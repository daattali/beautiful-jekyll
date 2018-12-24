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
 * @file DiscreteExteriorCalculusSolver.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/27
 *
 * Header file for module DiscreteExteriorCalculusSolver.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DiscreteExteriorCalculusSolver_RECURSES)
#error Recursive header files inclusion detected in DiscreteExteriorCalculusSolver.h
#else // defined(DiscreteExteriorCalculusSolver_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DiscreteExteriorCalculusSolver_RECURSES

#if !defined DiscreteExteriorCalculusSolver_h
/** Prevents repeated inclusion of headers. */
#define DiscreteExteriorCalculusSolver_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/base/Clone.h"
#include "DGtal/dec/KForm.h"
#include "DGtal/dec/LinearOperator.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class DiscreteExteriorCalculusSolver
  /**
   * Description of template class 'DiscreteExteriorCalculusSolver' <p>
   * \brief Aim:
   * This wraps a linear algebra solver around a discrete exterior calculus.
   *
   * @tparam TCalculus should be DiscreteExteriorCalculus.
   * @tparam TLinearAlgebraSolver should be a model of CLinearAlgebraSolver.
   * @tparam order_in is the input order of the linear problem.
   * @tparam duality_in is the input duality of the linear problem.
   * @tparam order_out is the output order of the linear problem.
   * @tparam duality_out is the output duality of the linear problem.
   */
  template <typename TCalculus, typename TLinearAlgebraSolver, Order order_in, Duality duality_in, Order order_out, Duality duality_out>
  class DiscreteExteriorCalculusSolver
  {
    // ----------------------- Standard services ------------------------------
  public:
    BOOST_STATIC_ASSERT(( order_in  >= 0 ));
    BOOST_STATIC_ASSERT(( order_in  <= TCalculus::dimensionEmbedded ));
    BOOST_STATIC_ASSERT(( order_out >= 0 ));
    BOOST_STATIC_ASSERT(( order_out <= TCalculus::dimensionEmbedded ));

    typedef TCalculus Calculus;
    typedef TLinearAlgebraSolver LinearAlgebraSolver;

    typedef LinearOperator<Calculus, order_in, duality_in, order_out, duality_out> Operator;
    typedef KForm<Calculus, order_in, duality_in> SolutionKForm;
    typedef KForm<Calculus, order_out, duality_out> InputKForm;

    /**
     * Constructor.
     */
    DiscreteExteriorCalculusSolver();

    // ----------------------- Interface --------------------------------------
  public:
    /**
     * Pointer to const calculus
     */
    const Calculus* myCalculus;

    /**
     * Linear algebra solver.
     */
    LinearAlgebraSolver myLinearAlgebraSolver;

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay(std::ostream& out) const;

    /**
     * Prefactorize problem / set problem operator.
     * @param linear_operator linear operator.
     * @return *this.
     */
    DiscreteExteriorCalculusSolver& compute(const Operator& linear_operator);

    /**
     * Solve prefactorized / set problem input.
     * @param input_kform input k-form.
     * @return problem solution.
     */
    SolutionKForm solve(const InputKForm& input_kform) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class DiscreteExteriorCalculusSolver


  /**
   * Overloads 'operator<<' for displaying objects of class 'DiscreteExteriorCalculusSolver'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'DiscreteExteriorCalculusSolver' to write.
   * @return the output stream after the writing.
   */
  template <typename C, typename S, Order order_in, Duality duality_in, Order order_out, Duality duality_out>
  std::ostream&
  operator<<(std::ostream& out, const DiscreteExteriorCalculusSolver<C, S, order_in, duality_in, order_out, duality_out>& object);

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/dec/DiscreteExteriorCalculusSolver.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DiscreteExteriorCalculusSolver_h

#undef DiscreteExteriorCalculusSolver_RECURSES
#endif // else defined(DiscreteExteriorCalculusSolver_RECURSES)
