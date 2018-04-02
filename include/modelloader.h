#ifndef MODELLOADER_H
#define MODELLOADER_H 
#include "glutcallbacks.h"
#include <SOIL/SOIL.h>

typedef GLubyte Pixel[3]; //r,g,b

/**
*Parse models and textures from txt file
*/
void readModelDataFromFile();

/**
*Initialize textres
*/
void initialize_texture();
#endif /*MODELLOADER_H*/
