#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// #define double float

const double inf = (double)(1.0 / 0.0);

double A, B, C;

double bruteforce(int N) {
	double d = 1 - A - B - C;
	assert(0 <= A);
	assert(0 <= B);
	assert(0 <= C);
	assert((double)-1e-7 <= d);
	assert(d < 1);
	assert(N < 30);
	int canhit = (A > 0) | (B > 0) << 1 | (C > 0) << 2;

	vector<double> dp(1 << N);
	vector<int> best(1 << N);
	rep(mask, 1, (1 << N)) {
		if (mask % 2 == 0) {
			dp[mask] = dp[mask >> 1];
			best[mask] = best[mask >> 1] << 1;
			continue;
		}
		int mask2 = mask << 2;
		double res = inf;
		int wh = -20;
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
			if (e < res - 1e-10) {
				res = e;
				wh = 1 << (i + 1);
			} else if (e < res + 1e-10) {
				wh |= 1 << (i + 1);
			}
		}
		assert(wh != -20);
		dp[mask] = res;
		best[mask] = wh;
	}
	int at = (1 << N) - 1;
	while (at) {
		int aimSet = best[at];
		int aim = __builtin_ffs(aimSet) - 2, hit = aim;
		double r = (double)rand() / (double)(RAND_MAX + 1.0) / (1 - d);
		if (r < A)
			hit--;
		else if (r < A + B)
			;
		else
			hit++;
		if (hit != -1) at &= ~(1 << hit);
		cerr << ' ';
		rep(i,0,N) cerr << ((at >> i) & 1);
		cerr << endl;
		rep(i,-1,N+1) if (i == aim) cerr << '*'; else if (i == hit) cerr << '+'; else cerr << ' ';
		cerr << endl;
		cerr << endl;
		/*
		cerr << aim << " -> " << hit;
		if (aimSet & (aimSet-1)) {
			cerr << " (could also aim at";
			rep(i,0,N+2) if (aimSet & (1 << i)) cerr << " " << i-1;
			cerr << ")";
		}
		cerr << endl;
		*/
		// usleep(100000);
	}
	return dp.back();
}

int main() {
	srand((int)time(0));
	int N;
	cin >> N;
	double a, b, c;
	cin >> a >> b >> c;
	assert(N <= 26);
	::A = a;
	::B = b;
	::C = c;
	cout << setprecision(10) << fixed << bruteforce(N) << endl;
}
