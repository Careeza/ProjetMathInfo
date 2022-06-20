#ifndef PARAMETRICPLOT_HPP

# define PARAMETRICPLOT_HPP

# include <functional>
# include "screen.hpp"

class PPlot {
	public:
		PPlot(std::function<double(double)> xt, std::function<double(double)> yt);
		void	plot(Screen &screen, double tStart, double tEnd, int size = 1);
		void	showDerivate(Screen &screen, double t);
	private:
		std::function<double(double)>	xt_;
		std::function<double(double)>	yt_;
};

#endif