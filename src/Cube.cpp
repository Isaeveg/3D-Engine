#include "Cube.h"

float vert[] = {
    -1, -1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1,    // Передняя грань
    -1, -1, -1, 1, -1, -1, 1, 1, -1, -1, 1, -1 // Задняя грань
};

float cols[] = {
    1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0,
    1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0};

unsigned char ind[] = {
    0, 1, 2, 2, 3, 0,
    1, 5, 6, 6, 2, 1,
    7, 6, 5, 5, 4, 7,
    4, 0, 3, 3, 7, 4,
    3, 2, 6, 6, 7, 3,
    4, 5, 1, 1, 0, 4};

void Cube::draw()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vert);
    glColorPointer(3, GL_FLOAT, 0, cols);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, ind);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}