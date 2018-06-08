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
	N = min(N, 1000000LL);
	vector<double> b(K), c(K), d(K);
	auto f = [&](int i, ll x) -> double {
		if (!x) return 0;
		return x * (c[i] / (d[i] + x) - b[i]);
	};
	priority_queue<pair<double, int>> pq;
	rep(i,0,K) {
		cin >> b[i] >> c[i] >> d[i];
		pq.push({f(i, 1) - f(i, 0), i});
	}

	vi x(K);
	rep(it,0,N) {
		auto pa = pq.top();
		pq.pop();
		if (pa.first <= 0) break;
		int i = pa.second;
		x[i]++;
		pq.push({f(i, x[i]+1) - f(i, x[i]), i});
	}

	double win = 0;
	rep(i,0,K) win += f(i, x[i]);
	cout << setprecision(10) << fixed << win << endl;
}
