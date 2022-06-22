#include "projet.hpp"
#include "index.hpp"
#include "mathBonus.hpp"
#include <boost/program_options.hpp>
#include <boost/math/constants/constants.hpp>
#include <SDL2/SDL_ttf.h>
#include <functional>

namespace po = boost::program_options;
TTF_Font *my_font = NULL;


Info::Info(bool fullScreen) : S(fullScreen), show(true) {
	TTF_Init();
	my_font = TTF_OpenFont("ressource/Keyboard.ttf", 20);
}

Info::~Info() {}

void			Info::addVirtualScreen(Flag f) {
    Vscreens.emplace_back(S, f);
    screen = &Vscreens.back();
}

VirtualScreen	*Info::getCurrentScreen() const {
    return (screen);
}

void			Info::selectScreen(int index) {
    screen = &Vscreens[index];
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

int     main(int argc, char **argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help", "describe arguments")
    ("BCurve", "Launch to see Bezier curve algorithm")
    ("LCurve", "Launch to see Lissajous curve")
    ("BCurveGFX", "Launch to see Bezier curve algorithm with GFX")
    ("Polygone", "Launch to see Polygone");
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
    	po::notify(vm);
	} catch(po::unknown_option const & unknown) {
		std::cout << "Unknown option: " << unknown.get_option_name() << std::endl;
		std::cerr << desc;
		return (1);
	}
    if (vm.count ("help")) {
        std::cerr << desc << "\n";
        return 1;
    }

	// my_font = TTF_OpenFont("ressource/Keyboard.ttf", 20);

    if (vm.count("BCurve")) {
    	bezierCurveLoop();
    } else if (vm.count("BCurveGFX")) {
    	bezierCurveLoopGFX();
    } else if (vm.count("LCurve")) {
		lissajousCurveLoop();
	} else if (vm.count("Polygone")) {
		polygoneLoop();
	}


    return (0);
}