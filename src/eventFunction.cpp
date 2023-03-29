#include <SDL2/SDL.h>
#include <functional>
#include "projet.hpp"
#include "timer.hpp"
#include <SDL2/SDL_image.h>

void	noneFunction(Info& info) {
	/* Do nothing */
	(void)info;
}

void	hideOrShowAlgo(Info& info) {
	/* Hide or show the algo */
	info.hideOrShowAlgo(!info.showAlgo());
}

void	changeBezierPoint(Info& info) {
	/* Change the bezier point */
	info.setBezierPoints(generateBezierPointsLoop({0, 0}, 10));
}

void	launchColorMap(Info& info) {
	/* Launch the color map */
	twoColorMapLoopImprove(info);
}

void	screenShot(Info& info) {
	/* Take a screenshot */
	std::string 	filename = "screenshot/";
	SDL_Renderer	*render = info.getCurrentScreen()->getRenderer();
	static int i = 0;
	int	w;
	int	h;

	SDL_SetRenderTarget(render, NULL);
	SDL_GetRendererOutputSize(render, &w,&h);
	SDL_Surface *surface = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
	// SDL_Surface *surface = SDL_CreateRGBSurface(SDL_PIXELFORMAT_RGB888, w, h, 24, rmask, gmask, bmask, amask);
	SDL_LockSurface(surface);
	if (SDL_RenderReadPixels(render, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch) != 0) {
		std::cout << "Error : " << SDL_GetError() << std::endl;
	}
	std::string name =  "Bezier";
	// std::cin >> name;
	i++;
	filename += name + std::to_string(i) + ".png";
	SDL_UnlockSurface(surface);
	IMG_SavePNG(surface, filename.c_str());
	SDL_FreeSurface(surface);
	SDL_RenderPresent(render);
}