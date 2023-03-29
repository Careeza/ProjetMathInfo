#include "polygone.hpp"
#include "draw.hpp"
#include "projet.hpp"
#include "point.hpp"
#include "polynome.hpp"
#include "mathBonus.hpp"
#include "screen.hpp"
#include "parametricPlot.hpp"
#include "indice.hpp"
#include <iostream>
#include <vector>
#include <tuple>
#include <random>

void    polygoneBuilder() {
	Info		info;
	Polygone	poly;

	VirtualScreen	*screen;
	info.addVirtualScreen(Flag::full);
	screen = info.getCurrentScreen();
	screen->createPlan({0, 1}, {1 * screen->getRatio(), 0});
	Timer		fps;
	info.getTimer().start();
	//ajout d'un polygone étoilé
	// poly.addPoint(Point(1 * screen->getRatio() / 2, 0.9));
	// poly.addPoint(Point(1 * screen->getRatio() / 2 + 0.4, 0.1));
	// poly.addPoint(Point(1 * screen->getRatio() / 2 - 0.4, 0.65));
	// poly.addPoint(Point(1 * screen->getRatio() / 2 + 0.4, 0.65));
	// poly.addPoint(Point(1 * screen->getRatio() / 2 - 0.4, 0.1));
	// representationAire(info, poly);
	while (handleEvent(noneFunction, noneFunction, screenShot, info))
	{
		fps.start();

		screen->startDraw();
		SDL_SetRenderDrawColor(screen->getRenderer(), 255, 255, 255, 255);
		SDL_RenderClear(screen->getRenderer());
		screen->startDraw();
		if (info.getClicked() == SDL_BUTTON_LEFT) {
			poly.addPoint(screen->convPoint(Point<int>{info.getMouseX(), info.getMouseY()}));
		}
		int indice = calcIndice(poly, screen->convPoint(Point<int>{info.getMouseX(), info.getMouseY()}));
		if (info.getMouseMooved()) {
			drawIndice(info, indice);
		}
		if (info.getClicked() == SDL_BUTTON_X1) {
			indiceAnimationLoopPolygone(info, screen->convPoint(Point<int>{info.getMouseX(), info.getMouseY()}), poly);
		} else if (info.getClicked()) {
			std::cout << "button: " << info.getClicked() << std::endl;
		}
		drawPolygone(*screen, poly, 5, 0, 0, 0);
		screen->finishDraw();
		info.renderPresent();
		SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
	}
}