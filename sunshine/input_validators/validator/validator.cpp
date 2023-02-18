#include "validator.h"

void run() {
	int n = Int(1, Arg("n"));
	Space();
	int k = Int(1, Arg("k"));
	Endl();

	assert(k <= n);

	SpacedFloats(n, 0.0, 1.0);
}
