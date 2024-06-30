#include <algine/core/Engine.h>
#include <algine/core/window/GLFWWindow.h>

#include "VisualizerContent.h"

using namespace algine;

static void exec() {
    GLFWWindow window("Visualizer", 1366, 768);
    window.setFullscreenDimensions(1366, 768);
    window.setMouseTracking(true);
    window.setKeyboardTracking(true);
    window.setWindowStateTracking(true);
    //window.setCursorMode(Window::CursorMode::Disabled);
    window.setContentLater<VisualizerContent>(&window);
    window.renderLoop();
}

int main(int argc, char **argv) {
    Engine::exec(argc, argv, &exec);
    return 0;
}
