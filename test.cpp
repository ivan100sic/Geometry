#include "intersect.hpp"
#include "soft_float.hpp"

#include <vector>
#include <iostream>
using namespace std;

#include "shape.hpp"
#include "backtrack_solver.hpp"
#include "bfs_solver.hpp"

typedef shape<soft_float> Shape;
typedef point<soft_float> Point;

int main() {

	if (0) {

		Shape p(Point(1.2, 2.03), Point(7.55, 6.11), SHAPE_LINE);
		Shape q(Point(4.98, 6.91), Point(7.33, 9.1011), SHAPE_LINE);

		auto r = intersect(p, q);
		cout << r[0] << endl;

		Shape c(Point(1.4, 1.7), Point(2.5, 2.97), SHAPE_CIRCLE);

		auto w = intersect(p, c);
		cout << w[0] << endl << w[1] << endl;

		cout << endl;

		Shape k1(Point(0.37, 0.65), Point(0.67, 0.33), SHAPE_CIRCLE);
		Shape k2(Point(1.06, 1), Point(0.28, 0.43), SHAPE_CIRCLE);
		auto t1 = intersect(k1, k2);

		cout << t1[0] << endl;
		cout << t1[1] << endl;

		cout << "Perpendicular line:\n";
		Shape k3(Point(0.57, 0.52), Point(1.54, 0.67), SHAPE_LINE);
		Point p4(0.75, 0.94);

		auto k5 = perpendicular_line(k3, p4);
		cout << k5 << endl;

		cout << "Bisector:\n";
		cout << bisector(k3.a, k3.b) << endl;

		cout << "Angle bisector:\n";
		Shape kq1(Point(0.37, 0.65), Point(0.67, 0.33), SHAPE_LINE);
		Shape kq2(Point(1.06, 1), Point(0.28, 0.43), SHAPE_LINE);
		cout << angle_bisector(kq1, kq2) << endl;

		cout << "Angle bisector 2:\n";
		cout << angle_bisector2(kq1, kq2) << endl;

	}

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

	if (0) {
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

	if (0) {
		simple_set<Point> ssp = {
			Point(1, 0),
			Point(0.473892179283747389247398274398271924, 0.880582876516288284886493948420462995),
			Point(-3.141483020432848234802384280840284032, 1.849302128304803480348032081082034284)		
		};
		simple_set<Shape> sss = { Shape(Point(0, 0), Point(1, 0), SHAPE_CIRCLE) };
		simple_set<Point> tsp;
		simple_set<Shape> tss = {
			Shape(Point(-0.5, 0.86602540378443864676372317075294), Point(1, 0), SHAPE_LINE),
			Shape(Point(-0.5, -0.86602540378443864676372317075294), Point(1, 0), SHAPE_LINE),
			Shape(Point(-0.5, 0.86602540378443864676372317075294), Point(-0.5, -0.86602540378443864676372317075294), SHAPE_LINE)
		};

		backtrack_solver<soft_float> bs(sss, ssp, tss, tsp, 6);

		auto sol = bs.solve();

		for (auto sh : sol.first) {
			cout << sh << '\n';
		}
	}

	if (0) {
		simple_set<Point> ssp = {
			Point(0, 0),
			Point(1, 0)
		};
		simple_set<Shape> sss;
		simple_set<Point> tsp;
		simple_set<Shape> tss = {
			Shape(Point(1, 0.5), Point(1, -0.5), SHAPE_LINE),
			Shape(Point(0, 0.5), Point(0, -0.5), SHAPE_LINE),
			Shape(Point(1, 0.5), Point(0, 0.5), SHAPE_LINE),
			Shape(Point(1, -0.5), Point(0, -0.5), SHAPE_LINE)
		};

		bfs_solver<soft_float> bs(sss, ssp, tss, tsp, 10);

		auto sol = bs.solve();

		for (auto sh : sol.first) {
			cout << sh << '\n';
		}
	}

	if (0) {
		simple_set<Point> ssp = {
			Point(1, 0),
			Point(0.473892179283747389247398274398271924, 0.880582876516288284886493948420462995),
			Point(-3.141483020432848234802384280840284032, 1.849302128304803480348032081082034284)
		};
		simple_set<Shape> sss = { Shape(Point(0, 0), Point(1, 0), SHAPE_CIRCLE) };
		simple_set<Point> tsp;
		simple_set<Shape> tss = {
			Shape(Point(-0.5, 0.86602540378443864676372317075294), Point(1, 0), SHAPE_LINE),
			Shape(Point(-0.5, -0.86602540378443864676372317075294), Point(1, 0), SHAPE_LINE),
			Shape(Point(-0.5, 0.86602540378443864676372317075294), Point(-0.5, -0.86602540378443864676372317075294), SHAPE_LINE)
		};

		backtrack_solver_l<soft_float> bs(sss, ssp, tss, tsp, 5);

		auto sol = bs.solve();

		for (auto sh : sol.first) {
			cout << sh << '\n';
		}
	}

	if (0) {
		simple_set<Point> ssp = {
			Point(0, 0),
			Point(1, 0)
		};
		simple_set<Shape> sss;
		simple_set<Point> tsp;
		simple_set<Shape> tss = {
			Shape(Point(0, 0), Point(1, 1), SHAPE_LINE),
			Shape(Point(0, 1), Point(1, 0), SHAPE_LINE),
			Shape(Point(0, -1), Point(1, -2), SHAPE_LINE),
			Shape(Point(0, -2), Point(1, -1), SHAPE_LINE),
		};

		backtrack_solver_l<soft_float> bs(sss, ssp, tss, tsp, 7);

		auto sol = bs.solve();

		for (auto sh : sol.first) {
			cout << sh << '\n';
		}
	}

	if (0) {
		simple_set<Point> ssp = {
			Point(0, 0),
			Point(1, 0),
			Point(0.21, 0.79)
		};
		simple_set<Shape> sss = {
			Shape(Point(0, 0), Point(1, 0), SHAPE_LINE),
			Shape(Point(0, 0), Point(0.21, 0.79), SHAPE_LINE),
		};
		simple_set<Point> tsp;
		simple_set<Shape> tss = {
			Shape(Point(0.21, 0.79), Point(1.21, 0.79), SHAPE_LINE),
			Shape(Point(1, 0), Point(1.21, 0.79), SHAPE_LINE),
		};

		bfs_solver<soft_float> bs(sss, ssp, tss, tsp, 6);

		auto sol = bs.solve();

		for (auto sh : sol.first) {
			cout << sh << '\n';
		}
	}

	if (0) {
		// Failed miserably
		simple_set<Point> ssp {
			Point(0, 0), Point(1, 0), Point(0.21, 0.78), Point(0.94, 0.78)
		};
		simple_set<Shape> sss;
		simple_set<Point> tsp;
		simple_set<Shape> tss = {
			Shape(Point(0, 0.39), Point(1, 0.39), SHAPE_LINE),
		};

		bfs_solver<soft_float> bs(sss, ssp, tss, tsp, 6);

		auto sol = bs.solve();

		for (auto sh : sol.first) {
			cout << sh << '\n';
		}
	}

	if (0) {
		simple_set<Point> ssp{
			Point(0, 0),
		};
		simple_set<Shape> sss {
			Shape(Point(0, 0), Point(1, 0), SHAPE_CIRCLE),
			Shape(Point(0, 0), Point(0, 1), SHAPE_LINE)
		};
		simple_set<Point> tsp;
		simple_set<Shape> tss = {
			Shape(Point(0, 1), Point(1, 1), SHAPE_LINE),
			Shape(Point(0, 1), Point(-1, 1), SHAPE_LINE),
			Shape(Point(0, -1), Point(1, -1), SHAPE_LINE),
			Shape(Point(0, -1), Point(-1, -1), SHAPE_LINE)
		};

		bfs_solver<soft_float> bs(sss, ssp, tss, tsp, 7);

		auto sol = bs.solve();

		for (auto sh : sol.first) {
			cout << sh << '\n';
		}
	}

	if (0) {
		simple_set<Point> ssp {
			Point(0, 0),
		};
		simple_set<Shape> sss {
			Shape(Point(0, 0), Point(0, 1), SHAPE_CIRCLE),
			Shape(Point(0, 0.12345), Point(1, 0.12345), SHAPE_LINE)
		};
		simple_set<Point> tsp;
		simple_set<Shape> tss = {
			Shape(Point(1, 1), Point(-1, 1), SHAPE_LINE),
			Shape(Point(-1, 1), Point(-1, -1), SHAPE_LINE),
			Shape(Point(-1, -1), Point(1, -1), SHAPE_LINE),
			Shape(Point(1, -1), Point(1, 1), SHAPE_LINE)
		};

		backtrack_solver<soft_float> bs(sss, ssp, tss, tsp, 11);

		auto sol = bs.solve();

		for (auto sh : sol.first) {
			cout << sh << '\n';
		}
	}

	if (0) {
		Point A(0, 0);
		Point B(5, 0);
		Point C(6.43, 2.11);
		Point D(3.7006, 2.19284282154467);
		simple_set<Point> ssp{
			A, B, C
		};
		simple_set<Shape> sss{
			Shape(A, B, SHAPE_LINE)
			//Shape(B, C, SHAPE_CIRCLE)
		};
		simple_set<Point> tsp;
		simple_set<Shape> tss = {
			Shape(A, D, SHAPE_LINE),
			Shape(B, D, SHAPE_LINE),
		};

		backtrack_solver<soft_float> bs(sss, ssp, tss, tsp, 6);

		auto sol = bs.solve();

		for (auto sh : sol.first) {
			cout << sh << '\n';
		}
	}

	if (1) {
		Point A(0, 0);
		Point B(1, 0);
		Point C(0.91, 0.77);
		Point D(0.41, 0.77);
		Point E(1.41, 0.77);

		simple_set<Point> ssp{
			A, B, C
		};
		simple_set<Shape> sss{
			Shape(A, B, SHAPE_LINE)
		};
		simple_set<Point> tsp;
		simple_set<Shape> tss = {
			Shape(A, D, SHAPE_LINE),
			Shape(B, E, SHAPE_LINE),
			Shape(D, E, SHAPE_LINE)
		};

		bfs_solver<soft_float> bs(sss, ssp, tss, tsp, 8);

		auto sol = bs.solve();

		for (auto sh : sol.first) {
			cout << sh << '\n';
		}

	}


	cout << '\n';
	system("pause");

	return 0;
}