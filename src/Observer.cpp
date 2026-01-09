#include "Observer.h"
#include <cmath>

Observer::Observer() {
    center = glm::vec3(0.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    radius = 15.0f;
    theta = 0.7f;
    phi = 0.5f;
    updatePosition();
}

void Observer::updatePosition() {
    eye.x = center.x + radius * cos(phi) * sin(theta);
    eye.y = center.y + radius * sin(phi);
    eye.z = center.z + radius * cos(phi) * cos(theta);
}

void Observer::apply() {
    gluLookAt(eye.x, eye.y, eye.z,
              center.x, center.y, center.z,
              up.x, up.y, up.z);
}