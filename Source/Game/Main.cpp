#include "Math/Math.h"
#include "Core/Random.h"
#include <random>
#include <SDL3/SDL.h>
#include <iostream>

int r[3000];
int g[3000];
int b[3000];
float posx1[3000];
float posx2[1000];
float posy1[3000];
float posy2[1000];
int getRandomNumber(int maxi) { return rand() % maxi;}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL3 Project", 1280, 1024, 0);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    srand(time(0));



    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    for (int i = 0; i < 3000; i++) {
        r[i] = getRandomNumber(256);
        g[i] = getRandomNumber(256);
        b[i] = getRandomNumber(256);
        posx1[i] = getRandomNumber(1280);
        posy1[i] = getRandomNumber(1024);
        if (i < 1000) {
            posx2[i] = getRandomNumber(1280);
            posy2[i] = getRandomNumber(1024);
        }
    }


    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set render draw color to black
        SDL_RenderClear(renderer); // Clear the renderer



        for (int i = 0; i < 1000; i++) {
            SDL_SetRenderDrawColor(renderer, r[i], g[i], b[i], 255);
            SDL_RenderLine(renderer, posx1[i], posy1[i], posx2[i], posy2[i]);
        }

        for (int i = 1001; i < 3000; i++) {
            SDL_SetRenderDrawColor(renderer, r[i], g[i], b[i], 255);
            SDL_RenderPoint(renderer, posx1[i], posy1[i]);
        }


        SDL_RenderPresent(renderer); // Render the screen
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}