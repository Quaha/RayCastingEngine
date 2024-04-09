#include "Geometry.hpp"

#include <cmath>

#include <iostream>

long double radiansToDegrees(long double angle) {
	return angle * 180 / PI;
}

long double degreesToRadians(long double angle) {
	return angle * PI / 180;
}

Vector Point::operator-(const Point& other) const {
	return { other, (*this) };
}

Vector::Vector(const Point& point1, const Point& point2) {
	x = point2.x - point1.x;
	y = point2.y - point1.y;
	z = point2.z - point1.z;
}

Vector Vector::operator+(const Vector& other) const {
	return { this->x + other.x, this->y + other.y, this->z + other.z };
}

Vector& Vector::operator+=(const Vector& other) {
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;

	return (*this);
}

Vector Vector::operator-(const Vector& other) const {
	return { this->x - other.x, this->y - other.y, this->z - other.z };
}

Vector& Vector::operator-=(const Vector& other) {
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;

	return (*this);
}

Vector Vector::operator-() const {
	return { -this->x, -this->y, -this->z };
}

long double Vector::getAbs2() const {
	return x * x + y * y + z * z;
}

long double Vector::abs2(const Vector& vector) {
	return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}

long double Vector::scalarProduct(const Vector& vector1, const Vector& vector2) {
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

long double Segment::getLength2() const {
	return (point1 - point2).getAbs2();
}

void Segment::updateBySegment(const Segment& segment) {
	Point P1 = point1;
	Point P2 = point2;
	Line L1(P1, P2);

	Point P3 = segment.point1;
	Point P4 = segment.point2;
	Line L2(P3, P4);

	Point P = Line::getIntersect(L1, L2);

	long double V1 = (P2.x - P1.x) * (P2.x - P1.x) + (P2.y - P1.y) * (P2.y - P1.y) + (P2.z - P1.z) * (P2.z - P1.z);
	long double V2 = (P2.x - P.x) * (P2.x - P.x) + (P2.y - P.y) * (P2.y - P.y) + (P2.z - P.z) * (P2.z - P.z);
	long double V3 = (P.x - P1.x) * (P.x - P1.x) + (P.y - P1.y) * (P.y - P1.y) + (P.z - P1.z) * (P.z - P1.z);

	long double V4 = (P3.x - P4.x) * (P3.x - P4.x) + (P3.y - P4.y) * (P3.y - P4.y) + (P3.z - P4.z) * (P3.z - P4.z);
	long double V5 = (P3.x - P.x) * (P3.x - P.x) + (P3.y - P.y) * (P3.y - P.y) + (P3.z - P.z) * (P3.z - P.z);
	long double V6 = (P.x - P4.x) * (P.x - P4.x) + (P.y - P4.y) * (P.y - P4.y) + (P.z - P4.z) * (P.z - P4.z);

	if (abs(sqrt((V1)) - sqrt(V2) - sqrt(V3)) <= 1e-10 && abs(sqrt((V4)) - sqrt(V5) - sqrt(V6)) <= 1e-10) {
		point2 = P;
	}
}

void Segment::updateByPolygon(const Polygon& polygon) {
	for (int i = 0; i < polygon.corners.size() - 1; i++) {
		Segment S = { polygon.corners[i], polygon.corners[i + 1] };
		updateBySegment(S);
	}
	Segment S = { polygon.corners.back(), polygon.corners[0] };
	updateBySegment(S);
}

Polygon::Polygon(const std::vector<Point> points) {
	corners = points;
}

Point Polygon::getIntersect(const Line& line, const Polygon& polygon) {
	


	
}

Polyhedron::Polyhedron(const Point& point, long double size) {
	long double x = point.x;
	long double y = point.y;
	long double z = point.z;

	Polygon P1({ {x, y, z}, {x + size, y, z}, {x, y + size, z}, {x + size, y + size, z} });
	Polygon P2({ {x, y, z}, {x + size, y, z}, {x, y, z + size}, {x + size, y, z + size} });
	Polygon P3({ {x, y, z}, {x, y + size, z}, {x, y, z + size}, {x, y + size, z + size} });
	Polygon P4({ {x + size, y + size, z + size}, {x, y + size, z + size}, {x + size, y, z + size}, {x, y, z + size} });
	Polygon P5({ {x + size, y + size, z + size}, {x, y + size, z + size}, {x + size, y + size, z}, {x, y + size, z} });
	Polygon P6({ {x + size, y + size, z + size}, {x + size, y, z + size}, {x + size, y + size, z}, {x + size, y, z} });

	edges.push_back(P1);
	edges.push_back(P2);
	edges.push_back(P3);
	edges.push_back(P4);
	edges.push_back(P5);
	edges.push_back(P6);
}

Line::Line(const Point& point1, const Point& point2) {
	point = point1;
	vector = point2 - point1;
}

Point Line::getIntersect(const Line& line1, const Line& line2) {
	long double t = (line2.vector.x * (line2.point.y - line1.point.y) - line2.vector.y * (line2.point.x - line1.point.x)) / (line1.vector.y * line2.vector.x - line1.vector.x * line2.vector.y);
	long double x = line1.point.x + line1.vector.x * t;
	long double y = line1.point.y + line1.vector.y * t;
	long double z = line1.point.z + line1.vector.z * t;
	return { x, y, z };
}