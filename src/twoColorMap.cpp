#include "draw.hpp"
#include "projet.hpp"
#include "point.hpp"
#include "polynome.hpp"
#include "polygone.hpp"
#include "mathBonus.hpp"
#include "screen.hpp"
#include "indice.hpp"
#include "parametricPlot.hpp"
#include <iostream>
#include <vector>
#include "SDL2_gfxPrimitives.h"

void    twoColorMapLoop(Info& info) {
	/* Illustrate the two color theoreme */
    VirtualScreen   *screen;
    screen = info.getCurrentScreen();

    Timer   	fps;
	std::function<double(double)> xt = info.getXT();
	std::function<double(double)> yt = info.getYT();
	PPlot		parametricPlot(xt, yt);

    info.getTimer().start();
	screen->startDraw();
	SDL_SetRenderDrawColor(screen->getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(screen->getRenderer());
	for (int i = 0; i < screen->getVirtualW(); i += 2) {
		for (int j = 0; j < screen->getVirtualH(); j += 2) {
			Point<double> p = screen->convPoint(Point<int>{i, j});
			int	indice = calcIndice(xt, yt, p);
			if (indice % 2 == 0) {
				SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 255, 255);
			} else {
				SDL_SetRenderDrawColor(screen->getRenderer(), 255, 0, 0, 255);
			}
			drawPoint(*screen, {i, j}, 2);
		}
		if (i % 600 == 0) {
			std::cout << "Debug : i = " << i << std::endl;
		}
	}
	std::cout << "END" << std::endl;
	SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 0, 255);
	parametricPlot.plot(*screen, 0, 1, 5);
	screen->finishDraw();
		info.renderPresent();
	while (handleEvent(noneFunction, noneFunction, screenShot, info))
    {
        fps.start();
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
    }
}

bool	findPointNotColored(std::vector<std::vector<Case>>& map, int&x, int &y) {
	for (size_t i = 0; i < map.size(); i++) {
		for (size_t j = 0; j < map[i].size(); j++) {
			if (map[i][j].colored == false) {
				x = i;
				y = j;
				return true;
			}
		}
	}
	return false;
}

void	colorMapRecursive(std::vector<std::vector<Case>>& map, int x, int y, int indice) {
	if (x < 0 || x >= static_cast<int>(map.size()) || y < 0 || y >= static_cast<int>(map[x].size())) {
		return;
	}
	if (map[x][y].colored == true) {
		return;
	}
	map[x][y].colored = true;
	map[x][y].indice = indice;
	colorMapRecursive(map, x - 1, y, indice);
	colorMapRecursive(map, x, y - 1, indice);
	colorMapRecursive(map, x + 1, y, indice);
	colorMapRecursive(map, x, y + 1, indice);
}

void	colorMapIterative(std::vector<std::vector<Case>>& map, int x, int y, int indice) {
	std::vector<Point<int>>	toColor;
	toColor.push_back(Point<int>{x, y});
	while (toColor.size() > 0) {
		Point<int>	p = toColor.back();
		toColor.pop_back();
		if (p.getX() < 0 || p.getX() >= static_cast<int>(map.size()) || p.getY() < 0 || p.getY() >= static_cast<int>(map[p.getX()].size())) {
			continue;
		}
		if (map[p.getX()][p.getY()].colored == true || map[p.getX()][p.getY()].onCurve == true) {
			continue;
		}
		map[p.getX()][p.getY()].colored = true;
		map[p.getX()][p.getY()].indice = indice;
		toColor.push_back(Point<int>{p.getX() - 1, p.getY()});
		toColor.push_back(Point<int>{p.getX(), p.getY() - 1});
		toColor.push_back(Point<int>{p.getX() + 1, p.getY()});
		toColor.push_back(Point<int>{p.getX(), p.getY() + 1});
	}
}

void    twoColorMapLoopImprove(Info& info) {
	/* Illustrate the two color theoreme improve algorithm */
    VirtualScreen   *screen;
    screen = info.getCurrentScreen();

    Timer   	fps;
	std::function<double(double)> xt = info.getXT();
	std::function<double(double)> yt = info.getYT();
	PPlot		parametricPlot(xt, yt);
	std::vector<std::vector<Case>>	map(screen->getVirtualW(), std::vector<Case>(screen->getVirtualH()));

	parametricPlot.plotOnMap(*screen, 0, 1, map);
    info.getTimer().start();
	screen->startDraw();
	int x;
	int	y;
	while(findPointNotColored(map, x, y)) {
		Point<double> p = screen->convPoint(Point<int>{x, y});
		int	indice = calcIndice(xt, yt, p);
		std::cout << indice << std::endl;
		colorMapIterative(map, x, y, indice);
	}

	SDL_SetRenderDrawColor(screen->getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(screen->getRenderer());
	screen->startDraw();
	for (size_t i = 0; i < map.size(); i++) {
		for (size_t j = 0; j < map[i].size(); j++) {
			if (map[i][j].onCurve == true) {
				SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 0, 255);
				drawPoint(*screen, {static_cast<int>(i), static_cast<int>(j)}, 1);
			} else if (map[i][j].colored == true) {
				if (abs(map[i][j].indice) % 2 == 0) {
					SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 255, 255);
				} else {
					SDL_SetRenderDrawColor(screen->getRenderer(), 255, 0, 0, 255);
				}
				drawPoint(*screen, {static_cast<int>(i), static_cast<int>(j)}, 1);
			}
		}
	}
	screen->finishDraw();
	info.renderPresent();
	// SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 0, 255);
	// parametricPlot.plot(*screen, 0, 1, 12);
	while (handleEvent(noneFunction, noneFunction, screenShot, info))
    {
        fps.start();
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
    }
}