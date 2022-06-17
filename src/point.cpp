#include "point.hpp"
#include <vector>
#include <random>

std::vector<Point<double>>  generateBezierPoint(Point<double> p1, Point<double> p2, int n, double y_min, double y_max) {
    std::vector<Point<double>>  points;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr_y(y_min, y_max);
    std::uniform_real_distribution<double> distr_x(0, 1);

    points.push_back(p1);
    for (int i = 0; i < n; i++) {
        points.push_back({distr_x(eng), distr_y(eng)});
    }
    points.push_back(p2);
    return (points);
}

std::ostream& operator<<(std::ostream &os, const Point<double> &p) {
	os << p.x_ << ", " << p.y_;
	return (os);
}