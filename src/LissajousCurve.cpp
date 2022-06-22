#include "draw.hpp"
#include "projet.hpp"
#include "point.hpp"
#include "polynome.hpp"
#include "mathBonus.hpp"
#include "screen.hpp"
#include "parametricPlot.hpp"
#include <iostream>
#include <vector>
#include <boost/math/constants/constants.hpp>


PPlot   lissajousCurvePlot(int m, int n) {
    return (PPlot{[m](double x) {return (sin(x * m));}, [n](double x){return (cos(x * n));}});
}

void    lissajousCurveLoop() {
    Screen  S;


    VirtualScreen   screen(S, Flag::left);
    screen.createPlan({-1.4 * screen.getRatio(), 1.4}, {1.4 * screen.getRatio(), -1.4});

    bool    close_requested = false;
    Timer   fps;
    Timer   timer;
    PPlot   lissajousPlot(lissajousCurvePlot(2, 3));

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
        double t = timer.get_ticks() / 10000.0;
        // if (t >= 1.0) {
        //     timer.start();
        //     t = 0;
        // }
        screen.startDraw();
        SDL_SetRenderDrawColor(screen.getRenderer(), 255, 255, 255, 255);
        SDL_RenderClear(screen.getRenderer());
        SDL_SetRenderDrawColor(screen.getRenderer(), 0, 0, 255, 255);
        lissajousPlot.plot(screen, -boost::math::constants::pi<double>(), boost::math::constants::pi<double>(), 5);
        lissajousPlot.showDerivate(screen, t);
        screen.renderPresent();
        // SDL_RenderPresent(screen.getRenderer());
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
    }
}
