#pragma once

#include "point.hpp"

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
};