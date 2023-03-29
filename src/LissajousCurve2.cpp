#include "draw.hpp"
#include "projet.hpp"
#include "point.hpp"
#include "polynome.hpp"
#include "mathBonus.hpp"
#include "screen.hpp"
#include "indice.hpp"
#include "parametricPlot.hpp"
#include <iostream>
#include <vector>
#include <boost/math/constants/constants.hpp>
#include "SDL2_gfxPrimitives.h"

void    lissajousCurveLoop2(int m, int n) {
	/* draw the lissajou curve */
    Info            info;
    VirtualScreen   *screen;
	std::function<double(double)> xt = [m](double x) {return (sin(x * m * 2 * M_PI));};
	std::function<double(double)> yt = [n](double x) {return (cos(x * n * 2 * M_PI));};

    info.addVirtualScreen(Flag::left);
    screen = info.getCurrentScreen();
    screen->createPlan({-1.4 * screen->getRatio(), 1.4}, {1.4 * screen->getRatio(), -1.4});
	info.addVirtualScreen(Flag::right);
    screen = info.getCurrentScreen();
	screen->createPlan({-1.4 * screen->getRatio(), 1.4}, {1.4 * screen->getRatio(), -1.4});
	std::function<double(double)> dxt = derivateFunction(xt);
	std::function<double(double)> dyt = derivateFunction(yt);

	tie(dxt, dyt) = normalizeFunction(dxt, dyt);

	Timer	fps;
	PPlot	lissajousPlot(xt, yt);
	PPlot	lissajousPlotDerivate(dxt, dyt);

	info.getTimer().start();
	info.getTimer().pause();
	while (handleEvent(noneFunction, noneFunction, screenShot, info))
	{
		fps.start();

        double t = info.getTimer().get_ticks() / 10000.0;
		if (t > 1.0) {
			t = 0;
		}
		SDL_SetRenderDrawColor(info.getCurrentScreen()->getRenderer(), 0, 0, 0, 255);
		info.selectScreen(1);
		screen = info.getCurrentScreen();
		screen->startDraw();
		SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 255, 255);
		drawArrow(*screen, 0, 0, dxt(t) / 2, dyt(t) / 2);
		double indicePart = calcIndicePart2(xt, yt, t);
		drawCircleIndice(*screen, {0, 0}, 0, indicePart, 500);
		filledCircleRGBA(screen->getRenderer(), screen->convPointSDL({dxt(t), dyt(t)}).x, screen->convPointSDL({dxt(t), dyt(t)}).y, 15, 255, 0, 0, 255);
		screen->finishDraw();
		info.selectScreen(0);
		screen = info.getCurrentScreen();
		screen->startDraw();
		SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 0, 255);
		lissajousPlot.plot(*screen, 0, 1, 5);
        screen->finishDraw();
		lissajousPlot.showDerivate(*screen, t);
		int indice = calcIndice(xt, yt, screen->convPoint(Point<int>{info.getMouseX(), info.getMouseY()}));
		if (info.getMouseMooved()) {
			drawIndice(info, indice);
		}
		info.renderPresent();
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
    }
}
