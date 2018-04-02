#include "modelloader.h"

void readModelDataFromFile() {
	int i = 0;
	int j = 0;
	FILE *file = fopen("Models/ModelDataBase.txt", "r");
	if (file != NULL)
	{
		char line[128];
		while (fgets(line, sizeof line, file) != NULL)
		{
			//newline jel leszedése a sor vegerol
			size_t len = strlen(line);
			if (len > 0 && line[len - 1] == '\n') {
				line[--len] = '\0';
			}
			//minden második sor texturanev
			if ((i % 2) == 0) {
				modelData[j].objFileName = malloc(strlen(line) + 1);
				strcpy(modelData[j].objFileName, line);
				modelData[j].texID = j;
			}
			else {
				modelData[j].textureFileName = malloc(strlen(line) + 1);
				strcpy(modelData[j].textureFileName, line);
				j++;
			}
			i++;
		}
		fclose(file);
	}
	else
	{
		printf("I/O error: ellenorizd a Models/ModelDataBase.txt fajl elerhetoseget");
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



