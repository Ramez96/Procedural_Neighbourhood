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

float fixedArray[526] = {0};
int globalCounter = 0;
void makeNetwork();
void makeBasesNetwork();
void makeBlockRow();
void makeBasement();
void makeHouse();
void makeWall();
gluggModel makeBases();
gluggModel makeTiles();

#endif



// --------------- Implementation part ----------------

// #ifdef MAIN

#ifndef _CITY_BUILDER_IMPLEMENTATION
#define _CITY_BUILDER_IMPLEMENTATION

void makeHouse(){
    makeBases();
    makeTiles();
    makeBasement();
}

void makeBlockRow(int depth, float translate){
	float newScale = randomiser(0.7,1.0);
    fixedArray[globalCounter] = newScale;    
	printf("OG Scale: %f \n", fixedArray[globalCounter]);
    globalCounter++;	    
	if(depth != 0){				
		gluggPushMatrix();		
		gluggTranslate(translate,0,0);		
		gluggScale(newScale,1,newScale);
		gluggCube(2);		
		gluggPopMatrix();
		makeBlockRow(depth-1, translate+2.5);		
	}
		
}

void makeNetwork(int depth, float translate){		
	if(depth != 0){
		gluggPushMatrix();
		gluggTranslate(0.0,0.0,translate);				
		makeBlockRow(16, 0);
		gluggPopMatrix();
		makeNetwork(depth-1,translate+2.5);		
	}	
}


gluggModel makeTiles(){
	gluggSetPositionName("inPosition");
	gluggSetNormalName("inNormal");
	gluggSetTexCoordName("inTexCoord");
	float scale = 1;
	float translate = 2.5;
	gluggBegin(GLUGG_TRIANGLES);
	gluggScale(scale,0.1,scale);
	gluggTranslate(-19.0,0.0,-19.0);		
	makeNetwork(16,0);	
	return gluggBuildModel(0);

}

void makeBasesRow(int depth, float translate){
	float newScale = fixedArray[globalCounter]*0.9f;
    printf("Scale: %f \n", fixedArray[globalCounter]);
    globalCounter++;
	if(depth != 0){				
		gluggPushMatrix();		
		gluggTranslate(translate,0.0,0);		
		gluggScale(newScale,1,newScale);
		gluggCube(2);		
		gluggPopMatrix();
		makeBasesRow(depth-1, translate+2.5);		
	}
		
}

void makeBasesNetwork(int depth, float translate){		
	if(depth != 0){
		gluggPushMatrix();
		gluggTranslate(0.0,0.0,translate);				
		makeBasesRow(16, 0);
		gluggPopMatrix();
		makeBasesNetwork(depth-1,translate+2.5);		
	}	
}

gluggModel makeBases(){
	gluggSetPositionName("inPosition");
	gluggSetNormalName("inNormal");
	gluggSetTexCoordName("inTexCoord");
	float scale = 1;
	float translate = 2.5;
	gluggBegin(GLUGG_TRIANGLES);
	gluggScale(scale,0.15,scale);
	gluggTranslate(-19.0,1.0,-19.0);		
	globalCounter = 0;
    makeBasesNetwork(16,0);	    
	return gluggBuildModel(0);
}

void makeBasement(){
    float newScale = randomiser(0.6f, 0.8f);
    gluggPushMatrix();
    gluggScale(newScale, 1, newScale);
    gluggTranslate(0,0.0,0);
    gluggCube(2);
    gluggColor(0.0, 1.0, 0.0); 
    gluggPopMatrix();

}





#endif
// #endif