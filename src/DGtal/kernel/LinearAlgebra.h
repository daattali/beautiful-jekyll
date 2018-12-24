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
 * @file LinearAlgebra.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/12/14
 *
 * Header file for module LinearAlgebra.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(LinearAlgebra_RECURSES)
#error Recursive header files inclusion detected in LinearAlgebra.h
#else // defined(LinearAlgebra_RECURSES)
/** Prevents recursive inclusion of headers. */
#define LinearAlgebra_RECURSES

#if !defined LinearAlgebra_h
/** Prevents repeated inclusion of headers. */
#define LinearAlgebra_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CSpace.h"
#include "DGtal/base/ConceptUtils.h"
#include <boost/type_traits.hpp>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class LinearAlgebra
  /**
   * Description of template class 'LinearAlgebra' <p> \brief Aim: A
   * utility class that contains methods to perform integral linear
   * algebra.
   */
  template <typename Space>
  struct LinearAlgebra
  {
    // ----------------------- Standard services ------------------------------
   
    BOOST_CONCEPT_ASSERT(( concepts::CSpace<Space> ));
    
    typedef typename Space::Integer Integer;
    typedef typename Space::Point Point;
    typedef typename Space::Vector Vector;
    static const typename Space::Dimension dimension;

    static Integer determinant(const Point &a, const Point &b);

   // ----------------------- Standard services ------------------------------
   
    /** 
     * Self display of the instance in a ostream
     * 
     * @param out the output stream.
     */
    void selfDisplay(std::ostream &out) const;

    /** 
     * @return true if the instance is valid.
     */
    static bool isValid();
    

  }; // end of class LinearAlgebra

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/LinearAlgebra.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined LinearAlgebra_h

#undef LinearAlgebra_RECURSES
#endif // else defined(LinearAlgebra_RECURSES)
