#include "parametricPlot.hpp"
#include "mathBonus.hpp"
#include "draw.hpp"
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


void	PPlot::showDerivate(VirtualScreen &screen, double t) {
	double	x = xt_(t);
	double	y = yt_(t);
	double	dx = derivate(xt_, t);
	double	dy = derivate(yt_, t);
	std::tie(dx, dy) = normalize(dx, dy);
	dx /= 5.0;
	dy /= 5.0;
	drawArrow(screen, x, y, dx, dy);
}