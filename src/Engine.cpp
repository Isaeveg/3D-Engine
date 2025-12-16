#include "Engine.h"

// Инициализация статического указателя
Engine* Engine::instance = nullptr;

Engine::Engine() 
    : windowWidth(800), windowHeight(600), windowTitle("OpenGL Lab 07"), 
      fps(60), currentProjection(PERSPECTIVE), windowHandle(0) {
    
    // Цвет фона по умолчанию (черный)
    clearColor[0] = 0.0f; clearColor[1] = 0.0f; clearColor[2] = 0.0f; clearColor[3] = 1.0f;
    instance = this;
}

Engine::~Engine() {
    // Деинициализация (если требуется специфическая очистка) [cite: 166]
}

void Engine::init(int argc, char** argv, int width, int height, const std::string& title) {
    windowWidth = width;
    windowHeight = height;
    windowTitle = title;

    // Инициализация GLUT [cite: 59, 60]
    glutInit(&argc, argv);
    
    // Режим отображения: Двойная буферизация, Цвета RGB, Буфер глубины [cite: 61]
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // Размер и создание окна [cite: 62, 63]
    glutInitWindowSize(windowWidth, windowHeight);
    windowHandle = glutCreateWindow(windowTitle.c_str());

    // Включение теста глубины (Z-buffer) [cite: 161]
    glEnable(GL_DEPTH_TEST);

    // Регистрация Callback-функций [cite: 66, 67, 71]
    glutDisplayFunc(renderWrapper);
    glutReshapeFunc(reshapeWrapper);
    glutKeyboardFunc(keyboardWrapper);
}

void Engine::run() {
    // Запуск таймера для контроля FPS [cite: 162]
    glutTimerFunc(1000 / fps, updateWrapper, 0);
    // Запуск главного цикла [cite: 64]
    glutMainLoop();
}

void Engine::setClearColor(float r, float g, float b, float a) {
    clearColor[0] = r; clearColor[1] = g; clearColor[2] = b; clearColor[3] = a;
    // Настройка цвета очистки 
    glClearColor(r, g, b, a);
}

void Engine::setFPS(int value) {
    if (value > 0) fps = value;
}

void Engine::setProjection(ProjectionType type) {
    currentProjection = type;
    // Принудительно вызываем reshape для пересчета матрицы проекции
    reshape(windowWidth, windowHeight); 
}

// --- Обработка логики (Реализация) ---

void Engine::render() {
    // Очистка буферов цвета и глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Установка матрицы модели-вида (Camera View)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Сдвигаем камеру назад, чтобы видеть объекты
    glTranslatef(0.0f, 0.0f, -5.0f);
    
    // Небольшое вращение для наглядности 3D
    static float angle = 0.0f;
    angle += 1.0f;
    glRotatef(angle, 1.0f, 1.0f, 0.0f);

    // Рисуем объекты (Задание 7)
    glColor3f(1.0f, 1.0f, 1.0f); // Белый цвет
    drawWireTeapot(1.0);

    // Смена буферов [cite: 75]
    glutSwapBuffers();
}

void Engine::reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    if (h == 0) h = 1; // Предотвращение деления на 0
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    
    // Работа с матрицей проекции [cite: 88]
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Использование GLM не обязательно для старого конвейера (glOrtho/gluPerspective),
    // но инструкция просит использовать GLM[cite: 86, 97, 115].
    // Здесь мы загружаем матрицу, созданную GLM, в OpenGL.

    glm::mat4 projection;
    
    if (currentProjection == ORTHOGRAPHIC) {
        //  glm::ortho
        float orthoSize = 3.0f;
        // Поддерживаем пропорции экрана в ортогональной проекции
        if (w >= h) {
            projection = glm::ortho(-orthoSize * aspect, orthoSize * aspect, -orthoSize, orthoSize, 0.1f, 100.0f);
        } else {
            projection = glm::ortho(-orthoSize, orthoSize, -orthoSize / aspect, orthoSize / aspect, 0.1f, 100.0f);
        }
    } else {
        //  glm::perspective
        // FOV = 60 градусов, zNear = 0.1, zFar = 100.0 [cite: 118, 120]
        projection = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 100.0f);
    }

    // Загрузка матрицы GLM в OpenGL (Legacy mode)
    glLoadMatrixf(glm::value_ptr(projection));
    
    glMatrixMode(GL_MODELVIEW);
}

void Engine::update(int value) {
    // Запрос на перерисовку кадра [cite: 73]
    glutPostRedisplay();
    // Перезапуск таймера
    glutTimerFunc(1000 / fps, updateWrapper, 0);
}

void Engine::keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: 
        glutLeaveMainLoop(); 
        break;
    case 'p':
    case 'P':
        std::cout << "Switching to Perspective Projection" << std::endl;
        setProjection(PERSPECTIVE); // 
        break;
    case 'o':
    case 'O':
        std::cout << "Switching to Orthogonal Projection" << std::endl;
        setProjection(ORTHOGRAPHIC); // 
        break;
    }
}

// Обертки для FreeGLUT (Static wrappers)

void Engine::renderWrapper() {
    if (instance) instance->render();
}
void Engine::updateWrapper(int value) {
    if (instance) instance->update(value);
}
void Engine::reshapeWrapper(int w, int h) {
    if (instance) instance->reshape(w, h);
}
void Engine::keyboardWrapper(unsigned char key, int x, int y) {
    if (instance) instance->keyboard(key, x, y);
}



void Engine::drawWireCube(double size) {
    glutWireCube(size);
}

void Engine::drawWireTeapot(double size) {
    glutWireTeapot(size);
}