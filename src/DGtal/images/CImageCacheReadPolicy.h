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
 * @file CImageCacheReadPolicy.h
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/02/22
 *
 * Header file for concept CImageCacheReadPolicy.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CImageCacheReadPolicy_RECURSES)
#error Recursive header files inclusion detected in CImageCacheReadPolicy.h
#else // defined(CImageCacheReadPolicy_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CImageCacheReadPolicy_RECURSES

#if !defined CImageCacheReadPolicy_h
/** Prevents repeated inclusion of headers. */
#define CImageCacheReadPolicy_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
/////////////////////////////////////////////////////////////////////////////
// class CImageCacheReadPolicy
/**
Description of \b concept '\b CImageCacheReadPolicy' <p>
@ingroup Concepts
@brief Aim: Defines the concept describing a cache read policy

### Refinement of

### Associated types :
 - \e ImageContainer : type of the image in the cache, model of concept CImage
 - \e Point : type of the image point
 - \e Domain : type of the image domain, model of concept CDomain

### Notation
 - \e X : A type that is a model of CImageCacheReadPolicy
 - \e x : object of type X
 - \e p : object of type Point
 - \e d : object of type Domain

### Definitions

### Valid expressions and semantics

| Name                | Expression              | Type requirements    | Return type       | Precondition                         | Semantics                                            | Post condition | Complexity |
|---------------------|-------------------------|----------------------|-------------------|--------------------------------------|------------------------------------------------------|----------------|------------|
| Get page            | x.getPage(p)            | p of type Point      | ImageContainer    | p should be in a domain of the cache | get the alias on the image that contains the point p |                |            |
| Get page            | x.getPage(d)            | d of type Domain     | ImageContainer    | d should be in a domain of the cache | get the alias on the image that matchs the domain d  |                |            |
| Get page to detach  | x.getPageToDetach()     |                      | ImageContainer    |                                      | get the alias on the image that we have to detach    |                |            |
| Update cache        | x.updateCache(d)        | d of type Domain     |                   |                                      | update the cache with a new Domain d                 |                |            |
| Clear cache         | x.clearCache()          |                      |                   |                                      | clear the cache                                      |                |            |

### Invariants

### Models
ImageCacheReadPolicyLAST, ImageCacheReadPolicyFIFO

### Notes

@tparam T the type that should be a model of CImageCacheReadPolicy.
 */
template <typename T>
struct CImageCacheReadPolicy
{
    // ----------------------- Concept checks ------------------------------
public:

    typedef typename T::ImageContainer ImageContainer;

    BOOST_CONCEPT_USAGE( CImageCacheReadPolicy )
    {
        ConceptUtils::sameType( myIC, myT.getPage(myDomain) );
        ConceptUtils::sameType( myIC, myT.getPage(myPoint) );
        ConceptUtils::sameType( myIC, myT.getPageToDetach() );
        myT.updateCache(myDomain); 
        myT.clearCache();

        // check const methods.
        checkConstConstraints();
    }
    
    void checkConstConstraints() const
    {
    }
    
    // ------------------------- Private Datas --------------------------------
private:
    T myT; // do not require T to be default constructible.
    ImageContainer * myIC;
    typename T::Point myPoint;
    typename T::Domain myDomain;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CImageCacheReadPolicy
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CImageCacheReadPolicy_h

#undef CImageCacheReadPolicy_RECURSES
#endif // else defined(CImageCacheReadPolicy_RECURSES)
