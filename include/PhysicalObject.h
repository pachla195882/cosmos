#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H

#include "Vector2.h"
#include "SDL3/SDL.h"
#include <vector>
#include <memory>
#include <string>

class PhysicalObject {
    public:
        virtual void update(float dt, 
            const std::vector<std::unique_ptr<PhysicalObject>>& objects) = 0;
        virtual void render(SDL_Renderer* renderer) const = 0;
        virtual Vector2 getPosition() const = 0;
        virtual float getMass() const = 0;
        virtual void setName(std::string name) = 0;
        virtual std::string getName() const = 0;
        virtual ~PhysicalObject() = default;

};

#endif //PHYSICALOBJECT_H