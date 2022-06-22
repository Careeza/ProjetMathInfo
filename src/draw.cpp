#include "draw.hpp"
#include "projet.hpp"
#include "point.hpp"
#include "polynome.hpp"
#include <vector>

void	drawLine(VirtualScreen& screen, Point<double> p1, Point<double> p2) {
	Point<int>	p1_ = screen.convPoint(p1);
	Point<int>	p2_ = screen.convPoint(p2);

	SDL_RenderDrawLine(screen.getRenderer(), p1_.getX(), p1_.getY(), p2_.getX(), p2_.getY());
}

void	drawLines(VirtualScreen& screen, const std::vector<Point<double>>& points) {
	std::vector<SDL_Point>	pointsSDL;
	
	for (Point<double> p : points) {
		pointsSDL.push_back(screen.convPointSDL(p));
	}
	SDL_RenderDrawLines(screen.getRenderer(), &pointsSDL[0], pointsSDL.size());
}

void	drawPoly(VirtualScreen& screen, Poly& px, Poly& py, double maxT)
{
	for (double t = 0; t <= maxT; t+= 0.0001) {
		double x = px(t);
		double y = py(t);
		SDL_Point point = screen.convPointSDL({x, y});
		SDL_RenderDrawPoint(screen.getRenderer(), point.x, point.y);
	}
}

void	drawPoint(VirtualScreen& screen, SDL_Point point, int size) {
	std::vector<SDL_Point>	points;

	points.push_back(point);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			points.push_back({point.x + i - size / 2, point.y + j - size / 2});
		}
	}
	SDL_RenderDrawPoints(screen.getRenderer(), &points[0], points.size());
}