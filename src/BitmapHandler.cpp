#include "BitmapHandler.h"
#include <iostream>
#include "stb_image.h" 

BitmapHandler::BitmapHandler(const std::string& filename) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(filename.c_str(), &width, &height, &channels, 0);

    if (data) {
        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        std::cout << "Texture loaded: " << filename << std::endl;
    } else {
        std::cout << "Failed to load texture: " << filename << std::endl;
    }
}

BitmapHandler::~BitmapHandler() {
    if (data) stbi_image_free(data);
    glDeleteTextures(1, &textureID);
}

void BitmapHandler::bind() {
    glBindTexture(GL_TEXTURE_2D, textureID);
}