#include "Geometry.hpp"

#include "cmath"

long double radiansToDegrees(long double angle) {
	return angle * 180 / PI;
}

long double degreesToRadians(long double angle) {
	return angle * PI / 180;
}

Coordinates Coordinates::operator+(const Coordinates& other) const {
	return { this->x + other.x, this->y + other.y };
}

Coordinates Coordinates::operator-(const Coordinates& other) const {
	return { this->x - other.x, this->y - other.y };
}

Vector Point::operator-(const Point& other) const{
	return { other, (*this) };
}

Vector::Vector(const Point& point1, const Point& point2) {
	x = point2.x - point1.x;
	y = point2.y - point1.y;
}

Vector Vector::operator+(const Vector& other) const {
	return { this->x + other.x, this->y + other.y };
}

Vector& Vector::operator+=(const Vector& other){
	this->x += other.x;
	this->y += other.y;

	return (*this);
}

Vector Vector::operator-(const Vector& other) const {
	return { this->x - other.x, this->y - other.y };
}

Vector& Vector::operator-=(const Vector& other) {
	this->x -= other.x;
	this->y -= other.y;

	return (*this);
}

Vector Vector::operator-() const {
	return {-this->x, -this->y};
}

long double Vector::getAbs2() const {
	return x * x + y * y;
}

long double Vector::abs2(const Vector& vector) {
	return vector.x * vector.x + vector.y * vector.y;
}

long double Vector::scalarProduct(const Vector& vector1, const Vector& vector2) {
	return vector1.x * vector2.x + vector1.y * vector2.y;
}

long double Vector::vectorProduct(const Vector& vector1, const Vector& vector2) {
	return vector1.x * vector2.y - vector1.y * vector2.x;
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

	long double V1 = (P2.x - P1.x) * (P2.x - P1.x) + (P2.y - P1.y) * (P2.y - P1.y);
	long double V2 = (P2.x - P.x) * (P2.x - P.x) + (P2.y - P.y) * (P2.y - P.y);
	long double V3 = (P.x - P1.x) * (P.x - P1.x) + (P.y - P1.y) * (P.y - P1.y);

	long double V4 = (P3.x - P4.x) * (P3.x - P4.x) + (P3.y - P4.y) * (P3.y - P4.y);
	long double V5 = (P3.x - P.x) * (P3.x - P.x) + (P3.y - P.y) * (P3.y - P.y);
	long double V6 = (P.x - P4.x) * (P.x - P4.x) + (P.y - P4.y) * (P.y - P4.y);

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

Polygon::Polygon() {
	corners.push_back({ 0, 0 });
}

Polygon::Polygon(const Point& point, long double width, long double height) {
	corners.push_back({ point.x, point.y });
	corners.push_back({ point.x + width, point.y });
	corners.push_back({ point.x + width, point.y + height });
	corners.push_back({ point.x, point.y + height });
}

Polygon::Polygon(const std::vector<Point> points) {
	corners = points;
}

Line::Line(const Point &point1,const Point &point2) {
	A = point2.y - point1.y;
	B = point1.x - point2.x;
	C = point1.y * point2.x - point1.x * point2.y;
}

Point Line::getIntersect(const Line &line1,const Line &line2) {
	long double x = (line1.B * line2.C - line2.B * line1.C) / (line1.A * line2.B - line2.A * line1.B);
	long double y = (line1.C * line2.A - line2.C * line1.A) / (line1.A * line2.B - line2.A * line1.B);
	return { x, y };
}