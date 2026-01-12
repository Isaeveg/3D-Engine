#ifndef OBSERVER_H
#define OBSERVER_H

#include <glm/glm.hpp>
#include <GL/freeglut.h>

class Observer
{
public:
    glm::vec3 eye;    // Позиция камеры
    glm::vec3 center; // Точка, на которую смотрим
    glm::vec3 up;     // Вектор верха

    float radius; // Дистанция от центра
    float theta;  // Горизонтальный угол (вращение)
    float phi;    // Вертикальный угол (наклон)

    Observer();
    void updatePosition();
    void apply();
};

#endif