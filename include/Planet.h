#ifndef PLANET_H
#define PLANET_H

#include "PhysicalObject.h"
#include "SDL3/SDL.h"
#include <string>

class Planet : public PhysicalObject{
    private:
        std::string m_name;
        Vector2 m_pos;
        Vector2 m_vel;
        float m_mass;
        int m_radius;
        Uint8 m_r, m_g, m_b;

        void drawCircle(SDL_Renderer* renderer) const;

    public:
        Planet(std::string name, Vector2 pos, Vector2 vel, float mass, int radius, Uint8 r, Uint8 g, Uint8 b);
        void update(float dt,
            const std::vector<std::unique_ptr<PhysicalObject>>& objects) override;
        void render(SDL_Renderer* renderer) const override;
        Vector2 getPosition() const override;
        float getMass() const override;
        std::string getName() const override;
        void setName(std::string name) override;

};

#endif