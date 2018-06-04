#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const double inf = 1.0 / 0.0;
const double MAGIC_FACTOR = 1.2;
#ifndef LIM
const int LIM = 27;
#endif

double rec(ll bits, ll obits, int N, int M, double A, double B, double C);
double rec2(ll bits, ll obits, int N, int M, double A, double B, double C, int x, int y) {
	ll bit = 1LL << x;
	ll obit = 1LL << y;
	assert(bits & bit);
	if (x == 0) {
		bits >>= 1;
		N--;
		if (!bits) return 0;
		if (!(bits & 1)) {
			bits >>= 1;
			N--;
		}
		obits >>= 1;
		return rec(bits, obits, N, M-1, A, B, C);
	}
	if (x == N-1) {
		bits &= ~bit;
		bit >>= 1;
		obits &= ~obit;
		obit >>= 1;
		obits |= obit;
		N--;
		if (!bits) return 0;
		if (!(bits & bit)) {
			bit >>= 1;
			N--;
		}
		return rec(bits, obits, N, M-1, A, B, C);
	}

	bool up = (bits & (bit << 1));
	bool down = (bits & (bit >> 1));
	if (up && down) {
		ll hobits = obits >> (y+1) << y;
		ll lobits = obits & ((obit >> 1) - 1);
		return rec(bits & ~bit, lobits | hobits, N, M-1, A, B, C);
	}

	double res = 0;
	ll ubits = bits >> (x + 1);
	ll uobits = obits >> (y + 1);
	int un = N - (x + 1);
	if (!up) {
		ubits >>= 1;
		un--;
	}
	res += rec(ubits, uobits, un, M-1 - y, A, B, C);

	ll lbits = bits & (bit - 1);
	ll lobits = (obits & (obit - 1)) | (1LL << (y-1));
	int ln = x;
	if (!down) ln--;
	res += rec(lbits, lobits, ln, y, A, B, C);
	return res;
}

struct Mem {
	double* ptr = 0;
	unordered_map<ll, double> map;
	double& operator[](ll x) {
		if (ptr) return ptr[x];
		else return map[x];
	}
};
vector<Mem> mem;
double rec(ll bits, ll obits, int N, int M, double A, double B, double C) {
	assert(obits < (1LL << M));
	double D = 1 - A - B - C;
	double& out = mem[M][obits];
	if (out != 0.0) return out;
	assert(bits & 1);
	assert(bits & (1LL << (N-1)));
	double res = inf;
	ll mask2 = bits << 2;
	ll canhit = (A > 0) | (B > 0) << 1 | (C > 0) << 2;
	int ya = 0, yb = 0, yc = 0, yd = 0;
	rep(i,-1,N+1) {
		ya = yb, yb = yc, yc = yd;
		yd += (int)((mask2 >> (i+3)) & 1);
		if (!(mask2 & (canhit << (i+1)))) continue;
		double miss = D;
		double e2 = 0;
		if (mask2 & (1LL << (i+1))) {
			e2 += A * rec2(bits, obits, N, M, A, B, C, i - 1, ya);
		}
		else miss += A;
		if (mask2 & (1LL << (i+2))) {
			e2 += B * rec2(bits, obits, N, M, A, B, C, i, yb);
		}
		else miss += B;
		if (mask2 & (1LL << (i+3))) {
			e2 += C * rec2(bits, obits, N, M, A, B, C, i + 1, yc);
		}
		else miss += C;
		assert(miss < 1);
		// e = 1 + e2 + miss * e
		double e = (1 + e2) / (1 - miss);
		res = min(res, e);
	}
	assert(res > 0);
	assert(yd == M);
	out = res;
	return res;
}

double solve(int N, double A, double B, double C, bool clear = true) {
	if (clear) mem.clear();
	if ((int)mem.size() < N+1) mem.resize(N+1);
	rep(m,1,N+1) {
		Mem& s = mem[m];
		if (m*MAGIC_FACTOR <= N) {
			if (!s.ptr) s.ptr = new double[1LL << (m-1)]{} - (1LL << (m-1));
			s.map.clear();
		} else {
			s.ptr = 0;
		}
	}
	return rec((1LL << N) - 1, (1LL << N) - 1, N, N, A, B, C);
}

struct BS {
	__uint128_t bits = 0;
	__uint128_t bit(int x) { return (__uint128_t)1 << x; }
	bool operator[](int x) { return bits & bit(x); }
	void set(int x) { bits |= bit(x); }
	void unset(int x) { bits &= ~bit(x); }
	bool none() const { return bits == 0; }
};

bool operator<(const BS& a, const BS& b) { return a.bits < b.bits; }

map<BS, double> mem2;
double simpleRec(BS mask, int lo, double A, double B, double C) {
	if (mask.none()) return 0;
	double& out = mem2[mask];
	if (out != 0.0) return out;
	while (!mask[lo]) lo++;
	double d = 1 - A - B - C;
	assert(0 <= A);
	assert(0 <= B);
	assert(0 <= C);
	assert(-1e-8 <= d);
	assert(d < 1);

	double res = inf;
	rep(i,lo - 1, lo + 4) {
		double miss = d;
		double e2 = 0;
		bool any = false;
		if (mask[i-1] && A) {
			BS mask2 = mask; mask2.unset(i-1);
			e2 += A * simpleRec(mask2, lo, A, B, C);
			any = 1;
		}
		else miss += A;
		if (mask[i] && B) {
			BS mask2 = mask; mask2.unset(i);
			e2 += B * simpleRec(mask2, lo, A, B, C);
			any = 1;
		}
		else miss += B;
		if (mask[i+1] && C) {
			BS mask2 = mask; mask2.unset(i+1);
			e2 += C * simpleRec(mask2, lo, A, B, C);
			any = 1;
		}
		else miss += C;
		if (!any) continue;
		assert(miss < 1);
		// e = 1 + e2 + miss * e
		double e = (1 + e2) / (1 - miss);
		res = min(res, e);
	}
	out = res;
	return res;
}

double solveSimple1(int N, double A, double B, double C) {
	mem2.clear();
	BS bs{};
	rep(i,0,N) bs.set(i+2);
	return simpleRec(bs, 0, A, B, C);
}
double solveSimple(int N, double A, double B, double C) {
	return min(solveSimple1(N, A, B, C), solveSimple1(N, C, B, A));
}

int main() {
	int N;
	double a, b, c;
	cin >> N >> a >> b >> c;
	if (abs(solveSimple(20, a, b, c) - solve(20, a, b, c)) < 1e-8) {
		// Optimization: only do heavy work within the tricky region.
		cout << setprecision(15) << fixed << solveSimple(N, a, b, c) << endl;
		return 0;
	}
	// cerr << setprecision(15) << fixed << solveSimple(N, a, b, c) << endl;
	double res;
	if (N <= LIM) {
		res = solve(N, a, b, c);
	} else {
		int x = LIM - ((N ^ LIM) & 1);
		double r2 = solve(x, a, b, c);
		double r1 = solve(x-2, a, b, c, false);
		double r0 = solve(x-4, a, b, c, false);
		cerr << "approximate rel precision: " << setprecision(10) << fixed <<
			abs((r2 - r1) - (r1 - r0)) * 2 / abs(r2 - r1) << endl;
		res = r2 + (r2 - r1) * (N - x) / 2;
	}
	cout << setprecision(15) << fixed << res << endl;
	return 0;
}

int main2() {
	double a, b, c;
	cin >> a >> b >> c;
	// solve(LIM, a, b, c);
	double res_last = 0, dif_last = 0;
	for (int n = (LIM&1); n <= LIM; n += 2) if (n) {
		double res = solve(n, a, b, c, false);
		double dif3 = res - res_last;
		res_last = res;
		double dif4 = dif3 - dif_last;
		dif_last = dif3;
		cout << setprecision(15) << fixed;
		cout << setw(2) << n << ' ' << dif3 << ' ' << showpos << dif4 << noshowpos << endl;
	}
	return 0;
}
