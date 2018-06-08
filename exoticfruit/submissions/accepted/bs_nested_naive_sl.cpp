// Same as bs_nested_sl.cpp, more or less, except with changed bs ranges
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define double long double

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	ll N;
	int K;
	cin >> N >> K;
	vector<double> b(K), c(K), d(K);
	rep(i,0,K) {
		cin >> b[i] >> c[i] >> d[i];
	}

	auto f = [&](int i, ll x) -> double {
		if (!x) return 0;
		return (double)x * (c[i] / (d[i] + (double)x) - b[i]);
	};
	auto f2 = [&](int i, ll x) -> double {
		// Bad precision, but long doubles should be enough
		return f(i, x) - f(i, x-1);
	};
	auto g = [&](double deriv) -> pair<ll, double> {
		ll a = 0;
		double b = 0;
		rep(i,0,K) {
			ll lo = 0, hi = 1LL << 40;
			while (hi - lo > 1) {
				ll mid = (lo + hi) / 2;
				if (f2(i, mid) >= deriv) lo = mid;
				else hi = mid;
			}
			a += lo;
			b += f(i, lo);
		}
		return {a, b};
	};

	double lo = 0, hi = 1e30 / 3;
	auto pa = g(lo);
	assert(g(hi).first == 0);
	if (pa.first <= N) {
		cerr << "can plant everything: " << pa.first << " vs " << N << endl;
		cout << setprecision(10) << fixed << pa.second << endl;
		return 0;
	} else {
		cerr << "if we plant everything (n = " << pa.first << "):" << endl;
		cerr << setprecision(20) << fixed << pa.second << endl;
	}

	rep(it,0,30*8) {
		double mid = (lo + hi) / 2;
		if (g(mid).first <= N) hi = mid;
		else lo = mid;
	}

	auto pa1 = g(lo);
	auto pa2 = g(hi);
	assert(pa1.first > pa2.first);
	assert(pa2.first <= N);

	cerr << scientific;
	cerr << lo << '\t' << pa1.first << '\t' << pa1.second << endl;
	cerr << hi << '\t' << pa2.first << '\t' << pa2.second << endl;
	cerr << "\t\t\t" << N << endl;

	ll ndif = pa1.first - pa2.first;
	double additionalCost = (lo + hi) / 2; // (pa1.second - pa2.second) / (double)ndif;
	assert(additionalCost >= 0);

	cerr << additionalCost << endl;

	double res = pa2.second + additionalCost * (double)(N - pa2.first);
	cout << setprecision(10) << fixed << res << endl;
}
