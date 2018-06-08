#include "validator.h"

void run() {
	int t = Int(0, 5);
	Endl();
	int n = Int(1, 500);
	Space();
	int m = Int(1, 500);
	Endl();

	assert(n == (int)Arg("n"));
	assert(m == (int)Arg("m"));
	assert(t == (int)Arg("t"));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c = Char();
			assert(c == '.' || ('a' <= c && c <= 'z'));
		}
		Endl();
	}
}
