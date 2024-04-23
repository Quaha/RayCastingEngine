#pragma once

#include <vector>

#include "constants.hpp"

struct Coordinates;
struct Point;
struct Vector;
struct Segment;
struct Polygon;
struct Polyhedron;
struct Line;
struct Plane;

double radiansToDegrees(double angle);
double degreesToRadians(double angle);

int sgn(double value);

struct Point {

	double x = 0;
	double y = 0;
	double z = 0;

	Vector operator-(const Point& point) const;
	Point operator+(const Vector& vector) const;

	Point() : x(0), y(0), z(0) {};
	Point(double x, double y, double z) : x(x), y(y), z(z) {};
};

struct Vector {

	double x = 0;
	double y = 0;
	double z = 0;

	Vector() : x(0), y(0), z(0) {};
	Vector(double x, double y, double z) : x(x), y(y), z(z) {};
	Vector(const Point& point1, const Point& point2); // Create an AB Vector

	Vector operator+(const Vector& other) const;
	Vector& operator+=(const Vector& other);

	Vector operator*(double t) const;

	Vector operator-(const Vector& other) const;
	Vector& operator-=(const Vector& other);

	Vector operator-() const;

	double getAbs2() const;
	static double abs2(const Vector& vector);

	static double scalarProduct(const Vector& vector1, const Vector& vector2);
	static double vectorProduct(const Vector& vector1, const Vector& vector2);
};

struct Segment {

	Point point1 = { 0, 0, 0 };
	Point point2 = { 0, 0, 0 };

	Segment() : point1({ 0, 0, 0 }), point2({ 0, 0, 0 }) {};
	Segment(const Point& point1, const Point& point2) : point1(point1), point2(point2) {};

	double getLength2() const;

	void updateByPolygon(const Polygon& polygon);
	void updateByPolyhedron(const Polyhedron& polyhedron);
};

struct Polygon {

	std::vector<Point> corners;

	Polygon(const std::vector<Point> points);

	static Point getIntersect(const Line& line, const Polygon& polygon);

};

struct Polyhedron {

	std::vector<Polygon> edges;

	Polyhedron(const Point& point, double size); // Create an cube
};

struct Line {

	Point point = { 0, 0, 0 };
	Vector vector = { 0, 0, 0 };

	Line(const Point& point, const Vector& vector) : point(point), vector(vector) {};
	Line(const Point& point1, const Point& point2);

	static Point getIntersect(const Line& line1, const Line& line2);
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