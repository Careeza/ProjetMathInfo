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
	protected:
		SDL_Window		*window;
		SDL_Renderer	*render;
		int				window_w;
		int				window_h;
		double			ratio;

	public:
		Screen(bool fullScreen = true);
		Screen(const Screen &screen);
		~Screen();
		double			getRatio() const;
		int				getWindowW() const;
		int				getWindowH() const;
		SDL_Renderer	*getRenderer() const;
};


class VirtualScreen : public Screen {
	public:
		VirtualScreen(const Screen &screen, Flag flag);
		~VirtualScreen();
		void		createPlan(Point<double> planUL, Point<double> planDR);
		Point<int>	convPoint(Point<double> p);
		SDL_Point	convPointSDL(Point<double> p);

		void		startDraw();
		void		renderPresent();

		int			getVirtualW() const;
		int			getVirtualH() const;
	private:
		SDL_Rect		virtualRect;
		double			planW;
		double			planH;
		Point<double>	planUL;
		Point<double>	planDR;
		SDL_Texture		*texture;
};

#endif