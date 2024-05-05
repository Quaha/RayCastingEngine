#include "libs.hpp"

#include "Camera.hpp"
#include "Window.hpp"

#include "Controller.hpp"

void processingUserActions(Camera& camera, Window& window) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		camera.moveForward();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		camera.moveBack();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		camera.moveLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		camera.moveRight();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		camera.moveUp();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		camera.moveDown();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		camera.rotateLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		camera.rotateRight();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		camera.rotateUp();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		camera.rotateDown();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		window.close();
	}
}