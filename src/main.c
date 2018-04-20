#include "glutcallbacks.h"
#include "modelloader.h"

void set_callbacks()
{
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key_handler);
	glutKeyboardUpFunc(key_up_handler);
	glutMouseFunc(mouse_handler);
	glutMotionFunc(motion_handler);
	glutIdleFunc(idle);
	glutSpecialUpFunc(key_special_handler);
}

void promptStartupOptions() 
{
	printf("Valassz: \n 1 - Alacsony textura felbontas \n 2 - Magas textura felbontas\n");
	scanf("%d", &graphicsMode);
	if (graphicsMode != 1 && graphicsMode != 2) {
		graphicsMode = 1;
		printf("Ervenytelen opcio, folytatas alacsony felbontassal");
	}
}

int main(int argc, char* argv[])
{
	promptStartupOptions();
	glutInit(&argc, argv);
	parseModels();
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	int window = glutCreateWindow("Grafika beadando");
	glutSetWindow(window);
    initialize();
    init_camera(&camera);
	set_callbacks();
    glutMainLoop();

    return 0;
}

