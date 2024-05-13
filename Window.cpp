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

void Window::drawRectangle(float x, float  y, float  height, float width, sf::ConvexShape &poly_shape, sf::Color C) {
	poly_shape.setPoint(0, { x, y });
	poly_shape.setPoint(1, { x + width, y });
	poly_shape.setPoint(2, { x + width, y + height });
	poly_shape.setPoint(3, { x, y + height });
	poly_shape.setFillColor(C);
	window.draw(poly_shape);
}

void Window::drawObjects3D(Camera& camera, const std::vector<Polyhedron> &objects) {

	std::vector<std::vector<Segment>> rays(REAL_HEIGHT, std::vector<Segment>(REAL_WIDTH));
	camera.getUpdatedRays(objects, rays);

	float W = (float)WINDOW_WIDTH / REAL_WIDTH;
	float H = (float)WINDOW_HEIGHT / REAL_HEIGHT;

	sf::ConvexShape poly_shape;
	poly_shape.setPointCount(4);

	for (int i = 0; i < REAL_HEIGHT; i++) {
		for (int j = 0; j < REAL_WIDTH; j++) {
			if (rays[i][j].updated) {
				sf::Uint8 C = (sf::Uint8)(256 * (rays[i][j].getLength() / RAYS_LENGTH));
				drawRectangle(W * j, H * i, H, W, poly_shape, { C, C, C });
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