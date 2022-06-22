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

std::tuple<std::vector<Sint16>, std::vector<Sint16>>  convBezierPointsGFX(VirtualScreen &screen, std::vector<Point<double>> points) {
    std::vector<Sint16>    x;
    std::vector<Sint16>    y;

    for (Point<double> p : points) {
        Point<int> p_ = screen.convPoint(p);
        x.push_back(p_.getX());
        y.push_back(p_.getY());
    }
    return (std::make_tuple(x, y));
}

void    bezierCurveLoopGFX() {
    Info            info;
    VirtualScreen   *screen;

    info.addVirtualScreen(Flag::full);
    screen = info.getCurrentScreen();
    screen->createPlan({0, 1}, {1, -1});
    std::vector<Point<double>>  bezierPoints = generateBezierPoints({0, 0}, {1, 0}, 100);
    Timer   fps;

    std::vector<Sint16> x;
    std::vector<Sint16> y;
    std::tie(x, y) = convBezierPointsGFX(*screen, bezierPoints);

    info.getTimer().start();
	while (handleEvent(noneFunction, noneFunction, info))
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
        bezierRGBA(screen->getRenderer(), &x[0], &y[0], x.size(), 5, 255, 0, 0, 255);
        screen->renderPresent();
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
    }
}
