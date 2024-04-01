#pragma once

#include "programData.hpp"
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
	void drawSegment(const Segment& segment, const sf::Color colour);

	void draw2D(Camera& camera, const std::vector<Polygon>& objects);
	void draw3D(Camera& camera, const std::vector<Polygon>& objects);

	void display();
	void clear(sf::Color colour = sf::Color::White);

};