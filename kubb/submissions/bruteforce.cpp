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

double A, B, C;

double bruteforce(int N) {
	double d = 1 - A - B - C;
	assert(0 <= A);
	assert(0 <= B);
	assert(0 <= C);
	assert(-1e-9 <= d);
	assert(d < 1);
	assert(N < 30);
	int canhit = (A > 0) | (B > 0) << 1 | (C > 0) << 2;

	vector<double> dp(1 << N);
	rep(mask, 1, (1 << N)) {
		int mask2 = mask << 2;
		double res = inf;
		int first = -1, last = - 1;
		rep(i,-1,N+1) if (mask2 & (canhit << (i+1))) {
			double miss = d;
			double e2 = 0;
			if (mask2 & (1 << (i+1))) e2 += A * dp[mask &~ (1 << (i - 1))];
			else miss += A;
			if (mask2 & (1 << (i+2))) e2 += B * dp[mask &~ (1 << (i + 0))];
			else miss += B;
			if (mask2 & (1 << (i+3))) e2 += C * dp[mask &~ (1 << (i + 1))];
			else miss += C;
			assert(miss < 1);
			// e = 1 + e2 + miss * e
			double e = (1 + e2) / (1 - miss);
			res = min(res, e);
		}
		dp[mask] = res;
	}
	return dp.back();
}

int main() {
	int N;
	cin >> N;
	double a, b, c;
	cin >> a >> b >> c;
	::A = a;
	::B = b;
	::C = c;
	cout << setprecision(10) << fixed << bruteforce(N) << endl;
}
