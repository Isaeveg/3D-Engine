#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Observer.h"
#include "Cube.h"

class Engine {
public:
    static Engine& getInstance();
    void Init(int argc, char* argv[], const std::string& title, int width, int height);
    void Start();
    void Display();
    void Reshape(int width, int height);
    void Keyboard(unsigned char key, int x, int y);
    void SpecialKeys(int key, int x, int y);

private:
    Engine();
    int width, height;
    Observer observer;
    float rotationAngle;

    static void DisplayWrapper();
    static void ReshapeWrapper(int w, int h);
    static void KeyboardWrapper(unsigned char k, int x, int y);
    static void SpecialKeysWrapper(int k, int x, int y);
};

#endif