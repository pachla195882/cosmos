#include <iostream>
#include <SDL3/SDL.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

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

    bool running = true;
    SDL_Event event;

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT) running = false; 
        }

        //BACKGROUND
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //SUN
        SDL_SetRenderDrawColor(renderer, 255, 255, 0 , 255);
        drawCircle(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 50);

        //PLANET
        SDL_SetRenderDrawColor(renderer, 0, 0, 255 , 255);
        drawCircle(renderer, WINDOW_WIDTH / 2 + 150, WINDOW_HEIGHT / 2 - 100, 10);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}