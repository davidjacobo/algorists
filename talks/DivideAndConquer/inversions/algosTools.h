#ifndef ALGOS_TOOLS_H
#define ALGOS_TOOLS_H

#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <limits>

/**
 * @brief Vector output format 
 */
template< typename T >
std::ostream& operator << ( std::ostream& _os, const std::vector< T >& array ){
  _os << " ( ";
  
  std::ostream_iterator< T > os(_os, " ");
  std::copy(array.begin(), array.end(), os);
 
  _os << " ) ";
     
  return _os;
}

namespace algos{
  namespace sorting_algos {
    /**
     * This is an implementation of an exception object to trow for bad
     * input order to sort
     */
    class order_error {
      public:
                
        /**
         * @brief Constructor by message
         */
        order_error(const std::string& _msg = "Invalid order to sort.")
        : msg(_msg){ }

        /**
         * @brief Say what is going on
         */
        const std::string& what() const
        { return msg; }
             
        protected:
                 
        /// The message
        std::string msg;
    };

    /*
	 * Class to perfom the comparison of two diferent keys in different
	 * types of data
     */
    template < typename T >
    struct compare{
  
      /*
	   * Pointer to a function to which type of comparison use.
	   * This pointer points to one of the previously defined methods
	   */
	  static bool (*comp_func)(T, T);

	  /*
	   * Pointer to a function to which numeric limit use to perform
	   * the ordering in the ordering methods
	   */
	  static T (*limit_func)();
	};

    /**
     * @brief Less Comparison 
     */
     template < typename T >
     bool less(T a, T b)
     { return a < b; }

    /**
     * @brief Great Comparison 
     */
     template < typename T >
     bool greater(T a, T b)
     { return a > b; }

    /**
     * @brief Less and equal Comparison 
     */
     template < typename T >
     bool lesseq(T a, T b)
     { return a <= b; }
 
    /**
     * @brief Great and equal Comparison 
     */
     template < typename T >
     bool greatereq(T a, T b)
     { return a >= b; }
     
  }
}

#endif /*ALGOS_TOOLS_H*/
