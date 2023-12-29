#ifndef _MY_UTILS_
#define _MY_UTILS_


#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctime>

float randomiser(float min, float max);

#endif


// #ifdef MAIN

#ifndef _MY_UTILS_IIMPLEMENTATION_
#define _MY_UTILS_IIMPLEMENTATION_

float randomiser(float min,float max){
    

    float randomFraction = static_cast<float>(std::rand()) / RAND_MAX;
    return min + randomFraction * (max - min);    
}
#endif
// #endif