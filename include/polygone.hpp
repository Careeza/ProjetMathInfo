#ifndef POLYGONE_HPP

# define POLYGONE_HPP

# include "point.hpp"
# include <vector>
# include <functional>

class Polygone {
	public:
		Polygone(std::vector<Point<double>>	points);
		Polygone();
		~Polygone();
		
		void	addPoint(Point<double> point);
		bool	isClosed();

		std::vector<Point<double>>	getPoints() const;
	private:
		std::vector<Point<double>>	points_;
		bool						closed_;
};

#endif