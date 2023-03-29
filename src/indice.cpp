#include <SDL2/SDL_ttf.h>
#include <tuple>
#include <string>
#include "projet.hpp"
#include "polygone.hpp"
#include "indice.hpp"
#include "mathBonus.hpp"
#include <boost/math/constants/constants.hpp>
#include <tuple>

void	drawIndice(Info& info, int indice) {
	/* Draw the numerival value of the indice near the mouse */
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	VirtualScreen	*screen;
	SDL_Color		color;
	SDL_Rect		TextRect;
	SDL_Rect		rect;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	screen = info.getCurrentScreen();
	surface = TTF_RenderText_Blended(my_font, std::to_string(indice).c_str(), color);
	TTF_SizeText(my_font, std::to_string(indice).c_str(), &TextRect.w, &TextRect.h);
	texture = SDL_CreateTextureFromSurface(screen->getRenderer(), surface);
	TextRect.x = info.getMouseX() - TextRect.w;
	TextRect.y = info.getMouseY() - TextRect.h;
	rect = {TextRect.x - 5, TextRect.y - 2, TextRect.w + 10, TextRect.h + 4};
	SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(screen->getRenderer(), &rect);
	SDL_RenderCopy(screen->getRenderer(), texture, NULL, &TextRect);
}

void	drawIndice(Info& info, double indice) {
	/* Draw the numerival value of the indice near the mouse */
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	VirtualScreen	*screen;
	SDL_Color		color;
	SDL_Rect		TextRect;
	SDL_Rect		rect;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	screen = info.getCurrentScreen();
	surface = TTF_RenderText_Blended(my_font, std::to_string(indice).c_str(), color);
	TTF_SizeText(my_font, std::to_string(indice).c_str(), &TextRect.w, &TextRect.h);
	texture = SDL_CreateTextureFromSurface(screen->getRenderer(), surface);
	TextRect.x = info.getMouseX() - TextRect.w;
	TextRect.y = info.getMouseY() - TextRect.h;
	rect = {TextRect.x - 5, TextRect.y - 2, TextRect.w + 10, TextRect.h + 4};
	SDL_SetRenderDrawColor(screen->getRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(screen->getRenderer(), &rect);
	SDL_RenderCopy(screen->getRenderer(), texture, NULL, &TextRect);
}

std::function<double(double)>	inIntegralFunction(std::function<double(double)> xt, std::function<double(double)> yt, Point<double> p) {
	/* return the function used in the integeal */
	std::function<double(double)> at;
	std::function<double(double)> bt;
	tie(at, bt) = shiftFunction(xt, yt, p);
	tie(at, bt) = normalizeFunction(at, bt);
	std::function<double(double)> I = {[at, bt](double t) {return (at(t) * derivate(bt, t) - bt(t) * derivate(at, t));}};
	return (I);
}

int		calcIndice(std::function<double(double)> xt, std::function<double(double)> yt, Point<double> p) {
	/* Calculate the indice of the function at the point p*/
	std::function<double(double)>	I = inIntegralFunction(xt, yt, p);
	return (round((integrate(0, 1, I, 10000)) / (2 * M_PI)));
}

double	calcIndicePart(std::function<double(double)> xt, std::function<double(double)> yt, Point<double> p, double t) {
	/* Calculate the indice of the function at the point p at the time t*/
	if (t < 0 || t > 1)
		return (0);

	std::function<double(double)>	I = inIntegralFunction(xt, yt, p);
	return (integrate(0, t, I, 10000));
}

int		calcIndice(Polygone poly, Point<double> p) {
	std::function<double(double)> 	xt;
	std::function<double(double)> 	yt;
	std::vector<Point<double>>		points;
	double							indice;

	points = poly.getPoints();
	if (points.size() < 3)
		return (0);
	indice = 0;
	for (int i = 0; i < points.size(); i++) {
		tie(xt, yt) = lineFunction(points[i], points[(i + 1) % points.size()]);
		indice += calcIndicePart(xt, yt, p, 1);
	}
	return (round(indice / (2 * M_PI)));
}

double	calcIndicePart(Polygone poly, Point<double> p, double t) {
	std::function<double(double)> 	xt;
	std::function<double(double)> 	yt;
	std::vector<Point<double>>		points;
	double							indice = 0;
	int								nbLineTravel;

	points = poly.getPoints();
	if (points.size() < 3)
		return (0);
	nbLineTravel = t / (1.0 / static_cast<double>(points.size()));
	for (int i = 0; i < nbLineTravel; i++) {
		tie(xt, yt) = lineFunction(points[i], points[(i + 1) % points.size()]);
		indice += calcIndicePart(xt, yt, p, 1);
	}
	t = (t - nbLineTravel * (1.0 / static_cast<double>(points.size()))) * static_cast<double>(points.size());
	if (t > 0) {
		tie(xt, yt) = lineFunction(points[nbLineTravel], points[(nbLineTravel + 1) % points.size()]);
		indice += calcIndicePart(xt, yt, p, t);
	}
	return (indice);
}

int		calcIndice2(std::function<double(double)> xt, std::function<double(double)> yt) {
	/* Calculate the indice of the function at the point p*/
	std::function<double(double)>	I = inIntegralFunction(derivateFunction(xt), derivateFunction(yt), Point<double>(0, 0));
	return (round((integrate(0, 1, I, 10000)) / (2 * M_PI)));
}

double	calcIndicePart2(std::function<double(double)> xt, std::function<double(double)> yt, double t) {
	/* Calculate the indice of the function at the point p at the time t*/
	if (t < 0 || t > 1)
		return (0);
	std::function<double(double)>	I = inIntegralFunction(derivateFunction(xt), derivateFunction(yt), Point<double>(0, 0));
	return (integrate(0, t, I, 1000));
}