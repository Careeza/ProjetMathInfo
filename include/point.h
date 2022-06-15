#ifndef POINT_H

# define POINT_H

template <class T>
class Point {
    public:
        Point();
        ~Point();
		void	setPoint(T x, T y);
    private:
        T x_;
        T y_;
};

#include "point.tpp"

#endif