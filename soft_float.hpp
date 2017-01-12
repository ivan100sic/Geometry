#pragma once

const double WORKING_PRECISION = 1e-12;

class soft_float {
	double x;
public:
	soft_float() : x(0.0) {}
	soft_float(int x) : x(x) {}
	soft_float(double x) : x(x) {}
	explicit operator double() const { return x; }

	bool operator == (const soft_float& b) const {
		double d = x - b.x;
		return -WORKING_PRECISION < d && d < WORKING_PRECISION;
	}

	bool operator != (const soft_float& b) const { return !(*this == b); }
	bool operator < (const soft_float& b) const { return x < b.x && *this != b; }
	bool operator > (const soft_float& b) const { return x > b.x && *this != b; }
	bool operator <= (const soft_float& b) const { return x < b.x || *this == b; }
	bool operator >= (const soft_float& b) const { return x > b.x || *this == b; }

	soft_float operator + (const soft_float& b) const { return x + b.x; }
	soft_float operator - (const soft_float& b) const { return x - b.x; }
	soft_float operator * (const soft_float& b) const { return x * b.x; }
	soft_float operator / (const soft_float& b) const { return x / b.x; }

	soft_float& operator += (const soft_float& b) { x += b.x; return *this; }
	soft_float& operator -= (const soft_float& b) { x -= b.x; return *this; }
	soft_float& operator *= (const soft_float& b) { x *= b.x; return *this; }
	soft_float& operator /= (const soft_float& b) { x /= b.x; return *this; }

	soft_float operator - () const { return -x; }

	friend soft_float sqrt(const soft_float& b) {
		return sqrt(b.x);
	}

};

