#include "glutcallbacks.h"

void display()
{
	double elapsed_time;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	elapsed_time = calc_elapsed_time();
	update_camera_position(&camera, elapsed_time);
	set_view_point(&camera);

	draw_scene(elapsed_time);

	glutPostRedisplay();
	glutSwapBuffers();
}

void key_handler(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		action.move_forward = TRUE;
		break;
	case 's':
		action.move_backward = TRUE;
		break;
	case 'a':
		action.step_left = TRUE;
		break;
	case 'd':
		action.step_right = TRUE;
		break;
	}
	glutPostRedisplay();
}

void key_special_handler(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		if (toggleHelp == TRUE) toggleHelp = FALSE; else
			toggleHelp = TRUE;
		break;
	}
}

void key_up_handler(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		action.move_forward = FALSE;
		break;
	case 's':
		action.move_backward = FALSE;
		break;
	case 'a':
		action.step_left = FALSE;
		break;
	case 'd':
		action.step_right = FALSE;
		break;
	case '+':
		set_lightings(0.1f);
		break;
	case '-':
		set_lightings(-0.1f);
		break;
	case ' ':
		if (toggleAttack == FALSE)
			toggleAttack = TRUE;
		break;
	}
	glutPostRedisplay();
}

void mouse_handler(int button, int state, int x, int y)
{
	mouse_x = x;
	mouse_y = y;
}

void motion_handler(int x, int y)
{
	double horizontal, vertical;
	horizontal = mouse_x - x;
	vertical = mouse_y - y;
	rotate_camera(&camera, horizontal, vertical);
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}

void idle()
{
	glutPostRedisplay();
}


void reshape(GLsizei width, GLsizei height)
{
	int x, y, w, h;
	double ratio;

	ratio = (double)width / height;
	if (ratio > VIEWPORT_RATIO) {
		w = (int)((double)height * VIEWPORT_RATIO);
		h = height;
		x = (width - w) / 2;
		y = 0;
	}
	else {
		w = width;
		h = (int)((double)width / VIEWPORT_RATIO);
		x = 0;
		y = (height - h) / 2;
	}
	glViewport(x, y, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.01, 10000.0);
}




