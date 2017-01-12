#pragma once

/* A point is defined by its two coordinates */
template<class Number>
struct point {
	Number x;
	Number y;

	point() : x(0), y(0) {}

	point(const Number& x, const Number& y) : x(x), y(y) {}

	point(Number&& x, Number&& y) : x(x), y(y) {}
};

