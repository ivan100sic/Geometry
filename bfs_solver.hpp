#pragma once

#include "simple_set.hpp"
#include "shape.hpp"
#include "intersect.hpp"
#include "point.hpp"
#include "all_intersections.hpp"

#include <vector>
#include <utility>
#include <map>
#include <set>
using namespace std;

// given a starting set of shapes and points and a target set of shapes and points, find
// a sequence of moves which generates all the target objects.
template<class Number>
class bfs_solver {

	typedef simple_set<shape<Number>> ss;
	typedef simple_set<point<Number>> sp;

	ss starting_shapes;
	sp starting_points;

	const ss& target_shapes;
	const sp& target_points;

	unsigned max_depth;

public:

	bfs_solver(
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

		// The worst template instance I've ever created
		vector<multimap<set<point<Number>>, simple_set<shape<Number>>>> dp(max_depth+1);

		typedef pair<const set<point<Number>>, simple_set<shape<Number>>> sp_pair;

		// depth 0
		dp[0].insert(
			sp_pair(
				set<point<Number>>(starting_points.begin(), starting_points.end()),
				starting_shapes
			)
		);

		for (unsigned depth = 1; depth <= max_depth; depth++) {
			cout << "Depth " << (depth-1) << " - " << dp[depth-1].size() << " unique patterns\n";
			for (auto x : dp[depth - 1]) {

				// push a shape instance
				auto do_work = [&](const shape<Number>& z) {
					if (!x.second.contains(z)) {
						ss nss = x.second;
						nss.insert(z);
						if (nss.count_missing(target_shapes) > max_depth - depth) return;
						set<point<Number>> nsp(x.first.begin(), x.first.end());
						make_all_intersections(nss, nsp);
						// No!
						// Check if this element already exists. It is "kinda" slow but necessary!
						auto er = dp[depth].equal_range(nsp);
						for (auto it = er.first; it != er.second; ++it) {
							if (nss == it->second) return;
						}
						dp[depth].insert(sp_pair(nsp, nss));
					}
				};

				for (auto it = x.first.begin(); it != x.first.end(); ++it) {
					auto jt = it;
					while (++jt != x.first.end()) {
						do_work(shape<Number>(*it, *jt, SHAPE_LINE));
						do_work(shape<Number>(*it, *jt, SHAPE_CIRCLE));
						do_work(shape<Number>(*jt, *it, SHAPE_CIRCLE));
					}
				}
			}
		}

		for (auto x : dp[max_depth]) {
			simple_set<point<Number>> abc(x.first);
			if (abc.contains_all(target_points)) {
				return make_pair(x.second, abc);
			}
		}

		return pair<ss, sp>();
	}

};