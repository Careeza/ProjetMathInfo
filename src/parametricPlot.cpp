#include "parametricPlot.hpp"
#include "mathBonus.hpp"
#include "SDL2_gfxPrimitives.h"

PPlot::PPlot(std::function<double(double)> xt, std::function<double(double)> yt) : xt_(xt), yt_(yt) {};


void	PPlot::plot(VirtualScreen &screen, double tStart, double tEnd, int size) {
	double	w = tEnd - tStart;
	double	pas = w / static_cast<double>(screen.getVirtualW()) / 8.0;

	if (w == 0)
		return ;
	for (double t = tStart; t <= tEnd; t += pas) {
		double x = xt_(t);
		double y = yt_(t);
		SDL_Point point = screen.convPointSDL({x, y});
		for (int i = -size / 2; i <= size / 2; i++) {
			SDL_RenderDrawPoint(screen.getRenderer(), point.x, point.y + i);
		}
	}
}

void	drawTriangle(VirtualScreen& screen, double x, double y, double dx, double dy) {
	double	x1 = x + dx + (dx * 0.2);
	double	y1 = y + dy + (dy * 0.2);
	
	double	x2 = x + dx - (dy * 0.2);
	double	y2 = y + dy + (dx * 0.2);

	double	x3 = x + dx + (dy * 0.2);
	double	y3 = y + dy - (dx * 0.2);

	SDL_Point p1 = screen.convPointSDL({x1, y1});
	SDL_Point p2 = screen.convPointSDL({x2, y2});
	SDL_Point p3 = screen.convPointSDL({x3, y3});
	filledTrigonRGBA(screen.getRenderer(), p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, 255, 0, 0, 255);
}


void	PPlot::showDerivate(VirtualScreen &screen, double t) {
	double	x = xt_(t);
	double	y = yt_(t);
	double	dx = derivate(xt_, t);
	double	dy = derivate(yt_, t);
	std::tie(dx, dy) = normalize(dx, dy);
	dx /= 5.0;
	dy /= 5.0;
	SDL_Point p1 = screen.convPointSDL({x, y});
	SDL_Point p2 = screen.convPointSDL({x + dx, y + dy});
	thickLineRGBA(screen.getRenderer(), p1.x, p1.y, p2.x, p2.y, 7, 0xFF, 0, 0, 0xFF);
	drawTriangle(screen, x, y, dx, dy);
	SDL_RenderDrawLine(screen.getRenderer(), p1.x, p1.y, p2.x, p2.y);
}