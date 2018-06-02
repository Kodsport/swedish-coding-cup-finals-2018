#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

double solve(const vector<double>& a, int K) {
	int N = sz(a);
	vector<double> dp(K+1), next;
	dp[0] = 1;
	rep(i,0,N) {
		next.assign(K+1, 0.0);
		double p = a[i];
		rep(i,0,K) {
			next[i+1] = dp[i] * p;
			next[0] += dp[i] * (1 - p);
		}
		next[K] += dp[K];
		dp.swap(next);
	}
	return dp[K];
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	int N, K;
	cin >> N >> K;
	assert(1 <= K && K <= N);
	vector<double> a(N);
	rep(i,0,N) cin >> a[i];
	cout << setprecision(10) << fixed << solve(a, K) << endl;
}
