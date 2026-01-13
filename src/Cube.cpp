#include "Cube.h"

float cube_v[] = {
    -1,-1,1, 1,-1,1, 1,1,1, -1,1,1,   
    -1,-1,-1, 1,-1,-1, 1,1,-1, -1,1,-1 
};

float cube_n[] = {
    0,0,1, 0,0,1, 0,0,1, 0,0,1,
    0,0,-1, 0,0,-1, 0,0,-1, 0,0,-1
};

float cube_uv[] = {
    0,0, 1,0, 1,1, 0,1,
    0,0, 1,0, 1,1, 0,1
};

unsigned char cube_i[] = {
    0,1,2, 2,3,0, 1,5,6, 6,2,1, 7,6,5, 5,4,7, 4,0,3, 3,7,4, 3,2,6, 6,7,3, 4,5,1, 1,0,4
};

void Cube::draw() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, cube_v);
    glNormalPointer(GL_FLOAT, 0, cube_n);
    glTexCoordPointer(2, GL_FLOAT, 0, cube_uv);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, cube_i);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}