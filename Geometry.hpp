#pragma once

#include <vector>
#include <CL/cl.h>

#include "Settings.hpp"

struct Point;
struct Vector;
struct Segment;
struct Polyhedron;
struct Line;
struct Plane;
struct Triangle;

float radiansToDegrees(float angle);
float degreesToRadians(float angle);

struct Point {

	float x = 0, y = 0, z = 0;

	Vector operator-(const Point& point) const;
	Point operator+(const Vector& vector) const;

	Point() : x(0), y(0), z(0) {};
	Point(float x, float y, float z) : x(x), y(y), z(z) {};
};

struct Vector {

	float x = 0, y = 0, z = 0;

	Vector() : x(0), y(0), z(0) {};
	Vector(float x, float y, float z) : x(x), y(y), z(z) {};
	Vector(const Point& point1, const Point& point2); // Create an directed vector from point1 to point2

	Vector operator+(const Vector& other) const;
	Vector& operator+=(const Vector& other);

	Vector operator*(float t) const;

	Vector operator-(const Vector& other) const;
	Vector& operator-=(const Vector& other);

	Vector operator-() const;

	float getAbs2() const;
	float getAbs() const;
	static float abs2(const Vector& vector);
};

struct Segment {

	Point point1 = { 0, 0, 0 };
	Point point2 = { 0, 0, 0 };

	bool updated = false;

	Segment() : point1({ 0, 0, 0 }), point2({ 0, 0, 0 }) {};
	Segment(const Point& point1, const Point& point2) : point1(point1), point2(point2) {};

	float getLength2() const;
	float getLength() const;
};

struct Polyhedron {

	std::vector<Triangle> edges;

	Polyhedron(const Point& point, float size); // Create an cube
	Polyhedron(const Point& point1, const Point& point2, const Point& point3, const Point& point4); // Create an tetrahedron
};

struct Line {

	Point point = { 0, 0, 0 };
	Vector vector = { 0, 0, 0 };

	Line(const Point& point, const Vector& vector) : point(point), vector(vector) {};
	Line(const Point& point1, const Point& point2);

};

struct Plane {

	Point point = { 0, 0, 0 };
	Vector vector1 = { 0, 0, 0 };
	Vector vector2 = { 0, 0, 0 };

	float A = 0, B = 0, C = 0, D = 0;

	Plane(const Point& point1, const Point& point2, const Point& point3);

	bool inPlane(const Point& point);
	static Point getIntersect(const Line& line, const Plane& plane);
};

struct Triangle {

	Point P1 = { 0, 0, 0 };
	Point P2 = { 0, 0, 0 };
	Point P3 = { 0, 0, 0 };

	static float getArea(const Point& point1, const Point& point2, const Point& point3);

	Triangle(const Point& point1, const Point& point2, const Point& point3);
	bool inTriangle(const Point& point) const;

	void updateRays(Segment rays[REAL_HEIGHT][REAL_WIDTH]) const;

};