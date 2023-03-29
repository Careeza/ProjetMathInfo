#include "parametricPlot.hpp"
#include "mathBonus.hpp"
#include "draw.hpp"
#include "SDL2_gfxPrimitives.h"

PPlot::PPlot(std::function<double(double)> xt, std::function<double(double)> yt) : xt_(xt), yt_(yt) {};


void	PPlot::plot(VirtualScreen &screen, double tStart, double tEnd, int size) {
	/* Plot the parametric function */
	double	w = tEnd - tStart;
	double	pas = w / static_cast<double>(screen.getVirtualW()) / 8.0;

	if (w == 0)
		return ;
	for (double t = tStart; t <= tEnd; t += pas) {
		double x = xt_(t);
		double y = yt_(t);
		SDL_Point point = screen.convPointSDL({x, y});
		drawPoint(screen, point, size);
		// for (int i = -size / 2; i <= size / 2; i++) {
		// 	SDL_RenderDrawPoint(screen.getRenderer(), point.x, point.y + i);
		// }
	}
	SDL_Point point = screen.convPointSDL({xt_(0), yt_(0)});
}

void	PPlot::plotOnMap(VirtualScreen &screen, double tStart, double tEnd, std::vector<std::vector<Case>> &map) {
	/* Plot the parametric function on a map*/
	double	w = tEnd - tStart;
	double	pas = w / static_cast<double>(screen.getVirtualW()) / 8.0;

	if (w == 0)
		return ;
	for (double t = tStart; t <= tEnd; t += pas) {
		double x = xt_(t);
		double y = yt_(t);
		SDL_Point point = screen.convPointSDL({x, y});
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (point.x + i >= 0 && point.x + i < map.size() && point.y + j >= 0 && point.y + j < map[0].size()) {
					map[point.x + i][point.y + j].colored = true;
					map[point.x + i][point.y + j].onCurve = true;
				}
			}
		}
	}
}



void	PPlot::showDerivate(VirtualScreen &screen, double t) {
	/* Plot the derivate of the parametric function */
	double	x = xt_(t);
	double	y = yt_(t);
	double	dx = derivate(xt_, t);
	double	dy = derivate(yt_, t);
	std::tie(dx, dy) = normalize(dx, dy);
	dx /= 5.0;
	dy /= 5.0;
	drawArrow(screen, x, y, dx, dy);
}

std::function<double(double)>	PPlot::getXt() const {
	/* Get the function of x */
	return (xt_);
}

std::function<double(double)>	PPlot::getYt() const {
	/* Get the function of y */
	return (yt_);
}