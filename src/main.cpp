#include "Engine.h"

int main(int argc, char *argv[])
{
    Engine &engine = Engine::getInstance();
    engine.init(argc, argv, 1280, 720, "3D Engine");
    engine.run();

    return 0;
}