#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <SDL.h>

#define SIZE 64
/*
    uint8_t cells[SIZE] = {0};
    cells[SIZE/2] = 1;
    uint8_t prev[SIZE];
    for (int i = 0; i < SIZE/2; i++) {
    memcpy(prev, cells, SIZE);
         for (int j = 0; j < SIZE; j++) {
             printf("%c", cells[j] & 1 ? '+':'-');
         }
         putchar('\n');
         //update state
        for (int h=0; h<SIZE; h++) {
            cells[h] = prev[h-1] ^ (prev[h] | prev[h+1]);
        }
    }
*/

int main(int argc, char* argv[]) {
    int quit = 0;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * screen = SDL_CreateWindow("Cellular automata", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    while(!quit) {
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_QUIT: quit = 1;break;
        }
    }

    SDL_Quit();
    return 0;
}
