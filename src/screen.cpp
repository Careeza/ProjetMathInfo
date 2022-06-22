#include "screen.hpp"
#include <vector>

Screen::Screen(bool fullScreen) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	if (fullScreen) {
		window = SDL_CreateWindow("Bezier", 0, 0, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
	} else {
		window = SDL_CreateWindow("Ant", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_ALLOW_HIGHDPI);
	}
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
	SDL_GL_GetDrawableSize(window, &window_w, &window_h);
	ratio = window_w / static_cast<double>(window_h);
}

Screen::Screen(const Screen &screen) : window(screen.window), render(screen.render), window_w(screen.window_w), window_h(screen.window_h), ratio(screen.ratio) {
}

Screen::~Screen() {
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
}

int				Screen::getWindowW() const {
	return (window_w);
}

int				Screen::getWindowH() const {
	return (window_h);
}

double			Screen::getRatio() const {
	return (ratio);
}

SDL_Renderer	*Screen::getRenderer() const {
	return (render);
}

VirtualScreen::VirtualScreen(const Screen &screen, Flag flag) : S(screen) {

	virtualRect.x = 0;
	virtualRect.y = 0;
	virtualRect.w = S.window_w;
	virtualRect.h = S.window_h;
	if (flag == Flag::up) {
		virtualRect.h /= 2;
	} else if (flag == Flag::down) {
		virtualRect.h /= 2;
		virtualRect.y = virtualRect.h;
	}
	if (flag == Flag::left) {
		virtualRect.w /= 2;
	} else if (flag == Flag::right) {
		virtualRect.w /= 2;
		virtualRect.x = virtualRect.w;
	}
	ratio = virtualRect.w / static_cast<double>(virtualRect.h);
	texture = SDL_CreateTexture(S.render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, virtualRect.w, virtualRect.h);

}

VirtualScreen::~VirtualScreen() {
	SDL_DestroyTexture(texture);
}

void	VirtualScreen::createPlan(Point<double> planUL, Point<double> planDR) {
	this->planUL = planUL;
	this->planDR = planDR;
	planW = abs(planUL.getX() - planDR.getX());
	planH = abs(planUL.getY() - planDR.getY());
}

Point<int>	VirtualScreen::convPoint(Point<double> p) {
	double	ratioX = (p.getX() - planUL.getX()) / planW;
	double	ratioY = -(p.getY() - planUL.getY()) / planH;
	Point<int> p_(ratioX * virtualRect.w, ratioY * virtualRect.h);
	return (p_);
}

SDL_Point	VirtualScreen::convPointSDL(Point<double> p) {
	double	ratioX = (p.getX() - planUL.getX()) / planW;
	double	ratioY = -(p.getY() - planUL.getY()) / planH;
	SDL_Point p_ = {static_cast<int>(ratioX * virtualRect.w), static_cast<int>(ratioY * virtualRect.h)};
	return (p_);
}

void		VirtualScreen::startDraw() {
	SDL_SetRenderTarget(S.render, texture);
}

void		VirtualScreen::renderPresent() {
	SDL_SetRenderTarget(S.render, NULL);
	SDL_SetRenderDrawColor(S.render, 0, 0, 0, 255);
	SDL_RenderClear(S.render);
	SDL_RenderCopy(S.render, texture, NULL, &virtualRect);
	SDL_RenderPresent(S.render);
}

int			VirtualScreen::getVirtualW() const {
	return (virtualRect.w);
}

int			VirtualScreen::getVirtualH() const {
	return (virtualRect.h);
}

SDL_Renderer	*VirtualScreen::getRenderer() const {
	return (S.render);
}

double			VirtualScreen::getRatio() const {
	return (ratio);
}
