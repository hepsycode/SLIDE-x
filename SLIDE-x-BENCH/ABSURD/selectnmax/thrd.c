/******************************************************************************
*   Copyright 2021 Politecnico di Milano
*
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*******************************************************************************/

#include <stdint.h>
#include <values.h>


/**
 * @brief 
 * 
 * @param a 
 * @param pos 
 * @return double 
 */
typedef int8_t TARGET_TYPE;
typedef int8_t TARGET_INDEX;

TARGET_TYPE select_nmax_routine(){
    TARGET_INDEX nmax = 0;
    TARGET_INDEX i,j;
    for(j = 0; j < size; j++){
            if(a[j] > nmax){
                nmax = a[j];
            } 
    }
    for(i=0;i<pos-1;i++){   
        TARGET_INDEX max=0; 
        for(j = 0; j < size; j++){
            if(a[j] > max && a[j]<nmax){
                max = a[j];
            } 
        }
        nmax=max;
        
    }
    return nmax;

}

/**
 * @brief It searches for the random n-th greater element in a random array . The execution time is measured through user defined MEASURE_START()/MEASURE_STOP() macros. 
 */
void main(){
    select_nmax_routine();
}
