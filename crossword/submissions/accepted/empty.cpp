#include <iostream>
using namespace std;

int main() {
	int T, N, M;
	cin >> T >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << '.';
		}
		cout << endl;
	}
}
