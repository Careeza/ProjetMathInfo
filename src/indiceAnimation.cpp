#include "draw.hpp"
#include "projet.hpp"
#include "point.hpp"
#include "polynome.hpp"
#include "mathBonus.hpp"
#include "screen.hpp"
#include "index.hpp"
#include "parametricPlot.hpp"
#include <iostream>
#include <vector>
#include <boost/math/constants/constants.hpp>

void    indiceAnimationLoop(Info& info, std::function<double(double)> xt, std::function<double(double)> yt, Point<double> p) {
    VirtualScreen   *screen;
    info.addVirtualScreen(Flag::full);
    screen = info.getCurrentScreen();

    Timer   fps;
	PPlot	parametricPlot(xt, yt);

    info.getTimer().start();
	while (handleEvent(noneFunction, noneFunction, info))
    {
        fps.start();

        double t = info.getTimer().get_ticks() / 10000.0;
        screen->startDraw();
        SDL_SetRenderDrawColor(screen->getRenderer(), 255, 255, 255, 255);
        SDL_RenderClear(screen->getRenderer());
        SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 255, 255);
        parametricPlot.plot(*screen, 0, 1, 5);
		int index = calcIndex(xt, yt, screen->convPoint(Point<int>{info.getMouseX(), info.getMouseY()}));
		if (info.getMouseMooved()) {
			drawIndex(info, index);
		}
        screen->renderPresent();
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
    }
}
