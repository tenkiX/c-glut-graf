#include "camera.h"
#include "utils.h"
#include <GL/glut.h>
#include <math.h>
#include "glutcallbacks.h"


void init_camera(struct Camera* camera)
{
	camera->position.x = 0;
	camera->position.y = 0;
	camera->position.z = 1;

	camera->pose.x = 0;
	camera->pose.y = 0;
	camera->pose.z = 0;
}

void set_view_point(const struct Camera* camera)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(-(camera->pose.x + 90), 1.0, 0, 0);
	glRotatef(-(camera->pose.z - 90), 0, 0, 1.0);
	glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(struct Camera* camera, double horizontal, double vertical)
{
	camera->pose.z += horizontal;
	camera->pose.x += vertical;

	if (camera->pose.z < 0) {
		camera->pose.z += 360.0;
	}

	if (camera->pose.z > 360.0) {
		camera->pose.z -= 360.0;
	}

	if (camera->pose.x < 0) {
		camera->pose.x += 360.0;
	}

	if (camera->pose.x > 360.0) {
		camera->pose.x -= 360.0;
	}
}

void move_camera_forward(struct Camera* camera, double distance)
{
	double angle = degree_to_radian(camera->pose.z);

	camera->position.x += cos(angle) * distance;
	camera->position.y += sin(angle) * distance;
}

void move_camera_backward(struct Camera* camera, double distance)
{
	double angle = degree_to_radian(camera->pose.z);

	camera->position.x -= cos(angle) * distance;
	camera->position.y -= sin(angle) * distance;
}

void step_camera_left(struct Camera* camera, double distance)
{
	double angle = degree_to_radian(camera->pose.z + 90.0);

	camera->position.x += cos(angle) * distance;
	camera->position.y += sin(angle) * distance;
}

void step_camera_right(struct Camera* camera, double distance)
{
	double angle = degree_to_radian(camera->pose.z - 90.0);

	camera->position.x += cos(angle) * distance;
	camera->position.y += sin(angle) * distance;
}

void update_camera_position(struct Camera* camera, double elapsed_time)
{
	double distance;
	distance = elapsed_time * CAMERA_SPEED;
	if (action.move_forward == TRUE) {
		move_camera_forward(camera, distance);
	}

	if (action.move_backward == TRUE) {
		move_camera_backward(camera, distance);
	}

	if (action.step_left == TRUE) {
		step_camera_left(camera, distance);
	}

	if (action.step_right == TRUE) {
		step_camera_right(camera, distance);
	}
}