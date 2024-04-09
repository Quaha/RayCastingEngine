#include "programData.hpp"
#include "Camera.hpp"

#include "Window.hpp"

/*
 ~-------->
 |        X
 |
 |
 |
 V Y

*/

Window::Window(unsigned int width, unsigned int height, const char* name) {
	window.create({ width, height }, name);
}

bool Window::isOpen() const {
	return window.isOpen();
}

void Window::close() {
	window.close();
}

void Window::processingWindowEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
}

void Window::drawPolygon(const Polygon& polygon, const sf::Color colour) {
	sf::ConvexShape poly_shape;
	poly_shape.setPointCount(polygon.corners.size());
	for (int i = 0; i < polygon.corners.size(); i++) {
		poly_shape.setPoint(i, { (float)polygon.corners[i].x, (float)polygon.corners[i].y });
	}
	poly_shape.setFillColor(colour);
	window.draw(poly_shape);
}

void Window::drawSegment(const Segment& segment, const sf::Color colour) {
	sf::RectangleShape segment_shape({ (float)1, (float)sqrt(segment.getLength2()) });
	segment_shape.setFillColor(colour);
	segment_shape.setPosition({(float)segment.point1.x, (float)segment.point1.y});
	segment_shape.rotate((float)90 + (float)radiansToDegrees(atan2l(segment.point1.y - segment.point2.y, segment.point1.x - segment.point2.x)));
	window.draw(segment_shape);
}

//void Window::draw2D(Camera& camera, const std::vector<Polygon>& objects) {
//	for (auto& p : objects) {
//		drawPolygon(p, sf::Color::Black);
//	}
//
//	const int CAMERA_SIZE = 15;
//	sf::CircleShape camera_shape(CAMERA_SIZE);
//	camera_shape.setFillColor(sf::Color::Green);
//	camera_shape.setPosition({ (float)camera.getPosition().x - CAMERA_SIZE, (float)camera.getPosition().y - CAMERA_SIZE });
//	window.draw(camera_shape);
//
//	std::vector<Segment> rays = camera.getRays(objects);
//	for (auto& p : rays) {
//		drawSegment(p, sf::Color::Red);
//	}
//}

void Window::draw3D(Camera& camera, const std::vector<Polyhedron> &objects) {

	//std::vector<Segment> rays = camera.getRays(objects);
	//long double objects_width = (long double)WINDOW_WIDTH / rays.size();
	//
	//for (int i = 0, j = (int)rays.size() - 1; i < rays.size(); i++, j--) {
	//	long double dist = sqrt(rays[j].getLength2());
	//	if (abs(dist - RAYS_LENGTH) < 1e-5) continue;
	//	dist *= cos(degreesToRadians(abs(i - (long double)rays.size() / 2) * RAYS_STEP) * 3 / 4);
	//	Polygon temp({(float)objects_width * (float)i, (float)WINDOW_HEIGHT / 2 - OBJECTS_HEIGHT/ 2 / dist}, objects_width, OBJECTS_HEIGHT / dist);
	//	sf::Color current(128, 128, 128);
	//	current.r = (sf::Uint8)(255 * dist / RAYS_LENGTH);
	//	current.g = (sf::Uint8)(255 * dist / RAYS_LENGTH);
	//	current.b = (sf::Uint8)(255 * dist / RAYS_LENGTH);
	//	drawPolygon(temp, current);
	//}
}

void Window::display() {
	window.display();
}

void Window::clear(sf::Color Colour) {
	window.clear(Colour);
}