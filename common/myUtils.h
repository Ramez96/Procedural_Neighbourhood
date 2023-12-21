#ifndef _MY_UTILS_
#define _MY_UTILS_


#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float randomiser(float min, float max);

#endif


// #ifdef MAIN

#ifndef _MY_UTILS_IIMPLEMENTATION_
#define _MY_UTILS_IIMPLEMENTATION_

float randomiser(float min,float max){
	float r = min+static_cast<float>(std::rand())/(RAND_MAX)*(max-min);
  	// printf("print divisor number: %.2f\n",static_cast<float>(std::rand())/(RAND_MAX));		

	// printf("print random number: %.2f\n", r);		
    return r;	
}


#endif
// #endif