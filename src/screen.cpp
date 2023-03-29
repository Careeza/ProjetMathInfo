#include "screen.hpp"
#include <vector>

Screen::Screen(bool fullScreen) {
	int w;
	int h;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	if (fullScreen) {
		window = SDL_CreateWindow("Bezier", 0, 0, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
	} else {
		window = SDL_CreateWindow("Bezier", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_ALLOW_HIGHDPI);
	}
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	//no blend
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_NONE);
	SDL_GL_GetDrawableSize(window, &window_w, &window_h);
	SDL_GetWindowSize(window, &w, &h);
	highDPI = window_w / w;
	ratio = window_w / static_cast<double>(window_h);
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

int				Screen::getHighDPI() const {
	return (highDPI);
}

SDL_Window		*Screen::getWindow() const {
	return (window);
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
	// SDL_DestroyTexture(texture);
}

void	VirtualScreen::createPlan(Point<double> planUL, Point<double> planDR) {
	/* Create a plan */
	this->planUL = planUL;
	this->planDR = planDR;
	planW = abs(planUL.getX() - planDR.getX());
	planH = abs(planUL.getY() - planDR.getY());
}

Point<int>	VirtualScreen::convPoint(Point<double> p) {
	/* Convert a point from the plan to the screen */
	double	ratioX = (p.getX() - planUL.getX()) / planW;
	double	ratioY = -(p.getY() - planUL.getY()) / planH;
	Point<int> p_(ratioX * virtualRect.w, ratioY * virtualRect.h);
	return (p_);
}

Point<double>	VirtualScreen::convPoint(Point<int> p) {
	/* Convert a point from the screen to the plan */
	double	ratioX = p.getX() / static_cast<double>(virtualRect.w);
	double	ratioY = p.getY() / static_cast<double>(virtualRect.h);
	Point<double> p_(ratioX * planW + planUL.getX(), -ratioY * planH + planUL.getY());
	// Point<double> p_(ratioX * static_cast<double>(planW) + static_cast<double>(planUL.getX()),
	// 			ratioY * static_cast<double>(planH) - static_cast<double>(planUL.getY()));
	return (p_);
}

SDL_Point	VirtualScreen::convPointSDL(Point<double> p) {
	/* Convert a point from the plan to the screen */
	double	ratioX = (p.getX() - planUL.getX()) / planW;
	double	ratioY = -(p.getY() - planUL.getY()) / planH;
	SDL_Point p_ = {static_cast<int>(ratioX * virtualRect.w), static_cast<int>(ratioY * virtualRect.h)};
	return (p_);
}

void		VirtualScreen::startDraw() {
	/* Start drawing on the virtual screen */
	SDL_SetRenderTarget(S.render, texture);
	SDL_SetRenderDrawColor(S.render, 255, 255, 255, 255);
	SDL_RenderClear(S.render);
}

void		VirtualScreen::finishDraw() {
	/* Present the virtual screen on the screen */
	SDL_SetRenderTarget(S.render, NULL);
	SDL_RenderCopy(S.render, texture, NULL, &virtualRect);
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
