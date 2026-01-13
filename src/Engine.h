#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <string>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Camera.h"

enum ShapeType { CUBE, PYRAMID, SPHERE, TEAPOT, TORUS };

struct GameObject {
    glm::vec3 pos;
    glm::vec3 rot;
    float scale;
    glm::vec3 color;
    ShapeType type;
    bool useTexture;
};

class Engine {
private:
    int windowWidth, windowHeight;
    int targetFPS;
    bool keys[256], specialKeys[256];
    Camera* camera;
    std::vector<GameObject> objects;
    int selectedIdx;
    
    bool lightEnabled;
    bool smoothShading;
    GLuint crateTexture;

    static Engine* instance;

    void render();
    void update(int value);
    void reshape(int w, int h);
    void processInput();
    void loadTexture();
    void drawInterface();

    void keyboard(unsigned char key, int x, int y);
    void keyboardUp(unsigned char key, int x, int y);
    void specialFunc(int key, int x, int y);
    void specialUpFunc(int key, int x, int y);
    void mouseMove(int x, int y);

public:
    Engine();
    ~Engine();
    static Engine& getInstance() { static Engine inst; return inst; }

    void init(int argc, char** argv, int w, int h, const std::string& title);
    void run();
    void spawnObject(ShapeType type);

    static void renderWrapper();
    static void updateWrapper(int v);
    static void reshapeWrapper(int w, int h);
    static void kbWrapper(unsigned char k, int x, int y);
    static void kbUpWrapper(unsigned char k, int x, int y);
    static void specWrapper(int k, int x, int y);
    static void specUpWrapper(int k, int x, int y);
    static void mouseWrapper(int x, int y);
};

#endif