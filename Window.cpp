#include "libs.hpp"
#include "Camera.hpp"

#include "Window.hpp"

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

void Window::drawRect(float x, float y, float width, float height, sf::Color C) {
	sf::ConvexShape poly_shape;
	poly_shape.setPointCount(4);
	poly_shape.setPoint(0, { x, y });
	poly_shape.setPoint(1, { x + width, y });
	poly_shape.setPoint(2, { x + width, y + height });
	poly_shape.setPoint(3, { x, y + height });
	poly_shape.setFillColor(C);
	window.draw(poly_shape);
}

void Window::draw3D(Camera& camera, const std::vector<Polyhedron> &objects) {

	std::vector<std::vector<Segment>> rays = camera.getRays(objects);

	int N = rays.size();
	int M = rays[0].size();

	double W = WINDOW_WIDTH / M;
	double H = WINDOW_HEIGHT / N;

	for (int i = N - 1; i >= 0; i--) {
		for (int j = 0; j < M; j++) {
			Segment ray = rays[i][j];
			double CURR_LENGTH = ray.getLength2();
			if (abs(CURR_LENGTH - RAYS_LENGTH * RAYS_LENGTH) > ACCURACY) {
				sf::Uint8 C = 256 * (sqrt(CURR_LENGTH / (RAYS_LENGTH * RAYS_LENGTH)));
				drawRect(W * i, H * j, W, H, { C, C, C });
			}
		}
	}

}

void Window::display() {
	window.display();
}

void Window::clear(sf::Color Colour) {
	window.clear(Colour);
}