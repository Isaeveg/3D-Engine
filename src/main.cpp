#include "Engine.h"

int main(int argc, char* argv[]) {
    Engine& engine = Engine::getInstance();
    engine.Init(argc, argv, "3D Fly Engine - Lab 9", 1280, 720);
    engine.Start();
    return 0;
}