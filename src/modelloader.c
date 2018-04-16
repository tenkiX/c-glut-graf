#include "modelloader.h"

void parseModels() {
	int i = 0;
	char modelnames[NUMBER_OF_MODELS][32] = { "Models/particle.obj", "Models/aderjanos.obj", "Models/szoba.obj", "Models/balta.obj", "Models/menu.obj" };
	char texturenames[NUMBER_OF_MODELS][32] = { "Textures/particle.png", "Textures/aderjanos.png", "Textures/szoba.png", "Textures/balta.png", "Textures/menu.png" };

	for (i = 0; i < NUMBER_OF_MODELS; i++) {
		modelData[i].objFileName = malloc(strlen(modelnames[i]));
		strcpy(modelData[i].objFileName, modelnames[i]);
		modelData[i].texID = i;
		modelData[i].textureFileName = malloc(strlen(texturenames[i]));
		strcpy(modelData[i].textureFileName, texturenames[i]);
	}
	for (i = 0; i < NUMBER_OF_MODELS; i++) {
		load_model(modelData[i].objFileName, &model[i]);
	}
}


void initialize_texture() {
	int i;
	for (i = 0; i < NUMBER_OF_MODELS; i++) {
		int width;
		int height;
		unsigned char* image = SOIL_load_image(modelData[i].textureFileName, &width, &height, 0, SOIL_LOAD_RGB);

		glBindTexture(GL_TEXTURE_2D, modelData[i].texID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, (Pixel*)image);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

}



