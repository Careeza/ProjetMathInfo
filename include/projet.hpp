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

class Info {
	public:
		Info(bool fullScreen = true);
		~Info();
		void			addVirtualScreen(Flag f);
		VirtualScreen	*getCurrentScreen() const;
		void			selectScreen(int index);
		Timer			&getTimer();
		void			hideOrShowAlgo(bool show_);
		bool			showAlgo() const;

	private:
		Screen  					S;
		std::vector<VirtualScreen>	Vscreens;
		VirtualScreen				*screen;
		Timer						timer;
		bool						show;
		int							mouse_x;
		int							mouse_y;
		bool						mooseMooved;
};

void    bezierCurveLoop();
void    bezierCurveLoopGFX();
void    lissajousCurveLoop();
void    polygoneLoop();
bool	handleEvent(std::function<void(Info& info)> f1, std::function<void(Info& info)> f2, Info& info);
void	noneFunction(Info& info);
void	hideOrShowAlgo(Info& info);

std::vector<Point<double>>  generateBezierPoints(Point<double> p1, Point<double> p2, int n, double y_min = -1, double y_max = 1);
std::vector<Point<double>>  generateNextPoints(std::vector<Point<double>> p, double t);


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