#include "validator.h"

void run() {
	int r = Int(1, Arg("r"));
	Space();
	int c = Int(1, Arg("c"));
	Endl();
	string mode = Arg("mode");
	bool allTilled = false;
	if (mode == "tilled") allTilled = true;
	else if (mode == "r6") assert(r == 6);
	else assert(mode == "general");

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			char c = Char();
			assert(c == '.' || c == '*');
			if (allTilled) assert(c == '.');
		}
		Endl();
	}
}
