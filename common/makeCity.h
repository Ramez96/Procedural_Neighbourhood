#ifndef _CITY_BUILDER_
#define _CITY_BUILDER_

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "MicroGlut.h"
#include "glugg.h"
#include "gluggShapes.h"
#include "myUtils.h"
// uses framework Cocoa
// uses framework OpenGL
#include "GL_utilities.h"
#include "VectorUtils4.h"


void makeBasement();
void makeHouse();
void makeWall();

#endif



// --------------- Implementation part ----------------

// #ifdef MAIN

#ifndef _CITY_BUILDER_IMPLEMENTATION
#define _CITY_BUILDER_IMPLEMENTATION

void makeHouse(){
    makeBasement();
}


void makeBasement(){
    
    float newScale = randomiser(0.6f, 0.8f);

    gluggPushMatrix();
    gluggScale(newScale, 1, newScale);
    gluggTranslate(0,2.0,0);
    gluggCube(2);
    gluggColor(0.0, 1.0, 0.0); 
    gluggPopMatrix();

}





#endif
// #endif