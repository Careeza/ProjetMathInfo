#include "parametricPlot.hpp"

PPlot::PPlot(std::function<double(double)> xt, std::function<double(double)> yt) : xt_(xt), yt_(yt) {};


void	PPlot::plot(Screen &screen, double tStart, double tEnd, int size) {
	double	w = tEnd - tStart;
	double	pas = w / static_cast<double>(screen.window_w) / 4.0;

	if (w == 0)
		return ;
	for (double t = tStart; t <= tEnd; t += pas) {
		double x = xt_(t);
		double y = yt_(t);
		SDL_Point point = screen.convPointSDL({x, y});
		for (int i = size / 2; i <= size / 2; i++) {
			SDL_RenderDrawPoint(screen.render, point.x, point.y + i);
		}
	}
}
