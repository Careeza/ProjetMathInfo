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
    std::vector<Point<double>>  new_p;

    for (size_t i = 0; i < p.size() - 1; i++) {
        new_p.push_back({p[i].getX() * (1 - t) + p[i + 1].getX() * t, p[i].getY() * (1 - t) + p[i + 1].getY() * t});
    }
    return (new_p);
}

PPlot   bezierCurvePlot(std::vector<Point<double>> bezierPoints) {
    Poly    px;
    Poly    py;

    std::tie(px, py) = BezierPoly(bezierPoints);
	return (PPlot{std::bind( &Poly::operator(), px, std::placeholders::_1), std::bind( &Poly::operator(), py, std::placeholders::_1 )});
}

void    bezierCurveLoop() {
    Info            info;
    VirtualScreen   *screen;

    info.addVirtualScreen(Flag::full);
    screen = info.getCurrentScreen();
    screen->createPlan({0, 1}, {1, -1});
    std::vector<Point<double>>  bezierPoints = generateBezierPoints({0, 0}, {1, 0}, 10);
    Timer   fps;
	PPlot	bezierPlot(bezierCurvePlot(bezierPoints));

    info.getTimer().start();
    while (handleEvent(hideOrShowAlgo, noneFunction, info))
    {
        fps.start();

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
            drawLines(*screen, bezierPoints);
        }
        auto nextP = bezierPoints;
        while (nextP.size() >= 2) {
            SDL_SetRenderDrawColor(screen->getRenderer(), bezierPoints.size() / static_cast<double>(nextP.size()) * 255, 42, (1.0 - bezierPoints.size() / static_cast<double>(nextP.size())) * 255, 255);
            nextP = generateNextPoints(nextP, t);
            if (info.showAlgo()) {
                drawLines(*screen, nextP);
            }
        }
        SDL_SetRenderDrawColor(screen->getRenderer(), 255, 0, 0, 255);
        SDL_Point p = screen->convPointSDL(nextP[0]);
        drawPoint(*screen, p, 15);
        SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 255, 255);
        bezierPlot.plot(*screen, 0, t, 3);
        screen->renderPresent();
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
    }
}
