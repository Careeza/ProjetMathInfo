#include <SDL2/SDL.h>
#include <functional>
#include "projet.hpp"
#include "timer.hpp"

void	noneFunction(Info& info)
{
	(void)info;
}

void	hideOrShowAlgo(Info& info)
{
	info.hideOrShowAlgo(!info.showAlgo());
}
