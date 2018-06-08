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
	int N, M;
	cin >> N >> M;
	vector<string> grid(N);
	rep(i,0,N) cin >> grid[i];
	rep(j,0,M) rep(i,0,N) {
		if (grid[i][j] != '.') continue;
		rep(k,0,3) rep(l,0,3) assert(grid.at(i+k).at(j+l) == '.');
		set<char> used;
		if (j-1 >= 0) rep(k,0,3) used.insert(grid.at(i+k).at(j-1));
		if (i-1 >= 0) rep(k,0,3) used.insert(grid.at(i-1).at(j+k));
		if (i+3 < N) rep(k,0,3) used.insert(grid.at(i+3).at(j+k));
		used.erase('.');
		used.erase('*');
		assert(used.size() < 4);
		char color;
		do color = (char)('1' + rand() % 4);
		while (used.count(color));
		rep(k,0,3) rep(l,0,3) grid[i+k][j+l] = color;
	}

	rep(i,0,N) cout << grid[i] << endl;
}
