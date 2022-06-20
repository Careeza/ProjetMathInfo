#ifndef DRAW_HPP

# define DRAW_HPP

# include <SDL2/SDL.h>
# include "screen.hpp"
# include "point.hpp"
# include "polynome.hpp"
# include <vector>

void	drawLine(Screen& screen, Point<double> p1, Point<double> p2);
void	drawLines(Screen& screen, const std::vector<Point<double>>& points);
void	drawPoly(Screen& screen, Poly& px, Poly& py, double maxT);
void	drawPoint(Screen& screen, SDL_Point point, int size = 1);

#endif