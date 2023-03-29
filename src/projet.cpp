#include "projet.hpp"
#include "indice.hpp"
#include "mathBonus.hpp"
#include "timer.hpp"
#include <boost/program_options.hpp>
#include <boost/math/constants/constants.hpp>
#include <SDL2/SDL_ttf.h>
#include <functional>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <SDL2/SDL_image.h>

TTF_Font *my_font = NULL;

Info::Info(bool fullScreen) : S(fullScreen), show(true) {
	TTF_Init();
	my_font = TTF_OpenFont("ressource/HelveticaNeue.ttc", 35);
	setMouseInfo(0, 0, false);
	click = false;
	std::cout << "Info constructor" << std::endl;
	std::cout << S.getWindowW() << std::endl;
	std::cout << S.getWindowH() << std::endl;
	video.open("video.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(S.getWindowW(), S.getWindowH()), true);
	if ( !video.isOpened() ) {
		std::cout << "Cannot open the video file" << std::endl;
	} else {
		std::cout << "Video file opened" << std::endl;
	}
	colorMap = false;
}

Info::~Info() {
	std::cout << "Info destructor" << std::endl;
	video.release();
}

void			Info::addVirtualScreen(Flag f) {
    Vscreens.emplace_back(S, f);
    screen = &Vscreens.back();
}

VirtualScreen	*Info::getCurrentScreen() const {
    return (screen);
}

void			Info::selectScreen(int index) {
    screen = &(Vscreens[index]);
}

Timer			&Info::getTimer() {
    return (timer);
}

void			Info::hideOrShowAlgo(bool show_) {
    show = show_;
}

void			Info::setMouseInfo(int x, int y, bool m) {
	mouse_x = x;
	mouse_y = y;
	mouseMooved = m;
}

void			Info::setClickInfo(int x, int y, int c) {
	mouse_x = x;
	mouse_y = y;
	click = c;
}

bool			Info::showAlgo() const {
    return (show);
}

int				Info::getHighDPI() const {
	return (S.getHighDPI());
}

int				Info::getMouseX() const {
	return (mouse_x);
}

int				Info::getMouseY() const {
	return (mouse_y);
}

bool			Info::getMouseMooved() const {
	return (mouseMooved);
}

int				Info::getClicked() const {
	return (click);
}

std::vector<Point<double>>	Info::getBezierPoints() const {
	return (bezierPoints);
}

void						Info::setBezierPoints(std::vector<Point<double>> points) {
	bezierPoints = points;
	tie(xt, yt) = bezierCurvePoly(bezierPoints);
}

bool			Info::getColorMap() const {
	return (colorMap);
}

void			Info::setColorMap(bool b) {
	colorMap = b;
}

std::function<double(double)>	Info::getXT() const {
	return (xt);
}

std::function<double(double)>	Info::getYT() const {
	return (yt);
}

void			Info::setXT(std::function<double(double)> f) {
	xt = f;
}

void			Info::setYT(std::function<double(double)> f) {
	yt = f;
}

cv::Mat	convScreenToMat(SDL_Renderer *render) {
	static int i = 0;
	std::string filename = "screenshot/screenshot" + std::to_string(i) + ".png";
	int	w;
	int	h;

	SDL_GetRendererOutputSize(render, &w, &h);
	SDL_Surface *surface = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
	// SDL_Surface *surface = SDL_CreateRGBSurface(SDL_PIXELFORMAT_RGB888, w, h, 24, rmask, gmask, bmask, amask);
	SDL_LockSurface(surface);
	if (SDL_RenderReadPixels(render, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch) != 0)
		std::cout << "Error : " << SDL_GetError() << std::endl;
	// SDL_RenderReadPixels(render, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
	
	SDL_UnlockSurface(surface);

	std::cout << "render Format = " << SDL_GetPixelFormatName(surface->format->format) << std::endl;

	// SDL_Texture	*texture = SDL_CreateTextureFromSurface(render, surface);
	// if (!texture)
	// 	std::cout << "Error : " << SDL_GetError() << std::endl;
	// uint32_t format;
	// SDL_QueryTexture(texture, &format, NULL, &w, &h);
	// std::cout << format << " fomat : " << std::endl;
	// std::cout << SDL_PIXELFORMAT_ARGB8888 << " Wanted format : " << std::endl;
	// std::cout << SDL_PIXELFORMAT_RGB888 << " Format not wanted : " << std::endl;
	// std::cout << SDL_PIXELFORMAT_RGBA8888 << " Format not wanted : " << std::endl;
	// std::cout << SDL_PIXELFORMAT_RGBA32 << " Format not wanted : " << std::endl;
	// std::cout << SDL_PIXELFORMAT_ARGB32 << " Format not wanted : " << std::endl;
	// SDL_SetRenderTarget(render, NULL);
	// SDL_RenderCopy(render, texture, NULL, NULL);
	// SDL_RenderPresent(render);


	IMG_SavePNG(surface, filename.c_str());
	i++;

	uint8_t		*pixelPtr = (uint8_t *)surface->pixels;
	cv::Mat	img = cv::Mat(h, w, CV_8UC4, pixelPtr);
	cv::cvtColor(img, img, cv::COLOR_RGBA2RGB);
	SDL_FreeSurface(surface); 
	return (img);
}

void			Info::renderPresent(bool save) {
	if (save) {
		// SDL_Delay(10);
		// convScreenToMat(S.getRenderer());
		video.write(convScreenToMat(S.getRenderer()));
		SDL_RenderPresent(S.getRenderer());
		// SDL_Delay(1000);
		// Timer	fps;
		// while (handleEvent(noneFunction, noneFunction, *this))
		// {
		// 	fps.start();
		// 	SDL_Delay(fmax(0, (1000 / 30) - fps.get_ticks()));
		// }
	} else {
		SDL_RenderPresent(S.getRenderer());
	}
}