#include <iostream>
#include <memory>
#include "include/Planet.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 1024;

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

    std::vector<std::unique_ptr<PhysicalObject>> objects;

    objects.push_back(std::make_unique<Planet>("Sun",
        Vector2{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}, Vector2{0,0}, 1300.0f, 50, 255, 255, 0)); 

        objects.push_back(std::make_unique<Planet>("Earth",
            Vector2{WINDOW_WIDTH / 2 + 180, WINDOW_HEIGHT / 2}, Vector2{0,1.0f}, 1.0f, 5, 0, 0, 255)); 

        objects.push_back(std::make_unique<Planet>("Mars",
            Vector2{WINDOW_WIDTH / 2 + 220, WINDOW_HEIGHT / 2}, Vector2{0,0.9f}, 0.9f, 4, 255, 50, 0)); 

        objects.push_back(std::make_unique<Planet>("Comet",
            Vector2{WINDOW_WIDTH / 2 + 400, WINDOW_HEIGHT / 2}, Vector2{0,0.5f}, 10.0f, 2, 255, 0, 255)); 

    bool running = true;
    SDL_Event event;
    float dt = 0.1f; //time derivative


    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT) running = false; 
        }

        //BACKGROUND
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (auto& object : objects){
            object->update(dt, objects);
            object->render(renderer);
        }
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}