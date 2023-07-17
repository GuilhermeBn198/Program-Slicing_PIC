#pragma once

#include <boost/type_traits/is_same.hpp>

namespace metaSMT {
  namespace type {

    struct Boolean {
      template<typename STREAM> 
      friend STREAM & operator<< (STREAM & out, Boolean const & ) \
      {  return (out << "Boolean"); }

    };

      /** equality of Boolean Types **/
      template <typename T>
      bool operator== (Boolean const & , T const & ) \
      {  return boost::is_same<T, Boolean>::value; }

  } /* type */
} /* metaSMT */
