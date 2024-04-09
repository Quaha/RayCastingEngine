#include "libs.hpp"

#include "Window.hpp"
#include "Camera.hpp"
#include "controller.hpp"

int main() {   

    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "RayCasting");
    Camera player(0, 0, 0);

    Polyhedron R({ 500, 500, 500 }, 100);

    while (window.isOpen()) {
        
        window.processingWindowEvents();
        processingUserActions(player, window);

        window.clear();
        window.draw3D(player, { R });
        window.display();
    }

    return 0;
}