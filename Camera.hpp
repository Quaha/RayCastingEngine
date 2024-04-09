#pragma once

#include "programData.hpp"

class Camera {

private:

	Point camera_position = { 0, 0, 0 };

	long double angle = 0;

	std::vector<Segment> rays;
	bool rays_is_updated = false;

public:

	Camera() : camera_position({ 0, 0, 0 }) {};
	Camera(long double x, long double y, long double z) : camera_position({ x, y, z }) {};

	void moveForward();
	void moveBack();
	void moveLeft();
	void moveRight();

	void rotateLeft();
	void rotateRight();

	Point getPosition() const;
	long double getAngle() const;

	void updateRays(const std::vector<Polygon>& objects);
	std::vector<Segment> getRays(const std::vector<Polygon>& objects);
};