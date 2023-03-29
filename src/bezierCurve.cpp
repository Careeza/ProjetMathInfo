#include "draw.hpp"
#include "projet.hpp"
#include "point.hpp"
#include "polynome.hpp"
#include "mathBonus.hpp"
#include "screen.hpp"
#include "parametricPlot.hpp"
#include <iostream>
#include <vector>
#include <tuple>
#include <random>

std::vector<Point<double>>  generateBezierPoints(Point<double> p1, Point<double> p2, int n, double y_min, double y_max) {
	/* Generate the points of the Bezier curve no loop allowed*/
    std::vector<Point<double>>  points;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr_y(y_min, y_max);
    std::uniform_real_distribution<double> distr_x(0, 1);

    points.push_back(p1);
    for (int i = 0; i < n; i++) {
        points.push_back({distr_x(eng), distr_y(eng)});
    }
    points.push_back(p2);
    std::sort(points.begin(), points.end());
    return (points);
}

std::vector<Point<double>>  generateNextPoints(std::vector<Point<double>> p, double t) {
	/* Generate the next points of the Bezier curve*/
    std::vector<Point<double>>  new_p;

    for (size_t i = 0; i < p.size() - 1; i++) {
        new_p.push_back({p[i].getX() * (1 - t) + p[i + 1].getX() * t, p[i].getY() * (1 - t) + p[i + 1].getY() * t});
    }
    return (new_p);
}

std::tuple<std::function<double(double)>, std::function<double(double)>>	bezierCurvePoly(std::vector<Point<double>> bezierPoints) {
	/* Generate the polynomial of the Bezier curve*/
    Poly    px;
    Poly    py;

    std::tie(px, py) = BezierPoly(bezierPoints);
	return (std::make_tuple(std::bind( &Poly::operator(), px, std::placeholders::_1), std::bind( &Poly::operator(), py, std::placeholders::_1 )));
}


PPlot   bezierCurvePlot(std::vector<Point<double>> bezierPoints) {
	/* Generate the plot of the Bezier curve*/
    Poly    px;
    Poly    py;

    std::tie(px, py) = BezierPoly(bezierPoints);
	return (PPlot{std::bind( &Poly::operator(), px, std::placeholders::_1), std::bind( &Poly::operator(), py, std::placeholders::_1 )});
}

void	firstDraw2(Info& info) {
	/* Draw the Bezier curve */
	VirtualScreen				*screen;
	std::vector<Point<double>>	bezierPoints;

	screen = info.getCurrentScreen();
	bezierPoints = info.getBezierPoints();
	screen->startDraw();
	drawLines(*screen, bezierPoints, 6, 0, 255, 0);
	SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 0, 255);
	drawPoints(*screen, bezierPoints, 15);
	screen->finishDraw();
	info.renderPresent();
}

void    bezierCurveLoop() {
	/* Draw the Bezier curve */
	Info            info;
	VirtualScreen   *screen;

	info.addVirtualScreen(Flag::full);
	screen = info.getCurrentScreen();
	screen->createPlan({0, 1}, {1, -1});
	std::vector<Point<double>>  bezierPoints;// = generateBezierPoints({0, 0}, {1, 0}, 3);
	Timer   fps;

	bezierPoints.push_back({0, 0});
	bezierPoints.push_back({0.33, 0.8});
	bezierPoints.push_back({0.66, -0.5});
	bezierPoints.push_back({1, 0});
	info.setBezierPoints(bezierPoints);

	PPlot	bezierPlot(bezierCurvePlot(bezierPoints));
	info.getTimer().start();
	info.getTimer().pause();

	firstDraw2(info);

	while (handleEvent(hideOrShowAlgo, noneFunction, screenShot, info))
	{
		fps.start();

		if (info.getTimer().is_paused()) {
			continue ;
		}

		double t = info.getTimer().get_ticks() / 10000.0;
		if (t >= 1.0) {
			info.getTimer().start();
			t = 0;
		}
		screen->startDraw();
		SDL_SetRenderDrawColor(screen->getRenderer(), 255, 255, 255, 255);
		SDL_RenderClear(screen->getRenderer());
		SDL_SetRenderDrawColor(screen->getRenderer(), 0, 255, 0, 255);
		if (info.showAlgo()) {
				drawLines(*screen, bezierPoints, 6, 0, 255, 0);
				SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 0, 255);
				drawPoints(*screen, bezierPoints, 15);
		}
		auto nextP = bezierPoints;
		while (nextP.size() >= 2) {
			SDL_SetRenderDrawColor(screen->getRenderer(), bezierPoints.size() / static_cast<double>(nextP.size()) * 255, 42, (1.0 - bezierPoints.size() / static_cast<double>(nextP.size())) * 255, 255);
			nextP = generateNextPoints(nextP, t);
			if (info.showAlgo()) {
				drawLines(*screen, nextP, 4, bezierPoints.size() / static_cast<double>(nextP.size()) * 255, 42, (1.0 - bezierPoints.size() / static_cast<double>(nextP.size())) * 255);
				drawPoints(*screen, nextP, 15);
			}
		}
		SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 0, 255);
		bezierPlot.plot(*screen, 0, t, 5);
		SDL_SetRenderDrawColor(screen->getRenderer(), 255, 0, 0, 255);
		drawPoint(*screen, screen->convPointSDL(bezierPoints[bezierPoints.size() - 1]), 30);
		drawPoint(*screen, screen->convPointSDL(bezierPoints[0]), 30);
		if (info.showAlgo()) {
			SDL_SetRenderDrawColor(screen->getRenderer(), 255, 0, 0, 255);
			SDL_Point p = screen->convPointSDL(nextP[0]);
			drawPoint(*screen, p, 15);
		}
		screen->finishDraw();
		info.renderPresent();
		SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
	}
}
