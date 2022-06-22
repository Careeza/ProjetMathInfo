#include <SDL2/SDL_ttf.h>
#include <tuple>
#include <string>
#include "projet.hpp"
#include "index.hpp"
#include "mathBonus.hpp"
#include <boost/math/constants/constants.hpp>

void	drawIndex(Info& info, int index) {
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	VirtualScreen	*screen;
	SDL_Color		color;
	SDL_Rect		TextRect;
	SDL_Rect		rect;

	// TTF_Font *my_font = TTF_OpenFont("ressource/Keyboard.ttf", 20);
	if(!my_font) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
	// handle error
	}

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	screen = info.getCurrentScreen();
	surface = TTF_RenderText_Blended(my_font, std::to_string(index).c_str(), color);
	TTF_SizeText(my_font, std::to_string(index).c_str(), &TextRect.w, &TextRect.h);
	texture = SDL_CreateTextureFromSurface(screen->getRenderer(), surface);
	TextRect.x = info.getMouseX() - TextRect.w;
	TextRect.y = info.getMouseY() - TextRect.h;
	rect = {TextRect.x - 5, TextRect.y - 2, TextRect.w + 10, TextRect.h + 4};
	SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(screen->getRenderer(), &rect);
	SDL_RenderCopy(screen->getRenderer(), texture, NULL, &TextRect);
}

std::tuple<std::function<double(double)>, std::function<double(double)>>	shiftFunction(std::function<double(double)> xt, std::function<double(double)> yt, Point<double> p) {
	double	x = p.getX();
	double	y = p.getY();

	std::function<double(double)> xt_ = {[x, xt](double t) {return (xt(t) - x);}};
	std::function<double(double)> yt_ = {[y, yt](double t) {return (yt(t) - y);}};
	return (std::make_tuple(xt_, yt_));
}


std::tuple<std::function<double(double)>, std::function<double(double)>>	normalizeFunction(std::function<double(double)> xt, std::function<double(double)> yt, Point<double> p) {
	std::function<double(double)> xt_;
	std::function<double(double)> yt_;

	tie(xt_, yt_) = shiftFunction(xt, yt, p);
	std::function<double(double)> at = {[p, xt_, yt_](double t) {return (normalizeX(xt_(t), yt_(t)));}};
	std::function<double(double)> bt = {[p, xt_, yt_](double t) {return (normalizeY(xt_(t), yt_(t)));}};
	return (std::make_tuple(at, bt));
}


std::function<double(double)>	inIntegralFunction(std::function<double(double)> xt, std::function<double(double)> yt, Point<double> p) {
	std::cout << "inIntegralFunction" << std::endl;
	std::function<double(double)> at;
	std::function<double(double)> bt;
	tie(at, bt) = normalizeFunction(xt, yt, p);
	std::cout << at(0) << ", " << bt(0) << std::endl;
	std::cout << at(0) * derivate(bt, 0) - bt(0) * derivate(at, 0) << std::endl;
	std::function<double(double)> I = {[at, bt](double t) {return (at(t) * derivate(bt, t) - bt(t) * derivate(at, t));}};
	std::cout << "inIntegralFunction =, " << I(0) << std::endl;
	return (I);
}

int		calcIndex(std::function<double(double)> xt, std::function<double(double)> yt, Point<double> p) {
	std::cout << xt(0) << ", " << yt(0) << std::endl;
	std::function<double(double)>	I = inIntegralFunction(xt, yt, p);
	return (round(integrate(0, 1, I, 100) / (2 * boost::math::constants::pi<double>())));
}