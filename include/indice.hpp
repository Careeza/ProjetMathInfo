#ifndef INDICE_HPP

# define INDICE_HPP

#include "projet.hpp"
#include "draw.hpp"

void	drawIndice(Info& info, int index);
void	drawIndice(Info& info, double index);
int		calcIndice(std::function<double(double)> xt, std::function<double(double)> yt, Point<double> p);
int		calcIndice(Polygone poly, Point<double> p);
double	calcIndicePart(std::function<double(double)> xt, std::function<double(double)> yt, Point<double> p, double t);
double	calcIndicePart(Polygone poly, Point<double> p, double t);
std::tuple<std::function<double(double)>, std::function<double(double)>>	shiftFunction(std::function<double(double)> xt, std::function<double(double)> yt, Point<double> p);
int		calcIndice2(std::function<double(double)> xt, std::function<double(double)> yt);
double	calcIndicePart2(std::function<double(double)> xt, std::function<double(double)> yt, double t);

#endif