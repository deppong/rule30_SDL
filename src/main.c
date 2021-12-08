#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <SDL.h>

#define WIDTH 800
#define HEIGHT 800


int main(int argc, char* argv[]) {
    int quit = 0;
    srand(time(0));

    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Cellular automata", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // background color
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
    // if cell is on color
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

    /*
        Allocating the size of the board to be 3 times that of the window, 
        just so where the board goes of the screen it doesn't run out of space
        and will accurately display edge cells values.
    */
    uint8_t *cells = malloc(sizeof(uint8_t)*WIDTH*3);
    uint8_t *prev = malloc(sizeof(uint8_t)*WIDTH*3);

    // Initializing at 0
    for(int i = 0; i < WIDTH*3; i++){
        cells[i] = 0;
        prev[i] = 0;
    }

    /*
          width     width      width
        |--------||---------||---------|
                       |
                    midpoint
                1.5 * the width 
    */
    cells[(int)(WIDTH+WIDTH*.5)] = 1;


    for (int i = 0; i < HEIGHT; i++) {
        memcpy(prev, cells, WIDTH*3);
        // Draw point if cell alive
        for (int x = 0; x < WIDTH*3; x++) {
            if(cells[x+(int)(WIDTH)]) SDL_RenderDrawPoint(renderer, x, i);
        }
        // update state
        for (int h=0; h<WIDTH*3; h++) {
            if (h!=0)
                cells[h] = prev[h-1] ^ (prev[h] | prev[h+1]);
        }
        SDL_RenderPresent(renderer);
    }
    
    while(!quit) {
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_QUIT: quit = 1;break;
            case SDL_KEYDOWN: if (event.key.keysym.sym == SDLK_ESCAPE) quit=1;break;
        }
    }

    // save results to a bmp file
    SDL_Surface *surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
    SDL_SaveBMP(surface, "rule30.bmp");

    // Free all this memory
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(surface);
    free(cells);
    free(prev);
    SDL_Quit();
    return 0;
}
