#pragma once

#include "programData.hpp"

class Camera {

private:

	Coordinates camera_position = { 0, 0 };

	long double angle = 0;

public:

	Camera() : camera_position({ 0, 0 }) {};
	Camera(long double x, long double y) : camera_position({ x, y }) {};

	void moveForward();
	void moveBack();
	void moveLeft();
	void moveRight();

	void rotateLeft();
	void rotateRight();

	Coordinates getPosition() const;
	long double getAngle() const;

	std::vector<Segment> getRays(const std::vector<Polygon>& objects) const;

};