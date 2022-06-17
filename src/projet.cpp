#include "projet.hpp"
#include "point.hpp"
#include "polynome.hpp"
#include <iostream>

void    loop(Screen& screen)
{
    auto    bezierPoints = generateBezierPoints({0, 0}, {1, 0}, 5);
    bool    close_requested = false;
    Timer   fps;
    Timer   timer; 

    timer.start();
    while (!close_requested)
    {
        fps.start();

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
        if (timer.get_ticks() >= 10000) {
            timer.start();
        }
        SDL_SetRenderDrawColor(screen.render, 0, 0, 0, 255);
        SDL_RenderClear(screen.render);
        SDL_SetRenderDrawColor(screen.render, 0, 255, 0, 255);
        drawLines(screen, bezierPoints);
        auto nextP = bezierPoints;
        double t = timer.get_ticks() / 10000.0;
        while (nextP.size() >= 2) {
            SDL_SetRenderDrawColor(screen.render, bezierPoints.size() / static_cast<double>(nextP.size()) * 255, 42, (1.0 - bezierPoints.size() / static_cast<double>(nextP.size())) * 255, 255);
            nextP = generateNextPoints(nextP, t);
            drawLines(screen, nextP);
        }
        SDL_RenderPresent(screen.render);
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
    }
}


int     main()
{
    // Screen  screen;
    Poly    p1{{3, 2}};
    Poly    p2 = p1 * p1;

    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p2(0) << std::endl;
    // screen.createVirtualScreen({0, 1}, {1, -1});
    // loop(screen);

    return (0);
}