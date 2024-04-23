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

	void drawPolygon(const Polygon& segment, const sf::Color colour);

	void drawRect(float x, float y, float width, float height, sf::Color C);

	void draw3D(Camera& camera, const std::vector<Polyhedron>& objects);

	void display();
	void clear(sf::Color colour = sf::Color::White);

};