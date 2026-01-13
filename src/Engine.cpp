#include "Engine.h"
#include "Cube.h"
#include "Primitives.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Engine* Engine::instance = nullptr;

Engine::Engine() : 
    windowWidth(1280), 
    windowHeight(720), 
    targetFPS(60), 
    selectedIdx(-1), 
    lightEnabled(true), 
    smoothShading(true) 
{
    camera = new Camera(glm::vec3(0.0f, 2.0f, 15.0f));
    for(int i=0; i<256; i++) { keys[i] = false; specialKeys[i] = false; }
    instance = this;
}

Engine::~Engine() { delete camera; }

void Engine::loadTexture() {
    glGenTextures(1, &crateTexture);
    glBindTexture(GL_TEXTURE_2D, crateTexture);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    
    // Пытаемся найти текстуру в разных папках
    unsigned char *data = stbi_load("assets/crate.jpg", &width, &height, &nrChannels, 0);
    if (!data) data = stbi_load("crate.jpg", &width, &height, &nrChannels, 0);
    
    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        std::cout << "Tekstura zaladowana!" << std::endl;
    } else {
        std::cout << "Blad: Nie znaleziono crate.jpg!" << std::endl;
    }
    stbi_image_free(data);
}

// РЕАЛИЗАЦИЯ ФУНКЦИИ, КОТОРОЙ НЕ ХВАТАЛО
void Engine::spawnObject(ShapeType type) {
    GameObject obj;
    obj.pos = camera->Position + camera->Front * 7.0f;
    obj.rot = glm::vec3(0.0f);
    obj.scale = 1.0f;
    obj.color = glm::vec3((rand()%100)/100.f, (rand()%100)/100.f, (rand()%100)/100.f);
    obj.type = type;
    obj.useTexture = (type == CUBE); 
    objects.push_back(obj);
    selectedIdx = (int)objects.size() - 1;
    std::cout << "Obiekt dodany. Typ: " << type << std::endl;
}

void Engine::keyboard(unsigned char key, int x, int y) {
    keys[key] = true; // Запоминаем нажатие для WASD
    
    if (key == 27) glutLeaveMainLoop(); // ESC

    // Управление светом и тенями
    if (key == 'l' || key == 'L') {
        lightEnabled = !lightEnabled;
        std::cout << "Swiatlo: " << (lightEnabled ? "ON" : "OFF") << std::endl;
    }
    if (key == 'k' || key == 'K') {
        smoothShading = !smoothShading;
        std::cout << "Cieniowanie: " << (smoothShading ? "SMOOTH" : "FLAT") << std::endl;
    }

    // Создание фигур
    if (key == '1') spawnObject(CUBE);
    if (key == '2') spawnObject(PYRAMID);
    if (key == '3') spawnObject(SPHERE);
    if (key == '4') spawnObject(TEAPOT);
    if (key == '5') spawnObject(TORUS);
    
    // TAB для переключения
    if (key == 9) {
        if (!objects.empty()) selectedIdx = (selectedIdx + 1) % objects.size();
    }

    // FPS
    if (key == ']') targetFPS += 5;
    if (key == '[') targetFPS = std::max(5, targetFPS - 5);
}

void Engine::keyboardUp(unsigned char key, int x, int y) {
    keys[key] = false; // Сбрасываем нажатие
}

void Engine::processInput() {
    float s = 0.15f; // Скорость камеры
    if (keys['w'] || keys['W']) camera->ProcessKeyboard(FORWARD, s);
    if (keys['s'] || keys['S']) camera->ProcessKeyboard(BACKWARD, s);
    if (keys['a'] || keys['A']) camera->ProcessKeyboard(LEFT, s);
    if (keys['d'] || keys['D']) camera->ProcessKeyboard(RIGHT, s);

    if (selectedIdx != -1) {
        float mS = 0.1f;
        // Векторы движения относительно взгляда
        glm::vec3 forward = glm::normalize(glm::vec3(camera->Front.x, 0, camera->Front.z));
        glm::vec3 right = camera->Right;

        if (specialKeys[GLUT_KEY_UP])    objects[selectedIdx].pos += forward * mS;
        if (specialKeys[GLUT_KEY_DOWN])  objects[selectedIdx].pos -= forward * mS;
        if (specialKeys[GLUT_KEY_LEFT])  objects[selectedIdx].pos -= right * mS;
        if (specialKeys[GLUT_KEY_RIGHT]) objects[selectedIdx].pos += right * mS;

        // Вращение R, T, Y
        if (keys['r'] || keys['R']) objects[selectedIdx].rot.y += 2.0f;
        if (keys['t'] || keys['T']) objects[selectedIdx].rot.x += 2.0f;
        if (keys['y'] || keys['Y']) objects[selectedIdx].rot.z += 2.0f;

        // Масштаб
        if (keys['+'] || keys['=']) objects[selectedIdx].scale += 0.05f;
        if (keys['-'] || keys['_']) objects[selectedIdx].scale -= 0.05f;
    }
}

void Engine::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (lightEnabled) glEnable(GL_LIGHTING); else glDisable(GL_LIGHTING);
    glShadeModel(smoothShading ? GL_SMOOTH : GL_FLAT);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(camera->GetViewMatrix()));

    GLfloat lp[] = { 0.0f, 10.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lp);

    for (int i = 0; i < (int)objects.size(); ++i) {
        glPushMatrix();
        glTranslatef(objects[i].pos.x, objects[i].pos.y, objects[i].pos.z);
        glRotatef(objects[i].rot.x, 1, 0, 0);
        glRotatef(objects[i].rot.y, 0, 1, 0);
        glRotatef(objects[i].rot.z, 0, 0, 1);
        glScalef(objects[i].scale, objects[i].scale, objects[i].scale);
        
        if (i == selectedIdx) glColor3f(1.0f, 1.0f, 1.0f);
        else glColor3f(objects[i].color.r, objects[i].color.g, objects[i].color.b);
        
        if (objects[i].useTexture) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, crateTexture);
            Cube::draw();
            glDisable(GL_TEXTURE_2D);
        } else {
            switch(objects[i].type) {
                case CUBE: Cube::draw(); break;
                case PYRAMID: Primitives::drawTriangles(); break;
                case SPHERE: glutSolidSphere(1.0, 30, 30); break;
                case TEAPOT: glutSolidTeapot(1.0); break;
                case TORUS: glutSolidTorus(0.3, 0.7, 20, 20); break;
            }
        }
        glPopMatrix();
    }
    drawInterface();
    glutSwapBuffers();
}

void Engine::init(int argc, char** argv, int w, int h, const std::string& title) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w, h);
    glutCreateWindow(title.c_str());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    loadTexture();

    glutDisplayFunc(renderWrapper);
    glutReshapeFunc(reshapeWrapper);
    glutKeyboardFunc(kbWrapper);
    glutKeyboardUpFunc(kbUpWrapper);
    glutSpecialFunc(specWrapper);
    glutSpecialUpFunc(specUpWrapper);
    glutPassiveMotionFunc(mouseWrapper);
    glutSetCursor(GLUT_CURSOR_NONE);
}

void Engine::update(int v) {
    processInput();
    glutPostRedisplay();
    glutTimerFunc(1000 / targetFPS, updateWrapper, 0);
}

void Engine::drawInterface() {
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    glColor3f(1, 1, 1);
    glRasterPos2i(10, windowHeight - 20);
    std::string s = "FPS: " + std::to_string(targetFPS) + " | Obiekt: " + (selectedIdx == -1 ? "None" : std::to_string(selectedIdx));
    for (char c : s) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    glPopMatrix(); glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW);
    if(lightEnabled) glEnable(GL_LIGHTING);
}

void Engine::run() { glutTimerFunc(1000/targetFPS, updateWrapper, 0); glutMainLoop(); }
void Engine::renderWrapper() { instance->render(); }
void Engine::updateWrapper(int v) { instance->update(v); }
void Engine::reshapeWrapper(int w, int h) { instance->reshape(w, h); }
void Engine::kbWrapper(unsigned char k, int x, int y) { instance->keyboard(k,x,y); }
void Engine::kbUpWrapper(unsigned char k, int x, int y) { instance->keyboardUp(k,x,y); }
void Engine::specWrapper(int k, int x, int y) { instance->specialKeys[k]=true; }
void Engine::specUpWrapper(int k, int x, int y) { instance->specialKeys[k]=false; }
void Engine::mouseWrapper(int x, int y) {
    int cx = glutGet(GLUT_WINDOW_WIDTH)/2, cy = glutGet(GLUT_WINDOW_HEIGHT)/2;
    if(x==cx && y==cy) return;
    instance->camera->ProcessMouseMovement(x-cx, cy-y);
    glutWarpPointer(cx, cy);
}
void Engine::reshape(int w, int h) {
    windowWidth = w; windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45.0, (double)w/h, 0.1, 1000.0);
}