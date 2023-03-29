#include "draw.hpp"
#include "projet.hpp"
#include "point.hpp"
#include "mathBonus.hpp"
#include "polynome.hpp"
#include "polygone.hpp"
#include <vector>
#include "SDL2_gfxPrimitives.h"

void	drawLine(VirtualScreen& screen, Point<double> p1, Point<double> p2) {
	/* Draw a line between two points*/
	Point<int>	p1_ = screen.convPoint(p1);
	Point<int>	p2_ = screen.convPoint(p2);

	SDL_RenderDrawLine(screen.getRenderer(), p1_.getX(), p1_.getY(), p2_.getX(), p2_.getY());
}

void	drawLine(VirtualScreen& screen, Point<double> p1, Point<double> p2, int size, int r, int g, int b) {
	/* Draw a line between two points*/
	Point<int>	p1_ = screen.convPoint(p1);
	Point<int>	p2_ = screen.convPoint(p2);

	thickLineRGBA(screen.getRenderer(), p1_.getX(), p1_.getY(), p2_.getX(), p2_.getY(), size, r, g, b, 255);
}

void	drawLines(VirtualScreen& screen, const std::vector<Point<double>>& points) {
	/* Draw all the lines between the points*/
	std::vector<SDL_Point>	pointsSDL;

	for (Point<double> p : points) {
		pointsSDL.push_back(screen.convPointSDL(p));
	}
	SDL_RenderDrawLines(screen.getRenderer(), &pointsSDL[0], pointsSDL.size());
}

void	drawLines(VirtualScreen& screen, const std::vector<Point<double>>& points, int size, int r, int g, int b) {
	/* Draw all the lines between the points*/
	std::vector<SDL_Point>	pointsSDL;

	for (Point<double> p : points) {
		pointsSDL.push_back(screen.convPointSDL(p));
	}
	for (size_t i = 0; i < pointsSDL.size() - 1; i++) {
		thickLineRGBA(screen.getRenderer(), pointsSDL[i].x, pointsSDL[i].y, pointsSDL[i + 1].x, pointsSDL[i + 1].y, size, r, g, b, 255);
	}
}

void	drawPoint(VirtualScreen& screen, SDL_Point point, int size) {
	/* Draw a point*/
	std::vector<SDL_Point>	points;

	points.push_back(point);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			points.push_back({point.x + i - size / 2, point.y + j - size / 2});
		}
	}
	SDL_RenderDrawPoints(screen.getRenderer(), &points[0], points.size());
}

void	drawPoints(VirtualScreen& screen, std::vector<Point<double>> points, int size) {
	for (Point<double> p : points) {
		drawPoint(screen, screen.convPointSDL(p), size);
	}
}

void	drawArrow(VirtualScreen& screen, double x, double y, double dx, double dy) {
	/* Draw an arrow*/
	SDL_Point p1 = screen.convPointSDL({x, y});
	SDL_Point p2 = screen.convPointSDL({x + dx, y + dy});
	
	thickLineRGBA(screen.getRenderer(), p1.x, p1.y, p2.x, p2.y, 7, 0xFF, 0, 0, 0xFF);

	double	x1 = x + dx + (dx * 0.2);
	double	y1 = y + dy + (dy * 0.2);
	
	double	x2 = x + dx - (dy * 0.2);
	double	y2 = y + dy + (dx * 0.2);

	double	x3 = x + dx + (dy * 0.2);
	double	y3 = y + dy - (dx * 0.2);

	p1 = screen.convPointSDL({x1, y1});
	p2 = screen.convPointSDL({x2, y2});
	SDL_Point p3 = screen.convPointSDL({x3, y3});
	filledTrigonRGBA(screen.getRenderer(), p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, 255, 0, 0, 255);
}

void	drawArrowAngle(VirtualScreen& screen, Point<double> p, double angle, int size) {
	/* Draw an arrow with an angle*/
	double	x = p.getX();
	double	y = p.getY();
	int		dx = cos(angle) * size;
	int		dy = -sin(angle) * size;
	
	SDL_Point p1 = screen.convPointSDL({x, y});
	SDL_Point p2;
	p2.x = p1.x + dx;
	p2.y = p1.y + dy;
	
	thickLineRGBA(screen.getRenderer(), p1.x, p1.y, p2.x, p2.y, 14, 0xFF, 0, 0, 0xFF);

	SDL_Point	p3;
	p3.x = p1.x + dx * 1.2;
	p3.y = p1.y + dy * 1.2;
	SDL_Point	p4;
	p4.x = p1.x + dx - dy * 0.2;
	p4.y = p1.y + dy + dx * 0.2;
	SDL_Point	p5;
	p5.x = p1.x + dx + dy * 0.2;
	p5.y = p1.y + dy - dx * 0.2;
	filledTrigonRGBA(screen.getRenderer(), p3.x, p3.y, p4.x, p4.y, p5.x, p5.y, 255, 0, 0, 255);
}

void	drawPointCoord(VirtualScreen& screen, Point<double> p, int x, int y) {
	/* Draw the coordinate value of the mouse*/
	std::string		text = std::to_string(p.getX()) + ", " + std::to_string(p.getY());
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	SDL_Color		color;
	SDL_Rect		TextRect;
	SDL_Rect		rect;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	surface = TTF_RenderText_Blended(my_font, text.c_str(), color);
	TTF_SizeText(my_font, text.c_str(), &TextRect.w, &TextRect.h);
	texture = SDL_CreateTextureFromSurface(screen.getRenderer(), surface);
	TextRect.x = x + TextRect.w;
	TextRect.y = y - TextRect.h;
	rect = {TextRect.x - 5, TextRect.y - 2, TextRect.w + 10, TextRect.h + 4};
	SDL_SetRenderDrawColor(screen.getRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(screen.getRenderer(), &rect);
	SDL_RenderCopy(screen.getRenderer(), texture, NULL, &TextRect);
}

double	convAngleGFX(double angle) {
	/* Convert an angle from radian to degree in anti clockwise*/
	if (angle <= 0) {
		return(-angle);
	} else {
		return(2 * M_PI - angle);
	}
}

void	drawCircleIndice(VirtualScreen& screen, Point<double> p, double angle0, double indice, int radius) {
	/* Draw a circle with an indice*/
	int		color;

	if (indice < 0) {
		color = 0xFFFF0000;
	} else {
		color = 0xFF0000FF;
	}
	while (radianToDegree(abs(indice)) >= 360) {
		if (indice < 0) {
			indice += 2 * M_PI;
		} else {
			indice -= 2 * M_PI;
		}
		thickCircleColor(screen.getRenderer(), screen.convPointSDL(p).x, screen.convPointSDL(p).y, radius, color, 10);
		radius += 50;
	}
	angle0 = convAngleGFX(angle0);
	int	angleSart = radianToDegree(angle0);
	int	angleFinal = angleSart - radianToDegree(indice);
	// indice = angle0 - indice;
	if (angleSart > angleFinal) {
		std::swap(angleSart, angleFinal);
	}
	thickArcColor(screen.getRenderer(), screen.convPointSDL(p).x, screen.convPointSDL(p).y, radius, angleSart, angleFinal, color, 10);
}

void	drawCircles(VirtualScreen& screen, std::vector<Point<double>>& points, int radius, int r, int g, int b) {
	/* Draw the circles*/
	for (int i = 0; i < points.size(); i++) {
		filledCircleRGBA(screen.getRenderer(), screen.convPointSDL(points[i]).x, screen.convPointSDL(points[i]).y, radius, r, g, b, 255);
	}
}

void	drawPolygone(VirtualScreen& screen, Polygone poly, int size, int r, int g, int b) {
	std::vector<Point<double>>	points = poly.getPoints();
	if (poly.isClosed()) {
		drawLines(screen, points, size, r, g, b);
		drawLine(screen, points[0], points[points.size() - 1], size, r, g, b);
	}
	if (points.size() > 0) {
		drawCircles(screen, points, size * 3, r, g, b);
	}
}

void	drawPointPolygone(VirtualScreen& screen, Polygone poly, int size, int r, int g, int b, double t) {
	std::function<double(double)> 	xt;
	std::function<double(double)> 	yt;
	std::vector<Point<double>>		points;
	int								nbLineTravel;

	points = poly.getPoints();
	if (points.size() < 3)
		return ;
	nbLineTravel = t / (1.0 / static_cast<double>(points.size()));
	t = (t - nbLineTravel * (1.0 / static_cast<double>(points.size()))) * static_cast<double>(points.size());
	std::cout << "t = " << t << std::endl;
	tie(xt, yt) = lineFunction(points[nbLineTravel % points.size()], points[(nbLineTravel + 1) % points.size()]);
	SDL_Point	p1 = screen.convPointSDL({xt(t), yt(t)});
	filledCircleRGBA(screen.getRenderer(), p1.x, p1.y, size, r, g, b, 255);
}

void	drawPolygoneOnMap(VirtualScreen& screen, Polygone& poly, std::vector<std::vector<Case>> &map) {
	double	pas = 1 / static_cast<double>(screen.getVirtualW()) / 8.0;
	std::function<double(double)> 	xt;
	std::function<double(double)> 	yt;
	std::vector<Point<double>>		points;

	points = poly.getPoints();
	if (points.size() < 3)
		return ;
	for (int i = 0; i < points.size(); i++) {
		tie(xt, yt) = lineFunction(points[i], points[(i + 1) % points.size()]);
		for (double t = 0; t <= 1; t += pas) {
			double x = xt(t);
			double y = yt(t);
			SDL_Point point = screen.convPointSDL({x, y});
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (point.x + i >= 0 && point.x + i < map.size() && point.y + j >= 0 && point.y + j < map[0].size()) {
						map[point.x + i][point.y + j].colored = true;
						map[point.x + i][point.y + j].onCurve = true;
					}
				}
			}
		}
	}
}

/*void	PPlot::plotOnMap(VirtualScreen &screen, double tStart, double tEnd, std::vector<std::vector<Case>> &map) {
	double	w = tEnd - tStart;
	double	pas = w / static_cast<double>(screen.getVirtualW()) / 8.0;

	if (w == 0)
		return ;
	for (double t = tStart; t <= tEnd; t += pas) {
		double x = xt_(t);
		double y = yt_(t);
		SDL_Point point = screen.convPointSDL({x, y});
		for (int i = -3; i <= 3; i++) {
			for (int j = -3; j <= 3; j++) {
				if (point.x + i >= 0 && point.x + i < map.size() && point.y + j >= 0 && point.y + j < map[0].size()) {
					map[point.x + i][point.y + j].colored = true;
					map[point.x + i][point.y + j].onCurve = true;
				}
			}
		}
	}
}
*/