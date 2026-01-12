#include "Primitives.h"

float pyramid_v[] = {
    0,1,0, -1,-1,1, 1,-1,1,  // Front
    0,1,0, 1,-1,1, 1,-1,-1,  // Right
    0,1,0, 1,-1,-1, -1,-1,-1, // Back
    0,1,0, -1,-1,-1, -1,-1,1  // Left
};

void Primitives::drawTriangles() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, pyramid_v);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glDisableClientState(GL_VERTEX_ARRAY);
}