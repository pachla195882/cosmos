#include "../include/Vector2.h"
#include <cmath>

Vector2::Vector2(float x, float y) : m_x(x), m_y(y) {};
Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(m_x - other.m_x, m_y - other.m_y);
}
Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(m_x + other.m_x, m_y + other.m_y);
}
Vector2 Vector2::operator*(float scalar) const {
    return Vector2(m_x * scalar, m_y * scalar);
}
float Vector2::magnitude() const { return std::sqrt(m_x * m_x + m_y * m_y); }

const float Vector2::getX() const {
    return m_x;
}

const float Vector2::getY() const {
    return m_y;
}