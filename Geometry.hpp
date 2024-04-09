#pragma once

#include <vector>

struct Coordinates;
struct Point;
struct Vector;
struct Segment;
struct Polygon;
struct Line;

const long double PI = 3.141592653589793238462643383279502884;

long double radiansToDegrees(long double angle);
long double degreesToRadians(long double angle);

struct Point {

	long double x = 0;
	long double y = 0;
	long double z = 0;

	Vector operator-(const Point& point) const;

	Point() : x(0), y(0), z(0) {};
	Point(long double x, long double y, long double z) : x(x), y(y), z(z) {};
};

struct Vector {

	long double x = 0;
	long double y = 0;
	long double z = 0;

	Vector() : x(0), y(0), z(0) {};
	Vector(long double x, long double y, long double z) : x(x), y(y), z(z) {};
	Vector(const Point& point1, const Point& point2); // Create an AB Vector

	Vector operator+(const Vector& other) const;
	Vector& operator+=(const Vector& other);

	Vector operator-(const Vector& other) const;
	Vector& operator-=(const Vector& other);

	Vector operator-() const;

	long double getAbs2() const;
	static long double abs2(const Vector& vector);

	static long double scalarProduct(const Vector& vector1, const Vector& vector2);
};

struct Segment {

	Point point1 = { 0, 0, 0 };
	Point point2 = { 0, 0, 0 };

	Segment() : point1({ 0, 0, 0 }), point2({ 0, 0, 0 }) {};
	Segment(const Point& point1, const Point& point2) : point1(point1), point2(point2) {};

	long double getLength2() const;

	void updateBySegment(const Segment& segment);
	void updateByPolygon(const Polygon& polygon);

};

struct Polygon {

	std::vector<Point> corners;

	Polygon(const std::vector<Point> points);

	static Point getIntersect(const Line& line, const Polygon& polygon);

};

struct Polyhedron {

	std::vector<Polygon> edges;

	Polyhedron(const Point& point, long double size); // Create an cube
};

struct Line {

	Point point = { 0, 0, 0 };
	Vector vector = { 0, 0, 0 };

	Line() : point({ 0, 0, 0 }), vector({ 0, 0, 0 }) {};
	Line(const Point& point, const Vector& vector) : point(point), vector(vector) {};
	Line(const Point& point1, const Point& point2);

	static Point getIntersect(const Line& line1, const Line& line2);
};