#include <bits/stdc++.h>

using namespace std;

class fistream
{
public:
	static const int bufsz = 1 << 16;

	class buffer
	{
	public:
		int isz;
		char ibuf[bufsz];
	};

	FILE * pin;
	stack<buffer> ibuf_stk;
	int ipt, isz;
	char ibuf[bufsz];
	char word[64];

	fistream();
	fistream(FILE *);

	operator bool ();

	void stack_buffer();
	void next_buffer();
	bool trim();

	bool integral();
	bool floating();
	bool getline(char *, const int &);

	bool eof();

	void putback(const char &);

	fistream & operator >> (char &);
	fistream & operator >> (char *);
	fistream & operator >> (int &);
	fistream & operator >> (unsigned int &);
	fistream & operator >> (long long &);
	fistream & operator >> (unsigned long long &);
	fistream & operator >> (__int128 &);
	fistream & operator >> (unsigned __int128 &);
	fistream & operator >> (float &);
	fistream & operator >> (double &);
	fistream & operator >> (long double &);
} fin(stdin), fin_null(0);

fistream::fistream() : pin(0), ipt(bufsz), isz(bufsz)
{

}

fistream::fistream(FILE * pin) : pin(pin), ipt(bufsz), isz(bufsz)
{

}

inline fistream::operator bool ()
{
	return this != &fin_null;
}

inline void fistream::stack_buffer()
{
	if (ipt == 0)
	{
		ibuf_stk.push(buffer());
		ibuf_stk.top().isz = isz;
		memcpy(ibuf_stk.top().ibuf, ibuf, sizeof ibuf[0] * isz);
		isz = bufsz;
		ipt = isz;
	}
}

inline void fistream::next_buffer()
{
	if (ibuf_stk.empty())
		isz = fread(ibuf, 1, bufsz, pin);
	else
	{
		isz = ibuf_stk.top().isz;
		memcpy(ibuf, ibuf_stk.top().ibuf, sizeof ibuf[0] * isz);
		ibuf_stk.pop();
	}
	ipt = 0;
}

inline bool fistream::trim()
{
	for (; isz > 0; next_buffer())
	{
		for (; ipt < isz && ibuf[ipt] <= ' '; ipt++);
		if (ipt < isz)
			break;
	}
	return eof();
}

inline bool fistream::integral()
{
	if (trim())
		return false;

	int len = 0;
	bool vld = false;
	if (ibuf[ipt] == '-' || ibuf[ipt] == '+')
		word[len++] = ibuf[ipt++];
	for (; isz > 0; next_buffer())
	{
		for (; ipt < isz && isdigit(ibuf[ipt]); ipt++)
		{
			word[len++] = ibuf[ipt];
			vld = true;
		}
		if (ipt < isz)
			break;
	}
	word[len] = 0;

	return vld;
}

inline bool fistream::floating()
{
	if (trim())
		return false;

	int len = 0;
	bool vld = false, rht = false;
	if (ibuf[ipt] == '-' || ibuf[ipt] == '+')
		word[len++] = ibuf[ipt++];
	for (; isz > 0; next_buffer())
	{
		for (; ipt < isz && (isdigit(ibuf[ipt]) || ibuf[ipt] == '.'); ipt++)
		{
			if (ibuf[ipt] == '.')
			{
				if (rht)
					break;
				else
					rht = true;
			}
			else
				vld = true;
			word[len++] = ibuf[ipt];
		}
		if (ipt < isz)
			break;
	}
	word[len] = 0;

	return vld;
}

inline bool fistream::getline(char * s, const int & n)
{
	if (this == &fin_null || eof())
		return false;

	int slen = 0;
	for (; isz > 0; next_buffer())
	{
		for (; ipt < isz && slen < n - 1 && ibuf[ipt] != '\n'; ipt++)
			s[slen++] = ibuf[ipt];
		if (ipt < isz)
			break;
	}
	s[slen] = 0;
	for (; isz > 0 && ipt == isz; next_buffer());
	if (ipt < isz && ibuf[ipt] == '\n')
		ipt++;
	return true;
}

inline bool fistream::eof()
{
	for (; isz > 0 && ipt == isz; next_buffer());
	return isz == 0;
}

inline void fistream::putback(const char & c)
{
	if (ipt == 0)
		stack_buffer();
	ibuf[--ipt] = c;
}

inline fistream & fistream::operator >> (char & c)
{
	if (this == &fin_null || trim())
		return fin_null;
	else
	{
		c = ibuf[ipt++];
		return *this;
	}
}

inline fistream & fistream::operator >> (char * s)
{
	if (this == &fin_null || trim())
		return fin_null;

	int slen = 0;
	for (; isz > 0; next_buffer())
	{
		for (; ipt < isz && ibuf[ipt] > ' '; ipt++)
			s[slen++] = ibuf[ipt];
		if (ipt < isz)
			break;
	}
	s[slen] = 0;

	return *this;
}

inline fistream & fistream::operator >> (int & x)
{
	if (this == &fin_null || !(this->integral()))
		return fin_null;

	int i = 0, sgn;
	int ans = 0;
	if (word[0] == '-')
		sgn = -1, i++;
	else if (word[0] == '+')
		sgn = 1, i++;
	else
		sgn = 1;
	for (; word[i]; i++)
		ans = ans * 10 + word[i] - '0';
	x = ans * sgn;

	return *this;
}

inline fistream & fistream::operator >> (unsigned int & x)
{
	if (this == &fin_null || !(this->integral()))
		return fin_null;

	int i = 0, sgn;
	int ans = 0;
	if (word[0] == '-')
		sgn = -1, i++;
	else if (word[0] == '+')
		sgn = 1, i++;
	else
		sgn = 1;
	for (; word[i]; i++)
		ans = ans * 10 + word[i] - '0';
	x = ans * sgn;

	return *this;
}

inline fistream & fistream::operator >> (long long & x)
{
	if (this == &fin_null || !(this->integral()))
		return fin_null;

	int i = 0, sgn;
	long long ans = 0;
	if (word[0] == '-')
		sgn = -1, i++;
	else if (word[0] == '+')
		sgn = 1, i++;
	else
		sgn = 1;
	for (; word[i]; i++)
		ans = ans * 10 + word[i] - '0';
	x = ans * sgn;

	return *this;
}

inline fistream & fistream::operator >> (unsigned long long & x)
{
	if (this == &fin_null || !(this->integral()))
		return fin_null;

	int i = 0, sgn;
	long long ans = 0;
	if (word[0] == '-')
		sgn = -1, i++;
	else if (word[0] == '+')
		sgn = 1, i++;
	else
		sgn = 1;
	for (; word[i]; i++)
		ans = ans * 10 + word[i] - '0';
	x = ans * sgn;

	return *this;
}

inline fistream & fistream::operator >> (__int128 & x)
{
	if (this == &fin_null || !(this->integral()))
		return fin_null;

	int i = 0, sgn;
	__int128 ans = 0;
	if (word[0] == '-')
		sgn = -1, i++;
	else if (word[0] == '+')
		sgn = 1, i++;
	else
		sgn = 1;
	for (; word[i]; i++)
		ans = ans * 10 + word[i] - '0';
	x = ans * sgn;

	return *this;
}

inline fistream & fistream::operator >> (unsigned __int128 & x)
{
	if (this == &fin_null || !(this->integral()))
		return fin_null;

	int i = 0, sgn;
	__int128 ans = 0;
	if (word[0] == '-')
		sgn = -1, i++;
	else if (word[0] == '+')
		sgn = 1, i++;
	else
		sgn = 1;
	for (; word[i]; i++)
		ans = ans * 10 + word[i] - '0';
	x = ans * sgn;

	return *this;
}

inline fistream & fistream::operator >> (float & x)
{
	if (this == &fin_null || !(this->floating()))
		return fin_null;

	int i = 0, sgn;
	bool vis = false;
	float ans = 0, factor = 1;
	if (word[0] == '-')
		sgn = -1, i++;
	else if (word[0] == '+')
		sgn = 1, i++;
	else
		sgn = 1;
	for (; word[i]; i++)
	{
		if (word[i] == '.')
		{
			vis = true;
			continue;
		}

		if (!vis)
			ans = ans * 10 + word[i] - '0';
		else
		{
			factor /= 10;
			ans += factor * (word[i] - '0');
		}
	}
	x = ans * sgn;

	return *this;
}

inline fistream & fistream::operator >> (double & x)
{
	if (this == &fin_null || !(this->floating()))
		return fin_null;

	int i = 0, sgn;
	bool vis = false;
	double ans = 0, factor = 1;
	if (word[0] == '-')
		sgn = -1, i++;
	else if (word[0] == '+')
		sgn = 1, i++;
	else
		sgn = 1;
	for (; word[i]; i++)
	{
		if (word[i] == '.')
		{
			vis = true;
			continue;
		}

		if (!vis)
			ans = ans * 10 + word[i] - '0';
		else
		{
			factor /= 10;
			ans += factor * (word[i] - '0');
		}
	}
	x = ans * sgn;

	return *this;
}

inline fistream & fistream::operator >> (long double & x)
{
	if (this == &fin_null || !(this->floating()))
		return fin_null;

	int i = 0, sgn;
	bool vis = false;
	long double ans = 0, factor = 1;
	if (word[0] == '-')
		sgn = -1, i++;
	else if (word[0] == '+')
		sgn = 1, i++;
	else
		sgn = 1;
	for (; word[i]; i++)
	{
		if (word[i] == '.')
		{
			vis = true;
			continue;
		}

		if (!vis)
			ans = ans * 10 + word[i] - '0';
		else
		{
			factor /= 10;
			ans += factor * (word[i] - '0');
		}
	}
	x = ans * sgn;

	return *this;
}

class fostream
{
public:
	static const int bufsz = 1 << 16;

	FILE * pout;
	int opt;
	char obuf[bufsz];
	char word[64];
	int pcs;
	string format_float, format_double, format_long_double;

	class precision
	{
	public:
		int pcs;

		precision() : pcs(0)
		{

		}

		precision(const int & pcs) : pcs(pcs)
		{

		}
	};

	fostream();
	fostream(FILE *);
	~fostream();

	void fprecision(const int &);
	fostream & operator << (const precision &);

	fostream & operator << (const char &);
	fostream & operator << (const char *);
	fostream & operator << (const int &);
	fostream & operator << (const unsigned int &);
	fostream & operator << (const long long &);
	fostream & operator << (const unsigned long long &);
	fostream & operator << (const __int128 &);
	fostream & operator << (const unsigned __int128 &);
	fostream & operator << (const float &);
	fostream & operator << (const double &);
	fostream & operator << (const long double &);

	void flush();
} fout(stdout), ferr(stderr);

const char fendl = '\n';

fostream::fostream() : pout(0), opt(0), pcs(3), format_float("%.3f"), format_double("%.3lf"), format_long_double("%.3Lf")
{

}

fostream::fostream(FILE * pout) : pout(pout), opt(0), pcs(3), format_float("%.3f"), format_double("%.3lf"), format_long_double("%.3Lf")
{

}

fostream::~fostream()
{
	flush();
}

inline void fostream::fprecision(const int & x)
{
	pcs = x;
	sprintf(word, "%%.%d", pcs);
	(format_float = word) += "f";
	(format_double = word) += "lf";
	(format_long_double = word) += "Lf";
}

inline fostream & fostream::operator << (const precision & rhs)
{
	fprecision(rhs.pcs);
	return *this;
}

inline fostream & fostream::operator << (const char & c)
{
	obuf[opt++] = c;
	if (opt == bufsz)
		flush();
	return *this;
}

inline fostream & fostream::operator << (const char * s)
{
	for (int i = 0; s[i]; i++)
	{
		obuf[opt++] = s[i];
		if (opt == bufsz)
			flush();
	}
	return *this;
}

inline fostream & fostream::operator << (const int & x)
{
	int len = 0;
	unsigned int y;
	if (x < 0)
		word[len++] = '-', y = -x;
	else
		y = x;
	if (y == 0)
		word[len++] = '0';
	else
	{
		for (; y > 0; y /= 10)
			word[len++] = '0' + y % 10;
	}
	reverse(word + (x < 0 ? 1 : 0), word + len);
	word[len] = 0;
	*this << word;
	return *this;
}

inline fostream & fostream::operator << (const unsigned int & x)
{
	int len = 0;
	if (x == 0)
		word[len++] = '0';
	else
	{
		for (unsigned int y = x; y > 0; y /= 10)
			word[len++] = '0' + y % 10;
	}
	reverse(word, word + len);
	word[len] = 0;
	*this << word;
	return *this;
}

inline fostream & fostream::operator << (const long long & x)
{
	int len = 0;
	unsigned long long y;
	if (x < 0)
		word[len++] = '-', y = -x;
	else
		y = x;
	if (y == 0)
		word[len++] = '0';
	else
	{
		for (; y > 0; y /= 10)
			word[len++] = '0' + y % 10;
	}
	reverse(word + (x < 0 ? 1 : 0), word + len);
	word[len] = 0;
	*this << word;
	return *this;
}

inline fostream & fostream::operator << (const unsigned long long & x)
{
	int len = 0;
	if (x == 0)
		word[len++] = '0';
	else
	{
		for (unsigned long long y = x; y > 0; y /= 10)
			word[len++] = '0' + y % 10;
	}
	reverse(word, word + len);
	word[len] = 0;
	*this << word;
	return *this;
}

inline fostream & fostream::operator << (const __int128 & x)
{
	int len = 0;
	unsigned __int128 y;
	if (x < 0)
		word[len++] = '-', y = -x;
	else
		y = x;
	if (y == 0)
		word[len++] = '0';
	else
	{
		for (; y > 0; y /= 10)
			word[len++] = '0' + y % 10;
	}
	reverse(word + (x < 0 ? 1 : 0), word + len);
	word[len] = 0;
	*this << word;
	return *this;
}

inline fostream & fostream::operator << (const unsigned __int128 & x)
{
	int len = 0;
	if (x == 0)
		word[len++] = '0';
	else
	{
		for (unsigned __int128 y = x; y > 0; y /= 10)
			word[len++] = '0' + y % 10;
	}
	reverse(word, word + len);
	word[len] = 0;
	*this << word;
	return *this;
}

inline fostream & fostream::operator << (const float & x)
{
	sprintf(word, format_float.c_str(), x);
	*this << word;
	return *this;
}

inline fostream & fostream::operator << (const double & x)
{
	sprintf(word, format_double.c_str(), x);
	*this << word;
	return *this;
}

inline fostream & fostream::operator << (const long double & x)
{
	sprintf(word, format_long_double.c_str(), x);
	*this << word;
	return *this;
}

inline void fostream::flush()
{
	if (opt > 0)
	{
		fwrite(obuf, 1, opt, pout);
		opt = 0;
	}
}

inline fostream::precision fsetprecision(const int & x)
{
	return fostream::precision(x);
}

typedef long long itype;
typedef long double ftype;

const ftype pi = acosl(-1); // 3.1415926535897932384626433832795l
const ftype radian = 180 / pi; // 57.295779513082320876798154814105l
const ftype eps = 1e-15l;
const int inf = 0x7f7f7f7f;
const long long infll = 0x7f7f7f7f7f7f7f7fll;
const ftype infl = 1e20l;

template <class T>
inline int sgn(const T & x)
{
	return (x > eps) - (x < -eps);
}

template <class T>
inline T sqr(const T & x)
{
	return x * x;
}

#define Vector Point

template <class T>
class Point
{
public:
	vector<T> xv;

	Point(void)
	{

	}

	Point(const T & n) : xv(n, 0)
	{

	}

	Point(const vector<T> & xv) : xv(xv)
	{

	}

	template <class S>
	Point(const Point<S> & src) : xv(src.xv)
	{

	}

	T & operator [] (const int & i)
	{
		return xv[i];
	}

	Vector operator + (const Vector & rhs) const
	{
		Vector ans(xv);
		for (int i = 0; i < xv.size(); i++)
			ans[i] += rhs.xv[i];
		return ans;
	}

	Vector operator - (const Vector & rhs) const
	{
		Vector ans(xv);
		for (int i = 0; i < xv.size(); i++)
			ans[i] -= rhs.xv[i];
		return ans;
	}

	T length(void) const
	{
		T ans = 0;
		for (const auto & x : xv)
			ans += sqr(x);
		return sqrtl(ans);
	}

	T length2(void) const
	{
		T ans = 0;
		for (const auto & x : xv)
			ans += sqr(x);
		return ans;
	}

	T distance(const Point & rhs) const
	{
		return (rhs - *this).length();
	}

	T distance2(const Point & rhs) const
	{
		return (rhs - *this).length2();
	}

	Vector operator * (const T & rhs) const
	{
		Vector ans(xv);
		for (auto & x : ans.xv)
			x *= rhs;
		return ans;
	}

	Vector operator / (const T & rhs) const
	{
		Vector ans(xv);
		for (auto & x : ans.xv)
			x /= rhs;
		return ans;
	}

	T operator & (const Vector & rhs) const
	{
		T ans = 0;
		for (int i = 0; i < xv.size(); i++)
			ans += xv[i] * rhs.xv[i];
		return ans;
	}

	T dot(const Point & lhs, const Point & rhs) const
	{
		return (lhs - *this) & (rhs - *this);
	}

	bool operator == (const Point & rhs) const
	{
		for (int i = 0; i < xv.size(); i++)
		{
			if (sgn(xv[i] - rhs.xv[i]) != 0)
				return false;
		}
		return true;
	}

	bool operator != (const Point & rhs) const
	{
		for (int i = 0; i < xv.size(); i++)
		{
			if (sgn(xv[i] - rhs.xv[i]) != 0)
				return true;
		}
		return false;
	}

	Point project(const Point & p, const Point & q) const
	{
		if (p == q)
			return p;
		else
			return p + (q - p) * p.dot(q, *this) / p.distance2(q);
	}

	T distance_to_line(const Point & p, const Point & q) const
	{
		if (p == q)
			return distance(p);
		else
			return distance(project(p, q));
	}

	T distance_to_segment(const Point & p, const Point & q) const
	{
		if (p == q)
			return distance(p);
		else if (p.dot(q, *this) < 0)
			return distance(p);
		else if (q.dot(p, *this) < 0)
			return distance(q);
		else
			return distance_to_line(p, q);
	}
};

inline void Assert(const bool & b)
{
	if (!b)
		for (; ; );
}

template <class T>
inline bool non_zero(const T & x)
{
	return x != 0;
}

int main(void)
{
#ifndef ONLINE_JUDGE
	freopen("MINDIST.in", "r", stdin);
#endif

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	fout << fsetprecision(20);

	int T;
	fin >> T;
	for (int TN = 0; TN < T; TN++)
	{
		int n;
		fin >> n;
		vector<int> a(n), b(n), c(n), d(n);
		Point<ftype> A(n), B(n), C(n), D(n);
		for (int i = 0; i < n; i++)
		{
			fin >> a[i];
			A[i] = a[i];
		}
		for (int i = 0; i < n; i++)
		{
			fin >> b[i];
			B[i] = b[i];
		}
		for (int i = 0; i < n; i++)
		{
			fin >> c[i];
			C[i] = c[i];
		}
		for (int i = 0; i < n; i++)
		{
			fin >> d[i];
			D[i] = d[i];
		}

		ftype ans = min(min(A.distance_to_segment(C, D), B.distance_to_segment(C, D)),
						min(C.distance_to_segment(A, B), D.distance_to_segment(A, B)));

		for (int i = 0; i < n; i++)
		{
			b[i] -= a[i];
			d[i] -= c[i];
		}

		if (count_if(b.begin(), b.end(), non_zero<int>) > 0 && count_if(d.begin(), d.end(), non_zero<int>) > 0)
		{
			int g = 0;
			for (int i = 0; i < n; i++)
				g = __gcd(g, b[i]);
			for (int i = 0; i < n; i++)
				b[i] /= g;
			g = 0;
			for (int i = 0; i < n; i++)
				g = __gcd(g, d[i]);
			for (int i = 0; i < n; i++)
				d[i] /= g;

			bool bcl = false;
			for (int z = 0; z < 2; z++)
			{
				int r = z ? -1 : 1;
				bool flg = true;
				for (int i = 0; i < n; i++)
				{
					if (b[i] != d[i] * r)
					{
						flg = false;
						break;
					}
				}
				if (flg)
				{
					bcl = true;
					break;
				}
			}

			if (!bcl)
			{
				Point<ftype> AB = B - A, Av = A - A.project(C, D), Bv = B - B.project(C, D), V = Bv - Av;
				Point<ftype> P = A + AB * ((V & Av) / (V & AB) * -1);
				if (A.dot(B, P) > 0 && B.dot(A, P) > 0)
					ans = min(ans, P.distance_to_segment(C, D));
			}
		}

		fout << ans << fendl;
	}

	return 0;
}
