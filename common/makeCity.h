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
float doorPosArray[526] = {0};
int globalCounter = 0;

const float CUBESIZE = 2.0;
const float TILEHEIGHT = CUBESIZE;
const float BASEHEIGHT = CUBESIZE;
const float WALLHEIGHT = 1.0;
const float TREEHEIGHT = 2.0;
const float CEILHEIGHT = CUBESIZE;
const float ROADWIDTH = 4;
const float TILEYSCALE = 0.005;
const float BASEYSCALE = 0.2;
const float CEILYSCALE = 0.05;
const float WALLYSCALE = 1.0f;


const int MAXSTORIES = 10;
const int STARTDEPTH = 10;
gluggModel tree, tiles, bases, story,ceiling, windows, roof, door,ground, sidewalks,roads;

void setTree(int depth, float rotAngle);
void setHorizontalTree(int depth, float translate);
void setVerticalTree(int depth,float translate);

void setHorizontalDoor(int depth, float translate);
void setVerticalDoor(int depth, float translate);

void setHorizontalRoof(int depth, float translate);
void setVerticalRoof(int depth, float translate);


void setHorizontalWindow(int depth, float translate);
void setVerticalWindow(int depth, float translate);

void setHorizontalCeil(int depth, float translate);
void setVerticalCeil(int depth, float translate);

void makeWall(int depth, float translate);
void makeRoom(int depth, float translate);

void makeBasesRow(int depth, float translate);
void makeBasesNetwork(int depth, float translate);

void makeNetwork(int depth, float translate);
void makeBlockRow(int depth, float translate);


gluggModel makeTiles();
gluggModel makeBases();
gluggModel makeStory();
gluggModel makeCeilings();
gluggModel MakeTree();
gluggModel makeDoor();
gluggModel makeRoof();
gluggModel makeWindows();
gluggModel makeSidewalks();
gluggModel makeRoads();
gluggModel makeFloor();

void foo(float translate, float scale,float start);
#endif

// --------------- Implementation part ----------------

// #ifdef MAIN

#ifndef _CITY_BUILDER_IMPLEMENTATION
#define _CITY_BUILDER_IMPLEMENTATION

void setTree(int depth, float rotAngle){
    if(depth != 0){
        gluggPushMatrix();
        gluggTranslate(0,1,0);
        gluggRotate(rotAngle,sin(rand()), sin(rand()), sin(rand()));
        gluggScale(0.8,0.8,0.8);
        gluggCylinderAlt(20,1,0.1,0.13);
        setTree(depth-1,-rotAngle);
        setTree(depth-1,rotAngle);
        gluggPopMatrix();
    }
}

void setHorizontalTree(int depth, float translate){
		if (depth != 0){
		if ((int)randomiser(0,2) == 1){
		float newScale = scaleArray[globalCounter];
		float treescale = randomiser(0.4,0.6);
		globalCounter++;
		gluggPushMatrix();
		gluggTranslate(translate,0,0);
		gluggScale(treescale,treescale,treescale);
		gluggCylinderAlt(20, 2, 0.1, 0.13);
		gluggPushMatrix();
		gluggTranslate(0,1,0);
		setTree(8,0.4);
		setTree(8,-0.55);
		setTree(8,-0.75);
		setTree(8,0.9);
		gluggPopMatrix();
		gluggPopMatrix();
		}
		setHorizontalTree(depth-1, translate+ROADWIDTH);
		}
}

void setVerticalTree(int depth, float translate){
	if(depth != 0){
		gluggPushMatrix();
		gluggTranslate(0.0,0,translate);
		setHorizontalTree(STARTDEPTH, 0);
		gluggPopMatrix();
		setVerticalTree(depth-1,translate+ROADWIDTH);
	}
}

gluggModel MakeTree(){
	float translate = 0;
	foo(translate,1,-17.5);
	setVerticalTree(STARTDEPTH,0);
	return gluggBuildModel(0);
}

void setHorizontalDoor(int depth, float translate){
	if(depth != 0){
		float newScale = scaleArray[globalCounter]*0.9f;
		float numberOfStories = storiesArray[globalCounter];
		int pos = randomiser(0,4);
		doorPosArray[globalCounter] = pos;
		globalCounter++;
		gluggPushMatrix();
		gluggTranslate(translate,0,0);
		gluggScale(newScale+0.001,1,newScale+0.001);
		gluggRotate(M_PI_2,0,0,1);


		// create door in the bottom floor
		gluggPushMatrix();
		gluggRotate(M_PI_2*pos,1,0,0);

		gluggTranslate(-0.1,1,0);
		gluggScale(0.8,1,0.3);
		gluggRectangle(1,2);
		gluggPopMatrix();


		gluggPopMatrix();
		setHorizontalDoor(depth-1, translate+ROADWIDTH);
	}
}
void setVerticalDoor(int depth, float translate){
	if(depth != 0){
		gluggPushMatrix();
		gluggTranslate(0.0,0.0,translate);
		setHorizontalDoor(STARTDEPTH, 0);
		gluggPopMatrix();
		setVerticalDoor(depth-1,translate+ROADWIDTH);
	}
}
gluggModel makeDoor(){
	float translate = BASEYSCALE*BASEHEIGHT+TILEYSCALE*TILEHEIGHT+WALLYSCALE*WALLHEIGHT/2;
	foo(translate,1,-19.5);
    setVerticalDoor(STARTDEPTH,0);
	return gluggBuildModel(0);
}

void setHorizontalRoof(int depth, float translate){
	if(depth != 0){
		float newScale = scaleArray[globalCounter]*0.9f;
		float numberOfStories = storiesArray[globalCounter];
		globalCounter++;
		if (numberOfStories <= MAXSTORIES/3){
			gluggPushMatrix();
			gluggTranslate(translate,0,0);
			gluggScale(newScale+0.001,1,newScale+0.001);			
			gluggTranslate(0,(numberOfStories-1)+(numberOfStories-1)*CEILYSCALE*CEILHEIGHT,0);
			
			gluggPushMatrix();
			gluggRoof(2,1,2);
			gluggPopMatrix();

			gluggPopMatrix();			
		}
		setHorizontalRoof(depth-1, translate+ROADWIDTH);
	}
}
void setVerticalRoof(int depth, float translate){
	if(depth != 0){
		gluggPushMatrix();
		gluggTranslate(0.0,0.0,translate);
		setHorizontalRoof(STARTDEPTH, 0);
		gluggPopMatrix();
		setVerticalRoof(depth-1,translate+ROADWIDTH);
	}
}
gluggModel makeRoof(){
	float translate = BASEYSCALE*BASEHEIGHT+TILEYSCALE*TILEHEIGHT+WALLHEIGHT*WALLYSCALE+CEILYSCALE*CEILHEIGHT;
	foo(translate, 1,-19.5);
	setVerticalRoof(STARTDEPTH, 0);
	return gluggBuildModel(0);
}

void setHorizontalWindow(int depth, float translate){
	if(depth != 0){
		float newScale = scaleArray[globalCounter]*0.9f;
		float numberOfStories = storiesArray[globalCounter];
		int doorPos = doorPosArray[globalCounter];
		globalCounter++;
		gluggPushMatrix();
		gluggTranslate(translate,0,0);
		gluggScale(newScale+0.001,1,newScale+0.001);
		gluggRotate(M_PI_2,0,0,1);

		for (size_t i = 0; i < numberOfStories; i++){
			gluggPushMatrix();
			gluggTranslate(WALLHEIGHT*i+CEILYSCALE*CEILHEIGHT*i,0,0);
			for (size_t j = 0; j < 4; j++){
				if (i == 0 && j == doorPos){
					gluggPushMatrix();
					gluggRotate(M_PI_2*j,1,0,0);
					gluggTranslate(0,1,0);
					gluggScale(0.3,1,0.3);
						if ((int)randomiser(0,2) == 1){
							gluggPushMatrix();
							gluggTranslate(0,0,2);
							gluggRectangle(1,1);
							gluggPopMatrix();
						}
						if ((int)randomiser(0,2) == 1){
							gluggPushMatrix();
							gluggTranslate(0,0,-2);
							gluggRectangle(1,1);
							gluggPopMatrix();
						}
					gluggPopMatrix();
				}
				else{
					gluggPushMatrix();
					gluggRotate(M_PI_2*j,1,0,0);
					gluggTranslate(0,1,0);
					gluggScale(0.3,1,0.3);

					gluggPushMatrix();
					gluggTranslate(0,0,0);
					gluggRectangle(1,1);
					gluggPopMatrix();

					if ((int)randomiser(0,2) == 1){
						gluggPushMatrix();
						gluggTranslate(0,0,2);
						gluggRectangle(1,1);
						gluggPopMatrix();
					}

					if ((int)randomiser(0,2) == 1){
						gluggPushMatrix();
						gluggTranslate(0,0,-2);
						gluggRectangle(1,1);
						gluggPopMatrix();
					}
					gluggPopMatrix();
				}
			}
			gluggPopMatrix();
		}
		gluggPopMatrix();
		setHorizontalWindow(depth-1, translate+ROADWIDTH);
	}
}
void setVerticalWindow(int depth, float translate){
	if(depth != 0){
		gluggPushMatrix();
		gluggTranslate(0.0,0.0,translate);
		setHorizontalWindow(STARTDEPTH, 0);
		gluggPopMatrix();
		setVerticalWindow(depth-1,translate+ROADWIDTH);
	}
}
gluggModel makeWindows(){
	float translate = BASEYSCALE*BASEHEIGHT+TILEYSCALE*TILEHEIGHT+WALLYSCALE*WALLHEIGHT/2;
	foo(translate, 1,-19.5);
    setVerticalWindow(STARTDEPTH,0);
	return gluggBuildModel(0);
}

void setHorizontalCeil(int depth, float translate){
	if(depth != 0){
		float newScale = scaleArray[globalCounter]*0.9f;
		float numberOfStories = storiesArray[globalCounter];
		globalCounter++;
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
	float translate = BASEYSCALE*BASEHEIGHT+TILEYSCALE*TILEHEIGHT+WALLHEIGHT*WALLYSCALE+CEILYSCALE*CEILHEIGHT/2;
	foo(translate, CEILYSCALE,-19.5);
    setVerticalCeil(STARTDEPTH,0);
	return gluggBuildModel(0);
}

void makeWall(int depth, float translate){

	if(depth != 0){
		float newScale = scaleArray[globalCounter]*0.9f;
    	// printf("Scale: %f \n", scaleArray[globalCounter]);
		int numberOfStories = randomiser(1,MAXSTORIES);
		// printf("Randomised Number %d\n", numberOfStories );
		storiesArray[globalCounter] = numberOfStories;
		globalCounter++;
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
			gluggRectangle(WALLHEIGHT,2);
			gluggPopMatrix();
			//east
			gluggPushMatrix();
			gluggRotate(M_PI,1,0,0);
			gluggTranslate(0,1,0);
			gluggRectangle(WALLHEIGHT,2);
			gluggPopMatrix();
			//north
			gluggRotate(M_PI_2,1,0,0);
			gluggPushMatrix();
			gluggTranslate(0,1,0);
			gluggRectangle(WALLHEIGHT,2);
			gluggPopMatrix();
			//South
			gluggPushMatrix();
			gluggRotate(M_PI,1,0,0);
			gluggTranslate(0,1,0);
			gluggRectangle(WALLHEIGHT,2);
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
	float translate = BASEYSCALE*BASEHEIGHT+TILEYSCALE*TILEHEIGHT+WALLYSCALE*WALLHEIGHT/2;
	foo(translate,WALLYSCALE,-19.5);
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
	float translate = TILEYSCALE*TILEHEIGHT+BASEYSCALE*BASEHEIGHT/2;
	foo(translate, BASEYSCALE,-19.5);
    makeBasesNetwork(STARTDEPTH,0);
	return gluggBuildModel(0);
}

//SCRIPT FOR TILES
void makeBlockRow(int depth, float translate){

	if(depth != 0){
		float newScale = randomiser(0.5,1.0);
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
	float translate = TILEYSCALE*TILEHEIGHT/2;
	foo(translate, TILEYSCALE,-19.5);
	makeNetwork(STARTDEPTH,0);
	return gluggBuildModel(0);
}

gluggModel makeRoads(){
	gluggBegin(GLUGG_TRIANGLES);
	gluggPushMatrix();
	gluggTranslate(0,0,-17.5);
	for(int i = 0; i < 10;i++){
		gluggPushMatrix();
		gluggTranslate(-1,-0.4,ROADWIDTH*i);
		gluggScale(40,1,1.7);		
		gluggCube(1);
		gluggPopMatrix();		
	}
	gluggPopMatrix();
	return gluggBuildModel(0);
}

gluggModel makeSidewalks(){
	gluggBegin(GLUGG_TRIANGLES);
	gluggPushMatrix();
	gluggTranslate(0,0,-17.5);
	for(int i = 0; i < 10;i++){		
		gluggPushMatrix();
		gluggTranslate(-1,-0.2,ROADWIDTH*i+1.6);
		gluggScale(40,1,1.5);		
		gluggCube(1);
		gluggPopMatrix();
		
		gluggPushMatrix();
		gluggTranslate(-1,-0.2,ROADWIDTH*i-1.6);
		gluggScale(40,1,1.5);		
		gluggCube(1);
		gluggPopMatrix();		
	}
	gluggPopMatrix();
	return gluggBuildModel(0);
}

void foo(float translate, float scale, float start){
	gluggSetPositionName("inPosition");
	gluggSetNormalName("inNormal");
	gluggSetTexCoordName("inTexCoord");
	gluggSetColorName("inColor");
	gluggBegin(GLUGG_TRIANGLES);
	gluggTranslate(start,translate,start);
	gluggScale(1,scale,1);
	globalCounter = 0;
}
#endif
// #endif