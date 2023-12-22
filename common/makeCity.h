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
void makeHouse();

gluggModel makeBases();
gluggModel makeTiles();

void makeWall();
void makeRoom();
gluggModel makeStory();



#endif



// --------------- Implementation part ----------------

// #ifdef MAIN

#ifndef _CITY_BUILDER_IMPLEMENTATION
#define _CITY_BUILDER_IMPLEMENTATION

//SCRIPT FOR PLOTS
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
	float scale = 1;
	float translate = 2.5;
	gluggBegin(GLUGG_TRIANGLES);	
	gluggScale(scale,0.1,scale);
	gluggTranslate(-19.0,0.0,-19.0);		
	makeNetwork(16,0);	
	return gluggBuildModel(0);

}


void makeWall(int depth, float translate){
	float newScale = fixedArray[globalCounter]*0.9f;
    printf("Scale: %f \n", fixedArray[globalCounter]);
    globalCounter++;
	if(depth != 0){				
		gluggPushMatrix();		
		gluggTranslate(translate,0.0,0);		
		gluggScale(newScale,1,newScale);
		gluggRotate(M_PI_2,0,0,1);
		gluggTranslate(3,0.0,0);		
		//west
		gluggPushMatrix();
		gluggTranslate(0,1,0);
		makeRectangle(2,4);		
		gluggPopMatrix();
		//east
		gluggPushMatrix();
		gluggTranslate(0,-1,0);
		makeRectangle(2,4);		
		gluggPopMatrix();
		//north
		gluggRotate(M_PI_2,1,0,0);
		gluggPushMatrix();
		gluggTranslate(0,1,0);
		makeRectangle(2,4);		
		gluggPopMatrix();
		//South
		gluggPushMatrix();
		gluggTranslate(0,-1,0);
		makeRectangle(2,4);		
		gluggPopMatrix();
		gluggPopMatrix();
		makeWall(depth-1, translate+2.5);		
	}
		
}

void makeRoom(int depth, float translate){		
	if(depth != 0){
		gluggPushMatrix();
		gluggTranslate(0.0,0.0,translate);	
		makeWall(16,0);			
		gluggPopMatrix();
		makeRoom(depth-1,translate+2.5);		
	}	
}

gluggModel makeStory(){
	gluggSetPositionName("inPosition");
	gluggSetNormalName("inNormal");
	gluggSetTexCoordName("inTexCoord");
	gluggSetColorName("inColor");
	float scale = 1;
	float translate = 2.5;
	gluggBegin(GLUGG_TRIANGLES);
	gluggColor(0.0,0.0,1.0);	
	gluggScale(scale,0.15,scale);
	gluggTranslate(-19.0,1.0,-19.0);		
	globalCounter = 0;
    makeRoom(16,0);	    
	return gluggBuildModel(0);
}

// gluggModel makeHouse(){
// 	int numberOfStories = randomiser(1,10);
// 	for(int i = 0; i < numberOfStories; i++){
// 		// add stories
// 	}
// 	// add roof
// }

void setHorizontalCeil(int depth, float translate){
	float newScale = fixedArray[globalCounter]*0.9f;
    printf("Scale: %f \n", fixedArray[globalCounter]);
    globalCounter++;
	if(depth != 0){				
		gluggPushMatrix();		
		gluggTranslate(translate,5.1,0);		
		gluggScale(newScale,0.1,newScale);
		gluggCube(2);		
		gluggPopMatrix();
		setHorizontalCeil(depth-1, translate+2.5);		
	}
		
}

void setVerticalCeil(int depth, float translate){		
	if(depth != 0){
		gluggPushMatrix();
		gluggTranslate(0.0,0.0,translate);				
		setHorizontalCeil(16, 0);
		gluggPopMatrix();
		setVerticalCeil(depth-1,translate+2.5);		
	}	
}

gluggModel makeCeilings(){
	gluggSetPositionName("inPosition");
	gluggSetNormalName("inNormal");
	gluggSetTexCoordName("inTexCoord");
	gluggSetColorName("inColor");
	float scale = 1;
	float translate = 2.5;
	gluggBegin(GLUGG_TRIANGLES);
	gluggColor(0.0,0.0,1.0);	
	gluggScale(scale,0.15,scale);
	gluggTranslate(-19.0,1.0,-19.0);		
	globalCounter = 0;
    setVerticalCeil(16,0);	    
	return gluggBuildModel(0);
}


//SCRIPT FOR FOUNDATION OF HOUSE
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
	gluggSetColorName("inColor");
	float scale = 1;
	float translate = 2.5;
	gluggBegin(GLUGG_TRIANGLES);
	gluggColor(0.0,0.0,1.0);	
	gluggScale(scale,0.15,scale);
	gluggTranslate(-19.0,1.0,-19.0);		
	globalCounter = 0;
    makeBasesNetwork(16,0);	    
	return gluggBuildModel(0);
}



#endif
// #endif