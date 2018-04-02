#include "scene.h"
#include "glutcallbacks.h"
#include "camera.h"
#define MAX_PARTICLES 15
#define PARTICLES_LIFE 10 
#define PARTICLES_SPEED 1.0f

struct particle particles[MAX_PARTICLES];
GLfloat material1[] = { 1, 0.2f, 0.2f, 1 };
GLfloat material2[] = { 0.8f, 0.8f, 1, 1 };
GLfloat full_mat[] = { 1, 1, 1, 1 };
GLfloat no_mat[] = { 0, 0, 0, 0 };
GLfloat material_shininess[] = { 100.0 };

float currentLightStrength = 0.8f;
void set_lightings(float value)
{
	if (value == -1) currentLightStrength = 0.8f;
	else {
		if (((currentLightStrength + value) <= 1) && ((currentLightStrength + value) >= 0)) 
		currentLightStrength += value;
	}
	GLfloat light_position[] = { 0.0, 0.0, 5, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat light_ambient[] = { currentLightStrength, currentLightStrength, currentLightStrength, 0 };
	GLfloat light_diffuse[] = { currentLightStrength, currentLightStrength, currentLightStrength, 0 };
	GLfloat light_specular[] = { currentLightStrength, currentLightStrength, currentLightStrength, 0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glClearColor(currentLightStrength, currentLightStrength, currentLightStrength + 0.2f, 1.0);
}

void initialize()
{
	toggleHelp = FALSE;
	toggleAttack = FALSE;
	attackTimer = 0;
	int i;
	srand(time(NULL));
	/*init particlesystem with random coordinates*/
	float startZ = 0;
	for (i = 0; i < MAX_PARTICLES; i++) {
		particles[i].x = rand() % 10 - 5;
		particles[i].y = rand() % 10 - 5;
		particles[i].z = rand() % 10 + startZ;
	}
	set_lightings(-1);

	action.move_forward = FALSE;
	action.move_backward = FALSE;
	action.step_left = FALSE;
	action.step_right = FALSE;

	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
	glClearColor(1, 1, 1, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
	);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearDepth(1.0);
	glEnable(GL_TEXTURE_2D);
	initialize_texture();
	gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 1000.0);
	glMatrixMode(GL_PROJECTION);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

}

void glprint(int x, int y, char *st)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.0, 1.0, 0.0);

	int l, i;

	l = strlen(st);
	glRasterPos2i(x, y);
	for (i = 0; i < l; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void draw_scene(double elapsed_time)
{
	/*room*/
	glBindTexture(GL_TEXTURE_2D, modelData[2].texID);
	glPushMatrix();
	glScalef(1.0f, 1.0f, 1.0f);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(90, 1, 0, 0);
	draw_model(&model[2]);
	glPopMatrix();

	/*Mr Janos Ader*/
	glBindTexture(GL_TEXTURE_2D, modelData[1].texID);
	glPushMatrix();
	glScalef(1.0f, 1.0f, 1.0f);
	glTranslatef(-2.0f, 2.0f, 0.0f);
	glRotatef(90, 1, 0, 0);
	draw_model(&model[1]);
	glTranslatef(2.0f, -2.0f, 0.0f);
	glPopMatrix();

	/*axe*/
	glBindTexture(GL_TEXTURE_2D, modelData[3].texID);
	glPushMatrix();
	glTranslatef(camera.position.x, camera.position.y, camera.position.z);
	glRotatef(90, 1, 0, 0);
	glRotatef(camera.pose.z + 105, 0, 1, 0);
	glRotatef(-camera.pose.x, 1, 0, 0);
	glTranslatef(0.05, -.5f, -0.05);
	if (toggleAttack == TRUE) {
		attackTimer += 4 * elapsed_time;
		if (attackTimer > 1) {
			toggleAttack = FALSE;
		}
	}
	else {
		if (attackTimer > 0) attackTimer -= 4 * elapsed_time;
	}
	glRotatef(attackTimer * 45, 1, 0.2, 0);
	draw_model(&model[3]);
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, full_mat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);

	/*particles*/
	glBindTexture(GL_TEXTURE_2D, modelData[0].texID);
	glPushMatrix();
	glScalef(0.35f, 0.35f, 0.35f);
	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	int i;
	/*we want every second particle to have different colour*/ 
	for (i = 0; i < MAX_PARTICLES; i++) {
		if (i % 2 == 0) {
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material1);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material1);
		}
		else {
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material2);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material2);
		}
		particles[i].y += PARTICLES_SPEED * elapsed_time; 
		if (particles[i].y>PARTICLES_LIFE) { particles[i].y = 0; }
		glTranslatef(particles[i].x, particles[i].y, particles[i].z);
		draw_model(&model[0]);
		glTranslatef(-particles[i].x, -particles[i].y, -particles[i].z);
	}

	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, full_mat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, full_mat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_mat);

	/*help text*/
	if (toggleHelp == TRUE)
	{
		glprint(20, 20, "Space utes W elore S hatra D jobbra A balra +- fenyero F1 segitseg");
	}

}