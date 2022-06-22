#ifndef DRAW_HPP

# define DRAW_HPP

# include <SDL2/SDL.h>
# include "screen.hpp"
# include "point.hpp"
# include "polynome.hpp"
# include <vector>

void	drawLine(VirtualScreen& screen, Point<double> p1, Point<double> p2);
void	drawLines(VirtualScreen& screen, const std::vector<Point<double>>& points);
void	drawPoly(VirtualScreen& screen, Poly& px, Poly& py, double maxT);
void	drawPoint(VirtualScreen& screen, SDL_Point point, int size = 1);
void	drawArrow(VirtualScreen& screen, double x, double y, double dx, double dy);

#endif