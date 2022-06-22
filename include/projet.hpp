#ifndef PROJET_HPP

# define PROJET_HPP

# include <SDL2/SDL.h>
# include <SDL2/SDL_timer.h>
# include <vector>
# include "draw.hpp"
# include "timer.hpp"
# include "point.hpp"
# include "polynome.hpp"
# include "screen.hpp"

void    bezierCurveLoop();
void    bezierCurveLoopGFX();
void    lissajousCurveLoop();

std::vector<Point<double>>  generateBezierPoints(Point<double> p1, Point<double> p2, int n, double y_min = -1, double y_max = 1);
std::vector<Point<double>>  generateNextPoints(std::vector<Point<double>> p, double t);


# if SDL_BYTEORDER == SDL_BIG_ENDIAN
    #define rmask 0xff000000
    #define gmask 0x00ff0000
    #define bmask 0x0000ff00
    #define amask 0x000000ff
# else
    #define rmask 0x000000ff
    #define gmask 0x0000ff00
    #define bmask 0x00ff0000
    #define amask 0xff000000
# endif

#endif