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
        friend std::ostream& operator<<(std::ostream &os, const Point<int> &p);
        bool    operator<(const Point<T>& p) const;
        bool    operator>(const Point<T>& p) const;
        T       getX() { return (x_); };
        T       getY() { return (y_); };

    private:
        T x_;
        T y_;
};

std::ostream& operator<<(std::ostream &os, const Point<double> &p);
std::ostream& operator<<(std::ostream &os, const Point<int> &p);

std::vector<Point<double>>  generateBezierPoints(Point<double> p1, Point<double> p2, int n, double y_min = -1, double y_max = 1);
std::vector<Point<double>>  generateNextPoints(std::vector<Point<double>> p, double time);

#include "point.tpp"

#endif