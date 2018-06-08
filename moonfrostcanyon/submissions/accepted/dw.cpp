#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = (a); i < (b); ++i)
#define rrep(i,a,b) for(int i = (b); i --> (a);)
#define all(v) (v).begin(),(v).end()
#define trav(x,v) for(auto &x : v)
#define sz(v) int(v.size())
typedef vector<int> vi;
typedef long long ll;
typedef pair<int,int> pii;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);

	int r, c;
	cin >> r >> c;
	vector<string> farm(r);
	trav(x, farm) cin >> x;

	rep(i,0,r) rep(j,0,c) if(farm[i][j]=='.'){
		vector<bool> seen(4, false);

		rep(d,0,3) rep(e,0,2) rep(t,0,2){
			int x = d, y = e ? 3 : -1;
			if(t) swap(x,y);
			x += i, y += j;
			if(0 <= x && 0 <= y && x < r && y < c &&
				farm[x][y] >= '1' && farm[x][y] <= '4')
					seen[farm[x][y]-'1'] = true;
		}
		rep(d,0,4) if(!seen[d]){
			rep(x,i,i+3) rep(y,j,j+3)
				farm[x][y] = '1'+d;
			break;
		}
	}
	trav(x, farm) cout << x << endl;
}
