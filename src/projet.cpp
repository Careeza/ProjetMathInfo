#include "draw.hpp"
#include "projet.hpp"
#include "point.hpp"
#include "polynome.hpp"
#include "mathBonus.hpp"
#include "screen.hpp"
#include <iostream>
#include <vector>
#include <tuple>

void    loop(Screen& screen)
{
    auto    bezierPoints = generateBezierPoints({0, 0}, {1, 0}, 30);
    bool    close_requested = false;
    Timer   fps;
    Timer   timer; 
    Poly    px;
    Poly    py;
    bool    showAlgo = true;

    std::tie(px, py) = BezierPoly(bezierPoints);
    std::cout << py << std::endl;
    std::cout << px << std::endl;
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
                            showAlgo = !showAlgo;
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
        SDL_SetRenderDrawColor(screen.render, 255, 255, 255, 255);
        SDL_RenderClear(screen.render);
        double t = timer.get_ticks() / 10000.0;
        SDL_SetRenderDrawColor(screen.render, 0, 255, 0, 255);
        if (showAlgo)
            drawLines(screen, bezierPoints);
        auto nextP = bezierPoints;
        while (nextP.size() >= 2) {
            SDL_SetRenderDrawColor(screen.render, bezierPoints.size() / static_cast<double>(nextP.size()) * 255, 42, (1.0 - bezierPoints.size() / static_cast<double>(nextP.size())) * 255, 255);
            nextP = generateNextPoints(nextP, t);
            if (showAlgo)
                drawLines(screen, nextP);
        }
        SDL_SetRenderDrawColor(screen.render, 255, 0, 0, 255);
        SDL_Point p = screen.convPointSDL(nextP[0]);
        drawPoint(screen, p, 15);
        SDL_SetRenderDrawColor(screen.render, 0, 0, 255, 255);
        drawPoly(screen, px, py, t);
        SDL_RenderPresent(screen.render);
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
    }
}


int     main()
{
    Screen  screen;

    screen.createVirtualScreen({0, 1}, {1, -1});
    loop(screen);

    return (0);
}