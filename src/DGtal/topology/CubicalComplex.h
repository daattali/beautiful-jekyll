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
* @file CubicalComplex.h
* @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
* Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
*
* @date 2015/08/28
*
* Header file for module CubicalComplex.cpp
*
* This file is part of the DGtal library.
*/

#if defined(CubicalComplex_RECURSES)
#error Recursive header files inclusion detected in CubicalComplex.h
#else // defined(CubicalComplex_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CubicalComplex_RECURSES

#if !defined CubicalComplex_h
/** Prevents repeated inclusion of headers. */
#define CubicalComplex_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/type_traits.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/base/Alias.h"
#include "DGtal/base/ContainerTraits.h"
#include "DGtal/base/CSTLAssociativeContainer.h"
#include "DGtal/topology/CCellularGridSpaceND.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /**
  * Any cell is stored within a cubical complex with an associated
  * data. You may define your own associated data but the type must
  * derive from this class CubicalCellData. Its basic usage is to
  * store flags associated to the cells, but it may store other
  * values.
  *
  * @note Predefined flags are CubicalComplex::REMOVED,
  * CubicalComplex::COLLAPSIBLE, CubicalComplex::FIXED,
  * CubicalComplex::USER1. Other bits can be used to associate an
  * integer to the cell. The corresponding mask is
  * CubicalComplex::VALUE.
  *
  * @note Such data is notably used in collapse operation
  * (CubicalComplex::collapse).
  */
  struct CubicalCellData {
    inline CubicalCellData() : data( 0 ) {}
    CubicalCellData( uint32_t d ) : data( d ) {}
    uint32_t data;
  };

  // Forward definitions.
  template < typename TKSpace, typename TCellContainer >
  class CubicalComplex;

  namespace functions {
    template < typename TKSpace, typename TCellContainer >
    CubicalComplex< TKSpace, TCellContainer >&
    operator|=( CubicalComplex< TKSpace, TCellContainer >&,
                const CubicalComplex< TKSpace, TCellContainer >& );
    template < typename TKSpace, typename TCellContainer >
    CubicalComplex< TKSpace, TCellContainer >&
    operator&=( CubicalComplex< TKSpace, TCellContainer >&,
                const CubicalComplex< TKSpace, TCellContainer >& );
    template < typename TKSpace, typename TCellContainer >
    CubicalComplex< TKSpace, TCellContainer >&
    operator^=( CubicalComplex< TKSpace, TCellContainer >&,
                const CubicalComplex< TKSpace, TCellContainer >& );
    template < typename TKSpace, typename TCellContainer >
    CubicalComplex< TKSpace, TCellContainer >&
    operator-=( CubicalComplex< TKSpace, TCellContainer >&,
                const CubicalComplex< TKSpace, TCellContainer >& );
    template < typename TKSpace, typename TCellContainer >
    CubicalComplex< TKSpace, TCellContainer >
    operator| ( const CubicalComplex< TKSpace, TCellContainer >&,
                const CubicalComplex< TKSpace, TCellContainer >& );
    template < typename TKSpace, typename TCellContainer >
    CubicalComplex< TKSpace, TCellContainer >
    operator& ( const CubicalComplex< TKSpace, TCellContainer >&,
                const CubicalComplex< TKSpace, TCellContainer >& );
    template < typename TKSpace, typename TCellContainer >
    CubicalComplex< TKSpace, TCellContainer >
    operator^ ( const CubicalComplex< TKSpace, TCellContainer >&,
                const CubicalComplex< TKSpace, TCellContainer >& );
    template < typename TKSpace, typename TCellContainer >
    CubicalComplex< TKSpace, TCellContainer >
    operator- ( const CubicalComplex< TKSpace, TCellContainer >&,
                const CubicalComplex< TKSpace, TCellContainer >& );

    template < typename TKSpace, typename TCellContainer >
    CubicalComplex< TKSpace, TCellContainer >
    operator~ ( const CubicalComplex< TKSpace, TCellContainer >& );
    template < typename TKSpace, typename TCellContainer >
    CubicalComplex< TKSpace, TCellContainer >
    operator* ( const CubicalComplex< TKSpace, TCellContainer >& );

    template < typename TKSpace, typename TCellContainer >
    bool
    operator==( const CubicalComplex< TKSpace, TCellContainer >&,
                const CubicalComplex< TKSpace, TCellContainer >& );
    template < typename TKSpace, typename TCellContainer >
    bool
    operator!=( const CubicalComplex< TKSpace, TCellContainer >&,
                const CubicalComplex< TKSpace, TCellContainer >& );
    template < typename TKSpace, typename TCellContainer >
    bool
    operator<=( const CubicalComplex< TKSpace, TCellContainer >&,
                const CubicalComplex< TKSpace, TCellContainer >& );
    template < typename TKSpace, typename TCellContainer >
    bool
    operator>=( const CubicalComplex< TKSpace, TCellContainer >&,
                const CubicalComplex< TKSpace, TCellContainer >& );
  } // namespace functions


  /////////////////////////////////////////////////////////////////////////////
  // template class CubicalComplex
  /**
  * Description of template class 'CubicalComplex' <p> \brief Aim:
  * This class represents an arbitrary cubical complex living in some
  * Khalimsky space. Cubical complexes are sets of cells of different
  * dimensions related together with incidence relations. Two cells
  * in a cubical complex are incident if and only if they are
  * incident in the surrounding Khalimsky space. In other words,
  * cubical complexes are defined here as subsets of Khalimsky spaces.
  *
  * A cubical complex is a (immutable) model of boost::Container and
  * offers forward iterators to enumerate elements. It is close from
  * being an AssociativeContainer, but values are not sorted (they are
  * sorted per dimension), and are not modifiable. It is not exactly a
  * container in the usual sense because it cannot be constructed by
  * default, and because iterators may not modified values.
  *
  * @tparam TKSpace any model of concepts::CCellularGridSpaceND, i.e. a type
  * that models a Khalimsky space.
  *
  * @tparam TCellContainer any model of associative container, mapping
  * a KSpace::Cell to a CubicalCellData or any type deriving from
  * it. It could be for instance a std::map or a
  * std::unordered_map. Note that unfortunately, unordered_map are
  * (strangely) not models of boost::AssociativeContainer, hence we
  * cannot check concepts here.
  *
  */
  template < typename TKSpace,
             typename TCellContainer = typename TKSpace::template CellMap< CubicalCellData >::Type >
  class CubicalComplex
  {
    // ----------------------- associated types ------------------------------
  public:
    typedef CubicalComplex< TKSpace, TCellContainer > Self;

    BOOST_CONCEPT_ASSERT(( concepts::CCellularGridSpaceND< TKSpace > ));
    BOOST_STATIC_ASSERT( IsPairAssociativeContainer< TCellContainer >::value );

    // JOL: Not used, because unordered_set and unordered_map do not pass
    // these concept checks.
    // BOOST_CONCEPT_ASSERT(( boost::AssociativeContainer< TCellContainer > ));
    // BOOST_CONCEPT_ASSERT(( boost::PairAssociativeContainer< TCellContainer > ));
    BOOST_CONCEPT_ASSERT(( concepts::CSTLAssociativeContainer< TCellContainer > ));

    friend Self& DGtal::functions::operator|=<>( Self&, const Self& );
    friend Self& DGtal::functions::operator&=<>( Self&, const Self& );
    friend Self& DGtal::functions::operator^=<>( Self&, const Self& );
    friend Self& DGtal::functions::operator-=<>( Self&, const Self& );
    friend Self  DGtal::functions::operator| <>( const Self&, const Self& );
    friend Self  DGtal::functions::operator& <>( const Self&, const Self& );
    friend Self  DGtal::functions::operator^ <>( const Self&, const Self& );
    friend Self  DGtal::functions::operator- <>( const Self&, const Self& );
    friend Self  DGtal::functions::operator~ <>( const Self& );
    friend Self  DGtal::functions::operator* <>( const Self& );
    friend bool  DGtal::functions::operator==<>( const Self&, const Self& );
    friend bool  DGtal::functions::operator!=<>( const Self&, const Self& );
    friend bool  DGtal::functions::operator<=<>( const Self&, const Self& );
    friend bool  DGtal::functions::operator>=<>( const Self&, const Self& );

    typedef TKSpace                             KSpace;        ///< Type of the cellular grid space.
    typedef TCellContainer                      CellContainer; ///< Type for storing cells, an associative container Cell -> Data
    typedef typename CellContainer::mapped_type Data;          ///< Type of data associated to each cell.

    BOOST_STATIC_ASSERT (( boost::is_base_of< CubicalCellData, Data >::value ));
    BOOST_STATIC_ASSERT (( boost::is_same< typename TKSpace::Cell, typename CellContainer::key_type >::value ));


    /// The dimension of the embedding space.
    static const Dimension dimension = KSpace::dimension;
    typedef typename KSpace::Integer     Integer;     ///< Type for integers in the space.
    typedef typename KSpace::Cell        Cell;        ///< Type for a cell in the space.
    typedef typename KSpace::Cells       Cells;       ///< Type for a sequence of cells in the space.
    typedef typename KSpace::Space       Space;       ///< Type of the digital space
    typedef typename KSpace::Size        Size;        ///< Type for a number of elements
    typedef typename KSpace::Point       Point;       ///< Type for a point in the digital space
    typedef typename KSpace::DirIterator DirIterator; ///< Type for iterating over cell directions
    typedef CellContainer                CellMap;     ///< Type for storing cells, an associative container Cell -> Data
    typedef typename CellMap::const_iterator CellMapConstIterator; ///< Const iterator for visiting type CellMap
    typedef typename CellMap::iterator   CellMapIterator;          ///< Iterator for visiting type CellMap


    /// Possible cell types within a complex.
    enum CellType {
      Maximal /**< The cell has no proper coface */,
      Free    /**< The cell has 1 proper coface */,
      Any     /**< The cell has strictly more than 2 proper cofaces.*/
    };

    /// Flag Used to indicate in a cell data that this cell has been (virtually) removed.
    BOOST_STATIC_CONSTANT( uint32_t, REMOVED     = 0x10000000 );
    /// Flag Used to indicate in a cell data that this cell is collapsible.
    BOOST_STATIC_CONSTANT( uint32_t, COLLAPSIBLE = 0x20000000 );
    /// Flag Used to indicate in a cell data that this cell is fixed.
    BOOST_STATIC_CONSTANT( uint32_t, FIXED       = 0x40000000 );
    /// User flag for a cell.
    BOOST_STATIC_CONSTANT( uint32_t, USER1       = 0x80000000 );
    /// Value for a cell.
    BOOST_STATIC_CONSTANT( uint32_t, VALUE       = 0x0fffffff );

    // ----------------------- inner types ------------------------------------

    /**
    * This structure is used to order cells (represented by their
    * iterator in the CubicalComplex container) in a priority queue.
    * By default, it compares the values associated to each cell (the
    * value is the cell data masked by VALUE).
    */
    struct DefaultCellMapIteratorPriority {

      /**
      * This operator compares two cells specified by their iterators
      * \a it1 and \a it2 and returns true whenever \a it1 has
      * smallest data & VALUE than \a it2.
      *
      * @param it1 any iterator on a cell of this cubical complex.
      * @param it2 any iterator on a cell of this cubical complex.
      * @return 'true' iff the value part of the data of \a it1 is smaller than the one of \a it2.
      */
      bool operator()( const CellMapIterator& it1, const CellMapIterator& it2 ) const
      {
        uint32_t v1 = it1->second.data & VALUE;
        uint32_t v2 = it2->second.data & VALUE;
        return ( v1 < v2 )
          || ( ( v1 == v2 ) && ( it1->first < it2->first ) );
      }
    };

    /**
     * An non-mutable iterator class to visit all the cells (and not their datas)
     * of the complex. A model of boost::ForwardIterator.
     */
    struct ConstIterator
      : public boost::iterator_facade< ConstIterator, Cell const,
                                       std::forward_iterator_tag >
    {
      friend class CubicalComplex;

      typedef boost::iterator_facade< ConstIterator, Cell const,
                                      std::forward_iterator_tag > Base;
      typedef ConstIterator                  Self;
      typedef typename Base::value_type      Value;
      typedef typename Base::pointer         Pointer;
      typedef typename Base::reference       Reference;
      typedef typename Base::difference_type DifferenceType;

      /// Default iterator. Invalid.
      ConstIterator() : myCC( 0 ), myD( 0 ) {}

      /**
       * Constructor from complex \a cc and cell dimension \a d.
       * If the dimension is lower or equal to the dimension of the complex,
       *
       * @param cc any valid cubical complex that is aliased in the iterator.
       * @param d the dimension of the starting cell.
       *
       */
      ConstIterator( ConstAlias<CubicalComplex> cc, Dimension d )
        : myCC( &cc ), myD( d )
      {
        if ( myD <= myCC->dimension )
          {
            myIt    = myCC->begin( myD );
            myItEnd = myCC->end( myD );
            nextDimension();
          }
        else
          {
            myD     = myCC->dimension + 1;
            myIt    = myCC->end( myCC->dimension );
            myItEnd = myCC->end( myCC->dimension );
          }
      }

      /**
       * Detailed constructor from complex \a cc, cell dimension \a d and iterators.
       *
       * @param cc any valid cubical complex that is aliased in the iterator.
       * @param d the dimension of the starting cell (0<=d<=dimension).
       * @param it an iterator pointing on a cell of the complex.
       */
      ConstIterator( ConstAlias<CubicalComplex> cc, Dimension d,
                     CellMapConstIterator it )
        : myCC( &cc ), myD( d ), myIt( it )
      {
        ASSERT( d <= myCC->dimension );
        myItEnd = myCC->end( d );
        nextDimension();
      }

    private:
      friend class boost::iterator_core_access;

      void nextDimension()
      {
        while ( myIt == myItEnd )
          {
            if ( ++myD > myCC->dimension ) break;
            myIt    = myCC->begin( myD );
            myItEnd = myCC->end( myD );
          }
      }

      void increment()
      {
        ASSERT( myCC != 0 );
        ++myIt;
        nextDimension();
      }

      bool equal( const ConstIterator& other ) const
      {
        return ( myD == other.myD ) && ( myIt == other.myIt );
      }

      Cell const& dereference() const
      {
        return myIt->first;
      }

      Dimension dimension() const
      {
        return myD;
      }

    private:
      const CubicalComplex* myCC;
      Dimension myD;
      CellMapConstIterator myIt;
      CellMapConstIterator myItEnd;
    };

    /**
     * A mutable iterator class to visit all the cells (and not their
     * datas) of the complex. A model of boost::ForwardIterator. Note
     * that, as for associative container, values are not modifiable.
     */
    struct Iterator
      : public boost::iterator_facade< Iterator, Cell const,
                                       std::forward_iterator_tag >
    {
      friend class CubicalComplex;

      typedef boost::iterator_facade< Iterator, Cell const,
                                      std::forward_iterator_tag > Base;
      typedef Iterator                       Self;
      typedef typename Base::value_type      Value;
      typedef typename Base::pointer         Pointer;
      typedef typename Base::reference       Reference;
      typedef typename Base::difference_type DifferenceType;

      /// Default iterator. Invalid.
      Iterator() : myCC( 0 ), myD( 0 ) {}

      /**
       * Constructor from complex \a cc and cell dimension \a d.
       *
       * @param cc any valid cubical complex that is aliased in the iterator.
       * @param d the dimension of the starting cell.
       *
       */
      Iterator( Alias<CubicalComplex> cc, Dimension d )
        : myCC( &cc ), myD( d )
      {
        if ( myD <= myCC->dimension )
          {
            myIt    = myCC->begin( myD );
            myItEnd = myCC->end( myD );
            nextDimension();
          }
        else
          {
            myD     = myCC->dimension + 1;
            myIt    = myCC->end( myCC->dimension );
            myItEnd = myCC->end( myCC->dimension );
          }
      }

      /**
       * Detailed constructor from complex \a cc, cell dimension \a d and iterators.
       *
       * @param cc any valid cubical complex that is aliased in the iterator.
       * @param d the dimension of the starting cell (0<=d<=dimension).
       * @param it an iterator pointing on a cell of the complex.
       */
      Iterator( Alias<CubicalComplex> cc, Dimension d,
                CellMapIterator it )
        : myCC( &cc ), myD( d ), myIt( it )
      {
        ASSERT( d <= myCC->dimension );
        myItEnd = myCC->end( d );
        nextDimension();
      }

    private:
      friend class boost::iterator_core_access;

      void nextDimension()
      {
        while ( myIt == myItEnd )
          {
            if ( ++myD > myCC->dimension ) break;
            myIt    = myCC->begin( myD );
            myItEnd = myCC->end( myD );
          }
      }

      void increment()
      {
        ASSERT( myCC != 0 );
        ++myIt;
        nextDimension();
      }

      bool equal( const Iterator& other ) const
      {
        return ( myD == other.myD ) && ( myIt == other.myIt );
      }

      Cell const& dereference() const
      {
        return myIt->first;
      }

      Dimension dimension() const
      {
        return myD;
      }

    private:
      CubicalComplex* myCC;
      Dimension myD;
      CellMapIterator myIt;
      CellMapIterator myItEnd;
    };

    // ----------------------- STL inner types ------------------------------
  public:

    // Renaming for STL-type of iterator.
    typedef ConstIterator                           const_iterator;
    typedef Iterator                                iterator;
    typedef Cell                                    value_type;
    typedef Cell const&                             reference;
    typedef Cell const&                             const_reference;
    typedef typename CellContainer::size_type       size_type;
    typedef typename CellContainer::difference_type difference_type;
    typedef Cell const*                             pointer;
    typedef Cell const*                             const_pointer;

    // ----------------------- Standard services ------------------------------
  public:

    /**
    * Destructor.
    */
    ~CubicalComplex();

  protected:
    /**
    * Constructor. The cubical complex is not valid. A user may not
    * instantiate an empty CubicalComplex, because it needs the
    * Khalimsky space.
    */
    CubicalComplex();
  public:

    /**
    * Constructor of empty complex. Needs a space to represents
    * cubical cells.
    *
    * @param aK a Khalimsky space.
    */
    CubicalComplex ( ConstAlias<KSpace> aK );

    /**
    * Copy constructor.
    * @param other the object to clone.
    * Forbidden by default.
    */
    CubicalComplex ( const CubicalComplex & other );

    /**
    * Constructor a complex from a digital set.
    * @param set - a digital set from which to create a complex.
    * Set has to be of the same dimension as a Khalimsky space.
    */
    template < typename TDigitalSet >
    void construct ( const TDigitalSet & set );

    /**
    * Assignment.
    * @param other the object to copy.
    * @return a reference on 'this'.
    * Forbidden by default.
    */
    CubicalComplex & operator= ( const CubicalComplex & other );

    /**
    * Clears the cubical complex, which becomes empty.
    */
    void clear();

    /**
    * Clears all cells of dimension \a d of the cubical complex.
    * @param d the dimension of cell \a aCell.
    */
    void clear( Dimension d );

    /**
    * Fills the data of every cell of this cubical complex, which
    * becomes \a data. Default value resets the data to zero.
    *
    * @param data any data.
    */
    void fillData( Data data = Data() );

    /**
    * Fills the data of every cell of dimension \a d this cubical
    * complex, which becomes \a data. Default value resets the data to
    * zero.
    *
    * @param d the dimension of cell \a aCell.
    * @param data any data.
    */
    void fillData( Dimension d, Data data = Data() );

    /**
    * @return the maximal dimension of a cell in the complex, 0 if
    * the complex is empty.
    */
    Dimension dim() const;

    /**
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @return the dimension of the cell \a aCell.
    */
    Dimension dim( const Cell& aCell ) const;

    /**
    * @param d the dimension of cells.
    * @return the number of cells of dimension \a d in this complex.
    */
    Size nbCells( Dimension d ) const;

    /**
    * @note For instance, all Platonician solids have euler number
    * equal to one, while their surface have euler number equal to
    * two.
    *
    * @return the Euler number of this complex which equals nbCells( 0 ) - nbCells( 1 ) + nbCells( 2 ) - ...
    */
    Integer euler() const;

    /**
    * @return a reference to the Khalimsky space associated to this complex.
    */
    const KSpace& space() const;

    // ---------- cell container operations ---------------
  public:

    /**
     * @param d input Dimension
     *
     * @return CellContainer associated to cell of dimension d.
     */
    const CellMap & getCells(const Dimension d) const ;

    /**
     * @param d input Dimension
     *
     * @return CellContainer associated to cell of dimension d.
     */
    CellMap & getCells(const Dimension d) ;

    /// @return an iterator pointing on the first cell of this complex
    /// (lower dimensional cells come first).
    ConstIterator begin() const;

    /// @return an iterator pointing after the last cell of this complex
    /// (upper dimensional cells arrive last).
    ConstIterator end() const;

    /// @return an iterator pointing on the first cell of this complex
    /// (lower dimensional cells come first).
    Iterator begin();

    /// @return an iterator pointing after the last cell of this complex
    /// (upper dimensional cells arrive last).
    Iterator end();

    /**
     * @param aCell any cell.
     * @return the number of matches for \a aCell, which is thus zero (not present) or one (present).
     */
    Size count( const Cell& aCell ) const;

    /// @return the total number of cells in this complex.
    Size size() const;

    /// @return the maximal number of cells in this complex (i.e., the
    /// number of cells of the Khalimsky space).
    Size max_size() const;

    /// @return 'true' if and only if the complex does not hold any cell.
    bool empty() const;

    /**
     * Get range of equal elements to \a aCell. Because all elements
     * in a set container are unique, the range returned will contain
     * a single element at most.
     *
     * @param aCell any cell.
     *
     * @return the bounds of a range that includes all the elements in
     * the container that are equivalent to val.
     */
    std::pair< ConstIterator, ConstIterator > equal_range( const Cell& aCell ) const;

    /**
     * Get range of equal elements to \a aCell. Because all elements
     * in a set container are unique, the range returned will contain
     * a single element at most.
     *
     * @param aCell any cell.
     *
     * @return the bounds of a range that includes all the elements in
     * the container that are equivalent to val.
     */
    std::pair< Iterator, Iterator > equal_range( const Cell& aCell );

    /**
     * Erase element pointed by iterator \a it.
     * @param position any iterator on a valid cell.
     */
    void erase( Iterator position );

    /**
     * Erases cell \a aCell from the complex (STL version, see eraseCell).
     * @param aCell any cell valid in the Khalimsky space associated to the complex.
     * @return the number of cells effectively removed from the cubical complex.
     */
    Size erase( const Cell& aCell );

    /**
     * Erases range of cells [\a first, \a last ).
     * @param first an iterator on the beginning of a range of cells within this complex.
     * @param last an iterator on the end of a range of cells within this complex.
     */
    void erase( Iterator first, Iterator last );

    /**
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @return an iterator pointing on the cell or end() if not found.
    */
    ConstIterator find( const Cell& aCell ) const;

    /**
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @return an iterator pointing on the cell or end() if not found.
    */
    Iterator find( const Cell& aCell );

    /**
     * Insert element \a aCell into the complex.
     *
     * @param aCell any cell valid in the Khalimsky space associated to the complex.
     *
     * @return a pair with an iterator pointing on the inserted
     * element and a boolean that is true whenever this was indeed a
     * new element in the complex.
     */
    std::pair< Iterator, bool > insert( const Cell& aCell );

    /**
     * Insert element \a aCell into the complex with possible hint given by position.
     *
     * @param aCell any cell valid in the Khalimsky space associated to the complex.
     * @param position an hint for the position where the element can be inserted.
     * @return  an iterator pointing on the inserted element.
     */
    Iterator insert( Iterator position, const Cell& aCell );

    /**
     * Insert a range of cells [first, last).
     *
     * @tparam InputIterator any model of boost::InputIterator where elements are Cell.
     * @param first the beginning of the range.
     * @param last the end of the range.
     */
    template <class InputIterator>
    void insert( InputIterator first, InputIterator last );

    /**
     * Swaps complex \a other with \a this.  Note that complexes must
     * live in the same space. If one complex is invalid then it is
     * initialized with the space of the other.
     *
     * @param other a complex living in the same space.
     */
    void swap( CubicalComplex& other );

    // ---------- enhanced container operations ---------------
  public:

    /**
    * Access or change the data associated to \a aCell. Note that if
    * \a aCell was not in this complex, then it is inserted.
    *
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @return a reference on the data associated with \a aCell.
    */
    Data& operator[]( const Cell& aCell );

    /**
    * Makes CubicalComplex a functor Cell -> boolean, which represents
    * the characteristic cell function.
    *
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @return 'true' if and only if \a aCell belongs to this complex.
    */
    bool operator()( const Cell& aCell ) const;

    /**
    * Insert cell \a aCell into CubicalComplex and assign to it the value \a data.
    *
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @param data any value.
    */
    void insertCell( const Cell& aCell, const Data& data = Data() );

    /**
    * Insert cell \a aCell into CubicalComplex and assign to it the
    * value \a data. Faster than the other insertCell method.
    *
    * @param d the dimension of cell \a aCell.
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @param data any value.
    */
    void insertCell( Dimension d, const Cell& aCell, const Data& data = Data() );

    /**
    * Insert the cells within range [it,itE) into the
    * CubicalComplex. The value associated to each cell is the
    * default.
    *
    * @param it an iterator pointing at the beginning of a range of (arbitrary) cells.
    * @param itE an iterator pointing after the end of a range of (arbitrary) cells.
    * @param data any value.
    * @tparam CellConstIterator any model of a forward const iterator on Cell.
    */
    template <typename CellConstIterator>
    void insertCells( CellConstIterator it, CellConstIterator itE, const Data& data = Data() );

    /**
    * Insert the cells within range [it,itE) into the
    * CubicalComplex. The value associated to each cell is the
    * default.
    *
    * @param d the dimension of all cells in the range [it,itE).
    * @param it an iterator pointing at the beginning of a range of (arbitrary) cells.
    * @param itE an iterator pointing after the end of a range of (arbitrary) cells.
    * @param data any value.
    * @tparam CellConstIterator any model of a forward const iterator on Cell.
    */
    template <typename CellConstIterator>
    void insertCells( Dimension d, CellConstIterator it, CellConstIterator itE, const Data& data = Data() );

    /**
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @return 'true' if and only if \a aCell belongs to this complex.
    */
    bool belongs( const Cell& aCell ) const;

    /**
    * @param d the dimension of cell \a aCell.
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @return 'true' if and only if \a aCell belongs to this complex.
    */
    bool belongs( Dimension d, const Cell& aCell ) const;

    /**
    * Erases cell \a aCell from the complex.
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @return the number of cells effectively removed from the cubical complex.
    */
    Size eraseCell( const Cell& aCell );

    /**
    * Erases cell \a aCell from the complex.
    * @param d the dimension of cell \a aCell.
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @return the number of cells effectively removed from the cubical complex.
    */
    Size eraseCell( Dimension d, const Cell& aCell );

    /**
    * Erases cell pointed by iterator \a it.
    * @param it any valid iterator on a cell of this complex.
    */
    void eraseCell( CellMapIterator it );

    /**
    * Erases cells in range [\a it, \a itE).
    * @param it any valid iterator on the first element of range of cells of this complex.
    * @param itE any valid iterator after the last element of range of cells of this complex.
    */
    void eraseCells( CellMapIterator it, CellMapIterator itE );

    /**
    * Erases the cells stored in range [it,itE) from the
    * CubicalComplex.
    *
    * @param it an iterator pointing at the beginning of a range of (arbitrary) cells.
    * @param itE an iterator pointing after the end of a range of (arbitrary) cells.
    * @return the number of cells effectively removed from the cubical complex.
    * @tparam CellConstIterator any model of a forward const iterator on Cell.
    */
    template <typename CellConstIterator>
    Size eraseCells( CellConstIterator it, CellConstIterator itE );

    /**
    * Erases the cells of dimension \a d stored in range [it,itE) from the
    * CubicalComplex.
    *
    * @param d the dimension of every cell in range [it,itE).
    * @param it an iterator pointing at the beginning of a range of (arbitrary) cells.
    * @param itE an iterator pointing after the end of a range of (arbitrary) cells.
    * @return the number of cells effectively removed from the cubical complex.
    * @tparam CellConstIterator any model of a forward const iterator on Cell.
    */
    template <typename CellConstIterator>
    Size eraseCells( Dimension d, CellConstIterator it, CellConstIterator itE );

    /**
    * Outputs all the cells that are proper faces of \a aCell with output iterator \a it.
    *
    * @param outIt the output iterator on Cell that is used for outputing faces.
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @param hintClosed when 'true', this hint tells that the complex
    * is closed, so this speeds up this method, otherwise, the
    * complex may be arbitrary.
    *
    * @tparam CellOutputIterator any model of boost::OutputIterator, with value_type Cell.
    *
    * @note all returned cells belong to this complex, while it is
    * not compulsory for \a aCell to belong to it.
    */
    template <typename CellOutputIterator>
    void faces( CellOutputIterator& outIt, const Cell& aCell,
                bool hintClosed = false ) const;

    /**
    * Outputs all the cells that are direct faces of \a aCell with
    * output iterator \a it (direct faces are lower incident cells
    * with a dimension just one below).
    *
    * @param outIt the output iterator on Cell that is used for outputing faces.
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @param hintClosed when 'true', this hint tells that the complex
    * is closed, so this speeds up this method, otherwise, the
    * complex may be arbitrary.
    *
    * @tparam CellOutputIterator any model of boost::OutputIterator, with value_type Cell.
    *
    * @note all returned cells belong to this complex, while it is
    * not compulsory for \a aCell to belong to it.
    */
    template <typename CellOutputIterator>
    void directFaces( CellOutputIterator& outIt, const Cell& aCell,
                      bool hintClosed = false ) const;

    /**
    * Outputs all the iterators on cells that are direct faces of \a aCell with
    * output iterator \a it (direct faces are lower incident cells
    * with a dimension just one below).
    *
    * @param outIt the output iterator on CellMapIterator that is used for outputing face iterators.
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    *
    * @tparam CellMapIteratorOutputIterator any model of boost::OutputIterator, with value_type CellMapIterator.
    *
    * @note all returned cells belong to this complex, while it is
    * not compulsory for \a aCell to belong to it.
    */
    template <typename CellMapIteratorOutputIterator>
    void directFacesIterators( CellMapIteratorOutputIterator& outIt, const Cell& aCell );

    /**
    * Outputs all the cells that are proper co-faces of \a aCell with
    * output iterator \a it.
    *
    * @param outIt the output iterator on Cell that is used for outputing faces.
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @param hintOpen when 'true', this hint tells that the complex
    * is open, so this speeds up this method, otherwise, the
    * complex may be arbitrary.
    *
    * @tparam CellOutputIterator any model of boost::OutputIterator, with value_type Cell.
    *
    * @note all returned cells belong to this complex, while it is
    * not compulsory for \a aCell to belong to it.
    */
    template <typename CellOutputIterator>
    void coFaces( CellOutputIterator& outIt, const Cell& aCell,
                  bool hintOpen = false ) const;

    /**
    * Outputs all the cells that are direct co-faces of \a aCell with
    * output iterator \a it (direct faces are upper incident cells
    * with a dimension just one above).
    *
    * @param outIt the output iterator on Cell that is used for outputing faces.
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @param hintOpen when 'true', this hint tells that the complex
    * is open, so this speeds up this method, otherwise, the
    * complex may be arbitrary.
    *
    * @tparam CellOutputIterator any model of boost::OutputIterator, with value_type Cell.
    *
    * @note all returned cells belong to this complex, while it is
    * not compulsory for \a aCell to belong to it.
    */
    template <typename CellOutputIterator>
    void directCoFaces( CellOutputIterator& outIt, const Cell& aCell,
                        bool hintOpen = false ) const;

    /**
    * Outputs all the iterators on cells that are direct co-faces of \a aCell with
    * output iterator \a it (direct faces are upper incident cells
    * with a dimension just one above).
    *
    * @param outIt the output iterator on CellMapIterator that is used for outputing face iterators.
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    *
    * @tparam CellMapIteratorOutputIterator any model of boost::OutputIterator, with value_type CellMapIterator.
    *
    * @note all returned cells belong to this complex, while it is
    * not compulsory for \a aCell to belong to it.
    */
    template <typename CellMapIteratorOutputIterator>
    void directCoFacesIterators( CellMapIteratorOutputIterator& outIt, const Cell& aCell );

    /**
    * @param d any valid dimension.
    * @return a const iterator pointing on the first cell of dimension \a d of this.
    */
    CellMapConstIterator begin( Dimension d ) const;

    /**
    * @param d any valid dimension.
    * @return a const iterator pointing after the last cell of dimension \a d of this.
    */
    CellMapConstIterator end( Dimension d ) const;

    /**
    * @param d any valid dimension.
    * @return an iterator pointing on the first cell of dimension \a d of this.
    */
    CellMapIterator begin( Dimension d );

    /**
    * @param d any valid dimension.
    * @return an iterator pointing after the last cell of dimension \a d of this.
    */
    CellMapIterator end( Dimension d );

    /**
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @return an iterator pointing on the pair (aCell,data) if the cell belongs to the complex, or end( dim( aCell ) )
    */
    CellMapConstIterator findCell( const Cell& aCell ) const;

    /**
    * @param d the dimension of cell \a aCell.
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @return an iterator pointing on the pair (aCell,data) if the cell belongs to the complex, or end( d )
    */
    CellMapConstIterator findCell( Dimension d, const Cell& aCell ) const;

    /**
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @return an iterator pointing on the pair (aCell,data) if the cell belongs to the complex, or end( dim( aCell ) )
    */
    CellMapIterator findCell( const Cell& aCell );

    /**
    * @param d the dimension of cell \a aCell.
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @return an iterator pointing on the pair (aCell,data) if the cell belongs to the complex, or end( d )
    */
    CellMapIterator findCell( Dimension d, const Cell& aCell );

    // ---------- local operations for extracting specific subcomplexes -------------
  public:

    /**
    * Returns the boundary of the cell \a aCell as a cell collection,
    * i.e. all the cells that are proper faces of \a aCell. Generally
    * faster than method \ref faces, which outputs cells with an
    * output iterator.
    *
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @param hintClosed when 'true', this hint tells that the complex
    * is (locally) closed, so this speeds up this method, otherwise, the
    * complex may be arbitrary.
    *
    * @return the collection of cells that defines the boundary of \a
    * aCell, i.e. its proper faces.
    *
    * @note all returned cells belong to this complex, while it is
    * not compulsory for \a aCell to belong to it.
    */
    Cells cellBoundary( const Cell& aCell, bool hintClosed = false ) const;

    /**
    * Returns the co-boundary of the cell \a aCell as a cell collection,
    * i.e. all the cells that are proper co-faces of \a aCell. Generally
    * faster than method \ref coFaces, which outputs cells with an
    * output iterator.
    *
    * @param aCell any cell valid in the Khalimsky space associated to the complex.
    * @param hintOpen when 'true', this hint tells that the complex
    * is (locally) open, so this speeds up this method, otherwise, the
    * complex may be arbitrary.
    *
    * @return the collection of cells that defines the co-boundary of \a aCell, i.e. its proper co-faces.
    *
    * @note all returned cells belong to this complex, while it is
    * not compulsory for \a aCell to belong to it.
    */
    Cells cellCoBoundary( const Cell& aCell, bool hintOpen = false ) const;


    // ---------------------- local properties --------------------------------------
  public:
    /**
     * @param aCell any cell valid in the Khalimsky space associated to the complex.
     *
     * @return 'true' if and only if \a aCell is interior to the
     * complex, which means that it has the same co-faces in the Khalimsky
     * space as in this complex.
     */
    bool isCellInterior( const Cell& aCell ) const;

    /**
     * @param aCell any cell valid in the Khalimsky space associated to the complex.
     *
     * @return 'true' if and only if \a aCell is not interior to the
     * complex, which means that it has more co-faces in the Khalimsky
     * space than in this complex.
     */
    bool isCellBoundary( const Cell& aCell ) const;

    /**
    * Given a cell [c], tells if it is a maximal cell in the complex
    * (return 0), or if it is a free face of the cell pointed by
    * [it_cell_up] (return 1) or if it is not a free face.
    *
    * The complex must be closed. In computing the 1-up-incident
    * cells, this method ignores cell marked as REMOVED. Furthermore,
    * if one 1-up-incident cell is not marked as COLLAPSIBLE, the
    * method returns 2.
    *
    * @param[in] c a cubical cell (belonging to 'this')
    *
    * @param[out] it_cell_up (returns) a pointer on a cell d if c is a
    * free face of d.
    *
    * @param[in] n the maximal dimension of a cell in this
    * complex. Default to \ref dimension, but can be less in some
    * cases: for instance, you know that your subcomplex is a digital
    * surface in Z3, hence you can pass 2 for \a n.
    *
    * @return CellType::Maximal if the cell is maximal, CellType::Free if the
    * cell is a free face, CellType::Any otherwise.
    */
    CellType computeCellType( const Cell& c, CellMapIterator& it_cell_up,
                              Dimension n = dimension );


    // ----------------------- Standard subcomplexes --------------------------------
  public:

    /**
     * Computes the (topological) interior to this complex.
     * @return the subcomplex of this composed of its interior cells.
     */
    CubicalComplex interior() const;

    /**
     * Computes the (topological) boundary of this complex (say X),
     * hence it may not be a subcomplex of X, but it is a subcomplex
     * of Cl(X).
     *
     * @param hintClosed when 'true', this hint tells that the complex
     * is closed, so this speeds up this method, otherwise, the
     * complex may be arbitrary.
     *
     * @return the subcomplex of this composed of its boundary cells.
     */
    CubicalComplex boundary( bool hintClosed = false ) const;

    /**
     * Computes the (topological) interior \a intcc and the
     * (topological) boundary \a bdcc of this complex. Note that \a bdcc
     * is not necessarily a subcomplex.
     *
     * @param[out] intcc returns the interior subcomplex of this complex.
     * @param[out] bdcc returns the boundary of this complex.
     *
     * @param hintClosed when 'true', this hint tells that the complex
     * is closed, so this speeds up this method, otherwise, the
     * complex may be arbitrary.
     */
    void getInteriorAndBoundary( CubicalComplex& intcc,
                                 CubicalComplex& bdcc,
                                 bool hintClosed = false ) const;

    /**
    * Returns the closure of the cells in \a S within this complex,
    * i.e. the smallest subcomplex that contains each cell in \a S.
    *
    * @param S any complex the cells of which belong to this complex.
    * @param hintClosed when 'true', this hint tells that the complex
    * is (locally around \a S) closed, so this speeds up this method, otherwise, the
    * complex may be arbitrary.
    * @return the closure of \a S within this complex as a cubical complex.
    */
    CubicalComplex closure( const CubicalComplex& S, bool hintClosed = false ) const;

    /**
    * Returns the star of the cells in \a S within this complex, i.e. the
    * set of all cells of this complex that have any faces in \a S.
    *
    * @param S any complex the cells of which belong to this complex.
    * @param hintOpen when 'true', this hint tells that the complex
    * is (locally around \a S) open, so this speeds up this method, otherwise, the
    * complex may be arbitrary.
    * @return the star of \a S within this complex as a cubical complex.
    */
    CubicalComplex star( const CubicalComplex& S, bool hintOpen = false ) const;

    /**
    * Returns the link of the cells in \a S within this complex,
    * i.e. the closed star of \a S minus the stars of all faces of \a
    * S.
    *
    * @param S any complex the cells of which belong to this complex.
    * @param hintClosed when 'true', this hint tells that the complex
    * is (locally around \a S) closed, so this speeds up this method, otherwise, the
    * complex may be arbitrary.
    * @param hintOpen when 'true', this hint tells that the complex
    * is (locally around \a S) open, so this speeds up this method, otherwise, the
    * complex may be arbitrary.
    * @return the link of \a S within this complex as a cubical complex.
    */
    CubicalComplex link( const CubicalComplex& S, bool hintClosed = false, bool hintOpen = false ) const;

    // ----------------------- global operations on complexes -----------------------
  public:

    /**
    * Close the whole complex (see also DGtal::functions::operator~).
    */
    void close();

    /**
    * Close all cells of dimension less or equal to \a k.
    * @param k any strictly positive integer.
    */
    void close( Dimension k );

    /**
    * Open the whole complex  (see also DGtal::functions::operator*).
    */
    void open();

    /**
    * Open all cells of dimension less or or equal to \a k.
    * @param k any strictly positive integer.
    */
    void open( Dimension k );


    // ----------------------- Interface --------------------------------------
  public:

    /**
    * Writes/Displays the object on an output stream.
    * @param out the output stream where the object is written.
    */
    void selfDisplay ( std::ostream & out ) const;

    /**
    * Checks the validity/consistency of the object.
    * @return 'true' if the object is valid, 'false' otherwise.
    */
    bool isValid() const;

    // --------------- CDrawableWithBoard2D realization ------------------
  public:
    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;

    // ------------------------- Protected Datas ------------------------------
  protected:

    /// The Khalimsky space in which lives the cubical complex.
    const KSpace* myKSpace;

    /// An array of map Cell -> Data that stores cells dimension per
    /// dimension (i.e. cells of dimension 0 are stored in myCells[0],
    /// cells of dimension 1 in myCells[1] and so on).
    std::vector<CellMap> myCells;


    // ------------------------- Hidden services ------------------------------
  protected:


  private:


    // ------------------------- Internals ------------------------------------
  private:


  }; // end of class CubicalComplex

  /**
   * Specialization of ContainerTraits for CubicalComplex.  A cubical
   * complex is close to being a container, but is not, essentially
   * because it requires a Khalimsky space to be valid.
   */
  template < typename TKSpace,
             typename TCellContainer >
  struct ContainerTraits< CubicalComplex< TKSpace, TCellContainer > >
  {
    //typedef typename ContainerTraits< TCellContainer >::Category Category;
    typedef SequenceCategory Category;
  };


  /**
  * Overloads 'operator<<' for displaying objects of class 'CubicalComplex'.
  * @param out the output stream where the object is written.
  * @param object the object of class 'CubicalComplex' to write.
  * @return the output stream after the writing.
  */
  template <typename TKSpace, typename TCellContainer>
  std::ostream&
  operator<< ( std::ostream & out,
               const CubicalComplex<TKSpace, TCellContainer> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/CubicalComplex.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CubicalComplex_h

#undef CubicalComplex_RECURSES
#endif // else defined(CubicalComplex_RECURSES)
