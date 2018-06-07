#include "validator.h"

void run() {
	int blim = Arg("b");
	int dlim = Arg("d");

	Int(1, Arg("n"));
	Space();
	int k = Int(1, Arg("k"));
	Endl();

	for (int i = 0; i < k; i++) {
		Int(0, blim);
		Space();
		Int(0, 1000000000);
		Space();
		Int(0, dlim);
		Endl();
	}
}
