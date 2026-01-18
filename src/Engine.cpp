#include "Engine.h"
#include "Cube.h"
#include "Pyramid.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void CubeObject::drawGeometry() {
    Cube::draw(); 
}

void PyramidObject::drawGeometry() {
    Pyramid::draw();
}

void SphereObject::drawGeometry() {
    glutSolidSphere(1.0, 30, 30);
}

void TeapotObject::drawGeometry() {
    glutSolidTeapot(1.0);
}

void TorusObject::drawGeometry() {
    glutSolidTorus(0.3, 0.7, 20, 20);
}

Engine* Engine::instance = nullptr;

Engine::Engine() : 
    windowWidth(1280), windowHeight(720), targetFPS(60), selectedIdx(-1), 
    lightEnabled(true), smoothShading(true), textureCrate(nullptr), textureWall(nullptr)
{
    camera = new Camera(glm::vec3(0.0f, 2.0f, 15.0f));
    for(int i=0; i<256; i++) { keys[i] = false; specialKeys[i] = false; }
    instance = this;
}

Engine::~Engine() { 
    delete camera; 
    delete textureCrate;
    delete textureWall;
    for(auto obj : objects) delete obj;
    objects.clear();
}

void Engine::loadTexture() {
    std::cout << "Loading textures..." << std::endl;
    textureCrate = new BitmapHandler("assets/crate.jpg");
    textureWall = new BitmapHandler("assets/wall.jpg");  
}

void Engine::spawnCube() {
    CubeObject* obj = new CubeObject(textureCrate);
    obj->pos = camera->Position + camera->Front * 5.0f;
    objects.push_back(obj);
    selectedIdx = (int)objects.size() - 1;
}

void Engine::spawnPyramid() {
    PyramidObject* obj = new PyramidObject(textureWall);
    obj->pos = camera->Position + camera->Front * 5.0f;
    objects.push_back(obj);
    selectedIdx = (int)objects.size() - 1;
}

void Engine::spawnSphere() {
    SphereObject* obj = new SphereObject();
    obj->pos = camera->Position + camera->Front * 5.0f;
    obj->color = glm::vec3((rand()%100)/100.f, (rand()%100)/100.f, (rand()%100)/100.f);
    objects.push_back(obj);
    selectedIdx = (int)objects.size() - 1;
}

void Engine::spawnTeapot() {
    TeapotObject* obj = new TeapotObject();
    obj->pos = camera->Position + camera->Front * 5.0f;
    obj->color = glm::vec3((rand()%100)/100.f, (rand()%100)/100.f, (rand()%100)/100.f);
    objects.push_back(obj);
    selectedIdx = (int)objects.size() - 1;
}

void Engine::spawnTorus() {
    TorusObject* obj = new TorusObject();
    obj->pos = camera->Position + camera->Front * 5.0f;
    obj->color = glm::vec3((rand()%100)/100.f, (rand()%100)/100.f, (rand()%100)/100.f);
    objects.push_back(obj);
    selectedIdx = (int)objects.size() - 1;
}

void Engine::keyboard(unsigned char key, int x, int y) {
    keys[key] = true;
    if (key == 27) glutLeaveMainLoop(); 

    if (key == 'l' || key == 'L') lightEnabled = !lightEnabled;
    if (key == 'k' || key == 'K') smoothShading = !smoothShading;

    if (key == '1') spawnCube();
    if (key == '2') spawnPyramid();
    if (key == '3') spawnSphere();
    if (key == '4') spawnTeapot();
    if (key == '5') spawnTorus();
    
    if (key == 9) { 
        if (!objects.empty()) selectedIdx = (selectedIdx + 1) % objects.size();
    }

    if (key == ']') targetFPS += 5;
    if (key == '[') targetFPS = std::max(5, targetFPS - 5);

    if (key == 127) { 
        if (!objects.empty() && selectedIdx != -1) {
            
            delete objects[selectedIdx];
            objects.erase(objects.begin() + selectedIdx);
            
            std::cout << "Obiekt usuniety (Deleted)" << std::endl;

            if (objects.empty()) {
                selectedIdx = -1;
            } else {
                if (selectedIdx >= objects.size()) {
                    selectedIdx = (int)objects.size() - 1;
                }
            }
        }
    }
}

void Engine::keyboardUp(unsigned char key, int x, int y) {
    keys[key] = false;
}

void Engine::specialFunc(int key, int x, int y) { specialKeys[key] = true; }
void Engine::specialUpFunc(int key, int x, int y) { specialKeys[key] = false; }

void Engine::processInput() {
    float camSpeed = 0.15f; 
    if (keys['w'] || keys['W']) camera->ProcessKeyboard(FORWARD, camSpeed);
    if (keys['s'] || keys['S']) camera->ProcessKeyboard(BACKWARD, camSpeed);
    if (keys['a'] || keys['A']) camera->ProcessKeyboard(LEFT, camSpeed);
    if (keys['d'] || keys['D']) camera->ProcessKeyboard(RIGHT, camSpeed);

    if (selectedIdx != -1 && selectedIdx < objects.size()) {
        float objSpeed = 0.1f;
        GameObject* obj = objects[selectedIdx];
        
        glm::vec3 forward = glm::normalize(glm::vec3(camera->Front.x, 0, camera->Front.z));
        glm::vec3 right = camera->Right;

        if (specialKeys[GLUT_KEY_UP])    obj->pos += forward * objSpeed;
        if (specialKeys[GLUT_KEY_DOWN])  obj->pos -= forward * objSpeed;
        if (specialKeys[GLUT_KEY_LEFT])  obj->pos -= right * objSpeed;
        if (specialKeys[GLUT_KEY_RIGHT]) obj->pos += right * objSpeed;

        if (keys[32])                obj->pos.y += objSpeed; 
        if (keys['c'] || keys['C'])  obj->pos.y -= objSpeed; 

        if (keys['r'] || keys['R']) obj->rot.y += 2.0f;
        if (keys['t'] || keys['T']) obj->rot.x += 2.0f;
        if (keys['y'] || keys['Y']) obj->rot.z += 2.0f;

        if (keys['+'] || keys['=']) obj->scale += 0.05f;
        if (keys['-'] || keys['_']) obj->scale -= 0.05f;
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

    for (int i = 0; i < objects.size(); ++i) {
        glPushMatrix();
        GameObject* obj = objects[i];

        glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
        glRotatef(obj->rot.x, 1, 0, 0);
        glRotatef(obj->rot.y, 0, 1, 0);
        glRotatef(obj->rot.z, 0, 0, 1);
        glScalef(obj->scale, obj->scale, obj->scale);
        
        glColor3f(obj->color.r, obj->color.g, obj->color.b);
        obj->draw(); 
        
        if (i == selectedIdx) {
            glDisable(GL_LIGHTING);     
            glDisable(GL_TEXTURE_2D);   
            glEnable(GL_BLEND);         
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            glColor4f(1.0f, 1.0f, 1.0f, 0.25f); 
            
            glDepthFunc(GL_LEQUAL); 
            
            obj->drawGeometry();
            
            glDepthFunc(GL_LESS);
            glDisable(GL_BLEND);
            if (lightEnabled) glEnable(GL_LIGHTING);
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
    std::string s = "FPS: " + std::to_string(targetFPS) + 
                    " | Objects: " + std::to_string(objects.size()) + 
                    " | Sel: " + (selectedIdx == -1 ? "None" : std::to_string(selectedIdx));
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
void Engine::specWrapper(int k, int x, int y) { instance->specialFunc(k,x,y); }
void Engine::specUpWrapper(int k, int x, int y) { instance->specialUpFunc(k,x,y); }
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