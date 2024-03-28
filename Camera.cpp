#include "programData.hpp"

#include "Camera.hpp"

/*
 ~-------->
 |        X
 |  
 |
 |
 V Y

*/

void Camera::moveForward() {
	camera_position.x += USER_MOVE_SPEED * sin(angle);
	camera_position.y += USER_MOVE_SPEED * cos(angle);
}

void Camera::moveBack() {
	camera_position.x -= USER_MOVE_SPEED * sin(angle);
	camera_position.y -= USER_MOVE_SPEED * cos(angle);
}

void Camera::moveLeft() {
	camera_position.x += USER_MOVE_SPEED * sin(angle + PI / 2);
	camera_position.y += USER_MOVE_SPEED * cos(angle + PI / 2);
}

void Camera::moveRight() {
	camera_position.x -= USER_MOVE_SPEED * sin(angle + PI / 2);
	camera_position.y -= USER_MOVE_SPEED * cos(angle + PI / 2);
}

void Camera::rotateLeft() {
	angle += USER_ROTATE_SPEED;
	while (angle >= 2 * PI) {
		angle -= 2 * PI;
	}
}

void Camera::rotateRight() {
	angle -= USER_ROTATE_SPEED;
	while (angle < 0) {
		angle += 2 * PI;
	}
}

Coordinates Camera::getPosition() const {
	return camera_position;
}

long double Camera::getAngle() const {
	return angle;
}

std::vector<Segment> Camera::getRays(const std::vector<Polygon>& objects) const {
	std::vector<Segment> result(0);
	for (long double i = angle - degreesToRadians(FOV / 2); i <= angle + degreesToRadians(FOV / 2); i += degreesToRadians(RAYS_STEP)) {
		Segment temp;
		temp.point1 = this->getPosition();
		temp.point2 = { this->getPosition().x + RAYS_LENGTH * sin(i), this->getPosition().y + RAYS_LENGTH * cos(i) };
		result.push_back(temp);
	}
	for (int i = 0; i < result.size(); i++) {
		for (int j = 0; j < objects.size(); j++) {
			result[i].updateByPolygon(objects[j]);
		}
	}
	return result;
}