#ifndef POINT_HPP

# define POINT_HPP

#include <vector>
#include <iostream>

template <class T>
class Point {
    public:
        Point();
        Point(T x, T y);
        ~Point();

		void	setPoint(T x, T y);
        friend std::ostream& operator<<(std::ostream &os, const Point<double> &p);
        T       getX() { return (x_); };
        T       getY() { return (y_); };

    private:
        T x_;
        T y_;
};

std::ostream& operator<<(std::ostream &os, const Point<double> &p);

std::vector<Point<double>>  generateBezierPoint(Point<double> p1, Point<double> p2, int n, double y_min = -1, double y_max = 1);

#include "point.tpp"

#endif