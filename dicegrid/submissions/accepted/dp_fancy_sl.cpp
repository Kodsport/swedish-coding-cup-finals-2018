#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#ifndef MARGIN
const int MARGIN = 6;
#endif

void smax(ll& a, ll b) { a = max(a, b); }
void smax(int& a, int b) { a = max(a, b); }

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

struct Iv {
	ll from, to;
	int bits, occ;
};
ostream& operator<<(ostream& os, const Iv& iv) {
	return os << "[" << iv.from << ", " << iv.to << ")@" << iv.bits;
}

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
	queue<pair<Die, bool>> q;
	q.push({start, false});
	map<Die, int> seen;
	while (!q.empty()) {
		auto pa = q.front();
		q.pop();
		Die d = pa.first;
		if (seen.count(d)) continue;
		seen[d] = pa.second;
		q.push({d.right(), !pa.second});
		q.push({d.down(), !pa.second});
	}
	int id = 0;
	vi parity(24);
	trav(x, seen) {
		parity[id] = x.second;
		x.second = id++;
	}
	assert(id == 24);
	int startId = seen[start];
	int beforeStartId = seen[start.down().down().down()];
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
			ll skip = max((pa.first - last - MARGIN) / 4 * 4, 0LL);
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

	vector<set<ll>> blocked(N);
	trav(pa, blockedItems) {
		blocked[activey[pa.second]].insert(activex[pa.first]);
	}

	int oddBits = 0, evenBits = 0;
	rep(i,0,24) {
		if (parity[i]) oddBits |= 1 << i;
		else evenBits |= 1 << i;
	}

	vector<Iv> intervals = {Iv{0, 1, 1 << beforeStartId, 0}}, ivs2;
	if (M > 1) intervals.push_back(Iv{1, M, 0, 0});

	auto stepRight = [&](int bits) {
		int bits2 = 0;
		rep(i,0,24) if (bits & (1 << i))
			bits2 |= 1 << right[i];
		return bits2;
	};

	rep(i,0,N) {
// cerr << "i = " << i << endl;

		trav(iv, intervals) if (iv.bits != -1 && iv.bits != 0) {
			int bits2 = 0;
			rep(i,0,24) if (iv.bits & (1 << i))
				bits2 |= 1 << down[i];
			iv.bits = bits2;
		}

// cerr << "initial intervals: ";
// trav(iv, intervals) cerr << iv << ' ';
// cerr << endl;

		ivs2.clear();
		set<ll>& bl = blocked[i];
		vector<ll> BL(all(bl));
		int j = 0, js = sz(BL);
		trav(iv, intervals) {
			for (;;) {
				if (iv.from == iv.to) break;
				if (j != js && BL[j] < iv.to) { // split
					ll it = BL[j];
					j++;
					if (iv.from != it)
						ivs2.push_back(Iv{iv.from, it, iv.bits, 0});
					ivs2.push_back(Iv{it, it + 1, 0, 1});
					iv.from = it + 1;
				} else {
					iv.occ = 0;
					ivs2.push_back(iv);
					break;
				}
			}
		}
		intervals.swap(ivs2);
		ivs2.clear();

// cerr << "removed intervals: ";
// trav(iv, intervals) cerr << iv << ' ';
// cerr << endl;

		int lastBits = 0;
		trav(iv, intervals) {
			if (iv.occ) {
				assert(iv.bits == 0);
				lastBits = 0;
				ivs2.push_back(iv);
				continue;
			}
			if (lastBits == -1 || (iv.bits == 0 && lastBits == 0 && !ivs2.empty())) {
				assert(!ivs2.empty());
				ivs2.back().to = iv.to;
				continue;
			}
			if (iv.bits == 0) {
				if (lastBits == 0) {
					ivs2.push_back(iv);
				}
				else for (ll i = iv.from; i < iv.to; i++) {
					lastBits = stepRight(lastBits);
					ivs2.push_back(Iv{i, i+1, lastBits, 0});
				}
			} else {
				int bits2 = stepRight(lastBits);
				iv.bits |= bits2;
				if (__builtin_popcount(iv.bits) == 12)
					iv.bits = -1;
				lastBits = iv.bits;
				ivs2.push_back(iv);
			}
		}
		intervals.swap(ivs2);
		assert(!intervals.empty());

// cerr << "filled intervals: ";
// trav(iv, intervals) cerr << iv << ' ';
// cerr << endl;
	}

	vi delta(24, -100);
	{
	vector<vi> dp[24];
	const int inf = 100000;
	rep(i,0,24) dp[i].assign(10, vi(10, -inf));
	dp[startId][0][0] = scores[startId];
	rep(y,0,10) rep(x,0,10) rep(i,0,24) {
		if (x+1 < 10) smax(dp[right[i]][y][x+1], dp[i][y][x] + scores[right[i]]);
		if (y+1 < 10) smax(dp[down[i]][y+1][x], dp[i][y][x] + scores[down[i]]);
	}
	rep(y,8,10) {
		int x = 9;
		rep(i,0,24) if (dp[i][y][x] >= 0) {
			assert(delta[i] == -100);
			delta[i] = dp[i][y][x] - 7 * (x + y) / 2;
		}
	}
	assert(count(all(delta), -100) == 0);
	}

	assert(!intervals.empty());
	if (intervals.back().bits == 0) cout << "impossible" << endl;
	else {
		int bits = intervals.back().bits;
		if (bits == -1) bits = ((N + M) % 2 == 0 ? evenBits : oddBits);
		ll ret = -100;
		rep(i,0,24) if (bits & (1 << i))
			smax(ret, delta[i]);
		assert(ret != -100);
		ret += 7 * (N-1 + M-1) / 2;
		ret += addAns;
		cout << ret << endl;
		cerr << "trivial answer: " << (ret == solve(N-1, M-1) + addAns ? "yes" : "no") << endl;
		cerr << "allowed subset size: " << __builtin_popcount(bits) << endl;
	}
}
