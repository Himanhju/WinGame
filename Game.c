#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Mouse Click on Rectangle", 
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                          1500, 800, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    SDL_Event e;
    int quit = 0;
    int x1, y1 = 0;
    __uint128_t clicks = 0;
    __uint128_t time = 0;
    while(!quit){
        SDL_Rect rect = { x1, y1, 25, 25 };
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Get mouse position
                int x, y;
                SDL_GetMouseState(&x, &y);

                // Check if the mouse click is inside the rectangle
                if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) {
                    quit = 1;
                    time--;
                } else {
                    clicks++;
                }
            }
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_W]) {
            y1 -= 1;
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            y1 += 1;
        }
        if (currentKeyStates[SDL_SCANCODE_A]) {
            x1 -= 1;
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            x1 += 1;
        }
        if (x1 < 0) x1 = 0;
        if (x1 > 1500 - 25) x1 = 1500 - 25;
        if (y1 < 0) y1 = 0;
        if (y1 > 800 - 25) y1 = 800 - 25;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        time++;
    }
    __uint128_t score = ((clicks + 1)/2) * time * 0.005;
    printf("\n\nyou lose, you got %lli points\n\n\n", score);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}