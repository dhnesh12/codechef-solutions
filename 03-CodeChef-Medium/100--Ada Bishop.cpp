
#include <iostream>
#include <fstream>

#include <iostream>
#include <queue>


#include <vector>
#include <type_traits>

template <typename T, std::size_t N>
struct MakeVector {
	template <
			typename... Args,
			typename R = std::vector<decltype(MakeVector<T, N - 1>::make_vector(std::declval<Args>()...))>
	>
	static R make_vector(std::size_t first, Args... sizes) {
		auto inner = MakeVector<T, N - 1>::make_vector(sizes...);
		return R(first, inner);
	}
};

template <typename T>
struct MakeVector<T, 1> {

	template <typename R = std::vector<T>>
	static R make_vector(std::size_t size, const T& value) {
		return R(size, value);
	}
};

template <typename T, typename... Args>
auto make_vector(Args... args) -> decltype(MakeVector<T, sizeof...(Args) - 1>::make_vector(args...)) {
	return MakeVector<T, sizeof...(Args) - 1>::make_vector(args...);
}



#include <iterator>


#include <string>
#include <stdexcept>

#ifndef SPCPPL_ASSERT
	#ifdef SPCPPL_DEBUG
		#define SPCPPL_ASSERT(condition) \
		if(!(condition)) { \
			throw std::runtime_error(std::string() + #condition + " in line " + std::to_string(__LINE__) + " in " + __PRETTY_FUNCTION__); \
		}
	#else
		#define SPCPPL_ASSERT(condition)
	#endif
#endif



template <typename T>
class IntegerIterator: public std::iterator<std::input_iterator_tag, T, std::ptrdiff_t, T*, T> {
public:
	explicit IntegerIterator(T value): value(value) {

	}

	IntegerIterator& operator++() {
		++value;
		return *this;
	}

	IntegerIterator operator++(int) {
		IntegerIterator copy = *this;
		++value;
		return copy;
	}

	IntegerIterator& operator--() {
		--value;
		return *this;
	}

	IntegerIterator operator--(int) {
		IntegerIterator copy = *this;
		--value;
		return copy;
	}

	T operator*() const {
		return value;
	}

	bool operator==(IntegerIterator rhs) const {
		return value == rhs.value;
	}

	bool operator!=(IntegerIterator rhs) const {
		return !(*this == rhs);
	}

private:
	T value;
};

template <typename T>
class IntegerRange {
public:
	IntegerRange(T begin, T end): begin_(begin), end_(end) {
		SPCPPL_ASSERT(begin <= end);
	}

	IntegerIterator<T> begin() const {
		return IntegerIterator<T>(begin_);
	}

	IntegerIterator<T> end() const {
		return IntegerIterator<T>(end_);
	}

private:
	T begin_;
	T end_;
};

template <typename T>
class ReversedIntegerRange {
	using IteratorType = std::reverse_iterator<IntegerIterator<T>>;
public:
	ReversedIntegerRange(T begin, T end): begin_(begin), end_(end) {
		SPCPPL_ASSERT(begin >= end);
	}

	IteratorType begin() const {
		return IteratorType(IntegerIterator<T>(begin_));
	}

	IteratorType end() const {
		return IteratorType(IntegerIterator<T>(end_));
	}

private:
	T begin_;
	T end_;
};

template <typename T>
IntegerRange<T> range(T to) {
	return IntegerRange<T>(0, to);
}

template <typename T>
IntegerRange<T> range(T from, T to) {
	return IntegerRange<T>(from, to);
}

template <typename T>
IntegerRange<T> inclusiveRange(T to) {
	return IntegerRange<T>(0, to + 1);
}

template <typename T>
IntegerRange<T> inclusiveRange(T from, T to) {
	return IntegerRange<T>(from, to + 1);
}

template <typename T>
ReversedIntegerRange<T> downrange(T from) {
	return ReversedIntegerRange<T>(from, 0);
}

template <typename T>
ReversedIntegerRange<T> downrange(T from, T to) {
	return ReversedIntegerRange<T>(from, to);
}

template <typename T>
ReversedIntegerRange<T> inclusiveDownrange(T from) {
	return ReversedIntegerRange<T>(from + 1, 0);
}

template <typename T>
ReversedIntegerRange<T> inclusiveDownrange(T from, T to) {
	return ReversedIntegerRange<T>(from + 1, to);
}


using namespace std;

class AdaBishop {
public:

	int64_t sum(int64_t l, int64_t r) {
		return (abs(r - l) + 1) * (r + l) / 2;
	}
	int64_t angle(int64_t after, int64_t r) {
		// r - 1, ..., r - after
		after = min(after, r);
		if (after == 0) {
			return 0;
		}
		if (after == 1) {
			return (r - 1 + 1) / 2;
		}
		if (after % 2 == 0) {
			return sum((r - 1 + 1) / 2, (r - after + 1 + 1) / 2) + sum((r - 2 + 1) / 2, (r - after + 1) / 2);
		} else {
			return sum((r - 2 + 1) / 2, (r - after + 1 + 1) / 2) + sum((r - 1 + 1) / 2, (r - after + 1) / 2);
		}
	}

	static int odd(int64_t x) {
		return static_cast<int>(x % 2);
	}
	int64_t solveRight(int64_t n, int64_t m, int64_t r, int64_t c, int64_t k) {
		--k;
		int64_t lastC = c + (n - 1) * k;
		int64_t lastR = (k % 2 == 0) ? r : (n + 1 - r);

		if (lastC >= m) {
			return (m - c + 1) * n / 2 + odd(n) * odd(m - c + 1) * odd(r);
		}
		int64_t ans = (lastC - c + 1) * n / 2 + odd(n) * odd(lastC - c + 1) * odd(r);
		ans += angle(m - lastC, lastR);
		ans += angle(m - lastC, n + 1 - lastR);
		return ans;
	}

	int64_t solve(int64_t n, int64_t m, int64_t r, int64_t c, int64_t k) {
		r = min(r, n + 1 - r);
		if (n == 1) {
			return 1;
		} else if (k == 1) {
			int64_t ans = 1;
			for (auto x: {n - r, r - 1}) {
				for (auto y: {m - c, c - 1}) {
					ans += min(x, y);
				}
			}
			return ans;
		} else {
			return solveRight(n, m, r, c, k) + solveRight(n, m, r, m + 1 - c, k) - (n / 2 + odd(n) * odd(r));
		}
	}

	void solve(std::istream& in, std::ostream& out) {
	
		int64_t n, m, r, c, k;
		in >> n >> m >> r >> c >> k;

	
		out << solve(n, m, r, c, k) << "\n";

	}

	int64_t solveStupid(int64_t n, int64_t m, int64_t r, int64_t c, int64_t k) {
		vector<vector<int>> dist = make_vector<int>(n, m, -1);
		queue<pair<int, int>> q;
		q.push({r - 1, c - 1});

		dist[r - 1][c - 1] = 0;

		while (!q.empty()) {
			auto p = q.front();
			q.pop();
			for (int dx: {-1, 1}) {
				for (int dy: {-1, 1}) {
					auto pn = p;
					while (pn.first >= 0 && pn.first < n && pn.second >= 0 && pn.second < m) {
						if (dist[pn.first][pn.second] == -1) {
							dist[pn.first][pn.second] = dist[p.first][p.second] + 1;
							q.push(pn);
						}
						pn.first += dx;
						pn.second += dy;
					}
				}
			}
		}

		int ans = 0;
		for (int i: range(n)) {
			for (int j: range(m)) {
				if (dist[i][j] > -1 && dist[i][j] <= k) {
					++ans;
				}
			}
		}
		return ans;
	}
};


int main() {
	std::ios_base::sync_with_stdio(false);
	AdaBishop solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	in.tie(nullptr);
	out << std::fixed;
	out.precision(20);
	int n;
in >> n;
for(int i = 0; i < n; ++i) {
	solver.solve(in, out);
}

	return 0;
}
