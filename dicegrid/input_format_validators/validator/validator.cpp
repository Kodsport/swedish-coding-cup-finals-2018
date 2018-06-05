#include "validator.h"

void run() {
	int n = Int(1, Arg("n"));
	Space();
	int m = Int(1, Arg("m"));
	Space();
	int k = Int(0, Arg("k"));
	Endl();
	assert(n > 1 || m > 1);

	bool exact = Arg("exact");
	if (exact) assert(n == 2);
	map<pair<int, int>, int> seen;
	for (int i = 0; i < k; i++) {
		int y = Int(1, n);
		Space();
		int x = Int(1, m);
		Endl();
		assert(!(x == 1 && y == 1));
		assert(!(x == m && y == n));
		assert(!seen[make_pair(x,y)]++);
	}
}
