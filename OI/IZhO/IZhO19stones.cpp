#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
typedef long long ll;
typedef unsigned long long ull;
template<class T, class T2> bool chkmax(T &a, const T2 &b) {return (a < b) ? a = b, 1 : 0;}
const int MAX_N = 1e3 + 10;
char tab[MAX_N][MAX_N];

///First we fix the color of every stone to '-', then for every row we greedily pick the columns which have the maximum number of '-' and turn them to '+'

int get(int n, int m) {
	int total = n * m;
	int ret = 0, retmask;
	for(int mask = 0; mask < (1 << total); mask ++) {
		for(int j = 0; j < total; j ++) {
			tab[j / m][j % m] = (bool)(mask & (1 << j));
		}
		int a = 0;
		for(int i = 0; i < n; i ++) {
			int curr = 0;
			for(int j = 0; j < m; j ++) {
				if(tab[i][j]) {
					curr ++;
				} else {
					curr --;
				}
			}
			if(curr > 0) {
				a ++;
			}
		}
		for(int j = 0; j < m; j ++) {
			int curr = 0;
			for(int i = 0; i < n; i ++) {
				if(tab[i][j]) {
					curr --;
				} else {
					curr ++;
				}
			}
			if(curr > 0) {
				a ++;
			}
		}
		if(chkmax(ret, a)) {
			retmask = mask;
		}
	}
	for(int j = 0; j < total; j ++) {
		tab[j / m][j % m] = (bool)(retmask & (1 << j));
	}
	cout << n << " " << m << " " << ret << endl;
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < m; j ++) {
			cout << tab[i][j] << " ";
		}
		cout << endl;
	}
	cout << "!" << endl;
	return ret;
}

int cnt[MAX_N];
char ans[MAX_N][MAX_N];
int getFast(int n, int m) {
	bool rev = 0;
	if(n > m) {
		rev = true;
		swap(n, m);
	}
	for(int i = 0; i < m; i ++) {
		cnt[i] = n;
	}
	int ret = max(n, m);
	int halfCnt = (m / 2) + 1;
	int gotten = 0, opti = 0;
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < m; j ++) {
			ans[i][j] = tab[i][j] = '-';
		}
	}
	for(int i = 0; i < n; i ++) {
		//sort(cnt, cnt + m);
		//reverse(cnt, cnt + m);
		vector<pair<int, int> > cpy;
		for(int j = 0; j < m; j ++) {
			cpy.push_back({-cnt[j], j});
		}
		sort(cpy.begin(), cpy.end());
		for(int j = 0; j < halfCnt; j ++) {
			cnt[cpy[j].second] --;
			ans[i][cpy[j].second] = '+';
		}
		gotten ++;
		int curr = gotten;
		for(int j = 0; j < m; j ++) {
			if(cnt[j] * 2 > n) {
				curr ++;
			}
		}
		if(chkmax(ret, curr)) {
			for(int i = 0; i < n; i ++) {
				for(int j = 0; j < m; j ++) {
					tab[i][j] = ans[i][j];
				}
			}
		}
	}
	if(rev) {
		for(int i = 0; i < n; i ++) {
			for(int j = 0; j < m; j ++) {
				if(tab[i][j] == '-') {
					tab[i][j] = '+';
				} else {
					tab[i][j] = '-';
				}
			}
		}
		for(int i = 0; i < n; i ++) {
			for(int j = 0; j < m; j ++) {
				if(i < j) {
					swap(tab[i][j], tab[j][i]);
				}
			}
		}
		swap(n, m);
	}
	int a = 0;
	for(int i = 0; i < n; i ++) {
		int curr = 0;
		for(int j = 0; j < m; j ++) {
			if(tab[i][j] == '+') {
				curr ++;
			} else {
				curr --;
			}
		}
		if(curr > 0) {
			a ++;
		}
	}
	for(int j = 0; j < m; j ++) {
		int curr = 0;
		for(int i = 0; i < n; i ++) {
			if(tab[i][j] == '+') {
				curr --;
			} else {
				curr ++;
			}
		}
		if(curr > 0) {
			a ++;
		}
	}
	//cout << a << " " << ret << endl;
	cout << a << endl;
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < m; j ++) {
			cout << tab[i][j];
		}
		cout << endl;
	}
	//assert(a == ret);
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int t;
	cin >> t;
	while(t --) {
		int n, m;
		cin >> n >> m;
		getFast(n, m);
	}
}
