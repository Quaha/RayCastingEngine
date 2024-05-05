#include "libs.hpp"

#include "Camera.hpp"

void Camera::moveForward() {
	camera_position.x += USER_MOVE_SPEED * cos(angle1);
	camera_position.y += USER_MOVE_SPEED * sin(angle1);
}

void Camera::moveBack() {
	camera_position.x -= USER_MOVE_SPEED * cos(angle1);
	camera_position.y -= USER_MOVE_SPEED * sin(angle1);
}

void Camera::moveLeft() {
	camera_position.x += USER_MOVE_SPEED * sin(angle1);
	camera_position.y -= USER_MOVE_SPEED * cos(angle1);
}

void Camera::moveRight() {
	camera_position.x -= USER_MOVE_SPEED * sin(angle1);
	camera_position.y += USER_MOVE_SPEED * cos(angle1);
}

void Camera::moveUp() {
	camera_position.z -= USER_MOVE_SPEED;
}

void Camera::moveDown() {
	camera_position.z += USER_MOVE_SPEED;
}

void Camera::rotateLeft() {
	angle1 -= USER_ROTATE_SPEED;
	while (angle1 < 0) {
		angle1 += 2 * PI;
	}
}

void Camera::rotateRight() {
	angle1 += USER_ROTATE_SPEED;
	while (angle1 >= 2 * PI) {
		angle1 -= 2 * PI;
	}
}

void Camera::rotateUp() {
	angle2 -= USER_ROTATE_SPEED;
	if (angle2 < -PI / 2) {
		angle2 = -PI / 2;
	}
}
void Camera::rotateDown() {
	angle2 += USER_ROTATE_SPEED;
	if (angle2 > PI / 2) {
		angle2 = PI / 2;
	}
}

Point Camera::getPosition() const {
	return camera_position;
}

float Camera::getAngle1() const {
	return angle1;
}

float Camera::getAngle2() const {
	return angle2;
}

void Camera::getRays(const std::vector<Polyhedron>& objects, Segment rays[REAL_HEIGHT][REAL_WIDTH]) const{

	float RFOV_V = degreesToRadians(VERTICAL_FOV);
	float RFOV_H = degreesToRadians(HORIZONTAL_FOV);
	float RSTEP_V = degreesToRadians(VERTICAL_FOV / REAL_HEIGHT);
	float RSTEP_H = degreesToRadians(HORIZONTAL_FOV / REAL_WIDTH );

	Segment FILLER = { getPosition(), getPosition() };
	for (int i = 0; i < REAL_HEIGHT; i++) {
		for (int j = 0; j < REAL_WIDTH; j++) {

			float a = angle1 - RFOV_H / 2 + RSTEP_H * j;
			float b = angle2 - RFOV_V / 2 + RSTEP_V * i;

			rays[i][j] = FILLER;

			rays[i][j].point2.x += RAYS_LENGTH * cos(a) * cos(b);
			rays[i][j].point2.y += RAYS_LENGTH * sin(a) * cos(b);
			rays[i][j].point2.z += RAYS_LENGTH * sin(b);
		}
	}

	for (int k = 0; k < objects.size(); k++) {
		for (int d = 0; d < objects[k].edges.size(); d++) {
			objects[k].edges[d].updateRays(rays);
		}
	}
}