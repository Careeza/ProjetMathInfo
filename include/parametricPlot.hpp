#ifndef PARAMETRICPLOT_HPP

# define PARAMETRICPLOT_HPP

# include <functional>
# include "screen.hpp"
# include "mathBonus.hpp"

class PPlot {
	public:
		PPlot(std::function<double(double)> xt, std::function<double(double)> yt);
		void	plot(VirtualScreen &screen, double tStart, double tEnd, int size = 1);
		void	plotOnMap(VirtualScreen &screen, double tStart, double tEnd, std::vector<std::vector<Case>> &map);
		void	showDerivate(VirtualScreen &screen, double t);
		std::function<double(double)>	getXt() const;
		std::function<double(double)>	getYt() const;
	private:
		std::function<double(double)>	xt_;
		std::function<double(double)>	yt_;
};

#endif