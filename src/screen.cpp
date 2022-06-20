#include "screen.hpp"
#include <vector>

Screen::Screen(bool fullScreen) {
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
	ratio = window_w / static_cast<double>(window_h);
}
Screen::~Screen() {
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
}

void	Screen::createVirtualScreen(Point<double> virtualUL, Point<double> virtualDR) {
	this->virtualDR = virtualDR;
	this->virtualUL = virtualUL;
	virtual_w = abs(virtualUL.getX() - virtualDR.getX());
	virtual_h = abs(virtualUL.getY() - virtualDR.getY());
}


Point<int>	Screen::convPoint(Point<double> p) { 
	double	ratioX = (p.getX() - virtualUL.getX()) / virtual_w;
	double	ratioY = -(p.getY() - virtualUL.getY()) / virtual_h;
	Point<int> p_(ratioX * window_w, ratioY * window_h);
	return (p_);
};


SDL_Point	Screen::convPointSDL(Point<double> p) { 
	double	ratioX = (p.getX() - virtualUL.getX()) / virtual_w;
	double	ratioY = -(p.getY() - virtualUL.getY()) / virtual_h;
	SDL_Point p_ = {static_cast<int>(ratioX * window_w), static_cast<int>(ratioY * window_h)};
	return (p_);
};