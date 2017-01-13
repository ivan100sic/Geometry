#pragma once

#include <vector>
using namespace std;

template<class T>
class simple_set {
	vector<T> v;
public:
	simple_set() {}

	template<class Iterator>
	simple_set(Iterator begin, Iterator end) {
		while (begin != end) {
			insert(*begin);
			++begin;
		}
	}

	simple_set(initializer_list<T> obj) {
		for (auto x : obj) insert(x);
	}

	void insert(const T& x) {
		if (contains(x)) return;
		v.push_back(x);
	}

	bool contains(const T& x) const {
		for (size_t i = 0; i < v.size(); i++) {
			if (x == v[i]) {
				return true;
			}
		}
		return false;
	}

	template<class Iterable>
	size_t count_missing(Iterable v) const {
		size_t c = 0;
		for (auto x : v) {
			if (!contains(x)) c++;
		}
		return c;
	}

	template<class Iterable>
	bool contains_all(Iterable v) const {
		for (auto x : v) {
			if (!contains(x)) return false;
		}
		return true;
	}

	typename vector<T>::const_iterator begin() const {
		return v.begin();
	}

	typename vector<T>::const_iterator end() const {
		return v.end();
	}

	size_t size() const { return v.size(); }
};