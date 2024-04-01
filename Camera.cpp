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
	rays_is_updated = false;
	camera_position.x += USER_MOVE_SPEED * sin(angle);
	camera_position.y += USER_MOVE_SPEED * cos(angle);
}

void Camera::moveBack() {
	rays_is_updated = false;
	camera_position.x -= USER_MOVE_SPEED * sin(angle);
	camera_position.y -= USER_MOVE_SPEED * cos(angle);
}

void Camera::moveLeft() {
	rays_is_updated = false;
	camera_position.x += USER_MOVE_SPEED * sin(angle + PI / 2);
	camera_position.y += USER_MOVE_SPEED * cos(angle + PI / 2);
}

void Camera::moveRight() {
	rays_is_updated = false;
	camera_position.x -= USER_MOVE_SPEED * sin(angle + PI / 2);
	camera_position.y -= USER_MOVE_SPEED * cos(angle + PI / 2);
}

void Camera::rotateLeft() {
	rays_is_updated = false;
	angle += USER_ROTATE_SPEED;
	while (angle >= 2 * PI) {
		angle -= 2 * PI;
	}
}

void Camera::rotateRight() {
	rays_is_updated = false;
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

void Camera::updateRays(const std::vector<Polygon>& objects) {
	rays_is_updated = true;
	rays.clear();
	for (long double i = angle - degreesToRadians(FOV / 2); i <= angle + degreesToRadians(FOV / 2); i += degreesToRadians(RAYS_STEP)) {
		Segment temp;
		temp.point1 = this->getPosition();
		temp.point2 = { this->getPosition().x + RAYS_LENGTH * sin(i), this->getPosition().y + RAYS_LENGTH * cos(i) };
		rays.push_back(temp);
	}
	for (int i = 0; i < rays.size(); i++) {
		for (int j = 0; j < objects.size(); j++) {
			rays[i].updateByPolygon(objects[j]);
		}
	}
}

std::vector<Segment> Camera::getRays(const std::vector<Polygon>& objects) {
	if (!rays_is_updated) {
		updateRays(objects);
	}
	return rays;
}