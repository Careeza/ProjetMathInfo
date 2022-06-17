#include "point.hpp"
#include <iostream>

template <class T>
void	Point<T>::setPoint(T x, T y) {
	x_ = x;
	y_ = y;
}

template <class T>
Point<T>::Point(T x, T y) : x_(x), y_(y) {
	std::cout << "Constructor called" << std::endl;
	std::cout << x << ", " << y << std::endl;
}

template <class T>
Point<T>::Point() : x_(), y_(0) {}


template <class T>
Point<T>::~Point() {}