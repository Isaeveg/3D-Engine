#pragma once
#include <string>
#include <GL/freeglut.h>

// Obsługuje ładowanie i zarządzanie teksturami
class BitmapHandler {
private:
    GLuint textureID;
    int width, height, channels;
    unsigned char* data;

public:
    BitmapHandler(const std::string& filename);
    virtual ~BitmapHandler();
    
    // Metody do obsługi tekstury
    void bind(); 
    GLuint getTextureID() const { return textureID; }
};