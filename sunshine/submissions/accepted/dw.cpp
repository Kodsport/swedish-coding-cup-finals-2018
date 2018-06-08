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
typedef long double ld;

struct ST {
	vector<ld> t;
	int n;

	ST(vector<ld> &p){
		n = sz(p);
		t.resize(2*n);
		rep(i,0,n) t[i+n] = p[i];
		rrep(j,1,n)
			t[j] = t[2*j] * t[2*j+1];
	}

	ld query(int fr, int to){
		ld res = 1;
		for(fr += n, to += n; fr < to; fr /= 2, to /= 2){
			if(fr&1) res *= t[fr++];
			if(to&1) res *= t[--to];
		}
		return res;
	}
};

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	cin >> n >> k;

	vector<ld> p(n);
	trav(x, p) cin >> x;

	ST prods(p);	

	vector<ld> dp(n+1, 1);
	rep(i,0,n){
		int j = i-k+1;
		dp[i+1] = dp[i];
		if(j >= 0){
			ld q = prods.query(j, i+1);
			if(j > 0) q *= (1-p[j-1])*dp[j-1];
			dp[i+1] -= q;
		}
	}
	cout.precision(10);
	cout << 1 - dp[n] << endl;
}
