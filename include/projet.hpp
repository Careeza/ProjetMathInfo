#ifndef PROJET_HPP

# define PROJET_HPP

# include <SDL2/SDL.h>
# include <SDL2/SDL_timer.h>
# include "timer.hpp"
# include "point.hpp"
# include "polynome.hpp"

struct  Screen {
    SDL_Window		*window;
    SDL_Renderer	*render;
	int				window_w;
	int				window_h;
	Point<double>	virtualUL;
	Point<double>	virtualDR;
	double			virtual_w;
	double			virtual_h;
	Screen(bool fullScreen = true) {
		virtualDR = {1, -1};
		virtualUL = {-1, 1};
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
		if (fullScreen) {
			window = SDL_CreateWindow("Bezier", 0, 0, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
		} else {
			window = SDL_CreateWindow("Ant", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_ALLOW_HIGHDPI);
		}
		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
		SDL_GL_GetDrawableSize(window, &window_w, &window_h);
	};
	~Screen() {
		SDL_DestroyRenderer(render);
	    SDL_DestroyWindow(window);
	};
	void	createVirtualScreen(Point<double> virtualUL, Point<double> virtualDR) {
		this->virtualDR = virtualDR;
		this->virtualUL = virtualUL;
		virtual_w = abs(virtualUL.getX() - virtualDR.getX());
		virtual_h = abs(virtualUL.getY() - virtualDR.getY());
	};
	Point<int>	convPoint(Point<double> p) { 
		double	ratioX = (p.getX() - virtualUL.getX()) / virtual_w;
		double	ratioY = -(p.getY() - virtualUL.getY()) / virtual_h;
		Point<int> p_(ratioX * window_w, ratioY * window_h);
		return (p_);
	};
	SDL_Point	convPointSDL(Point<double> p, double scale = 1) { 
		double	ratioX = (p.getX() - virtualUL.getX()) / (virtual_w * scale);
		double	ratioY = -(p.getY() - virtualUL.getY()) / (virtual_h * scale);
		SDL_Point p_ = {static_cast<int>(ratioX * window_w), static_cast<int>(ratioY * window_h)};
		return (p_);
	};

};

void	drawLine(Screen& screen, Point<double> p1, Point<double> p2);
void	drawLines(Screen& screen, std::vector<Point<double>>& points);
void	drawPoly(Screen& screen, Poly& px, Poly& py, double maxT);
void	drawPoint(Screen& screen, SDL_Point point, int size = 1);


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