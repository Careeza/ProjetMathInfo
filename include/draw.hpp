#ifndef DRAW_HPP

# define DRAW_HPP

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include "screen.hpp"
# include "point.hpp"
# include "polynome.hpp"
# include "polygone.hpp"
# include "mathBonus.hpp"
# include <vector>

extern TTF_Font	*my_font;

void	drawLine(VirtualScreen& screen, Point<double> p1, Point<double> p2);
void	drawLine(VirtualScreen& screen, Point<double> p1, Point<double> p2, int size, int r, int g, int b);
void	drawLines(VirtualScreen& screen, const std::vector<Point<double>>& points);
void	drawLines(VirtualScreen& screen, const std::vector<Point<double>>& points, int size, int r, int g, int b);
void	drawPoint(VirtualScreen& screen, SDL_Point point, int size = 1);
void	drawPoints(VirtualScreen& screen, std::vector<Point<double>> points, int size);
void	drawArrow(VirtualScreen& screen, double x, double y, double dx, double dy);
void	drawArrowAngle(VirtualScreen& screen, Point<double> p, double angle, int size);
void	drawPointCoord(VirtualScreen& screen, Point<double> p, int x, int y);
void	drawCircleIndice(VirtualScreen& screen, Point<double> p, double angle0, double indice, int radius = 150);
void	drawPolygone(VirtualScreen& screen, Polygone polygone, int size = 1, int r = 0, int g = 0, int b = 0);
void	drawPointPolygone(VirtualScreen& screen, Polygone poly, int size, int r, int g, int b, double t);
void	drawPolygoneOnMap(VirtualScreen& screen, Polygone& poly, std::vector<std::vector<Case>> &map);

#endif