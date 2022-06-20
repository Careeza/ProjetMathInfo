#ifndef SCREEN_HPP

# define SCREEN_HPP

# include "point.hpp"
// # include "polynome.hpp"

# include <SDL2/SDL.h>
# include <SDL2/SDL_timer.h>

struct  Screen {
    SDL_Window		*window;
    SDL_Renderer	*render;
	int				window_w;
	int				window_h;
	Point<double>	virtualUL;
	Point<double>	virtualDR;
	double			virtual_w;
	double			virtual_h;
	double			ratio;
	Screen(bool fullScreen = true);
	~Screen();
	void	createVirtualScreen(Point<double> virtualUL, Point<double> virtualDR);
	Point<int>	convPoint(Point<double> p);
	SDL_Point	convPointSDL(Point<double> p);

};

#endif