#include "Engine.h"

int main(int argc, char** argv) {
    Engine gameEngine;

    gameEngine.init(argc, argv, 1024, 768, "GK Lab 07 - Engine Implementation");

    gameEngine.setFPS(60);
    gameEngine.setClearColor(0.1f, 0.1f, 0.1f, 1.0f); 

    std::cout << "Controls:" << std::endl;
    std::cout << "[P] - Perspective Projection" << std::endl;
    std::cout << "[O] - Orthogonal Projection" << std::endl;
    std::cout << "[ESC] - Exit" << std::endl;

    gameEngine.run();

    return 0;
}