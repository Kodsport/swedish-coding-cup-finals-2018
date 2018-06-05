#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

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
		return x * (c[i] / (d[i] + x) - b[i]);
	};
	auto f2 = [&](int i, ll x) -> double {
		if (x == 1) return f(i, 1);
		// return f(i, x) - f(i, x-1);
		return c[i] * d[i] / (d[i] + x) / (d[i] + x - 1) - b[i];
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

	double lo = 0, hi = 1e30;
	if (g(lo).first <= N) {
		cout << setprecision(10) << fixed << g(lo).second << endl;
		return 0;
	}

	assert(g(hi).first == 0);
	rep(it,0,30*8) {
		double mid = (lo + hi) / 2;
		if (g(mid).first <= N) hi = mid;
		else lo = mid;
	}

	auto pa1 = g(lo);
	auto pa2 = g(hi);
	assert(pa1.first > pa2.first);
	assert(pa2.first <= N);
	ll ndif = pa1.first - pa2.first;
	double additionalCost = (pa1.second - pa2.second) / ndif;
	assert(additionalCost >= 0);
	double res = pa2.second + additionalCost * (N - pa2.first);
	cout << setprecision(10) << fixed << res << endl;
}
