#include "Pyramid.h"

float pyramid_v[] = {
    0,1,0, -1,-1,1, 1,-1,1,
    0,1,0, 1,-1,1, 1,-1,-1,
    0,1,0, 1,-1,-1, -1,-1,-1,
    0,1,0, -1,-1,-1, -1,-1,1,
    -1,-1, 1,   1,-1, 1,   1,-1,-1,
    1,-1,-1,  -1,-1,-1,  -1,-1, 1
};

float pyramid_uv[] = {
    0.5f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 
    0.5f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 
    0.5f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 
    0.5f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 
    0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,
    1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 0.0f
};

void Pyramid::draw() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, pyramid_v);
    glTexCoordPointer(2, GL_FLOAT, 0, pyramid_uv);

    glDrawArrays(GL_TRIANGLES, 0, 18);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}