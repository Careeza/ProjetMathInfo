#include "projet.h"
#include "point.h"
#include <iostream>

void    loop(SDL_Window *window, SDL_Renderer *render)
{
    (void)window;
    (void)render;
    bool close_requested = false;
    Timer timer;

    while (!close_requested)
    {
        timer.start();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    close_requested = true;
                    std::cout << "QUIT" << std::endl;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            std::cout << "QUIT 2" << std::endl;
                            close_requested = true;
                            break;
                        case SDLK_a:
                            break;
                        case SDLK_b:
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }
        SDL_Delay(fmax(0, (1000 / 30) - timer.get_ticks()));
    }
}


int     main()
{
    Point<int>  point;

    (void)point;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    // SDL_Window *window = SDL_CreateWindow("Ant", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0); // => Creation fenetre SDL
    SDL_Window *window = SDL_CreateWindow("Bezier", 0, 0, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
    
    loop(window, render);

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    return (0);
}