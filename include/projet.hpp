#ifndef PROJET_HPP

# define PROJET_HPP

# include <SDL2/SDL.h>
# include <SDL2/SDL_timer.h>
# include <vector>
# include <functional>
# include "draw.hpp"
# include "timer.hpp"
# include "point.hpp"
# include "polynome.hpp"
# include "screen.hpp"
# include "parametricPlot.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class Info {
	public:
		Info(bool fullScreen = true);
		~Info();
		void			addVirtualScreen(Flag f);
		VirtualScreen	*getCurrentScreen() const;
		void			selectScreen(int index);
		Timer			&getTimer();
		void			hideOrShowAlgo(bool show_);
		void			setMouseInfo(int x, int y, bool m);
		void			setClickInfo(int x, int y, int c);
		bool			showAlgo() const;
		int				getMouseX() const;
		int				getMouseY() const;
		int				getHighDPI() const;
		bool			getMouseMooved() const;
		int				getClicked() const;
		bool			getColorMap() const;
		void			setColorMap(bool b);
		void			renderPresent(bool save = false);

		std::vector<Point<double>>		getBezierPoints() const;
		void							setBezierPoints(std::vector<Point<double>> points);
		std::function<double(double)>	getXT() const;
		std::function<double(double)>	getYT() const;
		void							setXT(std::function<double(double)> f);
		void							setYT(std::function<double(double)> f);

	private:
		Screen  					S;
		std::vector<VirtualScreen>	Vscreens;
		std::vector<Point<double>>  bezierPoints;
		VirtualScreen				*screen;
		Timer						timer;
		bool						show;
		int							mouse_x;
		int							mouse_y;
		bool						mouseMooved;
		int							click;
		bool						colorMap;
		cv::VideoWriter				video;

		std::function<double(double)>	xt;
		std::function<double(double)>	yt;
};

void    bezierCurveLoop();
void    bezierCurveLoopGFX();
void    lissajousCurveLoop(int m, int n);
void    lissajousCurveLoop2(int m, int n);
void    cercleUniteCurveLoop();
void    bezierCurveCloseLoop();
void    filmBezierCurve();
void    polygoneBuilder();
void    indiceAnimationLoop(Info& info, Point<double> p);
void    indiceAnimationLoopPolygone(Info& info, Point<double> p, Polygone poly);
void	twoColorMapLoop(Info& info);
void    twoColorMapLoopImprove(Info& info);
void    representationAire(Info& info, Polygone &poly);

bool	handleEvent(std::function<void(Info& info)> f1, std::function<void(Info& info)> f2, std::function<void(Info& info)> f3, Info& info);
void	noneFunction(Info& info);
void	hideOrShowAlgo(Info& info);
void	changeBezierPoint(Info& info);
void	screenShot(Info& info);
void	launchColorMap(Info& info);
std::tuple<std::vector<Sint16>, std::vector<Sint16>>  convBezierPointsGFX(VirtualScreen &screen, std::vector<Point<double>> points);

bool	findPointNotColored(std::vector<std::vector<Case>>& map, int&x, int &y);
void	colorMapIterative(std::vector<std::vector<Case>>& map, int x, int y, int indice);


std::vector<Point<double>>  generateBezierPoints(Point<double> p1, Point<double> p2, int n, double y_min = -1, double y_max = 1);
std::vector<Point<double>>  generateBezierPointsLoop(Point<double> p1, int n, double y_min = -1, double y_max = 1);
std::vector<Point<double>>  generateNextPoints(std::vector<Point<double>> p, double t);
std::tuple<std::function<double(double)>, std::function<double(double)>>	bezierCurvePoly(std::vector<Point<double>> bezierPoints);

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