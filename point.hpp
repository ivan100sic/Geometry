#pragma once

#include <iostream>
using namespace std;

template<class Number>
Number sq(Number x) {
	return x*x;
}

/* A point is defined by its two coordinates */
template<class Number>
struct point {
	Number x;
	Number y;

	point() : x(0), y(0) {}

	point(const Number& x, const Number& y) : x(x), y(y) {}

	point(Number&& x, Number&& y) : x(x), y(y) {}

	bool operator == (const point& o) const {
		return x == o.x && y == o.y;
	}

	bool operator != (const point& o) const {
		return !(*this == o);
	}

	bool operator < (const point& o) const {
		return x < o.x || (x == o.x && y < o.y);
	}

	friend ostream& operator << (ostream& os, point p) {
		return os << '(' << p.x << ", " << p.y << ')';
	}
};

template<class Number>
Number determinant(const point<Number>& a, const point<Number>& b, const point<Number>& c) {
	return a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x;
}

template<class Number>
Number distance2(const point<Number>& a, const point<Number>& b) {
	return sq(a.x - b.x) + sq(a.y - b.y);
}
