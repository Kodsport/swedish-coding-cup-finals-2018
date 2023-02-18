#include "validator.h"

typedef long long ll;

void run() {
	ll n = Int(1, Arg("n"));
	Space();
	ll m = Int(1, Arg("m"));
	Space();
	int k = Int(0, Arg("k"));
	Endl();
	assert(n > 1 || m > 1);

	bool exact = Arg("strict");
	if (exact) assert(n == 2);
	map<pair<ll, ll>, int> seen;
	for (int i = 0; i < k; i++) {
		ll y = Int(1, n);
		Space();
		ll x = Int(1, m);
		Endl();
		assert(!(x == 1 && y == 1));
		assert(!(x == m && y == n));
		assert(!seen[make_pair(x,y)]++);
	}
}
