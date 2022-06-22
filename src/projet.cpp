#include "projet.hpp"
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <boost/program_options/version.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int     main(int argc, char **argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help", "describe arguments")
    ("BCurve", "Launch to see Bezier curve algorithm")
    ("LCurve", "Launch to see Lissajous curve")
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
    } else if (vm.count("LCurve")) {
		lissajousCurveLoop();
	} else if (vm.count("Polygone")) {
		polygoneLoop();
	}


    return (0);
}