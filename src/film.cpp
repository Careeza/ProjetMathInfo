#include "draw.hpp"
#include "projet.hpp"
#include "point.hpp"
#include "polynome.hpp"
#include "mathBonus.hpp"
#include "screen.hpp"
#include "SDL2_gfxPrimitives.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <random>

void    filmBezierCurve() {
	/* Draw the Bezier curve using GFX*/
	Info            info;
	VirtualScreen   *screen;

	info.addVirtualScreen(Flag::full);
	screen = info.getCurrentScreen();
	screen->createPlan({0, 1}, {1, -1});
	std::vector<Point<double>>  bezierPoints = generateBezierPoints({0, 0}, {1, 0}, 5);

	std::vector<Sint16> x;
	std::vector<Sint16> y;
	std::tie(x, y) = convBezierPointsGFX(*screen, bezierPoints);

	info.getTimer().start();
	double t = 0;
	while (handleEvent(hideOrShowAlgo, noneFunction, screenShot, info))
	{
		t += 0.005;
		if (t >= 1.0) {
			return ;
		}
		screen->startDraw();
		SDL_SetRenderDrawColor(screen->getRenderer(), 255, 255, 255, 255);
		SDL_RenderClear(screen->getRenderer());
		if (info.showAlgo()) {
				drawLines(*screen, bezierPoints, 3, 255, 0, 0);
		}
		auto nextP = bezierPoints;
		while (nextP.size() >= 2) {
			SDL_SetRenderDrawColor(screen->getRenderer(), bezierPoints.size() / static_cast<double>(nextP.size()) * 255, 42, (1.0 - bezierPoints.size() / static_cast<double>(nextP.size())) * 255, 255);
			nextP = generateNextPoints(nextP, t);
			if (info.showAlgo()) {
				drawLines(*screen, nextP, 3, bezierPoints.size() / static_cast<double>(nextP.size()) * 255, 42, (1.0 - bezierPoints.size() / static_cast<double>(nextP.size())) * 255);
				drawPoints(*screen, nextP, 10);
			}
		}
		SDL_SetRenderDrawColor(screen->getRenderer(), 255, 0, 0, 255);
		SDL_Point p = screen->convPointSDL(nextP[0]);
		drawPoint(*screen, p, 15);
		SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 255, 255);
		bezierRGBA(screen->getRenderer(), &x[0], &y[0], x.size(), 5, 255, 0, 0, 255);
		screen->finishDraw();
		info.renderPresent(true);
	}
}
