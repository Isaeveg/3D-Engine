#include "Primitives.h"

// Данные вершин (из инструкции)
float PointVert[] = { -4,0,0,  0,4,0,  5,1,0,  0,0,0 };
float LineVert[]  = { -4,0,0,  0,4,0,  5,1,0,  0,0,0 }; // Две линии
float TriVert[]   = { -4,0,0, 0,4,0, -1,1,0,   5,1,0, 2,4,0, 0,0,0 }; // Два треугольника

void Primitives::drawPoints() {
    glEnable(GL_POINT_SMOOTH); glPointSize(10.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, PointVert);
    glDrawArrays(GL_POINTS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Primitives::drawLines() {
    glLineWidth(3.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, LineVert);
    glDrawArrays(GL_LINES, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Primitives::drawTriangles() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, TriVert);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableClientState(GL_VERTEX_ARRAY);
}