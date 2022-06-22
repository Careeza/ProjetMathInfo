#include <SDL2/SDL.h>
#include <functional>
#include "projet.hpp"
#include "timer.hpp"

bool	handleEvent(std::function<void(Info& info)> f1, std::function<void(Info& info)> f2, Info& info)
{
	bool		close_requested = false;
	SDL_Event	event;

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
		}
	}
	return (!close_requested);
}