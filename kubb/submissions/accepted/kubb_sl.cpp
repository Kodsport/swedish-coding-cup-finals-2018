#include <bits/stdc++.h>
using namespace std;

#define double long double

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const double inf = 1.0 / 0.0;
#ifndef LIM
const int LIM = 26;
#endif

double rec(ll bits, int N, double A, double B, double C);
double rec2(ll bits, int N, double A, double B, double C, int x) {
	ll bit = 1LL << x;
	assert(bits & bit);
	if (x == 0) {
		bits >>= 1;
		N--;
		if (!bits) return 0;
		if (!(bits & 1)) {
			bits >>= 1;
			N--;
		}
		return rec(bits, N, A, B, C);
	}
	if (x == N-1) {
		bits &= ~bit;
		bit >>= 1;
		N--;
		if (!bits) return 0;
		if (!(bits & bit)) {
			bit >>= 1;
			N--;
		}
		return rec(bits, N, A, B, C);
	}

	bool up = (bits & (bit << 1));
	bool down = (bits & (bit >> 1));
	if (up && down)
		return rec(bits & ~bit, N, A, B, C);

	double res = 0;
	ll ubits = bits >> (x + 1);
	int un = N - (x + 1);
	if (!up) {
		ubits >>= 1;
		un--;
	}
	res += rec(ubits, un, A, B, C);
	ll lbits = bits & (bit - 1);
	int ln = x;
	if (!down) ln--;
	res += rec(lbits, ln, A, B, C);
	return res;
}

unordered_map<ll, double> mem;
double rec(ll bits, int N, double A, double B, double C) {
	double D = 1 - A - B - C;
	double& out = mem[bits];
	if (out != 0.0) return out;
	assert(bits & 1);
	assert(bits & (1LL << (N-1)));
	double res = inf;
	ll mask2 = bits << 2;
	ll canhit = (A > 0) | (B > 0) << 1 | (C > 0) << 2;
	rep(i,-1,N+1) if (mask2 & (canhit << (i+1))) {
		double miss = D;
		double e2 = 0;
		if (mask2 & (1LL << (i+1))) {
			e2 += A * rec2(bits, N, A, B, C, i - 1);
		}
		else miss += A;
		if (mask2 & (1LL << (i+2))) {
			e2 += B * rec2(bits, N, A, B, C, i);
		}
		else miss += B;
		if (mask2 & (1LL << (i+3))) {
			e2 += C * rec2(bits, N, A, B, C, i + 1);
		}
		else miss += C;
		assert(miss < 1);
		// e = 1 + e2 + miss * e
		double e = (1 + e2) / (1 - miss);
		res = min(res, e);
	}
	assert(res > 0);
	out = res;
	return res;
}

double solve(int N, double A, double B, double C, bool clear = true) {
	if (clear) {
		mem.clear();
		mem.reserve((ll)pow(1.618, N));
	}
	return rec((1LL << N) - 1, N, A, B, C);
}

int main() {
	int N;
	double a, b, c;
	cin >> N >> a >> b >> c;
	double res;
	if (N <= LIM) {
		res = solve(N, a, b, c);
	} else {
		int x = LIM;
		double r2 = solve(x, a, b, c);
		double r1 = solve(x-1, a, b, c, false);
		res = r2 + (r2 - r1) * (N - x);
	}
	cout << setprecision(15) << fixed << res << endl;
	return 0;
}
