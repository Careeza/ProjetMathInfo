#include <SDL2/SDL.h>
#include <functional>
#include "projet.hpp"
#include "timer.hpp"

bool	handleEvent(Timer& timer, std::function<void(Screen& screen)> f1, std::function<void(Screen& screen)> f2, Screen& screen)
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
						f1(screen);
						break;
					case SDLK_b:
						f2(screen);
						break;
					case SDLK_KP_SPACE:
						if (timer.is_started()) {
							timer.pause();
						} else {
							timer.unpause();
						}
						break;
					default:
						break;
				}
				break;
		}
	}
	return (close_requested);
}