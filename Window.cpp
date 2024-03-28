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

void Window::draw2D(const Camera& camera, const std::vector<Polygon> &objects) {

	const int CAMERA_SIZE = 15;

	sf::CircleShape camera_shape(CAMERA_SIZE);
	camera_shape.setFillColor(sf::Color::Green);
	camera_shape.setPosition({ (float)camera.getPosition().x - CAMERA_SIZE, (float)camera.getPosition().y - CAMERA_SIZE});

	window.draw(camera_shape);

	for (auto& p : objects) {
		drawPolygon(p, sf::Color::Black);
	}

	std::vector<Segment> rays = camera.getRays(objects);
	for (auto& p : rays) {
		drawSegment(p, sf::Color::Red);
	}
}

void Window::display() {
	window.display();
}

void Window::clear(sf::Color Colour) {
	window.clear(Colour);
}