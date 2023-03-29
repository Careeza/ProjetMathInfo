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
#include "SDL2_gfxPrimitives.h"

void    indiceAnimationLoop(Info& info, Point<double> p) {
	/* Illustrate what is the indice of a point */
    VirtualScreen   *screen;
    screen = info.getCurrentScreen();

    Timer   	fps;
	Point<int>	p_ = screen->convPoint(p);
	std::function<double(double)> xt = info.getXT();
	std::function<double(double)> yt = info.getYT();
	PPlot		parametricPlot(xt, yt);

	std::cout << p << std::endl;

	double	angle0 = atan2(yt(0) - p.getY(), xt(0) - p.getX());

    info.getTimer().start();
	info.getTimer().pause();
	while (handleEvent(noneFunction, noneFunction, screenShot, info))
    {
        fps.start();

        double t = info.getTimer().get_ticks() / 10000.0;
        if (t > 1.0) {
			t = 1.0;
			info.getTimer().pause();
        }
		screen->startDraw();
		SDL_SetRenderDrawColor(screen->getRenderer(), 255, 255, 255, 255);
		SDL_RenderClear(screen->getRenderer());
		SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 0, 255);
		parametricPlot.plot(*screen, 0, 1, 5);
		SDL_SetRenderDrawColor(screen->getRenderer(), 255, 0, 0, 255);
		filledCircleRGBA(screen->getRenderer(), screen->convPointSDL({xt(t), yt(t)}).x, screen->convPointSDL({xt(t), yt(t)}).y, 15, 255, 0, 0, 255);
		// parametricPlot.showDerivate(*screen, t);
		double indice = calcIndicePart(xt, yt, p, t);
		if (info.getTimer().is_paused()) {
			std::cout << " ----- " << std::endl;
		}
		drawArrowAngle(*screen, p, angle0 + indice, 100);
		drawCircleIndice(*screen, p, angle0, indice);
		filledCircleRGBA(screen->getRenderer(), p_.getX(), p_.getY(), 15, 0, 0, 0, 255);
		screen->finishDraw();
		info.renderPresent();
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
    }
}


void    indiceAnimationLoopPolygone(Info& info, Point<double> p, Polygone poly) {
	/* Illustrate what is the indice of a point */
    VirtualScreen   *screen;
    screen = info.getCurrentScreen();

    Timer   	fps;
	Point<int>	p_ = screen->convPoint(p);
	std::vector<Point<double>>	points = poly.getPoints();


	double	angle0 = atan2(points[0].getY() - p.getY(), points[0].getX() - p.getX());
    info.getTimer().start();
	info.getTimer().pause();
	while (handleEvent(noneFunction, noneFunction, screenShot, info))
    {
        fps.start();

        double t = info.getTimer().get_ticks() / 10000.0;
        if (t > 1.0) {
			t = 1.0;
			info.getTimer().pause();
        }
		screen->startDraw();
		SDL_SetRenderDrawColor(screen->getRenderer(), 255, 255, 255, 255);
		SDL_RenderClear(screen->getRenderer());
		screen->startDraw();
		drawPolygone(*screen, poly, 5, 0, 0, 0);
		double indice = calcIndicePart(poly, p, t);
		drawArrowAngle(*screen, p, angle0 + indice, 100);
		drawPointPolygone(*screen, poly, 15, 255, 0, 0, t);
		drawCircleIndice(*screen, p, angle0, indice);
		filledCircleRGBA(screen->getRenderer(), p_.getX(), p_.getY(), 15, 0, 0, 0, 255);
		screen->finishDraw();
		info.renderPresent();
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
    }
}
