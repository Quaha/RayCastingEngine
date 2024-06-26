#pragma once

#include "libs.hpp"

class Camera {

private:

	Point camera_position = { 0, 0, 0 };

	double angle1 = 0; // xOy
	double angle2 = 0; // _|_ xOy

public:

	Camera() : camera_position({ 0, 0, 0 }) {};
	Camera(double x, double y, double z) : camera_position({ x, y, z }) {};

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
	double getAngle1() const;
	double getAngle2() const;

	void getUpdatedRays(const std::vector<Polyhedron>& objects, std::vector<std::vector<Segment>> &rays) const;
};