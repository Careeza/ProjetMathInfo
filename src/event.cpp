#include <SDL2/SDL.h>
#include <functional>
#include "projet.hpp"
#include "timer.hpp"

bool	handleEvent(std::function<void(Info& info)> f1, std::function<void(Info& info)> f2, std::function<void(Info& info)> f3, Info& info)
{
	/* Handle the events*/
	int			x;
	int			y;
	int			button;
	bool		close_requested = false;
	SDL_Event	event;

	SDL_GetMouseState(&x, &y);
	info.setMouseInfo(x * info.getHighDPI(), y * info.getHighDPI(), true);
	info.setClickInfo(x * info.getHighDPI(), y * info.getHighDPI(), false);
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				close_requested = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						close_requested = true;
						break;
					case SDLK_a:
						f1(info);
						break;
					case SDLK_b:
						f2(info);
						break;
					case SDLK_c:
						f3(info);
						f3(info);
						f3(info);
						f3(info);
						f3(info);
						f3(info);
						f3(info);
						break;
					case SDLK_SPACE:
						if (!info.getTimer().is_paused()) {
							info.getTimer().pause();
						} else {
							info.getTimer().unpause();
						}
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&x, &y);
				info.setMouseInfo(x * info.getHighDPI(), y * info.getHighDPI(), true);
				break;
			case SDL_MOUSEBUTTONDOWN:
				button = SDL_GetMouseState(&x, &y);
				info.setClickInfo(x * info.getHighDPI(), y * info.getHighDPI(), button);
				break;
			default:
				break;
		}
	}
	return (!close_requested);
}