#include <iostream>
#include <cmath>
#include <vector>
#include <SDL3/SDL.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float G = 0.1f;

struct Vector2 {
    float m_x,m_y;
    Vector2(float x = 0, float y = 0): m_x(x), m_y(y) {}
    Vector2 operator-(const Vector2& other) const {
        return Vector2(m_x - other.m_x, m_y - other.m_y);
    }
    Vector2 operator+(const Vector2& other) const {
        return Vector2(m_x + other.m_x, m_y + other.m_y);
    }
    Vector2 operator*(float scalar) const {
        return Vector2(m_x * scalar, m_y * scalar);
    }
};

struct Planet {
    Vector2 m_pos;
    Vector2 m_vel;
    float m_mass;
    int m_radius;
    Uint8 r, g, b;
};

Vector2 calculateGravity(const Planet& planet, const Planet& sun){
    Vector2 diff = sun.m_pos - planet.m_pos;
    float distance = std::sqrt(diff.m_x * diff.m_x + diff.m_y * diff.m_y);
    if (distance < 1.0f) distance = 1.0f; // avoid divide by 0
    float force = G * planet.m_mass * sun.m_mass / (distance * distance);
    Vector2 direction = diff * (1.0f / distance); // normalization
    return direction * (force / planet.m_mass); // a = F/m
}

void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius){
    for(int x = -radius; x <= radius; x++){
        for(int y = -radius; y <= radius; y++){
            if ( x*x + y*y <= radius*radius) {
                SDL_RenderPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}

int main(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "SDL_Init failed!" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("COSMOS", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    if(!window){
        std::cerr << "Creating window failed! " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if(!renderer){
        std::cerr << "Creating renderer failed! " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Planet sun
    {
        {WINDOW_WIDTH/2, WINDOW_HEIGHT/2},
        {0,0},
        2000.0f,
        50, 
        255, 255, 0
    };
    
    Planet earth
    {
        {WINDOW_WIDTH/2+200, WINDOW_HEIGHT/2},
        {0, 1.0f}, 
        1.0f, 
        20, 
        0, 0, 255
    };

    Planet mars
    {
        {WINDOW_WIDTH/2+270, WINDOW_HEIGHT/2}, 
        {0, 0.8f}, 
        0.5f, 
        15, 
        255, 0, 0
    };

    std::vector<Planet> planets{earth, mars};

    bool running = true;
    SDL_Event event;
    const float dt = 0.1f; //time derivative


    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT) running = false; 
        }

        //BACKGROUND
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //SUN
        SDL_SetRenderDrawColor(renderer, sun.r, sun.g, sun.b , 255);
        drawCircle(renderer, static_cast<int>(sun.m_pos.m_x), static_cast<int>(sun.m_pos.m_y), sun.m_radius);

        for (auto& planet : planets){
            Vector2 gravity = calculateGravity(planet, sun);
            planet.m_vel = planet.m_vel + gravity * dt; // speed update
            planet.m_pos = planet.m_pos + planet.m_vel * dt; // position update

            SDL_SetRenderDrawColor(renderer, planet.r, planet.g, planet.b, 255);
            drawCircle(renderer, static_cast<int>(planet.m_pos.m_x), static_cast<int>(planet.m_pos.m_y), planet.m_radius);
        }
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}