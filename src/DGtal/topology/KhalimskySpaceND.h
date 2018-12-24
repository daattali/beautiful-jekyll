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
 * @file KhalimskySpaceND.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @author Roland Denis ( \c roland.denis@univ-smb.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/02/08
 *
 * Header file for module KhalimskySpaceND.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(KhalimskySpaceND_RECURSES)
#error Recursive header files inclusion detected in KhalimskySpaceND.h
#else // defined(KhalimskySpaceND_RECURSES)
/** Prevents recursive inclusion of headers. */
#define KhalimskySpaceND_RECURSES

#if !defined KhalimskySpaceND_h
/** Prevents repeated inclusion of headers. */
#define KhalimskySpaceND_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <set>
#include <map>
#include <array>
#include <DGtal/base/Common.h>
#include <DGtal/kernel/CInteger.h>
#include <DGtal/kernel/PointVector.h>
#include <DGtal/kernel/SpaceND.h>
#include <DGtal/topology/KhalimskyPreSpaceND.h>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // Pre-declaration
  template <
      Dimension dim,
      typename TInteger = DGtal::int32_t
  >
  class KhalimskySpaceND;

  /////////////////////////////////////////////////////////////////////////////
  /** Internal class of KhalimskySpaceND that provides some optimizations
   * depending on the space type.
   */
  template < class TKhalimskySpace >
  class KhalimskySpaceNDHelper;

  /////////////////////////////////////////////////////////////////////////////
  /**
   * @brief Represents an (unsigned) cell in a cellular grid space by its
   * Khalimsky coordinates.
   * @tparam dim the dimension of the digital space.
   * @tparam TInteger the Integer class used to specify the arithmetic computations (default type = int32).
   */
  template < Dimension dim,
             typename TInteger = DGtal::int32_t >
  struct KhalimskyCell
  {

    //Integer must be a model of the concept CInteger.
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<TInteger> ) );


    // Aliases
  public:
    using Integer = TInteger;
    using UnsignedInteger = typename NumberTraits<Integer>::UnsignedVersion;
    using Point   = PointVector< dim, Integer >;
    using PreCell = KhalimskyPreCell< dim, Integer >;
    using CellularGridSpace = KhalimskySpaceND< dim, TInteger >;
    using PreCellularGridSpace = KhalimskyPreSpaceND< dim, TInteger >;
    using Self    = KhalimskyCell< dim, Integer >;

    // Friendship
    friend class KhalimskySpaceND< dim, TInteger >;
    friend class KhalimskySpaceNDHelper< CellularGridSpace >;

  private:
    // Underlying pre-cell
    PreCell myPreCell;

  private:

    /**
     * Explicit constructor from its Khalimsky coordinates.
     * @param aPoint Its Khalimsky coordinates as a point.
     */
    explicit KhalimskyCell( const Point & aPoint );

    /**
     * Explicit constructor from a KhalimskyPreCell.
     * @param aCell a pre-cell.
     */
    explicit KhalimskyCell( const PreCell & aCell );

  public:
    /// Constant conversion to KhalimskyPreCell.
    operator PreCell const& () const;

    /// Returns the underlying constant pre-cell.
    PreCell const& preCell() const;

  private:
    /// Mutable conversion to KhalimskyPreCell.
    explicit operator PreCell & ();

  public:
    /**
     * Default constructor.
     */
    explicit KhalimskyCell( Integer dummy = 0 );

    /** Copy constructor.
     * @param other any other cell.
     */
    KhalimskyCell( const KhalimskyCell & other ) = default;

    /** Copy operator.
     * @param other any other cell.
     */
    KhalimskyCell & operator=( const KhalimskyCell & other ) = default;

    /** Move constructor.
     * @param other any other cell.
     */
    KhalimskyCell( KhalimskyCell && other ) = default;

    /** Move operator.
     * @param other any other cell.
     */
    KhalimskyCell & operator=( KhalimskyCell && other ) = default;

    /**
     * Equality operator.
     * @param other any other cell.
     */
    bool operator==( const KhalimskyCell & other ) const;

    /**
     * Difference operator.
     * @param other any other cell.
    */
    bool operator!=( const KhalimskyCell & other ) const;

    /**
     * Inferior operator. (lexicographic order).
     * @param other any other cell.
    */
    bool operator<( const KhalimskyCell & other ) const;

    // --------------- CDrawableWithBoard2D realization -------------------
  public:

    /**
     * Default drawing style object.
     * @return the dyn. alloc. default style for this object.
     */
    //DrawableWithBoard2D* defaultStyle( std::string mode = "" ) const;

    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;

  };

  template < Dimension dim,
             typename TInteger >
  std::ostream &
  operator<<( std::ostream & out,
              const KhalimskyCell< dim, TInteger > & object );


  /////////////////////////////////////////////////////////////////////////////
  /**
   * @brief Represents a signed cell in a cellular grid space by its
   * Khalimsky coordinates and a boolean value.
   * @tparam dim the dimension of the digital space.
   * @tparam TInteger the Integer class used to specify the arithmetic computations (default type = int32).
   */
  template < Dimension dim,
             typename TInteger = DGtal::int32_t >
  struct SignedKhalimskyCell
  {
    //Integer must be a model of the concept CInteger.
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<TInteger> ) );

    // Aliases
  public:
    using Integer = TInteger;
    using UnsignedInteger = typename NumberTraits<Integer>::UnsignedVersion;
    using Point   = PointVector< dim, Integer >;
    using SPreCell = SignedKhalimskyPreCell< dim, Integer >;
    using CellularGridSpace = KhalimskySpaceND< dim, TInteger >;
    using PreCellularGridSpace = KhalimskyPreSpaceND< dim, TInteger >;
    using Self    = SignedKhalimskyCell< dim, Integer >;

    // Friendship
    friend class KhalimskySpaceND< dim, TInteger >;
    friend class KhalimskySpaceNDHelper< CellularGridSpace >;

  private:
    // Underlying signed pre-cell
    SPreCell mySPreCell;

  private:
    /**
     * Explicit constructor from its Khalimsky coordinates.
     * @param aPoint any point.
     * @param positive if cell has positive sign.
     */
    explicit SignedKhalimskyCell( const Point & aPoint, bool positive );

    /**²
     * Explicit constructor from a SignedKhalimskyPreCell.
     * @param aCell a pre-cell.
     */
    explicit SignedKhalimskyCell( const SPreCell & aCell );

  public:
    /// Constant conversion to KhalimskySignedPreCell.
    operator SPreCell const& () const;

    /// Returns the underlying constant signed pre-cell.
    SPreCell const& preCell() const;

  private:
    /// Mutable conversion to KhalimskySignedPreCell.
    explicit operator SPreCell & ();

  public:
    /**
     * Default constructor.
     */
    explicit SignedKhalimskyCell( Integer dummy = 0 );

    /** Copy constructor.
     * @param other any other cell.
     */
    SignedKhalimskyCell( const SignedKhalimskyCell & other ) = default;

    /** Copy operator.
     * @param other any other cell.
     */
    SignedKhalimskyCell & operator=( const SignedKhalimskyCell & other ) = default;

    /** Move constructor.
     * @param other any other cell.
     */
    SignedKhalimskyCell( SignedKhalimskyCell && other ) = default;

    /** Move operator.
     * @param other any other cell.
     */
    SignedKhalimskyCell & operator=( SignedKhalimskyCell && other ) = default;

    /**
     * Equality operator.
     * @param other any other cell.
     */
    bool operator==( const SignedKhalimskyCell & other ) const;

    /**
     * Difference operator.
     * @param other any other cell.
     */
    bool operator!=( const SignedKhalimskyCell & other ) const;

    /**
     * Inferior operator. (lexicographic order).
     * @param other any other cell.
     */
    bool operator<( const SignedKhalimskyCell & other ) const;

    // --------------- CDrawableWithBoard2D realization -------------------
  public:

    /**
     * Default drawing style object.
     * @return the dyn. alloc. default style for this object.
     */
    //DrawableWithBoard2D* defaultStyle( std::string mode = "" ) const;

    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;

  };

  template < Dimension dim,
             typename TInteger >
  std::ostream &
  operator<<( std::ostream & out,
              const SignedKhalimskyCell< dim, TInteger > & object );

  /////////////////////////////////////////////////////////////////////////////
  // template class KhalimskySpaceND
  /**
   * Description of template class 'KhalimskySpaceND' <p>
   *
   * \brief Aim: This class is a model of CCellularGridSpaceND. It
   * represents the cubical grid as a cell complex, whose cells are
   * defined as an array of integers. The topology of the cells is
   * defined by the parity of the coordinates (even: closed, odd:
   * open).
   *
   * When \b initializing the space using init(),
   * the user should choose, for each dimension spanned by the space,
   * between a closed and non-periodic (default) cell dimension,
   * an open cell dimension or a periodic cell dimension.
   * The space is generally finite, except for arbitrary size
   * integers and when the space has a periodic dimension.
   *
   * @anchor KhalimskySpaceNDBounds
   * Supposing that the space has been initialized with digital bounds \c lower and \c upper,
   * the methods lowerBound() and upperBound() will always return, respectively, \c lower and \c upper.
   * It as also true for periodic dimension, in order to span over the unique digital points of the space.
   *
   * In the same way, lowerCell() and upperCell() respect the following rules:
   * - the k-th Khalimsky coordinate of lowerCell() is equal to:
   *    - `2*lower[k]` if the k-th dimension is closed or periodic,
   *    - `2*lower[k]+1` if the k-th dimension is open;
   * - the k-th Khalimsky coordinate of upperCell() is equal to:
   *    - `2*upper[k]+2` if the k-th dimension is closed,
   *    - `2*upper[k]+1` if the k-th dimension is open or periodic.
   *    .
   * .
   * The special behavior for __periodic dimensions__ guarantees that each cell has unique
   * Khalimsky coordinates in this range.
   * It is useful to span the space and also for cell-based containers (see e.g. CubicalComplex).
   * Uniqueness also gives meaning to equality tests between cells.
   *
   * Following this concept, the related methods size(), min(), max(),
   * uFirst(), uLast(), uGetMin(), uGetMax(), uDistanceToMin(), uDistanceToMax(),
   * sFirst(), sLast(), sGetMin(), sGetMax(), sDistanceToMin() and sDistanceToMax()
   * behave for periodic dimensions like for finite dimensions, using the bounds described above.
   *
   * Thus, if a cell needs to be __compared to the bounds__, prefer using dedicated tests like
   * uIsMin(), uIsMax(), sIsMin() and sIsMax() that return always \c false for a periodic dimension,
   * and uIsInside() and sIsInside() that return always \c true for a periodic dimension.
   *
   * To be consistent with those choices, each cell returned or modified by a KhalimskySpaceND method
   * will have his Khalimsky coordinates along periodic dimensions between the corresponding
   * coordinates of lowerCell() and upperCell().
   * But, in order to keep low computational cost, each cell passed by parameter to a KhalimskySpaceND
   * method must follow the same conditions.
   * This validity can be tested with the dedicated methods uIsValid() and sIsValid().
   *
   * Exceptions exist for uCell(const PreCell &) const and sCell(const SPreCell &) const that are specially featured
   * to correct Khalimsky coordinates of a given cell.
   * In addition, when a method accepts a coordinate as parameter, it is always corrected along periodic dimensions.
   *
   * @tparam dim the dimension of the digital space.
   * @tparam TInteger the Integer class used to specify the arithmetic computations (default type = int32).
   * @note Essentially a backport from [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene).
   *
   * @warning Periodic Khalimsky space and per-dimension closure specification are new features.
   * Therefore, there is no guarantee that it is compatible with the whole DGtal library.
   *
  */
  template <
      Dimension dim,
      typename TInteger
  >
  class KhalimskySpaceND
    : private KhalimskySpaceNDHelper< KhalimskySpaceND< dim, TInteger > >
  {

    typedef KhalimskySpaceNDHelper< KhalimskySpaceND< dim, TInteger > > Helper; ///< Features basic operations on coordinates, especially for periodic dimensions.
    friend class KhalimskySpaceNDHelper< KhalimskySpaceND< dim, TInteger > >;

    //Integer must be signed to characterize a ring.
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<TInteger> ) );

  public:
    ///Arithmetic ring induced by (+,-,*) and Integer numbers.
    typedef TInteger Integer;

    ///Type used to represent sizes in the digital space.
    typedef typename NumberTraits<Integer>::UnsignedVersion Size;

    // Spaces
    typedef SpaceND<dim, Integer> Space;
    typedef KhalimskySpaceND<dim, Integer>    CellularGridSpace;
    typedef KhalimskyPreSpaceND<dim, Integer> PreCellularGridSpace;

    // Cells
    typedef KhalimskyCell< dim, Integer > Cell;
    typedef KhalimskyPreCell< dim, Integer > PreCell;
    typedef SignedKhalimskyCell< dim, Integer > SCell;
    typedef SignedKhalimskyPreCell< dim, Integer > SPreCell;

    typedef SCell Surfel;
    typedef bool Sign;
    using DirIterator = typename PreCellularGridSpace::DirIterator;

    // Points and Vectors
    typedef PointVector< dim, Integer > Point;
    typedef PointVector< dim, Integer > Vector;


    // static constants
    static const constexpr Dimension dimension = dim;
    static const constexpr Dimension DIM = dim;
    static const constexpr Sign POS = true;
    static const constexpr Sign NEG = false;

    template < typename CellType >
    using AnyCellCollection = typename PreCellularGridSpace::template AnyCellCollection< CellType >;

    // Neighborhoods, Incident cells, Faces and Cofaces
    typedef AnyCellCollection<Cell> Cells;
    typedef AnyCellCollection<SCell> SCells;

    // Sets, Maps
    /// Preferred type for defining a set of Cell(s).
    typedef std::set<Cell> CellSet;

    /// Preferred type for defining a set of SCell(s).
    typedef std::set<SCell> SCellSet;

    /// Preferred type for defining a set of surfels (always signed cells).
    typedef std::set<SCell> SurfelSet;

    /// Template rebinding for defining the type that is a mapping
    /// Cell -> Value.
    template <typename Value> struct CellMap {
        typedef std::map<Cell,Value> Type;
    };

    /// Template rebinding for defining the type that is a mapping
    /// SCell -> Value.
    template <typename Value> struct SCellMap {
        typedef std::map<SCell,Value> Type;
    };

    /// Template rebinding for defining the type that is a mapping
    /// SCell -> Value.
    template <typename Value> struct SurfelMap {
        typedef std::map<SCell,Value> Type;
    };

    /// Boundaries closure type
    enum Closure
      {
        CLOSED,   ///< The dimension is closed and non-periodic.
        OPEN,     ///< The dimension is open.
        PERIODIC  ///< The dimension is periodic.
      };

    // ----------------------- Standard services ------------------------------
    /** @name Standard services
     * @{
     */
  public:

    /**
     * Destructor.
     */
    ~KhalimskySpaceND();

    /**
     * Default constructor.
     */
    KhalimskySpaceND();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    KhalimskySpaceND ( const KhalimskySpaceND & other ) = default;

    /**
     * Copy operator.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    KhalimskySpaceND & operator= ( const KhalimskySpaceND & other ) = default;

    /**
     * Move constructor.
     * @param other the object to clone.
     */
    KhalimskySpaceND ( KhalimskySpaceND && other ) = default;

    /**
     * Move operator.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    KhalimskySpaceND & operator= ( KhalimskySpaceND && other ) = default;

    /**
     * Specifies the upper and lower bounds for the maximal cells in
     * this space.
     *
     * @param lower the lowest point in this space (digital coords)
     * @param upper the upper point in this space (digital coords)
     * @param isClosed 'true' if this space is closed and non-periodic in every dimension, 'false' if open.
     *
     * @return true if the initialization was valid (ie, such bounds
     * are representable with these integers).
     */
    bool init( const Point & lower,
               const Point & upper,
               bool isClosed );

    /**
     * Specifies the upper and lower bounds for the maximal cells in
     * this space.
     *
     * @param lower the lowest point in this space (digital coords)
     * @param upper the upper point in this space (digital coords)
     * @param closure \a CLOSED, \a OPEN or \a PERIODIC if this space is resp. closed (and non-periodic),
     *        open or periodic in every dimension.
     *
     * @return true if the initialization was valid (ie, such bounds
     * are representable with these integers).
     */
    bool init( const Point & lower,
               const Point & upper,
               Closure closure );

    /**
     * Specifies the upper and lower bounds for the maximal cells in
     * this space.
     *
     * @param lower the lowest point in this space (digital coords)
     * @param upper the upper point in this space (digital coords)
     * @param closure an array of \a CLOSED, \a OPEN or \a PERIODIC if this space is resp. closed (and non-periodic),
     *        open or periodic in the corresponding dimension.
     *
     * @return true if the initialization was valid (ie, such bounds
     * are representable with these integers).
     */
    bool init( const Point & lower,
               const Point & upper,
               const std::array<Closure, dim> & closure );

    /// @}

    // ------------------------- Basic services ------------------------------
    /** @name Basic services
     * @{
     */
  public:

    /**
     * @param k a dimension.
     * @return the width of the space in the \a k-dimension.
     * @note For periodic dimension, it returns the number of unique coordinates along that dimension.
     */
    Size size( Dimension k ) const;

    /**
     * @param k a dimension.
     * @return the minimal digital coordinate in the \a k-dimension.
     * @note For periodic dimension, it returns the minimal unique digital coordinate along that dimension.
     */
    Integer min( Dimension k ) const;

    /**
     * @param k a coordinate.
     * @return the maximal digital coordinate in the \a k-dimension.
     * @note For periodic dimension, it returns the maximal unique digital coordinate along that dimension.
     */
    Integer max( Dimension k ) const;

    /**
     * @return the lower bound for digital points in this space.
     * @note For periodic dimension, it returns the lower digital point with unique coordinates. See also the \ref KhalimskySpaceNDBounds "class documentation".
     */
    const Point & lowerBound() const;

    /**
     * @return the upper bound for digital points in this space.
     * @note For periodic dimension, it returns the upper digital point with unique coordinates. See also the \ref KhalimskySpaceNDBounds "class documentation".
     */
    const Point & upperBound() const;

    /**
     * @return the lower bound for cells in this space.
     * @note For periodic dimension, it returns the upper cell with unique coordinates. See also the \ref KhalimskySpaceNDBounds "class documentation".
     */
    const Cell & lowerCell() const;

    /**
     * @return the upper bound for cells in this space.
     * @note For periodic dimension, it returns the upper cell with unique coordinates. See also the \ref KhalimskySpaceNDBounds "class documentation".
     */
    const Cell & upperCell() const;

    /**
     * @param c an unsigned cell.
     * @param k a dimension.
     * @returns \c true if the given unsigned cell has his k-th Khalimsky coordinate
     * between those of the cells returned by lowerCell and upperCell.
     * @note For periodic dimension, even if there is no bounds, it guarantees that
     * each cell has unique coordinates.
     * @see uCell(const Cell &) const to correct Khalimsky coordinates along
     * periodic dimensions.
     */
    bool uIsValid( const PreCell & c, Dimension k ) const;

    /**
     * @param c a unsigned cell.
     * @returns \c true if the given unsigned cell has Khalimsky coordinates
     * between those of the cells returned by lowerCell and upperCell.
     * @note For periodic dimension, even if there is no bounds, it guarantees that
     * each cell has unique coordinates.
     * @see uCell(const Cell &) const to correct Khalimsky coordinates along
     * periodic dimensions.
     */
    bool uIsValid( const PreCell & c ) const;

    /**
     * @param c a signed cell.
     * @param k a dimension.
     * @returns \c true if the given signed cell his k-th Khalimsky coordinate
     * between those of the cells returned by lowerCell and upperCell.
     * @note For periodic dimension, even if there is no bounds, it guarantees that
     * each cell has unique coordinates.
     * @see sCell(const SCell &) const to correct Khalimsky coordinates along
     * periodic dimensions.
     */
    bool sIsValid( const SPreCell & c, Dimension k ) const;

    /**
     * @param c a signed cell.
     * @returns \c true if the given signed cell has Khalimsky coordinates
     * between those of the cells returned by lowerCell and upperCell.
     * @note For periodic dimension, even if there is no bounds, it guarantees that
     * each cell has unique coordinates.
     * @see sCell(const SCell &) const to correct Khalimsky coordinates along
     * periodic dimensions.
     */
    bool sIsValid( const SPreCell & c ) const;

    /**
     * @param p an integer point (Khalimsky coordinates of cell).
     * @param k a dimension.
     * @returns \c true if the given cell has his k-th Khalimsky coordinate
     * between those of the cells returned by lowerCell and upperCell.
     * @note For periodic dimension, even if there is no bounds, it guarantees that
     * each cell has unique coordinates.
     */
    bool cIsValid( const Point & p, Dimension k ) const;

    /**
     * @param p an integer point (Khalimsky coordinates of cell).
     * @returns \c true if the given cell has Khalimsky coordinates
     * between those of the cells returned by lowerCell and upperCell.
     * @note For periodic dimension, even if there is no bounds, it guarantees that
     * each cell has unique coordinates.
     */
    bool cIsValid( const Point & p ) const;

    /// @}

    // ----------------------- Closure type query --------------------------
    /** @name Closure type query
     *  @{
     */
  public:

    /**
     * @return 'true' iff the space is closed or periodic along every dimension.
     */
    bool isSpaceClosed() const;

    /**
     * @param k the dimension.
     * @return 'true' iff the space is closed or periodic along the specified dimension.
     */
    bool isSpaceClosed( Dimension k ) const;

    /**
     * @return 'true' iff the space is periodic along every dimension.
     */
    bool isSpacePeriodic() const;

    /**
     * @param k the dimension.
     * @return 'true' iff the space is periodic along the specified dimension.
     */
    bool isSpacePeriodic( Dimension k ) const;

    /**
     * @return 'true' iff the space is periodic along at least one dimension.
     */
    bool isAnyDimensionPeriodic() const;

    /** Gets closure type.
     * @param k the dimension.
     * @return closure type along the specified dimension.
     */
    Closure getClosure( Dimension k ) const;

    /// @}

    // ----------------------- Cell creation services --------------------------
    /** @name Cell creation services
     * @{
     */
  public:

    /** From an unsigned cell, returns an unsigned cell lying into this Khalismky space.
     *
     * Along a non-periodic dimension, if the given Khalimsky coordinate lies
     * outside the space, it replaces it by the nearest valid coordinate.
     *
     * Along a periodic dimension, the Khalimsky coordinate is corrected
     * (by periodicity) to lie between the coordinates of lowerCell() and upperCell().
     *
     * @param c a cell.
     * @return the same cell with appropriate Khalimsky coordinates
     *         along periodic dimensions.
     * @post `uIsValid(uCell(c))` is \a true.
     * @post `uCell(c) == c` if `uIsValid(c)`.
     */
    Cell uCell( const PreCell & c ) const;

    /** From the Khalimsky coordinates of a cell,
     * builds the corresponding unsigned cell lying into this Khalismky space.
     *
     * Along a non-periodic dimension, if the given Khalimsky coordinate lies
     * outside the space, it is replaced by the nearest valid coordinate.
     *
     * Along a periodic dimension, the Khalimsky coordinate is corrected
     * (by periodicity) to lie between the coordinates of lowerCell() and upperCell().
     *
     * @param kp an integer point (Khalimsky coordinates of cell).
     * @return the unsigned cell.
     * @post `uIsValid(uCell(kp))` is \a true.
     */
    Cell uCell( const Point & kp ) const;

    /** From the digital coordinates of a point in Zn and a cell type,
     * builds the corresponding unsigned cell lying into this Khalismky space.
     *
     * Along a non-periodic dimension, if the given digital coordinate lies
     * outside the space, it is replaced by the nearest valid coordinate.
     *
     * Along a periodic dimension, the digital coordinate is corrected
     * (by periodicity) to lie between the coordinates of lowerCell() and upperCell().
     *
     * @param p an integer point (digital coordinates of cell).
     * @param c another cell defining the topology.
     * @return the cell having the topology of [c] and the given
     * digital coordinates [p].
     * @post `uIsValid(uCell(p, c))` is \a true.
     */
    Cell uCell( Point p, const PreCell & c ) const;

    /** From a signed cell, returns a signed cell lying into this Khalismky space.
     *
     * Along a non-periodic dimension, if the given Khalimsky coordinate lies
     * outside the space, it replaces it by the nearest valid coordinate.
     *
     * Along a periodic dimension, the Khalimsky coordinate is corrected
     * (by periodicity) to lie between the coordinates of lowerCell() and upperCell().
     *
     * @param c a signed cell.
     * @return the same signed cell with appropriate Khalimsky coordinates
     *          along periodic dimensions.
     * @post `sIsValid(sCell(c))` is \a true.
     * @post `sCell(c) == c` if `sIsValid(c)`.
     */
    SCell sCell( const SPreCell & c ) const;

    /** From the Khalimsky coordinates of a cell and a sign,
     * builds the corresponding signed cell lying into this Khalismky space.
     *
     * Along a non-periodic dimension, if the given Khalimsky coordinate lies
     * outside the space, it is replaced by the nearest valid coordinate.
     *
     * Along a periodic dimension, the Khalimsky coordinate is corrected
     * (by periodicity) to lie between the coordinates of lowerCell() and upperCell().
     *
     * @param kp an integer point (Khalimsky coordinates of cell).
     * @param sign the sign of the cell (either POS or NEG).
     * @return the signed cell.
     * @post `sIsValid(sCell(kp, sign))` is \a true.
     */
    SCell sCell( const Point & kp, Sign sign = POS ) const;

    /** From the digital coordinates of a point in Zn and a signed cell type,
     * builds the corresponding signed cell lying into this Khalismky space.
     *
     * Along a non-periodic dimension, if the given digital coordinate lies
     * outside the space, it is replaced by the nearest valid coordinate.
     *
     * Along a periodic dimension, the digital coordinate is corrected
     * (by periodicity) to lie between the coordinates of lowerCell() and upperCell().
     *
     * @param p an integer point (digital coordinates of cell).
     * @param c another cell defining the topology and sign.
     * @return the cell having the topology and sign of [c] and the given
     * digital coordinates [p].
     * @post `sIsValid(sCell(p, c))` is \a true.
     */
    SCell sCell( Point p, const SPreCell & c ) const;

    /** From the digital coordinates of a point in Zn,
     * builds the corresponding spel (cell of maximal dimension) lying into this Khalismky space.
     *
     * Along a non-periodic dimension, if the given digital coordinate lies
     * outside the space, it is replaced by the nearest valid coordinate.
     *
     * Along a periodic dimension, the digital coordinate is corrected
     * (by periodicity) to lie between the coordinates of lowerCell() and upperCell().
     *
     * @param p an integer point (digital coordinates of cell).
     * @return the spel having the given digital coordinates [p].
     * @post `uIsValid(uSpel(p))` is \a true.
     */
    Cell uSpel( Point p ) const;

    /** From the digital coordinates of a point in Zn,
     * builds the corresponding spel (cell of maximal dimension) lying into this Khalismky space.
     *
     * Along a non-periodic dimension, if the given digital coordinate lies
     * outside the space, it is replaced by the nearest valid coordinate.
     *
     * Along a periodic dimension, the digital coordinate is corrected
     * (by periodicity) to lie between the coordinates of lowerCell() and upperCell().
     *
     * @param p an integer point (digital coordinates of cell).
     * @param sign the sign of the cell (either POS or NEG).
     * @return the signed spel having the given digital coordinates [p].
     * @post `sIsValid(sSpel(p, sign))` is \a true.
     */
    SCell sSpel( Point p, Sign sign = POS ) const;

    /** From the digital coordinates of a point in Zn,
     * builds the corresponding pointel (cell of dimension 0) lying into this Khalismky space.
     *
     * Along a non-periodic dimension, if the given digital coordinate lies
     * outside the space, it is replaced by the nearest valid coordinate.
     *
     * Along a periodic dimension, the digital coordinate is corrected
     * (by periodicity) to lie between the coordinates of lowerCell() and upperCell().
     *
     * @param p an integer point (digital coordinates of cell).
     * @return the pointel having the given digital coordinates [p].
     * @post `uIsValid(uSpel(p))` is \a true.
     */
    Cell uPointel( Point p ) const;

    /** From the digital coordinates of a point in Zn,
     * builds the corresponding pointel (cell of dimension 0) lying into this Khalismky space.
     *
     * Along a non-periodic dimension, if the given digital coordinate lies
     * outside the space, it is replaced by the nearest valid coordinate.
     *
     * Along a periodic dimension, the digital coordinate is corrected
     * (by periodicity) to lie between the coordinates of lowerCell() and upperCell().
     *
     * @param p an integer point (digital coordinates of cell).
     * @param sign the sign of the cell (either POS or NEG).
     *
     * @return the signed pointel having the given digital coordinates [p].
     * @post `uIsValid(uSpel(p))` is \a true.
     */
    SCell sPointel( Point p, Sign sign = POS ) const;

    ///@}

    // ----------------------- Read accessors to cells ------------------------
    /** @name Read accessors to cells
     * @{
     */
  public:
    /**
     * @param c any unsigned cell.
     * @param k any valid dimension.
     * @return its Khalimsky coordinate along [k].
     * @pre  `uIsValid(c)` is \a true.
     */
    Integer uKCoord( const Cell & c, Dimension k ) const;

    /**
     * @param c any unsigned cell.
     * @param k any valid dimension.
     * @return its digital coordinate along [k].
     * @pre  `uIsValid(c)` is \a true.
     */
    Integer uCoord( const Cell & c, Dimension k ) const;

    /**
     * @param c any unsigned cell.
     * @return its Khalimsky coordinates.
     * @pre  `uIsValid(c)` is \a true.
     */
    const Point & uKCoords( const Cell & c ) const;

    /**
     * @param c any unsigned cell.
     * @return its digital coordinates
     * @pre  `uIsValid(c)` is \a true.
     */
    Point uCoords( const Cell & c ) const;

    /**
     * @param c any signed cell.
     * @param k any valid dimension.
     * @return its Khalimsky coordinate along [k].
     * @pre  `uIsValid(c)` is \a true.
     */
    Integer sKCoord( const SCell & c, Dimension k ) const;

    /**
     * @param c any signed cell.
     * @param k any valid dimension.
     * @return its digital coordinate along [k].
     * @pre  `uIsValid(c)` is \a true.
     */
    Integer sCoord( const SCell & c, Dimension k ) const;

    /**
     * @param c any signed cell.
     * @return its Khalimsky coordinates.
     * @pre  `uIsValid(c)` is \a true.
     */
    const Point & sKCoords( const SCell & c ) const;

    /**
     * @param c any signed cell.
     * @return its digital coordinates.
     * @pre  `uIsValid(c)` is \a true.
     */
    Point sCoords( const SCell & c  ) const;

    /**
     * @param c any signed cell.
     * @return its sign.
     * @pre  `uIsValid(c)` is \a true.
     */
    Sign sSign( const SCell & c ) const;

    /// @}

    // ----------------------- Write accessors to cells ------------------------
    /** @name Write accessors to cells
     * @{
     */
  public:

    /** Sets the [k]-th Khalimsky coordinate of [c] to [i].
     * @param c any unsigned cell.
     * @param k any valid dimension.
     * @param i an integer coordinate within the space.
     * @note The coordinate \a i will be corrected if \a k is a periodic dimension.
     * @pre  `uIsValid(c)` is \a true and \a i is within the space bounds if \a k is a non-periodic dimension.
     * @post `uIsValid(c)` is \a true.
     */
    void uSetKCoord( Cell & c, Dimension k, Integer i ) const;

    /** Sets the [k]-th Khalimsky coordinate of [c] to [i].
     * @param c any signed cell.
     * @param k any valid dimension.
     * @param i an integer coordinate within the space.
     * @note The coordinate \a i will be corrected if \a k is a periodic dimension.
     * @pre  `sIsValid(c)` is \a true and \a i is within the space bounds if \a k is a non-periodic dimension.
     * @post `sIsValid(c)` is \a true.
     */
    void sSetKCoord( SCell & c, Dimension k, Integer i ) const;

    /** Sets the [k]-th digital coordinate of [c] to [i].
     * @param c any unsigned cell.
     * @param k any valid dimension.
     * @param i an integer coordinate within the space.
     * @note The coordinate \a i will be corrected if \a k is a periodic dimension.
     * @pre  `uIsValid(c)` is \a true and \a i is within the space bounds if \a k is a non-periodic dimension.
     * @post `uIsValid(c)` is \a true.
     */
    void uSetCoord( Cell & c, Dimension k, Integer i ) const;

    /** Sets the [k]-th digital coordinate of [c] to [i].
     * @param c any signed cell.
     * @param k any valid dimension.
     * @param i an integer coordinate within the space.
     * @note The coordinate \a i will be corrected if \a k is a periodic dimension.
     * @pre  `sIsValid(c)` is \a true and \a i is within the space bounds if \a k is a non-periodic dimension.
     * @post `sIsValid(c)` is \a true.
     */
    void sSetCoord( SCell & c, Dimension k, Integer i ) const;

    /** Sets the Khalimsky coordinates of [c] to [kp].
     * @param c any unsigned cell.
     * @param kp the new Khalimsky coordinates for [c].
     * @note The coordinates \a kp will be corrected for periodic dimensions.
     * @pre  \a kp is within the space bounds for non-periodic dimensions.
     * @post `uIsValid(c)` is \a true.
     *
     */
    void uSetKCoords( Cell & c, const Point & kp ) const;

    /** Sets the Khalimsky coordinates of [c] to [kp].
     * @param c any signed cell.
     * @param kp the new Khalimsky coordinates for [c].
     * @note The coordinates \a kp will be corrected for periodic dimensions.
     * @pre  \a kp is within the space bounds for non-periodic dimensions.
     * @post `sIsValid(c)` is \a true.
     */
    void sSetKCoords( SCell & c, const Point & kp ) const;

    /** Sets the digital coordinates of [c] to [kp].
     * @param c any unsigned cell.
     * @param kp the new Khalimsky coordinates for [c].
     * @note The coordinates \a kp will be corrected for periodic dimensions.
     * @pre  \a kp is within the space bounds for non-periodic dimensions.
     * @post `uIsValid(c)` is \a true.
     */
    void uSetCoords( Cell & c, const Point & kp ) const;

    /** Sets the digital coordinates of [c] to [kp].
     * @param c any signed cell.
     * @param kp the new Khalimsky coordinates for [c].
     * @note The coordinates \a kp will be corrected for periodic dimensions.
     * @pre  \a kp is within the space bounds for non-periodic dimensions.
     * @post `sIsValid(c)` is \a true.
     */
    void sSetCoords( SCell & c, const Point & kp ) const;

    /** Sets the sign of the cell.
     * @param c (modified) any signed cell.
     * @param s any sign.
     */
    void sSetSign( SCell & c, Sign s ) const;

    /// @}

    // -------------------- Conversion signed/unsigned ------------------------
    /** @name Conversion signed/unsigned
     * @{
     */
  public:
    /** Creates a signed cell from an unsigned one and a given sign.
     * @param p any unsigned cell.
     * @param s a sign.
     * @return the signed version of the cell [p] with sign [s].
     * @pre  `uIsValid(p)` is \a true.
     * @post `sIsValid(signs(p, s))` is \a true.
     */
    SCell signs( const Cell & p, Sign s ) const;

    /** Creates an unsigned cell from a signed one.
     * @param p any signed cell.
     * @return the unsigned version of the cell [p].
     * @pre  `sIsValid(p)` is \a true.
     * @post `uIsValid(unsigns(p))` is \a true.
     */
    Cell unsigns( const SCell & p ) const;

    /**
     * Creates the signed cell with the inverse sign of [p].
     * @param p any signed cell.
     * @return the cell [p] with opposite sign.
     * @pre  `sIsValid(p)` is \a true.
     * @post `sIsValid(sOpp(p))` is \a true.
     */
    SCell sOpp( const SCell & p ) const;

    /// @}

    // ------------------------- Cell topology services -----------------------
    /** @name Cell topology services
     * @{
     */
  public:
    /**
     * @param p any unsigned cell.
     * @return the topology word of [p].
     */
    Integer uTopology( const Cell & p ) const;

    /**
     * @param p any signed cell.
     * @return the topology word of [p].
     */
    Integer sTopology( const SCell & p ) const;

    /**
     * @param p any unsigned cell.
     * @return the dimension of the cell [p].
     */
    Dimension uDim( const Cell & p ) const;

    /**
     * @param p any signed cell.
     * @return the dimension of the cell [p].
     */
    Dimension sDim( const SCell & p ) const;

    /**
     * @param b any unsigned cell.
     * @return 'true' if [b] is a surfel (spans all but one coordinate).
     */
    bool uIsSurfel( const Cell & b ) const;

    /**
     * @param b any signed cell.
     * @return 'true' if [b] is a surfel (spans all but one coordinate).
     */
    bool sIsSurfel( const SCell & b ) const;

    /**
     * @param p any cell.
     * @param k any direction.
     * @return 'true' if [p] is open along the direction [k].
     */
    bool uIsOpen( const Cell & p, Dimension k ) const;

    /**
     * @param p any signed cell.
     * @param k any direction.
     * @return 'true' if [p] is open along the direction [k].
     */
    bool sIsOpen( const SCell & p, Dimension k ) const;

    /// @}

    // -------------------- Iterator services for cells ------------------------
    /** @name Iterator services for cells
     * @{
     */
  public:

    /** Given an unsigned cell [p], returns an iterator to iterate over
     * each coordinate the cell spans. (A spel spans all coordinates; a
     * surfel all but one, etc). Example:
     *
     * @code
     * KSpace::Cell p;
     * ...
     * for ( KSpace::DirIterator q = ks.uDirs( p ); q != 0; ++q )
     * {
     *   Dimension dir = *q;
     * ...
     * }
     * @endcode
     *
     * @param p any unsigned cell.
     * @return an iterator that points on the first coordinate spanned
     * by the cell.
     */
    DirIterator uDirs( const Cell & p ) const;

    /** Given a signed cell [p], returns an iterator to iterate over
     * each coordinate the cell spans. (A spel spans all coordinates; a
     * surfel all but one, etc). Example:
     *
     * @code
     * KSpace::SCell p;
     * ...
     * for ( KSpace::DirIterator q = ks.uDirs( p ); q != 0; ++q )
     * {
     *   Dimension dir = *q;
     * ...
     * }
     *  @endcode
     *
     * @param p any signed cell.
     * @return an iterator that points on the first coordinate spanned
     * by the cell.
     */
    DirIterator sDirs( const SCell & p ) const;

    /** Given an unsigned cell [p], returns an iterator to iterate over each
     * coordinate the cell does not span. (A spel spans all coordinates;
     * a surfel all but one, etc). Example:
     *
     * @code
     * KSpace::Cell p;
     * ...
     * for ( KSpace::DirIterator q = ks.uOrthDirs( p ); q != 0; ++q )
     * {
     *   Dimension dir = *q;
     * ...
     * }
     * @endcode
     *
     * @param p any unsigned cell.
     * @return an iterator that points on the first coordinate spanned
     * by the cell.
     */
    DirIterator uOrthDirs( const Cell & p ) const;

    /** Given a signed cell [p], returns an iterator to iterate over each
     * coordinate the cell does not span. (A spel spans all coordinates;
     * a surfel all but one, etc). Example:
     *
     * @code
     * KSpace::SCell p;
     * ...
     * for ( KSpace::DirIterator q = ks.uOrthDirs( p ); q != 0; ++q )
     * {
     *   Dimension dir = *q;
     * ...
     * }
     * @endcode
     *
     * @param p any signed cell.
     * @return an iterator that points on the first coordinate spanned
     * by the cell.
     */
    DirIterator sOrthDirs( const SCell & p ) const;

    /** Given an unsigned surfel [s], returns its orthogonal direction (ie,
     * the coordinate where the surfel is closed).
     *
     * @param s an unsigned surfel
     * @return the orthogonal direction of [s]
     */
    Dimension uOrthDir( const Cell & s ) const;

    /** Given a signed surfel [s], returns its orthogonal direction (ie,
     * the coordinate where the surfel is closed).
     *
     * @param s a signed surfel
     * @return the orthogonal direction of [s]
     */
    Dimension sOrthDir( const SCell & s ) const;

    /// @}

    // -------------------- Unsigned cell geometry services --------------------
    /** @name Unsigned cell geometry services
     * @{
     */
  public:

    /**
     * @return the k-th Khalimsky coordinate of the first cell of the space with the same type as [p].
     * @note For periodic dimension, it returns the first unique coordinate of a cell of same type as \a p.
     * @post The returned coordinate is between `lowerCell()[k]` and `upperCell()[k]`.
     */
    Integer uFirst( const PreCell & p, Dimension k ) const;

    /**
     * @return the first cell of the space with the same type as [p].
     * @note Along periodic dimensions, it returns the first unique coordinate of a cell of same type as \a p.
     * @post `uIsValid(uFirst(p))` is \a true.
     */
    Cell uFirst( const PreCell & p ) const;

    /**
     * @return the k-th Khalimsky coordinate of the last cell of the space with the same type as [p].
     * @note For periodic dimension, it returns the last unique coordinate of a cell of same type as \a p.
     * @post The returned coordinate is between `lowerCell()[k]` and `upperCell()[k]`.
     */
    Integer uLast( const PreCell & p, Dimension k ) const;

    /**
     * @return the last cell of the space with the same type as [p].
     * @note Along periodic dimensions, it returns the last unique coordinate of a cell of same type as \a p.
     * @post `uIsValid(uLast(p))` is \a true.
     */
    Cell uLast( const PreCell & p ) const;

    /**
     * @param p any cell.
     * @param k the coordinate that is changed.
     * @return the same element as [p] except for the incremented
     * coordinate [k].
     * @pre `uIsValid(p)` and not `uIsMax(p)`.
     * @post `uIsValid(uGetIncr(p, k))` is \a true.
     */
    Cell uGetIncr( const Cell & p, Dimension k ) const;

    /** Useful to check if you are going out of the space.
     *
     * @param p any cell.
     * @param k the tested coordinate.
     * @return true if [p] cannot have its [k]-coordinate augmented
     * without leaving the space.
     * @note It returns always \a false for periodic dimension.
     * @pre `uIsInside(p)` is \a true.
     */
    bool uIsMax( const Cell & p, Dimension k ) const;


    /** Useful to check if you are going out of the space.
     *
     *  @param p any cell.
     *  @param k the tested coordinate.
     *  @return true if [p] has its [k]-coordinate within the allowed bounds.
     *  @note It returns always \a true for periodic dimension.
     */
    bool uIsInside( const PreCell & p, Dimension k ) const;


    /** Useful to check if you are going out of the space.
     *
     * @param p any cell.
     * @return true if [p] has its coordinates within the allowed bounds.
     * @note Only the non-periodic dimensions are checked.
     */
    bool uIsInside( const PreCell & p ) const;

    /** Useful to check if you are going out of the space.
     *
     *  @param p any integer point (Khalimsky coordinates).
     *  @param k the tested coordinate.
     *  @return true if [p] has its [k]-coordinate within the allowed bounds.
     *  @note It returns always \a true for periodic dimension.
     */
    bool cIsInside( const Point & p, Dimension k ) const;


    /** Useful to check if you are going out of the space.
     *
     * @param p any integer point (Khalimsky coordinates).
     * @return true if [p] has its coordinates within the allowed bounds.
     * @note Only the non-periodic dimensions are checked.
     */
    bool cIsInside( const Point & p ) const;

    /** Useful to check if you are going out of the space.
     *
     * @param p any cell.
     * @param k the concerned coordinate.
     * @return the cell similar to [p] but with the maximum allowed
     * [k]-coordinate.
     * @pre  `uIsValid(p, d)` is \a true for each dimension \a d different than \a k.
     * @post `uIsValid(uGetMax(p, k))` is \a true.
     */
    Cell uGetMax( Cell p, Dimension k ) const;

    /**
     * @param p any cell.
     * @param k the coordinate that is changed.
     * @return the same element as [p] except for an decremented
     * coordinate [k].
     * @pre  `uIsValid(p)` and not `uIsMin(p)`.
     * @post `uIsValid(uGetDecr(p, k))` is \a true.
     */
    Cell uGetDecr( const Cell & p, Dimension k ) const;

    /** Useful to check if you are going out of the space.
     * @param p any cell.
     * @param k the tested coordinate.
     * @return true if [p] cannot have its [k]-coordinate decreased
     * without leaving the space.
     * @note It returns always \a false for periodic dimension.
     * @pre  `uIsInside(p)` is \a true.
     */
    bool uIsMin( const Cell & p, Dimension k ) const;

    /** Useful to check if you are going out of the space.
     *
     * @param p any cell.
     * @param k the concerned coordinate.
     * @return the cell similar to [p] but with the minimum allowed
     * [k]-coordinate.
     * @pre `uIsValid(p, d)` is \a true for each dimension \a d different than \a k.
     * @post `uIsValid(uGetMin(p, k))` is \a true.
     */
    Cell uGetMin( Cell p, Dimension k ) const;


    /**
     * @param p any cell.
     * @param k the coordinate that is changed.
     * @param x the increment.
     * @return the same element as [p] except for a coordinate [k]
     * incremented with x.
     * @pre `uIsValid(p)` and ( `x <= uDistanceToMax(p, k)` or `isSpacePeriodic(k)` ).
     * @post `uIsValid(uGetAdd(p, k, x))` is \a true.
     */
    Cell uGetAdd( const Cell & p, Dimension k, Integer x ) const;

    /**
     * @param p any cell.
     * @param k the coordinate that is changed.
     * @param x the decrement.
     * @return the same element as [p] except for a coordinate [k]
     * decremented with x.
     * @pre `uIsValid(p)` and ( `x <= uDistanceToMin(p, k)` or `isSpacePeriodic(k)` ).
     * @post `uIsValid(uGetSub(p, k, x))` is \a true.
     */
    Cell uGetSub( const Cell & p, Dimension k, Integer x ) const;

    /** Useful to check if you are going out of the space (for non-periodic dimensions).
     *
     * @param p any cell.
     * @param k the coordinate that is tested.
     * @return the number of increment to do to reach the maximum value.
     * @pre `uIsValid(p)` is \a true.
     */
    Integer uDistanceToMax( const Cell & p, Dimension k ) const;

    /** Useful to check if you are going out of the space (for non-periodic dimensions).
     *
     * @param p any cell.
     * @param k the coordinate that is tested.
     * @return the number of decrement to do to reach the minimum
     * value.
     * @pre `uIsValid(p)` is \a true.
     */
    Integer uDistanceToMin( const Cell & p, Dimension k ) const;

    /** Add the vector [vec] to [p].
     *
     * @param p any cell.
     * @param vec any pointel.
     * @return the unsigned copy of the cell [p] translated by [coord].
     * @pre  `uIsValid(p, k)` and ( `uDistanceToMin(p, k) <= vec[k] <= uDistanceToMax(p, k) or isPeriodicSpace(k) )` for each dimension \a k.
     * @post `uIsValid(uTranslation(p, vec))` is \a true.
     */
    Cell uTranslation( const Cell & p, const Vector & vec ) const;

    /** Return the projection of [p] along the [k]th direction toward
     *  [bound]. Otherwise said, p[ k ] == bound[ k ] afterwards.
     *
     * @param p any cell.
     * @param bound the element acting as bound (same topology as p).
     * @param k the concerned coordinate.
     * @return the projection.
     * @pre  `uIsValid(p)` and `uIsValid(bound)` and `uIsOpen(p, k) == uIsOpen(bound, k)`
     * @post `uIsValid(uProjection(p, bound, k))` and `uTopology(p) == uTopology(uProjection(p, bound, k))`.
     */
    Cell uProjection( const Cell & p, const Cell & bound, Dimension k ) const;

    /** Projects [p] along the [k]th direction toward
     *  [bound]. Otherwise said, p[ k ] == bound[ k ] afterwards
     *
     * @param [in,out] p any cell.
     * @param [in] bound the element acting as bound (same topology as p).
     * @param [in] k the concerned coordinate.
     * @pre  `uIsValid(p)` and `uIsValid(bound)` and `uIsOpen(p, k) == uIsOpen(bound, k)`
     * @post `uIsValid(p)`.
     */
    void uProject( Cell & p, const Cell & bound, Dimension k ) const;

    /** Increment the cell [p] to its next position (as classically done in
     *  a scanning). Example:
     *
     * \code
     * KSpace K;
     * Cell first, last; // lower and upper bounds
     * Cell p = first;
     * do
     * { // ... whatever [p] is the current cell
     * }
     * while ( K.uNext( p, first, last ) );
     * \endcode
     *
     * @param p any cell.
     * @param lower the lower bound.
     * @param upper the upper bound.
     * @return true if p is still within the bounds, false if the
     * scanning is finished.
     * @pre `uIsValid(p)` and `uIsValid(lower)` and `uIsValid(upper)` and `uTopology(p) == uTopology(lower) == uTopology(upper)`.
     * @post `uIsValid(p)` is \a true.
     */
    bool uNext( Cell & p, const Cell & lower, const Cell & upper ) const;

    /// @}

    // -------------------- Signed cell geometry services --------------------
    /** @name Signed cell geometry services
     * @{
     */
  public:

    /**
     * @return the k-th coordinate of the first cell of the space with the same type as [p].
     * @note For periodic dimension, it returns the first unique coordinate of a cell of same type as \a p.
     * @post The returned coordinate is between `lowerCell()[k]` and `upperCell()[k]`.
    */
    Integer sFirst( const SPreCell & p, Dimension k ) const;

    /**
     * @return the first cell of the space with the same type as [p].
     * @note Along periodic dimensions, it returns the first unique coordinate of a cell of same type as \a p.
     * @post `sIsValid(sFirst(p))` is \a true.
     */
    SCell sFirst( const SPreCell & p ) const;

    /**
     * @return the k-th Khalimsky coordinate of the last cell of the space with the same type as [p].
     * @note For periodic dimension, it returns the last unique coordinate of a cell of same type as \a p.
     * @post The returned coordinate is between `lowerCell()[k]` and `upperCell()[k]`.
    */
    Integer sLast( const SPreCell & p, Dimension k ) const;

    /**
     * @return the last cell of the space with the same type as [p].
     * @note Along periodic dimensions, it returns the last unique coordinate of a cell of same type as \a p.
     * @post `sIsValid(sLast(p))` is \a true.
     */
    SCell sLast( const SPreCell & p ) const;

    /**
     * @param p any cell.
     * @param k the coordinate that is changed.
     * @return the same element as [p] except for the incremented
     * coordinate [k].
     * @pre `sIsValid(p)` and not `sIsMax(p)`.
     * @post `sIsValid(sGetIncr(p, k))` is \a true.
     */
    SCell sGetIncr( const SCell & p, Dimension k ) const;

    /** Useful to check if you are going out of the space.
     * @param p any cell.
     * @param k the tested coordinate.
     * @return true if [p] cannot have its [k]-coordinate augmented
     * without leaving the space.
     * @note It returns always \a false for periodic dimension.
     * @pre `sIsInside(p)` is \a true.
     */
    bool sIsMax( const SCell & p, Dimension k ) const;

    /** Useful to check if you are going out of the space.
     * @param p any cell.
     * @param k the tested coordinate.
     * @return true if [p] has its [k]-coordinate within the allowed bounds.
     *  @note It returns always \a true for periodic dimension.
     */
    bool sIsInside( const SPreCell & p, Dimension k ) const;

    /** Useful to check if you are going out of the space.
     *
     * @param p any cell.
     * @return true if [p] has its coordinates within the allowed bounds.
     * @note Only the non-periodic dimensions are checked.
     */
    bool sIsInside( const SPreCell & p ) const;

    /** Useful to check if you are going out of the space.
     *
     * @param p any cell.
     * @param k the concerned coordinate.
     * @return the cell similar to [p] but with the maximum allowed
     * [k]-coordinate.
     * @pre  `sIsValid(p, d)` is \a true for each dimension \a d different than \a k.
     * @post `sIsValid(sGetMax(p, k))` is \a true.
     */
    SCell sGetMax( SCell p, Dimension k ) const;

    /**
     * @param p any cell.
     * @param k the coordinate that is changed.
     * @return the same element as [p] except for an decremented
     * coordinate [k].
     * @pre  `sIsValid(p)` and not `sIsMin(p)`.
     * @post `sIsValid(sGetDecr(p, k))` is \a true.
     */
    SCell sGetDecr( const SCell & p, Dimension k ) const;

    /** Useful to check if you are going out of the space.
     *
     * @param p any cell.
     * @param k the tested coordinate.
     * @return true if [p] cannot have its [k]-coordinate decreased
     * without leaving the space.
     * @note It returns always \a false for periodic dimension.
     * @pre  `sIsInside(p)` is \a true.
     */
    bool sIsMin( const SCell & p, Dimension k ) const;

    /** Useful to check if you are going out of the space.
     * @param p any cell.
     * @param k the concerned coordinate.
     * @return the cell similar to [p] but with the minimum allowed
     * [k]-coordinate.
     * @pre `sIsValid(p, d)` is \a true for each dimension \a d different than \a k.
     * @post `sIsValid(sGetMin(p, k))` is \a true.
    */
    SCell sGetMin( SCell p, Dimension k ) const;

    /**
     * @param p any cell.
     * @param k the coordinate that is changed.
     * @param x the increment.
     * @return the same element as [p] except for a coordinate [k]
     * incremented with x.
     * @pre `sIsValid(p)` and ( `x <= sDistanceToMax(p, k)` or `isSpacePeriodic(k)` ).
     * @post `sIsValid(sGetAdd(p, k, x))` is \a true.
     */
    SCell sGetAdd( const SCell & p, Dimension k, Integer x ) const;

    /**
     * @param p any cell.
     * @param k the coordinate that is changed.
     * @param x the decrement.
     * @return the same element as [p] except for a coordinate [k]
     * decremented with x.
     * @pre suIsValid(p)` and ( `x <= sDistanceToMin(p, k)` or `isSpacePeriodic(k)` ).
     * @post `sIsValid(sGetSub(p, k, x))` is \a true.
     */
    SCell sGetSub( const SCell & p, Dimension k, Integer x ) const;

    /** Useful to check if you are going out of the space (for non-periodic dimensions).
     *
     * @param p any cell.
     * @param k the coordinate that is tested.
     * @return the number of increment to do to reach the maximum value.
     * @pre `sIsValid(p)` is \a true.
     */
    Integer sDistanceToMax( const SCell & p, Dimension k ) const;

    /** Useful to check if you are going out of the space (for non-periodic dimensions).
     *
     * @param p any cell.
     * @param k the coordinate that is tested.
     * @return the number of decrement to do to reach the minimum
     * value.
     * @pre `sIsValid(p)` is \a true.
     */
    Integer sDistanceToMin( const SCell & p, Dimension k ) const;

    /** Add the vector [vec] to [p].
     *
     * @param p any cell.
     * @param vec any pointel.
     * @return the signed code of the cell [p] translated by [coord].
     * @pre  `sIsValid(p, k)` and ( `sDistanceToMin(p, k) <= vec[k] <= sDistanceToMax(p, k) or isPeriodicSpace(k) )` for each dimension \a k.
     * @post `sIsValid(sTranslation(p, vec))` is \a true.
     */
    SCell sTranslation( const SCell & p, const Vector & vec ) const;

    /** Return the projection of [p] along the [k]th direction toward
     *  [bound]. Otherwise said, p[ k ] == bound[ k ] afterwards.
     *
     * @param p any cell.
     * @param bound the element acting as bound (same topology as p).
     * @param k the concerned coordinate.
     * @return the projection.
     * @pre  `sIsValid(p)` and `sIsValid(bound)` and `sIsOpen(p, k) == sIsOpen(bound, k)`
     * @post `sIsValid(sProjection(p, bound, k))` and `sTopology(p) == sTopology(sProjection(p, bound, k))`.
     */
    SCell sProjection( const SCell & p, const SCell & bound, Dimension k ) const;

    /** Projects [p] along the [k]th direction toward
     *  [bound]. Otherwise said, p[ k ] == bound[ k ] afterwards.
     *
     * @param p any cell.
     * @param bound the element acting as bound (same topology as p).
     * @param k the concerned coordinate.
     * @pre  `sIsValid(p)` and `sIsValid(bound)` and `sIsOpen(p, k) == sIsOpen(bound, k)`
     * @post `sIsValid(p)`.
     */
    void sProject( SCell & p, const SCell & bound, Dimension k ) const;

    /** Increment the cell [p] to its next position (as classically done in
     *  a scanning). Example:

     * \code
     * KSpace K;
     * Cell first, last; // lower and upper bounds
     * Cell p = first;
     * do
     * { // ... whatever [p] is the current cell
     * }
     * while ( K.uNext( p, first, last ) );
     * \endcode
     *
     * @param p any cell.
     * @param lower the lower bound.
     * @param upper the upper bound.
     * @return true if p is still within the bounds, false if the
     * scanning is finished.
     * @pre `sIsValid(p)` and `sIsValid(lower)` and `sIsValid(upper)` and `sTopology(p) == sTopology(lower) == sTopology(upper)`.
     * @post `sIsValid(p)` is \a true.
     */
    bool sNext( SCell & p, const SCell & lower, const SCell & upper ) const;

    /// @}

    // ----------------------- Neighborhood services --------------------------
    /** @name Neighborhood services
     * @{
     */
  public:

    /** Computes the 1-neighborhood of the cell [c] and returns
     *  it. It is the set of cells with same topology that are adjacent
     *  to [c] and which are within the bounds of this space.
     *
     * @param cell the unsigned cell of interest.
     * @return the cells of the 1-neighborhood of [cell].
     * @pre  `uIsValid(cell)` is \a true.
     * @post `uIsValid(c)` is \a true for every returned cell \a c.
     */
    Cells uNeighborhood( const Cell & cell ) const;

    /** Computes the 1-neighborhood of the cell [c] and returns
     *  it. It is the set of cells with same topology that are adjacent
     *  to [c] and which are within the bounds of this space.
     *
     * @param cell the signed cell of interest.
     * @return the cells of the 1-neighborhood of [cell].
     * @pre  `sIsValid(cell)` is \a true.
     * @post `sIsValid(c)` is \a true for every returned cell \a c.
     */
    SCells sNeighborhood( const SCell & cell ) const;

    /** Computes the proper 1-neighborhood of the cell [c] and returns
     *  it. It is the set of cells with same topology that are adjacent
     *  to [c], different from [c] and which are within the bounds of
     *  this space.
     *
     * @param cell the unsigned cell of interest.
     * @return the cells of the proper 1-neighborhood of [cell].
     * @pre  `uIsValid(cell)` is \a true.
     * @post `uIsValid(c)` is \a true for every returned cell \a c.
     */
    Cells uProperNeighborhood( const Cell & cell ) const;

    /** Computes the proper 1-neighborhood of the cell [c] and returns
     *  it. It is the set of cells with same topology that are adjacent
     *  to [c], different from [c] and which are within the bounds of
     *  this space.
     *
     * @param cell the signed cell of interest.
     * @return the cells of the proper 1-neighborhood of [cell].
     * @pre  `sIsValid(cell)` is \a true.
     * @post `sIsValid(c)` is \a true for every returned cell \a c.
     */
    SCells sProperNeighborhood( const SCell & cell ) const;

    /**
     * @param p any cell.
     * @param k the coordinate that is changed.
     * @param up if 'true' the orientation is forward along axis
     * [k], otherwise backward.
     * @return the adjacent element to [p] along axis [k] in the given
     * direction and orientation.
     * @note It is an alias to 'up ? uGetIncr( p, k ) : uGetDecr( p, k )'.
     * @pre  `uIsValid(p)` and not `uIs(Min|Max)(p, k)` depending on \a up value.
     * @post `uIsValid(uAdjacent(p, k, up)) is \a true.
     */
    Cell uAdjacent( const Cell & p, Dimension k, bool up ) const;

    /**
     * @param p any cell.
     * @param k the coordinate that is changed.
     * @param up if 'true' the orientation is forward along axis
     * [k], otherwise backward.
     * @return the adjacent element to [p] along axis [k] in the given
     * direction and orientation.
     * @note It is an alias to 'up ? sGetIncr( p, k ) : sGetDecr( p, k )'.
     * @pre  `sIsValid(p)` and not `sIs(Min|Max)(p, k)` depending on \a up value.
     * @post `sIsValid(sAdjacent(p, k, up)) is \a true.
     */
    SCell sAdjacent( const SCell & p, Dimension k, bool up ) const;

    /// @}

    // ----------------------- Incidence services --------------------------
    /** @name Incidence services
     * @{
     */
  public:

    /**
     * @param c any unsigned cell.
     * @param k any coordinate.
     * @param up if 'true' the orientation is forward along axis
     * [k], otherwise backward.
     * @return the forward or backward unsigned cell incident to [c]
     * along axis [k], depending on [up].
     * @note It may be a lower incident cell if [c] is open along axis
     * [k], else an upper incident cell.
     * @pre  `uIsValid(c)` and the cell should have an incident cell in this direction/orientation.
     * @post `uIsValid(uIncident(c, k, up))` is \a true.
     */
    Cell uIncident( const Cell & c, Dimension k, bool up ) const;

    /**
     * @param c any signed cell.
     * @param k any coordinate.
     * @param up if 'true' the orientation is forward along axis
     * [k], otherwise backward.
     * @return the forward or backward signed cell incident to [c]
     * along axis [k], depending on [up]. It is worthy to note
     * that the forward and backward cell have opposite
     * sign. Furthermore, the sign of these cells is defined so as to
     * satisfy a boundary operator.
     * @note It may be a lower incident cell if [c] is open along axis
     * [k], else an upper incident cell.
     * @pre  `sIsValid(c)` and the cell should have an incident cell in this direction/orientation.
     * @post `sIsValid(sIncident(c, k, up))` is \a true.
     */
    SCell sIncident( const SCell & c, Dimension k, bool up ) const;

    /**
     * @param c any unsigned cell.
     * @return the cells directly low incident to c in this space.
     * @pre  `uIsValid(c)` is \a true.
     * @post `uIsValid(b)` is \a true for every returned cell \a b.
     */
    Cells uLowerIncident( const Cell & c ) const;

    /**
     * @param c any unsigned cell.
     * @return the cells directly up incident to c in this space.
     * @pre  `uIsValid(c)` is \a true.
     * @post `uIsValid(b)` is \a true for every returned cell \a b.
     */
    Cells uUpperIncident( const Cell & c ) const;

    /**
     *  @param c any signed cell.
     *  @return the signed cells directly low incident to c in this space.
     *  @note it is the lower boundary of c expressed as a list of signed cells.
     * @pre  `sIsValid(c)` is \a true.
     * @post `sIsValid(b)` is \a true for every returned cell \a b.
     */
    SCells sLowerIncident( const SCell & c ) const;

    /**
     * @param c any signed cell.
     * @return the signed cells directly up incident to c in this space.
     * @note it is the upper boundary of c expressed as a list of signed cells.
     * @pre  `sIsValid(c)` is \a true.
     * @post `sIsValid(b)` is \a true for every returned cell \a b.
     */
    SCells sUpperIncident( const SCell & c ) const;

    /**
     * @param c any unsigned cell.
     * @return the proper faces of [c] (chain of lower incidence) that belong to the space.
     * @pre  `uIsValid(c)` is \a true.
     * @post `uIsValid(b)` is \a true for every returned cell \a b.
     */
    Cells uFaces( const Cell & c ) const;

    /**
     * @param c any unsigned cell.
     * @return the proper cofaces of [c] (chain of upper incidence) that belong to the space.
     * @pre  `uIsValid(c)` is \a true.
     * @post `uIsValid(b)` is \a true for every returned cell \a b.
     */
    Cells uCoFaces( const Cell & c ) const;

    /** Return 'true' if the direct orientation of [p] along [k] is in
     *  the positive coordinate direction. The direct orientation in a
     *  direction allows to go from positive incident cells to positive
     *  incident cells.  This means that
     *  @code
     *  K.sSign( K.sIncident( p, k, K.sDirect( p, k ) ) ) == K.POS
     *  @endcode
     *  is always true.
     *
     * @param p any signed cell.
     * @param k any coordinate.
     * @return the direct orientation of [p] along [k] (true is
     * upward, false is backward).
     */
    bool sDirect( const SCell & p, Dimension k ) const;

    /**
     * @param p any signed cell.
     * @param k any coordinate.
     * @return the direct incident cell of [p] along [k] (the incident
     * cell along [k])
     * @pre  `sIsValid(p)` and the cell should have a direct incident cell in this direction.
     * @post `sIsValid(c)` is \a true for every returned cell \a c.
ose sign is positive).
     */
    SCell sDirectIncident( const SCell & p, Dimension k ) const;

    /**
     * @param p any signed cell.
     * @param k any coordinate.
     * @return the indirect incident cell of [p] along [k] (the incident
     * cell along [k] whose sign is negative).
     * @pre  `sIsValid(p)` and the cell should have an indirect incident cell in this direction.
     * @post `sIsValid(c)` is \a true for every returned cell \a c.
ose sign is positive).
    */
    SCell sIndirectIncident( const SCell & p, Dimension k ) const;

    /// @}

    // ----------------------- Interface --------------------------------------
    /** @name DGtal interface
     * @{
     */
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

    /// @}

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    Point myLower;
    Point myUpper;
    Cell myCellLower;
    Cell myCellUpper;
    std::array<Closure, dimension> myClosure;

    // ------------------------- Hidden services ------------------------------
  protected:


  private:



    // ------------------------- Internals ------------------------------------
    /** @name Internals
     * @{
     */
  private:
    /**
     * Used by uFaces for computing incident faces.
     */
    void uAddFaces( Cells& faces, const Cell& c, Dimension axis ) const;

    /**
     * Used by uCoFaces for computing incident cofaces.
     */
    void uAddCoFaces( Cells& cofaces, const Cell& c, Dimension axis ) const;

    /// @}

  }; // end of class KhalimskySpaceND


  /**
   * Overloads 'operator<<' for displaying objects of class 'KhalimskySpaceND'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'KhalimskySpaceND' to write.
   * @return the output stream after the writing.
   */
  template < Dimension dim,
             typename TInteger >
  std::ostream&
  operator<< ( std::ostream & out,
               const KhalimskySpaceND<dim, TInteger > & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/KhalimskySpaceND.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined KhalimskySpaceND_h

#undef KhalimskySpaceND_RECURSES
#endif // else defined(KhalimskySpaceND_RECURSES)
