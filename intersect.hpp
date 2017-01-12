#pragma once

#include "point.hpp"
#include "shape.hpp"

#include <vector>
using namespace std;

/* Reconsider */
template<class Number>
Number sq(Number x) {
	return x*x;
}

template<class Number>
vector<point<Number>> intersect_line_line(shape<Number> p, shape<Number> q) {
	/* 0 or 1 point */
	Number cross = (p.a.x - p.b.x) * (q.a.y - q.b.y) - (p.a.y - p.b.y) * (q.a.x - q.b.x);
	if (cross == Number(0)) {
		return vector<point<Number>>();
	}
	Number xn = p.a.y * p.b.x * (q.b.x - q.a.x) - p.b.x * q.a.y * q.b.x + p.b.x * q.a.x * q.b.y +
		p.a.x * (p.b.y * (q.a.x - q.b.x) + q.a.y * q.b.x - q.a.x * q.b.y);

	Number yn = p.a.y * (q.a.y * q.b.x - q.a.x * q.b.y + p.b.x * (q.b.y - q.a.y)) +
		p.b.y * (q.a.x * q.b.y - q.a.y * q.b.x + p.a.x * (q.a.y - q.b.y));

	return vector<point<Number>> { point<Number>(xn / cross, yn / cross) };
}

template<class Number>
vector<point<Number>> intersect_line_circle(shape<Number> p, shape<Number> k) {
	// Reduce the problem to a circle in the origin with radius 1

	// This number is defined because k.a != k.b
	Number rad = sqrt(sq(k.a.x - k.b.x) + sq(k.a.y - k.b.y));
	p.a.x /= rad;
	p.a.y /= rad;

	p.b.x /= rad;
	p.b.y /= rad;

	k.a.x /= rad;
	k.a.y /= rad;

	p.a.x -= k.a.x;
	p.a.y -= k.a.y;

	p.b.x -= k.a.x;
	p.b.y -= k.a.y;

	// This number is defined because p.a != p.b
	Number ls2 = sq(p.a.x - p.b.x) + sq(p.a.y - p.b.y);
	Number cm = (p.a.y * p.b.x - p.a.x * p.b.y) / ls2;
	Number cx = (p.a.y - p.b.y) * cm;
	Number cy = (p.b.x - p.a.x) * cm;

	// Compute the distance to the origin
	Number dis = sq(cx) + sq(cy);

	auto fix = [&](Point a) { return Point((a.x + k.a.x) * rad, (a.y + k.a.y) * rad); };

	if (dis > Number(1)) {
		return vector<point<Number>>();
	}

	if (dis == Number(1)) {
		return vector<point<Number>> {
			fix(Point(cx, cy))
		};
	}

	// General case:

	Number offset = sqrt(Number(1) - dis);

	// The two solution points are at distance offset from c

	Number ls = sqrt(ls2);

	point<Number> p1 = point<Number>(cx + offset * (p.a.x - p.b.x) / ls, cy + offset * (p.a.y - p.b.y) / ls);
	point<Number> p2 = point<Number>(cx - offset * (p.a.x - p.b.x) / ls, cy - offset * (p.a.y - p.b.y) / ls);

	return vector<point<Number>> {fix(p1), fix(p2)};
}

template<class Number>
vector<point<Number>> intersect_circle_circle(shape<Number> p, shape<Number> k) {
	// Again reduce the problem

	Number rad = sqrt(sq(k.a.x - k.b.x) + sq(k.a.y - k.b.y));
	p.a.x /= rad;
	p.a.y /= rad;

	p.b.x /= rad;
	p.b.y /= rad;

	k.a.x /= rad;
	k.a.y /= rad;

	p.a.x -= k.a.x;
	p.a.y -= k.a.y;

	p.b.x -= k.a.x;
	p.b.y -= k.a.y;

	Number s2 = sq(p.a.x) + sq(p.a.y);
	Number s = sqrt(s2);
	Number d2 = sq(p.a.x - p.b.x) + sq(p.a.y - p.b.y);
	Number d = sqrt(d2);

	Number disc = (s - d + Number(1)) * (d - s + Number(1)) * (d + s - Number(1)) * (d + s + Number(1));

	if (disc < Number(0)) {
		return vector<point<Number>>();
	}

	Number x0 = (s2 - d2 + Number(1)) / Number(2);

	auto fix = [&](point<Number> a) { return point<Number>((a.x + k.a.x) * rad, (a.y + k.a.y) * rad); };

	if (disc == Number(0)) {
		point<Number> p1(x0 * p.a.x / s2, x0 * p.a.y / s2);
		return vector<point<Number>> {fix(p1)};
	}

	Number y0 = sqrt(disc) / Number(2);

	point<Number> p1((x0 * p.a.x - y0 * p.a.y) / s2, (x0 * p.a.y + y0 * p.a.x) / s2);
	point<Number> p2((x0 * p.a.x + y0 * p.a.y) / s2, (x0 * p.a.y - y0 * p.a.x) / s2);
	
	return vector<point<Number>> {fix(p1), fix(p2)};

}

template<class Number>
vector<point<Number>> intersect(const shape<Number>& s1, const shape<Number>& s2) {
	if (s1.type == SHAPE_LINE && s2.type == SHAPE_LINE) {
		return intersect_line_line(s1, s2);
	}
	if (s1.type == SHAPE_LINE && s2.type == SHAPE_CIRCLE) {
		return intersect_line_circle(s1, s2);
	}
	if (s1.type == SHAPE_CIRCLE && s2.type == SHAPE_LINE) {
		return intersect_line_circle(s2, s1);
	}
	if (s1.type == SHAPE_CIRCLE && s2.type == SHAPE_CIRCLE) {
		return intersect_circle_circle(s1, s2);
	}

	// failed
	return vector<point<Number>>();
}