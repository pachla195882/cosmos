#include "../include/Planet.h"
#include <cmath>

const float G = 0.1f; //gravitational constant

Planet::Planet(std::string name, Vector2 pos, Vector2 vel, float mass, int radius, Uint8 r, Uint8 g, Uint8 b)
: m_name(name), m_pos(pos), m_vel(vel), m_mass(mass), m_radius(radius), m_r(r), m_g(g), m_b(b) {}

void Planet::update(float dt, const std::vector<std::unique_ptr<PhysicalObject>>& objects){
    for (const auto& object : objects){
        if ( object.get() != this){
            Vector2 diff = object->getPosition() - m_pos;
            float distance = diff.magnitude();
            if (distance < 1.0f) distance = 1.0f;
            float force = G * m_mass * object->getMass() / (distance * distance);
            Vector2 direction = diff * (1.0f / distance);
            Vector2 gravity = direction * (force / m_mass);
            m_vel = m_vel + gravity * dt;
        }
    }
    m_pos = m_pos + m_vel * dt;
}

void Planet::render(SDL_Renderer* renderer) const { 
    SDL_SetRenderDrawColor(renderer, m_r, m_g, m_b, 255);
    drawCircle(renderer);
}

void Planet::drawCircle(SDL_Renderer* renderer) const {
    for(int x = - m_radius; x <= m_radius; x++){
        for(int y = - m_radius; y <= m_radius; y++){
            if ( x * x + y * y <= m_radius * m_radius) {
                SDL_RenderPoint(renderer, static_cast<int>(m_pos.getX()) + x, static_cast<int>(m_pos.getY()) + y);
            }
        }
    }
}

Vector2 Planet::getPosition() const { return m_pos; }

float Planet::getMass() const { return m_mass; }

void Planet::setName(std::string name) {
    this->m_name = name;
}

std::string Planet::getName() const {
    return m_name;
}