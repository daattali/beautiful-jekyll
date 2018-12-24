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
 * @file CPreCellularGridSpaceND.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 * @author Roland Denis ( \c roland.denis@univ-smb.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2016/23/02
 *
 * Header file for concept CPreCellularGridSpaceND.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CPreCellularGridSpaceND_RECURSES)
#error Recursive header files inclusion detected in CPreCellularGridSpaceND.h
#else // defined(CPreCellularGridSpaceND_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CPreCellularGridSpaceND_RECURSES

#if !defined CPreCellularGridSpaceND_h
/** Prevents repeated inclusion of headers. */
#define CPreCellularGridSpaceND_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CConstSinglePassRange.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/kernel/CUnsignedNumber.h"
#include "DGtal/kernel/CIntegralNumber.h"

//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal {
  namespace concepts {

/////////////////////////////////////////////////////////////////////////////
// class CPreCellularGridSpaceND
/**
Description of \b concept '\b CPreCellularGridSpaceND' <p>
@ingroup Concepts

@brief Aim: This concept describes an unbounded cellular grid space in nD. In
these spaces obtained by cartesian product, cells have a cubic shape
that depends on the dimension: 0-cells are points, 1-cells are unit
segments, 2-cells are squares, 3-cells are cubes, and so on.

This concept is rather complex since it gathers all possible
operations on cells. The idea is that only the space knows what are
the cells, how to compute their adjacent or incident cells, how to
extract their coordinates, where are the bounds, what is the topology
and dimension of a cell, etc. Worse (!), you have two kinds of cells,
normal cells (unsigned), and oriented cells (signed). The latter are
used to define orientation and boundary operators.

@note Another way of defining orientation and boundary operators is to
define chains on cells and chain complexes. However, this is
unnecessary here.

Models of CPreCellularGridSpaceND are used whenever you need to define a
topology on a full digital space.

The space size only depends on the given integer precision.

We refer the reader to \ref moduleCellularTopology for further
details.

### Refinement of

- boost::DefaultConstructible
- boost::CopyConstructible

### Associated types :

- \e Integer: the integral type for representing coordinates in the space (model of CInteger).
- \e Space: the corresponding digital space (same dimension and same \e Integer type as this).
- \e PreCelullarGridSpace: the pre-celullar grid space type associated to this model (can be itself).
- \e Cell: the type that represents an unsigned cell. Cell's are ordered.
- \e SCell: the type that represents a signed cell. SCell's are ordered.
- \e Surfel: the type that represents a signed n-1-cell. Should be promotable to SCell and reciprocally. Surfel's are ordered.
- \e Sign: the type that represents the sign/orientation of a cell. Should be promotable to \c bool and reciprocally (POS is true, NEG is false).
- \e DirIterator: the type that represents an iterator over the open or closed directions of a cell (signed or not).
- \e Point: the type for defining points in \e Space (same as Space::Point).
- \e Vector: the type for defining vectors in \e Space  (same as Space::Vector).
- \e Cells: a container that stores unsigned cells (not a set, rather a enumerable collection type, model of CConstSinglePassRange).
- \e SCells: a container that stores signed cells (not a set, rather a enumerable collection type, model of CConstSinglePassRange).
- \e CellSet: a set container that stores unsigned cells (efficient for queries like \c find, model of boost::UniqueAssociativeContainer and boost::SimpleAssociativeContainer).
- \e SCellSet: a set container that stores signed cells (efficient for queries like \c find, model of boost::UniqueAssociativeContainer and boost::SimpleAssociativeContainer).
- \e SurfelSet: a set container that stores surfels, i.e. signed n-1-cells (efficient for queries like \c find, model of boost::UniqueAssociativeContainer and boost::SimpleAssociativeContainer).
- \e CellMap<Value>: an associative container Cell->Value rebinder type (efficient for key queries). Use as \c typename X::template CellMap<Value>::Type, which is a model of boost::UniqueAssociativeContainer and boost::PairAssociativeContainer.
- \e SCellMap<Value>: an associative container SCell->Value rebinder type (efficient for key queries). Use as \c typename X::template SCellMap<Value>::Type, which is a model of boost::UniqueAssociativeContainer and boost::PairAssociativeContainer.
- \e SurfelMap<Value>: an associative container Surfel->Value rebinder type (efficient for key queries). Use as \c typename X::template SurfelMap<Value>::Type, which is a model of boost::UniqueAssociativeContainer and boost::PairAssociativeContainer.


\note DirIterator should be use as follows:
@code
KSpace x;
Cell c;
for ( KSpace::DirIterator q = x.uDirs( c ); q != 0; ++q )
  {
    Dimension dir = *q;
    ...
  }
@endcode

### Notation
- \e X : A type that is a model of \e CPreCellularGridSpaceND
- \e x : object of type \e X
- \e k : object of type Dimension
- \e i : object of type \e Integer
- \e c : object of type \e Cell
- \e sc : object of type \e SCell
- \e s : object of type \e Surfel
- \e p, \e p1, \e p2 : object of type \e Point
- \e v : object of type \e Vector
- \e sign: object of type \e Sign

### Definitions

- \b digital coordinates are the natural coordinates of the cells of
  maximal dimension in the cellular space. For instance, it represents
  the coordinates of the pixels in an image. Two adjacent pixels have
  digital coordinates that differ by one in the cellular space. It
  is clear that incident cells (cells of lower dimension) may also
  have the same \e digital coordinates.
- \b Khalimsky coordinates are a way to number cells such that any two
  cells have different coordinates. More precisely, digital
  coordinates are doubled and the odd parity depends on whether or not
  the cell is open along this coordinate axis.
- a \b spel is a cell of maximal dimension (say n), a \b surfel is a
  cell of dimension n-1, a \b pointel is a cell of dimension 0.  Spels
  have thus all their Khalimsky coordinates odd. Surfels have only one
  Khalimsky coordinate that is even. Pointels have all their Khalimsky
  coordinates even.
- the \b topology of a cell along a dimension \e k is open if the cell
  is open along the \e k-th coordinate axis. We code open with 1 and
  closed with 0. The \b topology \b word of a cell is the integer
  whose \e k-th bit is the topology of the cell along the \e k-th
  axis. The \b dimension of a cell is the number of coordinates where
  the cell is open. It is also the sum of the bits of its topology
  word.
- \b adjacent cells to some cell \e c are cells with the same topology
  as \e c but whose one of their digital coordinates differs by
  one. They are often called 1-adjacent.
- \b incident cells to some cell \e c are cells that are either a face
  of \e c or such that \e c is one of their faces.


### Valid expressions and semantics

| Name          | Expression       | Type requirements | Return type   | Precondition | Semantics                             | Post condition | Complexity |
|---------------|------------------|-------------------|---------------|--------------|---------------------------------------|----------------|------------|
| dimension     | \e X::dimension  |                   | \e Dimension  |              | the dimension of the space            |                |            |
| DIM           | \e X::dimension  |                   | \e Dimension  |              | the dimension of the space            |                |            |
| POS           | \e X::POS        |                   | \e Sign       |              | the positive sign for cells           |                |            |
| NEG           | \e X::NEG        |                   | \e Sign       |              | the negative sign for cells           |                |            |
|               |                  |                   |               |              |                                       |                |            |
| Make unsigned cell | \e x.uCell(\e p)|               | \e Cell       |              | returns the unsigned cell with \e Khalimsky coordinates equal to \e p| | |
| Make unsigned cell | \e x.uCell(\e p, \e c)|         | \e Cell       |              | returns the unsigned cell with \e digital coordinates equal to \e p and topology equal to \e c| | |
| Make signed cell | \e x.sCell(\e p, \e sign = POS)|  | \e SCell      |              | returns the signed cell with \e Khalimsky coordinates equal to \e p and sign \e sign| | |
| Make signed cell | \e x.sCell(\e p, \e sc)|          | \e SCell      |              | returns the signed cell with \e digital coordinates equal to \e p and sign and topology equal to \e sc| | |
| Make unsigned spel | \e x.uSpel(\e p)|               | \e Cell       |              | returns the unsigned spel with \e digital coordinates equal to \e p| | |
| Make signed spel | \e x.sSpel(\e p, \e sign = POS)|  | \e SCell      |              | returns the signed spel with \e digital coordinates equal to \e p and sign \e sign| | |
| Make unsigned pointel | \e x.uPointel(\e p)|         | \e Cell       |              | returns the unsigned pointel with \e digital coordinates equal to \e p| | |
| Make signed pointel | \e x.sPointel(\e p, \e sign = POS)| | \e SCell |              | returns the signed pointel with \e digital coordinates equal to \e p and sign \e sign| | |
|               |                  |                   |               |              |                                       |                |            |
| Get Khalimsky coordinate| \e x.uKCoord(\e c, \e k)|  | \e Integer    |              | returns the Khalimsky coordinate of cell \e c along axis \e k | |   |
| Get digital coordinate| \e x.uCoord(\e c, \e k)|     | \e Integer    |              | returns the digital coordinate of cell \e c along axis \e k | |     |
| Get Khalimsky coordinates| \e x.uKCoords(\e c)| | \e Point     |              | returns the Khalimsky coordinates of cell \e c |       |            |
| Get digital coordinates| \e x.uCoords(\e c)|   | \e Point      |              | returns the digital coordinates of cell \e c |         |            |
| Get Khalimsky coordinate| \e x.sKCoord(\e sc, \e k)|  | \e Integer   |              | returns the Khalimsky coordinate of signed cell \e sc along axis \e k | | |
| Get digital coordinate| \e x.sCoord(\e sc, \e k)|     | \e Integer   |              | returns the digital coordinate of signed cell \e sc along axis \e k | | |
| Get Khalimsky coordinates| \e x.sKCoords(\e sc, \e k)| | \e Point    |              | returns the Khalimsky coordinates of signed cell \e sc |       |    |
| Get digital coordinates| \e x.sCoords(\e sc, \e k)|   | \e Point     |              | returns the digital coordinates of signed cell \e sc |         |    |
|               |                  |                   |               |              |                                       |                |            |
| Set Khalimsky coordinate |\e x.uSetKCoord(\e c,\e k,\e i)| |         |              | Sets the \e k-th Khalimsky coordinate of \e c to \e i | |           |
| Set digital coordinate |\e x.uSetCoord(\e c,\e k,\e i)| |            |              | Sets the \e k-th digital coordinate of \e c to \e i |  |            |
| Set Khalimsky coordinates |\e x.uSetKCoords(\e c,\e p)| |            |              | Sets the Khalimsky coordinates of \e c to \e p |       |            |
| Set digital coordinates |\e x.uSetCoords(\e c,\e p)| |               |              | Sets the digital coordinates of \e c to \e p |         |            |
| Set Khalimsky coordinate |\e x.sSetKCoord(\e sc,\e k,\e i)| |        |              | Sets the \e k-th Khalimsky coordinate of \e sc to \e i | |           |
| Set digital coordinate |\e x.sSetCoord(\e sc,\e k,\e i)| |           |              | Sets the \e k-th digital coordinate of \e sc to \e i |  |            |
| Set Khalimsky coordinates |\e x.sSetKCoords(\e sc,\e p)| |           |              | Sets the Khalimsky coordinates of \e sc to \e p |       |            |
| Set digital coordinates |\e x.sSetCoords(\e sc,\e p)| |              |              | Sets the digital coordinates of \e sc to \e p |         |            |
|               |                  |                   |               |              |                                       |                |            |
| Sign/orient cell | \e x.signs(\e c,\e sign)|         |               |              | returns the signed cell with same topology as \e c and sign \e sign| | |
| Change sign   | \e x.sSetSign(\e sc, \e sign)|       |               |              | Sets the sign of the signed cell \e sc to \e sign |    |            |
| Get sign      | \e x.sSign(\e sc)|                   | \e Sign       |              | returns the sign of cell \e sc        |                |            |
| Unsign/unorient signed cell | \e x.unsigns(\e sc)|   |               |              | returns the unsigned cell with same topology as \e sc| | |
| Flip sign     | \e x.sOpp(\e sc) |                   |               |              | returns the signed cell with opposite sign to \e sc| | |
|               |                  |                   |               |              |                                       |                |            |
| Get topology word |\e x.uTopology(\e c) |            | \e Integer    |              | returns the topology word of unsigned cell \e c |      |            |
| Get topology word |\e x.sTopology(\e sc) |           | \e Integer    |              | returns the topology word of signed cell \e sc |       |            |
| Get cell dimension |\e x.uDim(\e c) |                | Dimension     |              | returns the dimension of the unsigned cell \e c |      |            |
| Get cell dimension |\e x.sDim(\e sc) |               | Dimension     |              | returns the dimension of the signed cell \e sc |       |            |
| Surfel test   |\e x.uIsSurfel(\e s) |                | \c bool       |              | returns 'true' iff the unsigned cell \e c has dimension n-1 | |     |
| Surfel test   |\e x.sIsSurfel(\e sc) |               | \c bool       |              | returns 'true' iff the signed cell \e sc has dimension n-1 | |      |
| Open test     |\e x.uIsOpen(\e c,\e k) |             | \c bool       |              | returns 'true' iff the unsigned cell \e c is open along the \e k-th axis| | |
| Open test     |\e x.sIsOpen(\e sc,\e k) |            | \c bool       |              | returns 'true' iff the signed cell \e sc is open along the \e k-th axis| | |
|               |                  |                   |               |              |                                       |                |            |
| Get open directions |\e x.uDirs(\e c)|               | \e DirIterator|              | returns a kind of iterator that enumerates the open directions of \e c| | |
| Get open directions |\e x.sDirs(\e sc)|              | \e DirIterator|              | returns a kind of iterator that enumerates the open directions of \e sc| | |
| Get closed directions |\e x.uOrthDirs(\e c)|         | \e DirIterator|              | returns a kind of iterator that enumerates the closed directions of \e c| | |
| Get closed directions |\e x.sOrthDirs(\e sc)|        | \e DirIterator|              | returns a kind of iterator that enumerates the closed directions of \e sc| | |
| Get closed direction of surfel |\e x.uOrthDir(\e c)|\e x.uIsSurfel(\e c)| Dimension     |              | returns the closed direction of the n-1-cell \e c| | |
| Get closed direction of surfel |\e x.sOrthDir(\e sc)|\e x.sIsSurfel(\e sc)| Dimension    |              | returns the closed direction of the signed n-1-cell \e sc| | |
|               |                  |                   |               |              |                                       |                |            |
| Get next cell along some axis|\e x.uGetIncr(\e c,\e k)| | \e Cell    |              | returns the same cell as \e c except the \e k-th coordinate that is incremented | | |
| Get previous cell along some axis|\e x.uGetDecr(\e c,\e k)| | \e Cell |             | returns the same cell as \e c except the \e k-th coordinate that is decremented | | |
| Maximal coordinate test|\e x.uIsMax(\e c,\e k)|      | \c bool       |              | returns 'true' iff the cell has the maximal possible \e k-th coordinate | | |
| Minimal coordinate test|\e x.uIsMin(\e c,\e k)|      | \c bool       |              | returns 'true' iff the cell has the minimal possible \e k-th coordinate | | |
| Inside test along some axis|\e x.uIsInside(\e c,\e k)| | \c bool     |              | returns 'true' iff the cell \e c has a valid \e k-th coordinate | | |
| Get cell further along some axis|\e x.uGetAdd(\e c,\e k,\e i)| | \e Cell|           | returns the same cell as \e c except the \e k-th coordinate that is increased by \e i | | |
| Get cell before along some axis|\e x.uGetSub(\e c,\e k,\e i)| | \e Cell|            | returns the same cell as \e c except the \e k-th coordinate that is decreased by \e i | | |
| Get the translation of a cell |\e x.uTranslation(\e c,\e v)| | \e Cell  |           | returns the cell that is the translation of \e c by the vector \e v | | |
| Get the projection of a cell |\e x.uProjection(\e c,\e bc,\e k)| \e bc is a \e Cell| \e Cell | | returns the same cell as \e c except for the \e k-th coordinate that is equal to the one of \e bc | | |
| Projection of a cell |\e x.uProject(\e c,\e bc,\e k)| \e bc is a \e Cell| |         | modifies cell \e c such that its \e k-th coordinate that is equal to the one of \e bc | | |
| Next cell within bounds |\e x.uNext(\e c,\e lc,\e uc)| \e lc, \e uc are \e Cell|\c bool|  | cell \e c becomes the next cell with same topology within lower and upper bounds \e lc and \e uc, returns 'true' iff \e c is still within bounds | | |
|               |                  |                   |               |              |                                       |                |            |
| Get next cell along some axis|\e x.sGetIncr(\e sc,\e k)| | \e SCell  |              | returns the same cell as \e sc except the \e k-th coordinate that is incremented | | |
| Get previous cell along some axis|\e x.sGetDecr(\e sc,\e k)| | \e SCell |           | returns the same cell as \e sc except the \e k-th coordinate that is decremented | | |
| Maximal coordinate test|\e x.sIsMax(\e sc,\e k)|      | \c bool      |              | returns 'true' iff the cell has the maximal possible \e k-th coordinate | | |
| Minimal coordinate test|\e x.sIsMin(\e sc,\e k)|      | \c bool      |              | returns 'true' iff the cell has the minimal possible \e k-th coordinate | | |
| Inside test along some axis|\e x.sIsInside(\e sc,\e k)| | \c bool    |              | returns 'true' iff the cell \e sc has a valid \e k-th coordinate | | |
| Get cell further along some axis|\e x.sGetAdd(\e sc,\e k,\e i)| | \e SCell|         | returns the same cell as \e sc except the \e k-th coordinate that is increased by \e i | | |
| Get cell before along some axis|\e x.sGetSub(\e sc,\e k,\e i)| | \e SCell|          | returns the same cell as \e sc except the \e k-th coordinate that is decreased by \e i | | |
| Get the translation of a cell |\e x.sTranslation(\e sc,\e v)| | \e SCell  |         | returns the cell that is the translation of \e sc by the vector \e v | | |
| Get the projection of a cell |\e x.sProjection(\e sc,\e bc,\e k)| \e bc is a \e SCell| \e SCell | | returns the same cell as \e sc except for the \e k-th coordinate that is equal to the one of \e bc | | |
| Projection of a cell |\e x.sProject(\e sc,\e bc,\e k)| \e bc is a \e SCell| |       | modifies cell \e sc such that its \e k-th coordinate that is equal to the one of \e bc | | |
| Next cell within bounds |\e x.sNext(\e sc,\e lc,\e uc)| \e lc, \e uc are \e SCell|\c bool|  | cell \e sc becomes the next cell with same topology within lower and upper bounds \e lc and \e uc, returns 'true' iff \e sc is still within bounds | | |
|               |                  |                   |               |              |                                       |                |            |
| Neighborhood |\e x.uNeighborhood(\e c) |             | \e Cells      |              | returns the range of cells that forms the 1-neighborhood of \e c | | |
| Neighborhood |\e x.sNeighborhood(\e sc)|             | \e SCells     |              | returns the range of signed cells that forms the 1-neighborhood of \e sc | | |
| Proper neighborhood |\e x.uProperNeighborhood(\e c) | | \e Cells     |              | returns the range of cells that forms the proper 1-neighborhood of \e c, hence without \e c itself| | |
| Proper neighborhood |\e x.sProperNeighborhood(\e sc)| | \e SCells    |              | returns the range of signed cells that forms the proper 1-neighborhood of \e sc, hence without \e sc itself| | |
| Adjacent cell|\e x.uAdjacent(\e c,\e k,\e b)|\e b is a \c bool |\e Cell |           | return the cell adjacent to \e c along axis \e k either with greater coordinate (\e b is \c true) or lesser | | |
| Adjacent cell|\e x.sAdjacent(\e sc,\e k,\e b)|\e b is a \c bool |\e SCell |         | return the signed cell adjacent to \e sc along axis \e k either with greater coordinate (\e b is \c true) or lesser | | |
|               |                  |                   |               |              |                                       |                |            |
| Incident cell|\e x.uIncident(\e c,\e k,\e b)|\e b is a \c bool |\e Cell |           | return the cell incident to \e c along axis \e k either with greater coordinate (\e b is \c true) or lesser | | |
| Incident cell|\e x.sIncident(\e sc,\e k,\e b)|\e b is a \c bool |\e SCell |         | return the signed cell incident to \e sc along axis \e k either with greater coordinate (\e b is \c true) or lesser | | |
| Lower incident cells|\e x.uLowerIncident(\e c)|      |\e Cells       |              | return all the cells just lower incident to \e c (1-dim less) | | |
| Lower incident cells|\e x.sLowerIncident(\e sc)|     |\e SCells      |              | return all the signed cells just lower incident to \e sc (1-dim less) | | |
| Upper incident cells|\e x.uUpperIncident(\e c)|      |\e Cells       |              | return all the cells just upper incident to \e c (1-dim more) | | |
| Upper incident cells|\e x.sUpperIncident(\e sc)|     |\e SCells      |              | return all the signed cells just upper incident to \e c (1-dim more) | | |
| Faces of a cell|\e x.uFaces(\e c)|                   |\e Cells       |              | return all the faces of the cell \e c | | |
| Co-Faces of a cell|\e x.uCoFaces(\e c)|              |\e Cells       |              | return all the co-faces of the cell \e c | | |
| Direct orientation|\e x.sDirect(\e sc,\e k)|         |\c bool        |              | return the direct orientation of cell \e sc along axis \e k | | |
| Direct incident cell|\e x.sDirectIncident(\e sc,\e k)| |\e SCell     |              | return the signed cell that is the direct incident cell to \e sc along axis \e k | | |
| Indirect incident cell|\e x.sIndirectIncident(\e sc,\e k)| |\e SCell |              | return the signed cell that is the indirect incident cell to \e sc along axis \e k | | |


### Invariants

### Models

- KhalimskyPreSpaceND

### Notes

@tparam T the type that should be a model of CPreCellularGridSpaceND.
 */
template <typename T>
struct CPreCellularGridSpaceND
  : boost::DefaultConstructible<T>, boost::CopyConstructible<T>
{
  // ----------------------- Concept checks ------------------------------
public:
  typedef typename T::Integer Integer;
  typedef typename T::Space Space;
  typedef typename T::PreCellularGridSpace PreCellularGridSpace;
  typedef typename T::Cell Cell;
  typedef typename T::SCell SCell;
  typedef typename T::Surfel Surfel;
  typedef typename T::Sign Sign;
  typedef typename T::DirIterator DirIterator;
  typedef typename T::Point Point;
  typedef typename T::Vector Vector;
  typedef typename T::Cells Cells;
  typedef typename T::SCells SCells;
  typedef typename T::CellSet CellSet;
  typedef typename T::SCellSet SCellSet;
  typedef typename T::SurfelSet SurfelSet;
  typedef int Dummy;
  typedef typename T::template CellMap<Dummy>::Type CellMap;
  typedef typename T::template SCellMap<Dummy>::Type SCellMap;
  typedef typename T::template SurfelMap<Dummy>::Type SurfelMap;

  BOOST_CONCEPT_ASSERT(( CInteger< Integer > ));
  BOOST_STATIC_ASSERT(( ConceptUtils::SameType< Integer, typename Space::Integer >::value ));
  BOOST_STATIC_ASSERT(( ConceptUtils::SameType< Point, typename Space::Point >::value ));
  BOOST_STATIC_ASSERT(( ConceptUtils::SameType< Vector, typename Space::Vector >::value ));
  BOOST_CONCEPT_ASSERT(( CConstSinglePassRange< Cells > ));
  BOOST_CONCEPT_ASSERT(( CConstSinglePassRange< SCells > ));
  BOOST_CONCEPT_ASSERT(( boost::UniqueAssociativeContainer< CellSet > ));
  BOOST_CONCEPT_ASSERT(( boost::UniqueAssociativeContainer< SCellSet > ));
  BOOST_CONCEPT_ASSERT(( boost::UniqueAssociativeContainer< SurfelSet > ));
  BOOST_CONCEPT_ASSERT(( boost::SimpleAssociativeContainer< CellSet > ));
  BOOST_CONCEPT_ASSERT(( boost::SimpleAssociativeContainer< SCellSet > ));
  BOOST_CONCEPT_ASSERT(( boost::SimpleAssociativeContainer< SurfelSet > ));
  BOOST_CONCEPT_ASSERT(( boost::UniqueAssociativeContainer< CellMap > ));
  BOOST_CONCEPT_ASSERT(( boost::UniqueAssociativeContainer< SCellMap > ));
  BOOST_CONCEPT_ASSERT(( boost::UniqueAssociativeContainer< SurfelMap > ));
  BOOST_CONCEPT_ASSERT(( boost::PairAssociativeContainer< CellMap > ));
  BOOST_CONCEPT_ASSERT(( boost::PairAssociativeContainer< SCellMap > ));
  BOOST_CONCEPT_ASSERT(( boost::PairAssociativeContainer< SurfelMap > ));

  BOOST_CONCEPT_USAGE( CPreCellularGridSpaceND )
  {
    ConceptUtils::sameType( myDim, T::dimension );
    ConceptUtils::sameType( myDim, T::DIM );
    ConceptUtils::sameType( mySign, T::POS );
    ConceptUtils::sameType( mySign, T::NEG );
    checkConstConstraints();
  }
  void checkConstConstraints() const
  {
    ConceptUtils::sameType( myCell, myX.uCell( myP1 ) );
    ConceptUtils::sameType( myCell, myX.uCell( myP1, myCell ) );
    ConceptUtils::sameType( mySCell, myX.sCell( myP1 ) );
    ConceptUtils::sameType( mySCell, myX.sCell( myP1, mySign ) );
    ConceptUtils::sameType( mySCell, myX.sCell( myP1, mySCell ) );
    ConceptUtils::sameType( myCell, myX.uSpel( myP1 ) );
    ConceptUtils::sameType( mySCell, myX.sSpel( myP1 ) );
    ConceptUtils::sameType( mySCell, myX.sSpel( myP1, myBool ) );
    ConceptUtils::sameType( myCell, myX.uPointel( myP1 ) );
    ConceptUtils::sameType( mySCell, myX.sPointel( myP1 ) );
    ConceptUtils::sameType( mySCell, myX.sPointel( myP1, myBool ) );
    ConceptUtils::sameType( myInteger, myX.uKCoord( myCell, myDim ) );
    ConceptUtils::sameType( myInteger, myX.uCoord( myCell, myDim ) );
    ConceptUtils::sameType( myP1, myX.uKCoords( myCell ) );
    ConceptUtils::sameType( myP1, myX.uCoords( myCell ) );
    ConceptUtils::sameType( myInteger, myX.sKCoord( mySCell, myDim ) );
    ConceptUtils::sameType( myInteger, myX.sCoord( mySCell, myDim ) );
    ConceptUtils::sameType( myP1, myX.sKCoords( mySCell ) );
    ConceptUtils::sameType( myP1, myX.sCoords( mySCell ) );
    myX.uSetKCoord( myMutableCell, myDim, myInteger );
    myX.uSetCoord( myMutableCell, myDim, myInteger );
    myX.uSetKCoords( myMutableCell, myP1 );
    myX.uSetCoords( myMutableCell, myP1 );
    myX.sSetKCoord( myMutableSCell, myDim, myInteger );
    myX.sSetCoord( myMutableSCell, myDim, myInteger );
    myX.sSetKCoords( myMutableSCell, myP1 );
    myX.sSetCoords( myMutableSCell, myP1 );
    ConceptUtils::sameType( mySign, myX.sSign( mySCell ) );
    myX.sSetSign( myMutableSCell, mySign );
    ConceptUtils::sameType( mySCell, myX.signs( myCell, mySign ) );
    ConceptUtils::sameType( mySCell, myX.sOpp( mySCell ) );
    ConceptUtils::sameType( myCell, myX.unsigns( mySCell ) );
    ConceptUtils::sameType( myInteger, myX.uTopology( myCell ) );
    ConceptUtils::sameType( myInteger, myX.sTopology( mySCell ) );
    ConceptUtils::sameType( myDim, myX.uDim( myCell ) );
    ConceptUtils::sameType( myDim, myX.sDim( mySCell ) );
    ConceptUtils::sameType( myBool, myX.uIsSurfel( myCell ) );
    ConceptUtils::sameType( myBool, myX.sIsSurfel( mySCell ) );
    ConceptUtils::sameType( myBool, myX.uIsOpen( myCell, myDim ) );
    ConceptUtils::sameType( myBool, myX.sIsOpen( mySCell, myDim ) );
    ConceptUtils::sameType( myDirIt, myX.uDirs( myCell ) );
    ConceptUtils::sameType( myDirIt, myX.sDirs( mySCell ) );
    ConceptUtils::sameType( myDirIt, myX.uOrthDirs( myCell ) );
    ConceptUtils::sameType( myDirIt, myX.sOrthDirs( mySCell ) );
    ConceptUtils::sameType( myDim, myX.uOrthDir( myCell ) );
    ConceptUtils::sameType( myDim, myX.sOrthDir( mySCell ) );
    // -------------------- Unsigned cell geometry services --------------------
    ConceptUtils::sameType( myCell, myX.uGetIncr( myCell, myDim ) );
    ConceptUtils::sameType( myCell, myX.uGetDecr( myCell, myDim ) );
    ConceptUtils::sameType( myBool, myX.uIsMax( myCell, myDim ) );
    ConceptUtils::sameType( myBool, myX.uIsMin( myCell, myDim ) );
    ConceptUtils::sameType( myBool, myX.uIsInside( myCell, myDim ) );
    ConceptUtils::sameType( myCell, myX.uGetAdd( myCell, myDim, myInteger ) );
    ConceptUtils::sameType( myCell, myX.uGetSub( myCell, myDim, myInteger ) );
    ConceptUtils::sameType( myCell, myX.uTranslation( myCell, myV ) );
    ConceptUtils::sameType( myCell, myX.uProjection( myCell, myCell, myDim ) );
    myX.uProject( myMutableCell, myCell, myDim );
    ConceptUtils::sameType( myBool, myX.uNext( myMutableCell, myCell, myCell ) );
    // -------------------- Signed cell geometry services --------------------
    ConceptUtils::sameType( mySCell, myX.sGetIncr( mySCell, myDim ) );
    ConceptUtils::sameType( mySCell, myX.sGetDecr( mySCell, myDim ) );
    ConceptUtils::sameType( myBool, myX.sIsMax( mySCell, myDim ) );
    ConceptUtils::sameType( myBool, myX.sIsMin( mySCell, myDim ) );
    ConceptUtils::sameType( myBool, myX.sIsInside( mySCell, myDim ) );
    ConceptUtils::sameType( mySCell, myX.sGetAdd( mySCell, myDim, myInteger ) );
    ConceptUtils::sameType( mySCell, myX.sGetSub( mySCell, myDim, myInteger ) );
    ConceptUtils::sameType( mySCell, myX.sTranslation( mySCell, myV ) );
    ConceptUtils::sameType( mySCell, myX.sProjection( mySCell, mySCell, myDim ) );
    myX.sProject( myMutableSCell, mySCell, myDim );
    ConceptUtils::sameType( myBool, myX.sNext( myMutableSCell, mySCell, mySCell ) );
    // ----------------------- Neighborhood services --------------------------
    ConceptUtils::sameType( myCells, myX.uNeighborhood( myCell ) );
    ConceptUtils::sameType( myCells, myX.uProperNeighborhood( myCell ) );
    ConceptUtils::sameType( mySCells, myX.sNeighborhood( mySCell ) );
    ConceptUtils::sameType( mySCells, myX.sProperNeighborhood( mySCell ) );
    ConceptUtils::sameType( myCell, myX.uAdjacent( myCell, myDim, myBool ) );
    ConceptUtils::sameType( mySCell, myX.sAdjacent( mySCell, myDim, myBool ) );
    // ----------------------- Incidence services --------------------------
    ConceptUtils::sameType( myCell, myX.uIncident( myCell, myDim, myBool ) );
    ConceptUtils::sameType( mySCell, myX.sIncident( mySCell, myDim, myBool ) );
    ConceptUtils::sameType( myCells, myX.uLowerIncident( myCell ) );
    ConceptUtils::sameType( myCells, myX.uUpperIncident( myCell ) );
    ConceptUtils::sameType( mySCells, myX.sLowerIncident( mySCell ) );
    ConceptUtils::sameType( mySCells, myX.sUpperIncident( mySCell ) );
    ConceptUtils::sameType( myCells, myX.uFaces( myCell ) );
    ConceptUtils::sameType( myCells, myX.uCoFaces( myCell ) );
    ConceptUtils::sameType( myBool, myX.sDirect( mySCell, myDim ) );
    ConceptUtils::sameType( mySCell, myX.sDirectIncident( mySCell, myDim ) );
    ConceptUtils::sameType( mySCell, myX.sIndirectIncident( mySCell, myDim ) );

}
  // ------------------------- Private Datas --------------------------------
private:
  T myX; // do not require T to be default constructible.
  Integer myInteger;
  Dimension myDim;
  Point myP1, myP2;
  Vector myV;
  Cell myCell;
  SCell mySCell;
  mutable Cell myMutableCell;
  mutable SCell myMutableSCell;
  bool myBool;
  Sign mySign;
  DirIterator myDirIt;
  Cells myCells;
  SCells mySCells;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CPreCellularGridSpaceND

} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CPreCellularGridSpaceND_h

#undef CPreCellularGridSpaceND_RECURSES
#endif // else defined(CPreCellularGridSpaceND_RECURSES)
