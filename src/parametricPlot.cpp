#include "parametricPlot.hpp"
#include "mathBonus.hpp"

PPlot::PPlot(std::function<double(double)> xt, std::function<double(double)> yt) : xt_(xt), yt_(yt) {};


void	PPlot::plot(Screen &screen, double tStart, double tEnd, int size) {
	double	w = tEnd - tStart;
	double	pas = w / static_cast<double>(screen.window_w) / 8.0;

	if (w == 0)
		return ;
	for (double t = tStart; t <= tEnd; t += pas) {
		double x = xt_(t);
		double y = yt_(t);
		SDL_Point point = screen.convPointSDL({x, y});
		for (int i = -size / 2; i <= size / 2; i++) {
			SDL_RenderDrawPoint(screen.render, point.x, point.y + i);
		}
	}
}

void	PPlot::showDerivate(Screen &screen, double t) {
	double	x = xt_(t);
	double	y = yt_(t);
	double	dx = derivate(xt_, t);
	double	dy = derivate(yt_, t);
	std::tie(dx, dy) = normalize(dx, dy);
	dx /= 5.0;
	dy /= 5.0;
	SDL_Point p1 = screen.convPointSDL({x, y});
	SDL_Point p2 = screen.convPointSDL({x + dx, y + dy});
	SDL_RenderDrawLine(screen.render, p1.x, p1.y, p2.x, p2.y);
}
