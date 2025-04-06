#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

class Vector2{
    private:
        float m_x, m_y;
    public:
    Vector2(float x = 0, float y = 0);
    Vector2 operator-(const Vector2 &other) const;
    Vector2 operator+(const Vector2 &other) const;
    Vector2 operator*(float scalar) const;
    float magnitude() const;
    const float getX() const;
    const float getY() const;

};

#endif