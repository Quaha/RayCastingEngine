#pragma once

#include "libs.hpp"
#include "Camera.hpp"

class Window {

private:
	sf::RenderWindow window;
public:

	Window(unsigned int width, unsigned int height, const char* name);

	bool isOpen() const;
	void close();

	void processingWindowEvents();

	void drawRectangle(float x, float y, float height, float width, sf::ConvexShape &poly_shape, sf::Color C);

	void drawObjects3D(Camera& camera, const std::vector<Polyhedron>& objects);

	void display();
	void clear(sf::Color colour = sf::Color::White);

};