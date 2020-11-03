#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")
#define endl "\n"
typedef long long ll;
template<class T, class T2> inline ostream &operator <<(ostream &out, const pair<T, T2> &x) { out << x.first << " " << x.second; return out;}
template<class T, class T2> inline istream &operator >>(istream &in, pair<T, T2> &x) { in >> x.first >> x.second; return in;}
template<class T, class T2> inline bool chkmax(T &x, const T2 &y) { return x < y ? x = y, 1 : 0; }
template<class T, class T2> inline bool chkmin(T &x, const T2 &y) { return x > y ? x = y, 1 : 0; }
const ll mod = 1e9 + 7;
#define out(x) "{" << (#x) << ": " << x << "} "
 
const int MAX_N = 410;
int dp[MAX_N][MAX_N][MAX_N][3];
int n;
string in;
int cnt[MAX_N][3];
vector<int> ind[3];
 
int getCode(char c) {
	if(c == 'R') {
		return 0;
	} else if(c == 'G') {
		return 1;
	} else if(c == 'Y') {
		return 2;
	}
}
 
signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	cin >> in;
 
	for(int i = 0; i < n; i ++) {
		if(i != 0) {
			for(int j = 0; j < 3; j ++) {
				cnt[i][j] = cnt[i - 1][j];
			}
		}
		cnt[i][getCode(in[i])] ++;
		ind[getCode(in[i])].push_back(i);
	}
 
	for(int i = 0; i <= ind[0].size(); i ++) {
		for(int j = 0; j <= ind[1].size(); j ++) {
			for(int k = 0; k <= ind[2].size(); k ++) {
				for(int last = 0; last < 3; last ++) {
					dp[i][j][k][last] = mod;
				}
			}
		}
	}
	
	dp[0][0][0][0] = dp[0][0][0][1] = dp[0][0][0][2] = 0;
 
	for(int i = 0; i <= ind[0].size(); i ++) {
		for(int j = 0; j <= ind[1].size(); j ++) {
			for(int k = 0; k <= ind[2].size(); k ++) {
				for(int last = 0; last < 3; last ++) {
					if(dp[i][j][k][last] == mod) {continue;}
					if(last != 0 && i != ind[0].size()) {
						int toGet = ind[0][i];
						int cost = max(0, cnt[toGet][1] - j) + max(0, cnt[toGet][2] - k);
						chkmin(dp[i + 1][j][k][0], dp[i][j][k][last] + cost);
					} 
					if(last != 1 && j != ind[1].size()) {
						int toGet = ind[1][j];
						int cost = max(0, cnt[toGet][0] - i) + max(0, cnt[toGet][2] - k);
						chkmin(dp[i][j + 1][k][1], dp[i][j][k][last] + cost);
					} 	
					if(last != 2 && k != ind[2].size()) {
						int toGet = ind[2][k];
						int cost = max(0, cnt[toGet][0] - i) + max(0, cnt[toGet][1] - j);
						chkmin(dp[i][j][k + 1][2], dp[i][j][k][last] + cost);
					} 
				}
			}
		}
	}
	
	int ans = mod;
	for(int i = 0; i < 3; i ++) {
		chkmin(ans, dp[ind[0].size()][ind[1].size()][ind[2].size()][i]);
	}
	
	if(ans >= mod) {
		cout << -1 << endl;
	} else {
		cout << ans << endl;
	}
	return 0;
}
 