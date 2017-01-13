#pragma once

#include "simple_set.hpp"
#include "shape.hpp"
#include "intersect.hpp"
#include "point.hpp"

#include <vector>
#include <utility>
using namespace std;

// given a starting set of shapes and points and a target set of shapes and points, find
// a sequence of moves which generates all the target objects.
template<class Number>
class backtrack_solver {

	typedef simple_set<shape<Number>> ss;
	typedef simple_set<point<Number>> sp;

	const ss& starting_shapes;
	sp starting_points;
	
	const ss& target_shapes;
	const sp& target_points;

	unsigned max_depth;

public:

	backtrack_solver(
		const ss& starting_shapes, const sp& starting_points,
		const ss& target_shapes, const sp& target_points,
		unsigned max_depth
	) :
		starting_shapes(starting_shapes), starting_points(starting_points),
		target_shapes(target_shapes), target_points(target_points),
		max_depth(max_depth)
	{
		// find all intersections
		for (auto it = starting_shapes.begin(); it != starting_shapes.end(); ++it) {
			auto jt = it;
			while (++jt != starting_shapes.end()) {
				auto v = intersect(*it, *jt);
				for (auto p : v) {
					this->starting_points.insert(p);
				}
			}
		}
	}

	pair<ss, sp> solve() const {
		if (max_depth == 0) {
			if (starting_shapes.contains_all(target_shapes)
				&& starting_points.contains_all(target_points))
			{
				return make_pair(starting_shapes, starting_points);
			} else {
				return pair<ss, sp>();
			}
		}

		// check feasibility
		if (starting_shapes.count_missing(target_shapes) > max_depth) {
			return pair<ss, sp>();
		}

		// create a new shape from every two given points
		for (auto it = starting_points.begin(); it != starting_points.end(); ++it) {
			auto jt = it;
			while (++jt != starting_points.end()) {
				bool flag = false;
				pair<ss, sp> sol;

				

				auto do_work = [&](const shape<Number>& z) {
					if (!starting_shapes.contains(z)) {
						ss nss = starting_shapes;
						nss.insert(z);
						backtrack_solver bs(nss, starting_points, target_shapes, target_points, max_depth - 1);
						auto ret = bs.solve();
						if (ret.first.size() + ret.second.size() != 0) {
							sol = ret;
							flag = true;
						}
					}
				};

				// line
				{
					shape<Number> z(*it, *jt, SHAPE_LINE);
					do_work(z);
					if (flag) return sol;
				}

				// circle 1
				{
					shape<Number> z(*it, *jt, SHAPE_CIRCLE);
					do_work(z);
					if (flag) return sol;
				}

				// circle 2
				{
					shape<Number> z(*jt, *it, SHAPE_CIRCLE);
					do_work(z);
					if (flag) return sol;
				}
			}
		}

		return pair<ss, sp>();
	}

};