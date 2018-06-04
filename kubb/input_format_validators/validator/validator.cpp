#include "validator.h"

void run() {
	string mode = Arg("mode");
	int n = Int(1, Arg("n"));
	Endl();

	double a = Float(0, 1);
	Space();
	double b = Float(0, 1);
	Space();
	double c = Float(0, 1);
	Endl();

	if (mode == "trivial") {
		assert(n == 5);
		assert(a == 0);
		assert(c == 0);
	}
	else if (mode == "bad") {
		assert(b == 0);
	}
	else {
		assert(mode == "standard");
	}

	double su = a + b + c;
	assert(0.1 <= su);
	assert(su <= 0.9);
}
