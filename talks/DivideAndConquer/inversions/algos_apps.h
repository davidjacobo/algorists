#ifndef ALGOS_APPS_H
#define ALGOS_APPS_H

#include "algosTools.h"


namespace algos {
  namespace apps {
  
    template<typename T>
    unsigned int countSplit(std::vector<T>& inputList
			    , unsigned int begin
			    , unsigned int middle
			    , unsigned int end) {
       unsigned int inversions = 0;
       unsigned int leftSize = middle - begin;
       unsigned int rightSize = end - middle;
      
       std::vector<T> leftPart(leftSize);
       std::vector<T> rightPart(rightSize);
      
       for(unsigned int i= 0, j=begin; i<leftSize ;i++)leftPart[i] = inputList[j++]; 
       for(unsigned int i= 0, j=middle; i<rightSize ;i++)rightPart[i] = inputList[j++];
       
       
       unsigned int j = 0, i = 0, k;

       for(k = begin; k < end && i < leftSize && j < rightSize ; k++) {
          if(leftPart[i] < rightPart[j])
             inputList[k] = leftPart[i++];
          else {
             inputList[k] = rightPart[j++];
             inversions += leftSize - i;
          }          
       }
       
       for(;i<leftSize && k<end;i++) inputList[k++] = leftPart[i];
       for(;j<rightSize&& k<end;j++) inputList[k++] = rightPart[j];

       return inversions;
    }

    template< typename T>
    unsigned int _count(std::vector<T>& inputList
	               , unsigned int begin
	               , unsigned int end ) {
       unsigned int currentArraySize = end - begin;
       if(currentArraySize == 1) {
          return 0;
       }

       unsigned int middle = begin + (end - begin)/2;
       unsigned int x = _count<T>(inputList, begin, middle);
       unsigned int y = _count<T>(inputList, middle, end);      
       unsigned int z = countSplit<T>(inputList, begin, middle, end);
      
       return x+y+z;
    }
  
    template< typename T >
    unsigned int count_inversions(const std::vector<T>& inputList) {
       std::vector<T> inputListCpy = inputList;
       unsigned int total = _count<T>(inputListCpy, 0, inputListCpy.size());

       return total;
    }
  }
}


#endif /*ALGOS_APPS_H*/
