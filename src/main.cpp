// C++ version 2022.
// Adapted to lastest GLUGG.

#define MAIN
#include "MicroGlut.h"
#include "GL_utilities.h"
#include "VectorUtils4.h"
#include "LittleOBJLoaderX.h"
#include "LoadTGA.h"
#include "gluggShapes.h"
#include "glugg.h"
#include "makeCity.h"
#include <math.h>


#define PI 3.14159265

// uses framework OpenGL
// uses framework Cocoa

void MakeCylinderAlt(int aSlices, float height, float topwidth, float bottomwidth){
	gluggMode(GLUGG_TRIANGLE_STRIP);
	vec3 top = SetVector(0,height,0);
	vec3 center = SetVector(0,0,0);
	vec3 bn = SetVector(0,-1,0); // Bottom normal
	vec3 tn = SetVector(0,1,0); // Top normal

	for (float a = 0.0; a < 2.0*M_PI+0.0001; a += 2.0*M_PI / aSlices)
	{
		float a1 = a;

		vec3 p1 = SetVector(topwidth * cos(a1), height, topwidth * sin(a1));
		vec3 p2 = SetVector(bottomwidth * cos(a1), 0, bottomwidth * sin(a1));
		vec3 pn = SetVector(cos(a1), 0, sin(a1));

		// Done making points and normals. Now create polygons!
		gluggNormalv(pn);
	    gluggTexCoord(height, a1/M_PI);
	    gluggVertexv(p2);
	    gluggTexCoord(0, a1/M_PI);
	    gluggVertexv(p1);
	}

	// Then walk around the top and bottom with fans
	gluggMode(GLUGG_TRIANGLE_FAN);
	gluggNormalv(bn);
	gluggVertexv(center);
	// Walk around edge
	for (float a = 0.0; a <= 2.0*M_PI+0.001; a += 2.0*M_PI / aSlices)
	{
		vec3 p = vec3(bottomwidth * cos(a), 0, bottomwidth * sin(a));
	    gluggVertexv(p);
	}
	// Walk around edge
	gluggMode(GLUGG_TRIANGLE_FAN); // Reset to new fan
	gluggNormalv(tn);
	gluggVertexv(top);
	for (float a = 2.0*M_PI; a >= -0.001; a -= 2.0*M_PI / aSlices)
	{
		vec3 p = vec3(topwidth * cos(a), height, topwidth * sin(a));
	    gluggVertexv(p);
	}
}


mat4 projectionMatrix;
Model *floormodel;
GLuint grasstex, barktex, asfalttex, concretetex, brickstex;

// Reference to shader programs
GLuint phongShader, texShader;

// Floor quad
GLfloat vertices2[] = {	-20.5,0.0,-20.5,
						20.5,0.0,-20.5,
						20.5,0.0,20.5,
						-20.5,0.0,20.5};
GLfloat normals2[] = {	0,1.0,0,
						0,1.0,0,
						0,1.0,0,
						0,1.0,0};
GLfloat texcoord2[] = {	50.0f, 50.0f,
						0.0f, 50.0f,
						0.0f, 0.0f,
						50.0f, 0.0f};
GLuint indices2[] = {	0,3,2, 0,2,1};




void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

	// Set the clipping volume
	projectionMatrix = perspective(45,1.0f*w/h,1,1000);
	glUseProgram(phongShader);
	glUniformMatrix4fv(glGetUniformLocation(phongShader, "projectionMatrix"), 1, GL_TRUE, projectionMatrix.m);
	glUseProgram(texShader);
	glUniformMatrix4fv(glGetUniformLocation(texShader, "projectionMatrix"), 1, GL_TRUE, projectionMatrix.m);
}

void init(void)
{
	// GL inits
	glClearColor(0.4,0.6,0.8,0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	printError("GL inits");

	projectionMatrix = frustum(-0.1, 0.1, -0.1, 0.1, 0.2, 300.0);

	// Load and compile shader
	phongShader = loadShaders("phong.vert", "phong.frag");
	texShader = loadShaders("textured.vert", "textured.frag");
	printError("init shader");

	// Upload geometry to the GPU:
	//floormodel = LoadDataToModel((vec3 *)vertices2, (vec3 *)normals2, (vec2 *)texcoord2, NULL,
	//		indices2, 4, 6);

// Important! The shader we upload to must be active!
	glUseProgram(phongShader);
	glUniformMatrix4fv(glGetUniformLocation(phongShader, "projectionMatrix"), 1, GL_TRUE, projectionMatrix.m);
	glUseProgram(texShader);
	glUniformMatrix4fv(glGetUniformLocation(texShader, "projectionMatrix"), 1, GL_TRUE, projectionMatrix.m);

	glUniform1i(glGetUniformLocation(texShader, "tex"), 0); // Texture unit 0

	LoadTGATextureSimple("grass.tga", &grasstex);
	glBindTexture(GL_TEXTURE_2D, grasstex);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,	GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,	GL_REPEAT);

	LoadTGATextureSimple("bark2.tga", &barktex);

	tiles = makeTiles();
	bases = makeBases();
	story = makeStory();
	ceiling = makeCeilings();
	door = makeDoor();
	windows = makeWindows();
	roof = makeRoof();
	tree = MakeTree();
	sidewalks = makeSidewalks();
	roads = makeRoads();
	printError("init arrays");
}

GLfloat a = 0.0;
vec3 campos = vec3(0, 1.5, 10);
vec3 forward = vec3(0, 0, -4);
vec3 up = vec3(0, 1, 0);

void display(void)
{
	printError("pre display");

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 worldToView, m; // m1, m2, m, tr, scale;

	if (glutKeyIsDown('a'))
		forward = mat3(Ry(0.05))* forward;
	if (glutKeyIsDown('d'))
		forward = mat3(Ry(-0.05)) * forward;
	if (glutKeyIsDown('w'))
		campos = campos + forward * 0.1;
	if (glutKeyIsDown('s'))
		campos = campos - forward * 0.1;
	if (glutKeyIsDown('q'))
	{
		vec3 side = cross(forward, vec3(0,1,0));
		campos = campos - side * 0.05;
	}
	if (glutKeyIsDown('e'))
	{
		vec3 side = cross(forward, vec3(0,1,0));
		campos = campos + side * 0.05;
	}

	// Move up/down
	if (glutKeyIsDown('z'))
		campos = campos + vec3(0,1,0) * 0.01;
	if (glutKeyIsDown('c'))
		campos = campos - vec3(0,1,0) * 0.01;

	// NOTE: Looking up and down is done by making a side vector and rotation around arbitrary axis!
	if (glutKeyIsDown('+'))
	{
		vec3 side = cross(forward, vec3(0,1,0));
		mat4 m = ArbRotate(side, 0.05);
		forward = mat3(m) * forward;
	}
	if (glutKeyIsDown('-'))
	{
		vec3 side = cross(forward, vec3(0,1,0));
		mat4 m = ArbRotate(side, -0.05);
		forward = m * forward;
	}

	worldToView = lookAtv(campos, campos + forward, up);

	a += 0.1;

	// glBindTexture(GL_TEXTURE_2D, grasstex);
	// Floor
	// glUseProgram(texShader);
	// m = worldToView;
	// glUniformMatrix4fv(glGetUniformLocation(texShader, "modelviewMatrix"), 1, GL_TRUE, m.m);
	// DrawModel(floormodel, texShader, "inPosition", "inNormal", "inTexCoord");

	glBindTexture(GL_TEXTURE_2D, barktex);
	glUseProgram(texShader);
    m = worldToView * T(0, 0, 0);
    glUniformMatrix4fv(glGetUniformLocation(texShader, "modelviewMatrix"), 1, GL_TRUE, m.m);
	gluggDrawModel(tree, texShader);

	//Draw the tree, as defined on MakeBases
	//glBindTexture(GL_TEXTURE_2D, barktex);
	glUseProgram(phongShader);
    m = worldToView * T(0, 0, 0);
    glUniformMatrix4fv(glGetUniformLocation(phongShader, "modelviewMatrix"), 1, GL_TRUE, m.m);
	// Set red color in the Phong shader

	glUniform3f(glGetUniformLocation(phongShader, "inColor"), 0.5f, 0.5f, 0.5f); 
	gluggDrawModel(tiles, phongShader);

	glUniform3f(glGetUniformLocation(phongShader, "inColor"), 0.1f, 0.1f, 0.1f); 
	gluggDrawModel(bases, phongShader);

	glUniform3f(glGetUniformLocation(phongShader, "inColor"), 0.71f, 0.41f, 0.32f); 
	gluggDrawModel(story, phongShader);

	glUniform3f(glGetUniformLocation(phongShader, "inColor"), 0.1f, 0.1f, 0.1f);
	gluggDrawModel(ceiling, phongShader);

	glUniform3f(glGetUniformLocation(phongShader, "inColor"), .2,.3,.5);
	gluggDrawModel(windows, phongShader);

	glUniform3f(glGetUniformLocation(phongShader, "inColor"), 0.6f, 0.3f, 0.1f);
	gluggDrawModel(roof, phongShader);

	glUniform3f(glGetUniformLocation(phongShader, "inColor"), 0.4f, 0.3f, 0.3f);
	gluggDrawModel(door, phongShader);

	glUniform3f(glGetUniformLocation(phongShader, "inColor"), 0.1f, 0.3f, 0.1f);
	gluggDrawModel(ground, phongShader);
	// glUniform3f(glGetUniformLocation(phongShader, "inColor"), 0.4f, 0.3f, 0.3f);
	// gluggDrawModel(tree, phongShader);

	glUniform3f(glGetUniformLocation(phongShader, "inColor"), 0.3f, 0.3f, 0.3f);
	gluggDrawModel(sidewalks, phongShader);

	glUniform3f(glGetUniformLocation(phongShader, "inColor"), 0.1f, 0.1f, 0.1f);
	gluggDrawModel(roads, phongShader);

	printError("display");

	glutSwapBuffers();
}

void keys(unsigned char key, int x, int y)
{
	switch (key)
	{
		case ' ':
			forward.y = 0;
			forward = normalize(forward) * 4.0;
			break;
	}
}

int main(int argc, char *argv[])
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	glutInit(&argc, argv);
	glutInitContextVersion(3, 2);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,360);
	glutCreateWindow ("Procedueral City Block");
	glutRepeatingTimer(20);
	glutDisplayFunc(display);
	glutKeyboardFunc(keys);
	glutReshapeFunc(reshape);
	init ();
	glutMainLoop();
}