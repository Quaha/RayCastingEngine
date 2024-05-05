#include "Geometry.hpp"

#include <cmath>

float radiansToDegrees(float angle) {
	return angle * 180 / PI;
}

float degreesToRadians(float angle) {
	return angle * PI / 180;
}

Vector Point::operator-(const Point& other) const {
	return { other, (*this) };
}

Point Point::operator+(const Vector& vector) const {
	return { this->x + vector.x, this->y + vector.y, this->z + vector.z };
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

Vector Vector::operator*(float t) const {
	return { this->x * t, this->y * t, this->z * t };
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

float Vector::getAbs2() const {
	return x * x + y * y + z * z;
}

float Vector::getAbs() const {
	return sqrt(x * x + y * y + z * z);
}

float Vector::abs2(const Vector& vector) {
	return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}

float Segment::getLength2() const {
	return (point1 - point2).getAbs2();
}

float Segment::getLength() const {
	return (point1 - point2).getAbs();
}

Polyhedron::Polyhedron(const Point& point, float size) {
	float x = point.x;
	float y = point.y;
	float z = point.z;

	Triangle T1({ x, y, z }, { x + size, y, z }, { x, y + size, z });
	Triangle T2({ x + size, y + size, z }, { x + size, y, z }, { x, y + size, z });

	edges.push_back(T1);
	edges.push_back(T2);

	Triangle T3({ x, y, z + size }, { x + size, y, z + size }, { x, y + size, z + size });
	Triangle T4({ x + size, y + size, z + size }, { x + size, y, z + size }, { x, y + size, z + size });

	edges.push_back(T3);
	edges.push_back(T4);

	Triangle T5({ x, y, z }, { x + size, y, z }, { x, y, z + size });
	Triangle T6({ x + size, y, z + size }, { x + size, y, z }, { x, y, z + size });

	edges.push_back(T5);
	edges.push_back(T6);

	Triangle T7({ x, y + size, z }, { x + size, y + size, z }, { x, y + size, z + size });
	Triangle T8({ x + size, y + size, z + size }, { x + size, y + size, z }, { x, y + size, z + size });

	edges.push_back(T7);
	edges.push_back(T8);

	Triangle T9({ x, y, z }, { x, y + size, z }, { x, y, z + size });
	Triangle T10({ x, y + size, z + size }, { x, y + size, z }, { x, y, z + size });

	edges.push_back(T9);
	edges.push_back(T10);

	Triangle T11({ x + size, y, z }, { x + size, y + size, z }, { x + size, y, z + size });
	Triangle T12({ x + size, y + size, z + size }, { x + size, y + size, z }, { x + size, y, z + size });

	edges.push_back(T11);
	edges.push_back(T12);
}

Polyhedron::Polyhedron(const Point& point1, const Point& point2, const Point& point3, const Point& point4) {
	edges.push_back({ point1, point2, point3 });
	edges.push_back({ point4, point2, point3 });
	edges.push_back({ point1, point4, point3 });
	edges.push_back({ point1, point2, point4 });
}

Line::Line(const Point& point1, const Point& point2) {
	point = point1;
	vector = point2 - point1;
}

Plane::Plane(const Point& point1, const Point& point2, const Point& point3) {
	point = point1;
	vector1 = point2 - point1;
	vector2 = point3 - point1;

	A = vector1.y * vector2.z - vector2.y * vector1.z;
	B = - (vector1.x * vector2.z - vector2.x * vector1.z);
	C = vector1.x * vector2.y - vector2.x * vector1.y;
	D = -point.x * A - point.y * B - point.z * C;
}

bool Plane::inPlane(const Point& point) {
	return abs(A * point.x + B * point.y + C * point.z + D) < ACCURACY;
}

Point Plane::getIntersect(const Line& line, const Plane& plane) {
	float t = -(plane.A * line.point.x + plane.B * line.point.y + plane.C * line.point.z + plane.D) / (plane.A * line.vector.x + plane.B * line.vector.y + plane.C * line.vector.z);

	Point result = line.point + line.vector * t;
	return result;
}

float Triangle::getArea(const Point& point1, const Point& point2, const Point& point3) {
	float d1 = (point1 - point2).getAbs();
	float d2 = (point1 - point3).getAbs();
	float d3 = (point2 - point3).getAbs();
	float p = (d1 + d2 + d3) / 2;
	return sqrt(p * (p - d1) * (p - d2) * (p - d3));
}

Triangle::Triangle(const Point& point1, const Point& point2, const Point& point3) {
	P1 = point1;
	P2 = point2;
	P3 = point3;
}

bool Triangle::inTriangle(const Point& P) const{
	return abs(getArea(P1, P2, P3) - (getArea(P, P2, P3) + getArea(P1, P, P3) + getArea(P1, P2, P))) < ACCURACY;
}

void Triangle::updateRays(Segment rays[REAL_HEIGHT][REAL_WIDTH]) const {

	Plane plane(P1, P2, P3);

	for (int i = 0; i < REAL_HEIGHT; i++) {
		for (int j = 0; j < REAL_WIDTH; j++) {

			Point possible_point = Plane::getIntersect({ rays[i][j].point1,  rays[i][j].point2 - rays[i][j].point1 }, plane);
			if (inTriangle(possible_point)) {
				Vector AC = possible_point - rays[i][j].point1;
				Vector BC = possible_point - rays[i][j].point2;
				Vector AB = rays[i][j].point1 - rays[i][j].point2;

				if (abs(AC.getAbs() + BC.getAbs() - AB.getAbs()) > ACCURACY) return;

				if ((rays[i][j].point2 - rays[i][j].point1).getAbs2() > (possible_point - rays[i][j].point1).getAbs2()) {
					rays[i][j].point2 = possible_point;
					rays[i][j].updated = true;
				}
			}
		}
	}
}