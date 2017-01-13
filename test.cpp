#include "intersect.hpp"
#include "soft_float.hpp"

#include <vector>
#include <iostream>
using namespace std;

#include "shape.hpp"
#include "backtrack_solver.hpp"

typedef shape<soft_float> Shape;
typedef point<soft_float> Point;

int main() {
	Shape p(Point(1.2, 2.03), Point(7.55, 6.11), SHAPE_LINE);
	Shape q(Point(4.98, 6.91), Point(7.33, 9.1011), SHAPE_LINE);

	auto r = intersect(p, q);
	cout << (double)r[0].x << ' ' << (double)r[0].y << endl;

	Shape c(Point(1.4, 1.7), Point(2.5, 2.97), SHAPE_CIRCLE);

	auto w = intersect(p, c);
	cout << (double)w[0].x << ' ' << (double)w[0].y << endl;
	cout << (double)w[1].x << ' ' << (double)w[1].y << endl;

	cout << endl;

	Shape k1(Point(0.37, 0.65), Point(0.67, 0.33), SHAPE_CIRCLE);
	Shape k2(Point(1.06, 1), Point(0.28, 0.43), SHAPE_CIRCLE);
	auto t1 = intersect(k1, k2);

	cout << (double)t1[0].x << ' ' << (double)t1[0].y << endl;
	cout << (double)t1[1].x << ' ' << (double)t1[1].y << endl;

	cout << "Solving...\n\n";

	if (0) {
		simple_set<Point> ssp = { Point(0, 0), Point(1, 0) };
		simple_set<Shape> sss = { Shape(Point(0, 0), Point(1, 0), SHAPE_LINE) };
		simple_set<Point> tsp;
		simple_set<Shape> tss = { Shape(Point(0, 0), Point(1, 1), SHAPE_LINE) };
		backtrack_solver<soft_float> bs(sss, ssp, tss, tsp, 5);

		auto sol = bs.solve();

		for (auto sh : sol.first) {
			cout << sh << '\n';
		}
	}

	if (0) {
		simple_set<Point> ssp = { Point(0, 0), Point(1, 0) };
		simple_set<Shape> sss = { Shape(Point(0, 0), Point(1, 0), SHAPE_CIRCLE) };
		simple_set<Point> tsp;
		simple_set<Shape> tss = {
			Shape(Point(1, 0), Point(0, 1), SHAPE_LINE),
			Shape(Point(0, 1), Point(-1, 0), SHAPE_LINE),
			Shape(Point(-1, 0), Point(0, -1), SHAPE_LINE),
			Shape(Point(0, -1), Point(1, 0), SHAPE_LINE)		
		};
		backtrack_solver<soft_float> bs(sss, ssp, tss, tsp, 7);

		auto sol = bs.solve();

		for (auto sh : sol.first) {
			cout << sh << '\n';
		}
	}

	{
		simple_set<Point> ssp = { Point(0, 0), Point(1, 0) };
		simple_set<Shape> sss = { Shape(Point(0, 0), Point(1, 0), SHAPE_LINE) };
		simple_set<Point> tsp;
		simple_set<Shape> tss = {
			Shape(Point(0, 0), Point(1, 1), SHAPE_LINE),
			Shape(Point(1, 0), Point(2, 1), SHAPE_LINE),
			Shape(Point(0, 0.70710678118654752440084436210485), Point(1, 0.70710678118654752440084436210485), SHAPE_LINE)
		};
		backtrack_solver<soft_float> bs(sss, ssp, tss, tsp, 7);

		auto sol = bs.solve();

		for (auto sh : sol.first) {
			cout << sh << '\n';
		}
	}

	cout << '\n';
	system("pause");

	return 0;
}