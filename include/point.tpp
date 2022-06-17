#include "point.hpp"
#include <iostream>

template <class T>
void	Point<T>::setPoint(T x, T y) {
	x_ = x;
	y_ = y;
}

template <class T>
Point<T>::Point(T x, T y) : x_(x), y_(y) {}

template <class T>
Point<T>::Point() : x_(), y_(0) {}


template <class T>
Point<T>::~Point() {}

template <class T>
bool    Point<T>::operator<(const Point<T>& p) const {
	return (this->x_ <= p.x_);
}

template <class T>
bool    Point<T>::operator>(const Point<T>& p) const {
	return (this->x_ >= p.x_);
}