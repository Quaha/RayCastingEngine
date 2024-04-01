#include "libs.hpp"

#include "Window.hpp"
#include "Camera.hpp"
#include "controller.hpp"

int main() {   

    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "RayCasting");
    Camera player(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    Polygon R1({ 500, 500 }, 100, 100);
    Polygon R2({ {100, 100}, {500, 100}, {250, 200} });

    while (window.isOpen()) {
        
        window.processingWindowEvents();
        processingUserActions(player, window);

        window.clear();
        window.draw2D(player, { R1, R2 });
        window.draw3D(player, { R1, R2 });
        window.display();
    }

    return 0;
}