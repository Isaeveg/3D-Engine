#include "Engine.h"
#include "Primitives.h"
#include "Cube.h"

Engine *Engine::instance = nullptr;

Engine::Engine()
    : windowWidth(800), windowHeight(600), windowTitle("ESHKERE Engine"),
      fps(60), currentProjection(PERSPECTIVE), windowHandle(0),
      firstMouse(true), lastX(400), lastY(300)
{

    clearColor[0] = 0.0f;
    clearColor[1] = 0.0f;
    clearColor[2] = 0.0f;
    clearColor[3] = 1.0f;

    for (int i = 0; i < 1024; i++)
        keys[i] = false;

    camera = new Camera(glm::vec3(0.0f, 0.0f, 15.0f));

    instance = this;
}

Engine::~Engine()
{
    delete camera;
}

void Engine::init(int argc, char **argv, int width, int height, const std::string &title)
{
    windowWidth = width;
    windowHeight = height;
    windowTitle = title;
    lastX = width / 2.0f;
    lastY = height / 2.0f;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    windowHandle = glutCreateWindow(windowTitle.c_str());

    glEnable(GL_DEPTH_TEST);

    // Захват курсора (чтобы он не вылетал из окна при вращении)
    glutSetCursor(GLUT_CURSOR_NONE);

    // Регистрация Callback-функций
    glutDisplayFunc(renderWrapper);
    glutReshapeFunc(reshapeWrapper);
    glutKeyboardFunc(keyboardWrapper);       // Нажатие
    glutKeyboardUpFunc(keyboardUpWrapper);   // Отпускание
    glutPassiveMotionFunc(mouseMoveWrapper); // Движение мыши без клика

    glutWarpPointer(windowWidth / 2, windowHeight / 2);
}

void Engine::run()
{
    glutTimerFunc(1000 / fps, updateWrapper, 0);
    glutMainLoop();
}

void Engine::setClearColor(float r, float g, float b, float a)
{
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
    glClearColor(r, g, b, a);
}
void Engine::setFPS(int value)
{
    if (value > 0)
        fps = value;
}
void Engine::setProjection(ProjectionType type)
{
    currentProjection = type;
    reshape(windowWidth, windowHeight);
}

// --- ЛОГИКА ВВОДА ---

void Engine::keyboard(unsigned char key, int x, int y)
{
    // Вывод кода нажатой клавиши в консоль для отладки
    std::cout << "Key pressed: " << key << " (Code: " << (int)key << ")" << std::endl;

    if (key >= 0 && key < 1024)
        keys[key] = true;

    if (key == 27)
        glutLeaveMainLoop();
    if (key == 'p' || key == 'P')
        setProjection(PERSPECTIVE);
    if (key == 'o' || key == 'O')
        setProjection(ORTHOGRAPHIC);
}

void Engine::keyboardUp(unsigned char key, int x, int y)
{
    if (key >= 0 && key < 1024)
        keys[key] = false; // Запоминаем, что клавиша отпущена
}

void Engine::mouseMove(int x, int y)
{
    // Находим центр окна
    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;

    // ВАЖНО: glutWarpPointer вызывает событие mouseMove.
    // Если мышь уже в центре, значит это наш же сброс - игнорируем его,
    // иначе камера будет дрожать или дрейфовать.
    if (x == centerX && y == centerY)
        return;

    // Считаем смещение относительно ЦЕНТРА окна
    float xoffset = x - centerX;
    float yoffset = centerY - y; // Инверсия Y (в оконных координатах Y растет вниз)

    // Передаем смещение в камеру
    camera->ProcessMouseMovement(xoffset, yoffset);

    // Возвращаем курсор принудительно в центр экрана
    glutWarpPointer(centerX, centerY);
}

void Engine::processInput()
{
    // Вызывается каждый кадр перед отрисовкой
    float velocity = camera->MovementSpeed;

    // WASD - Движение по горизонтали
    if (keys['w'] || keys['W'])
        camera->ProcessKeyboard(FORWARD, velocity);
    if (keys['s'] || keys['S'])
        camera->ProcessKeyboard(BACKWARD, velocity);
    if (keys['a'] || keys['A'])
        camera->ProcessKeyboard(LEFT, velocity);
    if (keys['d'] || keys['D'])
        camera->ProcessKeyboard(RIGHT, velocity);

    // SPACE - Полет вверх (вдоль оси Y или локального вектора Up)
    if (keys[' '])
        camera->ProcessKeyboard(UP, velocity);

    // C - Полет вниз (вместо Ctrl, так как GLUT плохо ловит удержание Ctrl)
    if (keys['c'] || keys['C'])
        camera->ProcessKeyboard(DOWN, velocity);
}

void Engine::update(int value)
{
    processInput(); // <--- Обрабатываем зажатые клавиши здесь

    glutPostRedisplay();
    glutTimerFunc(1000 / fps, updateWrapper, 0);
}

void Engine::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // Получаем матрицу вида от камеры
    glLoadMatrixf(glm::value_ptr(camera->GetViewMatrix()));

    // 1. Куб
    glPushMatrix();
    static float a = 0;
    a += 1.0f;
    glRotatef(a, 1, 1, 0);
    Cube::draw();
    glPopMatrix();

    // 2. Остальное
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-6, 0, 0);
    Primitives::drawTriangles();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(6, 0, 0);
    Primitives::drawPoints();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 5, 0);
    Primitives::drawLines();
    glPopMatrix();

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

void Engine::reshape(int w, int h)
{
    windowWidth = w;
    windowHeight = h;
    if (h == 0)
        h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glm::mat4 projection;
    if (currentProjection == ORTHOGRAPHIC)
    {
        float orthoSize = 10.0f;
        if (w >= h)
            projection = glm::ortho(-orthoSize * aspect, orthoSize * aspect, -orthoSize, orthoSize, 0.1f, 100.0f);
        else
            projection = glm::ortho(-orthoSize, orthoSize, -orthoSize / aspect, orthoSize / aspect, 0.1f, 100.0f);
    }
    else
    {
        projection = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 100.0f);
    }
    glLoadMatrixf(glm::value_ptr(projection));
    glMatrixMode(GL_MODELVIEW);
}

// Обертки
void Engine::renderWrapper()
{
    if (instance)
        instance->render();
}
void Engine::updateWrapper(int value)
{
    if (instance)
        instance->update(value);
}
void Engine::reshapeWrapper(int w, int h)
{
    if (instance)
        instance->reshape(w, h);
}
void Engine::keyboardWrapper(unsigned char key, int x, int y)
{
    if (instance)
        instance->keyboard(key, x, y);
}
void Engine::keyboardUpWrapper(unsigned char key, int x, int y)
{
    if (instance)
        instance->keyboardUp(key, x, y);
}
void Engine::mouseMoveWrapper(int x, int y)
{
    if (instance)
        instance->mouseMove(x, y);
}

void Engine::drawWireCube(double size) { glutWireCube(size); }
void Engine::drawWireTeapot(double size) { glutWireTeapot(size); }
