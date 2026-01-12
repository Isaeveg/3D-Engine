#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

#include "Camera.h"
#include "Observer.h" // <--- Добавлено: нужно для использования класса Observer

enum ProjectionType
{
    ORTHOGRAPHIC,
    PERSPECTIVE
};

class Engine
{
private:
    int windowWidth;
    int windowHeight;
    std::string windowTitle;
    int windowHandle;
    int fps;

    ProjectionType currentProjection;
    float clearColor[4];

    Camera *camera;
    Observer observer;          // <--- Добавлено: поле observer, которое используется в cpp
    float rotationAngle = 0.0f; // <--- Добавлено: переменная для вращения объектов

    // --- Управление вводом ---
    bool keys[1024]; // Массив состояний клавиш (нажата/отпущена)

    // Для мыши
    bool firstMouse;
    float lastX, lastY;

    static Engine *instance;

    void render();
    void update(int value);
    void reshape(int w, int h);

    // Обработчики событий
    void keyboard(unsigned char key, int x, int y);
    void keyboardUp(unsigned char key, int x, int y); // Когда клавишу отпустили
    void mouseMove(int x, int y);                     // Движение мыши

    // Обработка логики движения (вызывается каждый кадр)
    void processInput();

    // Статические обертки
    static void renderWrapper();
    static void updateWrapper(int value);
    static void reshapeWrapper(int w, int h);
    static void keyboardWrapper(unsigned char key, int x, int y);
    static void keyboardUpWrapper(unsigned char key, int x, int y);
    static void mouseMoveWrapper(int x, int y);

public:
    Engine();
    ~Engine();

    static Engine &getInstance()
    {
        static Engine instance;
        return instance;
    }

    void init(int argc, char **argv, int width, int height, const std::string &title);
    void run();
    void setClearColor(float r, float g, float b, float a);
    void setFPS(int value);
    void setProjection(ProjectionType type);

    void drawWireCube(double size);
    void drawWireTeapot(double size);
};

#endif // <--- Добавлено: закрывающий endif