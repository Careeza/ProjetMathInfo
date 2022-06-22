#include "draw.hpp"
#include "projet.hpp"
#include "point.hpp"
#include "polynome.hpp"
#include <vector>
#include "SDL2_gfxPrimitives.h"

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

void	drawArrow(VirtualScreen& screen, double x, double y, double dx, double dy) {
	SDL_Point p1 = screen.convPointSDL({x, y});
	SDL_Point p2 = screen.convPointSDL({x + dx, y + dy});
	
	thickLineRGBA(screen.getRenderer(), p1.x, p1.y, p2.x, p2.y, 7, 0xFF, 0, 0, 0xFF);

	double	x1 = x + dx + (dx * 0.2);
	double	y1 = y + dy + (dy * 0.2);
	
	double	x2 = x + dx - (dy * 0.2);
	double	y2 = y + dy + (dx * 0.2);

	double	x3 = x + dx + (dy * 0.2);
	double	y3 = y + dy - (dx * 0.2);

	p1 = screen.convPointSDL({x1, y1});
	p2 = screen.convPointSDL({x2, y2});
	SDL_Point p3 = screen.convPointSDL({x3, y3});
	filledTrigonRGBA(screen.getRenderer(), p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, 255, 0, 0, 255);
}

void	drawArrowAngle(VirtualScreen& screen, Point<double> p, double angle, double size) {
	double	x = p.getX();
	double	y = p.getY();
	double	dx = cos(angle) * size;
	double	dy = cos(angle) * size;
	
	SDL_Point p1 = screen.convPointSDL({x, y});
	SDL_Point p2 = screen.convPointSDL({x + dx, y + dy});
	
	thickLineRGBA(screen.getRenderer(), p1.x, p1.y, p2.x, p2.y, 7, 0xFF, 0, 0, 0xFF);

	double	x1 = x + dx + (dx * 0.2);
	double	y1 = y + dy + (dy * 0.2);
	
	double	x2 = x + dx - (dy * 0.2);
	double	y2 = y + dy + (dx * 0.2);

	double	x3 = x + dx + (dy * 0.2);
	double	y3 = y + dy - (dx * 0.2);

	p1 = screen.convPointSDL({x1, y1});
	p2 = screen.convPointSDL({x2, y2});
	SDL_Point p3 = screen.convPointSDL({x3, y3});
	filledTrigonRGBA(screen.getRenderer(), p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, 255, 0, 0, 255);

}