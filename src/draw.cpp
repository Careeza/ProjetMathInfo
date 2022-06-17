#include "projet.hpp"
#include "point.hpp"
#include <vector>

void	drawLine(Screen& screen, Point<double> p1, Point<double> p2) {
	Point<int>	p1_ = screen.convPoint(p1);
	Point<int>	p2_ = screen.convPoint(p2);

	SDL_RenderDrawLine(screen.render, p1_.getX(), p1_.getY(), p2_.getX(), p2_.getY());
	// std::cout << "[" << p1_ << " - " << p2_ << "]" << std::endl;
}

void	drawLines(Screen& screen, std::vector<Point<double>> points) {
	std::vector<SDL_Point>	pointsSDL;
	
	for (Point<double> p : points) {
		pointsSDL.push_back(screen.convPointSDL(p));
	}
	SDL_RenderDrawLines(screen.render, &pointsSDL[0], pointsSDL.size());
}
