#include "point.h"

template <class T>
void	Point<T>::setPoint(T x, T y) {
	x_ = 0;
	y_ = 0;
}

template <class T>
Point<T>::Point() : x_(0), y_(0) {}


template <class T>
Point<T>::~Point() {}