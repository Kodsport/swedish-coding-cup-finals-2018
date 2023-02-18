#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

bool is_free(int r, int c, const vector<string>& G) {
    rep(dr,-1,2) rep(dc,-1,2) if (G[r+dr][c+dc] != '.') return false;
    return true;
}

const vector<pii> w = {
    pii(-2, -1),
    pii(-2, 0),
    pii(-2, 1),

    pii(-1, 2),
    pii(0, 2),
    pii(1, 2),

    pii(2, 1),
    pii(2, 0),
    pii(2, -1),

    pii(1, -2),
    pii(0, -2),
    pii(-1, -2),
};

int get_free(int r, int c, const vector<string>& G) {
    vector<bool> used(4);
    trav(it, w) {
        char ch = G[r+it.first][c+it.second];
        if (isdigit(ch)) used[ch - '1'] = true;
    }
    rep(i,0,4) if(!used[i]) return i + 1;
    assert(false && "could not greedily color");
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

    int R, C;
    cin >> R >> C;
    vector<string> G(R + 4, string(C + 4, '*'));
    rep(i,2,R+2) {
        string row;
        cin >> row;
        rep(j,2,C+2) G[i][j] = row[j - 2];
    }
    rep(i,2,R+2) {
        rep(j,2,C+2) {
            if (is_free(i, j, G)) {
                int w = get_free(i, j, G);
                rep(di,-1,2) rep(dj,-1,2) G[i+di][j+dj] = '0' + w;
            }
        }
    }
    rep(i,2,R+2) {
        rep(j,2,C+2) 
            if (G[i][j] == '.') return 43;
    }
    return 42;
}
