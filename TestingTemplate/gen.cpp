#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(atoi(argv[1]));
	int n = 5;
	cout << n << endl;
	for(int i = 0; i < n; i ++) {
		cout << (rand() % n + 1) << " ";
	}
	cout << endl;
}