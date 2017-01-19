#pragma once

#include "simple_set.hpp"
#include "shape.hpp"
#include "intersect.hpp"
#include "point.hpp"

template<class Number, class Container>
void make_all_intersections(const simple_set<shape<Number>>& ss, Container& sp) {
	for (auto it = ss.begin(); it != ss.end(); ++it) {
		auto jt = it;
		while (++jt != ss.end()) {
			auto v = intersect(*it, *jt);
			for (auto p : v) {
				sp.insert(p);
			}
		}
	}
}