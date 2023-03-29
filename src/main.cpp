#include "projet.hpp"
#include "indice.hpp"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int     main(int argc, char **argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help", "describe arguments")
    ("Cercle", "Launch to see Bezier curve algorithm")
    ("BCurve", "Launch to see Bezier curve algorithm")
    ("BLoop", "Launch to see Bezier close loop")
    ("LCurve", "Launch to see Lissajous curve")
    ("LCurve2", "Launch to see Lissajous curve")
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
    if (vm.count("BCurve")) {
    	bezierCurveLoop();
    } else if (vm.count("BCurveGFX")) {
		bezierCurveLoopGFX();
    } else if (vm.count("LCurve")) {
		lissajousCurveLoop(2, 3);
	} else if (vm.count("Polygone")) {
		polygoneBuilder();
	} else if (vm.count("BLoop")) {
		bezierCurveCloseLoop();
	} else if (vm.count("LCurve2")) {
		lissajousCurveLoop2(2, 3);
	} else if (vm.count("Cercle")) {
		cercleUniteCurveLoop();
	} else {
		std::cerr << desc << "\n";
		return 1;
	}
    return (0);
}