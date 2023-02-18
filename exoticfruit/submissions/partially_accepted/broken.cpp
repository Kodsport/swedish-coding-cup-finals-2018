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

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);

	ll n;
	int k;
	cin >> n >> k;

	vi b(k), c(k), d(k);
	rep(i,0,k) cin >> b[i] >> c[i] >> d[i];

	ld lo = 0, hi = 2e9;
	ld res = -1;

	rep(_,0,300){
		ld mi = (lo + hi) / 2;
		if(mi == lo) break;

		ll tot = 0;
		bool isbig = false;
		res = 0;
		rep(i,0,k){
			ll x;
			if(c[i]==0){
				x = 0;
			} else if(d[i]==0){
				if(c[i]-b[i] >= mi) x = 1;
				else x = 0;
			} else {
				ld y = ld(d[i])*c[i] /(mi+b[i]);
				ld z = round(sqrt(y));
				while(y < z*(z+1)) --z;
				while(y >= z*(z+1)) ++z;
				if(z >= d[i]+n) isbig = true;
				x = z - d[i]+0.1;
			}
			tot += x;
			if(tot >= n) isbig = true;

			if(x+d[i] > 0)
				res += x*(c[i]*1./(x+d[i]) - b[i]);
		}
		res += (n-tot)*mi;
		
		if(isbig)
			lo = mi;
		else
			hi = mi;
	}
	cout.precision(15);
	cout << res << endl;
}
