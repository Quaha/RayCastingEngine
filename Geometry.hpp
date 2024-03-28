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

struct Coordinates {

	long double x = 0;
	long double y = 0;

	Coordinates() : x(0), y(0) {};
	Coordinates(long double x, long double y) : x(x), y(y) {};

	Coordinates operator+(const Coordinates& other) const;
	Coordinates operator-(const Coordinates& other) const;
};

struct Point {

	long double x = 0;
	long double y = 0;

	Vector operator-(const Point& point) const;

	Point() : x(0), y(0) {};
	Point(long double x, long double y) : x(x), y(y) {};
	Point(const Coordinates& coordinates) : x(coordinates.x), y(coordinates.y) {};
};

struct Vector {

	long double x = 0;
	long double y = 0;

	Vector() : x(0), y(0) {};
	Vector(long double x, long double y) : x(x), y(y) {};
	Vector(const Point& point1, const Point& point2); // Create an AB Vector

	Vector operator+(const Vector& other) const;
	Vector& operator+=(const Vector& other);

	Vector operator-(const Vector& other) const;
	Vector& operator-=(const Vector& other);

	Vector operator-() const;

	long double getAbs2() const;
	static long double abs2(const Vector& vector);

	static long double scalarProduct(const Vector& vector1, const Vector& vector2);
	static long double vectorProduct(const Vector& vector1, const Vector& vector2);
};

struct Segment {

	Point point1 = { 0, 0 };
	Point point2 = { 0, 0 };

	Segment() : point1({ 0, 0 }), point2({ 0, 0 }) {};
	Segment(const Point& point1, const Point& point2) : point1(point1), point2(point2) {};

	long double getLength2() const;

	void updateBySegment(const Segment& segment);
	void updateByPolygon(const Polygon& polygon);

};

struct Polygon {

	std::vector<Point> corners;

	Polygon();
	Polygon(const Point& point, long double width, long double height); // Create an rectangle
	Polygon(const std::vector<Point> points);

};

struct Line {

	long double A = 0, B = 0, C = 0; // Coefficients of the general equation of the line

	Line() : A(0), B(0), C(0) {};
	Line(long double A, long double B, long double C) : A(A), B(B), C(C) {};
	Line(const Point &point1, const Point &point2);

	static Point getIntersect(const Line& line1,const Line& line2);
};