#pragma once

#include "libs.hpp"

#include "Settings.hpp"

struct Point;
struct Vector;
struct Segment;
struct Polyhedron;
struct Line;
struct Plane;
struct Triangle;

double radiansToDegrees(double angle);
double degreesToRadians(double angle);

struct Point {

	double x = 0, y = 0, z = 0;

	Vector operator-(const Point& point) const;
	Point operator+(const Vector& vector) const;

	Point() : x(0), y(0), z(0) {};
	Point(double x, double y, double z) : x(x), y(y), z(z) {};
};

struct Vector {

	double x = 0, y = 0, z = 0;

	Vector() : x(0), y(0), z(0) {};
	Vector(double x, double y, double z) : x(x), y(y), z(z) {};
	Vector(const Point& point1, const Point& point2); // Create a directed vector from point1 to point2

	Vector operator+(const Vector& other) const;
	Vector& operator+=(const Vector& other);

	Vector operator*(double t) const;

	Vector operator-(const Vector& other) const;
	Vector& operator-=(const Vector& other);

	Vector operator-() const;

	double getAbs2() const;
	double getAbs() const;
	static double abs2(const Vector& vector);
};

struct Segment {

	Point point1 = { 0, 0, 0 };
	Point point2 = { 0, 0, 0 };

	bool updated = false;

	Segment() : point1({ 0, 0, 0 }), point2({ 0, 0, 0 }) {};
	Segment(const Point& point1, const Point& point2) : point1(point1), point2(point2) {};

	double getLength2() const;
	double getLength() const;

	bool inSegment(const Point& point) const;
};

struct Polyhedron {

	std::vector<Triangle> edges;

	Polyhedron(const Point& point, double size); // Create a cube
	Polyhedron(const Point& point1, const Point& point2, const Point& point3, const Point& point4); // Create a tetrahedron
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

	double A = 0, B = 0, C = 0, D = 0;

	Plane(const Point& point1, const Point& point2, const Point& point3);

	bool inPlane(const Point& point);
	static Point getIntersect(const Line& line, const Plane& plane);
};

struct Triangle {

	Point P1 = { 0, 0, 0 };
	Point P2 = { 0, 0, 0 };
	Point P3 = { 0, 0, 0 };

	static double getArea(const Point& point1, const Point& point2, const Point& point3);

	Triangle(const Point& point1, const Point& point2, const Point& point3);

	bool inTriangle(const Point& point) const;

	void updateRays(std::vector<std::vector<Segment>> &rays) const;

};