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

float scaleArray[526] = {0};
float storiesArray[526] = {0};
int globalCounter = 0;
int storiesCounter = 0;

const float CUBESIZE = 2.0;
const float TILEHEIGHT = CUBESIZE;
const float BASEHEIGHT = CUBESIZE;
const float WALLHEIGHT = 1.0;
const float CEILHEIGHT =CUBESIZE;
const float ROADWIDTH = 2.5;
const float TILEYSCALE = 0.005;
const float BASEYSCALE = 0.2;
const float CEILYSCALE = 0.05;
const float WALLYSCALE = 1.0f;


const int STARTDEPTH = 16;




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

void setHorizontalCeil(int depth, float translate){

	if(depth != 0){			
		float newScale = scaleArray[globalCounter]*0.9f;
		// printf("Scale: %f \n", scaleArray[globalCounter]);
		float numberOfStories = storiesArray[storiesCounter];
		globalCounter++;	
		storiesCounter++;
		for (size_t i = 0; i < numberOfStories; i++){
		gluggPushMatrix();		
		gluggTranslate(translate,(WALLHEIGHT)/CEILYSCALE*i+CEILHEIGHT*i,0);	
		gluggScale(newScale+0.001,1,newScale+0.001);
		gluggCube(CUBESIZE);		
		gluggPopMatrix();
		}		
		setHorizontalCeil(depth-1, translate+ROADWIDTH);			

	}
}

void setVerticalCeil(int depth, float translate){		
	if(depth != 0){
		gluggPushMatrix();
		gluggTranslate(0.0,0.0,translate);				
		setHorizontalCeil(STARTDEPTH, 0);
		gluggPopMatrix();
		setVerticalCeil(depth-1,translate+ROADWIDTH);		
	}	
}

gluggModel makeCeilings(){
	gluggSetPositionName("inPosition");
	gluggSetNormalName("inNormal");
	gluggSetTexCoordName("inTexCoord");
	gluggSetColorName("inColor");
	float scale = 1;
	float translate = ROADWIDTH;
	gluggBegin(GLUGG_TRIANGLES);
	gluggColor(0.0,0.0,1.0);	
	gluggTranslate(-19.5,BASEYSCALE*BASEHEIGHT+TILEYSCALE*TILEHEIGHT+WALLHEIGHT*WALLYSCALE+CEILYSCALE*CEILHEIGHT/2,-19.5);		
	gluggScale(scale,CEILYSCALE,scale);
	globalCounter = 0;
	storiesCounter = 0;
    setVerticalCeil(STARTDEPTH,0);	    
	return gluggBuildModel(0);
}



void makeWall(int depth, float translate){
	
	if(depth != 0){			
		float newScale = scaleArray[globalCounter]*0.9f;
    	// printf("Scale: %f \n", scaleArray[globalCounter]);
		int numberOfStories = randomiser(1,10);
		printf("Randomised Number %d\n", numberOfStories );
		storiesArray[storiesCounter] = numberOfStories;	
		globalCounter++;
		storiesCounter++;
		gluggPushMatrix();		
		gluggTranslate(translate,0.0,0);		
		gluggScale(newScale,1,newScale);
		gluggRotate(M_PI_2,0,0,1);
		for(int i = 0; i < numberOfStories; i++){
			// translate the height of the wall + ceiling x number of stories
			gluggPushMatrix();
			if (i == 0){
				gluggTranslate(WALLHEIGHT*i,0.0,0);		
			}
			else{
				gluggTranslate(WALLHEIGHT*i+CEILYSCALE*CEILHEIGHT*i,0.0,0);		
			}
			//west
			gluggPushMatrix();
			gluggTranslate(0,1,0);
			makeRectangle(WALLHEIGHT,2);		
			gluggPopMatrix();
			//east
			gluggPushMatrix();
			gluggRotate(M_PI,1,0,0);
			gluggTranslate(0,1,0);
			makeRectangle(WALLHEIGHT,2);		
			gluggPopMatrix();
			//north
			gluggRotate(M_PI_2,1,0,0);
			gluggPushMatrix();
			gluggTranslate(0,1,0);
			makeRectangle(WALLHEIGHT,2);		
			gluggPopMatrix();
			//South
			gluggPushMatrix();
			gluggRotate(M_PI,1,0,0);
			gluggTranslate(0,1,0);
			makeRectangle(WALLHEIGHT,2);		
			gluggPopMatrix();
			gluggPopMatrix();
		}			
		gluggPopMatrix();

		makeWall(depth-1, translate+ROADWIDTH);		
	}
		
}

void makeRoom(int depth, float translate){		
	if(depth != 0){
		int numberOfStories = randomiser(1,50);	
		gluggPushMatrix();
		gluggTranslate(0.0,0.0,translate);	
		makeWall(STARTDEPTH,0);			
		gluggPopMatrix();
		makeRoom(depth-1,translate+ROADWIDTH);		
	}	
}

gluggModel makeStory(){	
	gluggSetPositionName("inPosition");
	gluggSetNormalName("inNormal");
	gluggSetTexCoordName("inTexCoord");
	gluggSetColorName("inColor");
	float scale = 1;
	float translate = ROADWIDTH;
	gluggBegin(GLUGG_TRIANGLES);
	gluggTranslate(-19.5,BASEYSCALE*BASEHEIGHT+TILEYSCALE*TILEHEIGHT+WALLYSCALE*WALLHEIGHT/2,-19.5);		
	gluggScale(scale,WALLYSCALE,scale);
	globalCounter = 0;
	storiesCounter = 0;
    makeRoom(STARTDEPTH,0);	

	return gluggBuildModel(0);    
}





//SCRIPT FOR FOUNDATION OF HOUSE
void makeBasesRow(int depth, float translate){
	
	if(depth != 0){		
		float newScale = scaleArray[globalCounter]*0.9f;
		printf("Scale: %f \n", scaleArray[globalCounter]);
		globalCounter++;		
		gluggPushMatrix();		
		gluggTranslate(translate,0.0,0);		
		gluggScale(newScale,1,newScale);
		gluggCube(CUBESIZE);		
		gluggPopMatrix();
		makeBasesRow(depth-1, translate+ROADWIDTH);		
	}
}

void makeBasesNetwork(int depth, float translate){		
	if(depth != 0){
		gluggPushMatrix();
		gluggTranslate(0.0,0.0,translate);				
		makeBasesRow(STARTDEPTH, 0);
		gluggPopMatrix();
		makeBasesNetwork(depth-1,translate+ROADWIDTH);		
	}	
}

gluggModel makeBases(){
	gluggSetPositionName("inPosition");
	gluggSetNormalName("inNormal");
	gluggSetTexCoordName("inTexCoord");
	gluggSetColorName("inColor");
	float scale = 1;
	float translate = ROADWIDTH;
	gluggBegin(GLUGG_TRIANGLES);
	gluggTranslate(-19.5,TILEYSCALE*TILEHEIGHT+BASEYSCALE*BASEHEIGHT/2,-19.5);		

	gluggScale(scale,BASEYSCALE,scale);
	globalCounter = 0;
    makeBasesNetwork(STARTDEPTH,0);	    
	return gluggBuildModel(0);
}

//SCRIPT FOR TILES
void makeBlockRow(int depth, float translate){
	    
	if(depth != 0){				
		float newScale = randomiser(0.7,1.0);
		scaleArray[globalCounter] = newScale;    
		// printf("OG Scale: %f \n", scaleArray[globalCounter]);
		globalCounter++;	
		gluggPushMatrix();		
		gluggTranslate(translate,0,0);		
		gluggScale(newScale,1,newScale);
		gluggCube(CUBESIZE);		
		gluggPopMatrix();
		makeBlockRow(depth-1, translate+ROADWIDTH);		
	}
	
}
void makeNetwork(int depth, float translate){		
	if(depth != 0){
		gluggPushMatrix();
		gluggTranslate(0.0,0,translate);				
		makeBlockRow(STARTDEPTH, 0);
		gluggPopMatrix();
		makeNetwork(depth-1,translate+ROADWIDTH);		
	}	
}
gluggModel makeTiles(){	
	float scale = 1;
	float translate = ROADWIDTH;
	gluggBegin(GLUGG_TRIANGLES);	
	gluggTranslate(-19.5,TILEYSCALE*TILEHEIGHT/2,-19.5);		
	gluggScale(scale,TILEYSCALE,scale);
	makeNetwork(STARTDEPTH,0);	
	return gluggBuildModel(0);

}


#endif
// #endif