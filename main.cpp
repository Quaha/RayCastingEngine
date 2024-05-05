#include "libs.hpp"

#include "Window.hpp"
#include "Camera.hpp"
#include "Controller.hpp"

int main() {   

    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "RayCastingEngine");
    Camera user(0, 0, 0);

    Polyhedron cube({ 300 , -200, -50 }, 100);
    Polyhedron tetrahedron({ 200, 200, 200 }, {0, 200, 200 }, { 200, 0, 200 }, { 200, 200,0 });

    while (window.isOpen()) {
        
        window.processingWindowEvents();
        processingUserActions(user, window);

        window.clear();
        window.drawObjects3D(user, {cube, tetrahedron});
        window.display();
    }

    return 0;
}