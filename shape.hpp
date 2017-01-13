#pragma once

#include "point.hpp"

#include <iostream>
using namespace std;

const int SHAPE_UNDEFINED = 0;
const int SHAPE_CIRCLE = 1;
const int SHAPE_LINE = 2;

template<class Number>
struct shape {
	typedef point<Number> point_t;

	int type;
	point_t a;
	point_t b;

	shape() : type(SHAPE_UNDEFINED) {}

	shape(const point_t& a, const point_t& b, int type) : type(type), a(a), b(b) {}

	shape(point_t&& a, point_t&& b, int type) : type(type), a(a), b(b) {}

	bool operator == (const shape<Number>& o) const {
		if (type != o.type) return false;
		if (type == SHAPE_LINE) {
			// 4 collinear points
			return determinant(a, b, o.a) == Number(0) && determinant(a, b, o.b) == Number(0);
		}
		if (type == SHAPE_CIRCLE) {
			// equal centers and radiuses
			return a == o.a && distance2(a, b) == distance2(o.a, o.b);
		}
		return true;
	}

	friend ostream& operator << (ostream& os, const shape& x) {
		if (x.type == SHAPE_LINE) {
			return os << "Line: " << x.a << " -> " << x.b;
		}
		if (x.type == SHAPE_CIRCLE) {
			return os << "Circle: " << x.a << " )* " << x.b;
		}
		return os;
	}
};