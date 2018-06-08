#include <iostream>
using namespace std;

int main() {
	int T, N, M;
	cin >> T >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int jj = j % 8;
			if (j < M/4*4) {
				int lim = (N-1)/4*4;
				if (i == 0) cout << "..aha..."[jj];
				else if (i == lim) cout << "a.....ah"[jj];
				else if (i < lim) {
					if (i % 2 == 0) cout << "aha.aha."[jj];
					else if (i % 4 == 1) cout << "..h.h...."[jj];
					else cout << "h.....h.."[jj];
				}
				else cout << '.';
			}
			else cout << '.';
		}
		cout << endl;
	}
}
