/* -*- mode: c++ -*- */
/**
 * @file   Tools.h
 * @author Sebastien Fourey <http://www.greyc.ensicaen.fr/~seb>
 * @date   Nov 2008
 * 
 * @brief 
 */
/*
 * \@copyright This File is part of the Board library which is
 * licensed under the terms of the GNU Lesser General Public Licence.
 * See the LICENCE file for further details.
 */
#ifndef _BOARD_TOOLS_H_
#define _BOARD_TOOLS_H_

#include <iostream>
#include <ctime>
#include <cstring>

#define SHOW( V ) std::cerr << " " #V " = " << ( V ) << std::endl

namespace LibBoard {

  /**
   * A "prefixable" message stream
   * 
   */
  class MessageStream {
  public:
    
    inline MessageStream( std::ostream & out, const char * prefix  );
    
    template<typename T> 
    inline MessageStream operator<<( const T & v );
    
  private:
    std::ostream & _out;    
    const char * _prefix;
  };
  
  extern MessageStream error;
  extern MessageStream warning;
  extern MessageStream notice;
  
  MessageStream::MessageStream( std::ostream & out, const char * prefix )
    : _out( out ),
      _prefix( prefix )
  {
  }

  template<typename T> 
  MessageStream MessageStream::operator<<( const T & v )
  {
    if ( _prefix )
      _out << _prefix << v;
    else
      _out << v;
    return MessageStream( _out, 0 );
  }


#if defined( _MSC_VER )
#define secured_sprintf sprintf_s
#else
#define secured_sprintf snprintf
#endif // defined( _MSC_VER )

inline void secured_strncpy( char * dst, const char * src, size_t count );
inline void secured_ctime( char * str, const time_t * t, size_t count ); 

}

#include "Tools.ih"

#endif /* _SHAPE_H_ */

