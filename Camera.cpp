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
	while (angle1 < 0) {
		angle1 += 2 * PI;
	}
}
void Camera::rotateDown() {
	angle2 += USER_ROTATE_SPEED;
	while (angle1 >= 2 * PI) {
		angle1 -= 2 * PI;
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
	double RFOV = degreesToRadians(FOV);
	double RSTEP = degreesToRadians(RAYS_STEP);
	Segment FILLER;
	FILLER.point1 = getPosition();
	FILLER.point2 = getPosition();
	std::vector<std::vector<Segment>> rays((int)(RFOV / RSTEP) + 1, std::vector<Segment>((int)(RFOV / RSTEP) + 1, FILLER));
	int i = 0, j = 0;
	for (double a = angle1 - RFOV/2; a <= angle1 + RFOV/2; a += RSTEP, i++) {
		j = 0;
		for (double b = angle2 - RFOV / 2; b <= angle2 + RFOV / 2; b += RSTEP, j++) {
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