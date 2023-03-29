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

std::vector<Point<double>>  generateBezierPointsLoop(Point<double> p1, int n, double y_min, double y_max) {
	/* Generate the points of the Bezier curve */
    std::vector<Point<double>>  points;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr_y(y_min, y_max);
    std::uniform_real_distribution<double> distr_x(0, 1.5);

    points.push_back(p1);
    for (int i = 0; i < n; i++) {
        points.push_back({distr_x(eng), distr_y(eng)});
    }
    points.push_back(p1);
    return (points);
}


void    bezierCurveCloseLoop() {
	/* Draw the Bezier curve */
    Info            info;
    VirtualScreen   *screen;

    info.addVirtualScreen(Flag::full);
    screen = info.getCurrentScreen();
    screen->createPlan({-0.1, 1}, {1.1, -1});
    info.setBezierPoints(generateBezierPointsLoop({0, 0}, 10));
	std::vector<Point<double>>  bezierPoints = info.getBezierPoints();
    Timer   fps;

    info.getTimer().start();
    while (handleEvent(changeBezierPoint, launchColorMap, screenShot, info))
    {
        fps.start();
		std::function<double(double)>	xt = info.getXT();
		std::function<double(double)>	yt = info.getYT();
		PPlot	bezierPlot(xt, yt);

        screen->startDraw();
        SDL_SetRenderDrawColor(screen->getRenderer(), 255, 255, 255, 255);
        SDL_RenderClear(screen->getRenderer());
        SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 0, 255);
        bezierPlot.plot(*screen, 0, 1, 3);
		SDL_SetRenderDrawColor(screen->getRenderer(), 255, 0, 0, 255);
		drawPoint(*screen, screen->convPointSDL(bezierPoints[0]), 30);
		int indice = calcIndice(xt, yt, screen->convPoint(Point<int>{info.getMouseX(), info.getMouseY()}));
		if (info.getMouseMooved()) {
			drawIndice(info, indice);
		}
		if (info.getClicked()) {
			indiceAnimationLoop(info, screen->convPoint(Point<int>{info.getMouseX(), info.getMouseY()}));
		}
		screen->finishDraw();
		info.renderPresent();
		SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
	}
}
