#include "projet.hpp"
#include "point.hpp"
#include "polynome.hpp"
#include <vector>

void	drawLine(Screen& screen, Point<double> p1, Point<double> p2) {
	Point<int>	p1_ = screen.convPoint(p1);
	Point<int>	p2_ = screen.convPoint(p2);

	SDL_RenderDrawLine(screen.render, p1_.getX(), p1_.getY(), p2_.getX(), p2_.getY());
	// std::cout << "[" << p1_ << " - " << p2_ << "]" << std::endl;
}

void	drawLines(Screen& screen, std::vector<Point<double>>& points) {
	std::vector<SDL_Point>	pointsSDL;
	
	for (Point<double> p : points) {
		pointsSDL.push_back(screen.convPointSDL(p));
	}
	SDL_RenderDrawLines(screen.render, &pointsSDL[0], pointsSDL.size());
}

void	drawPoly(Screen& screen, Poly& px, Poly& py, double maxT)
{
	// SDL_SetRenderDrawColor(screen.render, )
	for (double t = 0; t <= maxT; t+= 0.0001) {
		double x = px(t);
		double y = py(t);
		// std::cout << "[" << x << ", " << y << "]" << std::endl;
		SDL_Point point = screen.convPointSDL({x, y});
		// std::cout << "t = " << t << " [" << point.x << ", " << point.y << "] " << "- [" << x << ", " << y << "]" << std::endl;
		SDL_RenderDrawPoint(screen.render, point.x, point.y);
	}
	// exit(0);
	// SDL_RenderPresent()
}

void	drawPoint(Screen& screen, SDL_Point point, int size) {
	std::vector<SDL_Point>	points;

	points.push_back(point);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			points.push_back({point.x + i - size / 2, point.y + j - size / 2});
		}
	}
	SDL_RenderDrawPoints(screen.render, &points[0], points.size());
}