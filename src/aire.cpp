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

void	calculAire1(std::vector<std::vector<Case>>& map, int w, int h) {
	int	aire = 0;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (map[i][j].indice != 0) {
				aire++;
			}
		}
	}
	std::cout << aire / (static_cast<double>(w * h)) << std::endl;
}

void	calculAire2(std::vector<std::vector<Case>>& map, int w, int h) {
	int	aire = 0;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (map[i][j].indice != 0) {
				aire += map[i][j].indice;
			}
		}
	}
	std::cout << aire / (static_cast<double>(w * h)) << std::endl;
}

void    representationAire(Info& info, Polygone &poly) {
	Timer   	fps;
	/* Illustrate the two color theoreme improve algorithm */
    VirtualScreen   *screen;
    screen = info.getCurrentScreen();
	std::vector<std::vector<Case>>	map(screen->getVirtualW(), std::vector<Case>(screen->getVirtualH()));

	drawPolygoneOnMap(*screen, poly, map);
	// parametricPlot.plotOnMap(*screen, 0, 1, map);
	screen->startDraw();
	int x;
	int	y;
	while(findPointNotColored(map, x, y)) {
		Point<double> p = screen->convPoint(Point<int>{x, y});
		int	indice = calcIndice(poly, p);
		colorMapIterative(map, x, y, indice);
	}
	int debug = 0;
	for (size_t i = 0; i < map.size(); i++) {
		for (size_t j = 0; j < map[i].size(); j++) {
			if (map[i][j].onCurve == true) {
				debug++;
				map[i][j].indice = calcIndice(poly, screen->convPoint(Point<int>{x, y}));
			}
		}
		std::cout << debug << std::endl;
	}
	std::cout << debug << std::endl;
	calculAire1(map, screen->getVirtualW(), screen->getVirtualH());
	calculAire2(map, screen->getVirtualW(), screen->getVirtualH());

    info.getTimer().start();
	SDL_SetRenderDrawColor(screen->getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(screen->getRenderer());
	screen->startDraw();
	for (size_t i = 0; i < map.size(); i++) {
		for (size_t j = 0; j < map[i].size(); j++) {
			if (map[i][j].onCurve == true) {
				SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 0, 255);
				drawPoint(*screen, {static_cast<int>(i), static_cast<int>(j)}, 1);
			} else if (map[i][j].colored == true) {
				if (map[i][j].indice == 0) {
					SDL_SetRenderDrawColor(screen->getRenderer(), 255, 255, 255, 255);
				} else {
					SDL_SetRenderDrawColor(screen->getRenderer(), 255, 0, 0, 255);
				}
				drawPoint(*screen, {static_cast<int>(i), static_cast<int>(j)}, 1);
			}
		}
	}
	screen->finishDraw();
	info.renderPresent();
	while (handleEvent(noneFunction, noneFunction, screenShot, info))
    {
        fps.start();
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
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
				if (map[i][j].indice == 0) {
					SDL_SetRenderDrawColor(screen->getRenderer(), 255, 255, 255, 255);
				} else if (map[i][j].indice < 0) {
					SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 100 * map[i][j].indice, 255);
				} else {
					SDL_SetRenderDrawColor(screen->getRenderer(), 100 * abs(map[i][j].indice), 0, 0, 255);
				}
				drawPoint(*screen, {static_cast<int>(i), static_cast<int>(j)}, 1);
			}
		}
	}
	screen->finishDraw();
	info.renderPresent();
	while (handleEvent(noneFunction, noneFunction, screenShot, info))
    {
        fps.start();
        SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
    }

}