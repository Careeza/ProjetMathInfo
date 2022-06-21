#ifndef POLYGONE_HPP

# define POLYGONE_HPP

# include "point.hpp"
# include <vector>

class Polygone {
	public:
		Poly(std::vector<Point<double>>	points);
		~Poly();
	private:
		std::vector<Point<double>>	points_;
		// std::vector<Point<<double>>	rPoints_;
};

#endif