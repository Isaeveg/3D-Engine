#include "Cube.h"

// Упрощенный куб (8 вершин) + Индексы
float vert[] = { 
    -1,-1,1,  1,-1,1,  1,1,1,  -1,1,1, // Передняя грань
    -1,-1,-1, 1,-1,-1, 1,1,-1, -1,1,-1 // Задняя грань
};
// Цвета для вершин
float cols[] = {
    1,0,0, 0,1,0, 0,0,1, 1,1,0,
    1,0,1, 0,1,1, 1,1,1, 0,0,0
};
// Порядок соединения вершин (какие треугольники рисовать)
unsigned char ind[] = {
    0,1,2, 2,3,0, // Перед
    1,5,6, 6,2,1, // Право
    7,6,5, 5,4,7, // Зад
    4,0,3, 3,7,4, // Лево
    3,2,6, 6,7,3, // Верх
    4,5,1, 1,0,4  // Низ
};

void Cube::draw() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, vert);
    glColorPointer(3, GL_FLOAT, 0, cols);
    
    // Рисуем куб через индексы
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, ind);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}