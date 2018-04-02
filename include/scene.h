#ifndef SCENE_H
#define SCENE_H
#define NUMBER_OF_MODELS 4
#include "camera.h"
#include <GL/glut.h>
#include <time.h>
#include "utils.h"

float attackTimer;
int toggleAttack;
int toggleHelp;

struct Model model[NUMBER_OF_MODELS];

struct ModelData {
	char* textureFileName;
	char* objFileName;
	int texID;
} modelData[NUMBER_OF_MODELS];

struct particle
{
	GLfloat x, y, z;
};

/* Initializes key actions, camera and light setup */
void init_scene();

/* Prints text to screen space coordinates */
void glprint(int x, int y, char *st);

/* Sets the power of light by the given value */
void set_lightings(float lightPower);

/* Draws the scene: binds textures, places models */
void draw_scene(double elapsed_time);

#endif /* SCENE_H */
