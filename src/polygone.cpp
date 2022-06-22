#include "draw.hpp"
#include "projet.hpp"
#include "point.hpp"
#include "polynome.hpp"
#include "mathBonus.hpp"
#include "screen.hpp"
#include "parametricPlot.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <boost/math/constants/constants.hpp>

PPlot   lissajousCurvePlot2(int m, int n) {
    return (PPlot{[m](double x) {return (sin(x * m));}, [n](double x){return (cos(x * n));}});
}


void    polygoneLoop() {
	Screen	screen;
    Timer   fps;
    Timer   timer;
	PPlot   lissajousPlot(lissajousCurvePlot2(2, 3));

	screen.createVirtualScreen({-1, 1}, {1, -1});
    timer.start();
	while (handleEvent(timer, noneFunction, noneFunction, screen))
	{
        fps.start();

        double t = timer.get_ticks() / 10000.0;
		SDL_SetRenderDrawColor(screen.render, 255, 255, 255, 255);
		SDL_RenderClear(screen.render);
		SDL_SetRenderDrawColor(screen.render, 0, 0, 255, 255);
		lissajousPlot.plot(screen, -boost::math::constants::pi<double>(), boost::math::constants::pi<double>(), 5);
		lissajousPlot.showDerivate(screen, t);
		SDL_RenderPresent(screen.render);
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
	}
	std::cout << " ? ? ? " << std::endl;
}