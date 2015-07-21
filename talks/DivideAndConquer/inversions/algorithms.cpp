#include "algos_apps.h"

 
  
template<>  
bool (*algos::sorting_algos::compare< unsigned int >::comp_func)(unsigned int, unsigned int) = NULL;

template<>
unsigned int (*algos::sorting_algos::compare< unsigned int >::limit_func)() = &std::numeric_limits< unsigned int >::max;
    
 
int main(int argv, char** argc){

  /**
   * @compile g++ algorithms.cpp
   */

    unsigned int low, high;
    unsigned int array[] = {6,5,4,3,2,1};
    std::vector<unsigned int> list(array, array + 6);

    std::cout << "The list:" 
	      << list 
	      << std::endl;

    std::cout << "The number of inversions is: " 
      	      << algos::apps::count_inversions<unsigned int>(list) 
	      << std::endl;
    
  
    return EXIT_SUCCESS;
}

