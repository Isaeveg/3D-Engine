#pragma once
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

// Типы проекций согласно лекции
enum ProjectionType {
    ORTHOGRAPHIC,
    PERSPECTIVE
};

class Engine {
private:
    // Параметры окна
    int windowWidth;
    int windowHeight;
    std::string windowTitle;
    int windowHandle;

    // Параметры движка
    int fps;
    ProjectionType currentProjection;
    
    // Цвета очистки экрана
    float clearColor[4];

    // Статический указатель для callback-функций GLUT (т.к. GLUT написан на C)
    static Engine* instance;

    // Внутренние методы для обработки событий
    void render();
    void update(int value);
    void reshape(int w, int h);
    void keyboard(unsigned char key, int x, int y);

    // Статические обертки (Wrappers) для GLUT
    static void renderWrapper();
    static void updateWrapper(int value);
    static void reshapeWrapper(int w, int h);
    static void keyboardWrapper(unsigned char key, int x, int y);

public:
    Engine();
    ~Engine();

    // Инициализация системы [cite: 159]
    void init(int argc, char** argv, int width, int height, const std::string& title);

    // Главный цикл [cite: 162]
    void run();

    // Настройка параметров [cite: 160, 161]
    void setClearColor(float r, float g, float b, float a);
    void setFPS(int value);
    
    // Переключение проекции 
    void setProjection(ProjectionType type);

    // Задание 7: Обертки для рисования объектов FreeGLUT [cite: 167]
    void drawWireCube(double size);
    void drawWireTeapot(double size);
};