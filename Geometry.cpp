#include "Geometry.hpp"

#include <cmath>

double radiansToDegrees(double angle) {
	return angle * 180 / PI;
}

double degreesToRadians(double angle) {
	return angle * PI / 180;
}

int sgn(double value) {
	if (value >= 0) {
		return 1;
	}
	return -1;
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

Vector Vector::operator*(double t) const {
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

double Vector::getAbs2() const {
	return x * x + y * y + z * z;
}

double Vector::getAbs() const {
	return sqrt(x * x + y * y + z * z);
}

double Vector::abs2(const Vector& vector) {
	return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}

double Vector::scalarProduct(const Vector& vector1, const Vector& vector2) {
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

double Vector::vectorProduct(const Vector& vector1, const Vector& vector2) {
	return vector1.y * vector2.z - vector1.z * vector2.y - vector1.x * vector2.z + vector2.x * vector1.z + vector1.x * vector2.y - vector2.x * vector1.y;
}

double Segment::getLength2() const {
	return (point1 - point2).getAbs2();
}

double Segment::getLength() const {
	return (point1 - point2).getAbs();
}

void Segment::updateByPolygon(const Polygon& polygon) {
	
	Plane plane(polygon.corners[0], polygon.corners[1], polygon.corners[2]);

	Point possible_point = Plane::getIntersect({point1, point2 - point1}, plane);

	if (plane.inPlane(possible_point)) {
		int cnt_plus = 0;
		int cnt_minus = 0;
		for (int i = 0; i < polygon.corners.size(); i++) {
			Point P1 = polygon.corners[i];
			Point P2 = polygon.corners[(i + 1) % polygon.corners.size()];
			if (sgn(Vector::vectorProduct(P2 - P1, possible_point - P1)) == 1) {
				cnt_plus++;
			}
			else {
				cnt_minus--;
			}
		}

		if (cnt_plus == 0 || cnt_minus == 0) {
			Vector AC = possible_point - point1;
			Vector BC = possible_point - point2;
			Vector AB = point1 - point2;

			if (abs(AC.getAbs() + BC.getAbs() - AB.getAbs()) > ACCURACY) return;
			
			if ((this->point2 - (this->point1)).getAbs2() > (possible_point - (this->point1)).getAbs2()) {
				point2 = possible_point;
			}
		}

	}
}

void Segment::updateByPolyhedron(const Polyhedron& polyhedron) {

	for (int i = 0; i < polyhedron.edges.size(); i++) {
		updateByPolygon(polyhedron.edges[i]);
	}

}

Polygon::Polygon(const std::vector<Point> points) {
	corners = points;
}

Point Polygon::getIntersect(const Line& line, const Polygon& polygon) {
	
	Plane plane(polygon.corners[0], polygon.corners[1], polygon.corners[2]);
	double t = -(plane.A * line.point.x + plane.B * line.point.y + plane.C * line.point.z + plane.D) / (plane.A * line.vector.x + plane.B * line.vector.y + plane.C * line.vector.z);
	
	Point result = line.point + line.vector * t;
	return result;
}

Polyhedron::Polyhedron(const Point& point, double size) {
	double x = point.x;
	double y = point.y;
	double z = point.z;

	Polygon P1({ {x, y, z}, {x + size, y, z}, {x + size, y + size, z} , {x, y + size, z} });
	Polygon P2({ {x, y, z}, {x + size, y, z}, {x + size, y, z + size} , {x, y, z + size} });
	Polygon P3({ {x, y, z}, {x, y, z + size}, {x, y + size, z + size} , {x, y + size, z} });
	Polygon P4({ {x + size, y + size, z + size}, {x, y + size, z + size}, {x, y, z + size}, {x + size, y, z + size} });
	Polygon P5({ {x + size, y + size, z + size}, {x, y + size, z + size}, {x, y + size, z}, {x + size, y + size, z} });
	Polygon P6({ {x + size, y + size, z + size}, {x + size, y, z + size}, {x + size, y, z}, {x + size, y + size, z} });

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

Plane::Plane(const Point& point1, const Point& point2, const Point& point3) {
	point = point1;
	vector1 = point2 - point1;
	vector2 = point3 - point1;

	A = vector1.y * vector2.z - vector2.y * vector1.z;
	B = - (vector1.x * vector2.z - vector2.x * vector1.z);
	C = vector1.x * vector2.y - vector2.x * vector1.y;
	D = -point.x * A + point.y * B - point.z * C;

}

bool Plane::inPlane(const Point& point) {
	return abs(A * point.x + B * point.y + C * point.z + D) < ACCURACY;
}

Point Plane::getIntersect(const Line& line, const Plane& plane) {
	double t = -(plane.A * line.point.x + plane.B * line.point.y + plane.C * line.point.z + plane.D) / (plane.A * line.vector.x + plane.B * line.vector.y + plane.C * line.vector.z);

	Point result = line.point + line.vector * t;
	return result;
}