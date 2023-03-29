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

void    cercleUniteCurveLoop() {
	/* draw the lissajou curve */
    Info            info;
    VirtualScreen   *screen;
	std::function<double(double)> xt = [](double x) {return (cos(x * 4 * M_PI));};
	std::function<double(double)> yt = [](double x) {return (sin(x * 4 * M_PI));};
	info.setXT(xt);
	info.setYT(yt);
    info.addVirtualScreen(Flag::full);
    screen = info.getCurrentScreen();
    screen->createPlan({-1.4 * screen->getRatio(), 1.4}, {1.4 * screen->getRatio(), -1.4});

    Timer   fps;
	PPlot	lissajousPlot(xt, yt);

    info.getTimer().start();
	while (handleEvent(noneFunction, launchColorMap, screenShot, info))
    {
        fps.start();

        double t = info.getTimer().get_ticks() / 10000.0;
        screen->startDraw();
        SDL_SetRenderDrawColor(screen->getRenderer(), 255, 255, 255, 255);
        SDL_RenderClear(screen->getRenderer());
        SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 0, 255);
        lissajousPlot.plot(*screen, 0, 1, 5);
        // lissajousPlot.showDerivate(*screen, t);
		int indice = calcIndice(xt, yt, screen->convPoint(Point<int>{info.getMouseX(), info.getMouseY()}));
		if (info.getMouseMooved()) {
			drawIndice(info, indice);
		}
		if (info.getClicked()) {
			indiceAnimationLoop(info, Point<double>{0, 0});
		}
        screen->finishDraw();
		info.renderPresent();
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
    }
}
