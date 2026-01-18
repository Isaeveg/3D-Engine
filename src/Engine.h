#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <string>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Camera.h"
#include "BitmapHandler.h"

class GameObject {
public:
    glm::vec3 pos;
    glm::vec3 rot;
    float scale;
    glm::vec3 color;
    
    GameObject() : pos(0), rot(0), scale(1.0f), color(1) {}
    virtual ~GameObject() {}
  
    virtual void draw() {
        drawGeometry();
    }
    virtual void drawGeometry() = 0; 
};

class TexturedObject : public GameObject {
protected:
    BitmapHandler* texture;
public:
    TexturedObject(BitmapHandler* tex) : texture(tex) {}
    
    void draw() override {
        if(texture) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
            glColor3f(1,1,1); 
        }
        
        drawGeometry(); 
        
        if(texture) {
            glDisable(GL_TEXTURE_2D);
        }
    }
};

class CubeObject : public TexturedObject {
public:
    CubeObject(BitmapHandler* tex) : TexturedObject(tex) {}
    void drawGeometry() override; 
};

class PyramidObject : public TexturedObject {
public:
    PyramidObject(BitmapHandler* tex) : TexturedObject(tex) {}
    void drawGeometry() override; 
};

class SphereObject : public GameObject {
public:
    void drawGeometry() override;
};

class TeapotObject : public GameObject {
public:
    void drawGeometry() override;
};

class TorusObject : public GameObject {
public:
    void drawGeometry() override;
};

class Engine {
private:
    int windowWidth, windowHeight;
    int targetFPS;
    bool keys[256], specialKeys[256];
    Camera* camera;
    
    std::vector<GameObject*> objects;
    int selectedIdx;
    
    bool lightEnabled;
    bool smoothShading;
   
    BitmapHandler* textureCrate;
    BitmapHandler* textureWall;

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

    // Tworzenie obiektów
    void spawnCube();
    void spawnPyramid();
    void spawnSphere();
    void spawnTeapot();
    void spawnTorus();

    // Wrapper functions dla FreeGLUT callbacks
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