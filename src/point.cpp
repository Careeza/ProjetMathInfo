#include "point.hpp"
#include <vector>
#include <random>
#include <algorithm>

std::vector<Point<double>>  generateBezierPoints(Point<double> p1, Point<double> p2, int n, double y_min, double y_max) {
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
    std::sort(points.begin(), points.end());
    return (points);
}

std::vector<Point<double>>  generateNextPoints(std::vector<Point<double>> p, double t) {
    std::vector<Point<double>>  new_p;

    for (size_t i = 0; i < p.size() - 1; i++) {
        new_p.push_back({p[i].getX() * (1 - t) + p[i + 1].getX() * t, p[i].getY() * (1 - t) + p[i + 1].getY() * t});
    }
    return (new_p);
}

std::ostream& operator<<(std::ostream &os, const Point<double> &p) {
	os << p.x_ << ", " << p.y_;
	return (os);
}


std::ostream& operator<<(std::ostream &os, const Point<int> &p) {
	os << p.x_ << ", " << p.y_;
	return (os);
}