#ifndef INDEX_HPP

# define INDEX_HPP

#include <SDL2/SDL_ttf.h>
#include "projet.hpp"

extern TTF_Font	*my_font;

void	drawIndex(Info& info, int index);
int		calcIndex(std::function<double(double)> xt, std::function<double(double)> yt, Point<double> p);

#endif