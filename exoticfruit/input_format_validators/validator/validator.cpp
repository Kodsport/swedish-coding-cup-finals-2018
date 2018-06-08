#include "validator.h"

void run() {
	int dlim = Arg("d");
	int nozer = Arg("nozero", 0);

	Int(1, Arg("n"));
	Space();
	int k = Int(1, Arg("k"));
	Endl();

	for (int i = 0; i < k; i++) {
		int b = Int(0, 1000000000);
		Space();
		int c = Int(0, 1000000000);
		Space();
		int d = Int(0, dlim);
		Endl();
		if (nozero) {
			assert(b > 0);
			assert(c > 0);
			assert(d > 0);
		}
	}
}
