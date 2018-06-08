#include <vector>
#include <algorithm>
#include <tuple>
#include <cstring>
#include "validate.h"

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vector<string> read_input(istream &in) {
    int R, C;
    in >> R >> C;
    vector<string> G(R + 4, string(C + 4, '*'));
    rep(i,2,R+2) {
        string row;
        in >> row;
        rep(j,2,C+2) G[i][j] = row[j - 2];
    }
    return G;
}

vector<string> read_solution(int R, int C, istream &sol, feedback_function feedback) {
    vector<string> G(R + 4, string(C + 4, '*'));
    rep(i,2,R+2) {
        string row;
        if (!(sol >> row)) feedback("Missing row %d", i - 1);
        if ((int)row.size() != C) feedback("Row %d has length %d, expected %d", i - 1, (int)row.size(), C);
        rep(j,2,C+2) G[i][j] = row[j - 2];
    }
    string S;
    if (sol >> S) {
        feedback("Trailing output");
    }
    return G;
}

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

bool check_same(int r, int c, const vector<string>& G) {
    char w = G[r][c];
    rep(dr,-1,2) rep(dc,-1,2) if (G[r+dr][c+dc] != w) return false;
    return true;
}

bool check_surround_different(int r, int c, const vector<string>& G) {
    trav(it, w) {
        char ch = G[r+it.first][c+it.second];
        if (ch == G[r][c]) return false;
    }
    return true;
}

void check_solution(int R, int C, vector<string>& inp, vector<string>& ans, feedback_function feedback) {
    // check same squares are tilled
    rep(i,0,R) rep(j,0,C) {
        if (inp[i][j] == '*' && ans[i][j] != '*') feedback("row %d, col %d should be stone", i-1, j-1);
        if (inp[i][j] == '.' && !('1' <= ans[i][j] && ans[i][j] <= '4')) feedback("row %d, col %d should be a seed", i-1, j-1);
    }

    // check all 3x3 are same, and non-adjacent
    rep(i,2,R-2) {
        rep(j,2,C-2) {
            if (is_free(i, j, inp)) {
                rep(di,-1,2) rep(dj,-1,2) inp[i+di][j+dj] = 'x';

                if (!check_same(i, j, ans)) feedback("3x3 centered at %d, %d was not same seed", i-1, j-1);

                if (!check_surround_different(i, j, ans)) feedback("3x3 centered at %d, %d had adjacent of same color", i-1, j-1);
            }
        }
    }
}


int main(int argc, char **argv) {
    init_io(argc, argv);

    vector<string> inp, sol;
    inp = read_input(judge_in);
    int R = (int)inp.size(),
        C = (int)inp[0].size();
    sol = read_solution(R-4, C-4, cin, wrong_answer);
    check_solution(R, C, inp, sol, wrong_answer);
    accept();
}
