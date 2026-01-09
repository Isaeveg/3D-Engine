#include "Engine.h"

Engine::Engine() : rotationAngle(0.0f), width(1280), height(720) {}

Engine& Engine::getInstance() {
    static Engine instance;
    return instance;
}

void Engine::Init(int argc, char* argv[], const std::string& title, int width, int height) {
    this->width = width;
    this->height = height;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow(title.c_str());
    
    glutDisplayFunc(DisplayWrapper);
    glutReshapeFunc(ReshapeWrapper);
    glutKeyboardFunc(KeyboardWrapper);
    glutSpecialFunc(SpecialKeysWrapper);

    glClearColor(0.02f, 0.02f, 0.05f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void Engine::Start() {
    glutMainLoop();
}

void Engine::Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    observer.apply();

    // Задание 2 & 3: Три объекта с трансформациями GLM
    glm::mat4 base = glm::mat4(1.0f);

    // 1. Зеленый куб (Вращение + Перемещение)
    glm::mat4 m1 = glm::rotate(base, glm::radians(rotationAngle), glm::vec3(0, 1, 0));
    m1 = glm::translate(m1, glm::vec3(5.0f, 0, 0));
    glLoadMatrixf(glm::value_ptr(m1));
    glColor3f(0.0f, 1.0f, 0.5f);
    glutSolidCube(1.2f);

    // 2. Желтый чайник (Вращение + Перемещение + Собственное вращение)
    glm::mat4 m2 = glm::rotate(base, glm::radians(rotationAngle + 120.0f), glm::vec3(0, 1, 0));
    m2 = glm::translate(m2, glm::vec3(5.0f, 2.0f * sin(rotationAngle * 0.05f), 0));
    m2 = glm::rotate(m2, glm::radians(rotationAngle * 2.0f), glm::vec3(1, 1, 0));
    glLoadMatrixf(glm::value_ptr(m2));
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidTeapot(1.0f);

    // 3. Синяя сфера (Вращение + Перемещение + Масштабирование)
    glm::mat4 m3 = glm::rotate(base, glm::radians(rotationAngle + 240.0f), glm::vec3(0, 1, 0));
    m3 = glm::translate(m3, glm::vec3(5.0f, 0, 0));
    float scale = 0.8f + 0.4f * sin(rotationAngle * 0.1f);
    m3 = glm::scale(m3, glm::vec3(scale));
    glLoadMatrixf(glm::value_ptr(m3));
    glColor3f(0.2f, 0.5f, 1.0f);
    glutSolidSphere(1.0f, 20, 20);

    rotationAngle += 0.5f;
    glutSwapBuffers();
    glutPostRedisplay();
}

void Engine::Reshape(int width, int height) {
    this->width = width; this->height = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)width/height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void Engine::Keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': observer.radius -= 0.5f; break; // Приближение
        case 's': observer.radius += 0.5f; break; // Отдаление
        case 'a': observer.theta -= 0.05f; break; // Поворот влево
        case 'd': observer.theta += 0.05f; break; // Поворот вправо
        case 'q': observer.phi += 0.05f; break;   // Наклон вверх
        case 'e': observer.phi -= 0.05f; break;   // Наклон вниз
        case 27: exit(0); break;
    }
    if (observer.radius < 2.0f) observer.radius = 2.0f;
    observer.updatePosition();
}

void Engine::SpecialKeys(int key, int x, int y) {
    float moveStep = 0.5f;
    // Стрелки позволяют "летать" - смещать точку, куда мы смотрим
    switch (key) {
        case GLUT_KEY_UP:    observer.center.y += moveStep; break;
        case GLUT_KEY_DOWN:  observer.center.y -= moveStep; break;
        case GLUT_KEY_LEFT:  observer.center.x -= moveStep; break;
        case GLUT_KEY_RIGHT: observer.center.x += moveStep; break;
    }
    observer.updatePosition();
}

void Engine::DisplayWrapper() { getInstance().Display(); }
void Engine::ReshapeWrapper(int w, int h) { getInstance().Reshape(w, h); }
void Engine::KeyboardWrapper(unsigned char k, int x, int y) { getInstance().Keyboard(k, x, y); }
void Engine::SpecialKeysWrapper(int k, int x, int y) { getInstance().SpecialKeys(k, x, y); }