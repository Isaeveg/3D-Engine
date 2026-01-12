#include "Observer.h"

Observer::Observer() : eye(0,2,15), center(0,0,0), up(0,1,0) {}

void Observer::apply() {
    gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
}