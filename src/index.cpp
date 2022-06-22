#include <SDL2/SDL_ttf.h>
#include "projet.hpp"
#include "index.hpp"

void	drawIndex(Info& info, int index) {
	SDL_Surface		*surface;
	SDL_Color		color;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	surface = TTF_RenderText_Blended(my_font, static_cast<std::string>(index).c_str(), color);
	// return (surface);
}