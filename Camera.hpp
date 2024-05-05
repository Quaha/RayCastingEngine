#pragma once

#include "libs.hpp"

class Camera {

private:

	Point camera_position = { 0, 0, 0 };

	float angle1 = 0; // xOy
	float angle2 = 0; // z

public:

	Camera() : camera_position({ 0, 0, 0 }) {};
	Camera(float x, float y, float z) : camera_position({ x, y, z }) {};

	void moveForward();
	void moveBack();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void rotateLeft();
	void rotateRight();
	void rotateUp();
	void rotateDown();

	Point getPosition() const;
	float getAngle1() const;
	float getAngle2() const;

	void getRays(const std::vector<Polyhedron>& objects, Segment rays[REAL_HEIGHT][REAL_WIDTH]) const;
};