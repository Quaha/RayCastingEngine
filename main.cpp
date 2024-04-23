#include "libs.hpp"

#include "Window.hpp"
#include "Camera.hpp"
#include "controller.hpp"

int main() {   

    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "RayCastingEngine");
    Camera user(0, 0, 0);

    Polyhedron cube1({ 200 , -50, -50 }, 100);
    Polyhedron cube2({ 400 , -50, -50 }, 100);

    while (window.isOpen()) {
        
        window.processingWindowEvents();
        processingUserActions(user, window);

        window.clear();
        window.draw3D(user, { cube1, cube2 });
        window.display();
    }

    return 0;
}