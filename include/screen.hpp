#ifndef SCREEN_HPP

# define SCREEN_HPP

# include "point.hpp"
// # include "polynome.hpp"

# include <SDL2/SDL.h>
# include <SDL2/SDL_timer.h>

enum struct Flag {
	left,
	right,
	up,
	down,
	full,
};

class  Screen {
	friend class VirtualScreen;
	private:
		SDL_Window		*window;
		SDL_Renderer	*render;
		int				window_w;
		int				window_h;
		int				highDPI;
		double			ratio;

	public:
		Screen(bool fullScreen = true);
		~Screen();
		double			getRatio() const;
		int				getWindowW() const;
		int				getWindowH() const;
		int				getHighDPI() const;
		SDL_Renderer	*getRenderer() const;
		SDL_Window		*getWindow() const;
};


class VirtualScreen {
	public:
		VirtualScreen(const Screen &screen, Flag flag);
		~VirtualScreen();
		void			createPlan(Point<double> planUL, Point<double> planDR);
		Point<int>		convPoint(Point<double> p);
		Point<double>	convPoint(Point<int> p);
		SDL_Point		convPointSDL(Point<double> p);

		void		startDraw();
		void		finishDraw();

		int			getVirtualW() const;
		int			getVirtualH() const;

		SDL_Renderer	*getRenderer() const;
		double			getRatio() const;
	private:
		const Screen	&S;
		double			ratio;
		SDL_Rect		virtualRect;
		double			planW;
		double			planH;
		Point<double>	planUL;
		Point<double>	planDR;
		SDL_Texture		*texture;
};

#endif