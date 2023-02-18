#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void smax(ll& a, ll b) { a = max(a, b); }

struct Die {
	array<int, 6> sides; // bottom, right, front, left, up, top
	static void rot(int& a, int& b, int& c, int& d) {
		int olda = a;
		a = b, b = c, c = d, d = olda;
	}
	int score() const { return sides[5]; }
	Die right() const {
		Die ret = *this;
		rot(ret.sides[0], ret.sides[1], ret.sides[5], ret.sides[3]);
		return ret;
	}
	Die down() const {
		Die ret = *this;
		rot(ret.sides[0], ret.sides[2], ret.sides[5], ret.sides[4]);
		return ret;
	}
	void print() const {
		cout << ' ' << sides[4] << endl;
		cout << sides[3] << sides[5] << sides[1] << endl;
		cout << ' ' << sides[2] << endl;
	}
};
bool operator<(const Die& a, const Die& b) { return a.sides < b.sides; }

ll solve(ll y, ll x) {
	ll r = 7 * (x + y + 2) / 2 + (x + y) % 2;
	const int tab1[] = {1, 2, 4, 4};
	const int tab2[] = {0, 0, 2, 1};
	const int tab3[] = {1, 0, 2, 4};
	const int tab4[] = {0, 0, 0, 1};
	if (y == 0) r -= tab1[x % 4];
	else if (y == 1) r -= tab2[x % 4];
	else if (x == 0) r -= tab3[y % 4];
	else if (x == 1) r -= tab4[y % 4];
	return r;
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	Die start;
	start.sides = {{1, 4, 2, 3, 5, 6}};
	queue<Die> q;
	q.push(start);
	map<Die, int> seen;
	while (!q.empty()) {
		Die d = q.front();
		q.pop();
		if (seen.count(d)) continue;
		seen[d];
		q.push(d.right());
		q.push(d.down());
	}
	int id = 0;
	trav(x, seen) x.second = id++;
	assert(id == 24);
	int startId = seen[start];
	vi right(id), down(id), scores(id);
	trav(pa, seen) {
		right[pa.second] = seen[pa.first.right()];
		down[pa.second] = seen[pa.first.down()];
		scores[pa.second] = pa.first.score();
	}

	ll N, M, K;
	cin >> N >> M >> K;

	map<ll, ll> activex;
	map<ll, ll> activey;
	vector<pair<ll, ll>> blockedItems;
	rep(i,0,K) {
		ll x, y;
		cin >> y >> x;
		--y, --x;
		activex[x];
		activey[y];
		blockedItems.emplace_back(x, y);
	}
	activex[0];
	activey[0];
	activex[M-1];
	activey[N-1];

	ll addAns = 0;
	auto renumber = [&](map<ll, ll>& m, ll& lim) {
		ll cur = 0;
		ll last = 0;
		trav(pa, m) {
			assert(pa.first >= last);
			ll dif = pa.first - last;
			ll skip = max((pa.first - last - 8) / 4 * 4, 0LL);
			last = pa.first;
			cur += dif - skip;
			addAns += skip * 7 / 2;
			pa.second = cur;
		}
		lim = cur + 1;
	};
	renumber(activex, M);
	renumber(activey, N);

	assert(N < INT_MAX);
	assert(M < INT_MAX);

	if (N*M > 1000000) {
		if (K == 0) {
			cout << solve(N-1, M-1) + addAns << endl;
			return 0;
		}
		cout << "error" << endl;
		return 0;
	}

	vector<vi> blocked(N, vi(M));
	trav(pa, blockedItems) {
		blocked[activey[pa.second]][activex[pa.first]] = 1;
	}

	vector<vector<ll>> dp[24];
	const ll inf = LLONG_MAX;
	rep(i,0,24) dp[i].assign(N, vector<ll>(M, -inf));
	dp[startId][0][0] = scores[startId];
	rep(y,0,N) rep(x,0,M) rep(i,0,24) {
		if (blocked[y][x]) dp[i][y][x] = -inf;
		if (x+1 < M) smax(dp[right[i]][y][x+1], dp[i][y][x] + scores[right[i]]);
		if (y+1 < N) smax(dp[down[i]][y+1][x], dp[i][y][x] + scores[down[i]]);
	}

	ll ret = -1;
	rep(i,0,24) smax(ret, dp[i][N-1][M-1]);
	if (ret < 0) cout << "impossible" << endl;
	else {
		ret += addAns;
		cout << ret << endl;
		cerr << "trivial answer: " << (ret == solve(N-1, M-1) + addAns ? "yes" : "no") << endl;
	}
}
