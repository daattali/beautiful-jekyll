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
 * @file Signal.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/07/06
 *
 * Header file for module Signal.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Signal_RECURSES)
#error Recursive header files inclusion detected in Signal.h
#else // defined(Signal_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Signal_RECURSES

#if !defined Signal_h
/** Prevents repeated inclusion of headers. */
#define Signal_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CowPtr.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /**
     Represents the signal data.

     @tparam TValue the type chosen for each sample (generally float
     or double).
  */
  template <typename TValue>
  struct SignalData {
    typedef TValue Value;

    /// a dyn. array on Value s.
    Value* data;
    /// the size of the array @ref data.
    unsigned int size;
    /// the true index of the zero abscissa.
    int zero;
    /// when 'true', the signal is periodic, otherwise infinite (with
    /// default value outside).
    bool periodic;

    /** 
     * Constructor. The object is not valid.
     * @see init.
     */
    SignalData();
    
    /** 
     * Initializer.
     *
     * @param s the number of data in the signal.
     * @param z the index of the zero-th element.
     * @param p 'true' if the signal is periodic.
     * @param def the default value.
     */
    void init( unsigned int s, int z = 0, bool p = false, 
               const Value & def = Value( 0 ) );

    /**
     * Initializer.
     *
     * @param t the array containing initial data.
     * @param size the size of the signal.
     * @param z the index of the zero-th element.
     * @param p 'true' if the signal is periodic.
     * @param def the default value.
     */
    void init( const Value* t, unsigned int size, int z = 0, bool p = false, 
               const Value & def = Value( 0 )  );
    
    /** 
     * Constructor.  
     *
     * @param s the number of data in the signal.
     * @param z the index of the zero-th element.
     * @param p 'true' if the signal is periodic.
     * @param def the default value.
     */
    SignalData( unsigned int s, int z = 0, bool p = false, 
                const Value & def = Value( 0 ) );
    
    /**
     * Constructor.
     * @param t the array containing initial data.
     * @param size the size of the signal.
     * @param z the index of the zero-th element.
     * @param p 'true' if the signal is periodic.
     * @param def the default value.
     */
    SignalData( const Value* t, unsigned int size, int z = 0, bool p = false, 
                const Value & def = Value( 0 )  );
    
    /** 
     * Destructor.
     */
    ~SignalData();
    
    /** 
     * Copy constructor.
     * @param other the data to clone.
     */
    SignalData( const SignalData & other );
    
    /** 
     * Assignment.
     * @param other the data to clone.
     * @return 'this'.
     */
    SignalData& operator=( const SignalData & other );
    
    /** 
     * Default value.
     * @return the default value.
     */
    const Value& defaut() const;
  };


  /////////////////////////////////////////////////////////////////////////////
  // template class Signal
  /**
     Description of template class 'Signal' <p> \brief Aim: Represents
     a discrete signal, periodic or not. The signal can be passed by
     value since it is only cloned when modified.

     @tparam TValue the type chosen for each sample (generally float
     or double).
     
     This class is a backport from
     [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene).
  */
  template <typename TValue>
  class Signal
  {
    
  public:
    typedef TValue Value;
    /** 
        @return the gaussian signal of order 2 (binomial signal of
        order 2 / 4).
        
        TValue must be able to represent real values.
    */
    static Signal<TValue> G2();

    /** 
        @return the binomial signal of order 2.
    */
    static Signal<TValue> H2();
    
    /** 
        @return the right difference signal.
    */
    static Signal<TValue> Delta();
    
    /** 
        @return the gaussian signal of order 2n (binomial signal of
        order 2n / 2^n).
    */
    static Signal<TValue> G2n( unsigned int n );

    /** 
        @return the binomial signal of order 2n.
    */
    static Signal<TValue> H2n( unsigned int n );
    
    /** 
        @return the differential operator with binomial weights of order 2n.
    */
    static Signal<TValue> D2n( unsigned int n );

    // ----------------------- Standard services ----------------------------
  public:
      
    /**
       Destructor. 
    */
    ~Signal();

    /**
       Constructor.
    */
    Signal();
      
    
    /**
       Constructor.
       @param size the size of the signal.
       @param z the index of the zero-th element.
       @param periodic 'true' if the signal is periodic.
       @param def the default value.
    */
    Signal( unsigned int size, int z, bool periodic, 
            const TValue & def = TValue( 0 )  );
    
    /**
       Constructor.
       @param t the array containing initial data.
       @param size the size of the signal.
       @param z the index of the zero-th element.
       @param periodic 'true' if the signal is periodic.
       @param def the default value.
    */
    Signal( const TValue* t, unsigned int size, int z, bool periodic, 
            const TValue & def = TValue( 0 )  );
    
    /**
       Copy constructor.
       @param other the object to clone.
    */
    Signal( const Signal<TValue> & other );
    
    /**
       Assignment.
       @param other the object to copy.
       @return a reference on 'this'.
    */
    Signal<TValue> & operator=( const Signal<TValue> & other );


    /** 
     * Initializer.
     *
     * @param s the number of data in the signal.
     * @param z the index of the zero-th element.
     * @param p 'true' if the signal is periodic.
     * @param def the default value.
     */
    void init( unsigned int s, int z = 0, bool p = false, 
               const TValue & def = TValue( 0 ) );

    /**
     * Initializer.
     *
     * @param t the array containing initial data.
     * @param size the size of the signal.
     * @param z the index of the zero-th element.
     * @param p 'true' if the signal is periodic.
     * @param def the default value.
     */
    void init( const TValue* t, unsigned int size, int z = 0, bool p = false, 
               const TValue & def = TValue( 0 )  );
 

    /**
       @return the number of elements in the signal.
    */
    unsigned int size() const;

    // ----------------------- Signal services ----------------------------
  public:
    
    /** 
        Protected rw access to value. If index is out of bound, return
        0 if not periodic or the correct value otherwise.
        
        @param i the index in the signal .
        
        @return the i-th value in the signal.
    */      
    TValue & operator[]( int i );
    
    /** 
        Protected ro access to value. If index is out of bound, return 0
        if not periodic or the correct value otherwise.
        
        @param i the index in the signal .
        
        @return the i-th value in the signal.
    */      
    const TValue & operator[]( int i ) const;
    
    /** 
        The signal becomes a constant signal of value [val].
  
        @param val the value of the whole signal.
    */      
    void setAll( const TValue & val = TValue( 0 ) );
    
    
    /** 
        External product of a signal by a scalar value.
        
        @param val the external value.
        
    */
    void multiply( const TValue & val );

    /** 
        Convolution product of two signals (F = this).
        F*G( a ) = sum F(a-i)G(i) 
        
        @param G the second signal (not periodic)
        
        @return the signal that is the convolution of F and G, of type
        F. The returned signal is periodic iff Fis periodic.
    */
    Signal<TValue> operator*( const Signal<TValue>& G );

    // ----------------------- Interface --------------------------------------
  public:

    /**
       Writes/Displays the object on an output stream.
       @param out the output stream where the object is written.
    */
    void selfDisplay ( std::ostream & out ) const;
    
    /**
       Checks the validity/consistency of the object.
       @return 'true' if the object is valid, 'false' otherwise.
    */
    bool isValid() const;

     
    // ------------------------- Datas --------------------------------------
  private:
      
    /**
       the array that stores the data.
    */
    CowPtr< SignalData<TValue> > m_data;
      
    // ------------------------- Hidden services ----------------------------
  protected:
    

  }; // end of class Signal


  /**
   * Overloads 'operator<<' for displaying objects of class 'Signal'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Signal' to write.
   * @return the output stream after the writing.
   */
  template <typename TValue>
  std::ostream&
  operator<< ( std::ostream & out, const Signal<TValue> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/math/Signal.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Signal_h

#undef Signal_RECURSES
#endif // else defined(Signal_RECURSES)
