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
    Info            info;
    VirtualScreen   *screen;

    info.addVirtualScreen(Flag::full);
    screen = info.getCurrentScreen();
    screen->createPlan({-1.4 * screen->getRatio(), 1.4}, {1.4 * screen->getRatio(), -1.4});

    Timer   fps;
    PPlot   lissajousPlot(lissajousCurvePlot(2, 3));

    info.getTimer().start();
	while (handleEvent(noneFunction, noneFunction, info))
    {
        fps.start();

        double t = info.getTimer().get_ticks() / 10000.0;
        screen->startDraw();
        SDL_SetRenderDrawColor(screen->getRenderer(), 255, 255, 255, 255);
        SDL_RenderClear(screen->getRenderer());
        SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 255, 255);
        lissajousPlot.plot(*screen, -boost::math::constants::pi<double>(), boost::math::constants::pi<double>(), 5);
        lissajousPlot.showDerivate(*screen, t);
        screen->renderPresent();
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
    }
}
