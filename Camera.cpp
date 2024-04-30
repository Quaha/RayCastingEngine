#include "libs.hpp"

#include "Camera.hpp"

void Camera::moveForward() {
	camera_position.x += USER_MOVE_SPEED * cos(angle1) * cos(angle2);
	camera_position.y += USER_MOVE_SPEED * sin(angle1) * cos(angle2);
	camera_position.z += USER_MOVE_SPEED * sin(angle2);
}

void Camera::moveBack() {
	camera_position.x -= USER_MOVE_SPEED * cos(angle1) * cos(angle2);
	camera_position.y -= USER_MOVE_SPEED * sin(angle1) * cos(angle2);
	camera_position.z -= USER_MOVE_SPEED * sin(angle2);
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

double Camera::getAngle1() const {
	return angle1;
}

double Camera::getAngle2() const {
	return angle2;
}

std::vector<std::vector<Segment>> Camera::getRays(const std::vector<Polyhedron>& objects) {
	double RFOV_V = degreesToRadians(VERTICAL_FOV);
	double RFOV_H = degreesToRadians(HORIZONTAL_FOV);
	double RSTEP_V = degreesToRadians((double)VERTICAL_FOV / REAL_HEIGHT);
	double RSTEP_H = degreesToRadians((double)HORIZONTAL_FOV / REAL_WIDTH );
	Segment FILLER = { getPosition(), getPosition() };
	std::vector<std::vector<Segment>> rays(REAL_WIDTH, std::vector<Segment>(REAL_HEIGHT, FILLER));
	for (int i = 0; i < REAL_WIDTH; i++) {
		for (int j = 0; j < REAL_HEIGHT; j++) {
			double a = angle1 - RFOV_H / 2 + RSTEP_H * i;
			double b = angle2 - RFOV_V / 2 + RSTEP_V * j;
			rays[i][j].point2.x += RAYS_LENGTH * cos(a) * cos(b);
			rays[i][j].point2.y += RAYS_LENGTH * sin(a) * cos(b);
			rays[i][j].point2.z += RAYS_LENGTH * sin(b);
		}
	}

	for (int i = 0; i < rays.size(); i++) {
		for (int j = 0; j < rays[i].size(); j++) {
			for (int k = 0; k < objects.size(); k++) {
				rays[i][j].updateByPolyhedron(objects[k]);
			}
		}
	}
	return rays;
}