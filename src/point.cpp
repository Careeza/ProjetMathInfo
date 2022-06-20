#include "point.hpp"
#include <vector>
#include <iostream>
#include <algorithm>


std::ostream& operator<<(std::ostream &os, const Point<double> &p) {
	os << p.x_ << ", " << p.y_;
	return (os);
}


std::ostream& operator<<(std::ostream &os, const Point<int> &p) {
	os << p.x_ << ", " << p.y_;
	return (os);
}