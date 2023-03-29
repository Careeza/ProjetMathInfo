#include "polygone.hpp"

Polygone::Polygone(std::vector<Point<double>>	points) : points_(points), closed_(false) {
	if (points_.size() > 2) {
		closed_ = true;
	}
}

Polygone::~Polygone() {
}

Polygone::Polygone() : closed_(false) {}

void	Polygone::addPoint(Point<double> point) {
	points_.push_back(point);
	if (points_.size() > 2) {
		closed_ = true;
	}
}

bool	Polygone::isClosed() {
	return (closed_);
}

std::vector<Point<double>>	Polygone::getPoints() const {
	return (points_);
}